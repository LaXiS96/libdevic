#pragma once

#include <libdevic.h>
#include <ch32v00x.h>

devic_gpio_pin_t devic_gpio_pin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
