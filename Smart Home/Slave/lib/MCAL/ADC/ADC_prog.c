#include "../../../include/STD_TYPES.h"
#include "../../../include/BIT_MATH.h"
#include "ADC_private.h"
#include "ADC_config.h"
#include "ADC_interface.h"

void ADC_VidInit(u8 Copy_u8RefVoltage, u8 Copy_u8PreScalar)
{
   // SET REFERENCE VOLTAGE
   ADMUX &= 0b00011111;
   ADMUX |= Copy_u8RefVoltage;
   // SET CLOCK DIVISION FACTOR
   ADCSRA &= 0b11111000;
   ADCSRA |= Copy_u8PreScalar;
   // CLEAR LEFT ADJUSTMENT
   CLR_BIT(ADMUX, ADMUX_ADLAR);
   // ENABLE ADC
   SET_BIT(ADCSRA, ADCSRA_ADEN);
}

u16 ADC_u16ReadChannel(u8 Copy_u8Channel)
{
   // SET ADC CHANNEL
   ADMUX &= 0b11110000;
   ADMUX |= Copy_u8Channel;
   // START ADC CONVERSION
   SET_BIT(ADCSRA, ADCSRA_ADSC);
   // POLL UNTIL CONVERSION IS COMPLETE
   while (GET_BIT(ADCSRA, ADCSRA_ADSC))
      ;

   return ADC;
}

void ADC_VidEnableInterrupt(u8 Copy_u8Channel)
{
   // SET ADC CHANNEL
   ADMUX &= 0xF0;
   ADMUX |= Copy_u8Channel;

   // ENABLE ADC INTERRUPT
   SET_BIT(ADCSRA, ADCSRA_ADIE);
   
   // START ADC CONVERSION
   SET_BIT(ADCSRA, ADCSRA_ADSC);
   
}
