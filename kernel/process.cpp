#include <kernel/process.h>
#include <kernel/processmanager.h>
#include <kernel/taskmanager.h>

kernel::Process::Process(
        uint64 pid,
        HeapMemoryManager *heapMemoryManager, 
        VirtualMemory *virtualMemory, 
        uint64 memorySize,
        uint64 heapBase,
        uint64 heapSize,
        uint64 stackBottom,
        uint64 stackBase,
        uint64 stackSize, 
        mainFunction entryPoint, 
        int argc, 
        char **argv,
        OSSpace space)
    :
      pid(pid),
      stackSize(stackSize),
      heapMemoryManager(heapMemoryManager),
      virtualMemory(virtualMemory),
      memorySize(memorySize),
      heapBase(heapBase),
      heapSize(heapSize),
      stackBottom(stackBottom),
      stackBase(stackBase),
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
    createTask(entryPoint, argc, argv);    
}

void kernel::Process::initializeHeapManagement()
{
    if (!heapMemoryManager)
        heapMemoryManager = new HeapMemoryManager();
}

void kernel::Process::initializeVirtualMemory()
{
    if (!virtualMemory)
    {
        virtualMemory = new VirtualMemory();
        virtualMemory->initialize(memorySize, space);
    }
}

void kernel::Process::initializeGDT()
{
    if (!gdt)
        gdt = new GDT();
}

kernel::Task* kernel::Process::createTask(mainFunction entryPoint, int argc, char **argv)
{
    std::Node<Task*>* prevNode = this->findTaskPosition();
    Task *newTask = new Task(this, entryPoint, argc, argv);
    if(!newTask)
        return nullptr;
    
    if (prevNode)
    {
        Task *prevTask = (Task*)prevNode->value;
        if (stackBottom + stackSize > prevTask->stackBase + TASK_STACK_SIZE)
            newTask->initialize(prevTask->stackBase + TASK_STACK_SIZE);
        else
            return nullptr;
    } else
    {
        if (tasks.size() == 0)
            newTask->initialize((uint64)stackBase);
        else
            return nullptr;
    }
    tasks.addNodeAfter(prevNode, new std::Node<Task*>(newTask));
    TaskManager::getInstance()->addTask(newTask);
}

std::Node<Task*>* kernel::Process::findTaskPosition()
{
    std::Node<Task*> *currentNode = tasks.getFirst();
    if (currentNode)
    {
        std::Node<Task*> *nextNode = tasks.next();
        while (nextNode)
        {
            Task *currentTask = (Task*)currentNode->value;
            Task* nextTask = (Task*)nextNode->value;
            if (nextTask->stackBase - currentTask->stackBase >= TASK_STACK_SIZE * 2)
            {
                return currentNode;
            }
            currentNode = nextNode;
            nextNode = tasks.next();
        }
    }
    return currentNode;
}

void kernel::Process::onTaskFinished(Task *task)
{
    this->tasks.removeNodeByValue(task);
    if (this->tasks.size() == 0)
        ProcessManager::getInstance()->onProcessFinished(this);
}