#include "ulib.h"

//Dessine un rectangle dégradé à quatre coins
void ulDrawGradientRect(s16 x0, s16 y0, s16 x1, s16 y1, UL_COLOR color1, UL_COLOR color2, UL_COLOR color3, UL_COLOR color4)			{
	//Commence le dessin
	GFX_BEGIN = GL_QUADS;
		GFX_TEX_FORMAT = 0;

		//1. Haut-gauche
		GFX_COLOR = color1;
		GFX_VERTEX16 = ((u16)y0 << 16) | (u16)x0;
		GFX_VERTEX16 = ul_currentDepth;
		
		//2. Haut-droite
		GFX_COLOR = color2;
		GFX_VERTEX16 = ((u16)y0 << 16) | (u16)x1;
		GFX_VERTEX16 = ul_currentDepth;
		
		//3. Bas-droite
		GFX_COLOR = color4;
		GFX_VERTEX16 = ((u16)y1 << 16) | (u16)x1;
		GFX_VERTEX16 = ul_currentDepth;
		
		//4. Bas-gauche
		GFX_COLOR = color3;
		GFX_VERTEX16 = ((u16)y1 << 16) | (u16)x0;
		GFX_VERTEX16 = ul_currentDepth;
		
	GFX_END = 0;

	//Incrémentation auto de la profondeur	
	ul_currentDepth += ul_autoDepth;
}

