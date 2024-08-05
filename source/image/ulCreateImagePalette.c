#include "ulib.h"

int ulCreateImagePalette(UL_IMAGE *img, int location, int palCount)
{
    int success = 1;

    // Create a palette if the image can have one
    if (palCount && ulImageIsPaletted(img) && img->palState == UL_STATE_NONE)
    {
        // The place where you put the palette and the image must be the same!
        switch (img->imgState)
        {
            case UL_STATE_NONE:
            default:
                break;

            case UL_STATE_RAM:
            case UL_STATE_RAM_BLOCK:
                location = UL_IN_RAM;
                break;

            case UL_STATE_VRAM:
                location = UL_IN_VRAM;
                break;
        }

        if (location == UL_IN_RAM)
        {
            // Chaque pixel fait 2 octets
            img->palette = malloc(2 * palCount);
            if (img->palette)
            {
                img->palCount = palCount;
                img->palState = UL_STATE_RAM_BLOCK;
            }
            else
            {
                success = 0;
            }
        }
        else if (location == UL_IN_VRAM)
        {
            // Directement en VRAM
            img->palCount = palCount;

            // Aligner la taille à 2
            if (img->palCount & 1)
                img->palCount++;

            img->paletteID = uluTexLoadPal(NULL, img->palCount, img->format);
            if (img->paletteID >= 0)
                img->palState = UL_STATE_VRAM;
            else
                success = 0;
        }
    }
    else
    {
        img->palette = NULL;
        img->palCount = 0;
    }
    return success;

/*
    if (ulImageIsPaletted(img) && !img->palette)
    {
        // Chaque pixel fait 2 octets - toujours 15 bits
        img->palette = malloc(2 * palCount);
        img->palCount = palCount;
        img->palState = UL_STATE_RAM_BLOCK;
    }
*/
}
