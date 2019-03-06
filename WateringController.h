#ifndef MIOGIAPICCO_WATERINGCONTROLLER_H
#define MIOGIAPICCO_WATERINGCONTROLLER_H


#include <stdint-gcc.h>
#include "Devices/PCA9685.h"
#include "dkulpaclibs/misc/Thread.h"
#include "bcm2835.h"

class WateringController : public Thread {
public:
    WateringController(uint8_t pin);
    int getState();
    void setState(uint8_t state);

protected:
    void onStart() override;

    void onRun() override;

    void onStop() override;

private:
    uint8_t lastState;
    uint8_t state;
    uint8_t pin;

    pthread_mutex_t stateMutex;
};


#endif //MIOGIAPICCO_WATERINGCONTROLLER_H
