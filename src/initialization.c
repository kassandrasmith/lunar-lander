#include <stdint.h>
#include <stdbool.h>
#include "../inc/initialization.h"
#include "inc/tm4c123gh6pm.h"
#include "driverlib/rom.h"
#include "driverlib/timer.h"
#include "driverlib/interrupt.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "../inc/sound.h"
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

void PortE_Init(void) {
    unsigned long volatile delay;
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    GPIOPinTypeGPIOInput(GPIO_PORTE_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2);
}

void sound_init(void) {
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    IntMasterEnable();
    TimerConfigure(TIMER0_BASE, TIMER_CFG_PERIODIC);
    TimerLoadSet(TIMER0_BASE, TIMER_A, SysCtlClockGet());
    IntEnable(INT_TIMER0A);
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    TimerEnable(TIMER0_BASE, TIMER_A);
    TimerIntRegister(TIMER0_BASE, TIMER_A, sound_handler);
    IntRegister(INT_TIMER0A, sound_handler);
}

/*
void (*PeriodicTask0)(void);   // user function

// ***************** Timer0_Init ****************
// Activate TIMER0 interrupts to run user task periodically
// Inputs:  task is a pointer to a user function
//          period in units (1/clockfreq)
// Outputs: none
void Timer0_Init(){
    SYSCTL_RCGCTIMER_R |= 0x01;   // 0) activate TIMER0
    PeriodicTask0 = sound_handler;          // user function
    TIMER0_CTL_R = 0x00000000;    // 1) disable TIMER0A during setup
    TIMER0_CFG_R = 0x00000000;    // 2) configure for 32-bit mode
    TIMER0_TAMR_R = 0x00000002;   // 3) configure for periodic mode, default down-count settings
    TIMER0_TAILR_R = 30000-1;    // 4) reload value
    TIMER0_TAPR_R = 0;            // 5) bus clock resolution
    TIMER0_ICR_R = 0x00000001;    // 6) clear TIMER0A timeout flag
    TIMER0_IMR_R = 0x00000001;    // 7) arm timeout interrupt
    NVIC_PRI4_R = (NVIC_PRI4_R&0x00FFFFFF)|0x80000000; // 8) priority 4
// interrupts enabled in the main program after all devices initialized
// vector number 35, interrupt number 19
    NVIC_EN0_R = 1<<19;           // 9) enable IRQ 19 in NVIC
    TIMER0_CTL_R = 0x00000001;    // 10) enable TIMER0A
}

void Timer0A_Handler(void){
    TIMER0_ICR_R = TIMER_ICR_TATOCINT;// acknowledge TIMER0A timeout
    (*PeriodicTask0)();                // execute user task
}*/


void sysTick_init(int frameRate) {

// Trigger an interrupt every 30th of a second.
// The period is in clock cycles, so we'll use a function from the libraries to fetch the clock config.
    SysTickPeriodSet(SysCtlClockGet() / (float) frameRate);
    SysTickEnable();
    SysTickIntRegister(game_loop);
    SysTickIntEnable();
}