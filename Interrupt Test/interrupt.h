#ifndef INTERRUPT_H_
#define INTERRUPT_H_


//#define F_CPU 4000000UL
#define BUTTON_INTERRUPT_DIR(DIR) SET(DDRD,_BV(PD2),DIR)
#define BUTTON_INTERRUPT_INI(STATE) SET(PORTD,_BV(PD2),STATE)


void INTERRUPT_initialise(void);
ISR(INT0_vect)；

#endif
