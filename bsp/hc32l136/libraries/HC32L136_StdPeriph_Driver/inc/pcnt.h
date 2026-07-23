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
/** \file pcnt.h
 **
 ** Headerfile for PCNT functions
 ** @link PCNT Group Some description @endlink 
 **
 ** History:
 **   - 2018-04-15   Devi     First Version
 **
 ******************************************************************************/

#ifndef __PCNT_H__
#define __PCNT_H__

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
 ** \brief PCNT S1通道极性选择
 ** \note
 ******************************************************************************/
typedef enum en_pcnt_s1sel
{
    S1P_Noinvert = 0u, ///<<S1通道极性不取反
    S1P_Invert   = 1u, ///<<S1通道极性取反
}en_pcnt_s1sel_t;

/**
 *******************************************************************************
 ** \brief PCNT S0通道极性选择
 ** \note
 ******************************************************************************/
typedef enum en_pcnt_s0sel
{
    S0P_Noinvert = 0u, ///<<S0通道极性不取反
    S0P_Invert   = 1u, ///<<S0通道极性取反
}en_pcnt_s0sel_t;

/**
 *******************************************************************************
 ** \brief PCNT 计数方向选择
 ** \note
 ******************************************************************************/
typedef enum en_pcnt_direcsel
{
    Direct_Add   = 0u, ///<<加计数
    Direct_Sub   = 1u, ///<<减计数
}en_pcnt_direcsel_t;

/**
 *******************************************************************************
 ** \brief PCNT 计数时钟选择
 ** \note
 ******************************************************************************/
typedef enum en_pcnt_clksel
{
    CLK_Pclk   = 1u, ///<<PCLK
    CLK_Xtl    = 2u, ///<<XTL
    CLK_Rcl    = 3u, ///<<RCL     
}en_pcnt_clksel_t;

/**
 *******************************************************************************
 ** \brief PCNT 脉冲计数模式选择
 ** \note
 ******************************************************************************/
typedef enum en_pcnt_modesel
{
    Single_Mode   = 1u, ///<<单通道脉冲计数模式
    Special_Mode  = 2u, ///<<双通道非正交脉冲计数模式
    Double_Mode   = 3u, ///<<双通道正交脉冲计数模式  
}en_pcnt_modesel_t;

/**
 ******************************************************************************
 ** \brief PCNT 状态
 *****************************************************************************/
typedef enum en_pcnt_status
{
    PCNT_S1E            = 0x80,   ///<S1通道脉冲解码错误
    PCNT_S0E            = 0x40,   ///<S0通道脉冲解码错误   
    PCNT_BB             = 0x20,   ///<脉冲解码错误    
    PCNT_FE             = 0x10,   ///<采样周期脉冲解码错误
    PCNT_DIR            = 0x08,   ///<反向改变中断    
    PCNT_TO             = 0x04,   ///<超时中断标识   
    PCNT_OV             = 0x02,   ///<上溢中断标识
    PCNT_UF             = 0x01,   ///<下溢中断标识     
}en_pcnt_status_t;

/**
 ******************************************************************************
 ** \brief PCNT 整体配置结构体
 *****************************************************************************/
typedef struct stc_pcnt_config
{
    en_pcnt_s1sel_t     bS1Sel;          ///< S1通道极性选择
	  en_pcnt_s0sel_t     bS0Sel;          ///< S0通道极性选择
    en_pcnt_direcsel_t  u8Direc;         ///< 计数方向选择    	
	  en_pcnt_clksel_t    u8Clk;           ///< 计数时钟选择
    en_pcnt_modesel_t   u8Mode;          ///< 脉冲计数模式选择
    boolean_t           bFLTEn;          ///< 滤波控制使能
    uint8_t             u8FLTDep;        ///< 滤波阀值
    uint8_t             u8FLTClk;        ///< 滤波时钟
    boolean_t           bTOEn;           ///< 超时使能
    uint16_t            u16TODep;         ///< 超时阀值
	  uint8_t             u8IrqStatus;     ///< 中断方式
    boolean_t           bIrqEn;           ///< 中断使能
    func_ptr_t          pfnIrqCb;         ///< 中断回调函数
}stc_pcnt_config_t;

//PCNT 中断
void Pcnt_IRQHandler(void);

/******************************************************************************
 * Global variable declarations ('extern', definition in C source)
 ******************************************************************************/

/******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/
///< PCNT初始化
en_result_t PCNT_Init(stc_pcnt_config_t*  pstcPcntConfig);
///< PCNT去初始化
void PCNT_DeInit(void);
///< PCNT 参数设置
en_result_t PCNT_Parameter(uint8_t start,uint8_t end);
///< PCNT 读取PCNT 方向
en_pcnt_direcsel_t PCNT_Direction(void);
///< PCNT 读取PCNT 计数值
uint16_t PCNT_Count(void);
///< PCNT 读取PCNT 溢出值
uint16_t PCNT_TopCount(void);
///< PCNT 设置PCNT
void PCNT_Run(boolean_t work);
///< PCNT获取状态
boolean_t PCNT_GetStatus(en_pcnt_status_t enStatus);
///< PCNT清除状态
void PCNT_ClrStatus(en_pcnt_status_t enStatus);
///< PCNT设置中断
void PCNT_SetIrqStatus(en_pcnt_status_t enStatus);


//@} // PCNT Group

#ifdef __cplusplus
#endif

#endif /* __PCNT_H__ */
/*******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/


