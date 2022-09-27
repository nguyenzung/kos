#ifndef TIMER
#define TIMER

#include <kernel/basedriver.h>

namespace driver {

class Timer : public kernel::BaseDriver {

public:
    Timer();
    ~Timer();

    void active();
    void deactive();
    void handleInterrupt();

    // void set  
    int get_update_in_progress_flag();
    unsigned char get_RTC_register(int reg);

    
};
}
#endif
