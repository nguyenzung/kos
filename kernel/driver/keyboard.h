#ifndef KEYBOARD
#define KEYBOARD

#include "../utils.h"
#include "../type.h"
#include "../basedriver.h"
#include "../interrupthandler.h"

class Keyboard : public kernel::BaseDriver {
protected:
    char keys[16];
    // static Keyboard *instance;
    // DEF_MODULE_INSTANCE(Keyboard)
public:

    Keyboard();
    ~Keyboard();

    void active();
    void deactive();
    void handleInterrupt();

    void onTranslateScanCode(uint8 code);
    void onKeyDown(char c);
};

#endif