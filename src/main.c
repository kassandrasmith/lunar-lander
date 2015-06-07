#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include "inc/tm4c123gh6pm.h"
#include "../inc/LCD.h"
#include "../inc/PLL.h"     //Phase-Lock-Loop, used to calibrate the clock spees
#include "../inc/initialization.h"		            //initialization sequences
#include "../inc/main.h"
#include "../inc/images.h"
#include "driverlib/systick.h"
#include "driverlib/fpu.h"
#include "driverlib/interrupt.h"

//define buttons
#define jetbutton (GPIO_PORTE_DATA_R & 0x01)
#define jetpushed 0x01
#define leftbutton (GPIO_PORTE_DATA_R & 0x02)
#define leftpushed 0x02
#define rightbutton (GPIO_PORTE_DATA_R & 0x04)
#define rightpushed 0x04

//declare global variables
uint16_t score;
uint16_t time;
uint16_t fuel = 1234;
char multiplier = 0; //To be used to increase score according to where the lander lands
int ttime = 1; //TODO set to refresh rate
//declare variables
int16_t vvelocity;                  //can be negative if vertical position is increasing
int16_t vaccel;                     //negative value causes increase in vertical position
int16_t hvelocity;                  //negative value moves left, positive moves right
uint16_t altitude=1;                //initialize to topmost of landscape-oriented screen
uint16_t xposit = 64;                //initialize to middle of landscape-oriented screen
uint16_t angle = 90;                 //0 points upwards
int accel = 1;


int main(void) {

    //Run initializations
    IntMasterDisable();
    DAC_Init();                                                 //Digital to analog converter necessary for sounds
    PortF_Init();
    screen_init();
    //FPUStackingEnable();

    // Frequency of Quartz= 80MHz / 30 Hz game engine = Interrupt rate +1
    // subtract one to get interrupts
    SysTickPeriodSet(270000u);
    SysTickEnable();
    SysTickIntRegister(game_loop);
    SysTickIntEnable();

    IntMasterEnable();                                         //end of initializations, enable interrupts
    //initial state for screen
    fill_background(0x0000);
    // We need to stall here and wait for systick to trigger the game
    // loop at regular intervals.
    while(true);
}

void game_loop() {

    draw_bitmap(10,10,lander,7,9);
}

void process_input() {
    bool noFuel = fuel==0;
    bool jetButtonPressed = jetbutton == jetpushed;
    bool rightButtonPressed = rightbutton == rightpushed;
    bool leftButtonPressed = leftbutton == leftpushed;
    if (!noFuel & jetButtonPressed) {
        accel = -0.811;    //negative accelaration forces lander opposite gravity
        fuel--;             //using fuel
    }
    if (noFuel | (!jetButtonPressed)) {
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
    const float angle = 3.14/2.0;
    const float accel = -0.5;
    float vaccel = sin(angle) * accel;
    float haccel = cos(angle) * accel;

    vvelocity += vaccel * ttime;
    hvelocity += haccel * ttime;

    altitude += vvelocity * ttime;
    xposit += hvelocity * ttime;
}
//"check" the things that will kill you
void check (void){

    //declare boolean
    bool outOfTime = time >= 240;
    bool crashed = altitude < 0;
    bool tooFast = vvelocity>=50;
    //check altitude
    if (crashed & tooFast) {
        die(2);

    } //(TODO)replace altitude check with terrain value check once terrain is generated
    if (crashed & (!tooFast)) {
        land();
    }
    if (altitude >= 128) {
        altitude = 128;     //TODO figure out how we want to handle the lander at the edges of the screen
    }
    //check time
    if (outOfTime) {
        die(1);
    }
    if (angle == -1) {
        angle = 179;
    }
    if (angle == 181) {
        angle = 0;
    }
}

void render (void) {
    ST7735_SetCursor(1, 1); //Set cursor to top left
    write_score(score);
    ST7735_SetCursor(1, 2); //FIXME set cursor to write below score
    write_time(time);
    ST7735_SetCursor(1, 3); ///FIXME set cursor to write below time
    write_fuel(fuel);

    draw_bitmap(xposit, altitude, lander, 7, 9);
    //TODO generate terrain
}

//Output some sort of death message
void die(DeathType_t deathtype) {
    ST7735_SetCursor(40, 1); ///FIXME set cursors
    ST7735_OutString("You died!");
    switch (deathtype) {
        case CRASHED:
            ST7735_SetCursor(40, 40);
            ST7735_OutString("Lost 20 fuel units.");
            fuel =- 20;
            ST7735_SetCursor(40, 60);
            ST7735_OutString("Fuel left:");
            ST7735_SetCursor(40, 80);
            write_fuel(fuel);
            ST7735_SetCursor(40, 100);
            ST7735_OutString("Current score:");
            write_score(score);
            break;
        case OUTOFTIME:
            ST7735_SetCursor(40, 40);
            ST7735_OutString("Out of time!");
            ST7735_OutString("Final score:");
            write_score(score);
            //TODO write a slight delay
            break;
    }
}

    void land() {
        draw_string(40, 20, "You landed!", 0xFFFF);
    if(fuel>0){
        draw_string(40, 40, "Fuel remaining:", 0xFFFF);
        write_fuel(fuel);
        //TODO write a slight delay
    }
    }

void write_score(uint16_t score) {
    draw_dec(score);
}

void write_fuel(uint16_t inFuel) {
    draw_dec(inFuel);
}

void write_time(uint16_t time) {
    char min = time / 60;
    draw_dec(min);

    uint8_t sec = (time - min * 60);
    draw_dec(sec);
}

char to_ASCII(char num) {
    num += 0x30;
    return num;
}
