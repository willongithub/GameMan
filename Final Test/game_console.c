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
	SCK_DIR(OUT);
    MOSI_DIR(OUT);
    MISO_DIR(IN);
	BAT_SEN_DIR(IN);
	BACKLIGHT_DIR(OUT);
	MCU_SS_DIR(OUT);

	//Initialize pins
	LCD_CD_SET(LOW);
	LCD_CS_SET(HIGH);
	LCD_RST_SET(HIGH);	
	MCU_SS_SET(HIGH);	
	UP_BUTTON_SET(PULLUP);
	DOWN_BUTTON_SET(PULLUP);
	RIGHT_BUTTON_SET(PULLUP);
	LEFT_BUTTON_SET(PULLUP);
	A_BUTTON_SET(PULLUP);
	B_BUTTON_SET(PULLUP);
	C_BUTTON_SET(PULLUP);


	byte frame_buffer[MAX_COLUMNS][MAX_PAGES];
	LCD_buffer_clear(frame_buffer);
	
	SPI_initialise();
	LCD_initialise();
	PWM_initialise();
	ADC_initialise();
	//FRAM_initialise();
	INTERRUPT_initialise();

	LCD_clear();

	byte row = 30;
	byte column = 40;
	byte page, pixel;
	//float volt;
	//byte integer, decimal_1, decimal_2;

	while (infinite_loop)//Master loop always true so always loop
	{
		
		if(~UP_BUTTON) row--;  //bottom view, so inverse
		if(~DOWN_BUTTON) row++;  //bottom view, so inverse
		if(~LEFT_BUTTON) column--;
		if(~RIGHT_BUTTON) column++;
		_delay_ms(155);

/*
// home screen routine
		LCD_clear();
		_delay_ms(255);
		LCD_fill();
		LCD_clear();
		write_homescreen();
		//LCD_clear();
		//_delay_ms(255);
		LCD_clear();
		_delay_ms(55);
		write_homescreen();
		_delay_ms(155);
		LCD_clear();
		write_homescreen();
		_delay_ms(255);
		_delay_ms(255);
		LCD_clear();
		_delay_ms(55);
		write_homescreen();
		_delay_ms(255);
		_delay_ms(255);
		_delay_ms(255);
		LCD_clear();
		LCD_fill();
		write_homescreen();		

		while(1);
*/


		if(~A_BUTTON) 
		{
			LCD_clear();
			//row = 35;
			//column = 45;
			//pingpong(frame_buffer);
			//tictactoe(frame_buffer);
			//LCD_buffer_clear(frame_buffer);
			LCD_fill();
			LCD_clear();
			//FRAM_write(0x09); //demo data to fram
		}


		if(~B_BUTTON) 
		{
			LCD_clear();
			LCD_fill();
			LCD_clear();
			/*
			byte digi;
			digi = FRAM_read();
			//digi = 0x08;
			if (digi == 0) write_v(3, 52);
			switch (digi)
			{
				//case 0x00:write_zero(3, 52);break;
				case 0x01:write_one(3, 52);break;
				case 0x02:write_two(3, 52);break;
				case 0x03:write_three(3, 52);break;
				case 0x04:write_four(3, 52);break;
				case 0x05:write_five(3, 52);break;
				case 0x06:write_six(3, 52);break;
				case 0x07:write_seven(3, 52);break;
				case 0x08:write_eight(3, 52);break;
				case 0x09:write_nine(3, 52);break;
				//default:write_zero(3, 52);
				break;
			}


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
			row = 0;
			column = 0;
		}



		if(~C_BUTTON) 
		{
			LCD_clear();
			//pingpong(frame_buffer);
			tictactoe(frame_buffer);
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
		//_delay_ms(55);
		

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
	//return(TRUE);
}


/*
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
		LCD_data_tx( 0x00 );
		buffer[text_column + 1][0] = OFF;
		select_column(text_column + 2 );
		LCD_data_tx( 0x00 );
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
*/





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
		if (~B_BUTTON)
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



/*
byte write_homescreen()
{
	byte text_page = 0;
	byte text_column = 0;

	select_page(text_page + 0);
	select_column(text_column + 0 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 1 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 2 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 3 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 4 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 5 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 6 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 7 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 8 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 9 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 10 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 11 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 12 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 13 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 14 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 15 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 16 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 17 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 18 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 19 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 20 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 21 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 22 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 23 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 24 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 25 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 26 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 27 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 28 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 29 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 30 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 31 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 32 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 33 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 34 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 35 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 36 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 37 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 38 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 39 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 40 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 41 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 42 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 43 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 44 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 45 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 46 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 47 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 48 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 49 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 50 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 51 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 52 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 53 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 54 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 55 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 56 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 57 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 58 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 59 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 60 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 61 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 62 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 63 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 64 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 65 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 66 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 67 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 68 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 69 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 70 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 71 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 72 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 73 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 74 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 75 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 76 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 77 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 78 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 79 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 80 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 81 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 82 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 83 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 84 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 85 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 86 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 87 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 88 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 89 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 90 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 91 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 92 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 93 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 94 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 95 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 96 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 97 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 98 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 99 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 100 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 101 ); 
	LCD_data_tx( 0x0 ) ;


	select_page(text_page + 1);
	select_column(text_column + 0 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 1 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 2 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 3 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 4 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 5 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 6 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 7 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 8 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 9 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 10 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 11 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 12 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 13 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 14 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 15 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 16 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 17 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 18 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 19 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 20 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 21 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 22 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 23 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 24 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 25 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 26 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 27 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 28 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 29 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 30 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 31 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 32 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 33 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 34 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 35 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 36 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 37 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 38 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 39 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 40 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 41 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 42 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 43 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 44 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 45 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 46 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 47 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 48 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 49 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 50 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 51 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 52 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 53 ); 
	LCD_data_tx( 0x80 ) ; 
	select_column(text_column + 54 ); 
	LCD_data_tx( 0xC0 ) ; 
	select_column(text_column + 55 ); 
	LCD_data_tx( 0xC0 ) ; 
	select_column(text_column + 56 ); 
	LCD_data_tx( 0x80 ) ; 
	select_column(text_column + 57 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 58 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 59 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 60 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 61 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 62 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 63 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 64 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 65 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 66 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 67 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 68 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 69 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 70 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 71 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 72 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 73 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 74 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 75 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 76 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 77 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 78 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 79 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 80 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 81 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 82 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 83 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 84 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 85 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 86 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 87 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 88 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 89 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 90 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 91 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 92 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 93 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 94 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 95 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 96 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 97 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 98 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 99 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 100 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 101 ); 
	LCD_data_tx( 0x0 ) ; 
	select_page(text_page + 2); 
	select_column(text_column + 0 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 1 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 2 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 3 ); 
	LCD_data_tx( 0x80 ) ; 
	select_column(text_column + 4 ); 
	LCD_data_tx( 0x80 ) ; 
	select_column(text_column + 5 ); 
	LCD_data_tx( 0xC0 ) ; 
	select_column(text_column + 6 ); 
	LCD_data_tx( 0xC0 ) ; 
	select_column(text_column + 7 ); 
	LCD_data_tx( 0xE0 ) ; 
	select_column(text_column + 8 ); 
	LCD_data_tx( 0xE0 ) ; 
	select_column(text_column + 9 ); 
	LCD_data_tx( 0x60 ) ; 
	select_column(text_column + 10 ); 
	LCD_data_tx( 0x70 ) ; 
	select_column(text_column + 11 ); 
	LCD_data_tx( 0x30 ) ; 
	select_column(text_column + 12 ); 
	LCD_data_tx( 0x30 ) ; 
	select_column(text_column + 13 ); 
	LCD_data_tx( 0x30 ) ; 
	select_column(text_column + 14 ); 
	LCD_data_tx( 0x30 ) ; 
	select_column(text_column + 15 ); 
	LCD_data_tx( 0x30 ) ; 
	select_column(text_column + 16 ); 
	LCD_data_tx( 0x30 ) ; 
	select_column(text_column + 17 ); 
	LCD_data_tx( 0x30 ) ; 
	select_column(text_column + 18 ); 
	LCD_data_tx( 0x30 ) ; 
	select_column(text_column + 19 ); 
	LCD_data_tx( 0x60 ) ; 
	select_column(text_column + 20 ); 
	LCD_data_tx( 0xE0 ) ; 
	select_column(text_column + 21 ); 
	LCD_data_tx( 0xC0 ) ; 
	select_column(text_column + 22 ); 
	LCD_data_tx( 0x80 ) ; 
	select_column(text_column + 23 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 24 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 25 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 26 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 27 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 28 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 29 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 30 ); 
	LCD_data_tx( 0xE0 ) ; 
	select_column(text_column + 31 ); 
	LCD_data_tx( 0xE0 ) ; 
	select_column(text_column + 32 ); 
	LCD_data_tx( 0x60 ) ; 
	select_column(text_column + 33 ); 
	LCD_data_tx( 0x30 ) ; 
	select_column(text_column + 34 ); 
	LCD_data_tx( 0x30 ) ; 
	select_column(text_column + 35 ); 
	LCD_data_tx( 0x10 ) ; 
	select_column(text_column + 36 ); 
	LCD_data_tx( 0x18 ) ; 
	select_column(text_column + 37 ); 
	LCD_data_tx( 0xF8 ) ; 
	select_column(text_column + 38 ); 
	LCD_data_tx( 0xB8 ) ; 
	select_column(text_column + 39 ); 
	LCD_data_tx( 0xE0 ) ; 
	select_column(text_column + 40 ); 
	LCD_data_tx( 0x70 ) ; 
	select_column(text_column + 41 ); 
	LCD_data_tx( 0x18 ) ; 
	select_column(text_column + 42 ); 
	LCD_data_tx( 0x38 ) ; 
	select_column(text_column + 43 ); 
	LCD_data_tx( 0x60 ) ; 
	select_column(text_column + 44 ); 
	LCD_data_tx( 0xC0 ) ; 
	select_column(text_column + 45 ); 
	LCD_data_tx( 0x80 ) ; 
	select_column(text_column + 46 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 47 ); 
	LCD_data_tx( 0x80 ) ; 
	select_column(text_column + 48 ); 
	LCD_data_tx( 0xC0 ) ; 
	select_column(text_column + 49 ); 
	LCD_data_tx( 0xD8 ) ; 
	select_column(text_column + 50 ); 
	LCD_data_tx( 0xFC ) ; 
	select_column(text_column + 51 ); 
	LCD_data_tx( 0xE6 ) ; 
	select_column(text_column + 52 ); 
	LCD_data_tx( 0x73 ) ; 
	select_column(text_column + 53 ); 
	LCD_data_tx( 0x71 ) ; 
	select_column(text_column + 54 ); 
	LCD_data_tx( 0x78 ) ; 
	select_column(text_column + 55 ); 
	LCD_data_tx( 0xE8 ) ; 
	select_column(text_column + 56 ); 
	LCD_data_tx( 0xC9 ) ; 
	select_column(text_column + 57 ); 
	LCD_data_tx( 0xCF ) ; 
	select_column(text_column + 58 ); 
	LCD_data_tx( 0x86 ) ; 
	select_column(text_column + 59 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 60 ); 
	LCD_data_tx( 0xC0 ) ; 
	select_column(text_column + 61 ); 
	LCD_data_tx( 0xE0 ) ; 
	select_column(text_column + 62 ); 
	LCD_data_tx( 0x20 ) ; 
	select_column(text_column + 63 ); 
	LCD_data_tx( 0x20 ) ; 
	select_column(text_column + 64 ); 
	LCD_data_tx( 0x20 ) ; 
	select_column(text_column + 65 ); 
	LCD_data_tx( 0x20 ) ; 
	select_column(text_column + 66 ); 
	LCD_data_tx( 0x20 ) ; 
	select_column(text_column + 67 ); 
	LCD_data_tx( 0xF8 ) ; 
	select_column(text_column + 68 ); 
	LCD_data_tx( 0xF8 ) ; 
	select_column(text_column + 69 ); 
	LCD_data_tx( 0x18 ) ; 
	select_column(text_column + 70 ); 
	LCD_data_tx( 0x18 ) ; 
	select_column(text_column + 71 ); 
	LCD_data_tx( 0x18 ) ; 
	select_column(text_column + 72 ); 
	LCD_data_tx( 0xF8 ) ; 
	select_column(text_column + 73 ); 
	LCD_data_tx( 0x80 ) ; 
	select_column(text_column + 74 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 75 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 76 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 77 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 78 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 79 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 80 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 81 ); 
	LCD_data_tx( 0xE0 ) ; 
	select_column(text_column + 82 ); 
	LCD_data_tx( 0xE0 ) ; 
	select_column(text_column + 83 ); 
	LCD_data_tx( 0x40 ) ; 
	select_column(text_column + 84 ); 
	LCD_data_tx( 0x40 ) ; 
	select_column(text_column + 85 ); 
	LCD_data_tx( 0x40 ) ; 
	select_column(text_column + 86 ); 
	LCD_data_tx( 0xC0 ) ; 
	select_column(text_column + 87 ); 
	LCD_data_tx( 0xC0 ) ; 
	select_column(text_column + 88 ); 
	LCD_data_tx( 0x80 ) ; 
	select_column(text_column + 89 ); 
	LCD_data_tx( 0x80 ) ; 
	select_column(text_column + 90 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 91 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 92 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 93 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 94 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 95 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 96 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 97 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 98 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 99 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 100 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 101 ); 
	LCD_data_tx( 0x0 ) ; 
	select_page(text_page + 3); 
	select_column(text_column + 0 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 1 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 2 ); 
	LCD_data_tx( 0x3 ) ; 
	select_column(text_column + 3 ); 
	LCD_data_tx( 0xF ) ; 
	select_column(text_column + 4 ); 
	LCD_data_tx( 0x3F ) ; 
	select_column(text_column + 5 ); 
	LCD_data_tx( 0x70 ) ; 
	select_column(text_column + 6 ); 
	LCD_data_tx( 0xE0 ) ; 
	select_column(text_column + 7 ); 
	LCD_data_tx( 0xC0 ) ; 
	select_column(text_column + 8 ); 
	LCD_data_tx( 0xC0 ) ; 
	select_column(text_column + 9 ); 
	LCD_data_tx( 0x80 ) ; 
	select_column(text_column + 10 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 11 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 12 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 13 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 14 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 15 ); 
	LCD_data_tx( 0xC ) ; 
	select_column(text_column + 16 ); 
	LCD_data_tx( 0x1C ) ; 
	select_column(text_column + 17 ); 
	LCD_data_tx( 0x3C ) ; 
	select_column(text_column + 18 ); 
	LCD_data_tx( 0x3C ) ; 
	select_column(text_column + 19 ); 
	LCD_data_tx( 0xF8 ) ; 
	select_column(text_column + 20 ); 
	LCD_data_tx( 0x20 ) ; 
	select_column(text_column + 21 ); 
	LCD_data_tx( 0x1 ) ; 
	select_column(text_column + 22 ); 
	LCD_data_tx( 0x83 ) ; 
	select_column(text_column + 23 ); 
	LCD_data_tx( 0xFF ) ; 
	select_column(text_column + 24 ); 
	LCD_data_tx( 0x7E ) ; 
	select_column(text_column + 25 ); 
	LCD_data_tx( 0x60 ) ; 
	select_column(text_column + 26 ); 
	LCD_data_tx( 0x20 ) ; 
	select_column(text_column + 27 ); 
	LCD_data_tx( 0xB0 ) ; 
	select_column(text_column + 28 ); 
	LCD_data_tx( 0x10 ) ; 
	select_column(text_column + 29 ); 
	LCD_data_tx( 0x10 ) ; 
	select_column(text_column + 30 ); 
	LCD_data_tx( 0x13 ) ; 
	select_column(text_column + 31 ); 
	LCD_data_tx( 0x13 ) ; 
	select_column(text_column + 32 ); 
	LCD_data_tx( 0x3F ) ; 
	select_column(text_column + 33 ); 
	LCD_data_tx( 0xFF ) ; 
	select_column(text_column + 34 ); 
	LCD_data_tx( 0x80 ) ; 
	select_column(text_column + 35 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 36 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 37 ); 
	LCD_data_tx( 0x7 ) ; 
	select_column(text_column + 38 ); 
	LCD_data_tx( 0x3 ) ; 
	select_column(text_column + 39 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 40 ); 
	LCD_data_tx( 0x40 ) ; 
	select_column(text_column + 41 ); 
	LCD_data_tx( 0x60 ) ; 
	select_column(text_column + 42 ); 
	LCD_data_tx( 0xF0 ) ; 
	select_column(text_column + 43 ); 
	LCD_data_tx( 0x98 ) ; 
	select_column(text_column + 44 ); 
	LCD_data_tx( 0xFC ) ; 
	select_column(text_column + 45 ); 
	LCD_data_tx( 0xFD ) ; 
	select_column(text_column + 46 ); 
	LCD_data_tx( 0x87 ) ; 
	select_column(text_column + 47 ); 
	LCD_data_tx( 0x1 ) ; 
	select_column(text_column + 48 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 49 ); 
	LCD_data_tx( 0x30 ) ; 
	select_column(text_column + 50 ); 
	LCD_data_tx( 0xC ) ; 
	select_column(text_column + 51 ); 
	LCD_data_tx( 0xE ) ; 
	select_column(text_column + 52 ); 
	LCD_data_tx( 0xE ) ; 
	select_column(text_column + 53 ); 
	LCD_data_tx( 0x46 ) ; 
	select_column(text_column + 54 ); 
	LCD_data_tx( 0x62 ) ; 
	select_column(text_column + 55 ); 
	LCD_data_tx( 0x30 ) ; 
	select_column(text_column + 56 ); 
	LCD_data_tx( 0x38 ) ; 
	select_column(text_column + 57 ); 
	LCD_data_tx( 0x3D ) ; 
	select_column(text_column + 58 ); 
	LCD_data_tx( 0x7F ) ; 
	select_column(text_column + 59 ); 
	LCD_data_tx( 0x67 ) ; 
	select_column(text_column + 60 ); 
	LCD_data_tx( 0xFF ) ; 
	select_column(text_column + 61 ); 
	LCD_data_tx( 0x9F ) ; 
	select_column(text_column + 62 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 63 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 64 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 65 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 66 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 67 ); 
	LCD_data_tx( 0x7 ) ; 
	select_column(text_column + 68 ); 
	LCD_data_tx( 0x1 ) ; 
	select_column(text_column + 69 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 70 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 71 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 72 ); 
	LCD_data_tx( 0x81 ) ; 
	select_column(text_column + 73 ); 
	LCD_data_tx( 0xFF ) ; 
	select_column(text_column + 74 ); 
	LCD_data_tx( 0x78 ) ; 
	select_column(text_column + 75 ); 
	LCD_data_tx( 0x30 ) ; 
	select_column(text_column + 76 ); 
	LCD_data_tx( 0x98 ) ; 
	select_column(text_column + 77 ); 
	LCD_data_tx( 0xD8 ) ; 
	select_column(text_column + 78 ); 
	LCD_data_tx( 0xAC ) ; 
	select_column(text_column + 79 ); 
	LCD_data_tx( 0xC ) ; 
	select_column(text_column + 80 ); 
	LCD_data_tx( 0xC ) ; 
	select_column(text_column + 81 ); 
	LCD_data_tx( 0xD ) ; 
	select_column(text_column + 82 ); 
	LCD_data_tx( 0x9F ) ; 
	select_column(text_column + 83 ); 
	LCD_data_tx( 0x38 ) ; 
	select_column(text_column + 84 ); 
	LCD_data_tx( 0xE0 ) ; 
	select_column(text_column + 85 ); 
	LCD_data_tx( 0x80 ) ; 
	select_column(text_column + 86 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 87 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 88 ); 
	LCD_data_tx( 0x1 ) ; 
	select_column(text_column + 89 ); 
	LCD_data_tx( 0x1F ) ; 
	select_column(text_column + 90 ); 
	LCD_data_tx( 0xFC ) ; 
	select_column(text_column + 91 ); 
	LCD_data_tx( 0x3F ) ; 
	select_column(text_column + 92 ); 
	LCD_data_tx( 0x3 ) ; 
	select_column(text_column + 93 ); 
	LCD_data_tx( 0x3 ) ; 
	select_column(text_column + 94 ); 
	LCD_data_tx( 0x3 ) ; 
	select_column(text_column + 95 ); 
	LCD_data_tx( 0xC3 ) ; 
	select_column(text_column + 96 ); 
	LCD_data_tx( 0xF2 ) ; 
	select_column(text_column + 97 ); 
	LCD_data_tx( 0x3E ) ; 
	select_column(text_column + 98 ); 
	LCD_data_tx( 0xE ) ; 
	select_column(text_column + 99 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 100 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 101 ); 
	LCD_data_tx( 0x0 ) ; 
	select_page(text_page + 4); 
	select_column(text_column + 0 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 1 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 2 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 3 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 4 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 5 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 6 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 7 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 8 ); 
	LCD_data_tx( 0x1 ) ; 
	select_column(text_column + 9 ); 
	LCD_data_tx( 0xF ) ; 
	select_column(text_column + 10 ); 
	LCD_data_tx( 0x3E ) ; 
	select_column(text_column + 11 ); 
	LCD_data_tx( 0xF0 ) ; 
	select_column(text_column + 12 ); 
	LCD_data_tx( 0xC0 ) ; 
	select_column(text_column + 13 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 14 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 15 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 16 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 17 ); 
	LCD_data_tx( 0x10 ) ; 
	select_column(text_column + 18 ); 
	LCD_data_tx( 0x71 ) ; 
	select_column(text_column + 19 ); 
	LCD_data_tx( 0xF8 ) ; 
	select_column(text_column + 20 ); 
	LCD_data_tx( 0xC ) ; 
	select_column(text_column + 21 ); 
	LCD_data_tx( 0xFE ) ; 
	select_column(text_column + 22 ); 
	LCD_data_tx( 0xE7 ) ; 
	select_column(text_column + 23 ); 
	LCD_data_tx( 0x81 ) ; 
	select_column(text_column + 24 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 25 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 26 ); 
	LCD_data_tx( 0x7 ) ; 
	select_column(text_column + 27 ); 
	LCD_data_tx( 0xF ) ; 
	select_column(text_column + 28 ); 
	LCD_data_tx( 0xE ) ; 
	select_column(text_column + 29 ); 
	LCD_data_tx( 0xC ) ; 
	select_column(text_column + 30 ); 
	LCD_data_tx( 0x4 ) ; 
	select_column(text_column + 31 ); 
	LCD_data_tx( 0x83 ) ; 
	select_column(text_column + 32 ); 
	LCD_data_tx( 0xC0 ) ; 
	select_column(text_column + 33 ); 
	LCD_data_tx( 0xE0 ) ; 
	select_column(text_column + 34 ); 
	LCD_data_tx( 0xFF ) ; 
	select_column(text_column + 35 ); 
	LCD_data_tx( 0xF ) ; 
	select_column(text_column + 36 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 37 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 38 ); 
	LCD_data_tx( 0xFE ) ; 
	select_column(text_column + 39 ); 
	LCD_data_tx( 0xFC ) ; 
	select_column(text_column + 40 ); 
	LCD_data_tx( 0x18 ) ; 
	select_column(text_column + 41 ); 
	LCD_data_tx( 0x18 ) ; 
	select_column(text_column + 42 ); 
	LCD_data_tx( 0x30 ) ; 
	select_column(text_column + 43 ); 
	LCD_data_tx( 0x30 ) ; 
	select_column(text_column + 44 ); 
	LCD_data_tx( 0x61 ) ; 
	select_column(text_column + 45 ); 
	LCD_data_tx( 0x63 ) ; 
	select_column(text_column + 46 ); 
	LCD_data_tx( 0xC7 ) ; 
	select_column(text_column + 47 ); 
	LCD_data_tx( 0xCE ) ; 
	select_column(text_column + 48 ); 
	LCD_data_tx( 0x8C ) ; 
	select_column(text_column + 49 ); 
	LCD_data_tx( 0x98 ) ; 
	select_column(text_column + 50 ); 
	LCD_data_tx( 0x10 ) ; 
	select_column(text_column + 51 ); 
	LCD_data_tx( 0xF0 ) ; 
	select_column(text_column + 52 ); 
	LCD_data_tx( 0x10 ) ; 
	select_column(text_column + 53 ); 
	LCD_data_tx( 0x10 ) ; 
	select_column(text_column + 54 ); 
	LCD_data_tx( 0x18 ) ; 
	select_column(text_column + 55 ); 
	LCD_data_tx( 0x8 ) ; 
	select_column(text_column + 56 ); 
	LCD_data_tx( 0xC ) ; 
	select_column(text_column + 57 ); 
	LCD_data_tx( 0x4 ) ; 
	select_column(text_column + 58 ); 
	LCD_data_tx( 0x7E ) ; 
	select_column(text_column + 59 ); 
	LCD_data_tx( 0x7F ) ; 
	select_column(text_column + 60 ); 
	LCD_data_tx( 0x61 ) ; 
	select_column(text_column + 61 ); 
	LCD_data_tx( 0x60 ) ; 
	select_column(text_column + 62 ); 
	LCD_data_tx( 0xC0 ) ; 
	select_column(text_column + 63 ); 
	LCD_data_tx( 0xC0 ) ; 
	select_column(text_column + 64 ); 
	LCD_data_tx( 0xFF ) ; 
	select_column(text_column + 65 ); 
	LCD_data_tx( 0x3C ) ; 
	select_column(text_column + 66 ); 
	LCD_data_tx( 0x68 ) ; 
	select_column(text_column + 67 ); 
	LCD_data_tx( 0x70 ) ; 
	select_column(text_column + 68 ); 
	LCD_data_tx( 0x38 ) ; 
	select_column(text_column + 69 ); 
	LCD_data_tx( 0xFC ) ; 
	select_column(text_column + 70 ); 
	LCD_data_tx( 0x80 ) ; 
	select_column(text_column + 71 ); 
	LCD_data_tx( 0x1F ) ; 
	select_column(text_column + 72 ); 
	LCD_data_tx( 0x37 ) ; 
	select_column(text_column + 73 ); 
	LCD_data_tx( 0x60 ) ; 
	select_column(text_column + 74 ); 
	LCD_data_tx( 0xC0 ) ; 
	select_column(text_column + 75 ); 
	LCD_data_tx( 0xC0 ) ; 
	select_column(text_column + 76 ); 
	LCD_data_tx( 0x80 ) ; 
	select_column(text_column + 77 ); 
	LCD_data_tx( 0x83 ) ; 
	select_column(text_column + 78 ); 
	LCD_data_tx( 0x87 ) ; 
	select_column(text_column + 79 ); 
	LCD_data_tx( 0x87 ) ; 
	select_column(text_column + 80 ); 
	LCD_data_tx( 0xC7 ) ; 
	select_column(text_column + 81 ); 
	LCD_data_tx( 0xC3 ) ; 
	select_column(text_column + 82 ); 
	LCD_data_tx( 0x61 ) ; 
	select_column(text_column + 83 ); 
	LCD_data_tx( 0x38 ) ; 
	select_column(text_column + 84 ); 
	LCD_data_tx( 0xF ) ; 
	select_column(text_column + 85 ); 
	LCD_data_tx( 0x7 ) ; 
	select_column(text_column + 86 ); 
	LCD_data_tx( 0xD0 ) ; 
	select_column(text_column + 87 ); 
	LCD_data_tx( 0xFC ) ; 
	select_column(text_column + 88 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 89 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 90 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 91 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 92 ); 
	LCD_data_tx( 0x80 ) ; 
	select_column(text_column + 93 ); 
	LCD_data_tx( 0xF0 ) ; 
	select_column(text_column + 94 ); 
	LCD_data_tx( 0x7E ) ; 
	select_column(text_column + 95 ); 
	LCD_data_tx( 0xF ) ; 
	select_column(text_column + 96 ); 
	LCD_data_tx( 0x1 ) ; 
	select_column(text_column + 97 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 98 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 99 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 100 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 101 ); 
	LCD_data_tx( 0x0 ) ; 
	select_page(text_page + 5); 
	select_column(text_column + 0 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 1 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 2 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 3 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 4 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 5 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 6 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 7 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 8 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 9 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 10 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 11 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 12 ); 
	LCD_data_tx( 0x3 ) ; 
	select_column(text_column + 13 ); 
	LCD_data_tx( 0x1F ) ; 
	select_column(text_column + 14 ); 
	LCD_data_tx( 0x7E ) ; 
	select_column(text_column + 15 ); 
	LCD_data_tx( 0xF0 ) ; 
	select_column(text_column + 16 ); 
	LCD_data_tx( 0xE0 ) ; 
	select_column(text_column + 17 ); 
	LCD_data_tx( 0x60 ) ; 
	select_column(text_column + 18 ); 
	LCD_data_tx( 0x60 ) ; 
	select_column(text_column + 19 ); 
	LCD_data_tx( 0x63 ) ; 
	select_column(text_column + 20 ); 
	LCD_data_tx( 0x3F ) ; 
	select_column(text_column + 21 ); 
	LCD_data_tx( 0x38 ) ; 
	select_column(text_column + 22 ); 
	LCD_data_tx( 0x1 ) ; 
	select_column(text_column + 23 ); 
	LCD_data_tx( 0x3 ) ; 
	select_column(text_column + 24 ); 
	LCD_data_tx( 0x3 ) ; 
	select_column(text_column + 25 ); 
	LCD_data_tx( 0x7 ) ; 
	select_column(text_column + 26 ); 
	LCD_data_tx( 0x6 ) ; 
	select_column(text_column + 27 ); 
	LCD_data_tx( 0x6 ) ; 
	select_column(text_column + 28 ); 
	LCD_data_tx( 0x6 ) ; 
	select_column(text_column + 29 ); 
	LCD_data_tx( 0x7 ) ; 
	select_column(text_column + 30 ); 
	LCD_data_tx( 0x3 ) ; 
	select_column(text_column + 31 ); 
	LCD_data_tx( 0x1 ) ; 
	select_column(text_column + 32 ); 
	LCD_data_tx( 0x1 ) ; 
	select_column(text_column + 33 ); 
	LCD_data_tx( 0x7 ) ; 
	select_column(text_column + 34 ); 
	LCD_data_tx( 0x7 ) ; 
	select_column(text_column + 35 ); 
	LCD_data_tx( 0x4 ) ; 
	select_column(text_column + 36 ); 
	LCD_data_tx( 0x6 ) ; 
	select_column(text_column + 37 ); 
	LCD_data_tx( 0x6 ) ; 
	select_column(text_column + 38 ); 
	LCD_data_tx( 0x3 ) ; 
	select_column(text_column + 39 ); 
	LCD_data_tx( 0x7 ) ; 
	select_column(text_column + 40 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 41 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 42 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 43 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 44 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 45 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 46 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 47 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 48 ); 
	LCD_data_tx( 0x1 ) ; 
	select_column(text_column + 49 ); 
	LCD_data_tx( 0x1 ) ; 
	select_column(text_column + 50 ); 
	LCD_data_tx( 0x3 ) ; 
	select_column(text_column + 51 ); 
	LCD_data_tx( 0x3 ) ; 
	select_column(text_column + 52 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 53 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 54 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 55 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 56 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 57 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 58 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 59 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 60 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 61 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 62 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 63 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 64 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 65 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 66 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 67 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 68 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 69 ); 
	LCD_data_tx( 0x3 ) ; 
	select_column(text_column + 70 ); 
	LCD_data_tx( 0x3 ) ; 
	select_column(text_column + 71 ); 
	LCD_data_tx( 0x3 ) ; 
	select_column(text_column + 72 ); 
	LCD_data_tx( 0x3 ) ; 
	select_column(text_column + 73 ); 
	LCD_data_tx( 0x6 ) ; 
	select_column(text_column + 74 ); 
	LCD_data_tx( 0x6 ) ; 
	select_column(text_column + 75 ); 
	LCD_data_tx( 0x7 ) ; 
	select_column(text_column + 76 ); 
	LCD_data_tx( 0x7 ) ; 
	select_column(text_column + 77 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 78 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 79 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 80 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 81 ); 
	LCD_data_tx( 0x7 ) ; 
	select_column(text_column + 82 ); 
	LCD_data_tx( 0x6 ) ; 
	select_column(text_column + 83 ); 
	LCD_data_tx( 0x4 ) ; 
	select_column(text_column + 84 ); 
	LCD_data_tx( 0x4 ) ; 
	select_column(text_column + 85 ); 
	LCD_data_tx( 0x4 ) ; 
	select_column(text_column + 86 ); 
	LCD_data_tx( 0x3F ) ; 
	select_column(text_column + 87 ); 
	LCD_data_tx( 0x3F ) ; 
	select_column(text_column + 88 ); 
	LCD_data_tx( 0x20 ) ; 
	select_column(text_column + 89 ); 
	LCD_data_tx( 0x60 ) ; 
	select_column(text_column + 90 ); 
	LCD_data_tx( 0x60 ) ; 
	select_column(text_column + 91 ); 
	LCD_data_tx( 0x7C ) ; 
	select_column(text_column + 92 ); 
	LCD_data_tx( 0x1F ) ; 
	select_column(text_column + 93 ); 
	LCD_data_tx( 0x3 ) ; 
	select_column(text_column + 94 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 95 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 96 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 97 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 98 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 99 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 100 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 101 ); 
	LCD_data_tx( 0x0 ) ;


	select_page(text_page + 6);
	select_column(text_column + 0 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 1 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 2 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 3 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 4 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 5 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 6 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 7 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 8 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 9 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 10 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 11 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 12 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 13 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 14 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 15 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 16 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 17 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 18 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 19 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 20 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 21 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 22 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 23 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 24 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 25 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 26 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 27 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 28 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 29 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 30 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 31 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 32 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 33 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 34 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 35 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 36 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 37 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 38 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 39 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 40 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 41 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 42 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 43 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 44 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 45 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 46 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 47 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 48 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 49 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 50 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 51 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 52 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 53 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 54 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 55 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 56 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 57 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 58 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 59 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 60 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 61 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 62 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 63 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 64 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 65 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 66 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 67 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 68 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 69 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 70 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 71 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 72 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 73 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 74 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 75 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 76 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 77 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 78 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 79 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 80 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 81 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 82 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 83 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 84 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 85 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 86 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 87 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 88 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 89 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 90 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 91 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 92 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 93 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 94 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 95 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 96 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 97 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 98 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 99 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 100 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 101 ); 
	LCD_data_tx( 0x0 ) ; 
	select_page(text_page + 7); 
	select_column(text_column + 0 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 1 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 2 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 3 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 4 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 5 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 6 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 7 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 8 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 9 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 10 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 11 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 12 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 13 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 14 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 15 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 16 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 17 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 18 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 19 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 20 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 21 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 22 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 23 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 24 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 25 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 26 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 27 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 28 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 29 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 30 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 31 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 32 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 33 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 34 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 35 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 36 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 37 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 38 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 39 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 40 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 41 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 42 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 43 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 44 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 45 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 46 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 47 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 48 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 49 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 50 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 51 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 52 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 53 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 54 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 55 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 56 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 57 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 58 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 59 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 60 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 61 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 62 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 63 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 64 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 65 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 66 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 67 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 68 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 69 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 70 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 71 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 72 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 73 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 74 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 75 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 76 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 77 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 78 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 79 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 80 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 81 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 82 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 83 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 84 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 85 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 86 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 87 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 88 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 89 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 90 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 91 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 92 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 93 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 94 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 95 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 96 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 97 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 98 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 99 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 100 ); 
	LCD_data_tx( 0x0 ) ; 
	select_column(text_column + 101 ); 
	LCD_data_tx( 0x0 ) ; 

	return(TRUE);
}

*/


