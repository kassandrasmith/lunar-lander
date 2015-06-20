#ifndef LUNAR_LANDER_DEBUGGING_UTILITIES_H
#define LUNAR_LANDER_DEBUGGING_UTILITIES_H

//Increment a counter
void tick();
//If the current tick counter is above a threshold, blink the onboard LED
void toggleLED(int tickThreshold);

void write_velocities(float, float);

void write_angle(int16_t angle);

#endif //LUNAR_LANDER_DEBUGGING_UTILITIES_H
