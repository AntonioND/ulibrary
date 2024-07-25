#include "ulib.h"
#include <filesystem.h>

/*
	SOURCE VFS: libFat
	Taille: 61 ko
*/

int VF_NITRO = -1;

#define _file_			((FILE*)f->ioPtr)

int vfsNitroOpen(void *param1, int param2, int type, int mode, VIRTUAL_FILE* f)			{
	const char *stdMode = "rb";

	//Utilise STDIO
	return (f->ioPtr = (void*)fopen((char*)param1, stdMode)) != NULL;
}

int vfsNitroClose(VIRTUAL_FILE *f)				{
   fclose(_file_);
	return 1;
}

int vfsNitroWrite(const void *ptr, size_t size, size_t n, VIRTUAL_FILE* f)			{
	return fwrite(ptr, size, n, _file_);
}

int vfsNitroRead(void *ptr, size_t size, size_t n, VIRTUAL_FILE* f)			{
	return fread(ptr, size, n, _file_);
}

int vfsNitroGetc(VIRTUAL_FILE *f)		{
   return fgetc(_file_);
}

int vfsNitroPutc(int caractere, VIRTUAL_FILE *f)		{
	return fputc(caractere, _file_);
}

char *vfsNitroGets(char *str, int maxLen, VIRTUAL_FILE *f)			{
	return fgets(str, maxLen, _file_);
}

void vfsNitroPuts(const char *s, VIRTUAL_FILE *f)		{
	fputs(s, _file_);
}

int vfsNitroSeek(VIRTUAL_FILE *f, int offset, int whence)		{
   int oldOffset = ftell(_file_);
   fseek(_file_, offset, whence);
	return oldOffset;
}

int vfsNitroEof(VIRTUAL_FILE *f)		{
	return feof(_file_);
}

VIRTUAL_FILE_SOURCE vfsNitroLib =		{
	vfsNitroOpen,
	vfsNitroClose,
	vfsNitroRead,
	vfsNitroWrite,
	vfsNitroGetc,
	vfsNitroPutc,
	vfsNitroGets,
	vfsNitroPuts,
	vfsNitroSeek,
	vfsNitroEof,
};

int ulInitNitroFs()		{
   if (!nitroFSInit(NULL))
       return -1;
   VF_NITRO = VirtualFileRegisterSource(&vfsNitroLib);
   return VF_NITRO;
}
