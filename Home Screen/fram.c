#include "game_console.h"

/*
byte FRAM_initialise(void)
{
	RAM_CS_DIR(OUT);
	RAM_WP_DIR(OUT);
	RAM_HOLD_DIR(OUT);

	RAM_CS_SET(HIGH);
	RAM_WP_SET(HIGH);
	RAM_HOLD_SET(HIGH);

	return(TRUE);
}

byte FRAM_write(byte data)
{
	byte address = 0x11;
	FRAM_CS_ACT;
	SPI_send(WREN);
	FRAM_CS_DEACT;
	_delay_ms(155);
	FRAM_CS_ACT;
	SPI_send(WRITE_UPPER);
	SPI_send(address);
	SPI_send(data);
	FRAM_CS_DEACT;
	return(TRUE);
}

byte FRAM_read(void)
{
	byte address = 0x11;
	FRAM_CS_ACT;
	SPI_send(READ_UPPER);
	SPI_send(address);
	SPI_send(0xFF);
	byte data = SPDR;
	FRAM_CS_DEACT;
	return(data);
}
*/