#include "basedriver.h"
#include "memorymanager.h"

using namespace kernel;

BaseDriver::BaseDriver(uint8 vector)
    :InterruptHandler(vector)
{
}

BaseDriver::~BaseDriver()
{
}
