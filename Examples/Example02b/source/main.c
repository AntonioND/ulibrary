/*
	Example 02b
	
	Simple sample that draws an image loaded from memory (into the data folder) and animates it.
*/

#include <ulib/ulib.h>
#include "james_png.h"

//Our image contains 3 frames, one next to the other vertically, and 32 pixel wide.
#define FRAME_HEIGHT 32

int main()
{
   UL_IMAGE *imgJames;
   int animStage = 0, frameNumber = 0;
   //The frame numbers that will be used for animations
   const int animPositions[] = {0, 1, 2, 1};
   
	//Initialize µLibrary
	ulInit(UL_INIT_ALL);
	//Initialize the graphical part
	ulInitGfx();
	//Initialize the text part
	ulInitText();
	//We will use the touchpad this time
	ulSetMainLcd(0);
	
	//Use bright pink as a transparent color
	ulSetTransparentColor(RGB15(31, 0, 31));
	{
		//We load our James character image. Note that the format is PAL4 (16 colors). It is enough for our image but may not for others.
		imgJames = ulLoadImageFilePNG((void*)james_png, (int)james_png_size, UL_IN_VRAM, UL_PF_PAL4);
	}
	ulDisableTransparentColor();
	
	//Define the image center, so that the stylus will control the center of the image. By default, images are specified by their top-left corner (that's the fastest). Usually you should not have to change the image center except for rotation.
	imgJames->centerX = imgJames->sizeX / 2;
	imgJames->centerY = FRAME_HEIGHT / 2;

	while(1)
	{
	   //Read keys
	   ulReadKeys(0);
	   
	   //We place our character to the same position as the touchpad stylus, making it follow it
	   imgJames->x = ul_keys.touch.x;
	   imgJames->y = ul_keys.touch.y;
	   
	   frameNumber++;
	   
	   //Each 8 frames, we increment the frame stage counter, so that we display the next frame
	   if (frameNumber % 8 == 0)
		   //Increment the animation counter
		   animStage = (animStage + 1) % 4;
	   
	   //Start our drawing
		ulStartDrawing2D();
		
		//Draw a gradient background
		ulDrawGradientRect(0, 0, 256, 192, RGB15(0, 0, 0), RGB15(0, 24, 0), RGB15(0, 24, 0), RGB15(0, 0, 0));

		//Set up the sprite part to draw only the desired image part. We could do it by ourself using the offsetX0, ... members.
		ulSetImageTileSize(imgJames,
			0,														//Image frames are aligned vertically, so we always begin to the left
			FRAME_HEIGHT * animPositions[animStage],	//Top position: animPositions defines the frame numbers in the image for each animation step (0, 1, 2, 1). Each frame is FRAME_HEIGHT tall, so we just have to multiply to get the actual position of the frame on the image!
			imgJames->sizeX,									//Every frame takes the entire image width
			FRAME_HEIGHT);										//Height of a frame
		
		//Draw our character on the screen!
		ulDrawImage(imgJames);
		
		//End the drawing
		ulEndDrawing();
		
		//Wait the VBlank (synchronize at 60 fps)
		ulSyncFrame();
	}

	return 0;
}

