/*! \file map.h
    \brief
    	Support for maps in µLibrary.
*/

#ifndef __UL_MAP_H__
#define __UL_MAP_H__

#ifdef __cplusplus
extern "C" {
#endif

/** @defgroup maps Maps

	Support for maps in µLibrary.
	@{
*/

/**
	\brief Map type.

Once created, you can change the map contents to make it scroll for example. */
typedef struct		{
   //Source image (do not access).
	UL_IMAGE *img;
   //Map data (do not access).
	void *map;
   /** Current horizontal scrolling value in pixels. */
	s16 scrollX;
   /** Current vertical scrolling value in pixels. */
	s16 scrollY;
   //Tile dimensions (do not access).
	s16 tileX, tileY;
   //Calculated upon the first drawing. Do not access.
	s16 drawSizeX, drawSizeY;
   //Map dimensions (do not access)
	s16 mapSizeX, mapSizeY;
   //Map format (do not access)
	int format;
} UL_MAP;

/** Creates a new map.
	\param img
		Source image, containing the tileset for the map. Tiles are placed from left to right, and from top to bottom by lines. A simple tileset
		containing 8 tiles of 16x16 each could be 128x16, 64x32, 16x128, etc.
		The width of the image MUST be a power of two and CANNOT exceed the maximum width of DS textures (2048?).
		If so, place some tiles on the next line.
	\param map_data
		Pointer to the raw map data. It's just a table whose size is mapSizeX * mapSizeY and currently each table entry is a 16 bits integer.
	\param tileX, tileY
		Size of a tile in the tileset. In the above example, it would be 16 and 16. Please note that they MUST be a power of two!
	\param mapSizeX, mapSizeY
		Dimensions of the map (x = width, y = height).
	\param map_format
		Currently supported map formats are:
			- UL_MF_U16: 16 bits entries. Bits 0-15: tile number. This format allows a large number of tiles.
			- UL_MF_U16_GBA: 16 bits entries. Bits 0-9: tile number, 10: mirror H, 11: mirror V, 12-15: palette number. Compatible with GBA/NDS standard maps.

	Note: The block n° 0 is ALWAYS treated as a transparent tile!
	Even if you've put a non transparent tile in the tileset for this entry, it will not be drawn at all!
	
	Namely, GBA Graphics has an option to generate a map with the first tile being always transparent.
	Some other editors may do it as well, and in any way, the only thing you've got to care about is that the first tile in the tileset is transparent.
	
	Note: The tileset's tint1 member is used to tint the ENTIRE map, no gradient is made!
*/
extern UL_MAP *ulCreateMap(UL_IMAGE *img, void *map_data, int tileX, int tileY, int mapSizeX, int mapSizeY, int map_format);

/** Deletes a map. Call this once you've finished with a map.
	\param map
		Map previously created with ulCreateMap.
*/
extern void ulDeleteMap(UL_MAP *map);

/** Draws a map on the screen.

Please note that drawing a map requires a large number of polygons (one for each tile) to be drawn on the screen, which will fill the vertex
memory a lot. A single fullscreen 8x8 scrolled map (33x25) already requires 825 quads, which is about 55% the total available memory!
To spare some memory, you should always use tiles that are at least 16x16 (15% memory this time) and use if possible null map entries (transparent),
which are simply skipped. */
extern void ulDrawMap(UL_MAP *m);

/** Map formats */
enum UL_MAP_FORMATS {
  	UL_MF_U16 = 0,					//!< 16 bits per entry
  	UL_MF_U16_GBA,					//!< 16 bits per entry, 10 for tile, 2 for mirror, 4 for palette
};

/** @} */ // end of maps

#ifdef __cplusplus
}
#endif

#endif

