#include "../../../include/BIT_MATH.h"
#include "../../../include/STD_TYPES.h"
#include "../DIO/DIO_interface.h"
#include "TIMER_PRIVATE.h"
#include "TIMER_INTERFAEC.h"


void TIMER0_Vid_Init(et_TIMER0MODE mode )
{
	/************** timer mode **************/
	switch(mode)
	{
	case TIMER0_NORMAL_MODE:
		CLR_BIT(TCCR0,TCCR0_WGM00);
		CLR_BIT(TCCR0,TCCR0_WGM01);
		break;

	case TIMER0_CTC_MODE:
		CLR_BIT(TCCR0,TCCR0_WGM00);
		SET_BIT(TCCR0,TCCR0_WGM01);
		break;

	case TIMER0_FASTPWM_MODE:
		SET_BIT(TCCR0,TCCR0_WGM00);
		SET_BIT(TCCR0,TCCR0_WGM01);
		break;

	case TIMER0_PHASECORRECT_MODE:
		SET_BIT(TCCR0,TCCR0_WGM00);
		CLR_BIT(TCCR0,TCCR0_WGM01);
		break;

	}
}
void PWM_Timer0_Init(u8 set_duty_cycle)
{

	TCNT0 = 0; //Set Timer Initial value
	OCR0 = set_duty_cycle;
	DIO_VidSetPinDirection(Port_B,Pin3,Output); //set PB3/OC0 as output pin --> pin where the PWM signal is generated from MC.

	/* Configure timer control register
	 * 1. Fast PWM mode FOC0=0
	 * 2. Fast PWM Mode WGM01=1 & WGM00=1
	 * 3. Clear OC0 when match occurs (non inverted mode) COM00=0 & COM01=1
	 * 4. clock = F_CPU/8 CS00=0 CS01=1 CS02=0
	 */
	TCCR0 =  (1<<TCCR0_WGM00)|(1<<TCCR0_WGM01)| (1<<TCCR0_COM01)|(1<<TCCR0_CS01)|(1<<TCCR0_CS00);

}

void set_dutycycle(u8 duty)
{
	OCR0 = duty ;//Set the OCR0 depending on the duty percentage
}
u8 TIMER0_Get_U8Dutycycle(void){
	return OCR0;
}
void TIMER0_Vid_stop(void)
{
	//disable the clock to stop the counter
	CLR_BIT(TCCR0, TCCR0_CS00);
	CLR_BIT(TCCR0, TCCR0_CS01);
	CLR_BIT(TCCR0, TCCR0_CS02);
}




void TIMER0_Interrupt_Enable()
{
	SET_BIT(TIMSK,TIMSK_TOIE0);
}
void TIMER0_Interrupt_Disable()
{
	CLR_BIT(TIMSK,TIMSK_TOIE0);
}

