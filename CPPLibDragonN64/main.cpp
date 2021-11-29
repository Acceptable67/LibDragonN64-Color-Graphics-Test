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
    Instance(resolution_t res, bitdepth_t dep) : LibN64(res, dep) {}

    virtual void OnCreate() 
    {
        /*any initialization code*/
        romTitle = "LibN64 Test";
    }
    
protected:
    virtual void FrameUpdate() 
    {
        DrawText(5, 10, "This is a test of the CPP LibDragon\nframework.");
        DrawCircle(30, 60, 6, RED);
        DrawTextFormat<float, float>(30, 90, (char*)"Total %f Elapsed %f", TICKS2SECONDS(fTotalTime), TICKS2SECONDS(fFrameTime));

        /*Draw N64 logo*/
        logo.Draw(LibN64_Display, 10, 160, 1, 1);
    }
    
    virtual void KeyAPressed() {
        DrawText(10, 30, (char*)"Key A pressed.");
    }

    virtual void KeyBPressed() {
        ClearScreen();
    }
    
    virtual void KeyZPressed() {
        /*Alternate resolution*/
        res = ~res & 1;
        if (res) {
            SetScreen(RESOLUTION_320x240, DEPTH_32_BPP);
        }
        else {
            SetScreen(RESOLUTION_640x480, DEPTH_32_BPP);
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
