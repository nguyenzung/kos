#ifndef KEYBOARD
#define KEYBOARD

#include "../type.h"

class Keyboard {
protected:
    char keys[16];
    static Keyboard *instance;

public:
    Keyboard();
    ~Keyboard();

    void onTranslateScanCode(uint8 code);
    void onKeyDown(char c);
};

#endif