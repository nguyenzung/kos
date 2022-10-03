#include <kernel/kernel.h>
#include <kernel/type.h>
#include <kernel/printer.h>
#include <driver/vga.h>
#include <kernel/utils.h>
#include <kernel/kernelobject.h>
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

    char **argv= new char*[1];
    argv[0] = new char[5];
    argv[0][0] = 'm';
    argv[0][1] = 'a';
    argv[0][2] = 'i';
    argv[0][3] = 'n';
    argv[0][4] = '\0';
    
    Task *mainTask = taskManager.makeTask(&Kernel::start, 1, 0);
    
    
    timer.active();
    cmos.active();
    serial.active();

    deviceManager.registerDevice(&timer);
    serial.printSerial(" Initialize Kernel \n");
    

    Task *task1 = taskManager.makeTask(&TaskTest::count, 10000, argv);
    Task *task2 = taskManager.makeTask(&TaskTest::ask, 20000, argv);
    Task *task3 = taskManager.makeTask(&TaskTest::count, 300000, argv);
    Task *task4 = taskManager.makeTask(&TaskTest::ask, 400000, argv);

    cmos.updateDateTime();

    std::Map<uint64, uint64> map;
    printf("\n %p ", map.put(10, 10));
    map.put(13, 13);
    map.put(15, 15);
    map.put(16, 16);
    map.put(18, 18);
    map.put(10, 1000);
    map.put(23, 23);
    map.preorderTravel();
    map.inorderTravel();

    printf("\n");
    
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
    // cmos.updateDateTime();
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
