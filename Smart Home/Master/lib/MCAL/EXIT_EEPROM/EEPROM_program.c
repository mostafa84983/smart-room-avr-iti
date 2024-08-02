/**
 ******************************************************************************
 * @File           : EEPROM_program.c
 * @Created on     : Sep 10, 2023
 * @Author         : Mahmoud Yasser
 ******************************************************************************
 */
#include "../../../include/BIT_MATH.h"
#include "../../../include/STD_TYPES.h"
#include "EEPROM_config.h"
#include "EEPROM_interface.h"
#include "../TWI/TWI_config.h"
#include "../TWI/TWI_interface.h"
#include "util/delay.h"
u8 EEPROM_writeByte(u16 u16addr, u8 u8data)
{
	/* Send the Start Bit */
    TWI_start();
    if (TWI_getStatus() != TWI_START)
        return ERROR;

    /* Send the device address, we need to get A8 A9 A10 address bits from the
     * memory location address and R/W=0 (write) */
    TWI_writeByte((u8)(0xA0 | ((u16addr & 0x0700)>>7)));
    if (TWI_getStatus() != TWI_MT_SLA_W_ACK)
        return ERROR;

    /* Send the required memory location address */
    TWI_writeByte((u8)(u16addr));
    if (TWI_getStatus() != TWI_MT_DATA_ACK)
        return ERROR;

    /* write byte to eeprom */
    TWI_writeByte(u8data);
    if (TWI_getStatus() != TWI_MT_DATA_ACK)
        return ERROR;

    /* Send the Stop Bit */
    TWI_stop();

    return SUCCESS;
}

u8 EEPROM_readByte(u16 u16addr, u8 *u8data)
{
	/* Send the Start Bit */
    TWI_start();
    if (TWI_getStatus() != TWI_START)
        return ERROR;

    /* Send the device address, we need to get A8 A9 A10 address bits from the
     * memory location address and R/W=0 (write) */
    TWI_writeByte((u8)((0xA0) | ((u16addr & 0x0700)>>7)));
    if (TWI_getStatus() != TWI_MT_SLA_W_ACK)
        return ERROR;

    /* Send the required memory location address */
    TWI_writeByte((u8)(u16addr));
    if (TWI_getStatus() != TWI_MT_DATA_ACK)
        return ERROR;

    /* Send the Repeated Start Bit */
    TWI_start();
    if (TWI_getStatus() != TWI_REP_START)
        return ERROR;

    /* Send the device address, we need to get A8 A9 A10 address bits from the
     * memory location address and R/W=1 (Read) */
    TWI_writeByte((u8)((0xA0) | ((u16addr & 0x0700)>>7) | 1));
    if (TWI_getStatus() != TWI_MT_SLA_R_ACK)
        return ERROR;

    /* Read Byte from Memory without send ACK */
    *u8data = TWI_readByteWithNACK();
    if (TWI_getStatus() != TWI_MR_DATA_NACK)
        return ERROR;

    /* Send the Stop Bit */
    TWI_stop();

    return SUCCESS;
}
void EEPROM_WriteBlock(u16 u16addr,u8*u8data,u8 const size)
{
	for(u8 i=0;i<size;i++)
	{
		EEPROM_writeByte(u16addr+i,u8data[i]);
		_delay_ms(10);
	}
}
/*u8* EEPROM_ReadBlock(u16 u16addr,u8 const size)
{
	u8* u8data,temp;
	for(u8 i=0;i<size;i++)
	{
		EEPROM_readByte(u16addr+i,&temp);
		u8data[i]=temp;
	}
	return u8data;
}*/
