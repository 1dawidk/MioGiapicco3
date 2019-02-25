#include "UI.h"

void UI::init() {
    this->start();
}

void UI::onStart() {
    cout << logo;
}

void UI::onRun() {
    cout << "Run" << endl;
}

void UI::onStop() {

}
