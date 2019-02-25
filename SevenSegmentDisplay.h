#ifndef MIOGIAPICCO_SEVENSEGMENTDISPLAY_H
#define MIOGIAPICCO_SEVENSEGMENTDISPLAY_H

#include "dkulpaclibs/misc/Thread.h"

class SevenSegmentDisplay : public Thread {

public:
    void init(int digitsNo);
    int digitsNo;

protected:
    void onStart() override;
    void onRun() override;
    void onStop() override;

private:
    int displayingDigit;
    int digitOnUs;

};


#endif //MIOGIAPICCO_SEVENSEGMENTDISPLAY_H
