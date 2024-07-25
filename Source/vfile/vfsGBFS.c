#include "ulib.h"
#include <gbfs.h>

/*
	SOURCE VFS: GBFS
	Taille: 
	
	Note: sur l'EZ3 les données commencent à 8000010 au lieu de 8000000, le rendant incompatible par défaut.
	gbfs_search_range corrige ce problème mais ralentit le tout!
*/

const GBFS_FILE *ul_data_gbfs;
int VF_GBFS = -1;

int vfsGBFSOpen(void *param1, int param2, int type, int mode, VIRTUAL_FILE* f)			{
   u32 len;
   const char *name = (const char*)param1;
   
   //GBFS: Lecture seule
	if (mode != VF_O_READ)
		return 0;
   
   //Pour la compatibilité avec libfat
   if (name[0] == '/')
   	name++;
   
	f->offset = 0;
   f->ioPtr = (void*)gbfs_get_obj(ul_data_gbfs, name, &len);
   f->maxSize = len;
   return 1;
}

int vfsGBFSClose(VIRTUAL_FILE *f)				{
	return vfsMemClose(f);
}

int vfsGBFSWrite(const void *ptr, size_t size, size_t n, VIRTUAL_FILE* f)			{
	return 0;
}

int vfsGBFSRead(void *ptr, size_t size, size_t n, VIRTUAL_FILE* f)			{
	return vfsMemRead(ptr, size, n, f);
}

int vfsGBFSGetc(VIRTUAL_FILE *f)		{
   return vfsMemGetc(f);
}

int vfsGBFSPutc(int caractere, VIRTUAL_FILE *f)		{
	return 0;
}

char *vfsGBFSGets(char *str, int maxLen, VIRTUAL_FILE *f)			{
	return vfsMemGets(str, maxLen, f);
}

void vfsGBFSPuts(const char *s, VIRTUAL_FILE *f)		{
   
}

int vfsGBFSSeek(VIRTUAL_FILE *f, int offset, int whence)		{
	return vfsMemSeek(f, offset, whence);
}

int vfsGBFSEof(VIRTUAL_FILE *f)		{
	return vfsMemEof(f);
}

VIRTUAL_FILE_SOURCE vfsGBFS =		{
	vfsGBFSOpen,
	vfsGBFSClose,
	vfsGBFSRead,
	vfsGBFSWrite,
	vfsGBFSGetc,
	vfsGBFSPutc,
	vfsGBFSGets,
	vfsGBFSPuts,
	vfsGBFSSeek,
	vfsGBFSEof,
};

int ulInitGBFS(int compatMode)		{
   //Active l'accès à la carte GBA
  	REG_EXMEMCNT &= ~0x80;
  	
  	//Pour la compat. avec EZ3!!
  	if (compatMode == GBFS_COMPATIBLE_MODE)
	  	gbfs_search_range(0x02400000, 0x08000000, 0x0a000000, 0x10);
  	ul_data_gbfs = find_first_gbfs_file((void*)0x08000000);
  	
  	if (ul_data_gbfs)
	   VF_GBFS = VirtualFileRegisterSource(&vfsGBFS);
	   
	//GBFS dépend de la source "mémoire"
	if (VF_MEMORY < 0)
		VirtualFileRegisterSource(&vfsMemory);

   return VF_GBFS;
}


