#ifndef LIST
#define LIST

#include <kernel/kernelobject.h>
#include <kernel/type.h>

namespace std {

template <typename T>
class Node
{
public:
    T value;
    Node *prev;
    Node *next;

    Node(T value):value(value), next(0), prev(0){}
    
    ~Node(){}

    void addPrev(Node *node)
    {
         this->prev = node;
        if (node)
        {
            node->next = this;
        }
    }
    
    void removePrev()
    {
        this->prev = 0;
        if (this->prev)
        {
            this->prev->next = 0;
        }
    }

    void addNext(Node *node)
    {
        this->next = node;
        if (node)
        {
            node->prev = this;
        }
    }

    void removeNext()
    {
        this->next = 0;
        if (this->next)
        {
            this->next->prev = 0;
        }
    }
};

template <class T>
class List
{
public:
    class Iterator
    {
    protected:
        Node<T>* ptr;

    public:
        Iterator(Node<T> *ptr)
        {
            this->ptr = ptr;
        }

        Iterator& operator = (Node<T>* ptr)
        {
            this->ptr = ptr;
            return *this;
        }

        Iterator& operator++()
        {
            if (ptr)
            {
                ptr = ptr->next;
            }
            return *this;
        }
 
        Iterator operator++(int)
        {
            Iterator iterator = *this;
            ++*this;
            return iterator;
        }
 
        bool operator!=(const Iterator& iterator)
        {
            return ptr != iterator.ptr;
        }
        
        bool operator==(const Iterator& iterator)
        {
            return ptr == iterator.ptr;
        }
 
        int operator*()
        {
            return ptr->value;
        }
    };
 

public:
    kernel::uint16 size;
    Node<T> *first;
    Node<T> *last;
    Node<T> *current;
    // Iterator it;

    List():size(0), first(0), last(0), current(0){}

    ~List(){}

    void addNode(Node<T> *node)
    {
        if (!first)
        {
            this->first = node;
            this->last = node;
        } else {
            this->last->addNext(node);
            this->last = node;
        }
        ++this->size;
    }

    void add(T value)
    {
        Node<T> *node = new Node<T>(value);
        this->addNode(node);
    }

    void addNodeAfter(Node<T> *prevNode, Node<T>* node) // user need to make sure prevNode in the list
    {
        if (!node)
        {
            return;
        }
        if(!prevNode)
        {
            node->addNext(this->first);
            this->first = node;
        }else{
            Node<T> *next = prevNode->next;
            prevNode->addNext(node);
            node->addNext(next);
            if(prevNode == this->last)
            {
                this->last = node;
            }
        }
        ++this->size;
    }

    bool removeNodeByAddress(Node<T> *node)
    {
        Node<T> *curr = this->first;
        while(curr)
        {
            if (curr == node)
            {
                Node<T> *prev = curr->prev;
                Node<T> *next = curr->next;
                if (prev)
                {
                    prev->addNext(next);
                }
                if (this->size == 1)
                {
                    this->first = this->last = 0;
                }else{
                    if (curr == this->first)
                    {
                        this->first = curr->next;
                    }
                    if (curr == this->last)
                    {
                        this->last = curr->prev;
                    }
                }
                --this->size;
                return true;
            }
            curr = curr->next;
        }
        return false;
    }

    Node<T> removeNodeByValue(T value)
    {
        Node<T> *curr = this->first;
        while(curr)
        {
            if (curr->value == value)
            {
                Node<T> *prev = curr->prev;
                Node<T> *next = curr->next;
                if (prev)
                {
                    prev->addNext(next);
                }
                if (this->size == 1)
                {
                    this->first = this->last = 0;
                }else{
                    if (curr == this->first)
                    {
                        this->first = curr->next;
                    }
                    if (curr == this->last)
                    {
                        this->last = curr->prev;
                    }
                }
                --this->size;
                return curr;
            }
            curr = curr->next;
        }
        return nullptr;
    }

    Node<T>* getFirst()
    {
        this->current = this->first;
        return this->current;
    }

    Node<T>* getLast()
    {
        return this->last ? this->last->next : this->last;
    }

    Node<T>* next()
    {
        if (this->current && this->current->next)
        {
            this->current = this->current->next;
            return this->current;
        } else 
        {
            return 0;
        }
    }

    Node<T>* getCurrent()
    {
        return this->current;
    }

    uint16 getSize()
    {
        return this->size;
    }

    Iterator begin()
    {
        // this->current = this->first;
        return Iterator(this->first);
    }
 
    Iterator end()
    {
        return Iterator(0);
    }

};

}
#endif