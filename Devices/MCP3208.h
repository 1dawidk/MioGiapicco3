#ifndef MIOGIAPICCO_MCP3208_H
#define MIOGIAPICCO_MCP3208_H


#include <pthread.h>
#include "../Peripherals/SPI.h"
#include <cstdint>
#include <iostream>

class MCP3208 {
public:
    MCP3208(SPI *spi, uint8_t cs_pin);
    float readCh(uint8_t ch);
private:
    SPI *spi_h;
    uint8_t cs_pin;
    float vRef;

    pthread_mutex_t readMutex;
};


#endif //MIOGIAPICCO_MCP3208_H
