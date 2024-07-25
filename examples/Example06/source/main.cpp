/*
	Example 06
	
	Sample that draws a large number of tinted balls on both screens.
*/

#include "main.h"
#include "CBall.h"

#define MAX_BALLS 120

int main()
{
   CBall *balls[MAX_BALLS];
   int i;
	int totalTime = 1;									//To avoid a divide by zero the first time
   
	//Initialize µLibrary
	ulInit(UL_INIT_ALL);
	//Initialize the graphical part
	ulInitGfx();
	//Initialize the text part
	ulInitText();

	//Show some splash screens!
	ulShowSplashScreen(1);
	ulShowSplashScreen(2);

	//Sucks banks C-D + drops at 30 fps
	ulInitDualScreenMode();	
	
	//Use bright pink as a transparent color
	ulSetTransparentColor(RGB15(31, 0, 31));
	
	//Initialization of balls
	for (i=0;i<MAX_BALLS;i++)			{
	   balls[i] =
			new CBall(										//Create a new ball
				rand() % SCREEN_WIDTH,					//Somewhere random on the screen
				rand() % TOTAL_SCREEN_HEIGHT,			//Same vertically
				rand() % (2 * UL_PI),					//Random angle modulo 2 PI (any possible angle in a circle)
				FIX(2 + rand() % 6)						//Random speed between 2.0 and 6.0 (game is running at half the framerate, so we need a double speed)
			);
		//Set a random color
		balls[i]->setColor(RGB15(4, 4, 4) | (rand() % 0x7fff));
	}

	while(1)
	{
	   //Update only one time of two, else the game will run too fast!
	   if (!ulGetMainLcd())			{
		   //Read keys
		   ulReadKeys(0);
		   
		   if (!ul_keys.held.R)			{
			   //Handle our balls
		   	for (i=0;i<MAX_BALLS;i++)
					balls[i]->handle();
			}
		}
		
	   //Start our drawing
		ulStartDrawing2D();
		
		if (!ulGetMainLcd())		{
		   //If we're there, then we control the top screen
		   
			//Draw a gradient background
			ulDrawGradientRect(0, 0, 256, 192, RGB15(0, 0, 24), RGB15(0, 0, 24), RGB15(0, 16, 31), RGB15(0, 16, 31));
	
		   //Draw our balls
	   	for (i=0;i<MAX_BALLS;i++)
				balls[i]->draw(0);
		}
		else			{
		   //Else we're on the touchpad
		   
			//Draw a gradient background
			ulDrawGradientRect(0, 0, 256, 192, RGB15(0, 16, 31), RGB15(0, 16, 31), RGB15(16, 24, 31), RGB15(16, 24, 31));
	
		   //Draw our balls but only the one which are on the bottom screen
	   	for (i=0;i<MAX_BALLS;i++)
				balls[i]->draw(SCREEN_HEIGHT + BORDER_HEIGHT);
			
			ulSetTextColor(RGB15(0, 0, 0));
			ulDrawString(1, 184, "Press R to hold");
			ulSetTextColor(RGB15(31, 31, 31));
			ulDrawString(0, 183, "Press R to hold");
		}
					
		//End the drawing
		ulEndDrawing();
		
		//Wait the VBlank (synchronize at 60 fps)
		ulSyncFrame();
		totalTime = TIMER1_DATA;
	}

	//Program end - should never get there
	return 0;
}

