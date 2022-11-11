#ifndef KERNEL
#define KERNEL

#include <kernel/interruptmanager.h>
#include <kernel/devicemanager.h>
#include <kernel/heapmemorymanager.h>
#include <kernel/taskmanager.h>
#include <kernel/context.h>
#include <kernel/physicalmemory.h>
#include <kernel/sdt.h>
#include <kernel/bsp.h>
#include <kernel/ap.h>
#include <kernel/virtualmemory.h>
#include <kernel/processmanager.h>
#include <kernel/pic.h>
#include <kernel/multiboot.h>
#include <kernel/graphicsserver.h>
#include <stdlib/list.h>
#include <driver/timer.h>
#include <driver/cmos.h>
#include <driver/serial.h>

namespace kernel 
{
class Kernel
{
    DECLARE_LOCK(intLock);
    HeapMemoryManager heapMemoryManager;
    DeviceManager deviceManager;
    InterruptManager interruptManager;
    TaskManager taskManager;
    PhysicalMemory physicalMemory;
    VirtualMemory virtualMemory;
    ProcessManager processManager;
    
    SDT sdt;
    BSP bsp;
    driver::Timer timer;
    driver::SERIAL serial;
    std::Vector<AP*> aps;
    driver::CMOS cmos;
    
    Multiboot multiboot;
    GraphicsServer graphics;
    
    static Kernel* instance;

public:
    Kernel();
    ~Kernel();

    static Kernel* getInstance();

    void initialize();
    void update();

    void loadCores();
    void loadDevice(BaseDriver *handler);
    void loadGraphics(BaseGraphicsDevice *device);
    void startSystemUI();

    static int start(int argc, char**argv);

    HeapMemoryManager* getHeapMemoryManager();
    DeviceManager* getDeviceManager();
    InterruptManager *getInterruptManager();
};

}
#endif
