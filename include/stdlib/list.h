#ifndef LIST
#define LIST

#include <kernel/printer.h>
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
 
        T operator*()
        {
            return ptr->value;
        }
    };
 

public:
    kernel::uint64 size_;
    Node<T> *first;
    Node<T> *last;
    Node<T> *current;
    // Iterator it;

    List():size_(0), first(0), last(0), current(0){}

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
        ++this->size_;
    }

    Node<T>* add(T value)
    {
        Node<T> *node = new Node<T>(value);
        if (node)
            this->addNode(node);
        return node;
    }

    void addNodeAfter(Node<T> *prevNode, Node<T>* node) // user need to make sure prevNode in the list
    {
        if (!node)
        {
            return;
        }
        if(!first)
        {
            first = node;
            last = node;
//            node->addNext(null);
        }else{
            Node<T> *next = prevNode->next;
            prevNode->addNext(node);
            node->addNext(next);
            if(prevNode == this->last)
            {
                this->last = node;
            }
        }
        ++this->size_;
    }
    
    /*
    *   Call when list size > 0
    */
    T getFirst()
    {
        Node<T> *first = this->first;
        return first->value;
    }

    /*
    *   Call when list size > 0
    */
    void removeFirst()
    {
        Node<T> *first = this->first;
        this->removeNodeByAddress(first);
        delete first;
    }
    
    /*
    *   Call when list size > 0
    */
    T getLast()
    {
        Node<T> *last = this->last;
        return last->value;
    }

    /*
    *   Call when list size > 0
    */
    void removeLast()
    {
        Node<T> *last = this->last;
        this->removeNodeByAddress(last);
        delete last;
    }

    Node<T>* removeNodeByAddress(Node<T> *node)
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
                if (this->size_ == 1)
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
                --this->size_;
                return node;
            }
            curr = curr->next;
        }
        return 0;
    }

    Node<T>* removeNodeByValue(T value)
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
                if (this->size_ == 1)
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
                --this->size_;
                return curr;
            }
            curr = curr->next;
        }
        return nullptr;
    }

    Node<T>* getFirstNode()
    {
        this->current = this->first;
        return this->current;
    }

    Node<T>* getLastNode()
    {
        return this->last ? this->last->next : this->last;
    }

    Node<T>* next()
    {
        if (this->current && this->current->next)
        {
            this->current = this->current->next;
        } else 
        {
            this->current = 0;
        }
        return this->current;
    }

    Node<T>* getCurrent()
    {
        return this->current;
    }

    kernel::uint64 size()
    {
        return this->size_;
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