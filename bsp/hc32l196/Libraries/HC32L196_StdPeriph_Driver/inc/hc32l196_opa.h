/*******************************************************************************
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
/******************************************************************************/
/** \file OPA.h
 **
 ** Headerfile for OPA functions
 ** @link OPA Group Some description @endlink 
 **
 ** History:
 **   - 2019-04-11       First Version
 **
 ******************************************************************************/

#ifndef __OPA_H__
#define __OPA_H__

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
 ** \defgroup OPAGroup  (OPA)
  **
 ******************************************************************************/
//@{

/**
 *******************************************************************************
 ** function prototypes.
 ******************************************************************************/

typedef enum en_opa_oenx
{
    OpaOen1  = 3u,            //OUT1
    OpaOen2  = 4u,            //OUT2
    OpaOen3  = 5u,            //OUT3
    OpaOen4  = 6u             //OUT4
}en_opa_oenx_t;
 
typedef enum en_opa_clksrc    // 自动校准脉冲宽度设置
{
    OpaM1Pclk     = 0u,       // 1个PCLK周期
    OpaM2Pclk     = 1u,       // 2个PCLK周期
    OpaM4Pclk     = 2u,       // 4个PCLK周期
    OpaM8Pclk     = 3u,       // 8个PCLK周期
    OpaM16Pclk    = 4u,       // 16个PCLK周期
    OpaM32Pclk    = 5u,       // 32个PCLK周期
    OpaM64Pclk    = 6u,       // 64个PCLK周期
    OpaM128Pclk   = 7u,       // 128个PCLK周期
    OpaM256Pclk   = 8u,       // 256个PCLK周期
    OpaM512Pclk   = 9u,       // 512个PCLK周期
    OpaM1024Pclk  = 10u,      // 1024个PCLK周期
    OpaM2048Pclk  = 11u,      // 2048个PCLK周期
    OpaM4096Pclk  = 12u       // 4096个PCLK周期
}en_opa_clksrc_t;

typedef enum en_opa_set0ctrl
{
    enClkSwSet = 3u,          // 软件校准使能
    enAzPulse  = 2u,          // 软件校准
    enTrigger  = 1u,          // 软件触发自动教零
    enAdctr    = 1u           // 使能ADC启动触发OPA自动校准功能
}en_opa_set0ctrl_t;

typedef struct
{
    boolean_t         bAzen;        // 自动教零配置
    boolean_t         bClk_sw_set;  // 自动教零选择
    boolean_t         bAz_pulse;    // 软件校准设置
    boolean_t         bTrigger;     // 软件触发校准设置
    boolean_t         bAdctr_en;    // ADC启动触发OPA自动校准设置
    en_opa_clksrc_t   enClksrc;     // 自动校准脉冲宽度设置
}stc_opa_zcfg_t;    


/******************************************************************************
 * Global variable declarations ('extern', definition in C source)
 ******************************************************************************/

/******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/
//OPA 通道使能
extern void Opa_Cmd(boolean_t NewStatus);
extern void Opa_CmdBuf(boolean_t NewStatus);

//OPA零点校准配置
extern void Opa_SetZero(stc_opa_zcfg_t* InitZero);

//使能输出OUTX
extern void Opa_CmdOnex(en_opa_oenx_t onex, boolean_t NewState);

//配置校零相关的位
extern void Opa_ZeroBitCtrl(en_opa_set0ctrl_t CtrlBit, boolean_t NewState);

//@} // OPA Group

#ifdef __cplusplus
#endif

#endif /* __OPA_H__ */
/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/


