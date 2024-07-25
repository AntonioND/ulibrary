#include <ulib/ulib.h>

//Class handling a ball
class CBall		{
private:
	static UL_IMAGE *imgBall;
	static int nInstances;
	int x, y, width, height, angle, speed;

public:
   CBall(int x, int y, int angle, int speed);
   ~CBall();
   
   void handle();
   void draw();
};

//Make it a fixed point value (1 = 256, 0.5 = 128, etc.)
#define FIX(x)		((x) << 8)
//Return the real value of a fixed point
#define UNFIX(x)	((x) >> 8)


