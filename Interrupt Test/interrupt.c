#include "game_console.h"


void INTERRUPT_initialise(void)
{
    BUTTON_INTERRUPT_DIR(IN)；
    BUTTON_INTERRUPT_INI(HIGH)
	GICR = 1<<INT0;					// Enable INT0
	MCUCR = 1<<ISC01 | 1<<ISC00;	// Trigger INT0 on rising edge
	sei();
}

//Interrupt Service Routine for INT0
ISR(INT0_vect)
{
	unsigned char i, temp;
 
	_delay_ms(500); // Software debouncing control
 
	temp = DataPort;	// Save current value on DataPort
 
	/* This for loop blink LEDs on Dataport 5 times*/
	for(i = 0; i<5; i++)
	{
		DataPort = 0x00;
		_delay_ms(500);	// Wait 5 seconds
		DataPort = 0xFF;
		_delay_ms(500);	// Wait 5 seconds
	}
 
	DataPort = temp;	//Restore old value to DataPort	
}
