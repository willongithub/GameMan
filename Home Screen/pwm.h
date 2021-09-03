#ifndef PWM_H_
#define PWM_H_

#define byte unsigned char

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

#define PWM0_SET_OUTPUT SET(DDRB,_BV(PB3),OUT)
#define PWM0_SET_FOC(STATE) SET(TCCR0,_BV(FOC0),STATE)
#define PWM0_SET_MODE(STATE) SET(TCCR0,(_BV(WGM01) | _BV(WGM00)),STATE)
#define PWM0_SET_COMPARE_OUT(STATE) SET(TCCR0,(_BV(COM01) | _BV(COM00)),STATE)
#define PWM0_SET_CLOCK(STATE) SET(TCCR0,(_BV(CS02) | _BV(CS01) | _BV(CS00)),STATE)



void PWM_initialise(void);

#endif

//----------------- EOF pwm.h ------------