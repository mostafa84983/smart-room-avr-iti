/**
 ******************************************************************************
 * @File           : GIE_program.c
 * @Created on     : Aug 23, 2023
 * @Author         : Mahmoud Yasser
 ******************************************************************************
 */
#include "../../../include/STD_TYPES.h"
#include "../../../include/BIT_MATH.h"

#include "GIE_interface.h"

void GIE_VidEnable()
{
	SET_BIT(SREG,SREF_I);
}
void GIE_VidDisable()
{
	CLR_BIT(SREG,SREF_I);
}

