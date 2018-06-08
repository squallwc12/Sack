#include "Logcollect.h"
#include <stdarg.h>

/* Private define ------------------------------------------------------------*/
#define EVENT_QUEUE_NAME_STRING      "NORM"
#define EMRG_EVENT_QUEUE_NAME_STRING "EMRG"

#define WaitPrintTime               10000
#define WaitPrintSupermeTime        100
#define WaitPrintLockTimeout        (EventCount.count.LostNum ++)
#define WaitPrintString             asm("nop")
#define PriorityLowest              0
#define PriorityHighest             3
#define PrioritySuperme             0xFF

/* Private types -------------------------------------------------------------*/
struct BrokerPrintParam{
    ucBool  LockFlag;
    ucMode  Priority;
};

/* Private variables ---------------------------------------------------------*/
LogStorage_Type       LogEventFIFO[EVENTSTORAGE_BUFFER_SIZE];
LogStorage_Type       LogEMRGEventFIFO[EMRG_EVENTSTORAGE_BUFFER_SIZE];
EventStorage_Typedef  NORMEventQueue  = {{false, 0, 0, false, false}, LogEventFIFO,     EVENTSTORAGE_BUFFER_SIZE,      NULL, NULL, NULL, EVENT_QUEUE_NAME_STRING};
EventStorage_Typedef  EMRGEventQueue  = {{false, 0, 0, false, false}, LogEMRGEventFIFO, EMRG_EVENTSTORAGE_BUFFER_SIZE, NULL, NULL, NULL, EMRG_EVENT_QUEUE_NAME_STRING};
EventCount_Typedef    EventCount;
volatile struct BrokerPrintParam   BrokerPrintState;

/* Private funtion -----------------------------------------------------------*/
ucBool  WaitPrintLock(ucMode Priority);
void    UnlockPrint(void);
void    broker_class_1_CreateExplainString(ucLOGData ID, cpLOGStr Str, ucLOGData Strsize);
ucBool  broker_class_1_PushEventStorageFIFO(EventStorage_Typedef *Queue, Logcollect_Type * log);
void    broker_CountEvent(logcollect_lvl lvl);

/**
  * @brief  broker_queue_DeInit deinit broker
  * @param  NULL
  * @retval NULL
  */
void broker_queue_DeInit(void)
{
    NORMEventQueue.QP.threadLock = false;
    NORMEventQueue.QP.head       = 0;
    NORMEventQueue.QP.foot       = 0;
    NORMEventQueue.QP.emptyFlag  = true;
    NORMEventQueue.QP.fullFlag   = false;
    NORMEventQueue.pQueue        = LogEventFIFO;
    NORMEventQueue.QueueSize     = EVENTSTORAGE_BUFFER_SIZE;
    NORMEventQueue.StrName       = EVENT_QUEUE_NAME_STRING;
    //NORMEventQueue.EventGetDataCallback = NULL;
    //NORMEventQueue.EventQueueFull       = NULL;
    //NORMEventQueue.EventQueueOverflow   = NULL;
    memset(NORMEventQueue.pQueue, 0, (sizeof(LogStorage_Type) * NORMEventQueue.QueueSize));
    
    EMRGEventQueue.QP.threadLock = false;
    EMRGEventQueue.QP.head       = 0;
    EMRGEventQueue.QP.foot       = 0;
    EMRGEventQueue.QP.emptyFlag  = true;
    EMRGEventQueue.QP.fullFlag   = false;
    EMRGEventQueue.pQueue        = LogEMRGEventFIFO;
    EMRGEventQueue.QueueSize     = EMRG_EVENTSTORAGE_BUFFER_SIZE;
    EMRGEventQueue.StrName       = EMRG_EVENT_QUEUE_NAME_STRING;
    //EMRGEventQueue.EventGetDataCallback = NULL;
    //EMRGEventQueue.EventQueueFull       = NULL;
    //EMRGEventQueue.EventQueueOverflow   = NULL;
    memset(EMRGEventQueue.pQueue, 0, (sizeof(LogStorage_Type) * EMRGEventQueue.QueueSize)); 
    
    memset(&EventCount, 0, sizeof(EventCount_Typedef));
}

/**
  * @brief  WaitPrintLock wait print lock flag
  * @param  Priority  : 
  * @retval false     : get flag
  *         true      : timeout
  */
ucBool WaitPrintLock(ucMode Priority)
{
    uiLOGData timeouti;
    uiLOGData timeoutsuperme;
    ucBool    tBool = true;
    
    if(Priority >= BrokerPrintState.Priority){
        BrokerPrintState.Priority = Priority;
    }
    
    for(timeouti = 0, timeoutsuperme = 0; (timeouti < WaitPrintTime)||(Priority == PrioritySuperme); timeouti++){
        //low priority level giveup wait flag
        if(Priority < BrokerPrintState.Priority){
            break;
        }
        //wait flag
        if(BrokerPrintState.LockFlag == false){
            BrokerPrintState.Priority = PriorityLowest;
            BrokerPrintState.LockFlag = true;
            tBool = false;
            break;
        }
        //warring (Priority == PrioritySuperme) may be deadlock so do something
        if(Priority == PrioritySuperme){
            if(timeouti > WaitPrintTime){
                timeoutsuperme ++;
                timeouti = 0;
            }
            if(timeoutsuperme > WaitPrintSupermeTime){
                break;
            }
        }
    }
    
    return tBool;
}

/**
  * @brief  UnlockPrint
  * @param  NULL 
  * @retval NULL
  */
void  UnlockPrint(void)
{
    BrokerPrintState.LockFlag = false;
}

/**
  * @brief  broker_sorting
  * @param  NULL
  * @retval NULL
  */
void broker_sorting(void)
{
    Logcollect_Type     templog;
    ucLOGData           ucloop;
    
    for(ucloop = 0; ucloop < (QUEUE_BUFFER_SIZE + 1); ucloop++) {
        if(SHIPPER_QUEUE_PULL(&templog) == true){
            //class 0: 自定义
            if( IS_CLASS_0(templog.event.StdID) ){
                CLASS_X_Print(lvl_0, &templog);
            }
            //class 1: 存储字段
            else if( IS_CLASS_1(templog.event.StdID) ){
                switch(templog.level){
                case Info_EMRG_Event:
                    broker_class_1_PushEventStorageFIFO(&EMRGEventQueue, &templog); //事件参数转移至存储队列-紧急(抢救)
                    break;
                case Info_Event:
                    broker_class_1_PushEventStorageFIFO(&NORMEventQueue, &templog); //事件参数转移至存储队列-正常
                    break;
                default:
                    break;
                }
                broker_class_1_CreateExplainString(templog.event.StdID, templog.message, LOG_COLLECT_MESSAGE_SIZE); //生成解释字段
                CLASS_X_Print(lvl_1, &templog);
            }
            //class N: 其它字段
            else{
                CLASS_X_Print(lvl_n, &templog);
            }
            
            broker_CountEvent(templog.level);
        }
        else{
            // Queue is empty
            break;
        }
    }
}

/**
  * @brief  broker_CountEvent
  * @param  lvl   :
  * @retval NULL
  */
void broker_CountEvent(logcollect_lvl lvl)
{
    switch(lvl){
    case Info_Debug:
        EventCount.count.DebugNum ++;
        break;
    case Info_Runing:
        EventCount.count.RuningNum ++;
        break;
    case Info_Event:
        EventCount.count.EventNum ++;
        break;
    case Info_EMRG_Event:
        EventCount.count.EMRGEventNum ++;
        break;
    case Info_Warning:
        EventCount.count.WarningNum ++;
        break;
    case Info_Error:
        EventCount.count.ErrorNum ++;
        break;
    default:
        EventCount.count.UnknowNum ++;
        break;
    }
}

/**
  * @brief  broker_class_1_PushEventStorageFIFO push data into queue
  * @param  Queue   : event queue
  *         log     : log 
  * @retval true   
  *         false
  */
ucBool broker_class_1_PushEventStorageFIFO(EventStorage_Typedef *Queue, Logcollect_Type * log)
{
    ucBool              rebool = true;
    Logcollect_Type     templog;
    char                LogStrbuf[LOG_COLLECT_MESSAGE_SIZE];
    
    if(Queue->QP.fullFlag != true) {
        if(Queue->QP.threadLock != true){
            //thread lock
            Queue->QP.threadLock = true;
            {
                memcpy(&Queue->pQueue[Queue->QP.foot].time,  &log->time,  sizeof(logcollect_timer));
                memcpy(&Queue->pQueue[Queue->QP.foot].event, &log->event, sizeof(logcollect_Event));
                  
                Queue->QP.foot = (Queue->QP.foot + 1) % Queue->QueueSize;
                Queue->QP.emptyFlag = false;
                //queue get new data - call processing funtion
                if(Queue->CBGetData != NULL){
                    Queue->CBGetData();
                }
                
                if(Queue->QP.head == Queue->QP.foot){
                    Queue->QP.fullFlag = true;
                    //warning
                    shipper_vsnprintf(LogStrbuf, LOG_COLLECT_MESSAGE_SIZE, "%s event FIFO full.", Queue->StrName);
                    SHIPPER_QUEUE_PUSH( SHIPPER_LOG_CUSTOM(&templog, Info_Warning, LogStrbuf) );
                    //queue is full - call processing funtion
                    if(Queue->CBQueueFull != NULL){
                        Queue->CBQueueFull();
                    }
                }
            }
            //thread unlock
            Queue->QP.threadLock = false;
        }
        else{
            //thread locked
            rebool = false;
        }
    }
    else{
        rebool = false;
        //error
        shipper_vsnprintf(LogStrbuf, LOG_COLLECT_MESSAGE_SIZE, "%s event FIFO full, data is discarded!", Queue->StrName);
        SHIPPER_QUEUE_PUSH( SHIPPER_LOG_CUSTOM(&templog, Info_Error, LogStrbuf) );
        //queue  is overflow - call processing funtion
        if(Queue->CBQueueOverflow != NULL){
            Queue->CBQueueOverflow( log );
        }
    }
    
    return rebool;
}

/**
  * @brief  broker_class_1_PullEventStorageFIFO pull data out queue
  * @param  Queue   : event queue
  *         pEvent  : log 
  * @retval true   
  *         false
  */
ucBool broker_class_1_PullEventStorageFIFO(EventStorage_Typedef *Queue, LogStorage_Type * pEvent)
{
    ucBool              rebool = true;
    
    if(Queue->QP.emptyFlag != true){
        if(Queue->QP.threadLock != true){
            //thread lock
            Queue->QP.threadLock = true;
            {
                memcpy(pEvent, &Queue->pQueue[Queue->QP.head], sizeof(LogStorage_Type));
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
            //thread locked
            rebool =false;
        }
    }
    else{
        //queue is empty
        rebool = false;
    }
    
    return rebool;
}

/**
  * @brief  broker_class_1_Create explain String
  * @param  Str     : buffer address
  *         Strsize : buffer size
  * @retval NULL
  */
void broker_class_1_CreateExplainString(ucLOGData ID, cpLOGStr Str, ucLOGData Strsize)
{
    switch(ID){
    case 1:
        snprintf(Str, Strsize, "this is event 1");
        break;
    case 2:
        snprintf(Str, Strsize, "this is event 2");
        break;
    default:
        snprintf(Str, Strsize, "unknow");
        break;
    }
}

/**
  * @brief  CLASS_X_Print printf log message
  * @param  lvl     : log level
  *         log     :
  * @retval NULL
  */
ucBool CLASS_X_Print(ucLogLevel lvl, Logcollect_Type * log)
{
    if(WaitPrintLock(PrioritySuperme) == false)
    {
        switch(lvl){
        case lvl_0:
        #if   (PRINTF_MESSAGE_LEVEL == 0)
            switch(log->level){
            case Info_Error:
                printf(_H_ERROR_);
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
                break;
            case Info_Warning:
                printf(_H_WARNING_);
                printf("Source : %s" _LINE_FEED_, log->source);
                printf("Line   : %d" _LINE_FEED_, log->line);
                break;
            case Info_Event:
            case Info_EMRG_Event:
                printf(_H_EVENT_);
                break;
            case Info_Runing:
            default:
                printf(_H_DBG_);
                break;
              }
            printf("Message: %s" _LINE_FEED_, log->message);
            printf(_H_DEFAULT_);
            break;
        #elif (PRINTF_MESSAGE_LEVEL == 1)
        #else
        #endif
            
        case lvl_1:
        #if   (PRINTF_MESSAGE_LEVEL == 0)
            printf(_H_EVENT_);
            printf("Event  : %02d [%02d,%02d,%02d,%02d,%02d]" _LINE_FEED_,
                   log->event.StdID,
                   log->event.Extpara.data[0],
                   log->event.Extpara.data[1],
                   log->event.Extpara.data[2],
                   log->event.Extpara.data[3],
                   log->event.Extpara.data[4] );
            printf("Message: %s" _LINE_FEED_, log->message);
            printf(_H_DEFAULT_);
        #elif (PRINTF_MESSAGE_LEVEL == 1)
        #else
        #endif
            break;
          
        case lvl_2:
        #if   (PRINTF_MESSAGE_LEVEL == 0)
        #elif (PRINTF_MESSAGE_LEVEL == 1)
        #else
        #endif
            break;
          
        default:
        #if   (PRINTF_MESSAGE_LEVEL == 0)
            printf(_H_RUN_);
            printf("Source : %s" _LINE_FEED_, log->source);
            printf("Line   : %d" _LINE_FEED_, log->line);
            printf(_H_DEFAULT_);
        #elif (PRINTF_MESSAGE_LEVEL == 1)
        #else
        #endif
            break;
        }
        
        UnlockPrint();
    }
    else{
        WaitPrintLockTimeout;
    }
    
    return true;
}

/**
  * @brief  broker_PullNormEventFIFO get norm event
  * @param  Str     : buffer address
  *         Strsize : buffer size
  * @retval NULL
  */
ucBool broker_PullNormEventFIFO(LogStorage_Type * pEvent)
{
    return( broker_class_1_PullEventStorageFIFO(&NORMEventQueue, pEvent));
}

/**
  * @brief  broker_CB_NormQueueFull normal event queue callback funtion 
  * @param  pFuntion  : funtion
  * @retval NULL
  */
void broker_CB_NormQueueFull(void (*pFuntion)(void))
{
    NORMEventQueue.CBQueueFull = pFuntion;
}

/**
  * @brief  broker_CB_NormGetNewData normal event queue callback funtion 
  * @param  pFuntion  : funtion
  * @retval NULL
  */
void broker_CB_NormGetNewData(void (*pFuntion)(void))
{
    NORMEventQueue.CBGetData = pFuntion;
}

/**
  * @brief  broker_CB_NormQueueOverflow normal event queue callback funtion 
  * @param  pFuntion  : funtion
  * @retval NULL
  */
void broker_CB_NormQueueOverflow(void (*pFuntion)(Logcollect_Type *))
{
    NORMEventQueue.CBQueueOverflow = pFuntion;
}

/**
  * @brief  broker_PullEmrgEventFIFO get emrg event
  * @param  Str     : buffer address
  *         Strsize : buffer size
  * @retval NULL
  */
ucBool broker_PullEmrgEventFIFO(LogStorage_Type * pEvent)
{
    return( broker_class_1_PullEventStorageFIFO(&EMRGEventQueue, pEvent));
}

/**
  * @brief  broker_CB_NormQueueFull normal event queue callback funtion 
  * @param  pFuntion  : funtion
  * @retval NULL
  */
void broker_CB_EmrgQueueFull(void (*pFuntion)(void))
{
    EMRGEventQueue.CBQueueFull = pFuntion;
}

/**
  * @brief  broker_CB_NormGetNewData normal event queue callback funtion 
  * @param  pFuntion  : funtion
  * @retval NULL
  */
void broker_CB_EmrgGetNewData(void (*pFuntion)(void))
{
    EMRGEventQueue.CBGetData = pFuntion;
}

/**
  * @brief  broker_CB_NormQueueOverflow normal event queue callback funtion 
  * @param  pFuntion  : funtion
  * @retval NULL
  */
void broker_CB_EmrgQueueOverflow(void (*pFuntion)(Logcollect_Type *))
{
    EMRGEventQueue.CBQueueOverflow = pFuntion;
}

/**
  * @brief  broker_printf printf str thread-safe
  * @param  format    : string
  *         ...       : parameter
  * @retval
  */
ucBool broker_printf(cpLOGStr format, ...)
{
    ucBool    reBool = false;
    
#if (USE_BROKER_PRINT != 0)
    va_list   vArgList;
        
    if(WaitPrintLock(PriorityLowest) == false){
        va_start(vArgList, format);
        vprintf(format, vArgList);
        va_end(vArgList);
        reBool = true;
        
        UnlockPrint();
    }
    else{
        WaitPrintString;
        reBool = false;
    }
#else
    reBool = true;
#endif
    
    return reBool;
}

/**
  * @brief  broker_superme_printf printf str thread-safe
  * @param  format    : string
  *         ...       : parameter
  * @retval
  */
void broker_superme_printf(cpLOGStr format, ...)
{
    va_list   vArgList;
        
    if(WaitPrintLock(PrioritySuperme) == false){
        va_start(vArgList, format);
        vprintf(format, vArgList);
        va_end(vArgList);
        
        UnlockPrint();
    }
    else{
        WaitPrintString;
    }
}