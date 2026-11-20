#pragma once

#include <libdevic.h>
#include <ch32v00x.h>

typedef enum
{
    /** SCL=PC2, SDA=PC1 */
    DEVIC_I2C_REMAP_0,
    /** SCL=PD1, SDA=PD0 */
    DEVIC_I2C_REMAP_1,
    /** SCL=PC5, SDA=PC6 */
    DEVIC_I2C_REMAP_2,
} devic_i2c_remap_t;

void devic_i2c_init(devic_i2c_remap_t remap, uint32_t clock);
