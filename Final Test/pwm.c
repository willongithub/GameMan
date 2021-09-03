#include "game_console.h"


void PWM_initialise(void)
{
	PWM0_SET_OUTPUT;
	PWM0_SET_FOC(LOW);
	PWM0_SET_MODE(FAST_PWM);
	PWM0_SET_COMPARE_OUT(COM_SET);
	PWM0_SET_CLOCK(CLK_IO);
	DUTY_CICRLE = 128;

	//TCCR0 |= ~_BV(WGM01)|_BV(WGM00);
	//TCCR0 |= _BV(COM01)|_BV(COM00);
	//TCCR0 |= _BV(CS02)|_BV(CS01)|_BV(CS00);
	//TCNT0=0x00;
	//OCR0=0x06;
}
