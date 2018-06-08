#include "ReportForm.h"

/* Private define ------------------------------------------------------------*/
#define WODAN_POINT      0
/* Private types -------------------------------------------------------------*/
Report_Typedef  Report_test;

/* Private funtion -----------------------------------------------------------*/
void Report_sort(Report_Typedef * Report, ucByte fList, ucByte lvl);

/* Private variables ---------------------------------------------------------*/
ReportList_rank_Typedef FormList_Array[REPORT_1_MAXSIZE];
ReportList_Typedef      FormList[REPORT_1_MAXSIZE] = FORM1_DEFAULT_VALUE;

/**
  * @brief  Report_Init
  * @param  NULL
  * @retval NULL
  */
void Report_DeInit(void)
{
    ucByte i;
    Report_Typedef * Report = &Report_test;

    Report->List     = FormList_Array;
    Report->Entry    = FormList;
    Report->FormSN   = 0;
    Report->MaxSize  = REPORT_1_MAXSIZE;

    for(i = 0; i<REPORT_1_MAXSIZE; i++){
        Report->Entry[i].State.Lonely   = FALSE;
        Report->Entry[i].State.Hide     = FALSE;
        Report->Entry[i].State.KP       = FALSE;
    }

    Report_sort(Report, WODAN_POINT, 0);
}

/**
  * @brief  Report_sort
  * @param  Report  :
  *         fList   : father level
  *         size    : report entry size
  *         lvl     : level
  * @retval NULL
  */
void Report_sort(Report_Typedef * Report, ucByte fList, ucByte lvl)
{
    ucByte i;

    for(i = 1; i < Report->MaxSize; i++){
        if((Report->Entry[i].fID == fList) && (Report->Entry[i].State.Hide != TRUE)){
            Report->List[Report->FormSN].ID  = i;
            Report->List[Report->FormSN].lvl = lvl;
            Report->FormSN++;
            if(Report->Entry[i].State.Lonely != TRUE){
                Report_sort(Report, i, lvl+1);
            }
        }
    }
}

/**
  * @brief  Report_SetEntry
  * @param  Report      :
  *         sID         :
  *         value       :
  * @retval NULL
  */
void Report_SetEntry(Report_Typedef * Report, ucByte sID, value_Typedef * value)
{
    if((sID < REPORT_1_MAXSIZE) && (Report != NULL)){
        memcpy(&Report->Entry[sID].Entry.Value, value, sizeof(value_Typedef));
    }
}

/**
  * @brief  Report_SetLonelyEntry
  * @param  Report      :
  *         sID         : entry id
  *         State       :
  *         Mode        : lonely flag TRUE or FALSE
  * @retval NULL
  */
void Report_SetStateEntry(Report_Typedef * Report, ucByte sID, EntryType State, ucByte Mode)
{
    if((sID < REPORT_1_MAXSIZE) && (Report != NULL)){
        switch(State){
        case StateLonely:
            Report->Entry[sID].State.Lonely = (Mode != TRUE)?(FALSE):(TRUE);
            Report->FormSN   = 0;
            Report_sort(Report, WODAN_POINT, 0);
            break;
        case StateHide:
            Report->Entry[sID].State.Hide   = (Mode != TRUE)?(FALSE):(TRUE);
            Report->FormSN   = 0;
            Report_sort(Report, WODAN_POINT, 0);
            break;
        case StateKP:
            Report->Entry[sID].State.KP     = (Mode != TRUE)?(FALSE):(TRUE);
            break;
        }
    }
}

/**
  * @brief  Report_print
  * @param  Report  :
  * @retval NULL
  */
void Report_print(void (*CBprint)(char *, ...), Report_Typedef * Report, ucByte lvl)
{
    ucByte i, tlvl;

    if(Report != NULL){
        for(i = 0; i < Report->FormSN; i++){
            if((Report->List[i].lvl <= lvl) && (Report->Entry[Report->List[i].ID].State.Hide != TRUE)){
                for(tlvl = 0; tlvl < Report->List[i].lvl; tlvl++){
                    CBprint("  ");
                }
                if(Report->Entry[Report->List[i].ID].State.KP != FALSE){
                    CBprint(_H_HIGHLIGHT_);
                }
                //category
                CBprint("%s:", Report->Entry[Report->List[i].ID].Entry.Item);
                //value
                switch(Report->Entry[Report->List[i].ID].Entry.Value.DataType){
                case Float:
                    CBprint(" %f", Report->Entry[Report->List[i].ID].Entry.Value.data.floatType);
                    break;
                case Integer:
                    CBprint(" %d", Report->Entry[Report->List[i].ID].Entry.Value.data.intType);
                    break;
                }
                //unit
                CBprint(" %s", Report->Entry[Report->List[i].ID].Entry.Unit);
                //remark
                CBprint(" %s", Report->Entry[Report->List[i].ID].Entry.Remark);
                if(Report->Entry[Report->List[i].ID].State.KP != FALSE){
                    CBprint(_H_DEFAULT_);
                }
                CBprint(SIGN_NL_CR);
            }
        }
    }
}
