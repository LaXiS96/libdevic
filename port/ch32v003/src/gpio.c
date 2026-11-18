#include <libdevic/port/ch32v003/gpio.h>

devic_gpio_pin_t devic_gpio_pin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    return (((uintptr_t)GPIOx << 16) | GPIO_Pin);
}

static bool get(void *ctx, devic_gpio_pin_t pin)
{
    GPIO_TypeDef *port = (GPIO_TypeDef *)(APB2PERIPH_BASE + (pin >> 16));
    return port->INDR & (pin & 0xFFFF);
}

static void set(void *ctx, devic_gpio_pin_t pin, bool value)
{
    GPIO_TypeDef *port = (GPIO_TypeDef *)(APB2PERIPH_BASE + (pin >> 16));
    if (value)
        port->BSHR = pin & 0xFFFF;
    else
        port->BCR = pin & 0xFFFF;
}

static const devic_gpio_fn_t fn = {
    .get = get,
    .set = set,
};

devic_gpio_t devic_gpio = {
    .fn = &fn,
};
