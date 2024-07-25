#include "ulib.h"

//Si quelqu'un arrive à faire ça en utilisant les TRIANGLE_STRIP, qu'il me fasse un signe, parce que je n'y suis pas arrivé, merci :)
void ulDrawRect(s16 x0, s16 y0, s16 x1, s16 y1, UL_COLOR color)			{
	//Commence le dessin
	GFX_BEGIN = GL_TRIANGLES;
		GFX_COLOR = color;
		GFX_TEX_FORMAT = 0;

		ulVertexXY(x0, y0);
		ulVertexXY(x1, y0);
		ulVertexXY(x1, y0);

		ulVertexXY(x1 - 1, y0);
		ulVertexXY(x1 - 1, y1);
		ulVertexXY(x1 - 1, y1);

		ulVertexXY(x0, y0);
		ulVertexXY(x0, y1);
		ulVertexXY(x0, y1);

		ulVertexXY(x0, y1 - 1);
		ulVertexXY(x1, y1 - 1);
		ulVertexXY(x1, y1 - 1);
		
	GFX_END = 0;

	//Incrémentation auto de la profondeur	
	ul_currentDepth += ul_autoDepth;
}

