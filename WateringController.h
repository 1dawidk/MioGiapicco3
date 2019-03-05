#ifndef MIOGIAPICCO_WATERINGCONTROLLER_H
#define MIOGIAPICCO_WATERINGCONTROLLER_H


#include <stdint-gcc.h>
#include "Devices/PCA9685.h"
#include "dkulpaclibs/misc/Thread.h"

class WateringController : public Thread {
public:
    WateringController(PCA9685 *pca9685);
    int getState();
    void setState(uint8_t state);

protected:
    void onStart() override;

    void onRun() override;

    void onStop() override;

private:
    uint8_t state;
    PCA9685 *pca9685;
};


#endif //MIOGIAPICCO_WATERINGCONTROLLER_H
