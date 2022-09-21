#include <kernel/task.h>
#include <kernel/printer.h>

Task::Task()
{

}

Task::Task(mainFunction entryPoint, int argc, char **argv)
{
    this->context.rip = (uint64)entryPoint;
    this->context.argc = argc;
    this->context.argv = argv;
}

Task::~Task()
{
}

void Task::initialize(uint64 rbp)
{
    this->context.rbp = rbp;
    this->context.rsp = rbp;
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

void Task::run()
{
    
}