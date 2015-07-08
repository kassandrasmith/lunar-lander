#include <stdint.h>
#include <stdbool.h>
#include "../inc/initialization.h"
#include "inc/tm4c123gh6pm.h"
#include "driverlib/rom.h"
#include "driverlib/timer.h"
#include "driverlib/interrupt.h"
#include "driverlib/systick.h"
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "inc/hw_gpio.h"
#include "inc/hw_ints.h"
#include "../inc/sound.h"
#include "../inc/main.h"

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
    // Turn on the LED to notify user that initialization is successful
    GPIO_PORTF_DATA_R |= 0x02;
}

//We initialize port E to use off-board buttons
//The buttons are wired to the pins
//What each button does is described in the bool statements of process_input
void PortE_Init(void) {
    unsigned long volatile delay;
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    GPIOPinTypeGPIOInput(GPIO_PORTE_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2);
}

//Sound Init is the initialization of Timer 2A, which will be where we play sound from
void sound_init(const uint16_t soundRate) {

    uint32_t TIMER_DEBUG = TIMER2_BASE;
    uint32_t INTERRUPT_NUM = INT_TIMER2A_TM4C123; //INT_TIMER2A;
    uint32_t AORB = TIMER_A;

    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER2);
    IntMasterEnable();
    TimerConfigure(TIMER_DEBUG, TIMER_CFG_PERIODIC);
    //Trigger an interrupt ever (1 / soundRate) of a second
    uint32_t period = SysCtlClockGet() / soundRate;
    TimerLoadSet(TIMER_DEBUG, AORB, period - 1);
    IntPrioritySet(INTERRUPT_NUM, 0);
    // Setup the interrupts for the timer timeouts.
    IntEnable(INTERRUPT_NUM);
    TimerIntEnable(TIMER_DEBUG, TIMER_TIMA_TIMEOUT);
    // Enable the timers.
    TimerEnable(TIMER_DEBUG, AORB);
}


void game_loop_init(const uint16_t frameRate) {
    uint32_t TIMER_DEBUG = TIMER1_BASE;
    uint32_t INTERRUPT_NUM = INT_TIMER1A_TM4C123; //maybe remove _TM4C123;
    uint32_t AORB = TIMER_A;

    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);
    IntMasterEnable();
    TimerConfigure(TIMER_DEBUG, TIMER_CFG_PERIODIC);
    //Trigger an interrupt ever (1 / soundRate) of a second
    uint32_t period = SysCtlClockGet() / frameRate;
    TimerLoadSet(TIMER_DEBUG, AORB, period - 1);
    IntPrioritySet(INTERRUPT_NUM, 0);
    // Setup the interrupts for the timer timeouts.
    IntEnable(INTERRUPT_NUM);
    TimerIntEnable(TIMER_DEBUG, TIMER_TIMA_TIMEOUT);
    // Enable the timers.
    TimerEnable(TIMER_DEBUG, AORB);
}

void button_Interrupt_Init(void) {
    //   SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_OSC_INT | SYSCTL_XTAL_16MHZ);
    GPIOIntTypeSet(GPIO_PORTE_BASE, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2, GPIO_FALLING_EDGE);
    GPIOIntRegister(GPIO_PORTE_BASE, buttonPushed);
    GPIOIntEnable(GPIO_PORTE_BASE, GPIO_INT_PIN_0 | GPIO_INT_PIN_1 | GPIO_INT_PIN_2);
    IntPrioritySet(GPIO_PORTE_BASE, 0);
}