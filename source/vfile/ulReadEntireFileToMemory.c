#include "ulib.h"

//Par blocs de 4 ko
#define BLOCK_SIZE (4 << 10)

//Lit un fichier entier vers la mémoire
void *ulReadEntireFileToMemory(VIRTUAL_FILE *f, int *fileSize)		{
   void *block = NULL;
   int add = 0;
   int size = 0, readSize, finalSize = 0;
   
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
	   finalSize += readSize;
   } while (readSize >= BLOCK_SIZE);
   
   if (fileSize)
   	*fileSize = finalSize;
   return block;
}

