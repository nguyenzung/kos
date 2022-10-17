#include <kernel/processor.h>

using namespace kernel;

Processor::Processor()
{
    
}

void Processor::initialize(uint8 localApicID)
{
    this->localApicId = localApicID;
}