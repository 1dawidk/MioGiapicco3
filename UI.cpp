#include "UI.h"

void UI::init(HD44780 *disp, DHT22* dht22, SunController *sunController, WateringController *wateringController) {
    this->display= disp;
    this->dht22= dht22;
    this->sunController= sunController;
    this->wateringController= wateringController;
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
    shownMenuPointer=122;
}

void UI::onRun() {

    refreshData();
    refreshScreen();
    testCtrlButtons();

    Thread::pause(200);
}

void UI::onStop() {

}

void UI::refreshData() {
    menuDatas[0]= to_string((int)dht22->getTemperature());
    menuDatas[1]= to_string((int)dht22->getHumidity());
    menuDatas[2]= to_string(wateringController->getState());
    menuDatas[3]= to_string(sunController->getState());
    int time= Clock::GetDayMinutes();
    menuDatas[4]= to_string(time/60)+":"+to_string(time%60);
}

void UI::refreshScreen() {
    if(shownMenuPointer!=menuPointer) {
        display->clrscr();
        shownMenuPointer= menuPointer;
    }
    display->write(menuNames[menuPointer] + ": " + menuDatas[menuPointer]+menuUnits[menuPointer], 0);
    display->write(menuNames[menuPointer + 1] + ": " + menuDatas[menuPointer+1]+menuUnits[menuPointer+1], 1);

    display->writexy(15, 0, "<");
}

void UI::testCtrlButtons() {
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
}
