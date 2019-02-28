#include <bcm2835.h>
#include "DHT11.h"

DHT11::DHT11(uint8_t dataPin) {
    this->dataPin= dataPin;
}

void DHT11::onStart() {
    bcm2835_gpio_fsel(dataPin, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_write(dataPin, HIGH);
}

void DHT11::onRun() {
    int dht11_dat[5] = { 0, 0, 0, 0, 0 };

    uint8_t laststate	= HIGH;
    uint8_t counter		= 0;
    uint8_t j		= 0, i;
    float	f; /* fahrenheit */

    dht11_dat[0] = dht11_dat[1] = dht11_dat[2] = dht11_dat[3] = dht11_dat[4] = 0;

    /* pull pin down for 18 milliseconds */
    bcm2835_gpio_fsel(dataPin, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_write(dataPin, LOW);
    delay( 18 );
    /* then pull it up for 40 microseconds */
    bcm2835_gpio_write(dataPin, HIGH);
    delayMicroseconds( 40 );
    /* prepare to read the pin */
    bcm2835_gpio_fsel(dataPin, BCM2835_GPIO_FSEL_INPT);


    /* detect change and read data */
    for ( i = 0; i < MAXTIMINGS; i++ )
    {
        counter = 0;
        while ( bcm2835_gpio_lev(dataPin) == laststate )
        {
            counter++;
            delayMicroseconds( 1 );
            if ( counter == 255 )
            {
                break;
            }
        }
        laststate = bcm2835_gpio_lev(dataPin);

        if ( counter == 255 )
            break;

        /* ignore first 3 transitions */
        if ( (i >= 4) && (i % 2 == 0) )
        {
            /* shove each bit into the storage bytes */
            dht11_dat[j / 8] <<= 1;
            if ( counter > 16 )
                dht11_dat[j / 8] |= 1;
            j++;
        }
    }

    /*
     * check we read 40 bits (8bit x 5 ) + verify checksum in the last byte
     * print it out if data is good
     */

    cout << "Humidity: " << dht11_dat[0] << "." << dht11_dat[1] << "%%" << " Temperature: "
         << dht11_dat[2] << "." << dht11_dat[3] << "*C" << endl;

    if ( (j >= 40) &&
         (dht11_dat[4] == ( (dht11_dat[0] + dht11_dat[1] + dht11_dat[2] + dht11_dat[3]) & 0xFF) ) )
    {
    }else  {
        cout << "Data not good, skip" << endl;
    }

    Thread::pause(2000);

}

void DHT11::onStop() {

}
