#ifndef MIOGIAPICCO_SUNCONTROLLER_H
#define MIOGIAPICCO_SUNCONTROLLER_H

#include "dkulpaclibs/misc/Thread.h"
#include "bcm2835.h"
#include "Devices/PCA9685.h"

class SunController : public Thread {
public:
    SunController(PCA9685 *pca9685);
    int getState();

protected:
    void onStart() override;
    void onRun() override;
    void onStop() override;

private:
    PCA9685 *pca9685;
    uint8_t state;

};


#endif //MIOGIAPICCO_SUNCONTROLLER_H
