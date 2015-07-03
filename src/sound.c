#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "../inc/LCD.h"
#include "../inc/main.h"
#include "driverlib/timer.h"
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/systick.h"
#include "inc/hw_types.h"
#include "driverlib/interrupt.h"
uint32_t g_ui32Flags;


// 6-bit 64-element sine wave
const unsigned short sineWave[64] = {
        32, 35, 38, 41, 44, 47, 49, 52, 54, 56, 58,
        59, 61, 62, 62, 63, 63, 63, 62, 62, 61, 59,
        58, 56, 54, 52, 49, 47, 44, 41, 38, 35,
        32, 29, 26, 23, 20, 17, 15, 12, 10, 8,
        6, 5, 3, 2, 2, 1, 1, 1, 2, 2, 3,
        5, 6, 8, 10, 12, 15, 17, 20, 23, 26, 29};

int i = 1;
void sound_handler(void) {
    //Send data to hardware DAC
    GPIO_PORTB_DATA_R = sineWave[i];
    //increment array
    i++;
    //keep variable on [0,63]
    i %= 64;
    // Use the flags to Toggle the LED for this timer
    GPIO_PORTF_DATA_R ^= 0x04;
    //print on screen for debug
    //draw_dec(5, 5, i);
    //draw_dec(5, 6, sineWave[i]);

}