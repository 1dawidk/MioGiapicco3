#ifndef MIOGIAPICCO_SUNCONTROLLER_H
#define MIOGIAPICCO_SUNCONTROLLER_H

#include "dkulpaclibs/misc/Thread.h"
#include "bcm2835.h"
#include "Devices/PCA9685.h"

class SunController : public Thread {
public:
    int getState();

protected:
    void onStart() override;
    void onRun() override;
    void onStop() override;

private:
    uint8_t state;

    const uint8_t sunAtHalfHour[48]={
            20,  20,  30,  40,  50,  60,  70,  80,    //0:00 - 3:30
            90,  90,  90,  90,  90,  90,  90,  90,    //4:00 - 7:30
            100, 100, 100, 100, 100, 100, 100, 100,   //8:00 - 11:30
            100, 100, 100, 100, 100, 100, 100, 100,   //12:00 - 15:30
            100, 100, 100, 100, 100, 100, 100, 100,   //16:00 - 19:30
            100, 100, 90,  80,  70,  50,  30,  20     //20:00 - 23:30
    };
};


#endif //MIOGIAPICCO_SUNCONTROLLER_H
