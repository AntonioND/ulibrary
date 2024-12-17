// Example 07
//
// Sample that demonstrates the use of µLib and PALib together.
//
// I've taken the 16cSpriteAnim sample for this, and I've just changed the way
// things are loaded:
//
// - NONE of the PALib functions shall touch to the main screen (0)! The main
//   screen is allocated to µLibrary and PALib will CRASH if it tries to do
//   anything with it. I've replaced every function call screen argument from 0
//   to 1 (sub-screen).

#include <PA9.h>         // Include for PA_Lib
#include "gfx/all_gfx.h"
#include <ulib/ulib.h>   // Include for µLibrary

int main(int argc, char ** argv)
{
    PA_Init();    // Initializes PA_Lib
    PA_InitVBL(); // Initializes a standard VBL

    // Init our µLibrary stuff there
    ulInit(UL_INIT_LIBONLY);
    ulInitGfx();
    ulInitText();

    // Show some splash screens!
    ulShowSplashScreen(1);
    ulShowSplashScreen(2);

    // We use the top screen. The touchpad will be left to PALib.
    ulSetMainLcd(1);

    PA_Init16cBg(1, 2); // Initializes a 16 color bg
    PA_LoadPal16c(PAL_BG1, ropes_Pal); // And loads its palette
    PA_16cErase(1); // Clear bg before start drawing

    u8 i = 0;      // position of our rope, from bottom
    u8 j = 0;      // step of our animation
    u8 frames = 0; //frames rendered, usefull to do animation timing

    // Infinite loop to keep the program running
    while (1)
    {
        // We can mix PALib and µLib code.
        const char *testString = "It works!";
        int posX, posY;
        ulStartDrawing2D();
        ulDrawGradientRect(0, 0, 256, 192, RGB15(31, 0, 0), RGB15(0, 24, 0),
                           RGB15(0, 0, 31), RGB15(20, 20, 20));

        // Calculate the positions to center our text on the screen
        posY = (SCREEN_HEIGHT - ul_curFont->charHeight) / 2;
        posX = (SCREEN_WIDTH - ulGetStringWidth(testString)) / 2;

        // Draw a shadowed bold text
        ulSetTextColor(RGB15(0, 0, 0));
        ulDrawString(posX + 2, posY + 1, "It works!");
        ulDrawString(posX + 1, posY + 1, "It works!");
        ulSetTextColor(RGB15(31, 31, 31));
        ulDrawString(posX, posY, "It works!");
        ulDrawString(posX + 1, posY, "It works!");

        i += 1; // Move the rope up 1 pixels
        if (i > 192) // If the rope has hit the top of the screen, start again from bottom
            i=0;

        if (++frames == 20) //If we have render 20 consecutive frames
        {
            j = j + 64; // Change animation to next frame

            // ropes_Sprite has three 8x16 pixels frames, so each frame is
            // (8x16)/2 = 64 bytes (since each pixels is 4bits) so our stride on
            // the animation image is 64.

            if (j > 128) // Check frame limit (only 3 frames on this animation)
                j = 0;

            frames = 0; // Reset frame counter
        }

        // Our drawing with µLib is terminated!
        ulEndDrawing();
        // Always call ulEndFrame if we don't use ulSyncFrame but PA_WaitForVBL
        ulEndFrame();

        PA_WaitForVBL(); // Typical wait for vertical blank...

        // Erase background (if there is only one row like in this example, you
        // should erase only the space ocupped by the row).
        PA_16cErase(1);
        PA_16c8Xi(1, 125, 192 - i, (u32 *)(ropes_Sprite + j), i); // Draw the row.
    }

    return 0;
}
