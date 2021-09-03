/*************************************************************************
Title:    Game Console Template Header File
Inital Author:   David Jahshan
Extended by : (PUT YOUR NAME HERE) (PUT YOUR STUDENT NUMBER HERE) 
Software: AVR-GCC 
Hardware: ATMEGA16 @ 8Mhz 

DESCRIPTION:
	Macros for Game Console

*************************************************************************/

#include <avr/io.h> 
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#define byte unsigned char 

/*ON OFF*/
#define ON 0xFF
#define OFF 0x00
#define HIGH 0xFF
#define LOW 0x00
#define IN 0x00
#define OUT 0xFF
#define ALL 0xFF
#define TRUE 1
#define FALSE 0
#define FORWARD 0x00
#define BACK 0xFF

#define PULLUP 0xFF

/*SET and GET MACRO*/
#define SET(PORT,MASK,VALUE) PORT = ((MASK & VALUE) | (PORT & ~MASK))
#define GET(PORT,MASK) PORT & MASK

//Devices Direction MACROs
//#define MULTI_LINES_DIR(DIR) SET(DDR?,(_BV(P?#)|_BV(P?#)|_BV(P?#)),DIR)

#define BAT_LOW_LED_DIR(DIR) SET(DDRA,_BV(PA4),DIR)
#define UP_BUTTON_DIR(DIR) SET(DDRC,_BV(PC0),DIR)
#define DOWN_BUTTON_DIR(DIR) SET(DDRD,_BV(PD7),DIR)
#define RIGHT_BUTTON_DIR(DIR) SET(DDRD,_BV(PD6),DIR)
#define LEFT_BUTTON_DIR(DIR) SET(DDRC,_BV(PC1),DIR)
#define A_BUTTON_DIR(DIR) SET(DDRD,_BV(PD3),DIR)
#define B_BUTTON_DIR(DIR) SET(DDRD,_BV(PD4),DIR)
#define C_BUTTON_DIR(DIR) SET(DDRD,_BV(PD5),DIR)


//Devices Outputs
//#define MULTI_LINES(STATE) SET(DDR?,(_BV(P?#)|_BV(P?#)|_BV(P?#)),DIR)

#define BAT_LOW_LED(STATE) SET(PORTA,_BV(PA4),~STATE)
#define UP_BUTTON_INI(STATE) SET(PORTC,_BV(PC0),STATE)
#define DOWN_BUTTON_INI(STATE) SET(PORTD,_BV(PD7),STATE)
#define RIGHT_BUTTON_INI(STATE) SET(PORTD,_BV(PD6),STATE)
#define LEFT_BUTTON_INI(STATE) SET(PORTC,_BV(PC1),STATE)
#define A_BUTTON_INI(STATE) SET(PORTD,_BV(PD3),STATE)
#define B_BUTTON_INI(STATE) SET(PORTD,_BV(PD4),STATE)
#define C_BUTTON_INI(STATE) SET(PORTD,_BV(PD5),STATE)


//Devices Inputs
#define UP_BUTTON GET(PINC,_BV(PC0))
#define DOWN_BUTTON GET(PIND,_BV(PD7))
#define RIGHT_BUTTON GET(PIND,_BV(PD6))
#define LEFT_BUTTON GET(PINC,_BV(PC1))
#define A_BUTTON GET(PIND,_BV(PD3))
#define B_BUTTON GET(PIND,_BV(PD4))
#define C_BUTTON GET(PIND,_BV(PD5))



