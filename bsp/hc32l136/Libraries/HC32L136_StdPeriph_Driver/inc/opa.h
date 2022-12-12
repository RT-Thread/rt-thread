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
/** \file OPA.h
 **
 ** Headerfile for OPA functions
 ** @link OPA Group Some description @endlink 
 **
 ** History:
 **   - 2018-04-15   Devi     First Version
 **
 ******************************************************************************/

#ifndef __OPA_H__
#define __OPA_H__

/*******************************************************************************
 * Include files
 ******************************************************************************/
#include "ddl.h"
#include "interrupts_hc32l136.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 ******************************************************************************
 ** \defgroup OPAGroup  (OPA)
  **
 ******************************************************************************/
//@{

/**
 *******************************************************************************
 ** function prototypes.
 ******************************************************************************/
/**
 *******************************************************************************
 ** \brief OPA通道选择
 ** \note
 ******************************************************************************/
typedef enum en_opa_channel
{
    OPA0 = 0u, ///<<OPA0
    OPA1 = 1u, ///<<OPA1
    OPA2 = 2u, ///<<OPA2
}en_opa_channel_t;

/**
 *******************************************************************************
 ** \brief OPA反向增益选择
 ** \note
 ******************************************************************************/
typedef enum en_opa_invert_pagagain
{
    Gain15         = 0u,               ///< 反向增益15倍
    Gain07         = 1u,               ///< 反向增益7倍
    Gain13_3       = 2u,               ///< 反向增益13/3倍
    Gain03         = 3u,               ///< 反向增益3倍
    Gain05_3       = 4u,               ///< 反向增益5/3倍
    Gain01         = 5u,               ///< 反向增益1倍
    Gain01_3        = 6u,               ///< 反向增益1/3倍
    Gain11_5       = 7u,               ///< 反向增益11/5倍   
}en_opa_invert_pagagain_t;

/**
 *******************************************************************************
 ** \brief OPA正向增益选择
 ** \note
 ******************************************************************************/
typedef enum en_opa_noinvert_pagagain
{
    Gain16         = 0u,               ///< 正向增益16倍
    Gain08         = 1u,               ///< 正向增益8倍
    Gain16_3       = 2u,               ///< 正向增益16/3倍
    Gain04         = 3u,               ///< 正向增益4倍
    Gain08_3       = 4u,               ///< 正向增益8/3倍
    Gain02         = 5u,               ///< 正向增益2倍
    Gain04_3       = 6u,               ///< 正向增益4/3倍
    Gain16_5       = 7u,               ///< 正向增益16/5倍   
}en_opa_noinvert_pagagain_t;

/**
 *******************************************************************************
 ** \brief 仪表增益配置
 ******************************************************************************/
typedef enum opa_metergain
{
    OpaMeterGain3 = 0u,                        
    OpaMeterGain1_3 = 1u,               
    OpaMeterGain1 = 2u,                             
}en_opa_metergain_t;


/**
 *******************************************************************************
 ** \brief opa 模式选择
 ******************************************************************************/
typedef enum opa_modesel
{
    OpaUintMode     = 0u,           ///< PGA单位增益        
    OpaForWardMode  = 1u,           ///< 正向输入PGA            
    OpaOppositeMode = 2u,           ///< 反向输入PGA              
    OpaThreeOppMode = 3u,           ///< 3个OPA级联反向输入PGA
    OpaThreeForMode = 4u,           ///< 3个OPA级联正向输入PGA
    OpaDiffMode     = 5u,           ///< 两运放差分输入PGA
    OpaMeterMode    = 6u,           ///< 仪表放大器
    OpaGpMode       = 7u,           ///< 通用运放       
}en_opa_modesel_t;

/**
 *******************************************************************************
 ** \brief opa 校正模式
 ******************************************************************************/
typedef enum opa_calsel
{
    OpaSoftMode         = 0u,           ///< 软件控制     
    OpaSoftTriggerMode  = 1u,           ///< 软件触发      
    OpaADCTriggerMode   = 2u,           ///< ADC触发                  
}en_opa_calsel_t;

/**
 ******************************************************************************
 ** \brief OPA增益配置
 *****************************************************************************/
typedef struct stc_opa_gain_config
{
    en_opa_invert_pagagain_t     enInGain;  ///< 反向增益
    en_opa_noinvert_pagagain_t   enNoInGain;  ///< 正向增益
}stc_opa_gain_config_t;


/******************************************************************************
 * Global variable declarations ('extern', definition in C source)
 ******************************************************************************/

/******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/
///< OPA初始化
en_result_t OPA_Init(void);
///< OPA去初始化
en_result_t OPA_DeInit(void);
///< OPA基本功能设置
en_result_t OPA_Operate(en_opa_channel_t enchannel ,en_opa_modesel_t enMode,stc_opa_gain_config_t *pstrGain);
///< OPA三级联设置
en_result_t OPA_ThreeOperate(en_opa_modesel_t enMode,stc_opa_gain_config_t *pstrGain0,stc_opa_gain_config_t *pstrGain1,stc_opa_gain_config_t *pstrGain2);
///< OPA 仪表模式
en_result_t OPA_MeterOperate(en_opa_metergain_t enGainMode);
///< OPA校正模式
en_result_t OPA_Cal(en_opa_calsel_t enCalMode);


//@} // OPA Group

#ifdef __cplusplus
#endif

#endif /* __OPA_H__ */
/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/


