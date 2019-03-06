#include "WindController.h"

WindController::WindController(uint8_t pin) {
    this->pin= pin;
}

int WindController::getState() {
    return 0;
}

void WindController::incTime() {
    pthread_mutex_lock(&minMutex);
    minLeft++;
    pthread_mutex_unlock(&minMutex);
}

void WindController::decTime() {
    pthread_mutex_lock(&minMutex);
    if(minLeft>0)
        minLeft--;
    pthread_mutex_unlock(&minMutex);
}

void WindController::onStart() {
    bcm2835_gpio_fsel(pin, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_write(pin, LOW);
    minMutex= PTHREAD_MUTEX_INITIALIZER;
}

void WindController::onRun() {
    Thread::pause(1000);
}

void WindController::onStop() {

}
