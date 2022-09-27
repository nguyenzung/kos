#include <driver/mouse.h>
#include <kernel/interruptmanager.h>
#include <kernel/iocommand.h>
#include <kernel/printer.h>

using namespace kernel;
using namespace driver;
void mouse_install();

Mouse::Mouse() : BaseDriver() { vector = IRQ_NUM + OFFSET; }

Mouse::~Mouse() { deactive(); }

bool Mouse::initializePS2Controler() {
  uint8 ret = 0;
  // 1. disable device
  // any PS/2 devices can't send data at the wrong time and mess up your
  // initialisation
  deactive();

  // 2. flush the output buffer
  (void)read();

  // 3. Set the Controller Configuration Byte
  waitToWrite();
  outb(READ_CONF_REQ, TEST_MOUSE_REQ);
  ret = read();
  // Printer::printf("after bootup config byte is %d\n", ret);

  // 4. Self test
  waitToWrite();
  outb(STATUS_REG, TEST_MOUSE_REQ);
  ret = read();
  // Printer::printf("test mouse result %d expect 0x00 \n", ret, MOUSE_OK);
  // 5. Enable MOUSE
  waitToWrite();
  outb(STATUS_REG, ENABLE_MOUSE);

  // 6. Set Compaq Status/Enable IRQ12
  waitToWrite();
  outb(STATUS_REG, READ_CONF_REQ);
  waitToRead();
  ret = read();
  ret |= (1 << INTERRUPT_BIT);
  // Printer::printf(" setting to mouse 0x60 %d\n", ret);
  waitToWrite();
  outb(STATUS_REG, WRITE_CONF_REQ);
  waitToWrite();
  outb(PORT_REG, ret);

  // request to set default config

  // writeCmd(DEFAULT_CONF_REQ);

  // enable package streaming
  writeCmd(PACKAGE_STREAM_REQ);
  read();

  return true;
}
void Mouse::active() {
  uint8 status;
  initializePS2Controler();
  if (!enableScrollWheel()) {
    Printer::printf("couldn't enable scrool wheel\n\0");
  }
}

bool Mouse::enableScrollWheel() {
  uint8 mouseID = 0;
  writeCmd(GET_MOUSE_ID_REQ);
  mouseID = read();
  if (isCmdSuccess(mouseID)) {
    mouseID = read();
    // setup if mouse scroll wheeling haven't enabled yet
    if (mouseID == 0) {
      // set sample rate
      auto func = [this](uint8 rate) {
        writeCmd(SET_SAMPLERATE_REQ);
        int mouseID = read();
        writeCmd(rate);
        (void)read();
      };

      // for below magic numbers follow osdev
      // https://wiki.osdev.org/Mouse_Input#Init.2FDetection_Command_Sequences
      func(200);
      func(200);
      func(80);

      writeCmd(0xF2);
      mouseID = 0;
      // ack
      if (isCmdSuccess(read())) {
        mouseID = read();
        // Printer::printf("mouseID after enable scroll wheeling %d\n", mouseID);
      } else {
        Printer::print("failed to query mouseID\n");
      }
    } else {
    }
  } else {
    Printer::printf("mouse ack failed %d\n", mouseID);
  }

  return true;
}
void Mouse::deactive() { outb(STATUS_REG, DISABLE_MOUSE); }

void Mouse::handleInterrupt() {
  uint8 status = inb(0x64);
  uint8 mouse_byte[3] = {0, 0, 0};
  int i = 0;
  xAxis = yAxis = zAxis = 0;
  button = 0;

  while (status & 0x01) {
    int mouse_in = inb(0x60);
    // Printer::printf("mouse data %d , i %d\n", mouse_in, i);
    if (status & 0x20)
      switch (i % 4) {
      case 0:
        mouse_byte[0] = mouse_in;
        break;
      case 1:
        mouse_byte[1] = mouse_in;
        break;
      case 2:
        mouse_byte[2] = mouse_in;
        break;
      case 3:
        if (mouse_byte[0] & 0x80 || mouse_byte[0] & 0x40)
          break;
        if (mouse_in == 15) {
          zAxis = SC_DOWN;
          break;
        } else if (mouse_in == 1) {
          zAxis = SC_UP;
          break;
        }
        if ((mouse_byte[0] & 0x20)) {
          mouse_byte[2] = 255 - mouse_byte[2];
          yAxis = -1 * mouse_byte[2];
        } else {
          yAxis = mouse_byte[2];
        }

        if (mouse_byte[0] & 0x10) {
          mouse_byte[1] = 255 - mouse_byte[1];
          xAxis = -1 * mouse_byte[1];
        } else {
          xAxis = mouse_byte[1];
        }

        if (mouse_byte[0] & 0x01) {
          button |= LEFT_CLICK;
        }
        if (mouse_byte[0] & 0x02) {
          button |= RIGHT_CLICK;
        }
        if (mouse_byte[0] & 0x04) {
          button |= MIDDLE_CLICK;
        }

      default:
        break;
      }
    i++;
    status = inb(STATUS_REG);
  }
  // doNotify();
}

void Mouse::doNotify() {
  if (zAxis != 0) {
    if (zAxis > 0)
      Printer::print("scroll up\n");
    else
      Printer::print("scroll down\n");
  } else if (xAxis || yAxis) {
    Printer::printf("pointer move : ");
    if (xAxis > 0)
      Printer::printf("right [%d] ", xAxis);
    else if (xAxis < 0)
      Printer::printf("left [%d] ", -1 * xAxis);

    if (yAxis > 0)
      Printer::printf("up [%d] ", yAxis);
    else if (yAxis < 0)
      Printer::printf("down [%d] ", -1 * yAxis);
  }
  switch (button) {
  case LEFT_CLICK:
    Printer::printf("left click ");
    break;
  case RIGHT_CLICK:
    Printer::printf("right click ");
    break;
  case MIDDLE_CLICK:
    Printer::printf("middle click ");
    break;
  default:
    break;
  }
  Printer::printf("\n");
}
void Mouse::onTranslateCode(uint8 code) {}

void Mouse::waitToRead() {
  uint32 timeout = WAITTING_TIMEOUT;
  while (--timeout) {
    if ((inb(STATUS_REG) & OUTPUT_BUF_BIT) == 1) {
      return;
    }
  }
}

void Mouse::waitToWrite() {
  uint32 timeout = WAITTING_TIMEOUT;
  while (--timeout) {
    if (!((inb(STATUS_REG) & INPUT_BUF_BIT))) {
      return;
    }
  }
}

void Mouse::writeCmd(uint8 byte) {
  waitToWrite();
  outb(STATUS_REG, MOUSE_ADDR);
  waitToWrite();
  outb(PORT_REG, byte);
}

uint8 Mouse::read() {
  waitToRead();
  return inb(PORT_REG);
}
