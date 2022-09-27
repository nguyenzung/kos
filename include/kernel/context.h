#ifndef CONTEXT
#define CONTEXT

#include <kernel/type.h>


namespace kernel 
{
    typedef int (*mainFunction)(int, char**);
class Context
{
public:
    uint64 ss;
    uint64 cs;
    uint64 flags;
    uint64 rip; // We can load from stack instead of access directly
    uint64 rsp;

    uint64 rax;
    uint64 rbx;
    uint64 rcx;
    uint64 rdx;
    uint64 rsi;
    uint64 rdi;
    
    uint64 r8;
    uint64 r9;
    uint64 r10;
    uint64 r11;
    uint64 r12;
    uint64 r13;
    uint64 r14;
    uint64 r15;

    uint64 rbp;
    uint64 task;
    void* pageAddress;
    uint16 codeSegmentOffset;
    uint16 dataSegmentOffset;
    

    mainFunction entryPoint;
    int argc;
    char **argv;

    Context();
    Context(uint64 rbp, uint64 rsp, mainFunction entryPoint);
    ~Context();

    void initialize();
    void save(uint64 *address);
    void load(uint64 *address);
};
}
#endif