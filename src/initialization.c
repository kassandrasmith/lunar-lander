#include <stdint.h>
#include <stdbool.h>
#include "../inc/initialization.h"
#include "inc/tm4c123gh6pm.h"
#include "driverlib/rom.h"

#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"

// GPIO_PIN_X is defined in gpio.h
#define LED_RED GPIO_PIN_1
#define LED_BLUE GPIO_PIN_2
#define LED_GREEN GPIO_PIN_3

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
    MAP_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    MAP_GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, LED_RED|LED_BLUE|LED_GREEN);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIO_PORTF_DATA_R |= 0x02;                      // Turns on the LED to notify user that initialization is successful
}

