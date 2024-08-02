#include "../include/STD_TYPES.h"
#include "../include/BIT_MATH.h"
#include "../lib/MCAL/DIO/DIO_interface.h"
#include "../lib/MCAL/ADC/ADC_interface.h"
#include "../lib/MCAL/GIE/GIE_interface.h"
#include "../lib/MCAL/TIMERS/TIMER_INTERFAEC.h"
#include "../lib/MCAL/TIMERS/TIMER1_interface.h"
#include "../lib/MCAL/UART/UART_interface.h"
#include "main_config.h"
#include <util/delay.h>

void vLDR(void);
void vFan(void);

u8 request = DEFAULT_ACK;
u8 response = DEFAULT_ACK;
u8 fanmode = AUTO;
u8 doorstatus = CLOSED_STATUS;
u8 Global_u8Rooms[4] = {AUTO, MANUAL, AUTO, MANUAL};
volatile u8 Global_u8LDRFlag = FALSE;
u8 fantemp = 25;
volatile u16 light = 0;
volatile u16 temp_sensor_reading = 0;

int main()
{

	GIE_VidEnable();
	TIMER1_VidInit();
	TIMER1_VidServoMotor_Angle(180);
	PWM_Timer0_Init(0);
	ADC_VidInit(ADC_REF_AVCC, clk_64_prescaler);
	UART_VidInit();

	DIO_VidSetPinDirection(ROOM1_PORT, ROOM1_PIN, Output);
	DIO_VidSetPinDirection(ROOM2_PORT, ROOM2_PIN, Output);
	DIO_VidSetPinDirection(ROOM3_PORT, ROOM3_PIN, Output);
	DIO_VidSetPinDirection(ROOM4_PORT, ROOM4_PIN, Output);

	DIO_VidSetPinValue(ROOM1_PORT, ROOM1_PIN, PinLow);
	DIO_VidSetPinValue(ROOM2_PORT, ROOM2_PIN, PinLow);
	DIO_VidSetPinValue(ROOM3_PORT, ROOM3_PIN, PinLow);
	DIO_VidSetPinValue(ROOM4_PORT, ROOM4_PIN, PinLow);

	DIO_VidSetPinDirection(FAN_PORT, FAN1_PIN, Output);
	DIO_VidSetPinDirection(FAN_PORT, FAN2_PIN, Output);

	DIO_VidSetPinValue(FAN_PORT, FAN1_PIN, PinLow);
	DIO_VidSetPinValue(FAN_PORT, FAN2_PIN, PinHigh);

	DIO_VidSetPinDirection(Port_D, DOOR_PIN, Output);

	while (1)
	{
		vFan();
		vLDR();
	}
}
void vLDR(void)
{
	Global_u8LDRFlag = FALSE;
	for (u8 Local_u8Counter = 0; Local_u8Counter < 4; Local_u8Counter++)
	{
		if (Global_u8Rooms[Local_u8Counter] == MANUAL)
			continue;

		if (Global_u8LDRFlag == FALSE)
		{
			light = ADC_u16ReadChannel(ADC_CHANNEL_0);
			Global_u8LDRFlag = TRUE;
		}
		if (light < SUNNY)
		{
			DIO_VidSetPinValue(ROOM1_PORT, ROOM1_PIN + Local_u8Counter, PinHigh);
		}
		else if (light >= SUNNY)
		{
			DIO_VidSetPinValue(ROOM1_PORT, ROOM1_PIN + Local_u8Counter, PinLow);
		}
	}
}

void vFan(void)
{
	if (MANUAL == fanmode)
		return;

	temp_sensor_reading = round(ADC_u16ReadChannel(ADC_CHANNEL_1) * 0.488);

	if (temp_sensor_reading >= (fantemp - 5) && temp_sensor_reading < fantemp)
	{
		set_dutycycle(LOW_SPEED);
	}
	else if (temp_sensor_reading >= fantemp && temp_sensor_reading < (fantemp + 5))
	{
		set_dutycycle(MEDIUM_SPEED);
	}
	else if (temp_sensor_reading >= (fantemp + 5))
	{
		set_dutycycle(HIGH_SPEED);
	}
	else
	{
		set_dutycycle(OFF_SPEED);
	}
}

ISR(UART_RXC_VECT)
{
	switch (UDR)
	{
	case ROOM1_STATUS:
		response = DIO_VidGetPinValue(ROOM1_PORT, ROOM1_PIN);
		UART_VidSendByte(response);
		break;
	case ROOM2_STATUS:
		response = DIO_VidGetPinValue(ROOM2_PORT, ROOM2_PIN);
		UART_VidSendByte(response);
		break;
	case ROOM3_STATUS:
		response = DIO_VidGetPinValue(ROOM3_PORT, ROOM3_PIN);
		UART_VidSendByte(response);
		break;

	case ROOM4_STATUS:
		response = DIO_VidGetPinValue(ROOM4_PORT, ROOM4_PIN);
		UART_VidSendByte(response);
		break;
	case ROOM1_SET_AUTO:
		Global_u8Rooms[0] = AUTO;
		break;
	case ROOM2_SET_AUTO:
		Global_u8Rooms[1] = AUTO;
		break;
	case ROOM3_SET_AUTO:
		Global_u8Rooms[2] = AUTO;
		break;
	case ROOM4_SET_AUTO:
		Global_u8Rooms[3] = AUTO;
		break;

	case ROOM1_TURN_ON:
		DIO_VidSetPinValue(ROOM1_PORT, ROOM1_PIN, PinHigh);
		Global_u8Rooms[0] = MANUAL;
		break;
	case ROOM2_TURN_ON:
		DIO_VidSetPinValue(ROOM2_PORT, ROOM2_PIN, PinHigh);
		Global_u8Rooms[1] = MANUAL;
		break;
	case ROOM3_TURN_ON:
		DIO_VidSetPinValue(ROOM3_PORT, ROOM3_PIN, PinHigh);
		Global_u8Rooms[2] = MANUAL;
		break;
	case ROOM4_TURN_ON:
		DIO_VidSetPinValue(ROOM4_PORT, ROOM4_PIN, PinHigh);
		Global_u8Rooms[3] = MANUAL;
		break;
	case ROOM1_TURN_OFF:
		DIO_VidSetPinValue(ROOM1_PORT, ROOM1_PIN, PinLow);
		Global_u8Rooms[0] = MANUAL;
		break;
	case ROOM2_TURN_OFF:
		DIO_VidSetPinValue(ROOM2_PORT, ROOM2_PIN, PinLow);
		Global_u8Rooms[1] = MANUAL;
		break;
	case ROOM3_TURN_OFF:
		DIO_VidSetPinValue(ROOM3_PORT, ROOM3_PIN, PinLow);
		Global_u8Rooms[2] = MANUAL;
		break;
	case ROOM4_TURN_OFF:
		DIO_VidSetPinValue(ROOM4_PORT, ROOM4_PIN, PinLow);
		Global_u8Rooms[3] = MANUAL;
		break;

	case FAN_SET_AUTO:
		fanmode = AUTO;
		break;
	case FAN_TURN_ON:
		set_dutycycle(HIGH_SPEED);
		fanmode = MANUAL;
		break;

	case FAN_TURN_OFF:
		set_dutycycle(OFF_SPEED);
		fanmode = MANUAL;
		break;
	case FAN_STATUS:
		if (OFF_SPEED == TIMER0_Get_U8Dutycycle())
		{
			response = OFF_STATUS;
		}
		else
		{
			response = ON_STATUS;
		}
		UART_VidSendByte(response);
		break;
	case SET_TEMPERATURE:
		CLR_BIT(UCSRB, UCSRB_RXCIE); //STOP ISR
		fantemp = UART_u8ReceiveData();
		fanmode = AUTO;
		SET_BIT(UCSRB, UCSRB_RXCIE); //EN ISR
		break;
	case DOOR_OPEN:
		TIMER1_VidServoMotor_Angle(90);
		doorstatus = OPEN_STATUS;
		break;
	case DOOR_CLOSE:
		TIMER1_VidServoMotor_Angle(180);
		doorstatus = CLOSED_STATUS;
		break;
	case DOOR_STATUS:
		response = doorstatus;
		UART_VidSendByte(response);
		break;
	case DOOR_SET_AUTO:
		TIMER1_VidServoMotor_Angle(90);
		doorstatus = OPEN_STATUS;
		_delay_ms(DOOR_TIME);
		TIMER1_VidServoMotor_Angle(180);
		doorstatus = CLOSED_STATUS;
		break;

	default:
		break;
	}
}