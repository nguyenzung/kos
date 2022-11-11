#ifndef STDIO_H
#define STDIO_H

#include <kernel/stdout.h>
#include <kernel/stdin.h>

namespace kernel
{

class StdIO
{
protected:
    StdIn in;
    StdOut out;
    
public:
    StdIO();
    ~StdIO();
};

}

#endif // STDIO_H
