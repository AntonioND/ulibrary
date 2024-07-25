#include "ulib.h"

//Dessine un pixel sur une image - lent
void ulSetImagePixel(UL_IMAGE *img, int x, int y, int pixelValue)			{
   void *pPixel = ulGetImageLineAddr(img, y);
   
   switch (img->format)			{
		case UL_PF_5551:
		case UL_PF_5550:
			((u16*)pPixel)[x] = pixelValue;
			break;

		case UL_PF_PAL8:
		case UL_PF_PAL5_A3:
		case UL_PF_PAL3_A5:
			((u8*)pPixel)[x] = pixelValue;
			break;

		case UL_PF_PAL4:
			((u8*)pPixel)[x >> 1] &= ~(15 << ((x & 1) << 2));
			((u8*)pPixel)[x >> 1] |= (pixelValue & 15) << ((x & 1) << 2);
			break;
		
		case UL_PF_PAL2:
			((u8*)pPixel)[x >> 2] &= ~(3 << ((x & 3) << 1));
			((u8*)pPixel)[x >> 2] |= (pixelValue & 3) << ((x & 3) << 1);
		   break;
	}
}

