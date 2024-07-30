#include "ulib.h"

void ulMirrorImageH(UL_IMAGE *img, int mirrorState)		{
   if ((mirrorState && img->offsetX1 >= img->offsetX0)
		|| (!mirrorState && img->offsetX1 <= img->offsetX0))			{
		//Exchange both coordinates to mirror the image
		int tmpOffset = img->offsetX0;
		img->offsetX0 = img->offsetX1;
		img->offsetX1 = tmpOffset;
	}
}

void ulMirrorImageV(UL_IMAGE *img, int mirrorState)		{
   if ((mirrorState && img->offsetY1 >= img->offsetY0)
		|| (!mirrorState && img->offsetY1 <= img->offsetY0))			{
		//Exchange both coordinates to mirror the image
		int tmpOffset = img->offsetY0;
		img->offsetY0 = img->offsetY1;
		img->offsetY1 = tmpOffset;
	}
}


