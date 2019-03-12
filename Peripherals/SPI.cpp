#include "SPI.h"

SPI::SPI(int clkDiv, int mode, int c0Set, int c1Set) {
    mut= PTHREAD_MUTEX_INITIALIZER;

    bcm2835_spi_begin();

    bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);
    bcm2835_spi_setDataMode(mode);
    bcm2835_spi_setClockDivider(clkDiv);
    bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, c0Set);
    bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS1, c1Set);
}

SPI::~SPI() {
    bcm2835_spi_end();
}

void SPI::WriteReg(int chip, uint8_t reg, uint8_t data) {
    pthread_mutex_lock(&mut);

    uint8_t buff[2]={reg, data};
    bcm2835_spi_chipSelect(chip);
    bcm2835_spi_transfern((char*)buff, 2);

    pthread_mutex_unlock(&mut);
}

int SPI::ReadReg(int chip, uint8_t reg) {
    pthread_mutex_lock(&mut);

    uint8_t buff[2]={reg, 0};
    bcm2835_spi_chipSelect(chip);
    bcm2835_spi_transfern((char*)buff, 2);

    pthread_mutex_unlock(&mut);

    return buff[1];
}

void SPI::ReadRegs(int chip, uint8_t freg, uint8_t *buff, uint8_t len) {
    pthread_mutex_lock(&mut);

    uint8_t sbuff[len+1];
    sbuff[0]=freg;
    bcm2835_spi_chipSelect(chip);
    bcm2835_spi_transfern((char*)sbuff, len+1);
    for(int i=0; i<len; i++){
        buff[i]= sbuff[i+1];
    }

    pthread_mutex_unlock(&mut);
}

void SPI::RawTransfer(int chip, uint8_t *buff, uint8_t len) {
    pthread_mutex_lock(&mut);

    bcm2835_spi_chipSelect(chip);
    bcm2835_spi_transfern((char*)buff, len);

    pthread_mutex_unlock(&mut);
}