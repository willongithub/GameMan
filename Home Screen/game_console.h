/*************************************************************************
Title:    Game Console Template Header File
Inital Author:   David Jahshan
Extended by : (SIQI WU) (750892) 
Software: AVR-GCC 
Hardware: ATMEGA16 @ 8Mhz 

DESCRIPTION:
	Macros for Game Console

*************************************************************************/
#ifndef GAME_CONSOLE_H_
#define GAME_CONSOLE_H_


#include <avr/io.h> 
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

#include "lcd.h"
#include "spi.h"
#include "pwm.h"
#include "adc.h"
#include "interrupt.h"
#include "fram.h"

#define byte unsigned char

#define infinite_loop 1

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


//byte frame_buffer[MAX_COLUMNS][MAX_PAGES];


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





#define LCD_CS_DIR(DIR) SET(DDRA,_BV(PA7),DIR)
#define LCD_CD_DIR(DIR) SET(DDRA,_BV(PA5),DIR)
#define LCD_RST_DIR(DIR) SET(DDRA,_BV(PA6),DIR)
#define RAM_CS_DIR(DIR) SET(DDRA,_BV(PA0),DIR)
#define RAM_WP_DIR(DIR) SET(DDRA,_BV(PA1),DIR)
#define RAM_HOLD_DIR(DIR) SET(DDRA,_BV(PA2),DIR)
#define SCK_DIR(DIR) SET(DDRB,_BV(PB7),DIR)
#define MOSI_DIR(DIR) SET(DDRB,_BV(PB5),DIR)
#define MISO_DIR(DIR) SET(DDRB,_BV(PB6),DIR)

#define BAT_SEN_DIR(DIR) SET(DDRA,_BV(PA3),DIR)

#define BACKLIGHT_DIR(DIR) SET(DDRB,_BV(PB3),DIR)

#define MCU_SS_DIR(DIR) SET(DDRB,_BV(PB4),DIR)

//#define BUTTON_INTERRUPT_DIR(DIR) 

//Devices Outputs
//#define MULTI_LINES(STATE) SET(DDR?,(_BV(P?#)|_BV(P?#)|_BV(P?#)),DIR)
#define BAT_LOW_LED(STATE) SET(PORTA,_BV(PA4),~STATE)
#define UP_BUTTON_SET(STATE) SET(PORTC,_BV(PC0),STATE)
#define DOWN_BUTTON_SET(STATE) SET(PORTD,_BV(PD7),STATE)
#define RIGHT_BUTTON_SET(STATE) SET(PORTD,_BV(PD6),STATE)
#define LEFT_BUTTON_SET(STATE) SET(PORTC,_BV(PC1),STATE)
#define A_BUTTON_SET(STATE) SET(PORTD,_BV(PD3),STATE)
#define B_BUTTON_SET(STATE) SET(PORTD,_BV(PD4),STATE)
#define C_BUTTON_SET(STATE) SET(PORTD,_BV(PD5),STATE)

#define LCD_CS_SET(STATE) SET(PORTA,_BV(PA7),STATE)
#define LCD_CD_SET(STATE) SET(PORTA,_BV(PA5),STATE)
#define LCD_RST_SET(STATE) SET(PORTA,_BV(PA6),STATE)
#define MCU_SS_SET(STATE) SET(PORTB,_BV(PB4),STATE)

#define RAM_CS_SET(STATE) SET(PORTA,_BV(PA0),STATE)
#define RAM_WP_SET(STATE) SET(PORTA,_BV(PA1),STATE)
#define RAM_HOLD_SET(STATE) SET(PORTA,_BV(PA2),STATE)

//#define SCK_SET_HIGH SET(PORTB,_BV(PB7),HIGH)
//#define SCK_SET_LOW SET(PORTB,_BV(PB7),LOW)
//#define MOSI_SET_HIGH SET(PORTB,_BV(PB5),HIGH)
//#define MOSI_SET_LOW SET(PORTB,_BV(PB5),LOW)

#define LCD_CHIP_SELECT SET(PORTA,_BV(PA7),LOW)
#define LCD_CHIP_DESELECT SET(PORTA,_BV(PA7),HIGH)
#define LCD_CD_SET(STATE) SET(PORTA,_BV(PA5),STATE)

#define BACKLIGHT_SET_LIGHTUP SET(PORTB,_BV(PB3),HIGH)

//Devices Inputs
#define UP_BUTTON GET(PINC,_BV(PC0))
#define DOWN_BUTTON GET(PIND,_BV(PD7))
#define RIGHT_BUTTON GET(PIND,_BV(PD6))
#define LEFT_BUTTON GET(PINC,_BV(PC1))
#define A_BUTTON GET(PIND,_BV(PD3))
#define B_BUTTON GET(PIND,_BV(PD4))
#define C_BUTTON GET(PIND,_BV(PD5))

/*
//Game_1_pingpong
byte pingpong(byte buffer[][MAX_PAGES]);
byte pad_move(byte column, byte buffer[][MAX_PAGES], byte dir);
//byte pad_move_v(byte row, byte buffer[][MAX_PAGES], byte dir);
byte ball_move(byte column, byte row, byte buffer[][MAX_PAGES]);
byte ball_clear(byte column, byte row, byte buffer[][MAX_PAGES]);


//Game_2_tictactoe
#define BOARDSIZE 3
#define X 0xAA
#define O 0x55
byte tictactoe(byte buffer[][MAX_PAGES]);
byte gameboard_draw(byte buffer[][MAX_PAGES]);
byte gamestate_draw(byte board[BOARDSIZE][BOARDSIZE]);
byte ai_move(byte board[BOARDSIZE][BOARDSIZE]);
byte human_move(byte board[BOARDSIZE][BOARDSIZE]);
byte move_show(byte x_axis, byte y_axis);
byte get_result(byte board[BOARDSIZE][BOARDSIZE]);
byte write_x(byte x_axis, byte y_axis);
byte write_o(byte x_axis, byte y_axis);
byte clear_pointer(byte x_axis, byte y_axis);
byte show_pointer(byte text_page , byte text_column);


/*
byte write_0(byte text_page , byte text_column);
byte write_1(byte text_page , byte text_column);


byte write_zero(byte text_page , byte text_column);
byte write_one(byte text_page , byte text_column);
byte write_two(byte text_page , byte text_column);
byte write_three(byte text_page , byte text_column);
byte write_four(byte text_page , byte text_column);
byte write_five(byte text_page , byte text_column);
byte write_six(byte text_page , byte text_column);
byte write_seven(byte text_page , byte text_column);
byte write_eight(byte text_page , byte text_column);
byte write_nine(byte text_page , byte text_column);
byte write_v(byte text_page , byte text_column);
*/

byte write_homescreen(void);

#endif

//----------------- EOF game_console.h ------------


