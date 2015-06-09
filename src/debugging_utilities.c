#include <inc/tm4c123gh6pm.h>
#include "stdint.h"
#include "../inc/debugging_utilities.h"
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