#include "bsp.h"
#include "uart.h"
#include <stdbool.h>

#define SERVO_HOLDING_PERIOD 5000U
#define SERVO_CLOSED_PULSE 1000U
#define SERVO_OPEN_PULSE   2000U

typedef enum {
    SERVO_OPEN,
    SERVO_IDLE,
    SERVO_HOLD,
    SERVO_CLOSE,
} ServoState;

int main(void)
{
    BSP_init();
    BSP_servoSetPulse(SERVO_CLOSED_PULSE);
    u32 lastServoChange = BSP_getTicks();
    ServoState servoState = SERVO_IDLE;
    UART_sendStr("Pet Feeder: Initialized\r\n");
    UART_sendStr("State: IDLE\r\n");
    while(1)
    {
        u32 now = BSP_getTicks();
        bool pressed = BSP_buttonPressed();
        switch(servoState)
        {
            case SERVO_IDLE:
            {
                if(pressed)
                {
                    servoState = SERVO_OPEN;
                }
                break;
            }
            case SERVO_OPEN:
            {
                UART_sendStr("State: OPENING\r\n");
                BSP_servoSetPulse(SERVO_OPEN_PULSE);
                lastServoChange = now;
                servoState = SERVO_HOLD;
                UART_sendStr("State: HOLDING\r\n");
                break;
            }
            case SERVO_HOLD:
            {
                if(now - lastServoChange >= SERVO_HOLDING_PERIOD)
                {
                    servoState = SERVO_CLOSE;
                }
                break;
            }
            case SERVO_CLOSE:
            {
                UART_sendStr("State: CLOSING\r\n");
                BSP_servoSetPulse(SERVO_CLOSED_PULSE);
                servoState = SERVO_IDLE;
                UART_sendStr("State: IDLE\r\n");
                break;
            }
        }
    }
    return 0;
}
