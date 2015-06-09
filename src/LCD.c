#include "../inc/LCD.h"
#include "../inc/ST7735.h"

void screen_init() {
#ifdef ST7735
    ST7735_InitR(INITR_GREENTAB);
#endif
}

void draw_bitmap(int16_t x, int16_t y, const uint16_t *image, int16_t w, int16_t h) {
#ifdef ST7735
    ST7735_DrawBitmap(x, y, image, w, h);
#endif
}

void fill_background(uint16_t color) {
#ifdef ST7735
    ST7735_FillScreen(color);
#endif
}

void draw_dec(uint16_t x, uint16_t y, uint32_t number) {
#ifdef ST7735
    ST7735_SetCursor(x, y);
    ST7735_SetTextColor(WHITE);
    ST7735_OutUDec(number);
#endif
}

void draw_char(uint16_t x, uint16_t y, char c, int16_t textColor, int16_t bgColor, uint8_t size) {
#ifdef ST7735
    ST7735_DrawChar(x, y, c, textColor, bgColor, size);
#endif
}

uint32_t draw_string(uint16_t x, uint16_t y, char *pt, int16_t textColor) {
#ifdef ST7735
    ST7735_DrawString(x, y, pt, textColor);
#endif
}

uint32_t draw_pixel(int16_t x, int16_t y, uint16_t color) {
#ifdef ST7735
    ST7735_DrawPixel(x, y, color);
#endif
}