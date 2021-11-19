#pragma once
#include <libdragon.h>
#include "SVector.h"
#include "sprites.h"

typedef const char* String;

#define _WIDTH 16
#define _HEIGHT 12

#define RED graphics_make_color(0xFF, 0x00, 0x00, 0xFF)
#define GREEN graphics_make_color(0x00, 0xFF, 0x00, 0xFF)
#define WHITE graphics_make_color(0xFF, 0xFF, 0xFF, 0xFF)
#define NAVY_BLUE graphics_make_color(17, 24, 128,255)
#define DARK_RED graphics_make_color(75, 19, 0,255)
#define DEEP_DARK_RED graphics_make_color(31, 1, 0,255)
#define SKY_BLUE graphics_make_color(17, 24, 215,255)
#define ORANGE graphics_make_color(0xFF, 0xA5, 0x00, 0xFF)
#define GOLD graphics_make_color(0xFF, 0xD7, 0x00, 255)
#define YELLOW graphics_make_color(0xFF, 0xFF, 0x00, 255)
#define DARK_GREEN graphics_make_color(0x00, 0x80, 0x00, 255)
#define CYAN graphics_make_color(0x00, 0xFF, 0xFF, 255)
#define GREY graphics_make_color(0x80, 0x80, 0x80, 255)
#define HI_RES
bool GameLoop = true;

#ifdef HI_RES
static resolution_t res = RESOLUTION_640x480;
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
int boffset = 10;
#else
static resolution_t res = RESOLUTION_320x240;
#define SCREEN_WIDTH 320f
#define SCREEN_HEIGHT 240
int boffset = 15;
#endif

static bitdepth_t bit = DEPTH_32_BPP;
static display_context_t disp = 0;

#define TICKS_TOTAL(since_start) (timer_ticks()-since_start) * 0.021333333 / 1000000.0

sprite_t* plane;

void DrawBox(int x, int y, int y1, int y2, int COLOR) {
#ifdef HI_RES
    graphics_draw_box(disp, x * 2, y * 2, y1, y2, COLOR);
#else
    graphics_draw_box(disp, x, y, y1, y2, COLOR);
#endif
}

void DrawText(int x, int y, char* t) {
#ifdef HI_RES
    graphics_draw_text(disp, x * 2, y * 2, (char*)t);
#else
    graphics_draw_text(disp, x, y, (char*)t);
#endif
}
