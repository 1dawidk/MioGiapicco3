#include "MCP3208.h"

MCP3208::MCP3208(SPI *spi, uint8_t cs_pin) {
    this->spi_h= spi;
    this->cs_pin= cs_pin;
    readMutex= PTHREAD_MUTEX_INITIALIZER;
    vRef= 3.3f;
}

float MCP3208::readCh(uint8_t ch) {
    float vol;
    uint8_t buff[3];

    buff[0]=0x18|ch;
    buff[1]=0;
    buff[2]=0;

    spi_h->RawTransfer(cs_pin, buff, 3);

    vol=(uint16_t)( ((uint16_t)(buff[1])<<6) | (buff[2]>>2));
    vol=vol*(vRef/4095);

    std::cout << "Spi out (ch: "<< ch << ": " << std::to_string(buff[0]) << " " << std::to_string(buff[1]) << " " << std::to_string(buff[2]) << ", V: " << vol << std::endl;

    return vol;
}

// 0x18 | ch
// 00011000 | ch (111-000)

//vol = buff[1]<<6 | buff[2]>>2
//vol = 0xxxxxxx<<6 | 00000000>>2


