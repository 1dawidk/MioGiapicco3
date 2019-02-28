#include "UI.h"

void UI::init() {
    this->start();
}

void UI::onStart() {
    cout << logo;
    bcm2835_gpio_fsel(RPI_BPLUS_GPIO_J8_07, BCM2835_GPIO_FSEL_OUTP);
}

void UI::onRun() {
    Thread::pause(500);
    bcm2835_gpio_write(RPI_BPLUS_GPIO_J8_07, HIGH);
    Thread::pause(500);
    bcm2835_gpio_write(RPI_BPLUS_GPIO_J8_07, LOW);
}

void UI::onStop() {

}
