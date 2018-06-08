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
    字体颜色:30-37
    背景颜色:40-47
    0xX0黑色; 0xX1红色; 0xX2绿色; 0xX3黄色; 0xX4蓝色; 0xX5紫色; 0xX6天蓝色; 0xX7白色;
*/
#define _H_DBG_                         "\033[37m"    //白色字 调试信息
#define _H_RUN_                         "\033[37m"    //白色字 运行信息/正常信息
#define _H_EVENT_                       "\033[32m"    //绿色字 事件信息
#define _H_WARNING_                     "\033[33m"    //黄色字 警告信息
#define _H_ERROR_                       "\033[31m"    //红色字 错误信息
#define _H_DEFAULT_                     "\033[0m"     //默认

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
    uiLOGData    year;  //年
    uiLOGData    month; //月
    uiLOGData    day;   //日
    uiLOGData    hour;  //时
    uiLOGData    min;   //分
    uiLOGData    sec;   //秒
    uiLOGData    msec;  //毫秒
}Logcollect_RT;

typedef struct{
    ulLOGData       ACC_timer;  //计时累加
    Logcollect_RT   RT_timer;   //实时时间
}logcollect_timer;

typedef enum {
    Info_Debug,         //调试信息
    Info_Runing,        //运行信息
    Info_Event,         //事件信息
    Info_EMRG_Event,    //紧急事件信息
    Info_Warning,       //警告信息
    Info_Error          //错误信息
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
