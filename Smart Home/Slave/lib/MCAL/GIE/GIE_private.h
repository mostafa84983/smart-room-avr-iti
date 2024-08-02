/**
 ******************************************************************************
 * @File           : GIE_private.h
 * @Created on     : Aug 23, 2023
 * @Author         : Mahmoud Yasser
 ******************************************************************************
 */

#ifndef GIE_PRIVATE_H_
#define GIE_PRIVATE_H_

#define SREG *((volatile u8*)0x5F)

// GENERIC VECTOR DEFINITION
#ifndef _VECTOR
#define _VECTOR(N) __vector_ ## N
#endif

// ISR DEFINITION (PULLED FROM <avr/interrupts.h>)
#define __INTR_ATTRS used, externally_visible
#define ISR(vector, ...)            \
    void vector (void) __attribute__ ((signal,__INTR_ATTRS)) __VA_ARGS__; \
    void vector (void)

#endif /* GIE_PRIVATE_H_ */
