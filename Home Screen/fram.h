#ifndef FRAM_H_
#define FRAM_H_

/*
#define RAM_CS PA0
#define RAM_WP PA1
#define RAM_HOLD PA2

//#define WREN 0x06
//#define WRITE 0x02
//#define READ 0x03
//#define RDSR 0x05
//#define WRSR 0x01
//#define WRDI 0x04

#define byte unsigned char

#define WREN 0x06
#define WRITE_LOWER 0x02 // Write opcode to access lower half of memory
#define WRITE_UPPER 0x0A // Write opcode to access upper half of memory
#define READ_LOWER 0x03 // Read opcode to access lower half of memory
#define READ_UPPER 0x0B // Read opcode to access upper half of memory
#define RDSR 0x05
#define WRSR 0x01
#define WRDI 0x04

#define FRAM_CS_ACT SET(PORTA,_BV(RAM_CS),LOW)
#define FRAM_CS_DEACT SET(PORTA,_BV(RAM_CS),HIGH)

byte FRAM_initialise(void);
byte FRAM_write(byte data);
//byte FRAM_write_singlebyte(byte address);
byte FRAM_read(void);
//byte FRAM_read_singlebyte(byte address);
//byte FRAM_write_statusRegister(byte setting);
//byte FRAM_read_statusRegister();
*/

#endif

//----------------- EOF fram.h ------------