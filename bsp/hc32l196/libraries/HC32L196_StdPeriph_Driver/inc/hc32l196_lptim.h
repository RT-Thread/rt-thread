/******************************************************************************
* Copyright (C) 2019, Huada Semiconductor Co.,Ltd All rights reserved.
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
/** \file lptim.h
 **
 ** 
 **  
 **
 ** History:
 **   - 2019-04-09        First version
 **
 *****************************************************************************/
#ifndef __LPTIM_H__
#define __LPTIM_H__

/*****************************************************************************
 * Include files
 *****************************************************************************/
#include "ddl.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 *******************************************************************************
 ** \brief LPTIMx  预除频 
 ** \note  LPTIMx_CR  PRS     在定时器运行时不可以更改该值
 ******************************************************************************/
typedef enum
{
    LptimPrsDiv1   = 0,       // 1分频
    LptimPrsDiv2   = 1,       // 2分频
    LptimPrsDiv4   = 2,       // 4分频
    LptimPrsDiv8   = 3,       // 8分频
    LptimPrsDiv16  = 4,       // 16分频
    LptimPrsDiv32  = 5,       // 32分频
    LptimPrsDiv64  = 6,       // 64分频
    LptimPrsDiv256 = 7        // 256分频
}en_lptim_prs_t;

/**
 *******************************************************************************
 ** \brief LPTIMx  时钟选择
 ** \note  LPTIMx_CR  TCK_SEL    
 ******************************************************************************/
typedef enum
{
    LptimPclk   = 0,
    LptimXtl    = 2,
    LptimRcl    = 3
}en_lptim_tcksel_t;

/**
 *******************************************************************************
 ** \brief LPTIMx  GATE极性控制位
 ** \note  LPTIMx_CR  GATE_P   
 ******************************************************************************/
typedef enum
{
    LptimGatePLow  = 0,
    LptimGatePHigh = 1
}en_lptim_gatep_t;

/**
 *******************************************************************************
 ** \brief LPTIMx  时钟选择
 ** \note  LPTIMx_CR  GATE   
 ******************************************************************************/
typedef enum
{
    LptimGateLow  = 0,
    LptimGateHigh = 1
}en_lptim_gate_t;

/**
 *******************************************************************************
 ** \brief LPTIMx  TOG输出使能位
 ** \note  LPTIMx_CR  TOG  
 ******************************************************************************/
typedef enum
{
    LptimTogEnLow  = 0,
    LptimTogEnHigh = 1
}en_lptim_togen_t;

/**
 *******************************************************************************
 ** \brief LPTIMx  CT计数器/定时器功能选择
 ** \note  LPTIMx_CR  CT
 ******************************************************************************/
typedef enum
{
    LptimTimerFun = 0,  //警示器功能，定时器使用TCK_SEL选择的时钟进行计数
    LptimCntFun   = 1   //计数器功能，计数器使用外部输入的下降沿进行计数，采样时钟使用TCK_SEL选择的时钟
}en_lptim_ct_t;

/**
 *******************************************************************************
 ** \brief LPTIMx  定时器工作模式
 ** \note  LPTIMx_CR  MD
 ******************************************************************************/
typedef enum
{
    LptimMode1 = 0,  //模式1无重载16位计数器/定时器
    LptimMode2 = 1   //模式2自动重载16位计数器/定时器
}en_lptim_md_t;

/**
 *******************************************************************************
 ** \brief LPTIMx 初始化配置的结构体
 ** \note       
 ******************************************************************************/
typedef struct
{
    en_lptim_prs_t       enPrs;
    en_lptim_tcksel_t    enTcksel;
    en_lptim_gatep_t     enGatep;
    en_lptim_gate_t      enGate;
    en_lptim_togen_t     enTogen;
    en_lptim_ct_t        enCt;
    en_lptim_md_t        enMd;
    uint16_t             u16Arr;
}stc_lptim_cfg_t;

/******************************************************************************
 * Global variable declarations ('extern', definition in C source)
 *****************************************************************************/

/******************************************************************************
 * Global function prototypes (definition in C source)
 *****************************************************************************/
extern void Lptim_ConfIt(M0P_LPTIMER_TypeDef* Lptimx, boolean_t NewStatus);
extern void Lptim_Cmd(M0P_LPTIMER_TypeDef* Lptimx, boolean_t NewStatus);
extern boolean_t Lptim_GetItStatus(M0P_LPTIMER_TypeDef* Lptimx);
extern void Lptim_ClrItStatus(M0P_LPTIMER_TypeDef* Lptimx);
extern en_result_t Lptim_Init(M0P_LPTIMER_TypeDef* Lptimx, stc_lptim_cfg_t* InitStruct);

#ifdef __cplusplus
#endif

#endif //__LPTIM_H__
/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/
