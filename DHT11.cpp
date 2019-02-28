#include <bcm2835.h>
#include "DHT11.h"

DHT11::DHT11(uint8_t dataPin) {
    this->dataPin= dataPin;
}

void DHT11::onStart() {
    bcm2835_gpio_fsel(dataPin, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_write(dataPin, HIGH);
}

void DHT11::onRun() {

    bcm2835_gpio_fsel(dataPin, BCM2835_GPIO_FSEL_OUTP);

    bcm2835_gpio_write(dataPin, LOW);
    bcm2835_delay(19);
    bcm2835_gpio_fsel(dataPin, BCM2835_GPIO_FSEL_INPT);


    uint8_t bytesRed=0;
    uint8_t lastLevel=0;
    uint8_t level=0;
    uint8_t state;
    uint8_t bits[40];
    clock_t t;

    while(bytesRed<40){
        level= bcm2835_gpio_lev(dataPin);

        if(level!=lastLevel){

        }

    }
}

void DHT11::onStop() {

}
