#include "NJU6450Driver.h"

NJU6450Driver::NJU6450Driver(uint8_t *dataPins, uint8_t a0Pin, uint8_t e1Pin, uint8_t e2Pin,
                             uint8_t resPin){
    this->dataPins= dataPins;
    this->a0Pin= a0Pin;
    this->e1Pin= e1Pin;
    this->e2Pin= e2Pin;
    this->resPin= resPin;
}

void NJU6450Driver::init() {
    for(int i=0; i<8; i++) {
        bcm2835_gpio_fsel(dataPins[i], BCM2835_GPIO_FSEL_OUTP);
    }
    bcm2835_gpio_fsel(a0Pin, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(e1Pin, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(e2Pin, BCM2835_GPIO_FSEL_OUTP);
    if(resPin!=NJU6450_DISABLE_PIN)
        bcm2835_gpio_fsel(resPin, BCM2835_GPIO_FSEL_OUTP);

    bcm2835_gpio_write(a0Pin, LOW);
    bcm2835_gpio_write(e1Pin, LOW);
    bcm2835_gpio_write(e2Pin, LOW);

    //Reset cpu
    bcm2835_gpio_write(resPin, LOW);
    bcm2835_delay(1);
    bcm2835_gpio_write(resPin, HIGH);
    bcm2835_delay(10);

    writeCmd(NJU6450_CHIP_0, 0xae);
    writeCmd(NJU6450_CHIP_1, 0xae);
    bcm2835_delay(10);
    writeCmd(NJU6450_CHIP_0, 0xa0);
    writeCmd(NJU6450_CHIP_1, 0xa0);
    bcm2835_delay(10);
    writeCmd(NJU6450_CHIP_0, 0xa4);
    writeCmd(NJU6450_CHIP_1, 0xa4);
    bcm2835_delay(10);
    writeCmd(NJU6450_CHIP_0, 0xa9);
    writeCmd(NJU6450_CHIP_1, 0xa9);
    bcm2835_delay(10);

    clrScr();

    writeCmd(NJU6450_CHIP_0, 0xaf);
    writeCmd(NJU6450_CHIP_1, 0xaf);
    bcm2835_delay(10);
}

void NJU6450Driver::clrScr() {
    for(int i=0; i<4; i++){
        for(int j=0; j<122; j++){

        }
    }

}

void NJU6450Driver::writeCmd(uint8_t chip, uint8_t cmd) {
    bcm2835_gpio_write(a0Pin, LOW);
    bcm2835_delay(1);

    if(chip==NJU6450_CHIP_0)
        bcm2835_gpio_write(e1Pin, HIGH);
    else {
        bcm2835_gpio_write(e2Pin, HIGH);
    }

    bcm2835_delay(1);

    for(int i=0; i<8; i++){
        bcm2835_gpio_write(dataPins[i], cmd&((uint8_t )1<<i));
    }

    bcm2835_gpio_write(e1Pin, LOW);
    bcm2835_gpio_write(e2Pin, LOW);
    bcm2835_delay(1);
}

void NJU6450Driver::writeData(uint8_t c, uint8_t p, uint8_t d) {
    bcm2835_gpio_write(a0Pin, HIGH);
    bcm2835_delay(1);


}
