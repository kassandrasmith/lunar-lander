#include <stdint.h>

#ifndef LUNAR_LANDER_IMAGES_H
#define LUNAR_LANDER_IMAGES_H

#define BLACK 0x0000
#define WHITE 0xFFFF

const uint16_t test_image[] = {
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

sprite leg0 = {.width = 3, .height = 7, .xoffset = -3, .yoffset = 1, .data = lander0Legs};
sprite leg1 = {.width = 4, .height = 7, .xoffset = -3, .yoffset = 2, .data = lander1Legs};
sprite leg2 = {.width = 6, .height = 7, .xoffset = -3, .yoffset = 3, .data = lander2Legs};
sprite leg3 = {.width = 7, .height = 5, .xoffset = -2, .yoffset = 4, .data = lander3Legs};
sprite leg4 = {.width = 5, .height = 3, .xoffset = 0, .yoffset = 3, .data = lander4Legs};
sprite leg5 = {.width = 7, .height = 5, .xoffset = 1, .yoffset = 4, .data = lander5Legs};
sprite leg6 = {.width = 6, .height = 7, .xoffset = 3, .yoffset = 3, .data = lander6Legs};
sprite leg7 = {.width = 4, .height = 7, .xoffset = 4, .yoffset = 2, .data = lander7Legs};
sprite leg8 = {.width = 3, .height = 7, .xoffset = 5, .yoffset = 1, .data = lander8Legs};
sprite *landerSprite[9] = {&leg0, &leg1, &leg2, &leg3, &leg4,
                           &leg5, &leg6, &leg7, &leg8};


#endif //LUNAR_LANDER_IMAGES_H
