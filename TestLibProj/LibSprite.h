#pragma once
#include <libdragon.h>
#include "Source.h"


class libSprite {
public:
    void Ready(int w, int h, int* nd) {
        this->Width = w;
        this->Height = h;
        this->Data = (int*)malloc(Width * Height);
        this->Data = nd;
    }

    void Draw(int x, int y, bool alpha, int scale) {
        for (int h = 0; h < Height; h++) {
            for (int w = 0; w < Width; w++) {
                if (!(Data[h * Width + w] >= 0xFFFE0000 && alpha == 1)) {
                    //graphics_draw_pixel(disp, x + (w), y + (h), sprArray[h * IMAGE_WIDTH + w]);
                    graphics_draw_box(disp, x + (w * scale), y + (h * scale), scale, scale, Data[h * Width + w]);
                }
            }
        }
    }

private:
    int Width;
    int Height;
    int* Data;
};
