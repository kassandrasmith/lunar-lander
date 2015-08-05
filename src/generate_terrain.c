#include <stdint.h>

void generate_terrain(uint16_t *container, uint16_t size){
    // The number of terrain features
    uint8_t features = rand() % 6 + 4;
    int feature_type[10];
    for (int i = 0; i < features; i++){
        feature_type[i] = (rand() % 5) - 3;
        //Verify that there's at least one flat area
    }

    int terrain_cursor = 0;
    uint16_t terrain_level = 120;
    for (int i = 0; i < features; i++) {
        const int incline = feature_type[i];
        const uint16_t length = rand() % 30 + 15;
        // Ensure that the minimum length is enough space for the lander to land
        for (int j = 0; j < length; j++) {
            if (terrain_cursor > size){
                goto done;
            }
            terrain_level += incline;
            container[terrain_cursor] = terrain_level;
            terrain_cursor++;
        }
    }
    done:
    return;

}