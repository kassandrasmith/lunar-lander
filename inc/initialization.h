#ifndef LUNAR_LANDER_INITIALIZATION_H
#define LUNAR_LANDER_INITIALIZATION_H

#include <stdint.h>

//Initializes digital to analog converter for sounds
void DAC_Init(void);

//Initializes PORT F, on board LEDs and switches
void PortF_Init(void);

void PortE_Init(void);

void sound_init(int frameRate);


void Timer0_Init(void);
void Timer0A_Handler(void);


void sysTick_init(int frameRate);

#endif
