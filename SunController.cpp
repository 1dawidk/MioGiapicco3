#include "SunController.h"


void SunController::onStart() {
    int dayM= Clock::GetDayMinutes();
    int h= dayM/60;

    state= sunAtHalfHour[h];
}

void SunController::onRun() {
    int dayM= Clock::GetDayMinutes();
    int h= dayM/60;

    if(state<sunAtHalfHour[h])
        state++;
    else if(state>sunAtHalfHour[h])
        state--;

    Thread::pause(120000);
}

void SunController::onStop() {

}


int SunController::getState() {
    return state;
}
