#include <iostream>

#include "UI.h"
#include "ImagePusher.h"
#include "SunController.h"
#include "Peripherals/I2C.h"
#include "Devices/DHT22.h"
#include "Devices/HD44780.h"
#include "Devices/PCA9685.h"
#include "DataGatherer.h"

int main() {
    UI *ui= new UI;

    bcm2835_init();
    //bcm2835_set_debug(1);

    I2C *i2c;

    DHT22 *dht22;
    HD44780 *display;
    PCA9685 *pca9685;

    SunController *sunController;
    WateringController *wateringController;
    WindController *windController;

    ImagePusher *imagePusher;
    DataGatherer *dataGatherer;


    //Create objects
    i2c= new I2C((uint16_t)100000);
    display= new HD44780(2, 16, HD44780_BUS_I2C, i2c, 0x27);
    pca9685= new PCA9685(i2c, 0x00);

    sunController= new SunController(pca9685);
    wateringController= new WateringController(RPI_BPLUS_GPIO_J8_35);
    windController= new WindController(RPI_BPLUS_GPIO_J8_37);
    dht22= new DHT22(RPI_BPLUS_GPIO_J8_15);

    imagePusher= new ImagePusher("https://dawidkulpa.pl/scripts/mioGiapicco3_imgupload.php");
    dataGatherer= new DataGatherer("https://dawidkulpa.pl/scripts/mioGiapicco3_dataupload.php",
            dht22, sunController, wateringController, windController);

    //Init / Start
    display->init();
    display->write("Init...", 0);
    dht22->start();
    imagePusher->start();
    dataGatherer->start();
    //sunController->start();
    //windController->start();

    display->write("Init [Done]", 0);
    delay(1000);
    display->clrscr();

    ui->init(display, dht22, sunController, wateringController, windController);

    while (ui->isRunning());
    ui->stop();

    bcm2835_close();

    return 0;
}