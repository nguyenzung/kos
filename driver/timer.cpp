#include <driver/timer.h>
#include <kernel/interruptmanager.h>
#include <kernel/printer.h>

using namespace driver;

Timer::Timer()
    :BaseDriver()
{
    vector = 0 + OFFSET;
}

Timer::~Timer() {

}

void Timer::active() {

}

void Timer::deactive() {

}

void Timer::handleInterrupt() {
    Printer::println(" Timer INT ", 11);
}