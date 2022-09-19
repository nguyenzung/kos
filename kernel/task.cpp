#include <kernel/task.h>

Task::Task(mainFuntion entryPoint)
{
    this->entryPoint = entryPoint;
}

Task::~Task()
{
}

void Task::save()
{

}

void Task::load()
{

}