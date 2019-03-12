#include "MCP3208.h"

MCP3208::MCP3208(SPI *spi) {
    this->spi_h= spi;
    readMutex= PTHREAD_MUTEX_INITIALIZER;
}

float MCP3208::ReadCh(uint8_t ch) {
    float vol;
    uint8_t buff[3];

    buff[0]=0x18|ch;
    buff[1]=0;
    buff[2]=0;

    //spi_h->RawTransfer(spiChip, buff, 3);

    vol=(uint16_t)( ((uint16_t)(buff[1])<<6) | (buff[2]>>2));
    vol=vol*(vRef/4095);

    return vol;
}


