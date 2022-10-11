#ifndef PROCESS_H
#define PROCESS_H

#include <kernel/virtualmemory.h>
#include <kernel/task.h>
#include <kernel/osspace.h>
#include <kernel/type.h>
#include <kernel/heapmemorymanager.h>
#include <stdlib/list.h>

namespace kernel
{

class GDT;
class MemoryMap;

typedef enum ProcessState
{
    IDLE,
    RUNNING
} ProcessState;

class Process
{
public:
    uint64 pid;
    
    uint64 cs;  // Code segment
    uint64 ds;  // Data segment
    
    uint64 memorySize;
    uint64 stackSize;
    OSSpace space;
    
    HeapMemoryManager *heapMemoryManager;
    VirtualMemory *virtualMemory;
    std::List<Task*> tasks;
    
    mainFunction entryPoint;
    int argc;
    char **argv;
    
    Process(uint64 pid, HeapMemoryManager *heapMemoryManager, VirtualMemory *virtualMemory, uint64 memorySize, uint64 stackSize, mainFunction entryPoint, int argc, char **argv, OSSpace osspace = OSSpace::RING_3);
    ~Process();
    
    Task* getMainTask();
    void initialize();
    kernel::Task* createTask(mainFunction entryPoint, int argc, char **argv);
    void onTaskFinish(Task *task);
};

}

#endif