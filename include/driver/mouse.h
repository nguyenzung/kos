#ifndef MOUSE
#define MOUSE

#include <kernel/basedriver.h>
#include <kernel/type.h>
#include <kernel/utils.h>

using namespace kernel;

namespace driver {

class Mouse : public kernel::BaseDriver {
private:
  void waitToWrite();
  void waitToRead();
  bool enableScrollWheel();
  void doNotify();
  bool initializePS2Controler();
  void writeCmd(uint8 byte);
  uint8 read();
  inline bool isCmdSuccess(uint8 ret_val) { return ret_val == MOUSE_CMD_OK; }
  void onTranslateCode(uint8 code);
  void setSampleRate(uint8 rate);

protected:

public:
  enum REGISTERS {
    IRQ_NUM = 12,
    PORT_REG = 0x60,
    STATUS_REG = 0x64,
    OUTPUT_BUF_BIT = 0x01,
    INPUT_BUF_BIT = 0x02,
    MOUSE_ADDR = 0xD4,
    WAITTING_TIMEOUT = 100000,
    INTERRUPT_BIT = 1
  };
  enum CMDS {
    WRITE_CONF_REQ = 0x60,
    ENABLE_MOUSE = 0xA8,
    DISABLE_MOUSE = 0xA7,
    READ_CONF_REQ = 0x20,
    DEFAULT_CONF_REQ = 0xF6,
    TEST_MOUSE_REQ = 0xA9,
    PACKAGE_STREAM_REQ = 0xF4,
    GET_MOUSE_ID_REQ = 0xF2,
    SET_SAMPLERATE_REQ = 0xF3
  };

  enum CODES { MOUSE_OK = 0x00, MOUSE_CMD_OK = 0xFA };

  Mouse();
  ~Mouse();

  void active();
  void deactive();
  void handleInterrupt();
};
} // namespace driver
#endif
