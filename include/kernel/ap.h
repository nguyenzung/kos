#ifndef AP_H
#define AP_H

#include <kernel/processor.h>
#include <kernel/sdt.h>

namespace kernel
{

class AP : public Processor
{
public:
    AP();
};

std::Vector<AP*> loadAPs();

}
#endif // AP_H
