#ifndef MIOGIAPICCO_SEVENSEGMENTDISPLAY_H
#define MIOGIAPICCO_SEVENSEGMENTDISPLAY_H

#include "bcm2835.h"
#include "dkulpaclibs/misc/Thread.h"

#define SEGMENTS_NO     7

#define SEVENSEGDISP_MODE_COMMON_CATHODE     0
#define SEVENSEGDISP_MODE_COMMON_ANODE       1

class SevenSegmentDisplay : public Thread {

public:
    SevenSegmentDisplay(uint8_t *digitsPins, uint8_t *segmentsPins, uint8_t digitNo, uint8_t mode);

    int digitsNo;

protected:
    void onStart() override;
    void onRun() override;
    void onStop() override;

private:
    uint8_t *digitsPins;
    uint8_t *segsPins;
    uint8_t displayingDigit;
    int digitOnUs;
    uint8_t mode;

};


#endif //MIOGIAPICCO_SEVENSEGMENTDISPLAY_H
