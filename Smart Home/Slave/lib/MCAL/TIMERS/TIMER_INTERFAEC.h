#ifndef TIMER_INTERFACE_H
#define TIMER_INTERFACE_H
typedef enum{
	TIMER0_NORMAL_MODE=0,
	TIMER0_PHASECORRECT_MODE,
	TIMER0_CTC_MODE,
	TIMER0_FASTPWM_MODE
}et_TIMER0MODE;
typedef enum{
	 No_clock_source=0,
	 No_prescaling,
	 clk_8_prescaler,
	 clk_64_prescaler,
	 clk_256_prescaler,
	 clk_1024_prescaler,
	 External_clock_fallingedge,
	 External_clock_risingedge
}et_TIMER0PRESSCAELER;

void TIMER0_Vid_Init(et_TIMER0MODE mode );
void set_dutycycle(u8 duty);
void TIMER0_Vid_stop(void);
void PWM_Timer0_Init(u8 set_duty_cycle);
void TIMER0_Interrupt_Enable();
void TIMER0_Interrupt_Disable();
u8 TIMER0_Get_U8Dutycycle(void);

#endif
