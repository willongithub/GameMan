#include "game_console.h"


byte INTERRUPT_initialise(void)
{
    BUTTON_INTERRUPT_DIR(IN);
    //BUTTON_INTERRUPT_SET(HIGH);
	
	GICR = 1<<INT1;					// Enable A Button Interrupt
	MCUCR = 1<<ISC11 | 0<<ISC10;

	//GICR = 1<<INT0;					// Enable INT0
	//MCUCR = 1<<ISC01 | 0<<ISC00;    // Trigger INT0 on falling edge
	//GIFR = 0 <<	INTF0;
	//SREG = 1 << 7;
	sei();

	return(TRUE);
}

//Interrupt Service Routine

ISR(INT0_vect)
{
	_delay_ms(255); // Software debouncing control

	BAT_LOW_LED(ON);
	_delay_ms(155);
	BAT_LOW_LED(OFF);
	
}

ISR(INT1_vect)
{
	float volt;
	byte integer, decimal_1, decimal_2;	

	volt = BAT_sense();
	//volt = 1.469;		
	integer = (byte)volt;
	decimal_1 = (byte)((volt - integer)*10.0);
	decimal_2 = (byte)((volt - integer)*100.0 - decimal_1*10.0);

	if (integer >= 1)
		write_1(3, 44);
	else
		write_0(3, 44);
		
	switch (decimal_1)
	{
		case 0:write_zero(3, 52);break;
		case 1:write_one(3, 52);break;
		case 2:write_two(3, 52);break;
		case 3:write_three(3, 52);break;
		case 4:write_four(3, 52);break;
		case 5:write_five(3, 52);break;
		case 6:write_six(3, 52);break;
		case 7:write_seven(3, 52);break;
		case 8:write_eight(3, 52);break;
		case 9:write_nine(3, 52);break;
		default:write_zero(3, 52);
		break;
	}
	switch (decimal_2)
	{
		case 0:write_zero(3, 58);break;
		case 1:write_one(3, 58);break;
		case 2:write_two(3, 58);break;
		case 3:write_three(3, 58);break;
		case 4:write_four(3, 58);break;
		case 5:write_five(3, 58);break;
		case 6:write_six(3, 58);break;
		case 7:write_seven(3, 58);break;
		case 8:write_eight(3, 58);break;
		case 9:write_nine(3, 58);break;
		default:write_zero(3, 58);
		break;
	}
	write_v(3, 66);
	LCD_clear();
}


