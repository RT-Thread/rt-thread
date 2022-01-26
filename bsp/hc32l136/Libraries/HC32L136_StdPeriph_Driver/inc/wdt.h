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
#include "interrupts_hc32l136.h"

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
typedef enum en_wdt_reset
{
    WRESET_EN    = 0,///<复位使能
    WINT_EN      = 1,///<中断使能
}en_wdt_reset_t;
/**
 ******************************************************************************
 ** \brief wdt当前运行状态
 *****************************************************************************/

typedef enum en_wdt_status
{
    Stop_Mode    = 0,///<停止模块
    Run_Mode     = 1,///<正常运行模式
}en_wdt_status_t;

/**
 ******************************************************************************
 ** \brief wdt总体配置，定时时间 、中断函数等
 *****************************************************************************/

typedef struct stc_wdt_config
{
    uint8_t          u8LoadValue;   ///<溢出时间      
    en_wdt_reset_t   enResetEnable;  ///<中断或复位使能       
    func_ptr_t       pfnWdtIrqCb;   ///<中断服务接口函数
} stc_wdt_config_t;
//wdt初始化
en_result_t Wdt_Init(stc_wdt_config_t* pstcConfig);
void Wdt_DeInit(void);

//wdt开始和停止
en_result_t Wdt_Start(void);

//wdt溢出时间设置及当前计数时间、状态读取
void Wdt_WriteWdtLoad(uint8_t u8LoadValue);
uint8_t Wdt_ReadWdtValue(void);
uint8_t Wdt_ReadwdtStatus(void);

//喂狗处理
void Wdt_Feed(void);

//@} // WdtGroup

#ifdef __cplusplus
#endif

#endif /* __WDT_H__ */



