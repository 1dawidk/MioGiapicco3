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
    display->write(menuNames[menuPointer]+": ", 0);
    display->write(menuNames[menuPointer+1]+": ", 1);

    int buttonPressed= buttonsManager->getEvent();

    switch (buttonPressed){
        case -1:
            break;
        case BUTTON_UP_NO:
            if(menuPointer>0)
                menuPointer--;
            break;
        case BUTTON_DOWN_NO:
            if(menuPointer<MENU_ITEMS_NO-2)
                menuPointer++;
            break;
        case BUTTON_LEFT_NO:
            cout << "LEFT button pressed" << endl;
            break;
        case BUTTON_RIGHT_NO:
            cout << "RIGHT button pressed" << endl;
            break;
    }

    Thread::pause(200);
}

void UI::onStop() {

}
