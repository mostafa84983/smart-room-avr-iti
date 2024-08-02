#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

typedef enum
{
	Port_A,
	Port_B,
	Port_C,
	Port_D
} et_Port;

typedef enum
{
	Pin0,
	Pin1,
	Pin2,
	Pin3,
	Pin4,
	Pin5,
	Pin6,
	Pin7
} et_Pin;

typedef enum
{
	Input,
	Output
} et_Direction;

typedef enum
{
	PinLow,
	PinHigh
} et_Status;

// Setting pin direction
void DIO_VidSetPinDirection(et_Port port, et_Pin pin, et_Direction direction);

// Setting pin value
void DIO_VidSetPinValue(et_Port port, et_Pin pin, et_Status value);

// getting pin value
et_Status DIO_VidGetPinValue(et_Port port, et_Pin pin);

#endif
