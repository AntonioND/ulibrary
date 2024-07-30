/*
	Example 02
	
	Simple sample that draws an image loaded from memory (into the data folder).
*/

#include <ulib/ulib.h>
#include "tails_png.h"

int main()
{
   UL_IMAGE *imgTails;
   
	//Initialize µLibrary
	ulInit(UL_INIT_ALL);
	//Initialize the graphical part
	ulInitGfx();
	//Initialize the text part
	ulInitText();

	//Show some splash screens!
	ulShowSplashScreen(1);
	ulShowSplashScreen(2);

	//We will use the touchscreen this time
	ulSetMainLcd(0);
	
	//Use bright pink as a transparent color
	ulSetTransparentColor(RGB15(31, 0, 31));
	{
		//We load our Tails character image. Note that the format is PAL4 (16 colors). It is enough for our image but may not for others.
		imgTails = ulLoadImageFilePNG((void*)tails_png, (int)tails_png_size, UL_IN_VRAM, UL_PF_PAL4);
	}
	ulDisableTransparentColor();
	
	//Define the image center, so that the stylus will control the center of the image.
	ulImageSetRotCenter(imgTails);

	while(1)
	{
	   //Read keys
	   ulReadKeys(0);
	   
	   //We place our character to the same position as the touchpad stylus, making it follow it
	   imgTails->x = ul_keys.touch.x;
	   imgTails->y = ul_keys.touch.y;
	   
	   //Start our drawing
		ulStartDrawing2D();
		
		//Draw a gradient background
		ulDrawGradientRect(0, 0, 256, 192, RGB15(0, 0, 24), RGB15(0, 0, 0), RGB15(0, 0, 0), RGB15(0, 0, 24));
		
		//Draw our cuty character on the screen!
		ulDrawImage(imgTails);
		
		//End the drawing
		ulEndDrawing();
		
		//Wait the VBlank (synchronize at 60 fps)
		ulSyncFrame();
	}

	//Program end - should never get there
	return 0;
}

