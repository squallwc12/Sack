/*
    FreeRTOS V8.0.1 - Copyright (C) 2014 Real Time Engineers Ltd. 
    All rights reserved

    VISIT http://www.FreeRTOS.org TO ENSURE YOU ARE USING THE LATEST VERSION.

    ***************************************************************************
     *                                                                       *
     *    FreeRTOS provides completely free yet professionally developed,    *
     *    robust, strictly quality controlled, supported, and cross          *
     *    platform software that has become a de facto standard.             *
     *                                                                       *
     *    Help yourself get started quickly and support the FreeRTOS         *
     *    project by purchasing a FreeRTOS tutorial book, reference          *
     *    manual, or both from: http://www.FreeRTOS.org/Documentation        *
     *                                                                       *
     *    Thank you!                                                         *
     *                                                                       *
    ***************************************************************************

    This file is part of the FreeRTOS distribution.

    FreeRTOS is free software; you can redistribute it and/or modify it under
    the terms of the GNU General Public License (version 2) as published by the
    Free Software Foundation >>!AND MODIFIED BY!<< the FreeRTOS exception.

    >>!   NOTE: The modification to the GPL is included to allow you to     !<<
    >>!   distribute a combined work that includes FreeRTOS without being   !<<
    >>!   obliged to provide the source code for proprietary components     !<<
    >>!   outside of the FreeRTOS kernel.                                   !<<

    FreeRTOS is distributed in the hope that it will be useful, but WITHOUT ANY
    WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
    FOR A PARTICULAR PURPOSE.  Full license text is available from the following
    link: http://www.freertos.org/a00114.html

    1 tab == 4 spaces!

    ***************************************************************************
     *                                                                       *
     *    Having a problem?  Start by reading the FAQ "My application does   *
     *    not run, what could be wrong?"                                     *
     *                                                                       *
     *    http://www.FreeRTOS.org/FAQHelp.html                               *
     *                                                                       *
    ***************************************************************************

    http://www.FreeRTOS.org - Documentation, books, training, latest versions,
    license and Real Time Engineers Ltd. contact details.

    http://www.FreeRTOS.org/plus - A selection of FreeRTOS ecosystem products,
    including FreeRTOS+Trace - an indispensable productivity tool, a DOS
    compatible FAT file system, and our tiny thread aware UDP/IP stack.

    http://www.OpenRTOS.com - Real Time Engineers ltd license FreeRTOS to High
    Integrity Systems to sell under the OpenRTOS brand.  Low cost OpenRTOS
    licenses offer ticketed support, indemnification and middleware.

    http://www.SafeRTOS.com - High Integrity Systems also provide a safety
    engineered and independently SIL3 certified version for use in safety and
    mission critical applications that require provable dependability.

    1 tab == 4 spaces!
*/

#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/*-----------------------------------------------------------
 * Application specific definitions.
 *
 * These definitions should be adjusted for your particular hardware and
 * application requirements.
 *
 * THESE PARAMETERS ARE DESCRIBED WITHIN THE 'CONFIGURATION' SECTION OF THE
 * FreeRTOS API DOCUMENTATION AVAILABLE ON THE FreeRTOS.org WEB SITE.
 *
 * See http://www.freertos.org/a00110.html.
 *----------------------------------------------------------*/

#define configUSE_PREEMPTION			        1
#define configUSE_IDLE_HOOK				0                       //*使用空闲钩子函数
#define configUSE_TICK_HOOK				1                       //*时间片中断钩子函数,用于实现简单定时功能
#define configCPU_CLOCK_HZ				( 16000000UL )
#define configLFXT_CLOCK_HZ       		        ( 32768L )              //*与FreeRTOS无关，系统外部低速时钟源的频率
#define configTICK_RATE_HZ				(( TickType_t )1000 )
#define configMAX_PRIORITIES			        ( 5 )                   //*有效的优先级数目
#define configTOTAL_HEAP_SIZE			        (( size_t )( 10 * 1024 ))//*可使用的RAM大小
#define configMAX_TASK_NAME_LEN			        ( 10 )                  //*最大任务名称字节长度
#define configUSE_TRACE_FACILITY		        1                       //*可视化跟踪调试
#define configUSE_16_BIT_TICKS			        0                       //*系统节拍计数器的变量类型(portTickType),1标识16bit无符号型;0标识32bit无符号型
#define configIDLE_SHOULD_YIELD			        1                       //*控制任务在空闲优先级中的行为
#define configUSE_MUTEXES				1                       //*互斥信号量
#define configQUEUE_REGISTRY_SIZE		        5                       //*系统调试队列记录的深度,关于:vQueueAddToRegistry()& vQueueUnregisterQueue()
#define configGENERATE_RUN_TIME_STATS	                0                       //*系统时间统计功能
                                                                                // 如果使用则必须启用 portCONFIGURE_TIMER_FOR_RUN_TIM_STATS()& portGET_RUN_TIME_COUNTER_VALLE()
                                                                                // 使用的时钟源必须要快于系统时钟源10-100倍，以保证计时准确
#define configCHECK_FOR_STACK_OVERFLOW	                2                       //*每个任务维护自己的栈空间,1使用方法一速度快但不能检测所有栈溢出;2使用方法二速度较慢但检测出的概率更大
#define configUSE_RECURSIVE_MUTEXES		        0                       //*递归信号量
#define configUSE_MALLOC_FAILED_HOOK	                1                       //*使用pvPortMalloc()函数失败时,vApplicationMallocFailedHook()函数
#define configUSE_APPLICATION_TASK_TAG	                0                       //*分配标签(如果要使用 vTaskSetApplicationTaskTag() )

#if __DATA_MODEL__ == __DATA_MODEL_SMALL__
	#define configMINIMAL_STACK_SIZE		(( unsigned short )256 )//*任务堆栈大小
#else
	#define configMINIMAL_STACK_SIZE		(( unsigned short )80 )
#endif

/* Co-routine definitions. */
#define configUSE_CO_ROUTINES 		                0                       //*使用协程
                                                                                // 协程(Co-routines)主要用于资源非常受限的系统(RAM很少)，通常不会使用在32bit处理器上，不建议使用，FreeRTOS开发者已经停止开发协程
#define configMAX_CO_ROUTINE_PRIORITIES               ( 2 )                     //*应用程序协程的有效优先级

/* Set the following definitions to 1 to include the API function, or zero
to exclude the API function. */
#define INCLUDE_vTaskPrioritySet		1
#define INCLUDE_uxTaskPriorityGet		1
#define INCLUDE_vTaskDelete			0
#define INCLUDE_vTaskCleanUpResources	        0
#define INCLUDE_vTaskSuspend			1
#define INCLUDE_vTaskDelayUntil			1
#define INCLUDE_vTaskDelay			1

/* This demo makes use of one or more example stats formatting functions.  These
format the raw data provided by the uxTaskGetSystemState() function in to human
readable ASCII form.  See the notes in the implementation of vTaskList() within 
FreeRTOS/Source/tasks.c for limitations. */
#define configUSE_STATS_FORMATTING_FUNCTIONS	1

/* The MSP430X port uses a callback function to configure its tick interrupt.
This allows the application to choose the tick interrupt source.
configTICK_VECTOR must also be set in FreeRTOSConfig.h to the correct
interrupt vector for the chosen tick interrupt source.  This implementation of
vApplicationSetupTimerInterrupt() generates the tick from timer A0, so in this
case configTICK__VECTOR is set to TIMER0_A0_VECTOR. */
#define configTICK_VECTOR				TIMER0_A0_VECTOR        //系统需要的时钟

/* Prevent the following definitions being included when FreeRTOSConfig.h
is included from an asm file. */
#ifdef __ICC430__
	extern void vConfigureTimerForRunTimeStats( void );
	extern volatile unsigned long ulStatsOverflowCount;
#endif /* __ICCARM__ */

/* Configure a 16 bit timer to generate the time base for the run time stats.
The timer is configured to interrupt each time it overflows so a count of
overflows can be kept - that way a 32 bit time value can be constructed from
the timers current count value and the number of overflows. */
//#define portCONFIGURE_TIMER_FOR_RUN_TIME_STATS() vConfigureTimerForRunTimeStats()

/* Construct a 32 bit time value for use as the run time stats time base.  This
comes from the current value of a 16 bit timer combined with the number of times
the timer has overflowed. */
#define portALT_GET_RUN_TIME_COUNTER_VALUE( ulCountValue )			\
	{									\
            /* Stop the counter counting temporarily. */			\
            TA1CTL &= ~MC__CONTINOUS;						\
                                                                                \
            /* Check to see if any counter overflow interrupts are pending. */  \
            if( ( TA1CTL & TAIFG ) != 0 )					\
            {									\
                    /* An overflow has occurred but not yet been processed. */	\
                    ulStatsOverflowCount++;					\
                                                                                \
                    /* Clear the interrupt. */					\
                    TA1CTL &= ~TAIFG;						\
            }								        \
                                                                                \
            /* Generate a 32 bit counter value by combinging the current peripheral	\
            counter value with the number of overflows. */			\
            ulCountValue = ( ulStatsOverflowCount << 16UL );			\
            ulCountValue |= ( unsigned long ) TA1R;				\
            TA1CTL |= MC__CONTINOUS;						\
	}
#endif /* FREERTOS_CONFIG_H */

