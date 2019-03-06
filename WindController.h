#ifndef MIOGIAPICCO_WINDCONTROLLER_H
#define MIOGIAPICCO_WINDCONTROLLER_H


#include <cstdint>
#include "dkulpaclibs/misc/Thread.h"
#include "bcm2835.h"

class WindController : public Thread{
public:
    WindController(uint8_t pin);
    int getState();
    void incTime();
    void decTime();

protected:
    void onStart() override;
    void onRun() override;
    void onStop() override;

private:
    uint8_t pin;
    uint8_t minLeft;
    pthread_mutex_t minMutex;
};


#endif //MIOGIAPICCO_WINDCONTROLLER_H
