#ifndef LOGGER_H
#define LOGGER_H

#include <kernel/widget.h>
#include <stdlib/list.h>

namespace ui
{

typedef struct Message {
    
} Messgage;

class Logger : public Widget {
protected:
    std::List<Message*> messages;
    
public:
    Logger();
    ~Logger();
    
    void addMessage(Message *message);
    void scrollUp();
};

}

#endif // LOGGER_H
