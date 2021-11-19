#include <libdragon.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
//#include <iostream>

#include "Source.h"


//uint32_t colors[11];


/*between x and y*/
#define RAND(x,y) rand() % y + x

class libConsoleGameEngine {
public:
	char screenBuffer[640*480];
	uint32_t colorBuf[640*480];
	int screenWidth;
	int screenHeight;
	

	void Init(int w, int h) {
		/*array initialization does not work*/
		colors[0] = RED;
		colors[1] = GREEN;
		colors[2] = WHITE;
		colors[3] = SKY_BLUE;
		colors[4] = CYAN;
		colors[5] = ORANGE;
		colors[6] = GOLD;
		colors[7] = YELLOW;
		colors[8] = GREY;
		colors[9] = WHITE;
		colors[10] = DARK_RED;
		colors[11] = SKY_BLUE;

		screenWidth = w;
		screenHeight = h;
	
		for (int i = 0; i < (screenWidth*screenHeight); i++) {
			colorBuf[i] = colors[RAND(2,7)];
		}

		DrawScreen_LBL();
	}

	void DrawScreen_PBP() {
		for (int h = 0; h < screenHeight; h++) {
			for (int w = 0; w < screenWidth; w++) {
				graphics_draw_box(disp, w, h,1,1, colors[RAND(0,11)]);
			}
		}
		
	}

	void DrawScreen_LBL() {
		for (int h = 0; h < screenHeight; h++) {
			uint32_t new_color = colors[rand() % 11 + 0];
			for (int w = 0; w < screenWidth; w++) {
				graphics_draw_box(disp, w, h, 1, 1, new_color);
			}
		}

	}

	void DrawCircle(int x, int y, int size) {
		for(int a = 0;a<80;a++)
			graphics_draw_box(disp, x + cosf(a) * 3.1415f * size, y + sinf(a) * 3.1415f * size, 2, 2, colors[RAND(9, 11)]);
	}

	void draw(int y, int x, uint32_t color) {
		colorBuf[y * screenWidth + x] = color;
	}
};


void init_displays()
{

	/* enable interrupts (on the CPU) */
	init_interrupts();
	/* Initialize peripherals */
	controller_init();
	//initialize the dfs
	dfs_init(DFS_DEFAULT_LOCATION);

	display_init(res, dep, 2, GAMMA_NONE, ANTIALIAS_RESAMPLE);

	while (!(disp = display_lock()));
	//display bg color
	graphics_fill_screen(disp, 0x0);
	//set text colour
	graphics_set_color(0xFFFFFFFF, 0x0);
}

libConsoleGameEngine geInstance;

bool running = true;

void __header() {
	graphics_draw_box(disp, 15, 15, 85, 30, 0x00);
	graphics_draw_text(disp, 20, 20, "Color Gen");
	graphics_set_color(RED, 0x0);
	graphics_draw_text(disp, 20, 32, (res==RESOLUTION_640x480) ? "[HI-RES]" : "[LO-RES]");
	graphics_set_color(WHITE, 0x0);
	graphics_draw_box(disp, 15, 75, 230, 20, 0x00);
	graphics_draw_text(disp, 20, 80, "<Press up to regenerate pbp>");
	graphics_draw_box(disp, 15, 105, 245, 20, 0x00);
	graphics_draw_text(disp, 20, 110, "<Press down to regenerate lbl>");
}

int s;

float angle = 0;
float distance = 0;
int main() {
	init_displays();
	timer_init();
	geInstance.Init(SWIDTH, SHEIGHT);
	geInstance.DrawScreen_LBL();
	
	long timer_start = timer_ticks();

	int cx = 260, cy = 160;
	__header();
	while (running) {

		controller_scan();
		controller_data keys = get_keys_down();
		if (keys.c[0].err == ERROR_NONE)
		{
			if (keys.c[0].up) {
				geInstance.DrawScreen_PBP();
				__header();
			}

			if (keys.c[0].down) {
				geInstance.DrawScreen_LBL();
				__header();
			}

			if (keys.c[0].C_left)  { cx -= 5.0;}
			if (keys.c[0].C_right) { cx += 5.0;}
			if (keys.c[0].C_up)    { cy -= 3.0; }
			if (keys.c[0].C_down)  { cy += 3.0; }

			if (keys.c[0].left) {
				angle -= 0.2;
			}
			if (keys.c[0].right) {
				angle += 0.2;
			}
			if (keys.c[0].Z) {
				distance += 1;
			}
			if (keys.c[0].B) {
				display_close();
				res = RESOLUTION_640x480;
				display_init(RESOLUTION_640x480, dep, 2, GAMMA_NONE, ANTIALIAS_RESAMPLE);
				disp = display_lock();
				geInstance.Init(640, 480);
			}
			if (keys.c[0].A) {
				display_close();
				res = RESOLUTION_320x240;
				display_init(RESOLUTION_320x240, dep, 2, GAMMA_NONE, ANTIALIAS_RESAMPLE);
				disp = display_lock();
				geInstance.Init(320, 240);
			}
			if (keys.c[0].start) {
				s = ~s & 1;
				if (s) {
					graphics_draw_box(disp, geInstance.screenWidth / 2 - 100, geInstance.screenHeight / 2 - 80, 200, 120, RED);
					graphics_draw_text(disp, geInstance.screenWidth / 2 - 60, geInstance.screenHeight / 2 - 70, "HELP MENU");
					graphics_draw_text(disp, geInstance.screenWidth / 2 - 60, geInstance.screenHeight / 2 - 65, "---------");
					graphics_draw_text(disp, geInstance.screenWidth / 2 - 80, geInstance.screenHeight / 2 - 55, "C-UP/DOWN/LEFT/RIGHT\nto move circle");
				} else {
					geInstance.DrawScreen_LBL();
					__header();
				}
			}
		}
		int linex = 40 + cosf(angle) * 3.1415 * distance;
		int liney = 80 + sinf(angle) * 3.1415 * distance;
		geInstance.DrawCircle(cosf(TicksInSeconds) * 3.1415f + 40, 160 + sinf(TicksInSeconds) * 3.1415f * 6, 4);
		geInstance.DrawCircle(120 + cosf(TicksInSeconds) * 3.1415f * 18, 160 + atanf(TicksInSeconds) * 3.1415f * 6, 4);
		graphics_draw_line(disp, 40 + TicksInSeconds, 30 + TicksInSeconds, linex,liney, RED);
		char buffer[50];
		sprintf(buffer, "x difference %f\ny %f\nc = %f\nline deg.%f", (40 + TicksInSeconds - linex), (30 + TicksInSeconds - liney), sqrt(pow(40 + TicksInSeconds - linex,2) + pow(30 + TicksInSeconds - liney,2)), angle/3.1415 * 180);
		graphics_set_color(GOLD, 0x0);
		graphics_draw_box(disp, 125, 15, 200, 40, 0x0);
		graphics_draw_text(disp, 130, 20, buffer);
		graphics_set_color(WHITE, 0x0);
		geInstance.DrawCircle(cx, cy, 4);


		long timer_running = timer_ticks();

		if (((timer_running - timer_start) * 0.021333333 / 1000000.0) >= 15) {
			timer_close();
			timer_init();
			timer_start = 0; timer_running = 0;
			geInstance.DrawScreen_PBP();
			__header();
		}


		char showTime[35]; 
		graphics_draw_box(disp, geInstance.screenWidth - 315, geInstance.screenHeight - 20, 310, 20, 0x00);
		sprintf(showTime, "Elapsed %.2f Start %.2f Remaining %.2f", TicksInSeconds, (timer_ticks() - timer_start) * 0.021333333 / 1000000.0, 15 - TicksInSeconds);
		graphics_draw_text(disp, geInstance.screenWidth - 310, geInstance.screenHeight - 15, showTime);
		display_show(disp); 
	}


	return 0;
}