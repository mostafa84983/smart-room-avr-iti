#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_


#define ADMUX    *((volatile u8*)0x27)
#define ADCSRA   *((volatile u8*)0x26)
#define ADC_H    *((volatile u8*)0x25)
#define ADC_L    *((volatile u8*)0x24)
#define ADC      *((volatile u16*)0x24)

/*  ISR VECTOR */
#define ADC_VECT _VECTOR(16)

#endif
