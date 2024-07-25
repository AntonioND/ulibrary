/*
	Example 01
	
	Simple hello world sample!
*/

#include <ulib/ulib.h>
#include "tails.h"

int main()
{
	UL_IMAGE *imgTails;
	int i;
	//Initialize µLibrary
	ulInit(UL_INIT_ALL);
	//Initialize the graphical part
	ulInitGfx();
	//Initialize the text part
	ulInitText();

	//Show some splash screens!
//	ulShowSplashScreen(1);
//	ulShowSplashScreen(2);

	//Use bright pink as a transparent color
	ulSetTransparentColor(RGB15(31, 0, 31));
	{
		//We load our Tails character image. Note that the format is PAL4 (16 colors). It is enough for our image but may not for others.
		imgTails = ulLoadImageFilePNG((void*)tails, (int)tails_size, UL_IN_VRAM, UL_PF_PAL5_A3);
	}
	ulDisableTransparentColor();
	
	ulDebug("Used texture mem: %i bytes\n%x", ulGetTexVramUsedMemory(), imgTails);
	
	while(1)
	{
	   //Start our drawing
		ulStartDrawing2D();
		
		ulDrawGradientRect(0, 0, 256, 192, RGB15(0, 0, 31), RGB15(0, 16, 31), RGB15(0, 16, 31), RGB15(0, 31, 31));
		//Draw a string (text) at top-left of the screen
		ulDrawString(0, 0, "Hello world!");

		ulSetAlpha(UL_FX_ALPHA, 31, 1);		
		ulDrawImage(imgTails);
		ulSetAlpha(UL_FX_ALPHA, 0, 0);
		
		//End the drawing
		ulEndDrawing();
		
		//Wait the VBlank (synchronize at 60 fps)
		ulSyncFrame();
	}

	//Program end - should never get there
	return 0;
}

