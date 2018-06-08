#include "msp430x54x.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>   

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "bsp.h"

#include "Logcollect.h"
#include "ReportForm.h"

void vRegTest1Task( void *pvParameters );
void vRegTest2Task( void *pvParameters );
void vRegTest3Task( void *pvParameters );
void vRegTest4Task( void *pvParameters );

char * pdata;
int    pline;
char * pfunc;

EventCount_Typedef  testbuf;

int main( void )
{
  // Stop watchdog timer to prevent time out reset
  _DINT();
  
  WDTCTL = WDTPW + WDTHOLD;
  Init_CLK();
  
  //POWER
  P5SEL &=~BIT4;
  P5DIR |= BIT4;
  P5OUT |= BIT4;
  
  //LED_POWER
  P7SEL &=~BIT3;
  P7DIR |= BIT3;
  P7OUT &=~BIT3;
  
  //PWM
  Init_PWM_TA1();
  
  //UART
  Init_UART();
  Init_UART_RS232();
  
  TX_PROC("RS232 hello world!");
  
  //数码管
  Init_Digitron();
  Digitron_print_uDEC(13258790);
  
  //log
  //shipper_queue_DeInit();
  Logcollect_RT RT;
  SHIPPER_REALTIME(RT, 2018, 5, 25, 16, 0, 53, 811);
  shipper_realtimer_set(&RT);
  
  _EINT();
  
  printf("Logcollect version: 0x%02X\r\n", Logcollect_Version);

  /* Create the LCD, button poll and register test tasks, as described at
   the top of this file. */
  xTaskCreate( vRegTest1Task, "Reg1", configMINIMAL_STACK_SIZE, NULL, 2, NULL );
  xTaskCreate( vRegTest2Task, "Reg2", configMINIMAL_STACK_SIZE, NULL, 2, NULL );
  xTaskCreate( vRegTest3Task, "Reg3", configMINIMAL_STACK_SIZE, NULL, 2, NULL );
  xTaskCreate( vRegTest4Task, "Reg4", configMINIMAL_STACK_SIZE, NULL, 2, NULL );
  
  /* Start the scheduler. */
  vTaskStartScheduler();

  for(;;)
  {
  }
}

/*-----------------------------------------------------------*/

/*测试任务*/
void vRegTest1Task( void *pvParameters )
{
  value_Typedef data;
  
  Report_DeInit();
  data.DataType = Float;
  data.data.floatType= 3.315;
  Report_SetEntry(&Report_test, 2, &data);
      
  for(;;)
  {
    broker_sorting();
    
    indexer_NormEventProcess();
    indexer_EmrgEventProcess();
    
    Report_print((CB_print)broker_superme_printf, &Report_test, PEPORT_ALL_ENTRY);
  }
}

/*-----------------------------------------------------------*/

/*测试任务*/
void vRegTest2Task( void *pvParameters )
{
  Logcollect_Type     templog;
  char                LogStrbuf[LOG_COLLECT_MESSAGE_SIZE];
  logcollect_Event    LogExtData;
  char                stri;
  
  for(;;)
  {
    shipper_vsnprintf(LogStrbuf, LOG_COLLECT_MESSAGE_SIZE, "data = %d", sizeof(long));
    SHIPPER_QUEUE_PUSH( SHIPPER_LOG_CUSTOM(&templog, Info_Debug, LogStrbuf) );
    testbuf.count.DebugNum ++;
    
    stri = (stri % 5) + 1;
    SHIPPER_EVENT(LogExtData, stri, 1, 2, 3, 4, 5);
    SHIPPER_QUEUE_PUSH( SHIPPER_LOG(&templog, Info_Event, &LogExtData) );
    testbuf.count.EventNum ++;
    
    while(broker_printf("#task 1\r\n") == false){
        vTaskDelay(1);
    };
    
    vTaskDelay(100);
  }
}

/*-----------------------------------------------------------*/

/*测试任务*/
void vRegTest3Task( void *pvParameters )
{
  Logcollect_Type     templog;
  logcollect_Event    LogExtData;
  
  for(;;)
  {    
    SHIPPER_EVENT(LogExtData, 0x03, 1, 2, 3, 4, 5);
    SHIPPER_QUEUE_PUSH( SHIPPER_LOG(&templog, Info_EMRG_Event, &LogExtData) );
    testbuf.count.EMRGEventNum ++;
    
    while(broker_printf("#task <%s>\r\n", __PRETTY_FUNCTION__) == false){
        vTaskDelay(1);
    };
    
    vTaskDelay(100);
  }
}

/*-----------------------------------------------------------*/

/*测试任务*/
void vRegTest4Task( void *pvParameters )
{
  Logcollect_Type     templog;
  char                LogStrbuf[LOG_COLLECT_MESSAGE_SIZE];
  
  for(;;)
  {
    shipper_vsnprintf(LogStrbuf, LOG_COLLECT_MESSAGE_SIZE, "task warning message");
    SHIPPER_QUEUE_PUSH( SHIPPER_LOG_CUSTOM(&templog, Info_Warning, LogStrbuf) );
    testbuf.count.WarningNum ++;
    
    while(broker_printf("#task 3\r\n") == false){
        vTaskDelay(1);
    };
    
    vTaskDelay(100);
  }
}

/*-----------------------------------------------------------*/

/* The MSP430X port uses this callback function to configure its tick interrupt.
This allows the application to choose the tick interrupt source.
configTICK_VECTOR must also be set in FreeRTOSConfig.h to the correct
interrupt vector for the chosen tick interrupt source.  This implementation of
vApplicationSetupTimerInterrupt() generates the tick from timer A0, so in this
case configTICK_VECTOR is set to TIMER0_A0_VECTOR. */
void vApplicationSetupTimerInterrupt( void )
{
  const unsigned short usACLK_Frequency_Hz = 32768;

  /* Ensure the timer is stopped. */
  TA0CTL = 0;
  
  /* Run the timer from the ACLK. */
  TA0CTL = TASSEL_1;
  
  /* Clear everything to start with. */
  TA0CTL |= TACLR;
  
  /* Set the compare match value according to the tick rate we want. */
  TA0CCR0 = usACLK_Frequency_Hz / configTICK_RATE_HZ;
  
  /* Enable the interrupts. */
  TA0CCTL0 = CCIE;
  
  /* Start up clean. */
  TA0CTL |= TACLR;
  
  /* Up mode. */
  TA0CTL |= MC_1;
}

/*-----------------------------------------------------------*/
void vApplicationMallocFailedHook( void )
{
  /* Called if a call to pvPortMalloc() fails because there is insufficient
  free memory available in the FreeRTOS heap.  pvPortMalloc() is called
  internally by FreeRTOS API functions that create tasks, queues or
  semaphores. */
  taskDISABLE_INTERRUPTS();
  for( ;; );
}

/*-----------------------------------------------------------*/
void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName )
{
  ( void ) pxTask;
  ( void ) pcTaskName;
  
  /* Run time stack overflow checking is performed if
  configconfigCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
  function is called if a stack overflow is detected. */
  taskDISABLE_INTERRUPTS();
  for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationTickHook( void )
{
  Digitron_scan();
}
