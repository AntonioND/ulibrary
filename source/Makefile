# Makefile for uLibrary
# Copyright (C) 2007 Brunni
# For conditions of distribution and use, see copyright notice in LICENSE (EN).RTF

# To compile, type:
#    make 
# To install, type:
#    make install

#---------------------------------------------------------------------------------
# Main target
#---------------------------------------------------------------------------------
TARGET=libul.a

#---------------------------------------------------------------------------------
# TOOLS
#---------------------------------------------------------------------------------
PREFIX=arm-eabi-
CC=$(PREFIX)gcc
AR=$(PREFIX)ar rc
RANLIB=$(PREFIX)ranlib
TAR=tar
SHELL=/bin/sh
EXE=
PATH 		:= $(DEVKITARM)/bin:$(PATH)

#---------------------------------------------------------------------------------
# options for code generation
#---------------------------------------------------------------------------------
ARCH	:=	-mthumb-interwork
# note: arm9tdmi isn't the correct CPU arch, but anything newer and LD
# *insists* it has a FPU or VFP, and it won't take no for an answer!
#CFLAGSDEFAULT	:=	-mcpu=arm9tdmi -mtune=arm9tdmi -fomit-frame-pointer\
#		-ffast-math \
#		$(ARCH)

CFLAGSDEFAULT := -mcpu=arm946e-s -mtune=arm946e-s -fomit-frame-pointer\
		-ffast-math \
		$(ARCH)

INCLUDE := 

CFLAGSDEFAULT	+=	$(INCLUDE) -DARM9 -I$(DEVKITPRO)/libnds/include -I$(CURDIR) -I$(DEVKITPRO)/PAlib/include/nds
ASFLAGS	:=	-g $(ARCH)
CFLAGS = -g -Wall -O2 $(CFLAGSDEFAULT)
CFLAGSOS = -g -Wall -Os $(CFLAGSDEFAULT)

#---------------------------------------------------------------------------------
# options for install
#---------------------------------------------------------------------------------
INSTALLDIR =$(DEVKITPRO)/libnds
INSTALL_INCLUDEDIR =${INSTALLDIR}/include/uLib
INSTALL_LIBDIR = ${INSTALLDIR}/lib

#---------------------------------------------------------------------------------
# Objects to link
#---------------------------------------------------------------------------------
OBJS = ulib.o drawing.o glWrapper.o \
	map.o text.o \
	vfile/VirtualFile.o vfile/vfsLibFat.o vfile/vfsGBFS.o vfile/ulReadEntireFileToMemory.o \
	texVramManager.o texPalManager.o \
	libLoadPng.o jpeg/gba-jpeg-decode.o libLoadJpg.o \
	libLoadGif.o gif/dev2gif.o gif/dgif_lib.o gif/egif_lib.o gif/gif_err.o gif/gif_font.o gif/gifalloc.o \
	keys.o \
	image/ulConvertImageToPaletted.o image/ulDrawImage.o image/ulCreateImageFromTexture.o image/ulCreateImagePalette.o image/ulDrawFillRect.o image/ulDrawLine.o image/ulDrawRect.o image/ulDrawGradientRect.o image/ulSetImagePixel.o image/ulGetImagePixel.o \
	image/lock_unlock_image.o image/mirror_h_v.o image/ulUnrealizeImage.o \
	messagebox.o textSize.o \
	loadutil/loading_utility.o loadutil/ulLoadImageFilePNG.o loadutil/ulLoadImageFileJPG.o loadutil/ulLoadImageFileGIF.o loadutil/ulLoadFontFile.o \
	splash/ulShowSplashScreen1.o splash/ulShowSplashScreen2.o

TARGET_HEADER = drawing.h glWrapper.h keys.h loading_utility.h map.h messagebox.h text.h ulib.h VirtualFile.h

#---------------------------------------------------------------------------------
# Make target
#---------------------------------------------------------------------------------
all: $(TARGET) install

$(TARGET): $(OBJS)
	$(AR) $@ $(OBJS)
	-@ ($(RANLIB) $@ || true) >/dev/null 2>&1

#---------------------------------------------------------------------------------
# Specifique targets
#---------------------------------------------------------------------------------
libLoadGif.o: libLoadGif.c
	$(CC) $(CFLAGSOS) -c $< -o $@

gif/dev2gif.o: gif/dev2gif.c
	$(CC) $(CFLAGSOS) -c $< -o $@

gif/dgif_lib.o: gif/dgif_lib.c
	$(CC) $(CFLAGSOS) -c $< -o $@

gif/egif_lib.o: gif/egif_lib.c
	$(CC) $(CFLAGSOS) -c $< -o $@

gif/gif_err.o: gif/gif_err.c
	$(CC) $(CFLAGSOS) -c $< -o $@

gif/gif_font.o: gif/gif_font.c
	$(CC) $(CFLAGSOS) -c $< -o $@

gif/gifalloc.o: gif/gifalloc.c
	$(CC) $(CFLAGSOS) -c $< -o $@

libLoadPng.o: libLoadPng.c
	$(CC) $(CFLAGSOS) -c $< -o $@
	
vfile/vfsLibFat.o: vfile/vfsLibFat.c
	$(CC) $(CFLAGSOS) -c $< -o $@

vfile/vfsLibGBFS.o: vfile/vfsLibGBFS.c
	$(CC) $(CFLAGSOS) -c $< -o $@

vfile/ulReadEntireFile.o: vfile/ulReadEntireFile.c
	$(CC) $(CFLAGSOS) -c $< -o $@

messagebox.o: messagebox.c
	$(CC) $(CFLAGSOS) -c $< -o $@

textSize.o: textSize.c
	$(CC) $(CFLAGSOS) -c $< -o $@

clean:
	rm -f *.o $(TARGET)
	rm -f gif/*.o
	rm -f jpeg/*.o
	rm -f image/*.o
	rm -f vfile/*.o
	rm -f loadutil/*.o
	rm -f splash/*.o

install: $(TARGET)
	-@ mkdir -p $(INSTALL_INCLUDEDIR)>/dev/null 2>&1
	-@ mkdir -p $(INSTALL_LIBDIR)>/dev/null 2>&1
	cp $(TARGET_HEADER) $(INSTALL_INCLUDEDIR)
	cp $(TARGET) libpng.a libz.a $(INSTALL_LIBDIR)

