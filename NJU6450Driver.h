#ifndef MIOGIAPICCO_NJU6450DRIVER_H
#define MIOGIAPICCO_NJU6450DRIVER_H

#include <cstdint>
#include "bcm2835.h"

#define NJU6450_DISABLE_PIN 120
#define NJU6450_CHIP_0      0
#define NJU6450_CHIP_1      1
#define NJU6450_WRITETYPE_DATA  0
#define NJU6450_WRITETYPE_CMD   1

class NJU6450Driver {
public:
    NJU6450Driver(uint8_t *dataPins, uint8_t a0Pin, uint8_t e1Pin, uint8_t e2Pin, uint8_t resPin);
    void init();

    void clrScr();

private:
    void writeCmd(uint8_t chip, uint8_t cmd);
    void writeData(uint8_t c, uint8_t p, uint8_t d);

    uint8_t *dataPins;
    uint8_t a0Pin;
    uint8_t e1Pin;
    uint8_t e2Pin;
    uint8_t resPin;
};


#endif //MIOGIAPICCO_NJU6450DRIVER_H
