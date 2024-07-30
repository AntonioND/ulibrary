/*
	Example 01
	
	Simple hello world sample!
*/

#include <ulib/ulib.h>

int main()
{
	//Initialize µLibrary
	ulInit(UL_INIT_ALL);
	//Initialize the graphical part
	ulInitGfx();
	//Initialize the text part
	ulInitText();

	//Show some splash screens!
	ulShowSplashScreen(1);
	ulShowSplashScreen(2);

	while(1)
	{
	   //Start our drawing
		ulStartDrawing2D();
		
		//Draw a string (text) at top-left of the screen
		ulDrawString(0, 0, "Hello world!");
		
		//End the drawing
		ulEndDrawing();
		
		//Wait the VBlank (synchronize at 60 fps)
		ulSyncFrame();
	}

	//Program end - should never get there
	return 0;
}
 
