#include <iostream>

#include "UI.h"
#include "ImagePusher.h"
#include "SunController.h"
#include "NJU6450Driver.h"
#include "DHT11.h"

int main() {
    UI *ui= new UI;

    bcm2835_init();

    ImagePusher *imagePusher= new ImagePusher;
    NJU6450Driver *display;
    SunController *sunController;
    DHT11 *dht11;

    //Create objects
    uint8_t disp_datapins[]= {
        RPI_BPLUS_GPIO_J8_29, RPI_BPLUS_GPIO_J8_31, RPI_BPLUS_GPIO_J8_33,
        RPI_BPLUS_GPIO_J8_35, RPI_BPLUS_GPIO_J8_37, RPI_BPLUS_GPIO_J8_36,
        RPI_BPLUS_GPIO_J8_38, RPI_BPLUS_GPIO_J8_40};
    display= new NJU6450Driver(disp_datapins, RPI_BPLUS_GPIO_J8_32,
            RPI_BPLUS_GPIO_J8_16, RPI_BPLUS_GPIO_J8_18,
            RPI_BPLUS_GPIO_J8_22);

    dht11= new DHT11(RPI_BPLUS_GPIO_J8_18);

    sunController= new SunController;

    //Init / Start
    display->init();
    dht11->start();
    //imagePusher->init("https://dawidkulpa.pl/projects/miogiapicco30/imgrec.php");
    //sunController->start();

    ui->init();



    while(ui->isRunning());

    return 0;
}