#ifndef LUNAR_LANDER_MAIN_H
#define LUNAR_LANDER_MAIN_H


typedef enum DeathType {
    CRASHED,
    OUTOFTIME
} DeathType_t;

void process_input(void);
void game_loop();
void update(void);
void check(void);
void render(void);
void die(DeathType_t);
void land(void);
void draw_terrain(void);

void write(uint16_t score, uint16_t fuel, uint16_t seconds);
void refresh(void);
void start_screen(void);
bool detect_collision(void);

#endif //LUNAR_LANDER_MAIN_H
