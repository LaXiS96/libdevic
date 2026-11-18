#pragma once

#include <libdevic/hal/gpio.h>
#include <ch32v00x.h>

/** Global GPIO driver instance */
extern devic_gpio_t devic_gpio;

devic_gpio_pin_t devic_gpio_pin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
