/**
  ******************************************************************************
  * @file    stm32h7xx_hal_adc_ex.h
  * @author  MCD Application Team
  * @version V1.2.0
  * @date   29-December-2017
  * @brief   Header file of ADC HAL extended module.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2017 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32H7xx_ADC_EX_H
#define __STM32H7xx_ADC_EX_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal_def.h"

/** @addtogroup STM32H7xx_HAL_Driver
  * @{
  */

/** @addtogroup ADCEx
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup ADCEx_Exported_Types ADC Extended Exported Types
  * @{
  */

/**
  * @brief  ADC group injected contexts queue configuration
  */
typedef struct
{
  uint32_t ContextQueue;                 /*!< Injected channel configuration context: build-up over each
                                              HAL_ADCEx_InjectedConfigChannel() call to finally initialize
                                              JSQR register at HAL_ADCEx_InjectedConfigChannel() last call */

  uint32_t ChannelCount;                 /*!< Number of channels in the injected sequence */
}ADC_InjectionConfigTypeDef;

/**
  * @brief  ADC handle Structure definition
  */
typedef struct
{
  ADC_TypeDef                   *Instance;              /*!< Register base address */

  ADC_InitTypeDef               Init;                   /*!< ADC initialization parameters and regular conversions setting */

  DMA_HandleTypeDef             *DMA_Handle;            /*!< Pointer DMA Handler */

  HAL_LockTypeDef               Lock;                   /*!< ADC locking object */

  __IO uint32_t                 State;                  /*!< ADC communication state (bit-map of ADC states) */

  __IO uint32_t                 ErrorCode;              /*!< ADC Error code */

  ADC_InjectionConfigTypeDef    InjectionConfig ;       /*!< ADC injected channel configuration build-up structure */
}ADC_HandleTypeDef;

/**
  * @brief  ADC Injected Conversion Oversampling structure definition
  */
typedef struct
{
  uint32_t Ratio;                         /*!< Configures the oversampling ratio.
                                               This parameter can be a value between 0 to 1023 */

  uint32_t RightBitShift;                 /*!< Configures the division coefficient for the Oversampler.
                                               This parameter can be a value of @ref ADCEx_Right_Bit_Shift */
}ADC_InjOversamplingTypeDef;

/**
  * @brief  Structure definition of ADC channel for regular group
  * @note   The setting of these parameters by function HAL_ADC_ConfigChannel() is conditioned to ADC state.
  *         ADC state can be either:
  *          - For all parameters: ADC disabled (this is the only possible ADC state to modify parameter 'SingleDiff')
  *          - For all except parameters 'SamplingTime', 'Offset', 'OffsetNumber': ADC enabled without conversion on going on regular group.
  *          - For parameters 'SamplingTime', 'Offset', 'OffsetNumber': ADC enabled without conversion on going on regular and injected groups.
  *         If ADC is not in the appropriate state to modify some parameters, these parameters setting is bypassed
  *         without error reporting (as it can be the expected behavior in case of intended action to update another parameter
  *        (which fulfills the ADC state condition) on the fly).
  */
typedef struct
{
  uint32_t Channel;                /*!< Specify the channel to configure into ADC regular group.
                                        This parameter can be a value of @ref ADC_channels
                                        Note: Depending on devices and ADC instances, some channels may not be available on device package pins. Refer to device DataSheet for channels availability. */

  uint32_t Rank;                   /*!< Specify the rank in the regular group sequencer.
                                        This parameter can be a value of @ref ADC_regular_rank
                                        Note: to disable a channel or change order of conversion sequencer, rank containing a previous channel setting can be overwritten by
                                        the new channel setting (or parameter number of conversions adjusted) */

  uint32_t SamplingTime;           /*!< Sampling time value to be set for the selected channel.
                                        Unit: ADC clock cycles
                                        Conversion time is the addition of sampling time and processing time
                                        This parameter can be a value of @ref ADC_sampling_times
                                        Caution: This parameter applies to a channel that can be used into regular and/or injected group.
                                                 It overwrites the last setting.
                                        Note: In case of usage of internal measurement channels (VrefInt/Vbat/TempSensor),
                                              sampling time constraints must be respected (sampling time can be adjusted in function of ADC clock frequency and sampling time setting)
                                              Refer to device DataSheet for timings values. */

  uint32_t SingleDiff;             /*!< Select single-ended or differential input.
                                        In differential mode: Differential measurement is carried out between the selected channel 'i' (positive input) and channel 'i+1' (negative input).
                                                              Only channel 'i' has to be configured, channel 'i+1' is configured automatically.
                                        This parameter must be a value of @ref ADCEx_SingleDifferential
                                       Caution: This parameter applies to a channel that can be used in a regular and/or injected group.
                                                 It overwrites the last setting.
                                        Note: Refer to Reference Manual to ensure the selected channel is available in differential mode.
                                        Note: When configuring a channel 'i' in differential mode, the channel 'i+1' is not usable separately.
                                        Note: This parameter must be modified when ADC is disabled (before ADC start conversion or after ADC stop conversion).
                                              If ADC is enabled, this parameter setting is bypassed without error reporting (as it can be the expected behavior in case
                                        of another parameter update on the fly) */

  uint32_t OffsetNumber;           /*!< Select the offset number
                                        This parameter can be a value of @ref ADCEx_OffsetNumber
                                        Caution: Only one offset is allowed per channel. This parameter overwrites the last setting. */

  uint32_t Offset;                 /*!< Define the offset to be subtracted from the raw converted data.
                                        Offset value must be a positive number.
                                        Depending of ADC resolution selected (16, 14, 12, 10 or 8 bits), this parameter must be a number between Min_Data = 0x0000 and Max_Data = 0xFFFF,
                                        0x3FFF, 0xFFF, 0x3FF or 0xFF respectively.
                                        Note: This parameter must be modified when no conversion is on going on both regular and injected groups (ADC disabled, or ADC enabled
                                        without continuous mode or external trigger that could launch a conversion). */

  FunctionalState OffsetRightShift;   /*!< Define the Right-shift data after Offset correction.
                                        This parameter is applied only for 16-bit or 8-bit resolution.
                                        This parameter can be set to ENABLE or DISABLE.*/

  FunctionalState OffsetSignedSaturation; /*!< Specify whether the Signed saturation feature is used or not.
                                             This parameter is applied only for 16-bit or 8-bit resolution.
                                             This parameter can be set to ENABLE or DISABLE. */
}ADC_ChannelConfTypeDef;

/**
  * @brief  Structure definition of ADC group injected and ADC channel affected to ADC group injected
  * @note   Parameters of this structure are shared within 2 scopes:
  *          - Scope channel: InjectedChannel, InjectedRank, InjectedSamplingTime , InjectedSingleDiff, InjectedOffsetNumber, InjectedOffset
  *          - Scope ADC group injected (affects all channels of injected group): InjectedNbrOfConversion, InjectedDiscontinuousConvMode,
  *            AutoInjectedConv, QueueInjectedContext, ExternalTrigInjecConv, ExternalTrigInjecConvEdge, InjecOversamplingMode, InjecOversampling.
  * @note   The setting of these parameters by function HAL_ADCEx_InjectedConfigChannel() is conditioned to ADC state.
  *         ADC state can be either:
  *          - For all parameters: ADC disabled (this is the only possible ADC state to modify parameter 'InjectedSingleDiff')
  *          - For parameters 'InjectedDiscontinuousConvMode', 'QueueInjectedContext', 'InjecOversampling': ADC enabled without conversion on going on injected group.
  *          - For parameters 'InjectedSamplingTime', 'InjectedOffset', 'InjectedOffsetNumber', 'AutoInjectedConv': ADC enabled without conversion on going on regular and injected groups.
  *          - For parameters 'InjectedChannel', 'InjectedRank', 'InjectedNbrOfConversion', 'ExternalTrigInjecConv', 'ExternalTrigInjecConvEdge': ADC enabled and while conversion on going
  *            on ADC groups regular and injected.
  *         If ADC is not in the appropriate state to modify some parameters, these parameters setting is bypassed
  *         without error reporting (as it can be the expected behavior in case of intended action to update another parameter (which fulfills the ADC state condition) on the fly).
  */
typedef struct
{
  uint32_t InjectedChannel;               /*!< Specifies the channel to configure into ADC group injected.
                                               This parameter can be a value of @ref ADC_channels
                                               Note: Depending on devices and ADC instances, some channels may not be available on device package pins. Refer to device datasheet for channels availability. */

  uint32_t InjectedRank;                  /*!< Specifies the rank in the ADC group injected sequencer.
                                               This parameter must be a value of @ref ADCEx_injected_rank.
                                               Note: to disable a channel or change order of conversion sequencer, rank containing a previous channel setting can be overwritten by
                                               the new channel setting (or parameter number of conversions adjusted) */

  uint32_t InjectedSamplingTime;          /*!< Sampling time value to be set for the selected channel.
                                               Unit: ADC clock cycles.
                                               Conversion time is the addition of sampling time and processing time
                                               This parameter can be a value of @ref ADC_sampling_times.
                                               Caution: This parameter applies to a channel that can be used in a regular and/or injected group.
                                                        It overwrites the last setting.
                                               Note: In case of usage of internal measurement channels (VrefInt/Vbat/TempSensor),
                                                     sampling time constraints must be respected (sampling time can be adjusted in function of ADC clock frequency and sampling time setting)
                                                     Refer to device datasheet for timings values. */

  uint32_t InjectedSingleDiff;            /*!< Selection of single-ended or differential input.
                                               In differential mode: Differential measurement is between the selected channel 'i' (positive input) and channel 'i+1' (negative input).
                                               Only channel 'i' has to be configured, channel 'i+1' is configured automatically.
                                               This parameter must be a value of @ref ADCEx_SingleDifferential.
                                               Caution: This parameter applies to a channel that can be used in a regular and/or injected group.
                                                        It overwrites the last setting.
                                               Note: Refer to Reference Manual to ensure the selected channel is available in differential mode.
                                               Note: When configuring a channel 'i' in differential mode, the channel 'i+1' is not usable separately.
                                               Note: This parameter must be modified when ADC is disabled (before ADC start conversion or after ADC stop conversion).
                                               If ADC is enabled, this parameter setting is bypassed without error reporting (as it can be the expected behavior in case
                                               of another parameter update on the fly) */

  uint32_t InjectedOffsetNumber;          /*!< Selects the offset number.
                                               This parameter can be a value of @ref ADCEx_OffsetNumber.
                                               Caution: Only one offset is allowed per channel. This parameter overwrites the last setting. */

  uint32_t InjectedOffset;                /*!< Defines the offset to be subtracted from the raw converted data.
                                               Offset value must be a positive number.
                                               Depending of ADC resolution selected (16, 14, 12, 10 or 8bits), this parameter must be a number
                                               between Min_Data = 0x0000 and Max_Data = 0xFFFF, 0x3FFF, 0xFFF, 0x3FF or 0xFF respectively.
                                               Note: This parameter must be modified when no conversion is on going on both regular and injected groups (ADC disabled, or ADC enabled
                                               without continuous mode or external trigger that could launch a conversion). */
  uint32_t InjectedOffsetRightShift;       /*!< Defines the Right-shift data after Offset correction.
                                                This parameter is applied only for 16-bit or 8-bit resolution.
                                                This parameter must be a value of @ref ADCEx_Right_Bit_Shift.*/
  FunctionalState InjectedOffsetSignedSaturation;      /*!< Specifies whether the Signed saturation feature is used or not.
                                               This parameter is applied only for 16-bit or 8-bit resolution.
                                               This parameter can be set to ENABLE or DISABLE. */
  uint32_t InjectedLeftBitShift;          /*!< Configures the left shifting applied to the final result with or without oversampling.
                                               This parameter can be a value of @ref ADCEx_Left_Bit_Shift */
  uint32_t InjectedNbrOfConversion;       /*!< Specifies the number of ranks that will be converted within the ADC group injected sequencer.
                                               To use the injected group sequencer and convert several ranks, parameter 'ScanConvMode' must be enabled.
                                               This parameter must be a number between Min_Data = 1 and Max_Data = 4.
                                               Caution: this setting impacts the entire injected group. Therefore, call of HAL_ADCEx_InjectedConfigChannel() to
                                                        configure a channel on injected group can impact the configuration of other channels previously set. */

  FunctionalState InjectedDiscontinuousConvMode; /*!< Specifies whether the conversions sequence of ADC group injected is performed in Complete-sequence/Discontinuous-sequence
                                               (main sequence subdivided in successive parts).
                                               Discontinuous mode is used only if sequencer is enabled (parameter 'ScanConvMode'). If sequencer is disabled, this parameter is discarded.
                                               Discontinuous mode can be enabled only if continuous mode is disabled.
                                               This parameter can be set to ENABLE or DISABLE.
                                               Note: This parameter must be modified when ADC is disabled (before ADC start conversion or after ADC stop conversion).
                                               Note: For injected group, discontinuous mode converts the sequence channel by channel (discontinuous length fixed to 1 rank).
                                               Caution: this setting impacts the entire injected group. Therefore, call of HAL_ADCEx_InjectedConfigChannel() to
                                                        configure a channel on injected group can impact the configuration of other channels previously set. */

  FunctionalState AutoInjectedConv;              /*!< Enables or disables the selected ADC group injected automatic conversion after regular one
                                               This parameter can be set to ENABLE or DISABLE.
                                               Note: To use Automatic injected conversion, discontinuous mode must be disabled ('DiscontinuousConvMode' and 'InjectedDiscontinuousConvMode' set to DISABLE)
                                               Note: To use Automatic injected conversion, injected group external triggers must be disabled ('ExternalTrigInjecConv' set to ADC_INJECTED_SOFTWARE_START)
                                               Note: In case of DMA used with regular group: if DMA configured in normal mode (single shot) JAUTO will be stopped upon DMA transfer complete.
                                                     To maintain JAUTO always enabled, DMA must be configured in circular mode.
                                               Caution: this setting impacts the entire injected group. Therefore, call of HAL_ADCEx_InjectedConfigChannel() to
                                                        configure a channel on injected group can impact the configuration of other channels previously set. */

  FunctionalState QueueInjectedContext;          /*!< Specifies whether the context queue feature is enabled.
                                               This parameter can be set to ENABLE or DISABLE.
                                               If context queue is enabled, injected sequencer&channels configurations are queued on up to 2 contexts. If a
                                               new injected context is set when queue is full, error is triggered by interruption and through function
                                               'HAL_ADCEx_InjectedQueueOverflowCallback'.
                                               Caution: This feature request that the sequence is fully configured before injected conversion start.
                                                        Therefore, configure channels with as many calls to HAL_ADCEx_InjectedConfigChannel() as the 'InjectedNbrOfConversion' parameter.
                                               Caution: this setting impacts the entire injected group. Therefore, call of HAL_ADCEx_InjectedConfigChannel() to
                                                        configure a channel on injected group can impact the configuration of other channels previously set.
                                               Note: This parameter must be modified when ADC is disabled (before ADC start conversion or after ADC stop conversion). */

  uint32_t ExternalTrigInjecConv;         /*!< Selects the external event used to trigger the conversion start of injected group.
                                               If set to ADC_INJECTED_SOFTWARE_START, external triggers are disabled and software trigger is used instead.
                                               This parameter can be a value of @ref ADCEx_Injected_External_Trigger_Source.
                                               Caution: this setting impacts the entire injected group. Therefore, call of HAL_ADCEx_InjectedConfigChannel() to
                                                        configure a channel on injected group can impact the configuration of other channels previously set. */

  uint32_t ExternalTrigInjecConvEdge;     /*!< Selects the external trigger edge of injected group.
                                               This parameter can be a value of @ref ADC_injected_external_trigger_edge.
                                               If trigger source is set to ADC_INJECTED_SOFTWARE_START, this parameter is discarded.
                                               Caution: this setting impacts the entire injected group. Therefore, call of HAL_ADCEx_InjectedConfigChannel() to
                                                        configure a channel on injected group can impact the configuration of other channels previously set. */

  FunctionalState InjecOversamplingMode;                 /*!< Specifies whether the oversampling feature is enabled or disabled.
                                                       This parameter can be set to ENABLE or DISABLE.
                                                       Note: This parameter can be modified only if there is no conversion is ongoing (both ADSTART and JADSTART cleared) */

  ADC_InjOversamplingTypeDef  InjecOversampling; /*!< Specifies the Oversampling parameters.
                                                      Caution: this setting overwrites the previous oversampling configuration if oversampling already enabled.
                                                      Note: This parameter can be modified only if there is no conversion is ongoing (both ADSTART and JADSTART cleared). */
}ADC_InjectionConfTypeDef;



/**
  * @brief  Structure definition of ADC MultiMode
  * @note   The setting of these parameters by function HAL_ADCEx_MultiModeConfigChannel() is conditioned by ADCs state (both Master and Slave ADCs).
  *         Both Master and Slave ADCs must be disabled.
  */
typedef struct
{
  uint32_t Mode;              /*!< Configures the ADC to operate in independent or MultiMode.
                                   This parameter can be a value of @ref ADCEx_Common_mode */
  uint32_t DualModeData;      /*!< Configures the Dual ADC Mode Data Format:
                                   This parameter can be a value of @ref ADCEx_Dual_Mode_Data_Format */
  uint32_t TwoSamplingDelay;  /*!< Configures the Delay between 2 sampling phases.
                                   This parameter can be a value of @ref ADCEx_delay_between_2_sampling_phases
                                   Delay range depends on selected resolution:
                                    from 1 to 9 clock cycles for 16 bits,
                                    from 1 to 9 clock cycles for 14 bits
                                    from 1 to 8 clock cycles for 12 bits
                                    from 1 to 6 clock cycles for 10 bits
                                    from 1 to 6 clock cycles for 8 bits     */
}ADC_MultiModeTypeDef;


/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup ADCEx_Exported_Constants ADC Extended Exported Constants
  * @{
  */

/** @defgroup ADCEx_Injected_External_Trigger_Source ADC Extended External Trigger Source for Injected Group
  * @{
  */
#define ADC_EXTERNALTRIGINJEC_T1_TRGO       ((uint32_t)0x00000000)                                                                             /*!< Event 0 triggers injected group conversion start  */
#define ADC_EXTERNALTRIGINJEC_T1_CC4        ((uint32_t)ADC_JSQR_JEXTSEL_0)                                                                     /*!< Event 1 triggers injected group conversion start  */
#define ADC_EXTERNALTRIGINJEC_T2_TRGO       ((uint32_t)ADC_JSQR_JEXTSEL_1)                                                                     /*!< Event 2 triggers injected group conversion start  */
#define ADC_EXTERNALTRIGINJEC_T2_CC1        ((uint32_t)(ADC_JSQR_JEXTSEL_1 | ADC_JSQR_JEXTSEL_0))                                              /*!< Event 3 triggers injected group conversion start  */
#define ADC_EXTERNALTRIGINJEC_T3_CC4        ((uint32_t)ADC_JSQR_JEXTSEL_2)                                                                     /*!< Event 4 triggers injected group conversion start  */
#define ADC_EXTERNALTRIGINJEC_T4_TRGO       ((uint32_t)(ADC_JSQR_JEXTSEL_2 | ADC_JSQR_JEXTSEL_0))                                              /*!< Event 5 triggers injected group conversion start  */
#define ADC_EXTERNALTRIGINJEC_EXT_IT15      ((uint32_t)(ADC_JSQR_JEXTSEL_2 | ADC_JSQR_JEXTSEL_1))                                              /*!< Event 6 triggers injected group conversion start  */
#define ADC_EXTERNALTRIGINJEC_T8_CC4        ((uint32_t)(ADC_JSQR_JEXTSEL_2 | ADC_JSQR_JEXTSEL_1 | ADC_JSQR_JEXTSEL_0))                         /*!< Event 7 triggers injected group conversion start  */
#define ADC_EXTERNALTRIGINJEC_T1_TRGO2      ((uint32_t)ADC_JSQR_JEXTSEL_3)                                                                     /*!< Event 8 triggers injected group conversion start  */
#define ADC_EXTERNALTRIGINJEC_T8_TRGO       ((uint32_t)(ADC_JSQR_JEXTSEL_3 | ADC_JSQR_JEXTSEL_0))                                              /*!< Event 9 triggers injected group conversion start  */
#define ADC_EXTERNALTRIGINJEC_T8_TRGO2      ((uint32_t)(ADC_JSQR_JEXTSEL_3 | ADC_JSQR_JEXTSEL_1))                                              /*!< Event 10 triggers injected group conversion start  */
#define ADC_EXTERNALTRIGINJEC_T3_CC3        ((uint32_t)(ADC_JSQR_JEXTSEL_3 | ADC_JSQR_JEXTSEL_1 | ADC_JSQR_JEXTSEL_0))                         /*!< Event 11 triggers injected group conversion start  */
#define ADC_EXTERNALTRIGINJEC_T3_TRGO       ((uint32_t)(ADC_JSQR_JEXTSEL_3 | ADC_JSQR_JEXTSEL_2))                                              /*!< Event 12 triggers injected group conversion start  */
#define ADC_EXTERNALTRIGINJEC_T3_CC1        ((uint32_t)(ADC_JSQR_JEXTSEL_3 | ADC_JSQR_JEXTSEL_2 | ADC_JSQR_JEXTSEL_0))                         /*!< Event 13 triggers injected group conversion start  */
#define ADC_EXTERNALTRIGINJEC_T6_TRGO       ((uint32_t)(ADC_JSQR_JEXTSEL_3 | ADC_JSQR_JEXTSEL_2 | ADC_JSQR_JEXTSEL_1))                         /*!< Event 14 triggers injected group conversion start  */
#define ADC_EXTERNALTRIGINJEC_T15_TRGO      ((uint32_t)(ADC_JSQR_JEXTSEL_3 | ADC_JSQR_JEXTSEL_2 | ADC_JSQR_JEXTSEL_1 | ADC_JSQR_JEXTSEL_0))    /*!< Event 15 triggers injected group conversion start  */
#define ADC_EXTERNALTRIGINJEC_HR1_ADCTRG2   ((uint32_t)ADC_JSQR_JEXTSEL_4)                                                                     /*!< Event 16 triggers injected group conversion start  */
#define ADC_EXTERNALTRIGINJEC_HR1_ADCTRG4   ((uint32_t)(ADC_JSQR_JEXTSEL_4 | ADC_JSQR_JEXTSEL_0))                                              /*!< Event 17 triggers injected group conversion start  */
#define ADC_EXTERNALTRIGINJEC_LPTIM1_OUT    ((uint32_t)(ADC_JSQR_JEXTSEL_4 | ADC_JSQR_JEXTSEL_1))                                              /*!< Event 18 triggers injected group conversion start  */
#define ADC_EXTERNALTRIGINJEC_LPTIM2_OUT    ((uint32_t)(ADC_JSQR_JEXTSEL_4 | ADC_JSQR_JEXTSEL_1 | ADC_JSQR_JEXTSEL_0))                         /*!< Event 19 triggers injected group conversion start  */
#define ADC_EXTERNALTRIGINJEC_LPTIM3_OUT    ((uint32_t)(ADC_JSQR_JEXTSEL_4 | ADC_JSQR_JEXTSEL_2))                                              /*!< Event 20 triggers injected group conversion start  */

#define ADC_INJECTED_SOFTWARE_START      ((uint32_t)0x00000001)                                                                                /*!< Software triggers injected group conversion start */
/**
  * @}
  */

/** @defgroup ADC_injected_external_trigger_edge ADC group injected trigger edge (when external trigger is selected)
  * @{
  */
#define ADC_EXTERNALTRIGINJECCONV_EDGE_NONE           ((uint32_t)0x00000000)          /*!< Injected conversions hardware trigger detection disabled                             */
#define ADC_EXTERNALTRIGINJECCONV_EDGE_RISING         ((uint32_t)ADC_JSQR_JEXTEN_0)   /*!< Injected conversions hardware trigger detection on the rising edge                   */
#define ADC_EXTERNALTRIGINJECCONV_EDGE_FALLING        ((uint32_t)ADC_JSQR_JEXTEN_1)   /*!< Injected conversions hardware trigger detection on the falling edge                  */
#define ADC_EXTERNALTRIGINJECCONV_EDGE_RISINGFALLING  ((uint32_t)ADC_JSQR_JEXTEN)     /*!< Injected conversions hardware trigger detection on both the rising and falling edges */
/**
  * @}
  */

/** @defgroup ADCEx_SingleDifferential ADC Extended Single-ended/Differential input mode
  * @{
  */
#define ADC_SINGLE_ENDED                ((uint32_t)0x00000000)       /*!< ADC channel set in single-ended input mode */
#define ADC_DIFFERENTIAL_ENDED          ((uint32_t)ADC_CR_ADCALDIF)  /*!< ADC channel set in differential mode       */
/**
  * @}
  */

/** @defgroup ADCEx_OffsetNumber ADC Extended Offset Number
  * @{
  */
#define ADC_OFFSET_NONE               ((uint32_t)0x00)     /*!< No offset correction                           */
#define ADC_OFFSET_1                  ((uint32_t)0x01)     /*!< Offset correction to apply to a first channel  */
#define ADC_OFFSET_2                  ((uint32_t)0x02)     /*!< Offset correction to apply to a second channel */
#define ADC_OFFSET_3                  ((uint32_t)0x03)     /*!< Offset correction to apply to a third channel  */
#define ADC_OFFSET_4                  ((uint32_t)0x04)     /*!< Offset correction to apply to a fourth channel */
/**
  * @}
  */

/** @defgroup ADCEx_injected_rank ADC Extended Injected Channel Rank
  * @{
  */
#define ADC_INJECTED_RANK_1    ((uint32_t)0x00000001)      /*!< ADC injected conversion rank 1 */
#define ADC_INJECTED_RANK_2    ((uint32_t)0x00000002)      /*!< ADC injected conversion rank 2 */
#define ADC_INJECTED_RANK_3    ((uint32_t)0x00000003)      /*!< ADC injected conversion rank 3 */
#define ADC_INJECTED_RANK_4    ((uint32_t)0x00000004)      /*!< ADC injected conversion rank 4 */
/**
  * @}
  */

/** @defgroup ADCEx_Common_mode ADC Extended multimode dual mode
  * @{
  */
#define ADC_MODE_INDEPENDENT                  ((uint32_t)(0x00000000))                                       /*!< Independent ADC conversions mode                           */
#define ADC_DUALMODE_REGSIMULT_INJECSIMULT    ((uint32_t)(ADC_CCR_DUAL_0))                                   /*!< Combined regular simultaneous + injected simultaneous mode */
#define ADC_DUALMODE_REGSIMULT_ALTERTRIG      ((uint32_t)(ADC_CCR_DUAL_1))                                   /*!< Combined regular simultaneous + alternate trigger mode     */
#define ADC_DUALMODE_REGINTERL_INJECSIMULT    ((uint32_t)(ADC_CCR_DUAL_1 | ADC_CCR_DUAL_0))                  /*!< Combined Interleaved mode + injected simultaneous mode     */
#define ADC_DUALMODE_INJECSIMULT              ((uint32_t)(ADC_CCR_DUAL_2 | ADC_CCR_DUAL_0))                  /*!< Injected simultaneous mode only                            */
#define ADC_DUALMODE_REGSIMULT                ((uint32_t)(ADC_CCR_DUAL_2 | ADC_CCR_DUAL_1))                  /*!< Regular simultaneous mode only                             */
#define ADC_DUALMODE_INTERL                   ((uint32_t)(ADC_CCR_DUAL_2 | ADC_CCR_DUAL_1 | ADC_CCR_DUAL_0)) /*!< Interleaved mode only                                      */
#define ADC_DUALMODE_ALTERTRIG                ((uint32_t)(ADC_CCR_DUAL_3 | ADC_CCR_DUAL_0))                  /*!< Alternate trigger mode only                                */
/**
  * @}
  */


/** @defgroup ADCEx_Dual_Mode_Data_Format ADC Extended Dual Mode Data Formatting
  * @{
  */
#define ADC_DUALMODEDATAFORMAT_DISABLED      ((uint32_t)0x00000000)                        /*!< Dual ADC mode without data packing: ADCx_CDR and ADCx_CDR2 registers not used */
#define ADC_DUALMODEDATAFORMAT_32_10_BITS    ((uint32_t)ADC_CCR_DAMDF_1)                    /*!< Data formatting mode for 32 down to 10-bit resolution */
#define ADC_DUALMODEDATAFORMAT_8_BITS        ((uint32_t)(ADC_CCR_DAMDF_0 |ADC_CCR_DAMDF_1)) /*!< Data formatting mode for 8-bit resolution */
/**
  * @}
  */

/** @defgroup ADCEx_delay_between_2_sampling_phases ADC Extended delay between 2 sampling phases
  * @{
  */
#define ADC_TWOSAMPLINGDELAY_1CYCLE     ((uint32_t)(0x00000000))                                          /*!< 1 ADC clock cycle delay                                          */
#define ADC_TWOSAMPLINGDELAY_2CYCLES    ((uint32_t)(ADC_CCR_DELAY_0))                                     /*!< 2 ADC clock cycles delay                                         */
#define ADC_TWOSAMPLINGDELAY_3CYCLES    ((uint32_t)(ADC_CCR_DELAY_1))                                     /*!< 3 ADC clock cycles delay                                         */
#define ADC_TWOSAMPLINGDELAY_4CYCLES    ((uint32_t)(ADC_CCR_DELAY_1 | ADC_CCR_DELAY_0))                   /*!< 4 ADC clock cycles delay (lower for less then 10-bit resolution) */
#define ADC_TWOSAMPLINGDELAY_5CYCLES    ((uint32_t)(ADC_CCR_DELAY_2))                                     /*!< 5 ADC clock cycles delay (lower for less then 12-bit resolution) */
#define ADC_TWOSAMPLINGDELAY_6CYCLES    ((uint32_t)(ADC_CCR_DELAY_2 | ADC_CCR_DELAY_0))                   /*!< 6 ADC clock cycles delay (lower for less then 14-bit resolution) */
#define ADC_TWOSAMPLINGDELAY_7CYCLES    ((uint32_t)(ADC_CCR_DELAY_2 | ADC_CCR_DELAY_1))                   /*!< 7 ADC clock cycles delay (lower for less then 16-bit resolution) */
#define ADC_TWOSAMPLINGDELAY_8CYCLES    ((uint32_t)(ADC_CCR_DELAY_2 | ADC_CCR_DELAY_1 | ADC_CCR_DELAY_0)) /*!< 8 ADC clock cycles delay (lower for less then 16-bit resolution) */
#define ADC_TWOSAMPLINGDELAY_9CYCLES    ((uint32_t)(ADC_CCR_DELAY_3))                                     /*!< 9 ADC clock cycles delay (lower for less then 16-bit resolution) */
/**
  * @}
  */

/** @defgroup ADCEx_analog_watchdog_number ADC Extended Analog Watchdog Selection
  * @{
  */
#define ADC_ANALOGWATCHDOG_1                    ((uint32_t)0x00000001)   /*!< Analog watchdog 1 selection */
#define ADC_ANALOGWATCHDOG_2                    ((uint32_t)0x00000002)   /*!< Analog watchdog 2 selection */
#define ADC_ANALOGWATCHDOG_3                    ((uint32_t)0x00000003)   /*!< Analog watchdog 3 selection */
/**
  * @}
  */

/** @defgroup ADCEx_analog_watchdog_mode ADC Extended Analog Watchdog Mode
  * @{
  */
#define ADC_ANALOGWATCHDOG_NONE                 ((uint32_t) 0x00000000)                                             /*!< No analog watchdog selected                                             */
#define ADC_ANALOGWATCHDOG_SINGLE_REG           ((uint32_t)(ADC_CFGR_AWD1SGL | ADC_CFGR_AWD1EN))                    /*!< Analog watchdog applied to a regular group single channel               */
#define ADC_ANALOGWATCHDOG_SINGLE_INJEC         ((uint32_t)(ADC_CFGR_AWD1SGL | ADC_CFGR_JAWD1EN))                   /*!< Analog watchdog applied to an injected group single channel             */
#define ADC_ANALOGWATCHDOG_SINGLE_REGINJEC      ((uint32_t)(ADC_CFGR_AWD1SGL | ADC_CFGR_AWD1EN | ADC_CFGR_JAWD1EN)) /*!< Analog watchdog applied to a regular and injected groups single channel */
#define ADC_ANALOGWATCHDOG_ALL_REG              ((uint32_t) ADC_CFGR_AWD1EN)                                        /*!< Analog watchdog applied to regular group all channels                   */
#define ADC_ANALOGWATCHDOG_ALL_INJEC            ((uint32_t) ADC_CFGR_JAWD1EN)                                       /*!< Analog watchdog applied to injected group all channels                  */
#define ADC_ANALOGWATCHDOG_ALL_REGINJEC         ((uint32_t)(ADC_CFGR_AWD1EN | ADC_CFGR_JAWD1EN))                    /*!< Analog watchdog applied to regular and injected groups all channels     */
/**
  * @}
  */

/** @defgroup ADCEx_conversion_group ADC Extended Conversion Group
  * @{
  */
#define ADC_REGULAR_GROUP             ((uint32_t)(ADC_FLAG_EOC | ADC_FLAG_EOS))                                 /*!< ADC regular group selection               */
#define ADC_INJECTED_GROUP            ((uint32_t)(ADC_FLAG_JEOC | ADC_FLAG_JEOS))                               /*!< ADC injected group selection              */
#define ADC_REGULAR_INJECTED_GROUP    ((uint32_t)(ADC_FLAG_EOC | ADC_FLAG_EOS | ADC_FLAG_JEOC | ADC_FLAG_JEOS)) /*!< ADC regular and injected groups selection */
/**
  * @}
  */

/** @defgroup ADCEx_Event_type ADC Extended Event Type
  * @{
  */
#define ADC_EOSMP_EVENT          ((uint32_t)ADC_FLAG_EOSMP) /*!< ADC End of Sampling event */
#define ADC_AWD1_EVENT           ((uint32_t)ADC_FLAG_AWD1)  /*!< ADC Analog watchdog 1 event (main analog watchdog, present on all STM32 series) */
#define ADC_AWD2_EVENT           ((uint32_t)ADC_FLAG_AWD2)  /*!< ADC Analog watchdog 2 event (additional analog watchdog, not present on all STM32 series) */
#define ADC_AWD3_EVENT           ((uint32_t)ADC_FLAG_AWD3)  /*!< ADC Analog watchdog 3 event (additional analog watchdog, not present on all STM32 series) */
#define ADC_OVR_EVENT            ((uint32_t)ADC_FLAG_OVR)   /*!< ADC overrun event */
#define ADC_JQOVF_EVENT          ((uint32_t)ADC_FLAG_JQOVF) /*!< ADC Injected Context Queue Overflow event */
/**
  * @}
  */
#define ADC_AWD_EVENT            ADC_AWD1_EVENT      /*!< ADC Analog watchdog 1 event: Naming for compatibility with other STM32 devices having only one analog watchdog */

/** @defgroup ADCEx_interrupts_definition ADC Extended Interrupts Definition
  * @{
  */
#define ADC_IT_RDY           ADC_IER_RDY        /*!< ADC Ready (ADRDY) interrupt source */
#define ADC_IT_EOSMP         ADC_IER_EOSMP      /*!< ADC End of Sampling interrupt source */
#define ADC_IT_EOC           ADC_IER_EOC        /*!< ADC End of Regular Conversion interrupt source */
#define ADC_IT_EOS           ADC_IER_EOS        /*!< ADC End of Regular sequence of Conversions interrupt source */
#define ADC_IT_OVR           ADC_IER_OVR        /*!< ADC overrun interrupt source */
#define ADC_IT_JEOC          ADC_IER_JEOC       /*!< ADC End of Injected Conversion interrupt source */
#define ADC_IT_JEOS          ADC_IER_JEOS       /*!< ADC End of Injected sequence of Conversions interrupt source */
#define ADC_IT_AWD1          ADC_IER_AWD1       /*!< ADC Analog watchdog 1 interrupt source (main analog watchdog) */
#define ADC_IT_AWD2          ADC_IER_AWD2       /*!< ADC Analog watchdog 2 interrupt source (additional analog watchdog) */
#define ADC_IT_AWD3          ADC_IER_AWD3       /*!< ADC Analog watchdog 3 interrupt source (additional analog watchdog) */
#define ADC_IT_JQOVF         ADC_IER_JQOVF      /*!< ADC Injected Context Queue Overflow interrupt source */

#define ADC_IT_AWD           ADC_IT_AWD1        /*!< ADC Analog watchdog 1 interrupt source: Naming for compatibility with other STM32 devices having only one analog watchdog */
/**
  * @}
  */

/** @defgroup ADCEx_flags_definition ADC Extended Flags Definition
  * @{
  */
#define ADC_FLAG_RDY           ADC_ISR_ADRD     /*!< ADC Ready (ADRDY) flag */
#define ADC_FLAG_EOSMP         ADC_ISR_EOSMP    /*!< ADC End of Sampling flag */
#define ADC_FLAG_EOC           ADC_ISR_EOC      /*!< ADC End of Regular Conversion flag */
#define ADC_FLAG_EOS           ADC_ISR_EOS      /*!< ADC End of Regular sequence of Conversions flag */
#define ADC_FLAG_OVR           ADC_ISR_OVR      /*!< ADC overrun flag */
#define ADC_FLAG_JEOC          ADC_ISR_JEOC     /*!< ADC End of Injected Conversion flag */
#define ADC_FLAG_JEOS          ADC_ISR_JEOS     /*!< ADC End of Injected sequence of Conversions flag */
#define ADC_FLAG_AWD1          ADC_ISR_AWD1     /*!< ADC Analog watchdog 1 flag (main analog watchdog) */
#define ADC_FLAG_AWD2          ADC_ISR_AWD2     /*!< ADC Analog watchdog 2 flag (additional analog watchdog) */
#define ADC_FLAG_AWD3          ADC_ISR_AWD3     /*!< ADC Analog watchdog 3 flag (additional analog watchdog) */
#define ADC_FLAG_JQOVF         ADC_ISR_JQOVF    /*!< ADC Injected Context Queue Overflow flag */

#define ADC_FLAG_AWD           ADC_FLAG_AWD1    /*!< ADC Analog watchdog 1 flag: Naming for compatibility with other STM32 devices having only one analog watchdog */

#define ADC_FLAG_ALL    (ADC_FLAG_RDY | ADC_FLAG_EOSMP | ADC_FLAG_EOC | ADC_FLAG_EOS |  \
                         ADC_FLAG_JEOC | ADC_FLAG_JEOS | ADC_FLAG_OVR | ADC_FLAG_AWD1 | \
                         ADC_FLAG_AWD2 | ADC_FLAG_AWD3 | ADC_FLAG_JQOVF)  /*!< ADC all flags */

/* Combination of all post-conversion flags bits: EOC/EOS, JEOC/JEOS, OVR, AWDx, JQOVF */
#define ADC_FLAG_POSTCONV_ALL (ADC_FLAG_EOC | ADC_FLAG_EOS  | ADC_FLAG_JEOC | ADC_FLAG_JEOS | \
                               ADC_FLAG_OVR | ADC_FLAG_AWD1 | ADC_FLAG_AWD2 | ADC_FLAG_AWD3 | \
                               ADC_FLAG_JQOVF) /*!< ADC post-conversion all flags */
/**
  * @}
  */


/** @defgroup ADCEx_Right_Bit_Shift   ADC Extended Oversampling Right Shift
  * @{
  */
#define ADC_RIGHTBITSHIFT_NONE  ((uint32_t)0x00000000)                                               /*!<  ADC No bit shift for oversampling */
#define ADC_RIGHTBITSHIFT_1     ((uint32_t)ADC_CFGR2_OVSS_0)                                         /*!<  ADC 1 bit shift for oversampling  */
#define ADC_RIGHTBITSHIFT_2     ((uint32_t)ADC_CFGR2_OVSS_1)                                         /*!<  ADC 2 bits shift for oversampling */
#define ADC_RIGHTBITSHIFT_3     ((uint32_t)(ADC_CFGR2_OVSS_1 | ADC_CFGR2_OVSS_0))                    /*!<  ADC 3 bits shift for oversampling */
#define ADC_RIGHTBITSHIFT_4     ((uint32_t)ADC_CFGR2_OVSS_2)                                         /*!<  ADC 4 bits shift for oversampling */
#define ADC_RIGHTBITSHIFT_5     ((uint32_t)(ADC_CFGR2_OVSS_2 | ADC_CFGR2_OVSS_0))                    /*!<  ADC 5 bits shift for oversampling */
#define ADC_RIGHTBITSHIFT_6     ((uint32_t)(ADC_CFGR2_OVSS_2 | ADC_CFGR2_OVSS_1))                    /*!<  ADC 6 bits shift for oversampling */
#define ADC_RIGHTBITSHIFT_7     ((uint32_t)(ADC_CFGR2_OVSS_2 | ADC_CFGR2_OVSS_1 | ADC_CFGR2_OVSS_0)) /*!<  ADC 7 bits shift for oversampling */
#define ADC_RIGHTBITSHIFT_8     ((uint32_t)ADC_CFGR2_OVSS_3)                                         /*!<  ADC 8 bits shift for oversampling */
#define ADC_RIGHTBITSHIFT_9     ((uint32_t)(ADC_CFGR2_OVSS_3 | ADC_CFGR2_OVSS_0))                    /*!<  ADC 9 bits shift for oversampling */
#define ADC_RIGHTBITSHIFT_10    ((uint32_t)(ADC_CFGR2_OVSS_3 | ADC_CFGR2_OVSS_1))                    /*!<  ADC 10 bits shift for oversampling */
#define ADC_RIGHTBITSHIFT_11    ((uint32_t)(ADC_CFGR2_OVSS_3 | ADC_CFGR2_OVSS_1 | ADC_CFGR2_OVSS_0)) /*!<  ADC 11 bits shift for oversampling */
/**
  * @}
  */

/** @defgroup ADCEx_Left_Bit_Shift   ADC Extended Oversampling left Shift
  * @{
  */
#define ADC_LEFTBITSHIFT_NONE  ((uint32_t)0x00000000)                                                                           /*!<  ADC No bit shift */
#define ADC_LEFTBITSHIFT_1     ((uint32_t)ADC_CFGR2_LSHIFT_0)                                                                   /*!<  ADC 1 bit shift  */
#define ADC_LEFTBITSHIFT_2     ((uint32_t)ADC_CFGR2_LSHIFT_1)                                                                   /*!<  ADC 2 bits shift */
#define ADC_LEFTBITSHIFT_3     ((uint32_t)(ADC_CFGR2_LSHIFT_1 | ADC_CFGR2_LSHIFT_0))                                            /*!<  ADC 3 bits shift */
#define ADC_LEFTBITSHIFT_4     ((uint32_t)ADC_CFGR2_LSHIFT_2)                                                                   /*!<  ADC 4 bits shift */
#define ADC_LEFTBITSHIFT_5     ((uint32_t)(ADC_CFGR2_LSHIFT_2 | ADC_CFGR2_LSHIFT_0))                                            /*!<  ADC 5 bits shift */
#define ADC_LEFTBITSHIFT_6     ((uint32_t)(ADC_CFGR2_LSHIFT_2 | ADC_CFGR2_LSHIFT_1))                                            /*!<  ADC 6 bits shift */
#define ADC_LEFTBITSHIFT_7     ((uint32_t)(ADC_CFGR2_LSHIFT_2 | ADC_CFGR2_LSHIFT_1 | ADC_CFGR2_LSHIFT_0))                       /*!<  ADC 7 bits shift */
#define ADC_LEFTBITSHIFT_8     ((uint32_t)ADC_CFGR2_LSHIFT_3)                                                                   /*!<  ADC 8 bits shift */
#define ADC_LEFTBITSHIFT_9     ((uint32_t)(ADC_CFGR2_LSHIFT_3 | ADC_CFGR2_LSHIFT_0))                                            /*!<  ADC 9 bits shift */
#define ADC_LEFTBITSHIFT_10    ((uint32_t)(ADC_CFGR2_LSHIFT_3 | ADC_CFGR2_LSHIFT_1))                                            /*!<  ADC 10 bits shift */
#define ADC_LEFTBITSHIFT_11    ((uint32_t)(ADC_CFGR2_LSHIFT_3 | ADC_CFGR2_LSHIFT_1 | ADC_CFGR2_LSHIFT_0))                       /*!<  ADC 11 bits shift */
#define ADC_LEFTBITSHIFT_12    ((uint32_t)(ADC_CFGR2_LSHIFT_3 | ADC_CFGR2_LSHIFT_2))                                            /*!<  ADC 12 bits shift */
#define ADC_LEFTBITSHIFT_13    ((uint32_t)(ADC_CFGR2_LSHIFT_3 | ADC_CFGR2_LSHIFT_2 | ADC_CFGR2_LSHIFT_0))                       /*!<  ADC 13 bits shift */
#define ADC_LEFTBITSHIFT_14    ((uint32_t)(ADC_CFGR2_LSHIFT_3 | ADC_CFGR2_LSHIFT_2 | ADC_CFGR2_LSHIFT_1))                       /*!<  ADC 14 bits shift */
#define ADC_LEFTBITSHIFT_15    ((uint32_t)(ADC_CFGR2_LSHIFT_3 | ADC_CFGR2_LSHIFT_2 | ADC_CFGR2_LSHIFT_1 | ADC_CFGR2_LSHIFT_0))  /*!<  ADC 15 bits shift */
/**
  * @}
  */

/** @defgroup ADCEx_Triggered_Oversampling_Mode   ADC Extended Triggered Regular Oversampling
  * @{
  */
#define ADC_TRIGGEREDMODE_SINGLE_TRIGGER      ((uint32_t)0x00000000)      /*!<  A single trigger for all channel oversampled conversions */
#define ADC_TRIGGEREDMODE_MULTI_TRIGGER       ((uint32_t)ADC_CFGR2_TROVS) /*!<  A trigger for each oversampled conversion                */
/**
  * @}
  */

/** @defgroup ADCEx_Regular_Oversampling_Mode   ADC Extended Regular Oversampling Continued or Resumed Mode
  * @{
  */
#define ADC_REGOVERSAMPLING_CONTINUED_MODE    ((uint32_t)0x00000000)      /*!<  Oversampling buffer maintained during injection sequence */
#define ADC_REGOVERSAMPLING_RESUMED_MODE      ((uint32_t)ADC_CFGR2_ROVSM) /*!<  Oversampling buffer zeroed during injection sequence     */
/**
  * @}
  */

/** @defgroup ADC_sampling_times ADC Sampling Times
  * @{
  */
#define ADC_SAMPLETIME_1CYCLE_5       ((uint32_t)0x00000000)                              /*!< Sampling time 1.5 ADC clock cycle    */
#define ADC_SAMPLETIME_2CYCLES_5      ((uint32_t)ADC_SMPR2_SMP10_0)                       /*!< Sampling time 2.5 ADC clock cycles   */
#define ADC_SAMPLETIME_8CYCLES_5      ((uint32_t)ADC_SMPR2_SMP10_1)                       /*!< Sampling time 8.5 ADC clock cycles  */
#define ADC_SAMPLETIME_16CYCLES_5     ((uint32_t)(ADC_SMPR2_SMP10_1 | ADC_SMPR2_SMP10_0)) /*!< Sampling time 16.5 ADC clock cycles  */
#define ADC_SAMPLETIME_32CYCLES_5     ((uint32_t)ADC_SMPR2_SMP10_2)                       /*!< Sampling time 32.5 ADC clock cycles  */
#define ADC_SAMPLETIME_64CYCLES_5     ((uint32_t)(ADC_SMPR2_SMP10_2 | ADC_SMPR2_SMP10_0)) /*!< Sampling time 64.5 ADC clock cycles  */
#define ADC_SAMPLETIME_387CYCLES_5    ((uint32_t)(ADC_SMPR2_SMP10_2 | ADC_SMPR2_SMP10_1)) /*!< Sampling time 387.5 ADC clock cycles */
#define ADC_SAMPLETIME_810CYCLES_5    ((uint32_t)ADC_SMPR2_SMP10)                         /*!< Sampling time 810.5 ADC clock cycles */
/**
  * @}
  */

/** @defgroup ADCEx_Calibration_Mode   ADC Extended Calibration mode offset mode or linear mode
  * @{
  */
#define ADC_CALIB_OFFSET                 ((uint32_t)0x00000000)
#define ADC_CALIB_OFFSET_LINEARITY         (ADC_CR_ADCALLIN)
/**
  * @}
  */

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/

/** @defgroup ADCEx_Private_Macro_internal_HAL_driver ADC Extended Private Macros
  * @{
  */

/**
  * @brief Verify the length of scheduled injected conversions group.
  * @param LENGTH : number of programmed conversions.   
  * @retval SET (LENGTH is within the maximum number of possible programmable injected conversions) or RESET (LENGTH is null or too large)
  */
#define IS_ADC_INJECTED_NB_CONV(LENGTH) (((LENGTH) >= ((uint32_t)1)) && ((LENGTH) <= ((uint32_t)4)))

/**
  * @brief Calibration factor length verification (7 bits maximum)
  * @param _Calibration_Factor_: Calibration factor value
  * @retval None
  */
#define IS_ADC_CALFACT(_Calibration_Factor_) ((_Calibration_Factor_) <= ((uint32_t)0x7F))

/**
  * @brief Verify the ADC channel setting.
  * @param __CHANNEL__: programmed ADC channel.
  * @retval SET (__CHANNEL__ is valid) or RESET (__CHANNEL__ is invalid)
  */
#define IS_ADC_CHANNEL(__CHANNEL__) (((__CHANNEL__) == ADC_CHANNEL_0)       || \
                                 ((__CHANNEL__) == ADC_CHANNEL_1)           || \
                                 ((__CHANNEL__) == ADC_CHANNEL_2)           || \
                                 ((__CHANNEL__) == ADC_CHANNEL_3)           || \
                                 ((__CHANNEL__) == ADC_CHANNEL_4)           || \
                                 ((__CHANNEL__) == ADC_CHANNEL_5)           || \
                                 ((__CHANNEL__) == ADC_CHANNEL_6)           || \
                                 ((__CHANNEL__) == ADC_CHANNEL_7)           || \
                                 ((__CHANNEL__) == ADC_CHANNEL_8)           || \
                                 ((__CHANNEL__) == ADC_CHANNEL_9)           || \
                                 ((__CHANNEL__) == ADC_CHANNEL_10)          || \
                                 ((__CHANNEL__) == ADC_CHANNEL_11)          || \
                                 ((__CHANNEL__) == ADC_CHANNEL_12)          || \
                                 ((__CHANNEL__) == ADC_CHANNEL_13)          || \
                                 ((__CHANNEL__) == ADC_CHANNEL_14)          || \
                                 ((__CHANNEL__) == ADC_CHANNEL_15)          || \
                                 ((__CHANNEL__) == ADC_CHANNEL_16)          || \
                                 ((__CHANNEL__) == ADC_CHANNEL_17)          || \
                                 ((__CHANNEL__) == ADC_CHANNEL_18)          || \
                                 ((__CHANNEL__) == ADC_CHANNEL_19)          || \
                                 ((__CHANNEL__) == ADC_CHANNEL_TEMPSENSOR)  || \
                                 ((__CHANNEL__) == ADC_CHANNEL_VBAT_DIV4)   || \
                                 ((__CHANNEL__) == ADC_CHANNEL_DAC1CH1_ADC2)|| \
                                 ((__CHANNEL__) == ADC_CHANNEL_DAC1CH2_ADC2)|| \
                                 ((__CHANNEL__) == ADC_CHANNEL_VREFINT)       )

/**
  * @brief Verify the ADC channel setting in differential mode for ADC1.
  * @param __CHANNEL__: programmed ADC channel.
  * @retval SET (__CHANNEL__ is valid) or RESET (__CHANNEL__ is invalid)
  */
#define IS_ADC1_DIFF_CHANNEL(__CHANNEL__) (((__CHANNEL__) == ADC_CHANNEL_1)|| \
                                      ((__CHANNEL__) == ADC_CHANNEL_2)      ||\
                                      ((__CHANNEL__) == ADC_CHANNEL_3)      ||\
                                      ((__CHANNEL__) == ADC_CHANNEL_4)      ||\
                                      ((__CHANNEL__) == ADC_CHANNEL_5)      ||\
                                      ((__CHANNEL__) == ADC_CHANNEL_10)     ||\
                                      ((__CHANNEL__) == ADC_CHANNEL_11)     ||\
                                      ((__CHANNEL__) == ADC_CHANNEL_12)     ||\
                                      ((__CHANNEL__) == ADC_CHANNEL_16)     ||\
                                      ((__CHANNEL__) == ADC_CHANNEL_18)      )

/**
  * @brief Verify the ADC channel setting in differential mode for ADC2.
  * @param __CHANNEL__: programmed ADC channel.
  * @retval SET (__CHANNEL__ is valid) or RESET (__CHANNEL__ is invalid)
  */
#define IS_ADC2_DIFF_CHANNEL(__CHANNEL__) (((__CHANNEL__) == ADC_CHANNEL_1)|| \
                                      ((__CHANNEL__) == ADC_CHANNEL_2)      || \
                                      ((__CHANNEL__) == ADC_CHANNEL_3)      || \
                                      ((__CHANNEL__) == ADC_CHANNEL_4)      || \
                                      ((__CHANNEL__) == ADC_CHANNEL_5)      || \
                                      ((__CHANNEL__) == ADC_CHANNEL_10)     || \
                                      ((__CHANNEL__) == ADC_CHANNEL_11)     || \
                                      ((__CHANNEL__) == ADC_CHANNEL_12)     || \
                                      ((__CHANNEL__) == ADC_CHANNEL_18)      )

/**
  * @brief Verify the ADC channel setting in differential mode for ADC3.
  * @param __CHANNEL__: programmed ADC channel.
  * @retval SET (__CHANNEL__ is valid) or RESET (__CHANNEL__ is invalid)
  */
#define IS_ADC3_DIFF_CHANNEL(__CHANNEL__) (((__CHANNEL__) == ADC_CHANNEL_1) || \
                                      ((__CHANNEL__) == ADC_CHANNEL_2)      || \
                                      ((__CHANNEL__) == ADC_CHANNEL_3)      || \
                                      ((__CHANNEL__) == ADC_CHANNEL_4)      || \
                                      ((__CHANNEL__) == ADC_CHANNEL_5)      || \
                                      ((__CHANNEL__) == ADC_CHANNEL_10)     || \
                                      ((__CHANNEL__) == ADC_CHANNEL_11)     || \
                                      ((__CHANNEL__) == ADC_CHANNEL_13)     || \
                                      ((__CHANNEL__) == ADC_CHANNEL_14)     || \
                                      ((__CHANNEL__) == ADC_CHANNEL_15)       )

/**
  * @brief Test if conversion trigger of injected group is software start
  *        or external trigger.
  * @param __HANDLE__: ADC handle
  * @retval SET (software start) or RESET (external trigger)
  */
#define ADC_IS_SOFTWARE_START_INJECTED(__HANDLE__)                       \
       (((__HANDLE__)->Instance->JSQR & ADC_JSQR_JEXTEN) == RESET)

/**
  * @brief Check if no conversion on going on regular or injected groups
  * @param __HANDLE__: ADC handle
  * @retval SET (conversion is on going) or RESET (no conversion is on going)
  */
#define ADC_IS_CONVERSION_ONGOING_REGULAR_INJECTED(__HANDLE__)                    \
       (( (((__HANDLE__)->Instance->CR) & (ADC_CR_ADSTART | ADC_CR_JADSTART)) == RESET  \
        ) ? RESET : SET)

/**
  * @brief Check if no conversion on going on injected group
  * @param __HANDLE__: ADC handle
  * @retval SET (conversion is on going) or RESET (no conversion is on going)
  */
#define ADC_IS_CONVERSION_ONGOING_INJECTED(__HANDLE__)                   \
       (( (((__HANDLE__)->Instance->CR) & ADC_CR_JADSTART) == RESET            \
        ) ? RESET : SET)

/**
  * @brief Check whether or not ADC is independent
  * @param __HANDLE__: ADC handle
  * @retval SET (ADC is independent) or RESET (ADC is not)
  */
#define ADC_IS_INDEPENDENT(__HANDLE__)    \
  ( ( ( ((__HANDLE__)->Instance) == ADC3) \
    )?                                    \
     SET                                  \
     :                                    \
     RESET                                \
  )

/**
  * @brief Set the ADC's sample time for Channels numbers between 0 and 9.
  * @param __SAMPLETIME__: Sample time parameter.
  * @param __CHANNELNB__: Channel number.
  * @retval None
  */
#define ADC_SMPR1(__SAMPLETIME__, __CHANNELNB__) ((__SAMPLETIME__) << (POSITION_VAL(ADC_SMPR1_SMP1) * (__CHANNELNB__)))

/**
  * @brief Set the ADC's sample time for Channels numbers between 10 and 18.
  * @param __SAMPLETIME__: Sample time parameter.
  * @param __CHANNELNB__: Channel number.
  * @retval None
  */
#define ADC_SMPR2(__SAMPLETIME__, __CHANNELNB__) ((__SAMPLETIME__) << ((POSITION_VAL(ADC_SMPR2_SMP11) * ((__CHANNELNB__) - 10))))

/**
  * @brief Set the selected regular Channel rank for rank between 1 and 4.
  * @param __CHANNELNB__: Channel number.
  * @param __RANKNB__: Rank number.
  * @retval None
  */
#define ADC_SQR1_RK(__CHANNELNB__, __RANKNB__) ((__CHANNELNB__) << (POSITION_VAL(ADC_SQR1_SQ1) * (__RANKNB__)))

/**
  * @brief Set the selected regular Channel rank for rank between 5 and 9.
  * @param __CHANNELNB__: Channel number.
  * @param __RANKNB__: Rank number.
  * @retval None
  */
#define ADC_SQR2_RK(__CHANNELNB__, __RANKNB__) ((__CHANNELNB__) << (POSITION_VAL(ADC_SQR2_SQ6) * ((__RANKNB__) - 5)))

/**
  * @brief Set the selected regular Channel rank for rank between 10 and 14.
  * @param __CHANNELNB__: Channel number.
  * @param __RANKNB__: Rank number.
  * @retval None
  */
#define ADC_SQR3_RK(__CHANNELNB__, __RANKNB__) ((__CHANNELNB__) << (POSITION_VAL(ADC_SQR3_SQ11) * ((__RANKNB__) - 10)))

/**
  * @brief Set the selected regular Channel rank for rank between 15 and 16.
  * @param __CHANNELNB__: Channel number.
  * @param __RANKNB__: Rank number.
  * @retval None
  */
#define ADC_SQR4_RK(__CHANNELNB__, __RANKNB__) ((__CHANNELNB__) << (POSITION_VAL(ADC_SQR4_SQ16) * ((__RANKNB__) - 15)))

/**
  * @brief Set the selected injected Channel rank.
  * @param __CHANNELNB__: Channel number.
  * @param __RANKNB__: Rank number.
  * @retval None
  */
#define ADC_JSQR_RK(__CHANNELNB__, __RANKNB__) ((__CHANNELNB__) << ((POSITION_VAL(ADC_JSQR_JSQ1)-3) * (__RANKNB__) +3))

/**
  * @brief Set the Analog Watchdog 1 channel.
  * @param __CHANNEL__: channel to be monitored by Analog Watchdog 1.
  * @retval None
  */
#define ADC_CFGR_SET_AWD1CH(__CHANNEL__) ((__CHANNEL__) << POSITION_VAL(ADC_CFGR_AWD1CH))

/**
  * @brief Configure the channel number into Analog Watchdog 2 or 3.
  * @param __CHANNEL__: ADC Channel
  * @retval None
  */
#define ADC_CFGR_SET_AWD23CR(__CHANNEL__) (1U << (__CHANNEL__))

/**
  * @brief Enable ADC injected context queue
  * @param __INJECT_CONTEXT_QUEUE_MODE__: Injected context queue mode.
  * @retval None
  */
#define ADC_CFGR_INJECT_CONTEXT_QUEUE(__INJECT_CONTEXT_QUEUE_MODE__) ((uint32_t)(__INJECT_CONTEXT_QUEUE_MODE__) << POSITION_VAL(ADC_CFGR_JQM))

/**
  * @brief Enable ADC discontinuous conversion mode for injected group
  * @param __INJECT_DISCONTINUOUS_MODE__: Injected discontinuous mode.
  * @retval None
  */
#define ADC_CFGR_INJECT_DISCCONTINUOUS(__INJECT_DISCONTINUOUS_MODE__) ((__INJECT_DISCONTINUOUS_MODE__) <<  POSITION_VAL(ADC_CFGR_JDISCEN))

/**
  * @brief Enable ADC discontinuous conversion mode for regular group
  * @param __REG_DISCONTINUOUS_MODE__: Regular discontinuous mode.
  * @retval None
  */
#define ADC_CFGR_REG_DISCONTINUOUS(__REG_DISCONTINUOUS_MODE__) ((__REG_DISCONTINUOUS_MODE__) << POSITION_VAL(ADC_CFGR_DISCEN))

/**
  * @brief Configures the number of discontinuous conversions for regular group.
  * @param __NBR_DISCONTINUOUS_CONV__: Number of discontinuous conversions.
  * @retval None
  */
#define ADC_CFGR_DISCONTINUOUS_NUM(__NBR_DISCONTINUOUS_CONV__) (((__NBR_DISCONTINUOUS_CONV__) - 1) << POSITION_VAL(ADC_CFGR_DISCNUM))

/**
  * @brief Enable the ADC auto delay mode.
  * @param __AUTOWAIT__: Auto delay bit enable or disable.
  * @retval None
  */
#define ADC_CFGR_AUTOWAIT(__AUTOWAIT__) ((__AUTOWAIT__) << POSITION_VAL(ADC_CFGR_AUTDLY))

/**
  * @brief Enable ADC continuous conversion mode.
  * @param __CONTINUOUS_MODE__: Continuous mode.
  * @retval None
  */
#define ADC_CFGR_CONTINUOUS(__CONTINUOUS_MODE__) ((__CONTINUOUS_MODE__) << POSITION_VAL(ADC_CFGR_CONT))

/**
  * @brief Enable the ADC DMA continuous request.
  * @param __DMACONTREQ_MODE__: DMA continuous request mode.
  * @retval None
  */
#define ADC_CFGR_DMACONTREQ(__DMACONTREQ_MODE__) ((__DMACONTREQ_MODE__))

/**
  * @brief Configure the channel number into offset OFRx register
  * @param __CHANNEL__: ADC Channel
  * @retval None
  */
#define ADC_OFR_CHANNEL(__CHANNEL__) ((__CHANNEL__) << POSITION_VAL(ADC_OFR1_OFFSET1_CH))

/**
  * @brief Configure the channel number into differential mode selection register
  * @param __CHANNEL__: ADC Channel
  * @retval None
  */
#define ADC_DIFSEL_CHANNEL(__CHANNEL__) (1U << (__CHANNEL__))

/**
  * @brief Calibration factor in differential mode to be set into calibration register
  * @param __CALIBRATION_FACTOR__: Calibration factor value
  * @retval None
  */
#define ADC_CALFACT_DIFF_SET(__CALIBRATION_FACTOR__) (((__CALIBRATION_FACTOR__) & (ADC_CALFACT_CALFACT_D >> POSITION_VAL(ADC_CALFACT_CALFACT_D)) ) << POSITION_VAL(ADC_CALFACT_CALFACT_D))

/**
  * @brief Calibration factor in differential mode to be retrieved from calibration register
  * @param __CALIBRATION_FACTOR__: Calibration factor value
  * @retval None
  */
#define ADC_CALFACT_DIFF_GET(__CALIBRATION_FACTOR__) ((__CALIBRATION_FACTOR__) >> POSITION_VAL(ADC_CALFACT_CALFACT_D))

/**
  * @brief Configure the analog watchdog high threshold into registers TR1, TR2 or TR3.
  * @param __THRESHOLD__: Threshold value
  * @retval None
  */
#define ADC_TRX_HIGHTHRESHOLD(__THRESHOLD__) ((__THRESHOLD__) << 16)

/**
  * @brief Enable the ADC DMA continuous request for ADC multimode.
  * @param __DMACONTREQ_MODE__: DMA continuous request mode.
  * @retval None
  */
#define ADC_CCR_MULTI_DMACONTREQ(__DMACONTREQ_MODE__) ((__DMACONTREQ_MODE__) << POSITION_VAL(ADC_CCR_DMACFG))

/**
  * @brief Enable the ADC peripheral
  * @param __HANDLE__: ADC handle
  * @retval None
  */
#define ADC_ENABLE(__HANDLE__) ((__HANDLE__)->Instance->CR |= ADC_CR_ADEN)

/**
  * @brief Verification of hardware constraints before ADC can be enabled
  * @param __HANDLE__: ADC handle
  * @retval SET (ADC can be enabled) or RESET (ADC cannot be enabled)
  */
#define ADC_ENABLING_CONDITIONS(__HANDLE__)                             \
       (( ( ((__HANDLE__)->Instance->CR) &                                    \
            (ADC_CR_ADCAL | ADC_CR_JADSTP | ADC_CR_ADSTP | ADC_CR_JADSTART |  \
             ADC_CR_ADSTART | ADC_CR_ADDIS | ADC_CR_ADEN                    ) \
           ) == RESET                                                         \
        ) ? SET : RESET)

/**
  * @brief Disable the ADC peripheral
  * @param __HANDLE__: ADC handle
  * @retval None
  */
#define ADC_DISABLE(__HANDLE__)                                          \
  do{                                                                          \
         (__HANDLE__)->Instance->CR |= ADC_CR_ADDIS;                           \
          __HAL_ADC_CLEAR_FLAG((__HANDLE__), (ADC_FLAG_EOSMP | ADC_FLAG_RDY)); \
  } while(0)

/**
  * @brief Verification of hardware constraints before ADC can be disabled
  * @param __HANDLE__: ADC handle
  * @retval SET (ADC can be disabled) or RESET (ADC cannot be disabled)
  */
#define ADC_DISABLING_CONDITIONS(__HANDLE__)                             \
       (( ( ((__HANDLE__)->Instance->CR) &                                     \
            (ADC_CR_JADSTART | ADC_CR_ADSTART | ADC_CR_ADEN)) == ADC_CR_ADEN   \
        ) ? SET : RESET)

/**
  * @brief Shift the offset in function of the selected ADC resolution.
  *        Offset has to be left-aligned on bit 15, the LSB (right bits) are set to 0
  *        If resolution 16 bits, no shift.
  *        If resolution 14 bits, shift of 2 ranks on the left.
  *        If resolution 12 bits, shift of 4 ranks on the left.
  *        If resolution 10 bits, shift of 6 ranks on the left.
  *        If resolution 8 bits, shift of 8 ranks on the left.
  *        therefore, shift = (16 - resolution) = 16 - (16 - (((RES[2:0]) >> 2)*2))
  * @param __HANDLE__: ADC handle
  * @param __OFFSET__: Value to be shifted
  * @retval None
  */
#define ADC_OFFSET_SHIFT_RESOLUTION(__HANDLE__, __OFFSET__) \
        ((__OFFSET__) << ((((__HANDLE__)->Instance->CFGR & ADC_CFGR_RES) >> 2)*2))

/**
  * @brief Shift the AWD1 threshold in function of the selected ADC resolution.
  *        Thresholds have to be left-aligned on bit 15, the LSB (right bits) are set to 0.
  *        If resolution 16 bits, no shift.
  *        If resolution 14 bits, shift of 2 ranks on the left.
  *        If resolution 12 bits, shift of 4 ranks on the left.
  *        If resolution 10 bits, shift of 6 ranks on the left.
  *        If resolution 8 bits, shift of 8 ranks on the left.
  *        therefore, shift = (16 - resolution) = 16 - (16- (((RES[2:0]) >> 2)*2))
  * @param __HANDLE__: ADC handle
  * @param __THRESHOLD__: Value to be shifted
  * @retval None
  */
#define ADC_AWD1THRESHOLD_SHIFT_RESOLUTION(__HANDLE__, __THRESHOLD__) \
        ((__THRESHOLD__) << ((((__HANDLE__)->Instance->CFGR & ADC_CFGR_RES) >> 2)*2))

/**
  * @brief Shift the AWD2 and AWD3 threshold in function of the selected ADC resolution.
  *        Thresholds have to be left-aligned on bit 15, the LSB (right bits) are set to 0.
  *        If resolution 16 bits, no shift.
  *        If resolution 14 bits, shift of 2 ranks on the left.
  *        If resolution 12 bits, shift of 4 ranks on the left.
  *        If resolution 10 bits, shift of 6 ranks on the left.
  *        If resolution 8 bits, shift of 8 ranks on the left.
  *        therefore, shift = (16 - resolution) = 16 - (16- (((RES[2:0]) >> 2)*2))
  * @param __HANDLE__: ADC handle
  * @param __THRESHOLD__: Value to be shifted
  * @retval None
  */
#define ADC_AWD23THRESHOLD_SHIFT_RESOLUTION(__HANDLE__, __THRESHOLD__) \
        ((__THRESHOLD__) << ((((__HANDLE__)->Instance->CFGR & ADC_CFGR_RES) >> 2)*2))

/**
  * @brief Report common register to ADC1 and ADC2
  * @param __HANDLE__: ADC handle
  * @retval Common control register
  */
#define ADC12_COMMON_REGISTER(__HANDLE__)   (ADC12_COMMON)

/**
  * @brief Report common register to ADC1 and ADC2
  * @param __HANDLE__: ADC handle
  * @retval Common control register
  */
#define ADC3_COMMON_REGISTER(__HANDLE__)   (ADC3_COMMON)

/**
  * @brief Report Master Instance
  * @param __HANDLE__: ADC handle
  * @note return same instance if ADC of input handle is independent ADC
  * @retval Master Instance
  */
#define ADC_MASTER_REGISTER(__HANDLE__)                                          \
  ( ( ((((__HANDLE__)->Instance) == ADC1) || (((__HANDLE__)->Instance) == ADC3)) \
    )?                                                                           \
     ((__HANDLE__)->Instance)                                                    \
     :                                                                           \
     (ADC1)                                                                      \
  )

/**
  * @brief Check whether or not dual regular conversions are enabled
  * @param __HANDLE__: ADC handle
  * @retval SET (dual regular conversions are enabled) or RESET (ADC is independent or no dual regular conversions are enabled)
  */
#define ADC_IS_DUAL_REGULAR_CONVERSION_ENABLE(__HANDLE__)                        \
  ( ( ((((__HANDLE__)->Instance) == ADC1) || (((__HANDLE__)->Instance) == ADC2)) \
    )?                                                                           \
     ( ((ADC12_COMMON->CCR & ADC_CCR_DUAL) != ADC_MODE_INDEPENDENT)     &&      \
       ((ADC12_COMMON->CCR & ADC_CCR_DUAL) != ADC_DUALMODE_INJECSIMULT) &&      \
       ((ADC12_COMMON->CCR & ADC_CCR_DUAL) != ADC_DUALMODE_ALTERTRIG) )         \
     :                                                                           \
     RESET                                                                       \
  )

/**
  * @brief Verification of condition for ADC start conversion: ADC must be in non-MultiMode or MultiMode with handle of ADC master
  * @param __HANDLE__: ADC handle
  * @retval SET (non-MultiMode or Master handle) or RESET (handle of Slave ADC in MultiMode)
  */
#define ADC12_NONMULTIMODE_OR_MULTIMODEMASTER(__HANDLE__)                        \
  ( ( ((__HANDLE__)->Instance == ADC1) || ((__HANDLE__)->Instance == ADC2)     \
    )?                                                                         \
     SET                                                                       \
     :                                                                         \
     ((ADC12_COMMON->CCR & ADC_CCR_DUAL) == RESET)                            \
  )

/**
  * @brief Verification of condition for ADC start conversion: ADC must be in non-MultiMode or MultiMode with handle of ADC master
  * @param __HANDLE__: ADC handle
  * @retval SET (non-MultiMode or Master handle) or RESET (handle of Slave ADC in MultiMode)
  */
#define ADC3_NONMULTIMODE_OR_MULTIMODEMASTER(__HANDLE__)                        \
  ( ( ((__HANDLE__)->Instance == ADC3)                                          \
    )?                                                                         \
     SET                                                                       \
     :                                                                         \
     ((ADC3_COMMON->CCR & ADC_CCR_DUAL) == RESET)                            \
  )

/**
  * @brief Ensure ADC Instance is Independent or Master, or is not Slave ADC with dual regular conversions enabled
  * @param __HANDLE__: ADC handle
  * @retval SET (Independent or Master, or Slave without dual regular conversions enabled) or RESET (Slave ADC with dual regular conversions enabled)
  */
#define ADC_INDEPENDENT_OR_NONMULTIMODEREGULAR_SLAVE(__HANDLE__)            \
  ( ( ((__HANDLE__)->Instance == ADC1) || ((__HANDLE__)->Instance == ADC3)  \
    )?                                                                      \
     SET                                                                    \
     :                                                                      \
     ( ((ADC12_COMMON->CCR & ADC_CCR_DUAL) == ADC_MODE_INDEPENDENT)     || \
       ((ADC12_COMMON->CCR & ADC_CCR_DUAL) == ADC_DUALMODE_INJECSIMULT) || \
       ((ADC12_COMMON->CCR & ADC_CCR_DUAL) == ADC_DUALMODE_ALTERTRIG) ))

/**
  * @brief Ensure ADC Instance is Independent or Master, or is not Slave ADC with dual injected conversions enabled
  * @param __HANDLE__: ADC handle
  * @retval SET (non-MultiMode or Master, or Slave without dual injected conversions enabled) or RESET (Slave ADC with dual injected conversions enabled)
  */
#define ADC_INDEPENDENT_OR_NONMULTIMODEINJECTED_SLAVE(__HANDLE__)         \
  ( ( ((__HANDLE__)->Instance == ADC1) || ((__HANDLE__)->Instance == ADC3) \
    )?                                                                     \
     SET                                                                   \
     :                                                                     \
     ( ((ADC12_COMMON->CCR & ADC_CCR_DUAL) == ADC_MODE_INDEPENDENT)    || \
       ((ADC12_COMMON->CCR & ADC_CCR_DUAL) == ADC_DUALMODE_REGSIMULT)  || \
       ((ADC12_COMMON->CCR & ADC_CCR_DUAL) == ADC_DUALMODE_INTERL) ))

/**
  * @brief Verification of ADC state: enabled or disabled, directly checked on instance as input parameter
  * @param __INSTANCE__: ADC instance
  * @retval SET (ADC enabled) or RESET (ADC disabled)
  */
#define ADC_INSTANCE_IS_ENABLED(__INSTANCE__)                                                    \
       (( ((((__INSTANCE__)->CR) & (ADC_CR_ADEN | ADC_CR_ADDIS)) == ADC_CR_ADEN) && \
          ((((__INSTANCE__)->ISR) & ADC_FLAG_RDY) == ADC_FLAG_RDY)                  \
        ) ? SET : RESET)

/**
  * @brief Verification of enabled/disabled status of ADCs other than that associated to the input parameter handle
  * @param __HANDLE__: ADC handle
  * @retval SET (at least one other ADC is enabled) or RESET (no other ADC is enabled, all other ADCs are disabled)
  */
#define ADC_ANY_OTHER_ENABLED(__HANDLE__)           \
  ( ( ((__HANDLE__)->Instance == ADC1)                                         \
    )?                                                                         \
     (ADC_INSTANCE_IS_ENABLED(ADC2)) || (ADC_INSTANCE_IS_ENABLED(ADC3))  \
     :                                                                         \
     ( ( ((__HANDLE__)->Instance == ADC2)                                      \
       )?                                                                      \
         (ADC_INSTANCE_IS_ENABLED(ADC1)) || (ADC_INSTANCE_IS_ENABLED(ADC3))  \
        :                                                                      \
          ADC_INSTANCE_IS_ENABLED(ADC1)) || (ADC_INSTANCE_IS_ENABLED(ADC2))    \
     )                                                                         \

/**
  * @brief Set handle instance of the ADC slave associated to the ADC master
  * @param __HANDLE_MASTER__: ADC master handle
  * @param __HANDLE_SLAVE__: ADC slave handle
  * @note if __HANDLE_MASTER__ is the handle of a slave ADC (ADC2) or an independent ADC (ADC3), __HANDLE_SLAVE__ instance is set to NULL
  * @retval None
  */
#define ADC_MULTI_SLAVE(__HANDLE_MASTER__, __HANDLE_SLAVE__)             \
  ( (((__HANDLE_MASTER__)->Instance == ADC1)) ? ((__HANDLE_SLAVE__)->Instance = ADC2) : ((__HANDLE_SLAVE__)->Instance = NULL) )

/**
  * @brief Verify the ADC single-ended input or differential mode setting.
  * @param SING_DIFF: programmed channel setting. 
  * @retval SET (SING_DIFF is valid) or RESET (SING_DIFF is invalid)
  */
#define IS_ADC_SINGLE_DIFFERENTIAL(SING_DIFF) (((SING_DIFF) == ADC_SINGLE_ENDED)      || \
                                               ((SING_DIFF) == ADC_DIFFERENTIAL_ENDED)  )

/**
  * @brief Verify the ADC offset management setting.
  * @param OFFSET_NUMBER: ADC offset management. 
  * @retval SET (OFFSET_NUMBER is valid) or RESET (OFFSET_NUMBER is invalid)
  */
#define IS_ADC_OFFSET_NUMBER(OFFSET_NUMBER) (((OFFSET_NUMBER) == ADC_OFFSET_NONE) || \
                                             ((OFFSET_NUMBER) == ADC_OFFSET_1)    || \
                                             ((OFFSET_NUMBER) == ADC_OFFSET_2)    || \
                                             ((OFFSET_NUMBER) == ADC_OFFSET_3)    || \
                                             ((OFFSET_NUMBER) == ADC_OFFSET_4)      )

/**
  * @brief Verify the ADC injected channel setting.
  * @param CHANNEL: programmed ADC injected channel. 
  * @retval SET (CHANNEL is valid) or RESET (__CHANNEL__ is invalid)
  */
#define IS_ADC_INJECTED_RANK(CHANNEL) (((CHANNEL) == ADC_INJECTED_RANK_1) || \
                                       ((CHANNEL) == ADC_INJECTED_RANK_2) || \
                                       ((CHANNEL) == ADC_INJECTED_RANK_3) || \
                                       ((CHANNEL) == ADC_INJECTED_RANK_4)   )

/**
  * @brief Verify the ADC injected conversions external trigger.
  * @param INJTRIG: programmed ADC injected conversions external trigger.
  * @retval SET (INJTRIG is a valid value) or RESET (INJTRIG is invalid)
  */ 
#define IS_ADC_EXTTRIGINJEC(INJTRIG) (((INJTRIG) == ADC_EXTERNALTRIGINJEC_T1_TRGO)     || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJEC_T1_CC4)      || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJEC_T2_TRGO)     || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJEC_T2_CC1)      || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJEC_T3_CC4)      || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJEC_T4_TRGO)     || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJEC_EXT_IT15)    || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJEC_T8_CC4)      || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJEC_T1_TRGO2)    || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJEC_T8_TRGO)     || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJEC_T8_TRGO2)    || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJEC_T3_CC3)      || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJEC_T3_TRGO)     || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJEC_T3_CC1)      || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJEC_T6_TRGO)     || \
                                      ((INJTRIG) == ADC_EXTERNALTRIGINJEC_T15_TRGO)    || \
                                                                                          \
                                      ((INJTRIG) == ADC_SOFTWARE_START)                   )

/**
  * @brief Verify the ADC edge trigger setting for injected group.
  * @param EDGE: programmed ADC edge trigger setting.
  * @retval SET (EDGE is a valid value) or RESET (EDGE is invalid)
  */ 
#define IS_ADC_EXTTRIGINJEC_EDGE(EDGE) (((EDGE) == ADC_EXTERNALTRIGINJECCONV_EDGE_NONE)         || \
                                        ((EDGE) == ADC_EXTERNALTRIGINJECCONV_EDGE_RISING)       || \
                                        ((EDGE) == ADC_EXTERNALTRIGINJECCONV_EDGE_FALLING)      || \
                                        ((EDGE) == ADC_EXTERNALTRIGINJECCONV_EDGE_RISINGFALLING)  )

/**
  * @brief Verify the ADC multimode setting.
  * @param MODE: programmed ADC multimode setting.
  * @retval SET (MODE is valid) or RESET (MODE is invalid)
  */ 
#define IS_ADC_MODE(MODE) (((MODE) == ADC_MODE_INDEPENDENT)               || \
                           ((MODE) == ADC_DUALMODE_REGSIMULT_INJECSIMULT) || \
                           ((MODE) == ADC_DUALMODE_REGSIMULT_ALTERTRIG)   || \
                           ((MODE) == ADC_DUALMODE_REGINTERL_INJECSIMULT) || \
                           ((MODE) == ADC_DUALMODE_INJECSIMULT)           || \
                           ((MODE) == ADC_DUALMODE_REGSIMULT)             || \
                           ((MODE) == ADC_DUALMODE_INTERL)                || \
                           ((MODE) == ADC_DUALMODE_ALTERTRIG)               )

/**
  * @brief Verify the ADC dual data mode setting.
  * @param MODE: programmed ADC dual mode setting.
  * @retval SET (MODE is valid) or RESET (MODE is invalid)
  */
#define IS_ADC_DUAL_DATA_MODE(MODE) (((MODE) == ADC_DUALMODEDATAFORMAT_DISABLED)   || \
                                     ((MODE) == ADC_DUALMODEDATAFORMAT_32_10_BITS) || \
                                     ((MODE) == ADC_DUALMODEDATAFORMAT_8_BITS)     )

/**
  * @brief Verify the ADC multimode delay setting.
  * @param DELAY: programmed ADC multimode delay setting.
  * @retval SET (DELAY is a valid value) or RESET (DELAY is invalid)
  */
#define IS_ADC_SAMPLING_DELAY(DELAY) (((DELAY) == ADC_TWOSAMPLINGDELAY_1CYCLE)   || \
                                      ((DELAY) == ADC_TWOSAMPLINGDELAY_2CYCLES)  || \
                                      ((DELAY) == ADC_TWOSAMPLINGDELAY_3CYCLES)  || \
                                      ((DELAY) == ADC_TWOSAMPLINGDELAY_4CYCLES)  || \
                                      ((DELAY) == ADC_TWOSAMPLINGDELAY_5CYCLES)  || \
                                      ((DELAY) == ADC_TWOSAMPLINGDELAY_6CYCLES)  || \
                                      ((DELAY) == ADC_TWOSAMPLINGDELAY_7CYCLES)  || \
                                      ((DELAY) == ADC_TWOSAMPLINGDELAY_8CYCLES)  || \
                                      ((DELAY) == ADC_TWOSAMPLINGDELAY_9CYCLES))

/**
  * @brief Verify the ADC analog watchdog setting.
  * @param WATCHDOG: programmed ADC analog watchdog setting.
  * @retval SET (WATCHDOG is valid) or RESET (WATCHDOG is invalid)
  */
#define IS_ADC_ANALOG_WATCHDOG_NUMBER(WATCHDOG) (((WATCHDOG) == ADC_ANALOGWATCHDOG_1) || \
                                                 ((WATCHDOG) == ADC_ANALOGWATCHDOG_2) || \
                                                 ((WATCHDOG) == ADC_ANALOGWATCHDOG_3)   )

/**
  * @brief Verify the ADC analog watchdog mode setting.
  * @param WATCHDOG: programmed ADC analog watchdog mode setting.
  * @retval SET (WATCHDOG is valid) or RESET (WATCHDOG is invalid)
  */
#define IS_ADC_ANALOG_WATCHDOG_MODE(WATCHDOG) (((WATCHDOG) == ADC_ANALOGWATCHDOG_NONE)             || \
                                               ((WATCHDOG) == ADC_ANALOGWATCHDOG_SINGLE_REG)       || \
                                               ((WATCHDOG) == ADC_ANALOGWATCHDOG_SINGLE_INJEC)     || \
                                               ((WATCHDOG) == ADC_ANALOGWATCHDOG_SINGLE_REGINJEC)  || \
                                               ((WATCHDOG) == ADC_ANALOGWATCHDOG_ALL_REG)          || \
                                               ((WATCHDOG) == ADC_ANALOGWATCHDOG_ALL_INJEC)        || \
                                               ((WATCHDOG) == ADC_ANALOGWATCHDOG_ALL_REGINJEC)       )

/**
  * @brief Verify the ADC conversion (regular or injected or both).
  * @param CONVERSION: ADC conversion group.
  * @retval SET (CONVERSION is valid) or RESET (CONVERSION is invalid)
  */#define IS_ADC_CONVERSION_GROUP(CONVERSION) (((CONVERSION) == ADC_REGULAR_GROUP)         || \
                                                 ((CONVERSION) == ADC_INJECTED_GROUP)        || \
                                                 ((CONVERSION) == ADC_REGULAR_INJECTED_GROUP)  )

/**
  * @brief Verify the ADC event type.
  * @param EVENT: ADC event.
  * @retval SET (EVENT is valid) or RESET (EVENT is invalid)
  */
#define IS_ADC_EVENT_TYPE(EVENT) (((EVENT) == ADC_EOSMP_EVENT) || \
                                  ((EVENT) == ADC_AWD_EVENT)   || \
                                  ((EVENT) == ADC_AWD2_EVENT)  || \
                                  ((EVENT) == ADC_AWD3_EVENT)  || \
                                  ((EVENT) == ADC_OVR_EVENT)   || \
                                  ((EVENT) == ADC_JQOVF_EVENT)  )

/**
  * @brief Verify the ADC scan mode.
  * @param SCAN_MODE: ADC scan mode.
  * @retval SET (SCAN_MODE is valid) or RESET (SCAN_MODE is invalid)
  */
#define IS_ADC_SCAN_MODE(SCAN_MODE) (((SCAN_MODE) == ADC_SCAN_DISABLE) || \
                                     ((SCAN_MODE) == ADC_SCAN_ENABLE)    )

/**
  * @brief Verify the ADC oversampling ratio. 
  * @param RATIO: programmed ADC oversampling ratio.
  * @retval SET (RATIO is a valid value) or RESET (RATIO is invalid)
  */
#define IS_ADC_OVERSAMPLING_RATIO(RATIO)  ((RATIO) < 1024)

/**
  * @brief Verify the ADC oversampling right shift. 
  * @param SHIFT: programmed ADC oversampling right shift.
  * @retval SET (SHIFT is a valid value) or RESET (SHIFT is invalid)
  */
#define IS_ADC_RIGHT_BIT_SHIFT(SHIFT)               (((SHIFT) == ADC_RIGHTBITSHIFT_NONE) || \
                                                     ((SHIFT) == ADC_RIGHTBITSHIFT_1   ) || \
                                                     ((SHIFT) == ADC_RIGHTBITSHIFT_2   ) || \
                                                     ((SHIFT) == ADC_RIGHTBITSHIFT_3   ) || \
                                                     ((SHIFT) == ADC_RIGHTBITSHIFT_4   ) || \
                                                     ((SHIFT) == ADC_RIGHTBITSHIFT_5   ) || \
                                                     ((SHIFT) == ADC_RIGHTBITSHIFT_6   ) || \
                                                     ((SHIFT) == ADC_RIGHTBITSHIFT_7   ) || \
                                                     ((SHIFT) == ADC_RIGHTBITSHIFT_8   ))

/**
  * @brief Verify the ADC oversampling left shift. 
  * @param SHIFT: programmed ADC oversampling left shift.
  * @retval SET (SHIFT is a valid value) or RESET (SHIFT is invalid)
  */
#define IS_ADC_LEFT_BIT_SHIFT(SHIFT)                (((SHIFT) == ADC_LEFTBITSHIFT_NONE) || \
                                                     ((SHIFT) == ADC_LEFTBITSHIFT_1   ) || \
                                                     ((SHIFT) == ADC_LEFTBITSHIFT_2   ) || \
                                                     ((SHIFT) == ADC_LEFTBITSHIFT_3   ) || \
                                                     ((SHIFT) == ADC_LEFTBITSHIFT_4   ) || \
                                                     ((SHIFT) == ADC_LEFTBITSHIFT_5   ) || \
                                                     ((SHIFT) == ADC_LEFTBITSHIFT_6   ) || \
                                                     ((SHIFT) == ADC_LEFTBITSHIFT_7   ) || \
                                                     ((SHIFT) == ADC_LEFTBITSHIFT_8   ) || \
                                                     ((SHIFT) == ADC_LEFTBITSHIFT_9   ) || \
                                                     ((SHIFT) == ADC_LEFTBITSHIFT_10   ) || \
                                                     ((SHIFT) == ADC_LEFTBITSHIFT_11   ) || \
                                                     ((SHIFT) == ADC_LEFTBITSHIFT_12   ) || \
                                                     ((SHIFT) == ADC_LEFTBITSHIFT_13   ) || \
                                                     ((SHIFT) == ADC_LEFTBITSHIFT_14   ) || \
                                                     ((SHIFT) == ADC_LEFTBITSHIFT_15   ))

/**
  * @brief Verify the ADC oversampling triggered mode. 
  * @param MODE: programmed ADC oversampling triggered mode. 
  * @retval SET (MODE is valid) or RESET (MODE is invalid)
  */ 
#define IS_ADC_TRIGGERED_OVERSAMPLING_MODE(MODE) (((MODE) == ADC_TRIGGEREDMODE_SINGLE_TRIGGER) || \
                                                  ((MODE) == ADC_TRIGGEREDMODE_MULTI_TRIGGER) )

/**
  * @brief Verify the ADC oversampling regular conversion resumed or continued mode. 
  * @param MODE: programmed ADC oversampling regular conversion resumed or continued mode. 
  * @retval SET (MODE is valid) or RESET (MODE is invalid)
  */ 
#define IS_ADC_REGOVERSAMPLING_MODE(MODE) (((MODE) == ADC_REGOVERSAMPLING_CONTINUED_MODE) || \
                                           ((MODE) == ADC_REGOVERSAMPLING_RESUMED_MODE) )

/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/
/** @addtogroup ADCEx_Exported_Functions ADC Extended Exported Functions
  * @{
  */

/* Initialization/de-initialization functions *********************************/

/** @addtogroup ADCEx_Exported_Functions_Group1 Extended Input and Output operation functions
  * @brief    Extended IO operation functions
  * @{
  */
/* I/O operation functions ****************************************************/

/* ADC calibration */

HAL_StatusTypeDef       HAL_ADCEx_Calibration_Start(ADC_HandleTypeDef* hadc, uint32_t CalibrationMode, uint32_t SingleDiff);
uint32_t                HAL_ADCEx_Calibration_GetValue(ADC_HandleTypeDef *hadc, uint32_t SingleDiff);
HAL_StatusTypeDef       HAL_ADCEx_LinearCalibration_GetValue(ADC_HandleTypeDef* hadc, uint32_t* LinearCalib_Buffer);
HAL_StatusTypeDef       HAL_ADCEx_Calibration_SetValue(ADC_HandleTypeDef *hadc, uint32_t SingleDiff, uint32_t CalibrationFactor);
HAL_StatusTypeDef       HAL_ADCEx_LinearCalibration_SetValue(ADC_HandleTypeDef *hadc, uint32_t* LinearCalib_Buffer);


/* Blocking mode: Polling */
HAL_StatusTypeDef       HAL_ADCEx_InjectedStart(ADC_HandleTypeDef* hadc);
HAL_StatusTypeDef       HAL_ADCEx_InjectedStop(ADC_HandleTypeDef* hadc);
HAL_StatusTypeDef       HAL_ADCEx_InjectedPollForConversion(ADC_HandleTypeDef* hadc, uint32_t Timeout);

/* Non-blocking mode: Interruption */
HAL_StatusTypeDef       HAL_ADCEx_InjectedStart_IT(ADC_HandleTypeDef* hadc);
HAL_StatusTypeDef       HAL_ADCEx_InjectedStop_IT(ADC_HandleTypeDef* hadc);


/* ADC multimode */
HAL_StatusTypeDef       HAL_ADCEx_MultiModeStart_DMA(ADC_HandleTypeDef *hadc, uint32_t *pData, uint32_t Length);
HAL_StatusTypeDef       HAL_ADCEx_MultiModeStop_DMA(ADC_HandleTypeDef *hadc);
uint32_t                HAL_ADCEx_MultiModeGetValue(ADC_HandleTypeDef *hadc);


/* ADC retrieve conversion value intended to be used with polling or interruption */
uint32_t                HAL_ADCEx_InjectedGetValue(ADC_HandleTypeDef* hadc, uint32_t InjectedRank);

/* ADC IRQHandler and Callbacks used in non-blocking modes (Interruption) */
void                    HAL_ADCEx_InjectedConvCpltCallback(ADC_HandleTypeDef* hadc);
void                    HAL_ADCEx_InjectedQueueOverflowCallback(ADC_HandleTypeDef* hadc);
void                    HAL_ADCEx_LevelOutOfWindow2Callback(ADC_HandleTypeDef* hadc);
void                    HAL_ADCEx_LevelOutOfWindow3Callback(ADC_HandleTypeDef* hadc);
void                    HAL_ADCEx_EndOfSamplingCallback(ADC_HandleTypeDef* hadc);


/* ADC Regular conversions stop */
HAL_StatusTypeDef HAL_ADCEx_RegularStop(ADC_HandleTypeDef* hadc);
HAL_StatusTypeDef HAL_ADCEx_RegularStop_IT(ADC_HandleTypeDef* hadc);
HAL_StatusTypeDef HAL_ADCEx_RegularStop_DMA(ADC_HandleTypeDef* hadc);
HAL_StatusTypeDef HAL_ADCEx_RegularMultiModeStop_DMA(ADC_HandleTypeDef* hadc);

/**
  * @}
  */

/** @addtogroup ADCEx_Exported_Functions_Group2 ADC Extended Peripheral Control functions
  * @brief    ADC Extended Peripheral Control functions
  * @{
  */
/* Peripheral Control functions ***********************************************/
HAL_StatusTypeDef       HAL_ADCEx_InjectedConfigChannel(ADC_HandleTypeDef* hadc,ADC_InjectionConfTypeDef* sConfigInjected);
HAL_StatusTypeDef       HAL_ADCEx_MultiModeConfigChannel(ADC_HandleTypeDef *hadc, ADC_MultiModeTypeDef *multimode);
HAL_StatusTypeDef       HAL_ADCEx_EnableInjectedQueue(ADC_HandleTypeDef* hadc);
HAL_StatusTypeDef       HAL_ADCEx_DisableInjectedQueue(ADC_HandleTypeDef* hadc);
HAL_StatusTypeDef       HAL_ADCEx_DisableVoltageRegulator(ADC_HandleTypeDef* hadc);
HAL_StatusTypeDef       HAL_ADCEx_EnterADCDeepPowerDownMode(ADC_HandleTypeDef* hadc);

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /*__STM32H7xx_ADC_EX_H */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
