// Lunar Lander
// Created by Kassandra Smith on 5/19/2015.
// Runs on TM4C123

/********Hardware I/O connections*******************
*Slide pot:
Slide pot pin 1 connected to ground
Slide pot pin 2 connected to PE2/AIN1
Slide pot pin 3 connected to +3.3V
*Buttons:
up button connected to PE0
back button connected to PE1
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
#include "ST7735.h"							//code written with different functions for the screen
#include "PLL.h"							//Phase-Lock-Loop, used to calibrate the clock spees


#include "initialization.h"		            //initialization sequences


void DisableInterrupts(void); 		// Disable interrupts
void EnableInterrupts(void);  		// Enable interrupts
void Delay100ms(uint32_t count); 	// time delay in 0.1 seconds



int main(void) {

    DisableInterrupts();                                        // Disable interrupts for initializations
    ADC_Init();                                                 //initializations
    DAC_Init();
    PortF_Init();
    ST7735_InitR(INITR_REDTAB);
    SysTick_Init();                                             // 30 Hz game engine
    EnableInterrupts();                                         //end of initializations, enable interrupts
    ST7735_FillScreen(0x000000);                                //fill screen with black
    ST7735_SetCursor(1, 1);
}