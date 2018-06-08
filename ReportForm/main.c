#include <stdio.h>
#include <stdlib.h>
#include "ReportForm.h"

int main()
{
    value_Typedef data;

    printf("Hello world!\n");
    Report_DeInit();
    data.DataType = 1;
    data.data.floatType= 3.3;
    Report_SetEntry(&Report_test, 2, &data);
    Report_print(printf, &Report_test, PEPORT_ALL_ENTRY);

    //printf("\n");
    //Report_SetStateEntry(&Report_test, 3, StateLonely, TRUE);
    //Report_print(&Report_test, PEPORT_ALL_ENTRY);

    //printf("\n");
    //Report_DeInit();
    //Report_print(&Report_test, PEPORT_ALL_ENTRY);

    //printf("\n");
    //Report_SetStateEntry(&Report_test, 3, StateHide, TRUE);
    //Report_print(&Report_test, PEPORT_ALL_ENTRY);

    //printf("\n");
    //Report_SetStateEntry(&Report_test, 6, StateHide, TRUE);
    //Report_print(&Report_test, PEPORT_ALL_ENTRY);
    return 0;
}
