#include <kernel/basedriver.h>
#include <kernel/memorymanager.h>

using namespace kernel;

BaseDriver::BaseDriver(uint8 vector)
    :InterruptHandler(vector)
{
}

BaseDriver::~BaseDriver()
{
}
