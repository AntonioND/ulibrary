#include "ulib.h"

//Retourne la valeur d'un pixel sur une image - lent - PAS TESTÉ
int ulGetImagePixel(UL_IMAGE *img, int x, int y)			{
   void *pPixel = ulGetImageLineAddr(img, y);
   
   switch (img->format)			{
		case UL_PF_5551:
		case UL_PF_5550:
			return ((u16*)pPixel)[x];

		case UL_PF_PAL8:
		case UL_PF_PAL5_A3:
		case UL_PF_PAL3_A5:
			return ((u8*)pPixel)[x];

		case UL_PF_PAL4:
			return ((u8*)pPixel)[x >> 1] & (15 << ((x & 1) << 2));
		
		case UL_PF_PAL2:
			return ((u8*)pPixel)[x >> 2] & (3 << ((x & 3) << 1));
	}
	
	return -1;
}

