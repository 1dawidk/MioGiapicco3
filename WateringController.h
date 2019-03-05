#ifndef MIOGIAPICCO_WATERINGCONTROLLER_H
#define MIOGIAPICCO_WATERINGCONTROLLER_H


#include <stdint-gcc.h>
#include "Devices/PCA9685.h"

class WateringController {
public:
    WateringController(PCA9685 *pca96851);
    int getState();

private:
    uint8_t state;
    PCA9685 *pca9685;
};


#endif //MIOGIAPICCO_WATERINGCONTROLLER_H
