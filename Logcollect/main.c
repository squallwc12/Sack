#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <pthread.h>
/*
    添加头文件路径方法: project-> bulid options-> Search directories
    添加静态库路径方法: project-> bulid options-> Linker setting
*/
#include "Logcollect.h"
int i;
unsigned char thead, tfoot, data[QUEUE_BUFFER_SIZE], datai;

void *pthread_func_1(void *arg)
{
    Logcollect_Type     templog;
    char                LogStrbuf[32];
    logcollect_Event    LogExtData;
    char                stri;

    while(1)
    {
        shipper_vsnprintf(LogStrbuf, 32, "data = %d", sizeof(long));
        SHIPPER_QUEUE_PUSH( SHIPPER_LOG_CUSTOM(&templog, Info_Debug, LogStrbuf) );

        stri = (stri % 5) + 1;
        SHIPPER_EVENT(LogExtData, stri, 1, 2, 3, 4, 5);
        SHIPPER_QUEUE_PUSH( SHIPPER_LOG(&templog, Info_Debug, &LogExtData) );

        Sleep(1000);
    }

    return NULL;
}

void *pthread_func_2(void *arg)
{
    Logcollect_Type     templog;

    while(1)
    {
        SHIPPER_QUEUE_PUSH( SHIPPER_LOG_CUSTOM(&templog, Info_Debug, "debug") );
        Sleep(500);

        broker_printf("***************************************\n");
    }

    return NULL;
}

int main()
{
    Logcollect_Type  templog;

    shipper_queue_DeInit();

    //创建测试线程
    pthread_t ntid;
    pthread_create(&ntid, NULL, pthread_func_1, NULL);
    pthread_create(&ntid, NULL, pthread_func_2, NULL);

    while(1)
    {
        if(SHIPPER_QUEUE_PULL(&templog) == true)
        {
            //queue_FT(&logqueue, &thead, &tfoot, data);
            //printf("head:%u, foot:%u, (%u) \n", thead, tfoot, templog.event.ID);
            //printf("%3u,%3u,%3u,%3u,%3u,%3u,%3u,%3u,%3u,%3u\n", data[0], data[1],data[2],data[3],data[4],data[5],data[6],data[7],data[8],data[9]);
            shipper_printf(&templog);
        }
        else
        {
            //printf("empty\n");
        }
        //Sleep(100);
    }

    return 0;
}

