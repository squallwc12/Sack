#include "msp430x54x.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "bsp.h"
#include "PIN_DEF.h"

char  event, RXBuffer[2];
//***************************************************************************//
//                                                                           //
//  Init_UART(void): ��ʼ��USB�˿�                                           //
//                                                                           //
//***************************************************************************//
void Init_UART(void)
{ 
  USB_PORT_SEL   |= TXD_U + RXD_U;  // ѡ�����Ź���
  USB_PORT_DIR   |= TXD_U;          // ѡ�����Ź���
  
  UCA1CTL1        = UCSWRST;        // ״̬����λ
  UCA1CTL1       |= UCSSEL_2;       // CLK = ACLK
  UCA1CTL0       |= UCMODE_0;	    // ѡ�񴮿ڹ���
  UCA1CTL0       &= ~UC7BIT;	    // 8λ����
  UCA1BR0         = 0xB8;           // (32768*650)kHz/115200=184.89 
  UCA1BR1         = 0x00; 
  UCA1MCTL        = UCBRF_15 + UCBRS_7;

  UCA1CTL1       &= ~UCSWRST;       // ����״̬��
  UCA1IE         |= UCRXIE;         // ��������ж�
}

//***************************************************************************//
//                                                                           //
//  UTX_PROC(void): USB�˿ڷ��ͳ���                                          //
//                                                                           //
//***************************************************************************//
void UTX_PROC(char *tx_buf)
{
  unsigned char i,length                                           ;
  length = strlen(tx_buf)                                          ;
  for(i=0;i<length;i++)
  {
    UCA1TXBUF = *tx_buf++                                          ; 
    while (!(UCA1IFG&UCTXIFG))                                     ; 
  }
}

//***************************************************************************//
//                                                                           //
//  �ض���printf����                                                         //
//                                                                           //
//***************************************************************************//
int putchar(int ch)
{
  UCA1TXBUF = (char)ch;
  while (!(UCA1IFG & UCTXIFG));
  return ch;
}

//***************************************************************************//
//                                                                           //
//  USB�����жϷ������                                                      //
//                                                                           //
//***************************************************************************//
#pragma vector=USCI_A1_VECTOR
__interrupt void USCI_A1_ISR(void)
{
  switch(__even_in_range(UCA1IV,4))
  {
  case 0:break                                                     ; // Vector 0 - no interrupt
  case 2:                                                            // Vector 2 - RXIFG
      RXBuffer[0]      = UCA1RXBUF                                 ;
      event           |= 0x01                                      ;
      break                                                        ;
  case 4:break                                                     ;  // Vector 4 - TXIFG
  default: break                                                   ;  
  }  
}