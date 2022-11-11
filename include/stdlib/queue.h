#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib/list.h>
#include <kernel/type.h>

namespace std
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
    
    T pop()
    {
        data.removeFirst();
    }
    
    T front()
    {
        return data.getFirst();
    }
    
    T back()
    {
        return data.getLast();
    }
    
    bool empty() 
    {
        return data.size() == 0;
    }
   
    kernel::uint64 size()
    {
        return data.size();
    }
};

}

#endif // QUEUE_H
