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
  Printer::printf("after bootup config byte is %d\n", ret);

  // 4. Self test
  waitToWrite();
  outb(STATUS_REG, TEST_MOUSE_REQ);
  ret = read();
  Printer::printf("test mouse result %d expect 0x00 \n", ret, MOUSE_OK);
  // 5. Enable MOUSE
  waitToWrite();
  outb(STATUS_REG, ENABLE_MOUSE);

  // 6. Set Compaq Status/Enable IRQ12
  waitToWrite();
  outb(STATUS_REG, READ_CONF_REQ);
  waitToRead();
  ret = read();
  ret |= (1 << INTERRUPT_BIT);
  Printer::printf(" setting to mouse 0x60 %d\n", ret);
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
  if (enableScrollWheel() == false) {
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
        Printer::printf("mouseID after enable scroll wheeling %d\n", mouseID);
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
  // disable interrupt
  asm volatile("cli");
  int value = inb(0x60);
  onTranslateCode(value);
  uint8 status = inb(0x64);
  uint8 mouse_byte[3] = {0, 0, 0};
  int i = 0;

  while (status & 0x01) {
    int mouse_in = inb(0x60);
    // Printer::printf("mouse data %d , i %d\n", mouse_in, i);
    if (status & 0x20)
      switch (i) {
      case 3:
      case 7:
        mouse_byte[0] = mouse_in;
        break;
      case 4:
      case 8:
        mouse_byte[1] = mouse_in;
        break;
      case 5:
      case 9:
        mouse_byte[2] = mouse_in;
        break;
      case 6:
      case 10:
        if (mouse_byte[0] & 0x80 || mouse_byte[0] & 0x40)
          break;
        if (mouse_in == 15) {
          Printer::printf(" scroll up %d ", mouse_in);
          break;
        } else if (mouse_in == 1) {
          Printer::printf(" scroll down ");
          break;
        }
        if ((mouse_byte[0] & 0x20)) {
          mouse_byte[2] = 255 - mouse_byte[2];
          Printer::printf(" down %d ", mouse_byte[2]);
        } else {
          Printer::printf(" up %d ", mouse_byte[2]);
        }

        if (mouse_byte[0] & 0x10) {
          mouse_byte[1] = 255 - mouse_byte[1];
          Printer::printf(" left %d ", mouse_byte[1]);
        } else {
          Printer::printf(" right %d ", mouse_byte[1]);
        }

        Printer::printf("\n\0");
      default:
        break;
      }
    i++;
    status = inb(0x64);
  }
  // enable interrupt
  asm volatile("sti");
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
