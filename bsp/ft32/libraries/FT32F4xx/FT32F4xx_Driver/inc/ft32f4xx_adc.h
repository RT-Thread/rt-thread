/**
  ******************************************************************************
  * @file               ft32f4xx_adc.h
  * @author             FMD AE
  * @brief              This file contains all the functions prototypes for the ADC firmware
  *                     library
  * @version            V1.0.0
  * @data                   2025-04-08
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FT32F4XX_ADC_H
#define __FT32F4XX_ADC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "ft32f4xx.h"

/** @addtogroup ADC
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/**
  * @brief  ADC group regular oversampling structure definition
  */
typedef struct
{
    uint32_t Ratio;                         /*!< Configures the oversampling ratio.
                                               This parameter can be a value of @ref ADC_OVS_RATIO */

    uint32_t RightBitShift;                 /*!< Configures the division coefficient for the Oversampler.
                                               This parameter can be a value of @ref ADC_OVS_SHIFT */

    uint32_t TriggeredMode;                 /*!< Selects the regular triggered oversampling mode.
                                               This parameter can be a value of @ref ADC_OVS_DISCONT_MODE */

    uint32_t OversamplingStopReset;         /*!< Selects the regular oversampling mode.
                                               The oversampling is either temporary stopped or reset upon an injected
                                               sequence interruption.
                                               If oversampling is enabled on both regular and injected groups, this
                                               parameter is discarded and forced to setting
                                               "ADC_REGOVERSAMPLING_RESUMED_MODE" (the oversampling buffer is zeroed
                                               during injection sequence).
                                               This parameter can be a value of @ref ADC_OVS_SCOPE_REG */
} ADC_OversamplingTypeDef;



/**
  * @brief  ADC group injected oversampling structure definition
  */
typedef struct
{
    uint32_t Ratio;                         /*!< Configures the oversampling ratio.
                                               This parameter can be a value of @ref ADC_OVS_RATIO */

    uint32_t RightBitShift;                 /*!< Configures the division coefficient for the Oversampler.
                                               This parameter can be a value of @ref ADC_OVS_SHIFT */

} ADC_InjOversamplingTypeDef;


/**
  * @brief  Structure definition of ADC instance.
  * @note   Parameters of this structure are shared within 3 scopes:
  *          - Scope entire ADC (affects ADC groups regular and injected): Resolution, DataAlign,
  *            GainCompensation, AutoDelayedConvMode.
  *          - Scope ADC group regular: ContinuousConvMode, NbrOfConversion, ExternalTrigConv, ExternalTrigConvEdge,
  *            DiscontinuousConvMode, NbrOfDiscConversion, DMAMode, Overrun, OversamplingMode, Oversampling,
  *            SamplingMode.
  *          - Scope ADC group injected: InjectedDiscontinuousConvMode, AutoInjectedConv, QueueInjectedContext,
  *            QueueMode.
  */
typedef struct
{
    uint32_t Resolution;                  /*!< Selects the resolution of the conversion.
                                             This parameter can be a value of @ref ADC_Resolution */

    FunctionalState ContinuousConvMode;   /*!< Specifies whether the conversion is performed in
                                             Continuous or Single mode.
                                             This parameter can be set to ENABLE or DISABLE. */

    uint32_t DataAlign;                   /*!< Specifies whether the ADC data alignment is left or right.
                                             This parameter can be a value of @ref ADC_data_align */

    uint32_t GainCompensation;            /*!< Specify the ADC gain compensation coefficient to be applied to ADC raw conversion
                                             data, based on following formula:
                                               DATA = DATA(raw) * (gain compensation coef) / 4096
                                             "2.12" bit format, unsigned: 2 bits exponents / 12 bits mantissa
                                             Gain step is 1/4096 = 0.000244
                                             Gain range is 0.0000 to 3.999756
                                             This parameter value can be
                                              0           Gain compensation will be disabled and coefficient set to 0
                                              1 -> 0x3FFF Gain compensation will be enabled and coefficient set to specified
                                                          value
                                             Note: Gain compensation when enabled is applied to all channels. */

    uint32_t NbrOfConversion;             /*!< Specify the number of ranks that will be converted within the regular group
                                             sequencer.
                                             This parameter must be a number between Min_Data = 1 and Max_Data = 16.
                                             Note: This parameter must be modified when no conversion is on going on regular
                                                   group (ADC disabled, or ADC stop conversion). */

    uint32_t ExternalTrigConvEdge;        /*!< Selects the external trigger Edge and enables the
                                             trigger of a regular group. This parameter can be a value
                                             of @ref ADC_regular_external_trigger_edge */

    uint32_t ExternalTrigConv;            /*!< Defines the external trigger used to start the analog
                                             to digital conversion of regular channels. This parameter
                                             can be a value of @ref ADC12_external_trigger_sources
                                             or ADC3_external_trigger_sources */

    FunctionalState DiscontinuousConvMode;  /*!< Specify whether the conversions sequence of ADC group regular is performed
                                              in Complete-sequence/Discontinuous-sequence (main sequence subdivided in
                                              successive parts).
                                              Discontinuous mode is used only if sequencer is enabled. If sequencer
                                              is disabled, this parameter is discarded.
                                              Discontinuous mode can be enabled only if continuous mode is disabled.
                                              If continuous mode is enabled, this parameter setting is discarded.
                                              This parameter can be set to ENABLE or DISABLE. */

    uint32_t NbrOfDiscConversion;           /*!< Specifies the number of discontinuous conversions in which the main sequence
                                               of ADC group regular (parameter NbrOfConversion) will be subdivided.
                                               If parameter 'DiscontinuousConvMode' is disabled, this parameter is discarded.
                                               This parameter must be a number between Min_Data = 1 and Max_Data = 8. */

    uint32_t DMAMode;                       /*!< Specify whether the DMA requests are performed in one shot mode (DMA
                                              transfer stops when number of conversions is reached) or in continuous
                                              mode (DMA transfer unlimited, whatever number of conversions).
                                              This parameter can be set to ADC_DMAMODE_ONESHOT or ADC_DMAMODE_CIRCULAR.
                                              Note: In continuous mode, DMA must be configured in circular mode.
                                                    Otherwise an overrun will be triggered when DMA buffer maximum
                                                    pointer is reached. */

    FunctionalState AutoDelayedConvMode;    /*!< Enables or disables the Wait conversion mode.
                                               When the CPU clock is not fast enough to manage the data rate, a
                                               Hardware delay can be introduced between ADC conversions to reduce
                                               this data rate.
                                               The Hardware delay is inserted after each conversions and until the
                                               previous data is read from the ADC data register
                                               This is a way to automatically adapt the speed of the ADC to the speed
                                               of the system which will read the data.
                                               Any hardware triggers wich occur while a conversion is on going or
                                               while the automatic Delay is applied are ignored
                                               ADCx: where x can be 1/2/3 to select the ADCx peripheral.
                                               NewState: new state of the ADCx Auto-Delay.
                                               This parameter can be: ENABLE or DISABLE.  */

    uint32_t Overrun;                       /*!< Select the behavior in case of overrun: data overwritten or preserved (default).
                                               This parameter applies to ADC group regular only.
                                               This parameter can be set to ADC_OVR_MODE_PRESERVED or ADC_OVR_MODE_OVERWRITTEN.
                                               Note: In case of overrun set to data preserved and usage with programming model
                                                     with interruption (HAL_Start_IT()): ADC IRQ handler has to clear end of
                                                     conversion flags, this induces the release of the preserved data. If
                                                     needed, this data can be saved in function HAL_ADC_ConvCpltCallback(),
                                                     placed in user program code (called before end of conversion flags clear)
                                               Note: Error reporting with respect to the conversion mode:
                                                     - Usage with ADC conversion by polling for event or interruption: Error is
                                                       reported only if overrun is set to data preserved. If overrun is set to
                                                       data overwritten, user can willingly not read all the converted data,
                                                       this is not considered as an erroneous case.
                                                     - Usage with ADC conversion by DMA: Error is reported whatever overrun
                                                       setting (DMA is expected to process all data from data register). */


    FunctionalState InjectedDiscontinuousConvMode; /*!< Specifies whether the conversions sequence of ADC group injected
                                                      is performed in Complete-sequence/Discontinuous-sequence
                                                      (main sequence subdivided in successive parts).
                                                      Discontinuous mode can be enabled only if continuous mode is disabled.
                                                      This parameter can be set to ENABLE or DISABLE.
                                                      Note: This parameter must be modified when ADC is disabled (before ADC
                                                      start conversion or after ADC stop conversion).
                                                      Note: For injected group, discontinuous mode converts the sequence
                                                      channel by channel (discontinuous length fixed to 1 rank). */

    FunctionalState AutoInjectedConvMode;   /*!< Enables or disables the selected ADC group injected automatic conversion
                                               after regular one
                                               This parameter can be set to ENABLE or DISABLE.
                                               Note: To use Automatic injected conversion, discontinuous mode must
                                                     be disabled ('DiscontinuousConvMode' and
                                                     'InjectedDiscontinuousConvMode' set to DISABLE)
                                               Note: To use Automatic injected conversion, injected group external
                                                     triggers must be disabled ('ExternalTrigInjecConv' set to
                                                     ADC_INJECTED_SOFTWARE_START) */

    FunctionalState QueueInjectedContext;   /*!< Specifies whether the context queue feature is enabled.
                                               This parameter can be set to ENABLE or DISABLE.
                                               If context queue is enabled, injected sequencer&channels configurations
                                               are queued on up to 2 contexts. If a new injected context is set when
                                               queue is full, error is triggered by interruption.
                                               Note: This parameter must be modified when ADC is disabled (before ADC
                                                     start conversion or after ADC stop conversion). */

    FunctionalState QueueMode;              /*!< Specifies how an empty Queue is managed.
                                               This parameter can be set to JSQR mode 0 or JSQR mode 1.
                                               JSQR mode 0 : The Queue is never empty and maintains the last written
                                                             configuration into JSQR.
                                               JSQR mode 1 : The Queue can be empty and when this occurs, the software
                                                             and hardware triggers of the injected sequence are both
                                                             internally disabled just after the completion of the last
                                                             valid injected sequence.
                                               Note: The software is allowed to write this bit only when JADSTART=0
                                                     (which ensures that no injected conversion is ongoing).
                                                     When dual mode is enabled (Dual bits in ADC_Common->CCR register
                                                     are not equal to zero), the bit JQM of the slave ADC is no more
                                                     writable and its content is equal to the bit JQM of the master
                                                     ADC. */

    uint32_t SamplingMode;                  /*!< Select the sampling mode to be used for ADC group regular conversion.
                                               This parameter can be a value of @ref ADC_regular_sampling_mode */

    uint32_t SamplingPlusTime;              /*!< Addition of one clock cycle to the sampling time value to be set
                                               for the ADC_SMPRx registers.
                                               This parameter can be a value of @ref ADC_sampling_plus_times
                                               Unit: ADC clock cycles.
                                               Minimum sampling clock period, can select 1.5, 2.5, 3.5 or 4.5 clock cycles.
                                               Note: To make sure no conversion is ongoing, the software is allowed
                                                     to write this bit only when this bit only when ADSTART=0 and
                                                     JADSTART=0 */

    FunctionalState OversamplingMode;       /*!< Specifies whether the oversampling feature is enabled or disabled.
                                               This parameter can be set to ENABLE or DISABLE.
                                               Note: This parameter can be modified only if there is no
                                               conversion is ongoing (both ADSTART and JADSTART cleared). */

    ADC_OversamplingTypeDef Oversampling;   /*!< Specify the Oversampling parameters.
                                               Caution: this setting overwrites the previous oversampling configuration
                                                        if oversampling is already enabled.
                                               Note: This parameter can be modified only if there is no
                                                     conversion is ongoing (both ADSTART and JADSTART cleared).*/

} ADC_InitTypeDef;


/**
  * @brief  ADC group regular Channel Init structure definition
  */
typedef struct
{
    uint32_t Channel;                /*!< Specify the channel to configure into ADC regular group.
                                        This parameter can be a value of @ref ADC_channels
                                        Note: Depending on devices and ADC instances, some channels may not be available
                                              on device package pins. Refer to device datasheet for channels
                                              availability. */

    uint32_t Rank;                   /*!< Specify the rank in the regular group sequencer.
                                        This parameter can be a value of @ref ADC_reg_seq_ranks
                                        Note: to disable a channel or change order of conversion sequencer, rank
                                        containing a previous channel setting can be overwritten by the new channel
                                        setting (or parameter number of conversions adjusted) */

    uint32_t SamplingTime;           /*!< Sampling time value to be set for the selected channel.
                                        Unit: ADC clock cycles
                                        Conversion time is the addition of sampling time and processing time
                                        This parameter can be a value of @ref ADC_sampling_times
                                        Caution: This parameter applies to a channel that can be used into regular
                                                 and/or injected group. It overwrites the last setting.
                                        Note: In case of usage of internal measurement channels (VrefInt, Vbat, ...),
                                              sampling time constraints must be respected (sampling time can be adjusted
                                              in function of ADC clock frequency and sampling time setting).
                                              Refer to device datasheet for timings values. */

    uint32_t SingleDiff;             /*!< Select single-ended or differential input.
                                        In differential mode: Differential measurement is carried out between the
                                        selected channel 'i' (positive input) and channel 'i+1' (negative input).
                                        Only channel 'i' has to be configured, channel 'i+1' is configured automatically
                                        This parameter must be a value of @ref ADC_channel_single_diff_ending
                                        Caution: This parameter applies to a channel that can be used in a regular
                                                 and/or injected group.
                                                 It overwrites the last setting.
                                        Note: Refer to Reference Manual to ensure the selected channel is available in
                                              differential mode.
                                        Note: When configuring a channel 'i' in differential mode, the channel 'i+1' is
                                              not usable separately.
                                        Note: This parameter must be modified when ADC is disabled (before ADC start
                                              conversion or after ADC stop conversion).
                                              If ADC is enabled, this parameter setting is bypassed without error
                                              reporting (as it can be the expected behavior in case of another parameter
                                              update on the fly) */

    uint32_t OffsetNumber;           /*!< Select the offset number
                                        This parameter can be a value of @ref ADC_offset_number
                                        Caution: Only one offset is allowed per channel. This parameter overwrites the
                                                 last setting. */

    uint32_t Offset;                 /*!< Define the offset to be applied on the raw converted data.
                                        Offset value must be a positive number.
                                        Depending of ADC resolution selected (12, 10, 8 or 6 bits), this parameter
                                        must be a number between Min_Data = 0x000 and Max_Data = 0xFFF,
                                        0x3FF, 0xFF or 0x3F respectively.
                                        Note: This parameter must be modified when no conversion is on going on both
                                              regular and injected groups (ADC disabled, or ADC enabled without
                                              continuous mode or external trigger that could launch a conversion). */

    uint32_t OffsetSign;             /*!< Define if the offset should be subtracted (negative sign) or added (positive
                                        sign) from or to the raw converted data.
                                        This parameter can be a value of @ref ADC_OffsetSign.
                                        Note: This parameter must be modified when no conversion is on going on both
                                              regular and injected groups (ADC disabled, or ADC enabled without
                                              continuous mode or external trigger that could launch a conversion).*/

    FunctionalState OffsetSaturation;/*!< Define if the offset should be saturated upon under or over flow.
                                        This parameter value can be ENABLE or DISABLE.
                                        Note: This parameter must be modified when no conversion is on going on both
                                              regular and injected groups (ADC disabled, or ADC enabled without
                                              continuous mode or external trigger that could launch a conversion). */

} ADC_ChannelConfTypeDef;


/**
  * @brief  ADC group injected Init structure definition
  */
typedef struct
{

    uint32_t InjectedNbrOfConversion;       /*!< Specifies the number of ranks that will be converted within the ADC group
                                               injected sequencer.
                                               To use the injected group sequencer and convert several ranks, parameter
                                               'ScanConvMode' must be enabled.
                                               This parameter must be a number between Min_Data = 1 and Max_Data = 4. */

    uint32_t InjectedChannel;               /*!< Specifies the channel to configure into ADC group injected.
                                               This parameter can be a value of @ref ADC_channels
                                               Note: Depending on devices and ADC instances, some channels may not be
                                                     available on device package pins. Refer to device datasheet for
                                                     channels availability. */

    uint32_t InjectedRank;                  /*!< Specifies the rank in the ADC group injected sequencer.
                                               This parameter must be a value of @ref ADC_injected_seq_ranks.
                                               Note: to disable a channel or change order of conversion sequencer,
                                                     rank containing a previous channel setting can be overwritten by
                                                     the new channel setting (or parameter number of conversions
                                                     adjusted) */

    uint32_t ExternalTrigInjecConvEdge;     /*!< Selects the external trigger edge of injected group.
                                               This parameter can be a value of @ref ADC_injected_external_trigger_edge.
                                               If trigger source is set to ADC_INJECTED_SOFTWARE_START, this parameter
                                               is discarded. */

    uint32_t ExternalTrigInjecConv;         /*!< Selects the external event used to trigger the conversion start of
                                               injected group.
                                               If set to ADC_INJECTED_SOFTWARE_START, external triggers are disabled
                                               and software trigger is used instead.
                                               This parameter can be a value of @ref ADC12_injected_external_trigger_sources or
                                               ADC3_injected_external_trigger_sources. */



    FunctionalState InjectedOversamplingMode;      /*!< Specifies whether the oversampling feature is enabled or disabled.
                                                      This parameter can be set to ENABLE or DISABLE.
                                                      Note: This parameter can be modified only if there is no
                                                      conversion is ongoing (both ADSTART and JADSTART cleared). */

    ADC_InjOversamplingTypeDef  InjectedOversampling; /*!< Specifies the Oversampling parameters.
                                                      Caution: this setting overwrites the previous oversampling
                                                               configuration if oversampling already enabled.
                                                      Note: This parameter can be modified only if there is no
                                                            conversion is ongoing (both ADSTART and JADSTART cleared).*/

    uint32_t InjectedSamplingTime;          /*!< Sampling time value to be set for the selected channel.
                                               Unit: ADC clock cycles.
                                               Conversion time is the addition of sampling time and processing time
                                               (12.5 ADC clock cycles at ADC resolution 12 bits, 10.5 cycles at 10 bits,
                                               8.5 cycles at 8 bits, 6.5 cycles at 6 bits).
                                               This parameter can be a value of @ref ADC_sampling_times.
                                               Caution: This parameter applies to a channel that can be used in a
                                                        regular and/or injected group. It overwrites the last setting.
                                               Note: In case of usage of internal measurement channels (VrefInt, ...),
                                                     sampling time constraints must be respected (sampling time can be
                                                     adjusted in function of ADC clock frequency and sampling time
                                                     setting). Refer to device datasheet for timings values. */

    uint32_t InjectedSingleDiff;            /*!< Selection of single-ended or differential input.
                                               In differential mode: Differential measurement is between the selected
                                               channel 'i' (positive input) and channel 'i+1' (negative input).
                                               Only channel 'i' has to be configured, channel 'i+1' is configured
                                               automatically.
                                               This parameter must be a value of
                                               @ref ADC_channel_single_diff_ending.
                                               Caution: This parameter applies to a channel that can be used in a
                                               regular and/or injected group. It overwrites the last setting.
                                               Note: Refer to Reference Manual to ensure the selected channel is
                                                     available in differential mode.
                                               Note: When configuring a channel 'i' in differential mode, the channel
                                                     'i+1' is not usable separately.
                                               Note: This parameter must be modified when ADC is disabled (before ADC
                                                     start conversion or after ADC stop conversion).
                                               If ADC is enabled, this parameter setting is bypassed without error
                                               reporting (as it can be the expected behavior in case of another
                                               parameter update on the fly) */

    uint32_t InjectedOffsetNumber;          /*!< Selects the offset number.
                                               This parameter can be a value of @ref ADC_offset_number.
                                               Caution: Only one offset is allowed per channel. This parameter
                                                        overwrites the last setting. */

    uint32_t InjectedOffset;                /*!< Defines the offset to be applied on the raw converted data.
                                               Offset value must be a positive number.
                                               Depending of ADC resolution selected (12, 10, 8 or 6 bits), this
                                               parameter must be a number between Min_Data = 0x000 and Max_Data = 0xFFF,
                                               0x3FF, 0xFF or 0x3F respectively.
                                               Note: This parameter must be modified when no conversion is on going
                                                     on both regular and injected groups (ADC disabled, or ADC enabled
                                                     without continuous mode or external trigger that could launch a
                                                     conversion). */

    uint32_t InjectedOffsetSign;                /*!< Define if the offset should be subtracted (negative sign) or added
                                                  (positive sign) from or to the raw converted data.
                                                  This parameter can be a value of @ref ADCEx_OffsetSign.
                                                  Note: This parameter must be modified when no conversion is on going
                                                        on both regular and injected groups (ADC disabled, or ADC
                                                        enabled without continuous mode or external trigger that could
                                                        launch a conversion). */

    FunctionalState InjectedOffsetSaturation;   /*!< Define if the offset should be saturated upon under or over flow.
                                               This parameter value can be ENABLE or DISABLE.
                                               Note: This parameter must be modified when no conversion is on going
                                                     on both regular and injected groups (ADC disabled, or ADC enabled
                                                     without continuous mode or external trigger that could launch a
                                                     conversion). */
} ADC_InjectedConfTypeDef;


/**
  * @brief  Structure definition of ADC analog watchdog
  * @note   The setting of these parameters by function ADC_AnalogWDGConfig() is conditioned to ADC state.
  *         ADC state can be either:
  *          - For all parameters except 'HighThreshold', 'LowThreshold': ADC disabled or ADC enabled without conversion
               on going on ADC groups regular and injected.
  *          - For parameters 'HighThreshold', 'LowThreshold': ADC enabled with conversion on going on regular and
               injected groups.
  */
typedef struct
{
    uint32_t WatchdogNumber;    /*!< Select which ADC analog watchdog is monitoring the selected channel.
                                   For Analog Watchdog 1: Only 1 channel can be monitored (or overall group of channels
                                                          by setting parameter 'WatchdogMode')
                                   For Analog Watchdog 2 and 3: Several channels can be monitored (by successive calls
                                                                of 'ADC_AnalogWDGConfig()' for each channel)
                                   This parameter can be a value of @ref ADCx_AnalogWatchdog_X_Selection. */

    uint32_t WatchdogMode;      /*!< Configure the ADC analog watchdog mode: single/all/none channels.
                                   For Analog Watchdog 1: Configure the ADC analog watchdog mode: single channel or all
                                                          channels, ADC groups regular and-or injected.
                                   For Analog Watchdog 2 and 3: No need to configure the ADC analog watchdog mode.
                                   This parameter can be a value of @ref ADCx_AnalogWatchdog_1_Channel_Mode_Selection. */

    uint32_t Channel;           /*!< Select which ADC channel to monitor by analog watchdog.
                                   For Analog Watchdog 1: this parameter has an effect only if parameter 'WatchdogMode'
                                                          is configured on single channel (only 1 channel can be
                                                          monitored).
                                   This parameter can be a value of @ref ADC_channels for Analog Watchdog 1.
                                   For Analog Watchdog 2 and 3: Several channels can be monitored. To use this feature,
                                                                call successively the function ADC_AnalogWDGConfig()
                                                                for each channel to be added (or removed with value
                                                                'ADC_ANALOGWATCHDOG_NONE').
                                   This parameter can be a value of @ref ADCx_AnalogWatchdog_2_3_Channel_Selection
                                   for Analog Watchdog 2 and 3. */

    FunctionalState ITMode;     /*!< Specify whether the analog watchdog is configured in interrupt or polling mode.
                                   This parameter can be set to ENABLE or DISABLE */

    uint32_t HighThreshold;     /*!< Configure the ADC analog watchdog High threshold value.
                                   Depending of ADC resolution selected (12, 10, 8 or 6 bits). For Analog watchdog 1, this parameter must be a
                                   number between Min_Data = 0x000 and Max_Data = 0xFFF, 0x3FF, 0xFF or 0x3F
                                   respectively. For Analog watchdog 2 and 3, this parameter must be a
                                   number between Min_Data = 0x00 and Max_Data = 0xFF.
                                   Note: Analog watchdog 2 and 3 are limited to a resolution of 8 bits: if ADC
                                         resolution is 12 bits the 4 LSB are ignored, if ADC resolution is 10 bits the 2
                                         LSB are ignored.
                                   Note: If ADC oversampling is enabled, ADC analog watchdog thresholds are
                                         impacted: the comparison of analog watchdog thresholds is done on
                                         oversampling final computation (after ratio and shift application):
                                         ADC data register bitfield [11:4] (12 most significant bits). */

    uint32_t LowThreshold;      /*!< Configures the ADC analog watchdog Low threshold value.
                                   Depending of ADC resolution selected (12, 10, 8 or 6 bits). For Analog watchdog 1, this parameter must be a
                                   number between Min_Data = 0x000 and Max_Data = 0xFFF, 0x3FF, 0xFF or 0x3F
                                   respectively. For Analog watchdog 2 and 3, this parameter must be a
                                   number between Min_Data = 0x00 and Max_Data = 0xFF.
                                   Note: Analog watchdog 2 and 3 are limited to a resolution of 8 bits: if ADC
                                         resolution is 12 bits the 4 LSB are ignored, if ADC resolution is 10 bits the 2
                                         LSB are ignored.
                                   Note: If ADC oversampling is enabled, ADC analog watchdog thresholds are
                                         impacted: the comparison of analog watchdog thresholds is done on
                                         oversampling final computation (after ratio and shift application):
                                         ADC data register bitfield [11:4] (12 most significant bits).*/

    uint32_t FilteringConfig;   /*!< Specify whether filtering should be use and the number of samples to consider.
                                   Before setting flag or raising interrupt, analog watchdog can wait to have several
                                   consecutive out-of-window samples. This parameter allows to configure this number.
                                   This parameter only applies to Analog watchdog 1. For others, use value
                                   ADC_AWD_FILTERING_NONE.
                                   This parameter can be a value of @ref ADC_analog_watchdog_filtering_config. */
} ADC_AnalogWDGConfTypeDef;



/**
  * @brief  Structure definition of ADC multimode
  * @note   The setting of these parameters by function ADCx_MultiModeConfigChannel() is conditioned by ADCs state
  *         (both Master and Slave ADCs).
  *         Both Master and Slave ADCs must be disabled.
  */
typedef struct
{
    uint32_t Mode;              /*!< Configures the ADC to operate in independent or multimode.
                                   This parameter can be a value of @ref ADC_MULTI_MODE. */

    uint32_t DMAAccessMode;     /*!< Configures the DMA mode for multimode ADC:
                                   selection whether 2 DMA channels (each ADC uses its own DMA channel) or 1 DMA channel
                                   (one DMA channel for both ADC, DMA of ADC master).
                                   This parameter can be a value of @ref ADC_MULTI_DMA_TRANSFER_RESOLUTION. */

    uint32_t DMAMode;           /*!< Specify whether the DMA requests are performed in one shot mode (DMA
                                   transfer stops when number of conversions is reached) or in continuous
                                   mode (DMA transfer unlimited, whatever number of conversions).
                                   This parameter can be a value of @ref ADC_MULTI_DMA_MODE.
                                   Note: In continuous mode, DMA must be configured in circular mode.
                                         Otherwise an overrun will be triggered when DMA buffer maximum
                                         pointer is reached. */

    uint32_t TwoSamplingDelay;  /*!< Configures the Delay between 2 sampling phases.
                                   This parameter can be a value of @ref ADC_MULTI_TWOSMP_DELAY.
                                   Delay range from 1 to 16 clock cycles  */
} ADC_MultiModeTypeDef;





/* Exported constants --------------------------------------------------------*/

/** @defgroup ADC_Exported_Constants
  * @{
  */
#define IS_ADC_ALL_PERIPH(PERIPH)                  (((PERIPH) == ADC1)   || \
                                                    ((PERIPH) == ADC2)   || \
                                                    ((PERIPH) == ADC3))
/**
  * @}
  */

/** @defgroup ADC_ClockMode - ClockPreScaler
  * @{
  */
#define ADC_CLOCK_SYNC_HCLK_DIV1        (uint32_t)ADC_CCR_CKMODE_0         /*!<  Synchronous clock mode no divided   */
#define ADC_CLOCK_SYNC_HCLK_DIV2        (uint32_t)ADC_CCR_CKMODE_1         /*!<  Synchronous clock mode divided by 2 */
#define ADC_CLOCK_SYNC_HCLK_DIV4        (uint32_t)ADC_CCR_CKMODE           /*!<  Synchronous clock mode divided by 4 */

#define ADC_CLOCK_ASYNC_DIV1            (uint32_t)0x00000000                                           /*!< ADC asynchronous clock without prescaler              */
#define ADC_CLOCK_ASYNC_DIV2            ((uint32_t)ADC_CCR_PRESC_0)                                    /*!< ADC asynchronous clock with prescaler division by 2   */
#define ADC_CLOCK_ASYNC_DIV4            ((uint32_t)ADC_CCR_PRESC_1)                                    /*!< ADC asynchronous clock with prescaler division by 4   */
#define ADC_CLOCK_ASYNC_DIV6            ((uint32_t)(ADC_CCR_PRESC_0|ADC_CCR_PRESC_1))                  /*!< ADC asynchronous clock with prescaler division by 6   */
#define ADC_CLOCK_ASYNC_DIV8            ((uint32_t)ADC_CCR_PRESC_2)                                    /*!< ADC asynchronous clock with prescaler division by 8   */
#define ADC_CLOCK_ASYNC_DIV10           ((uint32_t)(ADC_CCR_PRESC_0|ADC_CCR_PRESC_2))                  /*!< ADC asynchronous clock with prescaler division by 10  */
#define ADC_CLOCK_ASYNC_DIV12           ((uint32_t)(ADC_CCR_PRESC_1|ADC_CCR_PRESC_2))                  /*!< ADC asynchronous clock with prescaler division by 12  */
#define ADC_CLOCK_ASYNC_DIV16           ((uint32_t)(ADC_CCR_PRESC_0|ADC_CCR_PRESC_1|ADC_CCR_PRESC_2))  /*!< ADC asynchronous clock with prescaler division by 16  */
#define ADC_CLOCK_ASYNC_DIV32           ((uint32_t)ADC_CCR_PRESC_3)                                    /*!< ADC asynchronous clock with prescaler division by 32  */
#define ADC_CLOCK_ASYNC_DIV64           ((uint32_t)(ADC_CCR_PRESC_0|ADC_CCR_PRESC_3))                  /*!< ADC asynchronous clock with prescaler division by 64  */
#define ADC_CLOCK_ASYNC_DIV128          ((uint32_t)(ADC_CCR_PRESC_1|ADC_CCR_PRESC_3))                  /*!< ADC asynchronous clock with prescaler division by 128 */
#define ADC_CLOCK_ASYNC_DIV256          ((uint32_t)(ADC_CCR_PRESC_0|ADC_CCR_PRESC_1|ADC_CCR_PRESC_3))  /*!< ADC asynchronous clock with prescaler division by 256 */

#define IS_ADC_CLOCKPRESCALER(ADC_CLOCK)   (((ADC_CLOCK) == ADC_CLOCK_SYNC_HCLK_DIV1 )  ||\
                                            ((ADC_CLOCK) == ADC_CLOCK_SYNC_HCLK_DIV2 )  ||\
                                            ((ADC_CLOCK) == ADC_CLOCK_SYNC_HCLK_DIV4 )  ||\
                                            ((ADC_CLOCK) == ADC_CLOCK_ASYNC_DIV1     )  ||\
                                            ((ADC_CLOCK) == ADC_CLOCK_ASYNC_DIV2     )  ||\
                                            ((ADC_CLOCK) == ADC_CLOCK_ASYNC_DIV4     )  ||\
                                            ((ADC_CLOCK) == ADC_CLOCK_ASYNC_DIV6     )  ||\
                                            ((ADC_CLOCK) == ADC_CLOCK_ASYNC_DIV8     )  ||\
                                            ((ADC_CLOCK) == ADC_CLOCK_ASYNC_DIV10    )  ||\
                                            ((ADC_CLOCK) == ADC_CLOCK_ASYNC_DIV16    )  ||\
                                            ((ADC_CLOCK) == ADC_CLOCK_ASYNC_DIV32    )  ||\
                                            ((ADC_CLOCK) == ADC_CLOCK_ASYNC_DIV64    )  ||\
                                            ((ADC_CLOCK) == ADC_CLOCK_ASYNC_DIV128   )  ||\
                                            ((ADC_CLOCK) == ADC_CLOCK_ASYNC_DIV256   )  )
/**
  * @}
  */

/** @defgroup ADC_Resolution
  * @{
  */
#define ADC_RESOLUTION_6B              ((uint32_t)0x00000000)     /*!< ADC resolution 6  bits */
#define ADC_RESOLUTION_8B              ADC_CFGR1_RES_0            /*!< ADC resolution 8  bits */
#define ADC_RESOLUTION_10B             ADC_CFGR1_RES_1            /*!< ADC resolution 10 bits */
#define ADC_RESOLUTION_12B             ADC_CFGR1_RES              /*!< ADC resolution 12 bits */

#define IS_ADC_RESOLUTION(RESOLUTION) (((RESOLUTION) == ADC_RESOLUTION_12B) || \
                                       ((RESOLUTION) == ADC_RESOLUTION_10B) || \
                                       ((RESOLUTION) == ADC_RESOLUTION_8B)  || \
                                       ((RESOLUTION) == ADC_RESOLUTION_6B))
/**
  * @}
  */

/** @defgroup ADC_data_align ADC conversion data alignment
  * @{
  */
#define ADC_DATAALIGN_RIGHT                (uint32_t)0x00000000     /*!< ADC conversion data alignment: right aligned
                                                                         (alignment on data register LSB bit 0)*/
#define ADC_DATAALIGN_LEFT                 ADC_CFGR1_ALIGN          /*!< ADC conversion data alignment: left aligned
                                                                         (alignment on data register MSB bit 15)*/

#define IS_ADC_DATA_ALIGN(ALIGN)           (((ALIGN) == ADC_DATAALIGN_RIGHT) || \
                                            ((ALIGN) == ADC_DATAALIGN_LEFT))
/**
  * @}
  */

/** @efgroup ADC_regular_external_trigger_edge ADC group regular trigger edge (when external trigger is selected)
  * @{
  */
#define ADC_SOFTWARE_START                         ((uint32_t)0x00000000)  /*!< ADC group regular trigger
                                                                                disabled (SW start)*/
#define ADC_EXTERNALTRIGCONVEDGE_RISING            ADC_CFGR1_EXTEN_0       /*!< ADC group regular conversion
                                                                                trigger polarity set to rising edge */
#define ADC_EXTERNALTRIGCONVEDGE_FALLING           ADC_CFGR1_EXTEN_1       /*!< ADC group regular conversion
                                                                                trigger polarity set to falling edge */
#define ADC_EXTERNALTRIGCONVEDGE_RISINGFALLING     ADC_CFGR1_EXTEN         /*!< ADC group regular conversion
                                                                                trigger polarity set to both rising and falling edges */

#define IS_ADC_EXT_TRIG_EDGE(EDGE)                (((EDGE) == ADC_SOFTWARE_START               )  || \
                                                   ((EDGE) == ADC_EXTERNALTRIGCONVEDGE_RISING  )  || \
                                                   ((EDGE) == ADC_EXTERNALTRIGCONVEDGE_FALLING )  || \
                                                   ((EDGE) == ADC_EXTERNALTRIGCONVEDGE_RISINGFALLING))
/**
  * @}
  */

/** @defgroup ADC_injected_external_trigger_edge ADC group injected trigger edge (when external trigger is selected)
  * @{
  */
#define ADC_INJECTED_SOFTWARE_START                  ((uint32_t)0x00000000)/*!< Injected conversions trigger
                                                                                disabled (SW start)*/
#define ADC_EXTERNALTRIGINJECCONVEDGE_RISING         (ADC_JSQR_JEXTEN_0)   /*!< Injected conversions trigger
                                                                                polarity set to rising edge */
#define ADC_EXTERNALTRIGINJECCONVEDGE_FALLING        (ADC_JSQR_JEXTEN_1)   /*!< Injected conversions trigger
                                                                                polarity set to falling edge */
#define ADC_EXTERNALTRIGINJECCONVEDGE_RISINGFALLING  (ADC_JSQR_JEXTEN)     /*!< Injected conversions trigger
                                                                                polarity set to both rising and falling edges */

#define IS_ADC_EXTTRIG_INJEC_EDGE(EDGE)            (((EDGE) == ADC_INJECTED_SOFTWARE_START          )  || \
                                                    ((EDGE) == ADC_EXTERNALTRIGINJECCONVEDGE_RISING )  || \
                                                    ((EDGE) == ADC_EXTERNALTRIGINJECCONVEDGE_FALLING)  || \
                                                    ((EDGE) == ADC_EXTERNALTRIGINJECCONVEDGE_RISINGFALLING))
/**
  * @}
  */

/** @defgroup ADC12_external_trigger_sources for ADC1/2 regular channels conversion
  * @{
  */
#define ADC12_EXTERNALTRIG_TIM1_CC1               ((uint32_t)0x00000000)
#define ADC12_EXTERNALTRIG_TIM1_CC2               ((uint32_t)ADC_CFGR1_EXTSEL_0)
#define ADC12_EXTERNALTRIG_TIM1_CC3               ((uint32_t)ADC_CFGR1_EXTSEL_1)
#define ADC12_EXTERNALTRIG_TIM2_CC2               ((uint32_t)(ADC_CFGR1_EXTSEL_0|ADC_CFGR1_EXTSEL_1))
#define ADC12_EXTERNALTRIG_TIM3_TRGO              ((uint32_t)ADC_CFGR1_EXTSEL_2)
#define ADC12_EXTERNALTRIG_TIM4_CC4               ((uint32_t)(ADC_CFGR1_EXTSEL_0|ADC_CFGR1_EXTSEL_2))
#define ADC12_EXTERNALTRIG_TIM8_TRGO              ((uint32_t)(ADC_CFGR1_EXTSEL_1|ADC_CFGR1_EXTSEL_2))
#define ADC12_EXTERNALTRIG_TIM8_TRGO2             ((uint32_t)(ADC_CFGR1_EXTSEL_0|ADC_CFGR1_EXTSEL_1|ADC_CFGR1_EXTSEL_2))
#define ADC12_EXTERNALTRIG_TIM1_TRGO              ((uint32_t)ADC_CFGR1_EXTSEL_3)
#define ADC12_EXTERNALTRIG_TIM1_TRGO2             ((uint32_t)(ADC_CFGR1_EXTSEL_0|ADC_CFGR1_EXTSEL_3))
#define ADC12_EXTERNALTRIG_TIM2_TRGO              ((uint32_t)(ADC_CFGR1_EXTSEL_1|ADC_CFGR1_EXTSEL_3))
#define ADC12_EXTERNALTRIG_TIM4_TRGO              ((uint32_t)(ADC_CFGR1_EXTSEL_0|ADC_CFGR1_EXTSEL_1|ADC_CFGR1_EXTSEL_3))
#define ADC12_EXTERNALTRIG_TIM6_TRGO              ((uint32_t)(ADC_CFGR1_EXTSEL_2|ADC_CFGR1_EXTSEL_3))
#define ADC12_EXTERNALTRIG_TIM3_CC4               ((uint32_t)(ADC_CFGR1_EXTSEL_0|ADC_CFGR1_EXTSEL_2|ADC_CFGR1_EXTSEL_3))
#define ADC12_EXTERNALTRIG_EPWM1_SOCA             ((uint32_t)(ADC_CFGR1_EXTSEL_1|ADC_CFGR1_EXTSEL_2|ADC_CFGR1_EXTSEL_3))
#define ADC12_EXTERNALTRIG_EPWM2_SOCA             ((uint32_t)(ADC_CFGR1_EXTSEL_0|ADC_CFGR1_EXTSEL_1|ADC_CFGR1_EXTSEL_2|ADC_CFGR1_EXTSEL_3))
#define ADC12_EXTERNALTRIG_EPWM3_SOCA             ((uint32_t)ADC_CFGR1_EXTSEL_4)
#define ADC12_EXTERNALTRIG_EPWM3_SOCB             ((uint32_t)(ADC_CFGR1_EXTSEL_0|ADC_CFGR1_EXTSEL_4))
#define ADC12_EXTERNALTRIG_EPWM4_SOCA             ((uint32_t)(ADC_CFGR1_EXTSEL_1|ADC_CFGR1_EXTSEL_4))
#define ADC12_EXTERNALTRIG_EPWM4_SOCB             ((uint32_t)(ADC_CFGR1_EXTSEL_0|ADC_CFGR1_EXTSEL_1|ADC_CFGR1_EXTSEL_4))
#define ADC12_EXTERNALTRIG_LPTIM_OUT              ((uint32_t)(ADC_CFGR1_EXTSEL_2|ADC_CFGR1_EXTSEL_4))
#define ADC12_EXTERNALTRIG_TIM7_TRGO              ((uint32_t)(ADC_CFGR1_EXTSEL_0|ADC_CFGR1_EXTSEL_2|ADC_CFGR1_EXTSEL_4))
#define ADC12_EXTERNALTRIG_EXTI11                 ((uint32_t)(ADC_CFGR1_EXTSEL_1|ADC_CFGR1_EXTSEL_2|ADC_CFGR1_EXTSEL_4))

#define IS_ADC12_REGULAR_EXTTRIG_SOURCE(SOURCE)     (((SOURCE) == ADC12_EXTERNALTRIG_TIM1_CC1    )  ||\
                                                     ((SOURCE) == ADC12_EXTERNALTRIG_TIM1_CC2    )  ||\
                                                     ((SOURCE) == ADC12_EXTERNALTRIG_TIM1_CC3    )  ||\
                                                     ((SOURCE) == ADC12_EXTERNALTRIG_TIM2_CC2    )  ||\
                                                     ((SOURCE) == ADC12_EXTERNALTRIG_TIM3_TRGO   )  ||\
                                                     ((SOURCE) == ADC12_EXTERNALTRIG_TIM4_CC4    )  ||\
                                                     ((SOURCE) == ADC12_EXTERNALTRIG_TIM8_TRGO   )  ||\
                                                     ((SOURCE) == ADC12_EXTERNALTRIG_TIM8_TRGO2  )  ||\
                                                     ((SOURCE) == ADC12_EXTERNALTRIG_TIM1_TRGO   )  ||\
                                                     ((SOURCE) == ADC12_EXTERNALTRIG_TIM1_TRGO2  )  ||\
                                                     ((SOURCE) == ADC12_EXTERNALTRIG_TIM2_TRGO   )  ||\
                                                     ((SOURCE) == ADC12_EXTERNALTRIG_TIM4_TRGO   )  ||\
                                                     ((SOURCE) == ADC12_EXTERNALTRIG_TIM6_TRGO   )  ||\
                                                     ((SOURCE) == ADC12_EXTERNALTRIG_TIM3_CC4    )  ||\
                                                     ((SOURCE) == ADC12_EXTERNALTRIG_EPWM1_SOCA  )  ||\
                                                     ((SOURCE) == ADC12_EXTERNALTRIG_EPWM2_SOCA  )  ||\
                                                     ((SOURCE) == ADC12_EXTERNALTRIG_EPWM3_SOCA  )  ||\
                                                     ((SOURCE) == ADC12_EXTERNALTRIG_EPWM3_SOCB  )  ||\
                                                     ((SOURCE) == ADC12_EXTERNALTRIG_EPWM4_SOCA  )  ||\
                                                     ((SOURCE) == ADC12_EXTERNALTRIG_EPWM4_SOCB  )  ||\
                                                     ((SOURCE) == ADC12_EXTERNALTRIG_LPTIM_OUT   )  ||\
                                                     ((SOURCE) == ADC12_EXTERNALTRIG_TIM7_TRGO   )  ||\
                                                     ((SOURCE) == ADC12_EXTERNALTRIG_EXTI11      )  )
/**
  * @}
  */

/** @defgroup ADC3_external_trigger_sources for ADC3 regular channels conversion
  * @{
  */
#define ADC3_EXTERNALTRIG_TIM3_CC1               ((uint32_t)0x00000000)
#define ADC3_EXTERNALTRIG_TIM2_CC3               ((uint32_t)ADC_CFGR1_EXTSEL_0)
#define ADC3_EXTERNALTRIG_TIM1_CC3               ((uint32_t)ADC_CFGR1_EXTSEL_1)
#define ADC3_EXTERNALTRIG_TIM8_CC1               ((uint32_t)(ADC_CFGR1_EXTSEL_0|ADC_CFGR1_EXTSEL_1))
#define ADC3_EXTERNALTRIG_TIM3_TRGO              ((uint32_t)ADC_CFGR1_EXTSEL_2)
#define ADC3_EXTERNALTRIG_TIM4_CC1               ((uint32_t)(ADC_CFGR1_EXTSEL_0|ADC_CFGR1_EXTSEL_2))
#define ADC3_EXTERNALTRIG_TIM8_TRGO              ((uint32_t)(ADC_CFGR1_EXTSEL_1|ADC_CFGR1_EXTSEL_2))
#define ADC3_EXTERNALTRIG_TIM8_TRGO2             ((uint32_t)(ADC_CFGR1_EXTSEL_0|ADC_CFGR1_EXTSEL_1|ADC_CFGR1_EXTSEL_2))
#define ADC3_EXTERNALTRIG_TIM1_TRGO              ((uint32_t)ADC_CFGR1_EXTSEL_3)
#define ADC3_EXTERNALTRIG_TIM1_TRGO2             ((uint32_t)(ADC_CFGR1_EXTSEL_0|ADC_CFGR1_EXTSEL_3))
#define ADC3_EXTERNALTRIG_TIM2_TRGO              ((uint32_t)(ADC_CFGR1_EXTSEL_1|ADC_CFGR1_EXTSEL_3))
#define ADC3_EXTERNALTRIG_TIM4_TRGO              ((uint32_t)(ADC_CFGR1_EXTSEL_0|ADC_CFGR1_EXTSEL_1|ADC_CFGR1_EXTSEL_3))
#define ADC3_EXTERNALTRIG_TIM6_TRGO              ((uint32_t)(ADC_CFGR1_EXTSEL_2|ADC_CFGR1_EXTSEL_3))
#define ADC3_EXTERNALTRIG_TIM2_CC1               ((uint32_t)(ADC_CFGR1_EXTSEL_0|ADC_CFGR1_EXTSEL_2|ADC_CFGR1_EXTSEL_3))
#define ADC3_EXTERNALTRIG_EPWM1_SOCB             ((uint32_t)(ADC_CFGR1_EXTSEL_1|ADC_CFGR1_EXTSEL_2|ADC_CFGR1_EXTSEL_3))
#define ADC3_EXTERNALTRIG_EPWM2_SOCB             ((uint32_t)(ADC_CFGR1_EXTSEL_0|ADC_CFGR1_EXTSEL_1|ADC_CFGR1_EXTSEL_2|ADC_CFGR1_EXTSEL_3))
#define ADC3_EXTERNALTRIG_EPWM1_SOCA             ((uint32_t)ADC_CFGR1_EXTSEL_4)
#define ADC3_EXTERNALTRIG_EPWM2_SOCA             ((uint32_t)(ADC_CFGR1_EXTSEL_0|ADC_CFGR1_EXTSEL_4))
#define ADC3_EXTERNALTRIG_EPWM3_SOCA             ((uint32_t)(ADC_CFGR1_EXTSEL_1|ADC_CFGR1_EXTSEL_4))
#define ADC3_EXTERNALTRIG_EPWM3_SOCB             ((uint32_t)(ADC_CFGR1_EXTSEL_0|ADC_CFGR1_EXTSEL_1|ADC_CFGR1_EXTSEL_4))
#define ADC3_EXTERNALTRIG_EPWM4_SOCA             ((uint32_t)(ADC_CFGR1_EXTSEL_2|ADC_CFGR1_EXTSEL_4))
#define ADC3_EXTERNALTRIG_EPWM4_SOCB             ((uint32_t)(ADC_CFGR1_EXTSEL_0|ADC_CFGR1_EXTSEL_2|ADC_CFGR1_EXTSEL_4))
#define ADC3_EXTERNALTRIG_LPTIM_OUT              ((uint32_t)(ADC_CFGR1_EXTSEL_1|ADC_CFGR1_EXTSEL_2|ADC_CFGR1_EXTSEL_4))
#define ADC3_EXTERNALTRIG_TIM7_TRGO              ((uint32_t)(ADC_CFGR1_EXTSEL_0|ADC_CFGR1_EXTSEL_1|ADC_CFGR1_EXTSEL_2|ADC_CFGR1_EXTSEL_4))
#define ADC3_EXTERNALTRIG_EXTI2                  ((uint32_t)(ADC_CFGR1_EXTSEL_3|ADC_CFGR1_EXTSEL_4))

#define IS_ADC3_REGULAR_EXTTRIG_SOURCE(SOURCE)      (((SOURCE) == ADC3_EXTERNALTRIG_TIM3_CC1    )   ||\
                                                     ((SOURCE) == ADC3_EXTERNALTRIG_TIM2_CC3    )   ||\
                                                     ((SOURCE) == ADC3_EXTERNALTRIG_TIM1_CC3    )   ||\
                                                     ((SOURCE) == ADC3_EXTERNALTRIG_TIM8_CC1    )   ||\
                                                     ((SOURCE) == ADC3_EXTERNALTRIG_TIM3_TRGO   )   ||\
                                                     ((SOURCE) == ADC3_EXTERNALTRIG_TIM4_CC1    )   ||\
                                                     ((SOURCE) == ADC3_EXTERNALTRIG_TIM8_TRGO   )   ||\
                                                     ((SOURCE) == ADC3_EXTERNALTRIG_TIM8_TRGO2  )   ||\
                                                     ((SOURCE) == ADC3_EXTERNALTRIG_TIM1_TRGO   )   ||\
                                                     ((SOURCE) == ADC3_EXTERNALTRIG_TIM1_TRGO2  )   ||\
                                                     ((SOURCE) == ADC3_EXTERNALTRIG_TIM2_TRGO   )   ||\
                                                     ((SOURCE) == ADC3_EXTERNALTRIG_TIM4_TRGO   )   ||\
                                                     ((SOURCE) == ADC3_EXTERNALTRIG_TIM6_TRGO   )   ||\
                                                     ((SOURCE) == ADC3_EXTERNALTRIG_TIM2_CC1    )   ||\
                                                     ((SOURCE) == ADC3_EXTERNALTRIG_EPWM1_SOCB  )   ||\
                                                     ((SOURCE) == ADC3_EXTERNALTRIG_EPWM2_SOCB  )   ||\
                                                     ((SOURCE) == ADC3_EXTERNALTRIG_EPWM1_SOCA  )   ||\
                                                     ((SOURCE) == ADC3_EXTERNALTRIG_EPWM2_SOCA  )   ||\
                                                     ((SOURCE) == ADC3_EXTERNALTRIG_EPWM3_SOCA  )   ||\
                                                     ((SOURCE) == ADC3_EXTERNALTRIG_EPWM3_SOCB  )   ||\
                                                     ((SOURCE) == ADC3_EXTERNALTRIG_EPWM4_SOCA  )   ||\
                                                     ((SOURCE) == ADC3_EXTERNALTRIG_EPWM4_SOCB  )   ||\
                                                     ((SOURCE) == ADC3_EXTERNALTRIG_LPTIM_OUT   )   ||\
                                                     ((SOURCE) == ADC3_EXTERNALTRIG_TIM7_TRGO   )   ||\
                                                     ((SOURCE) == ADC3_EXTERNALTRIG_EXTI2       )   )
/**
  * @}
  */


#define IS_ADC_REGULAR_EXTTRIG_SOURCE(ADCx, SOURCE)  ((((ADCx == ADC1) || (ADCx == ADC2)) && IS_ADC12_REGULAR_EXTTRIG_SOURCE(SOURCE)) || \
                                                       ((ADCx == ADC3) && IS_ADC3_REGULAR_EXTTRIG_SOURCE(SOURCE)))




/** @defgroup ADC12_injected_external_trigger_sources for ADC1/2 injected channels conversion
  * @{
  */
#define ADC12_EXTERNALTRIG_INJ_TIM1_CC1               ((uint32_t)0x00000000)
#define ADC12_EXTERNALTRIG_INJ_TIM1_CC4               ((uint32_t)ADC_JSQR_JEXTSEL_0)
#define ADC12_EXTERNALTRIG_INJ_TIM2_TRGO              ((uint32_t)ADC_JSQR_JEXTSEL_1)
#define ADC12_EXTERNALTRIG_INJ_TIM2_CC1               ((uint32_t)(ADC_JSQR_JEXTSEL_0|ADC_JSQR_JEXTSEL_1))
#define ADC12_EXTERNALTRIG_INJ_TIM3_CC4               ((uint32_t)ADC_JSQR_JEXTSEL_2)
#define ADC12_EXTERNALTRIG_INJ_TIM4_TRGO              ((uint32_t)(ADC_JSQR_JEXTSEL_0|ADC_JSQR_JEXTSEL_2))
#define ADC12_EXTERNALTRIG_INJ_TIM8_CC4               ((uint32_t)(ADC_JSQR_JEXTSEL_1|ADC_JSQR_JEXTSEL_2))
#define ADC12_EXTERNALTRIG_INJ_TIM1_TRGO2             ((uint32_t)(ADC_JSQR_JEXTSEL_0|ADC_JSQR_JEXTSEL_1|ADC_JSQR_JEXTSEL_2))
#define ADC12_EXTERNALTRIG_INJ_TIM8_TRGO              ((uint32_t)ADC_JSQR_JEXTSEL_3)
#define ADC12_EXTERNALTRIG_INJ_TIM8_TRGO2             ((uint32_t)(ADC_JSQR_JEXTSEL_0|ADC_JSQR_JEXTSEL_3))
#define ADC12_EXTERNALTRIG_INJ_TIM3_CC3               ((uint32_t)(ADC_JSQR_JEXTSEL_1|ADC_JSQR_JEXTSEL_3))
#define ADC12_EXTERNALTRIG_INJ_TIM3_TRGO              ((uint32_t)(ADC_JSQR_JEXTSEL_0|ADC_JSQR_JEXTSEL_1|ADC_JSQR_JEXTSEL_3))
#define ADC12_EXTERNALTRIG_INJ_TIM3_CC1               ((uint32_t)(ADC_JSQR_JEXTSEL_2|ADC_JSQR_JEXTSEL_3))
#define ADC12_EXTERNALTRIG_INJ_TIM6_TRGO              ((uint32_t)(ADC_JSQR_JEXTSEL_0|ADC_JSQR_JEXTSEL_2|ADC_JSQR_JEXTSEL_3))
#define ADC12_EXTERNALTRIG_INJ_EPWM1_SOCB             ((uint32_t)(ADC_JSQR_JEXTSEL_1|ADC_JSQR_JEXTSEL_2|ADC_JSQR_JEXTSEL_3))
#define ADC12_EXTERNALTRIG_INJ_EPWM2_SOCB             ((uint32_t)(ADC_JSQR_JEXTSEL_0|ADC_JSQR_JEXTSEL_1|ADC_JSQR_JEXTSEL_2|ADC_JSQR_JEXTSEL_3))
#define ADC12_EXTERNALTRIG_INJ_EPWM3_SOCA             ((uint32_t)ADC_JSQR_JEXTSEL_4)
#define ADC12_EXTERNALTRIG_INJ_EPWM3_SOCB             ((uint32_t)(ADC_JSQR_JEXTSEL_0|ADC_JSQR_JEXTSEL_4))
#define ADC12_EXTERNALTRIG_INJ_EPWM4_SOCA             ((uint32_t)(ADC_JSQR_JEXTSEL_1|ADC_JSQR_JEXTSEL_4))
#define ADC12_EXTERNALTRIG_INJ_EPWM4_SOCB             ((uint32_t)(ADC_JSQR_JEXTSEL_0|ADC_JSQR_JEXTSEL_1|ADC_JSQR_JEXTSEL_4))
#define ADC12_EXTERNALTRIG_INJ_LPTIM_OUT              ((uint32_t)(ADC_JSQR_JEXTSEL_2|ADC_JSQR_JEXTSEL_4))
#define ADC12_EXTERNALTRIG_INJ_TIM7_TRGO              ((uint32_t)(ADC_JSQR_JEXTSEL_0|ADC_JSQR_JEXTSEL_2|ADC_JSQR_JEXTSEL_4))
#define ADC12_EXTERNALTRIG_INJ_EXTI15                 ((uint32_t)(ADC_JSQR_JEXTSEL_1|ADC_JSQR_JEXTSEL_2|ADC_JSQR_JEXTSEL_4))

#define IS_ADC12_INJECTED_EXTTRIG_SOURCE(SOURCE)         (((SOURCE) == ADC12_EXTERNALTRIG_INJ_TIM1_CC1    )  ||\
                                                          ((SOURCE) == ADC12_EXTERNALTRIG_INJ_TIM1_CC4    )  ||\
                                                          ((SOURCE) == ADC12_EXTERNALTRIG_INJ_TIM2_TRGO   )  ||\
                                                          ((SOURCE) == ADC12_EXTERNALTRIG_INJ_TIM2_CC1    )  ||\
                                                          ((SOURCE) == ADC12_EXTERNALTRIG_INJ_TIM3_CC4    )  ||\
                                                          ((SOURCE) == ADC12_EXTERNALTRIG_INJ_TIM4_TRGO   )  ||\
                                                          ((SOURCE) == ADC12_EXTERNALTRIG_INJ_TIM8_CC4    )  ||\
                                                          ((SOURCE) == ADC12_EXTERNALTRIG_INJ_TIM1_TRGO2  )  ||\
                                                          ((SOURCE) == ADC12_EXTERNALTRIG_INJ_TIM8_TRGO   )  ||\
                                                          ((SOURCE) == ADC12_EXTERNALTRIG_INJ_TIM8_TRGO2  )  ||\
                                                          ((SOURCE) == ADC12_EXTERNALTRIG_INJ_TIM3_CC3    )  ||\
                                                          ((SOURCE) == ADC12_EXTERNALTRIG_INJ_TIM3_TRGO   )  ||\
                                                          ((SOURCE) == ADC12_EXTERNALTRIG_INJ_TIM3_CC1    )  ||\
                                                          ((SOURCE) == ADC12_EXTERNALTRIG_INJ_TIM6_TRGO   )  ||\
                                                          ((SOURCE) == ADC12_EXTERNALTRIG_INJ_EPWM1_SOCB  )  ||\
                                                          ((SOURCE) == ADC12_EXTERNALTRIG_INJ_EPWM2_SOCB  )  ||\
                                                          ((SOURCE) == ADC12_EXTERNALTRIG_INJ_EPWM3_SOCA  )  ||\
                                                          ((SOURCE) == ADC12_EXTERNALTRIG_INJ_EPWM3_SOCB  )  ||\
                                                          ((SOURCE) == ADC12_EXTERNALTRIG_INJ_EPWM4_SOCA  )  ||\
                                                          ((SOURCE) == ADC12_EXTERNALTRIG_INJ_EPWM4_SOCB  )  ||\
                                                          ((SOURCE) == ADC12_EXTERNALTRIG_INJ_LPTIM_OUT   )  ||\
                                                          ((SOURCE) == ADC12_EXTERNALTRIG_INJ_TIM7_TRGO   )  ||\
                                                          ((SOURCE) == ADC12_EXTERNALTRIG_INJ_EXTI15      )  )
/**
  * @}
  */

/** @defgroup ADC3_injected_external_trigger_sources for ADC3 injected channels conversion
  * @{
  */
#define ADC3_EXTERNALTRIG_INJ_TIM1_TRGO              ((uint32_t)0x00000000)
#define ADC3_EXTERNALTRIG_INJ_TIM1_CC4               ((uint32_t)ADC_JSQR_JEXTSEL_0)
#define ADC3_EXTERNALTRIG_INJ_TIM2_TRGO              ((uint32_t)ADC_JSQR_JEXTSEL_1)
#define ADC3_EXTERNALTRIG_INJ_TIM8_CC2               ((uint32_t)(ADC_JSQR_JEXTSEL_0|ADC_JSQR_JEXTSEL_1))
#define ADC3_EXTERNALTRIG_INJ_TIM4_CC3               ((uint32_t)ADC_JSQR_JEXTSEL_2)
#define ADC3_EXTERNALTRIG_INJ_TIM4_TRGO              ((uint32_t)(ADC_JSQR_JEXTSEL_0|ADC_JSQR_JEXTSEL_2))
#define ADC3_EXTERNALTRIG_INJ_TIM4_CC4               ((uint32_t)(ADC_JSQR_JEXTSEL_1|ADC_JSQR_JEXTSEL_2))
#define ADC3_EXTERNALTRIG_INJ_TIM8_CC4               ((uint32_t)(ADC_JSQR_JEXTSEL_0|ADC_JSQR_JEXTSEL_1|ADC_JSQR_JEXTSEL_2))
#define ADC3_EXTERNALTRIG_INJ_TIM1_TRGO2             ((uint32_t)ADC_JSQR_JEXTSEL_3)
#define ADC3_EXTERNALTRIG_INJ_TIM8_TRGO              ((uint32_t)(ADC_JSQR_JEXTSEL_0|ADC_JSQR_JEXTSEL_3))
#define ADC3_EXTERNALTRIG_INJ_TIM8_TRGO2             ((uint32_t)(ADC_JSQR_JEXTSEL_1|ADC_JSQR_JEXTSEL_3))
#define ADC3_EXTERNALTRIG_INJ_TIM1_CC3               ((uint32_t)(ADC_JSQR_JEXTSEL_0|ADC_JSQR_JEXTSEL_1|ADC_JSQR_JEXTSEL_3))
#define ADC3_EXTERNALTRIG_INJ_TIM3_TRGO              ((uint32_t)(ADC_JSQR_JEXTSEL_2|ADC_JSQR_JEXTSEL_3))
#define ADC3_EXTERNALTRIG_INJ_TIM6_TRGO              ((uint32_t)(ADC_JSQR_JEXTSEL_0|ADC_JSQR_JEXTSEL_2|ADC_JSQR_JEXTSEL_3))
#define ADC3_EXTERNALTRIG_INJ_EPWM1_SOCB             ((uint32_t)(ADC_JSQR_JEXTSEL_1|ADC_JSQR_JEXTSEL_2|ADC_JSQR_JEXTSEL_3))
#define ADC3_EXTERNALTRIG_INJ_EPWM2_SOCB             ((uint32_t)(ADC_JSQR_JEXTSEL_0|ADC_JSQR_JEXTSEL_1|ADC_JSQR_JEXTSEL_2|ADC_JSQR_JEXTSEL_3))
#define ADC3_EXTERNALTRIG_INJ_EPWM3_SOCA             ((uint32_t)ADC_JSQR_JEXTSEL_4)
#define ADC3_EXTERNALTRIG_INJ_EPWM3_SOCB             ((uint32_t)(ADC_JSQR_JEXTSEL_0|ADC_JSQR_JEXTSEL_4))
#define ADC3_EXTERNALTRIG_INJ_EPWM4_SOCA             ((uint32_t)(ADC_JSQR_JEXTSEL_1|ADC_JSQR_JEXTSEL_4))
#define ADC3_EXTERNALTRIG_INJ_EPWM4_SOCB             ((uint32_t)(ADC_JSQR_JEXTSEL_0|ADC_JSQR_JEXTSEL_1|ADC_JSQR_JEXTSEL_4))
#define ADC3_EXTERNALTRIG_INJ_EPWM1_SOCA             ((uint32_t)(ADC_JSQR_JEXTSEL_2|ADC_JSQR_JEXTSEL_4))
#define ADC3_EXTERNALTRIG_INJ_EPWM2_SOCA             ((uint32_t)(ADC_JSQR_JEXTSEL_0|ADC_JSQR_JEXTSEL_2|ADC_JSQR_JEXTSEL_4))
#define ADC3_EXTERNALTRIG_INJ_LPTIM_OUT              ((uint32_t)(ADC_JSQR_JEXTSEL_1|ADC_JSQR_JEXTSEL_2|ADC_JSQR_JEXTSEL_4))
#define ADC3_EXTERNALTRIG_INJ_TIM7_TRGO              ((uint32_t)(ADC_JSQR_JEXTSEL_0|ADC_JSQR_JEXTSEL_1|ADC_JSQR_JEXTSEL_2|ADC_JSQR_JEXTSEL_4))
#define ADC3_EXTERNALTRIG_INJ_EXTI3                  ((uint32_t)(ADC_JSQR_JEXTSEL_3|ADC_JSQR_JEXTSEL_4))

#define IS_ADC3_INJECTED_EXTTRIG_SOURCE(SOURCE)     (((SOURCE) == ADC3_EXTERNALTRIG_INJ_TIM1_TRGO   )   ||\
                                                     ((SOURCE) == ADC3_EXTERNALTRIG_INJ_TIM1_CC4    )   ||\
                                                     ((SOURCE) == ADC3_EXTERNALTRIG_INJ_TIM2_TRGO   )   ||\
                                                     ((SOURCE) == ADC3_EXTERNALTRIG_INJ_TIM8_CC2    )   ||\
                                                     ((SOURCE) == ADC3_EXTERNALTRIG_INJ_TIM4_CC3    )   ||\
                                                     ((SOURCE) == ADC3_EXTERNALTRIG_INJ_TIM4_TRGO   )   ||\
                                                     ((SOURCE) == ADC3_EXTERNALTRIG_INJ_TIM4_CC4    )   ||\
                                                     ((SOURCE) == ADC3_EXTERNALTRIG_INJ_TIM8_CC4    )   ||\
                                                     ((SOURCE) == ADC3_EXTERNALTRIG_INJ_TIM1_TRGO2  )   ||\
                                                     ((SOURCE) == ADC3_EXTERNALTRIG_INJ_TIM8_TRGO   )   ||\
                                                     ((SOURCE) == ADC3_EXTERNALTRIG_INJ_TIM8_TRGO2  )   ||\
                                                     ((SOURCE) == ADC3_EXTERNALTRIG_INJ_TIM1_CC3    )   ||\
                                                     ((SOURCE) == ADC3_EXTERNALTRIG_INJ_TIM3_TRGO   )   ||\
                                                     ((SOURCE) == ADC3_EXTERNALTRIG_INJ_TIM6_TRGO   )   ||\
                                                     ((SOURCE) == ADC3_EXTERNALTRIG_INJ_EPWM1_SOCB  )   ||\
                                                     ((SOURCE) == ADC3_EXTERNALTRIG_INJ_EPWM2_SOCB  )   ||\
                                                     ((SOURCE) == ADC3_EXTERNALTRIG_INJ_EPWM3_SOCA  )   ||\
                                                     ((SOURCE) == ADC3_EXTERNALTRIG_INJ_EPWM3_SOCB  )   ||\
                                                     ((SOURCE) == ADC3_EXTERNALTRIG_INJ_EPWM4_SOCA  )   ||\
                                                     ((SOURCE) == ADC3_EXTERNALTRIG_INJ_EPWM4_SOCB  )   ||\
                                                     ((SOURCE) == ADC3_EXTERNALTRIG_INJ_EPWM1_SOCA  )   ||\
                                                     ((SOURCE) == ADC3_EXTERNALTRIG_INJ_EPWM2_SOCA  )   ||\
                                                     ((SOURCE) == ADC3_EXTERNALTRIG_INJ_LPTIM_OUT   )   ||\
                                                     ((SOURCE) == ADC3_EXTERNALTRIG_INJ_TIM7_TRGO   )   ||\
                                                     ((SOURCE) == ADC3_EXTERNALTRIG_INJ_EXTI3       )   )
/**
  * @}
  */

#define IS_ADC_INJECTED_EXTTRIG_SOURCE(ADCx, SOURCE)  ((((ADCx == ADC1) || (ADCx == ADC2)) && IS_ADC12_INJECTED_EXTTRIG_SOURCE(SOURCE)) || \
                                                       ((ADCx == ADC3) && IS_ADC3_INJECTED_EXTTRIG_SOURCE(SOURCE)))




/** @defgroup ADC_DMA_Mode
  * @{
  */

#define ADC_DMAMODE_ONESHOT                        ((uint32_t)0x00000000)
#define ADC_DMAMODE_CIRCULAR                       ADC_CFGR1_DMACFG

#define IS_ADC_DMA_MODE(MODE) (((MODE) == ADC_DMAMODE_ONESHOT) || \
                               ((MODE) == ADC_DMAMODE_CIRCULAR))
/**
  * @}
  */


/** @defgroup ADCx_AnalogWatchdog_X_Selection
  * @{
  */
#define ADC_ANALOGWATCHDOG_1                        ((uint32_t)0x00000001)
#define ADC_ANALOGWATCHDOG_2                        ((uint32_t)0x00000002)
#define ADC_ANALOGWATCHDOG_3                        ((uint32_t)0x00000004)

#define  IS_ADC_ANALOG_WATCHDOG_NUMBER(NUMBER)      (((NUMBER) == ADC_ANALOGWATCHDOG_1) ||\
                                                     ((NUMBER) == ADC_ANALOGWATCHDOG_2) ||\
                                                     ((NUMBER) == ADC_ANALOGWATCHDOG_3))


/**
  * @}
  */

/** @defgroup ADCx_AnalogWatchdog_1_Channel_Mode_Selection
  * @{
  */
#define ADC_ANALOGWATCHDOG_NONE                    ((uint32_t)0x00000000)
/*!< ADC AWD not selected */

#define ADC_ANALOGWATCHDOG_SINGLE_REG              ((uint32_t)(ADC_CFGR1_AWD1SGL|ADC_CFGR1_AWD1EN))
/*!< ADC AWD applied to a regular group single channel */

#define ADC_ANALOGWATCHDOG_SINGLE_INJEC            ((uint32_t)(ADC_CFGR1_AWD1SGL|ADC_CFGR1_JAWD1EN))
/*!< ADC AWD applied to an injected group single channel */

#define ADC_ANALOGWATCHDOG_SINGLE_REGINJEC         ((uint32_t)(ADC_CFGR1_AWD1SGL|ADC_CFGR1_AWD1EN|ADC_CFGR1_JAWD1EN))
/*!< ADC AWD applied to a regular and injected groups single channel */

#define ADC_ANALOGWATCHDOG_ALL_REG                 ((uint32_t)ADC_CFGR1_AWD1EN)
/*!< ADC AWD applied to regular group all channels */

#define ADC_ANALOGWATCHDOG_ALL_INJEC               ((uint32_t)ADC_CFGR1_JAWD1EN)
/*!< ADC AWD applied to injected group all channels */

#define ADC_ANALOGWATCHDOG_ALL_REGINJEC            ((uint32_t)(ADC_CFGR1_AWD1EN|ADC_CFGR1_JAWD1EN))
/*!< ADC AWD applied to regular and injected groups all channels */


#define IS_ADC_ANALOG_WATCHDOG_1_MODE(MODE)          (((MODE) == ADC_ANALOGWATCHDOG_NONE)            ||\
                                                      ((MODE) == ADC_ANALOGWATCHDOG_SINGLE_REG)      ||\
                                                      ((MODE) == ADC_ANALOGWATCHDOG_SINGLE_INJEC)    ||\
                                                      ((MODE) == ADC_ANALOGWATCHDOG_SINGLE_REGINJEC) ||\
                                                      ((MODE) == ADC_ANALOGWATCHDOG_ALL_REG)         ||\
                                                      ((MODE) == ADC_ANALOGWATCHDOG_ALL_INJEC)       ||\
                                                      ((MODE) == ADC_ANALOGWATCHDOG_ALL_REGINJEC))
/**
  * @}
  */

/** @defgroup ADCx_AnalogWatchdog_2_3_Channel_Selection
  * @{
  */
#define ADC_ANALOGWATCHDOG23_CHANNEL_0                 ADC_AWD2CR_AWD2CH_0
#define ADC_ANALOGWATCHDOG23_CHANNEL_1                 ADC_AWD2CR_AWD2CH_1
#define ADC_ANALOGWATCHDOG23_CHANNEL_2                 ADC_AWD2CR_AWD2CH_2
#define ADC_ANALOGWATCHDOG23_CHANNEL_3                 ADC_AWD2CR_AWD2CH_3
#define ADC_ANALOGWATCHDOG23_CHANNEL_4                 ADC_AWD2CR_AWD2CH_4
#define ADC_ANALOGWATCHDOG23_CHANNEL_5                 ADC_AWD2CR_AWD2CH_5
#define ADC_ANALOGWATCHDOG23_CHANNEL_6                 ADC_AWD2CR_AWD2CH_6
#define ADC_ANALOGWATCHDOG23_CHANNEL_7                 ADC_AWD2CR_AWD2CH_7
#define ADC_ANALOGWATCHDOG23_CHANNEL_8                 ADC_AWD2CR_AWD2CH_8
#define ADC_ANALOGWATCHDOG23_CHANNEL_9                 ADC_AWD2CR_AWD2CH_9
#define ADC_ANALOGWATCHDOG23_CHANNEL_10                ADC_AWD2CR_AWD2CH_10
#define ADC_ANALOGWATCHDOG23_CHANNEL_11                ADC_AWD2CR_AWD2CH_11
#define ADC_ANALOGWATCHDOG23_CHANNEL_12                ADC_AWD2CR_AWD2CH_12
#define ADC_ANALOGWATCHDOG23_CHANNEL_13                ADC_AWD2CR_AWD2CH_13
#define ADC_ANALOGWATCHDOG23_CHANNEL_14                ADC_AWD2CR_AWD2CH_14
#define ADC_ANALOGWATCHDOG23_CHANNEL_15                ADC_AWD2CR_AWD2CH_15
#define ADC_ANALOGWATCHDOG23_CHANNEL_16                ADC_AWD2CR_AWD2CH_17
#define ADC_ANALOGWATCHDOG23_CHANNEL_18                ADC_AWD2CR_AWD2CH_18


#define IS_ADC_ANALOGWATCHDOG23_CHANNEL_SEL(CHANNEL) (((CHANNEL) == ADC_AnalogWatchdog23_Channel_0)  || \
                                                      ((CHANNEL) == ADC_AnalogWatchdog23_Channel_1)  || \
                                                      ((CHANNEL) == ADC_AnalogWatchdog23_Channel_2)  || \
                                                      ((CHANNEL) == ADC_AnalogWatchdog23_Channel_3)  || \
                                                      ((CHANNEL) == ADC_AnalogWatchdog23_Channel_4)  || \
                                                      ((CHANNEL) == ADC_AnalogWatchdog23_Channel_5)  || \
                                                      ((CHANNEL) == ADC_AnalogWatchdog23_Channel_6)  || \
                                                      ((CHANNEL) == ADC_AnalogWatchdog23_Channel_7)  || \
                                                      ((CHANNEL) == ADC_AnalogWatchdog23_Channel_8)  || \
                                                      ((CHANNEL) == ADC_AnalogWatchdog23_Channel_9)  || \
                                                      ((CHANNEL) == ADC_AnalogWatchdog23_Channel_10) || \
                                                      ((CHANNEL) == ADC_AnalogWatchdog23_Channel_11) || \
                                                      ((CHANNEL) == ADC_AnalogWatchdog23_Channel_12) || \
                                                      ((CHANNEL) == ADC_AnalogWatchdog23_Channel_13) || \
                                                      ((CHANNEL) == ADC_AnalogWatchdog23_Channel_14) || \
                                                      ((CHANNEL) == ADC_AnalogWatchdog23_Channel_15) || \
                                                      ((CHANNEL) == ADC_AnalogWatchdog23_Channel_16) || \
                                                      ((CHANNEL) == ADC_AnalogWatchdog23_Channel_17) || \
                                                      ((CHANNEL) == ADC_AnalogWatchdog23_Channel_18))
/**
  * @}
  */

/** @defgroup ADC_analog_watchdog_filtering_config ADC analog watchdog (AWD) filtering configuration
  * @{
  */
#define ADC_AWD_FILTERING_NONE          (0x00000000UL)                            /*!< ADC AWD no filtering, one
                                                                                       out-of-window sample to raise flag or interrupt */
#define ADC_AWD_FILTERING_2SAMPLES      ((ADC_TR1_AWDFILT_0))                     /*!< ADC AWD 2 consecutives
                                                                                       out-of-window samples to raise flag or interrupt */
#define ADC_AWD_FILTERING_3SAMPLES      ((ADC_TR1_AWDFILT_1))                     /*!< ADC AWD 3 consecutives
                                                                                       out-of-window samples to raise flag or interrupt */
#define ADC_AWD_FILTERING_4SAMPLES      ((ADC_TR1_AWDFILT_1 | ADC_TR1_AWDFILT_0)) /*!< ADC AWD 4 consecutives
                                                                                       out-of-window samples to raise flag or interrupt */
#define ADC_AWD_FILTERING_5SAMPLES      ((ADC_TR1_AWDFILT_2))                     /*!< ADC AWD 5 consecutives
                                                                                       out-of-window samples to raise flag or interrupt */
#define ADC_AWD_FILTERING_6SAMPLES      ((ADC_TR1_AWDFILT_2 | ADC_TR1_AWDFILT_0)) /*!< ADC AWD 6 consecutives
                                                                                       out-of-window samples to raise flag or interrupt */
#define ADC_AWD_FILTERING_7SAMPLES      ((ADC_TR1_AWDFILT_2 | ADC_TR1_AWDFILT_1)) /*!< ADC AWD 7 consecutives
                                                                                       out-of-window samples to raise flag or interrupt */
#define ADC_AWD_FILTERING_8SAMPLES      ((ADC_TR1_AWDFILT_2 | ADC_TR1_AWDFILT_1 |\
                                          ADC_TR1_AWDFILT_0))                     /*!< ADC AWD 8 consecutives
                                                                                       out-of-window samples to raise flag or interrupt */

#define IS_ADC_ANALOG_WATCHDOG_FILTERING_MODE(FILTERING)      (((FILTERING) == ADC_AWD_FILTERING_NONE)       ||\
                                                               ((FILTERING) == ADC_AWD_FILTERING_2SAMPLES)   ||\
                                                               ((FILTERING) == ADC_AWD_FILTERING_3SAMPLES)   ||\
                                                               ((FILTERING) == ADC_AWD_FILTERING_4SAMPLES)   ||\
                                                               ((FILTERING) == ADC_AWD_FILTERING_5SAMPLES)   ||\
                                                               ((FILTERING) == ADC_AWD_FILTERING_6SAMPLES)   ||\
                                                               ((FILTERING) == ADC_AWD_FILTERING_7SAMPLES)   ||\
                                                               ((FILTERING) == ADC_AWD_FILTERING_8SAMPLES)   )
/**
  * @}
  */

/** @defgroup ADC_sampling_plus_times
  * @{
  */
#define ADC_SAMPLETIMEPLUS_1_5CYCLES                 ((uint32_t)0x00000000)
#define ADC_SAMPLETIMEPLUS_2_5CYCLES                 ((uint32_t)ADC_SMPR1_SMPLUS_0)
#define ADC_SAMPLETIMEPLUS_3_5CYCLES                 ((uint32_t)ADC_SMPR1_SMPLUS_1)
#define ADC_SAMPLETIMEPLUS_4_5CYCLES                 ((uint32_t)ADC_SMPR1_SMPLUS)

#define IS_ADC_SAMPLE_PLUS_TIME(PLUS_TIME)   (((PLUS_TIME) == ADC_SAMPLETIMEPLUS_1_5CYCLES)    || \
                                              ((PLUS_TIME) == ADC_SAMPLETIMEPLUS_2_5CYCLES)    || \
                                              ((PLUS_TIME) == ADC_SAMPLETIMEPLUS_3_5CYCLES)    || \
                                              ((PLUS_TIME) == ADC_SAMPLETIMEPLUS_4_5CYCLES))
/**
  * @}
  */

/** @defgroup ADC_sampling_times
  * @{
  */
#define ADC_SAMPLETIME_1_5CYCLES                     ((uint32_t)0x00000000)
#define ADC_SAMPLETIME_6_5CYCLES                     ((uint32_t)0x00000001)
#define ADC_SAMPLETIME_12_5CYCLES                    ((uint32_t)0x00000002)
#define ADC_SAMPLETIME_24_5CYCLES                    ((uint32_t)0x00000003)
#define ADC_SAMPLETIME_47_5CYCLES                    ((uint32_t)0x00000004)
#define ADC_SAMPLETIME_92_5CYCLES                    ((uint32_t)0x00000005)
#define ADC_SAMPLETIME_247_5CYCLES                   ((uint32_t)0x00000006)
#define ADC_SAMPLETIME_640_5CYCLES                   ((uint32_t)0x00000007)

#define IS_ADC_SAMPLE_TIME(TIME) (((TIME) == ADC_SAMPLETIME_1_5CYCLES)    || \
                                  ((TIME) == ADC_SAMPLETIME_6_5CYCLES)    || \
                                  ((TIME) == ADC_SAMPLETIME_12_5CYCLES)   || \
                                  ((TIME) == ADC_SAMPLETIME_24_5CYCLES)   || \
                                  ((TIME) == ADC_SAMPLETIME_47_5CYCLES)   || \
                                  ((TIME) == ADC_SAMPLETIME_92_5CYCLES)   || \
                                  ((TIME) == ADC_SAMPLETIME_247_5CYCLES)  || \
                                  ((TIME) == ADC_SAMPLETIME_640_5CYCLES)  )
/**
  * @}
  */

/** @defgroup ADC_thresholds
  * @{
  */
#define IS_ADC_THRESHOLD(THRESHOLD) ((THRESHOLD) <= 0xFFF)
/**
  * @}
  */

/** @defgroup ADC_reg_seq_ranks  ADC group regular - Sequencer ranks
  * @{
  */
#define ADC_REGULAR_RANK_1                 (uint32_t)0x00000000 /*!< ADC group regular sequencer rank 1 */
#define ADC_REGULAR_RANK_2                 (uint32_t)0x00000001 /*!< ADC group regular sequencer rank 2 */
#define ADC_REGULAR_RANK_3                 (uint32_t)0x00000002 /*!< ADC group regular sequencer rank 3 */
#define ADC_REGULAR_RANK_4                 (uint32_t)0x00000003 /*!< ADC group regular sequencer rank 4 */
#define ADC_REGULAR_RANK_5                 (uint32_t)0x00000004 /*!< ADC group regular sequencer rank 5 */
#define ADC_REGULAR_RANK_6                 (uint32_t)0x00000005 /*!< ADC group regular sequencer rank 6 */
#define ADC_REGULAR_RANK_7                 (uint32_t)0x00000006 /*!< ADC group regular sequencer rank 7 */
#define ADC_REGULAR_RANK_8                 (uint32_t)0x00000007 /*!< ADC group regular sequencer rank 8 */
#define ADC_REGULAR_RANK_9                 (uint32_t)0x00000008 /*!< ADC group regular sequencer rank 9 */
#define ADC_REGULAR_RANK_10                (uint32_t)0x00000009 /*!< ADC group regular sequencer rank 10 */
#define ADC_REGULAR_RANK_11                (uint32_t)0x0000000a /*!< ADC group regular sequencer rank 11 */
#define ADC_REGULAR_RANK_12                (uint32_t)0x0000000b /*!< ADC group regular sequencer rank 12 */
#define ADC_REGULAR_RANK_13                (uint32_t)0x0000000c /*!< ADC group regular sequencer rank 13 */
#define ADC_REGULAR_RANK_14                (uint32_t)0x0000000d /*!< ADC group regular sequencer rank 14 */
#define ADC_REGULAR_RANK_15                (uint32_t)0x0000000e /*!< ADC group regular sequencer rank 15 */
#define ADC_REGULAR_RANK_16                (uint32_t)0x0000000f /*!< ADC group regular sequencer rank 16 */

#define IS_ADC_REGULAR_RANK(RANK)          (((RANK) == ADC_REGULAR_RANK_1 )   ||\
                                            ((RANK) == ADC_REGULAR_RANK_2 )   ||\
                                            ((RANK) == ADC_REGULAR_RANK_3 )   ||\
                                            ((RANK) == ADC_REGULAR_RANK_4 )   ||\
                                            ((RANK) == ADC_REGULAR_RANK_5 )   ||\
                                            ((RANK) == ADC_REGULAR_RANK_6 )   ||\
                                            ((RANK) == ADC_REGULAR_RANK_7 )   ||\
                                            ((RANK) == ADC_REGULAR_RANK_8 )   ||\
                                            ((RANK) == ADC_REGULAR_RANK_9 )   ||\
                                            ((RANK) == ADC_REGULAR_RANK_10)   ||\
                                            ((RANK) == ADC_REGULAR_RANK_11)   ||\
                                            ((RANK) == ADC_REGULAR_RANK_12)   ||\
                                            ((RANK) == ADC_REGULAR_RANK_13)   ||\
                                            ((RANK) == ADC_REGULAR_RANK_14)   ||\
                                            ((RANK) == ADC_REGULAR_RANK_15)   ||\
                                            ((RANK) == ADC_REGULAR_RANK_16)   )

/**
  * @}
  */

/** @defgroup ADC_channels
  * @{
  */
#define ADC_CHANNEL_RESET                          ((uint32_t)0x0000001f)
#define ADC_CHANNEL_0                              ((uint32_t)0x00000000)
#define ADC_CHANNEL_1                              ((uint32_t)0x00000001)
#define ADC_CHANNEL_2                              ((uint32_t)0x00000002)
#define ADC_CHANNEL_3                              ((uint32_t)0x00000003)
#define ADC_CHANNEL_4                              ((uint32_t)0x00000004)
#define ADC_CHANNEL_5                              ((uint32_t)0x00000005)
#define ADC_CHANNEL_6                              ((uint32_t)0x00000006)
#define ADC_CHANNEL_7                              ((uint32_t)0x00000007)
#define ADC_CHANNEL_8                              ((uint32_t)0x00000008)
#define ADC_CHANNEL_9                              ((uint32_t)0x00000009)
#define ADC_CHANNEL_10                             ((uint32_t)0x0000000a)
#define ADC_CHANNEL_11                             ((uint32_t)0x0000000b)
#define ADC_CHANNEL_12                             ((uint32_t)0x0000000c)
#define ADC_CHANNEL_13                             ((uint32_t)0x0000000d)
#define ADC_CHANNEL_14                             ((uint32_t)0x0000000e)
#define ADC_CHANNEL_15                             ((uint32_t)0x0000000f)
#define ADC_CHANNEL_16                             ((uint32_t)0x00000010)
#define ADC_CHANNEL_17                             ((uint32_t)0x00000011)
#define ADC_CHANNEL_18                             ((uint32_t)0x00000012)
#define ADC_CHANNEL_19                             ((uint32_t)0x00000013)
#define ADC_CHANNEL_20                             ((uint32_t)0x00000014)
#define ADC_CHANNEL_21                             ((uint32_t)0x00000015)

#define ADC1_CHANNEL_VREFINT                       ((uint32_t)ADC_CHANNEL_0)
#define ADC13_CHANNEL_TENOSENSOR                   ((uint32_t)ADC_CHANNEL_17)
#define ADC13_CHANNEL_VBAT                         ((uint32_t)ADC_CHANNEL_18)

#define ADC12_CHANNEL_OP1                          ((uint32_t)ADC_CHANNEL_19)
#define ADC12_CHANNEL_OP2                          ((uint32_t)ADC_CHANNEL_20)
#define ADC12_CHANNEL_OP3                          ((uint32_t)ADC_CHANNEL_21)

#define ADC12_CHANNEL_DAC1                         ((uint32_t)ADC_CHANNEL_17)
#define ADC12_CHANNEL_DAC2                         ((uint32_t)ADC_CHANNEL_18)

#define ADC3_CHANNEL_DAC1                          ((uint32_t)ADC_CHANNEL_14)
#define ADC3_CHANNEL_DAC2                          ((uint32_t)ADC_CHANNEL_15)

#define IS_ADC_CHANNEL(CHANNEL)                    (((CHANNEL) == ADC_CHANNEL_0)              || \
                                                    ((CHANNEL) == ADC_CHANNEL_1)              || \
                                                    ((CHANNEL) == ADC_CHANNEL_2)              || \
                                                    ((CHANNEL) == ADC_CHANNEL_3)              || \
                                                    ((CHANNEL) == ADC_CHANNEL_4)              || \
                                                    ((CHANNEL) == ADC_CHANNEL_5)              || \
                                                    ((CHANNEL) == ADC_CHANNEL_6)              || \
                                                    ((CHANNEL) == ADC_CHANNEL_7)              || \
                                                    ((CHANNEL) == ADC_CHANNEL_8)              || \
                                                    ((CHANNEL) == ADC_CHANNEL_9)              || \
                                                    ((CHANNEL) == ADC_CHANNEL_10)             || \
                                                    ((CHANNEL) == ADC_CHANNEL_11)             || \
                                                    ((CHANNEL) == ADC_CHANNEL_12)             || \
                                                    ((CHANNEL) == ADC_CHANNEL_13)             || \
                                                    ((CHANNEL) == ADC_CHANNEL_14)             || \
                                                    ((CHANNEL) == ADC_CHANNEL_15)             || \
                                                    ((CHANNEL) == ADC_CHANNEL_16)             || \
                                                    ((CHANNEL) == ADC_CHANNEL_17)             || \
                                                    ((CHANNEL) == ADC_CHANNEL_18)             || \
                                                    ((CHANNEL) == ADC_CHANNEL_19)             || \
                                                    ((CHANNEL) == ADC_CHANNEL_20)             || \
                                                    ((CHANNEL) == ADC_CHANNEL_21)             || \
                                                    ((CHANNEL) == ADC1_CHANNEL_VREFINT)       || \
                                                    ((CHANNEL) == ADC13_CHANNEL_TENOSENSOR)   || \
                                                    ((CHANNEL) == ADC13_CHANNEL_VBAT)         || \
                                                    ((CHANNEL) == ADC12_CHANNEL_OP1)          || \
                                                    ((CHANNEL) == ADC12_CHANNEL_OP2)          || \
                                                    ((CHANNEL) == ADC12_CHANNEL_OP3)          || \
                                                    ((CHANNEL) == ADC12_CHANNEL_DAC1)         || \
                                                    ((CHANNEL) == ADC12_CHANNEL_DAC2)         || \
                                                    ((CHANNEL) == ADC3_CHANNEL_DAC1)          || \
                                                    ((CHANNEL) == ADC3_CHANNEL_DAC2)          )
/**
  * @}
  */

/** @defgroup ADC_injected_seq_ranks  ADC group injected - Sequencer ranks
  * @{
  */
#define ADC_INJECTED_RANK_1                (uint32_t)0x00000000 /*!< ADC group injected sequencer rank 1 */
#define ADC_INJECTED_RANK_2                (uint32_t)0x00000001 /*!< ADC group injected sequencer rank 2 */
#define ADC_INJECTED_RANK_3                (uint32_t)0x00000002 /*!< ADC group injected sequencer rank 3 */
#define ADC_INJECTED_RANK_4                (uint32_t)0x00000003 /*!< ADC group injected sequencer rank 4 */

#define IS_ADC_INJECTED_RANK(CHANNEL)     (((CHANNEL) == ADC_INJECTED_RANK_1) || \
                                           ((CHANNEL) == ADC_INJECTED_RANK_2) || \
                                           ((CHANNEL) == ADC_INJECTED_RANK_3) || \
                                           ((CHANNEL) == ADC_INJECTED_RANK_4)   )
/**
  * @}
  */

/** @defgroup ADC_REG_SEQ_DISCONT_MODE  ADC group regular - Sequencer discontinuous mode
  * @{
  */
#define ADC_REG_SEQ_DISCONT_DISABLE     (uint32_t)0x00000000                      /*!< ADC group regular sequencer
                                                                                       discontinuous mode disable */
#define ADC_REG_SEQ_DISCNUM_1_CHANNEL   (ADC_CFGR1_DISCEN)                        /*!< ADC group regular sequencer
                                                                                       discontinuous mode enable with
                                                                                       sequence interruption every rank */
#define ADC_REG_SEQ_DISCNUM_2_CHANNELS  (ADC_CFGR1_DISCNUM_0 | ADC_CFGR1_DISCEN)  /*!< ADC group regular sequencer
                                                                                       discontinuous mode enabled with
                                                                                       sequence interruption every 2 ranks */
#define ADC_REG_SEQ_DISCNUM_3_CHANNELS  (ADC_CFGR1_DISCNUM_1 | ADC_CFGR1_DISCEN)  /*!< ADC group regular sequencer
                                                                                       discontinuous mode enable with
                                                                                       sequence interruption every 3 ranks */
#define ADC_REG_SEQ_DISCNUM_4_CHANNELS  (ADC_CFGR1_DISCNUM_1 | ADC_CFGR1_DISCNUM_0 \
                                         | ADC_CFGR1_DISCEN)                      /*!< ADC group regular sequencer
                                                                                       discontinuous mode enable with
                                                                                       sequence interruption every 4 ranks */
#define ADC_REG_SEQ_DISCNUM_5_CHANNELS  (ADC_CFGR1_DISCNUM_2 | ADC_CFGR1_DISCEN)  /*!< ADC group regular sequencer
                                                                                       discontinuous mode enable with 
                                                                                       sequence interruption every 5 ranks */
#define ADC_REG_SEQ_DISCNUM_6_CHANNELS  (ADC_CFGR1_DISCNUM_2 | ADC_CFGR1_DISCNUM_0 \
                                         | ADC_CFGR1_DISCEN)                      /*!< ADC group regular sequencer
                                                                                       discontinuous mode enable with
                                                                                       sequence interruption every 6 ranks */
#define ADC_REG_SEQ_DISCNUM_7_CHANNELS  (ADC_CFGR1_DISCNUM_2 | ADC_CFGR1_DISCNUM_1 \
                                         | ADC_CFGR1_DISCEN)                      /*!< ADC group regular sequencer
                                                                                       discontinuous mode enable with
                                                                                       sequence interruption every 7 ranks */
#define ADC_REG_SEQ_DISCNUM_8_CHANNELS  (ADC_CFGR1_DISCNUM_2 | ADC_CFGR1_DISCNUM_1 \
                                         | ADC_CFGR1_DISCNUM_0 \
                                         | ADC_CFGR1_DISCEN)                      /*!< ADC group regular sequencer
                                                                                       discontinuous mode enable with
                                                                                       sequence interruption every 8 ranks */

#define ADC_REG_SEQ_DISCNUM(DISCNUM)    (((DISCNUM) == ADC_REG_SEQ_DISCONT_DISABLE)    || \
                                         ((DISCNUM) == ADC_REG_SEQ_DISCNUM_1_CHANNEL)  || \
                                         ((DISCNUM) == ADC_REG_SEQ_DISCNUM_2_CHANNELS) || \
                                         ((DISCNUM) == ADC_REG_SEQ_DISCNUM_3_CHANNELS) || \
                                         ((DISCNUM) == ADC_REG_SEQ_DISCNUM_4_CHANNELS) || \
                                         ((DISCNUM) == ADC_REG_SEQ_DISCNUM_5_CHANNELS) || \
                                         ((DISCNUM) == ADC_REG_SEQ_DISCNUM_6_CHANNELS) || \
                                         ((DISCNUM) == ADC_REG_SEQ_DISCNUM_7_CHANNELS) || \
                                         ((DISCNUM) == ADC_REG_SEQ_DISCNUM_8_CHANNELS) )

/**
  * @}
  */

/** @defgroup ADC_OVS_RATIO  Oversampling - Ratio
  * @note The oversampling ratio is the number of ADC conversions performed, sum of these conversions data is computed
  *       to result as the ADC oversampling conversion data (before potential shift)
  */
#define ADC_OVERSAMPLING_RATIO_2           ((uint32_t)0x00000000)                                             /*!< ADC oversampling ratio    2 */
#define ADC_OVERSAMPLING_RATIO_4           ((uint32_t)ADC_CFGR2_OVSR_0)                                       /*!< ADC oversampling ratio    4 */
#define ADC_OVERSAMPLING_RATIO_8           ((uint32_t)ADC_CFGR2_OVSR_1)                                       /*!< ADC oversampling ratio    8 */
#define ADC_OVERSAMPLING_RATIO_16          ((uint32_t)(ADC_CFGR2_OVSR_0|ADC_CFGR2_OVSR_1))                    /*!< ADC oversampling ratio   16 */
#define ADC_OVERSAMPLING_RATIO_32          ((uint32_t)ADC_CFGR2_OVSR_2)                                       /*!< ADC oversampling ratio   32 */
#define ADC_OVERSAMPLING_RATIO_64          ((uint32_t)(ADC_CFGR2_OVSR_0|ADC_CFGR2_OVSR_2))                    /*!< ADC oversampling ratio   64 */
#define ADC_OVERSAMPLING_RATIO_128         ((uint32_t)(ADC_CFGR2_OVSR_1|ADC_CFGR2_OVSR_2))                    /*!< ADC oversampling ratio  128 */
#define ADC_OVERSAMPLING_RATIO_256         ((uint32_t)(ADC_CFGR2_OVSR_0|ADC_CFGR2_OVSR_1|ADC_CFGR2_OVSR_2))   /*!< ADC oversampling ratio  256 */


#define IS_ADC_OVERSAMPLING_RATIO(RATIO)   (((RATIO) == ADC_OVERSAMPLING_RATIO_2)   ||\
                                            ((RATIO) == ADC_OVERSAMPLING_RATIO_4)   ||\
                                            ((RATIO) == ADC_OVERSAMPLING_RATIO_8)   ||\
                                            ((RATIO) == ADC_OVERSAMPLING_RATIO_16)  ||\
                                            ((RATIO) == ADC_OVERSAMPLING_RATIO_32)  ||\
                                            ((RATIO) == ADC_OVERSAMPLING_RATIO_64)  ||\
                                            ((RATIO) == ADC_OVERSAMPLING_RATIO_128) ||\
                                            ((RATIO) == ADC_OVERSAMPLING_RATIO_256))
/**
  * @}
  */

/** @defgroup ADC_OVS_SHIFT  Oversampling - Data shift
  * @{
  */
/**
  * @note The sum of the ADC conversions data is divided by "Rightbitshift" number to result as the ADC oversampling
  *       conversion data)
  */
#define ADC_RIGHTBITSHIFT_NONE             ((uint32_t)0x00000000)                                           /*!< ADC oversampling no shift               */
#define ADC_RIGHTBITSHIFT_1                ((uint32_t)ADC_CFGR2_OVSS_0)                                     /*!< ADC oversampling right shift of 1 ranks */
#define ADC_RIGHTBITSHIFT_2                ((uint32_t)ADC_CFGR2_OVSS_1)                                     /*!< ADC oversampling right shift of 2 ranks */
#define ADC_RIGHTBITSHIFT_3                ((uint32_t)(ADC_CFGR2_OVSS_0|ADC_CFGR2_OVSS_1))                  /*!< ADC oversampling right shift of 3 ranks */
#define ADC_RIGHTBITSHIFT_4                ((uint32_t)ADC_CFGR2_OVSS_2)                                     /*!< ADC oversampling right shift of 4 ranks */
#define ADC_RIGHTBITSHIFT_5                ((uint32_t)(ADC_CFGR2_OVSS_0|ADC_CFGR2_OVSS_2))                  /*!< ADC oversampling right shift of 5 ranks */
#define ADC_RIGHTBITSHIFT_6                ((uint32_t)(ADC_CFGR2_OVSS_1|ADC_CFGR2_OVSS_2))                  /*!< ADC oversampling right shift of 6 ranks */
#define ADC_RIGHTBITSHIFT_7                ((uint32_t)(ADC_CFGR2_OVSS_0|ADC_CFGR2_OVSS_1|ADC_CFGR2_OVSS_2)) /*!< ADC oversampling right shift of 7 ranks */
#define ADC_RIGHTBITSHIFT_8                ((uint32_t)ADC_CFGR2_OVSS_3)                                     /*!< ADC oversampling right shift of 8 ranks */

#define IS_ADC_RIGHT_BIT_SHIFT(SHIFT)      (((SHIFT) == ADC_RIGHTBITSHIFT_NONE)   ||\
                                            ((SHIFT) == ADC_RIGHTBITSHIFT_1)      ||\
                                            ((SHIFT) == ADC_RIGHTBITSHIFT_2)      ||\
                                            ((SHIFT) == ADC_RIGHTBITSHIFT_3)      ||\
                                            ((SHIFT) == ADC_RIGHTBITSHIFT_4)      ||\
                                            ((SHIFT) == ADC_RIGHTBITSHIFT_5)      ||\
                                            ((SHIFT) == ADC_RIGHTBITSHIFT_6)      ||\
                                            ((SHIFT) == ADC_RIGHTBITSHIFT_7)      ||\
                                            ((SHIFT) == ADC_RIGHTBITSHIFT_8)       )
/**
  * @}
  */

/** @defgroup ADC_OVS_DISCONT_MODE  Oversampling - Discontinuous mode
  * @{
  */
#define ADC_TRIGGEREDMODE_SINGLE_TRIGGER   (0x00000000UL)       /*!< ADC oversampling discontinuous mode:
                                                                     continuous mode (all conversions of OVS ratio are done from 1 trigger) */
#define ADC_TRIGGEREDMODE_MULTI_TRIGGER    (ADC_CFGR2_TROVS)    /*!< ADC oversampling discontinuous mode:
                                                                     discontinuous mode (each conversion of OVS ratio needs a trigger) */

#define IS_ADC_TRIGGERED_OVERSAMPLING_MODE(MODE)    (((MODE) == ADC_TRIGGEREDMODE_SINGLE_TRIGGER)  ||\
                                                     ((MODE) == ADC_TRIGGEREDMODE_MULTI_TRIGGER))
/**
  * @}
  */

/** @defgroup ADC_OVS_SCOPE_REG  Oversampling - Oversampling scope for ADC group regular
  * @{
  */
#define ADC_REGOVERSAMPLING_CONTINUED_MODE   (0x00000000UL)       /*!< Oversampling buffer maintained
                                                                     during injection sequence */
#define ADC_REGOVERSAMPLING_RESUMED_MODE     (ADC_CFGR2_ROVSM)    /*!< Oversampling buffer zeroed during
                                                                     injection sequence */

#define IS_ADC_REGOVERSAMPLING_MODE(MODE)     (((MODE) == ADC_REGOVERSAMPLING_CONTINUED_MODE)  ||\
                                               ((MODE) == ADC_REGOVERSAMPLING_RESUMED_MODE))
/**
  * @}
  */


/** @defgroup ADC_interrupts_definition
  * @{
  */

#define ADC_IT_ADRDY                               ADC_IER_ADRDYIE    /*!< ADC Ready interrupt source */
#define ADC_IT_EOSMP                               ADC_IER_EOSMPIE    /*!< ADC End of sampling interrupt source */
#define ADC_IT_EOC                                 ADC_IER_EOCIE      /*!< ADC End of regular conversion interrupt source */
#define ADC_IT_EOS                                 ADC_IER_EOSIE      /*!< ADC End of regular sequence of conversions interrupt source */
#define ADC_IT_OVR                                 ADC_IER_OVRIE      /*!< ADC overrun interrupt source */
#define ADC_IT_JEOC                                ADC_IER_JEOCIE     /*!< ADC End of injected conversion interrupt source */
#define ADC_IT_JEOS                                ADC_IER_JEOSIE     /*!< ADC End of injected sequence of conversions interrupt source */
#define ADC_IT_AWD1                                ADC_IER_AWD1IE     /*!< ADC Analog watchdog 1 interrupt source (main analog watchdog) */
#define ADC_IT_AWD2                                ADC_IER_AWD2IE     /*!< ADC Analog watchdog 2 interrupt source (additional analog watchdog) */
#define ADC_IT_AWD3                                ADC_IER_AWD3IE     /*!< ADC Analog watchdog 3 interrupt source (additional analog watchdog) */
#define ADC_IT_JQOV                                ADC_IER_JQOVIE     /*!< ADC Injected Context Queue Overflow interrupt source */

#define IS_ADC_CONFIG_IT(IT) (((IT) != (uint32_t)RESET) && (((IT) & 0xFFFFF800) == (uint32_t)RESET))

#define IS_ADC_GET_IT(IT) (((IT) == ADC_IT_ADRDY) || ((IT) == ADC_IT_EOSMP)  || \
                           ((IT) == ADC_IT_EOC)   || ((IT) == ADC_IT_EOS)    || \
                           ((IT) == ADC_IT_OVR)   || ((IT) == ADC_IT_JEOC)   || \
                           ((IT) == ADC_IT_JEOS)  || ((IT) == ADC_IT_AWD1)   || \
                           ((IT) == ADC_IT_AWD2)  || ((IT) == ADC_IT_AWD3)   || \
                           ((IT) == ADC_IT_JQOV))

#define IS_ADC_CLEAR_IT(IT) (((IT) != (uint32_t)RESET) && (((IT) & 0xFFFFF800) == (uint32_t)RESET))

/**
  * @}
  */

/** @defgroup ADC_flags_definition
  * @{
  */

#define ADC_FLAG_ADRDY                             ADC_ISR_ADRDY
#define ADC_FLAG_EOSMP                             ADC_ISR_EOSMP
#define ADC_FLAG_EOC                               ADC_ISR_EOC
#define ADC_FLAG_EOS                               ADC_ISR_EOS
#define ADC_FLAG_OVR                               ADC_ISR_OVR
#define ADC_FLAG_JEOC                              ADC_ISR_JEOC
#define ADC_FLAG_JEOS                              ADC_ISR_JEOS
#define ADC_FLAG_AWD1                              ADC_ISR_AWD1
#define ADC_FLAG_AWD2                              ADC_ISR_AWD2
#define ADC_FLAG_AWD3                              ADC_ISR_AWD3
#define ADC_FLAG_JQOVF                             ADC_ISR_JQOVF

#define ADC_FLAG_ADEN                              ((uint32_t)0x01000001)
#define ADC_FLAG_ADDIS                             ((uint32_t)0x01000002)
#define ADC_FLAG_ADSTART                           ((uint32_t)0x01000004)
#define ADC_FLAG_JADSTART                          ((uint32_t)0x01000008)
#define ADC_FLAG_ADSTP                             ((uint32_t)0x01000010)
#define ADC_FLAG_JADSTP                            ((uint32_t)0x01000020)
#define ADC_FLAG_ADCAL                             ((uint32_t)0x81000000)

#define IS_ADC_CLEAR_FLAG(FLAG) (((FLAG) != (uint32_t)RESET) && (((FLAG) & 0xFFFFF800) == (uint32_t)RESET))

#define IS_ADC_GET_FLAG(FLAG) (((FLAG) == ADC_FLAG_ADRDY)   || ((FLAG) == ADC_FLAG_EOSMP)    || \
                               ((FLAG) == ADC_FLAG_EOC)     || ((FLAG) == ADC_FLAG_EOS)      || \
                               ((FLAG) == ADC_FLAG_OVR)     || ((FLAG) == ADC_FLAG_JEOC)     || \
                               ((FLAG) == ADC_FLAG_JEOS)    || ((FLAG) == ADC_FLAG_AWD1)     || \
                               ((FLAG) == ADC_FLAG_AWD2)    || ((FLAG) == ADC_FLAG_AWD3)     || \
                               ((FLAG) == ADC_FLAG_JQOVF)   || \
                               ((FLAG) == ADC_FLAG_ADEN)    || ((FLAG) == ADC_FLAG_ADDIS)    || \
                               ((FLAG) == ADC_FLAG_ADSTART) || ((FLAG) == ADC_FLAG_JADSTART) || \
                               ((FLAG) == ADC_FLAG_ADSTP)   || ((FLAG) == ADC_FLAG_JADSTP)   || \
                               ((FLAG) == ADC_FLAG_ADCAL))
/**
  * @}
  */


/** @defgroup ADC_REG_OVR_DATA_BEHAVIOR  ADC group regular - Overrun behavior on conversion data
  * @{
  */
#define ADC_OVR_MODE_PRESERVED             ((uint32_t)0x00000000)    /*!< ADC group regular behavior in case
                                                                          of overrun: data preserved */
#define ADC_OVR_MODE_OVERWRITTEN           (ADC_CFGR1_OVRMOD)        /*!< ADC group regular behavior in case
                                                                          of overrun: data overwritten */

#define IS_ADC_OVERRUN(OVR)               (((OVR) == ADC_OVR_MODE_PRESERVED) ||\
                                           ((OVR) == ADC_OVR_MODE_OVERWRITTEN))
/**
  * @}
  */

/** @defgroup ADC_regular_sampling_mode ADC group regular sampling mode
  * @{
  */
#define ADC_SAMPLING_MODE_NORMAL                ((uint32_t)0x00000000)   /*!< ADC conversions sampling phase duration is
                                                                              defined using  @ref ADC_HAL_EC_CHANNEL_SAMPLINGTIME */
#define ADC_SAMPLING_MODE_BULB                  (ADC_CFGR2_BULB)         /*!< ADC conversions sampling phase starts
                                                                              immediately after end of conversion, and stops upon trigger event.
                                                                              Note: First conversion is using minimal sampling time
                                                                              (see @ref ADC_CHANNEL_SAMPLINGTIME) */
#define ADC_SAMPLING_MODE_TRIGGER_CONTROLED     (ADC_CFGR2_SMPTRIG)      /*!< ADC conversions sampling phase is controlled
                                                                              by trigger events:
                                                                              Trigger rising edge  = start sampling
                                                                              Trigger falling edge = stop sampling and start conversion */

#define IS_ADC_SAMPLINGMODE(SAMPLINGMODE) (((SAMPLINGMODE) == ADC_SAMPLING_MODE_NORMAL)          || \
                                           ((SAMPLINGMODE) == ADC_SAMPLING_MODE_BULB)            || \
                                           ((SAMPLINGMODE) == ADC_SAMPLING_MODE_TRIGGER_CONTROLED))

/**
  * @}
  */

/** @defgroup ADC_channel_single_diff_ending  Channel - Single or differential ending
  * @{
  */
#define ADC_SINGLE_ENDED                ((uint32_t)0x00000000)     /*!< ADC channel ending set to single ended */
#define ADC_DIFFERENTIAL_ENDED          ((uint32_t)0x00000001)     /*!< ADC channel ending set to differential */

#define IS_ADC_SINGLE_DIFFERENTIAL(SING_DIFF) (((SING_DIFF) == ADC_SINGLE_ENDED)        || \
                                               ((SING_DIFF) == ADC_DIFFERENTIAL_ENDED)  )
/**
  * @}
  */

/** @defgroup ADC_offset_number  ADC instance - Offset number
  * @{
  */
#define ADC_OFFSET_NONE              ((uint32_t)0x00000000) /*!< ADC offset disabled: no offset correction for the selected
                                                                 ADC channel */
#define ADC_OFFSET_1                 ((uint32_t)0x00000001) /*!< ADC offset number 1: ADC channel and offset level to which
                                                                 the offset programmed will be applied (independently of channel mapped
                                                                 on ADC group regular or group injected) */
#define ADC_OFFSET_2                 ((uint32_t)0x00000002) /*!< ADC offset number 2: ADC channel and offset level to which
                                                                 the offset programmed will be applied (independently of channel mapped
                                                                 on ADC group regular or group injected) */
#define ADC_OFFSET_3                 ((uint32_t)0x00000004) /*!< ADC offset number 3: ADC channel and offset level to which
                                                                 the offset programmed will be applied (independently of channel mapped
                                                                 on ADC group regular or group injected) */
#define ADC_OFFSET_4                 ((uint32_t)0x00000008) /*!< ADC offset number 4: ADC channel and offset level to which
                                                                 the offset programmed will be applied (independently of channel mapped
                                                                 on ADC group regular or group injected) */

#define IS_ADC_OFFSET_NUMBER(NUMBER)            (((NUMBER) == ADC_OFFSET_NONE) || \
                                                 ((NUMBER) == ADC_OFFSET_1)    || \
                                                 ((NUMBER) == ADC_OFFSET_2)    || \
                                                 ((NUMBER) == ADC_OFFSET_3)    || \
                                                 ((NUMBER) == ADC_OFFSET_4)      )
/**
  * @}
  */


/** @defgroup ADC_OffsetSign ADC Extended Offset Sign
  * @{
  */
#define ADC_OFFSET_SIGN_NEGATIVE      ((uint32_t)0x00000000) /*!< Offset sign negative, offset is subtracted */
#define ADC_OFFSET_SIGN_POSITIVE      (ADC_OFR1_OFFSETPOS)   /*!< Offset sign positive, offset is added  */

#define IS_ADC_OFFSET_SIGN(SIGN)     (((SIGN) == ADC_OFFSET_SIGN_NEGATIVE) ||\
                                      ((SIGN) == ADC_OFFSET_SIGN_POSITIVE))
/**
  * @}
  */


/** @defgroup ADC_CFGR_fields ADCx CFGR fields
  * @{
  */
#define ADC_CFGR_FIELDS    (ADC_CFGR1_AWD1CH  | ADC_CFGR1_JAUTO   | ADC_CFGR1_JAWD1EN |\
                            ADC_CFGR1_AWD1EN  | ADC_CFGR1_AWD1SGL | ADC_CFGR1_JQM     |\
                            ADC_CFGR1_JDISCEN | ADC_CFGR1_DISCNUM | ADC_CFGR1_DISCEN  |\
                            ADC_CFGR1_AUTDLY  | ADC_CFGR1_CONT    | ADC_CFGR1_OVRMOD  |\
                            ADC_CFGR1_EXTEN   | ADC_CFGR1_EXTSEL  | ADC_CFGR1_ALIGN   |\
                            ADC_CFGR1_RES     | ADC_CFGR1_DMACFG  | ADC_CFGR1_DMAEN   )
/**
  * @}
  */


/**
  * @}
  */

/** @defgroup ADC_MULTI_MODE  Multimode - Mode
  * @{
  */
#define ADC_MODE_INDEPENDENT                    ((uint32_t)0x00000000)
/*!< ADC dual mode disabled (ADC independent
     mode) */

#define ADC_DUAL_MODE_REGSIMULT                 (uint32_t)(ADC_CCR_MULTI_2|ADC_CCR_MULTI_1)
/*!< ADC dual mode enabled: group regular
     simultaneous */

#define ADC_DUAL_MODE_INTERL                    (uint32_t)(ADC_CCR_MULTI_2|ADC_CCR_MULTI_1|ADC_CCR_MULTI_0)
/*!< ADC dual mode enabled: Combined
     group regular interleaved */

#define ADC_DUAL_MODE_INJECSIMULT               (uint32_t)(ADC_CCR_MULTI_2|ADC_CCR_MULTI_0)
/*!< ADC dual mode enabled: group
     injected simultaneous */

#define ADC_DUAL_MODE_ALTERTRIG                 (uint32_t)(ADC_CCR_MULTI_3|ADC_CCR_MULTI_0)
/*!< ADC dual mode enabled: group injected
     alternate trigger. Works only with external
     triggers (not internal SW start) */

#define ADC_DUAL_MODE_REGSIMULT_INJECSIMULT     (uint32_t)(ADC_CCR_MULTI_0)
/*!< ADC dual mode enabled: Combined
     group regular simultaneous + group
     injected simultaneous */

#define ADC_DUAL_MODE_REGSIMULT_ALTERTRIG       (uint32_t)(ADC_CCR_MULTI_1)
/*!< ADC dual mode enabled: Combined
     group regular simultaneous + group
     injected alternate trigger */


#define ADC_TRIPLE_MODE_REGSIMULT               (uint32_t)(ADC_CCR_MULTI_4|ADC_CCR_MULTI_2|ADC_CCR_MULTI_1)
/*!< ADC triple mode enabled: group regular
     simultaneous */


#define ADC_TRIPLE_MODE_INTERL                  (uint32_t)(ADC_CCR_MULTI_4|ADC_CCR_MULTI_2|ADC_CCR_MULTI_1|ADC_CCR_MULTI_0)
/*!< ADC triple mode enabled: Combined
     group regular interleaved */

#define ADC_TRIPLE_MODE_INJECSIMULT             (uint32_t)(ADC_CCR_MULTI_4|ADC_CCR_MULTI_2|ADC_CCR_MULTI_0)
/*!< ADC triple mode enabled: group
     injected simultaneous */


#define ADC_TRIPLE_MODE_ALTERTRIG               (uint32_t)(ADC_CCR_MULTI_4|ADC_CCR_MULTI_3|ADC_CCR_MULTI_0)
/*!< ADC triple mode enabled: group injected
     alternate trigger. Works only with external
     triggers (not internal SW start) */

#define ADC_TRIPLE_MODE_REGSIMULT_INJECSIMULT   (uint32_t)(ADC_CCR_MULTI_4|ADC_CCR_MULTI_0)
/*!< ADC triple mode enabled: Combined
     group regular simultaneous + group
     injected simultaneous */


#define ADC_TRIPLE_MODE_REGSIMULT_ALTERTRIG     (uint32_t)(ADC_CCR_MULTI_4|ADC_CCR_MULTI_1)
/*!< ADC triple mode enabled: Combined
     group regular simultaneous + group
     injected alternate trigger */


#define IS_ADC_MULTIMODE(MODE)     (((MODE) == ADC_MODE_INDEPENDENT)                  || \
                                    ((MODE) == ADC_DUAL_MODE_REGSIMULT_INJECSIMULT)   || \
                                    ((MODE) == ADC_DUAL_MODE_REGSIMULT_ALTERTRIG)     || \
                                    ((MODE) == ADC_DUAL_MODE_INJECSIMULT)             || \
                                    ((MODE) == ADC_DUAL_MODE_REGSIMULT)               || \
                                    ((MODE) == ADC_DUAL_MODE_INTERL)                  || \
                                    ((MODE) == ADC_DUAL_MODE_ALTERTRIG)               || \
                                    ((MODE) == ADC_TRIPLE_MODE_REGSIMULT_INJECSIMULT) || \
                                    ((MODE) == ADC_TRIPLE_MODE_REGSIMULT_ALTERTRIG)   || \
                                    ((MODE) == ADC_TRIPLE_MODE_INJECSIMULT)           || \
                                    ((MODE) == ADC_TRIPLE_MODE_REGSIMULT)             || \
                                    ((MODE) == ADC_TRIPLE_MODE_INTERL)                || \
                                    ((MODE) == ADC_TRIPLE_MODE_ALTERTRIG)             )
/**
  * @}
  */

/** @defgroup ADC_MULTI_DMA_TRANSFER_RESOLUTION  Multimode - DMA transfer mode depending on ADC resolution
  * @{
  */
#define ADC_DMAACCESSMODE_DISABLED         ((uint32_t)0x00000000)     /*!< DMA multimode disabled: each ADC uses its own
                                           DMA channel */
#define ADC_DMAACCESSMODE_1                (ADC_CCR_MDMA_0)   /*!< DMA multimode enabled (2/3 half-words one by one - 1 then 2 then 3) */
#define ADC_DMAACCESSMODE_2                (ADC_CCR_MDMA_1)   /*!< DMA multimode enabled (2/3 half-words by pairs - 2&1 then 1&3 then 3&2) */
#define ADC_DMAACCESSMODE_3                (ADC_CCR_MDMA)     /*!< DMA multimode enabled (2/3 bytes by pairs - 2&1 then 1&3 then 3&2) */

#define IS_ADC_DMA_ACCESS_MULTIMODE(MODE)     (((MODE) == ADC_DMAACCESSMODE_DISABLED)   || \
                                               ((MODE) == ADC_DMAACCESSMODE_1) || \
                                               ((MODE) == ADC_DMAACCESSMODE_2) || \
                                               ((MODE) == ADC_DMAACCESSMODE_3  ))
/**
  * @}
  */

/** @defgroup ADC_MULTI_DMA_MODE
  * @{
  */
#define ADC_MULTI_DMAMODE_ONESHOT                        ((uint32_t)0x00000000)
#define ADC_MULTI_DMAMODE_CIRCULAR                       ADC_CCR_DMACFG

#define IS_ADC_MULTI_DMA_MODE(MODE) (((MODE) == ADC_MULTI_DMAMODE_ONESHOT) || \
                                     ((MODE) == ADC_MULTI_DMAMODE_CIRCULAR))
/**
  * @}
  */


/** @defgroup ADC_MULTI_TWOSMP_DELAY  Multimode - Delay between two sampling phases
  * @{
  */
#define ADC_TWOSAMPLINGDELAY_1CYCLE        ((uint32_t)0x00000000)
/*!< ADC multimode delay between two
     sampling phases: 1 ADC clock cycle */
#define ADC_TWOSAMPLINGDELAY_2CYCLES       ((uint32_t)ADC_CCR_DELAY_0)
/*!< ADC multimode delay between two
     sampling phases: 2 ADC clock cycles */
#define ADC_TWOSAMPLINGDELAY_3CYCLES       ((uint32_t)ADC_CCR_DELAY_1)
/*!< ADC multimode delay between two
     sampling phases: 3 ADC clock cycles */
#define ADC_TWOSAMPLINGDELAY_4CYCLES       ((uint32_t)(ADC_CCR_DELAY_0|ADC_CCR_DELAY_1))
/*!< ADC multimode delay between two
     sampling phases: 4 ADC clock cycles */
#define ADC_TWOSAMPLINGDELAY_5CYCLES       (ADC_CCR_DELAY_2)
/*!< ADC multimode delay between two
     sampling phases: 5 ADC clock cycles */
#define ADC_TWOSAMPLINGDELAY_6CYCLES       ((uint32_t)(ADC_CCR_DELAY_0|ADC_CCR_DELAY_2))
/*!< ADC multimode delay between two
     sampling phases: 6 ADC clock cycles */
#define ADC_TWOSAMPLINGDELAY_7CYCLES       ((uint32_t)(ADC_CCR_DELAY_1|ADC_CCR_DELAY_2))
/*!< ADC multimode delay between two
     sampling phases: 7 ADC clock cycles */
#define ADC_TWOSAMPLINGDELAY_8CYCLES       ((uint32_t)(ADC_CCR_DELAY_0|ADC_CCR_DELAY_1|ADC_CCR_DELAY_2))
/*!< ADC multimode delay between two
     sampling phases: 8 ADC clock cycles */
#define ADC_TWOSAMPLINGDELAY_9CYCLES       ((uint32_t)ADC_CCR_DELAY_3)
/*!< ADC multimode delay between two
     sampling phases: 9 ADC clock cycles */
#define ADC_TWOSAMPLINGDELAY_10CYCLES      ((uint32_t)(ADC_CCR_DELAY_0|ADC_CCR_DELAY_3))
/*!< ADC multimode delay between two
     sampling phases: 10 ADC clock cycles */
#define ADC_TWOSAMPLINGDELAY_11CYCLES      ((uint32_t)(ADC_CCR_DELAY_1|ADC_CCR_DELAY_3))
/*!< ADC multimode delay between two
     sampling phases: 11 ADC clock cycles */
#define ADC_TWOSAMPLINGDELAY_12CYCLES      ((uint32_t)(ADC_CCR_DELAY_0|ADC_CCR_DELAY_1|ADC_CCR_DELAY_3))
/*!< ADC multimode delay between two
     sampling phases: 12 ADC clock cycles */
#define ADC_TWOSAMPLINGDELAY_13CYCLES      ((uint32_t)(ADC_CCR_DELAY_2|ADC_CCR_DELAY_3))
/*!< ADC multimode delay between two
     sampling phases: 13 ADC clock cycles */
#define ADC_TWOSAMPLINGDELAY_14CYCLES      ((uint32_t)(ADC_CCR_DELAY_0|ADC_CCR_DELAY_2|ADC_CCR_DELAY_3))
/*!< ADC multimode delay between two
     sampling phases: 14 ADC clock cycles */
#define ADC_TWOSAMPLINGDELAY_15CYCLES      ((uint32_t)(ADC_CCR_DELAY_1|ADC_CCR_DELAY_2|ADC_CCR_DELAY_3))
/*!< ADC multimode delay between two
     sampling phases: 15 ADC clock cycles */
#define ADC_TWOSAMPLINGDELAY_16CYCLES      ((uint32_t)(ADC_CCR_DELAY_0|ADC_CCR_DELAY_1|ADC_CCR_DELAY_2|ADC_CCR_DELAY_3))
/*!< ADC multimode delay between two
     sampling phases: 16 ADC clock cycles */


#define IS_ADC_TWOSAMPLING_DELAY(DELAY)   (((DELAY) == ADC_TWOSAMPLINGDELAY_1CYCLE)   || \
                                           ((DELAY) == ADC_TWOSAMPLINGDELAY_2CYCLES)  || \
                                           ((DELAY) == ADC_TWOSAMPLINGDELAY_3CYCLES)  || \
                                           ((DELAY) == ADC_TWOSAMPLINGDELAY_4CYCLES)  || \
                                           ((DELAY) == ADC_TWOSAMPLINGDELAY_5CYCLES)  || \
                                           ((DELAY) == ADC_TWOSAMPLINGDELAY_6CYCLES)  || \
                                           ((DELAY) == ADC_TWOSAMPLINGDELAY_7CYCLES)  || \
                                           ((DELAY) == ADC_TWOSAMPLINGDELAY_8CYCLES)  || \
                                           ((DELAY) == ADC_TWOSAMPLINGDELAY_9CYCLES)  || \
                                           ((DELAY) == ADC_TWOSAMPLINGDELAY_10CYCLES) || \
                                           ((DELAY) == ADC_TWOSAMPLINGDELAY_11CYCLES) || \
                                           ((DELAY) == ADC_TWOSAMPLINGDELAY_12CYCLES) || \
                                           ((DELAY) == ADC_TWOSAMPLINGDELAY_13CYCLES) || \
                                           ((DELAY) == ADC_TWOSAMPLINGDELAY_14CYCLES) || \
                                           ((DELAY) == ADC_TWOSAMPLINGDELAY_15CYCLES) || \
                                           ((DELAY) == ADC_TWOSAMPLINGDELAY_16CYCLES)   )
/**
  * @}
  */

/**
  * @brief Verify the length of the scheduled regular conversions group.
  * @param LENGTH number of programmed conversions.
  * @retval SET (LENGTH is within the maximum number of possible programmable regular conversions)
  *         or RESET (LENGTH is null or too large)
  */
#define IS_ADC_REGULAR_NUMBER(LENGTH) (((LENGTH) >= (uint32_t)(1)) && ((LENGTH) <= (uint32_t)(16)))
/**
  * @}
  */


/**
  * @brief Verify the length of the scheduled injected conversions group.
  * @param LENGTH number of programmed conversions.
  * @retval SET (LENGTH is within the maximum number of possible programmable regular conversions)
  *         or RESET (LENGTH is null or too large)
  */
#define IS_ADC_INJECTED_NUMBER(LENGTH) (((LENGTH) >= (uint32_t)(1)) && ((LENGTH) <= (uint32_t)(4)))
/**
  * @}
  */


/**
  * @brief Verify the number of scheduled regular conversions in discontinuous mode.
  * @param NUMBER number of scheduled regular conversions in discontinuous mode.
  * @retval SET (NUMBER is within the maximum number of regular conversions in discontinuous mode)
  *         or RESET (NUMBER is null or too large)
  */
#define IS_ADC_REGULAR_DISCONT_NUMBER(NUMBER) (((NUMBER) >= (uint32_t)(1)) && ((NUMBER) <= (uint32_t)(8)))
/**
  * @}
  */

/**
  * @brief Verify the ADC gain compensation.
  * @param GAIN_COMPENSATION programmed ADC gain compensation coefficient.
  * @retval SET (GAIN_COMPENSATION is a valid value) or RESET (GAIN_COMPENSATION is invalid)
  */
#define IS_ADC_GAIN_COMPENSATION(GAIN_COMPENSATION) ((GAIN_COMPENSATION) <= ((uint32_t)16383))
/**
  * @}
  */






/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/*  Function used to set the ADC configuration to the default reset state *****/
void ADC_DeInit(void);

/* Initialization and Configuration functions *********************************/
void ADC_Init(ADC_TypeDef* ADCx, ADC_InitTypeDef* ADC_InitStruct);
void ADC_StructInit(ADC_InitTypeDef* ADC_InitStruct);
void ADC_InjectedStructInit(ADC_InjectedConfTypeDef* ADC_InjectedConf);
void ADC_Cmd(ADC_TypeDef* ADCx, FunctionalState NewState);
void ADC_ClockModeConfig(uint32_t ClockMode);
void ADC_MultiModeConfig(ADC_MultiModeTypeDef* MultiMode);

/* Power saving functions *****************************************************/
void ADC_AutoPowerOffCmd(ADC_TypeDef* ADCx, FunctionalState NewState);
void ADC_ADC_AutDlyModeCmd(ADC_TypeDef* ADCx, FunctionalState NewState);
void ADC_DeepPWDModeCmd(ADC_TypeDef* ADCx, FunctionalState NewState);
void ADC_InternalRegulatorCmd(ADC_TypeDef* ADCx, FunctionalState NewState);

/* Analog Watchdog configuration functions ************************************/
void ADC_AnalogWDGConfig(ADC_TypeDef* ADCx, ADC_InitTypeDef* ADC_InitStruct, ADC_AnalogWDGConfTypeDef* AnalogWDGConfig);

/* Temperature Sensor , Vrefint and Vbat management function ... ******************/
void ADC_TempSensorCmd(FunctionalState NewState);
void ADC_VrefintCmd(FunctionalState NewState);
void ADC_VbatCmd(FunctionalState NewState);
void ADC_BatteryAutoChargingCmd(FunctionalState NewState);
void ADC_AWD2MonitorVbatCmd(FunctionalState NewState);
void ADC_AWD3MonitorVbatCmd(FunctionalState NewState);

/* Channels Configuration functions *******************************************/
void ADC_RegularChannelConfig(ADC_TypeDef* ADCx, ADC_ChannelConfTypeDef* RegularConfig);
void ADC_InjectedChannelConfig(ADC_TypeDef* ADCx, ADC_InjectedConfTypeDef* InjectedConfig);
void ADC_ContinuousModeCmd(ADC_TypeDef* ADCx, FunctionalState NewState);
void ADC_AutoDelayModeCmd(ADC_TypeDef* ADCx, FunctionalState NewState);
void ADC_AutoInjectedModeCmd(ADC_TypeDef* ADCx, FunctionalState NewState);
void ADC_REG_DiscModeCmd(ADC_TypeDef* ADCx, uint32_t DiscontNum);
void ADC_INJ_DiscModeCmd(ADC_TypeDef* ADCx, FunctionalState NewState);
void ADC_OverrunModeCmd(ADC_TypeDef* ADCx, FunctionalState NewState);
uint32_t ADC_StartSingleCalibration(ADC_TypeDef* ADCx);
uint32_t ADC_StartDiffCalibration(ADC_TypeDef* ADCx);
uint32_t ADC_GetSingleCalibrationFactor(ADC_TypeDef* ADCx);
uint32_t ADC_GetDiffCalibrationFactor(ADC_TypeDef* ADCx);
void ADC_SetSingleCalibrationFactor(ADC_TypeDef* ADCx, uint32_t Calfact_S);
void ADC_SetDiffCalibrationFactor(ADC_TypeDef* ADCx, uint32_t Calfact_D);
void ADC_REG_StartOfConversion(ADC_TypeDef* ADCx);
void ADC_REG_StopOfConversion(ADC_TypeDef* ADCx);
void ADC_INJ_StartOfConversion(ADC_TypeDef* ADCx);
void ADC_INJ_StopOfConversion(ADC_TypeDef* ADCx);
uint16_t ADC_REG_GetConversionValue(ADC_TypeDef* ADCx);
uint16_t ADC_INJ_GetConversionValue(ADC_TypeDef* ADCx, uint32_t INJ_RANK);
uint32_t ADC_ReadMultiConversionData32(void);
void ADC_StartSamplingPhase(ADC_TypeDef* ADCx);
void ADC_StoptSamplingPhase(ADC_TypeDef* ADCx);

/* Regular Channels DMA Configuration functions *******************************/
void ADC_DMACmd(ADC_TypeDef* ADCx, FunctionalState NewState);
void ADC_DMARequestModeConfig(ADC_TypeDef* ADCx, uint32_t ADC_DMARequestMode);

/* Interrupts and flags management functions **********************************/
void ADC_ITConfig(ADC_TypeDef* ADCx, uint32_t ADC_IT, FunctionalState NewState);
FlagStatus ADC_GetFlagStatus(ADC_TypeDef* ADCx, uint32_t ADC_FLAG);
FlagStatus ADC_GetMultiFlagStatus(ADC_TypeDef* ADCx, uint32_t ADC_FLAG);
void ADC_ClearFlag(ADC_TypeDef* ADCx, uint32_t ADC_FLAG);
ITStatus ADC_GetITStatus(ADC_TypeDef* ADCx, uint32_t ADC_IT);
void ADC_ClearITPendingBit(ADC_TypeDef* ADCx, uint32_t ADC_IT);


#ifdef __cplusplus
}
#endif

#endif /*__ft32f4XX_ADC_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT FMD *****END OF FILE****/
