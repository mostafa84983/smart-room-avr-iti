#ifndef MAIN_CONFIG_H_
#define MAIN_CONFIG_H_

#define NOT_STORED 0xFF
#define NOT_SELECTED 0xFF
#define NOT_PRESSED 0xFF

#define DEFUALT_DELAY_TIME (u16)200
#define BLOCK_MODE_TIME (u32)2000
#define CHARACTER_PREVIEW_TIME (u16)75
#define DOOR_TIME (u32)2000
#define DEGREES_SYMBOL (u8)0xDF

/*********************************** PIN Configuration ***********************************/
#define PASS_SIZE (u8)4
#define TRIES_ALLOWED (u8)3
#define PASSWORD_SYMBOL (u8)'*'
#define ASCII_ZERO (u8)'0'

#define PASS_NOT_SET (u8)0xFF
#define PASS_SET (u8)0x01

#define USER_PASS_STATUS_ADDRESS (u16)0X100
#define EEPROM_USER_ADDRESS (u16)0X102
#define LOGIN_BLOCKED_ADDRESS (u16)0X10A
/*****************************************************************************************/

/************************************   Login configurations *****************************/
#define LOGGED_OUT (u8)0
#define LOGGED_IN (u8)1
/*****************************************************************************************/

/************************************   Logic values *************************************/
#define FALSE (u8)0
#define TRUE (u8)1

#define AUTO (u8)1
#define MANUAL (u8)0
/*****************************************************************************************/

#define SELECT_ROOM1 (u8)'1'
#define SELECT_ROOM2 (u8)'2'
#define SELECT_ROOM3 (u8)'3'
#define SELECT_ROOM4 (u8)'4'

#define SELECT_DOOR (u8)'1'
#define SELECT_FAN (u8)'2'
#define SELECT_ROOMS (u8)'3'

#define SELECT_RETURN (u8)'0'

#define SELECT_AUTO (u8)'1'
#define SELECT_MANUAL (u8)'2'

#define SELECT_OPEN (u8)'1'
#define SELECT_CLOSE (u8)'2'

#define SELECT_ON (u8)'1'
#define SELECT_OFF (u8)'2'

/****************************   number of ticks to run timeout ***************************/
#define SESSION_TIMEOUT (u16)3000
/*****************************************************************************************/

/****************************   Show menu codes  *****************************************/
#define MAIN_MENU (u8)1
#define ROOM_CHOOSER_MENU (u8)2

#define DOOR_MAIN_MENU (u8)3
#define DOOR_MANUAL_MENU (u8)4

#define AUTO_MANUAL_MENU (u8)20
#define MANUAL_MENU (u8)22

#define FAN_AUTO_MENU (u8)13

/*****************************************************************************************/
/****************************   UART codes  *****************************************/

#define OFF_STATUS (u8)00
#define ON_STATUS (u8)01
#define OPEN_STATUS (u8)02
#define CLOSED_STATUS (u8)03

#define ROOM1 (u8)0
#define ROOM2 (u8)1
#define ROOM3 (u8)2
#define ROOM4 (u8)3
#define FAN (u8)4
#define DOOR (u8)6

#define ROOM1_STATUS (u8)11
#define ROOM2_STATUS (u8)12
#define ROOM3_STATUS (u8)13
#define ROOM4_STATUS (u8)14
#define FAN_STATUS (u8)15
#define DOOR_STATUS (u8)16

#define ROOM1_TURN_ON (u8)21
#define ROOM2_TURN_ON (u8)22
#define ROOM3_TURN_ON (u8)23
#define ROOM4_TURN_ON (u8)24
#define FAN_TURN_ON (u8)25
#define DOOR_OPEN (u8)26

#define ROOM1_TURN_OFF (u8)31
#define ROOM2_TURN_OFF (u8)32
#define ROOM3_TURN_OFF (u8)33
#define ROOM4_TURN_OFF (u8)34
#define FAN_TURN_OFF (u8)35
#define DOOR_CLOSE (u8)36

#define ROOM1_SET_AUTO (u8)41
#define ROOM2_SET_AUTO (u8)42
#define ROOM3_SET_AUTO (u8)43
#define ROOM4_SET_AUTO (u8)44
#define FAN_SET_AUTO (u8)45
#define DOOR_SET_AUTO (u8)46

#define SET_TEMPERATURE (u8)55

#define DEFAULT_ACK 0xFF
#define DEMAND_RESPONSE 0xFF

/*****************************************************************************************/
/****************************   Slave codes  *****************************************/
#define ROOM1_PORT Port_C
#define ROOM2_PORT Port_C
#define ROOM3_PORT Port_C
#define ROOM4_PORT Port_C

#define DOOR_PORT Port_D
#define DOOR_PIN Pin5
#define ROOM1_PIN Pin4
#define ROOM2_PIN Pin5
#define ROOM3_PIN Pin6
#define ROOM4_PIN Pin7

#define FAN_PORT Port_C
#define FAN1_PIN Pin0
#define FAN2_PIN Pin1
/****************************   Auto Mode Codes  *****************************************/
#define SUNNY 512
#define LOW_SPEED 50
#define MEDIUM_SPEED 150
#define HIGH_SPEED 255
#define OFF_SPEED 0

#endif /* MAIN_CONFIG_H_ */
