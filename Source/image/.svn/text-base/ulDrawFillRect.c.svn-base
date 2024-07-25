#include "ulib.h"

void ulDrawFillRect(s16 x0, s16 y0, s16 x1, s16 y1, UL_COLOR color)			{
	//Commence le dessin
	GFX_BEGIN = GL_QUADS;
		GFX_COLOR = color;
		GFX_TEX_FORMAT = 0;

		//1. Haut-gauche
		GFX_VERTEX16 = ((u16)y0 << 16) | (u16)x0;
		GFX_VERTEX16 = ul_currentDepth;
		
		//2. Haut-droite
		GFX_VERTEX16 = ((u16)y0 << 16) | (u16)x1;
		GFX_VERTEX16 = ul_currentDepth;
		
		//3. Bas-droite
		GFX_VERTEX16 = ((u16)y1 << 16) | (u16)x1;
		GFX_VERTEX16 = ul_currentDepth;
		
		//4. Bas-gauche
		GFX_VERTEX16 = ((u16)y1 << 16) | (u16)x0;
		GFX_VERTEX16 = ul_currentDepth;
		
	GFX_END = 0;

	//Incrémentation auto de la profondeur	
	ul_currentDepth += ul_autoDepth;
}

