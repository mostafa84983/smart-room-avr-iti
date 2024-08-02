/**
 ******************************************************************************
 * @File           : LCD_program.c
 * @Created on     : Aug 23, 2023
 * @Author         : Mahmoud Yasser
 ******************************************************************************
 */
#include "../../../include/STD_TYPES.h"
#include "../../../include/BIT_MATH.h"
#include "../../MCAL/DIO/DIO_interface.h"
#include "LCD_config.h"
#include "LCD_interface.h"
#include <util/delay.h>
#include <stdlib.h>

void LCD_VidInit(void)
{
	//Configure Enable and Rs as Output
	DIO_VidSetPinDirection(LCD_PORT,LCD_RS,Output);
	DIO_VidSetPinDirection(LCD_PORT,LCD_E,Output);
	_delay_ms(20);

	//Configure The Data Pins
	DIO_VidSetPinDirection(LCD_PORT,Pin3,Output);
	DIO_VidSetPinDirection(LCD_PORT,Pin4,Output);
	DIO_VidSetPinDirection(LCD_PORT,Pin5,Output);
	DIO_VidSetPinDirection(LCD_PORT,Pin6,Output);
	_delay_ms(20);

	//Send Commands 0x33 0x32 0x28 To init Lcd
	LCD_VidSendCommand(0x33);
	LCD_VidSendCommand(0x32);
	LCD_VidSendCommand(0x28);
	LCD_VidSendCommand(0x0C);
	LCD_VidSendCommand(0x01);
}

void LCD_VidSendCommand(u8 Copy_u8Command)
{

	//Clear RS
	DIO_VidSetPinValue(LCD_PORT,LCD_RS,PinLow);
	_delay_us(1);

	//Set Enable
	DIO_VidSetPinValue(LCD_PORT,LCD_E,PinHigh);
	_delay_us(1);

	//Send MSB Command
	DIO_VidSetPinValue(LCD_PORT,Pin3,GET_BIT(Copy_u8Command,Pin4));
	DIO_VidSetPinValue(LCD_PORT,Pin4,GET_BIT(Copy_u8Command,Pin5));
	DIO_VidSetPinValue(LCD_PORT,Pin5,GET_BIT(Copy_u8Command,Pin6));
	DIO_VidSetPinValue(LCD_PORT,Pin6,GET_BIT(Copy_u8Command,Pin7));
	_delay_ms(1);

	//Clear Enable
	DIO_VidSetPinValue(LCD_PORT,LCD_E,PinLow);
	_delay_us(1);

	//Set Enable
	DIO_VidSetPinValue(LCD_PORT,LCD_E,PinHigh);
	_delay_us(1);

	//Send LSB Command
	DIO_VidSetPinValue(LCD_PORT,Pin3,GET_BIT(Copy_u8Command,Pin0));
	DIO_VidSetPinValue(LCD_PORT,Pin4,GET_BIT(Copy_u8Command,Pin1));
	DIO_VidSetPinValue(LCD_PORT,Pin5,GET_BIT(Copy_u8Command,Pin2));
	DIO_VidSetPinValue(LCD_PORT,Pin6,GET_BIT(Copy_u8Command,Pin3));
	_delay_ms(1);

	//Clear Enable
	DIO_VidSetPinValue(LCD_PORT,LCD_E,PinLow);
	_delay_us(1);
}

void LCD_VidSendChar(u8 Copy_u8Data)
{

	//Set RS
	DIO_VidSetPinValue(LCD_PORT,LCD_RS,PinHigh);
	_delay_us(1);

	//Set Enable
	DIO_VidSetPinValue(LCD_PORT,LCD_E,PinHigh);
	_delay_us(1);

	//Send MSB Command
	DIO_VidSetPinValue(LCD_PORT,Pin3,GET_BIT(Copy_u8Data,Pin4));
	DIO_VidSetPinValue(LCD_PORT,Pin4,GET_BIT(Copy_u8Data,Pin5));
	DIO_VidSetPinValue(LCD_PORT,Pin5,GET_BIT(Copy_u8Data,Pin6));
	DIO_VidSetPinValue(LCD_PORT,Pin6,GET_BIT(Copy_u8Data,Pin7));
	_delay_ms(1);

	//Clear Enable
	DIO_VidSetPinValue(LCD_PORT,LCD_E,PinLow);
	_delay_us(1);

	//Set Enable
	DIO_VidSetPinValue(LCD_PORT,LCD_E,PinHigh);
	_delay_us(1);

	//Send LSB Command
	DIO_VidSetPinValue(LCD_PORT,Pin3,GET_BIT(Copy_u8Data,Pin0));
	DIO_VidSetPinValue(LCD_PORT,Pin4,GET_BIT(Copy_u8Data,Pin1));
	DIO_VidSetPinValue(LCD_PORT,Pin5,GET_BIT(Copy_u8Data,Pin2));
	DIO_VidSetPinValue(LCD_PORT,Pin6,GET_BIT(Copy_u8Data,Pin3));
	_delay_ms(1);

	//Clear Enable
	DIO_VidSetPinValue(LCD_PORT,LCD_E,PinLow);
	_delay_us(1);


}

void LCD_VidSendString(char *Copy_u8Data)
{
	u8 i;
	for(i=0;Copy_u8Data[i]!='\0';i++)
		LCD_VidSendChar(Copy_u8Data[i]);

}

void LCD_VidIntegerToString(u16 data)
{
   char arr[16];

   itoa(data,arr,10);

   LCD_VidSendString(arr);
}

void LCD_VidMoveCursor(u8 row, u8 column)
{

	u8 position;
	switch(row)
	{
	case 0 :
		position=0x00+column; //first row position is 0x00 + column
		break;
	case 1 :
		position=0x40+column; //second row position is 0x040 + column
		break;

	}
	LCD_VidSendCommand(position|0x80);
}
void LCD_VidSendString_XY(char *Copy_u8Data,u8 row, u8 column)
{
	LCD_VidMoveCursor(row,column);
	LCD_VidSendString(Copy_u8Data);
}
void LCD_VidIntegerToString_XY(u16 data,u8 row, u8 column)
{
	LCD_VidMoveCursor(row,column);
	LCD_VidIntegerToString(data);
}
void LCD_VidSendChar_XY(u8 Copy_u8Data,u8 row, u8 column)
{
	LCD_VidMoveCursor(row,column);
	LCD_VidSendChar(Copy_u8Data);
}

void LCD_VidSendFloat(f32 data)
{
	s16 _dot,dot_;
	_dot = data;
	dot_ = (data- _dot)*10;
	LCD_VidIntegerToString(_dot);
	if(dot_>0)
	{
		LCD_VidSendChar('.');
		LCD_VidIntegerToString(dot_);
	}
	else
	{

	}

}
void LCD_VidClearScreen()
{
	LCD_VidSendCommand(0x01);
}
void LCD_VidDeleteChar(void)
{
	LCD_VidSendCommand(LCD_DECREMENT_CURSOR);
	LCD_VidSendChar(SPACEBAR_KEY);
	LCD_VidSendCommand(LCD_INCREMENT_CURSOR);
	LCD_VidSendChar(SPACEBAR_KEY);
	LCD_VidSendCommand(LCD_DECREMENT_CURSOR);
	LCD_VidSendChar(SPACEBAR_KEY);
	LCD_VidSendCommand(LCD_INCREMENT_CURSOR);
}
