#include "game_console.h"


void PWM_initialise(void)
{
	PWM0_SET_OUTPUT;
	PWM0_SET_FOC(LOW);
	PWM0_SET_MODE(FAST_PWM);
	PWM0_SET_COMPARE_OUT(COM_SET);
	PWM0_SET_CLOCK(CLK_IO);
	DUTY_CICRLE=200;

	//TCCR2 |= ~_BV(WGM21)|_BV(WGM20);
	//TCCR2 |= _BV(COM21)|_BV(COM20);
	//TCCR2 |= _BV(CS22)|_BV(CS21)|_BV(CS20);
	//TCNT2=0x00;
	//OCR2=0x66;
}
