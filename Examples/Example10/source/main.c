/*
	Example 10
	
	More advanced sample showing the improvements of uLib 1.1.
*/

#include <ulib/ulib.h>
#include "calibri.h"
#include "test.h"

int play()
{
   UL_FONT *font;
   UL_IMAGE *img;
   int angle = 0;
   
	//Initialize µLibrary
	ulInit(UL_INIT_ALL);
	//Initialize the graphical part
	ulInitGfx();
	
	font = ulLoadFontFile((const char*)Calibri, (int)Calibri_size);
	if (!font)
		return -1;

	ulSetFont(font);

	img = ulLoadImageFilePNG((const char*)test, (int)test_size, UL_IN_VRAM, UL_PF_PAL5_A3);
	if (!img)
		return -2;

	img->x = 20;
	img->y = 30;

	while(1)
	{
	   //Start our drawing
		ulStartDrawing2D();

		//Write this on polygroup 0
		ulSetAlpha(UL_FX_DEFAULT, 0, 0);

		//Fill the screen with blue
		ulDrawFillRect(0, 0, UL_SCREEN_WIDTH, UL_SCREEN_HEIGHT, RGB15(0, 16, 0));

		//Draw a text scaled by 2x
		ulScaleScreenView(inttof32(2), inttof32(2));
		//Note that because of scaling, the text will in fact be drawn at (16, 30)
		ulDrawString(8, 15, "Hello world!");
		//Restore so that future objects are not transformed too
		ulResetScreenView();

		//To allow blending the image against the background
		ulSetAlpha(UL_FX_DEFAULT, 0, 1);

		//Rotate the image around its center by hand
		ulMoveScreenView(img->sizeX / 2 + img->x, img->sizeY / 2 + img->y);
		ulRotateScreenView(angle++);
		ulMoveScreenView(-(img->sizeX / 2 + img->x), -(img->sizeY / 2 + img->y));
		//Draw the image in the rotated screen
		ulDrawImage(img);
		ulResetScreenView();

		//End the drawing
		ulEndDrawing();

		//Wait the VBlank (synchronize at 60 fps)
		ulSyncFrame();
	}

	//Program end - should never get there
	return 0;
}

int main()		{
	int result = play();
	ulDebug("An error has occured (%i)", result);
	while(1);
	return 0;
}
   
 
