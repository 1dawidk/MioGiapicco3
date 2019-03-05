#include "UI.h"

void UI::init(HD44780 *disp, DHT22* dht22) {
    this->display= disp;
    this->dht22= dht22;
    this->start();
}

void UI::onStart() {
    buttonsManager= new ButtonsManager();
    buttonsManager->registerBtn(RPI_BPLUS_GPIO_J8_32, BTN_MODE_H_IDLE);
    buttonsManager->registerBtn(RPI_BPLUS_GPIO_J8_36, BTN_MODE_H_IDLE);
    buttonsManager->registerBtn(RPI_BPLUS_GPIO_J8_38, BTN_MODE_H_IDLE);
    buttonsManager->registerBtn(RPI_BPLUS_GPIO_J8_40, BTN_MODE_H_IDLE);
    buttonsManager->start();

    cout << logo;
    menuPointer=0;
}

void UI::onRun() {
    stringstream ss;

    display->write(menuNames[menuPointer]+": "+to_string((int)dht22->getTemperature()), 0);
    display->write(menuNames[menuPointer+1]+": "+to_string((int)dht22->getHumidity()), 1);

    if(buttonsManager->getEvent()!=-1){
        cout << "Press event occurred :)" << endl;
    }

    Thread::pause(200);
}

void UI::onStop() {

}
