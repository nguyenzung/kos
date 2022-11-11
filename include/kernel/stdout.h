#ifndef STDOUT_H
#define STDOUT_H

#include <kernel/utils.h>
#include <stdlib/list.h>

namespace kernel
{

class BaseOutput
{
    
};

class ScreenOutput : public BaseOutput
{
public:
    std::List<const char*> messages;
    
    void add(const char *message);
    const char* consume();
};

class StdOut 
{
public:
    
    
    StdOut();
    
};
}

#endif // STDOUT_H
