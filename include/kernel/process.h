#ifndef PROCESS_H
#define PROCESS_H

#include <kernel/virtualmemory.h>
#include <kernel/task.h>
#include <stdlib/list.h>
#include <kernel/type.h>

namespace kernel
{

class GDT;
class MemoryMap;

class Process
{
public:
    VirtualMemory virtualMemory;
    
    uint64 cs;  // Code segment
    uint64 ds;  // Data segment
    
    Process();

    void initialze();
};

}

#endif