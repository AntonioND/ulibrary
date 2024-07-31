µLibrary documentation {#mainpage}
======================

## Introduction

Welcome to the documentation for µLibrary.

µLibrary was first designed to be a very small library for the Nintendo DS video
game system. Now it's not so small anymore but I can't change the name :P

µLibrary's main goal has however been kept: offer 2D graphics using the 3D GPU.
It's quite unconventional, as the DS features two quite powerful 2D GPUs. The
fact is that they're coming directly from the GBA era and have some limitations,
for example the number of sprites, the maximum sprite size, the maximum double
size of scaled or rotated objects, and some things are unavailable like tinting,
drawing triangles or quads, gradients, etc.

Namely, the 3D GPU is also able to deal better with transparency: alpha channel
or full alpha blending of objects between others is available. It has however a
limit: it's able to display a maximum of 1536 quads at once. Each object like a
sprite or a rectangle is considered as a quad, making it the only limit you've
got (you could display 1500 sprites if it's the only thing needed on the
screen).

Finally, you may note that some things in µLibrary are vaguely similar to the
OldSchool Library for PSP. Anyway they are not compatible at all, and porting
from one library to another may be very hard, if ever possible. However, an
experience with OSLib, althrough not required or even recommended, is always
good and will help you when getting started with µLib.

## API documentation

- @ref main
  - @ref main_base
  - @ref main_maths
  - @ref main_misc
- @ref drawing
  - @ref drawing_base
  - @ref clipping
  - @ref screen_view
  - @ref untexgeo
  - @ref images
    - @ref images_creation
    - @ref images_loading
    - @ref images_drawing
    - @ref images_working
    - @ref image_adv
  - @ref adv_vertex
- @ref glwrapper
- @ref keys
- @ref loadutil
- @ref maps
- @ref messagebox
- @ref text
- @ref virtualfile
  - @ref virtualfile_io
  - @ref virtualfile_sources
