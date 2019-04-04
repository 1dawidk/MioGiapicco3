#include "DataPusher.h"

DataPusher::DataPusher(const string &url,
        DHT22 *dht22,
        SoilHumiditySensor *soilHumSensor,
        SunController *sunController,
        WateringController *wateringController,
        WindController *windController) {
    this->url= url;

    this->dht22= dht22;
    this->soilHumSensor= soilHumSensor;
    this->sunController= sunController;
    this->wateringController= wateringController;
    this->windController= windController;
}

void DataPusher::onStart() {
    lastSentHour=0;
}

void DataPusher::onRun() {
    int t= Clock::GetDayMinutes();
    int h= t/60;

    if(h!=lastSentHour){
        int hum= (int)dht22->getHumidity();
        int temp= (int)dht22->getTemperature();
        int sun= sunController->getState();
        int water= wateringController->getMinLeft();
        int wind= windController->getState();
        int soil= soilHumSensor->getAllChAvgLast();

        if(hum!=0 && temp!=0) {
            string curlPostFields = "hum=" + to_string(hum);
            curlPostFields += "&temp=" + to_string(temp);
            curlPostFields += "&sun=" + to_string(sun);
            curlPostFields += "&soil=" + to_string(soil);
            curlPostFields += "&water=";
            if (water)
                curlPostFields += "1";
            else
                curlPostFields += "0";
            curlPostFields += "&wind=";
            if (wind)
                curlPostFields += "1";
            else
                curlPostFields += "0";

            CURL *curlHandle = curl_easy_init();

            // Set curl opts
            curl_easy_setopt(curlHandle, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curlHandle, CURLOPT_POST, 1);
            curl_easy_setopt(curlHandle, CURLOPT_POSTFIELDS, curlPostFields.c_str());
            curl_easy_setopt(curlHandle, CURLOPT_VERBOSE, 0);

            // Perform curl
            curl_easy_perform(curlHandle);
            curl_easy_cleanup(curlHandle);

            cout << "Data uploaded: " << curlPostFields << endl;

            lastSentHour = h;
        }
    }

    Thread::pause(60000);
}

void DataPusher::onStop() {

}
