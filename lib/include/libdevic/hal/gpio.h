#pragma once

typedef uintptr_t devic_gpio_pin_t;

// TODO pin setup? the basics: input, output

typedef struct
{
    bool (*get)(void *ctx, devic_gpio_pin_t pin);
    void (*set)(void *ctx, devic_gpio_pin_t pin, bool value);
} devic_gpio_fn_t;

typedef struct
{
    const devic_gpio_fn_t *fn;
    void *ctx;
} devic_gpio_t;
