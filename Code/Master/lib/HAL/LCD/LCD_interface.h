/**
 ******************************************************************************
 * @File           : LCD_interface.h
 * @Created on     : Aug 23, 2023
 * @Author         : Mahmoud Yasser
 ******************************************************************************
 */
#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

void LCD_VidInit(void);
void LCD_VidSendCommand(u8 Copy_u8Command);
void LCD_VidSendChar(u8 Copy_u8Data);
void LCD_VidSendString(char *Copy_u8Data);
void LCD_VidIntegerToString(u16 data);
void LCD_VidMoveCursor(u8 row, u8 column);
void LCD_VidSendString_XY(char *Copy_u8Data,u8 row, u8 column);
void LCD_VidIntegerToString_XY(u16 data,u8 row, u8 column);
void LCD_VidSendFloat(f32 data);
void LCD_VidClearScreen();
void LCD_VidDeleteChar(void);
void LCD_VidSendChar_XY(u8 Copy_u8Data,u8 row, u8 column);
#endif
