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

    void active();
    void deactive();
    void handleInterrupt();

    // void set                                                                                                                                       
  void KhoiTaoSerial();
  bool buffer_gui_di_co_null_ko();
  void gui_di(char a);
  void printSerial(char *msg);

};

}
#endif
