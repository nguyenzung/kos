#ifndef PROCESS
#define PROCESS

#include <kernel/type.h>

namespace kernel
{

class GDT;
class MemoryMap;

class Process
{
public:
    
    uint64 cs;  // Code segment
    uint64 ds;  // Data segment
    
    Process();

    void initialze();
};

}

#endif