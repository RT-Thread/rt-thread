


#ifndef __CH57x_ADC_H__
#define __CH57x_ADC_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include "CH579SFR.h"
#include "core_cm0.h"


#define ROM_TMP_85C_ADDR    0x40634
#define ROM_TMP_25C_ADDR    0x40638


/**
  * @brief  adc single channel define
  */
typedef enum
{
    CH_EXTIN_0 = 0,         // ADC 外部模拟通道 0
    CH_EXTIN_1,             // ADC 外部模拟通道 1
    CH_EXTIN_2,             // ADC 外部模拟通道 2
    CH_EXTIN_3,             // ADC 外部模拟通道 3
    CH_EXTIN_4,             // ADC 外部模拟通道 4
    CH_EXTIN_5,             // ADC 外部模拟通道 5
    CH_EXTIN_6,             // ADC 外部模拟通道 6
    CH_EXTIN_7,             // ADC 外部模拟通道 7
    CH_EXTIN_8,             // ADC 外部模拟通道 8
    CH_EXTIN_9,             // ADC 外部模拟通道 9
    CH_EXTIN_10,            // ADC 外部模拟通道 10
    CH_EXTIN_11,            // ADC 外部模拟通道 11
    CH_EXTIN_12,            // ADC 外部模拟通道 12
    CH_EXTIN_13,            // ADC 外部模拟通道 13

    CH_INTE_VBAT,           // ADC 内部电池检测通道
    CH_INTE_VTEMP,          // ADC 内部温度传感器检测通道

}ADC_SingleChannelTypeDef;

/**
  * @brief  adc differential channel define
  */
typedef enum
{
    CH_DIFF_0_2 = 0,            // ADC 差分通道 #0-#2
    CH_DIFF_1_3,                // ADC 差分通道 #1-#3

}ADC_DiffChannelTypeDef;

/**
  * @brief  adc sampling clock
  */
typedef enum
{
    SampleFreq_3_2 = 0,         // 3.2M 采样频率
    SampleFreq_2_67,            // 2.67M 采样频率
    SampleFreq_5_33,            // 5.33M 采样频率
    SampleFreq_4,               // 4M 采样频率
}ADC_SampClkTypeDef;


/**
  * @brief  adc signal PGA
  */
typedef enum
{
    ADC_PGA_1_4 = 0,            // -12dB, 1/4倍
    ADC_PGA_1_2,                // -6dB, 1/2倍
    ADC_PGA_0,                  // 0dB, 1倍，无增益
    ADC_PGA_2,                  // 6dB, 2倍
}ADC_SignalPGATypeDef;


// refer to ADC_SingleChannelTypeDef
#define     ADC_ChannelCfg( d )     (R8_ADC_CHANNEL = d)                                                /* 设置 ADC 采样通道 */
// refer to ADC_SampClkTypeDef
#define     ADC_SampClkCfg( d )     (R8_ADC_CFG=R8_ADC_CFG&(~RB_ADC_CLK_DIV)|(d<<6))                    /* 设置 ADC 采样时钟 */
// refer to ADC_SignalPGATypeDef
#define     ADC_PGACfg( d )         (R8_ADC_CFG=R8_ADC_CFG&(~RB_ADC_PGA_GAIN)|(d<<4))               /* 设置 ADC 信号增益 */
#define     ADC_TempCalibCfg( d )   (R8_TEM_SENSOR=R8_TEM_SENSOR&(~RB_TEM_SEN_CALIB)|d)             /* 设置内部温度传感器校准值 */

void ADC_ExtSingleChSampInit( ADC_SampClkTypeDef sp, ADC_SignalPGATypeDef ga );                     /* 外部信号单通道采样初始化 */
void ADC_ExtDiffChSampInit( ADC_SampClkTypeDef sp, ADC_SignalPGATypeDef ga );                       /* 外部信号差分通道采样初始化 */
void TouchKey_ChSampInit( void );                                                                   /* 触摸按键通道采样初始化 */
void ADC_InterTSSampInit( void );                                                                   /* 内置温度传感器采样初始化 */
void ADC_InterBATSampInit( void );                                                                  /* 内置电池电压采样初始化 */

UINT16 ADC_ExcutSingleConver( void );                                                               /* ADC执行单次转换 */
signed short ADC_DataCalib_Rough( void );
void ADC_DataCalib_Fine( PUINT16 dat, ADC_SignalPGATypeDef ga );
UINT16 TouchKey_ExcutSingleConver( UINT8 d );                                                       /* TouchKey转换后数据 */
int ADC_GetCurrentTS( UINT16 ts_v );                                                              /* 获取当前采样的温度值（℃） */

#define ADC_ReadConverValue()       (R16_ADC_DATA)                                                  /* 读取转换后的数值 */
#define ADC_StartUp()               (R8_ADC_CONVERT = RB_ADC_START)                                 /* ADC启动转换 */
#define ADC_GetITStatus()           ( R8_ADC_INT_FLAG & RB_ADC_IF_EOC )                             /* 获取ADC转换完成标志 */
#define ADC_ClearITFlag()           (R8_ADC_CONVERT = 0)                                            /* 清除ADC转换完成标志 */

#define TouchKey_GetITStatus()      ( R8_ADC_INT_FLAG & RB_ADC_IF_EOC )                             /* 获取TouchKey转换完成标志 */
#define TouchKey_ClearITFlag()      (R8_TKEY_CTRL |= RB_TKEY_PWR_ON)                                /* 清除TouchKey转换完成标志 */


#ifdef __cplusplus
}
#endif

#endif  // __CH57x_ADC_H__

