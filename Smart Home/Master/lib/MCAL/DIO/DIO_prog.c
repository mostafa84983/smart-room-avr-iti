#include "../../../include/STD_TYPES.h"
#include "../../../include/BIT_MATH.h"
#include "DIO_private.h"
#include "DIO_interface.h"

// Setting pin direction
void DIO_VidSetPinDirection(et_Port port, et_Pin pin, et_Direction direction)
{
	if (direction == Input)
	{
		switch (port)
		{
		case Port_A:
			CLR_BIT(DDRA, pin);
			break;

		case Port_B:
			CLR_BIT(DDRB, pin);
			break;

		case Port_C:
			CLR_BIT(DDRC, pin);
			break;

		case Port_D:
			CLR_BIT(DDRD, pin);
			break;
		default:
			break;
		}
	}
	else if (direction == Output)
	{
		switch (port)
		{
		case Port_A:
			SET_BIT(DDRA, pin);
			break;

		case Port_B:
			SET_BIT(DDRB, pin);
			break;

		case Port_C:
			SET_BIT(DDRC, pin);
			break;

		case Port_D:
			SET_BIT(DDRD, pin);
			break;
		default:
			break;
		}
	}
}

// Setting pin value
void DIO_VidSetPinValue(et_Port port, et_Pin pin, et_Status value)
{
	if (value == PinLow)
	{
		switch (port)
		{
		case Port_A:
			CLR_BIT(PORTA, pin);
			break;

		case Port_B:
			CLR_BIT(PORTB, pin);
			break;

		case Port_C:
			CLR_BIT(PORTC, pin);
			break;

		case Port_D:
			CLR_BIT(PORTD, pin);
			break;
		default:
			break;
		}
	}
	else if (value == PinHigh)
	{
		switch (port)
		{
		case Port_A:
			SET_BIT(PORTA, pin);
			break;

		case Port_B:
			SET_BIT(PORTB, pin);
			break;

		case Port_C:
			SET_BIT(PORTC, pin);
			break;

		case Port_D:
			SET_BIT(PORTD, pin);
			break;
		default:
			break;
		}
	}
}

// getting pin value
et_Status DIO_VidGetPinValue(et_Port port, et_Pin pin)
{
	switch (port)
	{
	case Port_A:
		return GET_BIT(PINA, pin);
		break;

	case Port_B:
		return GET_BIT(PINB, pin);
		break;

	case Port_C:
		return GET_BIT(PINC, pin);
		break;

	case Port_D:
		return GET_BIT(PIND, pin);
		break;
	default:
		break;
	}
}
