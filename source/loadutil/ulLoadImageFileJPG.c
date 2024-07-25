#include "ulib.h"

UL_IMAGE *ulLoadImageFileJPG(const char *fileName, int fileSize, int location, int pixelFormat)			{
	VIRTUAL_FILE *f;
	UL_IMAGE *img = NULL;

	//Si aucune source n'est sélectionnée, on prend la dernière
	if (ul_loadUtilActiveSource == -1)
		ul_loadUtilActiveSource = VirtualFileSourcesNb - 1;

	//Charge un fichier PNG
	f = VirtualFileOpen((void*)fileName, fileSize, ul_loadUtilActiveSource, VF_O_READ);
	if (f)			{
		img = ulLoadImageJPG(f, location, pixelFormat);
		VirtualFileClose(f);
	}
	return img;
}

