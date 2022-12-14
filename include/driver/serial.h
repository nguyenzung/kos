#ifndef SERIAL_H
#define SERIAL_H

#include <kernel/basedriver.h>
#include <kernel/type.h>
#include <kernel/utils.h>

using namespace kernel;

namespace driver {

class SERIAL : public BaseDriver
{
    // DateTime dateTime;                                                                                                                             

public:
    SERIAL();
    ~SERIAL();
    
    DEF_MODULE_INSTANCE(SERIAL)

    void active();
    void deactive();
    void handleInterrupt();

    // void set                                                                                                                                       
    bool isBufferNull();
    void send(char a);
    void printSerial(char *msg);
    void println();
    void printNumber(uint64 number);

};



template <typename... Args>
void log(const char *format, Args... args)
{
    
}

}
#endif
