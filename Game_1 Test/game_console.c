/*************************************************************************
Title:    GameMan Console
Initial Author:   David Jahshan
Extended by : () ()
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

	BAT_SEN_DIR(IN);

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

	//BACKLIGHT_SET_LIGHTUP;

	byte frame_buffer[MAX_COLUMNS][MAX_PAGES];
	LCD_buffer_clear(frame_buffer);
	
	SPI_initialise();
	LCD_initialise();
	PWM_initialise();
	ADC_initialise();

	//BAT_sense();

	LCD_clear();

	byte row = 0;
	byte column = 0;
	byte page, pixel;

	float volt;
	byte integer, decimal_1, decimal_2;

	while (infinite_loop)//Master loop always true so always loop
	{
		
		if(~UP_BUTTON) row--;  //bottom view, so inverse
		if(~DOWN_BUTTON) row++;  //bottom view, so inverse
		if(~LEFT_BUTTON) column--;
		if(~RIGHT_BUTTON) column++;
		if(~A_BUTTON) 
		{
			LCD_clear();
			//row = 35;
			//column = 45;
			pingpong(frame_buffer);
			LCD_fill();
			LCD_clear();
		}
		if(~B_BUTTON) 
		{
			LCD_clear();

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

			row = 0;
			column = 0;
		}
		if(~C_BUTTON) 
		{
			LCD_fill();
			row = 0;
			column = 0;
			LCD_data_tx(0xFF);
			frame_buffer[column][page] = 0xFF;
		}
		page = row/8;
		pixel = row%8;
		select_page(page);
		select_column(column);
		pixel = (_BV(pixel) | (frame_buffer[column][page]));		
		frame_buffer[column][page] = pixel;
		LCD_data_tx(pixel);
		_delay_ms(55);

		//Turn on the LED if BUTTON is pressed
		/*
		if (~UP_BUTTON)
		{
			BAT_LOW_LED(ON);
			_delay_ms(55);	
		} 	
		else
		{
			BAT_LOW_LED(OFF);
		}		
		if (~DOWN_BUTTON)
		{
			BAT_LOW_LED(ON);
			_delay_ms(55);	
		} 	
		else
		{
			BAT_LOW_LED(OFF);
		}

		if (~RIGHT_BUTTON)
		{
			BAT_LOW_LED(ON);
			_delay_ms(55);	
		} 	
		else
		{
			BAT_LOW_LED(OFF);
		}

		if (~LEFT_BUTTON)
		{
			BAT_LOW_LED(ON);
			_delay_ms(55);	
		} 	
		else
		{
			BAT_LOW_LED(OFF);
		}

		if (~A_BUTTON)
		{
			BAT_LOW_LED(ON);
			_delay_ms(55);	
		} 	
		else
		{
			BAT_LOW_LED(OFF);
		}

		if (~B_BUTTON)
		{
			BAT_LOW_LED(ON);
			_delay_ms(55);	
		} 	
		else
		{
			BAT_LOW_LED(OFF);
		}

		if (~C_BUTTON)
		{
			BAT_LOW_LED(ON);
			_delay_ms(55);	
		} 	
		else
		{
			BAT_LOW_LED(OFF);
		}
		*/

	}
	 
}



byte pingpong(byte buffer[][MAX_PAGES])
{	
	byte ro = 63;
	byte col = 35;
	byte col_pad;
	col_pad = 50;
	pad_move(col_pad, buffer, 0);
	//byte pa = ro/8;
	//byte pi = ro%8;
	//select_page(pa); 
	//select_column(col);
	//LCD_data_tx(pi);
	byte direction_horizontal = 0;
	byte direction_vertical = 0;
	byte game = 1;
	while(game)
	{	
		if (~RIGHT_BUTTON)
		{
			pad_move(col_pad, buffer, 0);
			col_pad++;
		}
		if (~LEFT_BUTTON)
		{
			pad_move(col_pad, buffer, 1);
			col_pad--;
		}
		if (direction_vertical == 0)
		{
			if (direction_horizontal == 0)
			{
				ball_clear(col, ro, buffer);
				col++;
				ro--;
				ball_move(col, ro, buffer);
				if (col >= 101)
				{
					direction_horizontal = 1;
				}
				if (ro <= 0)
				{
					direction_vertical = 1;
				}
			}
			else
			{
				ball_clear(col, ro, buffer);
				col--;
				ro--;
				ball_move(col, ro, buffer);
				if (col <= 0)
				{
					direction_horizontal = 0;
				}
				if (ro <= 0)
				{
					direction_vertical = 1;
				}
			}
		}
		else
		{
			if (direction_horizontal == 0)
			{
				ball_clear(col, ro, buffer);
				col++;
				ro++;
				ball_move(col, ro, buffer);
				if (ro == 61)
				{
					if ((col >= col_pad-10) && (col <= col_pad+1))
					{
						direction_vertical = 0;
						col++;
					}
				}
				if (col >= 101)
				{
					direction_horizontal = 1;
				}
				if (ro >= 63)
				{
					game = 0;
				}
			}
			else
			{
				ball_clear(col, ro, buffer);
				col--;
				ro++;
				ball_move(col, ro, buffer);
				if (ro == 61)
				{
					if ((col >= col_pad-10) && (col <= col_pad+1))
					{
						direction_vertical = 0;
						col--;
					}
				}
				if (col <= 0)
				{
					direction_horizontal = 0;
				}
				if (ro >= 63)
				{
					game = 0;
				}
			}
		}
		
	}

	return(TRUE);
}

byte pad_move(byte text_column, byte buffer[][MAX_PAGES], byte dir)
{	
	byte pad_length = 10;
	byte i;
	byte pixel = 0x80;
	select_page(7);
	for (i = 0; i < pad_length; i++)
	{	
		buffer[text_column - i][7] = pixel;
		select_column(text_column - i );
		LCD_data_tx( pixel );
	}
	if (dir == 0)
	{
		buffer[text_column - 10][7] = OFF;
		select_column(text_column - 10 );
	}
	else
	{
		buffer[text_column + 1][7] = OFF;
		select_column(text_column + 1 );
	}
	LCD_data_tx( 0x00 );
	return(TRUE);
}


byte ball_move(byte column, byte row, byte buffer[][MAX_PAGES])
{	
	byte page, pixel;
	page = row/8;
	pixel = row%8;
	select_page(page); 
	select_column(column);
	pixel = (_BV(pixel) | (buffer[column][page]));	
	LCD_data_tx(pixel);
	//_delay_ms(255);
	_delay_ms(50);
	return(TRUE);
}

byte ball_clear(byte column, byte row, byte buffer[][MAX_PAGES])
{
	byte page, pixel;
	page = row/8;
	select_column(column+1);
	select_page(page+1);
	pixel = (OFF | (buffer[column+1][page+1]));
	LCD_data_tx(pixel);
	select_page(page);
	pixel = (OFF | (buffer[column+1][page]));
	LCD_data_tx(pixel);
	select_page(page-1);
	pixel = (OFF | (buffer[column+1][page-1]));
	LCD_data_tx(pixel);
	select_column(column-1);
	select_page(page+1);
	pixel = (OFF | (buffer[column-1][page+1]));
	LCD_data_tx(pixel);
	select_page(page);
	pixel = (OFF | (buffer[column-1][page]));
	LCD_data_tx(pixel);
	select_page(page-1);
	pixel = (OFF | (buffer[column-1][page-1]));
	LCD_data_tx(pixel);
}



byte write_0(byte text_page , byte text_column)
{   
	select_page(text_page + 0); 
	select_column(text_column - 0 ); 
	LCD_data_tx( 0x80 ); 
	select_column(text_column - 1 ); 
	LCD_data_tx( 0 ); 
	select_column(text_column - 2 ); 
	LCD_data_tx( 0x7c ); 
	select_column(text_column - 3 ); 
	LCD_data_tx( 0x82 ); 
	select_column(text_column - 4 ); 
	LCD_data_tx( 0x82 ); 
	select_column(text_column - 5 ); 
	LCD_data_tx( 0x7c ); 
	select_column(text_column - 6 ); 
	LCD_data_tx( 0 ); 
	select_column(text_column - 7 ); 
	LCD_data_tx( 0 );

	return(TRUE);
}



byte write_1(byte text_page , byte text_column)
{   
	select_page(text_page + 0);
	select_column(text_column - 0  );
	LCD_data_tx( 0x80 );
	select_column(text_column - 1  );
	LCD_data_tx( 0 );
	select_column(text_column - 2  );
	LCD_data_tx( 0x80 );
	select_column(text_column - 3  );
	LCD_data_tx( 0xfe );
	select_column(text_column - 4  );
	LCD_data_tx( 0x84 );
	select_column(text_column - 5  );
	LCD_data_tx( 0x88 );
	select_column(text_column - 6  );
	LCD_data_tx( 0 );
	select_column(text_column - 7  );
	LCD_data_tx( 0 );

	return(TRUE);
}

byte write_zero(byte text_page , byte text_column)
{   
	select_page(text_page + 0); 
	select_column(text_column - 0 ); 
	LCD_data_tx( 0 ); 
	select_column(text_column - 1 ); 
	LCD_data_tx( 0 ); 
	select_column(text_column - 2 ); 
	LCD_data_tx( 0x7c ); 
	select_column(text_column - 3 ); 
	LCD_data_tx( 0x82 ); 
	select_column(text_column - 4 ); 
	LCD_data_tx( 0x82 ); 
	select_column(text_column - 5 ); 
	LCD_data_tx( 0x7c ); 
	select_column(text_column - 6 ); 
	LCD_data_tx( 0 ); 
	select_column(text_column - 7 ); 
	LCD_data_tx( 0 );

	return(TRUE);
}

byte write_one(byte text_page , byte text_column)
{   
	select_page(text_page + 0);
	select_column(text_column - 0  );
	LCD_data_tx( 0 );
	select_column(text_column - 1  );
	LCD_data_tx( 0 );
	select_column(text_column - 2  );
	LCD_data_tx( 0x80 );
	select_column(text_column - 3  );
	LCD_data_tx( 0xfe );
	select_column(text_column - 4  );
	LCD_data_tx( 0x84 );
	select_column(text_column - 5  );
	LCD_data_tx( 0x88 );
	select_column(text_column - 6  );
	LCD_data_tx( 0 );
	select_column(text_column - 7  );
	LCD_data_tx( 0 );

	return(TRUE);
}

byte write_two(byte text_page , byte text_column)
{   
	select_page(text_page + 0);
	select_column(text_column - 0 ); 
	LCD_data_tx( 0 ); 
	select_column(text_column - 1 ); 
	LCD_data_tx( 0 ); 
	select_column(text_column - 2 ); 
	LCD_data_tx( 0x8c ); 
	select_column(text_column - 3 ); 
	LCD_data_tx( 0x92 ); 
	select_column(text_column - 4 ); 
	LCD_data_tx( 0xa2 ); 
	select_column(text_column - 5 ); 
	LCD_data_tx( 0xc4 ); 
	select_column(text_column - 6 ); 
	LCD_data_tx( 0 ); 
	select_column(text_column - 7 ); 
	LCD_data_tx( 0 );

	return(TRUE);
}


byte write_three(byte text_page , byte text_column)
{   
	select_page(text_page + 0); 
	select_column(text_column - 0 ); 
	LCD_data_tx( 0 ); 
	select_column(text_column - 1 ); 
	LCD_data_tx( 0 ); 
	select_column(text_column - 2 ); 
	LCD_data_tx( 0x6c ); 
	select_column(text_column - 3 ); 
	LCD_data_tx( 0x92 ); 
	select_column(text_column - 4 ); 
	LCD_data_tx( 0x92 ); 
	select_column(text_column - 5 ); 
	LCD_data_tx( 0x92 ); 
	select_column(text_column - 6 ); 
	LCD_data_tx( 0 ); 
	select_column(text_column - 7 ); 
	LCD_data_tx( 0 );

	return(TRUE);
}

byte write_four(byte text_page , byte text_column)
{   
	select_page(text_page + 0); 
	select_column(text_column - 0 ); 
	LCD_data_tx( 0 ); 
	select_column(text_column - 1 ); 
	LCD_data_tx( 0 ); 
	select_column(text_column - 2 ); 
	LCD_data_tx( 0x20 ); 
	select_column(text_column - 3 ); 
	LCD_data_tx( 0xfe ); 
	select_column(text_column - 4 ); 
	LCD_data_tx( 0x24 ); 
	select_column(text_column - 5 ); 
	LCD_data_tx( 0x38 ); 
	select_column(text_column - 6 ); 
	LCD_data_tx( 0x20 ); 
	select_column(text_column - 7 ); 
	LCD_data_tx( 0 );

	return(TRUE);
}

byte write_five(byte text_page , byte text_column)
{   
	select_page(text_page + 0); 
	select_column(text_column - 0 ); 
	LCD_data_tx( 0 ); 
	select_column(text_column - 1 ); 
	LCD_data_tx( 0 ); 
	select_column(text_column - 2 ); 
	LCD_data_tx( 0xf2 ); 
	select_column(text_column - 3 ); 
	LCD_data_tx( 0x92 ); 
	select_column(text_column - 4 ); 
	LCD_data_tx( 0x92 ); 
	select_column(text_column - 5 ); 
	LCD_data_tx( 0x9e ); 
	select_column(text_column - 6 ); 
	LCD_data_tx( 0 ); 
	select_column(text_column - 7 ); 
	LCD_data_tx( 0 ); 

	return(TRUE);
}

byte write_six(byte text_page , byte text_column)
{   
	select_page(text_page + 0); 
	select_column(text_column - 0 ); 
	LCD_data_tx( 0 ); 
	select_column(text_column - 1 ); 
	LCD_data_tx( 0 ); 
	select_column(text_column - 2 ); 
	LCD_data_tx( 0x60 ); 
	select_column(text_column - 3 ); 
	LCD_data_tx( 0x92 ); 
	select_column(text_column - 4 ); 
	LCD_data_tx( 0x92 ); 
	select_column(text_column - 5 ); 
	LCD_data_tx( 0x7c ); 
	select_column(text_column - 6 ); 
	LCD_data_tx( 0 ); 
	select_column(text_column - 7 ); 
	LCD_data_tx( 0 );

	return(TRUE);
}

byte write_seven(byte text_page , byte text_column)
{   
	select_page(text_page + 0); 
	select_column(text_column - 0 ); 
	LCD_data_tx( 0 ); 
	select_column(text_column - 1 ); 
	LCD_data_tx( 0 ); 
	select_column(text_column - 2 ); 
	LCD_data_tx( 0xe ); 
	select_column(text_column - 3 ); 
	LCD_data_tx( 0x12 ); 
	select_column(text_column - 4 ); 
	LCD_data_tx( 0xe2 ); 
	select_column(text_column - 5 ); 
	LCD_data_tx( 0x2 ); 
	select_column(text_column - 6 ); 
	LCD_data_tx( 0 ); 
	select_column(text_column - 7 ); 
	LCD_data_tx( 0 );

	return(TRUE);
}

byte write_eight(byte text_page , byte text_column)
{   
	select_page(text_page + 0); 
	select_column(text_column - 0 ); 
	LCD_data_tx( 0 ); 
	select_column(text_column - 1 ); 
	LCD_data_tx( 0 ); 
	select_column(text_column - 2 ); 
	LCD_data_tx( 0xfe ); 
	select_column(text_column - 3 ); 
	LCD_data_tx( 0x92 ); 
	select_column(text_column - 4 ); 
	LCD_data_tx( 0x92 ); 
	select_column(text_column - 5 ); 
	LCD_data_tx( 0xfe ); 
	select_column(text_column - 6 ); 
	LCD_data_tx( 0 ); 
	select_column(text_column - 7 ); 
	LCD_data_tx( 0 );
	
	return(TRUE);
}

byte write_nine(byte text_page , byte text_column)
{   
	select_page(text_page + 0); 
	select_column(text_column - 0 ); 
	LCD_data_tx( 0 ); 
	select_column(text_column - 1 ); 
	LCD_data_tx( 0 ); 
	select_column(text_column - 2 ); 
	LCD_data_tx( 0xfe ); 
	select_column(text_column - 3 ); 
	LCD_data_tx( 0x12 ); 
	select_column(text_column - 4 ); 
	LCD_data_tx( 0x12 ); 
	select_column(text_column - 5 ); 
	LCD_data_tx( 0x1e ); 
	select_column(text_column - 6 ); 
	LCD_data_tx( 0 ); 
	select_column(text_column - 7 ); 
	LCD_data_tx( 0 );
	
	return(TRUE);
}


byte write_v(byte text_page , byte text_column)
{   
	select_page(text_page + 0); 
	select_column(text_column - 0 ); 
	LCD_data_tx( 0 ); 
	select_column(text_column - 1 ); 
	LCD_data_tx( 0 ); 
	select_column(text_column - 2 ); 
	LCD_data_tx( 0x3c ); 
	select_column(text_column - 3 ); 
	LCD_data_tx( 0x40 ); 
	select_column(text_column - 4 ); 
	LCD_data_tx( 0x80 ); 
	select_column(text_column - 5 ); 
	LCD_data_tx( 0x40 ); 
	select_column(text_column - 6 ); 
	LCD_data_tx( 0x3c ); 
	select_column(text_column - 7 ); 
	LCD_data_tx( 0 ); 

	return(TRUE);
}


