#include <ui/label.h>

using namespace ui;

Label::Label(Widget* parent, const char *txt) : Widget(parent), m_color(0x000000), m_str(txt) {}

Label::~Label() {}

void Label::setStr(const char* str) { m_str = str; }
void Label::setColor(uint32 color) { m_color = color; }

void Label::render() {
	for (int i = 0; m_str[i] != 0; i++) {
		// use 8 due to hardcode font 8x8
		text(8 *i + 1, 0, m_str[i], m_color);
	}
}
