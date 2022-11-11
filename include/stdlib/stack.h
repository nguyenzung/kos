#ifndef STACK_H
#define STACK_H

#include <stdlib/list.h>
#include <kernel/type.h>

namespace std
{

template <typename T>
class Stack {
protected:
    std::List<T> data;
    
public:
    Stack()
    {
        
    }
    
    ~Stack()
    {
        
    }
    
    bool empty()
    {
        return this->data.size() == 0;
    }
    
    kernel::uint64 size()
    {
        return this->data.size();
    }
    
    void push(const T &value) 
    {
        data.add(value);
    }
    
    void pop()
    {
        data.removeLast();
    }
    
    T top()
    {
      return data.getLast();
    }
};

}

#endif // STACK_H
