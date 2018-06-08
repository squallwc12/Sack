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
#ifndef __REPORTFORM_H__
#define __REPORTFORM_H__

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ReportForm_typedef.h"


/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
extern Report_Typedef  Report_test;
/* Exported functions --------------------------------------------------------*/
void Report_DeInit(void);
void Report_SetEntry(Report_Typedef * Report, ucByte sID, value_Typedef * value);
void Report_SetStateEntry(Report_Typedef * Report, ucByte sID, EntryType State, ucByte Mode);
void Report_print(void (*CBprint)(char *, ...), Report_Typedef * Report, ucByte lvl);

#endif // __REPORTFORM_H__
