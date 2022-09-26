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
    argv[0] = new char[4];
    argv[0][0] = 'm';
    argv[0][1] = 'a';
    argv[0][2] = 'i';
    argv[0][3] = 'n';
    // delete[] argv[0];
    // delete[] argv;

    Task *mainTask = taskManager.makeTask(0, 1, 0);
    Task *task1 = taskManager.makeTask(&counter, 11, argv);
    Task *task2 = taskManager.makeTask(&ask, 12, argv);
    printf(" [TASK ] mainTask %d task1 %d task2 %d", mainTask, task1, task2);
    Printer::println(argv[0], 4);

    taskManager.initialize();
    interruptManager.initialize();

    std::UnorderedMap<uint64, uint64> map;
    map.put(1, 1001);
    map.put(5400, 1002);
    printf("[MAP CHECK ] %d \n", map.contains(5400));
    printf("[MAP CHECK ] %d \n", map.contains(1));
    printf("[MAP GET ] %d \n", map.get(1)->value);
    map.remove(5400);
    printf("[MAP CHECK ] %d \n", map.contains(5400));
    map[23]= 69;
    printf(" \n [MAP BIND ] %d \n", map[23].key);
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
