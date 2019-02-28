#ifndef MIOGIAPICCO_DHT11_H
#define MIOGIAPICCO_DHT11_H


#include <cstdint>
#include "dkulpaclibs/misc/Thread.h"
#include "iostream"

#define DHT11_READSTATE_BEFORELOW               0
#define DHT11_READSTATE_AFTERLOW                1
#define DHT11_READSTATE_INITSTATE_BEFORELOW     2
#define DHT11_READSTATE_INITSTATE_AFTERLOW      3
#define MAXTIMINGS	85

using namespace std;

class DHT11 : public Thread {
public:
    DHT11(uint8_t dataPin);

protected:
    void onStart() override;

    void onRun() override;

    void onStop() override;

private:
    uint8_t  dataPin;
};


#endif //MIOGIAPICCO_DHT11_H
