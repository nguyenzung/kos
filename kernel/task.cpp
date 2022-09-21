#include <kernel/task.h>
#include <kernel/printer.h>

Task::Task()
{

}

Task::Task(mainFunction entryPoint, int argc, char **argv)
{
    this->context.rip = (uint64)entryPoint;
    this->argc = argc;
    this->argv = argv;
}

Task::~Task()
{
}

void Task::initialize(uint64 rbp)
{
    this->context.rbp = rbp;
    this->context.rsp = rbp;
}

void Task::save(uint64 *address)
{
    this->context.save(address);
}

void Task::load(uint64 *address)
{
    this->context.load(address);
}

void Task::run()
{
    
}