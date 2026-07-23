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
#include "interrupts_hc32l136.h"

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
 ** \brief ADC采样模式
 *****************************************************************************/
typedef enum en_adc_op_mode
{
    AdcSglMode  = 0u,        /*!< 单输入通道单次采样模式 */
    AdcSCanMode     = 1u,        /*!< 多输入通道顺序扫描采样模式,多输入通道插队扫描采样模式*/   
} en_adc_op_mode_t;

/**
 ******************************************************************************
 ** \brief ADC时钟选择
 *****************************************************************************/
typedef enum en_adc_clk_sel
{
    AdcClkSysTDiv1  = 0u,        /*!< PCLK */
    AdcClkSysTDiv2  = 1u,        /*!< 1/2 PCLK */
    AdcClkSysTDiv4  = 2u,        /*!< 1/4 PCLK */
    AdcClkSysTDiv8  = 3u,        /*!< 1/8 PCLK */

} en_adc_clk_div_t;

/**
 ******************************************************************************
 ** \brief ADC参考电压
 *****************************************************************************/
typedef enum en_adc_ref_vol_sel
{
    RefVolSelInBgr1p5 = 0u,        /*!<内部参考电压1.5V(SPS<=200kHz)*/
    RefVolSelInBgr2p5 = 1u,        /*!<内部参考电压2.5V(avdd>3V,SPS<=200kHz)*/
    RefVolSelExtern1  = 2u,        /*!<外部输入(max avdd)   PB01*/
    RefVolSelAVDD     = 3u,        /*!<AVDD*/

}en_adc_ref_vol_sel_t;

/**
 ******************************************************************************
 ** \brief ADC采样通道选择
 *****************************************************************************/
typedef enum en_adc_samp_ch_sel
{
    AdcExInputCH0    =  0u,        /*!<使用通道0输入PA00*/
    AdcExInputCH1    =  1u,        /*!<使用通道1输入PA01*/
    AdcExInputCH2    =  2u,        /*!<使用通道2输入PA02*/
    AdcExInputCH3    =  3u,        /*!<使用通道3输入PA03*/
    AdcExInputCH4    =  4u,        /*!<使用通道4输入PA04*/
    AdcExInputCH5    =  5u,        /*!<使用通道5输入PA05*/
    AdcExInputCH6    =  6u,        /*!<使用通道6输入PA06*/
    AdcExInputCH7    =  7u,        /*!<使用通道7输入PA07*/
    AdcExInputCH8    =  8u,        /*!<使用通道8输入PB00*/
    AdcExInputCH9    =  9u,        /*!<使用通道8输入PB01*/
    AdcExInputCH10   =  10u,       /*!<使用通道8输入PC00*/
    AdcExInputCH11   =  11u,       /*!<使用通道1输入PC01*/
    AdcExInputCH12   =  12u,       /*!<使用通道2输入PC02*/
    AdcExInputCH13   =  13u,       /*!<使用通道3输入PC03*/
    AdcExInputCH14   =  14u,       /*!<使用通道4输入PC04*/
    AdcExInputCH15   =  15u,       /*!<使用通道5输入PC05*/
    AdcExInputCH16   =  16u,       /*!<使用通道6输入PB02*/
    AdcExInputCH17   =  17u,       /*!<使用通道7输入PB10*/
    AdcExInputCH18   =  18u,       /*!<使用通道8输入PB11*/
    AdcExInputCH19   =  19u,       /*!<使用通道8输入PB12*/
    AdcExInputCH20   =  20u,       /*!<使用通道7输入PB13*/
    AdcExInputCH21   =  21u,       /*!<使用通道8输入PB14*/
    AdcExInputCH22   =  22u,       /*!<使用通道8输入PB15*/
    AdcExInputCH23   =  23u,       /*!<使用通道8输入PC06*/  
    AdcOPA0Input     =  24u,       /*!<使用通道8输入OPA0*/
    AdcOPA1Input     =  25u,       /*!<使用通道8输入OPA1*/
    AdcOPA2Input     =  26u,       /*!<使用通道8输入OPA2*/                     
    AdcAVccDiV3Input =  27u,       /*!<使用1/3 AVCC(必须使用输入增益)*/
    AdcAiTsInput     =  28u,       /*!<使用BGR_TS(必须使用输入增益)*/
    AdcVref1P2Input  =  29u,       /*!<使用Vref1P2(必须使用输入增益)*/

}en_adc_samp_ch_sel_t;

/**
 ******************************************************************************
 ** \brief ADC采样周期数选择
 *****************************************************************************/
typedef enum en_adc_samp_time_sel
{
    AdcSampTime4Clk  =  0u,        /*!<4个采样时钟*/
    AdcSampTime6Clk  =  1u,        /*!<6个采样时钟*/
    AdcSampTime8Clk  =  2u,        /*!<8个采样时钟*/
    AdcSampTime12Clk =  3u,        /*!<12个采样时钟*/

}en_adc_samp_time_sel_t;

/**
 ******************************************************************************
 ** \brief ADC周边模块反射源选择
 *****************************************************************************/
typedef enum en_adc_trig_sel
{
    AdcTrigTimer0     =  0u,         /*!<选择timer0中断源，自动触发ADC采样*/
    AdcTrigTimer1     =  1u,         /*!<选择timer1中断源，自动触发ADC采样*/
    AdcTrigTimer2     =  2u,         /*!<选择timer2中断源，自动触发ADC采样*/
    AdcTrigTimer3     =  3u,         /*!<选择timer3中断源，自动触发ADC采样*/
    AdcTrigTimer4     =  4u,         /*!<选择timer4中断源，自动触发ADC采样*/
    AdcTrigTimer5     =  5u,         /*!<选择timer5中断源，自动触发ADC采样*/
    AdcTrigTimer6     =  6u,         /*!<选择timer6中断源，自动触发ADC采样*/
    AdcTrigUart0      =  7u,         /*!<选择uart0中断源，自动触发ADC采样*/
    AdcTrigUart1      =  8u,         /*!<选择uart1中断源，自动触发ADC采样*/
    AdcTrigLpuart0    =  9u,         /*!<选择lpuart0中断源，自动触发ADC采样*/
    AdcTrigLpuart1    =  10u,        /*!<选择lpuart1中断源，自动触发ADC采样*/
    AdcTrigVC0        =  11u,        /*!<选择VC0中断源，自动触发ADC采样*/
    AdcTrigVC1        =  12u,        /*!<选择VC1中断源，自动触发ADC采样*/
    AdcTrigRTC        =  13u,        /*!<选择RTC中断源，自动触发ADC采样*/
    AdcTrigPCA        =  14u,        /*!<选择PCA中断源，自动触发ADC采样*/
    AdcTrigSPI0       =  15u,        /*!<选择SPI0中断源，自动触发ADC采样*/
    AdcTrigSPI1       =  16u,        /*!<选择SPI1中断源，自动触发ADC采样*/
    AdcTrigDMA        =  17u,        /*!<选择DMA中断源，自动触发ADC采样*/
    AdcTrigPA03       =  18u,        /*!<选择PA03中断源，自动触发ADC采样*/
    AdcTrigPB03       =  19u,        /*!<选择PB03中断源，自动触发ADC采样*/
    AdcTrigPC03       =  20u,        /*!<选择PC03中断源，自动触发ADC采样*/
    AdcTrigPD03       =  21u,        /*!<选择PD03中断源，自动触发ADC采样*/
    AdcTrigPA07       =  22u,        /*!<选择PA07中断源，自动触发ADC采样*/
    AdcTrigPB07       =  23u,        /*!<选择PB07中断源，自动触发ADC采样*/
    AdcTrigPC07       =  24u,        /*!<选择PC07中断源，自动触发ADC采样*/
    AdcTrigPD07       =  25u,        /*!<选择PD07中断源，自动触发ADC采样*/
    AdcTrigPA11       =  26u,        /*!<选择PA11中断源，自动触发ADC采样*/
    AdcTrigPB11       =  27u,        /*!<选择PB11中断源，自动触发ADC采样*/
    AdcTrigPC11       =  28u,        /*!<选择PC11中断源，自动触发ADC采样*/
    AdcTrigPA15       =  29u,        /*!<选择PA15中断源，自动触发ADC采样*/
    AdcTrigPB15       =  30u,        /*!<选择PB15中断源，自动触发ADC采样*/
    AdcTrigPC15       =  31u,        /*!<选择PC15中断源，自动触发ADC采样*/
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
    CH0MUX     =  0u,         /*!<转换通道0*/
    CH1MUX     =  1u,         /*!<转换通道1*/
    CH2MUX     =  2u,         /*!<转换通道2*/
    CH3MUX     =  3u,         /*!<转换通道3*/
    CH4MUX     =  4u,         /*!<转换通道4*/
    CH5MUX     =  5u,         /*!<转换通道5*/
    CH6MUX     =  6u,         /*!<转换通道6*/
    CH7MUX     =  7u,         /*!<转换通道7*/
    CH8MUX     =  8u,         /*!<转换通道8*/
    CH9MUX     =  9u,         /*!<转换通道9*/
    CH10MUX    =  10u,        /*!<转换通道10*/
    CH11MUX    =  11u,        /*!<转换通道11*/
    CH12MUX    =  12u,        /*!<转换通道12*/
    CH13MUX    =  13u,        /*!<转换通道13*/
    CH14MUX    =  14u,        /*!<转换通道14*/
    CH15MUX    =  15u,        /*!<转换通道15*/
}en_adc_sqr_chmux_t;
/**
 ******************************************************************************
 ** \brief ADC插队转换通道
 *****************************************************************************/
typedef enum en_adc_jqr_chmux
{
    JQRCH0MUX     =  0u,         /*!<转换通道0*/
    JQRCH1MUX     =  1u,         /*!<转换通道1*/
    JQRCH2MUX     =  2u,         /*!<转换通道2*/
    JQRCH3MUX     =  3u,         /*!<转换通道3*/
}en_adc_jqr_chmux_t;
/**
 ******************************************************************************
 ** \brief ADC结果对齐方式
 *****************************************************************************/
typedef enum en_adc_align
{
     AlignRight  = 0u,
     AlignLeft = 1u,    
}en_adc_align_t;
/******************************************************************************
 * Extern type definitions ('typedef')                                        *
 ******************************************************************************/

/**
 ******************************************************************************
 ** \brief  ADC配置
 *****************************************************************************/
typedef struct stc_adc_cfg
{
    /*! ADC操作模式*/
    en_adc_op_mode_t enAdcOpMode;

    /*! ADC时钟选择*/
    en_adc_clk_div_t  enAdcClkDiv;

    /*! ADC采样时间*/
    en_adc_samp_time_sel_t  enAdcSampTimeSel;

    /*! ADC参考电压*/
    en_adc_ref_vol_sel_t    enAdcRefVolSel;

    /*! ADC输入增益使能*/
    boolean_t    bAdcInBufEn;
}stc_adc_cfg_t;

 /**
 ******************************************************************************
 ** \brief  ADC DMA触发源寄存器配置
 *****************************************************************************/
typedef enum en_adc_dmatrig
{
   /*!插队扫描触发DMA读取控制*/ 
  DmaJqr = 0, 
   /*!顺序扫描触发DMA读取控制*/   
  DmaSqr = 1   
}en_adc_dmatrig_t;
 /**
 ******************************************************************************
 ** \brief  ADC外部触发源寄存器配置
 *****************************************************************************/
typedef struct stc_adc_ext_trig_cfg
{
    /*! 外部触发源寄存器选择*/
    en_adc_ext_trig_sel_t   enAdcExtTrigRegSel;
    
    /*! ADC单次及顺序转换触发选择*/
    en_adc_trig_sel_t       enAdcTrig0Sel;

    /*! ADC插队转换触发选择*/
    en_adc_trig_sel_t       enAdcTrig1Sel;

}stc_adc_ext_trig_cfg_t;

/**
 ******************************************************************************
 ** \brief  ADC中断配置
 *****************************************************************************/
typedef struct stc_adc_irq
{
    /*!<ADC插队扫描完成中断*/
    boolean_t  bAdcJQRIrq;   
    /*!<ADC顺序扫描完成中断*/
    boolean_t  bAdcSQRIrq;  
    /*! ADC区间中断*/
    boolean_t  bAdcRegCmp;
    /*! ADC上超出区间中断*/
    boolean_t  bAdcHhtCmp;
    /*! ADC下超出区间中断*/
    boolean_t  bAdcLltCmp;    
    /*!<ADC单次转换完成中断*/
    boolean_t  bAdcIrq;
}stc_adc_irq_t;

typedef struct stc_adc_threshold_cfg
{
   
    boolean_t bAdcRegCmp ;      /*!ADC区间使能*/ 

    boolean_t bAdcHhtCmp ;     /*!ADC上超出区间使能*/ 

    boolean_t bAdcLltCmp ;     /*!ADC下超出区间使能*/
    
    uint32_t u32AdcRegHighThd; /*!ADC下超出区间*/
    
    uint32_t u32AdcRegLowThd; /*!ADC下超出区间*/ 
    
    en_adc_samp_ch_sel_t enThCh; /*!阈值比较通道选择*/
    
}stc_adc_threshold_cfg_t;
/**
 ******************************************************************************
 ** \brief  ADC中断回调函数
 *****************************************************************************/
typedef struct stc_adc_irq_calbakfn_pt
{
    /*! ADC插队扫描中断回调函数指针*/
    func_ptr_t  pfnAdcJQRIrq;
    /*! ADC顺序扫描中断回调函数指针*/
    func_ptr_t  pfnAdcSQRIrq;    
    /*! ADC区间中断回调函数指针*/
    func_ptr_t  pfnAdcRegIrq;
    /*! ADC上超出区间中断回调函数指针*/
    func_ptr_t  pfnAdcHhtIrq;
    /*! ADC下超出区间中断回调函数指针*/
    func_ptr_t  pfnAdcLltIrq;
    /*! ADC单次转换中断回调函数指针*/
    func_ptr_t  pfnAdcIrq; 
}stc_adc_irq_calbakfn_pt_t;

/******************************************************************************
 * Global variable definitions ('extern')
 ******************************************************************************/

/******************************************************************************
 * Global function prototypes (definition in C source)
 ******************************************************************************/
//ADC initialization
en_result_t Adc_Init(stc_adc_cfg_t* pstcAdcConfig);
//ADC ExtTrig Register config
en_result_t Adc_ExtTrigCfg(stc_adc_ext_trig_cfg_t* pstcExtTrigConfig);
//ADC de-init
void Adc_DeInit(void);

//ADC conversion start
void Adc_SGL_Start(void);
//ADC conversion stop
void Adc_SGL_Stop(void);

//ADC SQR conversion start
void Adc_SQR_Start(void);
//ADC SQR conversion stop
void Adc_SQR_Stop(void);

//ADC JQR conversion start
void Adc_JQR_Start(void);
//ADC JQR conversion stop
void Adc_JQR_Stop(void);

//ADC conversion enable
void Adc_Enable(void);
//ADC conversion disable
void Adc_Disable(void);

//ADC single covert mode configuration
en_result_t Adc_ConfigSglMode(stc_adc_cfg_t* pstcAdcConfig);
//ADC SQR mode configuration
en_result_t Adc_ConfigSqrMode(stc_adc_cfg_t* pstcAdcConfig, uint8_t u8AdcSampCnt,boolean_t  bAdcResultAccEn);
//ADC JQR mode configuration
en_result_t Adc_ConfigJqrMode(stc_adc_cfg_t* pstcAdcConfig, uint8_t u8AdcSampCnt,boolean_t  bAdcResultAccEn);

//ADC single covert mode channel configuraion 
en_result_t Adc_ConfigSglChannel( en_adc_samp_ch_sel_t enstcAdcSampCh);
//ADC SQR mode channel configuraion 
en_result_t Adc_ConfigSqrChannel(en_adc_sqr_chmux_t enstcAdcSqrChMux, en_adc_samp_ch_sel_t enstcAdcSampCh);
//ADC JQR mode channel configuraion 
en_result_t Adc_ConfigJqrChannel(en_adc_jqr_chmux_t enstcAdcJqrChMux, en_adc_samp_ch_sel_t enstcAdcSampCh);
//ADC DMA Trigger 
en_result_t Adc_ConfigDmaTrig(en_adc_dmatrig_t enAdcDmaTrig);
//ADC IRQ configuration
void Adc_ConfigIrq(stc_adc_irq_t* pstcAdcIrqCfg,
                   stc_adc_irq_calbakfn_pt_t* pstcAdcIrqCalbaks);
//ADC enable IRQ
void Adc_EnableIrq(void);
//ADC disable IRQ
void Adc_DisableIrq(void);
//ADC enable threshold compare
void Adc_ThresholdCfg(stc_adc_threshold_cfg_t* stcAdcThrCfg);
//ADC get IRQ state
void Adc_GetIrqState(stc_adc_irq_t* pstcAdcIrqState);
//ADC clear IRQ states
void Adc_ClrSglIrqState(void);
void Adc_ClrJqrIrqState(void);
void Adc_ClrSqrIrqState(void);
void Adc_ClrRegIrqState(void);
void Adc_ClrHtIrqState(void);
void Adc_ClrLtIrqState(void);

//查询ADC单次转换状态
boolean_t Adc_PollSglBusyState(void);
//查询ADC顺序扫描转换转换状态
boolean_t Adc_PollSqrBusyState(void);
//查询ADC插队扫描转换状态
boolean_t Adc_PollJqrBusyState(void);
//查询ADC结果比较区间状态
boolean_t Adc_PollRegBusyState(void);
//查询ADC结果比较上阈值状态
boolean_t Adc_PollHTBusyState(void);
//查询ADC结果比较下阈值状态
boolean_t Adc_PollLtBusyState(void);
//获取单次转换采样值
en_result_t Adc_GetSglResult(uint16_t* pu16AdcResult);
//获取顺序扫描采样值
en_result_t Adc_GetSqrResult(uint16_t* pu16AdcResult,uint8_t SQRChannelIndex);
//获取插队扫描采样值
en_result_t Adc_GetJqrResult(uint16_t* pu16AdcResult,uint8_t JQRChannelIndex);
//获取累加采样值
en_result_t Adc_GetAccResult(uint32_t* pu32AdcAccResult);
//clear ADC accumulated result
void Adc_ClrAccResult(void);
//设置参考电压
en_result_t Adc_SetVref(en_adc_ref_vol_sel_t enAdcRefVolSel);
//设置结果对齐方式
en_result_t Adc_SetAlign(en_adc_align_t enAlign);
//@}
#ifdef __cplusplus
}
#endif

#endif /* __ADC_H__ */
/******************************************************************************/
/* EOF (not truncated)                                                        */
/******************************************************************************/
