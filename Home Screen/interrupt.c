#include "game_console.h"

/*
byte INTERRUPT_initialise(void)
{
    BUTTON_INTERRUPT_DIR(IN);
    BUTTON_INTERRUPT_SET(HIGH);
	GICR = 1<<INT0;					// Enable INT0
	MCUCR = 1<<ISC01 | 1<<ISC00;	// Trigger INT0 on rising edge
	sei();

	return(TRUE);
}

//Interrupt Service Routine for INT0

ISR(INT0_vect)
{
	byte i;
 
	_delay_ms(50); // Software debouncing control
 
	
	for(i = 0; i < 5; i++)
	{
		BAT_LOW_LED(ON);
		_delay_ms(155);
		BAT_LOW_LED(OFF);
	}
}

*/
