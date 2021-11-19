#include <stdio.h>
#include <stdlib.h>

#include "LibN64.h"
class Instance : public LibN64 {
public:
    Instance(resolution_t res, bitdepth_t dep) : LibN64(res, dep) {}

    virtual void OnCreate() 
    {

    }
protected:
    virtual void FrameUpdate() 
    {
        DrawText(5, 10, (char*)"This is a test of the CPP LibDragon\nframework.");
    }
    
    virtual void KeyAPressed() {
        DrawText(10, 30, (char*)"Key A pressed.");
    }
};

int main(void) {
    Instance n64g(RESOLUTION_320x240, DEPTH_32_BPP);
    n64g.Begin();
   
    return 0;
}
