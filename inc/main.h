#ifndef LUNAR_LANDER_MAIN_H
#define LUNAR_LANDER_MAIN_H

typedef struct GameState GameState;

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
void generate_terrain(uint16_t* container, uint16_t size);
void draw_terrain(void);

void write(uint16_t score, uint16_t fuel, uint16_t seconds);
void reset_lander_attributes(GameState *state);
bool detect_collision(void);

uint16_t button_pushed(void);

void draw_terrain_chunk(void);
#endif //LUNAR_LANDER_MAIN_H
