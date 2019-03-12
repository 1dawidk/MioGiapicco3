#ifndef MIOGIAPICCO_MCP3208_H
#define MIOGIAPICCO_MCP3208_H


#include <pthread.h>
#include "../Peripherals/SPI.h"
#include <cstdint>

class MCP3208 {
public:
    MCP3208(SPI *spi);
    float ReadCh(uint8_t ch);
private:
    SPI *spi_h;
    float vRef;

    pthread_mutex_t readMutex;
};


#endif //MIOGIAPICCO_MCP3208_H
