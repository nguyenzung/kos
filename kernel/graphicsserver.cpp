#include <kernel/graphicsserver.h>

using namespace kernel;

GraphicsServer::GraphicsServer()
    :width(0), height(0), depth(0), frameBuffer(0)
{
    
}

GraphicsServer::~GraphicsServer()
{
    if (this->frameBuffer)
        delete this->frameBuffer;
}

void GraphicsServer::initializeDevice(BaseGraphicsDevice *device)
{
    this->width = device->width;
    this->height = device->height;
    this->depth = device->depth;
    this->frameBuffer = new uint8[this->width * this->height * this->depth];
    
}

void GraphicsServer::update()
{
    if (this->frameBuffer)
    {
        for(uint16 j = 0; j < this->height; ++j)
        {
            for (uint16 i = 0; i < this->width; ++i)
            {
                uint8 *data = this->frameBuffer + (this->width * j + i) * this->depth;
                this->device->drawPixel(i, j, data[0], data[1], data[2]);
            }
        }
    }
}
