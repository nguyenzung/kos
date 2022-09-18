#include <datastructure/list.h>
#include <kernel/printer.h>
#include <kernel/type.h>

using namespace ds;

Node::Node(kernel::KernelObject *value):value(value)
{
}

Node::~Node()
{
}

void Node::addPrev(Node *node)
{
    this->prev = node;
    if (node)
    {
        node->next = this;
    }
}

void Node::removePrev()
{
    this->prev = 0;
}

void Node::addNext(Node *node)
{
    this->next = node;
    if (node)
    {
        node->prev = this;
    }
}

void Node::removeNext()
{
    this->next = 0;
}


List::List():size(0), first(0), last(0), current(0)
{
}

List::~List()
{
}

void List::addNode(Node *node)
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

bool List::removeNodeByAddress(Node *node)
{
    Node *curr = this->first;
    while(curr)
    {
        if (curr == node)
        {
            Node *prev = curr->prev;
            Node *next = curr->next;
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

bool List::removeNodeByValue(kernel::KernelObject *kernelObject)
{
    Node *curr = this->first;
    while(curr)
    {
        if (curr->value == kernelObject)
        {
            Node *prev = curr->prev;
            Node *next = curr->next;
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

void List::travel()
{
    Node *curr = this->first;
    while (curr)
    {
        kernel::Printer::printlnNumber((kernel::uint64)curr->value);
        curr = curr->next;
    }
    
}