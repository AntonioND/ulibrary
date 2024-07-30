#include "ulib.h"

UL_FONT *ul_curFont = NULL;
UL_FONT *ul_lcdFont = NULL;
UL_COLOR ul_curTextColor = 0xffff;

const unsigned char ul_lcdFont_data[] = {
    0x2a, 0x15, 0x2a, 0x15, 0x2a, 0x15, 0x2a, 0x15,
    0xc, 0x2, 0x4, 0x28, 0x2e, 0x38, 0x28, 0x28,
    0xc, 0x2, 0x4, 0x28, 0x2e, 0x10, 0x28, 0x28,
    0xe, 0x2, 0x6, 0x2a, 0x2e, 0x10, 0x28, 0x28,
    0xe, 0x2, 0x6, 0x2, 0x3e, 0x10, 0x10, 0x10,
    0xe, 0x2, 0x6, 0x3a, 0x2e, 0x28, 0x18, 0x30,
    0x4, 0xa, 0xe, 0xa, 0x2a, 0x18, 0x18, 0x28,
    0x0, 0x8, 0x1c, 0x1c, 0x1c, 0x3e, 0x8, 0x0,
    0x0, 0x38, 0x3c, 0x3e, 0x3c, 0x38, 0x0, 0x0,
    0x20, 0x28, 0x38, 0x3e, 0x38, 0x28, 0x20, 0x0,
    0x0, 0xe, 0x8, 0x8, 0x3e, 0x1c, 0x8, 0x0,
    0x10, 0x28, 0x28, 0x2e, 0x1a, 0xe, 0x0, 0x0,
    0x3e, 0x8, 0x1c, 0x3e, 0x8, 0x8, 0x8, 0x0,
    0x20, 0x20, 0x28, 0x2c, 0x3e, 0xc, 0x8, 0x0,
    0x1c, 0x22, 0x3e, 0x3e, 0x36, 0x36, 0x3e, 0x0,
    0x0, 0x20, 0x10, 0xa, 0x4, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x1e, 0x1e, 0x1e, 0x1e, 0x0, 0x0,
    0x0, 0x10, 0x18, 0x1c, 0x18, 0x10, 0x0, 0x0,
    0x0, 0x4, 0xc, 0x1c, 0xc, 0x4, 0x0, 0x0,
    0x0, 0x0, 0x8, 0x1c, 0x3e, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x3e, 0x1c, 0x8, 0x0, 0x0,
    0x0, 0x8, 0x4, 0x3e, 0x4, 0x8, 0x0, 0x0,
    0x0, 0x8, 0x10, 0x3e, 0x10, 0x8, 0x0, 0x0,
    0x8, 0x1c, 0x2a, 0x8, 0x8, 0x8, 0x8, 0x0,
    0x8, 0x8, 0x8, 0x8, 0x2a, 0x1c, 0x8, 0x0,
    0x10, 0x18, 0x1c, 0x1e, 0x1e, 0x1c, 0x18, 0x10,
    0x2, 0x6, 0xe, 0x1e, 0x1e, 0xe, 0x6, 0x2,
    0x0, 0x8, 0x1c, 0x3e, 0x1c, 0x1c, 0x1c, 0x0,
    0x0, 0x22, 0x22, 0x22, 0x22, 0x1c, 0x0, 0x0,
    0x0, 0x1c, 0x22, 0x22, 0x22, 0x22, 0x0, 0x0,
    0x0, 0x3c, 0x2, 0x2, 0x2, 0x3c, 0x0, 0x0,
    0x0, 0x3c, 0x2, 0x3e, 0x2, 0x3c, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x8, 0x8, 0x8, 0x8, 0x0, 0x8, 0x8, 0x0,
    0x14, 0x14, 0x14, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x14, 0x14, 0x3e, 0x14, 0x3e, 0x14, 0x14, 0x0,
    0x8, 0x3c, 0xa, 0x1c, 0x28, 0x1e, 0x8, 0x0,
    0x6, 0x26, 0x10, 0x8, 0x4, 0x32, 0x30, 0x0,
    0x4, 0xa, 0xa, 0x4, 0x2a, 0x12, 0x2c, 0x0,
    0x8, 0x8, 0x8, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x10, 0x8, 0x4, 0x4, 0x4, 0x8, 0x10, 0x0,
    0x4, 0x8, 0x10, 0x10, 0x10, 0x8, 0x4, 0x0,
    0x0, 0x8, 0x2a, 0x1c, 0x2a, 0x8, 0x0, 0x0,
    0x0, 0x8, 0x8, 0x3e, 0x8, 0x8, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0xc, 0x8, 0x4,
    0x0, 0x0, 0x0, 0x3e, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0xc, 0xc, 0x0,
    0x0, 0x20, 0x10, 0x8, 0x4, 0x2, 0x0, 0x0,
    0x1c, 0x22, 0x22, 0x2a, 0x22, 0x22, 0x1c, 0x0,
    0x8, 0xc, 0x8, 0x8, 0x8, 0x8, 0x1c, 0x0,
    0x1c, 0x22, 0x20, 0x10, 0x8, 0x4, 0x3e, 0x0,
    0x3e, 0x10, 0x8, 0x10, 0x20, 0x22, 0x1c, 0x0,
    0x10, 0x18, 0x14, 0x12, 0x3e, 0x10, 0x10, 0x0,
    0x3e, 0x2, 0x1e, 0x20, 0x20, 0x22, 0x1c, 0x0,
    0x18, 0x4, 0x2, 0x1e, 0x22, 0x22, 0x1c, 0x0,
    0x3e, 0x20, 0x10, 0x8, 0x4, 0x4, 0x4, 0x0,
    0x1c, 0x22, 0x22, 0x1c, 0x22, 0x22, 0x1c, 0x0,
    0x1c, 0x22, 0x22, 0x3c, 0x20, 0x10, 0xc, 0x0,
    0x0, 0xc, 0xc, 0x0, 0xc, 0xc, 0x0, 0x0,
    0x0, 0x0, 0xc, 0xc, 0x0, 0xc, 0x8, 0x4,
    0x10, 0x8, 0x4, 0x2, 0x4, 0x8, 0x10, 0x0,
    0x0, 0x0, 0x3e, 0x0, 0x3e, 0x0, 0x0, 0x0,
    0x4, 0x8, 0x10, 0x20, 0x10, 0x8, 0x4, 0x0,
    0x1c, 0x22, 0x20, 0x10, 0x8, 0x0, 0x8, 0x0,
    0x1c, 0x22, 0x2a, 0x3a, 0xa, 0x2, 0x3c, 0x0,
    0x1c, 0x22, 0x22, 0x3e, 0x22, 0x22, 0x22, 0x0,
    0x1e, 0x22, 0x22, 0x1e, 0x22, 0x22, 0x1e, 0x0,
    0x1c, 0x22, 0x2, 0x2, 0x2, 0x22, 0x1c, 0x0,
    0x1e, 0x22, 0x22, 0x22, 0x22, 0x22, 0x1e, 0x0,
    0x3e, 0x2, 0x2, 0x1e, 0x2, 0x2, 0x3e, 0x0,
    0x3e, 0x2, 0x2, 0x1e, 0x2, 0x2, 0x2, 0x0,
    0x1c, 0x22, 0x2, 0x3a, 0x22, 0x22, 0x1c, 0x0,
    0x22, 0x22, 0x22, 0x3e, 0x22, 0x22, 0x22, 0x0,
    0x1c, 0x8, 0x8, 0x8, 0x8, 0x8, 0x1c, 0x0,
    0x38, 0x10, 0x10, 0x10, 0x10, 0x12, 0xc, 0x0,
    0x22, 0x12, 0xa, 0x6, 0xa, 0x12, 0x22, 0x0,
    0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x3e, 0x0,
    0x22, 0x36, 0x2a, 0x2a, 0x22, 0x22, 0x22, 0x0,
    0x22, 0x22, 0x26, 0x2a, 0x32, 0x22, 0x22, 0x0,
    0x1c, 0x22, 0x22, 0x22, 0x22, 0x22, 0x1c, 0x0,
    0x1e, 0x22, 0x22, 0x1e, 0x2, 0x2, 0x2, 0x0,
    0x1c, 0x22, 0x22, 0x22, 0x2a, 0x12, 0x2c, 0x0,
    0x1e, 0x22, 0x22, 0x1e, 0xa, 0x12, 0x22, 0x0,
    0x3c, 0x2, 0x2, 0x1c, 0x20, 0x20, 0x1e, 0x0,
    0x3e, 0x8, 0x8, 0x8, 0x8, 0x8, 0x8, 0x0,
    0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x1c, 0x0,
    0x22, 0x22, 0x22, 0x22, 0x22, 0x14, 0x8, 0x0,
    0x22, 0x22, 0x22, 0x2a, 0x2a, 0x2a, 0x14, 0x0,
    0x22, 0x22, 0x14, 0x8, 0x14, 0x22, 0x22, 0x0,
    0x22, 0x22, 0x22, 0x14, 0x8, 0x8, 0x8, 0x0,
    0x3e, 0x20, 0x10, 0x8, 0x4, 0x2, 0x3e, 0x0,
    0x18, 0x8, 0x8, 0x8, 0x8, 0x8, 0x18, 0x0,
    0x0, 0x2, 0x4, 0x8, 0x10, 0x20, 0x0, 0x0,
    0x18, 0x10, 0x10, 0x10, 0x10, 0x10, 0x18, 0x0,
    0x8, 0x14, 0x22, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3e, 0x0,
    0x8, 0x8, 0x10, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x1c, 0x20, 0x3c, 0x22, 0x3c, 0x0,
    0x2, 0x2, 0x1a, 0x26, 0x22, 0x22, 0x1e, 0x0,
    0x0, 0x0, 0x1c, 0x2, 0x2, 0x22, 0x1c, 0x0,
    0x20, 0x20, 0x2c, 0x32, 0x22, 0x22, 0x3c, 0x0,
    0x0, 0x0, 0x1c, 0x22, 0x3e, 0x2, 0x1c, 0x0,
    0x18, 0x24, 0x4, 0xe, 0x4, 0x4, 0x4, 0x0,
    0x0, 0x0, 0x3c, 0x22, 0x22, 0x3c, 0x20, 0x1c,
    0x2, 0x2, 0x1a, 0x26, 0x22, 0x22, 0x22, 0x0,
    0x8, 0x0, 0xc, 0x8, 0x8, 0x8, 0x1c, 0x0,
    0x10, 0x0, 0x18, 0x10, 0x10, 0x10, 0x12, 0xc,
    0x4, 0x4, 0x24, 0x14, 0xc, 0x14, 0x24, 0x0,
    0xc, 0x8, 0x8, 0x8, 0x8, 0x8, 0x1c, 0x0,
    0x0, 0x0, 0x16, 0x2a, 0x2a, 0x22, 0x22, 0x0,
    0x0, 0x0, 0x1a, 0x26, 0x22, 0x22, 0x22, 0x0,
    0x0, 0x0, 0x1c, 0x22, 0x22, 0x22, 0x1c, 0x0,
    0x0, 0x0, 0x1e, 0x22, 0x22, 0x1e, 0x2, 0x2,
    0x0, 0x0, 0x2c, 0x32, 0x22, 0x3c, 0x20, 0x20,
    0x0, 0x0, 0x1a, 0x26, 0x2, 0x2, 0x2, 0x0,
    0x0, 0x0, 0x1c, 0x2, 0x1c, 0x20, 0x1e, 0x0,
    0x4, 0x4, 0xe, 0x4, 0x4, 0x24, 0x18, 0x0,
    0x0, 0x0, 0x22, 0x22, 0x22, 0x32, 0x2c, 0x0,
    0x0, 0x0, 0x22, 0x22, 0x22, 0x14, 0x8, 0x0,
    0x0, 0x0, 0x22, 0x22, 0x2a, 0x2a, 0x14, 0x0,
    0x0, 0x0, 0x22, 0x14, 0x8, 0x14, 0x22, 0x0,
    0x0, 0x0, 0x22, 0x22, 0x22, 0x3c, 0x20, 0x1c,
    0x0, 0x0, 0x3e, 0x10, 0x8, 0x4, 0x3e, 0x0,
    0x30, 0x8, 0x8, 0x4, 0x8, 0x8, 0x30, 0x0,
    0x8, 0x8, 0x8, 0x8, 0x8, 0x8, 0x8, 0x0,
    0x6, 0x8, 0x8, 0x10, 0x8, 0x8, 0x6, 0x0,
    0x0, 0x4, 0x2a, 0x10, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x8, 0x1c, 0x3e, 0x1c, 0x8, 0x0, 0x0,
    0x0, 0x0, 0x2c, 0x12, 0x12, 0x12, 0x2c, 0x0,
    0x18, 0x24, 0x24, 0x1c, 0x24, 0x24, 0x1a, 0x0,
    0x3e, 0x22, 0x2, 0x2, 0x2, 0x2, 0x2, 0x0,
    0x0, 0x0, 0x24, 0x2a, 0x10, 0x18, 0x18, 0x8,
    0x0, 0x0, 0x0, 0x8, 0x14, 0x22, 0x3e, 0x0,
    0x18, 0x4, 0x8, 0x14, 0x22, 0x22, 0x1c, 0x0,
    0x0, 0x0, 0x1c, 0x2, 0xc, 0x2, 0x1c, 0x0,
    0x34, 0x1c, 0x2, 0x2, 0x2, 0x1c, 0x20, 0x18,
    0x18, 0x24, 0x22, 0x3e, 0x22, 0x12, 0xc, 0x0,
    0x0, 0x4, 0x8, 0x10, 0x18, 0x24, 0x22, 0x0,
    0x4, 0x18, 0x4, 0x18, 0x4, 0x4, 0x18, 0x8,
    0x3e, 0x14, 0x14, 0x14, 0x14, 0x14, 0x14, 0x0,
    0x0, 0x0, 0x3e, 0x14, 0x14, 0x14, 0x32, 0x0,
    0x0, 0x0, 0x8, 0x14, 0x14, 0xc, 0x4, 0x4,
    0x3e, 0x4, 0x8, 0x10, 0x8, 0x4, 0x3e, 0x0,
    0x0, 0x0, 0x3c, 0x12, 0x12, 0x12, 0xc, 0x0,
    0x0, 0x0, 0x1c, 0xa, 0x8, 0x28, 0x10, 0x0,
    0x0, 0x8, 0x8, 0x1c, 0x2a, 0x1c, 0x8, 0x8,
    0x0, 0x0, 0x2a, 0x2a, 0x2a, 0x1c, 0x8, 0x8,
    0x1c, 0x22, 0x22, 0x22, 0x14, 0x14, 0x36, 0x0,
    0x0, 0x0, 0x14, 0x22, 0x2a, 0x2a, 0x14, 0x0,
    0x0, 0x0, 0x3c, 0x4, 0x1c, 0x4, 0x3c, 0x0,
    0x0, 0x0, 0x18, 0x24, 0x1e, 0x2, 0xc, 0x0,
    0xc, 0x0, 0xc, 0xe, 0xc, 0x1c, 0xc, 0x0,
    0x1a, 0x6, 0x2, 0x2, 0x0, 0x0, 0x0, 0x0,
    0x1c, 0x8, 0x8, 0x8, 0x8, 0x0, 0x0, 0x0,
    0x3e, 0x0, 0x22, 0x14, 0x8, 0x14, 0x22, 0x0,
    0x3e, 0x0, 0x22, 0x22, 0x22, 0x3c, 0x20, 0x1c,
    0x20, 0x18, 0x6, 0x18, 0x20, 0x0, 0x3e, 0x0,
    0x10, 0x10, 0x3e, 0x8, 0x3e, 0x4, 0x4, 0x0,
    0x2, 0xc, 0x30, 0xc, 0x2, 0x0, 0x3e, 0x0,
    0x0, 0x0, 0x20, 0x10, 0x8, 0x4, 0x3e, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x2a, 0x0,
    0x8, 0x8, 0x0, 0x8, 0x8, 0x8, 0x8, 0x0,
    0x0, 0x8, 0x1c, 0xa, 0xa, 0x2a, 0x1c, 0x8,
    0x18, 0x24, 0x4, 0xe, 0x4, 0x24, 0x1e, 0x0,
    0x0, 0x22, 0x1c, 0x14, 0x1c, 0x22, 0x0, 0x0,
    0x22, 0x22, 0x14, 0x3e, 0x8, 0x3e, 0x8, 0x0,
    0x8, 0x8, 0x8, 0x0, 0x8, 0x8, 0x8, 0x0,
    0x1c, 0x2, 0x1c, 0x22, 0x1c, 0x20, 0x1c, 0x0,
    0x38, 0x8, 0x8, 0x8, 0xa, 0xc, 0x8, 0x0,
    0x1c, 0x22, 0x3a, 0x3a, 0x3a, 0x22, 0x1c, 0x0,
    0x3c, 0x22, 0x22, 0x32, 0x2c, 0x0, 0x3e, 0x0,
    0x0, 0x28, 0x14, 0xa, 0x5, 0xa, 0x14, 0x28,
    0x0, 0x0, 0x3e, 0x20, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x38, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x1e, 0x31, 0x2d, 0x31, 0x35, 0x2d, 0x1e, 0x0,
    0x0, 0xe, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0xc, 0x12, 0x12, 0xc, 0x0, 0x0, 0x0, 0x0,
    0x8, 0x8, 0x3e, 0x8, 0x8, 0x0, 0x3e, 0x0,
    0xc, 0x10, 0x8, 0x4, 0x1c, 0x0, 0x0, 0x0,
    0xc, 0x10, 0x8, 0x10, 0xc, 0x0, 0x0, 0x0,
    0x10, 0x18, 0x16, 0x10, 0x38, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x12, 0x12, 0x12, 0x12, 0x2e, 0x2,
    0x3c, 0x2a, 0x2a, 0x2a, 0x3c, 0x28, 0x28, 0x0,
    0x0, 0x0, 0x0, 0x8, 0x0, 0x0, 0x0, 0x0,
    0x4, 0xe, 0x4, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x8, 0xc, 0x8, 0x8, 0x1c, 0x0, 0x0, 0x0,
    0x1c, 0x22, 0x22, 0x22, 0x1c, 0x0, 0x3e, 0x0,
    0x0, 0x5, 0xa, 0x14, 0x28, 0x14, 0xa, 0x5,
    0x30, 0x20, 0x2c, 0x12, 0x12, 0x1a, 0x34, 0x0,
    0x10, 0x28, 0x8, 0x8, 0x8, 0xa, 0x4, 0x0,
    0x0, 0x14, 0x2a, 0x2a, 0x14, 0x0, 0x0, 0x0,
    0x8, 0x0, 0x8, 0x4, 0x2, 0x22, 0x1c, 0x0,
    0x4, 0x8, 0x1c, 0x22, 0x3e, 0x22, 0x22, 0x0,
    0x10, 0x8, 0x1c, 0x22, 0x3e, 0x22, 0x22, 0x0,
    0x8, 0x14, 0x1c, 0x22, 0x3e, 0x22, 0x22, 0x0,
    0x28, 0x14, 0x1c, 0x22, 0x3e, 0x22, 0x22, 0x0,
    0x14, 0x0, 0x1c, 0x22, 0x3e, 0x22, 0x22, 0x0,
    0x8, 0x14, 0x8, 0x1c, 0x22, 0x3e, 0x22, 0x0,
    0x38, 0xc, 0xc, 0x3a, 0xe, 0xa, 0x3a, 0x0,
    0x1c, 0x22, 0x2, 0x2, 0x22, 0x1c, 0x8, 0xc,
    0x4, 0x8, 0x3e, 0x2, 0x1e, 0x2, 0x3e, 0x0,
    0x10, 0x8, 0x3e, 0x2, 0x1e, 0x2, 0x3e, 0x0,
    0x8, 0x14, 0x3e, 0x2, 0x1e, 0x2, 0x3e, 0x0,
    0x14, 0x0, 0x3e, 0x2, 0x1e, 0x2, 0x3e, 0x0,
    0x4, 0x8, 0x1c, 0x8, 0x8, 0x8, 0x1c, 0x0,
    0x10, 0x8, 0x1c, 0x8, 0x8, 0x8, 0x1c, 0x0,
    0x8, 0x14, 0x1c, 0x8, 0x8, 0x8, 0x1c, 0x0,
    0x14, 0x0, 0x1c, 0x8, 0x8, 0x8, 0x1c, 0x0,
    0x1e, 0x24, 0x24, 0x2e, 0x24, 0x24, 0x1e, 0x0,
    0x28, 0x14, 0x22, 0x26, 0x2a, 0x32, 0x22, 0x0,
    0x4, 0x8, 0x1c, 0x22, 0x22, 0x22, 0x1c, 0x0,
    0x10, 0x8, 0x1c, 0x22, 0x22, 0x22, 0x1c, 0x0,
    0x8, 0x14, 0x1c, 0x22, 0x22, 0x22, 0x1c, 0x0,
    0x28, 0x14, 0x1c, 0x22, 0x22, 0x22, 0x1c, 0x0,
    0x14, 0x0, 0x1c, 0x22, 0x22, 0x22, 0x1c, 0x0,
    0x0, 0x0, 0x0, 0x14, 0x8, 0x14, 0x0, 0x0,
    0x1c, 0x32, 0x32, 0x2a, 0x26, 0x26, 0x1c, 0x0,
    0x4, 0x8, 0x22, 0x22, 0x22, 0x22, 0x1c, 0x0,
    0x10, 0x8, 0x22, 0x22, 0x22, 0x22, 0x1c, 0x0,
    0x8, 0x14, 0x0, 0x22, 0x22, 0x22, 0x1c, 0x0,
    0x14, 0x0, 0x22, 0x22, 0x22, 0x22, 0x1c, 0x0,
    0x10, 0x8, 0x22, 0x22, 0x14, 0x8, 0x8, 0x0,
    0x2, 0x1e, 0x22, 0x22, 0x22, 0x1e, 0x2, 0x0,
    0x18, 0x24, 0x14, 0x24, 0x24, 0x2c, 0x16, 0x0,
    0x4, 0x8, 0x3c, 0x22, 0x22, 0x32, 0x2c, 0x0,
    0x10, 0x8, 0x3c, 0x22, 0x22, 0x32, 0x2c, 0x0,
    0x8, 0x14, 0x3c, 0x22, 0x22, 0x32, 0x2c, 0x0,
    0x28, 0x14, 0x3c, 0x22, 0x22, 0x32, 0x2c, 0x0,
    0x14, 0x0, 0x3c, 0x22, 0x22, 0x32, 0x2c, 0x0,
    0x8, 0x14, 0x8, 0x3c, 0x22, 0x32, 0x2c, 0x0,
    0x0, 0x0, 0x16, 0x28, 0x3c, 0xa, 0x34, 0x0,
    0x0, 0x0, 0x1c, 0x2, 0x22, 0x1c, 0x8, 0x4,
    0x4, 0x8, 0x1c, 0x22, 0x3e, 0x2, 0x1c, 0x0,
    0x10, 0x8, 0x1c, 0x22, 0x3e, 0x2, 0x1c, 0x0,
    0x8, 0x14, 0x1c, 0x22, 0x3e, 0x2, 0x1c, 0x0,
    0x14, 0x0, 0x1c, 0x22, 0x3e, 0x2, 0x1c, 0x0,
    0x4, 0x8, 0xc, 0x8, 0x8, 0x8, 0x1c, 0x0,
    0x10, 0x8, 0xc, 0x8, 0x8, 0x8, 0x1c, 0x0,
    0x8, 0x14, 0xc, 0x8, 0x8, 0x8, 0x1c, 0x0,
    0x14, 0x0, 0xc, 0x8, 0x8, 0x8, 0x1c, 0x0,
    0x14, 0x8, 0x14, 0x20, 0x3c, 0x22, 0x1c, 0x0,
    0x28, 0x14, 0x0, 0x1a, 0x26, 0x22, 0x22, 0x0,
    0x4, 0x8, 0x0, 0x1c, 0x22, 0x22, 0x1c, 0x0,
    0x10, 0x8, 0x0, 0x1c, 0x22, 0x22, 0x1c, 0x0,
    0x8, 0x14, 0x0, 0x1c, 0x22, 0x22, 0x1c, 0x0,
    0x28, 0x14, 0x0, 0x1c, 0x22, 0x22, 0x1c, 0x0,
    0x14, 0x0, 0x0, 0x1c, 0x22, 0x22, 0x1c, 0x0,
    0x0, 0x8, 0x0, 0x3e, 0x0, 0x8, 0x0, 0x0,
    0x0, 0x0, 0x1c, 0x32, 0x2a, 0x26, 0x1c, 0x0,
    0x4, 0x8, 0x22, 0x22, 0x22, 0x32, 0x2c, 0x0,
    0x10, 0x8, 0x22, 0x22, 0x22, 0x32, 0x2c, 0x0,
    0x8, 0x14, 0x0, 0x22, 0x22, 0x32, 0x2c, 0x0,
    0x14, 0x0, 0x22, 0x22, 0x22, 0x32, 0x2c, 0x0,
    0x10, 0x8, 0x22, 0x22, 0x22, 0x3c, 0x20, 0x1c,
    0x2, 0x1a, 0x26, 0x22, 0x22, 0x26, 0x1a, 0x2,
    0x14, 0x0, 0x22, 0x22, 0x22, 0x3c, 0x20, 0x1c,
};

UL_FONTINFO ul_lcdFontInfo =
{
    (void*)ul_lcdFont_data, // Fonte par d�faut LCD
    1,                      // 1 bit par pixel
    NULL,                   // Proportionnelle
    6, 8, 1,                // 6x8 (1 octet par ligne)
};

// bitplanes: format (bits par pixel) de la fonte, imagePlanes: format de la
// texture � remplir (puissance de deux)
void ulDrawChar1BitToImage(UL_IMAGE *img, int x0, int y0, int w, int h,
                           int width, int bitPlanes, int imagePlanes,
                           const unsigned char *font)
{
    unsigned char v, t, *data;
    int x,xx,y;

    for (y = 0; y < h; y++)
    {
        data = (u8*)ulGetImagePixelAddr(img, x0, y + y0);
        for (xx = 0; xx < width; )
        {
            v = *font++;
            for (x = 0; x < 8; x += bitPlanes)
            {
                if (xx < w)
                {
                    int offset = (xx + x0) & (ul_pixelsPerByte[imagePlanes] - 1);
                    t = v & ((1 << bitPlanes) - 1);
                    if (t)
                        *data |= t << (offset * imagePlanes);

                    // Dernier pixel pour cet octet
                    if (offset == ul_pixelsPerByte[imagePlanes] - 1)
                        data++;
                }
                v >>= bitPlanes;
                xx++;
            }
        }
    }
}

UL_FONT *ulCreateFont(UL_FONTINFO *fi)
{
    UL_FONT *f;
    int i, x, y;
    const int pixelplanewidth[4] = { 3, 2, 2, 1 };
    int imageFormat;

    f = (UL_FONT*)malloc(sizeof(UL_FONT));
    if (!f)
        return NULL;

    // Liste des tailles
    f->charWidths = (u8*)malloc(256 * sizeof(char));
    if (!f->charWidths)
    {
        free(f);
        return NULL;
    }

    if (fi->charWidths)
    {
        // R�utilise les tailles fournies
        for (i = 0; i < 256; i++)
            f->charWidths[i] = fi->charWidths[i];
        //f->charWidths = fi->charWidths;
        f->isCharWidthConstant = 0;
    }
    else
    {
        // Remplit la table avec les m�mes tailles
        for (i = 0; i < 256; i++)
            f->charWidths[i] = fi->charWidth;
        f->isCharWidthConstant = 1;
    }

    // Position des caract�res (pour les fontes non proportionnelles)
    f->charPositions = (u16*)malloc(256 * sizeof(short));
    if (!f->charPositions)
    {
        free(f->charWidths);
        free(f);
        return NULL;
    }
    f->addedSpace = fi->addedSpace;
    x = y = 0;
    for (i=0;i<256;i++)
    {
        if (x + f->charWidths[i] + f->addedSpace >= UL_TEXT_TEXWIDTH)
        {
            // Prochaine ligne
            x = 0;
            y ++;
        }
        f->charPositions[i] = x + (y<<UL_TEXT_TEXDECAL);
        x += f->charWidths[i] + f->addedSpace;
    }

    // Palette de 4 ou 16 selon le format de la police
    if (fi->pixelFormat <= 2)
    {
        f->img = ulCreateImage(UL_TEXT_TEXWIDTH, (y + 1) * fi->charHeight,
                               UL_IN_RAM, UL_PF_PAL2, 4);
        imageFormat = 2;
    }
    else
    {
        f->img = ulCreateImage(UL_TEXT_TEXWIDTH, (y + 1) * fi->charHeight,
                               UL_IN_RAM, UL_PF_PAL4, 16);
        imageFormat = 4;
    }

    if (!f->img)
    {
        free(f->charPositions);
        free(f->charWidths);
        free(f);
        return NULL;
    }

    f->charHeight = fi->charHeight;

//    ulLockImage(f->img, UL_LOCK_ALL);
//    {
         memset(f->img->texture, 0, (f->img->sysSizeX * f->img->sysSizeY * ul_pixelWidth[f->img->format]) >> 3);

        // Couleurs par d�faut - la premi�re est transparente
        ((UL_COLOR*)f->img->palette)[0] = RGB15(0,0,0);
        ((UL_COLOR*)f->img->palette)[1] = RGB15(31,31,31);

        // Couleurs additionnelles (stock�es dans le fichier)
        int palCount = ulMin(f->img->palCount, fi->paletteCount);
        for (i = 0; i < palCount; i++)
        {
            unsigned long color = fi->paletteData[i];
            //Conversion de 24-bit � 15-bit
            ((UL_COLOR*)f->img->palette)[i] = RGB15((color & 0xff) >> 3,
                                                    ((color >> 8) & 0xff) >> 3,
                                                    ((color >> 16) & 0xff) >> 3);
        }

        // Dessine les caract�res sur le buffer
        for (i = 0; i < 256; i++)
        {
            ulDrawChar1BitToImage(f->img, UL_TEXT_CHARPOSXY(f, i),
                                  f->charWidths[i] + f->addedSpace,
                                  f->charHeight,
                                  fi->lineWidth << pixelplanewidth[fi->pixelFormat - 1],
                                  fi->pixelFormat,
                                  imageFormat,
                                  (u8 *)fi->fontdata + i * fi->lineWidth * fi->charHeight);
        }
//    }
//    ulUnlockImage(f->img, UL_LOCK_ALL);

    // On va pouvoir utiliser l'image - retir�, sera mise en VRAM par d�faut au
    // premier affichage
    ulRealizeImage(f->img);
    return f;
}


UL_FONT *ulLoadFont(VIRTUAL_FILE *f)
{
    UL_FONTINFO fi;
    UL_FONT_FORMAT_HEADER fh;
    UL_FONT *font = NULL;
    unsigned char tcTaillesCar[256], *tcCaracteres;
    unsigned long *paletteData = NULL;

    // Lit l'en-t�te de la fonte
    VirtualFileRead(&fh, sizeof(fh), 1, f);

    // V�rifie l'en-t�te
    if (!strcmp(fh.strVersion, "OSLFont v01"))
    {
        fi.pixelFormat = fh.pixelFormat;
        // VERIFIER 1 <= PIXELFORMAT <= 4
        if (fh.variableWidth)
        {
            VirtualFileRead(tcTaillesCar, 256, sizeof(u8), f);
            fi.charWidths = tcTaillesCar;
        }
        else
        {
            fi.charWidths = NULL;
        }

        fi.charWidth = fh.charWidth;
        fi.charHeight = fh.charHeight;
        fi.lineWidth = fh.lineWidth;
        fi.addedSpace = fh.addedSpace;
        // Lit les donn�es des caract�res
        tcCaracteres = (u8*)malloc(fh.lineWidth*fi.charHeight*256);
        if (tcCaracteres)
        {
            if (VirtualFileRead(tcCaracteres, fh.lineWidth*fi.charHeight * 256, 1, f) > 0)
            {
                fi.fontdata = tcCaracteres;
                // If it has not been loaded properly, we will have 0 colors
                fi.paletteCount = 0;
                // Est-ce qu'il reste encore des couleurs � charger?
                if (fh.paletteCount > 0)
                {
                    paletteData = malloc(fh.paletteCount * sizeof(unsigned long));
                    if (paletteData)
                    {
                        // Lit les entr�es de palette
                        if (VirtualFileRead(paletteData,
                                            fh.paletteCount * sizeof(unsigned long), 1, f) > 0)
                        {
                            // We'll do nothing with this
                            fi.paletteCount = fh.paletteCount;
                            fi.paletteData = paletteData;
                        }
                    }
                }
                // Chargement final de la fonte
                font = ulCreateFont(&fi);
                if (paletteData)
                   free(paletteData);
            }
            free(tcCaracteres);
        }
    }
    return font;
}

void ulDeleteFont(UL_FONT *f)
{
    ulDeleteImage(f->img);
    free(f->charPositions);
    free(f->charWidths);
    free(f);
}

void ulDrawTile(int u, int v, int x, int y, int sizeX, int sizeY)
{
    // Commence le dessin
    GFX_BEGIN = GL_QUADS;

        ulVertexUVXY(u, v, x, y);
        ulVertexUVXY(u, v+sizeY, x, y+sizeY);
        ulVertexUVXY(u+sizeX, v+sizeY, x+sizeX, y+sizeY);
        ulVertexUVXY(u+sizeX, v, x+sizeX, y);

    GFX_END = 0;

    // Pas d'incr�mentation auto de la profondeur: les polys sont tous au m�me
    // niveau avec ce syst�me
    return;
}

// Ne fonctionne pas, parce que les caract�res sont des rectangles extraits de
// la texture de la police en cours, et m�me si les positions des caract�res
// sont toujours align�es � l'�cran, elles ne le sont pas forc�ment sur la
// texture.
/*
int ul_multiCharIndex;

void ulBeginMultichar()
{
    ul_multiCharIndex = 1;
}

void ulDrawMultichar(int u, int v, int x, int y, int sizeX, int sizeY)
{
    if (ul_multiCharIndex == 1)
    {
        // Commence le dessin
        GFX_BEGIN = GL_QUAD_STRIP;

            // 1. Haut-gauche
            GFX_TEX_COORD = TEXTURE_PACK(inttot16(v), inttot16(u));
            GFX_VERTEX16 = (y << 16) | (x & 0xffff);
            GFX_VERTEX16 = ul_currentDepth;

            // 2. Bas-gauche
            GFX_TEX_COORD = TEXTURE_PACK(inttot16(v + sizeY), inttot16(u));
            GFX_VERTEX16 = ((y + sizeY) << 16) | (x & 0xffff);
            GFX_VERTEX16 = ul_currentDepth;

            // 3. Haut-droite
            GFX_TEX_COORD = TEXTURE_PACK(inttot16(v), inttot16(u + sizeX));
            GFX_VERTEX16 = (y << 16) | ((x + sizeX) & 0xffff);
            GFX_VERTEX16 = ul_currentDepth;

            // 4. Bas-droite
            GFX_TEX_COORD = TEXTURE_PACK(inttot16(v + sizeY), inttot16(u + sizeX));
            GFX_VERTEX16 = ((y + sizeY) << 16) | ((x + sizeX) & 0xffff);
            GFX_VERTEX16 = ul_currentDepth;

        ul_multiCharIndex++;
    }
    else
    {
        // 3. Haut-droite
        GFX_TEX_COORD = TEXTURE_PACK(inttot16(v), inttot16(u + sizeX));
        GFX_VERTEX16 = (y << 16) | ((x + sizeX) & 0xffff);
        GFX_VERTEX16 = ul_currentDepth;

        // 4. Bas-droite
        GFX_TEX_COORD = TEXTURE_PACK(inttot16(v + sizeY), inttot16(u + sizeX));
        GFX_VERTEX16 = ((y + sizeY) << 16) | ((x + sizeX) & 0xffff);
        GFX_VERTEX16 = ul_currentDepth;
    }
}

void ulEndMultichar()
{
    if (ul_multiCharIndex != 1)
        GFX_END = 0;
}
*/

void ulDrawChar(int x, int y, unsigned char c)
{
    // Mise en place avant dessin
    ulSetTexture(ul_curFont->img);
    GFX_COLOR = ul_curTextColor;

    // Dessine le caract�re
    ulDrawTile(UL_TEXT_CHARPOSXY(ul_curFont, c), x, y,
               ul_curFont->charWidths[c] + ul_curFont->addedSpace,
               ul_curFont->charHeight);

    ul_currentDepth += ul_autoDepth;
}

void ulDrawString(int x, int y, const char *str)
{
    unsigned char c;

    // Mise en place avant dessin
    ulSetTexture(ul_curFont->img);
    GFX_COLOR = ul_curTextColor;

    // Parcourt tous les caract�res
    while(*str)
    {
        c = *(unsigned char*)str++;
        ulDrawTile(UL_TEXT_CHARPOSXY(ul_curFont, c), x, y,
                   ul_curFont->charWidths[c] + ul_curFont->addedSpace,
                   ul_curFont->charHeight);
        x += ul_curFont->charWidths[c];
    }

    ul_currentDepth += ul_autoDepth;
}

void ulDrawTextBox(int x0, int y0, int x1, int y1, const char *text, int format)
{
    int x,y, x2;
    unsigned char c;
    const char *text2;

    // Mise en place avant dessin
    ulSetTexture(ul_curFont->img);
    GFX_COLOR = ul_curTextColor;

    x = x0;
    y = y0;
    while(*text)
    {
        c = *text;
        if (c == ' ')
        {
            text2 = text;
            x2 = x;
            do
            {
                x2 += ul_curFont->charWidths[(int)(*text2++)];
                if (x2 > x1)
                {
                    text++;
                    goto newline;
                }
            } while(*text2 != '\n' && *text2 != ' ' && *text2);
        }
        if (x + ul_curFont->charWidths[c] > x1 || *text=='\n')
        {
newline:
            // Prochaine ligne
            x = x0;
            y += ul_curFont->charHeight;
            // Trop bas -> termin�
            if (y + ul_curFont->charHeight > y1)
                break;
            // Retour -> saute
            if (*text == '\n')
                text++;
            continue;
        }
        //ulDrawChar(x,y,c);
        ulDrawTile(UL_TEXT_CHARPOSXY(ul_curFont, c), x, y,
                   ul_curFont->charWidths[c] + ul_curFont->addedSpace,
                   ul_curFont->charHeight);
        x += ul_curFont->charWidths[c];
        text++;
    }

    ul_currentDepth += ul_autoDepth;
}

void ulSetTextColor(UL_COLOR color)
{
   ul_curTextColor = color;
}

void ulInitText()
{
    // Charge et utilise la fonte syst�me
    if (!ul_lcdFont)
        ul_lcdFont = ulCreateFont(&ul_lcdFontInfo);
    ulSetFont(ul_lcdFont);
}
