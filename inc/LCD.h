#include <stdint.h>

#ifndef LUNAR_LANDER_LCD_H
#define LUNAR_LANDER_LCD_H

#define ST7735
#ifdef ST7735
#define BLACK 0x0000
#define WHITE 0xFFFF
#endif

void screen_init();
void draw_bitmap(int16_t x, int16_t y, const uint16_t *image, int16_t w, int16_t h);
void fill_background(uint16_t color);

void draw_dec(uint16_t x, uint16_t y, uint32_t number);

void draw_char(uint16_t x, uint16_t y, char c, int16_t textColor, int16_t bgColor, uint8_t size);

uint32_t draw_string(uint16_t x, uint16_t y, char *pt, int16_t textColor);

#endif //LUNAR_LANDER_LCD_H
