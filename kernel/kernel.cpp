#include <kernel/kernel.h>
#include <kernel/type.h>
#include <kernel/printer.h>
#include <driver/vga.h>
#include <kernel/utils.h>
#include <kernel/kernelobject.h>
#include <stdlib/list.h>
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
    argv[0] = new char[4];
    argv[0][0] = 'm';
    argv[0][1] = 'a';
    argv[0][2] = 'i';
    argv[0][3] = 'n';
    // delete argv[0];
    // delete argv;

    Task *mainTask = taskManager.makeTask(0, 1, 0);
    Task *task1 = taskManager.makeTask(&counter, 11, argv);
    Task *task2 = taskManager.makeTask(&ask, 12, argv);
    Printer::println(argv[0], 4);
    //Printer::println(" OK ", 4);
    // Printer::println(" OK ", 4);
    char address[] = "vietnam";
    printf("integer %d \n address %p \n string %s \n", 2022,
                    mainTask->context.rbp, address);

    Printer::printlnAddress(mainTask->context.rbp);
    Printer::printlnAddress(task1->context.rbp);

    taskManager.initialize();
    interruptManager.initialize();

    // VGA vga;
    // vga.setupVideoMode();
    // vga.drawRectangle(0,0, 320, 200, VGAColor::CYAN);
}

void Kernel::start()
{
    asm("int $0x81");
    asm ("sti");
    Printer::println("Bad news", 8);
}

int Kernel::hlt(int argc, char **argv)
{
    Printer::println("Good news", 8);
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

void debug()
{
    Printer::println(" [DEBUG]", 8);
}
