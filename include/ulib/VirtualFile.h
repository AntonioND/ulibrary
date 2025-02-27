/// @file VirtualFile.h
///
/// @brief Virtual File support for µLibrary.
///
/// This API is meant to be an universal mean to manipulate every file source
/// possible as you can define your own.

#ifndef __UL_VIRTUALFILE_H__
#define __UL_VIRTUALFILE_H__

#ifdef __cplusplus
extern "C" {
#endif

/// @defgroup virtualfile Virtual Files
///
/// Virtual File support for µLibrary.
///
/// This API is meant to be an universal mean to manipulate every file source
/// possible as you can define your own.
///
/// @{

/// Virtual File type.
typedef struct
{
    /// User data for IO processing (usually a pointer to data, FILE*, usw.)
    void *ioPtr;

    /// Virtual file type (source number.
    u16 type;

    /// Internal variables for memory-based (RAM / ROM) sources
    int offset, maxSize;
} VIRTUAL_FILE;

/// Enumeration describing the available file open modes.
///
/// Please note that some sources do not support some modes like READWRITE or
/// WRITE, in this case they'll fail when an attempt to open a file in one of
/// these modes is made. The resulting file returned by VirtualFileOpen will be
/// NULL.
typedef enum VF_OPEN_MODES {
    VF_O_READ,      ///< Read only
    VF_O_READWRITE, ///< Read & Write
    VF_O_WRITE      ///< Write only
} VF_OPEN_MODES;

/// Structure of a Virtual File Source.
typedef struct
{
    /// Open a file.
    ///
    /// Return 1 if anything went well, or 0 to throw an error (the opening will
    /// be cancelled and NULL will be returned to the user).
    int (*fOpen)(void *param1, int param2, int type, VF_OPEN_MODES mode, VIRTUAL_FILE* f);

    /// Close a file.
    ///
    /// Return 1 if anything went well, 0 to throw an error.
    int (*fClose)(VIRTUAL_FILE *f);

    /// Read in a file.
    ///
    /// Returns the number of bytes effectively read.
    int (*fRead)(void *ptr, size_t size, size_t n, VIRTUAL_FILE* f);

    /// Write in a file
    ///
    /// Returns the number of bytes effectively written.
    int (*fWrite)(const void *ptr, size_t size, size_t n, VIRTUAL_FILE* f);

    /// Read a single character.
    ///
    /// Returns the next character (byte) in the file.
    int (*fGetc)(VIRTUAL_FILE *f);

    /// Write a single character
    ///
    /// Writes a single character. Returns the character value if anything went
    /// well, -1 else.
    int (*fPutc)(int caractere, VIRTUAL_FILE *f);

    /// Read a string
    ///
    /// Reads a string to the buffer pointed to by str, of a maximum size of
    /// maxLen. Returns a pointer to the read string (str in general).  Reading
    /// stops to the next carriage return found (\\n). The routine should handle
    /// correctly the following sequences by reading them entirely: \\r, \\r\\n,
    /// \\n. If a \\r is found, you should read the following byte and rewind
    /// one byte behind if it's not a \\n.  If you cannot afford a rewind, then
    /// keep the next character in cache and return it to the next read.
    char* (*fGets)(char *str, int maxLen, VIRTUAL_FILE *f);

    /// Write a string
    ///
    /// Writes an entire string to the file.
    void (*fPuts)(const char *s, VIRTUAL_FILE *f);

    /// Moving in the file
    ///
    /// Sets the current file position and returns the old one. The whence
    /// parameter uses the same values as stdio (SEEK_SET, SEEK_CUR, SEEK_END).
    int (*fSeek)(VIRTUAL_FILE *f, int offset, int whence);

    /// End of file
    ///
    /// Returns true (1) if it's the end of the file, false (0) else.
    int (*fEof)(VIRTUAL_FILE *f);

} VIRTUAL_FILE_SOURCE;

/// Virtual file list item. Used for RAM based devices.
typedef struct
{
   const char *name; ///< Virtual file name
   void *data;       ///< RAM data block
   int size;         ///< Block data size

   /// Associated source (e.g. &VF_MEMORY).
   ///
   /// Don't forget the &, which is there so you can pass a variable which is
   /// not known at compile time (virtual file sources are registered upon
   /// start, so the compiler doesn't know the ID it will be given in advance).
   int *type;
} UL_VIRTUALFILENAME;

// Initializes the virtual filesystem.
//
// Done by default by µLibrary, so there is no need to call it by yourself.
void VirtualFileInit();

/// Open a new file.
///
/// @param param1
///     Depends on the file source. By default:
///     - VF_MEMORY: pointer to your data
///     - VF_NITRO, VF_FILE: pointer to a string containing the file name
/// @param param2
///     Depends on the file source. By default:
///     - VF_MEMORY: total size of the memory block
///     - VF_NITRO, VF_FILE: 0
/// @param type
///     File type. By default, can be:
///     - VF_MEMORY: Read/write from a memory block.
///     - VF_FILE: Read from standard stdio routines (libfat). Requires a prior call to ulInitLibFat().
///     - VF_NITRO: Read from NitroFS. Requires a prior call to ulInitNitroFs().
/// @param mode
///     One of VF_OPEN_MODES.
VIRTUAL_FILE *VirtualFileOpen(void *param1, int param2, int type, VF_OPEN_MODES mode);

/// Closes an open file.
int VirtualFileClose(VIRTUAL_FILE *f);

/// @defgroup virtualfile_io I/O routines
///
/// Routines for reading / writing to a virtual file. Make sure to check the
/// Virtual File main page to know how to open files, etc.
///
/// @{

/// Writes in a file and returns the number of bytes effectively written.
#define VirtualFileWrite(ptr, size, n, f) \
        (VirtualFileGetSource(f)->fWrite(ptr, size, n, f))

/// Reads in a file and returns the number of bytes effectively read.
#define VirtualFileRead(ptr, size, n, f) \
        (VirtualFileGetSource(f)->fRead(ptr, size, n, f))

/// Reads a single character.
///
/// Returns the next character (byte) in the file.
#define VirtualFileGetc(f) \
        (VirtualFileGetSource(f)->fGetc(f))

/// Writes a single character.
///
/// Returns the character value if anything went well, -1 else.
#define VirtualFilePutc(caractere, f) \
        (VirtualFileGetSource(f)->fPutc(caractere, f))

/// Reads a string to the buffer pointed to by str, of a maximum size of maxLen.
///
/// Returns a pointer to the read string (str in general).
///
/// Reading stops to the next carriage return found (\\n, \\r\\n or \\r),
/// supporting files created by every OS (I think).
#define VirtualFileGets(str, maxLen, f) \
        (VirtualFileGetSource(f)->fGets(str, maxLen, f))

/// Writes a string to the file.
#define VirtualFilePuts(s, f) \
        (VirtualFileGetSource(f)->fPuts(s, f))

/// Sets the current file position and returns the old one.
///
/// The whence parameter uses the same values as stdio (SEEK_SET, SEEK_CUR,
/// SEEK_END).
#define VirtualFileSeek(f, offset, whence) \
        (VirtualFileGetSource(f)->fSeek(f, offset, whence))

/// Returns true (1) if it's the end of the file, false (0) else.
#define VirtualFileEof(f) \
        (VirtualFileGetSource(f)->fEof(f))

/// @}

/// Adds a new file source to the virtual file system.
///
/// @param vfs
///     Must be a pointer to a valid VIRTUAL_FILE_SOURCE interface containing
///     all your functions for handling the file source.
/// \return
///     Returns the identifier of your source or -1 if it has failed. You can
///     then use this ID as a file type (parameter for VirtualFileOpen).
int VirtualFileRegisterSource(VIRTUAL_FILE_SOURCE *vfs);

/// Registers a file list for RAM based devices (such as VF_MEMORY).
///
/// This way you can make a virtual file driver for files in RAM and then easily
/// switch from a libFat, NitroFS or RAM system, only by speficying file names
/// when loading.
///
/// @param vfl
///     List of files (each file is a UL_VIRTUALFILENAME item)
void ulSetVirtualFilenameList(UL_VIRTUALFILENAME *vfl, int numberOfEntries);

/** Call this function in your virtual file source OPEN handler, if it's a RAM based device and param2 == 0 (means null size, impossible).
It will return a UL_VIRTUALFILENAME where you can get a pointer to the data and their size. Note that the return value can be NULL if the file has not been found or an error occured (e.g. fname is NULL). */
UL_VIRTUALFILENAME *ulFindFileInVirtualFilenameList(const char *fname, int type);

// Maximum number of sources
#define VF_MAX_SOURCES 16

// Gets a pointer to the virtual file source associated to a file
#define VirtualFileGetSource(vf) (VirtualFileSources[(vf)->type])

// List of virtual file sources
extern VIRTUAL_FILE_SOURCE *VirtualFileSources[VF_MAX_SOURCES];
extern int VirtualFileSourcesNb;
extern UL_VIRTUALFILENAME *ul_virtualFileList;
extern int ul_virtualFileListNumber;

/// Reads an entire file to memory and returns a pointer to the memory block.
///
/// The block memory usage is stepped by 4 kB, so even a 1 kB file will take 16
/// kB, so this function is not recommended for opening a lot of small files.
/// The bloc must be freed (using free) once you've finished with it!
///
/// @param f
///     Pointer to an open virtual file.
/// @param size
///     Pointer to an integer that will contain the number of bytes read from
///     the file.
void *ulReadEntireFileToMemory(VIRTUAL_FILE *f, int *size);

// Source par défaut: mémoire
int vfsMemOpen(void *param1, int param2, int type, VF_OPEN_MODES mode, VIRTUAL_FILE* f);
int vfsMemClose(VIRTUAL_FILE *f);
int vfsMemWrite(const void *ptr, size_t size, size_t n, VIRTUAL_FILE* f);
int vfsMemRead(void *ptr, size_t size, size_t n, VIRTUAL_FILE* f);
int vfsMemGetc(VIRTUAL_FILE *f);
int vfsMemPutc(int caractere, VIRTUAL_FILE *f);
char *vfsMemGets(char *str, int maxLen, VIRTUAL_FILE *f);
void vfsMemPuts(const char *s, VIRTUAL_FILE *f);
int vfsMemSeek(VIRTUAL_FILE *f, int offset, int whence);
int vfsMemEof(VIRTUAL_FILE *f);
extern VIRTUAL_FILE_SOURCE vfsMemory;

/// @defgroup virtualfile_sources Virtual file sources
///
/// There are three virtual file sources available by default: memory, libfat
/// and NitroFS.
///
/// @{

/// Initializes LibFAT.
///
/// Crashes if no device supporting libfat is present.
///
/// You have to call this routine before you can work with files. libFat support
/// will be added to your code, eating something like 75 kB.
int ulInitLibFat();

/// Initializes NitroFs.
///
/// Returns 0 in case of success or -1 if it failed.
///
/// You have to call this routine before you can open any NitroFS file.
int ulInitNitroFs();

/// Read and write from memory.
///
/// Automatically registered when initializing µLibrary.
extern int VF_MEMORY;

/// Use libFat as a virtual file source.
///
/// Needs to call ulInitLibFat to use it. However, it will crash if no device
/// supporting libFat is present, so be careful.
///
/// If you want to create several versions, I suggest you to keep a global
/// variable that identifies the virtual file source you're using. In one
/// version, it could have the value of VF_NITRO, in another VF_FILE. At startup
/// you would just have to do:
/// ```
/// int myID;
///
/// // ...
///
/// #if defined(USE_NITROFS)
/// myID = ulInitNitroFs();
/// #elif defined(USE_LIBFAT)
/// myID = ulInitLibFat();
/// #endif
///
/// // ...
///
/// VIRTUAL_FILE *f = VirtualFileOpen("/test.txt", 0, myID, VF_O_READ);
///
/// // ...
/// ```
///
/// It could even be a choice proposed to the user at startup.
extern int VF_FILE;

/// Use NitroFS. Needs to call ulInitNitroFs to use that source.
extern int VF_NITRO;

/// @}

/// @}

#ifdef __cplusplus
}
#endif

#endif // __UL_VIRTUALFILE_H__
