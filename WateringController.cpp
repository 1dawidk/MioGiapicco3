#include "WateringController.h"

WateringController::WateringController(PCA9685 *pca9685) {
    this->pca9685= pca9685;
}

int WateringController::getState() {
    return state;
}

void WateringController::setState(uint8_t state) {
    this->state= state;
}

void WateringController::onStart() {

}

void WateringController::onRun() {

}

void WateringController::onStop() {

}
