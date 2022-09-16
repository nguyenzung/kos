#ifndef KERNEL
#define KERNEL


#include "interruptmanager.h"
#include "devicemanager.h"
#include "memorymanager.h"

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

#endif