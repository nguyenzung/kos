#ifndef LIST
#define LIST

#include <kernel/kernelobject.h>
#include <kernel/type.h>

namespace ds {

class Node
{
public:
    kernel::KernelObject *value;
    Node *prev;
    Node *next;

    Node(kernel::KernelObject *value);
    ~Node();

    void addPrev(Node *node);
    void removePrev();

    void addNext(Node *node);
    void removeNext();
};

class List
{
public:

    class Iterator
    {

    };

    kernel::uint16 size;
    Node *first;
    Node *last;
    Node *current;

    List();
    ~List();

    void addNode(Node *node);
    void addNodeAfter(Node *prevNode, Node* node);  // user need to make sure prevNode in the list
    bool removeNodeByAddress(Node *node);
    bool removeNodeByValue(kernel::KernelObject *kernelObject);

    Node* begin();
    Node* end();
    Node* next();
    Node* getCurrent();
};

}
#endif