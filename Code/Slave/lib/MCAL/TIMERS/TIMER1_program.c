/**
 ******************************************************************************
 * @File           : TIMER1_program.c
 * @Created on     : Aug 29, 2023
 ******************************************************************************
 */


#include "../../../include/BIT_MATH.h"
#include "../../../include/STD_TYPES.h"
#include"TIMER1_private.h"
#include "TIMER1_interface.h"

void TIMER1_VidInit()
{
	//Non Inverting Mode FPWM
	SET_BIT(TCCR1A,TCCR1A_COM1A1);
	CLR_BIT(TCCR1A,TCCR1A_COM1A0);

	//Seting Waveform Geniration Mode
	CLR_BIT(TCCR1A,TCCR1A_WGM10);
	SET_BIT(TCCR1A,TCCR1A_WGM11);//
	SET_BIT(TCCR1B,TCCR1B_WGM12);
	SET_BIT(TCCR1B,TCCR1B_WGM13);

	//Set Presscaler Devide By 8
	TCCR1B&=0xf8;
	TCCR1B|=2;

	TIMER1_Vid_SetICR_TopValue(19999);

}
void TIMER1_Vid_SetICR_TopValue(u16 value)
{
	ICR1 = value;
}

void TIMER1_Vid_SetOCR_CompMatch(u16 value)
{
	OCR1A = value;
}

void TIMER1_VidServoMotor_Angle(u16 value)
{

	TIMER1_Vid_SetOCR_CompMatch(( (50 * value) + 8991 )/9);
}
