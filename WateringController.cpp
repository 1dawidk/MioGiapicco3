#include "WateringController.h"

WateringController::WateringController(uint8_t pin) {
    this->pin= pin;
}

int WateringController::getMinLeft() {
    return minLeft;
}

void WateringController::incTime() {
    pthread_mutex_lock(&minMutex);
    this->minLeft++;
    pthread_mutex_unlock(&minMutex);
}

void WateringController::decTime() {
    pthread_mutex_lock(&minMutex);
    if(minLeft>0)
        minLeft--;
    pthread_mutex_unlock(&minMutex);
}

void WateringController::onStart() {
    bcm2835_gpio_fsel(pin, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_write(pin, LOW);
    minMutex= PTHREAD_MUTEX_INITIALIZER;
}

void WateringController::onRun() {

    pthread_mutex_lock(&minMutex);
    /*if(lastState!=minLeft){
        if(minLeft==0){
            bcm2835_gpio_write(pin, LOW);
        } else {
            bcm2835_gpio_write(pin, HIGH);
        }
    }*/
    pthread_mutex_unlock(&minMutex);

    Thread::pause(1000);
}

void WateringController::onStop() {

}
