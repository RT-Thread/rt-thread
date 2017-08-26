#ifndef __DELAY_H__
#define __DELAY_H__
#ifdef __cplusplus
extern "C" {
#endif
#include "common.h"
#include "core_cm0plus.h"
//本构件实现的接口函数列表
    void DelayInit(void);                   //延时初始化
    void DelayUs(uint32_t us);      //延时us
    void DelayMs(uint32_t ms);      //延时ms

#ifdef __cplusplus
}
#endif

#endif
