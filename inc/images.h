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
const uint16_t lander4Image[] = {
        BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK,
        BLACK, WHITE, BLACK, BLACK, BLACK, WHITE, BLACK,
        BLACK, BLACK, WHITE, BLACK, WHITE, BLACK, BLACK,
        BLACK, BLACK, WHITE, WHITE, WHITE, BLACK, BLACK,
        BLACK, BLACK, WHITE, BLACK, WHITE, BLACK, BLACK,
        BLACK, WHITE, BLACK, BLACK, BLACK, WHITE, BLACK,
        BLACK, BLACK, WHITE, BLACK, WHITE, BLACK, BLACK,
        BLACK, BLACK, BLACK, WHITE, BLACK, BLACK, BLACK,
        BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK,
};

/* Sideways landers (2)
 * x: 9 px
 * y: 7 px
 */

const uint16_t lander0Image[] = {
        BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK,
        BLACK, WHITE, BLACK, BLACK, BLACK, WHITE, BLACK, BLACK, BLACK,
        BLACK, BLACK, WHITE, WHITE, WHITE, BLACK, WHITE, BLACK, BLACK,
        BLACK, BLACK, BLACK, WHITE, BLACK, BLACK, BLACK, WHITE, BLACK,
        BLACK, BLACK, WHITE, WHITE, WHITE, BLACK, WHITE, BLACK, BLACK,
        BLACK, WHITE, BLACK, BLACK, BLACK, WHITE, BLACK, BLACK, BLACK,
        BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK,
};
const uint16_t lander8Image[] = {
        BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK,
        BLACK, BLACK, BLACK, WHITE, BLACK, BLACK, BLACK, WHITE, BLACK,
        BLACK, BLACK, WHITE, BLACK, WHITE, WHITE, WHITE, BLACK, BLACK,
        BLACK, WHITE, BLACK, BLACK, BLACK, WHITE, BLACK, BLACK, BLACK,
        BLACK, BLACK, WHITE, BLACK, WHITE, WHITE, WHITE, BLACK, BLACK,
        BLACK, BLACK, BLACK, WHITE, BLACK, BLACK, BLACK, WHITE, BLACK,
        BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK,
};

/* Angled landers (2/6))
 * x: 9 px
 * y: 9 px
 */

const uint16_t lander2Image[] = {
        BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK,
        BLACK, BLACK, BLACK, BLACK, WHITE, WHITE, WHITE, WHITE, BLACK,
        BLACK, BLACK, BLACK, BLACK, WHITE, BLACK, BLACK, WHITE, BLACK,
        BLACK, BLACK, BLACK, WHITE, WHITE, BLACK, BLACK, WHITE, BLACK,
        BLACK, WHITE, WHITE, BLACK, WHITE, WHITE, WHITE, WHITE, BLACK,
        BLACK, BLACK, BLACK, BLACK, BLACK, WHITE, BLACK, BLACK, BLACK,
        BLACK, BLACK, BLACK, BLACK, WHITE, BLACK, BLACK, BLACK, BLACK,
        BLACK, BLACK, BLACK, BLACK, WHITE, BLACK, BLACK, BLACK, BLACK,
        BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK,
};

const uint16_t lander6Image[] = {
       BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK,
       BLACK, WHITE, WHITE, WHITE, WHITE, BLACK, BLACK, BLACK, BLACK,
       BLACK, WHITE, BLACK, BLACK, WHITE, BLACK, BLACK, BLACK, BLACK,
       BLACK, WHITE, BLACK, BLACK, WHITE, WHITE, BLACK, BLACK, BLACK,
       BLACK, WHITE, WHITE, WHITE, WHITE, BLACK, WHITE, WHITE, BLACK,
       BLACK, BLACK, BLACK, WHITE, BLACK, BLACK, BLACK, BLACK, BLACK,
       BLACK, BLACK, BLACK, BLACK, WHITE, BLACK, BLACK, BLACK, BLACK,
       BLACK, BLACK, BLACK, BLACK, WHITE, BLACK, BLACK, BLACK, BLACK,
       BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK,
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
        const uint16_t *data;
} sprite;


sprite lander0 = {.width = 9, .height = 7, .data = lander0Image};
sprite lander2 = {.width = 9, .height = 9, .data = lander2Image};
sprite lander4 = {.width = 7, .height = 9, .data = lander4Image};
sprite lander6 = {.width = 9, .height = 9, .data = lander6Image};
sprite lander8 = {.width = 9, .height = 7, .data = lander8Image};


sprite *landerSprites[9] = {&lander8, &lander8, &lander6, &lander4, &lander4, &lander4,
                            &lander2, &lander0, &lander0};


#endif //LUNAR_LANDER_IMAGES_H
