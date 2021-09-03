#include "game_console.h"


void SPI_initialise(void)
{
	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0)|(1<<CPOL)|(1<<CPHA);

	//initialization indicator, two blinks
	BAT_LOW_LED(ON);
	_delay_ms(255);
	BAT_LOW_LED(OFF);
	_delay_ms(120);
	BAT_LOW_LED(ON);
	_delay_ms(255);
	BAT_LOW_LED(OFF);
	_delay_ms(255);
	_delay_ms(255);
}
