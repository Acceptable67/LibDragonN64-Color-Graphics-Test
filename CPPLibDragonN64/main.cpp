#include <stdio.h>
#include <stdlib.h>
#include <LibSprite.h>
#include "LibN64.h"
#include "Sprites.h"
/*  virtual functions to override:
    KeyAPressed
    KeyBPressed
    KeyDUPressed
    KeyDDPressed
    KeyDLPressed
    KeyDRPressed
    KeyZPressed
    OnCreate
    FrameUpdate
*/

libSprite logo;

class Instance : public LibN64 {
public:
    char* buffer;
    Instance(resolution_t res, bitdepth_t dep) : LibN64(res, dep) {}

    virtual void OnCreate() override 
    {
        int* n64logo = __lib64_rom2buf<int>(0xB020120C, 0x50 * 0x4E);
       
        /*any initialization code*/
        logo.Ready(0x50, 0x4E, n64logo);
        romTitle = "LibN64 Test";
    }
    
protected:
    virtual void FrameUpdate() override
    {

        //ClearScreen();
        DrawText(5, 10, "This is a test of the CPP LibDragon\nframework.");
        DrawCircle(30, 60, 6, RED);
        DrawTextFormat(30, 90, "Total %.4f Elapsed %.4f", TICKS2SECONDS(fTotalTime), TICKS2SECONDS(fFrameTime));
        DrawTextFormat(2, 4, "%s", buffer);
        /*Draw N64 logo*/
        logo.Draw(LibN64_Display, 10, 160, 1, 1);
    }
    
    virtual void KeyAPressed() override {
        DrawText(10, 30, (char*)"Key A pressed.");
    }

    virtual void KeyBPressed() override {
        ClearScreen();
    }
    
    virtual void KeyZPressed() override {
        /*Alternate resolution*/
        res = ~res & 1;
        if (res) {
            SetScreen(RESOLUTION_320x240, DEPTH_32_BPP);
        }
        else {
            SetScreen(RESOLUTION_256x240, DEPTH_32_BPP);
        }
    }
private:
    int res;
};

int main(void) {
    Instance n64g(RESOLUTION_320x240, DEPTH_32_BPP);
    n64g.Begin();
   
    return 0;
}
