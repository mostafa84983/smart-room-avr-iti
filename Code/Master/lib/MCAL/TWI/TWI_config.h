/**
 ******************************************************************************
 * @File           : TWI_config.h
 * @Created on     : Sep 10, 2023
 * @Author         : Mahmoud Yasser
 ******************************************************************************
 */

#ifndef MCAL_TWI_TWI_CONFIG_H_
#define MCAL_TWI_TWI_CONFIG_H_

#define TWI_START         0x08 /* start has been sent */
#define TWI_REP_START     0x10 /* repeated start */
#define TWI_MT_SLA_W_ACK  0x18 /* Master transmit ( slave address + Write request ) to slave + ACK received from slave. */
#define TWI_MT_SLA_R_ACK  0x40 /* Master transmit ( slave address + Read request ) to slave + ACK received from slave. */
#define TWI_MT_DATA_ACK   0x28 /* Master transmit data and ACK has been received from Slave. */
#define TWI_MR_DATA_ACK   0x50 /* Master received data and send ACK to slave. */
#define TWI_MR_DATA_NACK  0x58 /* Master received data but doesn't send ACK to slave. */

#define TWEN				2
#define TWSTO				4
#define TWSTA				5
#define TWEA				6
#define TWINT				7

\
#endif /* MCAL_TWI_TWI_CONFIG_H_ */
