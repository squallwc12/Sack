#ifndef __BSP_H__
#define __BSP_H__

#define  FLL_FACTOR     649
/* CLK.c ---------------------------------------------------------------------*/
void Init_CLK(void);

/* UART_usb.c ----------------------------------------------------------------*/
void Init_UART(void);

/* UART_rs232.c --------------------------------------------------------------*/
void Init_UART_RS232(void);
void TX_PROC(char *tx_buf);

/* PWM TIMEA1_usb.c ----------------------------------------------------------*/
void Init_PWM_TA1(void);

/* DIGITRON.c ----------------------------------------------------------------*/
void Init_Digitron(void);
void Digitron_print_uDEC(unsigned long number);
void Digitron_scan(void);

#endif

