#ifndef TASK
#define TASK

#include <kernel/kernelobject.h>
#include <kernel/type.h>

using namespace kernel;

typedef int (*mainFuntion)(int argc, char**argv);

class Process;
class Task : public KernelObject
{
public:
    Process *process;
    uint16 taskID;

public:
    uint64 rax;
    uint64 rbx;
    uint64 rcx;
    uint64 rdx;
    uint64 rsi;
    uint64 rdi;
    uint64 rsp;
    uint64 rbp;
    uint64 r8;
    uint64 r9;
    uint64 r10;
    uint64 r11;
    uint64 r12;
    uint64 r13;
    uint64 r14;
    uint64 r15;

    uint64 rip; // We can load from stack instead of access directly
    
    void* pageAddress;
    void* codeSegment;
    void* dataSegment;
    mainFuntion entryPoint;

public:
    Task(mainFuntion entryPoint);
    ~Task();

    void initialize(uint64 rbp);
    void save(void *address);
    void load();
};

#endif