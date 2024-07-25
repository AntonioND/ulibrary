/*! \file drawing.h
    \brief
    	Main file about drawing in µLib.
*/

/** @defgroup drawing

	All about drawing!
	@{
*/

#ifndef __UL_DRAWING_H__
#define __UL_DRAWING_H__

#ifdef __cplusplus
extern "C" {
#endif

#ifndef REG_CAPTURE
	#define	REG_CAPTURE		(*(vu32*)0x04000064)
#endif

/** Defines the screen width of the Nintendo DS. Example of use:

\code
//Fade the whole screen with a semi transparent (16) black rectangle
ulSetAlpha(UL_FX_ALPHA, 16, 1);
ulDrawFillRect(0, 0, UL_SCREEN_WIDTH, UL_SCREEN_HEIGHT, RGB15(0, 0, 0));
//Restore default alpha
ulSetAlpha(UL_FX_DEFAULT, 0, 0);
\endcode */
#define UL_SCREEN_WIDTH 256
/** Defines the screen height. See #UL_SCREEN_WIDTH for more information. */
#define UL_SCREEN_HEIGHT 192

/** Color type. It's cleaner to use this when manipulating colors as your code will become more easily portable (e.g. on PSP where colors are
32 bits). */
typedef unsigned short UL_COLOR;

/** Retrieves the red component value of the specified color. Example:

\code
//Brightens a color (approach each component from the maximum, 31)
void colorBrighten(UL_COLOR c)
{
	u8 r, g, b;
	
	r = (31 + ulGetColorRed(c)) / 2;
	g = (31 + ulGetColorGreen(c)) / 2;
	b = (31 + ulGetColorBlue(c)) / 2;
	
	return RGB15(r, g, b);
} \endcode */
#define ulGetColorRed(color)		((color) & 31)
/** Retrieves the green component value of the specified color. */
#define ulGetColorGreen(color)	(((color) >> 5) & 31)
/** Retrieves the blue component value of the specified color. */
#define ulGetColorBlue(color)		(((color) >> 10) & 31)


/** Image type */
typedef struct			{
	//Public
	s16 x, y;							//Coordonnées
	//Utiliser ulSetDepth
//	s16 z;								//Profondeur de l'objet
	s16 stretchX, stretchY;
	u16 angle;							//0 ... 511
	s16 centerX, centerY;			//Centre de rotation
	s16 offsetX0, offsetY0, offsetX1, offsetY1;
	s16 tint1, tint2, tint3, tint4;

	//Protégé
	u16 sizeX, sizeY;
	//System size (power of 2 boundary)
	u16 sysSizeX, sysSizeY;
	u8 format;							//Voir UL_IMAGE_FORMATS
	u8 imgState, palState;			//Voir UL_IMAGE_STATES
	u8 location;
	s16 textureID, paletteID, palCount;
	void *texture, *palette;
} UL_IMAGE;

/** Special effects */
typedef enum UL_SPECIAL_EFFECT		{
   UL_FX_DEFAULT = 0,									//!< Opaque
	UL_FX_ALPHA = 1										//!< Alpha blending
} UL_SPECIAL_EFFECT;

extern s32 ul_currentDepth;
extern u8 ul_autoDepth;


/** @defgroup drawing_base Drawing base

	Contains basic functions you need to call for drawing.
	@{
*/

/**
	\~english Initialization of the graphical part 
	\~french Initialisation de la partie graphique
*/
void ulInitGfx();

/**
	\~english Initialize dual screen mode. See the supplied samples for an example of using dual screen. However, be aware that using the dual
	screen mode will drop your application framerate to 30 fps! You can also use PALib or libnds to control the second screen.
	\~french Initialisation du mode double écran
*/
void ulInitDualScreenMode();

/** Stops the dual screen mode. */
void ulStopDualScreenMode();

/**
	\~english Start a new drawing, configure 2D. Call it once per frame.
	
	You can call it a second time (or more) in a frame to reset the view to 2D. If you want to draw some 3D, just set up the needed 3D params and call ulStartDrawing2D to return to 2D. Note that this function has not been tested,
	any feedback is appreciated. ;)
	
	\~french Début de dessin, configuration 2D. L'appeler une fois par frame.
*/
void ulStartDrawing2D();
/**
	\~english End the current drawing. Call after you've finished drawing, and once per frame. Further drawing will not be possible until the next frame.
	\~french Fin du dessin, à n'appeler qu'en fin de frame.
*/
void ulEndDrawing();
/**
	\~english Waits the VBlank period to synchronize at 60 fps. You need to call it, else call ulEndFrame during the VBlank.
	\~french Attend la VBlank.
*/
void ulSyncFrame();

/**
	\~english End of a frame. Call it only if you don't call ulSyncFrame.
	\~french Fin d'une frame.
*/
void ulEndFrame();

/** @} */ // end of base



/** Enables edge antialiasing. */
#define ulEnableEdgeAntialiasing()		(GFX_CONTROL |=  GL_ANTIALIAS)
/** Disables edge antialiasing. */
#define ulDisableEdgeAntialiasing()		(GFX_CONTROL &= ~GL_ANTIALIAS)

/** 
	\~english Sets the transparent color for loading images. Any pixel matching this color will be set as transparent upon loading.
	This does not have any effect ouside of loading images, and doesn't work for JPG format.
	Also, this will not affect GIF files which do have a transparent color. The said transparent color will be used instead.
	\~french Définit la couleur transparente d'arrière plan de l'image.
*/
#define ulSetTransparentColor(color)	(ul_colorKeyEnabled = 1, ul_colorKeyValue = color)
/** 
	\~english Disables the transparent color setting (as it is by default).
	Useful if your image already has an alpha channel and you don't need to have a color key.
*/
#define ulDisableTransparentColor()		(ul_colorKeyEnabled = 0)

//Définit la couleur du fond, à tester. N'a pas l'air de marcher super bien...
void ulSetScreenBackgroundColor(UL_COLOR color);


/** @defgroup clipping Clipping / Windowing
	\brief Broken. Please see detailed description!
	
	Does not work properly because of precision errors, and doesn't work at all with rotation!
	If you've got any idea on how to do it better, please tell me, it would really help, thanks ;)
	@{
*/

/**
	\~english Defines a window on the screen.
	Everything will be drawn within this window. If you draw an object at (0,0), it will be drawn on the top-left corner of your window. If the object exceeds of any corner of the window, it will be clipped (cutted).
	\~french Définit une fenêtre (tout ce qui sera dessiné sera redirigé à cet endroit), ne fonctionne pas bien.
*/
void ulSetScreenWindow(int x0, int y0, int x1, int y1);
/**
	\~english Defines the screen clipping zone.
	Only pixels within the clipping rectangle will be drawn on the screen.
	
	Currently, does not work properly (especially with rotation), I should find another way to do that, if you have any idea, please tell me ;)
	\~french Définit la zone de clipping (tout ce qui est dessiné en dehors ne sera pas affiché), ne fonctionne pas bien.
*/
void ulSetScreenClipping(int x0, int y0, int x1, int y1);
/**
	\~english Resets the clipping region, including the window.
	\~french Réinitialise la zone de clipping, incluant la fenêtre.
*/
void ulResetScreenClipping();
/** @} */ // end of clipping



/** @defgroup screen_view Screen view
	
	Contains functions to move, rotate and scale the screen as a whole. This will affect the objects that you will draw after having called these
	commands, the objects drawn before will stay as they were.

	Something interesting is that all these function can be combined to fine tune your final screen transformation.
	For example you can move the screen and then rotate it, enabling you to control its rotation center.
	
	@{
*/

/** Resets the screen projection to its initial state. The objects drawn from here will not be transformed anymore. */
void ulResetScreenView();

/** Moves the screen as a whole.
	\param posX
		Horizontale move. A positive values means moving rightwards while a negative value moves leftwards.
	\param posY
		Vertical move. A positive value means moving downwards while a negative value moves upwards.
		
	Note: The values for these parameters are defined in pixels.
*/
void ulMoveScreenView(int posX, int posY);

/** Scales the screen view.
	\param scaleX
		Horizontal scaling factor. 4096 (1 << 12) means 1. 8192 means 2 and 2048 means 0.5 for example.
	\param scaleY
		Vertical scaling factor.

	Note: The values for these parameters are defined in fixed point. There are 20 bits for the integer part and 12 bits for the decimal part.
	If you want to convert an integer number to a fixed factor you can do the following: inttof32(number). If you want to convert a float to a
	fixed number, you can do floattof32(number).
	
	Note 2: Scaling with a negative factor flips the screen. This can be useful...
*/
void ulScaleScreenView(int scaleX, int scaleY);

/** Rotates the screen view.
	\param angle
		Angle of rotation. It's not in degrees but in the same scale that ulSin, ulCos, etc. between 0 and 2 * UL_PI. The rotation is done
		clockwise.

	Don't forget that you can mix up these routines to fine tune your transformation. For example, by default a rotation is done around the
	top-left point of the screen. If you want to center your rotation, you can just move your screen prior to rotate it and move it to its
	initial position afterwards.
	
	\code
ulMoveScreenView(UL_SCREEN_WIDTH / 2, UL_SCREEN_HEIGHT / 2);
ulRotateScreenView(angle);
ulMoveScreenView(-UL_SCREEN_WIDTH / 2, -UL_SCREEN_HEIGHT / 2);
	\endcode
*/
void ulRotateScreenView(int angle);


/** @} */ // end of screen_view


/** @defgroup untexgeo Untextured geometry
	 
	 \brief Untextured geometry (rectangles, lines, etc.)

	 - No$gba doesn't recognize lines ("flat triangles"), rendering lines & empty rectangles as invisible.
	 - Do not enable edge antialiasing when drawing lines else they'll be too fine and invisible on DS.
    @{
*/

/** \~english Draws a filled rectangle.
	 \~french Dessine un rectangle plein */
void ulDrawFillRect(s16 x0, s16 y0, s16 x1, s16 y1, UL_COLOR color);

/** \~english Draws a line (doesn't work on no$gba)
	 \~french Dessine une ligne (ne fonctionne pas sur no$gba) */
void ulDrawLine(s16 x0, s16 y0, s16 x1, s16 y1, UL_COLOR color);

/** \~english Draws an empty rectangle (doesn't work on no$gba)
	 \~french Dessine un rectangle vide (ne fonctionne pas sur no$gba) */
void ulDrawRect(s16 x0, s16 y0, s16 x1, s16 y1, UL_COLOR color);

/** Draws a 4 corner gradient-filled rectangle.
	\param color1
		Color used for the top-left corner.
	\param color2
		Color used for the top-right corner.
	\param color3
		Color used for the bottom-left corner.
	\param color4
		Color used for the bottom-right corner.
*/
void ulDrawGradientRect(s16 x0, s16 y0, s16 x1, s16 y1, UL_COLOR color1, UL_COLOR color2, UL_COLOR color3, UL_COLOR color4);

/** @} */ // end of untexgeo



/** @defgroup images Images
	 
	 \brief Image support in µLibrary.
    @{
*/

//Valeur de la color key (PNG de type RGB)
extern u8 ul_colorKeyEnabled;
extern UL_COLOR ul_colorKeyValue;

/** Available image pixel formats */
enum UL_IMAGE_FORMATS	 {
						UL_PF_PAL5_A3=1,				//!< 32-colour palette + 8-tone alpha
						UL_PF_PAL2,						//!< 4-colour palette
						UL_PF_PAL4,						//!< 16-colour palette
						UL_PF_PAL8,						//!< 256-colour palette
						UL_PF_COMPRESSED,				//!< Not figured out
						UL_PF_PAL3_A5,					//!< 8-colour palette + 32-tone alpha
						UL_PF_5551, 					//!< 16-bit RGBA
						UL_PF_5550,						//!< 15-bit RGB - virtual format (5551 with alpha bit set to 1)
};

/** Image or palette states (location in memory) */
enum UL_IMAGE_STATES			{
	UL_STATE_NONE = 0,				//!< N'existe pas encore
	UL_STATE_RAM,						//!< L'image est quelque part en mémoire, ne pas s'en occuper
	UL_STATE_RAM_BLOCK,				//!< L'image utilise un bloc, à libérer (free) une fois que l'image est copiée en VRAM
	UL_STATE_VRAM,						//!< L'image a été copiée en VRAM et n'est plus accessible
};

/** Reason for locking an image (wether you want to access its palette, texture, etc.) */
typedef enum UL_LOCK_REASON			{
   UL_LOCK_NONE = 0,					//!< Do not use
   UL_LOCK_PIXELS = 1,				//!< Access to image pixel data
   UL_LOCK_PALETTE = 2,				//!< Access to image palette data
} UL_LOCK_REASON;

//Taille des palettes (2^n)
extern const u8 ul_paletteSizes[];
extern const int ul_pixelWidth[];
extern const u8 ul_pixelsPerByte[];

/** Size of pixel formats */
extern const u8 ul_pixelSizes[];

/** @defgroup images_creation Creating and deleting images
	\brief Image Basic routines needed to work with images.
    @{
*/

enum UL_IMAGE_LOCATION		{
   UL_IN_RAM = 0,
   UL_IN_VRAM = 1,
};   

/** Creates a new image and allocates memory in RAM for it */
extern UL_IMAGE *ulCreateImage(int width, int height, int location, int format, int palCount);
/* Creates an image from an uncompressed texture + palette. */
//extern UL_IMAGE *ulCreateImageFromTexture(const void *texture, int width, int height, int location, int format, void *palette, int palcount);
/** Creates a palette for an image. The image must not have a palette already, else this function will fail.
	
	\return
		1 on success

	It is impossible to resize a palette once created, so choose the number of colors carefully.
	
	To allocate the maximum number of colors for each image, use 1 << ul_paletteSizes[imageFormat] as a palette color count.
	
	Important note: the location of the palette MUST be the same as the location of the image texture! If a texture is already loaded, the palette location will be
	automatically adjusted to match the location of the texture.
	
	Very important: To be used as textures, image dimensions must have a size power of two. The members sysSizeX and sysSizeY indicate the real dimension of data in memory.
*/
int ulCreateImagePalette(UL_IMAGE *img, int location, int palCount);

/** Converts a true color image (5550 or 5551) to a paletted format, creating a palette for it. A pointer to the new image is returned and the original image is left untouched. */
extern UL_IMAGE *ulConvertImageToPaletted(UL_IMAGE *imgOriginal, int newLocation, int newFormat);

/** Copies an image to Video RAM. It is necessary so that you can draw that image on the screen.
	
	However, the system will realize the image automatically if it's not already done before drawing it.
	
	Please note that when you create or load an image, it will be placed in RAM, and it's accessable by its texture and palette members. Once you've realized it, these pointers will become NULL and image will not be accessable anymore, except if you lock it (search for ulLockImage). */
int ulRealizeImage(UL_IMAGE *img);
/** Copies an image back to Main RAM.

	This function does the exact opposite of ulRealizeImage, so do it only if it has been realized before. The image and palette will be in RAM back again, so you can modify it. Realize the image again once finished with it, or
	wait for the system to do it automatically, but remember that it can cause flickering if done during a mid-game frame as discussed in the documentation!
*/
int ulUnrealizeImage(UL_IMAGE *img);

/** Deletes an image. The image can be in VRAM (realized) or in main RAM, it doesn't matter. */
void ulDeleteImage(UL_IMAGE *img);

/** @} */ // end of images_creation



/** @defgroup images_loading Loading images
	\brief Image loading support for various formats.

	Here are the approximative code sizes for currently supported formats:
		- JPG loading code: 7 kB
		- GIF loading code: 35 kB
		- PNG loading code: 135 kB

	You can choose between 2 alternatives:
		- Use gif for paletted images (up to 256 colors) and jpg for true color images (16 bits).
		- Use png for everything. Png decoding code is huge but png files take less space, so it may be a better solution in the long term.
    @{
*/

/** Loads a PNG file. You can pass an open virtual file, which can be open from everything (RAM, libFat, gbfs, ...).
	
	If your PNG contains a palette and the wanted pixelFormat is paletted, then it will use that palette, in the same order. The first color will be transparent.
	
	If your PNG doesn't contain a palette and the wanted pixelFormat is paletted, then a palette will be created from the source image, but it must not contain more than the total number of colors! The color key (ulSetTransparentColor) will be used as a transparent color.
	
	If the wanted pixelFormat is not paletted, then the image will be loaded directly, wether it contains a palette or not. The color key will be used for transparency if your pixel format is 5551, as well as the alpha channel defined in your PNG (0 - 127 = transparent, 128 - 255 = opaque).
 */
UL_IMAGE *ulLoadImagePNG(VIRTUAL_FILE *f, int location, int pixelFormat);
/** Loads a JPG file. Same remark as for loading PNG. The format must be 16 bits (5550 or 5551) and there is no transparency support. */
UL_IMAGE *ulLoadImageJPG(VIRTUAL_FILE *f, int location, int pixelFormat);
/** Loads a GIF file. Same remarks as for loading PNG. Your GIF file can have a transparent color set, which is not the first one. The palette colors will then be swapped so that this color becomes transparent. If your GIF has no transparent color, it searches for the color key and uses this one as transparent. If it's not found or you have not defined a color key, then it uses the first palette color as transparent. */
UL_IMAGE *ulLoadImageGIF(VIRTUAL_FILE *f, int location, int pixelFormat);

/** @} */ // end of images_loading


/** @defgroup images_drawing Drawing images
	\brief Some routines to draw your images.
    @{
*/
/** Draws an image, using its properties. */
void ulDrawImage(UL_IMAGE *img);
/** Draws an image, specifying its coordinates on the screen.

Important: the coordinates specified there will be set in the image itself, and will be left even after this routine has finished. Example:
	\code
img->x = img->y = 0;                //Set image coordinates to (0,0)
ulDrawImage(img);                   //Will be drawn at (0,0)
ulDrawImageXY(img, 10, 20);         //Will be drawn at (10,20)
ulDrawImage(img);                   //Will be drawn at (10,20)
	\endcode

	For this reason, you should not mix usage of ulDrawImage and ulDrawImageXY for a single image, else you may encounter vicious problems like
	objects mysteriously disappearing: in the example above, you could expect the second ulDrawImage to draw at (0,0) like the first one, but it will draw at (10,20) instead.
*/
static inline void ulDrawImageXY(UL_IMAGE *img, s16 x, s16 y)			{
   img->x = x;
   img->y = y;
	ulDrawImage(img);
}
   
//#define ulDrawImageXY(img, xpos, ypos)					({ (img)->x = xpos; (img)->y = ypos; ulDrawImage(img); })

/** @} */ // end of images_drawing


/** @defgroup images_working Working with images
	\brief Some basic useful routines when working with your images.
    @{
*/

/** Resets all properties of an image to the default.
	Useful if you do a lot of transformations to your image and you want to be sure they will not be left for the next drawing. */
void ulResetImageProperties(UL_IMAGE *img);

/** Defines the uniform tint of an image. */
#define ulSetImageTint(img, tint)						(img->tint1 = img->tint2 = img->tint3 = img->tint4 = tint)

/** Defines the coordinates of the image part to display.
	You can for example have a "sprite sheet" (very big image containing several sprites) and choose between them by selecting a small rectangular area as an image tile and draw it.
	
	\b Important: This command will reset the stretch factors of the image to the size of the tile. So, if you want your image to be zoomed, you need to stretch it again after having called this. */
#define ulSetImageTile(img, x0, y0, x1, y1)			({ (img)->offsetX0 = x0; (img)->offsetY0 = y0; (img)->offsetX1 = x1; (img)->offsetY1 = y1; (img)->stretchX = (x1) - (x0); (img)->stretchY = (y1) - (y0); })
/** Same as ulSetImageTile, except that you pass the tile size instead of bottom-right coordinates. */
#define ulSetImageTileSize(img, x0, y0, x1, y1)		({ (img)->offsetX0 = x0; (img)->offsetY0 = y0; (img)->offsetX1 = (x0) + (x1); (img)->offsetY1 = (y0) + (y1); (img)->stretchX = x1; (img)->stretchY = y1; })

/** Resets the internal tile coordinates so that the full image will be drawn on the screen. */
#define ulResetImageTile(img)								({ (img)->offsetX0 = 0; (img)->offsetY0 = 0; (img)->offsetX1 = (img)->sizeX; (img)->offsetY1 = (img)->sizeY; (img)->stretchX = (img)->sizeX; (img)->stretchY = (img)->sizeY; })

/** Mirrors the image horizontally.
	\param img
		Image you want to flip.
	\param mirrorState
		Set to 1 (true) to mirror horizontally, 0 (false) to disable mirroring.
 */
extern void ulMirrorImageH(UL_IMAGE *img, int mirrorState);

/** Mirrors the image vertically.
	\param img
		Image you want to flip.
	\param mirrorState
		Set to 1 (true) to mirror horizontally, 0 (false) to disable mirroring.
*/
extern void ulMirrorImageV(UL_IMAGE *img, int mirrorState);

/** @} */ // end of images_working


/** @defgroup image_adv Advanced
	\brief More advanced routines for manipulating images.
    @{
*/

/** Retrieves wether an image needs a palette or not based on its pixel format */
#define ulImageIsPaletted(img)   (img->format >= UL_PF_PAL5_A3 && img->format <= UL_PF_PAL3_A5)

/** Defines the rotation center of an image to the center of it. */
#define ulImageSetRotCenter(img)							((img)->centerX = ulAbs((img)->offsetX1 - (img)->offsetX0) >> 1, (img)->centerY = ulAbs((img)->offsetY1 - (img)->offsetY0) >> 1)

/** Locks an image so that you can access its contents in software. Returns a pointer to the image contents. It's only useful if your image is in VRAM, but you can call this function even if your image is in RAM, it's a safe way to access your image.
	
	You must provide the reason for which you want to lock your image: UL_LOCK_PIXELS (pixel data) or UL_LOCK_PALETTE (palette data). The corresponding pointer will be returned. You can lock both elements with 2 successive calls.
	
	Note: only one image can be locked at a time. Always unlock everything from an image before locking another one.
	
	Note 2: images should be locked for a very small time, especially if they're stored in VRAM, because this will also lock the video memory, making the GPU unable to read from it. If you're doing that during a render, the screen may display transparent bands due to a rendering failure.
*/
void *ulLockImage(UL_IMAGE *img, UL_LOCK_REASON lockReason);

/** Unlocks a locked image. Always unlock the your images shortly after having locked them! You must provide the same reason as the one you used when locking it.
	If you lock both elements of a single image, you should lock them at the same time, and also unlock them at the same time.

	Example:
	\code
void *tetxurepointer = ulLockImage(image, UL_LOCK_PIXELS);
void *palettepointer = ulLockImage(image, UL_LOCK_PALETTE);
[use your pointers]
ulUnlockImage(image, UL_LOCK_PALETTE);
ulUnlockImage(image, UL_LOCK_PIXELS);
	\endcode
*/
void ulUnlockImage(UL_IMAGE *img, UL_LOCK_REASON lockReason);

/** Return a pointer to the beginning of an image line pixel data. */
#define ulGetImageLineAddr(img,y)			((char*)((img)->texture) + (y)*(((img)->sysSizeX * ul_pixelWidth[(img)->format])>>3))
/** Return a pointer to the corresponding pixel of an image.

Please note that some image formats are not byte-boundary, like 2 or 4 bits formats. You'll have to so some more work to set a single pixel on
these images. */
#define ulGetImagePixelAddr(img,x,y)	((char*)((img)->texture) + ((((y)*(img)->sysSizeX + (x)) * ul_pixelWidth[(img)->format])>>3))

/** Returns the total size (in bytes) of an image. */
#define ulGetImageTotalSize(img)			(((img)->sysSizeX * (img)->sysSizeY * ul_pixelWidth[(img)->format]) >> 3)

/** Draws a single pixel on an image.
	\param pixelValue
		The raw pixel value.
			- A 16-bit color with alpha in 5551
			- A 15-bit color value without alpha in 5550
			- A 8-bit color palette index in PAL8
			- A 5-bit color palette index in PAL5_A3 with the 3 MSB set to the alpha value
			- A 3-bit color palette index in PAL3_A5 with the 5 MSB set to the alpha value

	Note that this function is not optimized for speed, but should be okay for most uses.
	If you need a very fast mean to do it, then you'll have to write your own renderer function, which will be able to draw several pixels at once depending on the image format.
*/
void ulSetImagePixel(UL_IMAGE *img, int x, int y, int pixelValue);
/** Returns the raw value of a pixel on an image. Same considerations as ulSetImagePixel apply.

	The return value will be a color if it's a 15 or 16-bit image, it will be a value (palette entry) in other cases.
*/
int ulGetImagePixel(UL_IMAGE *img, int x, int y);

/** Treats the first color palette as opaque. When enabled, image loading routines (GIF/PNG/...) will NEVER use the color 0 except if it's transparent (color key and so on). Values:
   	- 0: disabled (default), color 0 will not be used by loading routines if no color of the image matches the defined color key or if color keying is disabled. Only colors 1 to 3/15/255 will be used instead.
   	- 1: partially enabled, keeps the same palette order as loaded images. Thus, the first color of paletted PNG/GIF images will always appear as transparent, no matter their value.
		- 2: fully enabled: hardware will process color 0 as opaque, but it may cause problems because transparency may be rendered incorrectly in formats like UL_PF_PAL3_A5 (to be tested).
*/
extern u8 ul_firstPaletteColorOpaque;

/** @} */ // end of images_adv

/** @} */ // end of images



/** @defgroup adv_vertex Advanced vertex commands
	\brief Advanced vertex commands and depth management.
    @{
*/

/** Defines the depth of the next object to draw. */
#define ulSetDepth(z)					(ul_currentDepth = z)
/** Retreives the current depth. Useful when the AutoDepth mode is enabled. */
#define ulGetDepth()						ul_currentDepth

/** Set whether you want to increment the depth of objects automatically. Enabled by default.
	\param enable
		0 = disable, 1 = enable. Do not set to any other value, else priority problems can and will appear.
	
	- When enabled, depth of objects will automatically be incremented so that the first drawn object is at the bottom and the last one is on top of all others. A typical platformer scene render could start with a sky, then with mountains, then with ground, character & objects, and finally the HUD (score, time, etc.).
	- When disabled, the depth will stay the same and the default DS priority will be used: the first object will appear on top of all others, then the 2nd, ... until the last, which is in the background.
*/
//Incrémente automatiquement la priorité de façon à ce que les objets dessinés en dernier soient les premiers affichés. 1 = actif, le dernier objet affiché est devant, 0 = inactif, le dernier affiché est derrière. Ne pas mettre d'autre valeur!
#define ulSetAutoDepth(enable)		(ul_autoDepth = enable)

/** Begins to draw a new 2D/3D object.
	\param vtype
		Defines the type of object you want to draw.
		- GL_TRIANGLES: individual triangles (3 vertices)
		- GL_QUADS: individual quadliterals (4 vertices)
		- GL_TRIANGLE_STRIP: stripped triangles (3 vertices + 1 per linked triangle)
		- GL_QUAD_STRIP: stripped quads (4 vertices + 2 per linked quad)

	Lines are drawn as a flat triangles. That is, to draw a line from (x0,y0) to (x1,y1), you can do this:
	\code
ulVertexBegin(GL_TRIANGLES);
ulVertexXY(x0, y0);
ulVertexXY(x1, y1);
ulVertexXY(x1, y1);
ulVertexEnd();
	\endcode
	If you want to know how GL_TRIANGLE_STRIP or GL_QUAD_STRIP works, here is a small definition taken from gbatek: http://nocash.emubase.de/gbatek.htm
	\code
	Separate Tri.     Triangle Strips   Line Segment
	v0                 v2___v4____v6
	|\      v3         /|\  |\    /\     v0    v1
	| \     /\      v0( | \ | \  /  \     ------
	|__\   /__\        \|__\|__\/____\         v2
	v1 v2 v4  v5       v1   v3  v5   v7
	
	
	Separate Quads          Quadliteral Strips         Prohibited Quads
	 v0__v3                 v0__v2____v4     v10__    v0__v3     v4
	  /  \   v4____v7        /  \     |\ _____ / /v11   \/       |\
	 /    \   |    \        /    \    | |v6 v8| /       /\     v5| \
	/______\  |_____\      /______\___|_|_____|/       /__\     /___\
	v1    v2  v5    v6     v1    v3  v5 v7   v9       v2   v1   v6   v7
	\endcode
*/
#define ulVertexBegin(vtype)				( GFX_BEGIN = vtype )
/** Call this after you've finished to draw your object. Look at the examples above for more informations. */
#define ulVertexEnd()						( GFX_END = 0 )

/** You MUST call this after you've terminated to draw any object on the screen. It is necessary to get the auto-depth feature working. */
#define ulVertexHandleDepth()				( ul_currentDepth += ul_autoDepth )

/** Issues a 2D vertex command.
	\param u, v
		Texture coordinates
	\param x, y
		Vertex coordinates

	You should first select a texture using ulSetTexture. After your 2D object has finished drawing, make sure to call the auto-increment handling routine!
	Here is a code sample for a simple drawing routine:
	\code
void drawAnImage(UL_IMAGE *img)
{
	ulSetTexture(img);

	//Begins drawing quadliterals
	ulVertexBegin(GL_QUADS);

	//Drawing order for a quad is: top-left, bottom-left, bottom-right, top-right.
	ulVertexUVXY(img->offsetX0, img->offsetY0, img->x, img->y);
	ulVertexUVXY(img->offsetX0, img->offsetY1, img->x, img->y + img->stretchY);
	ulVertexUVXY(img->offsetX1, img->offsetY1, img->x + img->stretchX, img->y + img->stretchY);
	ulVertexUVXY(img->offsetX1, img->offsetY0, img->x + img->stretchX, img->y);

	//End there. You could also continue and draw other quads (issue 4 new vertex commands)
	ulVertexEnd();

	//Auto-increment depth
	ulVertexHandleDepth();
	return;
}
	\endcode
*/
#define ulVertexUVXY(u, v, x, y)			({ GFX_TEX_COORD = ((u16)(v)) << 20 | ((u16)(u)) << 4;			\
														GFX_VERTEX16 = (((u16)(y)) << 16) | ((u16)(x)); \
														GFX_VERTEX16 = ul_currentDepth; })

/** Issues a 2D vertex command.
	\param x, y
		Vertex coordinates

	Same remarks as for ulVertexUVXY, except that there is no texture here. You should disable texturing when doing that!
	Here is a code sample for a simple drawing routine:
	\code
void drawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, UL_COLOR color)
{
	//We're drawing a simple colored triangle (untextured)
	ulDisableTexture();

	//Begins drawing quadliterals
	ulVertexBegin(GL_TRIANGLES);
	
	//You can define the color of each vertex before issuing the vertex command, or once for all, like here. If the vertices have different colors, a gradient will appear between each corner.
	ulVertexColor(color);

	//Draw our triangle (3 vertices)
	ulVertexXY(x0, y0);
	ulVertexXY(x1, y1);
	ulVertexXY(x2, y2);

	//End our drawing.
	ulVertexEnd();

	//Don't forget to auto-increment depth
	ulVertexHandleDepth();
	return;
}
	\endcode
*/
#define ulVertexXY(x, y)					({ GFX_VERTEX16 = (((u16)(y)) << 16) | ((u16)(x)); \
														GFX_VERTEX16 = ul_currentDepth; })
/** Set the next vertex color. In a 2D or 3D object, each vertex can have its own color, just call this before issuing the vertex command to set its color. */
#define ulVertexColor(color)				( GFX_COLOR = color )

/** Sets the current image as a texture so you can draw on the screen by issuing vertex commands. This function will realize the image if it's not already done. */
void ulSetTexture(UL_IMAGE *img);

/** Disables texturing. Use it if you want to draw a coloured or gradient-filled object. */
#define ulDisableTexture()		(GFX_TEX_FORMAT = 0)

/** @} */ // end of adv_vertex

/** Defines the transparency and grouping of objects. Everything drawn next to this command will use those alpha parameters. You can then
	restore the original state (opaque) by writing ulSetAlpha(UL_FX_DEFAULT, 0, 0).
	\param effect
		can be UL_FX_DEFAULT for opaque or UL_FX_ALPHA for semi-transparency (alpha blending).
	\param coeff
		blending coefficient: 0 = wireframe, 1 = nearly transparent, ..., 31 = nearly opaque.
		Has no effect with UL_FX_DEFAULT.
	\param polygroup
		defines the polygon group of next objects. Objects with different polygroups will be blended together, while objects with the same
		polygroup will be merged and drawn as a single layer. In each group, the first object drawn will have the highest priority.
	
	Example:
	\code
//Default (opaque) objects always have 0 as an ID. Any other value may cause garbage on real DS.
ulSetAlpha(UL_FX_DEFAULT, 0, 0);
//Draw a blue sky background
ulDrawFillRect(0, 0, 256, 192, RGB15(0, 16, 31));
//Set alpha to 1/2, set ID to 1 so that actual objects will be blended with the background (ID = 0)
ulSetAlpha(UL_FX_ALPHA, 16, 1);
//Draw a semi transparent image
ulDrawImage(anImage);
//Restore to default (opaque)
ulSetAlpha(UL_FX_DEFAULT, 0, 0);
	\endcode
*/
void ulSetAlpha(UL_SPECIAL_EFFECT effect, int coeff, int polygroup);

/** Set the main LCD, the one which is currently controlled by µLibrary.
	\param position
		- 0 = touchpad
		- 1 = top screen

You can also use the libnds macro lcdSwap if you simply want to swap the LCDs.

Note: By default, µLibrary controls the top screen.
*/
static inline void ulSetMainLcd(int position)			{
   if (position == 0)
   	REG_POWERCNT &= ~POWER_SWAP_LCDS;
   else
   	REG_POWERCNT |= POWER_SWAP_LCDS;
}

/** Returns 1 if µLibrary is currently drawing to the top screen, 0 if it is on the touchpad. */
static inline int ulGetMainLcd()			{
	return REG_POWERCNT & POWER_SWAP_LCDS;
}

/** Does a capture. */
void ulSetRegCapture(bool enable, uint8 srcBlend, uint8 destBlend, uint8 bank, uint8 offset, uint8 size, uint8 source, uint8 srcOffset);

/** @} */ // end of drawing

#ifdef __cplusplus
}
#endif

#endif

