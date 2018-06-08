/**
  ******************************************************************************
  * @file    ReportForm/ReportForm.h
  * @author  Chad
  * @version V0.01
  * @date    7-June-2018
  * @brief   Library configuration file.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; ReportForm system </center></h2>
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __REPORTFORM_CONFIG_H__
#define __REPORTFORM_CONFIG_H__

/* Includes ------------------------------------------------------------------*/
#include <limits.h>

/* Exported types ------------------------------------------------------------*/
#define REPORT_1_MAXSIZE    10
#define PEPORT_ALL_ENTRY    UCHAR_MAX

/* Exported define -----------------------------------------------------------*/
#define FORM1_DEFAULT_VALUE \
{\
    /*0*/{0, {FALSE, FALSE, FALSE}, {"", {Integer, 0}, "", ""}},\
    /*1*/{0, {FALSE, FALSE, FALSE}, {"list1", {Integer, 788}, "ppm", "none"}},\
    /*2*/{0, {FALSE, FALSE, FALSE}, {"list2", {Integer, 23}, "ppm", "none"}},\
    /*3*/{1, {FALSE, FALSE, FALSE}, {"list3", {Integer, 23}, "ppm", "none"}},\
    /*4*/{1, {FALSE, FALSE, FALSE}, {"list4", {Integer, 23}, "ppm", "none"}},\
    /*5*/{2, {FALSE, FALSE, FALSE}, {"list5", {Integer, 23}, "ppm", "none"}},\
    /*6*/{2, {FALSE, FALSE, FALSE}, {"list6", {Integer, 23}, "ppm", "none"}},\
    /*7*/{3, {FALSE, FALSE, FALSE}, {"list7", {Integer, 23}, "ppm", "none"}},\
    /*8*/{3, {FALSE, FALSE, FALSE}, {"list8", {Integer, 23}, "ppm", "none"}},\
    /*9*/{3, {FALSE, FALSE, FALSE}, {"list9", {Integer, 23}, "ppm", "none"}}\
}

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/


#endif // __REPORTFORM_CONFIG_H__
