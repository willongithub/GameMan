#include "game_console.h"


byte ADC_initialise(void)
{

	// AREF = AVcc
    ADMUX = (1<<REFS0);
 
    // ADC Enable and prescaler of 128
    // 16000000/128 = 125000
    ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);

  return(TRUE);
}


unsigned int ADC_read(unsigned char ch)
{
ch= ch & 0b00000111; // channel must be b/w 0 to 7
ADMUX |= ch; // selecting channel
 
ADCSRA|=(1<<ADSC); // start conversion
while(!(ADCSRA & (1<<ADIF))); // waiting for ADIF, conversion complete
ADCSRA|=(1<<ADIF); // clearing of ADIF, it is done by writing 1 to it
 
return (ADC);
}


float BAT_sense(void)
{
  unsigned int BAT_read;
  float BAT_volt;
  //BAT_read = ADCH;
  BAT_read = ADC_read(3);
  BAT_volt = (BAT_read * ADC_VREF_INTERNAL) / ADC_MAX ; 
  if(BAT_volt <= 1.0)
    //ADC_INT_FLAG(HIGH);
	BAT_LOW_LED(ON);
  //else
    //BAT_LOW_LED(OFF)

	return(BAT_volt);
}

