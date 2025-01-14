# µLibrary

## 1. Introduction

This is a library that provides functions to create 2D games using the 3D engine
of the Nintendo DS. The 3D GPU is more flexible than the 2D GPU:

- You can blend sprites with each other.
- You can display up to 1536 sprites (vs 128 of the 2D GPU).
- You can rotate and scale your sprites without restrictions.
- You can use bigger sprites (up to 2048x2048 vs 64x64).
- You can draw primitives like lines, rectangles, etc, allowing nice effects
  like in Yoshi's island for example. :)

The render method is similar to a sheet of paper: you first draw a background,
then put some mountains, then some trees, some characters and so on: you draw
your objects in the order they should appear on the screen (the first is behind,
the last one is over the others).

The problem of using the 3D GPU is clear: you can only use one screen at a time
(or 2 screens but at 30 FPS). However, µLibrary is fully compatible with PALib
and you can use it to handle the second screen at 60 FPS. It's a good solution
if you do not plan to use the second screen intensively: displaying a BG with
some sprites and get the stylus state could be enough, and you can concentrate
on the main screen which is driven by µLibrary.

Here is a small list of features of µLibrary:

- Supported image formats: PNG, GIF, JPG
- Special image effects: stretching, tinting (4 corners), mirroring, rotation
  (with a defined center), selection of an image frame to display (just like on
  spritesheets).
- 18-bit render quality instead of 15-bit: provides 8 times more colors!
- Virtual file system: it is possible to load files independantly from the
  actual support (RAM, FAT, NitroFS are supported by default, but you can define
  your own). It allows you to create more easily software that are compatible
  with all existing flashcards.
- Untextured geometry (rectangles, gradients, lines, etc).
- Basic message box system.
- VideoGL wrapper for texture and palette loading in VRAM: it is now possible to
  load and unload things dynamically. Furthermore, it is more flexible (you can
  choose which banks you want to use for what, etc).
- Keypad and touchscreen handler namely with support of stylus speed and double
  click and support of autorepeated keys (menus for example).
- Includes 2 splash screens.
- Low level wrapper to draw primitives.
- Text system using the same font format as OSLib (development library for PSP).

Performance is good, one of the examples shows that an unoptimized C++ code that
draws 400 balls bouncing on the screen uses less than 15% of CPU...

A few examples are supplied, as well as a Doxygen documentation. There are also
two templates: one with PAlib and one without it.

## 2. Installation

You can install this library directly with ``wf-pacman`` by running:

```bash
wf-pacman -Sy blocksds-ulibrary
```

You can use µLibrary and [PAlib](https://github.com/AntonioND/palib) at the same
time (some examples require PAlib!). You can install it with this command:

```bash
wf-pacman -Sy blocksds-palib
```

If you want to build µLibrary from source instead, simply clone this repository
and run this to build and install the library in your BlocksDS environment:

```bash
make -j`nproc` install
```

## 3. Examples

Once you have installed the library, go to the folder of any example or template
and run:

```bash
make
```

Note that the examples and templates that use PAlib won't work because there
isn't a working up-to-date port of PAlib to BlocksDS.

## 4. About

Programmed by Florian Brönnimann, aka Brunni: http://brunni.dev-fr.org

Original website: https://web.archive.org/web/20110725231708/http://brunni.dev-fr.org/index.php?page=ndssoft_ulib

Official forum: http://www.playeradvance.org/forum/forumdisplay.php?f=103

Port to BlocksDS by Antonio Niño Díaz, aka AntonioND.
