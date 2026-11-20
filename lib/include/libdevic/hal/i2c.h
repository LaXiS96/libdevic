#pragma once

#define DEVIC_ERR_I2C_NACK -100
#define DEVIC_ERR_I2C_BUS_ERROR -101
#define DEVIC_ERR_I2C_ARBITRATION_LOST -102
#define DEVIC_ERR_I2C_OVERRUN -103

typedef struct devic_i2c devic_i2c_t;

typedef struct
{
    const uint8_t *data;
    size_t length;
} devic_i2c_buffer_t;

/**
 * @param write_bufs buffer of bytes to write, NULL skips writing
 * @param write_len number of bytes to write, 0 skips writing
 * @param read_buf buffer for read data, NULL skips reading
 * @param read_len number of bytes to read, 0 skips reading
 */
devic_err_t devic_i2c_transfer(devic_i2c_t *dev, uint8_t address, const uint8_t *write_buf, size_t write_len, uint8_t *read_buf, size_t read_len);

/**
 * @param write_bufs array of buffers to write, NULL skips writing
 * @param write_len number of write buffers, 0 skips writing
 * @param read_buf buffer for read data, NULL skips reading
 * @param read_len number of bytes to read, 0 skips reading
 */
devic_err_t devic_i2c_transferv(devic_i2c_t *dev, uint8_t address, const devic_i2c_buffer_t *write_bufs, size_t write_len, uint8_t *read_buf, size_t read_len);
