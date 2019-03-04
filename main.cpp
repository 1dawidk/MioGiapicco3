#include <iostream>

#include "UI.h"
#include "ImagePusher.h"
#include "SunController.h"
#include "Peripherals/I2C.h"
#include "Devices/DHT11.h"
#include "Devices/HD44780.h"
#include "Devices/PCA9685.h"

int main() {
    UI *ui= new UI;

    bcm2835_init();
    //bcm2835_set_debug(1);

    I2C *i2c;

    DHT11 *dht11;
    HD44780 *display;
    PCA9685 *pca9685;

    SunController *sunController;

    ImagePusher *imagePusher;


    //Create objects
    i2c= new I2C((uint16_t)100000);
    imagePusher= new ImagePusher;
    display= new HD44780(2, 16, HD44780_BUS_I2C, i2c, 0x27);

    sunController= new SunController;
    dht11= new DHT11(RPI_BPLUS_GPIO_J8_12);


    //Init / Start
    display->init();
    display->write("Init...", 0);
    dht11->start();
    //imagePusher->init("https://dawidkulpa.pl/projects/miogiapicco30/imgrec.php");
    //sunController->start();

    display->write("Init [Done]", 0);
    delay(2000);
    display->clrscr();

    ui->init();


    getchar();
    ui->stop();

    bcm2835_close();

    return 0;
}