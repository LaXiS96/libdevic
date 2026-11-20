#include <libdevic/device/blink.h>

void devic_blink_init(devic_blink_t *dev, devic_gpio_t *gpio, devic_gpio_pin_t pin)
{
    dev->gpio = gpio;
    dev->pin = pin;
}

void devic_blink(devic_blink_t *dev)
{
    bool state = devic_gpio_get(dev->gpio, dev->pin);
    devic_gpio_set(dev->gpio, dev->pin, !state);
}
