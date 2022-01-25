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
/** \file bt.h
 **
 ** 基本定时器数据结构及API声明
 ** @link BT Timer3 Group Some description @endlink
 **
 ** History:
 **   - 2018-04-29   Husj     First Version
 **
 *****************************************************************************/

#ifndef __TIMER0_H__
#define __TIMER0_H__

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
 ** \defgroup Tim0Group Base Timer (BT)
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
 ** \brief Timer3 通道定义
 *****************************************************************************/
typedef enum en_tim0_channel
{
    Tim0CH0  = 0u,        ///< Timer3通道0
    Tim0CH1  = 1u,        ///< Timer3通道1
    Tim0CH2  = 2u,        ///< Timer3通道2
}en_tim0_channel_t;

/**
 ******************************************************************************
 ** \brief 工作模式选择数据类型重定义 (MODE)(模式0/1/23)
 *****************************************************************************/
typedef enum en_tim0_work_mode
{
    Tim0WorkMode0  = 0u,         ///< 定时器模式
    Tim0WorkMode1  = 1u,         ///< PWC模式
    Tim0WorkMode2  = 2u,         ///< 锯齿波模式
    Tim0WorkMode3  = 3u,         ///< 三角波模式
}en_tim0_work_mode_t;

/**
 ******************************************************************************
 ** \brief 极性控制数据类型重定义 (GATE_P)(模式0)
 *****************************************************************************/
typedef enum en_tim0_m0cr_gatep
{
    Tim0GatePositive = 0u,            ///< 高电平有效
    Tim0GateOpposite = 1u,            ///< 低电平有效
}en_tim0_m0cr_gatep_t;

/**
 ******************************************************************************
 ** \brief TIM3 预除频选择 (PRS)(模式0/1/23)
 *****************************************************************************/
typedef enum en_tim0_cr_timclkdiv
{
    Tim0PCLKDiv1   = 0u,           ///< Div 1
    Tim0PCLKDiv2   = 1u,           ///< Div 2
    Tim0PCLKDiv4   = 2u,           ///< Div 4
    Tim0PCLKDiv8   = 3u,           ///< Div 8
    Tim0PCLKDiv16  = 4u,           ///< Div 16
    Tim0PCLKDiv32  = 5u,           ///< Div 32
    Tim0PCLKDiv64  = 6u,           ///< Div 64
    Tim0PCLKDiv256 = 7u,           ///< Div 256
}en_tim0_cr_timclkdiv_t;

/**
 ******************************************************************************
 ** \brief 计数/定时器功能选择数据类型重定义 (CT)(模式0/1/23)
 *****************************************************************************/
typedef enum en_tim0_cr_ct
{
    Tim0Timer   = 0u,            ///< 定时器功能，计数时钟为内部PCLK
    Tim0Counter = 1u,            ///< 计数器功能，计数时钟为外部ETR
}en_tim0_cr_ct_t;


/**
 ******************************************************************************
 ** \brief 定时器工作模式数据类型重定义 (MD)(模式0)
 *****************************************************************************/
typedef enum en_tim0_m0cr_md
{
    Tim032bitFreeMode  = 0u,         ///< 32位计数器/定时器
    Tim016bitArrMode  = 1u,         ///< 自动重装载16位计数器/定时器
}en_tim0_m0cr_md_t;

/**
 ******************************************************************************
** \brief TIM3中断类型数据类型重定义(模式0/1/23)
 *****************************************************************************/
typedef enum en_tim0_irq_type
{
    Tim0UevIrq   = 0u,         ///< 溢出/事件更新中断
    Tim0CA0Irq   = 2u,         ///< CH0A捕获/比较中断(仅模式1/23存在)
    Tim0CA1Irq   = 3u,         ///< CH1A捕获/比较中断(仅模式23存在)
    Tim0CA2Irq   = 4u,         ///< CH2A捕获/比较中断(仅模式23存在)
    Tim0CB0Irq   = 5u,         ///< CH0B捕获/比较中断(仅模式23存在)
    Tim0CB1Irq   = 6u,         ///< CH1B捕获/比较中断(仅模式23存在)
    Tim0CB2Irq   = 7u,         ///< CH2B捕获/比较中断(仅模式23存在)
    Tim0CA0E     = 8u,         ///< CH0A捕获数据丢失标志(仅模式23存在)(不是中断)
    Tim0CA1E     = 9u,         ///< CH1A捕获数据丢失标志(仅模式23存在)(不是中断)
    Tim0CA2E     = 10u,        ///< CH2A捕获数据丢失标志(仅模式23存在)(不是中断)
    Tim0CB0E     = 11u,        ///< CH0B捕获数据丢失标志(仅模式23存在)(不是中断)
    Tim0CB1E     = 12u,        ///< CH1B捕获数据丢失标志(仅模式23存在)(不是中断)
    Tim0CB2E     = 13u,        ///< CH2B捕获数据丢失标志(仅模式23存在)(不是中断)
    Tim0BkIrq    = 14u,        ///< 刹车中断(仅模式23存在）
    Tim0TrigIrq  = 15u,        ///< 触发中断(仅模式23存在）   
}en_tim0_irq_type_t;

/**
 ******************************************************************************
 ** \brief 测量开始结束数据类型重定义 (Edg1stEdg2nd)(模式1)
 *****************************************************************************/
typedef enum en_tim0_m1cr_Edge
{
    Tim0PwcRiseToRise  = 0u,            ///< 上升沿到上升沿(周期)
    Tim0PwcFallToRise  = 1u,            ///< 下降沿到上升沿(低电平)
    Tim0PwcRiseToFall  = 2u,            ///< 上升沿到下降沿(高电平)
    Tim0PwcFallToFall  = 3u,            ///< 下降沿到下降沿(周期)
}en_tim0_m1cr_Edge_t;

/**
 ******************************************************************************
 ** \brief PWC测量测试模式选择数据类型重定义 (Oneshot)(模式1)
 *****************************************************************************/
typedef enum en_tim0_m1cr_oneshot
{
    Tim0PwcCycleDetect    = 0u,         ///< PWC循环测量
    Tim0PwcOneShotDetect  = 1u,         ///< PWC单次测量
}en_tim0_m1cr_oneshot_t;

/**
 ******************************************************************************
 ** \brief PWC IA0选择数据类型重定义 (IA0S)(模式1)
 *****************************************************************************/
typedef enum en_tim0_m1_mscr_ia0s
{
    Tim0IA0Input    = 0u,         ///< IAO输入
    Tim0XORInput    = 1u,         ///< IA0 ETR GATE XOR(TIM0/1/2)/IA0 IA1 IA2 XOR(TIM3)
}en_tim0_m1_mscr_ia0s_t;

/**
 ******************************************************************************
 ** \brief PWC IB0选择数据类型重定义 (IA0S)(模式1)
 *****************************************************************************/
typedef enum en_tim0_m1_mscr_ib0s
{
    Tim0IB0Input    = 0u,         ///< IBO输入
    Tim0TsInput     = 1u,         ///< 内部触发TS选择信号
}en_tim0_m1_mscr_ib0s_t;

/**
 ******************************************************************************
 ** \brief 输出极性、输入相位 数据类型重定义 (CCPA0/CCPB0/ETP/BKP)(模式1/23)
 *****************************************************************************/
typedef enum en_tim0_port_polarity
{
    Tim0PortPositive      = 0u,         ///< 正常输入输出
    Tim0PortOpposite      = 1u,         ///< 反向输入输出
}en_tim0_port_polarity_t;

/**
 ******************************************************************************
 ** \brief 滤波选择数据类型重定义 (FLTET/FLTA0/FLAB0)(模式1/23)
 *****************************************************************************/
typedef enum en_tim0_flt
{
    Tim0FltNone          = 0u,         ///< 无滤波
    Tim0FltPCLKCnt3      = 4u,         ///< PCLK 3个连续有效
    Tim0FltPCLKDiv4Cnt3  = 5u,         ///< PCLK/4 3个连续有效
    Tim0FltPCLKDiv16Cnt3 = 6u,         ///< PCLK/16 3个连续有效
    Tim0FltPCLKDiv64Cnt3 = 7u,         ///< PCLK/64 3个连续有效
}en_tim0_flt_t;

/**
 ******************************************************************************
 ** \brief 通道比较控制 数据类型重定义 (OCMA/OCMB)(模式23)
 *****************************************************************************/
typedef enum en_tim0_m23_fltr_ocm
{
    Tim0ForceLow      = 0u,         ///< 强制为0
    Tim0ForceHigh     = 1u,         ///< 强制为1
    Tim0CMPForceLow   = 2u,         ///< 比较匹配时强制为0
    Tim0CMPForceHigh  = 3u,         ///< 比较匹配时强制为1
    Tim0CMPInverse    = 4u,         ///< 比较匹配时翻转电平
    Tim0CMPOnePrdHigh = 5u,         ///< 比较匹配时输出一个计数周期的高电平
    Tim0PWMMode1      = 6u,         ///< 通道控制为PWM mode 1
    Tim0PWMMode2      = 7u,         ///< 通道控制为PWM mode 2
}en_tim0_m23_fltr_ocm_t;

/**
 ******************************************************************************
 ** \brief 主从模式TS数据类型重定义 (TS)(模式1/23)
 *****************************************************************************/
typedef enum en_tim0_mscr_ts
{
    Tim0Ts0ETR        = 0u,         ///< ETR外部输入滤波后的相位选择信号
    Tim0Ts1TIM0TRGO   = 1u,         ///< Timer0的TRGO输出信号
    Tim0Ts2TIM1TRGO   = 2u,         ///< Timer1的TRGO输出信号
    Tim0Ts3TIM2TRGO   = 3u,         ///< Timer2的TRGO输出信号
    Tim0Ts4TIM3TRGO   = 4u,         ///< Timer3的TRGO输出信号
    //Tim0Ts5IA0ED    = 5u,         ///< 无效
    Tim0Ts6IAFP       = 6u,         ///< CH0A 外部输输入滤波后的相位选择信号
    Tim0Ts7IBFP       = 7u,         ///< CH0B 外部输输入滤波后的相位选择信
}en_tim0_mscr_ts_t;

/**
 ******************************************************************************
 ** \brief PWM输出模式选择数据类型重定义 (COMP)(模式23)
 *****************************************************************************/
typedef enum en_tim0_m23cr_comp
{
    Tim0IndependentPWM      = 0u,         ///< 独立PWM输出
    Tim0ComplementaryPWM    = 1u,         ///< 互补PWM输出
}en_tim0_m23cr_comp_t;

/**
 ******************************************************************************
 ** \brief 计数方向选择数据类型重定义 (DIR)(模式23)
 *****************************************************************************/
typedef enum en_tim0_m23cr_dir
{
    Tim0CntUp      = 0u,         ///< 向上计数
    Tim0CntDown    = 1u,         ///< 向下计数
}en_tim0_m23cr_dir_t;

/**
 ******************************************************************************
 ** \brief 计数方向选择数据类型重定义 (PWM2S)(模式23)
 *****************************************************************************/
typedef enum en_tim0_m23cr_pwm2s
{
    Tim0DoublePointCmp      = 0u,         ///< 双点比较使能，使用CCRA,CCRB比较控制OCREFA输出
    Tim0SinglePointCmp      = 1u,         ///< 单点比较使能，使用CCRA比较控制OCREFA输出
}en_tim0_m23cr_pwm2s_t;

/**
 ******************************************************************************
 ** \brief GATE在PWM互补模式下捕获或比较功能 选择数据类型重定义 (CSG)(模式23)
 *****************************************************************************/
typedef enum en_tim0_m23cr_csg
{
     Tim0PWMCompGateCmpOut    = 0u,         ///< 在PWM互补模式下，Gate作为比较输出
     Tim0PWMCompGateCapIn     = 1u,         ///< 在PWM互补模式下，Gate作为捕获输入
}en_tim0_m23cr_csg_t;


/**
 ******************************************************************************
 ** \brief 比较捕获寄存器 数据类型重定义 (CCR0A,CCR0B)(模式23)
 *****************************************************************************/
typedef enum en_tim0_m23_ccrx
{
     Tim0CCR0A    = 0u,         ///< CCR0A比较捕获寄存器
     Tim0CCR0B    = 1u,         ///< CCR0B比较捕获寄存器
     Tim0CCR1A    = 2u,         ///< CCR1A比较捕获寄存器
     Tim0CCR1B    = 3u,         ///< CCR1B比较捕获寄存器
     Tim0CCR2A    = 4u,         ///< CCR2A比较捕获寄存器
     Tim0CCR2B    = 5u,         ///< CCR2B比较捕获寄存器
}en_tim0_m23_ccrx_t;

/**
 ******************************************************************************
 ** \brief  OCREF清除源 选择数据类型重定义 (OCCS)(模式23)
 *****************************************************************************/
typedef enum en_tim0_m23ce_occs
{
     Tim0OC_Ref_Clr  = 0u,         ///< 来自VC的OC_Ref_Clr
     Tim0ETRf        = 1u,         ///< 外部ETRf
}en_tim0_m23ce_occs_t;

/**
 ******************************************************************************
 ** \brief  比较匹配中断模式 选择数据类型重定义 (CIS/CISB)(模式23)
 *****************************************************************************/
typedef enum en_tim0_m23_cisa_cisb
{
     Tim0CmpIntNone        = 0u,         ///< 无比较匹配中断
     Tim0CmpIntRise        = 1u,         ///< 比较匹配上升沿中断
     Tim0CmpIntFall        = 2u,         ///< 比较匹配下降沿中断
     Tim0CmpIntRiseFall    = 3u,         ///< 比较匹配上升沿下降沿中断
}en_tim0_m23_cisa_cisb_t;

/**
 ******************************************************************************
 ** \brief TIM3端口控制 - 刹车时CHx输出状态控制(BKSA/BKSB)(模式23)
 **
 ** \note
 ******************************************************************************/
typedef enum en_tim0_m23_crchx_bks
{
    Tim0CHxBksHiZ         = 0u,         ///< 刹车使能时，CHx端口输出高阻态
    Tim0CHxBksNorm        = 1u,         ///< 刹车使能时，CHx端口正常输出
    Tim0CHxBksLow         = 2u,         ///< 刹车使能时，CHx端口输出低电平
    Tim0CHxBksHigh        = 3u,         ///< 刹车使能时，CHx端口输出高电平
}en_tim0_m23_crchx_bks_t;

/**
 ******************************************************************************
** \brief TIM3端口控制 - CHx上升沿下降沿捕获(CRx/CFx)(模式23)
 **
 ** \note
 ******************************************************************************/
typedef enum en_tim0_m23_crch0_cfx_crx
{
    Tim0CHxCapNone        = 0u,         ///< CHx通道捕获禁止
    Tim0CHxCapRise        = 1u,         ///< CHx通道上升沿捕获使能
    Tim0CHxCapFall        = 2u,         ///< CHx通道下降沿捕获使能
    Tim0CHxCapFallRise    = 3u,         ///< CHx通道上升沿下降沿捕获都使能
}en_tim0_m23_crch0_cfx_crx_t;

/**
 ******************************************************************************
** \brief TIM3端口控制 - CHx比较捕获模式(CSA/CSB)(模式23)
 **
 ** \note
 ******************************************************************************/
typedef enum en_tim0_m23_crch0_csa_csb
{
    Tim0CHxCmpMode        = 0u,         ///< CHx通道设置为比较模式
    Tim0CHxCapMode        = 1u,         ///< CHx通道设置为捕获模式
}en_tim0_m23_crch0_csa_csb_t;

/**
 ******************************************************************************
 ** \brief  比较模式下 DMA比较触发选择 数据类型重定义 (CCDS)(模式23)
 *****************************************************************************/
typedef enum en_tim0_m23_mscr_ccds
{
     Tim0CmpTrigDMA  = 0u,         ///< 比较匹配触发DMA
     Tim0UEVTrigDMA  = 1u,         ///< 事件更新代替比较匹配触发DMA
}en_tim0_m23_mscr_ccds_t;

/**
 ******************************************************************************
 ** \brief  主从模式选择 数据类型重定义 (MSM)(模式23)
 *****************************************************************************/
typedef enum en_tim0_m23_mscr_msm
{
     Tim0SlaveMode    = 0u,         ///< 从模式
     Tim0MasterMode   = 1u,         ///< 主模式
}en_tim0_m23_mscr_msm_t;

/**
 ******************************************************************************
 ** \brief  触发主模式输出源 数据类型重定义 (MMS)(模式23)
 *****************************************************************************/
typedef enum en_tim0_m23_mscr_mms
{
     Tim0MasterUG         = 0u,         ///< UG(软件更新)源
     Tim0MasterCTEN       = 1u,         ///< CTEN源
     Tim0MasterUEV        = 2u,         ///< UEV更新源
     Tim0MasterCMPSO      = 3u,         ///< 比较匹配选择输出源
     Tim0MasterOCA0Ref    = 4u,         ///< OCA0_Ref源
     Tim0MasterOCB0Ref    = 5u,         ///< OCB0_Ref源
     //Tim0MasterOCB0Ref  = 6u,
     //Tim0MasterOCB0Ref  = 7u,
}en_tim0_m23_mscr_mms_t;

/**
 ******************************************************************************
 ** \brief  触发从模式选择 数据类型重定义 (SMS)(模式23)
 *****************************************************************************/
typedef enum en_tim0_m23_mscr_sms
{
     Tim0SlaveIClk        = 0u,         ///< 使用内部时钟
     Tim0SlaveResetTIM    = 1u,         ///< 复位功能
     Tim0SlaveTrigMode    = 2u,         ///< 触发模式
     Tim0SlaveEClk        = 3u,         ///< 外部时钟模式
     Tim0SlaveCodeCnt1    = 4u,         ///< 正交编码计数模式1
     Tim0SlaveCodeCnt2    = 5u,         ///< 正交编码计数模式2
     Tim0SlaveCodeCnt3    = 6u,         ///< 正交编码计数模式3
     Tim0SlaveGateCtrl    = 7u,         ///< 门控功能
}en_tim0_m23_mscr_sms_t;

/**
 ******************************************************************************
 ** \brief 定时器运行控制数据类型重定义 (CTEN)
 *****************************************************************************/
typedef enum en_tim0_start
{
    Tim0CTENDisable = 0u,            ///< 停止
    Tim0CTENEnable  = 1u,            ///< 运行
}en_tim0_start_t;

/**
 ******************************************************************************
 ** \brief TIM3 mode0 配置结构体定义(模式0)
 *****************************************************************************/
typedef struct stc_tim0_mode0_config
{
    en_tim0_work_mode_t     enWorkMode;       ///< 工作模式设置
    en_tim0_m0cr_gatep_t    enGateP;          ///< 门控极性控制
    boolean_t               bEnGate;          ///< 门控使能
    en_tim0_cr_timclkdiv_t  enPRS;            ///< 预除频配置
    boolean_t               bEnTog;           ///< 翻转输出使能
    en_tim0_cr_ct_t         enCT;             ///< 定时/计数功能选择
    en_tim0_m0cr_md_t       enCntMode;        ///< 计数模式配置
    
    func_ptr_t              pfnTim0Cb;        ///< Timer3中断服务回调函数[void function(void)]
}stc_tim0_mode0_config_t;

/**
 ******************************************************************************
 ** \brief TIM3 mode1 配置结构体定义(模式1)
 *****************************************************************************/
typedef struct stc_tim0_mode1_config
{
    en_tim0_work_mode_t     enWorkMode;       ///< 工作模式设置
    en_tim0_cr_timclkdiv_t  enPRS;            ///< 预除频配置
    en_tim0_cr_ct_t         enCT;             ///< 定时/计数功能选择
    en_tim0_m1cr_oneshot_t  enOneShot;        ///< 单次测量/循环测量选择
    
    func_ptr_t              pfnTim0Cb;        ///< Timer3中断服务回调函数[void function(void)]

}stc_tim0_mode1_config_t;

/**
 ******************************************************************************
 ** \brief PWC输入配置结构体定义(模式1)
 *****************************************************************************/
typedef struct stc_tim0_pwc_input_config
{
    en_tim0_mscr_ts_t          enTsSel;       ///< 触发输入源选择
    en_tim0_m1_mscr_ia0s_t     enIA0Sel;      ///< CHA0输入选择
    en_tim0_m1_mscr_ib0s_t     enIB0Sel;      ///< CHB0输入选择
    en_tim0_port_polarity_t    enETRPhase;    ///< ETR相位选择
    en_tim0_flt_t              enFltETR;      ///< ETR滤波设置
    en_tim0_flt_t              enFltIA0;      ///< CHA0滤波设置
    en_tim0_flt_t              enFltIB0;      ///< CHB0滤波设置
}stc_tim0_pwc_input_config_t;

/**
 ******************************************************************************
 ** \brief TIM3 mode23 配置结构体定义(模式23)
 *****************************************************************************/
typedef struct stc_tim0_mode23_config
{
    en_tim0_work_mode_t         enWorkMode;       ///< 工作模式设置
    en_tim0_m23cr_dir_t         enCntDir;         ///< 计数方向
    en_tim0_cr_timclkdiv_t      enPRS;            ///< 时钟预除频配置
    en_tim0_cr_ct_t             enCT;             ///< 定时/计数功能选择
    en_tim0_m23cr_comp_t        enPWMTypeSel;     ///< PWM模式选择（独立/互补）
    en_tim0_m23cr_pwm2s_t       enPWM2sSel;       ///< OCREFA双点比较功能选择
    boolean_t                   bOneShot;         ///< 单次触发模式使能/禁止
    boolean_t                   bURSSel;          ///< 更新源选择
    
    func_ptr_t                  pfnTim0Cb;        ///< Timer3中断服务回调函数[void function(void)]
}stc_tim0_mode23_config_t;

/**
 ******************************************************************************
 ** \brief GATE在PWM互补模式下捕获或比较功能 配置结构体定义(模式23)
 *****************************************************************************/
typedef struct stc_tim0_m23_gate_config
{
    en_tim0_m23cr_csg_t        enGateFuncSel;      ///< Gate比较、捕获功能选择
    boolean_t                  bGateRiseCap;       ///< GATE作为捕获功能时，上沿捕获有效控制
    boolean_t                  bGateFallCap;       ///< GATE作为捕获功能时，下沿捕获有效控制
}stc_tim0_m23_gate_config_t;

/**
 ******************************************************************************
 ** \brief CHA/CHB通道比较控制 配置结构体定义(模式23)
 *****************************************************************************/
typedef struct stc_tim0_m23_compare_config
{
    en_tim0_m23_crch0_csa_csb_t  enCHxACmpCap;     ///< CH0A比较/捕获功能选择
    en_tim0_m23_fltr_ocm_t       enCHxACmpCtrl;    ///< CH0A通道比较控制
    en_tim0_port_polarity_t      enCHxAPolarity;   ///< CH0A输出极性控制
    boolean_t                    bCHxACmpBufEn;    ///< 比较A缓存功能 使能/禁止
    en_tim0_m23_cisa_cisb_t      enCHxACmpIntSel;  ///< CHA比较匹配中断选择
    
    en_tim0_m23_crch0_csa_csb_t  enCHxBCmpCap;     ///< CH0B比较/捕获功能选择
    en_tim0_m23_fltr_ocm_t       enCHxBCmpCtrl;    ///< CH0B通道比较控制
    en_tim0_port_polarity_t      enCHxBPolarity;   ///< CH0B输出极性控制
    boolean_t                    bCHxBCmpBufEn;    ///< 比较B缓存功能 使能/禁止
    en_tim0_m23_cisa_cisb_t      enCHxBCmpIntSel;  ///< CHB0比较匹配中断选择
}stc_tim0_m23_compare_config_t;

/**
 ******************************************************************************
 ** \brief CHA/CHB通道捕获控制 配置结构体定义(模式23)
 *****************************************************************************/
typedef struct stc_tim0_m23_input_config
{
    en_tim0_m23_crch0_csa_csb_t  enCHxACmpCap;     ///< CH0A比较/捕获功能选择
    en_tim0_m23_crch0_cfx_crx_t  enCHxACapSel;     ///< CH0A捕获边沿选择
    en_tim0_flt_t                enCHxAInFlt;      ///< CH0A通道捕获滤波控制
    en_tim0_port_polarity_t      enCHxAPolarity;   ///< CH0A输入相位
    
    en_tim0_m23_crch0_csa_csb_t  enCHxBCmpCap;     ///< CH0A比较/捕获功能选择
    en_tim0_m23_crch0_cfx_crx_t  enCHxBCapSel;     ///< CH0B捕获边沿选择
    en_tim0_flt_t                enCHxBInFlt;      ///< CH0B通道捕获滤波控制
    en_tim0_port_polarity_t      enCHxBPolarity;   ///< CH0B输入相位
    
}stc_tim0_m23_input_config_t;   

/**
 ******************************************************************************
 ** \brief ETR输入相位滤波配置结构体定义(模式23)
 *****************************************************************************/
typedef struct stc_tim0_m23_etr_input_config
{
    en_tim0_port_polarity_t     enETRPolarity;  ///< ETR输入极性设置
    en_tim0_flt_t               enETRFlt;       ///< ETR滤波设置
}stc_tim0_m23_etr_input_config_t;

/**
 ******************************************************************************
 ** \brief 刹车BK输入相位滤波配置结构体定义(模式23)
 *****************************************************************************/
typedef struct stc_tim0_m23_bk_input_config
{
    boolean_t                   bEnBrake;         ///< 刹车使能
    boolean_t                   bEnVC0Brake;      ///< 使能VC0刹车
    boolean_t                   bEnVC1Brake;      ///< 使能VC1刹车
    boolean_t                   bEnSafetyBk;      ///< 使能safety刹车
    boolean_t                   bEnBKSync;        ///< TIM0/TIM1/TIM2刹车同步使能
    en_tim0_m23_crchx_bks_t     enBkCH0AStat;     ///< 刹车时CHA端口状态设置
    en_tim0_m23_crchx_bks_t     enBkCH0BStat;     ///< 刹车时CHB端口状态设置
    en_tim0_m23_crchx_bks_t     enBkCH1AStat;     ///< 刹车时CHA端口状态设置
    en_tim0_m23_crchx_bks_t     enBkCH1BStat;     ///< 刹车时CHB端口状态设置
    en_tim0_m23_crchx_bks_t     enBkCH2AStat;     ///< 刹车时CHA端口状态设置
    en_tim0_m23_crchx_bks_t     enBkCH2BStat;     ///< 刹车时CHB端口状态设置
    en_tim0_port_polarity_t     enBrakePolarity;  ///< 刹车BK输入极性设置
    en_tim0_flt_t               enBrakeFlt;       ///< 刹车BK滤波设置
}stc_tim0_m23_bk_input_config_t;

/**
 ******************************************************************************
** \brief 死区功能配置结构体定义(模式23)
 *****************************************************************************/
typedef struct stc_tim0_m23_dt_config
{
    boolean_t       bEnDeadTime;      ///< 刹车时CHA端口状态设置
    uint8_t         u8DeadTimeValue;  ///< 刹车时CHA端口状态设置
}stc_tim0_m23_dt_config_t;

/**
 ******************************************************************************
 ** \brief 触发ADC配置结构体定义(模式23)
 *****************************************************************************/
typedef struct stc_tim0_m23_adc_trig_config
{
    boolean_t     bEnTrigADC;          ///< 触发ADC全局控制
    boolean_t     bEnUevTrigADC;       ///< 事件更新触发ADC
    boolean_t     bEnCH0ACmpTrigADC;   ///< CH0A比较匹配触发ADC
    boolean_t     bEnCH0BCmpTrigADC;   ///< CH0B比较匹配触发ADC
    boolean_t     bEnCH1ACmpTrigADC;   ///< CH0A比较匹配触发ADC
    boolean_t     bEnCH1BCmpTrigADC;   ///< CH0B比较匹配触发ADC
    boolean_t     bEnCH2ACmpTrigADC;   ///< CH0A比较匹配触发ADC
    boolean_t     bEnCH2BCmpTrigADC;   ///< CH0B比较匹配触发ADC
}stc_tim0_m23_adc_trig_config_t;

/**
 ******************************************************************************
 ** \brief  DMA触发 配置结构体定义(模式23)
 *****************************************************************************/
typedef struct stc_tim0_m23_trig_dma_config
{
    boolean_t                bUevTrigDMA;      ///< 更新 触发DMA使能
    boolean_t                bTITrigDMA;       ///< Trig 触发DMA功能
    boolean_t                bCmpA0TrigDMA;    ///< CH0A捕获比较触发DMA使能
    boolean_t                bCmpB0TrigDMA;    ///< CH0B捕获比较触发DMA使能
    boolean_t                bCmpA1TrigDMA;    ///< CH1A捕获比较触发DMA使能
    boolean_t                bCmpB1TrigDMA;    ///< CH1B捕获比较触发DMA使能
    boolean_t                bCmpA2TrigDMA;    ///< CH2A捕获比较触发DMA使能
    boolean_t                bCmpB2TrigDMA;    ///< CH2B捕获比较触发DMA使能
    en_tim0_m23_mscr_ccds_t  enCmpUevTrigDMA;  ///< 比较模式下DMA比较触发选择
}stc_tim0_m23_trig_dma_config_t;

/**
 ******************************************************************************
 ** \brief  主从模式 配置结构体定义(模式23)
 *****************************************************************************/
typedef struct stc_tim0_m23_master_slave_config
{
    en_tim0_m23_mscr_msm_t      enMasterSlaveSel;  ///< 主从模式选择
    en_tim0_m23_mscr_mms_t      enMasterSrc;       ///< 主模式触发源选择
    en_tim0_m23_mscr_sms_t      enSlaveModeSel;    ///< 从模式选择
    en_tim0_mscr_ts_t           enTsSel;           ///< 触发输入源选择
}stc_tim0_m23_master_slave_config_t;

/**
 ******************************************************************************
 ** \brief  OCREF清除功能 配置结构体定义(模式23)
 *****************************************************************************/
typedef struct stc_tim0_m23_OCREF_Clr_config
{
    en_tim0_m23ce_occs_t       enOCRefClrSrcSel;  ///< OCREF清除源选择
    boolean_t                  bVCClrEn;          ///< 是否使能来自VC的OCREF_Clr
}stc_tim0_m23_OCREF_Clr_config_t;

/******************************************************************************
 * Global variable declarations ('extern', definition in C source)
 *****************************************************************************/

/******************************************************************************
 * Global function prototypes (definition in C source)
 *****************************************************************************/
//中断相关函数

//中断标志获取
boolean_t Tim0_GetIntFlag(en_tim0_irq_type_t enTim0Irq);
//中断标志清除
en_result_t Tim0_ClearIntFlag(en_tim0_irq_type_t enTim0Irq);
//所有中断标志清除
en_result_t Tim0_ClearAllIntFlag(void);
//模式0中断使能
en_result_t Tim0_Mode0_EnableIrq(void);
//模式1中断使能
en_result_t Tim0_Mode1_EnableIrq (en_tim0_irq_type_t enTim0Irq);
//模式2中断使能
en_result_t Tim0_Mode23_EnableIrq (en_tim0_irq_type_t enTim0Irq);
//模式0中断禁止
en_result_t Tim0_Mode0_DisableIrq(void);
//模式1中断禁止
en_result_t Tim0_Mode1_DisableIrq (en_tim0_irq_type_t enTim0Irq);
//模式2中断禁止
en_result_t Tim0_Mode23_DisableIrq (en_tim0_irq_type_t enTim0Irq);


//模式0初始化及相关功能操作

//timer配置及初始化
en_result_t Tim0_Mode0_Init(stc_tim0_mode0_config_t* pstcConfig);
//timer 启动/停止
en_result_t Tim0_M0_Run(void);
en_result_t Tim0_M0_Stop(void);
//重载值设置
en_result_t Tim0_M0_ARRSet(uint16_t u16Data);
//16位计数值设置/获取
en_result_t Tim0_M0_Cnt16Set(uint16_t u16Data);
uint16_t Tim0_M0_Cnt16Get(void);
//32位计数值设置/获取
en_result_t Tim0_M0_Cnt32Set(uint32_t u32Data);
uint32_t Tim0_M0_Cnt32Get(void);
//翻转输出使能/禁止设定
en_result_t Tim0_M0_EnTOG_Output(boolean_t bEnOutput);


//模式1初始化及相关功能操作

//timer配置及初始化
en_result_t Tim0_Mode1_Init(stc_tim0_mode1_config_t* pstcConfig);
//PWC 输入配置
en_result_t Tim0_M1_Input_Config(stc_tim0_pwc_input_config_t* pstcConfig);
//PWC测量边沿起始结束选择
en_result_t Tim0_M1_PWC_Edge_Sel(en_tim0_m1cr_Edge_t enEdgeSel);
//timer 启动/停止
en_result_t Tim0_M1_Run(void);
en_result_t Tim0_M1_Stop(void);
//16位计数值设置/获取
en_result_t Tim0_M1_Cnt16Set(uint16_t u16Data);
uint16_t Tim0_M1_Cnt16Get(void);
//脉冲宽度测量结果数值获取
uint16_t Tim0_M1_PWC_CapValueGet(void);


//模式1初始化及相关功能操作

//timer配置及初始化
en_result_t Tim0_Mode23_Init(stc_tim0_mode23_config_t* pstcConfig);
//timer 启动/停止
en_result_t Tim0_M23_Run(void);
en_result_t Tim0_M23_Stop(void);
//PWM输出使能
en_result_t Tim0_M23_EnPWM_Output(boolean_t bEnOutput, boolean_t bEnAutoOutput);
//重载值设置
en_result_t Tim0_M23_ARRSet(uint16_t u16Data, boolean_t bArrBufEn);
//16位计数值设置/获取
en_result_t Tim0_M23_Cnt16Set(uint16_t u16Data);
uint16_t Tim0_M23_Cnt16Get(void);
//比较捕获寄存器CCR0A/CCR0B设置/读取
en_result_t Tim0_M23_CCR_Set(en_tim0_m23_ccrx_t enCCRSel, uint16_t u16Data);
uint16_t Tim0_M23_CCR_Get(en_tim0_m23_ccrx_t enCCRSel);
//PWM互补输出模式下，GATE功能选择
en_result_t Tim0_M23_GateFuncSel(stc_tim0_m23_gate_config_t* pstcConfig);
//主从模式配置
en_result_t Tim0_M23_MasterSlave_Set(stc_tim0_m23_master_slave_config_t* pstcConfig);
//CH0A/CH0B比较通道控制
en_result_t Tim0_M23_PortOutput_Config(en_tim0_channel_t enTim0Chx, stc_tim0_m23_compare_config_t* pstcConfig);
//CH0A/CH0B输入控制
en_result_t Tim0_M23_PortInput_Config(en_tim0_channel_t enTim0Chx, stc_tim0_m23_input_config_t* pstcConfig);
//ERT输入控制
en_result_t Tim0_M23_ETRInput_Config(stc_tim0_m23_etr_input_config_t* pstcConfig);
//刹车BK输入控制
en_result_t Tim0_M23_BrakeInput_Config(stc_tim0_m23_bk_input_config_t* pstcConfig);
//触发ADC控制
en_result_t Tim0_M23_TrigADC_Config(stc_tim0_m23_adc_trig_config_t* pstcConfig);
//死区功能
en_result_t Tim0_M23_DT_Config(stc_tim0_m23_dt_config_t* pstcConfig);
//重复周期设置
en_result_t Tim0_M23_SetValidPeriod(uint8_t u8ValidPeriod);
//OCREF清除功能
en_result_t Tim0_M23_OCRefClr(stc_tim0_m23_OCREF_Clr_config_t* pstcConfig);
//使能DMA传输
en_result_t Tim0_M23_EnDMA(stc_tim0_m23_trig_dma_config_t* pstcConfig);
//捕获比较A软件触发
en_result_t Tim0_M23_EnSwTrigCapCmpA(en_tim0_channel_t enTim0Chx);
//捕获比较B软件触发
en_result_t Tim0_M23_EnSwTrigCapCmpB(en_tim0_channel_t enTim0Chx);
//软件更新使能
en_result_t Tim0_M23_EnSwUev(void);
//软件触发使能
en_result_t Tim0_M23_EnSwTrig(void);
//软件刹车使能
en_result_t Tim0_M23_EnSwBk(void);


//@} // Tim0Group

#ifdef __cplusplus
#endif


#endif /* __BT_H__ */
/******************************************************************************
 * EOF (not truncated)
 *****************************************************************************/


