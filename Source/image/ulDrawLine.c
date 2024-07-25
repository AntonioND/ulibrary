#include "ulib.h"

void ulDrawLine(s16 x0, s16 y0, s16 x1, s16 y1, UL_COLOR color)			{
	//Commence le dessin
	GFX_BEGIN = GL_TRIANGLES;
		GFX_COLOR = color;
		GFX_TEX_FORMAT = 0;

		GFX_VERTEX16 = ((u16)y0 << 16) | (u16)x0;
		GFX_VERTEX16 = ul_currentDepth;
		
		GFX_VERTEX16 = ((u16)y1 << 16) | (u16)x1;
		GFX_VERTEX16 = ul_currentDepth;
		
		GFX_VERTEX16 = ((u16)y1 << 16) | (u16)x1;
		GFX_VERTEX16 = ul_currentDepth;

	GFX_END = 0;

	//Incrémentation auto de la profondeur	
	ul_currentDepth += ul_autoDepth;
}

