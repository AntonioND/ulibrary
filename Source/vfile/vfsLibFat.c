#include "ulib.h"
#include <fat.h>				// filesystem functions

/*
	SOURCE VFS: libFat
	Taille: 61 ko
*/

int VF_FILE = -1;

#define _file_			((FILE*)f->ioPtr)

int vfsFatOpen(void *param1, int param2, int type, int mode, VIRTUAL_FILE* f)			{
	const char *stdMode = "rb";
	if (mode == VF_O_WRITE)
		stdMode = "wb";
	else if (mode == VF_O_READWRITE)
		stdMode = "wb+";
	
	//Utilise STDIO
	return (f->ioPtr = (void*)fopen((char*)param1, stdMode)) != NULL;
}

int vfsFatClose(VIRTUAL_FILE *f)				{
   fclose(_file_);
	return 1;
}

int vfsFatWrite(const void *ptr, size_t size, size_t n, VIRTUAL_FILE* f)			{
	return fwrite(ptr, size, n, _file_);
}

int vfsFatRead(void *ptr, size_t size, size_t n, VIRTUAL_FILE* f)			{
	return fread(ptr, size, n, _file_);
}

int vfsFatGetc(VIRTUAL_FILE *f)		{
   return fgetc(_file_);
}

int vfsFatPutc(int caractere, VIRTUAL_FILE *f)		{
	return fputc(caractere, _file_);
}

char *vfsFatGets(char *str, int maxLen, VIRTUAL_FILE *f)			{
	return fgets(str, maxLen, _file_);
}

void vfsFatPuts(const char *s, VIRTUAL_FILE *f)		{
	fputs(s, _file_);
}

int vfsFatSeek(VIRTUAL_FILE *f, int offset, int whence)		{
   int oldOffset = ftell(_file_);
   fseek(_file_, offset, whence);
	return oldOffset;
}

int vfsFatEof(VIRTUAL_FILE *f)		{
	return feof(_file_);
}

VIRTUAL_FILE_SOURCE vfsFatLib =		{
	vfsFatOpen,
	vfsFatClose,
	vfsFatRead,
	vfsFatWrite,
	vfsFatGetc,
	vfsFatPutc,
	vfsFatGets,
	vfsFatPuts,
	vfsFatSeek,
	vfsFatEof,
};

int ulInitLibFat()		{
   fatInitDefault();
   VF_FILE = VirtualFileRegisterSource(&vfsFatLib);
   return VF_FILE;
}


