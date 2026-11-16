#pragma once

#include <stdint.h>
#include <stdbool.h>

typedef uint32_t devic_gpio_pin_t;

typedef struct
{
    void (*set)(void *ctx, devic_gpio_pin_t pin, bool value);
} devic_gpio_fn_t;

typedef struct
{
    const devic_gpio_fn_t *fn;
    void *ctx;
} devic_gpio_t;
