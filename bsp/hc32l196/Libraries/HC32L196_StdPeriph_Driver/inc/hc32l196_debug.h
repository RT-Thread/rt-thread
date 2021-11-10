/*******************************************************************************
* Copyright (C) 2018, Huada Semiconductor Co.,Ltd All rights reserved.
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
/******************************************************************************/
/** \file debug.h
 **
 ** Headerfile for DEBUG functions
 ** @link Debug Group Some description @endlink 
 **
 ** History:
 **   - 2018-04-15   Lux     First Version
 **
 ******************************************************************************/

#ifndef __DEBUG_H__
#define __DEBUG_H__

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "ddl.h"


#ifdef __cplusplus
extern "C"
{
#endif

/**
 ******************************************************************************
 ** \defgroup DebugGroup (DEBUG)
  **
 ******************************************************************************/
//@{

/**
 *******************************************************************************
 ** function prototypes.
 ******************************************************************************/

/******************************************************************************
 * Global type definitions
 ******************************************************************************/ 
/**
 *******************************************************************************
 ** \brief 调试模式下各模块工作状态类型定义
 ** \note
 ******************************************************************************/
typedef enum en_debug_module_active
{
    DebugMskTim0   = 0x0001u,               ///< TIM0 
    DebugMskTim1   = 0x0002u,               ///< TIM1 
    DebugMskTim2   = 0x0004u,               ///< TIM2 
    DebugMskLpTim0 = 0x0008u,               ///< LPTIM0
    DebugMskTim4   = 0x0010u,               ///< TIM4 
    DebugMskTim5   = 0x0020u,               ///< TIM5 
    DebugMskTim6   = 0x0040u,               ///< TIM6 
    DebugMskPca    = 0x0080u,               ///< PCA  
    DebugMskWdt    = 0x0100u,               ///< WDT  
    DebugMskRtc    = 0x0200u,               ///< RTC  
    DebugMskTim3   = 0x0800u,               ///< TIM3 
    DebugMskLpTim1 = 0x1000u,               ///< LPTIM1 
}en_debug_module_active_t; 
 
/*******************************************************************************
 * Global definitions
 ******************************************************************************/

/******************************************************************************
 * Global variable declarations ('extern', definition in C source)
 ******************************************************************************/

/******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/
///< 在SWD调试模式下，使能模块计数功能
en_result_t Debug_ActiveEnable(en_debug_module_active_t enModule);
///< 在SWD调试模式下，暂停模块计数功能
en_result_t Debug_ActiveDisable(en_debug_module_active_t enModule);

//@} // Debug Group

#ifdef __cplusplus
#endif

#endif /* __DEBUG_H__ */
/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/


