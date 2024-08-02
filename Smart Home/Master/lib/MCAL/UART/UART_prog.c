#include "../../../include/STD_TYPES.h"
#include "../../../include/BIT_MATH.h"
#include "UART_private.h"
#include "UART_config.h"
#include "UART_interface.h"

void UART_VidInit(void)
{
    // SELECT THIS REGISTER
    SET_BIT(UCSRC, UCSRC_URSEL);
    // SET  FORMAT 8 DATA, 1 STOP, NO PARITY
    SET_BIT(UCSRC, UCSRC_UCSZ0);
    SET_BIT(UCSRC, UCSRC_UCSZ1);
    // SET BAUD RATE TO 9600
    UBRRH = (u8)(UBRR_VAL >> 8);
    UBRRL = (u8)UBRR_VAL;
    // ENABLE RX & TX
    SET_BIT(UCSRB, UCSRB_RXEN);
    SET_BIT(UCSRB, UCSRB_TXEN);
}

void UART_VidSendByte(u8 Copy_u8Byte)
{
    // Polling until UDR is empty
    while (GET_BIT(UCSRA, UCSRA_UDRE) != 1)
        ;
    // Send Data
    UDR = Copy_u8Byte;
}

void UART_VidSendString(const char *str)
{
    while (*str)
        UART_VidSendByte(*str++);
}

u8 UART_u8ReceiveData(void)
{
    // Polling until receive complete
    while (GET_BIT(UCSRA, UCSRA_RXC) != 1)
        ;
    return UDR;
}
