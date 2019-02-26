#ifndef MIOGIAPICCO_SUNCONTROLLER_H
#define MIOGIAPICCO_SUNCONTROLLER_H

#include "dkulpaclibs/misc/Thread.h"
#include "bcm2835.h"

class SunController : public Thread {
public:

protected:
    void onStart() override;
    void onRun() override;
    void onStop() override;

};


#endif //MIOGIAPICCO_SUNCONTROLLER_H
