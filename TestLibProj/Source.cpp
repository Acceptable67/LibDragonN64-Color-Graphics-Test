#include <libdragon.h>
#include <vector>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "testClass.h"
#include "Source.h"
#include "LibSprite.h"

void init_displays()
{

    /* enable interrupts (on the CPU) */
    //init_interrupts();
    /* Initialize peripherals */
    controller_init();
    //initialize the dfs
    dfs_init(DFS_DEFAULT_LOCATION);

    display_init(res, bit, 2, GAMMA_NONE, ANTIALIAS_RESAMPLE);

    while (!(disp = display_lock()));
    //display bg color
    graphics_fill_screen(disp, 0x0);
    //set text colour
    graphics_set_color(0xFFFFFFFF, 0x0);
}

char map[_HEIGHT][_WIDTH] =
{
    { '#','#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
    { '#','.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
    { '#','.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
    { '#','.', '.', '.', '.', '#', '#', '.', '.', '#', '#', '.', '.', '.', '.', '#'},
    { '#','.', '.', '.', '.', '#', '#', '.', '.', '#', '#', '.', '.', '.', '.', '#'},
    { '#','.', '.', '.', '.', '.', '.', '.', '.', '#', '#', '.', '.', '.', '.', '#'},
    { '#','.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
    { '#','.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
    { '#','.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
    { '#','.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '.', '#'},
    { '#','#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}
};

struct {
    int x;
    int y;
} PCoords = { 1,1 };

int calcMapDraw = SCREEN_WIDTH / 2 - ((SCREEN_WIDTH / 2) / 2 * 1.5);

int bx = calcMapDraw;
int by = 10;

int bh = 15;
int bw = 15;
void draw_msg(long st) {

}

void click(int infl) {

}

libSprite wiz, background, profUp, profDown, profLeft, profRight;

bool WillCollide(int x1, int y1) {
  
    if (map[y1][x1] == '#' ||
        map[y1][x1] == '%') {

        long start = timer_ticks();
        //draw_msg(2);

        while (TICKS_TOTAL(start) < 0.5) {
            background.Draw(disp, 0, TICKS_TOTAL(start), false, 2);
            char buffer[40];
            sprintf(buffer, "Collision detected (Ticks total %f)", TICKS_TOTAL(start));
            DrawText(10, 200, buffer);
        }
        background.Draw(disp, 0, 0, false, 2);
        return true;
    }
    else {
        map[PCoords.y][PCoords.x] = '.';
        PCoords.x = x1;
        PCoords.y = y1;
        map[PCoords.y][PCoords.x] = '&';
         background.Draw(disp, 0, 0, false, 2);
        return false;
    }
}

int angle;

struct gMapItem {
    int x;
    int y;
};

gMapItem weapon, test;

void DrawMap() {
    bx = calcMapDraw;
    //graphics_fill_screen(disp, 0x0);

    DrawBox(bx - 10, 5, _WIDTH * 22, _HEIGHT * 22, GREY);
    for (int h = 0; h < _HEIGHT; h++) {
        for (int w = 0; w < _WIDTH; w++) {
            if (map[h][w] == '#') {
                DrawBox(bx, by, bw, bh, ORANGE);
                //graphics_draw_pixel(disp, x, y, RED);
            }
            if (map[h][w] == '.') {
                //DrawBox(bx, by, bw, bh, WHITE);
                //graphics_draw_pixel(disp, x, y, );
                //drawBox(x, y, x + 1, y + 1, WHITE);
            }
            if (map[h][w] == '&') {
                DrawBox(bx, by, bw, bh, GREEN);
                //graphics_draw_pixel(disp, x, y, G);
            }
            if (map[h][w] == '%') {
                DrawBox(bx, by, bw, bh, SKY_BLUE);
                DrawText(bx, by + 5, (char*)"obj");
                //graphics_draw_pixel(disp, x, y, G);
            }
            bx += boffset;
        }
        bx = calcMapDraw;
        by += boffset;
    }
    /*restore values*/
    bx = calcMapDraw;
    by = boffset;

    /*draw from file*/
    //char(*Text) = (char*)(0xB0204A05);

    char buffer[30];
    sprintf(buffer, "Player X: %d Y: %d", PCoords.x, PCoords.y);
    DrawBox(5, 215, 150, 25, GREY);
    DrawText(10, 220, buffer);

    int distance = 10;
   /* for (int i = 0; i < 10; i++) {
        float nX = PCoords.x + sinf(i) * 3.1415f * distance;
        float nY = PCoords.y + cosf(i) * 3.1415f * distance;
        DrawBox(180 + nX, 20 + nY, 15, 15, RED);
    }*/
}

int ty = 30;

struct {
    int x;
    int y;
} curSprPos = { 20,170};

libSprite* curSpr;

void initLibSprites() {
    wiz.Ready(0x64, 0x96, wizdata);
    background.Ready(0x0140, 0xf0, bgdata);
    profUp.Ready(0x2f, 0x3a, sprPlayerUp);
    profDown.Ready(0x2D, 0x37, sprPlayerDown);
    profLeft.Ready(0x31, 0x37, sprPlayerLeft);
    profRight.Ready(0x2e, 0x36, sprPlayerRight);
}

Vector<int> v;
Vector<String> st;
Vector<float> fl;

//test items
gMapItem items[2] = 
{
    {2,4},
    {3,6} 
};


int main(void) {
    init_displays();
    initLibSprites();
    timer_init();
    map[PCoords.y][PCoords.x] = '&';
   
    DrawMap();
    background.Draw(disp, 0, 0, false, 2);
    
    curSpr = &profDown;
      weapon.x = 4;
    weapon.y = 5;
    test.y = 5;
    test.x = 2;
    
    Vector<gMapItem*> sp;
    sp.push_backp(&items[0]);
    sp.push_backp(&items[1]);

    for (int i = 0; i < 2; i++) {
        map[sp.at<gMapItem*>(i)->y][sp.at<gMapItem*>(i)->x] = '%';
    }
    while (GameLoop) {
        controller_scan();
        controller_data keys = get_keys_down();

        if (keys.c[0].err == ERROR_NONE)
        {
            if (keys.c[0].down)
            {

                if (!WillCollide(PCoords.x, PCoords.y + 1));
                curSpr = &profDown;
                curSprPos.y += 20;

                v.push_back(2);
                v.push_back(4);
              
                
                char buff[45];
                sprintf(buff, "test %d %d c %d stack size %d ptr %p gMapItem1 Y%d X%d gMapItem2 Y%d X%d", v.at(0), v.at(1), v.counter, sizeof(v.stack), &v, sp.at<gMapItem*>(0)->y, sp.at<gMapItem*>(0)->x, sp.at<gMapItem*>(1)->y, sp.at<gMapItem*>(1)->x);
                DrawText(10, 200, buff);
                DrawMap();
            }
            else if (keys.c[0].up)
            {
                if (!WillCollide(PCoords.x, PCoords.y - 1));
                curSpr = &profUp;
                curSprPos.y -= 20;
                DrawMap();
            }
            else if (keys.c[0].left) {
                if (!WillCollide(PCoords.x - 1, PCoords.y));
                curSpr = &profLeft;
                curSprPos.x -= 20;
                DrawMap();
            }
            else if (keys.c[0].right) {
                if (!WillCollide(PCoords.x + 1, PCoords.y));
                curSpr = &profRight;
                curSprPos.x += 20;
                DrawMap();
            }
            else if (keys.c[0].B) {
                angle -= 20;
            }
            else if (keys.c[0].A) {
                angle += 20;
            }

            curSpr->Draw(disp, curSprPos.x, curSprPos.y, true, 2);
            char buf[20];
            sprintf(buf, "X %d Y %d", curSprPos.x, curSprPos.y);
            DrawText(curSprPos.x-20 + sin(angle) * 3.1415f, curSprPos.y-60 + cos(angle) * 3.1415f, buf);
            wiz.Draw(disp, 5, 40, false, 1);

           // st.push_back("test");
            //st.at(0);
        }
        display_show(disp);
    }
    return 0;
}