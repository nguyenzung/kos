#include <kernel/basegraphicsdevice.h>

using namespace kernel;

BaseGraphicsDevice::BaseGraphicsDevice():BaseDriver() {

}

BaseGraphicsDevice::~BaseGraphicsDevice() {
    
}

void BaseGraphicsDevice::active()
{
    setupVideoMode();
}

void BaseGraphicsDevice::deactive()
{
    
}

void BaseGraphicsDevice::handleInterrupt()
{
    
}

void BaseGraphicsDevice::clearScreen(uint8 r, uint8 g, uint8 b)
{
    
}
