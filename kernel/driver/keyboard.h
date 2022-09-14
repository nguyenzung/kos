#ifndef KEYBOARD
#define KEYBOARD

#include "../utils.h"
#include "../type.h"

class Keyboard {
protected:
    char keys[16];
    // static Keyboard *instance;
    DEF_MODULE_INSTANCE(Keyboard)
public:


    Keyboard();
    ~Keyboard();

    void onTranslateScanCode(uint8 code);
    void onKeyDown(char c);
};

#endif