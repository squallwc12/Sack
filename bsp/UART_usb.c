#include "msp430x54x.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "bsp.h"
#include "PIN_DEF.h"

char  event, RXBuffer[2];
//***************************************************************************//
//                                                                           //
//  Init_UART(void): 初始化USB端口                                           //
//                                                                           //
//***************************************************************************//
void Init_UART(void)
{ 
  USB_PORT_SEL   |= TXD_U + RXD_U;  // 选择引脚功能
  USB_PORT_DIR   |= TXD_U;          // 选择引脚功能
  
  UCA1CTL1        = UCSWRST;        // 状态机复位
  UCA1CTL1       |= UCSSEL_2;       // CLK = ACLK
  UCA1CTL0       |= UCMODE_0;	    // 选择串口功能
  UCA1CTL0       &= ~UC7BIT;	    // 8位数据
  UCA1BR0         = 0xB8;           // (32768*650)kHz/115200=184.89 
  UCA1BR1         = 0x00; 
  UCA1MCTL        = UCBRF_15 + UCBRS_7;

  UCA1CTL1       &= ~UCSWRST;       // 启动状态机
  UCA1IE         |= UCRXIE;         // 允许接收中断
}

//***************************************************************************//
//                                                                           //
//  UTX_PROC(void): USB端口发送程序                                          //
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
//  重定向printf函数                                                         //
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
//  USB接收中断服务程序                                                      //
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