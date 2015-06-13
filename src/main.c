#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include "../inc/buttons.h"
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
#include "driverlib/gpio.h"
#include "../inc/debugging_utilities.h"
#include "../inc/computations.h"

#define FRAME_RATE 30

//declare global variables
uint16_t score = 0;
uint16_t time = 0;
uint16_t seconds = 0;
uint16_t fuel = 3000;
char multiplier = 0; //To be used to increase score according to where the lander lands
float ttime = .01; //TODO set to refresh rate
//declare variables
float yvelocity;                  //can be negative if vertical position is increasing
float xvelocity;                  //negative value moves left, positive moves right
float yposit = 9;                //initialize to topmost of landscape-oriented screen
float xposit = 64;                //initialize to middle of landscape-oriented screen
uint16_t angle = 4;                 //0 points upwards
float accel;                     //negative value causes increase in vertical position


int oldxposit;
int oldyposit;
int landerx;
int landery;



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

    PortE_Init();

    ButtonsInit();
    //Port F controls on-board buttons and LEDs which we use for debugging
    // (may not be necessary in later releases)
    PortF_Init();
    screen_init();
    FPUStackingEnable();

    // Trigger an interrupt every 30th of a second.
    // The period is in clock cycles, so we'll use a function from the libraries to fetch the clock config.
    SysTickPeriodSet(SysCtlClockGet() / (float)FRAME_RATE);
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
    process_input();
    update();
    check();
    render();
    tick();
    toggleLED(FRAME_RATE);      //Debugging heartbeat
}

void process_input() {

    uint8_t buttonState = ButtonsPoll(0, 0);
    bool noFuel = fuel == 0;

    bool jetButtonPressed = GPIO_PORTE_DATA_R & (1 << 0);
    bool rightButtonPressed = GPIO_PORTE_DATA_R & (1 << 1);
    bool leftButtonPressed = GPIO_PORTE_DATA_R & (1 << 2);
#define ONBOARDBUTTONS
    #ifdef ONBOARDBUTTONS
        leftButtonPressed = (buttonState & ALL_BUTTONS) == LEFT_BUTTON;
        rightButtonPressed = (buttonState & ALL_BUTTONS) == RIGHT_BUTTON;
    #endif

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
    if (angle <= -1) {
        angle = 0;
    }
    if (angle >= 9) {
        angle = 8;
    }
}
//update location and time
void update (void){
    time++;
    float vaccel = sinAngle(angle) * accel;
    float haccel = cosAngle(angle) * accel;

    yvelocity += vaccel * ttime;
    xvelocity += haccel * ttime;

    yposit += yvelocity * ttime;
    xposit += xvelocity * ttime;
}
//"check" the things that will kill you
void check (void){

    //declare boolean
    bool outOfTime = time >= 240;
    bool crashed = yposit < 0;
    bool tooFast = yvelocity >= 50;
    //check yposit
    if (crashed & tooFast) {
        die(CRASHED);

    } //(TODO)replace yposit check with terrain value check once terrain is generated
    if (crashed & (!tooFast)) {
        land();
    }
    if (yposit >= 128) {
        yposit = 128;     //TODO figure out how we want to handle the lander at the edges of the screen
    }
    //check time
    if (outOfTime) {
        die(OUTOFTIME);
    }

}

void render (void) {
    write_score(score);
    if (time % FRAME_RATE == 0) {
        write_time(seconds);
        seconds++;
    }
    write_fuel(fuel);
    oldxposit = xposit;
    oldyposit = yposit;
    if (angle == 0) {
        draw_bitmap(xposit, yposit, lander_left, 9, 7);
        landerx = 9;
        landery = 7;
    }
    else {
        draw_bitmap(xposit, yposit, lander, 7, 9);
        landerx = 7;
        landery = 9;
    }
    refresh();
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
    draw_dec(0, 2, score);
}

void write_fuel(uint16_t inFuel) {
    draw_dec(0, 5, inFuel);
}

void write_time(uint16_t seconds) {
    //FIXME: The seconds doesn't draw a leading zero for the tens place.
    //This leads to strange behaviour at the start of a new minute
    //FIXME: Doesn't handle over 10 minutes
    uint8_t min = (uint8_t) (seconds / 60);
    draw_dec(3, 10, min);
    draw_string(4, 10, ":", WHITE);
    uint8_t sec = seconds - min * 60;
    draw_dec(5, 10, sec);
}

void draw_terrain(void) {

    for(int i = 0; i < WIDTH; i++) {
        int terrainx = i;
        int terrainy = 10;
        storeTerrainX[i] = terrainx;
        storeTerrainY[i] = terrainy;
        draw_pixel(terrainx, terrainy, WHITE);
    }
}

void refresh(void) {
    draw_bitmap(oldxposit, oldyposit, black, landerx, 1);
}

