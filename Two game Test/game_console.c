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
	//ADC_initialise();

	//BAT_sense();

	LCD_clear();

	byte row = 35;
	byte column = 45;
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
			//pingpong(frame_buffer);
			tictactoe(frame_buffer);
			LCD_buffer_clear(frame_buffer);
			LCD_fill();
			LCD_clear();
		}
		if(~B_BUTTON) 
		{
			LCD_clear();
/*
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
*/
			row = 30;
			column = 40;
		}
		if(~C_BUTTON) 
		{
			LCD_clear();
			pingpong(frame_buffer);
			LCD_fill();
			row = 0;
			column = 0;
			page = row/8;
			select_page(page);
			select_column(column);
			LCD_data_tx(0xFF);
			//frame_buffer[column][page] = 0xFF;
			LCD_buffer_clear(frame_buffer);
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
	col_pad = 30;
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
			col_pad+=2;
		}
		if (~LEFT_BUTTON)
		{
			pad_move(col_pad, buffer, 1);
			col_pad-=2;
		}
		if (direction_vertical == 0)
		{
			if (direction_horizontal == 0)
			{
				ball_clear(col, ro, buffer);
				col++;
				ro--;
				ball_move(col, ro, buffer);
				if (ro == 2)
				{
					if ((col >= col_pad-10) && (col <= col_pad+1))
					{
						direction_vertical = 1;
						col++;
					}
				}
				if (col >= 101)
				{
					direction_horizontal = 1;
				}
				if (ro <= 0)
				{
					game = 0;
				}
			}
			else
			{
				ball_clear(col, ro, buffer);
				col--;
				ro--;
				ball_move(col, ro, buffer);
				if (ro == 2)
				{
					if ((col >= col_pad-10) && (col <= col_pad+1))
					{
						direction_vertical = 1;
						col--;
					}
				}
				if (col <= 0)
				{
					direction_horizontal = 0;
				}
				if (ro <= 0)
				{
					game = 0;
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
		LCD_data_tx( 0x00 );
		buffer[text_column - 10][7] = OFF;
		select_column(text_column - 11 );
		LCD_data_tx( 0x00 );
	}
	else
	{
		buffer[text_column + 1][7] = OFF;
		select_column(text_column + 1 );
		LCD_data_tx( 0x00 );
		buffer[text_column + 1][7] = OFF;
		select_column(text_column + 2 );
		LCD_data_tx( 0x00 );
	}
	

	pixel = 0x01;
	select_page(0);
	for (i = 0; i < pad_length; i++)
	{	
		buffer[text_column - i][0] = pixel;
		select_column(text_column - i );
		LCD_data_tx( pixel );
	}
	if (dir == 0)
	{
		buffer[text_column - 10][0] = OFF;
		select_column(text_column - 10 );
		LCD_data_tx( 0x00 );
		buffer[text_column - 10][0] = OFF;
		select_column(text_column - 11 );
		LCD_data_tx( 0x00 );
	}
	else
	{
		buffer[text_column + 1][0] = OFF;
		select_column(text_column + 1 );
		buffer[text_column + 1][0] = OFF;
		select_column(text_column + 2 );
	}
	

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


/*
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
*/

//TicTacToe
byte tictactoe(byte buffer[][MAX_PAGES])
{
	byte board_buffer[BOARDSIZE][BOARDSIZE];
	gameboard_draw(buffer);
	byte game = ON;
	byte move_count = 0;
	byte result = 0;	
	while(game)
	{
		human_move(board_buffer);
		gamestate_draw(board_buffer);
		ai_move(board_buffer);
		gamestate_draw(board_buffer);
		result = get_result(board_buffer);
		move_count++;
		if (result != 0)
		{
			game = 0;
		}
		if (move_count == 9)
		{
			game = 0;
		}
	}
	return(TRUE);
}

byte gameboard_draw(byte buffer[][MAX_PAGES])
{
	byte i, column, row, page, pixel;

	column = 40;
	//select_column(column);
	for (i = 0; i <= MAX_PAGES; i++)
	{
		select_page(i);
		select_column(column);
		pixel = ON;
		pixel = (pixel | (buffer[column][i]));	
		buffer[column][i] = pixel;
		LCD_data_tx(pixel);
	}
	column = 61;
	//select_column(column);
	for (i = 0; i <= MAX_PAGES; i++)
	{
		select_page(i);
		select_column(column);
		pixel = ON;
		pixel = (pixel | (buffer[column][i]));	
		buffer[column][i] = pixel;
		LCD_data_tx(pixel);
	}

	row = 21;
	page = row/8;
	pixel = 0x10;
	select_page(page);
	for (i = 18; i < 84; i++)
	{
		select_column(i);
		//select_page(page);
		//pixel = (pixel | (buffer[i][page]));
		buffer[i][page] = pixel;
		LCD_data_tx(pixel);
	}
	row = 42;
	page = row/8;
	pixel = 0x08;
	select_page(page);
	for (i = 18; i < 84; i++)
	{
		select_column(i);
		//select_page(page);
		//pixel = (pixel | (buffer[i][page]));
		buffer[i][page] = pixel;
		LCD_data_tx(pixel);
	}
	return(TRUE);
}

byte gamestate_draw(byte board[BOARDSIZE][BOARDSIZE])
{
	byte i, j;
	for (i = 0; i < BOARDSIZE; i++)
	{
		for (j = 0; j < BOARDSIZE; j++)
		{
			if (board[i][j] == X)
			{
				write_x(i, j);
			}	
			if (board[i][j] == O)
			{
				write_o(i, j);
			}			
		}
	}
	return(TRUE);
}

byte human_move(byte board[BOARDSIZE][BOARDSIZE])
{
	byte x = 1;
	byte y = 1;
	byte move = ON;
	while(move)
	{
		clear_pointer(x, y);
		if (~UP_BUTTON)
		{
			if (y == 0)
			{
				y = 0;
			}
			else y--;
			_delay_ms(150);
		}
		if (~DOWN_BUTTON)
		{
			if (y > 2)
			{
				y = 2;
			}
			else y++;
			_delay_ms(150);
		}
		if (~RIGHT_BUTTON)
		{
			if (x > 2)
			{
				x = 2;
			}
			else x++;
			_delay_ms(150);
		}
		if (~LEFT_BUTTON)
		{
			if (x == 0)
			{
				x = 0;
			}
			else x--;
			_delay_ms(150);
		}
		move_show(x, y);
		//_delay_ms(250);
		if (~A_BUTTON)
		{
			if ((board[x][y] != X) && (board[x][y] != O))
			{
				board[x][y] = X;
				clear_pointer(x, y);
				_delay_ms(150);
				move = OFF;
			}
		}
	}
	return(TRUE);	
}

byte ai_move(byte board[BOARDSIZE][BOARDSIZE])
{
	byte i, j;
	for (i = 0; i < BOARDSIZE; i++)
	{
		for (j = 0; j < BOARDSIZE; j++)
		{
			if ((board[i][j] != X) && (board[i][j] != O))
			{
				board[i][j] = O;
				return(TRUE);
			}
		}
	}
	return(TRUE);
}

byte move_show(byte x_axis, byte y_axis)
{
	byte column, page;
	column = x_axis*21+20;
	page = y_axis*3;
	show_pointer(page, column);
}

byte show_pointer(byte text_page , byte text_column)
{
	select_page(text_page);
	select_column(text_column+1);
	LCD_data_tx(0x1C);
	select_column(text_column+2);
	LCD_data_tx(0x04);
	select_column(text_column+3);
	LCD_data_tx(0x04);
	select_column(text_column+16);
	LCD_data_tx(0x04);
	select_column(text_column+17);
	LCD_data_tx(0x04);
	select_column(text_column+18);
	LCD_data_tx(0x1C);

	select_page(text_page+1);
	select_column(text_column+1);
	LCD_data_tx(0x38);
	select_column(text_column+2);
	LCD_data_tx(0x20);
	select_column(text_column+3);
	LCD_data_tx(0x20);
	select_column(text_column+16);
	LCD_data_tx(0x20);
	select_column(text_column+17);
	LCD_data_tx(0x20);
	select_column(text_column+18);
	LCD_data_tx(0x38);
	return(TRUE);
}

byte clear_pointer(byte x_axis, byte y_axis)
{	
	byte text_column = x_axis*21+20;
	byte text_page = y_axis*3;
	select_page(text_page);
	select_column(text_column+1);
	LCD_data_tx(OFF);
	select_column(text_column+2);
	LCD_data_tx(OFF);
	select_column(text_column+3);
	LCD_data_tx(OFF);
	select_column(text_column+16);
	LCD_data_tx(OFF);
	select_column(text_column+17);
	LCD_data_tx(OFF);
	select_column(text_column+18);
	LCD_data_tx(OFF);
	select_page(text_page+1);
	select_column(text_column+1);
	LCD_data_tx(OFF);
	select_column(text_column+2);
	LCD_data_tx(OFF);
	select_column(text_column+3);
	LCD_data_tx(OFF);
	select_column(text_column+16);
	LCD_data_tx(OFF);
	select_column(text_column+17);
	LCD_data_tx(OFF);
	select_column(text_column+18);
	LCD_data_tx(OFF);
	return(TRUE);
}

byte write_x(byte x_axis, byte y_axis)
{
	byte text_column = x_axis*21+20;
	byte text_page = y_axis*3;
	select_page(text_page);
	select_column(text_column+5);
	LCD_data_tx(0x08);
	select_column(text_column+14);
	LCD_data_tx(0x08);
	select_column(text_column+6);
	LCD_data_tx(0x10);
	select_column(text_column+13);
	LCD_data_tx(0x10);
	select_column(text_column+7);
	LCD_data_tx(0x20);
	select_column(text_column+12);
	LCD_data_tx(0x20);
	select_column(text_column+8);
	LCD_data_tx(0x40);
	select_column(text_column+11);
	LCD_data_tx(0x40);
	select_column(text_column+9);
	LCD_data_tx(0x80);
	select_column(text_column+10);
	LCD_data_tx(0x80);

	select_page(text_page+1);
	select_column(text_column+5);
	LCD_data_tx(0x10);
	select_column(text_column+14);
	LCD_data_tx(0x10);
	select_column(text_column+6);
	LCD_data_tx(0x08);
	select_column(text_column+13);
	LCD_data_tx(0x08);
	select_column(text_column+7);
	LCD_data_tx(0x04);
	select_column(text_column+12);
	LCD_data_tx(0x04);
	select_column(text_column+8);
	LCD_data_tx(0x02);
	select_column(text_column+11);
	LCD_data_tx(0x02);
	select_column(text_column+9);
	LCD_data_tx(0x01);
	select_column(text_column+10);
	LCD_data_tx(0x01);
}

byte write_o(byte x_axis, byte y_axis)
{
	byte text_column = x_axis*21+20;
	byte text_page = y_axis*3;
	select_page(text_page);
	select_column(text_column+5);
	LCD_data_tx(0xC0);
	select_column(text_column+6);
	LCD_data_tx(0x20);
	select_column(text_column+7);
	LCD_data_tx(0x10);
	select_column(text_column+8);
	LCD_data_tx(0x08);
	select_column(text_column+9);
	LCD_data_tx(0x08);
	select_column(text_column+10);
	LCD_data_tx(0x08);
	select_column(text_column+11);
	LCD_data_tx(0x08);
	select_column(text_column+12);
	LCD_data_tx(0x10);
	select_column(text_column+13);
	LCD_data_tx(0x20);
	select_column(text_column+14);
	LCD_data_tx(0xC0);

	select_page(text_page+1);
	select_column(text_column+5);
	LCD_data_tx(0x03);
	select_column(text_column+6);
	LCD_data_tx(0x04);
	select_column(text_column+7);
	LCD_data_tx(0x08);
	select_column(text_column+8);
	LCD_data_tx(0x10);
	select_column(text_column+9);
	LCD_data_tx(0x10);
	select_column(text_column+10);
	LCD_data_tx(0x10);
	select_column(text_column+11);
	LCD_data_tx(0x10);
	select_column(text_column+12);
	LCD_data_tx(0x08);
	select_column(text_column+13);
	LCD_data_tx(0x04);
	select_column(text_column+14);
	LCD_data_tx(0x03);

	return(TRUE);
}

byte get_result(byte board[BOARDSIZE][BOARDSIZE])
{
	byte i, j;
	byte count_x =0, count_o = 0;
	byte WINNING = 3;
	byte result = 0;
	byte WIN = 1;
	byte LOSE = 2;

	//evaluate winning condition horizontally
	for (i = 0; i < BOARDSIZE; i++)
	{
		for (j = 0; j < BOARDSIZE; j++)
		{
			if (board[i][j] == O)
			{
				count_o++;
			}
			if (board[i][j] == X) {
				count_x++;
			}	
		}
		if (count_o == WINNING)
		{
			result = LOSE;
		}
		if (count_x == WINNING)
		{
			result = WIN;
		}
		count_o = 0;
		count_x = 0;	
	}

	//evaluate winning condition vertically
	for (i = 0; i < BOARDSIZE; i++)
	{
		for (j = 0; j < BOARDSIZE; j++)
		{
			if (board[j][i] == O)
			{
				count_o++;
			}
			if (board[j][i] == X) {
				count_x++;
			}	
		}
		if (count_o == WINNING)
		{
			result = LOSE;
		}
		if (count_x == WINNING)
		{
			result = WIN;
		}
		count_o = 0;
		count_x = 0;	
	}

	if (board[1][1] == O) {
		if (board[0][0] == board[2][2] && board[0][0] == O)
		{
			result = WIN;
		}
		if (board[0][2] == board[2][0] && board[0][2] == O)
		{
			result = WIN;
		}
		}
	if (board[1][1] == X) {
		if (board[0][0] == board[2][2] && board[0][0] == X)
		{				
			result = LOSE;
		}
		if (board[0][2] == board[2][0] && board[0][2] == X)
		{
			result = LOSE;
		}		
	}

	return(result);
}
