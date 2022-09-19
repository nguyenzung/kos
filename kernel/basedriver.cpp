#include <kernel/basedriver.h>
#include <kernel/heapmemorymanager.h>

using namespace kernel;

BaseDriver::BaseDriver(uint8 vector)
    :InterruptHandler(vector)
{
}

BaseDriver::~BaseDriver()
{
}
