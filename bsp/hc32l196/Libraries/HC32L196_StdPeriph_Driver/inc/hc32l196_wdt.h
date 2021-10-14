/******************************************************************************
* Copyright (C) 2017, Huada Semiconductor Co.,Ltd All rights reserved.
*
* This software is owned and published by:
* Huada Semiconductor Co.,Ltd ("HDSC").
*
* BY DOWNLOADING, INSTALLING OR USING THIS SOFTWARE, YOU AGREE TO BE BOUND
* BY ALL THE TERMS AND CONDITIONS OF THIS AGREEMENT.
*
* This software contains source code for use with HDSC
* components. This software is licensed by HDSC to be adapted only
* for use in systems utilizing HDSC components. HDSC shall not be
* responsible for misuse or illegal use of this software for devices not
* supported herein. HDSC is providing this software "AS IS" and will
* not be responsible for issues arising from incorrect user implementation
* of the software.
*
* Disclaimer:
* HDSC MAKES NO WARRANTY, EXPRESS OR IMPLIED, ARISING BY LAW OR OTHERWISE,
* REGARDING THE SOFTWARE (INCLUDING ANY ACOOMPANYING WRITTEN MATERIALS),
* ITS PERFORMANCE OR SUITABILITY FOR YOUR INTENDED USE, INCLUDING,
* WITHOUT LIMITATION, THE IMPLIED WARRANTY OF MERCHANTABILITY, THE IMPLIED
* WARRANTY OF FITNESS FOR A PARTICULAR PURPOSE OR USE, AND THE IMPLIED
* WARRANTY OF NONINFRINGEMENT.
* HDSC SHALL HAVE NO LIABILITY (WHETHER IN CONTRACT, WARRANTY, TORT,
* NEGLIGENCE OR OTHERWISE) FOR ANY DAMAGES WHATSOEVER (INCLUDING, WITHOUT
* LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS, BUSINESS INTERRUPTION,
* LOSS OF BUSINESS INFORMATION, OR OTHER PECUNIARY LOSS) ARISING FROM USE OR
* INABILITY TO USE THE SOFTWARE, INCLUDING, WITHOUT LIMITATION, ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL OR CONSEQUENTIAL DAMAGES OR LOSS OF DATA,
* SAVINGS OR PROFITS,
* EVEN IF Disclaimer HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* YOU ASSUME ALL RESPONSIBILITIES FOR SELECTION OF THE SOFTWARE TO ACHIEVE YOUR
* INTENDED RESULTS, AND FOR THE INSTALLATION OF, USE OF, AND RESULTS OBTAINED
* FROM, THE SOFTWARE.
*
* This software may be replicated in part or whole for the licensed use,
* with the restriction that this Disclaimer and Copyright notice must be
* included with each copy of this software, whether used in part or whole,
* at all times.
*/
/*****************************************************************************/
/** \file wdt.h
 **
 ** Headerfile for WDT functions
 **  
 **
 ** History:
 **   - 2017-05-10   Cathy     First Version
 **
 *****************************************************************************/

#ifndef __WDT_H__
#define __WDT_H__

#include "ddl.h"


/**
 ******************************************************************************
 ** \defgroup WdtGroup Watchdog Timer (WDT)
 **
 ******************************************************************************/
//@{

/******************************************************************************/
/* Global pre-processor symbols/macros ('#define')                            */
/******************************************************************************/

/******************************************************************************
 * Global type definitions
 ******************************************************************************/
/**
 ******************************************************************************
 ** \brief wdt溢出后复位或中断配置
 *****************************************************************************/
typedef enum en_wdt_func
{
    WdtResetEn    = 0,   ///<复位使能
    WdtIntEn      = 1,   ///<中断使能
}en_wdt_func_t;

/**
 ******************************************************************************
 ** \brief wdt当前运行时间配置数据类型定义
 *****************************************************************************/

typedef enum en_wdt_time
{
    WdtT1ms6   = 0u,       ///<1.6ms
    WdtT3ms2   = 1u,       ///<3.2ms
    WdtT6ms4   = 2u,       ///<6.4ms
    WdtT13ms   = 3u,       ///<13ms
    WdtT26ms   = 4u,       ///<26ms
    WdtT51ms   = 5u,       ///<51ms
    WdtT102ms  = 6u,       ///<102ms
    WdtT205ms  = 7u,       ///<205ms
    WdtT500ms  = 8u,       ///<500ms
    WdtT820ms  = 9u,       ///<820ms
    WdtT1s64   = 10u,      ///<1.64s
    WdtT3s28   = 11u,      ///<3.28s
    WdtT6s55   = 12u,      ///<6.55s
    WdtT13s1   = 13u,      ///<13.1s
    WdtT26s2   = 14u,      ///<26.2s
    WdtT52s4   = 15u,      ///<52.4s
}en_wdt_time_t;


//wdt初始化
en_result_t Wdt_Init(en_wdt_func_t enFunc, en_wdt_time_t enTime);

//wdt开始和停止
void Wdt_Start(void);
//喂狗处理
void Wdt_Feed(void);
//喂狗处理
void Wdt_IrqClr(void);
//wdt溢出时间设置
void Wdt_WriteWdtLoad(uint8_t u8LoadValue);
///< 当前计数时间获取
uint8_t Wdt_ReadWdtValue(void);
//< 中断状态获取
boolean_t Wdt_GetIrqStatus(void);
///< 运行状态获取
boolean_t Wdt_ReadwdtStatus(void);

//@} // WdtGroup

#ifdef __cplusplus
#endif

#endif /* __WDT_H__ */



