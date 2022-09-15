#include "keyboard.h"
#include "../printer.h"

IMPLE_MODULE_INSTANCE(Keyboard)

Keyboard::Keyboard() {
    Keyboard::setInstance(this);
}

Keyboard::~Keyboard() {

}

void Keyboard::onTranslateScanCode(uint8 code) {
    if(code < 0x80)
    {
        switch(code)
        {
            case 0x02: this->onKeyDown('1'); break;
            case 0x03: this->onKeyDown('2'); break;
            case 0x04: this->onKeyDown('3'); break;
            case 0x05: this->onKeyDown('4'); break;
            case 0x06: this->onKeyDown('5'); break;
            case 0x07: this->onKeyDown('6'); break;
            case 0x08: this->onKeyDown('7'); break;
            case 0x09: this->onKeyDown('8'); break;
            case 0x0A: this->onKeyDown('9'); break;
            case 0x0B: this->onKeyDown('0'); break;

            case 0x10: this->onKeyDown('q'); break;
            case 0x11: this->onKeyDown('w'); break;
            case 0x12: this->onKeyDown('e'); break;
            case 0x13: this->onKeyDown('r'); break;
            case 0x14: this->onKeyDown('t'); break;
            case 0x15: this->onKeyDown('z'); break;
            case 0x16: this->onKeyDown('u'); break;
            case 0x17: this->onKeyDown('i'); break;
            case 0x18: this->onKeyDown('o'); break;
            case 0x19: this->onKeyDown('p'); break;

            case 0x1E: this->onKeyDown('a'); break;
            case 0x1F: this->onKeyDown('s'); break;
            case 0x20: this->onKeyDown('d'); break;
            case 0x21: this->onKeyDown('f'); break;
            case 0x22: this->onKeyDown('g'); break;
            case 0x23: this->onKeyDown('h'); break;
            case 0x24: this->onKeyDown('j'); break;
            case 0x25: this->onKeyDown('k'); break;
            case 0x26: this->onKeyDown('l'); break;

            case 0x2C: this->onKeyDown('y'); break;
            case 0x2D: this->onKeyDown('x'); break;
            case 0x2E: this->onKeyDown('c'); break;
            case 0x2F: this->onKeyDown('v'); break;
            case 0x30: this->onKeyDown('b'); break;
            case 0x31: this->onKeyDown('n'); break;
            case 0x32: this->onKeyDown('m'); break;
            case 0x33: this->onKeyDown(','); break;
            case 0x34: this->onKeyDown('.'); break;
            case 0x35: this->onKeyDown('-'); break;

            case 0x1C: this->onKeyDown('\n'); break;
            case 0x39: this->onKeyDown(' '); break;

            default:
            {
                Printer::print("KEY PRESS", 10);
                break;
            }
        }
    }else {
        Printer::printAddress(code);
    }
}

void Keyboard::onKeyDown(char c) {
    Printer::print(&c, 1);
}