#include "lib2d.h"
#include "gif/gif_lib.h"

//s16 gifwidth, gifheight;
u16 *temppalette; // Utilisé pour stocker la palette des gifs...
GifFileType* gifinfo;
u8 *tempscreen; // Ecran temporaire...
//extern u8 PA_nBit[2]; 

//int ulGifBits;			//Mode de couleur
int GifBits;				//Mode de couleur

const short InterlacedOffset[] = { 0, 4, 2, 1 }; /* The way Interlaced image should. */
const short InterlacedJumps[] = { 8, 8, 4, 2 };    /* be read - offsets and jumps... */

int m;

GifPixelType LineBuf[2048]; // Buffer temporaire
   
int readFunc(GifFileType* GifFile, GifByteType* buf, int count)
{
    char* ptr = (char*)GifFile->UserData;
    memcpy(buf, ptr, count);
    GifFile->UserData = ptr + count;
    return count;
}

void CopyLine(void* dst, void* src, int count){ // Pour 8 bit
/*s16 temp = (count +1) >> 1;
	DMA_Copy(src, dst, temp, DMA_16NOW); // Copy rapide*/

    do {
	*(u16*) dst = *(u16*) src;
	src = (u8*)src + 2;
	dst = (u8*)dst + 2;
	count -= 2;
    }
    while (count > 0); // On fait 4 par 4, puis 2 par 2...
//	if (count >= 0) *(u16*) dst = *(u16*) src; // On finit les 2 derniers
}

void CopyLine2(void* dst, void* src, int count){ // Pour 16 bit
u8 *temp = (u8*)src;
    do {
	*(u16*)dst = temppalette[*temp]; // On prend la couleur de la palette
	temp++;
	dst = (u8*)dst + 2;
	count -= 1;
    }
    while (count > 0);
}



int DGifGetLineByte(GifFileType *GifFile, GifPixelType *Line, int LineLen){
    if (GifBits == 0) CopyLine(LineBuf, Line, LineLen); // On fait un backup 
    int result = DGifGetLine(GifFile, LineBuf, LineLen); // Nouvelle ligne
//	if (PA_GifInfo.CurrentFrame >=  PA_GifInfo.StartFrame) {
		if (GifBits == 0) CopyLine(Line, LineBuf, LineLen); // Copie 8 bit
		if (GifBits == 1) CopyLine2(Line, LineBuf, LineLen); // Copie 8 bit	
//	}
    return result;
}



#define GAMMA(x)	((x) >> 3)

/*#ifdef _NO_FILEIO
#define PrintGifError()
#endif*/

//#define EXIT_FAILURE 1


UL_IMAGE *ulLoadImageGIF(VIRTUAL_FILE *f, int flags, int pixelFormat)
{
	UL_IMAGE *img = NULL;
	void *input;
   
   input = ulReadEntireFileToMemory(f);
 
   if (input)			{

		int	i, j, Row, Col, Width, Height, ExtCode, Count;
		GifRecordType RecordType;
		GifByteType *Extension;
		GifFileType *GifFile;
		ColorMapObject *ColorMap;
			
		GifBits = pixelFormat;
		if (GifBits == 1) { // On utilise une palette temporaire...
			temppalette = (u16*)malloc(512); // Ecran temporaire	
			Palette = temppalette;
		}
		
		GifFile = DGifOpen(input, readFunc);
 
		// Scan the content of the GIF file and load the image(s) in:
		do {								// Je vire les messages d'erreur pour gagner de la place
			DGifGetRecordType(GifFile, &RecordType);
		
			switch (RecordType) {
				case IMAGE_DESC_RECORD_TYPE:
					DGifGetImageDesc(GifFile);
					/*if (DGifGetImageDesc(GifFile) == GIF_ERROR) {
					PrintGifError();
					return EXIT_FAILURE;
					}*/
					Row = GifFile->Image.Top; /* Image Position relative to Screen. */
					Col = GifFile->Image.Left;
					Width = GifFile->Image.Width;
					Height = GifFile->Image.Height;

					// Update Color map
					ColorMap = (GifFile->Image.ColorMap	? GifFile->Image.ColorMap: GifFile->SColorMap);
					//		if (PA_GifInfo.CurrentFrame >=  PA_GifInfo.StartFrame) {// Load Palette only if correct frame
					i = ColorMap->ColorCount;
					while (--i >= 0)  {
						GifColorType* pColor = &ColorMap->Colors[i];
						Palette[i] = RGB15(GAMMA(pColor->Red), GAMMA(pColor->Green), GAMMA(pColor->Blue));
					}
					//		}

					//GifFile->Image.Delay;
					/*
				    if (GifFile->Image.Left + GifFile->Image.Width > GifFile->SWidth ||
					GifFile->Image.Top + GifFile->Image.Height > GifFile->SHeight) {
					return EXIT_FAILURE;
				    }*/
			
					if (GifFile->Image.Interlace) {
						// Need to perform 4 passes on the images:
						for (Count = i = 0; i < 4; i++) {
							for (j = Row + InterlacedOffset[i]; j < Row + Height;
								j += InterlacedJumps[i]) {
								DGifGetLineByte(GifFile, (ScreenBuff + (((SWidth*j) + Col) << GifBits)),Width);
								/*if (DGifGetLineByte(GifFile, &ScreenBuff[j][Col],
									Width) == GIF_ERROR) {
									PrintGifError();
									return EXIT_FAILURE;
								}*/
							}
						}
					}
					else {
						for (i = 0; i < Height; i++) {
							DGifGetLineByte(GifFile, (ScreenBuff + (((SWidth*Row) + Col) << GifBits)),Width);
							Row++;
							/*
							if (DGifGetLineByte(GifFile, &ScreenBuff[Row++][Col],
							Width) == GIF_ERROR) {
								PrintGifError();
								return EXIT_FAILURE;
							}*/
						}
					}
					break;
			
				case EXTENSION_RECORD_TYPE:
					// Skip any extension blocks in file:
					DGifGetExtension(GifFile, &ExtCode, &Extension);

					//	s32	test = DGifGetExtension(GifFile, &ExtCode, &Extension);

					// CHECK HERE FOR GIF TIMING !!
			
				    /*if (DGifGetExtension(GifFile, &ExtCode, &Extension) == GIF_ERROR) {
					PrintGifError();
					return EXIT_FAILURE;
				    }*/
					while (Extension != NULL) {
						if(ExtCode == GRAPHICS_EXT_FUNC_CODE)
						{
							s32 disposalMethod = (Extension[1] >> 2) & 7;
							disposalMethod = 0;
		//						if((Extension[1] & 1) == 1) // transparency color exists
		//							pd->transColor = Extension[4];		
		
							int tmpDelay = 0;
							double tmpNumber = 0;
		
							tmpDelay = Extension[2];
							tmpDelay += Extension[3] << 8;
		
							tmpNumber = (double)(tmpDelay) * (double)60;
							tmpNumber = tmpNumber / (double)100;
		
							tmpDelay = (int)tmpNumber;
		//						s32 time;
							
		//						PA_GifInfo.CurrentFrame++;
		//						if (PA_GifInfo.CurrentFrame > PA_GifInfo.EndFrame) PA_GifInfo.Play = 0; // Last frame...
							
		/*						if (PA_GifInfo.CurrentFrame-1 >=  PA_GifInfo.StartFrame){	// Don't wait if not at the right frame yet				
								for(time=0;time*PA_GifInfo.Speed<tmpNumber;time++) {
									PA_WaitForVBL(); 
									while(PA_GifInfo.Play == 2) PA_WaitForVBL(); // Pause animation !
									if (PA_GifInfo.Play == 0) goto GifStop;
								}
							}*/
							
							
		//						pd->aniDelay = tmpDelay;
							
							
						}
						DGifGetExtensionNext(GifFile, &Extension);
						/*if(DGifGetExtensionNext(pd->streamFile, &Extension) == GIF_ERROR) 
						{
							closeGifStreaming(pd);
							pd->error = true;
							sendCallBack(pd, FINISH_PROGRESS, 0);
							return;
						}*/
				   }
					break;

				case TERMINATE_RECORD_TYPE:
					break;
				default:		    /* Should be traps by DGifGetRecordType. */
					break;
			}
		} while (RecordType != TERMINATE_RECORD_TYPE);
		 
		 /* Close file when done */
		//	GifStop:
		DGifCloseFile(GifFile);
		 /*if (DGifCloseFile(GifFile) == GIF_ERROR) {
		PrintGifError();
		return EXIT_FAILURE;
		 }*/
		
		if (GifBits == 1) free(temppalette); // On vire la mémoire allouée
	
		
	   free((void*)input);
	}
	return img;
}

/*
#include "jpeg/gba-jpeg.h"
#include "jpeg/gba-jpeg-decode.h"

//Par blocs de 16 ko
#define BLOCK_SIZE (16 << 10)

//Lit un fichier entier vers la mémoire
void *ulReadEntireFileToMemory(VIRTUAL_FILE *f)		{
   void *block = NULL;
   int add = 0;
   int size = 0, readSize;
   
   do		{
      size += BLOCK_SIZE;
      if (block)
		   block = realloc(block, size);
      else
		   block = malloc(size);

		//L'allocation a échoué?
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
	
   //Format 16 bits obligatoire pour le JPG!
   if (ul_pixelWidth[pixelFormat] != 16)
   	return NULL;
   
   input = (const unsigned char*)ulReadEntireFileToMemory(f);
   
   if (input)			{
      int width, height;
		JPEG_Decoder decoder;
		
		JPEG_Decoder_ReadHeaders(&decoder, &input);
		width = decoder.frame.width;
		height = decoder.frame.height;
		
		//Crée l'image dans laquelle on mettra notre bitmap
		img = ulCreateImage(width, height, pixelFormat, 0);

		if (img)			{
		   if (!JPEG_Decoder_ReadImage (&decoder, &input, img->texture, img->sysSizeX, img->sysSizeY))			{
		   	ulDeleteImage(img);
		   	img = NULL;
			}
		}
		
	   free((void*)input);
	}
	return img;
}
*/

