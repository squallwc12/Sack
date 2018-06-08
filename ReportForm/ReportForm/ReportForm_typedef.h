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
#ifndef __REPORTFORM_TYPEDEF_H__
#define __REPORTFORM_TYPEDEF_H__

/* Includes ------------------------------------------------------------------*/
#include "ReportForm_config.h"

/* Exported types ------------------------------------------------------------*/
#define SIGN_CR                     "\r"
#define SIGN_NL                     "\n"
#define SIGN_NL_CR                  "\r\n"

#define _H_HIGHLIGHT_               "\033[31m"    //ºìÉ«×Ö
#define _H_DEFAULT_                 "\033[0m"     //Ä¬ÈÏ

#ifndef TRUE
#define TRUE    1
#endif // TRUE

#ifndef FALSE
#define FALSE   0
#endif // FALSE

/* Exported typedef ----------------------------------------------------------*/
typedef unsigned char   ucByte;
typedef char *          String;
typedef int             iWORD;
typedef float           fWORD;
typedef void (* CB_print)(char *,...);

/* Exported types ------------------------------------------------------------*/
typedef enum{
    Integer  = 0,
    Float = 1
}ValueType;

typedef enum{
    StateLonely = 0,
    StateHide   = 1,
    StateKP     = 2
}EntryType;

typedef struct{
    ucByte      DataType;
    union{
        iWORD   intType;
        fWORD   floatType;
    }data;
}value_Typedef;

typedef struct{
    String          Item;
    value_Typedef   Value;
    String          Unit;
    String          Remark;
}Entry_Typedef;

typedef struct{
    ucByte          Lonely; //hide child node
    ucByte          Hide;   //hide self node and child node
    ucByte          KP;     //highlight
}Status_Typedef;

typedef struct{
    ucByte          fID;    //father ID
    Status_Typedef  State;
    Entry_Typedef   Entry;
}ReportList_Typedef;

/* Report sort */
typedef struct{
    ucByte          lvl;
    ucByte          ID;
}ReportList_rank_Typedef;

/* Report */
typedef struct{
    ucByte                      FormSN;
    ucByte                      MaxSize;
    ReportList_rank_Typedef *   List;
    ReportList_Typedef      *   Entry;
}Report_Typedef;
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/


#endif // __REPORTFORM_TYPEDEF_H__
