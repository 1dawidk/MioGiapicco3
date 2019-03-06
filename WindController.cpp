#include "WindController.h"

WindController::WindController(uint8_t pin) {
    this->pin= pin;
}

int WindController::getState() {
    return 0;
}

void WindController::incTime() {
    minLeft++;
}

void WindController::devTime() {
    minLeft--;
    if(minLeft<0)
        minLeft=0;
}
