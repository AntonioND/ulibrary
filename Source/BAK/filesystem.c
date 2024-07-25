#include "commun.h"

const char test_format[]=" Game boy advance filesystem by Brünni ****";

#define ALIGNEMENT 4
#define LIMITE_RECHERCHE ((const u32 *)0x0a000000)

TAF *bfsFat;
void *bfsData;
//FICHIER *bfsCurFile;

void bfsInit()           {
    const u32 *ici=(u32*)((u32)InitFS&(-ALIGNEMENT));

    while(ici<LIMITE_RECHERCHE)         {
        if (*ici==0x2a2a2a2a)       {             //Les étoiles
            if (!memcmp(ici+1,test_format,44))          {
                ici+=48/4;
                break;
            }
        }
        ici+=ALIGNEMENT/4;
    }

    bfsFat=(TAF*)ici;
    bfsData=(void*)ici+bfsFat->nbFichiers*sizeof(FICHIER)+sizeof(int);
}

void *bfsSymFind(const char *symbole, FICHIER **f)         {
    int i;
    
    for (i=0;i<bfsFat->nbFichiers;i++)          {
        if (!strcmp(symbole,bfsFat->f[i].nom))      {
            if (f!=NULL)
                *f=&bfsFat->f[i];
            return (void*)bfsData+bfsFat->f[i].offset;
        }
    }
    return NULL;
}



