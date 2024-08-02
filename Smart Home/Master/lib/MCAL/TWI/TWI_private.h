/**
 ******************************************************************************
 * @File           : TWI_private.h
 * @Created on     : Sep 10, 2023
 * @Author         : Mahmoud Yasser
 ******************************************************************************
 */

#ifndef MCAL_TWI_TWI_PRIVATE_H_
#define MCAL_TWI_TWI_PRIVATE_H_

#define TWBR	*((volatile u8*)0x20)
#define TWSR	*((volatile u8*)0x21)
#define TWAR	*((volatile u8*)0x22)
#define TWCR	*((volatile u8*)0x56)
#define TWDR	*((volatile u8*)0x23)

#endif /* MCAL_TWI_TWI_PRIVATE_H_ */
