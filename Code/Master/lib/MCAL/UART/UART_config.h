#ifndef UART_CONFIG_H_
#define UART_CONFIG_H_

#ifdef F_CPU
#undef F_CPU
#endif
#define F_CPU 8000000UL

#define BAUD 9600
#define UBRR_VAL ((F_CPU / 16 / BAUD) - 1)

#define ENTER_KEY 0x0D
#define BACKSPACE_KEY 0x08
#define CTRL_BACKSPACE_KEY 0x7F
#define SPACEBAR_KEY 0x20
#define TAB_KEY 0x09

#endif
