#include <ui/label.h>
#include <stdlib/string.h>

using namespace ui;

#define FONT_SIZE 8
#define DEFAULT_PADDING 2

Label::Label(Widget *parent, const char *txt)
    : Widget(parent), textColor(0x000000), backgroundColor(0xffff00), padding(DEFAULT_PADDING)
{
    setText(txt);
}

Label::~Label() 
{
    if (_text)
        delete _text;
}

void Label::setText(const char *str) 
{ 
    if (_text)
        delete _text;
    size_t size = std::strlen(str);
    _text = new char[size];
    std::strncpy(_text, str, size);
    updateSize();
}

void Label::setTextColor(uint32 color) 
{ 
    textColor = color;
}

void Label::setBackgroundColor(uint32 color)
{
    backgroundColor = color;
}


void Label::render() {
    rectangle(0, 0, width, height, backgroundColor);
    for (int i = 0; _text[i] != 0; i++) {
        // use 8 due to hardcode font 8x8
        text(padding + 8 * i, padding, _text[i], textColor);
    }
}

void Label::updateSize()
{
    size_t size = std::strlen(_text);
    width = size * FONT_SIZE + padding * 2;
    height = FONT_SIZE + padding * 2;
}
