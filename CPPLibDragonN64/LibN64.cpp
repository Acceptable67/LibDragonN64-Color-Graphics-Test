#include "LibN64.h"

void LibN64::CheckAndSwitchRes(resolution_t r) 
{
	auto sr = [&](auto x, auto y)  
	{
		this->screenWidth = x;
		this->screenHeight = y;
	};

	switch (r) 
	{
		case RESOLUTION_320x240: sr(320, 240); break;
		case RESOLUTION_256x240: sr(256, 240); break;
		case RESOLUTION_640x480: sr(640, 480); break;
		case RESOLUTION_512x480: sr(512, 480); break;
		default: sr(320, 240); break;
	}
}

LibN64::LibN64(resolution_t res = RESOLUTION_320x240, bitdepth_t dep = DEPTH_32_BPP) 
{
	LibN64_Display = 0;
	
	CheckAndSwitchRes(res);
	
	/* enable interrupts (on the CPU) */
	init_interrupts();
	/* Initialize peripherals */
	controller_init();
	//initialize the dfs
	dfs_init(DFS_DEFAULT_LOCATION);
	display_init(res, dep, 2, GAMMA_NONE, ANTIALIAS_RESAMPLE);

	while (!(LibN64_Display = display_lock()));
	//display bg color
	graphics_fill_screen(LibN64_Display, 0x0);
	//set text colour
	graphics_set_color(0xFFFFFFFF, 0x0);

	lActive = true;
}

void LibN64::FrameUpdate()  {}
void LibN64::KeyAPressed()  {}
void LibN64::KeyBPressed()  {}
void LibN64::KeyDUPressed() {}
void LibN64::KeyDDPressed() {}
void LibN64::KeyDLPressed() {}
void LibN64::KeyDRPressed() {}
void LibN64::KeyZPressed()	{}
void LibN64::KeyStartPressed() {}
void LibN64::OnCreate() {}

void LibN64::ClearScreen() {
	graphics_fill_screen(LibN64_Display, 0x0);
}

void LibN64::SetScreen(resolution_t resol, bitdepth_t bd)
{
	CheckAndSwitchRes(resol);

	display_close();
	display_init(resol, bd, 2, GAMMA_NONE, ANTIALIAS_RESAMPLE);
	LibN64_Display = display_lock();
}

/*void LibN64::DrawFrame() {
	for (int h = 0; h < screenHeight; h++) {
		for (int w = 0; w < screenWidth; w++) {
			graphics_draw_box(LibN64_Display, w, h, 1,1,screenBuf[h * screenWidth + w]);

		}
	}
}*/

unsigned LibN64::ScreenWidth() { return screenWidth; }

unsigned LibN64::ScreenHeight() { return screenHeight; }


void LibN64::DrawBox(int x, int y, int scale, unsigned c)
{
	graphics_draw_box(LibN64_Display, x, y, scale, scale, c);
}

void LibN64::Begin() 
{	
	this->OnCreate();
	while (lActive) {
		timer_init();
		this->FrameUpdate();

		controller_scan();
		controller_data keys = get_keys_down();

		if (keys.c[0].err == ERROR_NONE) {
			if (keys.c[0].A) {
				this->KeyAPressed();
			}
			if (keys.c[0].B) {
				this->KeyBPressed();
			}
			if (keys.c[0].up) {
				this->KeyDUPressed();
			}
			if (keys.c[0].down) {
				this->KeyDDPressed();
			}
			if (keys.c[0].left) {
				this->KeyDLPressed();
			}
			if (keys.c[0].right) {
				this->KeyDRPressed();
			}
			if (keys.c[0].Z) {
				this->KeyZPressed();
			}
			if (keys.c[0].start) {
				this->KeyStartPressed();
			}
		}
		display_show(LibN64_Display);

		fFrameTime = timer_ticks();
		fTotalTime += fFrameTime;
		timer_close();
	}
}

void LibN64::Close() 
{
	lActive = false;
}
void LibN64::DrawCircle(int x, int y, int scale, unsigned c) 
{
	for(int angles =0;angles<80*scale;angles++) {
		graphics_draw_box(LibN64_Display, x + cosf(angles) * 3.1415f * scale, y + sinf(angles) * 3.1415f * scale, 1, 1, c);
	}
}

void LibN64::DrawLine(int x1, int y1, int x2, int y2, unsigned c) {
	graphics_draw_line(this->LibN64_Display, x1, y1, x2, y2, c);
}

void LibN64::DrawText(int x, int y, const char* buf, unsigned c) 
{
	graphics_set_color(c, 0);
	graphics_draw_text(LibN64_Display, x, y, buf);
	graphics_set_color(WHITE, 0);
}

constexpr auto LibN64::Ticks2Seconds(float t) 
{
	return (t * 0.021333333 / 1000000.0);
}
