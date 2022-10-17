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
    kernel.loadDevice(&keyboard);
    
    mouse.active();
    kernel.loadDevice(&mouse);
}

void OS::startOS()
{
    kernel::Kernel::start(1, 0);    
}