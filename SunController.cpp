#include "SunController.h"

SunController::SunController(PCA9685 *pca9685) {
    this->pca9685= pca9685;
}

void SunController::onStart() {

}

void SunController::onRun() {

}

void SunController::onStop() {

}


int SunController::getState() {
    return 78;
}
