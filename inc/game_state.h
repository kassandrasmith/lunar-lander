#include <stdint.h>
#ifndef LUNAR_LANDER_GAME_STATE_H
#define LUNAR_LANDER_GAME_STATE_H

typedef enum lander_heading {
    WEST,
    WESTSOUTHWEST,
    SOUTHWEST,
    SOUTHSOUTHWEST,
    SOUTH,
    SOUTHSOUTHEAST,
    SOUTHEAST,
    EASTSOUTHEAST,
    EAST
} lander_heading;

typedef struct GameState {
    uint16_t score;
    uint16_t time;
    uint16_t fuel;
    uint16_t xposit;
    uint16_t yposit;
    float yvelocity;                    //can be negative if vertical position is increasing
    float xvelocity;                    //negative value moves left, positive moves right
    float xaccel;                       //acceleration in the x direction
    float yaccel;                       //acceleration in the x direction
    lander_heading heading;
} GameState;

typedef enum screen {
    GAMEPLAY,
    START,
    DEATH,
    ENDGAME
} screen;

#endif //LUNAR_LANDER_GAME_STATE_H
