#include "LibN64.h"

LibN64::LibN64(resolution_t res=RESOLUTION_320x240, bitdepth_t dep=DEPTH_32_BPP) {
	LibN64_Display = 0;
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

}

void LibN64::FrameUpdate() { }

void LibN64::DrawBox(int x, int y, int scale, uint32_t c=WHITE)
{
	graphics_draw_box(LibN64_Display, x, y, scale, scale, c);
}

void LibN64::Begin() {
	display_show(LibN64_Display);
	
	while (lActive) {
		this->FrameUpdate();
	}
}

void LibN64::Close() {
	lActive = false;
}

void LibN64::DrawText(int x, int y, char* buf, uint32_t c=WHITE) {
	graphics_set_color(c, 0);
	graphics_draw_text(LibN64_Display, x, y, buf);
	graphics_set_color(WHITE, 0);
}