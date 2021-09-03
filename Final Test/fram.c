#include "game_console.h"


byte FRAM_initialise(void)
{
	RAM_CS_DIR(OUT);
	RAM_WP_DIR(OUT);
	RAM_HOLD_DIR(OUT);

	RAM_CS_SET(HIGH);
	RAM_WP_SET(HIGH);
	RAM_HOLD_SET(HIGH);

	//reset status register
	FRAM_CS_ACT;
	//_delay_ms(155);
	SPI_send(WREN);
	FRAM_CS_DEACT;
	_delay_ms(155);
	FRAM_CS_ACT;
	//_delay_ms(155);
	SPI_send(WRSR);
	SPI_send(0x00);
	FRAM_CS_DEACT;
	return(TRUE);
}

/*
byte FRAM_write(byte data)
{
	byte address_h = 0x00;
	byte address_l = 0x00;

	FRAM_CS_ACT;
	//_delay_ms(155);
	SPI_send(WREN);
	FRAM_CS_DEACT;
	_delay_ms(155);
	FRAM_CS_ACT;
	//_delay_ms(155);
	SPI_send(WRITE);
	SPI_send(address_h);
	SPI_send(address_l);
	SPI_send(data);
	FRAM_CS_DEACT;
	return(TRUE);
}

byte FRAM_read(void)
{
	byte address_h = 0x00;
	byte address_l = 0x00;
	byte data;

	FRAM_CS_ACT;
	//_delay_ms(155);
	SPI_send(READ);
	SPI_send(address_h);
	SPI_send(address_l);
	SPI_send(0xFF); //dummy data
	FRAM_CS_DEACT;
	
	data = SPDR;
	return data;
}
*/
