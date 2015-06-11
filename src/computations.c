#include "../inc/computations.h"
#include <stdint.h>
#include <stdio.h>
#include "inc/tm4c123gh6pm.h"

//sine for the first two quadrants is never negative

//Sine Table
//sin0 = sin180 = 0;       //0
//sin30 = sin150 = 0.5;    //pi/6
//sin45 = sin135 = 0.707;  //pi/4
//sin60 = sin120 = 0.866; //pi/3
//sin90 = 1.0;            //pi/2

float sineValues[] = {
        0, 0.5, 0.707, 0.866, 1, 0.866, 0.707, 0.5, 0
};

float sinAngle(uint16_t angle) {
    return sineValues[angle];
    }

//cosine can be negative, which increases the number of checks we must do
//Cosine Table
//cosin0 = 1; //0
//cosin180 = -1;
//cosin30 = 0.866; //pi/6
//cosin150 = -0.866;
//cosin45 = 0.707; //pi/4
//cosin135 = -0.707;
//cosin60 = 0.5; //pi/3
//cosin120 = -0.5;
//cosin90 = 0.0;            //pi/2

float cosineValues[] = {
        -1, -0.866, -0.707, -0.5, 0, 0.5, 0.707, 0.866, 1
};

float cosAngle (uint16_t angle){
    return cosineValues[angle];
}
