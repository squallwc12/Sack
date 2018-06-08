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
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __LOGCOLLECT_TYPE_H__
#define __LOGCOLLECT_TYPE_H__

#include "Logcollect_config.h"
/* Includes ------------------------------------------------------------------*/
/* Define --------------------------------------------------------------------*/
/*
    ������ɫ:30-37
    ������ɫ:40-47
    0xX0��ɫ; 0xX1��ɫ; 0xX2��ɫ; 0xX3��ɫ; 0xX4��ɫ; 0xX5��ɫ; 0xX6����ɫ; 0xX7��ɫ;
*/
#define _H_DBG_                         "\033[37m"    //��ɫ�� ������Ϣ
#define _H_RUN_                         "\033[37m"    //��ɫ�� ������Ϣ/������Ϣ
#define _H_EVENT_                       "\033[32m"    //��ɫ�� �¼���Ϣ
#define _H_WARNING_                     "\033[33m"    //��ɫ�� ������Ϣ
#define _H_ERROR_                       "\033[31m"    //��ɫ�� ������Ϣ
#define _H_DEFAULT_                     "\033[0m"     //Ĭ��

/* Exported typedef ----------------------------------------------------------*/
typedef unsigned long   ulLOGData;
typedef unsigned int    uiLOGData;
typedef unsigned int    uiLine;
typedef unsigned char   ucLOGData;
typedef unsigned char   ucMode;
typedef const char *    ccLOGStateStr;
typedef char *          cpLOGStr;

/* Exported types ------------------------------------------------------------*/
typedef struct {
    uiLOGData    year;  //��
    uiLOGData    month; //��
    uiLOGData    day;   //��
    uiLOGData    hour;  //ʱ
    uiLOGData    min;   //��
    uiLOGData    sec;   //��
    uiLOGData    msec;  //����
}Logcollect_RT;

typedef struct{
    ulLOGData       ACC_timer;  //��ʱ�ۼ�
    Logcollect_RT   RT_timer;   //ʵʱʱ��
}logcollect_timer;

typedef enum {
    Info_Debug,         //������Ϣ
    Info_Runing,        //������Ϣ
    Info_Event,         //�¼���Ϣ
    Info_EMRG_Event,    //�����¼���Ϣ
    Info_Warning,       //������Ϣ
    Info_Error          //������Ϣ
}logcollect_lvl;

typedef enum{
    #define TRUE    1
    #define FALSE   0
    true = TRUE,
    false = FALSE
}ucBool;

typedef enum{
    lvl_0,
    lvl_1,
    lvl_2,
    lvl_n = 0xff
}ucLogLevel;

/*
    event format -
    StdID : Standard event identifier
    data  : Extend event identifier
*/
typedef struct {
    ucLOGData   StdID;
    struct{
        ucLOGData   data[EXT_EVENT_BUFFER_SIZE];
    }Extpara;
}logcollect_Event;

/* event conten */
typedef struct {
    logcollect_timer    time;
    ccLOGStateStr       source;
    uiLine              line;
    logcollect_lvl      level;
    logcollect_Event    event;
    char                message[LOG_COLLECT_MESSAGE_SIZE];
}Logcollect_Type;

/* Queue parameter */
typedef struct {
    ucLOGData   threadLock;
    ucLOGData   head;
    ucLOGData   foot;
    ucLOGData   emptyFlag;
    ucLOGData   fullFlag;
}QueueParameter_Typedef;

/* logger for storage */
typedef struct {
    logcollect_timer    time;
    logcollect_Event    event;
}LogStorage_Type;

/* event queue */
typedef struct {
    QueueParameter_Typedef  QP;
    Logcollect_Type *       pQueue;
    ucLOGData               QueueSize;
    void                    (*CBGetData)(void);
    void                    (*CBQueueFull)(void);
    void                    (*CBQueueOverflow)(Logcollect_Type *);
    ccLOGStateStr           StrName;
}LogQueue_Type;

/* event stroage queue*/
typedef struct {
    QueueParameter_Typedef  QP;
    LogStorage_Type *       pQueue;
    ucLOGData               QueueSize;
    void                    (*CBGetData)(void);
    void                    (*CBQueueFull)(void);
    void                    (*CBQueueOverflow)(Logcollect_Type *);
    ccLOGStateStr           StrName;
}EventStorage_Typedef;

/* event count */
typedef struct {
    struct{
        ulLOGData   DebugNum;
        ulLOGData   RuningNum;
        ulLOGData   EventNum;
        ulLOGData   EMRGEventNum;
        ulLOGData   WarningNum;
        ulLOGData   ErrorNum;
        ulLOGData   UnknowNum;
        ulLOGData   LostNum;
    }count;
}EventCount_Typedef;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

#endif // __LOGCOLLECT_TYPE_H__
