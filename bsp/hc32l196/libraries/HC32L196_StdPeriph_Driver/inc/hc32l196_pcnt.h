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
/** \file pcnt.h
 **
 ** Headerfile for PCNT functions
 ** @link PCNT Group Some description @endlink 
 **
 ** History:
 **   - 2019-04-08        First Version
 **
 ******************************************************************************/

#ifndef __PCNT_H__
#define __PCNT_H__

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
 ** \defgroup PCNTGroup  (PCNT)
  **
 ******************************************************************************/
//@{

/**
 *******************************************************************************
 ** function prototypes.
 ******************************************************************************/


/**
 *******************************************************************************
 ** \brief PCNT S0通道极性选择
 ** \note           PCNT_CTRL  S0P
 ******************************************************************************/
typedef enum 
{
    PcntS0PNoinvert = 0u, //  S0通道极性不取反
    PcntS0PInvert   = 1u  //  S0通道极性取反
}en_pcnt_s0polar_t;

/**
 *******************************************************************************
 ** \brief PCNT S1通道极性选择
 ** \note           PCNT_CTRL  S1P
 ******************************************************************************/
typedef enum 
{
    PcntS1PNoinvert = 0u, //  S1通道极性不取反
    PcntS1PInvert   = 1u  //  S1通道极性取反
}en_pcnt_s1polar_t;

/**
 *******************************************************************************
 ** \brief PCNT 计数方向选择
 ** \note           PCNT_CTRL  DIR
 ******************************************************************************/
typedef enum 
{
    PcntNDoubleDirAdd  = 0u, //  加计数
    PcntNDoubleDirSub  = 1u  //  减计数
}en_pcnt_dir_t;

/**
 *******************************************************************************
 ** \brief PCNT 计数时钟选择
 ** \note           PCNT_CTRL  ClkSel
 ******************************************************************************/
typedef enum 
{
    PcntCLKPclk   = 1u, //  PCLK
    PcntCLKXtl    = 2u, //  XTL
    PcntCLKRcl    = 3u  //  RCL     
}en_pcnt_clksel_t;

/**
 *******************************************************************************
 ** \brief PCNT 脉冲计数模式选择
 ** \note           PCNT_CTRL  Mode
 ******************************************************************************/
typedef enum 
{
    PcntSingleMode   = 1u, // 单通道脉冲计数模式
    PcntSpecialMode  = 2u, // 双通道非正交脉冲计数模式
    PcntDoubleMode   = 3u  // 双通道正交脉冲计数模式  
}en_pcnt_mode_t;

/**
 ******************************************************************************
 ** \brief PCNT 状态
 ** \note           PCNT_IFR  & PCNT_ICR  &  PCNT_IEN
 *****************************************************************************/
typedef enum 
{
    PcntS1E            = 7,   // S1通道脉冲解码错误
    PcntS0E            = 6,   // S0通道脉冲解码错误   
    PcntBB             = 5,   // 脉冲解码错误    
    PcntFE             = 4,   // 采样周期脉冲解码错误
    PcntDIR            = 3,   // 反向改变中断    
    PcntTO             = 2,   // 超时中断标识   
    PcntOV             = 1,   // 上溢中断标识
    PcntUF             = 0,   // 下溢中断标识     
}en_pcnt_itfce_t;

/**
 ******************************************************************************
 ** \brief PCNT 状态寄存器1   PCNT_SR1
 ** \note           PCNT_SR1 : DIR
 *****************************************************************************/
typedef enum
{
    PcntDoubleDirAdd = 0,     //  双通道正交脉冲加计数
    PcntDoubleDirSub = 1      //  双通道正交脉冲加计数
}en_pcnt_sr1dir_t;

/**
 ******************************************************************************
 ** \brief PCNT 观测输出选择寄存器   PCNT_DBG
 ** \note           PCNT_DBG: DBG
 *****************************************************************************/
typedef enum
{
    PcntDBGZero = 0,     //  固定为0
    PcntDBGSxA  = 1,     //  脉冲同步之后通过S0A/S1A输出
    PcntDBGSxP  = 2,     //  脉冲极性选择之后通过S0P/S1P输出
    PcntDBGSxPF = 3      //  脉冲滤波之后通过S0PF/S1PF输出
}en_pcnt_dbg_t;

typedef enum
{
    PcntDirUp   = 0,   //加计数
    PcntDirDown = 1    //减计数
}en_pent_dir_t;
/**
 ******************************************************************************
 ** \brief PCNT 整体配置结构体
 *****************************************************************************/
typedef struct stc_pcnt_cfg
{
    en_pcnt_s0polar_t   Pcnt_S0Sel;         //  S0通道极性选择
    en_pcnt_s1polar_t   Pcnt_S1Sel;         //  S1通道极性选择       
    en_pcnt_clksel_t    Pcnt_Clk;           //  计数时钟选择
    en_pcnt_mode_t      Pcnt_Mode;          //  脉冲计数模式选择
    boolean_t           Pcnt_FltEn;         //  脉冲宽度滤波器使能控制  PCNT_FLT: EN 
    uint8_t             Pcnt_DebTop;        //  计数器阀值   PCNT_FLT: DebTop
    uint16_t            Pcnt_ClkDiv;        //  滤波时钟分频系数  PCNT_FLT: ClkDiv
    boolean_t           Pcnt_TocrEn;        //  超时功能使能控制位    PCNT_TOCR  : EN
    uint16_t            Pcnt_TocrTh;        //  超时阈值      PCNT_TOCR  :  TH
    en_pcnt_dbg_t       Pcnt_Dbg;           //  观测输出选择寄存器   PCNT_DBG
    en_pent_dir_t       Pcnt_Dir;
}stc_pcnt_initstruct_t;


/******************************************************************************
 * Global variable declarations ('extern', definition in C source)
 ******************************************************************************/

/******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/
extern boolean_t Pcnt_Cmd(boolean_t NewState);
extern en_result_t Pcnt_SetB2T(uint16_t value);
extern en_result_t Pcnt_SetB2C(uint16_t value);
extern en_result_t Pcnt_SetT2C(void);
extern void Pcnt_Init(stc_pcnt_initstruct_t*  InitStruct);
extern void Pcnt_ItCfg(en_pcnt_itfce_t IT_Src, boolean_t NewState);
extern boolean_t Pcnt_GetItStatus(en_pcnt_itfce_t IT_Src);
extern void Pcnt_ClrItStatus(en_pcnt_itfce_t IT_Src);
extern uint16_t Pcnt_GetCnt(void);
extern uint16_t Pcnt_GetTop(void);
extern uint16_t Pcnt_GetBuf(void);
extern void Pcnt_SetCnt(uint16_t value);
extern void Pcnt_SetBuf(uint16_t value);
extern void Pcnt_SetTop(uint16_t value);
//@} // PCNT Group

#ifdef __cplusplus
#endif

#endif /* __PCNT_H__ */
/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/


