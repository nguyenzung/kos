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

using namespace kernel;

extern void* heapBase;
extern void* stackBase;

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
    deviceManager.initialize();
    taskManager.initialize();
    interruptManager.initialize();
    physicalMemory.initialize();
    
    Task *mainTask = taskManager.makeTask(&Kernel::start, 1, 0);
    
    timer.active();
    cmos.active();
    serial.active();

    deviceManager.registerDevice(&timer);
    serial.printSerial("Initialize Kernel");    
    
    cmos.updateDateTime();
    
    bsp.intialize();
    printf("\n BSP Local APICID: %d ", bsp.localApicId);
    sdt.initialize();

    virtualMemory.initialize(512*1024*1024, OSSpace::RING_0);
    virtualMemory.active();

    char *argv[] = {"Main"};
    
    Task *task1 = taskManager.makeTask(&TaskTest::count, 10000, argv);
    Task *task2 = taskManager.makeTask(&TaskTest::ask, 20000, argv);
    Task *task3 = taskManager.makeTask(&TaskTest::count, 300000, argv);
    Task *task4 = taskManager.makeTask(&TaskTest::ask, 400000, argv);

//    printf("\n Task %d %d %d %d", task1, task2, task3, task4);

    

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

//     printf("\n");
    
    /*
    *   Stress test: slow need to improve heap allocation algorithm
    */
    // printf("\n i = %d", physicalMemory.minAllocatedIndex);
    // uint32 i;
    // printf("\n Use %d ", physicalMemory.load(physicalMemory.minAllocatedIndex + 4));
    // printf("\n Use %d ", physicalMemory.load(physicalMemory.minAllocatedIndex + 3));
    // printf("\n Use %d ", physicalMemory.load(physicalMemory.minAllocatedIndex + 4));
    // printf("\n Use %d ", physicalMemory.load(physicalMemory.minAllocatedIndex + 2));
    // printf("\n Use %d ", physicalMemory.unload(physicalMemory.minAllocatedIndex + 4));
    // printf("\n Use %d ", physicalMemory.unload(physicalMemory.minAllocatedIndex + 2)); 
    // for (i = physicalMemory.minAllocatedIndex; i < physicalMemory.totalFrame - 5; i++)
    // {
    //     uint32 index = physicalMemory.load();
    //     if(i % 1000 ==0)
    //         printf("\n Load %d ", index);
    // }

    // uint64 address = &Kernel::initialize;
    // VGA vga;
    // vga.setupVideoMode();
    // vga.drawRectangle(0,0, 320, 200, VGAColor::CYAN);
}

void Kernel::update()
{
//     cmos.updateDateTime();
}

int Kernel::start(int argc, char **argv)
{    
    asm("sti");
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
