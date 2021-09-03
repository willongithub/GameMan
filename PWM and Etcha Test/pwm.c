#include "game_console.h"


void PWM_initialise(void)
{
  PWM0_SET_OUTPUT;
  PWM0_SET_FOC(LOW);
  PWM0_SET_MODE(FAST_PWM);
  PWM0_SET_COMPARE_OUT(COM_SET);
  PWM0_SET_CLOCK(CLK_IO);
  DUTY_CICRLE=200;
}
