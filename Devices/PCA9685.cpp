#include "PCA9685.h"
#include <iostream>
#include <ncurses.h>

using namespace std;

PCA9685::PCA9685(I2C *i2c_handle, uint8_t addr) {
    this->i2cH= i2c_handle;
    this->addr= addr;

    coreFreq=25000000;
    scale= 4.4951;
}

int PCA9685::init(uint8_t updateRate, uint8_t invert, uint8_t instant) {
    uint8_t r;

    uint8_t pre_scale= (uint8_t)(((unsigned long)coreFreq)/(4096UL*updateRate));
    uint8_t mode1;
    uint8_t mode2;

    //Put to sleep
    mode1= 0x31;
    i2cH->write(addr, (uint8_t)0x00, &mode1);

    //Set prescaler
    r=i2cH->write(addr, (uint8_t)0xFE, &pre_scale);

    //Set Ctrl2
    mode2= (uint8_t)0x04 | invert | instant;
    r+=i2cH->write(addr, (uint8_t)0x01, &mode2);

    //Set Ctrl1
    mode1= 0x21;
    r+=i2cH->write(addr, (uint8_t)0x00, &mode1);

    return r;
}

void PCA9685::calib(int coreFreq, double scale) {
    this->scale= scale;
    this->coreFreq= coreFreq;
}

int PCA9685::setOutput(uint8_t outPin, uint16_t turnOnAt, uint16_t turnOffAt) {
    uint8_t regAdr= (uint8_t)(0x06+outPin*4);
    uint8_t buff[]= {(uint8_t)turnOnAt, (uint8_t)(turnOnAt>>8),
                     (uint8_t)turnOffAt, (uint8_t)(turnOffAt>>8)};

    return i2cH->write(addr, regAdr, buff, 4);
}

int PCA9685::setOutputs(uint8_t firstPin, uint8_t pinCnt, const uint16_t *turnOnAt, const uint16_t *turnOffAt) {
    uint8_t regAdr= (uint8_t)(0x06 + firstPin*4);
    uint8_t buff[pinCnt*4];

    for(int i=0; i<pinCnt; i++){
        buff[i*4 + 0]= (uint8_t)turnOnAt[i];
        buff[i*4 + 1]= (uint8_t)(turnOnAt[i]>>8);
        buff[i*4 + 2]= (uint8_t)turnOffAt[i];
        buff[i*4 + 3]= (uint8_t)(turnOffAt[i]>>8);
    }

    return i2cH->write(addr, regAdr, buff, (uint8_t)(pinCnt*4));
}

void PCA9685::outputOn(uint8_t pin, uint16_t at) {
    setOutput(pin, 0, at);
}

void PCA9685::outputOff(uint8_t pin) {
    setOutput(pin,0,0);
}

double PCA9685::getScale() {
    return scale;
}
