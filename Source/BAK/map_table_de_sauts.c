#include "lib2d.h"

/*
	MAP
	
	A tester: support des palettes multiples!
*/

void ulDrawMap_u16(UL_MAP *m, int dsX, int dsY, int mY, int dX, int tX, int tY, int sX, int sY, int ttX)			{
   int x, y, v, bY, mX;
	u16 *map = (u16*)m->map;
   
	for (y=0;y<dsY;y++)			{
	   //Multiplication => ok
		bY = m->mapSizeX * mY;
		mX = dX;
		for (x=0;x<dsX;x++)			{
			v = map[bY + mX];

			//La première tile est toujours transparente!
			if (v)				{
			   int u0, v0, x0, y0, u1, v1;
			   
			   u0 = ((v << tX) & ((1 << ttX) - 1));
			   v0 = ((v << tX) >> ttX) << tY;
			   x0 = (x << tX) - sX;
			   y0 = (y<<tY) - sY;
			   
			   u1 = u0 + m->tileX;
			   v1 = v0 + m->tileY;
			   
			   ulAdd2DVertex(u0, v0, x0, y0);
			   ulAdd2DVertex(u0, v1, x0, y0 + m->tileY);
			   ulAdd2DVertex(u1, v1, x0 + m->tileX, y0 + m->tileY);
			   ulAdd2DVertex(u1, v0, x0 + m->tileX, y0);
			}
			mX++;
			if (mX >= m->mapSizeX)
				mX -= m->mapSizeX;
		}
		mY++;
		if (mY >= m->mapSizeY)
			mY -= m->mapSizeY;
	}
}

void ulDrawMap_u16mp(UL_MAP *m, int dsX, int dsY, int mY, int dX, int tX, int tY, int sX, int sY, int ttX)			{
   int x, y, v, flags, bY, mX;
	u16 *map = (u16*)m->map;
	int bHasPalette = (m->img->paletteID != -1), nDecal = (4 - (m->img->format == GL_RGB4));
	//Taille des palettes (2^n)
	const u8 palSizes[]=		{
		0,										//Non utilisé
		5, 									//UL_PF_PAL5_A3: 32 couleurs
		2, 									//UL_PF_PAL2: 4 couleurs
		4, 									//UL_PF_PAL4: 16 couleurs
		8, 									//UL_PF_PAL8: 256 couleurs
		0, 									//UL_PF_COMPRESSED
		3, 									//UL_PF_PAL3_A5: 8 couleurs
		0, 									//UL_PF_5551
		0, 									//UL_PF_5550
	};
	int palSize = palSizes[m->img->format];
   
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
			   int u0, v0, x0, y0, u1, v1;
			   
			   u0 = ((v << tX) & ((1 << ttX) - 1));
			   v0 = ((v << tX) >> ttX) << tY;
			   x0 = (x << tX) - sX;
			   y0 = (y<<tY) - sY;
			   
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
			   
			   ulAdd2DVertex(u0, v0, x0, y0);
			   ulAdd2DVertex(u0, v1, x0, y0 + m->tileY);
			   ulAdd2DVertex(u1, v1, x0 + m->tileX, y0 + m->tileY);
			   ulAdd2DVertex(u1, v0, x0 + m->tileX, y0);
			}
			mX++;
			if (mX >= m->mapSizeX)
				mX -= m->mapSizeX;
		}
		mY++;
		if (mY >= m->mapSizeY)
			mY -= m->mapSizeY;
	}
}

void *ul_mapFunctions[]=		{
   ulDrawMap_u16,
   ulDrawMap_u16mp,
};

//tileX, tileY, img->sizeX doivent être des puissances de deux!
void ulDrawMap(UL_MAP *m)
{
	int ttX=0, i, sX, sY, tX=0, tY=0, mY, dX, dsX, dsY;
	void (*fct)(UL_MAP *m, int dsX, int dsY, int mY, int dX, int tX, int tY, int sX, int sY, int ttX) = ul_mapFunctions[m->format];

	ulSetTexture(m->img);

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

	//Fait appel à la fonction correspondant au type de map
	fct(m, dsX, dsY, mY, dX, tX, tY, sX, sY, ttX);

	GFX_END = 0;
	ul_currentDepth += ul_autoDepth;
}

UL_MAP *ulCreateMap(UL_IMAGE *img, void *map_data, int tileX, int tileY, int mapSizeX, int mapSizeY, int map_format)
{
	UL_MAP *m;
	m = (UL_MAP*)malloc(sizeof(UL_MAP));
	if (!m)
		return NULL;
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

