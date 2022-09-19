#ifndef TASK_MANAGER
#define TASK_MANAGER

#include <kernel/task.h>
#include <datastructure/list.h>

#define STACK_SIZE 1 << 20  // 1MB for stack size

namespace kernel 
{

class TaskManager
{
protected:
    ds::List list;

public:
    TaskManager();
    ~TaskManager();
    static Task* makeTask(void *entryPoint);
    void addTask(Task *task);
    void active();

protected:
   /*
    *   Find position of new task in the list. Return prev task address
    */
    Task* findTaskPosition();   
};

}

#endif