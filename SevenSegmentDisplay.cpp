#include "SevenSegmentDisplay.h"

void SevenSegmentDisplay::init(int digitsNo) {
    this->digitsNo= digitsNo;
}

void SevenSegmentDisplay::onStart() {
    //TODO: Init GPIOs

    //TODO: Compute digit on time (in ms)

    displayingDigit= 0;
}

void SevenSegmentDisplay::onRun() {
    //TODO: Set common cathode(anode) for i digit as on

    //TODO: Set anodes(cathodes) of segments as on

    //Keep it on for several ms
    Thread::pause(digitOnMs);

    //Go to next digit
    displayingDigit++;
    if(displayingDigit>=digitsNo)
        displayingDigit=0;
}

void SevenSegmentDisplay::onStop() {

}
