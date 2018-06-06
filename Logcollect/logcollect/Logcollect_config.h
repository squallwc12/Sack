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
#define EXT_EVENT_BUFFER_SIZE             ( 5)        //��־��չ��������
#define QUEUE_BUFFER_SIZE                 (10)        //�������
#define EVENTSTORAGE_BUFFER_SIZE          ( 5)        //���洢�¼��Ķ������-�洢��־����
#define EMRG_EVENTSTORAGE_BUFFER_SIZE     ( 5)        //���洢����(����)�¼��Ķ������-�洢��־����
#define LOG_COLLECT_MESSAGE_SIZE          (48)        //��־��Ϣ�ַ�����󳤶�
#define QUEUE_WAIT_TO_TIMOUT              (10000)     //��ʱ�ȴ����ʱ��
#define GET_MESSAGE_LEVEL                 ( 0)        //��Ϣ��ȡ����(0,��ȫ;1,����Debug)
#define PRINTF_MESSAGE_LEVEL              ( 0)        //��Ϣ��ӡ����(0,��ȫ;1,����;2,�޽���)
#define USE_BROKER_PRINT                  ( 0)        //ʹ�� broker_printf ����

#define EVENT_0                     0x00
#define EVENT_1                     0x01

#define _LINE_FEED_                 SIGN_NL_CR
#define DELAY_TIME(X)               //delay_us(X)

#define IS_CLASS_0(X)               (X == 0x00)                                 //�Զ�����,��־�ؼ�����Ч,��������ַ���
#define IS_CLASS_1(X)               ((X == 0x01)||(X == 0x02)||(X == 0x03))     //��־��,����ת�����洢�б�,�����б����ɶ�Ӧ���ַ���
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
