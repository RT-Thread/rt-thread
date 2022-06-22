/**
  ******************************************************************************
  * @file    stm32wbxx_hal_adc_ex.h
  * @author  MCD Application Team
  * @brief   Header file of ADC HAL extended module.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32WBxx_HAL_ADC_EX_H
#define STM32WBxx_HAL_ADC_EX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32wbxx_hal_def.h"

/** @addtogroup STM32WBxx_HAL_Driver
  * @{
  */

/** @addtogroup ADCEx
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup ADCEx_Exported_Types ADC Extended Exported Types
  * @{
  */

#if defined (ADC_SUPPORT_2_5_MSPS)
/* Feature "ADC group injected" not available on ADC peripheral of this STM32WB device */
#else
/**
  * @brief  ADC Injected Conversion Oversampling structure definition
  */
typedef struct
{
  uint32_t Ratio;                         /*!< Configures the oversampling ratio.
                                               This parameter can be a value of @ref ADC_HAL_EC_OVS_RATIO */

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
                                               Depending of ADC resolution selected (12, 10, 8 or 6 bits), this parameter must be a number
                                               between Min_Data = 0x000 and Max_Data = 0xFFF,  0x3FF, 0xFF or 0x3F respectively.
                                               Note: This parameter must be modified when no conversion is on going on both regular and injected groups (ADC disabled, or ADC enabled
                                               without continuous mode or external trigger that could launch a conversion). */

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
#endif /* ADC_SUPPORT_2_5_MSPS */

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/

/** @defgroup ADCEx_Exported_Constants ADC Extended Exported Constants
  * @{
  */

#if defined (ADC_SUPPORT_2_5_MSPS)
/* Feature "ADC group injected" not available on ADC peripheral of this STM32WB device */
#else
/** @defgroup ADC_injected_external_trigger_source ADC group injected trigger source
  * @{
  */
/* ADC group regular trigger sources for all ADC instances */
#define ADC_INJECTED_SOFTWARE_START        (LL_ADC_INJ_TRIG_SOFTWARE)            /*!< Software triggers injected group conversion start */
#define ADC_EXTERNALTRIGINJEC_T1_TRGO      (LL_ADC_INJ_TRIG_EXT_TIM1_TRGO)       /*!< ADC group injected conversion trigger from external peripheral: TIM1 TRGO. Trigger edge set to rising edge (default setting). */
#define ADC_EXTERNALTRIGINJEC_T1_TRGO2     (LL_ADC_INJ_TRIG_EXT_TIM1_TRGO2)      /*!< ADC group injected conversion trigger from external peripheral: TIM1 TRGO2. Trigger edge set to rising edge (default setting). */
#define ADC_EXTERNALTRIGINJEC_T1_CC4       (LL_ADC_INJ_TRIG_EXT_TIM1_CH4)        /*!< ADC group injected conversion trigger from external peripheral: TIM1 channel 4 event (capture compare: input capture or output capture). Trigger edge set to rising edge (default setting). */
#define ADC_EXTERNALTRIGINJEC_T2_TRGO      (LL_ADC_INJ_TRIG_EXT_TIM2_TRGO)       /*!< ADC group injected conversion trigger from external peripheral: TIM2 TRGO. Trigger edge set to rising edge (default setting). */
#define ADC_EXTERNALTRIGINJEC_T2_CC1       (LL_ADC_INJ_TRIG_EXT_TIM2_CH1)        /*!< ADC group injected conversion trigger from external peripheral: TIM2 channel 1 event (capture compare: input capture or output capture). Trigger edge set to rising edge (default setting). */
#define ADC_EXTERNALTRIGINJEC_EXT_IT15     (LL_ADC_INJ_TRIG_EXT_EXTI_LINE15)     /*!< ADC group injected conversion trigger from external peripheral: external interrupt line 15. Trigger edge set to rising edge (default setting). */
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
#endif /* ADC_SUPPORT_2_5_MSPS */

/** @defgroup ADC_HAL_EC_CHANNEL_SINGLE_DIFF_ENDING  Channel - Single or differential ending
  * @{
  */
#define ADC_SINGLE_ENDED                (LL_ADC_SINGLE_ENDED)         /*!< ADC channel ending set to single ended (literal also used to set calibration mode) */
#if !defined (ADC_SUPPORT_2_5_MSPS)
#define ADC_DIFFERENTIAL_ENDED          (LL_ADC_DIFFERENTIAL_ENDED)   /*!< ADC channel ending set to differential (literal also used to set calibration mode) */
#endif
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

#if defined (ADC_SUPPORT_2_5_MSPS)
/* Feature "ADC group injected" not available on ADC peripheral of this STM32WB device */
#else
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
#endif /* ADC_SUPPORT_2_5_MSPS */

/** @defgroup ADC_HAL_EC_GROUPS  ADC instance - Groups
  * @{
  */
#define ADC_REGULAR_GROUP                  (LL_ADC_GROUP_REGULAR)           /*!< ADC group regular (available on all STM32 devices) */
#if defined (ADC_SUPPORT_2_5_MSPS)
/* Feature "ADC group injected" not available on ADC peripheral of this STM32WB device */
#else
#define ADC_INJECTED_GROUP                 (LL_ADC_GROUP_INJECTED)          /*!< ADC group injected (not available on all STM32 devices)*/
#define ADC_REGULAR_INJECTED_GROUP         (LL_ADC_GROUP_REGULAR_INJECTED)  /*!< ADC both groups regular and injected */
#endif /* ADC_SUPPORT_2_5_MSPS */
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
#define ADC_CFGR_FIELDS_2  ((ADC_CFGR_DMACFG | ADC_CFGR_AUTDLY))
/**
  * @}
  */


/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/

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
  * @brief Check whether or not ADC is independent.
  * @param __HANDLE__ ADC handle.
  * @note  When multimode feature is not available, the macro always returns SET.
  * @retval SET (ADC is independent) or RESET (ADC is not).
  */
#define ADC_IS_INDEPENDENT(__HANDLE__)   (SET)

#if defined (ADC_SUPPORT_2_5_MSPS)
/* Feature "ADC group injected" not available on ADC peripheral of this STM32WB device */
#else
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
#endif /* ADC_SUPPORT_2_5_MSPS */

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

#if defined (ADC_SUPPORT_2_5_MSPS)
/**
  * @brief Enable ADC overrun mode.
  * @param _OVERRUN_MODE_ Overrun mode.
  * @retval Overun bit setting to be programmed into CFGR register
  */
/* Note: Bit ADC_CFGR1_OVRMOD not used directly in constant                   */
/* "ADC_OVR_DATA_OVERWRITTEN" to have this case defined to 0x00, to set it    */
/* as the default case to be compliant with other STM32 devices.              */
#define ADC_CFGR_OVERRUN(_OVERRUN_MODE_)                                       \
  ( ( (_OVERRUN_MODE_) != (ADC_OVR_DATA_PRESERVED)                             \
    )? (ADC_CFGR1_OVRMOD) : (0x00000000UL)                                     \
  )

/**
  * @brief Enable the ADC auto off mode.
  * @param _AUTOOFF_ Auto off bit enable or disable.
  * @retval None
  */
#define ADC_CFGR_AUTOOFF(_AUTOOFF_)                                            \
  ((_AUTOOFF_) << 15UL)

/**
  * @brief Set ADC scan mode with differentiation of sequencer setting
  *        fixed or configurable
  * @param _SCAN_MODE_ Scan conversion mode.
  * @retval None
  */
/* Note: Scan mode set using this macro (instead of parameter direct set)     */
/*       due to different modes on other STM32 devices:                       */
/*       if scan mode is disabled, sequencer is set to fully configurable     */
/*       with setting of only rank 1 enabled afterwards.                      */
#define ADC_SCAN_SEQ_MODE(_SCAN_MODE_)                                         \
  ( (((_SCAN_MODE_) & ADC_SCAN_SEQ_FIXED_INT) != 0UL                           \
    )?                                                                         \
     ((_SCAN_MODE_) & (~ADC_SCAN_SEQ_FIXED_INT))                               \
     :                                                                         \
     (ADC_CFGR1_CHSELRMOD)                                                     \
  )

#endif
/**
  * @brief Configure the ADC DMA continuous request.
  * @param __DMACONTREQ_MODE__ DMA continuous request mode.
  * @retval None
  */
#define ADC_CFGR_DMACONTREQ(__DMACONTREQ_MODE__) ((__DMACONTREQ_MODE__) <<  ADC_CFGR_DMACFG_Pos)


/**
  * @brief Shift the offset with respect to the selected ADC resolution.
  * @note   Offset has to be left-aligned on bit 11, the LSB (right bits) are set to 0.
  *         If resolution 12 bits, no shift.
  *         If resolution 10 bits, shift of 2 ranks on the left.
  *         If resolution 8 bits, shift of 4 ranks on the left.
  *         If resolution 6 bits, shift of 6 ranks on the left.
  *         Therefore, shift = (12 - resolution) = 12 - (12- (((RES[1:0]) >> 3)*2)).
  * @param __HANDLE__ ADC handle
  * @param __OFFSET__ Value to be shifted
  * @retval None
  */
#define ADC_OFFSET_SHIFT_RESOLUTION(__HANDLE__, __OFFSET__) \
  ((__OFFSET__) << ((((__HANDLE__)->Instance->CFGR & ADC_CFGR_RES) >> 3UL) * 2UL))

/**
  * @brief Shift the AWD1 threshold with respect to the selected ADC resolution.
  * @note  Thresholds have to be left-aligned on bit 11, the LSB (right bits) are set to 0.
  *        If resolution 12 bits, no shift.
  *        If resolution 10 bits, shift of 2 ranks on the left.
  *        If resolution 8 bits, shift of 4 ranks on the left.
  *        If resolution 6 bits, shift of 6 ranks on the left.
  *        Therefore, shift = (12 - resolution) = 12 - (12- (((RES[1:0]) >> 3)*2)).
  * @param __HANDLE__ ADC handle
  * @param __THRESHOLD__ Value to be shifted
  * @retval None
  */
#if defined (ADC_SUPPORT_2_5_MSPS)
#define ADC_AWD1THRESHOLD_SHIFT_RESOLUTION(__HANDLE__, __THRESHOLD__) \
  ((__THRESHOLD__) << ((((__HANDLE__)->Instance->CFGR1 & ADC_CFGR1_RES) >> 3UL) * 2UL))
#else
#define ADC_AWD1THRESHOLD_SHIFT_RESOLUTION(__HANDLE__, __THRESHOLD__) \
  ((__THRESHOLD__) << ((((__HANDLE__)->Instance->CFGR & ADC_CFGR_RES) >> 3UL) * 2UL))
#endif

/**
  * @brief Shift the AWD2 and AWD3 threshold with respect to the selected ADC resolution.
  * @note  Thresholds have to be left-aligned on bit 7.
  *        If resolution 12 bits, shift of 4 ranks on the right (the 4 LSB are discarded).
  *        If resolution 10 bits, shift of 2 ranks on the right (the 2 LSB are discarded).
  *        If resolution 8 bits, no shift.
  *        If resolution 6 bits, shift of 2 ranks on the left (the 2 LSB are set to 0).
  * @param __HANDLE__ ADC handle
  * @param __THRESHOLD__ Value to be shifted
  * @retval None
  */
#if defined (ADC_SUPPORT_2_5_MSPS)
#define ADC_AWD23THRESHOLD_SHIFT_RESOLUTION(__HANDLE__, __THRESHOLD__)                                       \
  ((((__HANDLE__)->Instance->CFGR1 & ADC_CFGR1_RES) != (ADC_CFGR1_RES_1 | ADC_CFGR1_RES_0))                    ? \
   ((__THRESHOLD__) >> ((4UL - ((((__HANDLE__)->Instance->CFGR1 & ADC_CFGR1_RES) >> 3UL) * 2UL)) & 0x1FUL)) : \
   ((__THRESHOLD__) << 2UL)                                                                                 \
  )
#else
#define ADC_AWD23THRESHOLD_SHIFT_RESOLUTION(__HANDLE__, __THRESHOLD__)                                       \
  ((((__HANDLE__)->Instance->CFGR & ADC_CFGR_RES) != (ADC_CFGR_RES_1 | ADC_CFGR_RES_0))                    ? \
   ((__THRESHOLD__) >> ((4UL - ((((__HANDLE__)->Instance->CFGR & ADC_CFGR_RES) >> 3UL) * 2UL)) & 0x1FUL)) : \
   ((__THRESHOLD__) << 2UL)                                                                                 \
  )
#endif

/**
  * @brief Clear Common Control Register.
  * @param __HANDLE__ ADC handle.
  * @retval None
  */
#if defined (ADC_SUPPORT_2_5_MSPS)
#define ADC_CLEAR_COMMON_CONTROL_REGISTER(__HANDLE__) CLEAR_BIT(__LL_ADC_COMMON_INSTANCE((__HANDLE__)->Instance)->CCR, \
                                                                                                      ADC_CCR_PRESC  | \
                                                                                                      ADC_CCR_VBATEN | \
                                                                                                      ADC_CCR_TSEN   | \
                                                                                                      ADC_CCR_VREFEN )
#else
#define ADC_CLEAR_COMMON_CONTROL_REGISTER(__HANDLE__) CLEAR_BIT(__LL_ADC_COMMON_INSTANCE((__HANDLE__)->Instance)->CCR, ADC_CCR_CKMODE | \
                                                                                                      ADC_CCR_PRESC  | \
                                                                                                      ADC_CCR_VBATEN | \
                                                                                                      ADC_CCR_TSEN   | \
                                                                                                      ADC_CCR_VREFEN )
#endif


/**
  * @brief Verify the ADC instance connected to the temperature sensor.
  * @param __HANDLE__ ADC handle.
  * @retval SET (ADC instance is valid) or RESET (ADC instance is invalid)
  */
#define ADC_TEMPERATURE_SENSOR_INSTANCE(__HANDLE__)  (((__HANDLE__)->Instance) == ADC1)

/**
  * @brief Verify the ADC instance connected to the battery voltage VBAT.
  * @param __HANDLE__ ADC handle.
  * @retval SET (ADC instance is valid) or RESET (ADC instance is invalid)
  */
#define ADC_BATTERY_VOLTAGE_INSTANCE(__HANDLE__)  (((__HANDLE__)->Instance) == ADC1)

/**
  * @brief Verify the ADC instance connected to the internal voltage reference VREFINT.
  * @param __HANDLE__ ADC handle.
  * @retval SET (ADC instance is valid) or RESET (ADC instance is invalid)
  */
#define ADC_VREFINT_INSTANCE(__HANDLE__)  (((__HANDLE__)->Instance) == ADC1)

#if defined (ADC_SUPPORT_2_5_MSPS)
/* Feature "ADC group injected" not available on ADC peripheral of this STM32WB device */
#else
/**
  * @brief Verify the length of scheduled injected conversions group.
  * @param __LENGTH__ number of programmed conversions.
  * @retval SET (__LENGTH__ is within the maximum number of possible programmable injected conversions) or RESET (__LENGTH__ is null or too large)
  */
#define IS_ADC_INJECTED_NB_CONV(__LENGTH__) (((__LENGTH__) >= (1U)) && ((__LENGTH__) <= (4U)))
#endif /* ADC_SUPPORT_2_5_MSPS */

/**
  * @brief Calibration factor size verification (7 bits maximum).
  * @param __CALIBRATION_FACTOR__ Calibration factor value.
  * @retval SET (__CALIBRATION_FACTOR__ is within the authorized size) or RESET (__CALIBRATION_FACTOR__ is too large)
  */
#define IS_ADC_CALFACT(__CALIBRATION_FACTOR__) ((__CALIBRATION_FACTOR__) <= (0x7FU))


/**
  * @brief Verify the ADC channel setting.
  * @param __HANDLE__ ADC handle.
  * @param __CHANNEL__ programmed ADC channel.
  * @retval SET (__CHANNEL__ is valid) or RESET (__CHANNEL__ is invalid)
  */
#define IS_ADC_CHANNEL(__HANDLE__, __CHANNEL__) ((((__HANDLE__)->Instance) == ADC1)  && \
                                                         (((__CHANNEL__) == ADC_CHANNEL_0)           || \
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
                                                          ((__CHANNEL__) == ADC_CHANNEL_VREFINT)     || \
                                                          ((__CHANNEL__) == ADC_CHANNEL_TEMPSENSOR)  || \
                                                          ((__CHANNEL__) == ADC_CHANNEL_VBAT)))

/**
  * @brief Verify the ADC channel setting in differential mode.
  * @param __HANDLE__ ADC handle.
  * @param __CHANNEL__ programmed ADC channel.
  * @retval SET (__CHANNEL__ is valid) or RESET (__CHANNEL__ is invalid)
  */
#define IS_ADC_DIFF_CHANNEL(__HANDLE__, __CHANNEL__) (((__CHANNEL__) == ADC_CHANNEL_1)      || \
                                                      ((__CHANNEL__) == ADC_CHANNEL_2)      || \
                                                      ((__CHANNEL__) == ADC_CHANNEL_3)      || \
                                                      ((__CHANNEL__) == ADC_CHANNEL_4)      || \
                                                      ((__CHANNEL__) == ADC_CHANNEL_5)      || \
                                                      ((__CHANNEL__) == ADC_CHANNEL_6)      || \
                                                      ((__CHANNEL__) == ADC_CHANNEL_7)      || \
                                                      ((__CHANNEL__) == ADC_CHANNEL_8)      || \
                                                      ((__CHANNEL__) == ADC_CHANNEL_9)      || \
                                                      ((__CHANNEL__) == ADC_CHANNEL_10)     || \
                                                      ((__CHANNEL__) == ADC_CHANNEL_11)     || \
                                                      ((__CHANNEL__) == ADC_CHANNEL_12)     || \
                                                      ((__CHANNEL__) == ADC_CHANNEL_13)     || \
                                                      ((__CHANNEL__) == ADC_CHANNEL_14)     || \
                                                      ((__CHANNEL__) == ADC_CHANNEL_15)       )

/**
  * @brief Verify the ADC single-ended input or differential mode setting.
  * @param __SING_DIFF__ programmed channel setting.
  * @retval SET (__SING_DIFF__ is valid) or RESET (__SING_DIFF__ is invalid)
  */
#if defined (ADC_SUPPORT_2_5_MSPS)
#define IS_ADC_SINGLE_DIFFERENTIAL(__SING_DIFF__) ((__SING_DIFF__) == ADC_SINGLE_ENDED)
#else
#define IS_ADC_SINGLE_DIFFERENTIAL(__SING_DIFF__) (((__SING_DIFF__) == ADC_SINGLE_ENDED)      || \
                                                   ((__SING_DIFF__) == ADC_DIFFERENTIAL_ENDED)  )
#endif

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

#if defined (ADC_SUPPORT_2_5_MSPS)
/* Feature "ADC group injected" not available on ADC peripheral of this STM32WB device */
#else
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
  * @param __HANDLE__ ADC handle.
  * @param __INJTRIG__ programmed ADC injected conversions external trigger.
  * @retval SET (__INJTRIG__ is a valid value) or RESET (__INJTRIG__ is invalid)
  */
#define IS_ADC_EXTTRIGINJEC(__HANDLE__, __INJTRIG__) (((__INJTRIG__) == ADC_EXTERNALTRIGINJEC_T1_TRGO)     || \
                                                      ((__INJTRIG__) == ADC_EXTERNALTRIGINJEC_T1_CC4)      || \
                                                      ((__INJTRIG__) == ADC_EXTERNALTRIGINJEC_T2_TRGO)     || \
                                                      ((__INJTRIG__) == ADC_EXTERNALTRIGINJEC_T2_CC1)      || \
                                                      ((__INJTRIG__) == ADC_EXTERNALTRIGINJEC_EXT_IT15)    || \
                                                      ((__INJTRIG__) == ADC_EXTERNALTRIGINJEC_T1_TRGO2)    || \
                                                      ((__INJTRIG__) == ADC_INJECTED_SOFTWARE_START)       )

/**
  * @brief Verify the ADC edge trigger setting for injected group.
  * @param __EDGE__ programmed ADC edge trigger setting.
  * @retval SET (__EDGE__ is a valid value) or RESET (__EDGE__ is invalid)
  */
#define IS_ADC_EXTTRIGINJEC_EDGE(__EDGE__) (((__EDGE__) == ADC_EXTERNALTRIGINJECCONV_EDGE_NONE)         || \
                                            ((__EDGE__) == ADC_EXTERNALTRIGINJECCONV_EDGE_RISING)       || \
                                            ((__EDGE__) == ADC_EXTERNALTRIGINJECCONV_EDGE_FALLING)      || \
                                            ((__EDGE__) == ADC_EXTERNALTRIGINJECCONV_EDGE_RISINGFALLING) )
#endif /* ADC_SUPPORT_2_5_MSPS */

/**
  * @brief Verify the ADC analog watchdog setting.
  * @param __WATCHDOG__ programmed ADC analog watchdog setting.
  * @retval SET (__WATCHDOG__ is valid) or RESET (__WATCHDOG__ is invalid)
  */
#if defined (ADC_SUPPORT_2_5_MSPS)
#define IS_ADC_ANALOG_WATCHDOG_NUMBER(__WATCHDOG__) ((__WATCHDOG__) == ADC_ANALOGWATCHDOG_1)
#else
#define IS_ADC_ANALOG_WATCHDOG_NUMBER(__WATCHDOG__) (((__WATCHDOG__) == ADC_ANALOGWATCHDOG_1) || \
                                                     ((__WATCHDOG__) == ADC_ANALOGWATCHDOG_2) || \
                                                     ((__WATCHDOG__) == ADC_ANALOGWATCHDOG_3)   )
#endif

/**
  * @brief Verify the ADC analog watchdog mode setting.
  * @param __WATCHDOG_MODE__ programmed ADC analog watchdog mode setting.
  * @retval SET (__WATCHDOG_MODE__ is valid) or RESET (__WATCHDOG_MODE__ is invalid)
  */
#if defined (ADC_SUPPORT_2_5_MSPS)
#define IS_ADC_ANALOG_WATCHDOG_MODE(__WATCHDOG_MODE__) (((__WATCHDOG_MODE__) == ADC_ANALOGWATCHDOG_NONE)             || \
                                                        ((__WATCHDOG_MODE__) == ADC_ANALOGWATCHDOG_SINGLE_REG)       || \
                                                        ((__WATCHDOG_MODE__) == ADC_ANALOGWATCHDOG_ALL_REG)            )
#else
#define IS_ADC_ANALOG_WATCHDOG_MODE(__WATCHDOG_MODE__) (((__WATCHDOG_MODE__) == ADC_ANALOGWATCHDOG_NONE)             || \
                                                        ((__WATCHDOG_MODE__) == ADC_ANALOGWATCHDOG_SINGLE_REG)       || \
                                                        ((__WATCHDOG_MODE__) == ADC_ANALOGWATCHDOG_SINGLE_INJEC)     || \
                                                        ((__WATCHDOG_MODE__) == ADC_ANALOGWATCHDOG_SINGLE_REGINJEC)  || \
                                                        ((__WATCHDOG_MODE__) == ADC_ANALOGWATCHDOG_ALL_REG)          || \
                                                        ((__WATCHDOG_MODE__) == ADC_ANALOGWATCHDOG_ALL_INJEC)        || \
                                                        ((__WATCHDOG_MODE__) == ADC_ANALOGWATCHDOG_ALL_REGINJEC)       )
#endif /* ADC_SUPPORT_2_5_MSPS */

#if defined (ADC_SUPPORT_2_5_MSPS)
#define IS_ADC_TRIGGER_FREQ(TRIGGER_FREQ) (((TRIGGER_FREQ) == LL_ADC_TRIGGER_FREQ_HIGH) || \
                                           ((TRIGGER_FREQ) == LL_ADC_TRIGGER_FREQ_LOW)    )
#endif

/**
  * @brief Verify the ADC conversion (regular or injected or both).
  * @param __CONVERSION__ ADC conversion group.
  * @retval SET (__CONVERSION__ is valid) or RESET (__CONVERSION__ is invalid)
  */
#define IS_ADC_CONVERSION_GROUP(__CONVERSION__) (((__CONVERSION__) == ADC_REGULAR_GROUP)         || \
                                                 ((__CONVERSION__) == ADC_INJECTED_GROUP)        || \
                                                 ((__CONVERSION__) == ADC_REGULAR_INJECTED_GROUP)  )

/**
  * @brief Verify the ADC event type.
  * @param __EVENT__ ADC event.
  * @retval SET (__EVENT__ is valid) or RESET (__EVENT__ is invalid)
  */
#if defined (ADC_SUPPORT_2_5_MSPS)
#define IS_ADC_EVENT_TYPE(__EVENT__) (((__EVENT__) == ADC_EOSMP_EVENT) || \
                                      ((__EVENT__) == ADC_AWD1_EVENT)  || \
                                      ((__EVENT__) == ADC_AWD2_EVENT)  || \
                                      ((__EVENT__) == ADC_AWD3_EVENT)  || \
                                      ((__EVENT__) == ADC_OVR_EVENT)     )
#else
#define IS_ADC_EVENT_TYPE(__EVENT__) (((__EVENT__) == ADC_EOSMP_EVENT)  || \
                                      ((__EVENT__) == ADC_AWD_EVENT)    || \
                                      ((__EVENT__) == ADC_AWD2_EVENT)   || \
                                      ((__EVENT__) == ADC_AWD3_EVENT)   || \
                                      ((__EVENT__) == ADC_OVR_EVENT)    || \
                                      ((__EVENT__) == ADC_JQOVF_EVENT)  )
#endif /* ADC_SUPPORT_2_5_MSPS */

#if defined (ADC_SUPPORT_2_5_MSPS)
/* Feature "ADC oversampling" not available on ADC peripheral of this STM32WB device */
#else
/**
  * @brief Verify the ADC oversampling ratio.
  * @param __RATIO__ programmed ADC oversampling ratio.
  * @retval SET (__RATIO__ is a valid value) or RESET (__RATIO__ is invalid)
  */
#define IS_ADC_OVERSAMPLING_RATIO(__RATIO__)      (((__RATIO__) == ADC_OVERSAMPLING_RATIO_2   ) || \
                                                   ((__RATIO__) == ADC_OVERSAMPLING_RATIO_4   ) || \
                                                   ((__RATIO__) == ADC_OVERSAMPLING_RATIO_8   ) || \
                                                   ((__RATIO__) == ADC_OVERSAMPLING_RATIO_16  ) || \
                                                   ((__RATIO__) == ADC_OVERSAMPLING_RATIO_32  ) || \
                                                   ((__RATIO__) == ADC_OVERSAMPLING_RATIO_64  ) || \
                                                   ((__RATIO__) == ADC_OVERSAMPLING_RATIO_128 ) || \
                                                   ((__RATIO__) == ADC_OVERSAMPLING_RATIO_256 ))
#endif

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
                                                  ((__SHIFT__) == ADC_RIGHTBITSHIFT_8   ))

/**
  * @brief Verify the ADC oversampling triggered mode.
  * @param __MODE__ programmed ADC oversampling triggered mode.
  * @retval SET (__MODE__ is valid) or RESET (__MODE__ is invalid)
  */
#define IS_ADC_TRIGGERED_OVERSAMPLING_MODE(__MODE__) (((__MODE__) == ADC_TRIGGEREDMODE_SINGLE_TRIGGER) || \
                                                      ((__MODE__) == ADC_TRIGGEREDMODE_MULTI_TRIGGER) )

#if defined (ADC_SUPPORT_2_5_MSPS)
#else
/**
  * @brief Verify the ADC oversampling regular conversion resumed or continued mode.
  * @param __MODE__ programmed ADC oversampling regular conversion resumed or continued mode.
  * @retval SET (__MODE__ is valid) or RESET (__MODE__ is invalid)
  */
#define IS_ADC_REGOVERSAMPLING_MODE(__MODE__) (((__MODE__) == ADC_REGOVERSAMPLING_CONTINUED_MODE) || \
                                               ((__MODE__) == ADC_REGOVERSAMPLING_RESUMED_MODE) )
#endif

/**
  * @brief Verify the DFSDM mode configuration.
  * @param __HANDLE__ ADC handle.
  * @note When DMSDFM configuration is not supported, the macro systematically reports SET. For
  *      this reason, the input parameter is the ADC handle and not the configuration parameter
  *      directly.
  * @retval SET (DFSDM mode configuration is valid) or RESET (DFSDM mode configuration is invalid)
  */
#define IS_ADC_DFSDMCFG_MODE(__HANDLE__) (SET)

/**
  * @brief Return the DFSDM configuration mode.
  * @param __HANDLE__ ADC handle.
  * @note When DMSDFM configuration is not supported, the macro systematically reports 0x0 (i.e disabled).
  *       For this reason, the input parameter is the ADC handle and not the configuration parameter
  *       directly.
  * @retval DFSDM configuration mode
  */
#define ADC_CFGR_DFSDM(__HANDLE__) (0x0UL)

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
HAL_StatusTypeDef       HAL_ADCEx_Calibration_Start(ADC_HandleTypeDef *hadc, uint32_t SingleDiff);
uint32_t                HAL_ADCEx_Calibration_GetValue(ADC_HandleTypeDef *hadc, uint32_t SingleDiff);
HAL_StatusTypeDef       HAL_ADCEx_Calibration_SetValue(ADC_HandleTypeDef *hadc, uint32_t SingleDiff,
                                                       uint32_t CalibrationFactor);

#if defined (ADC_SUPPORT_2_5_MSPS)
/* Feature "ADC group injected" not available on ADC peripheral of this STM32WB device */
#else
/* Blocking mode: Polling */
HAL_StatusTypeDef       HAL_ADCEx_InjectedStart(ADC_HandleTypeDef *hadc);
HAL_StatusTypeDef       HAL_ADCEx_InjectedStop(ADC_HandleTypeDef *hadc);
HAL_StatusTypeDef       HAL_ADCEx_InjectedPollForConversion(ADC_HandleTypeDef *hadc, uint32_t Timeout);

/* Non-blocking mode: Interruption */
HAL_StatusTypeDef       HAL_ADCEx_InjectedStart_IT(ADC_HandleTypeDef *hadc);
HAL_StatusTypeDef       HAL_ADCEx_InjectedStop_IT(ADC_HandleTypeDef *hadc);
#endif /* ADC_SUPPORT_2_5_MSPS */

#if defined (ADC_SUPPORT_2_5_MSPS)
/* Feature "ADC group injected" not available on ADC peripheral of this STM32WB device */
#else
/* ADC retrieve conversion value intended to be used with polling or interruption */
uint32_t                HAL_ADCEx_InjectedGetValue(ADC_HandleTypeDef *hadc, uint32_t InjectedRank);
#endif /* ADC_SUPPORT_2_5_MSPS */

/* ADC IRQHandler and Callbacks used in non-blocking modes (Interruption) */
#if defined (ADC_SUPPORT_2_5_MSPS)
/* Feature "ADC group injected" not available on ADC peripheral of this STM32WB device */
#else
void                    HAL_ADCEx_InjectedConvCpltCallback(ADC_HandleTypeDef *hadc);
void                    HAL_ADCEx_InjectedQueueOverflowCallback(ADC_HandleTypeDef *hadc);
#endif /* ADC_SUPPORT_2_5_MSPS */
void                    HAL_ADCEx_LevelOutOfWindow2Callback(ADC_HandleTypeDef *hadc);
void                    HAL_ADCEx_LevelOutOfWindow3Callback(ADC_HandleTypeDef *hadc);
void                    HAL_ADCEx_EndOfSamplingCallback(ADC_HandleTypeDef *hadc);

#if defined (ADC_SUPPORT_2_5_MSPS)
/* Feature "ADC group injected" not available on ADC peripheral of this STM32WB device */
#else
/* ADC group regular conversions stop */
HAL_StatusTypeDef HAL_ADCEx_RegularStop(ADC_HandleTypeDef *hadc);
HAL_StatusTypeDef HAL_ADCEx_RegularStop_IT(ADC_HandleTypeDef *hadc);
HAL_StatusTypeDef HAL_ADCEx_RegularStop_DMA(ADC_HandleTypeDef *hadc);
#endif /* ADC_SUPPORT_2_5_MSPS */
/**
  * @}
  */

/** @addtogroup ADCEx_Exported_Functions_Group2
  * @{
  */
/* Peripheral Control functions ***********************************************/
#if defined (ADC_SUPPORT_2_5_MSPS)
/* Feature "ADC group injected" not available on ADC peripheral of this STM32WB device */
#else
HAL_StatusTypeDef       HAL_ADCEx_InjectedConfigChannel(ADC_HandleTypeDef *hadc,ADC_InjectionConfTypeDef* sConfigInjected);
#endif /* ADC_SUPPORT_2_5_MSPS */
#if defined (ADC_SUPPORT_2_5_MSPS)
/* Feature "ADC group injected" not available on ADC peripheral of this STM32WB device */
#else
HAL_StatusTypeDef       HAL_ADCEx_EnableInjectedQueue(ADC_HandleTypeDef *hadc);
HAL_StatusTypeDef       HAL_ADCEx_DisableInjectedQueue(ADC_HandleTypeDef *hadc);
#endif /* ADC_SUPPORT_2_5_MSPS */
HAL_StatusTypeDef       HAL_ADCEx_DisableVoltageRegulator(ADC_HandleTypeDef *hadc);
#if defined (ADC_SUPPORT_2_5_MSPS)
/* Feature " ADC deep power-down" not available on ADC peripheral of this STM32WB device */
#else
HAL_StatusTypeDef       HAL_ADCEx_EnterADCDeepPowerDownMode(ADC_HandleTypeDef *hadc);
#endif

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

#endif /* STM32WBxx_HAL_ADC_EX_H */


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
