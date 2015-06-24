#include "../inc/computations.h"
#include <stdint.h>
#include <stdio.h>
#include "inc/tm4c123gh6pm.h"

//sine for the first two quadrants is never negative

/*
 * Sine Table
 * angle    degrees   -> sine
 * 0 or 8   0 or 180  -> 0
 * 1 or 7   30 or 150 -> 0.5
 * 2 or 6   45 or 135 -> 0.707
 * 3 or 5   60 or 120 -> 0.866
 * 4        90        -> 1.0
 */

float sineValues[] = {
        0, 0.5, 0.707, 0.866, 1, 0.866, 0.707, 0.5, 0
};

float sinAngle(uint16_t angle) {
    return sineValues[angle];
    }

//cosine can be negative, which increases the number of checks we must do
/*
 * Cosine Table
 * angle    degrees -> cosine
 * 8        0    ->  1
 * 7        30   -> 0.866
 * 6        45   -> 0.707
 * 5        60   -> 0.5
 * 4        90   -> 0.0
 * 3        120  -> -0.5
 * 2        135  -> -0.707
 * 1        150  -> -0.866
 * 0        180  -> -1
 */

float cosineValues[] = {
        1, 0.866, 0.707, 0.5, 0, -0.5, -0.707, -0.866, -1
};

float cosAngle (uint16_t angle){
    return cosineValues[angle];
}
