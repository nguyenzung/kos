#ifndef TASK_MANAGER
#define TASK_MANAGER

#include <kernel/task.h>
#include <kernel/utils.h>
#include <stdlib/list.h>

#define TASK_STACK_SIZE (1 << 20)  // 1MB for stack size

namespace kernel 
{

class Process;
class TaskManager
{
protected:
    std::List<Task*> list;

public:
    uint64 saveCounter;

    TaskManager();
    ~TaskManager();

    DEF_MODULE_INSTANCE(TaskManager)

//    Task* makeTask(Process *process, mainFunction entryPoint, int argc, char** argv);
    Task* addTask(Task *task);
    void initialize();
    void save(uint64 *address);
    void load(uint64 *address);

    void saveMainKernel(uint64 *address);
    void loadMainKernel(uint64 *address);

    void removeTask(Task *task);

    void contextInfo();

    // static int runTask(mainFunction entryPoint, int argc, char **argv);
    static int runTask(Task *task);

protected:
   /*
    *   Find position of new task in the list. Return prev task address
    */
//    std::Node<Task*>* findTaskPosition();   
};

}

#endif
