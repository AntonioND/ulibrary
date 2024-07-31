#include "ulib.h"
#include "gif/gif_lib.h"

// Note: la palette temporaire ici est 16 bits parce qu'on est sur DS mais ce
// serait facile de l'adapter au 32 bits, regarder GAMMA et le remplissage de
// cette palette (nommée Palette dans ulLoadImageGif) Le swap de palette par
// rapport à la couleur transparente n'est utile que sur DS où seule la première
// couleur d'une palette est (et doit être) transparente!  Sur DS, à cause du
// fait que le mode paletté requiert que la première couleur soit transparente,
// tous les gifs auront leur première couleur comme transparente! Par contre en
// mode 16 bits (5551) le fonctionnement est normal.

u16 *temppalette; // Utilisé pour stocker la palette des gifs...

const short InterlacedOffset[] = { 0, 4, 2, 1 }; // The way Interlaced image should.
const short InterlacedJumps[] = { 8, 8, 4, 2 };  // be read - offsets and jumps...

int m;

GifPixelType LineBuf[2048]; // Buffer temporaire

int fnGifReadFunc(GifFileType* GifFile, GifByteType* buf, int count)
{
/*
    char* ptr = (char*)GifFile->UserData;
    memcpy(buf, ptr, count);
    GifFile->UserData = ptr + count;
*/
    VirtualFileRead(buf, 1, count, (VIRTUAL_FILE *)GifFile->UserData);

    return count;
}

void fnCopyLine(void *dst, void *src, int count, int pixelFormat,
                int transparentColor)
{
    int x;
    u8 *p_dest1 = (u8 *)dst;
    u16 *p_dest2 = (u16 *)dst;
    u8 *p_src = (u8 *)src;
    u8 r = 0, g = 0, b = 0, a = 0, pixel_value;

    for (x = 0; x < count; x++)
    {
        // Prochain pixel
        pixel_value = p_src[x];
        if (pixel_value == transparentColor)
            pixel_value = 0;
        else if (pixel_value < transparentColor)
            pixel_value++;

        if (temppalette)
        {
            r = temppalette[pixel_value] & 0x1f;
            g = (temppalette[pixel_value] >> 5) & 0x1f;
            b = (temppalette[pixel_value] >> 10) & 0x1f;
            a = temppalette[pixel_value] >> 15;
        }

        if (pixelFormat == UL_PF_5551)
        {
            p_dest2[x] = RGB15(r, g, b) | (a << 15);
        }
        else if (pixelFormat == UL_PF_5550)
        {
            p_dest2[x] = RGB15(r, g, b);
        }
        // Tous les 8 bits
        else if (ul_pixelSizes[pixelFormat] == 8)
        {
            p_dest1[x] = pixel_value;
        }
        else if (pixelFormat == UL_PF_PAL4)
        {
            p_dest1[x >> 1] &= ~(15 << ((x & 1) << 2));
            p_dest1[x >> 1] |= (pixel_value & 15) << ((x & 1) << 2);
        }
        else if (pixelFormat == UL_PF_PAL2)
        {
            p_dest1[x >> 2] &= ~(3 << ((x & 3) << 1));
            p_dest1[x >> 2] |= (pixel_value & 3) << ((x & 3) << 1);
        }
    }
}

int DGifGetLineByte(GifFileType *GifFile, GifPixelType *Line, int LineLen,
                    int pixelFormat, int transparentColor)
{
    // Nouvelle ligne
    int result = DGifGetLine(GifFile, LineBuf, LineLen);
    // Ecrit dans le buffer
    fnCopyLine(Line, LineBuf, LineLen, pixelFormat, transparentColor);
    return result;
}

#define GAMMA(x)    ((x) >> 3)

/*
#ifdef _NO_FILEIO
#define PrintGifError()
#endif
*/

//#define EXIT_FAILURE 1

// Gerer les 16 bits!!
//
// ulCreateImage()
UL_IMAGE *ulLoadImageGIF(VIRTUAL_FILE *f, int location, int pixelFormat)
{
    UL_IMAGE *img = NULL;

    int i, j, Row, Col, Width, Height, ExtCode, Count __attribute__((unused));
    u16 *Palette = NULL;
    GifRecordType RecordType;
    GifByteType *Extension;
    GifFileType *GifFile;
    ColorMapObject *ColorMap;
    int transparentColor = -1;

    GifFile = DGifOpen(f, fnGifReadFunc);
    if (!GifFile)
        return NULL;

    if (ul_pixelSizes[pixelFormat] > 8)
    {
        temppalette = (u16 *)malloc(512); // Ecran temporaire
        Palette = temppalette;
    }
    else
    {
        // En mode true color, on utilise une palette temporaire...
        temppalette = NULL;
    }

    // Scan the content of the GIF file and load the image(s) in:
    do { // Je vire les messages d'erreur pour gagner de la place
        DGifGetRecordType(GifFile, &RecordType);

        switch (RecordType)
        {
            case IMAGE_DESC_RECORD_TYPE:
                DGifGetImageDesc(GifFile);
                /*
                if (DGifGetImageDesc(GifFile) == GIF_ERROR)
                {
                    PrintGifError();
                    return EXIT_FAILURE;
                }
                */
                //Row = GifFile->Image.Top; // Image Position relative to Screen.
                //Col = GifFile->Image.Left;

                // Je n'en tiens pas compte car il faudrait aggrandir l'image,
                // c'est peut être utile pour les gifs animés remarque
                Row = Col = 0;
                Width = GifFile->Image.Width;
                Height = GifFile->Image.Height;

                // Update Color map
                ColorMap = (GifFile->Image.ColorMap ? GifFile->Image.ColorMap: GifFile->SColorMap);

                // Crée l'image dans laquelle on mettra nos données.

                // Faire attention de ne pas créer trop de couleurs, mais en
                // réserver une pour le décalage si jamais aucune couleur
                // transparente n'a été trouvée
                img = ulCreateImage(Width, Height, UL_IN_RAM, pixelFormat,
                                    ulMin(ColorMap->ColorCount + 1,
                                    1 << ul_paletteSizes[pixelFormat]));

                if (!img)
                    goto failed;

                if (img->palette)
                {
                    Palette = img->palette;
                    ColorMap->ColorCount = ulMin(ColorMap->ColorCount, img->palCount);
                }

                // Pas de couleur transparente trouvée mais une palette dispo =>
                // utilise la couleur par défaut (color key)
                if (img->palette && transparentColor == -1 && ul_colorKeyEnabled)
                {
                    for (i = 0; i < ColorMap->ColorCount; i++)
                    {
                        GifColorType* pColor = &ColorMap->Colors[i];
                        if ((pColor->Red >> 3) == (ul_colorKeyValue & 0x1f) &&
                            (pColor->Green >> 3) == ((ul_colorKeyValue>>5) & 0x1f) &&
                            (pColor->Blue >> 3) == ((ul_colorKeyValue>>10) & 0x1f))
                        {
                            transparentColor = i;
                            break;
                        }
                    }
                }

                // Bon ben ici si on a toujours rien trouvé, la première couleur
                // sera transparente sur DS en mode paletté, aucune sinon, on
                // doit donc faire en sorte que la première couleur NE SOIT PAS
                // utilisée.
                //
                // Cela devrait être suffisant: cette couleur n'existe pas, le
                // moteur cherchera à l'utiliser et incrémentera tout d'un cran
                // pour que ça fonctionne ^^
                if (img->palette && transparentColor == -1 && !ul_firstPaletteColorOpaque)
                {
                    transparentColor = ColorMap->ColorCount;
                    Palette[0] = 0;
                    for (i = 0; i < ColorMap->ColorCount; i++)
                    {
                        GifColorType* pColor = &ColorMap->Colors[i];
                        // Vérifie qu'on ne déborde pas
                        if (i + 1 < img->palCount)
                        {
                            Palette[i + 1] = RGB15(GAMMA(pColor->Red),
                                                   GAMMA(pColor->Green),
                                                   GAMMA(pColor->Blue)) | 0x8000;
                        }
                    }
                }
                else
                {
                    // Tenons compte de la couleur transparente
                    i = ColorMap->ColorCount;
                    j = ColorMap->ColorCount;
                    while (--i >= 0)  {
                        GifColorType* pColor = &ColorMap->Colors[i];
                        if (i == transparentColor)
                        {
                            Palette[0] = RGB15(GAMMA(pColor->Red),
                                               GAMMA(pColor->Green),
                                               GAMMA(pColor->Blue));
                        }
                        else
                        {
                            // Cette couleur est affichée (0x8000 = alpha à 1)
                            Palette[--j] = RGB15(GAMMA(pColor->Red),
                                                 GAMMA(pColor->Green),
                                                 GAMMA(pColor->Blue)) | 0x8000;
                        }
                    }
                }

                /*
                if (GifFile->Image.Left + GifFile->Image.Width > GifFile->SWidth ||
                    GifFile->Image.Top + GifFile->Image.Height > GifFile->SHeight)
                {
                    return EXIT_FAILURE;
                }
                */

                if (GifFile->Image.Interlace)
                {
                    // Need to perform 4 passes on the images:
                    for (Count = i = 0; i < 4; i++)
                    {
                        for (j = Row + InterlacedOffset[i]; j < Row + Height; j += InterlacedJumps[i])
                        {
                            DGifGetLineByte(GifFile,
                                            (GifPixelType*)ulGetImagePixelAddr(img, Col, j),
                                            Width, pixelFormat, transparentColor);
                            /*
                            if (DGifGetLineByte(GifFile, &ScreenBuff[j][Col], Width) == GIF_ERROR)
                            {
                                PrintGifError();
                                return EXIT_FAILURE;
                            }
                            */
                        }
                    }
                }
                else
                {
                    for (i = 0; i < Height; i++)
                    {
                        DGifGetLineByte(GifFile, (GifPixelType*)ulGetImagePixelAddr(img, Col, Row), Width, pixelFormat, transparentColor);
                        Row++;
                        /*
                        if (DGifGetLineByte(GifFile, &ScreenBuff[Row++][Col], Width) == GIF_ERROR)
                        {
                            PrintGifError();
                            return EXIT_FAILURE;
                        }
                        */
                    }
                }
                break;

            case EXTENSION_RECORD_TYPE:
                // Skip any extension blocks in file:
                DGifGetExtension(GifFile, &ExtCode, &Extension);

                while (Extension != NULL)
                {
                    // Couleur transparente
                    if (ExtCode == 249)
                    {
                       if (Extension[1] & 1)
                          transparentColor = Extension[4];
                    }
                    DGifGetExtensionNext(GifFile, &Extension);
                }
                break;

            case TERMINATE_RECORD_TYPE:
                break;
            default: // Should be traps by DGifGetRecordType.
                break;
        }
    } while (RecordType != TERMINATE_RECORD_TYPE);

    if (ul_pixelSizes[pixelFormat] > 8 && temppalette)
        free(temppalette); // Libère la mémoire allouée pour la palette fixe

    if (location == UL_IN_VRAM)
    {
        if (!ulRealizeImage(img))
        {
            ulDeleteImage(img);
            return NULL;
        }
    }

failed:
    // Close file when done
    DGifCloseFile(GifFile);

    return img;
}

/*
#include "jpeg/gba-jpeg.h"
#include "jpeg/gba-jpeg-decode.h"

//Par blocs de 16 ko
#define BLOCK_SIZE (16 << 10)

//Lit un fichier entier vers la mémoire
void *ulReadEntireFileToMemory(VIRTUAL_FILE *f)
{
    void *block = NULL;
    int add = 0;
    int size = 0, readSize;

    do
    {
        size += BLOCK_SIZE;
        if (block)
            block = realloc(block, size);
        else
           block = malloc(size);

        // L'allocation a échoué?
        if (!block)
            return NULL;

        readSize = VirtualFileRead((char*)block + add, 1, BLOCK_SIZE, f);
        add += BLOCK_SIZE;
    } while (readSize >= BLOCK_SIZE);

    return block;
}

UL_IMAGE *ulLoadImageJPG(VIRTUAL_FILE *f, int flags, int pixelFormat)
{
    UL_IMAGE *img = NULL;
    const unsigned char *input;

    // Format 16 bits obligatoire pour le JPG!
    if (ul_pixelWidth[pixelFormat] != 16)
        return NULL;

    input = (const unsigned char*)ulReadEntireFileToMemory(f);

    if (input)
    {
        int width, height;
        JPEG_Decoder decoder;

        JPEG_Decoder_ReadHeaders(&decoder, &input);
        width = decoder.frame.width;
        height = decoder.frame.height;

        // Crée l'image dans laquelle on mettra notre bitmap
        img = ulCreateImage(width, height, pixelFormat, 0);

        if (img)
        {
            if (!JPEG_Decoder_ReadImage (&decoder, &input, img->texture, img->sysSizeX, img->sysSizeY))
            {
                ulDeleteImage(img);
                img = NULL;
            }
        }

        free((void*)input);
    }
    return img;
}
*/
