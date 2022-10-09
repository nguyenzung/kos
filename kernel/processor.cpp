#include <kernel/processor.h>

using namespace kernel;

Processor::Processor()
{
    
}

void Processor::intialize(uint8 localApicID)
{
    this->localApicId = localApicID;
}