#include "ulib.h"
#include "jpeg/gba-jpeg.h"
#include "jpeg/gba-jpeg-decode.h"

UL_IMAGE *ulLoadImageJPG(VIRTUAL_FILE *f, int location, int pixelFormat)
{
	UL_IMAGE *img = NULL;
	const unsigned char *input, *input_free;
	
   //Format 16 bits obligatoire pour le JPG!
   if (ul_pixelWidth[pixelFormat] != 16)
   	return NULL;
   
   input = (const unsigned char*)ulReadEntireFileToMemory(f, NULL);
   input_free = input;
   
   if (input)			{
      int width, height;
		JPEG_Decoder decoder;
		
		JPEG_Decoder_ReadHeaders(&decoder, &input);
		width = decoder.frame.width;
		height = decoder.frame.height;
		
		//Crée l'image dans laquelle on mettra notre bitmap
		img = ulCreateImage(width, height, UL_IN_RAM, pixelFormat, 0);

		if (img)			{
		   if (!JPEG_Decoder_ReadImage (&decoder, &input, img->texture, img->sysSizeX, img->sysSizeY))			{
		   	ulDeleteImage(img);
		   	img = NULL;
			}
		}
		
	   free((void*)input_free);

		if (location == UL_IN_VRAM)			{
			if (!ulRealizeImage(img))			{
			   ulDeleteImage(img);
				return NULL;
			}
		}
	}
	return img;
}

