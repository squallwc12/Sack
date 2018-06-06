#include "msp430x54x.h"
#include "bsp.h"

void Init_PWM_TA1(void)
{
  P2SEL |= BIT2 + BIT3; //TA1 CH1
  P2DIR |= BIT2 + BIT3; //TA1 CH2
  
  //Period = (Frequency / TA1CCR0) Hz Frequency = TA1CTL[TASSEL_x]
  TA1CCR0  = 0x0200;
  
  //Outputmode
  TA1CCTL1 = OUTMOD_7;
  //Dutycycle = (TA1CCR1 / TA1CCR0) * 100%
  TA1CCR1  = 0x0100;
  
  TA1CCTL2 = OUTMOD_3;
  TA1CCR2  = 0x0100;

  TA1CTL   = 0;
  TA1CTL  |= MC_1;
  //TASSEL_1 aclk (32.768kHz)
  //TASSEL_2 sclk (21.2992 MHz)
  //ID_0 frequency division 
  TA1CTL  |= TASSEL_1 + ID_0 + TACLR;
}
