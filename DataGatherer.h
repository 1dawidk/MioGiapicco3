#ifndef MIOGIAPICCO_DATAGATHERER_H
#define MIOGIAPICCO_DATAGATHERER_H

#include "dkulpaclibs/misc/Thread.h"
#include "Devices/DHT22.h"
#include "WateringController.h"
#include "SunController.h"
#include "WindController.h"
#include <curl/curl.h>


class DataGatherer :  public Thread{
public:
    DataGatherer(const string &url,
            DHT22 *dht22,
            SunController *sunController,
            WateringController *wateringController,
            WindController *windController);
protected:
    void onStart() override;

    void onRun() override;

    void onStop() override;

private:
    string url;

    DHT22 *dht22;
    SunController *sunController;
    WateringController *wateringController;
    WindController *windController;

    int lastSentHour;
};


#endif //MIOGIAPICCO_DATAGATHERER_H
