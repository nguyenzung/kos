#ifndef BASE_DRIVER
#define BASE_DRIVER

#include <kernel/interrupthandler.h>
namespace kernel 
{

class BaseDriver : public InterruptHandler
{
private:
public:
    BaseDriver(uint8 vector = 0xff);
    ~BaseDriver();

    virtual void active() = 0;
    virtual void deactive() = 0;
};

}
#endif