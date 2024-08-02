#ifndef TIMER_PRIVATE_H
#define TIMER_PRIVATE_H
/******************TIMER0*****************************/

/* Timer/Counter0 Register*/
#define  TCNT0		      *((volatile u8*)0x52)
/*timer0 control register*/
#define TCCR0 			 *((volatile u8*)0x53)
/*generation mode bit0 normal or ctc*/
#define TCCR0_WGM00    6
/*generation mode bit1 normal or ctc*/
#define TCCR0_WGM01    3
/*presscaler bit 2*/
#define TCCR0_CS02     2
/*presscaler bit 1*/
#define TCCR0_CS01     1
/*presscaler bit 0*/
#define TCCR0_CS00     0
/***********************/
#define TCCR0_COM01    5
/*output compare register 0*/
#define OCR0    *((volatile u8*)0x5c)
/*timer mask*/
#define TIMSK   *((volatile u8*)0x59)
/*output compare 0 interrupt enable*/
#define TIMSK_OCIE0    1
/*normal mode interrupt enable*/
#define TIMSK_TOIE0    0
/**/
/**/
/**/
/**/


#endif
