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
/** \file pca.h
 **
 ** PCA（可编程计数阵列）数据结构及API声明
 **  
 **
 ** History:
 **   - 2017-04-15   Husj     First version
 **
 *****************************************************************************/

#ifndef __PCA_H__
#define __PCA_H__

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
 ******************************************************************************
 ** \defgroup PcaGroup Programmable Counter Array (PCA)
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
 ** \brief PCA 模块选择数据类型重定义
 *****************************************************************************/
typedef enum en_pca_module
{
    Module0    = 0u,        ///< 模块0
    Module1    = 1u,        ///< 模块1
    Module2    = 2u,        ///< 模块2
    Module3    = 3u,        ///< 模块3
    Module4    = 4u,        ///< 模块4
}en_pca_module_t;

/**
 ******************************************************************************
 ** \brief PCA 计数启/停控制数据类型重定义 (CR)
 *****************************************************************************/
typedef enum en_pca_start
{
    CRStop  = 0u,            ///< 停止计数
    CRStart = 1u,            ///< 开始计数
}en_pca_start_t;

/**
 ******************************************************************************
 ** \brief PCA IDLE 模式下启/停控制数据类型重定义 (CIDL)
 *****************************************************************************/
typedef enum en_pca_cidl
{
    IdleGoOn = 0u,            ///< 休眠模式下 PCA继续工作
    IdleStop = 1u,            ///< 休眠模式下 PCA停止工作 
}en_pca_cidl_t;

/**
 ******************************************************************************
 ** \brief PCA 模块4 WDT功能控制数据类型重定义 (WDTE)
 *****************************************************************************/
typedef enum en_pca_wdte
{
    PCAWDTDisable = 0u,            ///< 关闭 PCA模块4 WDT功能
    PCAWDTEnable  = 1u,            ///< 启动 PCA模块4 WDT功能
}en_pca_wdte_t;

/**
 ******************************************************************************
 ** \brief PCA 时钟分频及时钟源选择功能数据类型重定义 (CPS)
 *****************************************************************************/
typedef enum en_pca_clksel
{
    PCAPCLKDiv32  = 0u,         ///< PCLK/32
    PCAPCLKDiv16  = 1u,         ///< PCLK/16
    PCAPCLKDiv8   = 2u,         ///< PCLK/8
    PCAPCLKDiv4   = 3u,         ///< PCLK/4
    PCAPCLKDiv2   = 4u,         ///< PCLK/2
    PCATimer0Over = 5u,         ///< timer0 overflow
    PCATimer1Over = 6u,         ///< timer1 overflow
    PCAECI        = 7u,         ///< ECI 外部时钟,时钟PCLK四分频采样
}en_pca_clksel_t;

/**
 ******************************************************************************
 ** \brief PCA 允许比较器功能控制数据类型重定义 (ECOM)
 *****************************************************************************/
typedef enum en_pca_ecom
{
    ECOMDisable = 0u,            ///< 禁止比较器功能
    ECOMEnable  = 1u,            ///< 允许比较器功能
}en_pca_ecom_t;

/**
 ******************************************************************************
 ** \brief PCA 正沿捕获控制位数据类型重定义 (CAPP)
 *****************************************************************************/
typedef enum en_pca_capp
{
    CAPPDisable = 0u,            ///< 禁止上升沿捕获
    CAPPEnable  = 1u,            ///< 允许上升沿捕获
}en_pca_capp_t;

/**
 ******************************************************************************
 ** \brief PCA 负沿捕获控制位数据类型重定义 (CAPN)
 *****************************************************************************/
typedef enum en_pca_capn
{
    CAPNDisable = 0u,            ///< 禁止下降沿捕获
    CAPNEnable  = 1u,            ///< 允许下降沿捕获
}en_pca_capn_t;

/**
 ******************************************************************************
 ** \brief PCA 匹配控制位数据类型重定义 (MAT)
 *****************************************************************************/
typedef enum en_pca_mat
{
    MATDisable = 0u,            ///< 禁止匹配
    MATEnable  = 1u,            ///< 允许匹配
}en_pca_mat_t;

/**
 ******************************************************************************
 ** \brief PCA 翻转控制位数据类型重定义 (TOG)
 *****************************************************************************/
typedef enum en_pca_tog
{
    TOGDisable = 0u,            ///< 禁止翻转功能
    TOGEnable  = 1u,            ///< 允许翻转功能
}en_pca_tog_t;

/**
 ******************************************************************************
 ** \brief PCA 8bit脉宽调制控制数据类型重定义 (8bitPWM)
 *****************************************************************************/
typedef enum en_pca_pwm_8_bit
{
    PCA8bitPWMDisable = 0u,            ///< 禁止 PWM功能
    PCA8bitPWMEnable  = 1u,            ///< 允许CCPx引脚作为PWM输出
}en_pca_8bit_pwm_t;

/**
 ******************************************************************************
 ** \brief PCA 16bit脉宽调制控制数据类型重定义 (16bitPWM)
 *****************************************************************************/
typedef enum en_pca_pwm_16_bit
{
    PCA16bitPWMDisable = 0u,            ///< 16bitPWM 禁止
    PCA16bitPWMEnable  = 1u,            ///< 16bitPWM 使能
}en_pca_16bit_pwm_t;

/**
 ******************************************************************************
 ** \brief PCA 配置结构体定义 
 *****************************************************************************/
typedef struct stc_pca_config
{
    en_pca_cidl_t     enCIDL;       ///< 模式下启/停控制
    en_pca_wdte_t     enWDTE;       ///< WDT功能控制
    en_pca_clksel_t   enCPS;        ///< 时钟分频及时钟源选择功能
    
    func_ptr_t        pfnPcaCb;     ///< Pca中断服务回调函数[void function(void)]
}stc_pca_config_t;

/**
 ******************************************************************************
 ** \brief PCA 捕获模式配置结构体定义 
 *****************************************************************************/
typedef struct stc_pca_capmodconfig
{
    en_pca_ecom_t enECOM;                ///< 允许比较器功能控制
    en_pca_capp_t enCAPP;                ///< 正沿捕获控制
    en_pca_capn_t enCAPN;                ///< 负沿捕获控制
    en_pca_mat_t  enMAT;                 ///< 匹配控制
    en_pca_tog_t  enTOG;                 ///< 翻转控制
    en_pca_8bit_pwm_t  en8bitPWM;        ///< 8位脉宽调制控制
}stc_pca_capmodconfig_t;

/******************************************************************************
 * Global variable declarations ('extern', definition in C source)
 *****************************************************************************/

/******************************************************************************
 * Global function prototypes (definition in C source)
 *****************************************************************************/
//Interrupt related
//PCA中断标志获取
boolean_t Pca_GetIntFlag(en_pca_module_t enModule);
//PCA计数器中断标志获取
boolean_t Pca_GetCntIntFlag(void);
//PCA中断标志清除
en_result_t Pca_ClearIntFlag(en_pca_module_t enModule);
//PCA计数器中断标志清除
en_result_t Pca_ClearCntIntFlag(void);
//PCA中断使能
en_result_t Pca_EnableIrq (en_pca_module_t enModule);
//PCA计数器中断使能
en_result_t Pca_EnableCntIrq (void);
//PCA中断关闭
en_result_t Pca_DisableIrq(en_pca_module_t enModule);
//PCA计数器中断关闭
en_result_t Pca_DisableCntIrq(void);

//PCA配置及操作
//PCA初始化
en_result_t Pca_Init(stc_pca_config_t* pstcConfig);
//PCA捕获模式配置
en_result_t Pca_CapModConfig(en_pca_module_t enModule, stc_pca_capmodconfig_t* pstcCapMod);
//PCA计数器启动/停止
en_result_t Pca_Run(void);
en_result_t Pca_Stop(void);
//PCA16位比较数据设置
en_result_t Pca_CmpData16Set(en_pca_module_t enModule, uint16_t u16Data);
//PCA捕获16位数据获取
uint16_t Pca_CapData16Get(en_pca_module_t enModule);
//PCA比较数据高8位设置
en_result_t Pca_CmpDataHSet(en_pca_module_t enModule, uint8_t u8Data);
//PCA比较数据低8位设置
en_result_t Pca_CmpDataLSet(en_pca_module_t enModule, uint8_t u8Data);
//PCA计数值设置/获取
en_result_t Pca_Cnt16Set(uint16_t u16Data);
uint16_t Pca_Cnt16Get(void);
//PCA周期重载值设置/获取
en_result_t Pca_CARRSet(uint16_t u16Data);
uint16_t Pca_CARRGet(void);
//PCA 增强PWM功能使能/禁止
en_result_t Pca_Enable16bitPWM(void);
en_result_t Pca_Disable16bitPWM(void);
//PCA比较高速输出标志获取
boolean_t Pca_GetCmpHighFlag(en_pca_module_t enModule);
//@} // PcaGroup

#ifdef __cplusplus
#endif


#endif /* __PCA_H__ */
/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/


