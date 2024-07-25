/*
	Example 08
	
	Shows the use of various file systems.
*/

#include <ulib/ulib.h>
#include "roll.h"

//Draws a shadowed string
void drawShadowedText(int x, int y, int color, const char *text);
//Printf that uses the shadowed text routine
#define shadowedPrintf(x, y, color, format...)		({ char __str[1000]; sprintf(__str , ##format); drawShadowedText(x, y, color, __str); })

//Files stored in RAM.
UL_VIRTUALFILENAME ram_names[] =		{
   {"roll.png", (void*)roll, (int)roll_size, &VF_MEMORY},
};

int main()
{	
	UL_IMAGE *imgBack = NULL, *imgRoll = NULL;
	int dblClkAnimCnt = 0, dblClkAnimSens = 0;
	int fsInited = 0, nSystem, oldSource;
	
	//Initialization of the library
	ulInit(UL_INIT_ALL);
	ulInitGfx();
	ulInitText();

	//Show some splash screens!
	ulShowSplashScreen(1);
	ulShowSplashScreen(2);
	
	//Set up the second LCD
	ulSetMainLcd(0);
	
	ulDebug("Welcome!\nUse the touchscreen to make your selection...\n");

	//We show a message box asking the user which system to use
	UL_MSGBOX_BUTTON buttons[3] = {
	   {UL_KEY_Y, "Y: LibFat"},
	   {UL_KEY_B, "B: None"},
	   {UL_KEY_A, "A: GBFS"},
	};
	//Note the Render argument: this function will be called from within ulMessageBoxEx to render the background image!
	nSystem = ulMessageBoxEx("Please select the system you want to use for loading files.", "Hello", 3, buttons, NULL, 0);
	
	//First register the file names for the "none" system
	ulSetVirtualFilenameList(ram_names, ulNumberof(ram_names));
	
	//Auto select source (RAM by default, GBFS or libFat if they're initialized)
	ulSetLoadUtilitySource(-1);

	switch (nSystem)			{
	   case 0:
			//Try to init LibFat
			ulDebug("Initializing libFAT, it may HANG!\n");
			if (ulInitLibFat() > 0)
				fsInited = 1;
			break;
	   case 2:
			//Try to init GBFS	
			ulDebug("Initializing GBFS. If it's not found, verify that you have a slot 2 linker and that you appended GBFS to the end of the ROM.\n");
			if (ulInitGBFS(GBFS_COMPATIBLE_MODE) > 0)
				fsInited = 1;
			break;
	}
	
	//Print to the user if the file system was found
	if (nSystem == 1)
	   ulDebug("No file system chosen!\n");
	else if (fsInited)
	   ulDebug("File system initialized properly!\n");
	else
	   ulDebug("No file system is present!\n");

	ulDebug("Now loading...\n");
	
	//Set up our usual transparent color
	ulSetTransparentColor(RGB15(31, 0, 31));
	{
		//If a filesystem initialized correctly, we will load from it
		if (fsInited)		{
		   //By default all file loading functions will be using GBFS or FAT because we called that functions.
		   imgBack = ulLoadImageFileJPG("/back.jpg", 0, UL_IN_VRAM, UL_PF_5551);
		   if (imgBack)			{
			   //No matter its size, the image should be stretched (or shrinked) to take the entire screen
			   imgBack->stretchX = SCREEN_WIDTH;
			   imgBack->stretchY = SCREEN_HEIGHT;
			}
			else
			   ulDebug("Image could not be loaded!\nMaybe you didn't put a back.jpg image in the root of your file system or the image is too big to be loaded.\n");
		}

		//Now several sources exist, we must select which one we will load from before doing it!
		oldSource = ulSetLoadUtilitySource(VF_MEMORY);
	   //Load our image from memory
		imgRoll = ulLoadImageFilePNG("/roll.png", 0, UL_IN_VRAM, UL_PF_5551);
		//Restore the old source (libfat / gbfs)
		ulSetLoadUtilitySource(oldSource);
	}
	ulDisableTransparentColor();

	//Defines the center of rotation; useful for what will follow ;)
	imgRoll->centerX = imgRoll->sizeX / 2;
	imgRoll->centerY = imgRoll->sizeY / 2;
	
	ulDebug("Used texture mem: %i bytes\n", ulGetTexVramUsedMemory());
	ulDebug("Used palette mem: %i bytes\n", ulGetTexPalUsedMemory());
	
	while(1)
	{
	   ulReadKeys(0);
		//Launches the double click animation
		if (ul_keys.touch.doubleClick && !dblClkAnimCnt)
		   dblClkAnimSens = 16;
	   
		ulStartDrawing2D();
		
		//If the background image has been loaded successfully, then draw it, else draw a gradient.
		if (imgBack)
			ulDrawImage(imgBack);
		else
			ulDrawGradientRect(0, 0, 256, 192, RGB15(0, 0, 16), RGB15(0, 0, 16), RGB15(0, 16, 24), RGB15(0, 16, 24));

		if (!ul_keys.held.touch)		{
		   if (dblClkAnimCnt)
				ulSetAlpha(UL_FX_ALPHA, ulMin(31, 16 + (dblClkAnimCnt >> 4)), 1);
		   else
				ulSetAlpha(UL_FX_ALPHA, 16, 1);
		}
		imgRoll->stretchX = imgRoll->sizeX + ((imgRoll->sizeX * dblClkAnimCnt) >> 8);
		imgRoll->stretchY = imgRoll->sizeY + ((imgRoll->sizeY * dblClkAnimCnt) >> 8);
		
		//Handle rotation
		if (dblClkAnimCnt)		{
		   int value = dblClkAnimCnt;
		   //Dans l'autre sens => la moitié de l'anim a déjà passé
		   if (dblClkAnimSens < 0)
		   	value = 512 - dblClkAnimCnt;
		   else
			   value = dblClkAnimCnt;
			imgRoll->angle = value;
		}
		else
			imgRoll->angle = 0;
		
		ulDrawImageXY(imgRoll, ul_keys.touch.x, ul_keys.touch.y);
		ulSetAlpha(UL_FX_DEFAULT, 0, 0);
		
		//R locks the animation
		if (dblClkAnimSens && !ul_keys.held.R)		{
		   dblClkAnimCnt += dblClkAnimSens;
		   if (dblClkAnimCnt >= 256)
		   	dblClkAnimSens = -16;
		   if (dblClkAnimCnt < 0)
		   	dblClkAnimSens = dblClkAnimCnt = 0;
		}
		
		shadowedPrintf(0, 0, RGB15(31, 0, 0), "Welcome to my first NDS demo ^^");
		shadowedPrintf(0, 184, RGB15(31, 31, 31), "Stylus: %i, %i", ul_keys.touch.x, ul_keys.touch.y);

		ulEndDrawing();
		ulSyncFrame();
	}

	return 0;
}

void drawShadowedText(int x, int y, int color, const char *text)		{
	ulSetTextColor(RGB15(0, 0, 0));
	ulDrawString(x + 1, y + 1, text);
	ulSetTextColor(color);
	ulDrawString(x, y, text);
}


