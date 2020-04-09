/***************************************************************
*Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd.
*文件名：  system_ES8P508x.h
*作  者：  Liut
*版  本：  V1.00
*日  期：  2017/07/14
*描  述：  库函数配置文件
*备  注：  适用于 ES8P508x芯片
           本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
***************************************************************/
#ifndef __SYSTEMES8P508x_H__
#define __SYSTEMES8P508x_H__

#include "ES8P508x.h"
#include "type.h"

extern uint32_t SystemCoreClock;
extern void SystemInit(void);
extern void SystemCoreClockUpdate(void);

#endif

/*************************END OF FILE**********************/
