#pragma once

typedef struct
{
    // TODO void (*transfer)(void *ctx, uint8_t address, const uint8_t *write_buf, size_t write_len, uint8_t *read_buf, size_t read_len);
} devic_spi_fn_t;

typedef struct
{
    const devic_spi_fn_t *fn;
    void *ctx;
} devic_spi_t;
