#ifndef TASK
#define TASK

#include <kernel/kernelobject.h>
#include <kernel/context.h>
#include <kernel/type.h>

using namespace kernel;


class Process;
class Task : public KernelObject
{
public:
    Process*    process;
    uint16      taskID;
    int         argc;
    char**      argv;
public:
    Context context;

public:
    Task();
    Task(mainFunction entryPoint, int argc, char **argv);
    ~Task();

    void initialize(uint64 rbp);
    void save(uint64 *address);
    void load(uint64 *address);
    void run();
};

#endif