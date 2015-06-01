#include <stdio.h>							//Standard libraries
#include <stdint.h>							//Standard libraries
#include <stdbool.h>                        //Standard libraries
#include <math.h>                           //Standard libraries
#include "inc/tm4c123gh6pm.h"				    //inclusion of hardware library
#include "../inc/ST7735.h"							//different functions for the screen
#include "../inc/PLL.h"							    //Phase-Lock-Loop, used to calibrate the clock spees
#include "../inc/initialization.h"		            //initialization sequences
#include "../inc/main.h"

void DisableInterrupts(void); 		// Disable interrupts (HACK)may need to include for interrupts to work
void EnableInterrupts(void);  		// Enable interrupts  (HACK)may need to include for interrupts to work
void Delay100ms(uint32_t count); 	    // time delay in 0.1 seconds

//define buttons
#define jetbutton (GPIO_PORTE_DATA_R & 0x01)
#define jetpushed 0x01
#define leftbutton (GPIO_PORTE_DATA_R & 0x02)
#define leftpushed 0x02
#define rightbutton (GPIO_PORTE_DATA_R & 0x03)
#define rightpushed 0x03


//declare global variables
uint16_t score;
uint16_t time;
uint16_t fuel = 1000;
char multiplier =1; //To be used to increase score according to where the lander lands
int ttime; //TODO set to refresh rate
//declare variables
int16_t vvelocity;                  //can be negative if vertical position is increasing
int16_t vaccel;                     //negative value causes increase in vertical position
int16_t hvelocity;                  //negative value moves left, positive moves right
uint16_t altitude=1;                //initialize to topmost of landscape-oriented screen
uint16_t xposit = 64;                //initialize to middle of landscape-oriented screen
uint16_t angle = 90;                 //0 points upwards

int main(void) {

    //Run initializations
    DisableInterrupts();                                        // Disable interrupts for initializations
    DAC_Init();                                                 //Digital to analog converter necessary for sounds
    PortF_Init();
    ST7735_InitR(INITR_REDTAB);
    SysTick_Init(8000000);                                             // 30 Hz game engine FIXME number that gets passed
    EnableInterrupts();                                         //end of initializations, enable interrupts
    //initial state for screen
    ST7735_FillScreen(0x000000);                                //fill screen with black
    ST7735_SetCursor(1, 1);
    //ST7735_DrawBitmap(xposit, altitude,(!!!)lander, (!!!)x-size, (!!!)y-size );

    while(true) {
        process_input();
        update();
        check();
        render();
    }
}

void process_input(void) {
    //d=vt
    //d=do+vo+1/2at^2
    bool noFuel = fuel==0;
    bool jetButtonPressed = jetbutton == jetpushed;
    bool rightButtonPressed = rightbutton == rightpushed;
    bool leftButtonPressed = leftbutton == leftpushed;

    if (!noFuel & jetButtonPressed) {
        vaccel = -0.811;    //negative accelaration forces lander opposite gravity
        fuel--;             //using fuel
    }
    if (noFuel | (!jetButtonPressed)) {
        vaccel = 1.622;
    }

    if (leftButtonPressed) {
        angle--;
    }
    if (rightButtonPressed) {
        angle++;
    }
}

void update (void){
    time++;
    //TODO Uncrap the physics
    vvelocity = (vvelocity + (vaccel * ttime));
   hvelocity =  hvelocity*cos(angle)*ttime;
   altitude = (altitude + (vvelocity*sin(angle) * ttime) + (.5 * vaccel * (ttime ^ 2)));
}
//"check" the things that will kill you
void check (void){

    //declare boolean
    bool outOfTime = time >= 240;
    bool crashed = altitude < 0;
    bool tooFast = vvelocity>=50;
    //check altitude
    if (crashed & tooFast) {
        die();

    } //(TODO)replace altitude check with terrain value check once terrain is generated
    if (crashed & (!tooFast)) {
        landed();
    }
    if (altitude >= 128) {
        altitude = 128;     //TODO figure out how we want to handle the lander at the edges of the screen
    }
    //check time
    if (outOfTime) {
        die();
    }
    if (angle == -1) {
        angle = 179;
    }
    if (angle == 181) {
        angle = 0;
    }
}

void render (void) {
    write_time(time);
    write_score(score);
    write_fuel(fuel);

//ST7735_DrawBitmap(xposit, altitude,(!!!)lander, (!!!)x-size, (!!!)y-size ); //need to generate lander
    //TODO draw the lander
//TODO generate terrain
}

//TODO write death function
void die(void){
    //Output some sort of death message
}

//TODO write a message for winning
void landed(void){
}

//TODO change math to use modulo
void write_score (uint16_t score){
    score= (score+(100*multiplier));
    uint16_t outScore=score;
    ST7735_SetCursor(1, 1); //Set cursor to top left
    ST7735_OutChar (score/1000);
    outScore=score/1000;
    ST7735_OutChar ((score-( outScore*1000))/100);
    outScore=score/100;
    ST7735_OutChar ((score-( outScore*100))/10);
    outScore=score/10;
    ST7735_OutChar ((score-( outScore*10)));
}
void write_fuel (uint16_t fuel){
    uint16_t outfuel=fuel;

    ST7735_SetCursor(1, 30); ///TODO set cursor to write below time
    ST7735_OutChar (fuel/1000);
    outfuel=fuel/1000;
    ST7735_OutChar ((fuel-( outfuel*1000))/100);
    outfuel=fuel/100;
    ST7735_OutChar ((fuel-( outfuel*100))/10);
    outfuel=fuel/10;
    ST7735_OutChar ((fuel-( outfuel*10)));
}
void write_time (uint16_t time){
    char min = time / 60;
    uint8_t sec = (time - min * 60);
    uint8_t seca = (sec / 10);
    uint8_t secb = (sec - seca);
    //outputs time value formatted min:sec
    ST7735_SetCursor(1, 15); //TODO set cursor to write below score
    ST7735_OutChar(min + 30); //convert min to the ascii value
    ST7735_OutChar(0x3A); // ":" in ASCII
    st7735_OutChar(seca + 30);
    ST7735_OutChar(secb + 30);
}
