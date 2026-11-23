#include "bsp.h"
#include "uart.h"

typedef enum {
    SERVO_CENTER,
    SERVO_LEFT,
    SERVO_RIGHT
} ServoState;

int main(void)
{
    BSP_init();
    u32 lastServoChange = BSP_getTicks();
    ServoState servoState = SERVO_CENTER;
    UART_sendStr("Pet Feeder: Initialized\r\n");
    UART_sendStr("CENTER (1500 us)\r\n");
    while(1)
    {
        u32 now = BSP_getTicks();
        if(now - lastServoChange >= 2000U)
        {
            switch(servoState)
            {
                case SERVO_CENTER:
                {
                    servoState = SERVO_LEFT;
                    BSP_servoSetPulse(1300U);
                    UART_sendStr("Servo: 1300 us\r\n");
                    break;
                }
                case SERVO_LEFT:
                {
                    servoState = SERVO_RIGHT;
                    BSP_servoSetPulse(1700U);
                    UART_sendStr("Servo: 1700 us\r\n");
                    break;
                }
                case SERVO_RIGHT:
                {
                    servoState = SERVO_CENTER;
                    BSP_servoSetPulse(1500U);
                    UART_sendStr("Servo: 1500 us\r\n");
                    break;
                }
            }
            lastServoChange = now;
        }
    }
    return 0;
}
