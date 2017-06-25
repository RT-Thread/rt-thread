/******************************************************************************
*
* @brief  ADC 驱动头文件.  
*
******************************************************************************/
#ifndef ADC_H_
#define ADC_H_
#ifdef __cplusplus
extern "C" {
#endif
	
#include "common.h"
/******************************************************************************
 *
 *定义ADC参考电压
 *
*******************************************************************************/
#define ADC_VREF_VREFH                 0x00         /*!< ADC 参考电压 VREFH*/
#define ADC_VREF_VDDA                  0x01         /*!< ADC 参考电压 VDDA*/

/******************************************************************************
 *
 * 定义ADC时钟源
 *
*******************************************************************************/
#define CLOCK_SOURCE_BUS_CLOCK                          0x00    /*!< ADC时钟源选择总线时钟*/
#define CLOCK_SOURCE_BUS_CLOCK_DIVIDE_2                 0x01    /*!< ADC时钟源选择总线时钟2分频*/
#define CLOCK_SOURCE_ALTCLK                               0x02  /*!< ADC时钟源选择备用时钟*/
#define CLOCK_SOURCE_ADACK                                0x03  /*!< ADC时钟源选择异步时钟*/

/******************************************************************************
 *
 * 定义ADC源分频系数
 *
*******************************************************************************/
#define ADC_ADIV_DIVIDE_1                               0x00        /*!< ADC时钟源分频系数为1*/
#define ADC_ADIV_DIVIDE_2                               0x01        /*!< ADC时钟源分频系数为2*/
#define ADC_ADIV_DIVIDE_4                               0x02        /*!< ADC时钟源分频系数为4*/
#define ADC_ADIV_DIVIDE_8                               0x03        /*!< ADC时钟源分频系数为8*/

/******************************************************************************
 *
 * 定义ADC转换模式
 *
*******************************************************************************/
#define ADC_MODE_8BIT                                0x00       /*!< 8位转换*/
#define ADC_MODE_10BIT                               0x01       /*!< 10位转换*/
#define ADC_MODE_12BIT                               0x02       /*!< 12位转换*/

/*****************************************************************************
 *
 * 定义ADC输入通道
 *
*******************************************************************************/
#define ADC_CHANNEL_AD0                                 0x0  /*!< ADC输入通道0*/
#define ADC_CHANNEL_AD1                                 0x1  /*!< ADC输入通道1*/
#define ADC_CHANNEL_AD2                                 0x2  /*!< ADC输入通道2*/
#define ADC_CHANNEL_AD3                                 0x3  /*!< ADC输入通道3*/
#define ADC_CHANNEL_AD4                                 0x4  /*!< ADC输入通道4*/
#define ADC_CHANNEL_AD5                                 0x5  /*!< ADC输入通道5*/
#define ADC_CHANNEL_AD6                                 0x6  /*!< ADC输入通道6*/
#define ADC_CHANNEL_AD7                                 0x7  /*!< ADC输入通道7*/
#define ADC_CHANNEL_AD8                                 0x8  /*!< ADC输入通道8*/
#define ADC_CHANNEL_AD9                                 0x9  /*!< ADC输入通道9*/
#define ADC_CHANNEL_AD10                                0xa  /*!< ADC输入通道10*/
#define ADC_CHANNEL_AD11                                0xb  /*!< ADC输入通道11*/
#define ADC_CHANNEL_AD12                                0xc  /*!< ADC输入通道12*/
#define ADC_CHANNEL_AD13                                0xd  /*!< ADC输入通道13*/
#define ADC_CHANNEL_AD14                                0xe  /*!< ADC输入通道14*/
#define ADC_CHANNEL_AD15                                0xf  /*!< ADC输入通道15*/
#define ADC_CHANNEL_AD18_VSS                            0x12 /*!< ADC输入通道 VSS */
#define ADC_CHANNEL_AD22_TEMPSENSOR                     0x15 /*!< ADC输入通道温度传感器 */
#define ADC_CHANNEL_AD23_BANDGAP                        0x17 /*!< ADC输入通道带隙 */
#define ADC_CHANNEL_AD29_VREFH                          0x1D /*!< ADC输入通道 Vrefh */
#define ADC_CHANNEL_AD30_VREFL                          0x1E /*!< ADC输入通道 Vrefl */
#define ADC_CHANNEL_DISABLE                             0x1F /*!< ADC输入通道禁用 */

/******************************************************************************
 *
 * 定义 ADC FIFO 深度
 *
*******************************************************************************/
#define ADC_FIFO_DISABLE                                0 /*!< FIFO禁用*/
#define ADC_FIFO_LEVEL2                                 1 /*!< 2级FIFO */
#define ADC_FIFO_LEVEL3                                 2 /*!< 3级FIFO */
#define ADC_FIFO_LEVEL4                                 3 /*!< 4级FIFO */
#define ADC_FIFO_LEVEL5                                 4 /*!< 5级FIFO */
#define ADC_FIFO_LEVEL6                                 5 /*!< 6级FIFO */
#define ADC_FIFO_LEVEL7                                 6 /*!< 7级FIFO */
#define ADC_FIFO_LEVEL8                                 7 /*!< 8级FIFO */

/******************************************************************************
 *
 * 定义ADC转换触发源
 *
*******************************************************************************/
#define ADC_HARDWARE_TRIGGER                            0x01  /*!< 硬件触发 */
#define ADC_SOFTWARE_TRIGGER                            0x00  /*!< 软件触发 */
#define ADC_TRIGGER_RTC                                 0x00  /*!< 选择RTC溢出作为硬件触发源*/
#define ADC_TRIGGER_PIT                                 0x01  /*!< 选择PIT0溢出作为硬件触发源*/
#define ADC_TRIGGER_ETM2INIT                            0x10  /*!< 选择ETM2初始化化作为硬件触发源 */
#define ADC_TRIGGER_ETM2MATCH                           0x11  /*!< 选择ETM2匹配作为硬件触发源 */

/******************************************************************************
 *
 * 定义ADC比较触发模式
 *
*******************************************************************************/
#define ADC_COMPARE_LESS                                0x00 /*!< 输入小于比较电平时比较触发*/
#define ADC_COMPARE_GREATER                             0x01 /*!< 输入大于比价电平时比较触发*/

/******************************************************************************
 *
 * ADC回调函数声明
 *
******************************************************************************/
    typedef void (*ADC_CallbackType)(void);                         /*!< ADC回调函数 */

/******************************************************************************
 *
 * 定义ADC结构体变量
 *
*******************************************************************************/
    typedef struct
    {
        uint16_t bIntEn                 :1;     /*!< 1: 中断使能, 0: 禁用中断 */
        uint16_t bContinuousEn          :1;     /*!< 1: 使能连续转换模式, 0: 禁用连续转换模式 */
        uint16_t bHardwareTriggerEn     :1;     /*!< 1: 硬件触发, 0: 软件触发 */
        uint16_t bCompareEn             :1;     /*!< 1: 使能比较模式, 0: 禁用比较模式 */
        uint16_t bCompareGreaterEn      :1;     /*!< 1: 输入大于或等于比较电平时比较触发, 0: 输入小于比较电平时比较触发 */
        uint16_t bLowPowerEn            :1;     /*!< 1: 低功耗模式, 0: 高速模式 */
        uint16_t bLongSampleEn          :1;     /*!< 1: 长采样模式, 0: 短采样模式 */
        uint16_t bFiFoScanModeEn        :1;     /*!< 1: 使能FIFO扫描模式, 0: 禁用FIFO扫描模式 */
        uint16_t bCompareAndEn          :1;     /*!< 1: 对所有比较触发做与运算, 0: 对所有比较触发做或运算*/
#ifdef CPU_NV32
        uint16_t bReverse               :7;
#else
        uint16_t bHTRGMEn               :1;     /*!< one hardware trigger pulse trigger multiple conversions in fifo mode */
        uint16_t bHTRGMASKEn            :1;     /*!< Hardware trigger mask enable. */
        uint16_t bHTRGMASKSEL           :1;     /*!< This field selects hardware trigger mask mode. */
        uint16_t Reserve                :4;
#endif
    } ADC_SettingType;

/******************************************************************************
 *
 * ADC配置结构体
 *
*******************************************************************************/
    typedef struct
    {
        ADC_SettingType sSetting;               /*!< ADC配置结构体*/
        uint16_t u16PinControl;                 /*!< 引脚控制 */
        uint8_t u8ClockSource;                  /*!< 选择时钟源 */
        uint8_t u8ClockDiv;                     /*!< 设置时钟分频 */
        uint8_t u8Mode;                         /*!< 设置转换模式(8/10/12 bit mode) */
        uint8_t u8FiFoLevel;                    /*!< 设置FIFO深度 */
    } ADC_ConfigType,*ADC_ConfigTypePtr;
		
/*****************************************************************************//*!
 *
 * @brief 使能ADC中断.
 *
 * @param[in]  pADC 指向ADC模块
 *
 * @return none
 *
*****************************************************************************/
__STATIC_INLINE void ADC_IntEnable( ADC_Type *pADC )
 {
    pADC->SC1 |= ADC_SC1_AIEN_MASK;
 }
 
/*****************************************************************************//*!
 *
 * @brief 禁用ADC中断
 *
 * @param[in]  pADC 指向ADC模块
 *
 * @return none
 *
*****************************************************************************/
__STATIC_INLINE void ADC_IntDisable( ADC_Type *pADC )
  {
    pADC->SC1 &= ~ADC_SC1_AIEN_MASK;
  }
	
/*****************************************************************************//*!
 *
 * @brief 使能ADC连续转换.
 *
 * @param[in]  pADC 指向ADC模块.
 *
 * @return none
 *
*****************************************************************************/
__STATIC_INLINE void ADC_ContinuousConversion( ADC_Type *pADC )
 {
   pADC->SC1 |= ADC_SC1_ADCO_MASK;
 }
 
/*****************************************************************************//*!
 *
 * @brief 使能ADC单次转换
 *
 * @param[in]  pADC  指向ADC模块.
 *
 * @return none
 *
*****************************************************************************/
__STATIC_INLINE void ADC_SingleConversion( ADC_Type *pADC )
 {
    pADC->SC1 &= ~ADC_SC1_ADCO_MASK;
 }
 
/*****************************************************************************//*!
 *
 * @brief 设置ADC硬件触发.
 *
 * @param[in]  pADC  指向ADC模块 .
 *
 * @return none.
 *
*****************************************************************************/
__STATIC_INLINE void ADC_SetHardwareTrigger( ADC_Type *pADC )
 {
   pADC->SC2 |= ADC_SC2_ADTRG_MASK;
 }
 
/*****************************************************************************//*!
 *
 * @brief 设置ADC软件触发.
 *
 * @param[in]  pADC  指向ADC模块 .
 *
 * @return none
 *
*****************************************************************************/
__STATIC_INLINE void ADC_SetSoftwareTrigger( ADC_Type *pADC )
 {
   pADC->SC2 &= ~ADC_SC2_ADTRG_MASK;
 }
 
/*****************************************************************************//*!
 *
 * @brief 使能ADC比较功能
 *
 * @param[in]  pADC 指向ADC模块.
 *
 * @return none
 *
*****************************************************************************/
__STATIC_INLINE void ADC_CompareEnable( ADC_Type *pADC )
 {
   pADC->SC2 |= ADC_SC2_ACFE_MASK;
 }
 
/*****************************************************************************//*!
 *
 * @brief 禁用ADC比较功能.
 *
 * @param[in]  pADC  指向ADC模块
 *
 * @return none
 *
*****************************************************************************/
 __STATIC_INLINE void ADC_CompareDisable( ADC_Type *pADC )
  {
    pADC->SC2 &= ~ADC_SC2_ACFE_MASK;
  }
	
/*****************************************************************************//*!
 *
 * @brief 输入大于或等于比较电平时比较触发
 *
 * @param[in]  pADC   指向ADC模块.
 *
 * @return none
 *
*****************************************************************************/
__STATIC_INLINE void ADC_CompareGreaterFunction( ADC_Type *pADC )
  {
    pADC->SC2 |= ADC_SC2_ACFGT_MASK;
  }
	
/*****************************************************************************//*!
 *
 * @brief 输入小于比价电平时比较触发
 *
 * @param[in]  pADC   指向ADC模块
 *
 * @return none
 *
*****************************************************************************/
__STATIC_INLINE void ADC_CompareLessFunction( ADC_Type *pADC )
 {
   pADC->SC2 &= ~ADC_SC2_ACFGT_MASK;
 }
 
/*****************************************************************************//*!
 *
 * @brief 设置ADC为低功耗模式
 *
 * @param[in]   pADC 指向ADC模块
 *
 * @return none
 *
*****************************************************************************/
__STATIC_INLINE void ADC_SetLowPower( ADC_Type *pADC )
 {
   pADC->SC3 |= ADC_SC3_ADLPC_MASK;
 }
 
/*****************************************************************************//*!
 *
 * @brief 设置ADC为高速模式.
 *
 * @param[in]  pADC 指向ADC模块..
 *
 * @return none
 *
*****************************************************************************/
 __STATIC_INLINE void ADC_SetHighSpeed( ADC_Type *pADC )
  {
    pADC->SC3 &= ~ADC_SC3_ADLPC_MASK;
  }
	
/*****************************************************************************//*!
 *
 * @brief 设置ADC长采样.
 *
 * @param[in]  pADC   指向ADC模块.
 *
 * @return none
 *
*****************************************************************************/
__STATIC_INLINE void ADC_SetLongSample( ADC_Type *pADC )
 {
   pADC->SC3 |= ADC_SC3_ADLSMP_MASK;
 }
 
/*****************************************************************************//*!
 *
 * @brief 设置ADC短采样
 *
 * @param[in]  pADC  指向ADC模块.
 *
 * @return none
 *
*****************************************************************************/
__STATIC_INLINE void ADC_SetShortSample( ADC_Type *pADC )
 {
   pADC->SC3 &= ~ADC_SC3_ADLSMP_MASK;
 }
 
/*****************************************************************************//*!
 *
 * @brief 使能FIFO扫描模式
 *
 * @param[in]  pADC  指向ADC模块.
 *
 * @return none.
 *
*****************************************************************************/
__STATIC_INLINE void ADC_FifoScanModeEnable( ADC_Type *pADC )
  {
    pADC->SC4 |= ADC_SC4_ASCANE_MASK;
  }
	
/*****************************************************************************//*!
 *
 * @brief 禁用FIFO扫描模式.
 *
 * @param[in]  pADC  指向ADC模块.
 *
 * @return none
 *
*****************************************************************************/
__STATIC_INLINE void ADC_FifoScanModeDisable( ADC_Type *pADC )
 {
  pADC->SC4 &= ~ADC_SC4_ASCANE_MASK;
 }
/*****************************************************************************//*!
 *
 * @brief 对所有比较触发做或运算.
 *
 * @param[in]  pADC  指向ADC模块.
 *
 * @return none
 *
 *****************************************************************************/
__STATIC_INLINE void ADC_CompareFifoOr( ADC_Type *pADC )
 {
   pADC->SC4 &= ~ADC_SC4_ACFSEL_MASK;
 }
 
/*****************************************************************************//*!
 *
 * @brief 对所有比较触发做与运算
 *
 * @param[in]  pADC  指向ADC模块.
 *
 * @return none
 *
*****************************************************************************/
__STATIC_INLINE void ADC_CompareFifoAnd( ADC_Type *pADC )
 {
   pADC->SC4 |= ADC_SC4_ACFSEL_MASK;
 }
/*****************************************************************************//*!
 *
 * @brief 对ADC转换结果寄存器.
 *
 * @param[in]  pADC  指向ADC模块.
 *
 * @return ADC result value.
 *
*****************************************************************************/
__STATIC_INLINE uint16_t ADC_ReadResultReg( ADC_Type *pADC )
 {
   return (uint16_t)pADC->R;
 }
 
/*****************************************************************************//*!
 *
 * @brief 设置比较值.
 *
 * @param[in]  pADC  指向ADC模块.
 * @param[in]  u16Compare  比较值
 *
 * @return none
 *
*****************************************************************************/
__STATIC_INLINE void ADC_SetCompareValue( ADC_Type *pADC, uint16_t u16Compare )
  {
    pADC->CV = u16Compare;
  }
	
/*****************************************************************************//*!
 *
 * @brief 使能ADC输入引脚.
 *
 * @param[in]  pADC  指向ADC模块.
 * @param[in]  u16PinNumber    使能的ADC引脚
 *
 * @return none
 *
 * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void ADC_PinControlEnable( ADC_Type *pADC, uint16_t u16PinNumber)
  {
     ASSERT((u16PinNumber<16));
     pADC->APCTL1 &= ~(0x01<<u16PinNumber);
  }
	
/*****************************************************************************//*!
 *
 * @brief 禁用ADC输入引脚.
 *
 * @param[in]  pADC  指向ADC模块.
 * @param[in]  u16PinNumber  禁用的ADC引脚.
 *
 * @return none
 *
*****************************************************************************/
__STATIC_INLINE void ADC_PinControlDisable( ADC_Type *pADC, uint16_t u16PinNumber)
 {
   ASSERT((u16PinNumber<16));
   pADC->APCTL1 |= (0x01<<u16PinNumber);
 }
 
/*****************************************************************************//*!
 *
 * @brief 查看ADC转换状态
 *
 * @param[in]  pADC  指向ADC模块..
 *
 * @return 1 or 0
 *
*****************************************************************************/
__STATIC_INLINE uint8_t ADC_IsConversionActiveFlag( ADC_Type *pADC )
  {
    return(pADC->SC2 & ADC_SC2_ADACT_MASK);
  }
/*****************************************************************************//*!
 *
 * @brief 读取转换完成标准位
 *
 * @param[in]  pADC  指向ADC模块..
 *
 * @return 1 or 0
 *
*****************************************************************************/
__STATIC_INLINE uint8_t ADC_IsCOCOFlag( ADC_Type *pADC )
 {
   return(pADC->SC1 & ADC_SC1_COCO_MASK);
 }
 
/*****************************************************************************//*!
 *
 * @brief 读取结果FIFO中是否有有效新数据标志位
 *
 * @param[in]  pADC point to ADC module type.
 *
 * @return 1 or 0
 *
*****************************************************************************/
__STATIC_INLINE uint8_t ADC_IsFIFOEmptyFlag( ADC_Type *pADC )
 {
   return(pADC->SC2 & ADC_SC2_FEMPTY_MASK);
 }
 
/*****************************************************************************//*!
 *
 * @brief 读取结果FIFO是否满标志位
 *
 * @param[in]  pADC  指向ADC模块.
 *
 * @return  1 or 0
 *
*****************************************************************************/
__STATIC_INLINE uint8_t ADC_IsFIFOFullFlag( ADC_Type *pADC )
 {
   return(pADC->SC2 & ADC_SC2_FFULL_MASK);
 }
#ifndef CPU_NV32
/*****************************************************************************//*!
 *
 * @brief Hardware Trigger Multiple Conversion Enable
 *
 * @param[in]  pADC point to ADC module type.
 *
 * @return none
 *
*****************************************************************************/
__STATIC_INLINE void ADC_HardwareTriggerMultiple( ADC_Type *pADC )
  {
    pADC->SC4 |= ADC_SC4_HTRGME_MASK;
  }
/*****************************************************************************//*!
 *
 * @brief Hardware Trigger Single Conversion
 *
 * @param[in]  pADC point to ADC module type.
 *
 * @return none
 *
*****************************************************************************/
__STATIC_INLINE void ADC_HardwareTriggerSingle( ADC_Type *pADC )
{
   pADC->SC4 &= ~ADC_SC4_HTRGME_MASK;
}
/*****************************************************************************//*!
 *
 * @brief Hardware Trigger Mask Enable
 *
 * @param[in]  pADC point to ADC module type.
 *
 * @return none
 *
*****************************************************************************/
__STATIC_INLINE void ADC_HardwareTriggerMaskEnable( ADC_Type *pADC )
  {
    pADC->SC5 |= ADC_SC5_HTRGMASKE_MASK;
  }
/*****************************************************************************//*!
 *
 * @brief Hardware Trigger Mask Disable
 *
 * @param[in]  pADC point to ADC module type.
 *
 * @return none
 *
*****************************************************************************/
__STATIC_INLINE void ADC_HardwareTriggerMaskDisable( ADC_Type *pADC )
 {
   pADC->SC5 &= ~ADC_SC5_HTRGMASKE_MASK;
 }
/*****************************************************************************//*!
 *
 * @brief Hardware Trigger Mask Mode Select Automatic Mode
 *
 * @param[in]  pADC point to ADC module type.
 *
 * @return none
 *
*****************************************************************************/
__STATIC_INLINE void ADC_HardwareTriggerMaskAuto( ADC_Type *pADC )
  {
    pADC->SC5 |= ADC_SC5_HTRGMASKSEL_MASK;
  }
/*****************************************************************************//*!
 *
 * @brief Hardware Trigger Mask Mode Select to be with HTRGMASKE
 *
 * @param[in]  pADC point to ADC module type.
 *
 * @return none
 *
 * @ Pass/ Fail criteria: none
*****************************************************************************/
__STATIC_INLINE void ADC_HardwareTriggerMaskNonAuto( ADC_Type *pADC )
  {
    pADC->SC5 &= ~ADC_SC5_HTRGMASKSEL_MASK;
  }
#endif
/******************************************************************************
 * Global function
 ******************************************************************************/
void ADC_SetChannel( ADC_Type *pADC, uint8_t u8Channel );
void ADC_IntEnable( ADC_Type *pADC );
void ADC_IntDisable( ADC_Type *pADC );
void ADC_ContinuousConversion( ADC_Type *pADC );
void ADC_SingleConversion( ADC_Type *pADC );
void ADC_SetSoftwareTrigger( ADC_Type *pADC );
void ADC_SetHardwareTrigger( ADC_Type *pADC );
void ADC_VrefSelect( ADC_Type *pADC, uint8_t u8Vref );
void ADC_CompareEnable( ADC_Type *pADC );
void ADC_CompareDisable( ADC_Type *pADC );
void ADC_CompareGreaterFunction( ADC_Type *pADC );
void ADC_CompareLessFunction( ADC_Type *pADC );
void ADC_SetLowPower( ADC_Type *pADC );
void ADC_SetHighSpeed( ADC_Type *pADC );
void ADC_SelectClockDivide( ADC_Type *pADC, uint8_t u8Div);
void ADC_SetLongSample(ADC_Type *pADC);
void ADC_SetShortSample(ADC_Type *pADC);
void ADC_SetMode(ADC_Type *pADC, uint8_t u8Mode);
void ADC_SelectClock(ADC_Type *pADC, uint8_t u8Clock);
void ADC_FifoScanModeEnable(ADC_Type *pADC);
void ADC_FifoScanModeDisable(ADC_Type *pADC);
void ADC_CompareFifoOr(ADC_Type *pADC);
void ADC_CompareFifoAnd(ADC_Type *pADC);
void ADC_SetFifoLevel(ADC_Type *pADC, uint8_t u8FifoLevel);
uint16_t ADC_ReadResultReg(ADC_Type *pADC );
void ADC_SetCompareValue(ADC_Type *pADC, uint16_t u16Compare );
void ADC_PinControlEnable(ADC_Type *pADC, uint16_t u16PinNumber);
void ADC_PinControlDisable(ADC_Type *pADC, uint16_t u16PinNumber);
uint8_t ADC_IsConversionActiveFlag(ADC_Type *pADC);
uint8_t ADC_IsCOCOFlag(ADC_Type *pADC);
uint8_t ADC_IsFIFOEmptyFlag(ADC_Type *pADC);
uint8_t ADC_IsFIFOFullFlag(ADC_Type *pADC);
void ADC_HardwareTriggerMaskNonAuto(ADC_Type *pADC);
void ADC_HardwareTriggerMaskAuto(ADC_Type *pADC);
void ADC_HardwareTriggerMaskDisable( ADC_Type *pADC );
void ADC_HardwareTriggerMaskEnable( ADC_Type *pADC );
void ADC_HardwareTriggerSingle( ADC_Type *pADC );
void ADC_HardwareTriggerMultiple( ADC_Type *pADC );
unsigned int ADC_PollRead( ADC_Type *pADC, uint8_t u8Channel);
void ADC_SetCallBack(ADC_CallbackType pADC_CallBack);
void ADC_DeInit(ADC_Type *pADC);
void ADC_Init(ADC_Type *pADC, ADC_ConfigTypePtr pADC_Config);
#ifdef __cplusplus
}
#endif
#endif
