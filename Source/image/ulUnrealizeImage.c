#include "ulib.h"

void *ulReadTextureToMemory(int textureID, int sysSizeX, int sysSizeY, int type)			{
   void *block;
   int size;
   
   size = (sysSizeX * sysSizeY * ul_pixelSizes[type]) >> 3;
   block = malloc(size);
   if (block)			{
      u32 *texture = ulGetTextureAddress(textureID);
      
		// unlock texture memory
		ulChangeVramAllocation(ul_texVramBanks, UL_BANK_TYPE_LCD);
      swiCopy(texture, block , (size >> 2) | COPY_MODE_WORD);
		ulChangeVramAllocation(ul_texVramBanks, UL_BANK_TYPE_TEXTURE);
   }
	return block;   
}

void *ulReadPaletteToMemory(int paletteID, int palCount)			{
   void *block;
   int size;
   
   size = palCount * 2;
   block = malloc(size);
   if (block)			{
      u32 *pal = ulGetPaletteAddress(paletteID);
		// unlock palette memory
	 	ulChangeVramAllocation(ul_texPalVramBanks, UL_BANK_TYPE_LCD);
		swiCopy(pal, block , (size >> 2) | COPY_MODE_WORD);
	 	ulChangeVramAllocation(ul_texPalVramBanks, UL_BANK_TYPE_TEXPAL);
   }
	return block;   
}

//Copie une image en RAM pour qu'on puisse la modifier - ne doit pas être lockée
int ulUnrealizeImage(UL_IMAGE *img)		{
	int success = 1;
	
	if (!img->texture && img->imgState == UL_STATE_VRAM)			{
		int texID = img->textureID;
		void *memory;
		
		//Read back the texture
		memory = ulReadTextureToMemory(texID, img->sysSizeX, img->sysSizeY, img->format);
		if (memory)		{
		   img->texture = memory;
		   img->imgState = UL_STATE_RAM_BLOCK;
		   //Deletes the texture from VRAM
			if (texID != -1)
				ulFreeTextures(1, &texID);
		   img->textureID = -1;
		}
		else
			success = 0;
	}
	
	//Do not continue unless the first read has passed
	if (success)			{
		if (!img->palette && img->palState == UL_STATE_VRAM)			{
			void *memory;
			//Read back the palette
			memory = ulReadPaletteToMemory(img->paletteID, img->palCount);
			if (memory)			{
			   img->palette = memory;
			   img->palState = UL_STATE_RAM_BLOCK;
				//Unload the palette, useless now
				if (img->paletteID != -1)
					uluTexUnloadPal(img->paletteID);
				img->paletteID = -1;
			}
			else
				success = 0;
		}
	}
	return success;
}

