#include <libdevic/device/blink.h>

void devic_blink_init(devic_blink_t *dev, const devic_gpio_t *gpio, const devic_gpio_pin_t pin)
{
    dev->gpio = gpio;
    dev->pin = pin;
}

void devic_blink(devic_blink_t *dev)
{
    bool state = dev->gpio->fn->get(NULL, dev->pin);
    dev->gpio->fn->set(NULL, dev->pin, !state);
}
