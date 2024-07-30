#include "ulib.h"

//Permet d'accéder à la texture d'une image
//ATTENTION: PAS SÛR POUR LA PALETTE
void *ulLockImage(UL_IMAGE *img, UL_LOCK_REASON lockReason)			{
   void *result = NULL;
   if (lockReason & UL_LOCK_PIXELS)			{
      if (img->imgState == UL_STATE_VRAM)		{
         //On locke la VRAM
			ulChangeVramAllocation(ul_texVramBanks, UL_BANK_TYPE_LCD);
			img->texture = ulGetTextureAddress(img->textureID);
		}
		result = img->texture;
	}
	if (lockReason & UL_LOCK_PALETTE)		{
      if (img->palState == UL_STATE_VRAM)		{
		 	ulChangeVramAllocation(ul_texPalVramBanks, UL_BANK_TYPE_LCD);
			img->palette = ulGetPaletteAddress(img->paletteID);
		}
		result = img->palette;
	}
	return result;
}

void ulUnlockImage(UL_IMAGE *img, UL_LOCK_REASON lockReason)		{
   if (lockReason & UL_LOCK_PIXELS)		{
		ulChangeVramAllocation(ul_texVramBanks, UL_BANK_TYPE_TEXTURE);
	 	//Not accessable anymore
		if (img->imgState == UL_STATE_VRAM)
			img->texture = NULL;
	}
	if (lockReason & UL_LOCK_PALETTE)			{
	 	ulChangeVramAllocation(ul_texPalVramBanks, UL_BANK_TYPE_TEXPAL);
	 	//Not accessable anymore
		if (img->palState == UL_STATE_VRAM)
			img->palette = NULL;
	}
}

