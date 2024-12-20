/// @file loading_utility.h
///
/// @brief Utility functions to load files more easily in µLibrary.

#ifndef __UL_LOADINGUTILITY_H__
#define __UL_LOADINGUTILITY_H__

#ifdef __cplusplus
extern "C" {
#endif

/// @defgroup loadutil Loading utility
///
/// Utility functions to load files more easily in µLibrary.
///
/// @{

extern int ul_loadUtilActiveSource;

/// Retrieves the active source for this utility.
static inline int ulGetLoadUtilitySource()
{
    if (ul_loadUtilActiveSource >= 0)
        return ul_loadUtilActiveSource;
    else
        return VirtualFileSourcesNb - 1;
}

/// Defines the default source for files open via this utility.
///
/// Note that by default, the last initialized source is used, so if you do
/// nothing it will be memory, if you initialize libFat or NitroFS it will be
/// this one.
static inline int ulSetLoadUtilitySource(int source)
{
    int currentSource = ulGetLoadUtilitySource();
    ul_loadUtilActiveSource = source;
    return currentSource;
}

/// @ingroup images_loading
///
/// Load directly from a file. If the file is a filename for FAT or NitroFS, the
/// size should be 0.  If you're loading from memory, then fileName is a pointer
/// to the memory address and fileSize its size.
///
/// See the Loading utility section for more informations.
UL_IMAGE *ulLoadImageFilePNG(const char *fileName, int fileSize, int flags,
                             int pixelFormat);

/// @ingroup images_loading
///
/// Same but for JPG.
UL_IMAGE *ulLoadImageFileJPG(const char *fileName, int fileSize, int flags,
                             int pixelFormat);

/// @ingroup images_loading
///
/// Same but for GIF.
UL_IMAGE *ulLoadImageFileGIF(const char *fileName, int fileSize, int flags,
                             int pixelFormat);

/// @ingroup text
///
/// Loads a font from a file.
UL_FONT *ulLoadFontFile(const char *fileName, int fileSize);

/// @}

#ifdef __cplusplus
}
#endif

#endif // __UL_LOADINGUTILITY_H__
