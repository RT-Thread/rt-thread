/***************************************************************
 *Copyright (C), 2017, Shanghai Eastsoft Microelectronics Co., Ltd
 *文件名：  lib_wdt.c
 *作  者：  Liut
 *版  本：  V1.00
 *日  期：  2017/02/04
 *描  述：  看门狗模块库函数
 *备  注：  适用于 ES8P508x芯片
 本软件仅供学习和演示使用，对用户直接引用代码所带来的风险或后果不承担任何法律责任。
 ***************************************************************/
#include "lib_wdt.h"

/*************************************
  函数名：IWDT_Init
  描  述：IWDT初始化
  输入值：初始化结构体
  返回值：无
 **************************************/
void IWDT_Init(IWDT_InitStruType *WDT_InitStruct)
{
    uint32_t tmp;

    if (WDT_InitStruct->WDT_Clock != WDT_CLOCK_PCLK)
        tmp = (uint32_t)(32 * WDT_InitStruct->WDT_Tms);
    else
        tmp = SystemCoreClock / 1000 * WDT_InitStruct->WDT_Tms;

    IWDT->LOAD.LOAD = tmp;
    IWDT->CON.CLKS = WDT_InitStruct->WDT_Clock;
    IWDT->CON.IE = WDT_InitStruct->WDT_IE;
    IWDT->CON.RSTEN = WDT_InitStruct->WDT_Rst;

    return;
}

/*************************************
  函数名：IWDT_SetReloadValue
  描  述：设置WDT重载的初值
  输入值：初始值，32-bit无符号整数
  返回值：无
 **************************************/
void IWDT_SetReloadValue(uint32_t Value)
{
    IWDT->LOAD.LOAD = Value;
    return;
}

/*************************************
  函数名：IWDT_GetValue
  描  述：获取WDT当前值
  输入值：无
  返回值：当前值
 **************************************/
uint32_t IWDT_GetValue(void)
{
    return (uint32_t)IWDT->VALUE.VALUE;
}

/*************************************
  函数名：IWDT_GetFlagStatus
  描  述：获取WDT中断状态
  输入值：无
  返回值：SET/RESET
 **************************************/
FlagStatus IWDT_GetFlagStatus(void)
{
    FlagStatus bitstatus = RESET;

    if (IWDT->RIS.WDTIF != RESET)
        bitstatus = SET;

    return  bitstatus;
}

/*************************************
  函数名：IWDT_GetITStatus
  描  述：获取WDT使能中断状态
  输入值：无
  返回值：SET/RESET
 **************************************/
FlagStatus IWDT_GetITStatus(void)
{
    FlagStatus bitstatus = RESET;

    if (IWDT->CON.IE != RESET)
        bitstatus = SET;

    return  bitstatus;
}

/*************************************
  函数名：WWDT_Init
  描  述：WWDT初始化
  输入值：初始化结构体
  返回值：无
 **************************************/
void WWDT_Init(WWDT_InitStruType *WDT_InitStruct)
{
    uint32_t tmp;

    if (WDT_InitStruct->WDT_Clock != WDT_CLOCK_PCLK)
        tmp = (uint32_t)(32 * WDT_InitStruct->WDT_Tms);
    else
        tmp = SystemCoreClock / 1000 * WDT_InitStruct->WDT_Tms;

    WWDT->LOAD.LOAD = tmp;
    WWDT->CON.CLKS = WDT_InitStruct->WDT_Clock;
    WWDT->CON.IE = WDT_InitStruct->WDT_IE;
    WWDT->CON.RSTEN = WDT_InitStruct->WDT_Rst;
    WWDT->CON.WWDTWIN = WDT_InitStruct->WDT_Win;

    return;
}

/*************************************
  函数名：WWDT_SetReloadValue
  描  述：设置WDT重载的初值
  输入值：初始值，32-bit无符号整数
  返回值：无
 **************************************/
void WWDT_SetReloadValue(uint32_t Value)
{
    WWDT->LOAD.LOAD = Value;
    return;
}

/*************************************
  函数名：WWDT_GetValue
  描  述：获取WDT当前值
  输入值：无
  返回值：当前值
 **************************************/
uint32_t WWDT_GetValue(void)
{
    return (uint32_t)WWDT->VALUE.VALUE;
}

/*************************************
  函数名：WWDT_GetFlagStatus
  描  述：获取WDT中断状态
  输入值：无
  返回值：SET/RESET
 **************************************/
FlagStatus WWDT_GetFlagStatus(void)
{
    FlagStatus bitstatus = RESET;

    if (WWDT->RIS.WWDTIF != RESET)
        bitstatus = SET;

    return  bitstatus;
}

/*************************************
  函数名：WWDT_GetIEStatus
  描  述：获取WDT中断使能状态
  输入值：无
  返回值：SET/RESET
 **************************************/
FlagStatus WWDT_GetITStatus(void)
{
    FlagStatus bitstatus = RESET;

    if (WWDT->CON.IE != RESET)
        bitstatus = SET;

    return  bitstatus;
}

/*************************END OF FILE**********************/


