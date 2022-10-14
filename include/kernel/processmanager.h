#ifndef PROCESSMANAGER_H
#define PROCESSMANAGER_H

#include <kernel/process.h>
#include <kernel/type.h>
#include <stdlib/unorderedmap.h>

namespace kernel
{

class ProcessManager{
public:
    uint64 current;
    std::UnorderedMap<uint64, Process*> *processes;
    
    ProcessManager();
    ~ProcessManager();
    
    DEF_MODULE_INSTANCE(ProcessManager)
    
    void initialize();
    Process* find(uint64 pid);
    Process* makeProcess(
            HeapMemoryManager *heapMemoryManager,
            VirtualMemory *virtualMemory,
            uint64 memorySize,
            uint64 heapBase,
            uint64 heapSize,
            uint64 stackBottom,
            uint64 stackBase,
            uint64 stackSize,
            mainFunction entryPoint,
            int argc,
            char **argv,
            OSSpace osspace = OSSpace::RING_3
    );
    
    bool onProcessFinished(Process *process);
};

uint64 makeProcess(
        HeapMemoryManager *heapMemoryManager,
        VirtualMemory *virtualMemory,
        uint64 memorySize,
        uint64 heapBase,
        uint64 heapSize,
        uint64 stackBottom,
        uint64 stackBase,
        uint64 stackSize,
        mainFunction entryPoint,
        int argc,
        char **argv,
        OSSpace osspace = OSSpace::RING_3
);

Task* makeThread(uint64 pid, mainFunction entryPoint, int argc, char** argv);

}

#endif // PROCESSMANAGER_H
