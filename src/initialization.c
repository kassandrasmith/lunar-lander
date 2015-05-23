//
// Created by Kassandra on 5/19/2015.
//

#include "initialization.h"
//#include <stdint.h>           //import standard libraries
//#include "tm4c123gh6pm.h"

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
void PORTF_Init(void) {
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


// Initialize the Analog to Digital converter used to read the variable potentiometer
// Probably don't need the pot for this project but I've included it for reference
// ADC uses PORT E with one input at PE2
void ADC_Init(void){
    volatile uint32_t delay;
    SYSCTL_RCGCGPIO_R |= 0x00000010;                // activate clock for Port E
    while((SYSCTL_PRGPIO_R&0x10) != 0x10){};

    delay = SYSCTL_RCGCGPIO_R;                      // allow time for clock to stabilize
    GPIO_PORTE_DIR_R &= ~0x04;                      // make PE2 input
    GPIO_PORTE_AFSEL_R |= 0x04;                     // enable alternate function on PE2
    GPIO_PORTE_DEN_R &= ~0x04;                      // disable digital I/O on PE2
    GPIO_PORTE_AMSEL_R |= 0x04;                     // enable analog function on PE2
    SYSCTL_RCGCADC_R |= 0x0001;                     // activate ADC0 (legacy code)
// while((SYSCTL_PRADC_R&0x0001) != 0x0001){};  // good code, I don't think it's necessary
    delay = SYSCTL_RCGCADC_R;                       // extra time for clock to stabilize
    delay = SYSCTL_RCGCADC_R;                       // extra time for clock to stabilize
    ADC0_PC_R &= ~0xF;                              // clear max sample rate field
    ADC0_PC_R |= 0x1;                               // configure for 125K samples/sec
    ADC0_SSPRI_R = 0x0123;                          // Sequencer 3 is highest priority
    ADC0_ACTSS_R &= ~0x0008;                        // disable sample sequencer 3
    ADC0_EMUX_R &= ~0xF000;                         // seq3 is software trigger
//  ADC0_SAC_R = 0x06;              //    32 hardware averaging, also probably unecessary
    ADC0_SSMUX3_R = (ADC0_SSMUX3_R&0xFFFFFFF0)+1;   // channel Ain1 (PE2)
    ADC0_SSCTL3_R = 0x0006;                         // no TS0 D0, yes IE0 END0
    ADC0_ACTSS_R |= 0x0008;                         // enable sample sequencer 3
}
