#pragma once
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
#define PURPLE graphics_make_color(0xFF, 0x00, 0x9B, 0xFF)

#define SET_TEXT_COLOR(color,code) graphics_set_color(color,0);	code  \
								   graphics_set_color(0xFF, 0); \
							
#define LINE_MOVE
#define HI_RES

#define TicksInSeconds timer_ticks() * 0.021333333 / 1000000.0
#define SWIDTH 320
#define SHEIGHT 240

/*between x and y*/
#define RAND(x,y) rand() % y + x

static resolution_t		 res = RESOLUTION_320x240;
static display_context_t disp = 0;
static bitdepth_t		 dep = DEPTH_16_BPP;

uint32_t colors[15];