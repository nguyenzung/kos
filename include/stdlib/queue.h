#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib/list.h>
#include <kernel/type.h>

namespace stdlib
{

template <typename T>
class Queue
{
protected:
    std::List<T> data;

public:
    bool push(T t)
    {
        data.add(t);
    }
    
    T pop();
    
    kernel::uint32 size()
    {
        return data.size;
    }
};

}

#endif // QUEUE_H
