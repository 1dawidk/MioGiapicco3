#ifndef MIOGIAPICCO_WINDCONTROLLER_H
#define MIOGIAPICCO_WINDCONTROLLER_H


#include <cstdint>

class WindController {
public:
    WindController(uint8_t pin);
    int getState();
    void incTime();
    void devTime();

private:
    uint8_t pin;
    uint8_t minLeft;
};


#endif //MIOGIAPICCO_WINDCONTROLLER_H
