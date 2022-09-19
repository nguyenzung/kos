#include <kernel/taskmanager.h>

using namespace kernel;

TaskManager::TaskManager()
{
}

TaskManager::~TaskManager()
{
}

Task* TaskManager::makeTask(void *entryPoint)
{
    return 0;
}

Task* TaskManager::findTaskPosition()
{
    for(ds::Node *it = list.begin(); it != list.end(); it = list.next())
    {
        
    }
}