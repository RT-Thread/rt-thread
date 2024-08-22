/**
  ******************************************************************************
  * @file    stm32h7xx_hal_adc_ex.h
  * @author  MCD Application Team
  * @brief   Header file of ADC HAL extended module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2017 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32H7xx_HAL_ADC_EX_H
#define STM32H7xx_HAL_ADC_EX_H

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
  * @brief  ADC Injected Conversion Oversampling structure definition
  */
typedef struct
{
  uint32_t Ratio;                         /*!< Configures the oversampling ratio. */
#if defined(ADC_VER_V5_V90)
                                             /* On devices STM32H72xx and STM32H73xx this parameter can be a value from 1 to 1023 for ADC1/2 and value of @ref ADC_HAL_EC_OVS_RATIO for ADC3*/
#else
                                              /* This parameter can be a value of @ref ADC_HAL_EC_OVS_RATIO */
#endif

  uint32_t RightBitShift;                 /*!< Configures the division coefficient for the Oversampler.
                                               This parameter can be a value of @ref ADC_HAL_EC_OVS_SHIFT */
} ADC_InjOversamplingTypeDef;

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
                                               This parameter can be a value of @ref ADC_HAL_EC_CHANNEL
                                               Note: Depending on devices and ADC instances, some channels may not be available on device package pins. Refer to device datasheet for channels availability. */

  uint32_t InjectedRank;                  /*!< Specifies the rank in the ADC group injected sequencer.
                                               This parameter must be a value of @ref ADC_INJ_SEQ_RANKS.
                                               Note: to disable a channel or change order of conversion sequencer, rank containing a previous channel setting can be overwritten by
                                               the new channel setting (or parameter number of conversions adjusted) */

  uint32_t InjectedSamplingTime;          /*!< Sampling time value to be set for the selected channel.
                                               Unit: ADC clock cycles.
                                               Conversion time is the addition of sampling time and processing time
                                               (12.5 ADC clock cycles at ADC resolution 12 bits, 10.5 cycles at 10 bits, 8.5 cycles at 8 bits, 6.5 cycles at 6 bits).
                                               This parameter can be a value of @ref ADC_HAL_EC_CHANNEL_SAMPLINGTIME.
                                               Caution: This parameter applies to a channel that can be used in a regular and/or injected group.
                                                        It overwrites the last setting.
                                               Note: In case of usage of internal measurement channels (VrefInt/Vbat/TempSensor),
                                                     sampling time constraints must be respected (sampling time can be adjusted in function of ADC clock frequency and sampling time setting)
                                                     Refer to device datasheet for timings values. */

  uint32_t InjectedSingleDiff;            /*!< Selection of single-ended or differential input.
                                               In differential mode: Differential measurement is between the selected channel 'i' (positive input) and channel 'i+1' (negative input).
                                               Only channel 'i' has to be configured, channel 'i+1' is configured automatically.
                                               This parameter must be a value of @ref ADC_HAL_EC_CHANNEL_SINGLE_DIFF_ENDING.
                                               Caution: This parameter applies to a channel that can be used in a regular and/or injected group.
                                                        It overwrites the last setting.
                                               Note: Refer to Reference Manual to ensure the selected channel is available in differential mode.
                                               Note: When configuring a channel 'i' in differential mode, the channel 'i+1' is not usable separately.
                                               Note: This parameter must be modified when ADC is disabled (before ADC start conversion or after ADC stop conversion).
                                               If ADC is enabled, this parameter setting is bypassed without error reporting (as it can be the expected behavior in case
                                               of another parameter update on the fly) */

  uint32_t InjectedOffsetNumber;          /*!< Selects the offset number.
                                               This parameter can be a value of @ref ADC_HAL_EC_OFFSET_NB.
                                               Caution: Only one offset is allowed per channel. This parameter overwrites the last setting. */

  uint32_t InjectedOffset;                /*!< Defines the offset to be subtracted from the raw converted data.
                                               Offset value must be a positive number.
                                               Maximum value depends on ADC resolution and oversampling ratio (in case of oversampling used).
                                               This parameter must be a number between Min_Data = 0x0000 and Max_Data = 0x3FFFC00 (corresponding to resolution 16 bit and oversampling ratio 1024).
                                               Note: This parameter must be modified when no conversion is on going on both regular and injected groups (ADC disabled, or ADC enabled
                                               without continuous mode or external trigger that could launch a conversion). */

  uint32_t InjectedOffsetRightShift;       /*!< Specifies whether the 1 bit Right-shift feature is used or not.
                                                This parameter is applied only for 16-bit or 8-bit resolution.
                                                This parameter can be set to ENABLE or DISABLE. */
#if defined(ADC_VER_V5_V90)
  uint32_t InjectedOffsetSign;                /*!< Define if the offset should be subtracted (negative sign) or added (positive sign) from or to the raw converted data.
                                               This parameter can be a value of @ref ADCEx_OffsetSign.
                                               Note: 
                                                     - This parameter must be modified when no conversion is on going on both regular and injected groups (ADC disabled, or ADC enabled without continuous mode or external trigger that could launch a conversion). 
                                                     - On devices STM32H72xx and STM32H73xx, this parameter is specific to ADC3 only. */
  FunctionalState InjectedOffsetSaturation;   /*!< Define if the offset should be saturated upon under or over flow.
                                               This parameter value can be ENABLE or DISABLE.
                                               Note: 
                                                     - This parameter must be modified when no conversion is on going on both regular and injected groups (ADC disabled, or ADC enabled without continuous mode or external trigger that could launch a conversion). 
                                                     - On devices STM32H72xx and STM32H73xx, this parameter is specific to ADC3 only. */

#endif

  FunctionalState InjectedOffsetSignedSaturation;      /*!< Specifies whether the Signed saturation feature is used or not.
                                               This parameter is applied only for 16-bit or 8-bit resolution.
                                               This parameter can be set to ENABLE or DISABLE. */

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

  FunctionalState AutoInjectedConv;       /*!< Enables or disables the selected ADC group injected automatic conversion after regular one
                                               This parameter can be set to ENABLE or DISABLE.
                                               Note: To use Automatic injected conversion, discontinuous mode must be disabled ('DiscontinuousConvMode' and 'InjectedDiscontinuousConvMode' set to DISABLE)
                                               Note: To use Automatic injected conversion, injected group external triggers must be disabled ('ExternalTrigInjecConv' set to ADC_INJECTED_SOFTWARE_START)
                                               Note: In case of DMA used with regular group: if DMA configured in normal mode (single shot) JAUTO will be stopped upon DMA transfer complete.
                                                     To maintain JAUTO always enabled, DMA must be configured in circular mode.
                                               Caution: this setting impacts the entire injected group. Therefore, call of HAL_ADCEx_InjectedConfigChannel() to
                                                        configure a channel on injected group can impact the configuration of other channels previously set. */

  FunctionalState QueueInjectedContext;   /*!< Specifies whether the context queue feature is enabled.
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
                                               This parameter can be a value of @ref ADC_injected_external_trigger_source.
                                               Caution: this setting impacts the entire injected group. Therefore, call of HAL_ADCEx_InjectedConfigChannel() to
                                                        configure a channel on injected group can impact the configuration of other channels previously set. */

  uint32_t ExternalTrigInjecConvEdge;     /*!< Selects the external trigger edge of injected group.
                                               This parameter can be a value of @ref ADC_injected_external_trigger_edge.
                                               If trigger source is set to ADC_INJECTED_SOFTWARE_START, this parameter is discarded.
                                               Caution: this setting impacts the entire injected group. Therefore, call of HAL_ADCEx_InjectedConfigChannel() to
                                                        configure a channel on injected group can impact the configuration of other channels previously set. */

  FunctionalState InjecOversamplingMode;         /*!< Specifies whether the oversampling feature is enabled or disabled.
                                                      This parameter can be set to ENABLE or DISABLE.
                                                      Note: This parameter can be modified only if there is no conversion is ongoing (both ADSTART and JADSTART cleared). */

  ADC_InjOversamplingTypeDef  InjecOversampling; /*!< Specifies the Oversampling parameters.
                                                      Caution: this setting overwrites the previous oversampling configuration if oversampling already enabled.
                                                      Note: This parameter can be modified only if there is no conversion is ongoing (both ADSTART and JADSTART cleared). */
} ADC_InjectionConfTypeDef;

/**
  * @brief  Structure definition of ADC multimode
  * @note   The setting of these parameters by function HAL_ADCEx_MultiModeConfigChannel() is conditioned by ADCs state (both Master and Slave ADCs).
  *         Both Master and Slave ADCs must be disabled.
  */
typedef struct
{
  uint32_t Mode;              /*!< Configures the ADC to operate in independent or multimode.
                                   This parameter can be a value of @ref ADC_HAL_EC_MULTI_MODE. */

  uint32_t DualModeData;      /*!< Configures the Dual ADC Mode Data Format:
                                   This parameter can be a value of @ref ADCEx_Dual_Mode_Data_Format */

  uint32_t TwoSamplingDelay;  /*!< Configures the Delay between 2 sampling phases.
                                   This parameter can be a value of @ref ADC_HAL_EC_MULTI_TWOSMP_DELAY.
                                   Delay range depends on selected resolution:
                                   from 1 to 9 clock cycles for 16 bits,
                                   from 1 to 9 clock cycles for 14 bits
                                   from 1 to 8 clock cycles for 12 bits
                                   from 1 to 6 clock cycles for 10 bits
                                   from 1 to 6 clock cycles for 8 bits     */
} ADC_MultiModeTypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/

/** @defgroup ADCEx_Exported_Constants ADC Extended Exported Constants
  * @{
  */

/** @defgroup ADC_injected_external_trigger_source ADC group injected trigger source
  * @{
  */
/* ADC group regular trigger sources for all ADC instances */
#define ADC_INJECTED_SOFTWARE_START        (LL_ADC_INJ_TRIG_SOFTWARE)            /*!< Software triggers injected group conversion start */
#define ADC_EXTERNALTRIGINJEC_T1_TRGO      (LL_ADC_INJ_TRIG_EXT_TIM1_TRGO)       /*!< ADC group injected conversion trigger from external peripheral: TIM1 TRGO event. Trigger edge set to rising edge (default setting). */
#define ADC_EXTERNALTRIGINJEC_T1_CC4       (LL_ADC_INJ_TRIG_EXT_TIM1_CH4)        /*!< ADC group injected conversion trigger from external peripheral: TIM1 channel 4 event (capture compare: input capture or output capture). Trigger edge set to rising edge (default setting). */
#define ADC_EXTERNALTRIGINJEC_T2_TRGO      (LL_ADC_INJ_TRIG_EXT_TIM2_TRGO)       /*!< ADC group injected conversion trigger from external peripheral: TIM2 TRGO event. Trigger edge set to rising edge (default setting). */
#define ADC_EXTERNALTRIGINJEC_T2_CC1       (LL_ADC_INJ_TRIG_EXT_TIM2_CH1)        /*!< ADC group injected conversion trigger from external peripheral: TIM2 channel 1 event (capture compare: input capture or output capture). Trigger edge set to rising edge (default setting). */
#define ADC_EXTERNALTRIGINJEC_T3_CC4       (LL_ADC_INJ_TRIG_EXT_TIM3_CH4)        /*!< ADC group injected conversion trigger from external peripheral: TIM3 channel 4 event (capture compare: input capture or output capture). Trigger edge set to rising edge (default setting). */
#define ADC_EXTERNALTRIGINJEC_T4_TRGO      (LL_ADC_INJ_TRIG_EXT_TIM4_TRGO)       /*!< ADC group injected conversion trigger from external peripheral: TIM4 TRGO event. Trigger edge set to rising edge (default setting). */
#define ADC_EXTERNALTRIGINJEC_EXT_IT15     (LL_ADC_INJ_TRIG_EXT_EXTI_LINE15)     /*!< ADC group injected conversion trigger from external peripheral: external interrupt line 15. Trigger edge set to rising edge (default setting). */
#define ADC_EXTERNALTRIGINJEC_T8_CC4       (LL_ADC_INJ_TRIG_EXT_TIM8_CH4)        /*!< ADC group injected conversion trigger from external peripheral: TIM8 channel 4 event (capture compare: input capture or output capture). Trigger edge set to rising edge (default setting). */
#define ADC_EXTERNALTRIGINJEC_T1_TRGO2     (LL_ADC_INJ_TRIG_EXT_TIM1_TRGO2)      /*!< ADC group injected conversion trigger from external peripheral: TIM1 TRGO2 event. Trigger edge set to rising edge (default setting). */
#define ADC_EXTERNALTRIGINJEC_T8_TRGO      (LL_ADC_INJ_TRIG_EXT_TIM8_TRGO)       /*!< ADC group injected conversion trigger from external peripheral: TIM8 TRGO event. Trigger edge set to rising edge (default setting). */
#define ADC_EXTERNALTRIGINJEC_T8_TRGO2     (LL_ADC_INJ_TRIG_EXT_TIM8_TRGO2)      /*!< ADC group injected conversion trigger from external peripheral: TIM8 TRGO2 event. Trigger edge set to rising edge (default setting). */
#define ADC_EXTERNALTRIGINJEC_T3_CC3       (LL_ADC_INJ_TRIG_EXT_TIM3_CH3)        /*!< ADC group injected conversion trigger from external peripheral: TIM3 channel 3 event (capture compare: input capture or output capture). Trigger edge set to rising edge (default setting). */
#define ADC_EXTERNALTRIGINJEC_T3_TRGO      (LL_ADC_INJ_TRIG_EXT_TIM3_TRGO)       /*!< ADC group injected conversion trigger from external peripheral: TIM3 TRGO event. Trigger edge set to rising edge (default setting). */
#define ADC_EXTERNALTRIGINJEC_T3_CC1       (LL_ADC_INJ_TRIG_EXT_TIM3_CH1)        /*!< ADC group injected conversion trigger from external peripheral: TIM3 channel 1 event (capture compare: input capture or output capture). Trigger edge set to rising edge (default setting). */
#define ADC_EXTERNALTRIGINJEC_T6_TRGO      (LL_ADC_INJ_TRIG_EXT_TIM6_TRGO)       /*!< ADC group injected conversion trigger from external peripheral: TIM6 TRGO event. Trigger edge set to rising edge (default setting). */
#define ADC_EXTERNALTRIGINJEC_T15_TRGO     (LL_ADC_INJ_TRIG_EXT_TIM15_TRGO)      /*!< ADC group injected conversion trigger from external peripheral: TIM15 TRGO event. Trigger edge set to rising edge (default setting). */
#if defined(HRTIM1)
#define ADC_EXTERNALTRIGINJEC_HR1_ADCTRG2  (LL_ADC_INJ_TRIG_EXT_HRTIM_TRG2)      /*!< ADC group injected conversion trigger from external peripheral: HRTIM1 TRG2 event. Trigger edge set to rising edge (default setting). */
#define ADC_EXTERNALTRIGINJEC_HR1_ADCTRG4  (LL_ADC_INJ_TRIG_EXT_HRTIM_TRG4)      /*!< ADC group injected conversion trigger from external peripheral: HRTIM1 TRG4 event. Trigger edge set to rising edge (default setting). */
#endif /* HRTIM1 */
#define ADC_EXTERNALTRIGINJEC_LPTIM1_OUT   (LL_ADC_INJ_TRIG_EXT_LPTIM1_OUT)      /*!< ADC group injected conversion trigger from external peripheral: LPTIM1 OUT event. Trigger edge set to rising edge (default setting). */
#define ADC_EXTERNALTRIGINJEC_LPTIM2_OUT   (LL_ADC_INJ_TRIG_EXT_LPTIM2_OUT)      /*!< ADC group injected conversion trigger from external peripheral: LPTIM2 OUT event. Trigger edge set to rising edge (default setting). */
#define ADC_EXTERNALTRIGINJEC_LPTIM3_OUT   (LL_ADC_INJ_TRIG_EXT_LPTIM3_OUT)      /*!< ADC group injected conversion trigger from external peripheral: LPTIM3 OUT event. Trigger edge set to rising edge (default setting). */
/**
  * @}
  */

/** @defgroup ADC_injected_external_trigger_edge ADC group injected trigger edge (when external trigger is selected)
  * @{
  */
#define ADC_EXTERNALTRIGINJECCONV_EDGE_NONE           (0x00000000UL)        /*!< Injected conversions hardware trigger detection disabled                             */
#define ADC_EXTERNALTRIGINJECCONV_EDGE_RISING         (ADC_JSQR_JEXTEN_0)   /*!< Injected conversions hardware trigger detection on the rising edge                   */
#define ADC_EXTERNALTRIGINJECCONV_EDGE_FALLING        (ADC_JSQR_JEXTEN_1)   /*!< Injected conversions hardware trigger detection on the falling edge                  */
#define ADC_EXTERNALTRIGINJECCONV_EDGE_RISINGFALLING  (ADC_JSQR_JEXTEN)     /*!< Injected conversions hardware trigger detection on both the rising and falling edges */
/**
  * @}
  */

/** @defgroup ADC_HAL_EC_CHANNEL_SINGLE_DIFF_ENDING  Channel - Single or differential ending
  * @{
  */
#define ADC_SINGLE_ENDED                (LL_ADC_SINGLE_ENDED)         /*!< ADC channel ending set to single ended (literal also used to set calibration mode) */
#define ADC_DIFFERENTIAL_ENDED          (LL_ADC_DIFFERENTIAL_ENDED)   /*!< ADC channel ending set to differential (literal also used to set calibration mode) */
/**
  * @}
  */

/** @defgroup ADC_HAL_EC_OFFSET_NB  ADC instance - Offset number
  * @{
  */
#define ADC_OFFSET_NONE              (ADC_OFFSET_4 + 1U) /*!< ADC offset disabled: no offset correction for the selected ADC channel */
#define ADC_OFFSET_1                 (LL_ADC_OFFSET_1) /*!< ADC offset number 1: ADC channel and offset level to which the offset programmed will be applied (independently of channel mapped on ADC group regular or group injected) */
#define ADC_OFFSET_2                 (LL_ADC_OFFSET_2) /*!< ADC offset number 2: ADC channel and offset level to which the offset programmed will be applied (independently of channel mapped on ADC group regular or group injected) */
#define ADC_OFFSET_3                 (LL_ADC_OFFSET_3) /*!< ADC offset number 3: ADC channel and offset level to which the offset programmed will be applied (independently of channel mapped on ADC group regular or group injected) */
#define ADC_OFFSET_4                 (LL_ADC_OFFSET_4) /*!< ADC offset number 4: ADC channel and offset level to which the offset programmed will be applied (independently of channel mapped on ADC group regular or group injected) */
/**
  * @}
  */

#if defined(ADC_VER_V5_V90)
/** @defgroup ADCEx_OffsetSign ADC Extended Offset Sign
  * @{
  */
#define ADC3_OFFSET_SIGN_NEGATIVE      (0x00000000UL)          /*!< Offset sign negative, offset is subtracted */
#define ADC3_OFFSET_SIGN_POSITIVE      (ADC3_OFR1_OFFSETPOS)   /*!< Offset sign positive, offset is added  */
/**
  * @}
  */
#endif

/** @defgroup ADC_INJ_SEQ_RANKS  ADC group injected - Sequencer ranks
  * @{
  */
#define ADC_INJECTED_RANK_1                (LL_ADC_INJ_RANK_1) /*!< ADC group injected sequencer rank 1 */
#define ADC_INJECTED_RANK_2                (LL_ADC_INJ_RANK_2) /*!< ADC group injected sequencer rank 2 */
#define ADC_INJECTED_RANK_3                (LL_ADC_INJ_RANK_3) /*!< ADC group injected sequencer rank 3 */
#define ADC_INJECTED_RANK_4                (LL_ADC_INJ_RANK_4) /*!< ADC group injected sequencer rank 4 */
/**
  * @}
  */

/** @defgroup ADC_HAL_EC_MULTI_MODE  Multimode - Mode
  * @{
  */
#define ADC_MODE_INDEPENDENT               (LL_ADC_MULTI_INDEPENDENT)                                          /*!< ADC dual mode disabled (ADC independent mode) */
#define ADC_DUALMODE_REGSIMULT             (LL_ADC_MULTI_DUAL_REG_SIMULT) /*!< ADC dual mode enabled: group regular simultaneous */
#define ADC_DUALMODE_INTERL                (LL_ADC_MULTI_DUAL_REG_INTERL) /*!< ADC dual mode enabled: Combined group regular interleaved */
#define ADC_DUALMODE_INJECSIMULT           (LL_ADC_MULTI_DUAL_INJ_SIMULT) /*!< ADC dual mode enabled: group injected simultaneous */
#define ADC_DUALMODE_ALTERTRIG             (LL_ADC_MULTI_DUAL_INJ_ALTERN) /*!< ADC dual mode enabled: group injected alternate trigger. Works only with external triggers (not internal SW start) */
#define ADC_DUALMODE_REGSIMULT_INJECSIMULT (LL_ADC_MULTI_DUAL_REG_SIM_INJ_SIM) /*!< ADC dual mode enabled: Combined group regular simultaneous + group injected simultaneous */
#define ADC_DUALMODE_REGSIMULT_ALTERTRIG   (LL_ADC_MULTI_DUAL_REG_SIM_INJ_ALT) /*!< ADC dual mode enabled: Combined group regular simultaneous + group injected alternate trigger */
#define ADC_DUALMODE_REGINTERL_INJECSIMULT (LL_ADC_MULTI_DUAL_REG_INT_INJ_SIM) /*!< ADC dual mode enabled: Combined group regular interleaved + group injected simultaneous */

/** @defgroup ADCEx_Dual_Mode_Data_Format ADC Extended Dual Mode Data Formatting
  * @{
  */
#define ADC_DUALMODEDATAFORMAT_DISABLED      (0x00000000UL)                       /*!< Dual ADC mode without data packing: ADCx_CDR and ADCx_CDR2 registers not used */
#define ADC_DUALMODEDATAFORMAT_32_10_BITS    (ADC_CCR_DAMDF_1)                    /*!< Data formatting mode for 32 down to 10-bit resolution */
#define ADC_DUALMODEDATAFORMAT_8_BITS        ((ADC_CCR_DAMDF_0 |ADC_CCR_DAMDF_1)) /*!< Data formatting mode for 8-bit resolution */
/**
  * @}
  */

/** @defgroup ADC_HAL_EC_MULTI_TWOSMP_DELAY  Multimode - Delay between two sampling phases
  * @{
  */
#define ADC_TWOSAMPLINGDELAY_1CYCLE        (LL_ADC_MULTI_TWOSMP_DELAY_1CYCLE_5)   /*!< ADC multimode delay between two sampling phases: 1 ADC clock cycle */
#define ADC_TWOSAMPLINGDELAY_2CYCLES       (LL_ADC_MULTI_TWOSMP_DELAY_2CYCLES_5)  /*!< ADC multimode delay between two sampling phases: 2 ADC clock cycles */
#define ADC_TWOSAMPLINGDELAY_3CYCLES       (LL_ADC_MULTI_TWOSMP_DELAY_3CYCLES_5)  /*!< ADC multimode delay between two sampling phases: 3 ADC clock cycles */
#define ADC_TWOSAMPLINGDELAY_4CYCLES       (LL_ADC_MULTI_TWOSMP_DELAY_4CYCLES_5)  /*!< ADC multimode delay between two sampling phases: 4 ADC clock cycles */
#define ADC_TWOSAMPLINGDELAY_5CYCLES       (LL_ADC_MULTI_TWOSMP_DELAY_5CYCLES_5)  /*!< ADC multimode delay between two sampling phases: 5 ADC clock cycles */
#define ADC_TWOSAMPLINGDELAY_6CYCLES       (LL_ADC_MULTI_TWOSMP_DELAY_6CYCLES_5)  /*!< ADC multimode delay between two sampling phases: 6 ADC clock cycles */
#define ADC_TWOSAMPLINGDELAY_7CYCLES       (LL_ADC_MULTI_TWOSMP_DELAY_7CYCLES_5)  /*!< ADC multimode delay between two sampling phases: 7 ADC clock cycles */
#define ADC_TWOSAMPLINGDELAY_8CYCLES       (LL_ADC_MULTI_TWOSMP_DELAY_8CYCLES)   /*!< ADC multimode delay between two sampling phases: 8 ADC clock cycles */
#define ADC_TWOSAMPLINGDELAY_9CYCLES       (LL_ADC_MULTI_TWOSMP_DELAY_9CYCLES)   /*!< ADC multimode delay between two sampling phases: 9 ADC clock cycles */
/**
  * @}
  */

/**
  * @}
  */

/** @defgroup ADC_HAL_EC_GROUPS  ADC instance - Groups
  * @{
  */
#define ADC_REGULAR_GROUP                  (LL_ADC_GROUP_REGULAR)           /*!< ADC group regular (available on all STM32 devices) */
#define ADC_INJECTED_GROUP                 (LL_ADC_GROUP_INJECTED)          /*!< ADC group injected (not available on all STM32 devices)*/
#define ADC_REGULAR_INJECTED_GROUP         (LL_ADC_GROUP_REGULAR_INJECTED)  /*!< ADC both groups regular and injected */
/**
  * @}
  */

/** @defgroup ADC_CFGR_fields ADCx CFGR fields
  * @{
  */
#define ADC_CFGR_FIELDS    (ADC_CFGR_AWD1CH  | ADC_CFGR_JAUTO   | ADC_CFGR_JAWD1EN |\
                            ADC_CFGR_AWD1EN  | ADC_CFGR_AWD1SGL | ADC_CFGR_JQM     |\
                            ADC_CFGR_JDISCEN | ADC_CFGR_DISCNUM | ADC_CFGR_DISCEN  |\
                            ADC_CFGR_AUTDLY  | ADC_CFGR_CONT    | ADC_CFGR_OVRMOD  |\
                            ADC_CFGR_EXTEN   | ADC_CFGR_EXTSEL  | ADC_CFGR_ALIGN   |\
                            ADC_CFGR_RES     | ADC_CFGR_DMACFG  | ADC_CFGR_DMAEN   )
/**
  * @}
  */

/** @defgroup ADC_SMPR1_fields ADCx SMPR1 fields
  * @{
  */
#define ADC_SMPR1_FIELDS    (ADC_SMPR1_SMP9 | ADC_SMPR1_SMP8 | ADC_SMPR1_SMP7 |\
                             ADC_SMPR1_SMP6 | ADC_SMPR1_SMP5 | ADC_SMPR1_SMP4 |\
                             ADC_SMPR1_SMP3 | ADC_SMPR1_SMP2 | ADC_SMPR1_SMP1 |\
                             ADC_SMPR1_SMP0)
/**
  * @}
  */

/** @defgroup ADC_CFGR_fields_2 ADCx CFGR sub fields
  * @{
  */
/* ADC_CFGR fields of parameters that can be updated when no conversion
   (neither regular nor injected) is on-going  */
#define ADC_CFGR_FIELDS_2  ((uint32_t)(ADC_CFGR_DMNGT | ADC_CFGR_AUTDLY))
/**
  * @}
  */
#if defined(ADC_VER_V5_V90)
/** @defgroup ADC_CFGR_fields_2 ADCx CFGR sub fields
  * @{
  */
/* ADC_CFGR fields of parameters that can be updated when no conversion
   (neither regular nor injected) is on-going  */
#define ADC3_CFGR_FIELDS_2  ((ADC3_CFGR_DMACFG | ADC_CFGR_AUTDLY))
/**
  * @}
  */
#endif

#if defined(DFSDM1_Channel0)
/** @defgroup ADC_HAL_EC_REG_DFSDM_TRANSFER ADC group regular - DFSDM transfer of ADC conversion data
  * @{
  */
#define ADC_DFSDM_MODE_DISABLE     (0x00000000UL)                     /*!< ADC conversions are not transferred by DFSDM. */
#define ADC_DFSDM_MODE_ENABLE      (LL_ADC_REG_DFSDM_TRANSFER_ENABLE) /*!< ADC conversion data are transferred to DFSDM for post processing. The ADC conversion data format must be 16-bit signed and right aligned, refer to reference manual. DFSDM transfer cannot be used if DMA transfer is enabled. */
/**
  * @}
  */
#endif

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/

/** @defgroup ADCEx_Exported_Macro ADC Extended Exported Macros
  * @{
  */

/** @brief  Force ADC instance in multimode mode independent (multimode disable).
  * @note   This macro must be used only in case of transition from multimode
  *         to mode independent and in case of unknown previous state,
  *         to ensure ADC configuration is in mode independent.
  * @note   Standard way of multimode configuration change is done from
  *         HAL ADC handle of ADC master using function
  *         "HAL_ADCEx_MultiModeConfigChannel(..., ADC_MODE_INDEPENDENT)" )".
  *         Usage of this macro is not the Standard way of multimode
  *         configuration and can lead to have HAL ADC handles status
  *         misaligned. Usage of this macro must be limited to cases
  *         mentioned above.
  * @param __HANDLE__ ADC handle.
  * @retval None
  */
#define ADC_FORCE_MODE_INDEPENDENT(__HANDLE__)                                 \
  LL_ADC_SetMultimode(__LL_ADC_COMMON_INSTANCE((__HANDLE__)->Instance), LL_ADC_MULTI_INDEPENDENT)

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/

/** @defgroup ADCEx_Private_Macro_internal_HAL_driver ADC Extended Private Macros
  * @{
  */
/* Macro reserved for internal HAL driver usage, not intended to be used in   */
/* code of final user.                                                        */

/**
  * @brief Test if conversion trigger of injected group is software start
  *        or external trigger.
  * @param __HANDLE__ ADC handle.
  * @retval SET (software start) or RESET (external trigger).
  */
#define ADC_IS_SOFTWARE_START_INJECTED(__HANDLE__)                             \
  (((__HANDLE__)->Instance->JSQR & ADC_JSQR_JEXTEN) == 0UL)

/**
  * @brief Check if conversion is on going on regular or injected groups.
  * @param __HANDLE__ ADC handle.
  * @retval SET (conversion is on going) or RESET (no conversion is on going).
  */
#define ADC_IS_CONVERSION_ONGOING_REGULAR_INJECTED(__HANDLE__)                       \
       (( (((__HANDLE__)->Instance->CR) & (ADC_CR_ADSTART | ADC_CR_JADSTART)) == 0UL \
        ) ? RESET : SET)

/**
  * @brief Check if conversion is on going on injected group.
  * @param __HANDLE__ ADC handle.
  * @retval Value "0" (no conversion is on going) or value "1" (conversion is on going)
  */
#define ADC_IS_CONVERSION_ONGOING_INJECTED(__HANDLE__)                         \
  (LL_ADC_INJ_IsConversionOngoing((__HANDLE__)->Instance))


#if defined (ADC3)
/**
  * @brief Check whether or not ADC is independent.
  * @param __HANDLE__ ADC handle.
  * @note  When multimode feature is not available, the macro always returns SET.
  * @retval SET (ADC is independent) or RESET (ADC is not).
  */

#define ADC_IS_INDEPENDENT(__HANDLE__)    \
  ( ( ( ((__HANDLE__)->Instance) == ADC3) \
    )?                                    \
     SET                                  \
     :                                    \
     RESET                                \
  )
#endif

/**
  * @brief Set the selected injected Channel rank.
  * @param __CHANNELNB__ Channel number.
  * @param __RANKNB__ Rank number.
  * @retval None
  */
#define ADC_JSQR_RK(__CHANNELNB__, __RANKNB__) ((((__CHANNELNB__) & ADC_CHANNEL_ID_NUMBER_MASK) >> ADC_CHANNEL_ID_NUMBER_BITOFFSET_POS) << ((__RANKNB__) & ADC_INJ_RANK_ID_JSQR_MASK))

/**
  * @brief Configure ADC injected context queue
  * @param __INJECT_CONTEXT_QUEUE_MODE__ Injected context queue mode.
  * @retval None
  */
#define ADC_CFGR_INJECT_CONTEXT_QUEUE(__INJECT_CONTEXT_QUEUE_MODE__) ((__INJECT_CONTEXT_QUEUE_MODE__) << ADC_CFGR_JQM_Pos)

/**
  * @brief Configure ADC discontinuous conversion mode for injected group
  * @param __INJECT_DISCONTINUOUS_MODE__ Injected discontinuous mode.
  * @retval None
  */
#define ADC_CFGR_INJECT_DISCCONTINUOUS(__INJECT_DISCONTINUOUS_MODE__) ((__INJECT_DISCONTINUOUS_MODE__) <<  ADC_CFGR_JDISCEN_Pos)

/**
  * @brief Configure ADC discontinuous conversion mode for regular group
  * @param __REG_DISCONTINUOUS_MODE__ Regular discontinuous mode.
  * @retval None
  */
#define ADC_CFGR_REG_DISCONTINUOUS(__REG_DISCONTINUOUS_MODE__) ((__REG_DISCONTINUOUS_MODE__) << ADC_CFGR_DISCEN_Pos)

/**
  * @brief Configure the number of discontinuous conversions for regular group.
  * @param __NBR_DISCONTINUOUS_CONV__ Number of discontinuous conversions.
  * @retval None
  */
#define ADC_CFGR_DISCONTINUOUS_NUM(__NBR_DISCONTINUOUS_CONV__) (((__NBR_DISCONTINUOUS_CONV__) - 1UL) << ADC_CFGR_DISCNUM_Pos)

/**
  * @brief Configure the ADC auto delay mode.
  * @param __AUTOWAIT__ Auto delay bit enable or disable.
  * @retval None
  */
#define ADC_CFGR_AUTOWAIT(__AUTOWAIT__) ((__AUTOWAIT__) << ADC_CFGR_AUTDLY_Pos)

/**
  * @brief Configure ADC continuous conversion mode.
  * @param __CONTINUOUS_MODE__ Continuous mode.
  * @retval None
  */
#define ADC_CFGR_CONTINUOUS(__CONTINUOUS_MODE__) ((__CONTINUOUS_MODE__) << ADC_CFGR_CONT_Pos)

/**
  * @brief Enable the ADC DMA continuous request.
  * @param __DMACONTREQ_MODE__: DMA continuous request mode.
  * @retval None
  */
#define ADC_CFGR_DMACONTREQ(__DMACONTREQ_MODE__) ((__DMACONTREQ_MODE__))

#if defined(ADC_VER_V5_V90)
/**
  * @brief Configure the ADC DMA continuous request.
  * @param __DMACONTREQ_MODE__ DMA continuous request mode.
  * @retval None
  */
#define ADC3_CFGR_DMACONTREQ(__DMACONTREQ_MODE__) ((__DMACONTREQ_MODE__) <<  ADC3_CFGR_DMACFG_Pos)
#endif
/**
  * @brief Configure the channel number into offset OFRx register.
  * @param __CHANNEL__ ADC Channel.
  * @retval None
  */
#define ADC_OFR_CHANNEL(__CHANNEL__) ((__CHANNEL__) << ADC_OFR1_OFFSET1_CH_Pos)

/**
  * @brief Configure the channel number into differential mode selection register.
  * @param __CHANNEL__ ADC Channel.
  * @retval None
  */
#define ADC_DIFSEL_CHANNEL(__CHANNEL__) (1UL << (__CHANNEL__))

/**
  * @brief Configure calibration factor in differential mode to be set into calibration register.
  * @param __CALIBRATION_FACTOR__ Calibration factor value.
  * @retval None
  */
#define ADC_CALFACT_DIFF_SET(__CALIBRATION_FACTOR__) (((__CALIBRATION_FACTOR__) & (ADC_CALFACT_CALFACT_D_Pos >> ADC_CALFACT_CALFACT_D_Pos) ) << ADC_CALFACT_CALFACT_D_Pos)

/**
  * @brief Calibration factor in differential mode to be retrieved from calibration register.
  * @param __CALIBRATION_FACTOR__ Calibration factor value.
  * @retval None
  */
#define ADC_CALFACT_DIFF_GET(__CALIBRATION_FACTOR__) ((__CALIBRATION_FACTOR__) >> ADC_CALFACT_CALFACT_D_Pos)

/**
  * @brief Configure the analog watchdog high threshold into registers TR1, TR2 or TR3.
  * @param __THRESHOLD__ Threshold value.
  * @retval None
  */
#define ADC_TRX_HIGHTHRESHOLD(__THRESHOLD__) ((__THRESHOLD__) << 16UL)

/**
  * @brief Configure the ADC DMA continuous request for ADC multimode.
  * @param __DMACONTREQ_MODE__ DMA continuous request mode.
  * @retval None
  */
#define ADC_CCR_MULTI_DMACONTREQ(__DMACONTREQ_MODE__) ((__DMACONTREQ_MODE__) << ADC_CCR_DMACFG_Pos)

/**
  * @brief Shift the offset in function of the selected ADC resolution.
  * @note  Offset has to be left-aligned on bit 15, the LSB (right bits) are set to 0
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
#if defined(ADC_VER_V5_3)
#define ADC_OFFSET_SHIFT_RESOLUTION(__HANDLE__, __OFFSET__)                                                     \
        (                                                                                                       \
           ((((__HANDLE__)->Instance->CFGR) & ADC_CFGR_RES_2) == 0UL)                                           \
              ? ((__OFFSET__)<<(((((__HANDLE__)->Instance->CFGR) & ADC_CFGR_RES)>> 2UL)*2UL))                   \
               :                                                                                                \
               ((__OFFSET__)<<(((((__HANDLE__)->Instance->CFGR) & (ADC_CFGR_RES & 0xFFFFFFF3UL))>> 2UL )*2UL))  \
        )
#else
#define ADC_OFFSET_SHIFT_RESOLUTION(__HANDLE__, __OFFSET__)                                                     \
        (((DBGMCU->IDCODE & 0xF0000000UL) == 0x10000000UL)                                                      \
          ? ((__OFFSET__)<<(((((__HANDLE__)->Instance->CFGR) & ADC_CFGR_RES)>> 2UL)*2UL))                       \
             :                                                                                                  \
            ((((__HANDLE__)->Instance->CFGR) & ADC_CFGR_RES_2) == 0UL)                                          \
              ? ((__OFFSET__)<<(((((__HANDLE__)->Instance->CFGR) & ADC_CFGR_RES)>> 2UL)*2UL))                   \
               :                                                                                                \
               ((__OFFSET__)<<(((((__HANDLE__)->Instance->CFGR) & (ADC_CFGR_RES & 0xFFFFFFF3UL))>> 2UL )*2UL))  \
        )
#endif /* ADC_VER_V5_3 */

#if defined(ADC_VER_V5_V90)
#define ADC3_OFFSET_SHIFT_RESOLUTION(__HANDLE__, __OFFSET__) \
        ((__OFFSET__) << ((((__HANDLE__)->Instance->CFGR & ADC3_CFGR_RES) >> 3UL) * 2UL))

#endif /* ADC_VER_V5_V90 */

/**
  * @brief Shift the AWD1 threshold in function of the selected ADC resolution.
  * @note  Thresholds have to be left-aligned on bit 15, the LSB (right bits) are set to 0.
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
#if defined(ADC_VER_V5_3)
#if defined(ADC_VER_V5_V90)
#define ADC_AWD1THRESHOLD_SHIFT_RESOLUTION(__HANDLE__, __THRESHOLD__)                                           \
        (  ((__HANDLE__)->Instance == ADC3)                                                                       \
             ?((__THRESHOLD__)<<(((((__HANDLE__)->Instance->CFGR) & ADC3_CFGR_RES)>> 3UL)*2UL))                     \
               :                                                                                                   \
              ((((__HANDLE__)->Instance->CFGR) & ADC_CFGR_RES_2) == 0UL)                                          \
               ?((__THRESHOLD__)<<(((((__HANDLE__)->Instance->CFGR) & ADC_CFGR_RES)>> 2UL)*2UL))                    \
                :                                                                                                   \
                ((__THRESHOLD__)<<(((((__HANDLE__)->Instance->CFGR) & (ADC_CFGR_RES & 0xFFFFFFF3UL))>> 2UL )*2UL))  \
        )
#else
#define ADC_AWD1THRESHOLD_SHIFT_RESOLUTION(__HANDLE__, __THRESHOLD__)                                             \
        (                                                                                                         \
           ((((__HANDLE__)->Instance->CFGR) & ADC_CFGR_RES_2) == 0UL)                                             \
            ? ((__THRESHOLD__)<<(((((__HANDLE__)->Instance->CFGR) & ADC_CFGR_RES)>> 2UL)*2UL))                    \
              :                                                                                                   \
              ((__THRESHOLD__)<<(((((__HANDLE__)->Instance->CFGR) & (ADC_CFGR_RES & 0xFFFFFFF3UL))>> 2UL )*2UL))  \
        )
#endif

#else
#define ADC_AWD1THRESHOLD_SHIFT_RESOLUTION(__HANDLE__, __THRESHOLD__)                                             \
        (((DBGMCU->IDCODE & 0xF0000000UL) == 0x10000000UL)                                                        \
         ? ((__THRESHOLD__)<<(((((__HANDLE__)->Instance->CFGR) & ADC_CFGR_RES)>> 2UL)*2UL))                       \
            :                                                                                                     \
           ((((__HANDLE__)->Instance->CFGR) & ADC_CFGR_RES_2) == 0UL)                                             \
            ? ((__THRESHOLD__)<<(((((__HANDLE__)->Instance->CFGR) & ADC_CFGR_RES)>> 2UL)*2UL))                    \
              :                                                                                                   \
              ((__THRESHOLD__)<<(((((__HANDLE__)->Instance->CFGR) & (ADC_CFGR_RES & 0xFFFFFFF3UL))>> 2UL )*2UL))  \
        )
#endif /* ADC_VER_V5_3 */

/**
  * @brief Shift the AWD2 and AWD3 threshold in function of the selected ADC resolution.
  * @note  Thresholds have to be left-aligned on bit 15, the LSB (right bits) are set to 0.
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
#if defined(ADC_VER_V5_3) || defined(ADC_VER_V5_V90)
#define ADC_AWD23THRESHOLD_SHIFT_RESOLUTION(__HANDLE__, __THRESHOLD__)                                           \
        (                                                                                                           \
            ((((__HANDLE__)->Instance->CFGR) & ADC_CFGR_RES_2) == 0UL)                                              \
              ? ((__THRESHOLD__)<<(((((__HANDLE__)->Instance->CFGR) & ADC_CFGR_RES)>> 2UL)*2UL))                    \
                :                                                                                                   \
                ((__THRESHOLD__)<<(((((__HANDLE__)->Instance->CFGR) & (ADC_CFGR_RES & 0xFFFFFFF3UL))>> 2UL )*2UL))  \
        )
#else
#define ADC_AWD23THRESHOLD_SHIFT_RESOLUTION(__HANDLE__, __THRESHOLD__)                                              \
        (((DBGMCU->IDCODE & 0xF0000000UL) == 0x10000000UL)                                                          \
          ? ((__THRESHOLD__)<<(((((__HANDLE__)->Instance->CFGR) & ADC_CFGR_RES)>> 2UL)*2UL))                        \
            :                                                                                                       \
            ((((__HANDLE__)->Instance->CFGR) & ADC_CFGR_RES_2) == 0UL)                                              \
              ? ((__THRESHOLD__)<<(((((__HANDLE__)->Instance->CFGR) & ADC_CFGR_RES)>> 2UL)*2UL))                    \
                :                                                                                                   \
                ((__THRESHOLD__)<<(((((__HANDLE__)->Instance->CFGR) & (ADC_CFGR_RES & 0xFFFFFFF3UL))>> 2UL )*2UL))  \
        )
#endif /* ADC_VER_V5_3 */
/**
  * @brief Clear Common Control Register.
  * @param __HANDLE__ ADC handle.
  * @retval None
  */
/**
  * @brief Report common register to ADC1 and ADC2
  * @param __HANDLE__: ADC handle
  * @retval Common control register
  */
#define ADC12_COMMON_REGISTER(__HANDLE__)   (ADC12_COMMON)
#if defined (ADC3)
/**
  * @brief Report common register to ADC3
  * @param __HANDLE__: ADC handle
  * @retval Common control register
  */
#define ADC3_COMMON_REGISTER(__HANDLE__)   (ADC3_COMMON)
#endif
/**
  * @brief Report Master Instance
  * @param __HANDLE__: ADC handle
  * @note return same instance if ADC of input handle is independent ADC
  * @retval Master Instance
  */
#if defined (ADC3)
#define ADC_MASTER_REGISTER(__HANDLE__)                                          \
  ( ( ((((__HANDLE__)->Instance) == ADC1) || (((__HANDLE__)->Instance) == ADC3)) \
    )?                                                                           \
     ((__HANDLE__)->Instance)                                                    \
     :                                                                           \
     (ADC1)                                                                      \
  )
#else
#define ADC_MASTER_REGISTER(__HANDLE__) ( (ADC1))
#endif

/**
  * @brief Check whether or not dual regular conversions are enabled
  * @param __HANDLE__: ADC handle
  * @retval SET (dual regular conversions are enabled) or RESET (ADC is independent or no dual regular conversions are enabled)
  */
#define ADC_IS_DUAL_REGULAR_CONVERSION_ENABLE(__HANDLE__)                        \
  ( ( ((((__HANDLE__)->Instance) == ADC1) || (((__HANDLE__)->Instance) == ADC2)) \
    )?                                                                           \
     ( ((ADC12_COMMON->CCR & ADC_CCR_DUAL) != ADC_MODE_INDEPENDENT)     &&       \
       ((ADC12_COMMON->CCR & ADC_CCR_DUAL) != ADC_DUALMODE_INJECSIMULT) &&       \
       ((ADC12_COMMON->CCR & ADC_CCR_DUAL) != ADC_DUALMODE_ALTERTRIG) )          \
     :                                                                           \
     RESET                                                                       \
  )

/**
  * @brief Verification of condition for ADC start conversion: ADC must be in non-MultiMode or MultiMode with handle of ADC master
  * @param __HANDLE__: ADC handle
  * @retval SET (non-MultiMode or Master handle) or RESET (handle of Slave ADC in MultiMode)
  */
#define ADC12_NONMULTIMODE_OR_MULTIMODEMASTER(__HANDLE__)                      \
  ( ( ((__HANDLE__)->Instance == ADC1) || ((__HANDLE__)->Instance == ADC2)     \
    )?                                                                         \
     SET                                                                       \
     :                                                                         \
     ((ADC12_COMMON->CCR & ADC_CCR_DUAL) == RESET)                             \
  )
#if defined (ADC3)
/**
  * @brief Verification of condition for ADC start conversion: ADC must be in non-MultiMode or MultiMode with handle of ADC master
  * @param __HANDLE__: ADC handle
  * @retval SET (non-MultiMode or Master handle) or RESET (handle of Slave ADC in MultiMode)
  */
#define ADC3_NONMULTIMODE_OR_MULTIMODEMASTER(__HANDLE__)                        \
  ( ( ((__HANDLE__)->Instance == ADC3)                                          \
    )?                                                                          \
     SET                                                                        \
     :                                                                          \
     ((ADC3_COMMON->CCR & ADC_CCR_DUAL) == RESET)                              \
  )
#endif
/**
  * @brief Ensure ADC Instance is Independent or Master, or is not Slave ADC with dual regular conversions enabled
  * @param __HANDLE__: ADC handle
  * @retval SET (Independent or Master, or Slave without dual regular conversions enabled) or RESET (Slave ADC with dual regular conversions enabled)
  */
#if defined (ADC3)
#define ADC_INDEPENDENT_OR_NONMULTIMODEREGULAR_SLAVE(__HANDLE__)            \
  ( ( ((__HANDLE__)->Instance == ADC1) || ((__HANDLE__)->Instance == ADC3)  \
    )?                                                                      \
     SET                                                                    \
     :                                                                      \
     ( ((ADC12_COMMON->CCR & ADC_CCR_DUAL) == ADC_MODE_INDEPENDENT)     ||  \
       ((ADC12_COMMON->CCR & ADC_CCR_DUAL) == ADC_DUALMODE_INJECSIMULT) ||  \
       ((ADC12_COMMON->CCR & ADC_CCR_DUAL) == ADC_DUALMODE_ALTERTRIG) ))
#else
#define ADC_INDEPENDENT_OR_NONMULTIMODEREGULAR_SLAVE(__HANDLE__)            \
  ( ( ((__HANDLE__)->Instance == ADC1)                                      \
    )?                                                                      \
     SET                                                                    \
     :                                                                      \
     ( ((ADC12_COMMON->CCR & ADC_CCR_DUAL) == ADC_MODE_INDEPENDENT)     ||  \
       ((ADC12_COMMON->CCR & ADC_CCR_DUAL) == ADC_DUALMODE_INJECSIMULT) ||  \
       ((ADC12_COMMON->CCR & ADC_CCR_DUAL) == ADC_DUALMODE_ALTERTRIG) ))
#endif

/**
  * @brief Ensure ADC Instance is Independent or Master, or is not Slave ADC with dual injected conversions enabled
  * @param __HANDLE__: ADC handle
  * @retval SET (non-MultiMode or Master, or Slave without dual injected conversions enabled) or RESET (Slave ADC with dual injected conversions enabled)
  */
#if defined (ADC3)
#define ADC_INDEPENDENT_OR_NONMULTIMODEINJECTED_SLAVE(__HANDLE__)          \
  ( ( ((__HANDLE__)->Instance == ADC1) || ((__HANDLE__)->Instance == ADC3) \
    )?                                                                     \
     SET                                                                   \
     :                                                                     \
     ( ((ADC12_COMMON->CCR & ADC_CCR_DUAL) == ADC_MODE_INDEPENDENT)    ||  \
       ((ADC12_COMMON->CCR & ADC_CCR_DUAL) == ADC_DUALMODE_REGSIMULT)  ||  \
       ((ADC12_COMMON->CCR & ADC_CCR_DUAL) == ADC_DUALMODE_INTERL) ))
#else
#define ADC_INDEPENDENT_OR_NONMULTIMODEINJECTED_SLAVE(__HANDLE__)          \
  ( ( ((__HANDLE__)->Instance == ADC1)                                     \
    )?                                                                     \
     SET                                                                   \
     :                                                                     \
     ( ((ADC12_COMMON->CCR & ADC_CCR_DUAL) == ADC_MODE_INDEPENDENT)    ||  \
       ((ADC12_COMMON->CCR & ADC_CCR_DUAL) == ADC_DUALMODE_REGSIMULT)  ||  \
       ((ADC12_COMMON->CCR & ADC_CCR_DUAL) == ADC_DUALMODE_INTERL) ))
#endif

#define ADC_CLEAR_COMMON_CONTROL_REGISTER(__HANDLE__) CLEAR_BIT(__LL_ADC_COMMON_INSTANCE((__HANDLE__)->Instance)->CCR, ADC_CCR_CKMODE    | \
                                                                                                      ADC_CCR_PRESC     | \
                                                                                                      ADC_CCR_VBATEN    | \
                                                                                                      ADC_CCR_TSEN      | \
                                                                                                      ADC_CCR_VREFEN    | \
                                                                                                      ADC_CCR_DAMDF     | \
                                                                                                      ADC_CCR_DELAY     | \
                                                                                                      ADC_CCR_DUAL  )

/**
  * @brief Set handle instance of the ADC slave associated to the ADC master.
  * @param __HANDLE_MASTER__ ADC master handle.
  * @param __HANDLE_SLAVE__ ADC slave handle.
  * @note if __HANDLE_MASTER__ is the handle of a slave ADC (ADC2) or an independent ADC, __HANDLE_SLAVE__ instance is set to NULL.
  * @retval None
  */
#define ADC_MULTI_SLAVE(__HANDLE_MASTER__, __HANDLE_SLAVE__)             \
  ( (((__HANDLE_MASTER__)->Instance == ADC1)) ? ((__HANDLE_SLAVE__)->Instance = ADC2) : ((__HANDLE_SLAVE__)->Instance = NULL) )


/**
  * @brief Verify the ADC instance connected to the temperature sensor.
  * @param __HANDLE__ ADC handle.
  * @retval SET (ADC instance is valid) or RESET (ADC instance is invalid)
  */
#if defined(ADC3)
#define ADC_TEMPERATURE_SENSOR_INSTANCE(__HANDLE__)  (((__HANDLE__)->Instance) == ADC3)
#else
#define ADC_TEMPERATURE_SENSOR_INSTANCE(__HANDLE__)  (((__HANDLE__)->Instance) == ADC2)
#endif

/**
  * @brief Verify the ADC instance connected to the battery voltage VBAT.
  * @param __HANDLE__ ADC handle.
  * @retval SET (ADC instance is valid) or RESET (ADC instance is invalid)
  */
#if defined(ADC3)
#define ADC_BATTERY_VOLTAGE_INSTANCE(__HANDLE__)  (((__HANDLE__)->Instance) == ADC3)
#else
#define ADC_BATTERY_VOLTAGE_INSTANCE(__HANDLE__)  (((__HANDLE__)->Instance) == ADC2)
#endif

/**
  * @brief Verify the ADC instance connected to the internal voltage reference VREFINT.
  * @param __HANDLE__ ADC handle.
  * @retval SET (ADC instance is valid) or RESET (ADC instance is invalid)
  */
#if defined(ADC3)
#define ADC_VREFINT_INSTANCE(__HANDLE__)  (((__HANDLE__)->Instance) == ADC3)
#else
#define ADC_VREFINT_INSTANCE(__HANDLE__)  (((__HANDLE__)->Instance) == ADC2)
#endif

/**
  * @brief Verify the length of scheduled injected conversions group.
  * @param __LENGTH__ number of programmed conversions.
  * @retval SET (__LENGTH__ is within the maximum number of possible programmable injected conversions) or RESET (__LENGTH__ is null or too large)
  */
#define IS_ADC_INJECTED_NB_CONV(__LENGTH__) (((__LENGTH__) >= (1U)) && ((__LENGTH__) <= (4U)))

/**
  * @brief Calibration factor size verification (11 bits maximum).
  * @param __CALIBRATION_FACTOR__ Calibration factor value.
  * @retval SET (__CALIBRATION_FACTOR__ is within the authorized size) or RESET (__CALIBRATION_FACTOR__ is too large)
  */
#define IS_ADC_CALFACT(__CALIBRATION_FACTOR__) ((__CALIBRATION_FACTOR__) <= (0x7FFU))

#if defined(ADC_VER_V5_V90)
/**
  * @brief Calibration factor size verification (7 bits maximum on ADC3).
  * @param __CALIBRATION_FACTOR__ Calibration factor value.
  * @retval SET (__CALIBRATION_FACTOR__ is within the authorized size) or RESET (__CALIBRATION_FACTOR__ is too large)
  */
#define IS_ADC_CALFACT_ADC3(__CALIBRATION_FACTOR__) ((__CALIBRATION_FACTOR__) <= (0x7FU))
#endif

/**
  * @brief Verify the ADC channel setting.
  * @param __CHANNEL__ programmed ADC channel.
  * @retval SET (__CHANNEL__ is valid) or RESET (__CHANNEL__ is invalid)
  */
#define IS_ADC_CHANNEL(__CHANNEL__) (((__CHANNEL__) == ADC_CHANNEL_0)           || \
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
                                     ((__CHANNEL__) == ADC_CHANNEL_VBAT)        || \
                                     ((__CHANNEL__) == ADC_CHANNEL_DAC1CH1_ADC2)|| \
                                     ((__CHANNEL__) == ADC_CHANNEL_DAC1CH2_ADC2)|| \
                                     ((__CHANNEL__) == ADC_CHANNEL_VREFINT)       )

/**
  * @brief Verify the ADC channel setting in differential mode for ADC1.
  * @param __CHANNEL__: programmed ADC channel.
  * @retval SET (__CHANNEL__ is valid) or RESET (__CHANNEL__ is invalid)
  */
#define IS_ADC1_DIFF_CHANNEL(__CHANNEL__) (((__CHANNEL__) == ADC_CHANNEL_1)      || \
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
#define IS_ADC2_DIFF_CHANNEL(__CHANNEL__) (((__CHANNEL__) == ADC_CHANNEL_1)      || \
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
#define IS_ADC3_DIFF_CHANNEL(__CHANNEL__) (((__CHANNEL__) == ADC_CHANNEL_1)      || \
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
  * @brief Verify the ADC single-ended input or differential mode setting.
  * @param __SING_DIFF__ programmed channel setting.
  * @retval SET (__SING_DIFF__ is valid) or RESET (__SING_DIFF__ is invalid)
  */
#define IS_ADC_SINGLE_DIFFERENTIAL(__SING_DIFF__) (((__SING_DIFF__) == ADC_SINGLE_ENDED)      || \
                                                   ((__SING_DIFF__) == ADC_DIFFERENTIAL_ENDED)  )

/**
  * @brief Verify the ADC offset management setting.
  * @param __OFFSET_NUMBER__ ADC offset management.
  * @retval SET (__OFFSET_NUMBER__ is valid) or RESET (__OFFSET_NUMBER__ is invalid)
  */
#define IS_ADC_OFFSET_NUMBER(__OFFSET_NUMBER__) (((__OFFSET_NUMBER__) == ADC_OFFSET_NONE) || \
                                                 ((__OFFSET_NUMBER__) == ADC_OFFSET_1)    || \
                                                 ((__OFFSET_NUMBER__) == ADC_OFFSET_2)    || \
                                                 ((__OFFSET_NUMBER__) == ADC_OFFSET_3)    || \
                                                 ((__OFFSET_NUMBER__) == ADC_OFFSET_4)      )
#if defined(ADC_VER_V5_V90)
/**
  * @brief Verify the ADC offset sign setting.
  * @param __OFFSET_SIGN__ ADC offset sign.
  * @retval SET (__OFFSET_SIGN__ is valid) or RESET (__OFFSET_SIGN__ is invalid)
  */
#define IS_ADC3_OFFSET_SIGN(__OFFSET_SIGN__)     (((__OFFSET_SIGN__) == ADC3_OFFSET_SIGN_NEGATIVE) || \
                                                  ((__OFFSET_SIGN__) == ADC3_OFFSET_SIGN_POSITIVE)    )
#endif  /* ADC_VER_V5_V90 */
/**
  * @brief Verify the ADC injected channel setting.
  * @param __CHANNEL__ programmed ADC injected channel.
  * @retval SET (__CHANNEL__ is valid) or RESET (__CHANNEL__ is invalid)
  */
#define IS_ADC_INJECTED_RANK(__CHANNEL__) (((__CHANNEL__) == ADC_INJECTED_RANK_1) || \
                                           ((__CHANNEL__) == ADC_INJECTED_RANK_2) || \
                                           ((__CHANNEL__) == ADC_INJECTED_RANK_3) || \
                                           ((__CHANNEL__) == ADC_INJECTED_RANK_4)   )

/**
  * @brief Verify the ADC injected conversions external trigger.
  * @param __INJTRIG__ programmed ADC injected conversions external trigger.
  * @retval SET (__INJTRIG__ is a valid value) or RESET (__INJTRIG__ is invalid)
  */
#if defined (HRTIM1)
#define IS_ADC_EXTTRIGINJEC(__INJTRIG__) (((__INJTRIG__) == ADC_EXTERNALTRIGINJEC_T1_TRGO)     || \
                                          ((__INJTRIG__) == ADC_EXTERNALTRIGINJEC_T1_CC4)      || \
                                          ((__INJTRIG__) == ADC_EXTERNALTRIGINJEC_T2_TRGO)     || \
                                          ((__INJTRIG__) == ADC_EXTERNALTRIGINJEC_T2_CC1)      || \
                                          ((__INJTRIG__) == ADC_EXTERNALTRIGINJEC_T3_CC4)      || \
                                          ((__INJTRIG__) == ADC_EXTERNALTRIGINJEC_T4_TRGO)     || \
                                          ((__INJTRIG__) == ADC_EXTERNALTRIGINJEC_EXT_IT15)    || \
                                          ((__INJTRIG__) == ADC_EXTERNALTRIGINJEC_T8_CC4)      || \
                                          ((__INJTRIG__) == ADC_EXTERNALTRIGINJEC_T1_TRGO2)    || \
                                          ((__INJTRIG__) == ADC_EXTERNALTRIGINJEC_T8_TRGO)     || \
                                          ((__INJTRIG__) == ADC_EXTERNALTRIGINJEC_T8_TRGO2)    || \
                                          ((__INJTRIG__) == ADC_EXTERNALTRIGINJEC_T3_CC3)      || \
                                          ((__INJTRIG__) == ADC_EXTERNALTRIGINJEC_T3_TRGO)     || \
                                          ((__INJTRIG__) == ADC_EXTERNALTRIGINJEC_T3_CC1)      || \
                                          ((__INJTRIG__) == ADC_EXTERNALTRIGINJEC_T6_TRGO)     || \
                                          ((__INJTRIG__) == ADC_EXTERNALTRIGINJEC_T15_TRGO)    || \
                                          ((__INJTRIG__) == ADC_EXTERNALTRIGINJEC_HR1_ADCTRG2) || \
                                          ((__INJTRIG__) == ADC_EXTERNALTRIGINJEC_HR1_ADCTRG4) || \
                                          ((__INJTRIG__) == ADC_EXTERNALTRIGINJEC_LPTIM1_OUT)  || \
                                          ((__INJTRIG__) == ADC_EXTERNALTRIGINJEC_LPTIM2_OUT)  || \
                                          ((__INJTRIG__) == ADC_EXTERNALTRIGINJEC_LPTIM3_OUT)  || \
                                                                                          \
                                           ((__INJTRIG__) == ADC_SOFTWARE_START)                   )
#else
#define IS_ADC_EXTTRIGINJEC(__INJTRIG__) (((__INJTRIG__) == ADC_EXTERNALTRIGINJEC_T1_TRGO)     || \
                                          ((__INJTRIG__) == ADC_EXTERNALTRIGINJEC_T1_CC4)      || \
                                          ((__INJTRIG__) == ADC_EXTERNALTRIGINJEC_T2_TRGO)     || \
                                          ((__INJTRIG__) == ADC_EXTERNALTRIGINJEC_T2_CC1)      || \
                                          ((__INJTRIG__) == ADC_EXTERNALTRIGINJEC_T3_CC4)      || \
                                          ((__INJTRIG__) == ADC_EXTERNALTRIGINJEC_T4_TRGO)     || \
                                          ((__INJTRIG__) == ADC_EXTERNALTRIGINJEC_EXT_IT15)    || \
                                          ((__INJTRIG__) == ADC_EXTERNALTRIGINJEC_T8_CC4)      || \
                                          ((__INJTRIG__) == ADC_EXTERNALTRIGINJEC_T1_TRGO2)    || \
                                          ((__INJTRIG__) == ADC_EXTERNALTRIGINJEC_T8_TRGO)     || \
                                          ((__INJTRIG__) == ADC_EXTERNALTRIGINJEC_T8_TRGO2)    || \
                                          ((__INJTRIG__) == ADC_EXTERNALTRIGINJEC_T3_CC3)      || \
                                          ((__INJTRIG__) == ADC_EXTERNALTRIGINJEC_T3_TRGO)     || \
                                          ((__INJTRIG__) == ADC_EXTERNALTRIGINJEC_T3_CC1)      || \
                                          ((__INJTRIG__) == ADC_EXTERNALTRIGINJEC_T6_TRGO)     || \
                                          ((__INJTRIG__) == ADC_EXTERNALTRIGINJEC_T15_TRGO)    || \
                                          ((__INJTRIG__) == ADC_EXTERNALTRIGINJEC_LPTIM1_OUT)  || \
                                          ((__INJTRIG__) == ADC_EXTERNALTRIGINJEC_LPTIM2_OUT)  || \
                                          ((__INJTRIG__) == ADC_EXTERNALTRIGINJEC_LPTIM3_OUT)  || \
                                                                                          \
                                           ((__INJTRIG__) == ADC_SOFTWARE_START)                   )
#endif /* HRTIM */
/**
  * @brief Verify the ADC edge trigger setting for injected group.
  * @param __EDGE__ programmed ADC edge trigger setting.
  * @retval SET (__EDGE__ is a valid value) or RESET (__EDGE__ is invalid)
  */
#define IS_ADC_EXTTRIGINJEC_EDGE(__EDGE__) (((__EDGE__) == ADC_EXTERNALTRIGINJECCONV_EDGE_NONE)        || \
                                           ((__EDGE__) == ADC_EXTERNALTRIGINJECCONV_EDGE_RISING)       || \
                                           ((__EDGE__) == ADC_EXTERNALTRIGINJECCONV_EDGE_FALLING)      || \
                                           ((__EDGE__) == ADC_EXTERNALTRIGINJECCONV_EDGE_RISINGFALLING) )

/**
  * @brief Verify the ADC multimode setting.
  * @param __MODE__ programmed ADC multimode setting.
  * @retval SET (__MODE__ is valid) or RESET (__MODE__ is invalid)
  */
#define IS_ADC_MULTIMODE(__MODE__) (((__MODE__) == ADC_MODE_INDEPENDENT)          || \
                               ((__MODE__) == ADC_DUALMODE_REGSIMULT_INJECSIMULT) || \
                               ((__MODE__) == ADC_DUALMODE_REGSIMULT_ALTERTRIG)   || \
                               ((__MODE__) == ADC_DUALMODE_REGINTERL_INJECSIMULT) || \
                               ((__MODE__) == ADC_DUALMODE_INJECSIMULT)           || \
                               ((__MODE__) == ADC_DUALMODE_REGSIMULT)             || \
                               ((__MODE__) == ADC_DUALMODE_INTERL)                || \
                               ((__MODE__) == ADC_DUALMODE_ALTERTRIG)               )

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
  * @param __DELAY__ programmed ADC multimode delay setting.
  * @retval SET (__DELAY__ is a valid value) or RESET (__DELAY__ is invalid)
  */
#define IS_ADC_SAMPLING_DELAY(__DELAY__) (((__DELAY__) == ADC_TWOSAMPLINGDELAY_1CYCLE)   || \
                                          ((__DELAY__) == ADC_TWOSAMPLINGDELAY_2CYCLES)  || \
                                          ((__DELAY__) == ADC_TWOSAMPLINGDELAY_3CYCLES)  || \
                                          ((__DELAY__) == ADC_TWOSAMPLINGDELAY_4CYCLES)  || \
                                          ((__DELAY__) == ADC_TWOSAMPLINGDELAY_5CYCLES)  || \
                                          ((__DELAY__) == ADC_TWOSAMPLINGDELAY_6CYCLES)  || \
                                          ((__DELAY__) == ADC_TWOSAMPLINGDELAY_7CYCLES)  || \
                                          ((__DELAY__) == ADC_TWOSAMPLINGDELAY_8CYCLES)  || \
                                          ((__DELAY__) == ADC_TWOSAMPLINGDELAY_9CYCLES)    )

/**
  * @brief Verify the ADC analog watchdog setting.
  * @param __WATCHDOG__ programmed ADC analog watchdog setting.
  * @retval SET (__WATCHDOG__ is valid) or RESET (__WATCHDOG__ is invalid)
  */
#define IS_ADC_ANALOG_WATCHDOG_NUMBER(__WATCHDOG__) (((__WATCHDOG__) == ADC_ANALOGWATCHDOG_1) || \
                                                     ((__WATCHDOG__) == ADC_ANALOGWATCHDOG_2) || \
                                                     ((__WATCHDOG__) == ADC_ANALOGWATCHDOG_3)   )

/**
  * @brief Verify the ADC analog watchdog mode setting.
  * @param __WATCHDOG_MODE__ programmed ADC analog watchdog mode setting.
  * @retval SET (__WATCHDOG_MODE__ is valid) or RESET (__WATCHDOG_MODE__ is invalid)
  */
#define IS_ADC_ANALOG_WATCHDOG_MODE(__WATCHDOG_MODE__) (((__WATCHDOG_MODE__) == ADC_ANALOGWATCHDOG_NONE)             || \
                                                        ((__WATCHDOG_MODE__) == ADC_ANALOGWATCHDOG_SINGLE_REG)       || \
                                                        ((__WATCHDOG_MODE__) == ADC_ANALOGWATCHDOG_SINGLE_INJEC)     || \
                                                        ((__WATCHDOG_MODE__) == ADC_ANALOGWATCHDOG_SINGLE_REGINJEC)  || \
                                                        ((__WATCHDOG_MODE__) == ADC_ANALOGWATCHDOG_ALL_REG)          || \
                                                        ((__WATCHDOG_MODE__) == ADC_ANALOGWATCHDOG_ALL_INJEC)        || \
                                                        ((__WATCHDOG_MODE__) == ADC_ANALOGWATCHDOG_ALL_REGINJEC)       )

#if defined(ADC_VER_V5_V90)
/**
  * @brief Verify the ADC analog watchdog filtering setting.
  * @param __FILTERING_MODE__ programmed ADC analog watchdog mode setting.
  * @retval SET (__FILTERING_MODE__ is valid) or RESET (__FILTERING_MODE__ is invalid)
  */
#define IS_ADC_ANALOG_WATCHDOG_FILTERING_MODE_ADC3(__FILTERING_MODE__)  (((__FILTERING_MODE__) == ADC3_AWD_FILTERING_NONE)            || \
                                                                         ((__FILTERING_MODE__) == ADC3_AWD_FILTERING_2SAMPLES)        || \
                                                                         ((__FILTERING_MODE__) == ADC3_AWD_FILTERING_3SAMPLES)        || \
                                                                         ((__FILTERING_MODE__) == ADC3_AWD_FILTERING_4SAMPLES)        || \
                                                                         ((__FILTERING_MODE__) == ADC3_AWD_FILTERING_5SAMPLES)        || \
                                                                         ((__FILTERING_MODE__) == ADC3_AWD_FILTERING_6SAMPLES)        || \
                                                                         ((__FILTERING_MODE__) == ADC3_AWD_FILTERING_7SAMPLES)        || \
                                                                         ((__FILTERING_MODE__) == ADC3_AWD_FILTERING_8SAMPLES)           )

#endif /* ADC_VER_V5_V90 */

/**
  * @brief Verify the ADC conversion (regular or injected or both).
  * @param __CONVERSION__ ADC conversion group.
  * @retval SET (__CONVERSION__ is valid) or RESET (__CONVERSION__ is invalid)
  */
#define IS_ADC_CONVERSION_GROUP(__CONVERSION__) (((__CONVERSION__) == ADC_REGULAR_GROUP)     || \
                                             ((__CONVERSION__) == ADC_INJECTED_GROUP)        || \
                                             ((__CONVERSION__) == ADC_REGULAR_INJECTED_GROUP)  )

/**
  * @brief Verify the ADC event type.
  * @param __EVENT__ ADC event.
  * @retval SET (__EVENT__ is valid) or RESET (__EVENT__ is invalid)
  */
#define IS_ADC_EVENT_TYPE(__EVENT__) (((__EVENT__) == ADC_EOSMP_EVENT) || \
                                     ((__EVENT__) == ADC_AWD_EVENT)    || \
                                     ((__EVENT__) == ADC_AWD2_EVENT)   || \
                                     ((__EVENT__) == ADC_AWD3_EVENT)   || \
                                     ((__EVENT__) == ADC_OVR_EVENT)    || \
                                     ((__EVENT__) == ADC_JQOVF_EVENT)  )

/**
  * @brief Verify the ADC oversampling ratio.
  * @param RATIO: programmed ADC oversampling ratio.
  * @retval SET (RATIO is a valid value) or RESET (RATIO is invalid)
  */
#define IS_ADC_OVERSAMPLING_RATIO(RATIO)  (((RATIO) >= 1UL) && ((RATIO) <= 1024UL))

#if defined(ADC_VER_V5_V90)
/**
  * @brief Verify the ADC3 oversampling ratio.
  * @param __RATIO__ programmed ADC oversampling ratio.
  * @retval SET (__RATIO__ is a valid value) or RESET (__RATIO__ is invalid)
  */
#define IS_ADC_OVERSAMPLING_RATIO_ADC3(__RATIO__)    (((__RATIO__) == ADC3_OVERSAMPLING_RATIO_2   ) || \
                                                      ((__RATIO__) == ADC3_OVERSAMPLING_RATIO_4   ) || \
                                                      ((__RATIO__) == ADC3_OVERSAMPLING_RATIO_8   ) || \
                                                      ((__RATIO__) == ADC3_OVERSAMPLING_RATIO_16  ) || \
                                                      ((__RATIO__) == ADC3_OVERSAMPLING_RATIO_32  ) || \
                                                      ((__RATIO__) == ADC3_OVERSAMPLING_RATIO_64  ) || \
                                                      ((__RATIO__) == ADC3_OVERSAMPLING_RATIO_128 ) || \
                                                      ((__RATIO__) == ADC3_OVERSAMPLING_RATIO_256 ))
#endif  /* ADC_VER_V5_V90 */

/**
  * @brief Verify the ADC oversampling shift.
  * @param __SHIFT__ programmed ADC oversampling shift.
  * @retval SET (__SHIFT__ is a valid value) or RESET (__SHIFT__ is invalid)
  */
#define IS_ADC_RIGHT_BIT_SHIFT(__SHIFT__)        (((__SHIFT__) == ADC_RIGHTBITSHIFT_NONE) || \
                                                  ((__SHIFT__) == ADC_RIGHTBITSHIFT_1   ) || \
                                                  ((__SHIFT__) == ADC_RIGHTBITSHIFT_2   ) || \
                                                  ((__SHIFT__) == ADC_RIGHTBITSHIFT_3   ) || \
                                                  ((__SHIFT__) == ADC_RIGHTBITSHIFT_4   ) || \
                                                  ((__SHIFT__) == ADC_RIGHTBITSHIFT_5   ) || \
                                                  ((__SHIFT__) == ADC_RIGHTBITSHIFT_6   ) || \
                                                  ((__SHIFT__) == ADC_RIGHTBITSHIFT_7   ) || \
                                                  ((__SHIFT__) == ADC_RIGHTBITSHIFT_8   ) || \
                                                  ((__SHIFT__) == ADC_RIGHTBITSHIFT_9   ) || \
                                                  ((__SHIFT__) == ADC_RIGHTBITSHIFT_10  ) || \
                                                  ((__SHIFT__) == ADC_RIGHTBITSHIFT_11  ))

/**
  * @brief Verify the ADC oversampling triggered mode.
  * @param __MODE__ programmed ADC oversampling triggered mode.
  * @retval SET (__MODE__ is valid) or RESET (__MODE__ is invalid)
  */
#define IS_ADC_TRIGGERED_OVERSAMPLING_MODE(__MODE__) (((__MODE__) == ADC_TRIGGEREDMODE_SINGLE_TRIGGER) || \
                                                      ((__MODE__) == ADC_TRIGGEREDMODE_MULTI_TRIGGER) )

/**
  * @brief Verify the ADC oversampling regular conversion resumed or continued mode.
  * @param __MODE__ programmed ADC oversampling regular conversion resumed or continued mode.
  * @retval SET (__MODE__ is valid) or RESET (__MODE__ is invalid)
  */
#define IS_ADC_REGOVERSAMPLING_MODE(__MODE__) (((__MODE__) == ADC_REGOVERSAMPLING_CONTINUED_MODE) || \
                                               ((__MODE__) == ADC_REGOVERSAMPLING_RESUMED_MODE) )

/**
  * @brief Verify the DFSDM mode configuration.
  * @param __HANDLE__ ADC handle.
  * @note When DMSDFM configuration is not supported, the macro systematically reports SET. For
  *      this reason, the input parameter is the ADC handle and not the configuration parameter
  *      directly.
  * @retval SET (DFSDM mode configuration is valid) or RESET (DFSDM mode configuration is invalid)
  */
#if defined(DFSDM1_Channel0)
#define IS_ADC_DFSDMCFG_MODE(__HANDLE__) (((__HANDLE__)->Init.DFSDMConfig == ADC_DFSDM_MODE_DISABLE) || \
                                          ((__HANDLE__)->Init.DFSDMConfig == ADC_DFSDM_MODE_ENABLE) )
#else
#define IS_ADC_DFSDMCFG_MODE(__HANDLE__) (SET)
#endif

/**
  * @brief Return the DFSDM configuration mode.
  * @param __HANDLE__ ADC handle.
  * @note When DMSDFM configuration is not supported, the macro systematically reports 0x0 (i.e disabled).
  *       For this reason, the input parameter is the ADC handle and not the configuration parameter
  *       directly.
  * @retval DFSDM configuration mode
  */
#if defined(DFSDM1_Channel0)
#define ADC_CFGR_DFSDM(__HANDLE__) ((__HANDLE__)->Init.DFSDMConfig)
#else
#define ADC_CFGR_DFSDM(__HANDLE__) (0x0UL)
#endif

/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/
/** @addtogroup ADCEx_Exported_Functions
  * @{
  */

/** @addtogroup ADCEx_Exported_Functions_Group1
  * @{
  */
/* IO operation functions *****************************************************/

/* ADC calibration */
HAL_StatusTypeDef       HAL_ADCEx_Calibration_Start(ADC_HandleTypeDef *hadc, uint32_t CalibrationMode, uint32_t SingleDiff);
uint32_t                HAL_ADCEx_Calibration_GetValue(ADC_HandleTypeDef *hadc, uint32_t SingleDiff);
HAL_StatusTypeDef       HAL_ADCEx_LinearCalibration_GetValue(ADC_HandleTypeDef *hadc, uint32_t *LinearCalib_Buffer);
HAL_StatusTypeDef       HAL_ADCEx_Calibration_SetValue(ADC_HandleTypeDef *hadc, uint32_t SingleDiff, uint32_t CalibrationFactor);
HAL_StatusTypeDef       HAL_ADCEx_LinearCalibration_SetValue(ADC_HandleTypeDef *hadc, uint32_t *LinearCalib_Buffer);
HAL_StatusTypeDef       HAL_ADCEx_LinearCalibration_FactorLoad(ADC_HandleTypeDef *hadc);


/* Blocking mode: Polling */
HAL_StatusTypeDef       HAL_ADCEx_InjectedStart(ADC_HandleTypeDef *hadc);
HAL_StatusTypeDef       HAL_ADCEx_InjectedStop(ADC_HandleTypeDef *hadc);
HAL_StatusTypeDef       HAL_ADCEx_InjectedPollForConversion(ADC_HandleTypeDef *hadc, uint32_t Timeout);

/* Non-blocking mode: Interruption */
HAL_StatusTypeDef       HAL_ADCEx_InjectedStart_IT(ADC_HandleTypeDef *hadc);
HAL_StatusTypeDef       HAL_ADCEx_InjectedStop_IT(ADC_HandleTypeDef *hadc);

/* ADC multimode */
HAL_StatusTypeDef       HAL_ADCEx_MultiModeStart_DMA(ADC_HandleTypeDef *hadc, uint32_t *pData, uint32_t Length);
HAL_StatusTypeDef       HAL_ADCEx_MultiModeStop_DMA(ADC_HandleTypeDef *hadc);
uint32_t                HAL_ADCEx_MultiModeGetValue(ADC_HandleTypeDef *hadc);

/* ADC retrieve conversion value intended to be used with polling or interruption */
uint32_t                HAL_ADCEx_InjectedGetValue(ADC_HandleTypeDef *hadc, uint32_t InjectedRank);

/* ADC IRQHandler and Callbacks used in non-blocking modes (Interruption) */
void                    HAL_ADCEx_InjectedConvCpltCallback(ADC_HandleTypeDef *hadc);
void                    HAL_ADCEx_InjectedQueueOverflowCallback(ADC_HandleTypeDef *hadc);
void                    HAL_ADCEx_LevelOutOfWindow2Callback(ADC_HandleTypeDef *hadc);
void                    HAL_ADCEx_LevelOutOfWindow3Callback(ADC_HandleTypeDef *hadc);
void                    HAL_ADCEx_EndOfSamplingCallback(ADC_HandleTypeDef *hadc);

/* ADC group regular conversions stop */
HAL_StatusTypeDef HAL_ADCEx_RegularStop(ADC_HandleTypeDef *hadc);
HAL_StatusTypeDef HAL_ADCEx_RegularStop_IT(ADC_HandleTypeDef *hadc);
HAL_StatusTypeDef HAL_ADCEx_RegularStop_DMA(ADC_HandleTypeDef *hadc);
HAL_StatusTypeDef HAL_ADCEx_RegularMultiModeStop_DMA(ADC_HandleTypeDef *hadc);

/**
  * @}
  */

/** @addtogroup ADCEx_Exported_Functions_Group2
  * @{
  */
/* Peripheral Control functions ***********************************************/
HAL_StatusTypeDef       HAL_ADCEx_InjectedConfigChannel(ADC_HandleTypeDef *hadc, ADC_InjectionConfTypeDef *sConfigInjected);
HAL_StatusTypeDef       HAL_ADCEx_MultiModeConfigChannel(ADC_HandleTypeDef *hadc, ADC_MultiModeTypeDef *multimode);
HAL_StatusTypeDef       HAL_ADCEx_EnableInjectedQueue(ADC_HandleTypeDef *hadc);
HAL_StatusTypeDef       HAL_ADCEx_DisableInjectedQueue(ADC_HandleTypeDef *hadc);
HAL_StatusTypeDef       HAL_ADCEx_DisableVoltageRegulator(ADC_HandleTypeDef *hadc);
HAL_StatusTypeDef       HAL_ADCEx_EnterADCDeepPowerDownMode(ADC_HandleTypeDef *hadc);

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

#endif /* STM32H7xx_HAL_ADC_EX_H */


