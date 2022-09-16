#ifndef BASE_DRIVER
#define BASE_DRIVER

#include "interrupthandler.h"

class BaseDriver : InterruptHandler
{
private:
public:
    BaseDriver();
    ~BaseDriver();

    virtual void active() = 0;
    virtual void deactive() = 0;
};



#endif