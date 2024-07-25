/*! \file glWrapper.h
    \brief
    	Wrapper for the default libnds VideoGL utility library. Implements namely a dynamic texture system, which allows you to create and remove
    	textures / palettes into VRAM as you want.
*/

#ifndef __UL_GLWRAPPER_H__
#define __UL_GLWRAPPER_H__

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup glwrapper VideoGL Wrapper (internal)

	Wrapper for the default libnds VideoGL utility library. Implements namely a dynamic texture system, which allows you to create and remove
	textures / palettes into VRAM as you want. It's used for internal purposes but you can still use it if you want, however I can't guarantee
	full forward compatibility for some "hacky" functions.
	@{
*/

/** Available banks for memory allocation. */
typedef enum UL_BANKS	 {
	UL_BANK_A = 0x1,				//!< Bank A (128 kB)
	UL_BANK_B = 0x2,				//!< Bank B (128 kB)
	UL_BANK_C = 0x4,				//!< Bank C (128 kB)
	UL_BANK_D = 0x8,				//!< Bank D (128 kB)
	UL_BANK_E = 0x10,				//!< Bank E (64 kB)
	UL_BANK_F = 0x20,				//!< Bank F (16 kB)
	UL_BANK_G = 0x40,				//!< Bank G (16 kB)
	UL_BANK_H = 0x100,			//!< Bank H (32 kB)
	UL_BANK_I = 0x200,			//!< Bank I (16 kB)
} UL_BANKS;

#define UL_BANKS_NUMBER 11

/** Bank types. */
typedef enum UL_BANK_TYPE	 {
	UL_BANK_TYPE_LCD = 1,					//!< LCD (mapped to ARM9 memory)
	UL_BANK_TYPE_TEXTURE = 2,				//!< Texture memory
	UL_BANK_TYPE_TEXPAL = 4,				//!< Texture palette memory
} UL_BANK_TYPE;

extern void *ul_texVramBase;
extern int ul_texVramSize;
extern UL_BANKS ul_texVramBanks;
/** Allows to optimize the image sizes to use less memory. Enabled by default. */
extern u8 ul_optimizeTextureSize;
/** Fills textures with zeroes when creating them. See UL_TEXINITZERO for more information. */
extern u8 ul_initTexturesToZero;

typedef enum UL_TEXINITZERO_TYPE		{
   UL_TEXINITZERO_RAM = 1,						//<! Textures created in memory (RAM) will be filled first
	UL_TEXINITZERO_VRAM = 2,					//<! Textures created in texture memory (VRAM) will be filled first
	UL_TEXINITZERO_ALL = 3						//<! Every textures will be filled with zeroes
} UL_TEXINITZERO_TYPE;


//Attention: les tailles et offsets sont multiples de 16
#define ulTexVramAddressToOffset(add)		(((int)(add) - (int)ul_texVramBase) >> 4)
#define ulTexVramOffsetToAddress(add)		((void*)(((add) << 4) + ul_texVramBase))

#define ulGetTextureAddress(texID)			((void*)(((ulTextureParams[texID] & 0xFFFF) << 3) + ul_texVramBase))

extern int *ulTextureParams;
extern int ulTextureActive;

/*
	PALETTES
*/

extern void *ul_texPalVramBase;
extern int ul_texPalVramSize;
extern UL_BANKS ul_texPalVramBanks;

//Attention: les tailles et offsets sont multiples de 8 - attention ce n'est pas une adresse réelle (il faut rajouter ul_texPalVramBase) mais utilisable pour le GPU
#define ulTexPalAddressToOffset(add)		(((int)(add)) >> 3)
#define ulTexPalOffsetToAddress(add)		((void*)((add) << 3))

//#define ulGetPaletteAddress(palID)	((void*)(&VRAM_F[(palID) >> 1]))
#define ulGetPaletteAddress(palID)	((void*)((int)ul_texPalVramBase + palID))

/** Changes the VRAM allocation parameters for textures. By default, it is allocated to bank A and is 128 kB wide.

	\param activeBanks
		Banks that will be allocated to texture memory. OR them to allocate several banks. Usually UL_BANK_A | UL_BANK_B.
	\param baseAddr
		Video memory base address. Usually (void*)0x06800000. If you select UL_BANK_B only, it will be 0x06820000 and so on.
	\param totalSize
		Total video memory size. For one bank (UL_BANK_A) it's 128 << 10, for two banks (UL_BANK_A | UL_BANK_B) it's 256 << 10, and so on. << 10 multiplies a number by 1024, meaning kilobytes.
		Should be a multiple of 16.
			
	\return
		1 on success, 0 on failure. 

By calling this function, you must be very careful:
	- You MUST provide continuous banks.
	- Changing the texture memory base address will invalidate any pointer to it! You should not change it if you've got some images or textures
	created with µLibrary. Call it on program start or free all your textures / images before.
	- You can easily augment the total memory size, but not easily reduce it. Enough space must be free at the end of the memory heap, and
	even if half the total memory is used, there may be not any space free at the end because of memory fragmentation.
	- The total size will be aligned to 16 manually if it's not, rounded to the next 16 factor (above, never below).

	Here are two lines: the first one is the default, the second one is the recommended for accessing the 256 kB of texture memory.
   \code
ulSetTexVramParameters(UL_BANK_A, VRAM_A, 128 << 10);
ulSetTexVramParameters(UL_BANK_A | UL_BANK_B, VRAM_A, 256 << 10);
	\endcode
*/
int ulSetTexVramParameters(UL_BANKS activeBanks, void *baseAddr, int totalSize);
/** Same as ulSetTexVramParameters but for palettes. Default is:
   \code
ulSetTexPalVramParameters(UL_BANK_F, VRAM_F, 16 << 10);
	\endcode

An equivalent for what VideoGL uses by default is:
   \code
ulSetTexPalVramParameters(UL_BANK_E, VRAM_E, 64 << 10);
	\endcode
*/
int ulSetTexPalVramParameters(UL_BANKS activeBanks, void *baseAddr, int totalSize);


/** glTexImage2D replacement.

There are some differences:
   1) sizeX and sizeY parameter specifies the texture size IN PIXELS, unlike in libnds. If their size is not a power of two:
      - The width will be rounded to the next power of two (ex: 100 => 128)
      - The height will not be rounded, except if ul_optimizePaletteSize is 0, but the texture size supplied to the GPU will be rounded to the next power of two so that it accepts it.
   2) The texture parameter can be NULL to create a texture with uninitialized data. */
int ulTexImage2D(int target, int empty1, int type, int sizeX, int sizeY, int empty2, int param, uint8* texture);
/** glTexParameter replacement. */
void ulTexParameter(uint8 sizeX, uint8 sizeY, uint32* addr, uint8 mode, uint32 param);
/** glGetTexParameter replacement. */
extern inline int ulGetTexParameter()			{
   return ulTextureParams[ulTextureActive];
}
/** glGenTextures replacement. */
int ulGenTextures(int n, int *names);
/** glBindTexture replacement. */
void ulBindTexture(int target, int name);
/** Frees a list of textures created with ulGenTextures and ulTexImage2D. */
void ulFreeTextures(int n, int *names);
/** gluTexLoadPal replacement, with NULL parameter check for pal. */
int uluTexLoadPal(u16* pal, u16 count, uint8 format);
/** glTexUnloadPal replacement. */
void uluTexUnloadPal(u32 addr);
/** Binds a texture so that you can use it with the standard VideoGL API.

This is an awful hack, and will REPLACE the currently active texture in VideoGL. You should not use both systems at once, this hack is only
designed so that you can select a texture and use VideoGL commands that rely on the active texture. */
void ulBindTextureToGl(int target, int name);

/** */
extern inline void ulSetTexAlphaMask(int enable)			{
   if (enable)
	   ulTextureParams[ulTextureActive] |= GL_TEXTURE_COLOR0_TRANSPARENT;
	else
	   ulTextureParams[ulTextureActive] &= ~GL_TEXTURE_COLOR0_TRANSPARENT;
}

/** Changes the current state of one or several VRAM banks.
	Example (set bank A and B to LCD so you can access it):
	\code
ulChangeVramAllocation(UL_BANK_A | UL_BANK_B, UL_BANK_TYPE_LCD);
	\endcode
*/
void ulChangeVramAllocation(UL_BANKS banks, UL_BANK_TYPE type);

/** Internal, do not use. */
void *ulReadTextureToMemory(int textureID, int sizeX, int sizeY, int type);
/** Internal, do not use. */
void *ulReadPaletteToMemory(int paletteID, int palCount);

/** Returns the number of bytes available in texture memory. */
int ulGetTexVramAvailMemory();
/** Returns the number of bytes used in texture memory. */
int ulGetTexVramUsedMemory();
/** Returns the total number of bytes of texture memory (used + remaining). */
int ulGetTexVramTotalMemory();

/** Returns the number of bytes available in texture palette memory. */
int ulGetTexPalAvailMemory();
/** Returns the number of bytes used in texture palette memory. */
int ulGetTexPalUsedMemory();
/** Returns the total number of bytes of texture palette memory (used + remaining). */
int ulGetTexPalTotalMemory();

/** Returns the number of vertices available in the vertex memory (internal to the GPU).

	Each vertex counts as 1 unit, so a quad will take 4 vertices in memory, and a triangle 3 vertices.

	When the vertex memory is full, it will no more be possible to draw anything with µLibrary, so this is something very useful to watch!
*/
extern inline int ulGetVertexAvailMemory()			{
   return 6144 - GFX_VERTEX_RAM_USAGE;
}

/** Returns the number of vertex already stored since the render has started.  */
extern inline int ulGetVertexUsedMemory()			{
   return GFX_VERTEX_RAM_USAGE;
}

/** Returns the total number of vertices possible in the vertex memory. */
extern inline int ulGetVertexTotalMemory()			{
   return 6144;
}


/** @} */ // end of glwrapper

#ifdef __cplusplus
}
#endif

#endif

