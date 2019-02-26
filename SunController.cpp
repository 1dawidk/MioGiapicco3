#include "SunController.h"


void SunController::onStart() {
    bcm2835_gpio_fsel(RPI_GPIO_P1_12, BCM2835_GPIO_FSEL_ALT5);


    bcm2835_pwm_set_clock(BCM2835_PWM_CLOCK_DIVIDER_16);
    bcm2835_pwm_set_mode(0, 1, 1);
    bcm2835_pwm_set_range(0, 1024);
}

void SunController::onRun() {

    //This sets width
    //bcm2835_pwm_set_data(0, value)
}

void SunController::onStop() {

}
