/**
 ******************************************************************************
 * @File           : TIMER1_interface.h
 * @Created on     : Aug 29, 2023
 ******************************************************************************
 */

#ifndef TIMER1_INTERFACE_H_
#define TIMER1_INTERFACE_H_

void TIMER1_VidInit();

void TIMER1_Vid_SetICR_TopValue(u16 value);

void TIMER1_Vid_SetOCR_CompMatch(u16 value);

void TIMER1_VidServoMotor_Angle(u16 value);

#endif /* TIMER1_INTERFACE_H_ */
