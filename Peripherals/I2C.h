#ifndef MIOGIAPICCO_I2C_H
#define MIOGIAPICCO_I2C_H

#include <cstdint>
#include "pthread.h"
#include "bcm2835.h"

class I2C {
public:
    I2C(uint16_t baud);
    ~I2C();
    bool isReady();
    uint8_t write(uint8_t sadr, uint8_t data);
    uint8_t read(uint8_t sadr);
    uint8_t write(uint8_t sadr, uint8_t radr, const uint8_t *buff, uint8_t len=1);
    uint8_t read(uint8_t sadr, uint8_t radr, uint8_t *buff, uint8_t len=1);

private:
    bool ready;
    pthread_mutex_t mut; // Read / Write mutex
};


#endif //MIOGIAPICCO_I2C_H
