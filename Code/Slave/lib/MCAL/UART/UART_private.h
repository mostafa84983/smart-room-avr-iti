#ifndef UART_PRIVATE_H_
#define UART_PRIVATE_H_


// USART I/O Data Register
#define UDR *((volatile u8 *)0x2C)
// USART Control and Status Register A
#define UCSRA *((volatile u8 *)0x2B)
// USART Control and Status Register B
#define UCSRB *((volatile u8 *)0x2A)
// USART Control and Status Register C
#define UCSRC *((volatile u8 *)0x40)
// USART Baud Rate Register High
#define UBRRH *((volatile u8 *)0x40)
// USART Baud Rate Register Low
#define UBRRL *((volatile u8 *)0x29)

// Multi-processor Communication Mode
#define UCSRA_MPCM 		0
//  Double the USART Transmission Speed
#define UCSRA_U2X 		1
//  Parity Error
#define UCSRA_PE		2
// Data OverRun
#define UCSRA_DOR 		3
//  Frame Error
#define UCSRA_FE 		4
// USART Data Register Empty
#define UCSRA_UDRE 		5
// USART Transmit Complete
#define UCSRA_TXC 		6
// USART Receive Complete
#define UCSRA_RXC 		7

// TRANSMITTER ENABLE
#define UCSRB_TXEN 		3
// RECEIVER ENABLE
#define UCSRB_RXEN 		4
//  USART Data Register Empty Interrupt Enable
#define UCSRB_UDRIE 	5
// TX Complete Interrupt Enable
#define UCSRB_TXCIE 	6
// RX Complete Interrupt Enable
#define UCSRB_RXCIE 	7

// CHARCTER SIZE 0
#define UCSRC_UCSZ0 	1
// CHARCTER SIZE 1
#define UCSRC_UCSZ1 	2
// REGISTER SELECT 1->UCSRC , 0->UBRRH
#define UCSRC_URSEL 	7

#endif
