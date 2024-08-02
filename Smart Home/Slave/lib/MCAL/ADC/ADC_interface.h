#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

// Define ADC channel macros
#define ADC_CHANNEL_0   0x00
#define ADC_CHANNEL_1   0x01
#define ADC_CHANNEL_2   0x02
#define ADC_CHANNEL_3   0x03
#define ADC_CHANNEL_4   0x04
#define ADC_CHANNEL_5   0x05
#define ADC_CHANNEL_6   0x06
#define ADC_CHANNEL_7   0x07

// Define ADC reference voltage macros
#define ADC_REF_EXTERNAL    0x00
#define ADC_REF_AVCC        0x40
#define ADC_REF_INTERNAL    0xC0

// ADC PRESCALAR VALUES
#define ADC_CLOCK_DIV_2     0x01
#define ADC_CLOCK_DIV_4     0x02
#define ADC_CLOCK_DIV_8     0x03
#define ADC_CLOCK_DIV_16    0x04
#define ADC_CLOCK_DIV_32    0x05
#define ADC_CLOCK_DIV_64    0x06
#define ADC_CLOCK_DIV_128   0x07

void ADC_VidInit(u8 Copy_u8RefVoltage, u8 Copy_u8PreScalar);
void ADC_VidEnableInterrupt(u8 Copy_u8Channel);
u16 ADC_u16ReadChannel(u8 Copy_u8Channel);

#endif
