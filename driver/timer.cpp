#include <driver/timer.h>
#include <kernel/interruptmanager.h>
#include <kernel/printer.h>
#include <kernel/iocommand.h>

#define CURRENT_YEAR        2022                                                               
#define CURRENT_MONTH       01

uint8 century_register = 0x00;                                // Set by ACPI table parsing code if possible                                             


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
}

