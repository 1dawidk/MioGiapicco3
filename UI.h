#ifndef MIOGIAPICCO_UI_H
#define MIOGIAPICCO_UI_H

#include <iomanip>
#include <sstream>
#include "iostream"
#include "string"
#include "dkulpaclibs/misc/Thread.h"
#include "bcm2835.h"
#include "Devices/HD44780.h"
#include "ButtonsManager.h"
#include "Devices/DHT22.h"

#define BUTTON_UP_NO    1
#define BUTTON_DOWN_NO  0
#define BUTTON_LEFT_NO  3
#define BUTTON_RIGHT_NO 2

#define MENU_ITEMS_NO   5

using namespace std;

class UI : public Thread {
public:
    void init(HD44780 *disp, DHT22 *dht22);

protected:
    void onStart() override;
    void onRun() override;
    void onStop() override;

private:
    HD44780 *display;
    ButtonsManager *buttonsManager;
    DHT22 *dht22;
    int8_t menuPointer;

    uint8_t refReq;
    int menuDatas[MENU_ITEMS_NO];

    const string menuNames[MENU_ITEMS_NO]= {"Temp", "Hum", "Watering", "Sun", "Time"};
    const string logo= "  __  __ _          _____ _             _                       ____   ___  \n"
                       " |  \\/  (_)        / ____(_)           (_)                     |___ \\ / _ \\ \n"
                       " | \\  / |_  ___   | |  __ _  __ _ _ __  _  ___ ___ ___           __) | | | |\n"
                       " | |\\/| | |/ _ \\  | | |_ | |/ _` | '_ \\| |/ __/ __/ _ \\         |__ <| | | |\n"
                       " | |  | | | (_) | | |__| | | (_| | |_) | | (_| (_| (_) |        ___) | |_| |\n"
                       " |_|  |_|_|\\___/   \\_____|_|\\__,_| .__/|_|\\___\\___\\___/        |____(_)___/ \n"
                       "                                 | |                                        \n"
                       "                                 |_|";

};


#endif //MIOGIAPICCO_FILEUI_H
