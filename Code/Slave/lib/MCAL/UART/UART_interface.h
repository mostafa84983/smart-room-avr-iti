#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

#include "UART_config.h"

void UART_VidInit(void);
void UART_VidSendByte(u8 Copy_u8Byte);
void UART_VidSendString(const char *str);
u8 UART_u8ReceiveData(void);

#endif
