
#ifndef __APP_CONFIG_H__
#define __APP_CONFIG_H__
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <rtthread.h>

typedef struct RxCon
{
    rt_uint32_t recsize;
    char* recBuf;

} RxControl_Type;

typedef struct TxCon
{
    rt_uint32_t recsize;
    char* trnBuf;

} TxControl_Type;
#endif


