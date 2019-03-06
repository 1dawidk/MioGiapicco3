#include "WateringController.h"

WateringController::WateringController(uint8_t pin) {
    this->pin= pin;
}

int WateringController::getState() {
    return state;
}

void WateringController::setState(uint8_t state) {
    pthread_mutex_lock(&stateMutex);
    this->state= state;
    pthread_mutex_unlock(&stateMutex);
}

void WateringController::onStart() {
    bcm2835_gpio_fsel(pin, BCM2835_GPIO_FSEL_OUTP);
    stateMutex= PTHREAD_MUTEX_INITIALIZER;
}

void WateringController::onRun() {

    pthread_mutex_lock(&stateMutex);
    if(lastState!=state){
        if(state==0){
            bcm2835_gpio_write(pin, LOW);
        } else {
            bcm2835_gpio_write(pin, HIGH);
        }
    }
    pthread_mutex_unlock(&stateMutex);

    Thread::pause(1000);
}

void WateringController::onStop() {

}
