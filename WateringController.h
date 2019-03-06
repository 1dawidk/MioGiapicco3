#ifndef MIOGIAPICCO_WATERINGCONTROLLER_H
#define MIOGIAPICCO_WATERINGCONTROLLER_H


#include <stdint-gcc.h>
#include "Devices/PCA9685.h"
#include "dkulpaclibs/misc/Thread.h"
#include "bcm2835.h"

class WateringController : public Thread {
public:
    WateringController(uint8_t pin);
    int getMinLeft();
    void incTime();
    void decTime();

protected:
    void onStart() override;

    void onRun() override;

    void onStop() override;

private:
    uint8_t minLeft;
    uint8_t pin;

    pthread_mutex_t minMutex;
};


#endif //MIOGIAPICCO_WATERINGCONTROLLER_H
