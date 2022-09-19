#ifndef TASK_MANAGER
#define TASK_MANAGER

#include <kernel/task.h>
#include <kernel/utils.h>
#include <datastructure/list.h>

#define TASK_STACK_SIZE 1 << 20  // 1MB for stack size

namespace kernel 
{

class TaskManager
{
protected:
    ds::List list;

public:

    TaskManager();
    ~TaskManager();

    DEF_MODULE_INSTANCE(TaskManager);

    Task* makeTask(mainFuntion entryPoint);
    void active();
    void save(void *address);

protected:
   /*
    *   Find position of new task in the list. Return prev task address
    */
    ds::Node* findTaskPosition();   
};

}

#endif