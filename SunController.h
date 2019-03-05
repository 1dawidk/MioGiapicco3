#ifndef MIOGIAPICCO_SUNCONTROLLER_H
#define MIOGIAPICCO_SUNCONTROLLER_H

#include "dkulpaclibs/misc/Thread.h"
#include "bcm2835.h"

class SunController : public Thread {
public:
    int getState();

protected:
    void onStart() override;
    void onRun() override;
    void onStop() override;

    uint8_t state;

};


#endif //MIOGIAPICCO_SUNCONTROLLER_H
