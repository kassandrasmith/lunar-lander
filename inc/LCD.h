#include <stdint.h>

#ifndef LUNAR_LANDER_LCD_H
#define LUNAR_LANDER_LCD_H

void screen_init();

void draw_bitmap(int16_t x, int16_t y, const uint16_t *image, int16_t w, int16_t h);

void set_cursor(uint32_t newX, uint32_t newY);

void fill_background(uint16_t color);

void out_dec(uint32_t number);

void out_char(char c);

uint32_t out_string(uint16_t x, uint16_t y, char *pt, int16_t textColor);

#endif //LUNAR_LANDER_LCD_H
