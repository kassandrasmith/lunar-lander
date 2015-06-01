#ifndef LUNAR_LANDER_INITIALIZATION_H
#define LUNAR_LANDER_INITIALIZATION_H

#include <stdint.h>

//Initializes digital to analog converter for sounds
void DAC_Init(void);

//Initializes PORT F, on board LEDs and switches
void PortF_Init(void);

//Initializes the SysTick timer for interrupts
void SysTick_Init(uint32_t period);

// Initializes the Analog to Digital converter used to read the variable potentiometer
void ADC_Init(void);


#endif
