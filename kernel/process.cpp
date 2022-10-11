#include <kernel/process.h>
#include <kernel/taskmanager.h>

kernel::Process::Process(
        uint64 pid,
        HeapMemoryManager *heapMemoryManager, 
        VirtualMemory *virtualMemory, 
        uint64 memorySize, 
        uint64 stackSize, 
        mainFunction entryPoint, 
        int argc, 
        char **argv,
        OSSpace space)
    :
      pid(pid),
      memorySize(memorySize),
      stackSize(stackSize),
      heapMemoryManager(heapMemoryManager),
      virtualMemory(virtualMemory),
      entryPoint(entryPoint),
      argc(argc),
      argv(argv),
      space(space)
{
}

kernel::Process::~Process()
{
}

void kernel::Process::initialize()
{
    if (!heapMemoryManager)
        heapMemoryManager = new HeapMemoryManager();
    if (!virtualMemory)
    {
        virtualMemory = new VirtualMemory();
        virtualMemory->initialize(memorySize, space);
    }
    
    // TODO: init memory for
    createTask(entryPoint, argc, argv);    
}

kernel::Task* kernel::Process::createTask(mainFunction entryPoint, int argc, char **argv)
{
    TaskManager *taskManager = TaskManager::getInstance();
    Task *task = taskManager->makeTask(this, entryPoint, argc, argv);
    this->tasks.add(task);
}

void kernel::Process::onTaskFinish(Task *task)
{
    
}