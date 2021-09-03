#ifndef LCD_H_
#define LCD_H_


#define CMD_PAGE 0xB0
#define CMD_COL_LSB 0x00
#define CMD_COL_MSB 0x10
#define BACK 0xFF
#define COMMAND 0x00
#define DATA 0xFF
#define LCD_CS PA7
#define LCD_RST PA6
#define LCD_CD PA5
#define MAX_PAGES 7
#define MAX_COLUMNS 102

#define byte unsigned char



byte LCD_command_tx(byte tx_byte); //Sends a command byte

byte LCD_data_tx(byte tx_byte); //Sends a data byte

byte select_page (byte page);

byte select_column (byte column);

byte LCD_initialise(void);

byte LCD_send(byte cData);

byte LCD_clear(void);

byte LCD_fill(void);

byte LCD_buffer_clear(byte buffer[MAX_COLUMNS][MAX_PAGES]);

#endif
