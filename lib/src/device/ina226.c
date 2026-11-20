#include <libdevic/device/ina226.h>

static devic_err_t ina226_reset(devic_ina226_t *dev)
{
    return devic_i2c_transfer(dev->i2c, dev->address,
                              (uint8_t[]){INA226_REG_CONFIGURATION, 0x80, 0x00}, 3,
                              NULL, 0);
}

devic_err_t devic_ina226_init(devic_ina226_t *dev)
{
    return ina226_reset(dev);
}

devic_err_t devic_ina226_configure(devic_ina226_t *dev, devic_ina226_average_t average, devic_ina226_convtime_t bus_convtime, devic_ina226_convtime_t shunt_convtime)
{
    uint8_t buf[2] = {0};
    devic_err_return(devic_i2c_transfer(dev->i2c, dev->address,
                                        (uint8_t[]){INA226_REG_CONFIGURATION}, 1,
                                        buf, 2));
    uint16_t config = devic_u8_to_u16(buf[0], buf[1]);
    devic_bsm(config, 9, 0b111, average);
    devic_bsm(config, 6, 0b111, bus_convtime);
    devic_bsm(config, 3, 0b111, shunt_convtime);
    devic_err_return(devic_i2c_transfer(dev->i2c, dev->address,
                                        (uint8_t[]){INA226_REG_CONFIGURATION, devic_u16_be(config)}, 3,
                                        NULL, 0));
    return DEVIC_OK;
}

devic_err_t devic_ina226_alert(devic_ina226_t *dev, devic_ina226_alert_t alert)
{
    return devic_i2c_transfer(dev->i2c, dev->address,
                              (uint8_t[]){INA226_REG_MASK_ENABLE, devic_u16_be(alert)}, 3,
                              NULL, 0);
}

devic_err_t devic_ina226_readout(devic_ina226_t *dev, uint32_t *bus_voltage, int32_t *current, uint32_t *power)
{
    uint8_t buf[2] = {0};
    devic_err_return(devic_i2c_transfer(dev->i2c, dev->address,
                                        (uint8_t[]){INA226_REG_SHUNT_VOLTAGE}, 1,
                                        buf, 2));
    int16_t vshunt = (int16_t)devic_u8_to_u16(buf[0], buf[1]);
    devic_err_return(devic_i2c_transfer(dev->i2c, dev->address,
                                        (uint8_t[]){INA226_REG_BUS_VOLTAGE}, 1,
                                        buf, 2));
    uint16_t vbus = (uint16_t)devic_u8_to_u16(buf[0], buf[1]);

    *bus_voltage = (uint32_t)vbus * 125 / 100;                // 1.25mV LSB
    *current = vshunt * (int32_t)dev->current_lsb;            // 2.5uV LSB = Current_LSB in uA
    *power = *bus_voltage * (devic_abs_u32(*current) / 1000); // mV * mA = uW
    return DEVIC_OK;
}

devic_err_t devic_ina226_read_flags(devic_ina226_t *dev, devic_ina226_flag_t *flags)
{
    uint8_t buf[2] = {0};
    devic_err_return(devic_i2c_transfer(dev->i2c, dev->address,
                                        (uint8_t[]){INA226_REG_MASK_ENABLE}, 1,
                                        buf, 2));
    *flags = devic_u8_to_u16(buf[0], buf[1]);
    return DEVIC_OK;
}
