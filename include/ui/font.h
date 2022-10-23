#ifndef SYS_FONT
#define SYS_FONT

#include <kernel/type.h>

using namespace kernel;

namespace ui
{

class Font
{
public:
    Font();
    ~Font();
    
    void initialize();
    
    void drawChar(uint8 c, uint16 x, uint16 y);
};

}

#endif