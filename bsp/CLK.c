#include "msp430x54x.h"
#include "bsp.h"
#include "PIN_DEF.h"

void Init_CLK(void)
{
  WDTCTL     = WDTPW + WDTHOLD;       // �رտ��Ź�
  P7SEL     |= 0x03;                  // �˿ڹ���ѡ������
  UCSCTL6   &=~XT1OFF;                // ����ʹ��
  UCSCTL6   |= XCAP_3;                // �����ڲ����ص���
  UCSCTL3   |= SELREF_2;              // DCOref = REFO
  UCSCTL4   |= SELA_0;                // ACLK   = XT1  
  __bis_SR_register(SCG0);            // �ر�FLL���ƻ�·
  UCSCTL0    = 0x0000;                // ����DCOx, MODx
  UCSCTL1    = DCORSEL_7;             // ����DCO�𵴷�Χ
  UCSCTL2    = FLLD__1 + FLL_FACTOR;  // Fdco = ( FLL_FACTOR + 1)�FLLRef = (649 + 1) * 32768 = 21.2992MHz
  __bic_SR_register(SCG0);            // ��FLL���ƻ�·                                                            
  __delay_cycles(1024000); 
  do
  {
    UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + XT1HFOFFG + DCOFFG); // ��� XT2,XT1,DCO �����־                                                            
    SFRIFG1 &= ~OFIFG; 
  }while(SFRIFG1&OFIFG);              // ������������־
}
