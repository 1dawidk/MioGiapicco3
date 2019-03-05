#ifndef MIOGIAPICCO_BUTTONSMANAGER_H
#define MIOGIAPICCO_BUTTONSMANAGER_H

#include "dkulpaclibs/misc/Thread.h"
#include "bcm2835.h"
#include "vector"

using namespace std;

#define BTN_MODE_L_IDLE     0
#define BTN_MODE_H_IDLE     1

class ButtonsManager : public Thread {

public:
    ButtonsManager();
    void registerBtn(uint8_t pin, uint8_t mode);
    int getEvent();

protected:
    void onStart() override;
    void onRun() override;
    void onStop() override;

private:
    uint8_t btnsPin[12];
    uint8_t btnsNo;
    uint8_t btnsMode[12];
    uint8_t btnsLastState[12];

    vector<uint8_t> pressEvents;

    pthread_mutex_t getMutex;
};


#endif //MIOGIAPICCO_BUTTONSMANAGER_H
