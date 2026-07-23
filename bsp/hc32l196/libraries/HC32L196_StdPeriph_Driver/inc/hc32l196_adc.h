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
/** \file adc.h
 **
 ** Header file for AD Converter functions
 ** @link ADC Group Some description @endlink
 **
 **   - 2017-06-28 Alex    First Version
 **
 ******************************************************************************/

#ifndef __ADC_H__
#define __ADC_H__


/******************************************************************************/
/* Include files                                                              */
/******************************************************************************/
#include "ddl.h"


/* C binding of definitions if building with C++ compiler */
#ifdef __cplusplus
extern "C"
{
#endif

/**
 ******************************************************************************
 ** \defgroup AdcGroup AD Converter (ADC)
  **
 ******************************************************************************/
 
//@{

/******************************************************************************
 * Global definitions
 ******************************************************************************/
#define ADC_SCAN_CH0_EN     (0x1u)           /*!< SCAN模式使用ADC CH0 */
#define ADC_SCAN_CH1_EN     (0x1u<<1)        /*!< SCAN模式使用ADC CH1 */
#define ADC_SCAN_CH2_EN     (0x1u<<2)        /*!< SCAN模式使用ADC CH2 */
#define ADC_SCAN_CH3_EN     (0x1u<<3)        /*!< SCAN模式使用ADC CH3 */
#define ADC_SCAN_CH4_EN     (0x1u<<4)        /*!< SCAN模式使用ADC CH4 */
#define ADC_SCAN_CH5_EN     (0x1u<<5)        /*!< SCAN模式使用ADC CH5 */
#define ADC_SCAN_CH6_EN     (0x1u<<6)        /*!< SCAN模式使用ADC CH6 */
#define ADC_SCAN_CH7_EN     (0x1u<<7)        /*!< SCAN模式使用ADC CH7 */


/******************************************************************************
 ** Global type definitions
 *****************************************************************************/

 /**
 ******************************************************************************
 ** \brief ADC转换模式
 *****************************************************************************/
typedef enum en_adc_mode
{
    AdcSglMode  = 0u,           /*!< 单输入通道单次转换模式 */
    AdcScanMode = 1u,           /*!< 多输入通道顺序/插队扫描转换模式*/   
}en_adc_mode_t;

/**
 ******************************************************************************
 ** \brief ADC时钟分频选择
 *****************************************************************************/
typedef enum en_adc_clk_sel
{
    AdcMskClkDiv1  = 0u<<2,        /*!< PCLK */
    AdcMskClkDiv2  = 1u<<2,        /*!< 1/2 PCLK */
    AdcMskClkDiv4  = 2u<<2,        /*!< 1/4 PCLK */
    AdcMskClkDiv8  = 3u<<2,        /*!< 1/8 PCLK */
} en_adc_clk_div_t;

/**
 ******************************************************************************
 ** \brief ADC参考电压
 *****************************************************************************/
typedef enum en_adc_ref_vol_sel
{
    AdcMskRefVolSelInBgr1p5 = 0u<<9,        /*!<内部参考电压1.5V(SPS<=200kHz)*/
    AdcMskRefVolSelInBgr2p5 = 1u<<9,        /*!<内部参考电压2.5V(avdd>3V,SPS<=200kHz)*/
    AdcMskRefVolSelExtern1  = 2u<<9,        /*!<外部输入(max avdd)   PB01*/
    AdcMskRefVolSelAVDD     = 3u<<9,        /*!<AVDD*/
}en_adc_ref_vol_sel_t;

/**
 ******************************************************************************
 ** \brief ADC转换通道选择
 *****************************************************************************/
typedef enum en_adc_samp_ch_sel
{
    AdcExInputCH0    =  0u,        /*!<使用PA00*/
    AdcExInputCH1    =  1u,        /*!<使用PA01*/
    AdcExInputCH2    =  2u,        /*!<使用PA02*/
    AdcExInputCH3    =  3u,        /*!<使用PA03*/
    AdcExInputCH4    =  4u,        /*!<使用PA04*/
    AdcExInputCH5    =  5u,        /*!<使用PA05*/
    AdcExInputCH6    =  6u,        /*!<使用PA06*/
    AdcExInputCH7    =  7u,        /*!<使用PA07*/
    AdcExInputCH8    =  8u,        /*!<使用PB00*/
    AdcExInputCH9    =  9u,        /*!<使用PB01*/
    AdcExInputCH10   =  10u,       /*!<使用PC00*/
    AdcExInputCH11   =  11u,       /*!<使用PC01*/
    AdcExInputCH12   =  12u,       /*!<使用PC02*/
    AdcExInputCH13   =  13u,       /*!<使用PC03*/
    AdcExInputCH14   =  14u,       /*!<使用PC04*/
    AdcExInputCH15   =  15u,       /*!<使用PC05*/
    AdcExInputCH16   =  16u,       /*!<使用PB02*/
    AdcExInputCH17   =  17u,       /*!<使用PB10*/
    AdcExInputCH18   =  18u,       /*!<使用PB11*/
    AdcExInputCH19   =  19u,       /*!<使用PB12*/
    AdcExInputCH20   =  20u,       /*!<使用PB13*/
    AdcExInputCH21   =  21u,       /*!<使用PB14*/
    AdcExInputCH22   =  22u,       /*!<使用PB15*/
    AdcExInputCH23   =  23u,       /*!<使用PE15*/
    AdcExInputCH24   =  24u,       /*!<使用PE14*/
    AdcExInputCH25   =  25u,       /*!<使用PE13*/

    AdcDacInput      =  26u,       /*!<使用DAC输出(必须使用输入增益)*/                    
    AdcAVccdiv3Input =  27u,       /*!<使用1/3 AVCC(必须使用输入增益)*/
    AdcAiTsInput     =  28u,       /*!<使用内置温度传感器BGR_TS(必须使用输入增益)*/
    AdcVref1_2Input  =  29u,       /*!<使用内部基准1.2V(必须使用输入增益)*/

}en_adc_samp_ch_sel_t;

 /**
 ******************************************************************************
 ** \brief ADC输入信号放大器控制
 *****************************************************************************/
typedef enum en_adc_op_buf
{
    AdcMskBufEnable  = 1u<<11,          /*!< 打开放大器BUF */
    AdcMskBufDisable = 0u,              /*!< 关闭放大器BUF */  
} en_adc_op_buf_t;

/**
 ******************************************************************************
 ** \brief ADC采样周期选择
 *****************************************************************************/
typedef enum en_adc_samp_cycle_sel
{
    AdcMskSampCycle4Clk  =  0u<<12,        /*!<4个采样时钟*/
    AdcMskSampCycle6Clk  =  1u<<12,        /*!<6个采样时钟*/
    AdcMskSampCycle8Clk  =  2u<<12,        /*!<8个采样时钟*/
    AdcMskSampCycle12Clk =  3u<<12,        /*!<12个采样时钟*/

}en_adc_samp_cycle_sel_t;

 /**
 ******************************************************************************
 ** \brief ADC内部参考电压使能控制
 *****************************************************************************/
typedef enum en_adc_in_ref
{
    AdcMskInRefEnable  = 1u<<14,          /*!< 内部参考电压使能 */
    AdcMskInRefDisable = 0u,              /*!< 内部参考电压关闭 */  
}en_adc_in_ref_t;

/**
 ******************************************************************************
 ** \brief ADC周边模块反射源选择
 *****************************************************************************/
typedef enum en_adc_trig_sel
{
    AdcMskTrigTimer0     =  1u<<0,         /*!<选择timer0中断源，自动触发ADC采样*/
    AdcMskTrigTimer1     =  1u<<1,         /*!<选择timer1中断源，自动触发ADC采样*/
    AdcMskTrigTimer2     =  1u<<2,         /*!<选择timer2中断源，自动触发ADC采样*/
    AdcMskTrigTimer3     =  1u<<3,         /*!<选择timer3中断源，自动触发ADC采样*/
    AdcMskTrigTimer4     =  1u<<4,         /*!<选择timer4中断源，自动触发ADC采样*/
    AdcMskTrigTimer5     =  1u<<5,         /*!<选择timer5中断源，自动触发ADC采样*/
    AdcMskTrigTimer6     =  1u<<6,         /*!<选择timer6中断源，自动触发ADC采样*/
    AdcMskTrigUart0      =  1u<<7,         /*!<选择uart0中断源，自动触发ADC采样*/
    AdcMskTrigUart1      =  1u<<8,         /*!<选择uart1中断源，自动触发ADC采样*/
    AdcMskTrigLpuart0    =  1u<<9,         /*!<选择lpuart0中断源，自动触发ADC采样*/
    AdcMskTrigLpuart1    =  1u<<10,        /*!<选择lpuart1中断源，自动触发ADC采样*/
    AdcMskTrigVC0        =  1u<<11,        /*!<选择VC0中断源，自动触发ADC采样*/
    AdcMskTrigVC1        =  1u<<12,        /*!<选择VC1中断源，自动触发ADC采样*/
    AdcMskTrigRTC        =  1u<<13,        /*!<选择RTC中断源，自动触发ADC采样*/
    AdcMskTrigPCA        =  1u<<14,        /*!<选择PCA中断源，自动触发ADC采样*/
    AdcMskTrigSPI0       =  1u<<15,        /*!<选择SPI0中断源，自动触发ADC采样*/
    AdcMskTrigSPI1       =  1u<<16,        /*!<选择SPI1中断源，自动触发ADC采样*/
    AdcMskTrigDMA        =  1u<<17,        /*!<选择DMA中断源，自动触发ADC采样*/
    AdcMskTrigPA03       =  1u<<18,        /*!<选择PA03中断源，自动触发ADC采样*/
    AdcMskTrigPB03       =  1u<<19,        /*!<选择PB03中断源，自动触发ADC采样*/
    AdcMskTrigPC03       =  1u<<20,        /*!<选择PC03中断源，自动触发ADC采样*/
    AdcMskTrigPD03       =  1u<<21,        /*!<选择PD03中断源，自动触发ADC采样*/
    AdcMskTrigPA07       =  1u<<22,        /*!<选择PA07中断源，自动触发ADC采样*/
    AdcMskTrigPB07       =  1u<<23,        /*!<选择PB07中断源，自动触发ADC采样*/
    AdcMskTrigPC07       =  1u<<24,        /*!<选择PC07中断源，自动触发ADC采样*/
    AdcMskTrigPD07       =  1u<<25,        /*!<选择PD07中断源，自动触发ADC采样*/
    AdcMskTrigPA11       =  1u<<26,        /*!<选择PA11中断源，自动触发ADC采样*/
    AdcMskTrigPB11       =  1u<<27,        /*!<选择PB11中断源，自动触发ADC采样*/
    AdcMskTrigPC11       =  1u<<28,        /*!<选择PC11中断源，自动触发ADC采样*/
    AdcMskTrigPA15       =  1u<<29,        /*!<选择PA15中断源，自动触发ADC采样*/
    AdcMskTrigPB15       =  1u<<30,        /*!<选择PB15中断源，自动触发ADC采样*/
    AdcMskTrigPC15       =  1u<<31,        /*!<选择PC15中断源，自动触发ADC采样*/
}en_adc_trig_sel_t;

/**
 ******************************************************************************
 ** \brief ADC外部触发源寄存器选择
 *****************************************************************************/
typedef enum en_adc_ext_trig_sel
{
    AdcExtTrig0     =  0u,         /*!<单次及顺序扫描转换 外部触发源选择寄存器*/
    AdcExtTrig1     =  1u,         /*!<插队扫描转换 外部触发源选择寄存器*/
}en_adc_ext_trig_sel_t;

/**
 ******************************************************************************
 ** \brief ADC顺序转换通道
 *****************************************************************************/
typedef enum en_adc_sqr_chmux
{
    AdcSQRCH0MUX     =  0u,         /*!<顺序扫描模式转换通道0*/
    AdcSQRCH1MUX     =  1u,         /*!<顺序扫描模式转换通道1*/
    AdcSQRCH2MUX     =  2u,         /*!<顺序扫描模式转换通道2*/
    AdcSQRCH3MUX     =  3u,         /*!<顺序扫描模式转换通道3*/
    AdcSQRCH4MUX     =  4u,         /*!<顺序扫描模式转换通道4*/
    AdcSQRCH5MUX     =  5u,         /*!<顺序扫描模式转换通道5*/
    AdcSQRCH6MUX     =  6u,         /*!<顺序扫描模式转换通道6*/
    AdcSQRCH7MUX     =  7u,         /*!<顺序扫描模式转换通道7*/
    AdcSQRCH8MUX     =  8u,         /*!<顺序扫描模式转换通道8*/
    AdcSQRCH9MUX     =  9u,         /*!<顺序扫描模式转换通道9*/
    AdcSQRCH10MUX    =  10u,        /*!<顺序扫描模式转换通道10*/
    AdcSQRCH11MUX    =  11u,        /*!<顺序扫描模式转换通道11*/
    AdcSQRCH12MUX    =  12u,        /*!<顺序扫描模式转换通道12*/
    AdcSQRCH13MUX    =  13u,        /*!<顺序扫描模式转换通道13*/
    AdcSQRCH14MUX    =  14u,        /*!<顺序扫描模式转换通道14*/
    AdcSQRCH15MUX    =  15u,        /*!<顺序扫描模式转换通道15*/
}en_adc_sqr_chmux_t;

/**
 ******************************************************************************
 ** \brief ADC插队转换通道
 *****************************************************************************/
typedef enum en_adc_jqr_chmux
{
    AdcJQRCH0MUX     =  0u,         /*!<转换通道0*/
    AdcJQRCH1MUX     =  1u,         /*!<转换通道1*/
    AdcJQRCH2MUX     =  2u,         /*!<转换通道2*/
    AdcJQRCH3MUX     =  3u,         /*!<转换通道3*/
}en_adc_jqr_chmux_t;
/**
 ******************************************************************************
 ** \brief ADC结果对齐方式
 *****************************************************************************/
typedef enum en_adc_align
{
     AdcAlignRight  = 0u,
     AdcAlignLeft   = 1u,
}en_adc_align_t;

/**
 ******************************************************************************
 ** \brief ADC转换结果自动累加功能
 *****************************************************************************/
typedef enum en_adc_result_acc
{
     AdcResultAccEnable  = 1u,
     AdcResultAccDisable = 0u,
}en_adc_result_acc_t;

/**
 ******************************************************************************
 ** \brief ADC中断类型定义
 *****************************************************************************/
typedef enum en_adc_irq_type
{
    AdcMskIrqJqr =  1u<<5,        /*!<ADC插队扫描转换完成*/
    AdcMskIrqSqr =  1u<<4,        /*!<ADC顺序扫描转换完成*/
    AdcMskIrqReg =  1u<<3,        /*!<ADC转换结果比较区间内*/
    AdcMskIrqHt  =  1u<<2,        /*!<ADC转换结果高于HT*/
    AdcMskIrqLt  =  1u<<1,        /*!<ADC转换结果低于LT*/
    AdcMskIrqSgl =  1u<<0,        /*!<ADC单次转换完成*/

}en_adc_irq_type_t;


/******************************************************************************
 ** Extern type definitions ('typedef')
 ******************************************************************************/

/**
 ******************************************************************************
 ** \brief  ADC初始化配置结构体
 *****************************************************************************/
typedef struct stc_adc_cfg
{
    en_adc_mode_t           enAdcMode;                  /*! ADC转换模式*/
    
    en_adc_clk_div_t        enAdcClkDiv;                /*! ADC时钟选择*/
    en_adc_samp_cycle_sel_t enAdcSampCycleSel;          /*! ADC采样周期选择*/
    en_adc_ref_vol_sel_t    enAdcRefVolSel;             /*! ADC参考电压选择*/
    en_adc_op_buf_t         enAdcOpBuf;                 /*! ADC输入信号放大器控制使能*/
    en_adc_in_ref_t         enInRef;                    /*! ADC内部参考电压使能*/
    
    en_adc_align_t          enAdcAlign;                 /*! ADC转换结果对齐控制*/
}stc_adc_cfg_t;


/**
 ******************************************************************************
 ** \brief  ADC顺序扫描模式配置结构体
 *****************************************************************************/
typedef struct stc_adc_sqr_cfg
{
    uint8_t                 u8SqrCnt;                   /*! ADC顺序扫描转换次数*/
    en_adc_result_acc_t     enResultAcc;                /*! ADC转换结果自动累加功能*/
    boolean_t               bSqrDmaTrig;                /*! ADC顺序扫描转换完成DMA触发使能*/
}stc_adc_sqr_cfg_t;

/**
 ******************************************************************************
 ** \brief  ADC插队扫描模式配置结构体
 *****************************************************************************/
typedef struct stc_adc_jqr_cfg
{
    uint8_t                 u8JqrCnt;                   /*! ADC顺序扫描转换次数*/
    boolean_t               bJqrDmaTrig;                /*! ADC插队扫描转换完成DMA触发使能*/    
}stc_adc_jqr_cfg_t;


/**
 ******************************************************************************
 ** \brief  ADC比较功能配置结构体
 *****************************************************************************/
typedef struct stc_adc_threshold_cfg
{
    boolean_t bAdcRegCmp ;                  /*!ADC区间使能*/ 
    boolean_t bAdcHtCmp ;                   /*!ADC上超出区间使能*/ 
    boolean_t bAdcLtCmp ;                   /*!ADC下超出区间使能*/
    
    uint32_t u32AdcHighThd;                 /*!ADC比较上阈值*/
    uint32_t u32AdcLowThd;                  /*!ADC比较下阈值*/ 
    
    en_adc_samp_ch_sel_t    enSampChSel;    /*!ADC采样通道选择*/
    
}stc_adc_threshold_cfg_t;


/******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/
//ADC 初始化
en_result_t Adc_Init(stc_adc_cfg_t* pstcAdcCfg);

//ADC 中断使能
void Adc_EnableIrq(void);
//ADC 中断禁止
void Adc_DisableIrq(void);

//ADC 中断/采样完成状态获取
boolean_t Adc_GetIrqStatus(en_adc_irq_type_t enAdcIrq);
//ADC 中断/采样完成状态清除
void Adc_ClrIrqStatus(en_adc_irq_type_t enAdcIrq);

//ADC 使能
void Adc_Enable(void);
//ADC 禁止
void Adc_Disable(void);

//ADC 顺序扫描模式配置
en_result_t Adc_SqrModeCfg(stc_adc_sqr_cfg_t* pstcAdcSqrCfg);
//ADC 插队扫描模式配置
en_result_t Adc_JqrModeCfg(stc_adc_jqr_cfg_t* pstcAdcJqrCfg);

//ADC Sgl 单次转换模式通道选择配置 
en_result_t Adc_CfgSglChannel( en_adc_samp_ch_sel_t enstcAdcSampCh);
//ADC SQR 顺序扫描转换模式通道选择配置 
en_result_t Adc_CfgSqrChannel(en_adc_sqr_chmux_t enstcAdcSqrChMux, en_adc_samp_ch_sel_t enstcAdcSampCh);
//ADC JQR 插队扫描转换模式通道选择配置 
en_result_t Adc_CfgJqrChannel(en_adc_jqr_chmux_t enstcAdcJqrChMux, en_adc_samp_ch_sel_t enstcAdcSampCh);

///<ADC 单次转换外部触发源配置
void Adc_SglExtTrigCfg(en_adc_trig_sel_t enAdcTrigSel, boolean_t bValue);
///<ADC 顺序扫描转换外部触发源配置
void Adc_SqrExtTrigCfg(en_adc_trig_sel_t enAdcTrigSel, boolean_t bValue);
///<ADC 插队扫描转换外部触发源配置
void Adc_JqrExtTrigCfg(en_adc_trig_sel_t enAdcTrigSel, boolean_t bValue);

//ADC 阈值比较功能配置
void Adc_ThresholdCfg(stc_adc_threshold_cfg_t* pstcAdcThrCfg);

//ADC 单次转换模式启动
void Adc_SGL_Start(void);
//ADC 单次转换模式停止
void Adc_SGL_Stop(void);

//ADC 单次转换模式一直转换模式启动
void Adc_SGL_Always_Start(void);
//ADC 单次转换模式一直转换模式停止
void Adc_SGL_Always_Stop(void);

//ADC 顺序扫描转换模式启动
void Adc_SQR_Start(void);
//ADC 顺序扫描转换模式停止
void Adc_SQR_Stop(void);

//ADC 插队扫描转换模式启动
void Adc_JQR_Start(void);
//ADC 插队扫描转换模式停止
void Adc_JQR_Stop(void);

//获取单次转换采样值
uint32_t Adc_GetSglResult(void);
//获取顺序扫描采样值
uint32_t Adc_GetSqrResult(en_adc_sqr_chmux_t enstcAdcSqrChMux);
//获取插队扫描采样值
uint32_t Adc_GetJqrResult(en_adc_jqr_chmux_t enstcAdcJqrChMux);

//获取累加采样值
uint32_t Adc_GetAccResult(void);
//clear ADC 累加寄存器结果清除
void Adc_ClrAccResult(void);

//@}
#ifdef __cplusplus
}
#endif

#endif /* __ADC_H__ */
/******************************************************************************/
/* EOF (not truncated)                                                        */
/******************************************************************************/
