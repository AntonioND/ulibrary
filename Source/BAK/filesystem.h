#ifndef FILESYSTEM_H
#define FILESYSTEM_H

//Un fichier
typedef struct		{
	char nom[32];
	int offset;
	int taille;
} BFS_FILE;

//La table d'allocation des fichiers
typedef struct		{
	int nbFichiers;
	BFS_FILE f[];
} BFS_FAT;

//Fonctions de recherche des fichiers
extern void bfsInit();
extern void *bfsSymFind(const char *symbole, BFS_FILE **f);

//Données globales
extern BFS_FAT *bfsFat;
extern void *bfsData;
//extern BFS_FILE *bfsCurFile;

//Pour travailler avec FEOF et savoir lorsqu'un fichier est terminé.
//#define BFS_SET_CURRENT_FILE(f)     bfsCurFile=f;
//#define BFS_GET_CURRENT_FILE()      bfsCurFile;
//#define BFS_FEOF(ptr)               ((void*)(ptr)>=(void*)(bfsCurFile->offset+bfsCurFile->taille+bfsData))

#endif

