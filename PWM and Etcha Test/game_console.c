/*************************************************************************
Title:    GameMan Console
Initial Author:   David Jahshan
Extended by : (SIQI WU) (750892)
Software: AVR-GCC 
Hardware: ATMEGA16 @ 8Mhz 
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

	LCD_CS_DIR(OUT);
	LCD_CD_DIR(OUT);
	LCD_RST_DIR(OUT);
	//RAM_CS_DIR(OUT);
	//RAM_WP_DIR(OUT);
	//RAM_HOLD_DIR(OUT);
	SCK_DIR(OUT);
    MOSI_DIR(OUT);
    MISO_DIR(IN);

	BACKLIGHT_DIR(OUT);

	MCU_SS_DIR(OUT);


	//Initialize
	LCD_CD_INI(LOW);
	LCD_CS_INI(HIGH);
	LCD_RST_INI(HIGH);
	
	MCU_SS_INI(HIGH);	

	UP_BUTTON_INI(PULLUP);
	DOWN_BUTTON_INI(PULLUP);
	RIGHT_BUTTON_INI(PULLUP);
	LEFT_BUTTON_INI(PULLUP);
	A_BUTTON_INI(PULLUP);
	B_BUTTON_INI(PULLUP);
	C_BUTTON_INI(PULLUP);

	byte frame_buffer[MAX_COLUMNS][MAX_PAGES];
	
	SPI_initialise();
	LCD_initialise();
	PWM_initialise();

	byte row = 50;
	byte column = 30;
	byte page, pixel;
	

	select_page(4);
	select_column(20);
	LCD_data_tx(0x01);

	while (infinite_loop)//Master loop always true so always loop
	{
		
		//if(UP_BUTTON) row++;
		//if(DOWN_BUTTON) row --;
		//if(LEFT_BUTTON) column--;
		//if(RIGHT_BUTTON) column++;
		page = row/8;
		pixel = row%8;
		//select_page(3);
		//select_column(50);
		//pixel = (_BV(pixel) | (frame_buffer[column][page]));
		frame_buffer[column][page] = pixel;
		//LCD_data_tx(0xFF);
		//BAT_LOW_LED(ON);
		//_delay_ms(255);
		//BAT_LOW_LED(OFF);
		//_delay_ms(255);

		//Turn on the LED if BUTTON is pressed
		
		if (~UP_BUTTON)
		{
			BAT_LOW_LED(ON);
			_delay_ms(255);	
		} 	
		else
		{
			BAT_LOW_LED(OFF);
		}		
		if (~DOWN_BUTTON)
		{
			BAT_LOW_LED(ON);
			_delay_ms(255);	
		} 	
		else
		{
			BAT_LOW_LED(OFF);
		}

		if (~RIGHT_BUTTON)
		{
			BAT_LOW_LED(ON);
			_delay_ms(255);	
		} 	
		else
		{
			BAT_LOW_LED(OFF);
		}

		if (~LEFT_BUTTON)
		{
			BAT_LOW_LED(ON);
			_delay_ms(255);	
		} 	
		else
		{
			BAT_LOW_LED(OFF);
		}

		if (~A_BUTTON)
		{
			BAT_LOW_LED(ON);
			_delay_ms(255);	
		} 	
		else
		{
			BAT_LOW_LED(OFF);
		}

		if (~B_BUTTON)
		{
			BAT_LOW_LED(ON);
			_delay_ms(255);	
		} 	
		else
		{
			BAT_LOW_LED(OFF);
		}

		if (~C_BUTTON)
		{
			BAT_LOW_LED(ON);
			_delay_ms(255);	
		} 	
		else
		{
			BAT_LOW_LED(OFF);
		}
		
		

	}

}



