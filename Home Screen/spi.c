#include "game_console.h"


byte SPI_initialise(void)
{
	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0)|(1<<CPOL)|(1<<CPHA);

	//initialization indicator, two blinks
	_delay_ms(255);
	_delay_ms(255);
	BAT_LOW_LED(ON);
	_delay_ms(255);
	BAT_LOW_LED(OFF);
	_delay_ms(155);
	BAT_LOW_LED(ON);
	_delay_ms(255);
	BAT_LOW_LED(OFF);
	_delay_ms(255);
	_delay_ms(255);

	return(TRUE);
}

byte SPI_send(byte cData)
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
	return(SPDR);
}
