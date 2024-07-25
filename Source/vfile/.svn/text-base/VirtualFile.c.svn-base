#include "ulib.h"

/*
	Note: seek retourne l'ancienne position!
*/

VIRTUAL_FILE_SOURCE *VirtualFileSources[VF_MAX_SOURCES];
int VirtualFileSourcesNb = 0;
int VF_MEMORY = -1;
//List of files for RAM based devices
UL_VIRTUALFILENAME *ul_virtualFileList;
int ul_virtualFileListNumber = 0;

//Enregistre une nouvelle source
int VirtualFileRegisterSource(VIRTUAL_FILE_SOURCE *vfs)		{
	//Espace libre?
	if (VirtualFileSourcesNb >= VF_MAX_SOURCES)
		return -1;
	//Ajoute la source
	VirtualFileSources[VirtualFileSourcesNb] = vfs;
	return VirtualFileSourcesNb++;
}

VIRTUAL_FILE *VirtualFileOpen(void *param1, int param2, int type, int mode)			{
	VIRTUAL_FILE *f;
	f = (VIRTUAL_FILE*)malloc(sizeof(*f));
	if (f)		{
		memset(f, 0, sizeof(*f));
		f->type = type;
		if (!VirtualFileGetSource(f)->fOpen(param1, param2, type, mode, f))			{
			free(f);
			f = NULL;
		}			
	}
	return f;
}

int VirtualFileClose(VIRTUAL_FILE *f)			{
	int result = VirtualFileGetSource(f)->fClose(f);
	if (result)
		free(f);
	return result;
}

/*
	SOURCE 1 par défaut: Mémoire
*/

int vfsMemOpen(void *param1, int param2, int type, int mode, VIRTUAL_FILE* f)			{
	//Tous les modes sont supportés mais pas très bien pour l'instant, ne vous amusez pas à écrire et lire en même temps
//	if (mode != VF_O_READ || mode != VK_O_WRITE)
//		return 0;

	//C'est un nom de fichier?
	if (param2 == 0)			{
	   UL_VIRTUALFILENAME *file = ulFindFileInVirtualFilenameList((const char*)param1, type);
	   if (file)		{
		   param1 = file->data;
		   param2 = file->size;
		}
	}
		
	//Initialisation du bloc mémoire
	f->offset = 0;
	f->ioPtr = param1;
	f->maxSize = param2;
	return 1;
}

int vfsMemClose(VIRTUAL_FILE *f)				{
	return 1;
}

int vfsMemWrite(const void *ptr, size_t size, size_t n, VIRTUAL_FILE* f)			{
	int realSize = size * n, writeSize = 0;
	if (f->ioPtr)		{
		//Débordement?
		writeSize = ulMin(realSize, f->maxSize - f->offset);
		memcpy((char*)f->ioPtr + f->offset, ptr, writeSize);
		f->offset += realSize;
	}
	return writeSize;
}

int vfsMemRead(void *ptr, size_t size, size_t n, VIRTUAL_FILE* f)			{
	int readSize = 0, realSize = size * n;

	if (f->ioPtr)		{
		//min => pour éviter les débordements
		readSize = ulMin(realSize, f->maxSize - f->offset);
		memcpy(ptr, (char*)f->ioPtr + f->offset, readSize);
		f->offset += realSize;
	}
	return readSize;
}

int vfsMemGetc(VIRTUAL_FILE *f)		{
	unsigned char car;
	//Pour la sécurité, quand même un cas à part pour les fichiers
	if (VirtualFileRead(&car, sizeof(car), 1, f) < 1)
		return -1;
	else
		return (int)car;
}

int vfsMemPutc(int caractere, VIRTUAL_FILE *f)		{
	unsigned char car = caractere;
	if (VirtualFileWrite(&car, sizeof(car), 1, f) < 1)
		return -1;
	else
		return caractere;
}

char *vfsMemGets(char *str, int maxLen, VIRTUAL_FILE *f)			{
	const int blockSize = 16;
	int offset = 0, i, size;
	while(1)			{
		size = VirtualFileRead(str + offset, 1, ulMin(maxLen - offset, blockSize), f);
		if (offset + size < maxLen)
			str[offset + size] = 0;
		for (i=offset;i<offset+blockSize;i++)		{
			if (str[i] == 0)
				return str;
			//\r\n (Windows)
			if (str[i] == '\r')			{
				str[i] = 0;
				//Dernier bloc de la liste?
				if (i + 1 >= offset + blockSize)			{
					char temp[1];
					int tempSize;
					tempSize = VirtualFileRead(temp, 1, 1, f);
					//Prochain caractère est un \n?
					if (!(tempSize > 0 && temp[0] == '\n'))
						//Sinon on annule
						i--;
				}
				else	{
					if (str[i + 1] == '\n')
						i++;
				}
				//Retourne le pointeur
				VirtualFileSeek(f, -size + (i - offset) + 1, SEEK_CUR);
				return str;
			}
			else if (str[i] == '\n')			{
				str[i] = 0;
				//ATTENTION: MODIFIE DE -blockSize + i à -blockSize + i + 1, à vérifier!!!
				VirtualFileSeek(f, -blockSize + i + 1, SEEK_CUR);
				//Retourne le pointeur
				return str;
			}
		}
		offset += blockSize;
	}
	return str;
}

void vfsMemPuts(const char *s, VIRTUAL_FILE *f)		{
	VirtualFileWrite(s, strlen(s), 1, f);
}

int vfsMemSeek(VIRTUAL_FILE *f, int offset, int whence)		{
   int oldOffset = f->offset;
	if (f->ioPtr)		{
		if (whence == SEEK_SET)
			f->offset = offset;
		else if (whence == SEEK_CUR)
			f->offset += offset;
		else if (whence == SEEK_END)
			f->offset = f->maxSize + offset;
		f->offset = ulMax(ulMin(f->offset, f->maxSize), 0);
	}
	return oldOffset;
}

int vfsMemEof(VIRTUAL_FILE *f)		{
	return (f->offset < f->maxSize);
}

VIRTUAL_FILE_SOURCE vfsMemory =		{
	vfsMemOpen,
	vfsMemClose,
	vfsMemRead,
	vfsMemWrite,
	vfsMemGetc,
	vfsMemPutc,
	vfsMemGets,
	vfsMemPuts,
	vfsMemSeek,
	vfsMemEof,
};

//Définit la liste de fichiers pour les sources basées sur la mémoire
void ulSetVirtualFilenameList(UL_VIRTUALFILENAME *vfl, int numberOfEntries)		{
   ul_virtualFileList = vfl;
   ul_virtualFileListNumber = numberOfEntries;
}

UL_VIRTUALFILENAME *ulFindFileInVirtualFilenameList(const char *fname, int type)			{
   int i;
   if (fname)			{
      //Skip the first / that means root for libFat
      if (fname[0] == '/')
      	fname++;
	   for (i=0;i<ul_virtualFileListNumber;i++)			{
	      if (type == *ul_virtualFileList[i].type
	      	&& !strcmp(fname, ul_virtualFileList[i].name))
	      	return &ul_virtualFileList[i];
	   }
	}
   return NULL;
}

void VirtualFileInit()			{
   if (VF_MEMORY < 0)			{
	   //On enregistre les sources par défaut
		VF_MEMORY = VirtualFileRegisterSource(&vfsMemory);
	}
}

   

