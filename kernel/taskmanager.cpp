#include <kernel/taskmanager.h>
#include <kernel/kernel.h>
#include <kernel/printer.h>

extern void* stackBase;

IMPLE_MODULE_INSTANCE(TaskManager)

TaskManager::TaskManager()
{
    TaskManager::instance = this;
}

TaskManager::~TaskManager()
{
}

Task* TaskManager::makeTask(mainFuntion entryPoint)
{
    ds::Node* prevNode = this->findTaskPosition();
    Task *newTask = new Task(entryPoint);
    if (prevNode)
    {
        Task *prevTask = (Task*)prevNode->value;
        newTask->rbp = prevTask->rbp + TASK_STACK_SIZE;
    } else
    {
        newTask->rbp = (uint64)stackBase + TASK_STACK_SIZE;
    }
    list.addNodeAfter(prevNode,new ds::Node(newTask));
    return newTask;
}

void TaskManager::active()
{

}

void TaskManager::save(void *address)
{
    Printer::print(" SAVE ", 6);
    Printer::printlnNumber((uint64)address);
}

ds::Node* TaskManager::findTaskPosition()
{
    ds::Node *currentNode = list.begin();
    if (currentNode)
    {
        ds::Node *nextNode = list.next();
        while (nextNode)
        {
            Task *currentTask = (Task*)currentNode->value;
            Task* nextTask = (Task*)nextNode->value;
            if (nextTask->rbp - currentTask->rbp >= TASK_STACK_SIZE * 2)
            {
                return currentNode;
            }
            currentNode = nextNode;
            nextNode = list.next();
        }
    }
    return currentNode;
}