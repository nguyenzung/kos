#include "basegraphicsdevice.h"
#include "kernel/type.h"
#include "kernel/utils.h"

#ifndef VGA_H
#define VGA_H

typedef enum VGAColor {
    BLACK,
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    WHITE,
    GRAY,
    LIGHT_BLUE,
    LIGHT_GREEN,
    LIGHT_CYAN,
    LIGHT_RED,
    LIGHT_MAGENTA,
    YELLOW,
    BRIGHT_WHITE
} VGAColor;


class VGA: BaseGraphicsDevice
{
protected:
    uint8* getFrameSegment();        
    VGAColor getColorIndex(uint8 r, uint8 g, uint8 b);
    DEF_MODULE_INSTANCE(VGA)
public:
    VGA();
    void setupVideoMode() override;
    void drawPixel(uint32 x, uint32 y, VGAColor colorIndex);
    void drawPixel(uint32 x, uint32 y,  uint8 r, uint8 g, uint8 b) override;
    void drawRectangle(uint32 x, uint32 y, uint32 w, uint32 h, VGAColor color);
    void drawRectangle(uint32 x, uint32 y, uint32 w, uint32 h, uint8 r, uint8 g, uint8 b) override;

};
        
#endif