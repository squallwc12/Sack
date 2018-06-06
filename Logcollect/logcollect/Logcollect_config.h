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
#ifndef __LOGCOLLECT_CONFIG_H__
#define __LOGCOLLECT_CONFIG_H__

/* Includes ------------------------------------------------------------------*/
/* Define --------------------------------------------------------------------*/
#define SIGN_CR                     "\r"
#define SIGN_NL                     "\n"
#define SIGN_NL_CR                  "\r\n"

/* configuration item --------------------------------------------------------*/
#define EXT_EVENT_BUFFER_SIZE             ( 5)        //日志扩展参数数量
#define QUEUE_BUFFER_SIZE                 (10)        //队列深度
#define EVENTSTORAGE_BUFFER_SIZE          ( 5)        //待存储事件的队列深度-存储日志队列
#define EMRG_EVENTSTORAGE_BUFFER_SIZE     ( 5)        //待存储紧急(急救)事件的队列深度-存储日志队列
#define LOG_COLLECT_MESSAGE_SIZE          (48)        //日志消息字符串最大长度
#define QUEUE_WAIT_TO_TIMOUT              (10000)     //超时等待最大时间
#define GET_MESSAGE_LEVEL                 ( 0)        //消息获取级别(0,完全;1,忽视Debug)
#define PRINTF_MESSAGE_LEVEL              ( 0)        //消息打印级别(0,完全;1,缩略;2,无解释)
#define USE_BROKER_PRINT                  ( 0)        //使用 broker_printf 函数

#define EVENT_0                     0x00
#define EVENT_1                     0x01

#define _LINE_FEED_                 SIGN_NL_CR
#define DELAY_TIME(X)               //delay_us(X)

#define IS_CLASS_0(X)               (X == 0x00)                                 //自定义类,日志关键字无效,用于输出字符串
#define IS_CLASS_1(X)               ((X == 0x01)||(X == 0x02)||(X == 0x03))     //日志类,数据转移至存储列表,根据列表生成对应的字符串
#define IS

/* Exported typedef ----------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/

#if (PRINTF_MESSAGE_LEVEL > 2)
#error PRINTF_MESSAGE_LEVEL MUST be <= 2
#endif

#if (GET_MESSAGE_LEVEL > 1)
#error GET_MESSAGE_LEVEL MUST be <= 1
#endif

#endif // __LOGCOLLECT_CONFIG_H__
