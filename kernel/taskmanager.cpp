#include <kernel/taskmanager.h>
#include <kernel/kernel.h>
#include <kernel/kernelobject.h>
#include <kernel/process.h>
#include <kernel/printer.h>
#include <stdlib/lock.h>

extern void* stackBase;

IMPL_MODULE_INSTANCE(TaskManager)

TaskManager::TaskManager()
{
    saveCounter = 0;
    TaskManager::instance = this;
}

TaskManager::~TaskManager()
{
}

Task* TaskManager::addTask(Task *task)
{
    list.add(task);
    if (list.getCurrent() == 0)
    {
        list.getFirstNode();
    }
    return task;
}

void TaskManager::initialize()
{
    this->list.getFirstNode();
}

void TaskManager::save(uint64 *address)
{
    if(this->saveCounter == 0)
    {
        std::Node<Task*> *node = this->list.current;
        if (node)
        {
            Task *task = (Task*)node->value;
            task->save(address);
        }
    }
    this->saveCounter++;
}

void TaskManager::load(uint64 *address)
{
    this->saveCounter--;
    if(this->saveCounter == 0)
    {
        std::Node<Task*> *node = this->list.next();
        if (!node)
        {
            node = this->list.getFirstNode();
        }
        if (node)
        {
            Task *task = (Task*)node->value;
//            printf("\n Load %d ", task);
            task->load(address);
        }
    }
}

void TaskManager::saveMainKernel(uint64 *address)
{
    if(this->saveCounter == 0)
    {
        std::Node<Task*> *node = this->list.first;
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
        std::Node<Task*> *node = this->list.first;
        Task *task = (Task*)node->value;
        task->load(address);
    }
}

void TaskManager::removeTask(Task *task)
{
//    LOCK(taskList);
    this->list.removeNodeByValue(task);
//    UNLOCK(taskList);
}

void TaskManager::contextInfo() {
    Task *task = (Task*)this->list.current->value;
    task->context.info();
}

int TaskManager::runTask(Task *task)
{
    printf("\n Start run task %d %d ", task, task->context.entryPoint);
    int result = task->context.entryPoint(task->context.argc, task->context.argv);
    printf("\n Result %d: %d", result, task->context.argc);
    driver::SERIAL::getInstance()->printSerial("\nFinish a task: ");
    driver::SERIAL::getInstance()->printNumber(result);
    asm("cli");
    task->onFinished();
    TaskManager::getInstance()->removeTask(task);
    asm("sti");
    while (true)
    {
        asm("hlt");
    }
    return 0;
}
