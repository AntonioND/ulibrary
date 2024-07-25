#include "ulib.h"

//Crée une nouvelle image depuis une texture et une palette.
//This function has been removed because it doesn't respect the location model.
/*UL_IMAGE *ulCreateImageFromTexture(const void *texture, int width, int height, int location, int format, void *palette, int palCount)		{
	UL_IMAGE *img;
	int textureID;
	
	//Création de l'image
	img = malloc(sizeof(UL_IMAGE));
	if (img)			{
		memset(img, 0, sizeof(UL_IMAGE));
		ulGenTextures(1, &textureID);
		ulBindTexture(0, textureID);
		img->sysSizeX = 1 << ulGetPowerOf2Count(width);
		img->sysSizeY = 1 << ulGetPowerOf2Count(height);
		if (ulTexImage2D(0, 0, format, ulGetPowerOf2Count(width) - 3, ulGetPowerOf2Count(height) - 3, 0, GL_TEXTURE_COLOR0_TRANSPARENT | TEXGEN_TEXCOORD, (u8*)texture))			{
			//Système
			img->textureID = textureID;
			img->texture = (void*)texture;
			img->palette = palette;
			img->palCount = palCount;
			//En RAM mais pas à libérer!
			if (palette)
				img->palState = UL_STATE_RAM;			
			img->format = format;
			img->sizeX = width;
			img->sizeY = height;
			img->imgState = UL_STATE_VRAM;
			
			//Initialise les propriétés de l'image
			ulResetImageProperties(img);
		}
		else
			free(img);
	}
	return img;
}*/

