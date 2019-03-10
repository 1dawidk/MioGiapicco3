#include "SunController.h"


void SunController::onStart() {
    int dayM= Clock::GetDayMinutes();
    int hh= dayM/30;

    state= sunAtHalfHour[hh];

    bcm2835_gpio_fsel(RPI_BPLUS_GPIO_J8_12, BCM2835_GPIO_FSEL_ALT5);
    bcm2835_pwm_set_clock(BCM2835_PWM_CLOCK_DIVIDER_16);
    bcm2835_pwm_set_mode(0, 1, 1);
    bcm2835_pwm_set_range(0, 1000);
}

void SunController::onRun() {
    int dayM= Clock::GetDayMinutes();
    int hh= dayM/30;

    if(state<sunAtHalfHour[hh]) {
        state++;
        bcm2835_pwm_set_data(0, (uint32_t)state*10);
    } else if(state>sunAtHalfHour[hh]) {
        state--;
        bcm2835_pwm_set_data(0, (uint32_t)state*10);
    }

    Thread::pause(120000);
}

void SunController::onStop() {

}


int SunController::getState() {
    return state;
}
