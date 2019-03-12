#ifndef MIOGIAPICCO_SPI_H
#define MIOGIAPICCO_SPI_H

#include <pthread.h>
#include "bcm2835.h"


#define SPI_CHIP_0              BCM2835_SPI_CS0
#define SPI_CHIP_1              BCM2835_SPI_CS1

#define SPI_MODE_CPOL0_CPHA0    BCM2835_SPI_MODE0
#define SPI_MODE_CPOL0_CPHA1    BCM2835_SPI_MODE1
#define SPI_MODE_CPOL1_CPHA0    BCM2835_SPI_MODE2
#define SPI_MODE_CPOL1_CPHA1    BCM2835_SPI_MODE3

#define SPI_LOW                 LOW
#define SPI_HIGH                HIGH

class SPI {
public:
    SPI(int clkDiv, int mode, int c0Set, int c1Set);
    ~SPI();
    void WriteReg(int chip, uint8_t reg, uint8_t data);
    int ReadReg(int chip, uint8_t reg);
    void ReadRegs(int chip, uint8_t freg, uint8_t *buff, uint8_t len);
    void RawTransfer(int chip, uint8_t *buff, uint8_t len);
private:
    pthread_mutex_t mut;
};

#endif //MIOGIAPICCO_SPI_H
