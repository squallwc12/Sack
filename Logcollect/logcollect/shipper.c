#include "Logcollect.h"
#include <stdarg.h>

/* Private define ------------------------------------------------------------*/
#define QUEUE_STRING_NAME   "SHIPPER_QUEUE"

/* Private funtion -----------------------------------------------------------*/
void shipper_QueueFullCallback(void);

/* Private variables ---------------------------------------------------------*/
logcollect_timer    logtimer;
Logcollect_Type     logbuf[QUEUE_BUFFER_SIZE];
LogQueue_Type       logqueue = {{false, 0, 0, false, false}, logbuf, QUEUE_BUFFER_SIZE, NULL, shipper_QueueFullCallback, NULL, QUEUE_STRING_NAME};


/**
  * @brief  shipper init
  * @param  NULL
  * @retval NULL
  */
void shipper_queue_DeInit(void)
{
    logqueue.QP.threadLock = false;
    logqueue.QP.head = 0;
    logqueue.QP.foot = 0;
    logqueue.QP.emptyFlag = true;
    logqueue.QP.fullFlag  = false;
    logqueue.pQueue    = logbuf;
    logqueue.QueueSize = QUEUE_BUFFER_SIZE;
    logqueue.StrName   = NULL;
    //logqueue.EventGetDataCallback = NULL;
    //logqueue.EventQueueFull       = NULL;
    //logqueue.EventQueueOverflow   = NULL;
    
    memset(logqueue.pQueue, 0, (sizeof(Logcollect_Type) * QUEUE_BUFFER_SIZE));
}

/**
  * @brief  shipper_realtimer_set set fun realtime
  * @param  NULL
  * @retval NULL
  */
void shipper_realtimer_set(Logcollect_RT * ptime)
{
    if(ptime != NULL){
        memcpy(&logtimer.RT_timer, ptime, sizeof(Logcollect_RT));
    }
}

/**
  * @brief  shipper_timer_ACC timer accumulator
  * @param  NULL
  * @retval NULL
  */
void shipper_timer_ACC(void)
{
    logtimer.ACC_timer++;
}

/**
  * @brief  format log
  * @param  * pLog      : queue data point
  *         source      : funtion name
  *         level       : line number
  *         Event       : event struct
  *         message     : message string
  * @retval
  */
Logcollect_Type * shipper_format_log( Logcollect_Type * pLog,
                                      ccLOGStateStr source,
                                      uiLine line,
                                      logcollect_lvl level,
                                      logcollect_Event * Event,
                                      cpLOGStr message)
{
    Logcollect_Type tempLog;
    
    if(pLog == NULL){
        pLog = &tempLog;
    }
    
    //清空寄存器
    memset(pLog, 0, sizeof(Logcollect_Type));
    //复制系统时间
    memcpy(&pLog->time, &logtimer, sizeof(logtimer));
    //调用函数
    pLog->source = source;
    //调用所在行
    pLog->line   = line;
    //信息等级
    pLog->level  = level;
    //字符串复制
    if(message != NULL){
        strlcpy(pLog->message, message, LOG_COLLECT_MESSAGE_SIZE);
    }
    //事件参数复制
    if(Event != NULL) {
        memcpy(&pLog->event, Event, sizeof(logcollect_Event));
    }

    return (pLog);
}

/**
  * @brief  shipper_svnprintf printf str
  * @param  buffer      : queue data point
  *         bufsize     : buffer max string size
  *         format      : string
  *         ...         : parameter
  * @retval
  */
size_t shipper_vsnprintf(cpLOGStr buffer, uiLOGData bufsize, cpLOGStr format, ...)
{
    size_t i;

    va_list vArgList;
    va_start(vArgList, format);
    i = vsnprintf(buffer, bufsize, format, vArgList);
    va_end(vArgList);

    return i;
}

/**
  * @brief  shipper_event exten data input
  * @param  LogPoint  :queue data point，can use NULL
  *         ID        : Event ID
  *         Exdata0   : Event Extended parameter 0
  *         Exdata1   : Event Extended parameter 1
  *         Exdata2   : Event Extended parameter 2
  *         Exdata3   : Event Extended parameter 3
  *         Exdata4   : Event Extended parameter 4
  * @retval logcollect_Event * 
  */
logcollect_Event * shipper_event(logcollect_Event * LogPoint,
                                 uiLOGData ID,  uiLOGData Exdata0, 
                                                uiLOGData Exdata1, 
                                                uiLOGData Exdata2, 
                                                uiLOGData Exdata3, 
                                                uiLOGData Exdata4)
{
    static logcollect_Event tempEvent;
    
    if(LogPoint == NULL) {
      LogPoint = &tempEvent;
    }
    
    LogPoint->StdID = ID;
    LogPoint->Extpara.data[0] = Exdata0;
    LogPoint->Extpara.data[1] = Exdata1;
    LogPoint->Extpara.data[2] = Exdata2;
    LogPoint->Extpara.data[3] = Exdata3;
    LogPoint->Extpara.data[4] = Exdata4;
    
    return (LogPoint);
}

/**
  * @brief  push data to queue
  * @param  * Queue : queue data point
  *         data    :
  *         WaitLock: wait thread lock (true or false)
  * @retval true    success
  *         false   fail
  */
ucBool queue_push(LogQueue_Type *Queue, Logcollect_Type * data, ucMode WaitLock)
{
    unsigned int threadLock_timer = 0;
    
    if(WaitLock == true){
        while(Queue->QP.threadLock == true) {
            DELAY_TIME(1);
            if(threadLock_timer++ > QUEUE_WAIT_TO_TIMOUT){
                // wait to timeout
                goto queue_push_timeout;
            }
        }
    }
    
    if(Queue->QP.fullFlag == true){
        //call processing funtion
        if(Queue->CBQueueOverflow != NULL){
            Queue->CBQueueOverflow(Queue->pQueue);
        }
    }
    
    //thread lock
    Queue->QP.threadLock = true;
    {
        memcpy(&Queue->pQueue[Queue->QP.foot], data, sizeof(Logcollect_Type));
        Queue->QP.foot = (Queue->QP.foot + 1) % Queue->QueueSize;

        Queue->QP.emptyFlag = false;
        
         //queue get new data - call processing funtion
        if(Queue->CBGetData != NULL){
            Queue->CBGetData();
        }
                
        if(Queue->QP.head == Queue->QP.foot){
            Queue->QP.head = (Queue->QP.head + 1) % Queue->QueueSize;
            Queue->QP.fullFlag = true;
            
            //queue is full - call processing funtion
            if(Queue->CBQueueFull != NULL){
                Queue->CBQueueFull();
            }
        }
    }
    //thread unlock
    Queue->QP.threadLock = false;

    return true;

queue_push_timeout:
    return false;
}

/**
  * @brief  pull data from queue
  * @param  * Queue : queue data point
  *         * data  : 
  *         WaitLock: wait thread lock (true or false)
  * @retval true    success
  *         false   fail
  */
ucBool queue_pull(LogQueue_Type *Queue, Logcollect_Type * data, ucMode WaitLock)
{
    unsigned int threadLock_timer = 0;

    if(WaitLock == true){
        if(Queue->QP.threadLock == true) {
            DELAY_TIME(1);
            if(threadLock_timer++ > QUEUE_WAIT_TO_TIMOUT){
                // wait to timeout
                goto queue_pull_timeout;
            }
        }
    }

    if(Queue->QP.emptyFlag != true) {
        //thread lock
        Queue->QP.threadLock = true;
        {
            memcpy(data, &Queue->pQueue[Queue->QP.head], sizeof(Logcollect_Type));
            Queue->QP.head = (Queue->QP.head + 1) % Queue->QueueSize;

            Queue->QP.fullFlag = false;
            if(Queue->QP.head == Queue->QP.foot){
                Queue->QP.emptyFlag = true;
            }
        }
        //thread unlock
        Queue->QP.threadLock = false;
    }
    else{
        //queue is empty
        return false;
    }

    return true;

queue_pull_timeout:
    return false;
}

/**
  * @brief  shipper_QueueFullCallback
  * @param  NULL
  * @retval NULL
  */
void shipper_QueueFullCallback(void)
{
    //printf("shipper queue full\r\n");
}

/**
  * @brief  shipper_printf
  * @param  * log :queue data point
  * @retval NULL
  */
void shipper_printf(Logcollect_Type * log)
{
    printf(_H_WARNING_);
    printf("Time   : (%6lu)%04d-%02d-%02d %02d:%02d:%02d.%03d" _LINE_FEED_, 
           log->time.ACC_timer,
           log->time.RT_timer.year, 
           log->time.RT_timer.month, 
           log->time.RT_timer.day,
           log->time.RT_timer.hour,
           log->time.RT_timer.min,
           log->time.RT_timer.sec,
           log->time.RT_timer.msec);
    printf("Source : %s" _LINE_FEED_, log->source);
    printf("Line   : %d" _LINE_FEED_, log->line);
    printf("Level  : %u" _LINE_FEED_, log->level);
    printf("Message: %s" _LINE_FEED_, log->message);
    printf("Event  : %02d [%02d,%02d,%02d,%02d,%02d]" _LINE_FEED_,
           log->event.StdID,
           log->event.Extpara.data[0],
           log->event.Extpara.data[1],
           log->event.Extpara.data[2],
           log->event.Extpara.data[3],
           log->event.Extpara.data[4] );
    printf(_H_DEFAULT_);
    printf(_LINE_FEED_);
}
