#include <kernel/os.h>
#include <kernel/printer.h>

using namespace kernel;

OS::OS()
{
    
}

OS::~OS()
{
    
}

void OS::initialize()
{
    kernel.initialize();
}

void OS::setupHardware()
{
//    keyboard.active();
    kernel.loadDevice((BaseDriver*)&keyboard);
    
//    mouse.active();
    kernel.loadDevice((BaseDriver*)&mouse);
    
//    kernel.loadGraphics((BaseGraphicsDevice*)(&vesa));
}

void OS::startOS()
{
    kernel::Kernel::start(1, 0);    
}