#ifndef STDIN_H
#define STDIN_H

#include <kernel/utils.h>

namespace kernel
{

class BaseInput
{
    
};

class MouseIn : public BaseInput
{
    
};

class KeyboardIn : public BaseInput
{
    
};

class StdIn
{
public:
    KeyboardIn keyboardInput;
    MouseIn mouseInput;
    
public:
    StdIn();
    ~StdIn();
    
    
};

}

#endif // STDIN_H
