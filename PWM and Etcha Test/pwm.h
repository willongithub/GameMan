#ifndef _PWM_H
#define _PWM_H

// PWM
#define NORMAL 0x00
#define PHASE_CORRECT 0x40
#define CTC 0x08
#define FAST_PWM 0xFF
#define COM_NORMAL 0x00
#define COM_RESERVED 0x10
#define COM_CLEAR 0x20
#define COM_SET 0xFF
#define NO_CLK 0x00
#define CLK_IO 0x01
#define CLK8_IO
#define CLK64_IO
#define CLK256_IO
#define CLK1024_IO
#define DUTY_CICRLE OCR0

#define byte unsigned char



void PWM_initialise(void);

#endif
