#include "msp430x54x.h"
#include "bsp.h"
#include "PIN_DEF.h"

void Init_CLK(void)
{
  WDTCTL     = WDTPW + WDTHOLD;       // 关闭看门狗
  P7SEL     |= 0x03;                  // 端口功能选择振荡器
  UCSCTL6   &=~XT1OFF;                // 振荡器使能
  UCSCTL6   |= XCAP_3;                // 设置内部负载电容
  UCSCTL3   |= SELREF_2;              // DCOref = REFO
  UCSCTL4   |= SELA_0;                // ACLK   = XT1  
  __bis_SR_register(SCG0);            // 关闭FLL控制回路
  UCSCTL0    = 0x0000;                // 设置DCOx, MODx
  UCSCTL1    = DCORSEL_7;             // 设置DCO震荡范围
  UCSCTL2    = FLLD__1 + FLL_FACTOR;  // Fdco = ( FLL_FACTOR + 1)譌LLRef = (649 + 1) * 32768 = 21.2992MHz
  __bic_SR_register(SCG0);            // 打开FLL控制回路                                                            
  __delay_cycles(1024000); 
  do
  {
    UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + XT1HFOFFG + DCOFFG); // 清除 XT2,XT1,DCO 错误标志                                                            
    SFRIFG1 &= ~OFIFG; 
  }while(SFRIFG1&OFIFG);              // 检测震荡器错误标志
}
