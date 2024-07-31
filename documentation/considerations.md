# Considerations

Before using the µLibrary in your project, you must know that the 3D GPU can
only be on one screen at once, or on both with some limitations. In the first
case, the second screen must be updated using your own custom code (2D GPU), or
another library like PALib.

If you really want to use µLibrary on both screens, you can, but it will reserve
2 banks (C and D, 256 kB) for its use, and the framerate will drop to 30 FPS (1
frame per screen in alternance).

Important: Because of the use of the 3D GPU and the associated technical
limitations, µLibrary is NOT meant to be used alone in a game. If you choose to
use µLibrary, please consider the following:

- NEVER create a game that only uses one screen, or displays debug info on the
  second one. This is a very bad thing, the Nintendo DS has two screens, try to
  make use of them in a creative way.

- Avoid the use of µLibrary on both screens, this will drop framerate from 60 to
  30 FPS, reduce render quality from 18-bit to 15-bit and reserve 2 banks for
  internal buffers. If you think your game can only be done by using the special
  abilities provided by the 3D GPU and you accept this price to pay, then it's
  okay, but if you game is simple and could be made, say with PALib (2D GPU,
  very similar to the Game Boy Advance), then use it instead, you will get 60
  FPS. You can always keep µLibrary for one of the two screens.

- µLibrary is meant for games or applications that concentrate their action on
  one screen and use the second one for less important things. Displaying a BG
  or some sprites with libnds is quite simple and thus, you can make use of the
  second screen without having to learn a lot of things.
