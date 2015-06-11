#ifndef LUNAR_LANDER_COMPUTATIONS_H
#define LUNAR_LANDER_COMPUTATIONS_H

#include "stdint.h"

//"angle" refers to a number from 0 to 8 which corresponds to steps on the unit circle
//an "angle" of 0 corresponds to 180 degrees
//an "angle" of 8 corresponds to 0 degrees.

//0 = deg 180 = pi
//1 = deg 150 = 5pi/6
//2 = deg 135 = 3pi/4
//3 = deg 120 = 2pi/3
//4 = deg 90 = pi/2
//5 = deg 60 = pi/3
//6 = deg 45 = pi/4
//7 = deg 30 = pi/6
//8 = deg 0 = 0
//converts into the sine of the angle to make acceleration calculation
float sinAngle(uint16_t angle);

//converts into the cosine of the angle to make acceleration calculation
float cosAngle (uint16_t angle);


#endif //LUNAR_LANDER_COMPUTATIONS_H
