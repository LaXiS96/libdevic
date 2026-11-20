#include <stdio.h>
#include <libdevic/port/testing/gpio.h>

void devic_gpio_set(devic_gpio_t *dev, devic_gpio_pin_t pin, bool value)
{
    printf("gpio set %u %s", pin, value ? "true" : "false");
}
