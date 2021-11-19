#pragma once
#include <libdragon.h>

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

class LibN64 {
private:
	virtual void FrameUpdate();
public:
	display_context_t LibN64_Display;

	bool lActive;
public:
	LibN64(resolution_t res, bitdepth_t dep);
	void Begin();
	void Close();
	void DrawText(int x, int y, char* t, uint32_t c=WHITE);
	void DrawBox(int x, int y, int scale, uint32_t c = WHITE);
};
