#include "msp430x54x.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "bsp.h"
#include "PIN_DEF.h"

//***************************************************************************//
//                                                                           //
//  Init_UART(void): 初始化USB端口                                           //
//                                                                           //
//***************************************************************************//
void Init_UART_RS232(void)
{ 
  RS_PORT_SEL     |= TXD + RXD;  // 选择引脚功能
  RS_PORT_DIR     |= TXD;          // 选择引脚功能
  
  UCA3CTL1         = UCSWRST;        // 状态机复位
  UCA3CTL1        |= UCSSEL_2;       // CLK = ACLK
  UCA3CTL0        |= UCMODE_0;	    // 选择串口功能
  UCA3CTL0        &= ~UC7BIT;	    // 8位数据
  UCA3BR0          = 0xB8;           // (32768*650)kHz/115200=184.89 
  UCA3BR1          = 0x00; 
  UCA3MCTL         = UCBRF_15 + UCBRS_7;

  UCA3CTL1        &= ~UCSWRST;       // 启动状态机
  UCA3IE          |= UCRXIE;         // 允许接收中断
}
//***************************************************************************//
//                                                                           //
//  UTX_PROC(void): USB端口发送程序                                          //
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
//  USB接收中断服务程序                                                      //
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
