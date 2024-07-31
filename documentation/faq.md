# FAQ

**In some cases, when starting a new scene or when drawing some images, I get a
short flickering, usually more pronounced on emulator than on DS.**

Some problems may happen when an image is realized automatically. Images have to
be realized (copied to VRAM) before they can be used by the GPU (drawn on the
screen). By default, when loading images, you will certainly put them in RAM.
Example:

```
UL_IMAGE *myImage = ulLoadImageFilePNG("/file.png", 0, UL_IN_RAM, UL_PF_PAL8);
```

Putting images in RAM is a great idea because you can modify them after you
loaded them and it's what I would advise you to do by default. When you'll draw
them for the first time, µLibrary will copy them to the VRAM automatically. From
now, they won't be modifiable anymore (`image->texture` is `NULL`). The problem
is that you usually begin to draw images in your main loop, and realization
requires to locks video memory, and thus render error will occurs. If
realization is done during the first frame only, this is not a problem, but if
it appears in latter frames, then an annoying flickering may appear.

If you handle your images dynamically and think some images could be realized
during latter frames, put your images in VRAM (`UL_IN_VRAM`). If you still need
to access the image to modify it, then put it in RAM (`UL_IN_RAM`) and realize
it manually before beginning the game. Example:

```
UL_IMAGE *myImage = ulLoadImageFilePNG("/file.png", 0, UL_IN_RAM, UL_PF_PAL8);

// Do something with your image

ulRealizeImage(myImage);
```

**If a draw a large number of object, the screen gets messed up.**

On DS, there is a limit with the number of vertices that can be handled per
frame, which is 6144. If this number is exceeded, the render will be messed up.
A vertex (plural: vertices) is a coordinate, used for every object. For example
a quadliteral (square or rectangle image), which is the most used type in
µLibrary (`ulDrawImage()`, `ulDrawFillRect()`, etc.) takes 4 vertices (4
coordinates) in memory, so you can virtually display 1536 single images per
frame. But in fact, this number will grow more quickly, as every text character
takes 4 vertices as well (drawing Hello world for example would use 44
vertices). Same for maps: every tile takes 4 vertices, so a fullscreen 8x8 map
without any transparent tile would take 3300 vertices, that is more than half
the available number (!).

Here is a list of typical function needs in terms of vertices:

- Drawing a map: ((256 / tileSizeX + 1) * (256 / tileSizeY + 1) -
  numberOfTransparentTilesOnTheScreen) * 4, that is 3300 vertices for a 8x8 map,
  or 884 vertices for a 16x16 map (recommended). Transparent tiles are those set
  to 0, they are never drawn and thus spare some vertices.

- Drawing text: 4 * numberOfCharacters.

- Drawing an image: 4 vertices.

- Drawing a filled rectangle, gradient: 4 vertices

- Drawing an empty rectangle: 4 lines, that is 4 * 3 = 12 vertices (lines are
  drawn as triangles, which require 3 vertices).
