/*! \file ulib.h
    \brief Main µLibrary file
*/

/** @defgroup main

	Main µLibrary section.
	@{
*/

#ifndef __UL_LIB2D_H__
#define __UL_LIB2D_H__

#ifdef __cplusplus
extern "C" {
#endif

//Includes standard
#include <nds.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "VirtualFile.h"

/** @defgroup main_base Base

	Basic things about µLibrary.
	@{
*/

typedef enum UL_INIT_FLAGS			{
	UL_INIT_ALL = 0,						//!< Initialize all to get started easily
	UL_INIT_LIBONLY = 1,					//!< Initialize the library only, IRQ init and powerOn will be done by yourself
} UL_INIT_FLAGS;

/** Initialization of the library.
	\param flags
		- Pass UL_INIT_ALL by default. µLibrary will initialize everything for you so that you can get started very easily.
		- Pass UL_INIT_LIBONLY if you want to initialize the strict minimum to get µLibrary running. Do that if you know what you are doing, or if you initialize µLibrary after PA_Lib.
*/
void ulInit(UL_INIT_FLAGS flags);

/** @} */ // end of main_base


/** @defgroup main_maths Maths

	Some "maths" functions.
	@{
*/
//Trigonométrie
extern s16 ul_cos[512], ul_sin[512];

/** PI is 256 in µLibrary. One entire circle (2 PI) is 512 and not 360°. This was done like this because of speed. */
#define UL_PI 256
/**
	Calculates the sine of an angle. The return value is in fixed point format (256 = 1.0).
	\param angle
		Angle of the circle. 512 represents a full circle (2 PI).
	\param radius
		Radius of the circle in fixed point.
 */
#define ulSin(angle, radius)	((ul_sin[angle & 511] * radius) >> 8)
/** Calculates the cosine. See ulSin for further information. */
#define ulCos(angle, radius)	((ul_cos[angle & 511] * radius) >> 8)
/** Calculates the absolute value. */
#define ulAbs(x)					(((x)<0)?(-(x)):(x))
/** Returns the smallest value between the two. */
#define ulMin(x, y)				(((x)<(y))?(x):(y))
/** Returns the greatest value between the two. */
#define ulMax(x, y)				(((x)>(y))?(x):(y))
/** Returns the next (greater) power of two starting from that value. */
int ulGetPowerOf2Count(int value);
/** Returns the number of objects in an array.

Example:
   \code
int i;
SPRITE mySprites[10];
...
//Cycle through all 10 sprites
for (i = 0; i < ulNumberof(mySprites); i++)
{
   //And display them
   ulDrawImageXY(mySprites[i].image, mySprites[i].x, mySprites[i].y);
}
   \endcode
*/
#define ulNumberof(n)				(sizeof(n)/sizeof(*(n)))

/** @} */ // end of main_maths


/** @defgroup main_misc Miscellaneous

	Miscellaneous functions.
	@{
*/

/** Puts code in internal ARM9 memory (32 kB) [untested]. */
#define CODE_IN_ITCM __attribute__ ((section (".itcm"), long_call))
/** Puts data in internal ARM9 memory (16 kB) [untested]. */
#define DATA_IN_DTCM __attribute__ ((section (".dtcm")))

/*
	Bizarreries
*/
void *memcpy(void *dest, const void *src, size_t n);
void *memset(void *dest, int chr, size_t n);

//Debug avec PALib
extern int ul_isConsoleInited;

extern inline void ulDebugText(char *text)		{
   if (!ul_isConsoleInited)
	   consoleDemoInit();
	ul_isConsoleInited = 1;
	iprintf(text);
}

/** Debug text with PALib */
#define ulDebug(format...)				({ char __str[1000]; sprintf(__str , ##format); ulDebugText(__str); })

//Affiche les splash
int ulShowSplashScreen1();
int ulShowSplashScreen2();

/** Shows a splash screen.
	\param splashType
		- 1: official µLibrary splash v 1.0
		- 2: Neoflash competition splash
	\return
		0 if an error occured (not enough memory, etc.), 1 else.
	
	Before displaying a splash screen, please ensure that the library is successfully initialized, including the graphical part.
	\code
ulInit(UL_INIT_ALL);
ulInitGfx();
ulShowSplashScreen(1);
ulShowSplashScreen(2);
	\endcode
*/
extern inline int ulShowSplashScreen(int splashType)			{
   if (splashType == 1)
   	return ulShowSplashScreen1();
   else if (splashType == 2)
   	return ulShowSplashScreen2();
   return 0;
}

/** @} */ // end of main_misc

#include "drawing.h"
#include "glWrapper.h"
#include "text.h"
#include "map.h"
#include "keys.h"
#include "messagebox.h"
#include "loading_utility.h"

#ifdef __cplusplus
}
#endif

#endif //__LIB2D_H__

/** @} */ // end of main


