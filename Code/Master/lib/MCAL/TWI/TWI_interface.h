/**
 ******************************************************************************
 * @File           : TWI_interface.h
 * @Created on     : Sep 10, 2023
 * @Author         : Mahmoud Yasser
 ******************************************************************************
 */

#ifndef MCAL_TWI_TWI_INTERFACE_H_
#define MCAL_TWI_TWI_INTERFACE_H_

void TWI_init(void);
void TWI_start(void);
void TWI_stop(void);
void TWI_writeByte(u8 data);
u8 TWI_readByteWithACK(void);
u8 TWI_readByteWithNACK(void);
u8 TWI_getStatus(void);

#endif /* MCAL_TWI_TWI_INTERFACE_H_ */
