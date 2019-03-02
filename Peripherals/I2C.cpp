#include "I2C.h"

I2C::I2C(uint16_t baud) {
    ready=false;

    ready=(bool)bcm2835_i2c_begin();
    bcm2835_i2c_set_baudrate(baud);

    mut= PTHREAD_MUTEX_INITIALIZER;
}

I2C::~I2C() {
    bcm2835_i2c_end();
}

bool I2C::isReady() {
    return ready;
}

uint8_t I2C::write(uint8_t sadr, uint8_t data) {
    uint8_t r=0;

    pthread_mutex_lock(&mut);
    bcm2835_i2c_setSlaveAddress(sadr);
    r+=bcm2835_i2c_write((char*)&data, 1);
    pthread_mutex_unlock(&mut);

    return r;
}

uint8_t I2C::read(uint8_t sadr) {
    uint8_t r=0;

    pthread_mutex_lock(&mut);
    bcm2835_i2c_setSlaveAddress(sadr);
    bcm2835_i2c_read((char*)&r, 1);
    pthread_mutex_unlock(&mut);

    return r;
}

uint8_t I2C::write(uint8_t sadr, uint8_t radr, const uint8_t *buff, uint8_t len) {
    uint8_t r=0;
    char buffer[1+len];
    buffer[0]=radr;
    for(int i=1; i<=len; i++)
        buffer[i]=buff[i-1];

    pthread_mutex_lock(&mut);
    bcm2835_i2c_setSlaveAddress(sadr);
    r+=bcm2835_i2c_write((char*)&buffer, len+1);
    pthread_mutex_unlock(&mut);

    return r;
}

uint8_t I2C::read(uint8_t sadr, uint8_t radr, uint8_t *buff, uint8_t len) {
    uint8_t r=0;

    pthread_mutex_lock(&mut);
    bcm2835_i2c_setSlaveAddress(sadr);
    bcm2835_i2c_read_register_rs((char*)&radr,(char*)buff, len);
    pthread_mutex_unlock(&mut);

    return r;
}