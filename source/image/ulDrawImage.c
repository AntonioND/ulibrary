#include "ulib.h"

//Dessine une image
void ulDrawImage(UL_IMAGE *img)
{
	ulSetTexture(img);

	//Gère la rotation
	if (img->angle || img->centerX || img->centerY)			{
		/*
			Méthode #1
			
			Utilisation des matrices, il faudrait tester pour voir si c'est plus rapide
		*/

		//Matrice
		glPushMatrix();
//		glLoadIdentity();
		
		int cX, cY;
		
		cX = (-img->centerX * img->stretchX) / ulAbs(img->offsetX1 - img->offsetX0);
		cY = (-img->centerY * img->stretchY) / ulAbs(img->offsetY1 - img->offsetY0);
		
		glTranslate3f32(img->x, img->y, 0);
		glRotateZi(img->angle);
//		glRotatef(img->angle, 0, 0, 1.0);
		
		//Commence le dessin
		ulVertexBegin(GL_QUADS);
		
			//1. Haut-gauche
			GFX_COLOR = img->tint1;
		   ulVertexUVXY(img->offsetX0, img->offsetY0, cX, cY);
		   
		   //2. Bas-gauche
			GFX_COLOR = img->tint3;
		   ulVertexUVXY(img->offsetX0, img->offsetY1, cX, cY + img->stretchY);

			//3. Bas-droite
			GFX_COLOR = img->tint4;
		   ulVertexUVXY(img->offsetX1, img->offsetY1, cX + img->stretchX, cY + img->stretchY);
		   
		   //4. Haut-droite
			GFX_COLOR = img->tint2;
		   ulVertexUVXY(img->offsetX1, img->offsetY0, cX + img->stretchX, cY);
			
		ulVertexEnd();
		
		glPopMatrix(1);
		
		/*
			Méthode #2
			
			Utilisation de sin/cos, ancienne méthode
		*/
		
/*		int cX, cY, tmpX, tmpY, x, y;
		cX = ((-img->centerX * img->stretchX) << 8) / (img->offsetX1 - img->offsetX0);
		cY = ((-img->centerY * img->stretchY) << 8) / (img->offsetY1 - img->offsetY0);

		tmpX = cX + (img->stretchX << 8);
		tmpY = cY + (img->stretchY << 8);
		
		//Rendu en rotation
		GFX_BEGIN = GL_QUADS;
	
			//1. Haut-gauche
			GFX_COLOR = img->tint1;
			GFX_TEX_COORD = TEXTURE_PACK(inttot16(img->offsetX0), inttot16(img->offsetY0));
			x = ((ulCos(img->angle, cX) - ulSin(img->angle, cY)) >> 8) + img->x;
			y = ((ulSin(img->angle, cX) + ulCos(img->angle, cY)) >> 8) + img->y;
			GFX_VERTEX16 = (y << 16) | (x & 0xffff);
			GFX_VERTEX16 = ul_currentDepth;
						
			//2. Haut-droite
			GFX_COLOR = img->tint2;
			GFX_TEX_COORD = TEXTURE_PACK(inttot16(img->offsetX1), inttot16(img->offsetY0));
			x = ((ulCos(img->angle, tmpX) - ulSin(img->angle, cY)) >> 8) + img->x;
			y = ((ulSin(img->angle, tmpX) + ulCos(img->angle, cY)) >> 8) + img->y;
			GFX_VERTEX16 = (y << 16) | (x & 0xffff);
			GFX_VERTEX16 = ul_currentDepth;
			
			//4. Bas-droite
			GFX_COLOR = img->tint4;
			GFX_TEX_COORD = TEXTURE_PACK(inttot16(img->offsetX1), inttot16(img->offsetY1));
			x = ((ulCos(img->angle, tmpX) - ulSin(img->angle, tmpY)) >> 8) + img->x;
			y = ((ulSin(img->angle, tmpX) + ulCos(img->angle, tmpY)) >> 8) + img->y;
			GFX_VERTEX16 = (y << 16) | (x & 0xffff);
			GFX_VERTEX16 = ul_currentDepth;
			
			//3. Bas-gauche
			GFX_COLOR = img->tint3;
			GFX_TEX_COORD = TEXTURE_PACK(inttot16(img->offsetX0), inttot16(img->offsetY1));
			x = ((ulCos(img->angle, cX) - ulSin(img->angle, tmpY)) >> 8) + img->x;
			y = ((ulSin(img->angle, cX) + ulCos(img->angle, tmpY)) >> 8) + img->y;
			GFX_VERTEX16 = (y << 16) | (x & 0xffff);
			GFX_VERTEX16 = ul_currentDepth;
			
		GFX_END = 0;*/
	}
	else		{
	
		//Commence le dessin
		GFX_BEGIN = GL_QUADS;
	
			//ATTENTION: PEUT ÊTRE ENLEVER LES & 0xffff qui ne servent pas vraiment à grand chose...
			
			//1. Haut-gauche
			GFX_COLOR = img->tint1;
		   ulVertexUVXY(img->offsetX0, img->offsetY0, img->x, img->y);

		   //2. Bas-gauche
			GFX_COLOR = img->tint3;
		   ulVertexUVXY(img->offsetX0, img->offsetY1, img->x, img->y + img->stretchY);

			//3. Bas-droite
			GFX_COLOR = img->tint4;
		   ulVertexUVXY(img->offsetX1, img->offsetY1, img->x + img->stretchX, img->y + img->stretchY);
		   
		   //4. Haut-droite
			GFX_COLOR = img->tint2;
		   ulVertexUVXY(img->offsetX1, img->offsetY0, img->x + img->stretchX, img->y);
						
		GFX_END = 0;
	}

	//Incrémentation auto de la profondeur	
	ul_currentDepth += ul_autoDepth;
	return;
}

