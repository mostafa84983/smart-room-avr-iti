/**
 ******************************************************************************
 * @File           : EEPROM_interface.h
 * @Created on     : Sep 10, 2023
 * @Author         : Mahmoud Yasser
 ******************************************************************************
 */

#ifndef MCAL_EXIT_EEPROM_EEPROM_INTERFACE_H_
#define MCAL_EXIT_EEPROM_EEPROM_INTERFACE_H_

u8 EEPROM_writeByte(u16 u16addr,u8 u8data);
u8 EEPROM_readByte(u16 u16addr,u8 *u8data);
void EEPROM_WriteBlock(u16 u16addr,u8*u8data,u8 const size);
//u8* EEPROM_ReadBlock(u16 u16addr,u8 const size);

#endif /* MCAL_EXIT_EEPROM_EEPROM_INTERFACE_H_ */
