#include "ulib.h"

UL_FONT *ulLoadFontFile(const char *fileName, int fileSize)			{
	VIRTUAL_FILE *f;
	UL_FONT *ft = NULL;

	//Si aucune source n'est sélectionnée, on prend la dernière
	if (ul_loadUtilActiveSource == -1)
		ul_loadUtilActiveSource = VirtualFileSourcesNb - 1;

	//Charge un fichier PNG
	f = VirtualFileOpen((void*)fileName, fileSize, ul_loadUtilActiveSource, VF_O_READ);
	if (f)			{
		ft = ulLoadFont(f);
		VirtualFileClose(f);
	}
	return ft;
}

