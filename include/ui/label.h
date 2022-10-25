#ifndef INCLUDE_UI_LABEL_H_
#define INCLUDE_UI_LABEL_H_
#include <kernel/widget.h>

namespace ui {

class Label : public Widget {
protected:
    uint32 textColor;
    uint32 backgroundColor;    
    char *_text = nullptr;
    uint16 padding;

public:
    explicit Label(Widget *parent = 0, const char *txt = nullptr);
    ~Label();

    void setTextColor(uint32 color);
    void setBackgroundColor(uint32 color);
    void setText(const char *str);
    virtual void render();
    
protected:
    void updateSize();
};

} // namespace ui
#endif // INCLUDE_UI_LABEL_H_
