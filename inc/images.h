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


const uint16_t lander4Image[] = {
        BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK,
        BLACK, WHITE, BLACK, BLACK, BLACK, WHITE, BLACK,
        BLACK, BLACK, WHITE, BLACK, WHITE, BLACK, BLACK,
        BLACK, BLACK, WHITE, WHITE, WHITE, BLACK, BLACK,
        BLACK, BLACK, WHITE, BLACK, WHITE, BLACK, BLACK,
        BLACK, WHITE, BLACK, BLACK, BLACK, WHITE, BLACK,
        BLACK, BLACK, WHITE, WHITE, WHITE, BLACK, BLACK,
        BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK,
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
        BLACK, BLACK, BLACK, WHITE, BLACK, BLACK, WHITE, BLACK, BLACK,
        BLACK, BLACK, WHITE, WHITE, WHITE, BLACK, WHITE, BLACK, BLACK,
        BLACK, WHITE, BLACK, BLACK, BLACK, WHITE, BLACK, BLACK, BLACK,
        BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK,
};
const uint16_t lander8Image[] = {
        BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK,
        BLACK, BLACK, BLACK, WHITE, BLACK, BLACK, BLACK, WHITE, BLACK,
        BLACK, BLACK, WHITE, BLACK, WHITE, WHITE, WHITE, BLACK, BLACK,
        BLACK, BLACK, WHITE, BLACK, BLACK, WHITE, BLACK, BLACK, BLACK,
        BLACK, BLACK, WHITE, BLACK, WHITE, WHITE, WHITE, BLACK, BLACK,
        BLACK, BLACK, BLACK, WHITE, BLACK, BLACK, BLACK, WHITE, BLACK,
        BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK,
};

/* Angled landers (2/6))
 * x: 8 px
 * y: 8 px
 */
const uint16_t lander1Image[] = {
        BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK,
        BLACK, BLACK, WHITE, BLACK, BLACK, BLACK, BLACK, BLACK,
        BLACK, BLACK, BLACK, WHITE, BLACK, WHITE, BLACK, BLACK,
        BLACK, BLACK, BLACK, WHITE, WHITE, WHITE, WHITE, BLACK,
        BLACK, BLACK, BLACK, WHITE, BLACK, BLACK, WHITE, BLACK,
        BLACK, WHITE, WHITE, WHITE, BLACK, BLACK, WHITE, BLACK,
        BLACK, BLACK, BLACK, BLACK, WHITE, WHITE, BLACK, BLACK,
        BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK,
};

const uint16_t lander7Image[] = {
        BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK,
        BLACK, BLACK, BLACK, BLACK, BLACK, WHITE, BLACK, BLACK,
        BLACK, BLACK, WHITE, BLACK, WHITE, BLACK, BLACK, BLACK,
        BLACK, WHITE, WHITE, WHITE, WHITE, BLACK, BLACK, BLACK,
        BLACK, WHITE, BLACK, BLACK, WHITE, BLACK, BLACK, BLACK,
        BLACK, WHITE, BLACK, BLACK, WHITE, WHITE, WHITE, BLACK,
        BLACK, BLACK, WHITE, WHITE, BLACK, BLACK, BLACK, BLACK,
        BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK,
};

/* Angled landers (2/6))
 * x: 7 px
 * y: 8 px
 */
const uint16_t lander3Image[] = {
        BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK,
        BLACK, BLACK, BLACK, BLACK, BLACK, WHITE, BLACK, BLACK,
        BLACK, BLACK, BLACK, BLACK, BLACK, WHITE, BLACK, BLACK,
        BLACK, WHITE, WHITE, BLACK, WHITE, WHITE, BLACK, BLACK,
        BLACK, BLACK, WHITE, WHITE, BLACK, BLACK, WHITE, BLACK,
        BLACK, BLACK, BLACK, WHITE, BLACK, BLACK, WHITE, BLACK,
        BLACK, BLACK, BLACK, WHITE, BLACK, WHITE, WHITE, BLACK,
        BLACK, BLACK, BLACK, BLACK, WHITE, WHITE, BLACK, BLACK,
        BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK,

};

const uint16_t lander5Image[] = {
        BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK,
        BLACK, BLACK, WHITE, BLACK, BLACK, BLACK, BLACK, BLACK,
        BLACK, BLACK, WHITE, BLACK, BLACK, BLACK, BLACK, BLACK,
        BLACK, BLACK, WHITE, WHITE, BLACK, WHITE, WHITE, BLACK,
        BLACK, WHITE, BLACK, BLACK, WHITE, WHITE, BLACK, BLACK,
        BLACK, WHITE, BLACK, BLACK, WHITE, BLACK, BLACK, BLACK,
        BLACK, WHITE, WHITE, BLACK, WHITE, BLACK, BLACK, BLACK,
        BLACK, BLACK, WHITE, WHITE, BLACK, BLACK, BLACK, BLACK,
        BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK,
};




/* Angled landers (2/6))
 * x: 9 px
 * y: 9 px
 */
const uint16_t lander2Image[] = {
        BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK,
        BLACK, BLACK, BLACK, BLACK, WHITE, BLACK, BLACK, BLACK, BLACK,
        BLACK, BLACK, BLACK, BLACK, WHITE, BLACK, BLACK, BLACK, BLACK,
        BLACK, BLACK, BLACK, BLACK, BLACK, WHITE, BLACK, BLACK, BLACK,
        BLACK, WHITE, WHITE, BLACK, BLACK, WHITE, WHITE, BLACK, BLACK,
        BLACK, BLACK, BLACK, WHITE, WHITE, BLACK, BLACK, WHITE, BLACK,
        BLACK, BLACK, BLACK, BLACK, WHITE, BLACK, BLACK, WHITE, BLACK,
        BLACK, BLACK, BLACK, BLACK, BLACK, WHITE, WHITE, BLACK, BLACK,
        BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK,
};

const uint16_t lander6Image[] = {
       BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK,
       BLACK, BLACK, BLACK, BLACK, WHITE, BLACK, BLACK, BLACK, BLACK,
       BLACK, BLACK, BLACK, BLACK, WHITE, BLACK, BLACK, BLACK, BLACK,
       BLACK, BLACK, BLACK, WHITE, BLACK, BLACK, BLACK, BLACK, BLACK,
       BLACK, BLACK, WHITE, WHITE, BLACK, BLACK, WHITE, WHITE, BLACK,
       BLACK, WHITE, BLACK, BLACK, WHITE, WHITE, BLACK, BLACK, BLACK,
       BLACK, WHITE, BLACK, BLACK, WHITE, BLACK, BLACK, BLACK, BLACK,
       BLACK, BLACK, WHITE, WHITE, BLACK, BLACK, BLACK, BLACK, BLACK,
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
sprite lander1 = {.width = 8, .height = 8, .data = lander1Image};
sprite lander2 = {.width = 9, .height = 9, .data = lander2Image};
sprite lander3 = {.width = 8, .height = 9, .data = lander3Image};
sprite lander4 = {.width = 7, .height = 9, .data = lander4Image};
sprite lander5 = {.width = 8, .height = 9, .data = lander5Image};
sprite lander6 = {.width = 9, .height = 9, .data = lander6Image};
sprite lander7 = {.width = 8, .height = 8, .data = lander7Image};
sprite lander8 = {.width = 9, .height = 7, .data = lander8Image};


sprite *landerSprites[9] = {&lander8, &lander7, &lander6, &lander5, &lander4, &lander3,
                            &lander2, &lander1, &lander0};


/*
typedef struct testsprite {
    int16_t width;
    int16_t height;
    int16_t xoffset;
    int16_t yoffset;
    const uint16_t *data;
} testsprite;

testsprite test0Legs = {.width = 3, .height = 7, .xoffset = -4, .yoffset = 1,.data = lander0Legs};
 testsprite test1Legs = {.width = 4, .height = 7, .xoffset = 4, .yoffset = 1,.data = lander1Legs};
 testsprite test2Legs = {.width = 6, .height = 7, .xoffset = 4, .yoffset = 1,.data = lander2Legs};
 testsprite test3Legs = {.width = 7, .height = 5, .xoffset = 4, .yoffset = 1,.data = lander3Legs};

testsprite test4Legs = {.width = 5, .height = 3, .xoffset = 0, .yoffset = 3, .data = lander4Legs};

 testsprite test5Legs = {.width = 7, .height = 5, .xoffset = 4, .yoffset = 1,.data = lander5Legs};
 testsprite test6Legs = {.width = 6, .height = 7, .xoffset = 4, .yoffset = 1,.data = lander6Legs};
 testsprite test7Legs = {.width = 4, .height = 7, .xoffset = 4, .yoffset = 1,.data = lander7Legs};
 testsprite test8Legs = {.width = 3, .height = 7, .xoffset = 4, .yoffset = 1,.data = lander8Legs};
testsprite *testLanderSprite[9] = {&test0Legs, &test4Legs, &test4Legs, &test4Legs, &test4Legs,
                              &test4Legs, &test4Legs, &test4Legs, &test0Legs};

*/

#endif //LUNAR_LANDER_IMAGES_H
