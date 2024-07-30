/*
	Example 04
	
	Simple sample that shows a mMessage Box
*/

#include <ulib/ulib.h>
//Our map data is in the file Map.c
#include "Map.h"
//Our tileset PNG data
#include "mountains_png.h"

//Make it global so we can access it from our Render function
UL_MAP *mapMountains;

//This function will do our render
void Render()		{
   //Draw a background
   ulDrawGradientRect(0, 0, 256, 144, RGB15(31, 24, 13), RGB15(31, 24, 13), RGB15(31, 28, 22), RGB15(31, 28, 22));
   
   //Draw the map
   ulDrawMap(mapMountains);
   //Make it scroll horizontally
   mapMountains->scrollX++;

	//Print the memory currently usage out of the total number of objects possible on the screen at once
   ulPrintf_xy(0, 184, "GPU load: %i%%", (GFX_VERTEX_RAM_USAGE * 100) / 6144);
}

int main()
{
   //Image of our tileset
   UL_IMAGE *imgMountains;
   
	//Initialize µLibrary
	ulInit(UL_INIT_ALL);
	//Initialize the graphical part
	ulInitGfx();
	//Initialize the text part
	ulInitText();

	//Show some splash screens!
	ulShowSplashScreen(1);
	ulShowSplashScreen(2);

	//We'll work with the touchpad
	ulSetMainLcd(0);

	//Load our tileset
	ulSetTransparentColor(RGB15(31, 0, 31));
	imgMountains = ulLoadImageFilePNG((void*)mountains_png, (int)mountains_png_size, UL_IN_RAM, UL_PF_PAL4);

	//Now we can create a map with that tileset
	mapMountains = ulCreateMap(
		imgMountains,						//Tileset
		mountains_map,						//Map data
		16,16,								//Tiles size
		32,12,								//Map size
		UL_MF_U16);							//Map format

	//Output something to the top screen
	ulDebug("Touch the screen to open a\ndialog box!");

	while(1)
	{
	   ulReadKeys(0);
	   if (ul_keys.touch.click)		{
			UL_MSGBOX_BUTTON buttons[2] = {
			   {UL_KEY_A, "A: Continue"},
			   {UL_KEY_B, "B: quit"},
			};
			//Note the Render argument: this function will be called from within ulMessageBoxEx to render the background image!
			ulMessageBoxEx("Welcome!\nThis is a message box, you can move it, touch the buttons or press the corresponding keys.", "Hello!", 2, buttons, Render, 0);
	   }
	   
	   //Start our drawing
		ulStartDrawing2D();

		Render();
		
		//End the drawing
		ulEndDrawing();
		
		//Wait the VBlank (synchronize at 60 fps)
		ulSyncFrame();
	}

	//Program end - should never get there
	return 0;
}

