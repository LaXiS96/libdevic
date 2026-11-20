#include <ch32v00x.h>

#define STK_CTLR_STE (1 << 0)   // Enable counter
#define STK_CTLR_STIE (1 << 1)  // Enable interrupt
#define STK_CTLR_STCLK (1 << 2) // Use HCLK or HCLK/8

#define CMP_VALUE (SystemCoreClock / 1000)

volatile uint32_t devic_time_ms = 0;

void devic_time_init(void)
{
    SysTick->CTLR = 0;
    SysTick->SR = 0;
    SysTick->CNT = 0;
    SysTick->CMP = CMP_VALUE;
    NVIC_EnableIRQ(SysTick_IRQn);
    SysTick->CTLR = STK_CTLR_STE | STK_CTLR_STIE | STK_CTLR_STCLK;
}

__attribute__((interrupt("WCH-Interrupt-fast"))) void SysTick_Handler(void)
{
    SysTick->CMP += CMP_VALUE;
    SysTick->SR = 0;

    devic_time_ms++;
}

void devic_time_delay_ms(uint32_t ms)
{
    uint32_t start = devic_time_ms;
    while (devic_time_ms - start < ms)
        ;
}
