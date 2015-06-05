#ifndef LUNAR_LANDER_MAIN_H
#define LUNAR_LANDER_MAIN_H


typedef enum DeathType {
    CRASHED,
    OUTOFTIME
} DeathType_t;

void process_input(void);
void update(void);
void check(void);
void render(void);
void die(DeathType_t);
void land(void);
void write_score (uint16_t);
void write_fuel (uint16_t);
void write_time (uint16_t);




#endif //LUNAR_LANDER_MAIN_H
