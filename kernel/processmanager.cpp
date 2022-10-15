#include <kernel/processmanager.h>
#include <kernel/printer.h>

using namespace kernel;

IMPL_MODULE_INSTANCE(ProcessManager)

ProcessManager::ProcessManager()
    :current(0)
{
    ProcessManager::instance = this;
}

ProcessManager::~ProcessManager()
{
    if (processes)
        delete processes;
}

void ProcessManager::initialize()
{
    processes = new std::UnorderedMap<uint64, Process*>();
}

Process* ProcessManager::find(uint64 pid)
{
    return processes->contains(pid) ? (*processes)[pid].second : nullptr;
}

Process* ProcessManager::makeProcess(
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
        OSSpace osspace)
{
    Process *process = new Process(
                current,
                heapMemoryManager,
                virtualMemory,
                memorySize,
                heapBase,
                heapSize,
                stackBottom,
                stackBase,
                stackSize,
                entryPoint,
                argc,
                argv,
                osspace);
    (*processes)[current++] = process;
    process->initialize();
    return process;
}

bool ProcessManager::onProcessFinished(Process *process)
{
    processes->erase(process->pid);
    delete process;
}

uint64 kernel::makeProcess(
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
        OSSpace osspace)
{
    return ProcessManager::getInstance()->makeProcess(
                heapMemoryManager,
                virtualMemory,
                memorySize,
                heapBase,
                heapSize,
                stackBottom,
                stackBase,
                stackSize,
                entryPoint, 
                argc,
                argv,
                osspace)->pid;
}

Task* kernel::makeThread(uint64 pid, mainFunction entryPoint, int argc, char** argv)
{
    Process *process = ProcessManager::getInstance()->find(pid);
    return process->createTask(entryPoint, argc, argv);
}

