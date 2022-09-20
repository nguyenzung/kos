#include <kernel/kernel.h>
#include <kernel/type.h>
#include <kernel/printer.h>
#include <driver/vga.h>
#include <kernel/utils.h>
#include <kernel/kernelobject.h>
#include <datastructure/list.h>
#include <tasks/counter.h>

using namespace kernel;

extern void* heapBase;
extern void* stackBase;

Kernel* Kernel::instance = 0;

Kernel::Kernel()
    :Context()
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

void Kernel::startKernel()
{
    // Printer::printlnNumber(testAsm);
    this->rbp = (uint64)stackBase;

    heapMemoryManager.initialize();
    deviceManager.initialize();
    taskManager.initialize();
    interruptManager.initialize();

    // this->rbp = ;

    char *argv[]= {"counter"};
    Task *task1 = taskManager.makeTask(&counter, 1, argv);
    Task *task2 = taskManager.makeTask(&counter, 1, argv);
    Task *task3 = taskManager.makeTask(&counter, 1, argv);
    Printer::println(" OK ", 4);
    Printer::printlnAddress(task1->context.rbp);
    Printer::printlnAddress(task2->context.rbp);
    Printer::printlnAddress(task3->context.rbp);

    // taskManager.switchTask();
    // VGA vga;
    // vga.setupVideoMode();
    // vga.drawRectangle(0,0, 320, 200, VGAColor::CYAN);
}

void Kernel::hlt()
{
    uint64 testAsm = 12;
    asm("movq %%rsp, %0":"=m"(testAsm)::);
    Printer::print(" HTL ", 5);
    Printer::printlnAddress(testAsm);
    asm ("_cpp_stop:; hlt; jmp _cpp_stop;");
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
