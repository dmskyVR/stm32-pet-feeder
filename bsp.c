#include "bsp.h"
#include "uart.h"
#include "stm32c0xx.h"
static volatile u32 tickCounter = 0U;

void SysTick_Handler(void)
{
    tickCounter++;
}

u32 BSP_getTicks(void)
{
    return tickCounter;
}

static void SysTick_init(void)
{
    // Configure SysTick for a 1 ms interrupt interval    
    SysTick->CTRL = 0U;
    SysTick->LOAD = (SystemCoreClock / BSP_TICKS_PER_SEC) - 1U;
    SysTick->VAL = 0U;
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;
}

void BSP_init(void)
{
    UART_init();
    SysTick_init();
}
