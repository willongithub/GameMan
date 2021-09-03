#include "game_console.h"


byte ADC_initialise(void)
{
  ADC_SET_REF(ADC_REF_IN256);
  ADC_SET_INPUT(ADC3);//PA3
  ADC_ENABLE(ON);
  ADC_LEFT_ADJUST(ON);
  ADC_START_CONVERSATION(ON);
  //ADC_AUTO_TRIGGER(ON);
  ADC_INT_ENABLE(ON);
  ADC_CLK(ADC_CLK2);
  ADC_AUTO_SOURCE(FREE_RUNNING);
  ADC_INT_FLAG(LOW);

  return(TRUE);
}


float BAT_sense(void)
{
  unsigned int BAT_read;
  float BAT_volt;
  BAT_read = ADCH;
  BAT_volt = (BAT_read * ADC_VREF_INTERNAL) / ADC_MAX ; 
  if(BAT_volt <= 1.0)
    //ADC_INT_FLAG(HIGH);
	BAT_LOW_LED(ON);
  //else
    //BAT_LOW_LED(OFF)

	return(BAT_volt);
}
