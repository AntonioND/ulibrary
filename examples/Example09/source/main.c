// Example 09
//
// Same as Example02b except that a music is played meanwhile using PALib.

#include <ulib/ulib.h>
#include <PA9.h>
#include "james.h"
#include "bear.h"
#include "music.h"

// Our image contains 3 frames, one next to the other vertically, and 32 pixel wide.
#define FRAME_HEIGHT 32

// Helper that may be useful for defining several files
#define RAM_FILE_ENTRY(name, symbol) \
    {name, (void *)symbol, (int)symbol##_size, &VF_MEMORY}

// Files stored in RAM.
UL_VIRTUALFILENAME ram_names[] = {
    RAM_FILE_ENTRY("james.gif", james),
    RAM_FILE_ENTRY("bear.gif", bear),
};

int main(int argc, char *argv[])
{
    UL_IMAGE *imgJames, *imgBear;
    int animStage = 0, frameNumber = 0;

    // The frame numbers that will be used for animations
    const int animPositions[] = { 0, 1, 2, 1 };
    int i, j, fade = 0x1f;

    PA_Init();         // PA Init...
    PA_InitVBL();      // VBL Init...
    //PA_InitSound();    // Sound Init, for the mod player...
    //PA_PlayMod(music); // Play a mod file

    // Initialize µLibrary
    ulInit(UL_INIT_ALL);
    // Initialize the graphical part
    ulInitGfx();
    // Initialize the text part
    ulInitText();

    // Register the file names for the RAM file system. This is not obligatory,
    // you could directly pass "pointer, size" for file loading routines instead
    // of "name, 0".
    ulSetVirtualFilenameList(ram_names, ulNumberof(ram_names));

    // Show some splash screens!
    ulSetMainLcd(1);
    ulShowSplashScreen(1);
    ulShowSplashScreen(2);

    // We will use the touchpad this time
    ulSetMainLcd(0);
    // Ensure the second screen is black
    REG_BLDCNT_SUB = BLEND_FADE_BLACK | BLEND_SRC_BG0 | BLEND_SRC_BG1 | BLEND_SRC_BG2 | BLEND_SRC_BG3;
    REG_BLDY_SUB = 0x1f;
    REG_BLDCNT = BLEND_FADE_BLACK | BLEND_SRC_BG0 | BLEND_SRC_BG1 | BLEND_SRC_BG2 | BLEND_SRC_BG3;
    REG_BLDY = fade;

    // Use bright pink as a transparent color
    ulSetTransparentColor(RGB15(31, 0, 31));
    {
        // We load our James character image. Note that the format is PAL4 (16
        // colors). It is enough for our image but may not for others.
        imgJames = ulLoadImageFileGIF("james.gif", 0, UL_IN_VRAM, UL_PF_PAL4);
        imgBear = ulLoadImageFileGIF("bear.gif", 0, UL_IN_VRAM, UL_PF_PAL8);
    }
    ulDisableTransparentColor();

    // Define the image center, so that the stylus will control the center of
    // the image. By default, images are specified by their top-left corner
    // (that's the fastest). Usually you should not have to change the image
    // center except for rotation.
    imgJames->centerX = imgJames->sizeX / 2;
    imgJames->centerY = FRAME_HEIGHT / 2;

    while (1)
    {
        // Read keys
        ulReadKeys(0);

        // We place our character to the same position as the touchpad stylus,
        // making it follow it
        imgJames->x = ul_keys.touch.x;
        imgJames->y = ul_keys.touch.y;

        frameNumber++;

        // Each 8 frames, we increment the frame stage counter, so that we
        // display the next frame
        if (frameNumber % 8 == 0)
        {
            // Increment the animation counter
            animStage = (animStage + 1) % 4;
        }

        // Start our drawing
        ulStartDrawing2D();

        // Draw some bears in the background!
        if (imgBear)
        {
            ulSetImageTint(imgBear, RGB15(16, 16, 16));
            for (j = 0; j < SCREEN_HEIGHT; j += imgBear->sizeY)
            {
                for (i = 0; i < SCREEN_WIDTH; i += imgBear->sizeX)
                    ulDrawImageXY(imgBear, i, j);
            }
        }

        // Set up the sprite part to draw only the desired image part. We could
        // do it by ourself using the offsetX0, ... members.
        ulSetImageTileSize(imgJames,
            // Image frames are aligned vertically, so we always begin to the left
            0,

            // Top position: animPositions defines the frame numbers in the image
            // for each animation step (0, 1, 2, 1). Each frame is FRAME_HEIGHT
            // tall, so we just have to multiply to get the actual position of
            // the frame on the image!
            FRAME_HEIGHT * animPositions[animStage],

            // Every frame takes the entire image width
            imgJames->sizeX,
            // Height of a frame
            FRAME_HEIGHT);

        // Draw our character on the screen!
        ulDrawImage(imgJames);

        // End the drawing
        ulEndDrawing();

        // Wait the VBlank (synchronize at 60 fps)
        ulEndFrame();
        PA_WaitForVBL();

        // Fade the screen
        fade = ulMax(fade - 1, 0);
        REG_BLDY = fade;
    }

    return 0;
}
