#include <libdevic/device/bme280.h>

static BME280_INTF_RET_TYPE bme280_read(uint8_t reg_addr, uint8_t *reg_data, uint32_t len, void *intf_ptr)
{
    devic_bme280_t *dev = intf_ptr;
    devic_i2c_transfer(dev->i2c, dev->address,
                       (uint8_t[]){reg_addr}, 1,
                       reg_data, len);
    return BME280_OK;
}

static BME280_INTF_RET_TYPE bme280_write(uint8_t reg_addr, const uint8_t *reg_data, uint32_t len, void *intf_ptr)
{
    devic_bme280_t *dev = intf_ptr;
    devic_i2c_transferv(dev->i2c, dev->address,
                        (devic_i2c_buffer_t[]){
                            {.data = (uint8_t[]){reg_addr}, .length = 1},
                            {.data = reg_data, .length = len},
                        },
                        2,
                        NULL, 0);
    return BME280_OK;
}

static void bme280_delay_us(uint32_t period, void *intf_ptr)
{
    devic_time_delay_us(period);
}

void devic_bme280_init(devic_bme280_t *dev)
{
    dev->_dev.intf = BME280_I2C_INTF;
    dev->_dev.intf_ptr = dev;
    dev->_dev.read = bme280_read;
    dev->_dev.write = bme280_write;
    dev->_dev.delay_us = bme280_delay_us;

    // TODO check return codes
    bme280_init(&dev->_dev);

    struct bme280_settings settings = {};
    bme280_get_sensor_settings(&settings, &dev->_dev);
    settings.osr_h = BME280_OVERSAMPLING_1X;
    settings.osr_p = BME280_OVERSAMPLING_1X;
    settings.osr_t = BME280_OVERSAMPLING_1X;
    settings.filter = BME280_FILTER_COEFF_2;
    // settings.standby_time = BME280_STANDBY_TIME_0_5_MS;
    bme280_set_sensor_settings(BME280_SEL_ALL_SETTINGS, &settings, &dev->_dev);

    // TODO allow choosing mode
    // bme280_set_sensor_mode(BME280_POWERMODE_NORMAL, &dev->_dev);
    bme280_cal_meas_delay(&dev->_meas_delay, &settings);
}

int32_t devic_bme280_temperature(devic_bme280_t *dev)
{
    bme280_set_sensor_mode(BME280_POWERMODE_FORCED, &dev->_dev);
    devic_time_delay_us(dev->_meas_delay);
    struct bme280_data data = {};
    bme280_get_sensor_data(BME280_TEMP, &data, &dev->_dev);
    return data.temperature;
}
