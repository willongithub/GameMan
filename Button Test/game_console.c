/*************************************************************************
Title:    game_console Template
Initial Author:   David Jahshan
Extended by : (PUT YOUR NAME HERE) (PUT YOUR STUDENT NUMBER HERE)
Software: AVR-GCC 
Hardware: ATMEGA16 @ 8Mhz 

DESCRIPTION:
	Main and functions for Game Console basic sample code

*************************************************************************/


#include "game_console.h" 


int main(void)
{
	BAT_LOW_LED(OFF); //Make sure it is off before changing direction
	BAT_LOW_LED_DIR(OUT); //Set BATTERY LED I/Os as outputs.
	
	UP_BUTTON_DIR(IN); //Set BUTTON I/Os as input.
	DOWN_BUTTON_DIR(IN);
	RIGHT_BUTTON_DIR(IN);
	LEFT_BUTTON_DIR(IN);
	A_BUTTON_DIR(IN);
	B_BUTTON_DIR(IN);
	C_BUTTON_DIR(IN);

	UP_BUTTON_INI(PULLUP);
	DOWN_BUTTON_INI(PULLUP);
	RIGHT_BUTTON_INI(PULLUP);
	LEFT_BUTTON_INI(PULLUP);
	A_BUTTON_INI(PULLUP);
	B_BUTTON_INI(PULLUP);
	C_BUTTON_INI(PULLUP);

	while (TRUE)//Master loop always true so always loop
	{
		
		//Turn on the LED if BUTTON is pressed
		if (~UP_BUTTON)
		{
			BAT_LOW_LED(ON);	
		} 	
		else
		{
			BAT_LOW_LED(OFF);
		}
		

		if (~DOWN_BUTTON)
		{
			BAT_LOW_LED(ON);	
		} 	
		else
		{
			BAT_LOW_LED(OFF);
		}

		if (~RIGHT_BUTTON)
		{
			BAT_LOW_LED(ON);	
		} 	
		else
		{
			BAT_LOW_LED(OFF);
		}

		if (~LEFT_BUTTON)
		{
			BAT_LOW_LED(ON);	
		} 	
		else
		{
			BAT_LOW_LED(OFF);
		}

		if (~A_BUTTON)
		{
			BAT_LOW_LED(ON);	
		} 	
		else
		{
			BAT_LOW_LED(OFF);
		}

		if (~B_BUTTON)
		{
			BAT_LOW_LED(ON);	
		} 	
		else
		{
			BAT_LOW_LED(OFF);
		}

		if (~C_BUTTON)
		{
			BAT_LOW_LED(ON);	
		} 	
		else
		{
			BAT_LOW_LED(OFF);
		}



	}

}
