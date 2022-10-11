#include <kernel/processmanager.h>

using namespace kernel;

ProcessManager::ProcessManager()
{
    this->processes = new std::UnorderedMap<uint64, Process*>();
}

ProcessManager::~ProcessManager()
{
    if (this->processes)
        delete this->processes;
}

void ProcessManager::initialize()
{
    this->processes = new std::UnorderedMap<uint64, Process*>();
}