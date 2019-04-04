#include "SEN0193.h"

SEN0193::SEN0193(MCP3208 *mcp3208, uint8_t inChCnt, uint8_t *inChs, uint8_t avgFor, float min, float max) {
    this->mcp3208= mcp3208;
    this->inChCnt= inChCnt;
    this->inChs= inChs;
    chValues= new uint8_t[inChCnt];

    this->avgFor= avgFor;
    this->avgCnt=0;
    chSums= new uint16_t[inChCnt];
    chAvgs= new uint8_t[inChCnt];

    a= 100/(max-min);
    b = -a*min;
}

void SEN0193::onStart() {

}

void SEN0193::onRun() {
    avgCnt++;
    float voltage;

    for(int i=0; i<inChCnt; i++){
        voltage= mcp3208->readCh(inChs[i]);

        chValues[i]= (uint8_t)(a*voltage + b);

        std::cout << "Soil humidity - ch: " << i << ", voltage: " << voltage << "V, humidity: " << std::to_string(chValues[i]) << "%" << std::endl;

        chSums[i]+= chValues[i];
        if(avgCnt==avgFor){
            chAvgs[i]= (uint8_t)(chSums[i]/avgFor);
            chSums[i]=0;
        }
    }

    if(avgCnt==avgFor){
        avgCnt=0;
    }

    Thread::pause(1000);
}

void SEN0193::onStop() {

}

uint8_t SEN0193::getLastValue(uint8_t ch) {
    return chValues[ch];
}

uint8_t SEN0193::getAvgValue(uint8_t ch) {
    return chAvgs[ch];
}

uint8_t SEN0193::getAllChAvgLast() {
    uint16_t sum= 0;

    for(int i=0; i<inChCnt; i++){
        sum+= chValues[i];
    }

    return (uint8_t)(sum/inChCnt);
}

uint8_t SEN0193::getAllChAvgAvg() {
    uint16_t sum= 0;

    for(int i=0; i<inChCnt; i++){
        sum+= chAvgs[i];
    }

    return (uint8_t)(sum/inChCnt);
}
