#ifndef KERNEL
#define KERNEL


#include <kernel/interruptmanager.h>
#include <kernel/devicemanager.h>
#include <kernel/memorymanager.h>
#include <driver/timer.h>

namespace kernel {

class Kernel {
    MemoryManager memoryManager;
    DeviceManager deviceManager;
    InterruptManager interruptManager;
    static Kernel* instance;

public:
    Kernel();
    ~Kernel();

    static Kernel* getInstance();

    void startKernel();
    void hlt();

    MemoryManager* getMemoryManager();
    DeviceManager* getDeviceManager();
    InterruptManager *getInterruptManager();

};

}
#endif