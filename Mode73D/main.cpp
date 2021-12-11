#include <stdio.h>
#include <stdlib.h>
#include <LibSprite.h>
#include <LibN64Lib.h>
#include "Sprites.h"

/*test of pseudo-3D planes on LibDragon.*/

/*conversion of Javid9X's Mode7 code to LibDragon*/
class Mode7Test : public LibN64 {
public:
	Mode7Test(resolution_t res, bitdepth_t dep) : LibN64(res, dep) {}

	float fWorldX;
	float fWorldY;
	float fWorldA;
	float fNear;
	float fFar;
	float fFoVHalf;

	int nMapSize;

	void DrawMode() 
	{
		//ClearScreen();
	
		float fFarX1 = fWorldX + cosf(fWorldA - fFoVHalf) * fFar;
		float fFarY1 = fWorldY + sinf(fWorldA - fFoVHalf) * fFar;

		float fNearX1 = fWorldX + cosf(fWorldA - fFoVHalf) * fNear;
		float fNearY1 = fWorldY + sinf(fWorldA - fFoVHalf) * fNear;

		float fFarX2 = fWorldX + cosf(fWorldA + fFoVHalf) * fFar;
		float fFarY2 = fWorldY + sinf(fWorldA + fFoVHalf) * fFar;

		float fNearX2 = fWorldX + cosf(fWorldA + fFoVHalf) * fNear;
		float fNearY2 = fWorldY + sinf(fWorldA + fFoVHalf) * fNear;
		for (int y = 0; y < ScreenHeight() - 80; y++)
		{
		
			float fSampleDepth = (float)y / ((float)ScreenHeight() - 160);

			float fStartX = (fFarX1 - fNearX1) / (fSampleDepth)+fNearX1;
			float fStartY = (fFarY1 - fNearY1) / (fSampleDepth)+fNearY1;
			float fEndX = (fFarX2 - fNearX2) / (fSampleDepth)+fNearX2;
			float fEndY = (fFarY2 - fNearY2) / (fSampleDepth)+fNearY2;

			for (int x = 0; x < ScreenWidth(); x++)
			{
					float fSampleWidth = (float)x / (float)ScreenWidth();
					float fSampleX = (fEndX - fStartX) * fSampleWidth + fStartX;
					float fSampleY = (fEndY - fStartY) * fSampleWidth + fStartY;

					/*extend map forever*/
					//fSampleX = fmod(fSampleX, 1.0f);
					//fSampleY = fmod(fSampleY, 1.0f);

					int sx = (int)(fSampleX * (float)320.00);
					int sy = (int)(fSampleY * (float)240.00 - 1.0f);


					if ((sy * 320 + sx) < sizeof(bgdata)) {
						int col = bgdata[sy * 320 + sx];
						DrawBox(x, y + (ScreenHeight() - 160), 1, col);
					}

					DrawBox(x, (ScreenHeight() - 160) - y, 1, CYAN);
			}
		}


		graphics_draw_line(LibN64_Display, 0, ScreenHeight() - 160, ScreenWidth(), ScreenHeight() - 160, NAVY_BLUE);


		DrawTextFormat(20, 25,(char*)("[Angle] %f\n[F] %f\n[N] %f"), fWorldA, fFar, fNear);
		DrawTextFormat(20, 55,(char*)("[X] %f [Y] %f\n[FoV] %f"), fWorldX, fWorldY, fFoVHalf);
	}

private:
	virtual void OnCreate() override 
	{

		nMapSize = 1024;
		fWorldX = 000.0f;
		fWorldY = 000.0f;
		fWorldA = 0.1f;
		fNear = 0.01f;
		fFar = 0.8f;
		fFoVHalf = 3.14159f / 4.0f;
	}

protected:
	virtual void KeyDLPressed() override 
	{
		fWorldA -= 0.5f;
		DrawMode();
	}

	virtual void KeyDRPressed() override 
	{
		fWorldA += 0.5f;
		DrawMode();
	}

	virtual void KeyDUPressed() override
	{
		fWorldX += cosf(fWorldA) * 0.1f;
		fWorldY += sinf(fWorldA) * 0.1f;
		DrawMode();
	}

	virtual void KeyDDPressed() override
	{
		fWorldX -= cosf(fWorldA) * 0.1f;
		fWorldY -= sinf(fWorldA) * 0.1f;
		DrawMode();
	}
	
	virtual void KeyAPressed() override 
	{
		//fFar += 0.1;
	}

	virtual void KeyBPressed() override 
	{
		fFar -= 0.1;
	}
	virtual void KeyZPressed() override
	{
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
	Mode7Test n64g(RESOLUTION_320x240, DEPTH_32_BPP);
	n64g.Begin();

	return 0;
}
