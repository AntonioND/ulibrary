//Our main file
#include "main.h"
//Class definition
#include "CBall.h"
//Our ball PNG data
#include "ball_png.h"

//These variables are shared between all instances, only one image is needed in memory at a time to draw every ball ;)
int CBall::nInstances = 0;
UL_IMAGE *CBall::imgBall;

//Constructor
CBall::CBall(int x, int y, int angle, int speed)		{
   //First time: load the ball image
	if (this->nInstances == 0)			{
		//We load our ball image. Note that the format is PAL2 (4 colors). It's enough because our image is nearly monochrome.
		this->imgBall = ulLoadImageFilePNG((const char*)ball_png, (int)ball_png_size, UL_IN_VRAM, UL_PF_PAL2);
	}
   this->nInstances++;
   
   //Initialize the class members - positions are passed as integer values, convert them to fixed point values
   this->x = FIX(x);
   this->y = FIX(y);
   this->angle = angle;
   this->speed = speed;
   
   //Dimensions are determined with the image size
   this->width = FIX(this->imgBall->sizeX);
   this->height = FIX(this->imgBall->sizeY);
   
   //White by default
   this->color = 0x7fff;
}

//Destructor
CBall::~CBall()		{
   //No more instances?
   this->nInstances--;
	if (this->nInstances == 0)			{
	   //Unload our image!
	   ulDeleteImage(this->imgBall);
	}
}

//Move our ball (called each frame)
void CBall::handle()			{
   //Move our ball
   this->x += ulCos(this->angle, this->speed);
   this->y += ulSin(this->angle, this->speed);
   
   //Handle collisions with the screen borders
   if (this->y < 0)			{
      this->angle = 2 * UL_PI - this->angle;
      this->y = 0;
   }   
   else if (this->y + this->height > FIX(TOTAL_SCREEN_HEIGHT))			{
      this->angle = 2 * UL_PI - this->angle;
      this->y = FIX(TOTAL_SCREEN_HEIGHT) - this->height;
   }   
	
   if (this->x < 0)			{
      this->angle = UL_PI - this->angle;
      this->x = 0;
   }   
   else if (this->x + this->width > FIX(UL_SCREEN_WIDTH))			{
      this->angle = UL_PI - this->angle;
      this->x = FIX(UL_SCREEN_WIDTH) - this->width;
   }   
}

//Draw our ball
void CBall::draw(int offset)			{	   
   //Set the ball color
	ulSetImageTint(this->imgBall, this->color);
   
   //Is the ball in the screen we are drawing to?
   if (UNFIX(this->y + this->height) >= offset && UNFIX(y) <= offset + SCREEN_HEIGHT)			{
	   //Draw the ball image
   	ulDrawImageXY(this->imgBall, UNFIX(this->x), UNFIX(this->y) - offset);
	}
}

void CBall::setColor(u16 color)		{
   this->color = color;
}

   
