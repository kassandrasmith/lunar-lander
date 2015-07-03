#ifndef LUNAR_LANDER_INITIALIZATION_H
#define LUNAR_LANDER_INITIALIZATION_H

#include <stdint.h>

//Initializes digital to analog converter for sounds
void DAC_Init(void);

//Initializes PORT F, on board LEDs and switches
void PortF_Init(void);

void PortE_Init(void);

void sound_init(const uint16_t soundRate);

void game_loop_init(const uint16_t frameRate);

#endif
