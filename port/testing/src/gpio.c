#include <stdio.h>
#include <libdevic/port/testing/gpio.h>

static void set(void *ctx, devic_gpio_pin_t pin, bool value)
{
    printf("gpio set %u %s", pin, value ? "true" : "false");
}

static const devic_gpio_fn_t fn = {
    .set = set,
};

void devic_testing_gpio_init(devic_gpio_t *dev)
{
    dev->fn = &fn;
}
