#ifndef KERNEL
#define KERNEL

#include <kernel/interruptmanager.h>
#include <kernel/devicemanager.h>
#include <kernel/heapmemorymanager.h>
#include <kernel/taskmanager.h>
#include <kernel/context.h>
#include <driver/timer.h>
#include <driver/cmos.h>
#include <driver/serial.h>

namespace kernel 
{

class Kernel
{
    HeapMemoryManager heapMemoryManager;
    DeviceManager deviceManager;
    InterruptManager interruptManager;
    TaskManager taskManager;

    driver::CMOS cmos;
    driver::Timer timer;
    driver::SERIAL serial;

    static Kernel* instance;

public:
    Kernel();
    ~Kernel();

    static Kernel* getInstance();

    void initialize();
    void update();

    static int start(int argc, char**argv);

    HeapMemoryManager* getHeapMemoryManager();
    DeviceManager* getDeviceManager();
    InterruptManager *getInterruptManager();
};

}
#endif
