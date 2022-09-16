#include "interrupthandler.h"

using namespace kernel;

InterruptHandler::InterruptHandler(uint8 vector) {
    this->vector = vector;
}

uint8 InterruptHandler::getVector() {
    return this->vector;
}