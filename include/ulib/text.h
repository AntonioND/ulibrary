/// @file text.h
///
/// @brief Text support with support for loading OldSchool Library fonts (.oft).

#ifndef __UL_TEXT_H__
#define __UL_TEXT_H__

#ifdef __cplusplus
extern "C" {
#endif

/// @defgroup text Text
///
/// Text support with support for loading OldSchool Library fonts (.oft).
///
/// @{

/// Font information type
typedef struct
{
    void *fontdata;            ///< Character image data
    short pixelFormat;         ///< 1 = 1 bit (default)
    unsigned char *charWidths; ///< Width of characters
    int charWidth;             ///< Default char width (if charWidths is NULL)
    int charHeight;            ///< Height of characters (constant)
    int lineWidth;             ///< Number of bytes of data per line
    int recentrage;            ///< Added to text positions for drawing text (recentering)

    /// Space added between the characters on the texture (allows to make
    /// characters graphically bigger than what indicated by charWidths)
    unsigned char addedSpace;

    unsigned short paletteCount; ///< Palette count
    unsigned long *paletteData;  ///< Palette data
} UL_FONTINFO;

/// Font loaded into memory
typedef struct
{
    UL_IMAGE *img;                 ///< Character image data
    unsigned char *charWidths;     ///< Width of characters
    unsigned short *charPositions; ///< Positions of characters in the texture (bits: y:7, x:9)
    int isCharWidthConstant;       ///< To know wether we must free charWidth in the end
    int charWidth;
    int charHeight;                ///< Height of characters (constant)
    int recentrage;                ///< Added to text positions for drawing text (recentering)

    /// Space added between the characters on the texture (allows to make
    /// characters graphically bigger than what indicated by charWidths)
    unsigned char addedSpace;
} UL_FONT;

/// Header of a .oft file (Oslib FonT)
typedef struct
{
    char strVersion[12];         ///< "OSLFont v01"
    unsigned char pixelFormat;   ///< Number of bits per pixel (1 = 1 bit, default)
    unsigned char variableWidth; ///< If true, the first 256 bytes of data specify the character widths
    int charWidth, charHeight;   ///< Mean character sizes (used for the console)
    int lineWidth;               ///< Number of bytes of data per line

    /// Space added between the characters on the texture (allows to make
    /// characters graphically bigger than what indicated by charWidths)
    unsigned char addedSpace;

    unsigned short paletteCount; ///< Text palette data
    unsigned char reserved[29];  ///< Must be null (reserved)
} UL_FONT_FORMAT_HEADER;

/// Sets the current font.
#define ulSetFont(f) (ul_curFont = f)

// Texture width for character image data (when loaded). 512 is the maximum
// width on PSP and it's okay on DS (2048 IIRC).
#define UL_TEXT_TEXWIDTH 512

// Bit shift (1 << 9 == 512)
#define UL_TEXT_TEXDECAL 9

// Computes the actual position of a character in the texture and returns it as
// a dual argument form, for example: 1, 10.
#define UL_TEXT_CHARPOSXY(f, i) \
    (f)->charPositions[i]&(UL_TEXT_TEXWIDTH-1), \
    ((f)->charPositions[i]>>UL_TEXT_TEXDECAL) * (f)->charHeight

/// Initializes the text system with the default supplied font (2 kB).
///
/// Can be called several times, it will then only set the default font.
void ulInitText();

/// Creates a new font based on a FONTINFO header.
///
/// Not very useful, as you should load fonts from a whole file.  The only use
/// it currently has is for the default font, which is embedded in the source
/// code (but even there, you could only put the binary data of the file in a
/// simple table and use a virtual file to open and load it).
UL_FONT *ulCreateFont(UL_FONTINFO *fi);

/// Loads a font from an open virtual file.
UL_FONT *ulLoadFont(VIRTUAL_FILE *f);

/// Draws a character to the specified positions.
void ulDrawChar(int x, int y, unsigned char c);

/// Draws a string to the specified positions.
///
/// Note: Drawing an entire string is faster than drawing characters
/// individually.
void ulDrawString(int x, int y, const char *str);

// Console output is currently not available.
// void ulConsolePrint(const char *str);

/// Sets the text color.
void ulSetTextColor(UL_COLOR color);

// Unavailable, no text background is ever drawn on DS because it would require
// an additional polygon for each character...
// void ulSetBkColor(UL_COLOR color);

/// Draws a text box.
///
/// @param x0, y0, x1, y1
///     Rectangle where the text should be placed on. Text will automatically be
///     word-wrapped (words are not cut in half at the end of a line) so make
///     sure to let enough horizontal space else it will look ugly.
/// @param text
///     The text you want to draw. Currently, there is no special format tag
///     supported.
/// @param format
///     For future use. Set it to zero for now.
///
/// Also there, it should be faster to draw a text box using this method than
/// doing it by yourself and drawing individual characters.
void ulDrawTextBox(int x0, int y0, int x1, int y1, const char *text, int format);

void ulDeleteFont(UL_FONT *f);

/// Draws text using printf format somewhere on the screen.
///
/// @param x,y
///     Positions where to draw the text
/// @param format
///     Printf-like string (ex: "%i", someInteger)
#define ulPrintf_xy(x, y, format...) ({ \
        char __str[1000]; \
        sprintf(__str , ##format); \
        ulDrawString(x, y, __str); \
    })

/// Returns the size of a string using the current active font.
int ulGetStringWidth(const char *str);

/// Returns the height of a text box using the current active font.
///
/// @param width
///     Text box width (x1 - x0 in ulDrawTextBox)
/// @param maxHeight
///     Height limit. If set to 0, there will be no limit.
/// @param text
///     Text.
/// @param format
///     Set it to 0.
int ulGetTextBoxHeight(int width, int maxHeight, const char *text, int format);

/// Current console positions (unused)
extern int ul_consolePosX, ul_consolePosY;

/// Currently selected font.
extern UL_FONT *ul_curFont;

/// Default LCD font (loaded upon call to ulInitConsole()).
extern UL_FONT *ul_lcdFont;

extern UL_FONTINFO ul_lcdFontInfo;

/// @}

#ifdef __cplusplus
}
#endif

#endif // __UL_TEXT_H__
