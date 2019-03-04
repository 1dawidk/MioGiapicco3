#include "UI.h"

void UI::init(HD44780 *disp) {
    this->display= disp;
    this->start();
}

void UI::onStart() {
    cout << logo;
}

void UI::onRun() {
    display->write("Temperature: 21*C", 0);
    display->write("Humidity: 44%%", 1);
    Thread::pause(2000);
}

void UI::onStop() {

}
