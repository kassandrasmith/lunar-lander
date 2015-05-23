// Lunar Lander
// Created by Kassandra Smith on 5/19/2015.
// Runs on TM4C123; Tiva Launchpad

/********Hardware I/O connections*******************
*Slide pot:
Slide pot pin 1 connected to ground
Slide pot pin 2 connected to PE2/AIN1
Slide pot pin 3 connected to +3.3V
*Buttons:
jet button connected to PE0
left button connected to PE1
right button connected to PE2
*DAC:
32*R resistor DAC bit 0 on PB0
16*R resistor DAC bit 1 on PB1
8*R resistor DAC bit 2 on PB2
4*R resistor DAC bit 3 on PB3
2*R resistor DAC bit 4 on PB4
1*R resistor DAC bit 5 on PB5
*ST7735 Screen connections:
Backlight (pin 10) connected to +3.3 V
MISO (pin 9) unconnected
SCK (pin 8) connected to PA2 (SSI0Clk)
MOSI (pin 7) connected to PA5 (SSI0Tx)
TFT_CS (pin 6) connected to PA3 (SSI0Fss)
CARD_CS (pin 5) unconnected
Data/Command (pin 4) connected to PA6 (GPIO), high for data, low for command
RESET (pin 3) connected to PA7 (GPIO)
VCC (pin 2) connected to +3.3 V
Gnd (pin 1) connected to ground
*/

#include <stdio.h>							//Standard libraries
#include <stdint.h>							//Standard libraries
#include "tm4c123gh6pm.h"				    //inclusion of hardware library
#include "ST7735.h"							//different functions for the screen
#include "PLL.h"							//Phase-Lock-Loop, used to calibrate the clock spees
#include "initialization.h"		            //initialization sequences


#define jetbutton (GPIO_PORTE_DATA_R & 0x01)
#define jetpushed 0x01
#define leftbutton (GPIO_PORTE_DATA_R & 0x02)
#define leftpushed 0x02
#define rightbutton (GPIO_PORTE_DATA_R & 0x03)
#define rightpushed 0x03



//void DisableInterrupts(void); 		// Disable interrupts (!!!)may need to include for interrupts to work
//void EnableInterrupts(void);  		// Enable interrupts  (!!!)may need to include for interrupts to work
//void Delay100ms(uint32_t count); 	    // time delay in 0.1 seconds

//declare global variables
uint16_t score;
uint16_t time;
uint16_t fuel = 1000;

int main(void) {
    //Run initializations
    DisableInterrupts();                                        // Disable interrupts for initializations
//    ADC_Init();
    DAC_Init();                                                 //Digital to analog converter necessary for sounds
    PortF_Init();
    ST7735_InitR(INITR_REDTAB);
    SysTick_Init();                                             // 30 Hz game engine
    EnableInterrupts();                                         //end of initializations, enable interrupts

    //declare variables
    int32_t vvelocity;                  //can be negative if vertical position is increasing
    int32_t vaccel;                     //negative value causes increase in vertical position
    int32_t hvelocity;                  //negative value moves left, positive moves right
    uint16_t altitude=1;                //initialize to topmost of landscape-oriented screen
    uint16_t xposit = 1;                //initialize to leftmost of landscape-oriented screen
    uint32_t angle = 0;                 //0 points upwards

    ST7735_FillScreen(0x000000);                                //fill screen with black
    ST7735_SetCursor(1, 1);
    //ST7735_DrawBitmap(xposit, altitude,(!!!)lander, (!!!)x-size, (!!!)y-size );


    while(1) {
        //check altitude
        if ((altitude >= 120) & (vvelocity >=
                                 50)) { death(); } //(!!!)replace altitude check with terrain value check once terrain is generated
        //check time
        if (time >= 240) {
            death();
        }
        else {
            time++;
            if (time <= 240) { //gives 4 minutes to play
                //converts the time value into minutes and seconds
                char min = time / 60;
                uint8_t sec = (time - min * 60);
                uint8_t seca = (sec / 10);
                uint8_t secb = (sec - seca);
                //outputs time value formatted min:sec
                ST7735_OutChar(min + 30); //convert min to the ascii value
                ST7735_OutChar(0x3A); // ":" in ASCII
                st7735_OutChar(seca + 30);
                ST7735_OutChar(secb + 30);


//Figuring out how to push the lander in the direction it's facing rather than simply up, may have to switch to a polar system
                //d=vt
                //d=do+vo+1/2at^2
                if ((fuel != 0) & (jetbutton == jetpushed)) {
                    vaccel = -0.811;    //negative accelaration forces lander opposite gravity
                    fuel--;             //using fuel
                }
                if ((fuel == 0) | (jetbutton != jetpushed)) {
                    vaccel = 1.622;
                }
                vvelocity = (vvelocity + (vaccel * time));
                altitude = (altitude + (vvelocity * time) + (.5 * vaccel * (time ^ 2)));
                else { vaccel = 1.622 }


                //(!!!)Change the x value
                if ((fuel != 0) & (leftbutton == leftpushed)) {
                    angle--;
                }
                if ((fuel != 0) & (rightbutton == rightpushed)) {
                    angle++;
                }
                if (angle == -1) {
                    angle = 359;
                }
                if (angle == 361) {
                    angle = 0;
                }

            }
        }


        if ((altitude == 0) & (vvelocity <= 50)) {
            landed();
        }
        if (altitude >= 128) {
            altitude = 128;     //(!!!)Unsure of how we want to handle top or edges of screen, perhaps scrolling?
        }








        //after initial checks, redraw moving parts
        //ST7735_DrawBitmap(xposit, altitude,(!!!)lander, (!!!)x-size, (!!!)y-size ); //need to generate lander
        // generate terrain (!!!)






    }
    }

//write death function
void death(void){
    //don't really know what we want the death to do yet
    //Output some sort of death message
}

void landed(void){
        //Output score
    //score= (score+(100*multiplier))
    //uint16 outscore=score;
    //Set cursor where we want it
    //ST7735_OutChar (score/1000);
    //outscore=score/1000;
    //ST7735_OutChar ((score-(outscore*1000))/100);
    //outscore=score/100;
    //ST7735_OutChar ((score-(outscore*100))/10);
    //outscore=score/10;
    //ST7735_OutChar ((score-(outscore*10)));
        //could be done with just the score variable but I made another to follow what I was doing

        //Output some other message, then branch back to the start of the game, keeping score, time, and fuel values in tact
}