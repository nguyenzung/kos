#ifndef TESTSTACK_H
#define TESTSTACK_H

#include <stdlib/stack.h>
#include <driver/serial.h>
#include <kernel/type.h>

using namespace kernel;

void testStack() 
{
    driver::SERIAL::getInstance()->printSerial("\nTest Stack\n");
    std::Stack<uint64> stack;
    stack.push(12);
    stack.push(64);
    stack.push(37);
    driver::SERIAL::getInstance()->printNumber(stack.size());
    driver::SERIAL::getInstance()->printNumber(stack.top());
    stack.pop();
    driver::SERIAL::getInstance()->printNumber(stack.size());
    driver::SERIAL::getInstance()->printNumber(stack.top());
    driver::SERIAL::getInstance()->printNumber(stack.size());
    driver::SERIAL::getInstance()->printNumber(stack.top());
    driver::SERIAL::getInstance()->printNumber(stack.size());
    stack.pop();
    driver::SERIAL::getInstance()->printNumber(stack.top());
    driver::SERIAL::getInstance()->printNumber(stack.size());
    stack.pop();
    driver::SERIAL::getInstance()->printNumber(stack.size());
    driver::SERIAL::getInstance()->printSerial("\nEnd Test Stack\n");
}


#endif // TESTSTACK_H
