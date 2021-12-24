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
/** \file lpt.h
 **
 ** 低功耗定时器数据结构及API声明
 **  
 **
 ** History:
 **   - 2018-04-15   Husj     First version
 **
 *****************************************************************************/

#ifndef __LPT_H__
#define __LPT_H__

/*****************************************************************************
 * Include files
 *****************************************************************************/
#include "ddl.h"
#include "interrupts_hc32l136.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 *******************************************************************************
 ** \defgroup LptGroup Low Power Timer (LPT)
 **
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
 ** \brief GATE 极性控制数据类型重定义 (GATE_P)
 *****************************************************************************/
typedef enum en_lpt_gatep
{
    LptActHighLevel = 0u,            ///< 高电平有效
    LptActLowLevel  = 1u,            ///< 低电平有效
}en_lpt_gatep_t;

/**
 ******************************************************************************
 ** \brief 定时器门控数据类型重定义 (GATE)
 *****************************************************************************/
typedef enum en_lpt_gate
{
    LptGateDisable = 0u,            ///< 无门控
    LptGateEnable  = 1u,            ///< 门控使能
}en_lpt_gate_t;

/**
 ******************************************************************************
 ** \brief Lptimer 时钟选择数据类型重定义 (TCK_SEL)
 *****************************************************************************/
typedef enum en_lpt_clksel
{
    LptPCLK   = 0u,           ///< PCLK
    LptXIL32K = 2u,           ///< XIL32K
    LptIRC32K = 3u,           ///< IRC32K
}en_lpt_clksel_t;

/**
 ******************************************************************************
 ** \brief 翻转输出使能数据类型重定义 (TOG_EN)
 *****************************************************************************/
typedef enum en_lpt_toggle
{
    LptTogDisable = 0u,            ///< 翻转输出禁止
    LptTogEnable  = 1u,            ///< 翻转输出使能
}en_lpt_toggle_t;

/**
 ******************************************************************************
 ** \brief 计数/定时器功能选择数据类型重定义 (CT)
 *****************************************************************************/
typedef enum en_lpt_function
{
    LptTimer   = 0u,            ///< 定时器功能
    LptCounter = 1u,            ///< 计数器功能
}en_lpt_function_t;


/**
 ******************************************************************************
 ** \brief 定时器工作模式数据类型重定义 (MD)
 *****************************************************************************/
typedef enum en_lpt_mode
{
    Lpt16bitFreeMode  = 0u,         ///< 无重载16位计数器/定时器
    Lpt16bitArrMode   = 1u,         ///< 自动重装载16位计数器/定时器
}en_lpt_mode_t;

/**
 ******************************************************************************
 ** \brief 定时器运行控制数据类型重定义 (TR)
 *****************************************************************************/
typedef enum en_lpt_start
{
    LptTRDisable = 0u,            ///< 停止
    LptTREnable  = 1u,            ///< 运行
}en_lpt_start_t;

/**
 ******************************************************************************
 ** \brief Lptimer 配置结构体定义 
 *****************************************************************************/
typedef struct stc_lpt_config
{
    en_lpt_gatep_t    enGateP;      ///< 门控极性控制
    en_lpt_gate_t     enGate;       ///< 门控使能
    en_lpt_clksel_t   enTckSel;     ///< 时钟选择
    en_lpt_toggle_t   enTog;        ///< 翻转输出使能
    en_lpt_function_t enCT;         ///< 定时/计数模式选择
    en_lpt_mode_t     enMD;         ///< 工作模式选择
    
    func_ptr_t pfnLpTimCb;          ///< LpTimer中断服务回调函数[void function(void)]
}stc_lpt_config_t;


/******************************************************************************
 * Global variable declarations ('extern', definition in C source)
 *****************************************************************************/

/******************************************************************************
 * Global function prototypes (definition in C source)
 *****************************************************************************/
//中断相关函数 
//中断标志获取
boolean_t Lpt_GetIntFlag(void);
//中断标志清除
en_result_t Lpt_ClearIntFlag(void);
//中断使能/禁止
en_result_t Lpt_EnableIrq (void);
en_result_t Lpt_DisableIrq(void);

//初始化及相关功能操作
//Lptimer配置及初始化
en_result_t Lpt_Init(stc_lpt_config_t* pstcConfig);
//Lptimer 启动/停止
en_result_t Lpt_Run(void);
en_result_t Lpt_Stop(void);
//重载值设置
en_result_t Lpt_ARRSet(uint16_t u16Data);
//计数值获取
en_result_t Lpt_Cnt16Set(uint16_t u16Data);
uint16_t Lpt_Cnt16Get(void);

//@} // LptGroup

#ifdef __cplusplus
#endif


#endif /* __LPT_H__ */
/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/


