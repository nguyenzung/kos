#ifndef INCLUDE_UI_LABEL_H_
#define INCLUDE_UI_LABEL_H_
#include <kernel/widget.h>

namespace ui {

class Label : public Widget {
  protected:
    uint32 m_color;
    const char *m_str = nullptr;

  public:
    explicit Label(Widget *parent = 0, const char *txt = nullptr);
    ~Label();

    void setColor(uint32 color);
    void setStr(const char *str);
    virtual void render();
};

} // namespace ui
#endif // INCLUDE_UI_LABEL_H_
