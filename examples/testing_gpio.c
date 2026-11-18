#include <stdio.h>
#include <libdevic/port/testing.h>

static devic_gpio_t gpio = {};

int main(void)
{
    devic_gpio_init(&gpio);

    gpio.fn->set(NULL, 1, true);

    return 0;
}
