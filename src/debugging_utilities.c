#include <inc/tm4c123gh6pm.h>
#include "stdint.h"
#include "../inc/debugging_utilities.h"
#include "../inc/LCD.h"
int lastTimerValue;
uint16_t tickCount;

// Log the clock count for real time-interval estimation
void benchmark(){}

void toggleLED(int tickThreshold){
    if (tickCount > tickThreshold) {
        GPIO_PORTF_DATA_R ^= 0x02;
        tickCount = 0;
    }
}

void tick(){
    tickCount++;
}

void write_velocities(float xvel, float yvel) {
    #ifdef DEBUG
    draw_string(0, 3, "xv:", WHITE);
    draw_dec(3, 3, (uint32_t) (xvel * 1000u));
    draw_string(0, 4, "yv:", WHITE);
    draw_dec(3, 4, (uint32_t) (yvel * 1000u));
    #endif
}

void write_angle(int16_t angle) {
    #ifdef DEBUG
    draw_string(0, 5, "a:", WHITE);
    draw_dec(3, 5, (uint32_t) angle);
    #endif
}

