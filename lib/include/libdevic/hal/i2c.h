#pragma once

#define DEVIC_ERR_I2C_NACK -100
#define DEVIC_ERR_I2C_BUS_ERROR -101
#define DEVIC_ERR_I2C_ARBITRATION_LOST -102
#define DEVIC_ERR_I2C_OVERRUN -103

typedef struct devic_i2c devic_i2c_t;

/**
 * @param write_buf NULL skips write
 * @param write_len 0 skips write
 * @param read_buf NULL skips read
 * @param read_len 0 skips read
 */
devic_err_t devic_i2c_transfer(devic_i2c_t *dev, uint8_t address, const uint8_t *write_buf, size_t write_len, uint8_t *read_buf, size_t read_len);
