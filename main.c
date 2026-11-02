#include "bsp.h"
#include "uart.h"

int main(void)
{
    BSP_init();
    u32 lastTransmission = 0U;
    while(1)
    {
        u32 now = BSP_getTicks();
        if(now - lastTransmission >= 1000U)
        {
            UART_sendStr("Hello world!\r\n");
            lastTransmission = now;
        }
    }
    return 0;
}
