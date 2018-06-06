/**
  ******************************************************************************
  * @file    Logcollect/Logcollect.h
  * @author  Chad
  * @version V0.01
  * @date    22-May-2018
  * @brief   Library configuration file.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Logcollect system </center></h2>
  *
  *        https://github.com/squallwc12/Logcollect.git
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LOGCOLLECT_H__
#define __LOGCOLLECT_H__

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Logcollect_type.h"
#include "Logcollect_config.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
#define Logcollect_Version  0x0001

/* Exported macro ------------------------------------------------------------*/
#define SHIPPER_LOG(pLog, level, event)                 shipper_format_log(pLog, __func__, __LINE__, level, event, NULL)
#define SHIPPER_LOG_CUSTOM(pLog, level, message)        shipper_format_log(pLog, __func__, __LINE__, level, NULL, message)
#define SHIPPER_QUEUE_PUSH(event)                       queue_push(&logqueue, event, true)
#define SHIPPER_QUEUE_PULL(event)                       queue_pull(&logqueue, event, true)
#define SHIPPER_EVENT(event, ID, x0, x1, x2, x3, x4)    do{ event.StdID = ID; \
                                                            event.Extpara.data[0] = x0; event.Extpara.data[1] = x1;\
                                                            event.Extpara.data[2] = x2; event.Extpara.data[3] = x3;\
                                                            event.Extpara.data[4] = x4;\
                                                        }while(0)
#define SHIPPER_REALTIME(BUF, YEAR, MONTH, DAY, HOUR, MIN, SEC, MS) \
                                                        do{   BUF.year  = YEAR;   \
                                                              BUF.month = MONTH;  \
                                                              BUF.day   = DAY;    \
                                                              BUF.hour  = HOUR;   \
                                                              BUF.min   = MIN;    \
                                                              BUF.sec   = SEC;    \
                                                              BUF.msec  = MS;     \
                                                        }while(0);

/* Exported variables --------------------------------------------------------*/
extern logcollect_timer    logtimer_reg;
extern LogQueue_Type       logqueue;

/* Exported functions --------------------------------------------------------*/
/*shipper*/
void shipper_queue_DeInit(void);
void shipper_timer_ACC(void);
void shipper_realtimer_set(Logcollect_RT * ptime);
size_t shipper_vsnprintf(cpLOGStr buffer, uiLOGData bufsize, cpLOGStr format, ...);
logcollect_Event * shipper_event(logcollect_Event * LogPoint, uiLOGData ID, uiLOGData Exdata0, uiLOGData Exdata1, uiLOGData Exdata2, uiLOGData Exdata3, uiLOGData Exdata4);
Logcollect_Type *  shipper_format_log(Logcollect_Type * pLog, ccLOGStateStr source, uiLine line, logcollect_lvl level, logcollect_Event * Event, cpLOGStr message);
ucBool queue_push(LogQueue_Type *Queue, Logcollect_Type * data, ucMode WaitLock);
ucBool queue_pull(LogQueue_Type *Queue, Logcollect_Type * data, ucMode WaitLock);
void queue_FT(LogQueue_Type *Queue, unsigned char * head, unsigned char * foot, unsigned char data[]);
void shipper_printf(Logcollect_Type * log);

/*broker*/
void broker_queue_DeInit(void);
void broker_sorting(void);
ucBool broker_PullNormEventFIFO(LogStorage_Type * pEvent);
void broker_CB_NormQueueFull(void (*pFuntion)(void));
void broker_CB_NormGetNewData(void (*pFuntion)(void));
void broker_CB_NormQueueOverflow(void (*pFuntion)(Logcollect_Type *));
ucBool broker_PullEmrgEventFIFO(LogStorage_Type * pEvent);
void broker_CB_EmrgQueueFull(void (*pFuntion)(void));
void broker_CB_EmrgGetNewData(void (*pFuntion)(void));
void broker_CB_EmrgQueueOverflow(void (*pFuntion)(Logcollect_Type *));
ucBool CLASS_X_Print(ucLogLevel lvl, Logcollect_Type * log);
ucBool broker_printf(cpLOGStr format, ...);

/*indexer*/
ucBool broker_PullEmrgEventFIFO(LogStorage_Type * pEvent);
ucLOGData indexer_NormEventProcess(void);
ucLOGData indexer_EmrgEventProcess(void);

/*other*/
size_t strlcpy(char *dst, const char *src, size_t siz);

#endif // __LOGCOLLECT_H__
