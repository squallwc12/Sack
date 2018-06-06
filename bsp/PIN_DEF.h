//===========================================================================//
//                                                                           //
// �ļ���  PIN_DEF.H                                                         //
// ˵����  BW-DK5438�����嵥Ƭ�����Ź��ܶ�����IO�����궨��                   //
// ���룺  IAR Embedded Workbench IDE for msp430 v4.21                       //
// �汾��  v1.1                                                              //
// ��д��  JASON.ZHANG                                                       //
// ��Ȩ��  �������ղ�ά���Ӽ������޹�˾                                      //
//                                                                           //
//===========================================================================//


//***************************************************************************//
//                                                                           //
//                       ���Ź��ܶ���                                        //
//                                                                           //
//***************************************************************************//

// P1 ���Ŷ���
#define KP_INT                 BIT0 // �����ж� 
#define J60_INT                BIT1 // ENC28J60�ж�
#define BL_CTR                 BIT2 // TFT�������
#define TP_INT                 BIT3 // �������ж�
#define DIG5                   BIT4 // ����ܵ�5λ
#define DIG6                   BIT5 // ����ܵ�6λ
#define DIG7                   BIT6 // ����ܵ�7λ
#define DIG8                   BIT7 // ����ܵ�8λ

// P2 ���Ŷ���
#define	DB10   	 	       BIT0 // TFT�������߸�8λ         
#define	DB11   	 	       BIT1           
#define	DB12   	 	       BIT2          
#define	DB13   	 	       BIT3           
#define	DB14   	 	       BIT4           
#define	DB15   	 	       BIT5           
#define	DB16   	 	       BIT6           
#define	DB17   	 	       BIT7  

// P3 ���Ŷ���
#define	NCS25  	 	       BIT0  // SST25VƬѡ
#define SI25                   BIT1  // SST25V��������
#define	LCD_NRD	               BIT1  // LCD���ź�  
#define SO25                   BIT2  // SST25V�������
#define	LCD_NRS 	       BIT2  // LCD�Ĵ���ѡ��  
#define	LCD_NWR   	       BIT3  // LCDд�ź�
#define SC25                   BIT3  // SST25V����ʱ��
#define	TP_CS  	 	       BIT4  // XTP2046Ƭѡ
#define	TP_BUSY	 	       BIT5  // XTP2046æ
#define	LCD_NCS                BIT6  // LCDƬѡ
#define LCD_NRST   	       BIT7  // LCD��λ

// P4 ���Ŷ���
#define	DB00   	 	       BIT0  // TFT�������ߵ�8λ        
#define	DB01   	 	       BIT1           
#define	DB02   	 	       BIT2          
#define	DB03   	 	       BIT3           
#define	DB04   	 	       BIT4           
#define	DB05   	 	       BIT5           
#define	DB06   	 	       BIT6           
#define	DB07   	 	       BIT7           

// P5 ���Ŷ���
#define	NWOL   	               BIT0  // ENC28J60���绽��
#define	J60_CS                 BIT1  // ENC28J60Ƭѡ
#define	XT2IN	               BIT2  // XT2�����
#define	XT2OUT	               BIT3  // XT2�����
#define POWER 	               BIT4  // �����Դ���ƶ�
#define NC01                   BIT5  // δռ��
#define	TXD_U                  BIT6  // USB�������
#define	RXD_U                  BIT7  // USB��������

// P6 ���Ŷ���
#define	KPR0 	 	       BIT0  // ����0��
#define	KPR1   	               BIT1  // ����1��
#define	KPR2	               BIT2  // ����2��
#define	KPR3	               BIT3  // ����3��
#define KPC0   	 	       BIT4  // ����0��
#define	KPC1  	 	       BIT5  // ����1��
#define	KPC2  	               BIT6  // ����2��
#define	KPC3                   BIT7  // ����3��

// P7 ���Ŷ���
#define	XT1IN   	       BIT0  // XT1����
#define	XT1OUT                 BIT1  // XT1���  
#define NC02                   BIT2  // δռ��
#define	LED_PWR                BIT3  // LED��Դ����
#define DE_485    	       BIT4  // 485���ݿ��ƶ�
#define	TVBTM	               BIT5  // ����Դ��ѹ�������  
#define	TVBTB                  BIT6  // ���õ�ص�ѹ�������  
#define	BUZZER                 BIT7  // ���������ƶ�

// P8 ���Ŷ���
#define	SEGA    	       BIT0  // ����ܶ�ѡ
#define	SEGB    	       BIT1  
#define	SEGC    	       BIT2  
#define	SEGD    	       BIT3  
#define	SEGE    	       BIT4  
#define	SEGF    	       BIT5  
#define	SEGG    	       BIT6  
#define	SEGDP    	       BIT7  

// P9 ���Ŷ���
#define DIG1                   BIT0  // ����ܵ�1λ
#define DIG2                   BIT1  // ����ܵ�2λ
#define DIG3                   BIT2  // ����ܵ�3λ
#define DIG4                   BIT3  // ����ܵ�4λ
#define IrDA_OUT               BIT4  // �������
#define IrDA_IN                BIT5  // ��������
#define SDA5571                BIT6  // DAC5571����
#define SCK5571                BIT7  // DAC5571ʱ��

// P10 ���Ŷ���
#define	PNSS    	       BIT0  // ͨ��SPI�ӻ�Ƭѡ
#define	PMOSI                  BIT1  // ͨ��SPI�������  
#define	PMISO                  BIT2  // ͨ��SPI��������  
#define	PSCK                   BIT3  // ͨ��SPI����ʱ��  
#define TXD 	               BIT4  // UART����  
#define	RXD	               BIT5  // UART����  
#define	DIO_B20                BIT6  // DS18B20����
#define	NC03                   BIT7  // δռ��

// P11 ���Ŷ���
#define TACK                   BIT0  // ACLK���Զ�
#define TMCK                   BIT1  // MCLK���Զ�
#define TSMCK                  BIT2  // SMCLK���Զ�

//****************************************************************************
//                                                                           *
//                           �����궨��                                      *
//                                                                           *
//****************************************************************************

//------------------------------- ����Դ���� -------------------------------//
#define MAIN_POWER_ON          P5DIR  |= POWER;\
                               P5OUT  |= POWER
#define MAIN_POWER_OFF         P5OUT  &=~POWER
//------------------------------ LED��Դ���� -------------------------------//
#define LED_POWER_ON          P7DIR  |= LED_PWR;\
                              P7OUT  |= LED_PWR
#define LED_POWER_OFF         P7OUT  &=~LED_PWR

//----------------------------- TFTҺ�������� ------------------------------//
#define  LCD_POWER_ON          P1OUT  &=~BL_CTR   // LCD���⿪
#define  LCD_POWER_OFF         P1OUT  |= BL_CTR   // LCD�����
#define  SET_LCD_RST           P3OUT  |= LCD_NRST // LCD��λ
#define  CLR_LCD_RST           P3OUT  &=~LCD_NRST
#define  SET_LCD_CS            P3OUT  |= LCD_NCS  // LCDƬѡ
#define  CLR_LCD_CS            P3OUT  &=~LCD_NCS
#define  SET_LCD_RS            P3OUT  |= LCD_NRS  // LCD�Ĵ���ѡ��
#define  CLR_LCD_RS            P3OUT  &=~LCD_NRS
#define  SET_LCD_WR            P3OUT  |= LCD_NWR  // LCDд�ź�
#define  CLR_LCD_WR            P3OUT  &=~LCD_NWR 
#define  SET_LCD_RD            P3OUT  |= LCD_NRD  // LCD���ź�
#define  CLR_LCD_RD            P3OUT  &=~LCD_NRD
#define  LOW_BYTE_OUT(data)    P4OUT   = data
#define  HIGH_BYTE_OUT(data)   P2OUT   = data
#define  BUS_IN                P2DIR   = 0x00;\
                               P4DIR   = 0x00     // 
#define  BUS_OUT               P2DIR   = 0xFF;\
                               P4DIR   = 0xFF     
#define  TFT_DATA_HIGH         P2IN
#define  TFT_DATA_LOW          P4IN

//----------------------------- ͨ��SPI������ ------------------------------//
#define  SET_PNSS              P10OUT |= PNSS
#define  CLR_PNSS              P10OUT &=~PNSS
#define  SET_PSCK              P10OUT |= PSCK
#define  CLR_PSCK              P10OUT &=~PSCK
#define  SET_PMOSI             P10OUT |= PMOSI
#define  CLR_PMOSI             P10OUT &=~PMOSI
#define  PMISO_IS_SET         (P10IN&PMISO)

//------------------------------ ������������ ------------------------------//
#define  SET_TP_CS             P3OUT  |= TP_CS
#define  CLR_TP_CS             P3OUT  &=~TP_CS
#define  TP_INT_IS_CLR      (!(P1IN&TP_INT))

//------------------------------ ����ܲ����� ------------------------------//
#define  SET_DIGITS_OUT        P1OUT   = 0xF0;\
                               P1DIR   = 0xF0;\
                               P9OUT   = 0x0F;\
                               P9DIR   = 0x0F
#define  SET_SEGS_OUT          P8DIR   = 0xFF;\
                               P8OUT   = 0x00
#define  MASK_DIGITS           P1OUT  |= 0xF0;\
                               P9OUT  |= 0x0F
#define  LOW_DIGITS_OUT(data)  P9OUT  &= data
#define  HIGH_DIGITS_OUT(data) P1OUT  &= data

//---------------------------------- ���̲����� ----------------------------//
#define KEY_PORT_IN            P6IN 
#define KEY_PORT_OUT           P6OUT 
#define KEY_PORT_DIR           P6DIR 
#define KEY_PORT_REN           P6REN
#define ROW_IN_COL_OUT         P6DIR   =  KPC0+KPC1+KPC2+KPC3      ;\
                               P6OUT   =~(KPC0+KPC1+KPC2+KPC3)     ;\
                               __delay_cycles(20)                      // ���������������                                        
#define CLO_IN_ROW_OUT         P6DIR   =  KPR0+KPR1+KPR2+KPR3      ;\
                               P6OUT   =~(KPR0+KPR1+KPR2+KPR3)     ;\
                               __delay_cycles(20)                      // ���������������
#define INTERNAL_PULL_UP       P6REN   =  0xFF                         // ���̶˿��ڲ���������ʹ��

//------------------------------- USB�˿� ----------------------------//

#define USB_PORT_SEL           P5SEL
#define USB_PORT_DIR           P5DIR

//---------------------------- RS232/485�˿� -------------------------//
#define RS_PORT_SEL            P10SEL
#define RS_PORT_DIR            P10DIR
#define RS485_IN               P7OUT &=~DE_485;\
                               P7DIR |= DE_485;\
                               __delay_cycles(5)
#define RS485_OUT              P7OUT |= DE_485;\
                               P7DIR |= DE_485;\
                               __delay_cycles(5)

//------------------------------- ����˿� ---------------------------//

#define IrDA_PORT_SEL          P9SEL
#define IrDA_PORT_DIR          P9DIR
#define IrDA_PORT_OUT          P9OUT

//---------------------------------- SST25V ������ -------------------------//
#define SET_NCS25              P3OUT  |= NCS25    // SST25VFƬѡ
#define CLR_NCS25              P3OUT  &=~NCS25

//---------------------------------- ���̲����� ----------------------------//
#define ROW_IN_COL_OUT         P6DIR   =  KPC0+KPC1+KPC2+KPC3      ;\
                               P6OUT   =~(KPC0+KPC1+KPC2+KPC3)     ;\
                               __delay_cycles(20)                      // ���������������                                        
#define CLO_IN_ROW_OUT         P6DIR   =  KPR0+KPR1+KPR2+KPR3      ;\
                               P6OUT   =~(KPR0+KPR1+KPR2+KPR3)     ;\
                               __delay_cycles(20)                      // ���������������
#define INTERNAL_PULL_UP       P6REN   =  0xFF                         // ���̶˿��ڲ���������ʹ��

//------------------------------ ENC68J20������ ----------------------------//

#define CLR_J60_CS             P5OUT  &=~J60_CS
#define SET_J60_CS             P5OUT  |= J60_CS


//---------------------------------- ���붨��-------------------------------//
#define No_key   255
#define F1        10
#define F2        11
#define F3        12
#define Delete    12
#define Backspace 13
#define Enter     14
#define OK        15
#define Up        16
#define Down      17
#define Left      18
#define Right     19
#define Esc       20
#define Cancel    20
#define Power     21
#define Power1    21
#define Power2    22
#define Light     22
#define Update   255
