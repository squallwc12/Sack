#include "msp430x54x.h"
#include "bsp.h"

#define CLEAR_NUMBER          do{P8OUT = 0xFF;}while(0)

unsigned char Digitron_Number[] = {0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90};
unsigned long Digitron_usv;

void Init_Digitron(void)
{
  P1SEL &=~(BIT4 | BIT5 | BIT6 | BIT7);
  P1DIR |= (BIT4 | BIT5 | BIT6 | BIT7);
  P1OUT &=~(BIT4 | BIT5 | BIT6 | BIT7);
  
  P9SEL &=~(BIT0 | BIT1 | BIT2 | BIT3);
  P9DIR |= (BIT0 | BIT1 | BIT2 | BIT3);
  P9OUT &=~(BIT0 | BIT1 | BIT2 | BIT3);
  
  P8SEL  = 0x00;
  P8DIR  = 0xFF;
  CLEAR_NUMBER;
}

void Digitron_print_number(unsigned char number)
{
  P8OUT = Digitron_Number[number%10];
}

void Digitron_print_Digit(unsigned char digit)
{
    P1OUT |= 0xF0;
    P9OUT |= 0x0F;
    
    switch(digit%8){
    case 0:
      P1OUT &=~BIT7;
      break;
    case 1:
      P1OUT &=~BIT6;
      break;
    case 2:
      P1OUT &=~BIT5;
      break;
    case 3:
      P1OUT &=~BIT4;
      break;
    case 4:
      P9OUT &=~BIT3;
      break;
    case 5:
      P9OUT &=~BIT2;
      break;
    case 6:
      P9OUT &=~BIT1;
      break;
    case 7:
      P9OUT &=~BIT0;
      break;
    }
}

void Digitron_print_uDEC(unsigned long number)
{
  Digitron_usv = number;
}

void Digitron_scan(void)
{
  static unsigned char scani = 0;
  static unsigned char Luminance = 0;
  
  unsigned long Dnumber;
  unsigned char i;
  
  if( scani == 0 ){
    Luminance = (Luminance + 1)%2;
  }
  
  CLEAR_NUMBER;
  
  if(Luminance >= 1){
    Digitron_print_Digit(scani);
    
    for(i=0, Dnumber = Digitron_usv; i<scani; i++)
    {
      Dnumber /= 10;
    }
    
    Digitron_print_number(Dnumber%10);
  }
  
  scani = (scani + 1)%8;
}
