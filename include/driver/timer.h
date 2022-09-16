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
};
}
#endif