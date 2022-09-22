#ifndef TASK_MANAGER
#define TASK_MANAGER

#include <kernel/task.h>
#include <kernel/utils.h>
#include <datastructure/list.h>

#define TASK_STACK_SIZE (1 << 20)  // 1MB for stack size

namespace kernel 
{

class TaskManager
{
protected:
    ds::List list;

public:

    uint64 saveCounter;

    TaskManager();
    ~TaskManager();

    DEF_MODULE_INSTANCE(TaskManager);

    Task* makeTask(mainFunction entryPoint, int argc, char** argv);
    void initialize();
    void save(uint64 *address);
    void load(uint64 *address);
    void saveMainKernel(uint64 *address);
    void loadMainKernel(uint64 *address);

protected:
   /*
    *   Find position of new task in the list. Return prev task address
    */
    ds::Node* findTaskPosition();   
};

}

#endif