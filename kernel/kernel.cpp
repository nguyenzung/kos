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
    // delete[] argv[0];
    // delete[] argv;

    Task *mainTask = taskManager.makeTask(0, 1, 0);
    Task *task1 = taskManager.makeTask(&TaskTest::count, 11, argv);
    Task *task2 = taskManager.makeTask(&TaskTest::ask, 12, argv);

    taskManager.initialize();
    interruptManager.initialize();

    // uint64 address = &Kernel::initialize;
    // VGA vga;
    // vga.setupVideoMode();
    // vga.drawRectangle(0,0, 320, 200, VGAColor::CYAN);
}

void Kernel::start()
{
    asm("int $0x81");
    asm ("sti");
}

int Kernel::hlt(int argc, char **argv)
{
    
    asm("_cpp_stop:");
    asm("hlt");
    // printf("Kernel waiting");
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
