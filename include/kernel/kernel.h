#ifndef KERNEL
#define KERNEL

#include <kernel/interruptmanager.h>
#include <kernel/devicemanager.h>
#include <kernel/heapmemorymanager.h>
#include <driver/timer.h>

namespace kernel 
{

class Kernel 
{
    HeapMemoryManager heapMemoryManager;
    DeviceManager deviceManager;
    InterruptManager interruptManager;
    static Kernel* instance;

public:
    Kernel();
    ~Kernel();

    static Kernel* getInstance();

    void startKernel();
    void hlt();

    HeapMemoryManager* getHeapMemoryManager();
    DeviceManager* getDeviceManager();
    InterruptManager *getInterruptManager();
};

}
#endif