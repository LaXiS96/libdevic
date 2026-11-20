#pragma once

#include <libdevic.h>

// TODO copy documentation over

typedef enum
{
    INA226_REG_CONFIGURATION = 0x00,
    INA226_REG_SHUNT_VOLTAGE = 0x01,
    INA226_REG_BUS_VOLTAGE = 0x02,
    INA226_REG_POWER = 0x03,
    INA226_REG_CURRENT = 0x04,
    INA226_REG_CALIBRATION = 0x05,
    INA226_REG_MASK_ENABLE = 0x06,
    INA226_REG_ALERT_LIMIT = 0x07,
    INA226_REG_MANUFACTURER_ID = 0xFE,
    INA226_REG_DIE_ID = 0xFF,
} devic_ina226_register_t;

typedef enum
{
    INA226_AVERAGE_1,
    INA226_AVERAGE_4,
    INA226_AVERAGE_16,
    INA226_AVERAGE_64,
    INA226_AVERAGE_128,
    INA226_AVERAGE_256,
    INA226_AVERAGE_512,
    INA226_AVERAGE_1024,
} devic_ina226_average_t;

typedef enum
{
    INA226_CONVTIME_140us,
    INA226_CONVTIME_204us,
    INA226_CONVTIME_332us,
    INA226_CONVTIME_588us,
    INA226_CONVTIME_1100us,
    INA226_CONVTIME_2116us,
    INA226_CONVTIME_4156us,
    INA226_CONVTIME_8244us,
} devic_ina226_convtime_t;

typedef enum
{
    INA226_ALERT_LATCHING = (1 << 0),
    INA226_ALERT_POLARITY_INVERTED = (1 << 1),
    INA226_ALERT_ON_CONVERSION_READY = (1 << 10),
    INA226_ALERT_ON_POWER_OVER = (1 << 11),
    INA226_ALERT_ON_BUS_UNDER = (1 << 12),
    INA226_ALERT_ON_BUS_OVER = (1 << 13),
    INA226_ALERT_ON_SHUNT_UNDER = (1 << 14),
    INA226_ALERT_ON_SHUNT_OVER = (1 << 15),
} devic_ina226_alert_t;

typedef enum
{
    INA226_FLAG_OVERFLOW = (1 << 2),
    INA226_FLAG_CONVERSION_READY = (1 << 3),
    INA226_FLAG_ALERT = (1 << 4),
} devic_ina226_flag_t;

typedef struct
{
    devic_i2c_t *i2c;

    /** I2C address, right-aligned */
    uint8_t address;
    /** Current LSB in microamperes */
    uint16_t current_lsb;
} devic_ina226_t;

devic_err_t devic_ina226_init(devic_ina226_t *dev);
devic_err_t devic_ina226_configure(devic_ina226_t *dev, devic_ina226_average_t average, devic_ina226_convtime_t bus_convtime, devic_ina226_convtime_t shunt_convtime);
devic_err_t devic_ina226_alert(devic_ina226_t *dev, devic_ina226_alert_t alert);
devic_err_t devic_ina226_readout(devic_ina226_t *dev, uint32_t *bus_voltage, int32_t *current, uint32_t *power);
devic_err_t devic_ina226_read_flags(devic_ina226_t *dev, devic_ina226_flag_t *flags);
