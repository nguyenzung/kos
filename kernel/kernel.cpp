#include <kernel/kernel.h>
#include <kernel/type.h>
#include <kernel/printer.h>
#include <driver/vga.h>
#include <kernel/utils.h>
#include <kernel/heapmemorymanager.h>
#include <stdlib/lock.h>
#include <stdlib/list.h>
#include <stdlib/unorderedmap.h>
#include <stdlib/map.h>
#include <stdlib/math.h>
#include <stdlib/string.h>
#include <stdlib/algorithm.h>
#include <tasks/counter.h>

#define HEAP_SIZE 256*1024*1024
#define MAX_KERNEL_SIZE 1024*1024*1024

using namespace kernel;

extern void* heapBase;
extern void* stackBase;
extern void* stackBottom;

Kernel* Kernel::instance = 0;

Kernel::Kernel()
{
    Kernel::instance = this;
    INIT_LOCK(intLock);
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
    printf("\n Kernel initialize! ");
    uint64 kernelMemorySize = 1;
    kernelMemorySize <<= 32;   
    heapMemoryManager.initialize(heapBase, HEAP_SIZE, stackBase);
    deviceManager.initialize();
    taskManager.initialize();
    interruptManager.initialize();
    physicalMemory.initialize();
    
    cmos.updateDateTime();    

    virtualMemory.initialize(kernelMemorySize, OSSpace::RING_0);
    processManager.initialize();

    virtualMemory.active();
    timer.active();
    cmos.active();
    serial.active();

    deviceManager.registerDevice(&timer);
    serial.printSerial("Initialize Kernel");    
    
    cmos.updateDateTime();
    
    bsp.intialize();
    sdt.initialize();
    
    uint64 pid = makeProcess(
                &heapMemoryManager, 
                &virtualMemory,
                kernelMemorySize,
                (uint64)heapBase,
                HEAP_SIZE,
                (uint64)stackBottom,
                (uint64)stackBase,
                1<<26,
                &Kernel::start,
                1,
                0,
                OSSpace::RING_0);
    
    char **argv = new char*;
    argv[0] = new char[5];
    argv[0][0] = 'M';
    argv[0][0] = 'a';
    argv[0][0] = 'i';
    argv[0][0] = 'n';
    argv[0][0] = '\0';
        
    uint64 pid1 = makeProcess(
                &heapMemoryManager, 
                &virtualMemory,
                kernelMemorySize,
                (uint64)heapBase,
                HEAP_SIZE,
                (uint64)stackBottom,
                (uint64)stackBase + 0x10000,
                1<<26,
                &TaskTest::processOne,
                10,
                argv,
                OSSpace::RING_0);
    
    
    printf("\n Process ID: %d %d %d ", pid, pid1);
    
    makeThread(pid, &TaskTest::count, 200, argv);
    makeThread(pid, &TaskTest::ask, 200, argv); 
    makeThread(pid1, &TaskTest::processTwo, 5, argv);
    
    cmos.updateDateTime();

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

    // uint64 address = &Kernel::initialize;
    // VGA vga;
    // vga.setupVideoMode();
    // vga.drawRectangle(0,0, 320, 200, VGAColor::CYAN);
}

void Kernel::update()
{
     cmos.updateDateTime();
}

void Kernel::enableInterrupt()
{
    LOCK(intLock);
    asm ("sti");
    UNLOCK(intLock);
}

void Kernel::disableInterrupt()
{
    LOCK(intLock);
    asm ("cli");
    UNLOCK(intLock);
}

bool Kernel::isInterruptActive()
{
    LOCK(intLock);
    uint64 flags;
    asm ("pushf\n\t" "pop %0":"=g"(flags));
    UNLOCK(intLock);
    return flags & (1 << 9);
}

int Kernel::start(int argc, char **argv)
{    
    asm ("sti");
    asm("_cpp_stop:");
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
