/*************************************************************************
Title:    ESD Student's GameConsole Pins Discription
Author:   Sahil
Software: AVR-GCC 
Hardware: ATMEGA16 @ 8Mhz 
Website: SahilKhanna.org

DESCRIPTION:
	Macros for ESD Student's GameConsole Pins Discription

*************************************************************************/

#define BAT_LOW_LED_DIR(DIR) SET(DDRA,_BV(PA4),DIR)
//----------Defining BAT LOW LED PIN-----------------------------
#define BAT_LOW_LED(STATE) SET(PORTA,_BV(PA4),~STATE)


//----------Defining LCD PINS-----------------------------
#define LCD_DATA_COMMAND(STATE) SET(PORTA,_BV(PA5),STATE)
#define LCD_CS0(STATE) SET(PORTA,_BV(PA7),~STATE)
#define LCD_BACKLIGHT(STATE) SET(PORTB,_BV(PB3),STATE)
#define LCD_RESET(STATE) SET(PORTA,_BV(PA6),~STATE)
#define LCD_MOSI(STATE) SET(PORTB,_BV(PB5),STATE)
#define LCD_SCK(STATE) SET(PORTB,_BV(PB7),STATE)

//----------------LCD Direction MACROs--------------------
#define LCD_DATA_COMMAND_DIR(DIR) SET(DDRA,_BV(PA5),DIR)
#define LCD_CS0_DIR(DIR) SET(DDRA,_BV(PA7),DIR)
#define LCD_BACKLIGHT_DIR(DIR) SET(DDRB,_BV(PB3),DIR)
#define LCD_RESET_DIR(DIR) SET(DDRA,_BV(PA6),DIR)
#define LCD_MOSI_DIR(DIR) SET(DDRB,_BV(PB5),DIR)
#define LCD_SCK_DIR(DIR) SET(DDRB,_BV(PB7),DIR)

