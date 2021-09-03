#ifndef _SPI_H
#define _SPI_H

//#define SPI_ENABLE (_BV(SPIE)|_BV(SPE))
#define SPCR_SPIE 7
#define SPCR_SPE  6
#define SPCR_DORD 5
#define SPCR_MSTR 4
#define SPCR_CPOL 3
#define SPCR_CPHA 2
#define SPCR_SPR1 2
#define SPCR_SPR0 0

#define DDR_SPI DDRB
#define DD_MOSI DDB5
#define DD_SCK DDB7

#define byte unsigned char

void SPI_initialise(void);

#endif
