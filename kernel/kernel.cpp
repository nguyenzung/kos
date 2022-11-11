#include <kernel/kernel.h>
#include <kernel/type.h>
#include <kernel/printer.h>
#include <driver/vga.h>
#include <kernel/utils.h>
#include <kernel/heapmemorymanager.h>
#include <kernel/apic.h>
#include <kernel/multiboot.h>
#include <stdlib/lock.h>
#include <stdlib/list.h>
#include <stdlib/unorderedmap.h>
#include <stdlib/map.h>
#include <stdlib/math.h>
#include <stdlib/vector.h>
#include <stdlib/string.h>
#include <stdlib/algorithm.h>
#include <tasks/counter.h>
#include <ui/desktop.h>
#include <test/test.h>


#define HEAP_SIZE 256*1024*1024
#define MAX_KERNEL_SIZE 1024*1024*1024

using namespace kernel;

extern void* heapBase;
extern void* stackSize;
extern void* stackBase;
extern void* stackBottom;
extern void* multibootData;

Kernel* Kernel::instance = 0;

Kernel::Kernel()
{
    Kernel::instance = this;
}

Kernel::~Kernel() 
{
}

Kernel* Kernel::getInstance()
{
    return Kernel::instance;
}

void Kernel::initialize()
{
    uint64 kernelMemorySize = 1;
    kernelMemorySize <<= 32;   
    heapMemoryManager.initialize(heapBase, HEAP_SIZE, stackBase);
    deviceManager.initialize();
    taskManager.initialize();
    
    physicalMemory.initialize();
    
    virtualMemory.initialize(kernelMemorySize, OSSpace::RING_0);
    processManager.initialize();
    virtualMemory.active();
    
    sdt.initialize();
    loadCores();
    
    timer.active();
    deviceManager.registerDevice(&timer);
    cmos.active();
    serial.active();
    serial.printSerial("\n Initialize Kernel");    
    
    multiboot.initializeInLegacyMode(multibootData);
    
    interruptManager.initialize();
    interruptManager.enableAPIC();
    
    uint64 pid = makeProcess(
                &heapMemoryManager, 
                &virtualMemory,
                kernelMemorySize,
                (uint64)heapBase,
                HEAP_SIZE,
                (uint64)stackBottom,
                (uint64)stackBase,
                (uint64)stackSize,
                &Kernel::start,
                1,
                0,
                OSSpace::RING_0);
    printf("\n ProcessID: %d ", pid);
    
    char **argv = new char*;
    argv[0] = new char[5];
    argv[0][0] = 'M';
    argv[0][0] = 'a';
    argv[0][0] = 'i';
    argv[0][0] = 'n';
    argv[0][0] = '\0';
        
//    uint64 pid1 = makeProcess(
//                &heapMemoryManager, 
//                &virtualMemory,
//                kernelMemorySize,
//                (uint64)heapBase,
//                HEAP_SIZE,
//                (uint64)stackBottom,
//                (uint64)stackBase + 0x10000,
//                1<<26,
//                &TaskTest::processOne,
//                100,
//                argv,
//                OSSpace::RING_0);
    
    
//    printf("\n Process ID: %d %d %d ", pid, pid1);
    
//    makeThread(pid, &TaskTest::count, 1000, argv);
//    makeThread(pid, &TaskTest::ask, 2000, argv); 
    test();
//    makeThread(pid1, &TaskTest::processTwo, 120, argv);
    
//    cmos.updateDateTime();

//     std::Map<uint64, uint64> map;
//     map.put(40, 40);
//     map.put(50, 50);
//     map.put(30, 30);
//     map.put(35, 35);
//     map.put(25, 25);
//     map.put(13, 13);
//     map.put(33, 33);
//     map.put(43, 43);

//     map.preorderTravel();
//     map.inorderTravel();

//     map.earse(40);
//     map.earse(25);
//     map.put(46, 46);
//     map.put(24, 24);
//     map.put(54, 54);
//     map.put(58, 58);
//     map.earse(33);
//     map.put(60, 60);
//     map.preorderTravel();
//     map.inorderTravel(); 
    

}

void Kernel::update()
{
    static uint32 counter = 0;
    if (counter % 200 == 0)
    {
        graphics.update();
    }
    counter++;
}

void Kernel::loadCores()
{
    
}

void Kernel::loadDevice(BaseDriver *handler)
{
    handler->active();
    deviceManager.registerDevice(handler);
}

void Kernel::loadGraphics(BaseGraphicsDevice *device)
{
    device->active();
    graphics.initializeDevice(device);
}

void Kernel::startSystemUI()
{
    if (graphics.isReady())
    {
        ui::Desktop *desktop = new ui::Desktop();
        graphics.setBaseWidget(desktop);
    }
}

int Kernel::start(int argc, char **argv)
{    
    asm ("sti");
    Kernel::getInstance()->startSystemUI();
    asm("_cpp_stop:");
    asm("hlt");
    Kernel::getInstance()->update();
    asm("jmp _cpp_stop");
}

HeapMemoryManager* Kernel::getHeapMemoryManager() 
{
    return &this->heapMemoryManager;
}

DeviceManager* Kernel::getDeviceManager() 
{
    return &this->deviceManager;
}

InterruptManager* Kernel::getInterruptManager() 
{
    return &this->interruptManager;
}

void debug()
{
    Printer::println(" [DEBUG]", 8);
}
