#include <kernel/kernel.h>
#include <kernel/type.h>
#include <kernel/printer.h>
#include <driver/vga.h>
#include <kernel/utils.h>
#include <kernel/kernelobject.h>
#include <stdlib/lock.h>
#include <stdlib/list.h>
#include <stdlib/unorderedmap.h>
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
    heapMemoryManager.initialize();
    deviceManager.initialize();

    char **argv= new char*[1];
    argv[0] = new char[5];
    argv[0][0] = 'm';
    argv[0][1] = 'a';
    argv[0][2] = 'i';
    argv[0][3] = 'n';
    argv[0][4] = '\0';
    
    Task *mainTask = taskManager.makeTask(&Kernel::start, 1, 0);
    
    taskManager.initialize();
    interruptManager.initialize();

    timer.active();
    cmos.active();
    deviceManager.registerDevice(&timer);

    Task *task1 = taskManager.makeTask(&TaskTest::count, 100000, argv);
    Task *task2 = taskManager.makeTask(&TaskTest::ask, 200000, argv);
    Task *task3 = taskManager.makeTask(&TaskTest::count, 300000, argv);
    Task *task4 = taskManager.makeTask(&TaskTest::ask, 400000, argv);

    cmos.updateDateTime();

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
    printf(" HTL ");
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
