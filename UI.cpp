#include "UI.h"

void UI::init(HD44780 *disp) {
    this->display= disp;
    this->start();
}

void UI::onStart() {
    buttonsManager= new ButtonsManager;
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

    if(buttonsManager->getEvent()!=-1){
        cout << "Press event occurred :)";
    }

    Thread::pause(20);
}

void UI::onStop() {

}
