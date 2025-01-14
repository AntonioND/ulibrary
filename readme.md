# µLibrary

## 1. Introduction

This is a library that provides functions to create 2D games using the 3D engine
of the Nintendo DS. It also provides utilities to load common file formats like
PNG, JPG and GIF. It can load files from FAT or NitroFS. It also lets the user
display simple text boxes.

## 2. Install

You can install this library directly with ``wf-pacman`` by running:

```bash
wf-pacman -Sy blocksds-ulibrary
```

If you want to build it from source instead, simply run this to build and
install the library in your BlocksDS environment:

```bash
make install
```

You can also install PAlib from [this link](https://github.com/AntonioND/palib)
if you want to use PAlib and µLibrary at the same time (some examples do it!).

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

Official forum: http://www.playeradvance.org/forum/forumdisplay.php?f=103

Port to BlocksDS by Antonio Niño Díaz, aka AntonioND.
