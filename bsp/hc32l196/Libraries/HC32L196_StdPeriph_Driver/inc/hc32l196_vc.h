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
/******************************************************************************/
/** \file vc.h
 **
 ** Headerfile for Voltage Comparator functions
 ** @link VC Group Some description @endlink
 **
 **   - 2019-04-10    First Version
 **
 ******************************************************************************/

#ifndef __VC_H__
#define __VC_H__

/******************************************************************************
 * Include files
 ******************************************************************************/
#include "ddl.h"

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
typedef enum 
{
    VcChannel0 = 0u,                 //   通道0
    VcChannel1 = 1u,                 //   通道1
    VcChannel2 = 2u                  //   通道2
}en_vc_channel_t;


/**
 ******************************************************************************
 ** \brief VC迟滞                            VC_CR  VCx_HYS_SEL(x=0、1、2)
 *****************************************************************************/
typedef enum 
{
    VcDelayoff  = 0u,            //   迟滞关闭
    VcDelay10mv = 1u,            //   迟滞10mv
    VcDelay20mv = 2u,            //   迟滞20mv
    VcDelay30mv = 3u,            //   迟滞30mv
}en_vc_cmp_delay_t;

/**
 ******************************************************************************
 ** \brief VC偏置电流                       VC_CR  VCx_BIAS_SEL(x=0、1、2)
 *****************************************************************************/
typedef enum 
{
    VcBias300na  = 0u,            //   偏置电流300nA
    VcBias1200na = 1u,            //   偏置电流1.2uA
    VcBias10ua   = 2u,            //   偏置电流10uA
    VcBias20ua   = 3u,            //   偏置电流20uA
}en_vc_bias_current_t;

/**
 ******************************************************************************
 ** \brief VC输出滤波时间                     VCx_CR  debounce_time(x=0、1、2)
 *****************************************************************************/
typedef enum 
{
    VcFilter7us     = 0u,            //   输出滤波时间7us
    VcFilter14us    = 1u,            //   输出滤波时间14us
    VcFilter28us    = 2u,            //   输出滤波时间28us
    VcFilter112us   = 3u,            //   输出滤波时间112us
    VcFilter450us   = 4u,            //   输出滤波时间450us
    VcFilter1800us  = 5u,            //   输出滤波时间1.8ms
    VcFilter7200us  = 6u,            //   输出滤波时间7.2ms
    VcFilter28800us = 7u,            //   输出滤波时间28.8ms
}en_vc_resp_filter_t;

/**
 ******************************************************************************
 ** \brief VC P端输入
 *****************************************************************************/
typedef enum 
{                                                                                    
                                         //VC0             //VC1           //VC2
    VcInPCh0 = 0u,                //   输入通道0 PC0        输入通道0 PA0     输入通道0 PA5
    VcInPCh1 = 1u,                //   输入通道1 PC1        输入通道1 PA1     输入通道1 PB1
    VcInPCh2 = 2u,                //   输入通道2 PC2        输入通道2 PA2     输入通道2 PE9
    VcInPCh3 = 3u,                //   输入通道3 PC3        输入通道3 PA3     输入通道3 PE10
    VcInPCh4 = 4u,                //   输入通道4 PA0        输入通道4 PA4     输入通道4 PE11
    VcInPCh5 = 5u,                //   输入通道5 PA1        输入通道5 PA5     输入通道5 PE13
    VcInPCh6 = 6u,                //   输入通道6 PA2        输入通道6 PB1     输入通道6 PE14
    VcInPCh7 = 7u,                //   输入通道7 PA3        输入通道7 PB2     输入通道7 PE15
    VcInPCh8 = 8u,                //   输入通道7 PA4        输入通道8 PB10    输入通道8 PB11
    VcInPCh9 = 9u,                //   输入通道7 PA5        输入通道9 PB12    输入通道9 PB14
    VcInPCh10 = 10u,              //   输入通道7 PA6        输入通道10 PB13   输入通道10 PD9
    VcInPCh11 = 11u,              //   输入通道7 PA7        输入通道11 PB14   输入通道11 PD10
    VcInPCh12 = 12u,              //   输入通道7 PB4        输入通道12 PB4    输入通道12 PD11
    VcInPCh13 = 13u,              //   输入通道7 PB5        输入通道13 DAC0   输入通道13 PC7
    VcInPCh14 = 14u,              //   输入通道7 PB6        输入通道14 PB6    输入通道14 DAC0
    VcInPCh15 = 15u,              //   输入通道7 DAC0        输入通道15 PB7    输入通道15 DAC0                           
}en_vc_input_p_src_t;

/**
 ******************************************************************************
 ** \brief VC N端输入
 *****************************************************************************/
typedef enum 
{
                                 //VC0                          //VC1                         //VC2
    VcInNCh0    = 0u,         //   输入通道0  PA0               输入通道0 PC0                输入通道0 PA5
    VcInNCh1    = 1u,         //   输入通道1  PA1               输入通道1 PC1                输入通道1 PB1
    VcInNCh2    = 2u,         //   输入通道2  PA2               输入通道2 PC2                输入通道2 PE11
    VcInNCh3    = 3u,         //   输入通道3  PA3               输入通道3 PC3                输入通道3 PE15
    VcInNCh4    = 4u,         //   输入通道4  PA4               输入通道4 PA0                输入通道4 PB11
    VcInNCh5    = 5u,         //   输入通道5  PA5               输入通道5 PA1                输入通道5 PB14
    VcInNCh6    = 6u,         //   输入通道6  PA6               输入通道6 PB0                输入通道6 PD10
    VcInNCh7    = 7u,         //   输入通道7  PA7               输入通道7 PB1                输入通道7 PD11
    VcInNCh8    = 8u,         //   输入通道8  PC4               输入通道8 PB2                输入通道8 PC7
    VcInNCh9    = 9u,         //   输入通道9  PC5               输入通道9 PB3                输入通道9 DAC0
    VcInNCh10   = 10u,        //   输入通道10 DAC0              输入通道10 DAC1              输入通道10 DAC0   
    ResDivOut   = 11u,        //   电阻分压                     电阻分压                     NA
    AiTs        = 12u,        //   内部温度传感器输出电压       内部温度传感器输出电压       内部温度传感器输出电压
    AiBg1p2     = 13u,        //   内部基准1.2V                 内部基准1.2V                 内部基准1.2V 
    AiAdcVref   = 14u,        //   ADC参考电压VREF              ADC参考电压VREF              ADC参考电压VREF
    AiLdo       = 15u,        //   LDO输出电压                  LDO输出电压                  LDO输出电压
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
 ** \brief VC状态                       VC_IFR
 *****************************************************************************/
typedef enum en_vc_stat
{
    Vc0_Intf    = 0u,          //   VC0中断标志
    Vc1_Intf    = 1u,          //   VC1中断标志
    Vc0_Filter  = 2u,          //   VC0 Filter 后的状态          
    Vc1_Filter  = 3u,          //   VC1 Filter 后的状态          
    Vc2_Intf    = 4u,          //   VC2中断标志  
    Vc2_Filter  = 5u           //   VC2 Filter 后的状态     
}en_vc_ifr_t;

/**
 ******************************************************************************
 ** \brief VC输出配置                      VCx_OUT_CFG(x=0、1、2)
 ** \note       对于VC0，CHX = CHA；对于VC1 VC2，CHX = CHB
 *****************************************************************************/
typedef enum en_vc_output_cfg
{
    VcOutInvTimer = 0u,              //   结果输出反向到各Timer0,1,2,3 REFCLR
    VcOutTIM0RCLR = 1u,              //   结果输出到TIM0 REFCLR使能控制
    VcOutTIM1RCLR = 2u,              //   结果输出到TIM1 REFCLR使能控制
    VcOutTIM2RCLR = 3u,              //   结果输出到TIM2 REFCLR使能控制
    VcOutTIM3RCLR = 4u,              //   结果输出到TIM3 REFCLR使能控制
    VcOutTIMBK    = 5u,              //   结果输出到Timer0,1,2,3刹车控制
    VcOutInvTIM4  = 9u,              //   结果输出到Timer4反向使能
    VcOutTIM4     = 10u,             //   结果输出到Timer4捕获输入CHX使能
    VcOutInvTIM5  = 11u,             //   结果输出到Timer5反向使能
    VcOutTIM5     = 12u,             //   结果输出到Timer5捕获输入CHX使能
    VcOutInvTIM6  = 13u,             //   结果输出到Timer6反向使能
    VcOutTIM6     = 14u,             //   结果输出到Timer6捕获输入CHX使能
    VcOutBrake    = 15u,             //   结果作为Advanced Timer刹车控制
    VcOutDisable  = 16u              //   结果输出除能    
}en_vc_output_cfg_t;

/**
 ******************************************************************************
 ** \brief VC DIV参考电压Vref选择                   VC_CR   VC_REF2P5_SEL
 *****************************************************************************/
typedef enum en_vc_div_vref
{
    VcDivVrefAvcc = 0u,              ///< AVCC
    VcDivVrefAdc  = 1u,               ///< ADC_CR0 SREF选择参考电压
}en_vc_div_vref_t;

/**
 ******************************************************************************
 ** \brief VC模块配置               VC_CR   VC_REF2P5_SEL  VC_DIV_EN  VC_DIV
 *****************************************************************************/
typedef struct stc_vc_dac_cfg
{
    boolean_t           bDivEn;       //   VC_CR: VC_DIV_EN
    uint8_t             u8DivVal;     //   VC_CR: VC_DIV 范围：0-63
    en_vc_div_vref_t    enDivVref;    //   VC_CR: VC_REF2P5_SEL
}stc_vc_dac_cfg_t;

/**
 ******************************************************************************
 ** \brief VC通道配置                
 *****************************************************************************/
typedef struct stc_vc_channel_cfg
{
    en_vc_channel_t         enVcChannel;        //   VC通道选择
    en_vc_cmp_delay_t       enVcCmpDly;         //   VC迟滞
    en_vc_bias_current_t    enVcBiasCurrent;    //   VC功耗选择
    en_vc_resp_filter_t     enVcFilterTime;     //   输出滤波时间
    en_vc_input_p_src_t     enVcInPin_P;        //   P端输入
    en_vc_input_n_src_t     enVcInPin_N;        //   N端输入
    en_vc_output_cfg_t      enVcOutCfg;         //   输出配置
    boolean_t               bFlten;             //   滤波输出使能
}stc_vc_channel_cfg_t;

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
extern void Vc_CfgItType(en_vc_channel_t Channelx, en_vc_irq_sel_t ItType);
extern void  Vc_ItCfg(en_vc_channel_t Channelx, boolean_t NewStatus);
extern boolean_t Vc_GetItStatus(en_vc_ifr_t Result);
extern void Vc_ClearItStatus(en_vc_ifr_t NewStatus);
extern en_result_t Vc_DacInit(stc_vc_dac_cfg_t *pstcDacCfg);
extern void Vc_Init(stc_vc_channel_cfg_t *pstcChannelCfg);
extern void Vc_Cmd(en_vc_channel_t enChannel, boolean_t NewStatus);



#ifdef __cplusplus
}
#endif

#endif /* __VC_H__ */
/******************************************************************************
 * EOF (not truncated)
 ******************************************************************************/

