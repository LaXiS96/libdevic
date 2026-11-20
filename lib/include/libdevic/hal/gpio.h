#pragma once

typedef struct devic_gpio devic_gpio_t;

typedef uintptr_t devic_gpio_pin_t;

// TODO pin setup? the basics: input, output

bool devic_gpio_get(devic_gpio_t *dev, devic_gpio_pin_t pin);
void devic_gpio_set(devic_gpio_t *dev, devic_gpio_pin_t pin, bool value);
