#ifndef TESTQUEUE_H
#define TESTQUEUE_H

#include <stdlib/queue.h>
#include <driver/serial.h>
#include <kernel/type.h>

using namespace kernel;

void testQueue() 
{
    driver::SERIAL::getInstance()->printSerial("\nTest Queue\n");
    std::Queue<uint64> queue;
    queue.push(12);
    queue.push(64);
    queue.push(37);
    driver::SERIAL::getInstance()->printNumber(queue.size());
    driver::SERIAL::getInstance()->printNumber(queue.front());
    driver::SERIAL::getInstance()->printNumber(queue.back());
    queue.pop();
    driver::SERIAL::getInstance()->printNumber(queue.size());
    driver::SERIAL::getInstance()->printNumber(queue.front());
    driver::SERIAL::getInstance()->printNumber(queue.back());
    queue.pop();
    driver::SERIAL::getInstance()->printNumber(queue.size());
    driver::SERIAL::getInstance()->printNumber(queue.front());
    driver::SERIAL::getInstance()->printNumber(queue.back());
    queue.pop();
    driver::SERIAL::getInstance()->printNumber(queue.size());
    driver::SERIAL::getInstance()->printSerial("\nEnd Test Queue\n");
}

#endif // TESTQUEUE_H
