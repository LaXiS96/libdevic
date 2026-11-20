#pragma once

#include <libdevic.h>

typedef struct
{
    /** GPIO driver instance */
    devic_gpio_t *gpio;
    /** GPIO pin that will be blinked */
    devic_gpio_pin_t pin;
} devic_blink_t;

void devic_blink_init(devic_blink_t *dev, devic_gpio_t *gpio, devic_gpio_pin_t pin);
void devic_blink(devic_blink_t *dev);
