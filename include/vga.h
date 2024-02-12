#ifndef VGA_H
#define VGA_H

#include <stm32f4xx.h>

#define WIDTH ((uint16_t)640)
#define HEIGHT ((uint16_t)480)

#define HSYNC ((uint16_t)30)
#define HBP ((uint16_t)13)
#define HFP ((uint16_t)32)

#define VSYNC ((uint16_t)10)
#define VBP ((uint16_t)2)
#define VFP ((uint16_t)2)

#define PIXEL_SIZE 4

const uint32_t fb[WIDTH * HEIGHT];

class VGA
{
public:
    VGA();
};

#endif