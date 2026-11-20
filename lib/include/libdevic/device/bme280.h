#pragma once

#include <libdevic.h>

#include <libdevic/vendor/BME280_SensorAPI.h>

typedef struct
{
    devic_i2c_t *i2c;
    uint8_t address;

    struct bme280_dev _dev;
    uint32_t _meas_delay;
} devic_bme280_t;

// TODO error returns
void devic_bme280_init(devic_bme280_t *dev);
// TODO read all instead of one only
int32_t devic_bme280_temperature(devic_bme280_t *dev);
