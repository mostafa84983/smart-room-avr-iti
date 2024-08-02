/**
 ******************************************************************************
 * @File           : TIMER1_private.h
 * @Created on     : Aug 29, 2023
 ******************************************************************************
 */

#ifndef TIMER1_PRIVATE_H_
#define TIMER1_PRIVATE_H_

/**TIMER1 INTIAL **/
#define TCNT1               *((volatile u16*)0x4C)
//Timer 1A Control Register
#define TCCR1A				*((volatile u8*)0x4f)
#define TCCR1A_WGM10		0
#define TCCR1A_WGM11		1
#define TCCR1A_COM1A0		6
#define TCCR1A_COM1A1		7
//Timer 1b Control Register
#define TCCR1B				*((volatile u8*)0x4e)
#define TCCR1B_WGM12		3
#define TCCR1B_WGM13		4
#define TCCR1B_CS10		    0
#define TCCR1B_CS11		    1
//ICR1 Register
#define ICR1				*((volatile u16*)0x46)
//OCR1A Register
#define OCR1A				*((volatile u16*)0x4a)

#endif /* TIMER1_PRIVATE_H_ */
