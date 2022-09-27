#ifndef TIMER
#define TIMER

#include <kernel/basedriver.h>
#include <kernel/type.h>

namespace driver {



class Timer : public kernel::BaseDriver 
{
    // DateTime dateTime;

public:
    Timer();
    ~Timer();

    void active();
    void deactive();
    void handleInterrupt();

    // void set  
    

};
}
#endif
