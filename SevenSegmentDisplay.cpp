#include "SevenSegmentDisplay.h"

SevenSegmentDisplay::SevenSegmentDisplay(uint8_t *digitsPins, uint8_t *segmentsPins, uint8_t digitNo, uint8_t mode) {
    this->digitsNo= digitNo;
    this->digitsPins= digitsPins;
    this->segsPins= segmentsPins;
    this->mode= mode;
}

void SevenSegmentDisplay::onStart() {
    //Init GPIOs
    for(int i=0; i<digitsNo; i++){
        bcm2835_gpio_fsel(digitsPins[i], BCM2835_GPIO_FSEL_OUTP);
    }
    for(int i=0; i<SEGMENTS_NO; i++){
        bcm2835_gpio_fsel(segsPins[i], BCM2835_GPIO_FSEL_OUTP);
    }

    //Compute digit on time (in us)
    digitOnUs= 1000000/(6*digitsNo);

    displayingDigit= 0;
}

void SevenSegmentDisplay::onRun() {
    //TODO: Set common cathode(anode) for i digit as on

    //TODO: Set anodes(cathodes) of segments as on

    //Keep it on for several ms
    Thread::pauseUs(digitOnUs);

    //TODO: Deactivate digit display

    //Go to next digit
    displayingDigit++;
    if(displayingDigit>=digitsNo)
        displayingDigit=0;
}

void SevenSegmentDisplay::onStop() {

}
