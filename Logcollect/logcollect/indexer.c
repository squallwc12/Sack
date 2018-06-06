#include "Logcollect.h"

void indexer_print(LogStorage_Type * event);

/**
  * @brief  indexer_NorEventProcess 
  * @param  NULL
  * @retval NULL
  */
ucLOGData indexer_NormEventProcess(void)
{
    LogStorage_Type TempEvent;
    
    if( broker_PullNormEventFIFO(&TempEvent) == true ){
        indexer_print(&TempEvent);
    }
    
    return 0;
}

/**
  * @brief  indexer_NorEventProcess 
  * @param  NULL
  * @retval NULL
  */
ucLOGData indexer_EmrgEventProcess(void)
{
    LogStorage_Type TempEvent;
    
    if( broker_PullEmrgEventFIFO(&TempEvent) == true ){
        indexer_print(&TempEvent);
    }
    
    return 0;
}

/**
  * @brief  indexer_print 
  * @param  NULL
  * @retval NULL
  */
void indexer_print(LogStorage_Type * event)
{
    broker_printf("@save: (%6lu)%04d-%02d-%02d %02d:%02d:%02d.%03d" _LINE_FEED_, 
                   event->time.ACC_timer,
                   event->time.RT_timer.year, 
                   event->time.RT_timer.month, 
                   event->time.RT_timer.day,
                   event->time.RT_timer.hour,
                   event->time.RT_timer.min,
                   event->time.RT_timer.sec,
                   event->time.RT_timer.msec);
    broker_printf("@save: %02d [%02d,%02d,%02d,%02d,%02d]" _LINE_FEED_,
                   event->event.StdID,
                   event->event.Extpara.data[0],
                   event->event.Extpara.data[1],
                   event->event.Extpara.data[2],
                   event->event.Extpara.data[3],
                   event->event.Extpara.data[4] );
}
