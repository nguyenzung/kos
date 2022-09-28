#include <kernel/taskmanager.h>
#include <kernel/kernel.h>
#include <kernel/kernelobject.h>
#include <kernel/printer.h>
#include <stdlib/lock.h>

extern void* stackBase;

IMPL_MODULE_INSTANCE(TaskManager)

DECLARE_LOCK(taskList);

TaskManager::TaskManager()
{
    saveCounter = 0;
    TaskManager::instance = this;
}

TaskManager::~TaskManager()
{
}

Task* TaskManager::makeTask(mainFunction entryPoint, int argc, char** argv)
{
    // LOCK(taskList);
    std::Node<KernelObject*>* prevNode = this->findTaskPosition();
    Task *newTask = new Task(entryPoint, argc, argv);
    if (prevNode)
    {
        Task *prevTask = (Task*)prevNode->value;
        newTask->initialize(prevTask->context.rbp + TASK_STACK_SIZE);
    } else
    {
        newTask->initialize((uint64)stackBase);
    }
    list.addNodeAfter(prevNode,new std::Node<KernelObject*>(newTask));
    if (list.getCurrent() == 0)
    {
        list.getFirst();
    }
    // UNLOCK(taskList);
    return newTask;
}

void TaskManager::initialize()
{
    this->list.getFirst();
}

void TaskManager::save(uint64 *address)
{
    // LOCK(taskList);
    if(this->saveCounter == 0)
    {
        std::Node<KernelObject*> *node = this->list.current;
        if (node)
        {
            Task *task = (Task*)node->value;
            task->save(address);
        }
    }
    this->saveCounter++;
    // UNLOCK(taskList);
}

void TaskManager::load(uint64 *address)
{
    this->saveCounter--;
    if(this->saveCounter == 0)
    {
        std::Node<KernelObject*> *node = this->list.next();
        if (!node)
        {
            node = this->list.getFirst();
        }
        if (node)
        {
            Task *task = (Task*)node->value;
            task->load(address);
        }
    }
}

void TaskManager::saveMainKernel(uint64 *address)
{
    if(this->saveCounter == 0)
    {
        std::Node<KernelObject*> *node = this->list.first;
        Task *task = (Task*)node->value;
        task->save(address);
    }
    this->saveCounter++;
}

void TaskManager::loadMainKernel(uint64 *address)
{    
    this->saveCounter--;
    if(this->saveCounter == 0)
    {
        std::Node<KernelObject*> *node = this->list.first;
        Task *task = (Task*)node->value;
        task->load(address);
    }
}

void TaskManager::removeTask(Task *task)
{
    LOCK(taskList);
    this->list.removeNodeByValue(task);
    UNLOCK(taskList);
}

int TaskManager::runTask(Task *task)
{
    int result = task->context.entryPoint(task->context.argc, task->context.argv);
    asm("cli");
    TaskManager::getInstance()->removeTask(task);
    asm("sti");
    while (true)
    {
        asm("hlt");
    }
    return 0;
}

std::Node<KernelObject*>* TaskManager::findTaskPosition()
{
    LOCK(taskList);
    std::Node<KernelObject*> *currentNode = list.first;
    if (currentNode)
    {
        std::Node<KernelObject*> *nextNode = list.next();
        while (nextNode)
        {
            Task *currentTask = (Task*)currentNode->value;
            Task* nextTask = (Task*)nextNode->value;
            if (nextTask->context.rbp - currentTask->context.rbp >= TASK_STACK_SIZE * 2)
            {
                return currentNode;
            }
            currentNode = nextNode;
            nextNode = this->list.next();
        }
    }
    UNLOCK(taskList);
    return currentNode;
}