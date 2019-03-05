#include "ButtonsManager.h"

void ButtonsManager::registerBtn(uint8_t pin, uint8_t mode) {
    if(btnsNo<12) {
        btnsPin[btnsNo] = pin;
        btnsMode[btnsNo] = mode;

        bcm2835_gpio_fsel(pin, BCM2835_GPIO_FSEL_INPT);
        if (mode == BTN_MODE_H_IDLE)
            bcm2835_gpio_set_pud(pin, BCM2835_GPIO_PUD_UP);
        else
            bcm2835_gpio_set_pud(pin, BCM2835_GPIO_PUD_DOWN);

        btnsLastState[btnsNo]= HIGH;

        btnsNo++;
    }
}

void ButtonsManager::onStart() {
    btnsNo=0;
}

void ButtonsManager::onRun() {

    uint8_t level;

    for(uint8_t i=0; i<btnsNo; i++){
        level= bcm2835_gpio_lev(btnsPin[i]);

        if(level==LOW && level==btnsLastState[i]){
            pthread_mutex_lock(&getMutex);
            pressEvents.push_back(i);
            pthread_mutex_unlock(&getMutex);
        }
        btnsLastState[i]= level;
    }

    Thread::pause(18);
}

void ButtonsManager::onStop() {

}

int ButtonsManager::getEvent() {
    int idx=-1;

    if(!pressEvents.empty()){
        pthread_mutex_lock(&getMutex);
        idx= pressEvents[0];
        pressEvents.erase(pressEvents.begin());
        pthread_mutex_unlock(&getMutex);
    }

    return idx;
}
