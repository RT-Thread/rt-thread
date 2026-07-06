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
/******************************************************************************/
/** \file vc.h
 **
 ** Headerfile for Voltage Comparator functions
 ** @link VC Group Some description @endlink
 **
 **   - 2017-06-28 Alex    First Version
 **
 ******************************************************************************/

#ifndef __VC_H__
#define __VC_H__

/******************************************************************************
 * Include files
 ******************************************************************************/
#include "ddl.h"
#include "interrupts_hc32l136.h"

/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/**
 ******************************************************************************
 ** \defgroup VcGroup Voltage Comparator (VC)
 **
 ******************************************************************************/
//@{

/******************************************************************************
 * Global type definitions
 ******************************************************************************/

/**
 ******************************************************************************
 ** \brief VC通道
 *****************************************************************************/
typedef enum en_vc_channel
{
    VcChannel0 = 0u,                 ///< 通道0
    VcChannel1 = 1u,                 ///< 通道1
}en_vc_channel_t;


/**
 ******************************************************************************
 ** \brief VC迟滞
 *****************************************************************************/
typedef enum en_vc_cmp_delay
{
    VcDelayoff  = 0u,            ///< 迟滞关闭
    VcDelay10mv = 1u,            ///< 迟滞10mv
    VcDelay20mv = 2u,            ///< 迟滞20mv
    VcDelay30mv = 3u,            ///< 迟滞30mv
}en_vc_cmp_delay_t;

/**
 ******************************************************************************
 ** \brief VC偏置电流
 *****************************************************************************/
typedef enum en_vc_bias_current
{
    VcBias300na  = 0u,            ///< 偏置电流300na
    VcBias1200na = 1u,            ///< 偏置电流1.2ua
    VcBias10ua   = 2u,            ///< 偏置电流10ua
    VcBias20ua   = 3u,            ///< 偏置电流20ua
}en_vc_bias_current_t;

/**
 ******************************************************************************
 ** \brief VC输出滤波时间
 *****************************************************************************/
typedef enum en_vc_resp_filter
{
    VcFilter7us     = 0u,            ///< 输出滤波时间7us
    VcFilter14us    = 1u,           ///< 输出滤波时间14us
    VcFilter28us    = 2u,           ///< 输出滤波时间28us
    VcFilter112us   = 3u,          ///< 输出滤波时间112us
    VcFilter450us   = 4u,          ///< 输出滤波时间450us
    VcFilter1800us  = 5u,         ///< 输出滤波时间1.8ms
    VcFilter7200us  = 6u,         ///< 输出滤波时间7.2ms
    VcFilter28800us = 7u,        ///< 输出滤波时间28.8ms
}en_vc_resp_filter_t;

/**
 ******************************************************************************
 ** \brief VC P端输入
 *****************************************************************************/
typedef enum en_vc_input_p_src
{																					
                                   //VC0                        //VC1
    VcInPCh0 = 0u,                ///< 输入通道0 PC0		输入通道0 PA0
    VcInPCh1 = 1u,                ///< 输入通道1 PC1		输入通道0 PA1
    VcInPCh2 = 2u,                ///< 输入通道2 PC2		输入通道0 PA2
    VcInPCh3 = 3u,                ///< 输入通道3 PC3		输入通道0 PA3
    VcInPCh4 = 4u,                ///< 输入通道4 PA0		输入通道0 PA4
    VcInPCh5 = 5u,                ///< 输入通道5 PA1		输入通道0 PA5
    VcInPCh6 = 6u,                ///< 输入通道6 PA2		输入通道0 PB1
    VcInPCh7 = 7u,                ///< 输入通道7 PA3		输入通道0 PB2
    VcInPCh8 = 8u,                ///< 输入通道7 PA4		输入通道0 PB10
    VcInPCh9 = 9u,                ///< 输入通道7 PA5		输入通道0 PB12
    VcInPCh10 = 10u,                ///< 输入通道7 PA6		输入通道0 PB13
    VcInPCh11 = 11u,                ///< 输入通道7 PA7		输入通道0 PB14
    VcInPCh12 = 12u,                ///< 输入通道7 PB4		输入通道0 PB4
    VcInPCh13 = 13u,                ///< 输入通道7 PB5		输入通道0 PB5
    VcInPCh14 = 14u,                ///< 输入通道7 PB6		输入通道0 PB6
    VcInPCh15 = 15u,                ///< 输入通道7 PB7		输入通道0 PB7                           
}en_vc_input_p_src_t;

/**
 ******************************************************************************
 ** \brief VC N端输入
 *****************************************************************************/
typedef enum en_vc_input_n_src
{
                                 //VC0                          //VC1
    VcInNCh0    = 0u,         ///< 输入通道0  PA0	        输入通道0 PC0
    VcInNCh1    = 1u,         ///< 输入通道1  PA1		输入通道0 PC1
    VcInNCh2    = 2u,         ///< 输入通道2  PA2		输入通道0 PC2
    VcInNCh3    = 3u,         ///< 输入通道3  PA3		输入通道0 PC3
    VcInNCh4    = 4u,         ///< 输入通道4  PA4		输入通道0 PA0
    VcInNCh5    = 5u,         ///< 输入通道5  PA5		输入通道0 PA1
    VcInNCh6    = 6u,         ///< 输入通道6  PA6		输入通道0 PB0
    VcInNCh7    = 7u,         ///< 输入通道7  PA7		输入通道0 PB1
    VcInNCh8    = 8u,         ///< 输入通道8  PC4		输入通道0 PB2
    VcInNCh9    = 9u,         ///< 输入通道9  PC5		输入通道0 PB3
    VcInNCh10   = 10u,        ///< 输入通道10 PB0 		输入通道0 PB4   
    ResDivOut   = 11u,        ///< Vcc分压                      Vcc分压
    AiTs        = 12u,        ///< 温度传感器                  温度传感器
    AiBg1p2     = 13u,        ///< BGR 1.2V                    BGR 1.2V
    AiAdcVref   = 14u,        ///< ADCVREF                     ADCVREF
    AiLdo       = 15u,        ///< LDO                         LDO
}en_vc_input_n_src_t;

/**
 ******************************************************************************
 ** \brief VC中断触发方式
 *****************************************************************************/
typedef enum en_vc_irq_sel
{
    VcIrqNone = 0u,            ///< 无中断
    VcIrqRise = 1u,            ///< 上升沿触发
    VcIrqFall = 2u,            ///< 下降沿触发
    VcIrqHigh = 3u,            ///< 高电平触发

}en_vc_irq_sel_t;

/**
 ******************************************************************************
 ** \brief VC状态
 *****************************************************************************/
typedef enum en_vc_stat
{
    VcCmpResult  = 0u,                ///< VC比较输出结果
    VcIntrResult = 1u,               ///< VC中断状态
}en_vc_stat_t;

/**
 ******************************************************************************
 ** \brief VC输出配置
 *****************************************************************************/
typedef enum en_vc_output_config
{
    VcOutInvTimer = 0u,              ///< 结果输出负向到各Timer0,1,2,3
    VcOutTIM0RCLR = 1u,              ///< 结果使能输出到TIM0 REFCLR
    VcOutTIM1RCLR = 2u,              ///< 结果使能输出到TIM1 REFCLR
    VcOutTIM2RCLR = 3u,              ///< 结果使能输出到TIM2 REFCLR
    VcOutTIM3RCLR = 4u,              ///< 结果使能输出到TIM3 REFCLR
    VcOutTIMBK    = 5u,              ///< 结果使能输出到Timer0,1,2,3刹车
    VcOutInvTIM4  = 9u,              ///< 结果输出负向到Timer4
    VcOutTIM4     = 10u,             ///< 结果使能输出到Timer4
    VcOutInvTIM5  = 11u,             ///< 结果输出负向到Timer5
    VcOutTIM5     = 12u,             ///< 结果使能输出到Timer5
    VcOutInvTIM6  = 13u,             ///< 结果输出负向到Timer6
    VcOutTIM6     = 14u,             ///< 结果使能输出到Timer6
    VcOutBrake    = 15u,             ///< 结果使能输出到Advanced Timer刹车
    VcOutDisable  = 16u,             ///< 结果输出除能
}en_vc_output_config_t;

/**
 ******************************************************************************
 ** \brief VC DIV参考电压Vref选择
 *****************************************************************************/
typedef enum en_vc_div_vref
{
    VcDivVrefAvcc = 0u,              ///< AVCC
    VcDivVrefAdc  = 1u,               ///< ADC_CR0 SREF选择参考电压
}en_vc_div_vref_t;

/**
 ******************************************************************************
 ** \brief VC模块配置
 *****************************************************************************/
typedef struct stc_vc_dac_config
{
    boolean_t           bDivEn;       ///< 使能/除能 6-bit VCC divider
    uint8_t             u8DivVal;     ///< 6-bit VCC divider设置值
    en_vc_div_vref_t    enDivVref;    ///< 6-bit VCC divider输入参考电压选择
}stc_vc_dac_config_t;

/**
 ******************************************************************************
 ** \brief VC通道配置
 *****************************************************************************/
typedef struct stc_vc_channel_config
{
    en_vc_channel_t         enVcChannel;        ///< VC通道选择
    en_vc_cmp_delay_t       enVcCmpDly;         ///< VC迟滞
    en_vc_bias_current_t    enVcBiasCurrent;    ///< VC偏转电流
    en_vc_resp_filter_t     enVcFilterTime;     ///< 输出滤波时间
    en_vc_input_p_src_t     enVcInPin_P;        ///< P端输入
    en_vc_input_n_src_t     enVcInPin_N;        ///< N端输入
    en_vc_output_config_t   enVcOutConfig;      ///< 输出配置
    en_vc_irq_sel_t         enVcIrqSel;         ///< 中断触发方式
    func_ptr_t              pfnAnalogCmpCb;     ///< 中断回调函数
}stc_vc_channel_config_t;

/******************************************************************************
 * Global definitions
 ******************************************************************************/

/******************************************************************************
 * Local type definitions ('typedef')
 ******************************************************************************/

/******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/

//VC init/deinit

en_result_t Vc_ChannelInit(en_vc_channel_t enChannel,
                            stc_vc_channel_config_t *pstcChannelConfig);
en_result_t Vc_ChannelDeInit(en_vc_channel_t enChannel);
en_result_t Vc_DACInit(stc_vc_dac_config_t *pstcDacConfig);
//VC function enable/disable
en_result_t Vc_EnableChannel(en_vc_channel_t enChannel);
en_result_t Vc_DisableChannel(en_vc_channel_t enChannel);

//VC filter enable/disable
en_result_t Vc_EnableFilter(en_vc_channel_t enChannel);
en_result_t Vc_DisableFilter(en_vc_channel_t enChannel);

//get stat
boolean_t Vc_GetStat(en_vc_channel_t enChannel, en_vc_stat_t enStat);
//clear stat
void Vc_ClearIrq(en_vc_channel_t enChannel);

//irq enable/disable
en_result_t Vc_EnableIrq(en_vc_channel_t enChannel);
en_result_t Vc_DisableIrq(en_vc_channel_t enChannel);
en_result_t Vc_ConfigIrq(en_vc_channel_t enChannel, en_vc_irq_sel_t enSel);
//@} // VcGroup

#ifdef __cplusplus
}
#endif

#endif /* __VC_H__ */
/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/

