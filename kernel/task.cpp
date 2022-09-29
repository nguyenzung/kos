#include <kernel/task.h>
#include <kernel/taskmanager.h>
#include <kernel/printer.h>

Task::Task()
{

}

Task::Task(mainFunction entryPoint, int argc, char **argv)
{
    this->context.rip = (uint64)(&TaskManager::runTask);
    this->context.entryPoint = entryPoint;
    this->context.argc = argc;
    this->context.argv = argv;
    this->context.task = (uint64)this;
}

Task::~Task()
{
}

void Task::initialize(uint64 rbp)
{
    this->context.rbp = rbp;
    this->context.rsp = rbp;
    printf("\n [Task init] %d %d %d %d", this->context.rbp, this->context.rsp, this->context.rip, this);
    this->context.initialize();
}

void Task::save(uint64 *address)
{
    this->context.save(address);
}

void Task::load(uint64 *address)
{
    this->context.load(address);
}
