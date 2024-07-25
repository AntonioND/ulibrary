/*
	Example 05
	
	Simple dual screen hello world sample!
*/

#include <ulib/ulib.h>

int main()
{
   int currentFrame = 0;
   
	//Initialize µLibrary
	ulInit(UL_INIT_ALL);
	//Initialize the graphical part
	ulInitGfx();
	//Initialize the text part
	ulInitText();

	//Show some splash screens!
	ulShowSplashScreen(1);
	ulShowSplashScreen(2);

	//Set-up dual screen mode. Beware!!! It will eat up 2 whole banks (C-D) and force your game to run at 30 fps!
	ulInitDualScreenMode();
	
	while(1)
	{
	   currentFrame++;
	   
	   //Start our drawing
		ulStartDrawing2D();
		
		if (ulGetMainLcd())		{
			//We're on the touchpad
			ulDrawGradientRect(0, 0, 256, 192, RGB15(31, 0, 0), RGB15(0, 0, 0), RGB15(0, 0, 0), RGB15(31, 0, 0));
			ulDrawString(0, 0, "Even on the second screen!");
		}
		else		{
			//We're on the top screen
			ulDrawGradientRect(0, 0, 256, 192, RGB15(0, 0, 0), RGB15(0, 0, 31), RGB15(0, 0, 31), RGB15(0, 0, 0));
			ulDrawString(0, 0, "Hello world!");
		}
		
		//End the drawing
		ulEndDrawing();
		
		//Wait the VBlank (synchronize at 60 fps)
		ulSyncFrame();
	}

	//Program end - should never get there
	return 0;
}

