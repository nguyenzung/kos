#include <kernel/task.h>

Task::Task(mainFuntion entryPoint)
{
    this->entryPoint = entryPoint;
}

Task::~Task()
{
}

void Task::initialize(uint64 rbp)
{
    this->rbp = rbp;
    this->rsp = rbp;
}

void Task::save(void *address)
{
    asm("":"=m"(this->rax)::);
    asm("":"=m"(this->rbx)::);
    asm("":"=m"(this->rcx)::);
    asm("":"=m"(this->rdx)::);
}

void Task::load()
{

}