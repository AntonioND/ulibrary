## Version 1.14 - 06.08.2024

- Re-introduce v1.12 fixes to the location attribute of images. There was a
  mistake due to treating the values of one enum as the values of a different
  enum.

- The code of the library now uses enum typedefs in all places where it is
  possible. This lets the compiler warn the developer if the entries of two
  different enums are being mixed.

- Fix a few warnings.

## Version 1.13 - 05.08.2024

- `µLibrary` has been ported to BlocksDS, allowing programs that use it to be
  built with modern tools.

- `ulBindTextureToGl()` has been removed, as it required access to internal
  state of libnds, which is no longer exposed.

- `libpng` and `zlib` are no longer included in the repository, they are taken
  from the toolchain. The code that loads PNG images with `libpng` has been
  updated to work with modern `libpng`.

- `PAlib` examples are broken until there is a new version of `PAlib` that
  works with `BlocksDS`.

- The `Doxygen` documentation has been fixed and updated.

## Version 1.12 - 17.03.2009

- This release is only to keep working with the newest devkitpro & libnds
  releases. A lot of things have changed and some important things must have
  been rewritten This was the occasion of creating better makefiles, update
  samples, changing the logo and do other minor changes.

## Version 1.11 - 23.08.2008

- `devKitPro` has not really changed (thankfully), so no mandatory updates were
  needed.

- Fixes a few bugs, namely the palette issues reported by some people.

## Version 1.10 - 26.12.2007

- As usual, works with and requires the latest `libnds` version; that's a shame
  because nothing will run on emulators from now. You can however solve this
  problem by replacing your copy of `basic.arm7` in your `libnds` folder by mine
  (you can find it in the `tools` folder).

- Added `ulMoveScreenView()`, `ulRotateScreenView()`, `ulScaleScreenView()`
  and `ulResetScreenView()` to apply special transformations to your screen.
  You can for example rotate the screen as a whole or only a list of objects
  without any effort. This will namely allow you to scale and rotate objects
  like maps and text, which isn't available by default.

- Fonts now work better. Now the `font2oft` tool is in the `tools` folder.

- Added `ulGetColorRed()`, `ulGetColorGreen()`, `ulGetColorBlue()` to retrieve
  the component values of a color.

- Added `ulLoadFontFile()` to directly load a font from a file.

- PNG files with alpha can now be loaded directly as `UL_PF_PAL5_A3` and
  `UL_PF_PAL3_A5`. The alpha will be taken in account and set in the resulting
  image. Note that you will have to enable blending as usual with `ulSetAlpha()`
  and by setting another polygroup, because if all objects are with the same
  polygroup, none will blend with any other.

- Loading unpaletted PNG files to paletted formats reworked. If there aren't
  enough colors for the whole image, the nearest is taken. However you should
  avoid this situation because it's an extremely simple but weak method for
  reducing the colors of an image.

## Version 1.00 bêta 4 - 14.07.07

- Works with, and requires the last `libnds` version!.

- Added `ulDeleteMap()` function.

- Using bank B for textures wasn't working correctly; all my excuses!

- Some JPG files with a vertical size not multiple of 8 or 16 were loaded
  incorrectly.
