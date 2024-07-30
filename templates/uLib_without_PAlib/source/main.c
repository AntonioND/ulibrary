#include <ulib/ulib.h> // Include for �Library

int main(int argc, char *argv[])
{
    // Initialization of �library
    ulInit(UL_INIT_ALL);
    ulInitGfx();
    ulInitText();

    while (1)
    {
        ulReadKeys(0);

        ulStartDrawing2D();

        ulEndDrawing();
        ulSyncFrame();
    }

    return 0;
}
