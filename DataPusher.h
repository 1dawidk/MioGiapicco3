#ifndef MIOGIAPICCO_DATAPUSHER_H
#define MIOGIAPICCO_DATAPUSHER_H

#include "dkulpaclibs/misc/Thread.h"
#include "Devices/SoilHumiditySensor.h"
#include "Devices/DHT22.h"
#include "WateringController.h"
#include "SunController.h"
#include "WindController.h"
#include <curl/curl.h>


class DataPusher :  public Thread{
public:
    DataPusher(const string &url,
            DHT22 *dht22,
            SoilHumiditySensor *soilHumSensor,
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
    SoilHumiditySensor *soilHumSensor;
    SunController *sunController;
    WateringController *wateringController;
    WindController *windController;

    int lastSentHour;
};


#endif //MIOGIAPICCO_DATAPUSHER_H
