#include "UI.h"

void UI::init(HD44780 *disp, DHT22* dht22, SunController *sunController, WateringController *wateringController, WindController *windController) {
    this->display= disp;
    this->dht22= dht22;
    this->sunController= sunController;
    this->wateringController= wateringController;
    this->windController= windController;
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
    menuLines[TEMP_ID]= "Temp: ";
    menuLines[HUM_ID]= "Hum: ";
    menuLines[WATERING_ID]= "Watering: ";
    menuLines[WIND_ID]= "Wind: ";
    menuLines[SUN_ID]= "Sun: ";
    menuLines[TIME_ID]= "Time: ";


    menuLines[TEMP_ID]+= to_string((int)dht22->getTemperature()) + "*C";
    menuLines[HUM_ID]= to_string((int)dht22->getHumidity())+"%";

    if(wateringController->getMinLeft()==0)
        menuLines[WATERING_ID]+= "Off";
    else
        menuLines[WATERING_ID]+= to_string(wateringController->getMinLeft())+"min";

    if(windController->getState()==0){
        menuLines[WIND_ID]+= "Off";
    } else {
        menuLines[WIND_ID]+= to_string(windController->getState())+"min";
    }

    menuLines[SUN_ID]+= to_string(sunController->getState());

    int time= Clock::GetDayMinutes();
    if(time/60<10)
        menuLines[TIME_ID]+="0";
    menuLines[TIME_ID]+= to_string(time/60)+":";
    if(time%60<10)
        menuLines[TIME_ID]+="0";
    menuLines[TIME_ID]+=to_string(time%60);
}

void UI::refreshScreen() {
    if(shownMenuPointer!=menuPointer) {
        display->clrscr();
        shownMenuPointer= menuPointer;
    }
    display->write(menuLines[menuPointer], 0);
    display->write(menuLines[menuPointer+1], 1);

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
            if(menuPointer==2)
                wateringController->decTime();
            break;
        case BUTTON_RIGHT_NO:
            if(menuPointer==2)
                wateringController->incTime();
            break;
    }
}
