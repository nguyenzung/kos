#ifndef GRAPHICSERVER_H
#define GRAPHICSERVER_H

#include <kernel/basegraphicsdevice.h>
#include <kernel/type.h>

namespace kernel
{

class GraphicsServer
{
public:
    uint8 *frameBuffer;
    
    uint16 width;
    uint16 height;
    uint8 depth; 
    
    BaseGraphicsDevice *device;
    
    GraphicsServer();
    ~GraphicsServer();
    
    void initializeDevice(BaseGraphicsDevice *device);
    
    void update();
    
    void drawPixel();
    void clearScreen();
};

}

#endif // GRAPHICSERVER_H
