#include "msp430x54x.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "bsp.h"
#include "PIN_DEF.h"

//***************************************************************************//
//                                                                           //
//  Init_UART(void): ��ʼ��USB�˿�                                           //
//                                                                           //
//***************************************************************************//
void Init_UART_RS232(void)
{ 
  RS_PORT_SEL     |= TXD + RXD;  // ѡ�����Ź���
  RS_PORT_DIR     |= TXD;          // ѡ�����Ź���
  
  UCA3CTL1         = UCSWRST;        // ״̬����λ
  UCA3CTL1        |= UCSSEL_2;       // CLK = ACLK
  UCA3CTL0        |= UCMODE_0;	    // ѡ�񴮿ڹ���
  UCA3CTL0        &= ~UC7BIT;	    // 8λ����
  UCA3BR0          = 0xB8;           // (32768*650)kHz/115200=184.89 
  UCA3BR1          = 0x00; 
  UCA3MCTL         = UCBRF_15 + UCBRS_7;

  UCA3CTL1        &= ~UCSWRST;       // ����״̬��
  UCA3IE          |= UCRXIE;         // ��������ж�
}
//***************************************************************************//
//                                                                           //
//  UTX_PROC(void): USB�˿ڷ��ͳ���                                          //
//                                                                           //
//***************************************************************************//
void TX_PROC(char *tx_buf)
{
  unsigned char i,length                                           ;
  length = strlen(tx_buf)                                          ;
  for(i=0;i<length;i++)
  {
    UCA3TXBUF = *tx_buf++                                          ; 
    while (!(UCA3IFG&UCTXIFG))                                     ; 
  }
}

//***************************************************************************//
//                                                                           //
//  USB�����жϷ������                                                      //
//                                                                           //
//***************************************************************************//
#pragma vector=USCI_A3_VECTOR
__interrupt void USCI_A3_ISR(void)
{
  switch(__even_in_range(UCA3IV,4))
  {
  case 0:break                                                     ; // Vector 0 - no interrupt
  case 2:                                                            // Vector 2 - RXIFG
      //RXBuffer[0]      = UCA3RXBUF                                 ;
      //event           |= 0x01                                      ;
      break                                                        ;
  case 4:break                                                     ;  // Vector 4 - TXIFG
  default: break                                                   ;  
  }  
}
