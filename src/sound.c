#include <stdint.h>
#include "inc/tm4c123gh6pm.h"
#include "../inc/LCD.h"
#include <stdbool.h>
#include "driverlib/timer.h"
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "inc/hw_types.h"

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
    GPIO_PORTB_DATA_R = sineWave[i];
    i++;
    i %= 64;

    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    HWREGBITW(&g_ui32Flags, 0) ^= 1;
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, g_ui32Flags << 1);
    //TimerLoadSet(TIMER0_BASE, TIMER_A, 3000);
}