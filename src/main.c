#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include "inc/tm4c123gh6pm.h"
#include "../inc/LCD.h"
#include "../inc/PLL.h"
#include "../inc/initialization.h"
#include "../inc/main.h"
#include "../inc/images.h"
#include "driverlib/systick.h"
#include "driverlib/fpu.h"
#include "driverlib/interrupt.h"
#include "driverlib/sysctl.h"
#include "../inc/debugging_utilities.h"
#include "../inc/computations.h"

//declare global variables
uint16_t score = 0;
uint16_t time = 0;
uint16_t fuel = 1234;
char multiplier = 0; //To be used to increase score according to where the lander lands
int ttime = 1; //TODO set to refresh rate
//declare variables
int16_t vvelocity;                  //can be negative if vertical position is increasing
float accel;                     //negative value causes increase in vertical position
int16_t hvelocity;                  //negative value moves left, positive moves right
uint16_t altitude = 9;                //initialize to topmost of landscape-oriented screen
uint16_t xposit = 64;                //initialize to middle of landscape-oriented screen
uint16_t angle = 4;                 //0 points upwards

int storeTerrainX[WIDTH];
int storeTerrainY[WIDTH];

int main(void) {
    //Run initializations
    //Interrupts must be disabled here to prevent them
    //from triggering during an initialization
    IntMasterDisable();
    //Digital to analog converter for sounds.
    //We utilize a 6 bit 2R styled DAC
    DAC_Init();
    //Port F controls on-board buttons and LEDs which we use for debugging
    // (may not be necessary in later releases)
    PortF_Init();
    screen_init();
    FPUStackingEnable();

    // Trigger an interrupt every 30th of a second.
    // The period is in clock cycles, so we'll use a function from the libraries to fetch the clock config.
    SysTickPeriodSet(SysCtlClockGet() / 30.0);
    SysTickEnable();
    SysTickIntRegister(game_loop);
    SysTickIntEnable();

    IntMasterEnable();                                         //end of initializations, enable interrupts
    // initial state for screen
    fill_background(BLACK);
    // We need to stall here and wait for systick to trigger the game
    // loop at regular intervals.
    while(true);
}

void game_loop() {
    update();
    render();
    tick();
    toggleLED(30);      //Debugging heartbeat
}

void process_input() {
    bool noFuel = fuel == 0;
    bool jetButtonPressed = GPIO_PORTE_DATA_R & (1 << 0);
    bool rightButtonPressed = GPIO_PORTE_DATA_R & (1 << 1);
    bool leftButtonPressed = GPIO_PORTE_DATA_R & (1 << 2);

    if (!noFuel & jetButtonPressed) {
        accel = -0.811;    //negative accelaration forces lander opposite gravity
        fuel--;             //using fuel
    }
    if (noFuel | !jetButtonPressed) {
        accel = 1.622;
    }

    if (leftButtonPressed) {
        angle--;
    }
    if (rightButtonPressed) {
        angle++;
    }
}
//update location and time
void update (void){
    time++;
    float vaccel = sinAngle(angle) * accel;
    float haccel = cosAngle(angle) * accel;

    vvelocity += vaccel * ttime;
    hvelocity += haccel * ttime;

    altitude += 0 * ttime;
    xposit += 0 * ttime;
}
//"check" the things that will kill you
void check (void){

    //declare boolean
    bool outOfTime = time >= 240;
    bool crashed = altitude < 0;
    bool tooFast = vvelocity>=50;
    //check altitude
    if (crashed & tooFast) {
        die(CRASHED);

    } //(TODO)replace altitude check with terrain value check once terrain is generated
    if (crashed & (!tooFast)) {
        land();
    }
    if (altitude >= 128) {
        altitude = 128;     //TODO figure out how we want to handle the lander at the edges of the screen
    }
    //check time
    if (outOfTime) {
        die(OUTOFTIME);
    }
    if (angle <= -1) {
        angle = 0;
    }
    if (angle >= 9) {
        angle = 8;
    }
}

void render (void) {
    write_score(score);
    write_time(time);
    write_fuel(fuel);

    draw_bitmap(xposit, altitude, lander, 7, 9);
    draw_terrain();
}

//Output some sort of death message
void die(DeathType_t deathtype) {

    draw_string(40, 0, "You died!", WHITE);
    switch (deathtype) {
        case CRASHED:
            draw_string(40, 40, "Lost 20 fuel units.", WHITE);
            fuel =- 20;
            draw_string(40, 60, "Fuel left:", WHITE);
            write_fuel(fuel);
            draw_string(40, 80, "Current score:", WHITE);
            write_score(score);
            break;
        case OUTOFTIME:
            draw_string(40, 40, "Out of time!", WHITE);
            draw_string(40, 60, "Final score:", WHITE);
            write_score(score);
            //TODO write a slight delay
            break;
    }
}

void land() {
        draw_string(40, 20, "You landed!", WHITE);
    if(fuel>0){
        draw_string(40, 40, "Fuel remaining:", WHITE);
        write_fuel(fuel);
        //TODO write a slight delay
    }
}

void write_score(uint16_t score) {
    draw_dec(0, 0, score);
}

void write_fuel(uint16_t inFuel) {
    draw_dec(0, 5, inFuel);
}

void write_time(uint16_t time) {
    uint8_t min = (uint8_t) (time / 60);
    draw_dec(3, 0, min);
    draw_string(4, 0, ":", WHITE);
    uint8_t sec = time - min * 60;
    draw_dec(5, 0, sec);
}

void draw_terrain(void) {

    for(int i = 0; i < WIDTH; i++) {
        int terrainx = i;
        int terrainy = 10;
        storeTerrainX[i]={terrainx};
        storeTerrainY[i]={terrainy};
        draw_pixel(terrainx, terrainy, WHITE);
    }
}