#include "ulib.h"

inline int ulFindColorInPalette(UL_COLOR *palette, int count, UL_COLOR color)		{
   int i;
   for (i=1;i<count;i++)		{
      if ((palette[i] & 0x7fff) == (color & 0x7fff))
      	return i;
   }
   return -1;
}

//Supporte 16 bits (5551, 5550) seulement!
UL_IMAGE *ulConvertImageToPaletted(UL_IMAGE *imgOriginal, int newLocation, int newFormat)			{
   int palSize = 1 << ul_paletteSizes[newFormat];
   int width = imgOriginal->sizeX, height = imgOriginal->sizeY;
   UL_IMAGE *img;
   int i, j;
   u16 *palette, palCount;
   
   img = ulCreateImage(width, height, newLocation, newFormat, palSize);
   if (img)			{
      //D'abord: tout à zéro
      memset(img->texture, 0, (ul_pixelSizes[img->format] * img->sysSizeX * img->sysSizeY) >> 3);
      palette = (u16*)img->palette;
      
      //Première couleur: transparente
      palette[0] = 0;
      palCount = 1;
		
		//On parcourt toute l'image pour créer les index de la palette
      for (j=0;j<height;j++)		{
	      for (i=0;i<width;i++)			{
	         u16 pixel = *(u16*)ulGetImagePixelAddr(imgOriginal, i, j);
	         
	         //Pixel transparent?
	         if ((ul_colorKeyEnabled && (pixel & 0x7fff) == (ul_colorKeyValue & 0x7fff))
	         	|| (imgOriginal->format == UL_PF_5551 && !(pixel & 0x8000)))
	         	continue;
	         
				//Regarde si la couleur existe déjà et l'ajoute sinon
            int colorNb = ulFindColorInPalette(img->palette, palCount, pixel);
            if (colorNb < 0)			{
               if (palCount < palSize)			{
						palette[palCount] = pixel;
						colorNb = palCount++;
					}
					//Pas assez de couleurs, on pourrait essayer d'approcher au max mais le résultat serait assez mauvais parce que seules les couleurs des premiers pixels seraient disponibles.
	            else
	            	colorNb = 0;
          	}
          	
          	//Ecrit le pixel sur le buffer de destination
          	u8 *pxDest = (u8*)ulGetImagePixelAddr(img, i, j);
          	int imagePlanes = ul_pixelSizes[img->format];
			   int offset = i & (ul_pixelsPerByte[imagePlanes] - 1);
			   *pxDest |= colorNb << (offset * imagePlanes);
	      }
	   }
      ulDeleteImage(imgOriginal);
	}
   return img;
}

