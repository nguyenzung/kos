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

void Kernel::initialize()
{
    Printer::printlnNumber((uint64)(Kernel::getInstance));
    this->rbp = (uint64)stackBase;

    heapMemoryManager.initialize();
    deviceManager.initialize();
    

    // this->rbp = ;

    char *argv[]= {"counter"};
    Task *mainTask = taskManager.makeTask(&Kernel::hlt, 1, 0);
    // Task *task1 = taskManager.makeTask(&counter, 1, argv);
    Printer::println(" OK ", 4);
    Printer::printlnAddress(mainTask->context.rbp);
    // Printer::printlnAddress(task1->context.rbp);

    taskManager.initialize();
    interruptManager.initialize();
    // asm ("sti");
    // taskManager.switchTask();
    // VGA vga;
    // vga.setupVideoMode();
    // vga.drawRectangle(0,0, 320, 200, VGAColor::CYAN);
}

void Kernel::start()
{
    asm ("sti");
    asm("int $0x81");
    Printer::println("Bad news", 8);
}

int Kernel::hlt(int argc, char **argv)
{
    Printer::println("Good news", 9);
    asm("_cpp_stop:");
    asm("hlt");
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
