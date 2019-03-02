#ifndef MIOGIAPICCO_PCA9685_H
#define MIOGIAPICCO_PCA9685_H


#define PCA9685_INVERT_ENABLE       0x10
#define PCA9685_INVERT_DISABLE      0x00
#define PCA9685_INSTANT_ENABLE      0x08
#define PCA9685_INSTANT_DISABLE     0x00

#include "../Peripherals/I2C.h"

class PCA9685 {
public:
    PCA9685(I2C *i2c_handle, uint8_t addr);
    int init(uint8_t updateRate, uint8_t invert, uint8_t instant);
    void calib(int coreFreq, double scale);

    void outputOn(uint8_t pin, uint16_t at);
    void outputOff(uint8_t pin);

    int setOutput(uint8_t outPin, uint16_t turnOnAt, uint16_t turnOffAt);
    int setOutputs(uint8_t firstPin, uint8_t pinCnt, const uint16_t *turnOnAt, const uint16_t *turnOffAt);

    double getScale();
private:
    I2C *i2cH;
    uint8_t addr;

    double scale;
    int coreFreq;
};



#endif //MIOGIAPICCO_PCA9685_H
