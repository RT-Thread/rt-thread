/*
  ******************************************************************************
  * @file    HAL_ADC.h
  * @version V1.0.0
  * @date    2020
  * @brief   Header file of ADC HAL module.
  ******************************************************************************
*/
#ifndef __HAL_ADC_H__
#define __HAL_ADC_H__

#include "ACM32Fxx_HAL.h"

/****************  Total definition for ADC  **************************/
#define ADC_CH_MASK                           (BIT4|BIT3|BIT2|BIT1|BIT0)

/****************  Bit definition for ADC_SR register  **************************/
#define ADC_SR_AWD                            (BIT5)
#define ADC_SR_OVERF                          (BIT4)
#define ADC_SR_EOG                            (BIT3)
#define ADC_SR_JEOC                           (BIT2)
#define ADC_SR_EOC                            (BIT1)
#define ADC_SR_ADRDY                          (BIT0)

/****************  Bit definition for ADC_IE register  **************************/
#define ADC_IE_AWDIE                          (BIT5)
#define ADC_IE_OVERFIE                        (BIT4)
#define ADC_IE_EOGIE                          (BIT3)
#define ADC_IE_JEOCIE                         (BIT2)
#define ADC_IE_EOCIE                          (BIT1)

/****************  Bit definition for ADC_CR1 register  **************************/
#define ADC_CR1_AWDJCH_POS                     (27U)
#define ADC_CR1_AWDJCH_MASK                    (BIT31|BIT30|BIT29|BIT28|BIT27)
#define ADC_CR1_DISCNUM_POS                    (23U)
#define ADC_CR1_DISCNUM_MASK                   (BIT26|BIT25|BIT24|BIT23)
#define ADC_CR1_DISCEN                         BIT22
#define ADC_CR1_CONT                           BIT21
#define ADC_CR1_SWSTART                        BIT20
#define ADC_CR1_JSWSTART                       BIT19
#define ADC_CR1_EXTSEL_POS                     (16U)
#define ADC_CR1_EXTSEL_MASK                    (BIT18|BIT17|BIT16)
#define ADC_CR1_JEXTSEL_POS                    (13U)
#define ADC_CR1_JEXTSEL_MASK                   (BIT15|BIT14|BIT13)
#define ADC_CR1_DMA                            BIT12
#define ADC_CR1_AWDEN                          BIT11
#define ADC_CR1_JAWDEN                         BIT10
#define ADC_CR1_JEN                            BIT9
#define ADC_CR1_AWDSGL                         BIT8
#define ADC_CR1_AWDCH_POS                      (0U)
#define ADC_CR1_AWDCH_MASK                     (BIT4|BIT3|BIT2|BIT1|BIT0)

/****************  Bit definition for ADC_CR2 register  **************************/
#define ADC_CR2_FASTMOD                        BIT27
#define ADC_CR2_AFE_RSTN                       BIT26
#define ADC_CR2_JOVSE                          BIT25
#define ADC_CR2_JTOVS                          BIT24
#define ADC_CR2_OVSS_POS                      (20U)
#define ADC_CR2_OVSS_MASK                     (BIT23|BIT22|BIT21|BIT20)
#define ADC_CR2_OVSR_POS                      (17U)
#define ADC_CR2_OVSR_MASK                     (BIT19|BIT18|BIT17)
#define ADC_CR2_OVSE                           BIT16
#define ADC_CR2_BUF_STIME_POS                 (8U)
#define ADC_CR2_BUF_STIME_MASK                (BIT15|BIT14|BIT13|BIT12|BIT11|BIT10|BIT9|BIT8)
#define ADC_CR2_EN_BUF                         BIT7
#define ADC_CR2_DIV_POS                       (3U)
#define ADC_CR2_DIV_MASK                      (BIT6|BIT5|BIT4|BIT3)
#define ADC_CR2_ADC_STP                        BIT2
#define ADC_CR2_OVRMOD                         BIT1
#define ADC_CR2_ADC_EN                         BIT0

/****************  Bit definition for ADC_SMPR1 register  **************************/
#define ADC_SMPR_CH_MASK                      (BIT3|BIT2|BIT1|BIT0)

/****************  Bit definition for ADC_DIFF register  **************************/
#define ADC_DIFF_DIFF7_F                       BIT7
#define ADC_DIFF_DIFF6_E                       BIT6
#define ADC_DIFF_DIFF5_D                       BIT5
#define ADC_DIFF_DIFF4_C                       BIT4
#define ADC_DIFF_DIFF3_B                       BIT3
#define ADC_DIFF_DIFF2_A                       BIT2
#define ADC_DIFF_DIFF1_9                       BIT1
#define ADC_DIFF_DIFF0_8                       BIT0

/****************  Bit definition for ADC_HTR register  ***********************/
#define ADC_HTR_DHT                           (BIT27|BIT26|BIT25|BIT24|BIT23|BIT22|BIT21|BIT20|BIT19|BIT18|BIT17|BIT16)
#define ADC_HTR_HT                            (BIT11|BIT10|BIT9|BIT8|BIT7|BIT6|BIT5|BIT4|BIT3|BIT2|BIT1|BIT0)

/****************  Bit definition for ADC_LTR register  ***********************/
#define ADC_LTR_DLT                           (BIT27|BIT26|BIT25|BIT24|BIT23|BIT22|BIT21|BIT20|BIT19|BIT18|BIT17|BIT16)
#define ADC_LTR_LT                            (BIT11|BIT10|BIT9|BIT8|BIT7|BIT6|BIT5|BIT4|BIT3|BIT2|BIT1|BIT0)

/****************  Bit definition for ADC_SQR1 register  ***********************/
#define ADC_SQR1_L                            (BIT3|BIT2|BIT1|BIT0)

/****************  Bit definition for ADC_JSQR register  ***********************/
#define ADC_JSQR_JSQ                          (BIT4|BIT3|BIT2|BIT1|BIT0)

/****************  Bit definition for ADC_JDR register  ***********************/
#define ADC_JDR_JCH                           (BIT20|BIT19|BIT18|BIT17|BIT16)

/****************  Bit definition for ADC_DR register  ***********************/
#define ADC_DR_CH                             (BIT20|BIT19|BIT18|BIT17|BIT16)

/****************  Bit definition for ADC_SIGN register  ***********************/
#define ADC_SIGN_SIGN7_F                       BIT7
#define ADC_SIGN_SIGN6_E                       BIT6
#define ADC_SIGN_SIGN5_D                       BIT5
#define ADC_SIGN_SIGN4_C                       BIT4
#define ADC_SIGN_SIGN3_B                       BIT3
#define ADC_SIGN_SIGN2_A                       BIT2
#define ADC_SIGN_SIGN1_9                       BIT1
#define ADC_SIGN_SIGN0_8                       BIT0

/****************  Bit definition for ADC_TSREF register  ***********************/
#define ADC_TSREF_VREF1P2_EN                   BIT31
#define ADC_TSREF_HIZ_EN                       BIT27
#define ADC_TSREF_VREFBI_SEL_POS              (25U)
#define ADC_TSREF_VREFBI_SEL_MASK             (BIT26|BIT25)
#define ADC_TSREF_VREFBI_EN                    BIT24
#define ADC_TSREF_VTRIM_POS                   (19U)
#define ADC_TSREF_VTRIM_MASK                  (BIT23|BIT22|BIT21|BIT20|BIT19)
#define ADC_TSREF_TTRIM_POS                   (15U)
#define ADC_TSREF_TTRIM_MASK                  (BIT18|BIT17|BIT16|BIT15)
#define ADC_TSREF_ALG_MEAN_POS                (9U)
#define ADC_TSREF_ALG_MEAN_MASK               (BIT10|BIT9)
#define ADC_TSREF_ADJ_TD_OS_POS               (5U)
#define ADC_TSREF_ADJ_TD_OS_MASK              (BIT8|BIT7|BIT6|BIT5)
#define ADC_TSREF_ADJ_TD_GA_POS               (1U)
#define ADC_TSREF_ADJ_TD_GA_MASK              (BIT4|BIT3|BIT2|BIT1)
#define ADC_TSREF_EN_TS                        BIT0

/****************  Macro definition for register operation **************************/


/**************** Enable the specified ADC. **************************/
#define __HAL_ADC_ENABLE(__HANDLE__)                                           \
  (SET_BIT((__HANDLE__)->Instance->CR2, (ADC_CR2_ADC_EN)))

/**************** Disable the specified ADC. **************************/
#define __HAL_ADC_DISABLE(__HANDLE__)                                          \
  (CLEAR_BIT((__HANDLE__)->Instance->CR2, (ADC_CR2_ADC_EN)))

/**************** Enable the specified ADC interrupt source. **************************/
#define __HAL_ADC_ENABLE_IT(__HANDLE__, __INTERRUPT__)                         \
  (SET_BIT((__HANDLE__)->Instance->IE, (__INTERRUPT__)))

/**************** Disable the specified ADC interrupt source. **************************/
#define __HAL_ADC_DISABLE_IT(__HANDLE__, __INTERRUPT__)                        \
  (CLEAR_BIT((__HANDLE__)->Instance->IE, (__INTERRUPT__)))

/**************** Checks if the specified ADC interrupt source is enabled or disabled. **************************/
#define __HAL_ADC_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__)                     \
  (((__HANDLE__)->Instance->IE & (__INTERRUPT__)) == (__INTERRUPT__))

/**************** Get the selected ADC's flag status. **************************/
#define __HAL_ADC_GET_FLAG(__HANDLE__, __FLAG__)                               \
  ((((__HANDLE__)->Instance->SR) & (__FLAG__)) == (__FLAG__))

/**************** Clear the selected ADC's flag status. **************************/
#define __HAL_ADC_CLEAR_FLAG(__HANDLE__, __FLAG__)                             \
  (SET_BIT((__HANDLE__)->Instance->SR, (__FLAG__)))

/**************** Checks if the ADC regular group trig source is the specified source. **************************/
#define __HAL_ADC_CHECK_TRIG_REGULAR(__HANDLE__, __TRIGSOURCE__)                     \
  ((((__HANDLE__)->Instance->CR1 & ADC_CR1_EXTSEL_MASK) >> ADC_CR1_EXTSEL_POS) == (__TRIGSOURCE__))

/**************** Checks if the ADC injected channel trig source is the specified source. **************************/
#define __HAL_ADC_CHECK_TRIG_INJECTED(__HANDLE__, __TRIGSOURCE__)                     \
  ((((__HANDLE__)->Instance->CR1 & ADC_CR1_JEXTSEL_MASK) >> ADC_CR1_JEXTSEL_POS) == (__TRIGSOURCE__))

/****************  Bit definition for ADC_SMPR3 register  **************************/
#define ADC_SMPR3_CONV_PLUS_POS               (20U)
#define ADC_SMPR3_CONV_PLUS_MASK              (BIT21|BIT20)

/**
  * @brief  ADC ExTigger structure definition
  */
typedef struct
{
  uint32_t ExTrigSel;                     /*!< Configures the regular channel trig mode. */
  uint32_t JExTrigSel;                    /*!< Configures the inject channel trig mode. */
}ADC_ExTrigTypeDef;

/**
  * @brief  ADC group regular oversampling structure definition
  */
typedef struct
{
  uint32_t Ratio;                         /*!< Configures the oversampling ratio.
                                               This parameter can be a value of @ref ADC_CR2_OVSR_2X*/

  uint32_t RightBitShift;                 /*!< Configures the division coefficient for the Oversampler.
                                               This parameter can be a value of @ref ADC_CR2_OVSS_0 */

  uint32_t TriggeredMode;                 /*!< Selects the regular triggered oversampling mode.
                                               This parameter can be a value of
                                               0 : trig 1 time; other: trig N times, N refer to the oversampling Ratio*/
}ADC_OversamplingTypeDef;

/******************************** ADC Init mode define *******************************/
/******************************** ConConvMode define *******************************/
#define  ADC_CONCONVMODE_DISABLE                (0)
#define  ADC_CONCONVMODE_ENABLE                 (1)

/******************************** JChannelMode define *******************************/
#define  ADC_JCHANNELMODE_DISABLE               (0)
#define  ADC_JCHANNELMODE_ENABLE                (1)

/******************************** DiffMode define *******************************/
#define  ADC_DIFFMODE_DISABLE                   (0)
#define  ADC_DIFFMODE_ENABLE                    (1)

/******************************** DMAMode define *******************************/
#define  ADC_DMAMODE_DISABLE                    (0)
#define  ADC_DMAMODE_ENABLE                     (1)

/******************************** OverMode define *******************************/
#define  ADC_OVERMODE_DISABLE                   (0)
#define  ADC_OVERMODE_ENABLE                    (1)

/******************************** OverSampMode define *******************************/
#define  ADC_OVERSAMPMODE_DISABLE               (0)
#define  ADC_OVERSAMPMODE_ENABLE                (1)

/******************************** AnalogWDGEn define *******************************/
#define  ADC_ANALOGWDGEN_DISABLE                (0)
#define  ADC_ANALOGWDGEN_ENABLE                 (1)

/**
  * @brief  ADC Configuration Structure definition
  */
typedef struct
{
    uint32_t ClockDiv;              /*!< Specify the ADC clock div from the PCLK.
                                      This parameter can be set to ADC_CLOCK_DIV1 | ADC_CLOCK_DIV2 |... ADC_CLOCK_DIV16 */

    uint32_t ConConvMode;           /*!< Specify whether the conversion is performed in single mode (one conversion) or continuous mode for ADC group regular,
                                       after the first ADC conversion start trigger occurred (software start or external trigger).
                                       This parameter can be set to ADC_CONCONVMODE_DISABLE or ADC_CONCONVMODE_ENABLE. */
    uint32_t JChannelMode;          /*!< Specify if support inject channel. This parameter can be set to ADC_JCHANNELMODE_DISABLE or ADC_JCHANNELMODE_ENABLE*/
    uint32_t DiffMode;              /*!< Specify the differential parameters.
                                       ADC_DIFFMODE_DISABLE:single end mode,
                                       ADC_DIFFMODE_ENABLE:differential end mode */
    uint32_t ChannelEn;             /*!< Specify the enable ADC channels.
                                       This parameter can be set to ADC_CHANNEL_0_EN | ADC_CHANNEL_1_EN |... ADC_CHANNEL_15_EN*/

    ADC_ExTrigTypeDef ExTrigMode;    /*!< ADC ExTigger structure, config the regular and inject channel trig mode */

    uint32_t DMAMode;                /*!< Specify whether the DMA requests are performed in one shot mode (DMA transfer stops when number of conversions is reached)
                                       or in continuous mode (DMA transfer unlimited, whatever number of conversions).
                                       This parameter can be set to ADC_DMAMODE_ENABLE or ADC_DMAMODE_DISABLE.
                                       Note: In continuous mode, DMA must be configured in circular mode. Otherwise an overrun will be triggered when DMA buffer maximum pointer is reached. */

    uint32_t OverMode;               /*!<  ADC_OVERMODE_DISABLE,ADC_OVERMODE_ENABLE*/

    uint32_t OverSampMode;          /*!< Specify whether the oversampling feature is enabled or disabled.
                                           This parameter can be set to ADC_OVERSAMPMODE_ENABLE or ADC_OVERSAMPMODE_DISABLE.
                                           Note: This parameter can be modified only if there is no conversion is ongoing on ADC group regular. */
    ADC_OversamplingTypeDef Oversampling;   /*!< Specify ADC group regular oversampling structure. */

    uint32_t AnalogWDGEn;
}ADC_InitTypeDef;


typedef struct
{
    uint32_t RjMode;                /*!< Specify the channel mode, 0:regular, Other:inject*/
    uint32_t Channel;               /*!< Specify the channel to configure into ADC regular group.
                                        This parameter can be a value of @ref ADC_CHANNEL_0
                                        Note: Depending on devices and ADC instances, some channels may not be available on device package pins. Refer to device datasheet for channels availability. */

    uint32_t Sq;                    /*!< Add or remove the channel from ADC regular group sequencer and specify its conversion rank.
                                        This parameter is dependent on ScanConvMode:
                                        - sequencer configured to fully configurable:
                                          Channels ordering into each rank of scan sequence:
                                          whatever channel can be placed into whatever rank.
                                        - sequencer configured to not fully configurable:
                                          rank of each channel is fixed by channel HW number.
                                          (channel 0 fixed on rank 0, channel 1 fixed on rank1, ...).
                                          Despite the channel rank is fixed, this parameter allow an additional possibility: to remove the selected rank (selected channel) from sequencer.
                                        This parameter can be a value of @ref ADC_SEQUENCE_SQ1 */

    uint32_t Smp;                    /*!< Sampling time value to be set for the selected channel.
                                        Unit: ADC clock cycles
                                        This parameter can be a value of @ref ADC_SMP_CLOCK_3 */
}ADC_ChannelConfTypeDef;

typedef struct
{
    uint32_t WatchdogMode;      /*!< Configure the ADC analog watchdog mode: single/all/none channels.
                                   For Analog Watchdog 1: Configure the ADC analog watchdog mode: single channel or all channels, ADC group regular.
                                   For Analog Watchdog 2 and 3: Several channels can be monitored by applying successively the AWD init structure.
                                   This parameter can be a value of @ref ADC_ANALOGWATCHDOG_RCH_ALL. */

    uint32_t Channel;           /*!< Select which ADC channel to monitor by analog watchdog.
                                   For Analog Watchdog 1: this parameter has an effect only if parameter 'WatchdogMode' is configured on single channel (only 1 channel can be monitored).
                                   For Analog Watchdog 2 and 3: Several channels can be monitored. To use this feature, call successively the function HAL_ADC_AnalogWDGConfig() for each channel to be added (or removed with value 'ADC_ANALOGWATCHDOG_NONE').
                                   This parameter can be a value of @ref ADC_CHANNEL_0. */

    uint32_t ITMode;            /*!< Specify whether the analog watchdog is configured in interrupt or polling mode.
                                   This parameter can be set to ENABLE or DISABLE */

    uint32_t HighThreshold;     /*!< Configure the ADC analog watchdog High threshold value. */

    uint32_t LowThreshold;      /*!< Configures the ADC analog watchdog Low threshold value. */
}ADC_AnalogWDGConfTypeDef;

/******************************** ADC Over Sample Shift define *******************************/
#define ADC_CR2_OVSS_0                (0U)
#define ADC_CR2_OVSS_1                (1U)
#define ADC_CR2_OVSS_2                (2U)
#define ADC_CR2_OVSS_3                (3U)
#define ADC_CR2_OVSS_4                (4U)
#define ADC_CR2_OVSS_5                (5U)
#define ADC_CR2_OVSS_6                (6U)
#define ADC_CR2_OVSS_7                (7U)
#define ADC_CR2_OVSS_8                (8U)

/******************************** ADC Over Sample Rate define *******************************/
#define ADC_CR2_OVSR_2X               (0U)
#define ADC_CR2_OVSR_4X               (1U)
#define ADC_CR2_OVSR_8X               (2U)
#define ADC_CR2_OVSR_16X              (3U)
#define ADC_CR2_OVSR_32X              (4U)
#define ADC_CR2_OVSR_64X              (5U)
#define ADC_CR2_OVSR_128X             (6U)
#define ADC_CR2_OVSR_256X             (7U)

/******************************** ADC Sample period define *******************************/
#define ADC_SMP_CLOCK_3               (0U)
#define ADC_SMP_CLOCK_5               (1U)
#define ADC_SMP_CLOCK_7               (2U)
#define ADC_SMP_CLOCK_10              (3U)
#define ADC_SMP_CLOCK_13              (4U)
#define ADC_SMP_CLOCK_16              (5U)
#define ADC_SMP_CLOCK_20              (6U)
#define ADC_SMP_CLOCK_30              (7U)
#define ADC_SMP_CLOCK_60              (8U)
#define ADC_SMP_CLOCK_80              (9U)
#define ADC_SMP_CLOCK_100             (10U)
#define ADC_SMP_CLOCK_120             (11U)
#define ADC_SMP_CLOCK_160             (12U)
#define ADC_SMP_CLOCK_320             (13U)
#define ADC_SMP_CLOCK_480             (14U)
#define ADC_SMP_CLOCK_640             (15U)


/******************************** ADC ClockPrescale define *******************************/
#define  ADC_CLOCK_DIV1                              (0U)
#define  ADC_CLOCK_DIV2                              (1U)
#define  ADC_CLOCK_DIV3                              (2U)
#define  ADC_CLOCK_DIV4                              (3U)
#define  ADC_CLOCK_DIV5                              (4U)
#define  ADC_CLOCK_DIV6                              (5U)
#define  ADC_CLOCK_DIV7                              (6U)
#define  ADC_CLOCK_DIV8                              (7U)
#define  ADC_CLOCK_DIV9                              (8U)
#define  ADC_CLOCK_DIV10                             (9U)
#define  ADC_CLOCK_DIV11                             (10U)
#define  ADC_CLOCK_DIV12                             (11U)
#define  ADC_CLOCK_DIV13                             (12U)
#define  ADC_CLOCK_DIV14                             (13U)
#define  ADC_CLOCK_DIV15                             (14U)
#define  ADC_CLOCK_DIV16                             (15U)

/************************ADC_AnalogWDGConfTypeDef->WatchdogMode define********************/
#define  ADC_ANALOGWATCHDOG_RCH_ALL                 (1U)   //All regular channels
#define  ADC_ANALOGWATCHDOG_JCH_ALL                 (2U)   //All inject channels
#define  ADC_ANALOGWATCHDOG_RCH_AND_JCH_ALL         (3U)   //All regular and inject channels
#define  ADC_ANALOGWATCHDOG_RCH_SINGLE              (4U)   //Single regular channel
#define  ADC_ANALOGWATCHDOG_JCH_SINGLE              (5U)   //Single Inject channel
#define  ADC_ANALOGWATCHDOG_RCH_OR_JCH_SINGLE       (6U)   //Regular or inject channel

/******************************** ADC sequence number define *******************************/
#define  ADC_SEQUENCE_SQ1                           (1U)
#define  ADC_SEQUENCE_SQ2                           (2U)
#define  ADC_SEQUENCE_SQ3                           (3U)
#define  ADC_SEQUENCE_SQ4                           (4U)
#define  ADC_SEQUENCE_SQ5                           (5U)
#define  ADC_SEQUENCE_SQ6                           (6U)
#define  ADC_SEQUENCE_SQ7                           (7U)
#define  ADC_SEQUENCE_SQ8                           (8U)
#define  ADC_SEQUENCE_SQ9                           (9U)
#define  ADC_SEQUENCE_SQ10                          (10U)
#define  ADC_SEQUENCE_SQ11                          (11U)
#define  ADC_SEQUENCE_SQ12                          (12U)
#define  ADC_SEQUENCE_SQ13                          (13U)
#define  ADC_SEQUENCE_SQ14                          (14U)
#define  ADC_SEQUENCE_SQ15                          (15U)
#define  ADC_SEQUENCE_SQ16                          (16U)

/******************************** ADC channel number define *******************************/
#define  ADC_CHANNEL_0                              (0U)
#define  ADC_CHANNEL_1                              (1U)
#define  ADC_CHANNEL_2                              (2U)
#define  ADC_CHANNEL_3                              (3U)
#define  ADC_CHANNEL_4                              (4U)
#define  ADC_CHANNEL_5                              (5U)
#define  ADC_CHANNEL_6                              (6U)
#define  ADC_CHANNEL_7                              (7U)
#define  ADC_CHANNEL_8                              (8U)
#define  ADC_CHANNEL_9                              (9U)
#define  ADC_CHANNEL_10                             (10U)
#define  ADC_CHANNEL_11                             (11U)
#define  ADC_CHANNEL_12                             (12U)
#define  ADC_CHANNEL_13                             (13U)
#define  ADC_CHANNEL_14                             (14U)
#define  ADC_CHANNEL_15                             (15U)
#define  ADC_CHANNEL_TEMP                           (16U)
#define  ADC_CHANNEL_VBAT                           (17U)
#define  ADC_CHANNEL_VBGR                           (18U)
#define  ADC_CHANNEL_EXT2                           (19U)
#define  ADC_CHANNEL_EXT3                           (20U)

/******************************** ADC channel enable define *******************************/
#define  ADC_CHANNEL_0_EN                              (BIT0)
#define  ADC_CHANNEL_1_EN                              (BIT1)
#define  ADC_CHANNEL_2_EN                              (BIT2)
#define  ADC_CHANNEL_3_EN                              (BIT3)
#define  ADC_CHANNEL_4_EN                              (BIT4)
#define  ADC_CHANNEL_5_EN                              (BIT5)
#define  ADC_CHANNEL_6_EN                              (BIT6)
#define  ADC_CHANNEL_7_EN                              (BIT7)
#define  ADC_CHANNEL_8_EN                              (BIT8)
#define  ADC_CHANNEL_9_EN                              (BIT9)
#define  ADC_CHANNEL_10_EN                             (BIT10)
#define  ADC_CHANNEL_11_EN                             (BIT11)
#define  ADC_CHANNEL_12_EN                             (BIT12)
#define  ADC_CHANNEL_13_EN                             (BIT13)
#define  ADC_CHANNEL_14_EN                             (BIT14)
#define  ADC_CHANNEL_15_EN                             (BIT15)
#define  ADC_CHANNEL_TEMP_EN                           (BIT16)
#define  ADC_CHANNEL_VBAT_EN                           (BIT17)
#define  ADC_CHANNEL_VBGR_EN                           (BIT18)
#define  ADC_CHANNEL_EXT2_EN                           (BIT19)
#define  ADC_CHANNEL_EXT3_EN                           (BIT20)

/******************************** ADC Trig source define*******************************
 *  |     Trig Source           |     ACM32FXXX/FPXXX    |      ACM32F0X0          | *
 *  |     ADC_SOFTWARE_START    |     SWSTART/JSWSTART   |      SWSTART/JSWSTART   | *
 *  |     ADC_EXTERNAL_TIG1     |     TIM1_TRGO          |      TIM1_TRGO          | *
 *  |     ADC_EXTERNAL_TIG2     |     TIM1_CC4           |      TIM1_CC4           | *
 *  |     ADC_EXTERNAL_TIG3     |     TIM2_TRGO          |      RSV                | *
 *  |     ADC_EXTERNAL_TIG4     |     TIM3_TRGO          |      TIM3_TRGO          | *
 *  |     ADC_EXTERNAL_TIG5     |     TIM4_TRGO          |      TIM15_TRGO         | *
 *  |     ADC_EXTERNAL_TIG6     |     TIM6_TRGO          |      TIM6_TRGO          | *
 *  |     ADC_EXTERNAL_TIG7     |     EXTi Line 11       |      EXTi Line 11       | */
#define  ADC_SOFTWARE_START                           (0U)
#define  ADC_EXTERNAL_TIG1                            (1U)
#define  ADC_EXTERNAL_TIG2                            (2U)
#define  ADC_EXTERNAL_TIG3                            (3U)
#define  ADC_EXTERNAL_TIG4                            (4U)
#define  ADC_EXTERNAL_TIG5                            (5U)
#define  ADC_EXTERNAL_TIG6                            (6U)
#define  ADC_EXTERNAL_TIG7                            (7U)


/******************************** ADC results flag define for HAL level*******************************/
#define HAL_ADC_EOC_FLAG            0x80000000
#define HAL_ADC_JEOC_FLAG           0x40000000
#define HAL_ADC_AWD_FLAG            0x20000000

/**
  * @brief  ADC handle Structure definition
  */
typedef struct __ADC_HandleTypeDef
{
    ADC_TypeDef                     *Instance;                              /*!< Register base address */
    ADC_InitTypeDef                 Init;                                   /*!< ADC initialization parameters and regular conversions setting */
    DMA_HandleTypeDef               *DMA_Handle;                            /*!< Pointer DMA Handler */
    uint32_t                        ChannelNum;                             /*!< Total enable regular group channel number*/
    uint32_t                        *AdcResults;                            /*!< Point to the convert results*/
    void (*ConvCpltCallback)(struct __ADC_HandleTypeDef *hadc);             /*!< ADC conversion complete callback */
    void (*GroupCpltCallback)(struct __ADC_HandleTypeDef *hadc);            /*!< ADC regular group conversion complete callback */
    void (*InjectedConvCpltCallback)(struct __ADC_HandleTypeDef *hadc);     /*!< ADC injected conversion complete callback */
    void (*LevelOutOfWindowCallback)(struct __ADC_HandleTypeDef *hadc);     /*!< ADC analog watchdog callback */
}ADC_HandleTypeDef;

/******************************** ADC Instances *******************************/
#define IS_ADC_ALL_INSTANCE(INSTANCE)    ((INSTANCE) == ADC)
#define IS_ADC_ALL_CONCONVMODE(CONCONVMODE)     (((CONCONVMODE) == ADC_CONCONVMODE_DISABLE) || \
                                                 ((CONCONVMODE) == ADC_CONCONVMODE_ENABLE))

#define IS_ADC_ALL_JCHANNELMODE(JCHANNELMODE)    (((JCHANNELMODE) == ADC_JCHANNELMODE_DISABLE) || \
                                                  ((JCHANNELMODE) == ADC_JCHANNELMODE_ENABLE))

#define IS_ADC_ALL_DIFFMODE(DIFFMODE)            (((DIFFMODE) == ADC_DIFFMODE_DISABLE) || \
                                                  ((DIFFMODE) == ADC_DIFFMODE_ENABLE))

#define IS_ADC_ALL_DMAMODE(DMAMODE)              (((DMAMODE) == ADC_DMAMODE_DISABLE) || \
                                                  ((DMAMODE) == ADC_DMAMODE_ENABLE))

#define IS_ADC_ALL_OVERMODE(OVERMODE)            (((OVERMODE) == ADC_OVERMODE_DISABLE) || \
                                                  ((OVERMODE) == ADC_OVERMODE_ENABLE))

#define IS_ADC_ALL_OVERSAMPMODE(OVERSAMPMODE)    (((OVERSAMPMODE) == ADC_OVERSAMPMODE_DISABLE) || \
                                                  ((OVERSAMPMODE) == ADC_OVERSAMPMODE_ENABLE))

#define IS_ADC_ALL_OVSS(_OVSS)             (((_OVSS) == ADC_CR2_OVSS_0) || \
                                            ((_OVSS) == ADC_CR2_OVSS_1) || \
                                            ((_OVSS) == ADC_CR2_OVSS_2) || \
                                            ((_OVSS) == ADC_CR2_OVSS_3) || \
                                            ((_OVSS) == ADC_CR2_OVSS_4) || \
                                            ((_OVSS) == ADC_CR2_OVSS_5) || \
                                            ((_OVSS) == ADC_CR2_OVSS_6) || \
                                            ((_OVSS) == ADC_CR2_OVSS_7) || \
                                            ((_OVSS) == ADC_CR2_OVSS_8))

#define IS_ADC_ALL_OVSR(_OVSR)             (((_OVSR) == ADC_CR2_OVSR_2X) || \
                                            ((_OVSR) == ADC_CR2_OVSR_4X) || \
                                            ((_OVSR) == ADC_CR2_OVSR_8X) || \
                                            ((_OVSR) == ADC_CR2_OVSR_16X) || \
                                            ((_OVSR) == ADC_CR2_OVSR_32X) || \
                                            ((_OVSR) == ADC_CR2_OVSR_64X) || \
                                            ((_OVSR) == ADC_CR2_OVSR_128X) || \
                                            ((_OVSR) == ADC_CR2_OVSR_256X))

#define IS_ADC_ALL_ANALOGWDGEN(ANALOGWDGEN)      (((ANALOGWDGEN) == ADC_ANALOGWDGEN_DISABLE) || \
                                                  ((ANALOGWDGEN) == ADC_ANALOGWDGEN_ENABLE))

#define IS_ADC_ALL_CLOCKDIV(CLOCKDIV)      (((CLOCKDIV) == ADC_CLOCK_DIV1) || \
                                            ((CLOCKDIV) == ADC_CLOCK_DIV2) || \
                                            ((CLOCKDIV) == ADC_CLOCK_DIV3) || \
                                            ((CLOCKDIV) == ADC_CLOCK_DIV4) || \
                                            ((CLOCKDIV) == ADC_CLOCK_DIV5) || \
                                            ((CLOCKDIV) == ADC_CLOCK_DIV6) || \
                                            ((CLOCKDIV) == ADC_CLOCK_DIV7) || \
                                            ((CLOCKDIV) == ADC_CLOCK_DIV8) || \
                                            ((CLOCKDIV) == ADC_CLOCK_DIV9) || \
                                            ((CLOCKDIV) == ADC_CLOCK_DIV10) || \
                                            ((CLOCKDIV) == ADC_CLOCK_DIV11) || \
                                            ((CLOCKDIV) == ADC_CLOCK_DIV12) || \
                                            ((CLOCKDIV) == ADC_CLOCK_DIV13) || \
                                            ((CLOCKDIV) == ADC_CLOCK_DIV14) || \
                                            ((CLOCKDIV) == ADC_CLOCK_DIV15) || \
                                            ((CLOCKDIV) == ADC_CLOCK_DIV16))

#define IS_ADC_ALL_SEQUENCE(SEQUENCE)      (((SEQUENCE) == ADC_SEQUENCE_SQ1) || \
                                            ((SEQUENCE) == ADC_SEQUENCE_SQ2) || \
                                            ((SEQUENCE) == ADC_SEQUENCE_SQ3) || \
                                            ((SEQUENCE) == ADC_SEQUENCE_SQ4) || \
                                            ((SEQUENCE) == ADC_SEQUENCE_SQ5) || \
                                            ((SEQUENCE) == ADC_SEQUENCE_SQ6) || \
                                            ((SEQUENCE) == ADC_SEQUENCE_SQ7) || \
                                            ((SEQUENCE) == ADC_SEQUENCE_SQ8) || \
                                            ((SEQUENCE) == ADC_SEQUENCE_SQ9) || \
                                            ((SEQUENCE) == ADC_SEQUENCE_SQ10) || \
                                            ((SEQUENCE) == ADC_SEQUENCE_SQ11) || \
                                            ((SEQUENCE) == ADC_SEQUENCE_SQ12) || \
                                            ((SEQUENCE) == ADC_SEQUENCE_SQ13) || \
                                            ((SEQUENCE) == ADC_SEQUENCE_SQ14) || \
                                            ((SEQUENCE) == ADC_SEQUENCE_SQ15) || \
                                            ((SEQUENCE) == ADC_SEQUENCE_SQ16))

#define IS_ADC_ALL_CHANNEL(CHANNEL)        (((CHANNEL) == ADC_CHANNEL_0) || \
                                            ((CHANNEL) == ADC_CHANNEL_1) || \
                                            ((CHANNEL) == ADC_CHANNEL_2) || \
                                            ((CHANNEL) == ADC_CHANNEL_3) || \
                                            ((CHANNEL) == ADC_CHANNEL_4) || \
                                            ((CHANNEL) == ADC_CHANNEL_5) || \
                                            ((CHANNEL) == ADC_CHANNEL_6) || \
                                            ((CHANNEL) == ADC_CHANNEL_7) || \
                                            ((CHANNEL) == ADC_CHANNEL_8) || \
                                            ((CHANNEL) == ADC_CHANNEL_9) || \
                                            ((CHANNEL) == ADC_CHANNEL_10) || \
                                            ((CHANNEL) == ADC_CHANNEL_11) || \
                                            ((CHANNEL) == ADC_CHANNEL_12) || \
                                            ((CHANNEL) == ADC_CHANNEL_13) || \
                                            ((CHANNEL) == ADC_CHANNEL_14) || \
                                            ((CHANNEL) == ADC_CHANNEL_15) || \
                                            ((CHANNEL) == ADC_CHANNEL_TEMP) || \
                                            ((CHANNEL) == ADC_CHANNEL_VBAT) || \
                                            ((CHANNEL) == ADC_CHANNEL_VBGR) || \
                                            ((CHANNEL) == ADC_CHANNEL_EXT2) || \
                                            ((CHANNEL) == ADC_CHANNEL_EXT3))

#define IS_ADC_ALL_CHANNELEN(CHANNELEN)    ((CHANNELEN) <= 0x1FFFFF)

#define IS_ADC_ALL_SMPCLOCK(SMPCLOCK)      (((SMPCLOCK) == ADC_SMP_CLOCK_3) || \
                                            ((SMPCLOCK) == ADC_SMP_CLOCK_5) || \
                                            ((SMPCLOCK) == ADC_SMP_CLOCK_7) || \
                                            ((SMPCLOCK) == ADC_SMP_CLOCK_10) || \
                                            ((SMPCLOCK) == ADC_SMP_CLOCK_13) || \
                                            ((SMPCLOCK) == ADC_SMP_CLOCK_16) || \
                                            ((SMPCLOCK) == ADC_SMP_CLOCK_20) || \
                                            ((SMPCLOCK) == ADC_SMP_CLOCK_30) || \
                                            ((SMPCLOCK) == ADC_SMP_CLOCK_60) || \
                                            ((SMPCLOCK) == ADC_SMP_CLOCK_80) || \
                                            ((SMPCLOCK) == ADC_SMP_CLOCK_100) || \
                                            ((SMPCLOCK) == ADC_SMP_CLOCK_120) || \
                                            ((SMPCLOCK) == ADC_SMP_CLOCK_160) || \
                                            ((SMPCLOCK) == ADC_SMP_CLOCK_320) || \
                                            ((SMPCLOCK) == ADC_SMP_CLOCK_480) || \
                                            ((SMPCLOCK) == ADC_SMP_CLOCK_640))

#define IS_ADC_ALL_TRIG(_TRIG)             (((_TRIG) == ADC_SOFTWARE_START) || \
                                            ((_TRIG) == ADC_EXTERNAL_TIG1) || \
                                            ((_TRIG) == ADC_EXTERNAL_TIG2) || \
                                            ((_TRIG) == ADC_EXTERNAL_TIG3) || \
                                            ((_TRIG) == ADC_EXTERNAL_TIG4) || \
                                            ((_TRIG) == ADC_EXTERNAL_TIG5) || \
                                            ((_TRIG) == ADC_EXTERNAL_TIG6) || \
                                            ((_TRIG) == ADC_EXTERNAL_TIG7))

#define IS_ADC_EVENT_TYPE(_EVENT)          (((_EVENT) == ADC_SR_AWD) || \
                                            ((_EVENT) == ADC_SR_OVERF) || \
                                            ((_EVENT) == ADC_SR_EOG) || \
                                            ((_EVENT) == ADC_SR_JEOC) || \
                                            ((_EVENT) == ADC_SR_EOC))

/* Function : HAL_ADC_IRQHandler */
void HAL_ADC_IRQHandler(ADC_HandleTypeDef *hadc);
void HAL_ADC_MspInit(ADC_HandleTypeDef* hadc);
void HAL_ADC_MspDeInit(ADC_HandleTypeDef* hadc);
HAL_StatusTypeDef HAL_ADC_Init(ADC_HandleTypeDef* hadc);
HAL_StatusTypeDef HAL_ADC_DeInit(ADC_HandleTypeDef* hadc);
HAL_StatusTypeDef HAL_ADC_ConfigChannel(ADC_HandleTypeDef* hadc, ADC_ChannelConfTypeDef* sConfig);
HAL_StatusTypeDef HAL_ADC_AnalogWDGConfig(ADC_HandleTypeDef* hadc, ADC_AnalogWDGConfTypeDef* AnalogWDGConfig);
HAL_StatusTypeDef HAL_ADC_Start(ADC_HandleTypeDef* hadc);
HAL_StatusTypeDef HAL_ADC_Stop(ADC_HandleTypeDef* hadc);
HAL_StatusTypeDef HAL_ADC_Start_IT(ADC_HandleTypeDef* hadc);
HAL_StatusTypeDef HAL_ADC_Stop_IT(ADC_HandleTypeDef* hadc);
HAL_StatusTypeDef HAL_ADC_Start_DMA(ADC_HandleTypeDef* hadc, uint32_t* pData, uint32_t Length);
HAL_StatusTypeDef HAL_ADC_Stop_DMA(ADC_HandleTypeDef* hadc);
uint32_t HAL_ADC_GetValue(ADC_HandleTypeDef *hadc);
HAL_StatusTypeDef HAL_ADC_PollForEvent(ADC_HandleTypeDef *hadc, uint32_t EventType, uint32_t Timeout);
HAL_StatusTypeDef HAL_ADC_InjectedStart_IT(ADC_HandleTypeDef* hadc);
HAL_StatusTypeDef HAL_ADC_InjectedStop_IT(ADC_HandleTypeDef* hadc);
uint32_t HAL_ADC_InjectedGetValue(ADC_HandleTypeDef *hadc);
HAL_StatusTypeDef HAL_ADC_Polling(ADC_HandleTypeDef* hadc, uint32_t* pData, uint32_t Length, uint32_t Timeout);

#endif





