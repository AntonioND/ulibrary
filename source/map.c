#include "ulib.h"

/*
	MAP
	
	A tester: support des palettes multiples!
*/

//tileX, tileY, img->sizeX doivent être des puissances de deux!
void ulDrawMap(UL_MAP *m)
{
	s16 x, y, v, ttX=0, i, sX, sY, tX=0, tY=0, mX, mY, dX, bY, dsX, dsY, flags;
	u16 *map = (u16*)m->map;
	int bHasPalette = (m->img->paletteID != -1), nDecal = (4 - (m->img->format == GL_RGB4));
	int palSize = ul_paletteSizes[m->img->format];

	ulSetTexture(m->img);
	GFX_COLOR = m->img->tint1;

	//Calcule le drawSize s'il n'est pas fourni
	if (m->drawSizeX < 0 || m->drawSizeY < 0)			{
		m->drawSizeX = UL_SCREEN_WIDTH / m->tileX + 1;
		if (UL_SCREEN_WIDTH % m->tileX)
			m->drawSizeX++;
		m->drawSizeY = UL_SCREEN_HEIGHT / m->tileY + 1;
		if (UL_SCREEN_HEIGHT % m->tileY)
			m->drawSizeY++;
	}

	dsX = m->drawSizeX, dsY = m->drawSizeY;

	//Trouve les puissances de deux optimisées
	for (i=3;i<=9;i++)			{
		if (ttX == 0 && m->img->sysSizeX <= 1 << i)
			ttX = i;
		if (tX == 0 && m->tileX <= 1 << i)
			tX = i;
		if (tY == 0 && m->tileY <= 1 << i)
			tY = i;
	}

	sX = m->scrollX & ((1 << tX) - 1);
	sY = m->scrollY & ((1 << tY) - 1);

	//Hum... un modulo par map à la limite ça va
	dX = (m->scrollX >> tX) % m->mapSizeX;
	mY = (m->scrollY >> tY) % m->mapSizeY;

	//Pour parer au modulo négatif
	if (dX < 0)		dX += m->mapSizeX;
	if (mY < 0)		mY += m->mapSizeY;

	GFX_BEGIN = GL_QUADS;
	
	switch (m->format)			{
	   case UL_MF_U16:
/*		   ulVertexUVXY(0, 0, 0xffff, 0);
		   ulVertexUVXY(0, 16, 0xffff, 16);
		   ulVertexUVXY(16, 16, 15, 16);
		   ulVertexUVXY(16, 0, 15, 0);*/
			for (y=0;y<dsY;y++)			{
			   //Multiplication => ok
				bY = m->mapSizeX * mY;
				mX = dX;
				for (x=0;x<dsX;x++)			{
					v = map[bY + mX];
				
					//La première tile est toujours transparente!
					if (v)				{
					   //In fact these numbers are signed, but they have to be wrapped as unsigned when negative
					   u16 u0, v0, x0, y0, x1, y1, u1, v1;
					   
					   u0 = ((v << tX) & ((1 << ttX) - 1));
					   v0 = ((v << tX) >> ttX) << tY;
//					   x0 = (x << tX) - sX;
//					   y0 = (y << tY) - sY;
					   x1 = (x << tX) - (sX - m->tileX);
					   y1 = (y << tY) - (sY - m->tileY);
					   x0 = x1 - m->tileX;
					   y0 = y1 - m->tileY;
					   				   
					   u1 = u0 + m->tileX;
					   v1 = v0 + m->tileY;
					   
					   ulVertexUVXY(u0, v0, x0, y0);
					   ulVertexUVXY(u0, v1, x0, y1);
					   ulVertexUVXY(u1, v1, x1, y1);
					   ulVertexUVXY(u1, v0, x1, y0);
					}
					mX++;
					if (mX >= m->mapSizeX)
						mX -= m->mapSizeX;
				}
				mY++;
				if (mY >= m->mapSizeY)
					mY -= m->mapSizeY;
			}
			break;

	   case UL_MF_U16_GBA:
			for (y=0;y<dsY;y++)			{
			   //Multiplication => ok
				bY = m->mapSizeX * mY;
				mX = dX;
				for (x=0;x<dsX;x++)			{
					v = map[bY + mX];
					flags = v & ~0x3ff;
					v &= 0x3ff;
				
					//La première tile est toujours transparente!
					if (v)				{
					   s16 u0, v0, x0, y0, u1, v1;
					   
					   u0 = ((v << tX) & ((1 << ttX) - 1));
					   v0 = ((v << tX) >> ttX) << tY;
					   x0 = (x << tX) - sX;
					   y0 = (y<<tY)-sY;
					   
					   u1 = u0 + m->tileX;
					   v1 = v0 + m->tileY;
					   
					   //Mirroir horizontal
					   if (flags & 0x400)			{
					      int exchg = u0;
					   	u0 = u1;
					   	u1 = exchg;
						}
		
					   //Mirroir vertical
					   if (flags & 0x800)			{
					      int exchg = v0;
					   	v0 = v1;
					   	v1 = exchg;
						}
						
						//NON-TESTÉ! Support des palettes multiples
						if (bHasPalette)
						   GFX_PAL_FORMAT = ((u32)m->img->paletteID + ((flags >> 12) << palSize)) >> nDecal;
					   
					   ulVertexUVXY(u0, v0, x0, y0);
					   ulVertexUVXY(u0, v1, x0, y0 + m->tileY);
					   ulVertexUVXY(u1, v1, x0 + m->tileX, y0 + m->tileY);
					   ulVertexUVXY(u1, v0, x0 + m->tileX, y0);
					}
					mX++;
					if (mX >= m->mapSizeX)
						mX -= m->mapSizeX;
				}
				mY++;
				if (mY >= m->mapSizeY)
					mY -= m->mapSizeY;
			}
			break;
	}

	GFX_END = 0;
	ul_currentDepth += ul_autoDepth;
}

UL_MAP *ulCreateMap(UL_IMAGE *img, void *map_data, int tileX, int tileY, int mapSizeX, int mapSizeY, int map_format)
{
	UL_MAP *m;
	m = (UL_MAP*)malloc(sizeof(UL_MAP));
	if (!m)
		return NULL;
/*	if (map_format != UL_MF_U16_MP)		{
//		ulFatalError("Invalid map format");
		free(m);
		return NULL;
	}*/
	m->format = map_format;
	m->img = img;
	m->map = map_data;
	m->tileX = tileX;
	m->tileY = tileY;
	m->mapSizeX = mapSizeX;
	m->mapSizeY = mapSizeY;
	m->scrollX = m->scrollY = 0;
	m->drawSizeX = -1;
	m->drawSizeY = -1;
	return m;
}

void ulDeleteMap(UL_MAP *map)		{
   free(map);
}


