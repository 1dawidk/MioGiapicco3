#ifndef MIOGIAPICCO_SEN0193_H
#define MIOGIAPICCO_SEN0193_H


#include "MCP3208.h"
#include "dkulpaclibs/misc/Thread.h"

class SEN0193 : public Thread {
public:
    SEN0193(MCP3208 *mcp3208, uint8_t inChCnt, uint8_t *inChs, uint8_t avgFor);

    uint8_t getLastValue(uint8_t ch);
    uint8_t getAvgValue(uint8_t ch);
    uint8_t getAllChAvgLast();
    uint8_t getAllChAvgAvg();

protected:
    void onStart() override;
    void onRun() override;
    void onStop() override;

private:
    MCP3208 *mcp3208;

    float maxV;
    float minV;

    uint8_t inChCnt;
    uint8_t *inChs;
    uint8_t *chValues;

    uint8_t avgFor;
    uint8_t avgCnt;
    uint16_t *chSums;
    uint8_t *chAvgs;
};


#endif //MIOGIAPICCO_SEN0193_H
