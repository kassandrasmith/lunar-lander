#include "../inc/initialization.h"
#include <stdint.h>           //import standard libraries
#include "inc/tm4c123gh6pm.h"

//Initialize the Digital to Analog Converter (DAC) in order to produce sounds
//We use a 6-bit R, 2R method DAC
//The six bits use PORT B pins 5-0 as inputs
void DAC_Init(void) {
    unsigned long volatile delay;
    SYSCTL_RCGCGPIO_R |= 0x02;                      // enable clock for PORT B
    delay = SYSCTL_RCGCGPIO_R;                      // give the clock some time
    GPIO_PORTB_AMSEL_R &= ~0x7F;                    // disable PORT B analog function
    GPIO_PORTB_PCTL_R &= ~0x00000FFF;               // regular GPIO function
    GPIO_PORTB_DIR_R |= 0x7F;                       // make PB5-0 outputs
    GPIO_PORTB_AFSEL_R &= ~0x7F;                    // disable alternate functions on PB5-0
    GPIO_PORTB_DEN_R |= 0x7F;                       // enable digital I/O on PB5-0
    GPIO_PORTB_DR8R_R |= 0x7F;                      // 8-mA drive control register
}


//We initialize port F to use the on-board LED
//PORT F pin assignments:
//PF0 and PF4 are switches;
//PF3-1 are different LEDs
void PortF_Init(void) {
    unsigned long volatile delay;

    //Port F initialization
    SYSCTL_RCGCGPIO_R |= 0x20;                      // enable clock for PORT F
    delay = SYSCTL_RCGCGPIO_R;                      // give the clock some time
    GPIO_PORTF_AMSEL_R &= ~0x02;                    // disable analog function
    GPIO_PORTF_PCTL_R &= ~0x00000FFF;               // regular GPIO function
    GPIO_PORTF_DIR_R |= 0x02;                       // make PF1 output
    GPIO_PORTF_AFSEL_R &= ~0x02;                    // disable alt funct on PF1
    GPIO_PORTF_DEN_R |= 0x02;                       // enable digital I/O on PF1
    GPIO_PORTF_DR8R_R |= 0x02;                      // 8-mA drive control register
    GPIO_PORTF_PDR_R |= 0x02;                       // Pull down register for on board led
    GPIO_PORTF_PUR_R |= 0x10;                       // Pull up register for on board switch
    GPIO_PORTF_PUR_R |= 0x01;                       // Pull up register for on board switch
    GPIO_PORTF_DATA_R |= 0x02;                      // Turns on the LED to notify user that initialization is successful
}

//Initialize the SysTick timer for interrupts
int period = 7256;
void SysTick_Init(uint32_t period){
    NVIC_ST_CTRL_R = 0;                             // disable SysTick during setup
    NVIC_ST_RELOAD_R = period - 1;                  // reload value
    NVIC_ST_CURRENT_R = 0;                          // any write to current clears it
    NVIC_SYS_PRI3_R = (NVIC_SYS_PRI3_R&0x00FFFFFF)|0x20000000;  // priority 1
    NVIC_ST_CTRL_R = 0x0007;                        // enable SysTick with core clock and interrupts
}
