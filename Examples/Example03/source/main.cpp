/*
	Example 03
	
	Sample that draws a large number of balls on the screen.
*/

#include "main.h"
#include "CBall.h"

#define MAX_BALLS 40

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

	//Use bright pink as a transparent color
	ulSetTransparentColor(RGB15(31, 0, 31));
	
	//Initialization of balls
	for (i=0;i<MAX_BALLS;i++)			{
	   balls[i] =
			new CBall(										//Create a new ball
				rand() % SCREEN_WIDTH,					//Somewhere random on the screen
				rand() % SCREEN_HEIGHT,					//Same vertically
				rand() % (2 * UL_PI),					//Random angle modulo 2 PI (any possible angle in a circle)
				FIX(1 + rand() % 3)						//Random speed between 1.0 and 4.0
			);
	}

	while(1)
	{
	   //Initialize the timers to measure the framerate
	   TIMER1_CR = 0;
		TIMER1_DATA = 0;
		TIMER1_CR = TIMER_DIV_64 | TIMER_ENABLE;

	   //Read keys
	   ulReadKeys(0);
	   
	   if (!ul_keys.held.R)			{
		   //Handle our balls
	   	for (i=0;i<MAX_BALLS;i++)
				balls[i]->handle();
		}
	   
	   //Start our drawing
		ulStartDrawing2D();
		
		//Draw a gradient background
		ulDrawGradientRect(0, 0, 256, 192, RGB15(0, 0, 24), RGB15(0, 0, 24), RGB15(0, 16, 31), RGB15(0, 16, 31));

	   //Draw our balls
   	for (i=0;i<MAX_BALLS;i++)
			balls[i]->draw();
		
		//Calculate the CPU usage based on the timer value and total time per frame
		int cpuTime = (TIMER1_DATA * 1000) / totalTime;
		ulPrintf_xy(0, 0, "CPU: %02i.%i%%", cpuTime / 10, cpuTime % 10);
		
		//End the drawing
		ulEndDrawing();
		
		//Wait the VBlank (synchronize at 60 fps)
		ulSyncFrame();
		totalTime = TIMER1_DATA;
	}

	//Program end - should never get there
	return 0;
}

