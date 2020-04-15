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
#ifndef __LIBWDT_H__
#define __LIBWDT_H__

#include "system_ES8P508x.h"
#include "ES8P508x.h"
#include "type.h"

/* WDT时钟选择 */
typedef enum
{
    WDT_CLOCK_PCLK = 0x0,   //PCLK
    WDT_CLOCK_WDT  = 0x1,   //WDT时钟源，32kHz
} WDT_TYPE_CLKS;

/* 初始化结构体 */
typedef struct
{
    uint32_t WDT_Tms;       //定时时间，单位ms 
    TYPE_FUNCEN WDT_IE;     //中断使能
    TYPE_FUNCEN WDT_Rst;    //复位使能
    WDT_TYPE_CLKS WDT_Clock;//时钟选择
} IWDT_InitStruType;

typedef enum
{
    WDT_WIN_25 = 0x0,   //25%窗口内禁止喂狗，窗口内喂狗产生复位
    WDT_WIN_50 = 0x1,   //50%窗口内禁止喂狗，窗口内喂狗产生复位
    WDT_WIN_75 = 0x2,   //75%窗口内禁止喂狗，窗口内喂狗产生复位
    WDT_WIN_100 = 0x3,  //不禁止喂狗，喂狗将使看门狗计数器重载
} WDT_TYPE_WIN;

/* 初始化结构体 */
typedef struct
{
    uint32_t WDT_Tms;       //定时时间，单位ms 
    TYPE_FUNCEN WDT_IE;     //中断使能
    TYPE_FUNCEN WDT_Rst;    //复位使能
    WDT_TYPE_CLKS WDT_Clock;//时钟选择
    WDT_TYPE_WIN WDT_Win;   //禁止喂狗窗口
} WWDT_InitStruType;

#define IWDT_RegUnLock()     (IWDT->LOCK.Word = 0x1ACCE551)
#define IWDT_RegLock()       (IWDT->LOCK.Word = 0x0)

#define IWDT_Enable()        {IWDT_RegUnLock();IWDT->CON.EN = 1;IWDT_RegLock();}
#define IWDT_Disable()       {IWDT_RegUnLock();IWDT->CON.EN = 0;IWDT_RegLock();}

#define IWDT_Clear()         {IWDT_RegUnLock();IWDT->INTCLR.INTCLR = 0;IWDT_RegLock();}

#define IWDT_ITEnable()      {IWDT_RegUnLock();IWDT->CON.IE = 1;IWDT_RegLock();}
#define IWDT_ITDisable()     {IWDT_RegUnLock();IWDT->CON.IE = 0;IWDT_RegLock();}

#define IWDT_RstEnable()     {IWDT_RegUnLock();IWDT->CON.RSTEN = 1;IWDT_RegLock();}
#define IWDT_RstDisable()    {IWDT_RegUnLock();IWDT->CON.RSTEN = 0;IWDT_RegLock();}

#define IWDT_CLOCK_PCLK()    {IWDT_RegUnLock();IWDT->CON.CLKS = 0;IWDT_RegLock();}
#define IWDT_CLOCK_WDT()     {IWDT_RegUnLock();IWDT->CON.CLKS = 1;IWDT_RegLock();}

#define WWDT_RegUnLock()     (WWDT->LOCK.Word = 0x1ACCE551)
#define WWDT_RegLock()       (WWDT->LOCK.Word = 0x0)

#define WWDT_Enable()        {WWDT_RegUnLock();WWDT->CON.EN = 1;WWDT_RegLock();}
#define WWDT_Disable()       {WWDT_RegUnLock();WWDT->CON.EN = 0;WWDT_RegLock();}

#define WWDT_Clear()         {WWDT_RegUnLock();WWDT->INTCLR.INTCLR = 0;WWDT_RegLock();}

#define WWDT_ITEnable()      {WWDT_RegUnLock();WWDT->CON.IE = 1;WWDT_RegLock();}
#define WWDT_ITDisable()     {WWDT_RegUnLock();WWDT->CON.IE = 0;WWDT_RegLock();}

#define WWDT_RstEnable()     {WWDT_RegUnLock();WWDT->CON.RSTEN = 1;WWDT_RegLock();}
#define WWDT_RstDisable()    {WWDT_RegUnLock();WWDT->CON.RSTEN = 0;WWDT_RegLock();}

#define WWDT_CLOCK_PCLK()    {WWDT_RegUnLock();WWDT->CON.CLKS = 0;WWDT_RegLock();}
#define WWDT_CLOCK_WDT()     {WWDT_RegUnLock();WWDT->CON.CLKS = 1;WWDT_RegLock();}

void IWDT_Init(IWDT_InitStruType *IWDT_InitStruct);
void IWDT_SetReloadValue(uint32_t Value);
uint32_t IWDT_GetValue(void);
FlagStatus IWDT_GetFlagStatus(void);
FlagStatus IWDT_GetITStatus(void);
void WWDT_Init(WWDT_InitStruType *WDT_InitStruct);
void WWDT_SetReloadValue(uint32_t Value);
uint32_t WWDT_GetValue(void);
FlagStatus WWDT_GetFlagStatus(void);
FlagStatus WWDT_GetITStatus(void);

#endif

/*************************END OF FILE**********************/

