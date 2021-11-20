#pragma once
#include <libdragon.h>
#include <math.h>
#include <string.h>
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

#define TICKS_TOTAL(since_start) (timer_ticks()-since_start) * 0.021333333 / 1000000.0
#define TICKS2SECONDS(ticks) (ticks * 0.021333333 / 1000000.0)
class LibN64 {
private:
	virtual void FrameUpdate();
	virtual void KeyAPressed();
	virtual void KeyBPressed();

	virtual void KeyDUPressed();
	virtual void KeyDDPressed();
	virtual void KeyDLPressed();
	virtual void KeyDRPressed();

	uint32_t screenWidth;
	uint32_t screenHeight;

	void DrawFrame();
public:
	display_context_t LibN64_Display;

	const char* romTitle;
	bool lActive;

	float fFrameTime;
	float fTotalTime;
public:
	LibN64(resolution_t res, bitdepth_t dep);
	virtual void OnCreate();
	void Begin();
	void Close();
	void ClearScreen();
	uint32_t ScreenWidth();
	uint32_t ScreenHeight();
	void DrawText(int x, int y, const char* t, uint32_t c = WHITE);
	void DrawBox(int x, int y, int scale, uint32_t c = WHITE);
	void DrawCircle(int x, int y, int scale, uint32_t c = WHITE);
	
/*Functions are refusing to compile*/
#define DrawTextFormat(x,y,buf,arg) char buffer[strlen(buf)]; \
									sprintf(buffer, buf, arg); \
									graphics_draw_text(LibN64_Display, x, y, buffer); \

#define DrawTextFormat(x,y,buf,arg,arg2) char buffer[strlen(buf)]; \
									sprintf(buffer, buf, arg, arg2); \
									graphics_draw_text(LibN64_Display, x, y, buffer); \


};
