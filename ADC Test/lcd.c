#include "game_console.h"



byte LCD_send(byte cData)
{
    // Start transmission
    SPDR = cData;
    // Wait for transmission complete
    while (!(SPSR & (1<<SPIF))) {
		//BAT_LOW_LED(ON);
		//_delay_ms(255);
		//BAT_LOW_LED(OFF);
		//_delay_ms(255);
    };
	return SPDR;
}


/*
byte LCD_command_tx(byte tx_byte) //Sends a command byte
{
	byte tx_processed;
	byte tx_mask = 0x80;
	LCD_CHIP_SELECT(LCD_CS);
	LCD_CD_SET(LCD_CD, ON);
	while (tx_mask != 0x00)
	{
		tx_processed = tx_byte & tx_mask;
		SCK_SET_HIGH;
		if(tx_processed)
			MOSI_SET_HIGH;
		else
			MOSI_SET_LOW;
		SCK_SET_LOW;
		tx_mask>>=1;
	}
	SCK_SET_HIGH;
	LCD_CHIP_DESELECT(LCD_CS);
	return(TRUE);
}
*/

byte LCD_command_tx(byte tx_byte) //Sends a command byte
{
	LCD_CHIP_SELECT;
	LCD_CD_SET(COMMAND);
	LCD_send(tx_byte);
	LCD_CHIP_DESELECT;
	return(TRUE);
}

/*
byte LCD_data_tx(byte tx_byte) //Sends a data byte
{
	byte tx_processed;
	byte tx_mask = 0x80;
	LCD_CHIP_SELECT(LCD_CS);
	LCD_CD_SET(LCD_CD, OFF);
	while (tx_mask != 0x00)
	{
		tx_processed = tx_byte & tx_mask;
		SCK_SET_HIGH;
		if(tx_processed)
			MOSI_SET_HIGH;
		else
			MOSI_SET_LOW;
		SCK_SET_LOW;
		tx_mask>>=1;
	}
	SCK_SET_HIGH;
	LCD_CHIP_DESELECT(LCD_CS);
	return(TRUE);
}
*/

byte LCD_data_tx(byte tx_byte) //Sends a data byte
{
	LCD_CHIP_SELECT;
	LCD_CD_SET(DATA);
	LCD_send(tx_byte);
	LCD_CHIP_DESELECT;
	return(TRUE);
}


byte select_page (byte page)
{
	if (page > MAX_PAGES)
		page = MAX_PAGES-1;//if page selected beyound limit set to last page
	if (page < 0)
		page = 0;//if page selected is negtive set to first page
	byte page_cmd_address;
	page_cmd_address = (CMD_PAGE | page);
	LCD_command_tx(page_cmd_address);
	return(TRUE);
}

byte select_column (byte column)
{
	if (column > MAX_COLUMNS)
		column = MAX_COLUMNS-1;
	if (column < 0)
		column = 0;
	byte page_cmd_address_MSB;
	byte page_cmd_address_LSB;
	page_cmd_address_LSB = (CMD_COL_LSB | (column&0x0F));
	page_cmd_address_MSB = (CMD_COL_MSB | (column >> 4));
	LCD_command_tx(page_cmd_address_LSB);
	LCD_command_tx(page_cmd_address_MSB);
	return(TRUE);
}

byte LCD_initialise(void)
{
	LCD_RST_INI(HIGH);
	_delay_ms(20);
	LCD_RST_INI(LOW);
	_delay_ms(20);
	LCD_RST_INI(HIGH);
	_delay_ms(20);

	LCD_command_tx(0x40);//Display start line 0
	LCD_command_tx(0xA1);//SEG reverse(A1)SEG131~SEG0,normal(A0)
	LCD_command_tx(0xC0);//Normal COM0~COM63
	LCD_command_tx(0xA4);//Disable -> Set All Pixel to ON
	LCD_command_tx(0xA6);//Display inverse off(A6),inverse(A7)
	_delay_ms(120);
	LCD_command_tx(0xA2);//Set LCD Bias Ratio A2/A3
	LCD_command_tx(0x2F);//Set Power Control 28...2F
	LCD_command_tx(0x27);//Set VLCD Resistor Ratio 20...27
	LCD_command_tx(0x81);//Set Electronic Volume
	LCD_command_tx(0x10);//Set Electronic Volume 00...3F
	LCD_command_tx(0xFA);//Set Adv. Program Control
	LCD_command_tx(0x90);//Set Adv. Program Control x00100yz yz column wrap x Temp Comp
	LCD_command_tx(0xAF);//Display on

	//initialization indicator, one blink
	BAT_LOW_LED(ON);
	_delay_ms(255);
	BAT_LOW_LED(OFF);

	return(TRUE);
}

byte LCD_clear(void)
{	
	byte page, column;
	for (page = 0; page <= MAX_PAGES; page++)
	{
		for (column = 0; column < MAX_COLUMNS; column++)
		{
			select_page(page);
			select_column(column);
			LCD_data_tx(0x00);
		}
	}
	return(TRUE);
}

byte LCD_fill(void)
{	
	byte page, column;
	for (page = 0; page <= MAX_PAGES; page++)
	{
		for (column = 0; column < MAX_COLUMNS; column++)
		{
			select_page(page);
			select_column(column);
			LCD_data_tx(0xFF);
		}
	}
	return(TRUE);
}

byte LCD_buffer_clear(byte buffer[MAX_COLUMNS][MAX_PAGES])
{
	byte page, column;
	for (page = 0; page <= MAX_PAGES; page++)
	{
		for (column = 0; column < MAX_COLUMNS; column++)
		{
			buffer[column][page] = OFF;
		}
	}
	return(TRUE);
}
