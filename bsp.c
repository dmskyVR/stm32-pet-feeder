#include "bsp.h"
#include "stm32c031xx.h"
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

void BSP_servoInit(void)
{
    RCC->IOPENR |= RCC_IOPENR_GPIOAEN_Msk; //enable gpioa clock
    GPIOA->MODER &= ~GPIO_MODER_MODE6_Msk; //configure pa6 to alternate function
    GPIOA->MODER |= GPIO_MODER_MODE6_1;
    GPIOA->AFR[0] &= ~GPIO_AFRL_AFSEL6_Msk; // af1 for pa6(tim3)
    GPIOA->AFR[0] |= GPIO_AFRL_AFSEL6_0;
    RCC->APBENR1 |= RCC_APBENR1_TIM3EN_Msk; //enable peripheral clock
    TIM3->PSC = 11; //divide clock by 12
    TIM3->ARR = 19999; //20000 ticks
    TIM3->CCR1 = 1500; //1500 ticks
    TIM3->CCMR1 &= ~TIM_CCMR1_OC1M_Msk; //channel 1 for pwm mode 1
    TIM3->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2;
    TIM3->CCMR1 &= ~TIM_CCMR1_CC1S_Msk; //channel 1 as output
    TIM3->CCER &= ~TIM_CCER_CC1P_Msk; //active-high output polarity
    TIM3->CCER |= TIM_CCER_CC1E_Msk; //enable channel 1 output
    TIM3->EGR = TIM_EGR_UG_Msk; //update event to load prescaler cfg
    TIM3->SR = ~((u32)TIM_SR_UIF_Msk); //clear update interrupt flag
    TIM3->CR1 |= TIM_CR1_CEN_Msk; //enable counter
}

void BSP_servoSetPulse(u16 pulse_us)
{
    TIM3->CCR1 = pulse_us;
}

void BSP_init(void)
{
    UART_init();
    SysTick_init();
    BSP_servoInit();
}
