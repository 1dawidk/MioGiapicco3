#include <iostream>

#include "UI.h"
#include "ImagePusher.h"
#include "SunController.h"
#include "Peripherals/I2C.h"
#include "Peripherals/SPI.h"
#include "Devices/DHT22.h"
#include "Devices/HD44780.h"
#include "Devices/PCA9685.h"
#include "DataPusher.h"
#include "Devices/MCP3208.h"
#include "Devices/SEN0193.h"

int main() {
    UI *ui= new UI;

    bcm2835_init();
    //bcm2835_set_debug(1);

    I2C *i2c;
    SPI *spi;

    DHT22 *dht22;
    HD44780 *display;
    MCP3208 *mcp3208;
    SEN0193 *soilHumSensor;

    SunController *sunController;
    WateringController *wateringController;
    WindController *windController;

    ImagePusher *imagePusher;
    DataPusher *dataPusher;


    //Create objects
    i2c= new I2C((uint16_t)100000);
    spi= new SPI(1024, SPI_MODE_CPOL1_CPHA1, SPI_LOW, SPI_LOW);
    display= new HD44780(2, 16, HD44780_BUS_I2C, i2c, 0x27);
    mcp3208= new MCP3208(spi, SPI_CHIP_0);

    uint8_t humSensorChs[]= {0, 1};
    soilHumSensor= new SEN0193(mcp3208, 1, humSensorChs, 10);

    sunController= new SunController;
    wateringController= new WateringController(RPI_BPLUS_GPIO_J8_35);
    windController= new WindController(RPI_BPLUS_GPIO_J8_37);
    dht22= new DHT22(RPI_BPLUS_GPIO_J8_15);

    imagePusher= new ImagePusher("https://dawidkulpa.pl/scripts/mioGiapicco3_imgupload.php");
    dataPusher= new DataPusher("https://dawidkulpa.pl/scripts/mioGiapicco3_dataupload.php",
            dht22, soilHumSensor, sunController, wateringController, windController);

    //Init / Start
    display->init();
    display->write("Init...", 0);
    dht22->start();
    imagePusher->start();
    dataPusher->start();
    sunController->start();
    soilHumSensor->start();
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