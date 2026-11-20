#include <libdevic/port/ch32v003.h>

bool devic_gpio_get(devic_gpio_t *dev, devic_gpio_pin_t pin)
{
    GPIO_TypeDef *port = (GPIO_TypeDef *)(APB2PERIPH_BASE + (pin >> 16));
    return port->INDR & (pin & 0xFFFF);
}

void devic_gpio_set(devic_gpio_t *dev, devic_gpio_pin_t pin, bool value)
{
    GPIO_TypeDef *port = (GPIO_TypeDef *)(APB2PERIPH_BASE + (pin >> 16));
    if (value)
        port->BSHR = pin & 0xFFFF;
    else
        port->BCR = pin & 0xFFFF;
}

devic_gpio_pin_t devic_gpio_pin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
    return (((uintptr_t)GPIOx << 16) | GPIO_Pin);
}
