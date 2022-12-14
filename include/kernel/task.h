#ifndef TASK
#define TASK

#include <kernel/kernelobject.h>
#include <kernel/context.h>
#include <kernel/type.h>

namespace kernel
{

class Process;
class Task : public KernelObject
{
public:
    Process*    process;
    uint64      stackBase;
    uint16      taskID;

public:
    Context context;

public:
    Task(Process *process);
    Task(Process *process, mainFunction entryPoint, int argc, char **argv);
    ~Task();

    void initialize(uint64 stackBase);
    void save(uint64 *address);
    void load(uint64 *address);
    
    void onFinished();
    
    friend class Process;
};

}

#endif