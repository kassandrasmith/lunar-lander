#include "../inc/computations.h"
#include <stdint.h>
#include <stdio.h>
#include "inc/tm4c123gh6pm.h"

//sine for the first two quadrants is never negative

/*
 * Sine Table
 * 0 or 180  -> 0
 * 30 or 150 -> 0.5
 * 45 or 135 -> 0.707
 * 60 or 120 -> 0.866
 * 90         -> 1.0
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
 * 0    ->  1
 * 180  -> -1
 * 30   -> 0.866
 * 150  -> -0.866
 * 45   -> 0.707
 * 135  -> -0.707
 * 60   -> 0.5
 * 120  -> -0.5
 * 90   -> 0.0
 */

float cosineValues[] = {
        -1, -0.866, -0.707, -0.5, 0, 0.5, 0.707, 0.866, 1
};

float cosAngle (uint16_t angle){
    return cosineValues[angle];
}
