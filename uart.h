#ifndef UART_H
#define UART_H

void UART_sendChar(char c);
void UART_sendStr(const char *str);
void UART_init(void);

#endif