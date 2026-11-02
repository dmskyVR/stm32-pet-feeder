#include "uart.h"
#include "stm32c0xx.h"

void UART_sendChar(char c)
{
    while(!(USART2->ISR & USART_ISR_TXE_TXFNF_Msk)) //wait until USART is ready to accept char
    {
    }
    USART2->TDR = c; //send char
}

void UART_sendStr(const char *str)
{
    //loop iterating over elements to send one char at a time
    int i = 0;
    while(str[i] != '\0')
    {
        UART_sendChar(str[i]);
        ++i;
    }
}

void UART_init(void)
{
    RCC->IOPENR |= RCC_IOPENR_GPIOAEN; //enable gpioa
    RCC->APBENR1 |= RCC_APBENR1_USART2EN; //enable usart2 
    GPIOA->MODER &= ~(GPIO_MODER_MODE2_Msk | GPIO_MODER_MODE3_Msk); //clear for pa2 pa3
    GPIOA->MODER |= (GPIO_MODER_MODE2_1| GPIO_MODER_MODE3_1); //set for pa2 pa3
    GPIOA->AFR[0] &= ~(GPIO_AFRL_AFSEL2_Msk | GPIO_AFRL_AFSEL3_Msk); //set the alternate function as uart
    GPIOA->AFR[0] |= (GPIO_AFRL_AFSEL2_0 | GPIO_AFRL_AFSEL3_0); //set the alternate function as uart
    USART2->BRR = 104; // baud rate
    USART2->CR1 |= USART_CR1_TE_Msk | USART_CR1_UE_Msk; //enable TE and UE
}