#include <stdint.h>

#ifndef LUNAR_LANDER_IMAGES_H
#define LUNAR_LANDER_IMAGES_H

#define BLACK 0x0000
#define WHITE 0xFFFF

const uint16_t test[] = {
        WHITE, WHITE, WHITE, WHITE,
        WHITE, WHITE, WHITE, WHITE,
        WHITE, WHITE, WHITE, WHITE,
        WHITE, WHITE, WHITE, WHITE
};

/* Upright lander (1)
 * x: 7 px
 * y: 9 px
 */
const uint16_t landerBody[] = {

        BLACK, WHITE, WHITE, WHITE, BLACK,
        BLACK, WHITE, BLACK, WHITE, BLACK,
        WHITE, BLACK, BLACK, BLACK, WHITE,
        BLACK, WHITE, BLACK, WHITE, BLACK,
        BLACK, WHITE, WHITE, WHITE, BLACK,
        BLACK, BLACK, BLACK, BLACK, BLACK,
};

const uint16_t lander4Legs[] = {
        BLACK, BLACK, BLACK, BLACK, BLACK,
        WHITE, BLACK, BLACK, BLACK, WHITE,
        BLACK, WHITE, BLACK, WHITE, BLACK,
};

const uint16_t lander0Legs[] = {
        BLACK, BLACK, BLACK,
        BLACK, WHITE, BLACK,
        BLACK, BLACK, WHITE,
        BLACK, BLACK, BLACK,
        BLACK, BLACK, WHITE,
        BLACK, WHITE, BLACK,
        BLACK, BLACK, BLACK,
};


const uint16_t lander8Legs[] = {
        BLACK, BLACK, BLACK,
        BLACK, WHITE, BLACK,
        WHITE, BLACK, BLACK,
        BLACK, BLACK, BLACK,
        WHITE, BLACK, BLACK,
        BLACK, WHITE, BLACK,
        BLACK, BLACK, BLACK,
};

// 4 x 7

const uint16_t lander1Legs[] = {
        BLACK, BLACK, BLACK, BLACK,
        BLACK, BLACK, WHITE, BLACK,
        BLACK, BLACK, BLACK, WHITE,
        BLACK, BLACK, BLACK, WHITE,
        BLACK, BLACK, BLACK, WHITE,
        BLACK, WHITE, WHITE, WHITE,
        BLACK, BLACK, BLACK, BLACK,

};

const uint16_t lander7Legs[] = {
        BLACK, BLACK, BLACK, BLACK,
        BLACK, WHITE, BLACK, BLACK,
        WHITE, BLACK, BLACK, BLACK,
        WHITE, BLACK, BLACK, BLACK,
        WHITE, BLACK, BLACK, BLACK,
        WHITE, WHITE, WHITE, BLACK,
        BLACK, BLACK, BLACK, BLACK,
};

// 7 x 5

const uint16_t lander3Legs[] = {
        BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK,
        BLACK, BLACK, BLACK, BLACK, BLACK, WHITE, BLACK,
        BLACK, BLACK, BLACK, BLACK, BLACK, WHITE, BLACK,
        BLACK, WHITE, WHITE, BLACK, WHITE, WHITE, BLACK,
        BLACK, BLACK, WHITE, WHITE, BLACK, WHITE, BLACK,


};

const uint16_t lander5Legs[] = {
        BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK,
        BLACK, WHITE, BLACK, BLACK, BLACK, BLACK, BLACK,
        BLACK, WHITE, BLACK, BLACK, BLACK, BLACK, BLACK,
        BLACK, WHITE, WHITE, BLACK, WHITE, WHITE, BLACK,
        BLACK, WHITE, BLACK, WHITE, WHITE, BLACK, BLACK,
};

// 6 x 7

const uint16_t lander2Legs[] = {
        BLACK, BLACK, BLACK, BLACK, BLACK, BLACK,
        BLACK, BLACK, BLACK, BLACK, WHITE, BLACK,
        BLACK, BLACK, BLACK, BLACK, WHITE, BLACK,
        BLACK, BLACK, BLACK, BLACK, BLACK, WHITE,
        BLACK, WHITE, WHITE, BLACK, BLACK, WHITE,
        BLACK, BLACK, BLACK, WHITE, WHITE, BLACK,
        BLACK, BLACK, BLACK, BLACK, WHITE, BLACK,

};

const uint16_t lander6Legs[] = {
        BLACK, BLACK, BLACK, BLACK, BLACK, BLACK,
        BLACK, WHITE, BLACK, BLACK, BLACK, BLACK,
        BLACK, WHITE, BLACK, BLACK, BLACK, BLACK,
        WHITE, BLACK, BLACK, BLACK, BLACK, BLACK,
        WHITE, BLACK, BLACK, WHITE, WHITE, BLACK,
        BLACK, WHITE, WHITE, BLACK, BLACK, BLACK,
        BLACK, WHITE, BLACK, BLACK, BLACK, BLACK,
};


const uint16_t black[] = {
        BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK,
        BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK,
        BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK,
        BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK,
        BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK,
        BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK,
        BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK,
        BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK,
        BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK,
        BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK,
        BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK,
        BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK,
        BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK,
        BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK,
        BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK,
        BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK,
        BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK,
        BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK,
        BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK,
        BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK,
        BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK,
        BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK,
        BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK,
        BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK,
        BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK,
        BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK,
        BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK,
        BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK,
        BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK,
};


typedef struct sprite {
    int16_t width;
    int16_t height;
    int16_t xoffset;
    int16_t yoffset;
    const uint16_t *data;
} sprite;

sprite test0Legs = {.width = 3, .height = 7, .xoffset = -3, .yoffset = 1, .data = lander0Legs};
sprite test1Legs = {.width = 4, .height = 7, .xoffset = -3, .yoffset = 2, .data = lander1Legs};
sprite test2Legs = {.width = 6, .height = 7, .xoffset = -3, .yoffset = 3, .data = lander2Legs};
sprite test3Legs = {.width = 7, .height = 5, .xoffset = -2, .yoffset = 4, .data = lander3Legs};

sprite test4Legs = {.width = 5, .height = 3, .xoffset = 0, .yoffset = 3, .data = lander4Legs};

sprite test5Legs = {.width = 7, .height = 5, .xoffset = 1, .yoffset = 4, .data = lander5Legs};
sprite test6Legs = {.width = 6, .height = 7, .xoffset = 3, .yoffset = 3, .data = lander6Legs};
sprite test7Legs = {.width = 4, .height = 7, .xoffset = 4, .yoffset = 2, .data = lander7Legs};
sprite test8Legs = {.width = 3, .height = 7, .xoffset = 5, .yoffset = 1, .data = lander8Legs};
sprite *landerSprite[9] = {&test0Legs, &test1Legs, &test2Legs, &test3Legs, &test4Legs,
                           &test5Legs, &test6Legs, &test7Legs, &test8Legs};


#endif //LUNAR_LANDER_IMAGES_H
