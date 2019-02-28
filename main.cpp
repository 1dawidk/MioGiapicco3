#include <iostream>

#include "UI.h"
#include "ImagePusher.h"
#include "SunController.h"
#include "NJU6450Driver.h"
#include "DHT11.h"

int main() {
    UI *ui= new UI;

    bcm2835_init();
    bcm2835_set_debug(1);

    ImagePusher *imagePusher= new ImagePusher;
    NJU6450Driver *display;
    SunController *sunController;
    DHT11 *dht11;

    //Create objects
    dht11= new DHT11(RPI_BPLUS_GPIO_J8_18);

    sunController= new SunController;

    //Init / Start
    //display->init();
    dht11->start();
    //imagePusher->init("https://dawidkulpa.pl/projects/miogiapicco30/imgrec.php");
    //sunController->start();

    ui->init();


    getchar();
    ui->stop();

    bcm2835_close();

    return 0;
}