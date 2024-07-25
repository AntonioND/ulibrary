//Includes PALib and µLibrary
#include "main.h"

int main()
{	
	//Initialization of PA_Lib
	PA_Init();
	PA_InitVBL();

	//Initialization of µlibrary
	ulInit(UL_INIT_ALL);
	ulInitGfx();
	ulInitText();
	
	while(1)
	{
	   ulReadKeys(0);
			   
		ulStartDrawing2D();

		ulEndDrawing();
		ulSyncFrame();
	}

	return 0;
}

