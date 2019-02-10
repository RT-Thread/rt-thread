/**
  ******************************************************************************
  * @file    stm32h7xx_hal_adc.h
  * @author  MCD Application Team
  * @brief   Header file of ADC HAL module.
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
#ifndef __STM32H7xx_ADC_H
#define __STM32H7xx_ADC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal_def.h"

/** @addtogroup STM32H7xx_HAL_Driver
  * @{
  */

/** @addtogroup ADC
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup ADC_Exported_Types ADC Exported Types
  * @{
  */

/**
  * @brief  ADC Regular Conversion Oversampling structure definition
  */
typedef struct
{
  uint32_t Ratio;                         /*!< Configures the oversampling ratio. */


  uint32_t RightBitShift;                 /*!< Configures the division coefficient for the Oversampler.
                                               This parameter can be a value of @ref ADCEx_Right_Bit_Shift */

  uint32_t TriggeredMode;                 /*!< Selects the regular triggered oversampling mode.
                                               This parameter can be a value of @ref ADCEx_Triggered_Oversampling_Mode */

  uint32_t OversamplingStopReset;         /*!< Selects the regular oversampling mode.
                                               The oversampling is either temporary stopped or reset upon an injected
                                               sequence interruption.
                                               If oversampling is enabled on both regular and injected groups, this parameter
                                               is discarded and forced to setting "ADC_REGOVERSAMPLING_RESUMED_MODE"
                                               (the oversampling buffer is zeroed during injection sequence).
                                               This parameter can be a value of @ref ADCEx_Regular_Oversampling_Mode */
}ADC_OversamplingTypeDef;

/**
  * @brief  Structure definition of ADC instance and ADC group regular.
  * @note   Parameters of this structure are shared within 2 scopes:
  *          - Scope entire ADC (affects ADC groups regular and injected): ClockPrescaler, Resolution, DataAlign,
  *            ScanConvMode, EOCSelection, LowPowerAutoWait.
  *          - Scope ADC group regular: ContinuousConvMode, NbrOfConversion, DiscontinuousConvMode, NbrOfDiscConversion,
  *            ExternalTrigConv, ExternalTrigConvEdge, DMAContinuousRequests, Overrun, OversamplingMode, Oversampling.
  * @note   The setting of these parameters by function HAL_ADC_Init() is conditioned to ADC state.
  *         ADC state can be either:
  *          - For all parameters: ADC disabled
  *          - For all parameters except 'LowPowerAutoWait', 'DMAContinuousRequests' and 'Oversampling': ADC enabled without conversion on going on group regular.
  *          - For parameters 'LowPowerAutoWait' and 'DMAContinuousRequests': ADC enabled without conversion on going on groups regular and injected.
  *         If ADC is not in the appropriate state to modify some parameters, these parameters setting is bypassed
  *         without error reporting (as it can be the expected behavior in case of intended action to update another parameter
  *         (which fulfills the ADC state condition) on the fly).
  */
typedef struct
{
  uint32_t ClockPrescaler;        /*!< Select ADC clock source (synchronous clock derived from APB clock or asynchronous clock derived from System/PLL2/PLL3 clocks) and clock prescaler.

                                       This parameter can be a value of @ref ADC_ClockPrescaler.
                                       Note: The clock is common for all the ADCs.
                                       Note: In case of usage of channels on injected group, ADC frequency should be lower than AHB clock frequency /4 for resolution 16, 14, 12 or 10 bits,
                                             AHB clock frequency /3 for resolution 8 bits.
                                       Note: In case of synchronous clock mode based on HCLK/1, the configuration must be enabled only
                                             if the system clock has a 50% duty clock cycle (APB prescaler configured inside RCC
                                             must be bypassed and PCLK clock must have 50% duty cycle). Refer to reference manual for details.
                                       Note: In case of usage of the ADC dedicated PLL clock, it must be preliminarily enabled at RCC top level.
                                       Note: This parameter can be modified only if all ADCs are disabled. */

  uint32_t Resolution;            /*!< Configure the ADC resolution.
                                       This parameter can be a value of @ref ADC_Resolution */

  uint32_t ScanConvMode;          /*!< Configure the sequencer of ADC groups regular and injected.
                                       This parameter can be associated to parameter 'DiscontinuousConvMode' to have main sequence subdivided in successive parts.
                                       If disabled: Conversion is performed in single mode (one channel converted, the one defined in rank 1).
                                                    Parameters 'NbrOfConversion' and 'InjectedNbrOfConversion' are discarded (equivalent to set to 1).
                                       If enabled:  Conversions are performed in sequence mode (multiple ranks defined by 'NbrOfConversion' or 'InjectedNbrOfConversion' and rank of each channel in sequencer).
                                                    Scan direction is upward: from rank 1 to rank 'n'.
                                       This parameter can be a value of @ref ADC_Scan_mode */

  uint32_t EOCSelection;          /*!< Specify which EOC (End Of Conversion) flag is used for conversion by polling and interruption: end of unitary conversion or end of sequence conversions.
                                       This parameter can be a value of @ref ADC_EOCSelection. */

  FunctionalState LowPowerAutoWait;      /*!< Select the dynamic low power Auto Delay: new conversion start only when the previous
                                       conversion (for ADC group regular) or previous sequence (for ADC group injected) has been retrieved by user software,
                                       using function HAL_ADC_GetValue() or HAL_ADCEx_InjectedGetValue().
                                       This feature automatically adapts the frequency of ADC conversions triggers to the speed of the system that reads the data. Moreover, this avoids risk of overrun
                                       for low frequency applications.
                                       This parameter can be set to ENABLE or DISABLE.
                                       Note: Do not use with interruption or DMA (HAL_ADC_Start_IT(), HAL_ADC_Start_DMA()) since they clear immediately the EOC flag
                                             to free the IRQ vector sequencer.
                                             Do use with polling: 1. Start conversion with HAL_ADC_Start(), 2. Later on, when ADC conversion data is needed:
                                             use HAL_ADC_PollForConversion() to ensure that conversion is completed and HAL_ADC_GetValue() to retrieve conversion result and trig another conversion start.
                                             (in case of usage of ADC group injected, use the equivalent functions HAL_ADCExInjected_Start(), HAL_ADCEx_InjectedGetValue(), ...). */

  FunctionalState ContinuousConvMode;    /*!< Specify whether the conversion is performed in single mode (one conversion) or continuous mode for ADC group regular,
                                       after the first ADC conversion start trigger occurred (software start or external trigger).
                                       This parameter can be set to ENABLE or DISABLE. */

  uint32_t NbrOfConversion;       /*!< Specify the number of ranks that will be converted within the regular group sequencer.
                                       To use the regular group sequencer and convert several ranks, parameter 'ScanConvMode' must be enabled.
                                       This parameter must be a number between Min_Data = 1 and Max_Data = 16.
                                       Note: This parameter must be modified when no conversion is on going on regular group (ADC disabled, or ADC enabled without
                                       continuous mode or external trigger that could launch a conversion). */

  FunctionalState DiscontinuousConvMode; /*!< Specify whether the conversions sequence of ADC group regular is performed in Complete-sequence/Discontinuous-sequence
                                       (main sequence subdivided in successive parts).
                                       Discontinuous mode is used only if sequencer is enabled (parameter 'ScanConvMode'). If sequencer is disabled, this parameter is discarded.
                                       Discontinuous mode can be enabled only if continuous mode is disabled. If continuous mode is enabled, this parameter setting is discarded.
                                       This parameter can be set to ENABLE or DISABLE. */

  uint32_t NbrOfDiscConversion;   /*!< Specifies the number of discontinuous conversions in which the main sequence of ADC group regular (parameter NbrOfConversion) will be subdivided.
                                       If parameter 'DiscontinuousConvMode' is disabled, this parameter is discarded.
                                       This parameter must be a number between Min_Data = 1 and Max_Data = 8. */

  uint32_t ExternalTrigConv;      /*!< Select the external event source used to trigger ADC group regular conversion start.
                                       If set to ADC_SOFTWARE_START, external triggers are disabled and software trigger is used instead.
                                       This parameter can be a value of @ref ADC_regular_external_trigger_source.
                                       Caution: external trigger source is common to all ADC instances. */

  uint32_t ExternalTrigConvEdge;  /*!< Select the external event edge used to trigger ADC group regular conversion start.
                                       If trigger source is set to ADC_SOFTWARE_START, this parameter is discarded.
                                       This parameter can be a value of @ref ADC_regular_external_trigger_edge */

  uint32_t ConversionDataManagement; /*!< Specifies whether the Data conversion data is managed: using the DMA (oneshot or circular), or stored in the DR register or transfered to DFSDM register.
                                       Note: In continuous mode, DMA must be configured in circular mode. Otherwise an overrun will be triggered when DMA buffer maximum pointer is reached.
                                       This parameter can be a value of @ref ADC_ConversionDataManagement.
                                       Note: This parameter must be modified when no conversion is on going on both regular and injected groups
                                       (ADC disabled, or ADC enabled without continuous mode or external trigger that could launch a conversion). */

  uint32_t Overrun;                  /*!< Select the behavior in case of overrun: data overwritten or preserved (default).
                                       This parameter applies to ADC group regular only.
                                       This parameter can be a value of @ref ADC_Overrun.
                                       Note: In case of overrun set to data preserved and usage with programming model with interruption (HAL_Start_IT()): ADC IRQ handler has to clear
                                       end of conversion flags, this induces the release of the preserved data. If needed, this data can be saved in function
                                       HAL_ADC_ConvCpltCallback(), placed in user program code (called before end of conversion flags clear).
                                       Note: Error reporting with respect to the conversion mode:
                                             - Usage with ADC conversion by polling for event or interruption: Error is reported only if overrun is set to data preserved. If overrun is set to data
                                               overwritten, user can willingly not read all the converted data, this is not considered as an erroneous case.
                                             - Usage with ADC conversion by DMA: Error is reported whatever overrun setting (DMA is expected to process all data from data register). */

  uint32_t LeftBitShift;             /*!< Configures the left shifting applied to the final result with or without oversampling.
                                          This parameter can be a value of @ref ADCEx_Left_Bit_Shift */

  FunctionalState BoostMode;         /*!< Configures the Boost mode control.
                                        When selecting an analog ADC clock frequency bigger than 20MHz,
                                      it is mandatory to first enable the BOOST Mode.
                                          This parameter can be set to ENABLE or DISABLE. */

  FunctionalState OversamplingMode;        /*!< Specify whether the oversampling feature is enabled or disabled.
                                        This parameter can be set to ENABLE or DISABLE.
                                        Note: This parameter can be modified only if there is no conversion is ongoing on ADC groups regular and injected */

  ADC_OversamplingTypeDef Oversampling;   /*!< Specify the Oversampling parameters.
                                               Caution: this setting overwrites the previous oversampling configuration if oversampling is already enabled. */
}ADC_InitTypeDef;

/**
  * @brief  Structure definition of ADC analog watchdog
  * @note   The setting of these parameters by function HAL_ADC_AnalogWDGConfig() is conditioned to ADC state.
  *         ADC state can be either:
  *         ADC disabled or ADC enabled without conversion on going on ADC groups regular and injected.
  */
typedef struct
{
  uint32_t WatchdogNumber;    /*!< Select which ADC analog watchdog is monitoring the selected channel.
                                   For Analog Watchdog 1: Only 1 channel can be monitored (or overall group of channels by setting parameter 'WatchdogMode')
                                   For Analog Watchdog 2 and 3: Several channels can be monitored (by successive calls of 'HAL_ADC_AnalogWDGConfig()' for each channel)
                                   This parameter can be a value of @ref ADCEx_analog_watchdog_number. */

  uint32_t WatchdogMode;      /*!< Configure the ADC analog watchdog mode: single/all/none channels.
                                   For Analog Watchdog 1: Configure the ADC analog watchdog mode: single channel/all channels, ADC groups regular and/or injected.
                                   For Analog Watchdog 2 and 3: There is no configuration for all channels as AWD1. Set value 'ADC_ANALOGWATCHDOG_NONE' to reset
                                   channels group programmed with parameter 'Channel', set any other value to program the channel(s) to be monitored.
                                   This parameter can be a value of @ref ADCEx_analog_watchdog_mode. */

  uint32_t Channel;           /*!< Select which ADC channel to monitor by analog watchdog.
                                   For Analog Watchdog 1: this parameter has an effect only if parameter 'WatchdogMode' is configured on single channel (only 1 channel can be monitored).
                                   For Analog Watchdog 2 and 3: Several channels can be monitored. To use this feature, call successively the function HAL_ADC_AnalogWDGConfig() for each channel to be added (or removed with value 'ADC_ANALOGWATCHDOG_NONE').
                                   This parameter can be a value of @ref ADC_channels. */

  FunctionalState ITMode;            /*!< Specify whether the analog watchdog is configured in interrupt or polling mode.
                                   This parameter can be set to ENABLE or DISABLE */

  uint32_t HighThreshold;     /*!< Configure the ADC analog watchdog High threshold value.
                                   Depending of ADC resolution selected (16, 14, 12, 10 or 8 bits), this parameter must be a number
                                   between Min_Data = 0x0000 and Max_Data = 0xFFFF, 0x3FFF, 0xFFF, 0x3FF or 0xFF respectively. */

  uint32_t LowThreshold;      /*!< Configures the ADC analog watchdog Low threshold value.
                                   Depending of ADC resolution selected (16, 14, 12, or 8 bits), this parameter must be a number
                                   between Min_Data = 0x0000 and Max_Data = 0xFFFF, 0x3FFF, 0xFFF, 0x3FF or 0xFF respectively. */

}ADC_AnalogWDGConfTypeDef;

/** @defgroup ADC_States ADC States
  * @{
  */
/**
  * @brief  HAL ADC state machine: ADC states definition (bitfields)
  * @note   ADC state machine is managed by bitfields, state must be compared
  *         with bit by bit.
  *         For example:
  *           " if (HAL_IS_BIT_SET(HAL_ADC_GetState(hadc1), HAL_ADC_STATE_REG_BUSY)) "
  *           " if (HAL_IS_BIT_SET(HAL_ADC_GetState(hadc1), HAL_ADC_STATE_AWD1)    ) "
  */
/* States of ADC global scope */
#define HAL_ADC_STATE_RESET             ((uint32_t)0x00000000)    /*!< ADC not yet initialized or disabled */
#define HAL_ADC_STATE_READY             ((uint32_t)0x00000001)    /*!< ADC peripheral ready for use */
#define HAL_ADC_STATE_BUSY_INTERNAL     ((uint32_t)0x00000002)    /*!< ADC is busy due to an internal process (initialization, calibration) */
#define HAL_ADC_STATE_TIMEOUT           ((uint32_t)0x00000004)    /*!< TimeOut occurrence */

/* States of ADC errors */
#define HAL_ADC_STATE_ERROR_INTERNAL    ((uint32_t)0x00000010)    /*!< Internal error occurrence */
#define HAL_ADC_STATE_ERROR_CONFIG      ((uint32_t)0x00000020)    /*!< Configuration error occurrence */
#define HAL_ADC_STATE_ERROR_DMA         ((uint32_t)0x00000040)    /*!< DMA error occurrence */

/* States of ADC group regular */
#define HAL_ADC_STATE_REG_BUSY          ((uint32_t)0x00000100)    /*!< A conversion on ADC group regular is ongoing or can occur (either by continuous mode,
                                                                       external trigger, low power auto power-on (if feature available), multimode ADC master control (if feature available)) */
#define HAL_ADC_STATE_REG_EOC           ((uint32_t)0x00000200)    /*!< Conversion data available on group regular */
#define HAL_ADC_STATE_REG_OVR           ((uint32_t)0x00000400)    /*!< Overrun occurrence */
#define HAL_ADC_STATE_REG_EOSMP         ((uint32_t)0x00000800)    /*!< Not available on this STM32 serie: End Of Sampling flag raised  */

/* States of ADC group injected */
#define HAL_ADC_STATE_INJ_BUSY          ((uint32_t)0x00001000)    /*!< A conversion on ADC group injected is ongoing or can occur (either by auto-injection mode,
                                                                       external trigger, low power auto power-on (if feature available), multimode ADC master control (if feature available)) */
#define HAL_ADC_STATE_INJ_EOC           ((uint32_t)0x00002000)    /*!< Conversion data available on group injected */
#define HAL_ADC_STATE_INJ_JQOVF         ((uint32_t)0x00004000)    /*!< Injected queue overflow occurrence */

/* States of ADC analog watchdogs */
#define HAL_ADC_STATE_AWD1              ((uint32_t)0x00010000)    /*!< Out-of-window occurrence of ADC analog watchdog 1 */
#define HAL_ADC_STATE_AWD2              ((uint32_t)0x00020000)    /*!< Out-of-window occurrence of ADC analog watchdog 2 */
#define HAL_ADC_STATE_AWD3              ((uint32_t)0x00040000)    /*!< Out-of-window occurrence of ADC analog watchdog 3 */

/* States of ADC multi-mode */
#define HAL_ADC_STATE_MULTIMODE_SLAVE   ((uint32_t)0x00100000)    /*!< ADC in multimode slave state, controlled by another ADC master (when feature available) */
/**
  * @}
  */

/**
  * @}
  */


/* Exported constants --------------------------------------------------------*/

/** @defgroup ADC_Exported_Constants ADC Exported Constants
  * @{
  */

/** @defgroup ADC_Error_Code ADC Error Code
  * @{
  */
#define HAL_ADC_ERROR_NONE         ((uint32_t)0x00)   /*!< No error                                 */
#define HAL_ADC_ERROR_INTERNAL     ((uint32_t)0x01)   /*!< ADC IP internal error (problem of clocking,
                                                          enable/disable, erroneous state, ...)     */
#define HAL_ADC_ERROR_OVR          ((uint32_t)0x02)   /*!< Overrun error                            */
#define HAL_ADC_ERROR_DMA          ((uint32_t)0x04)   /*!< DMA transfer error                       */
#define HAL_ADC_ERROR_JQOVF        ((uint32_t)0x08)   /*!< Injected context queue overflow error    */
/**
  * @}
  */

/** @defgroup ADC_ClockPrescaler ADC clock source and clock prescaler
  * @{
  */
#define ADC_CLOCK_SYNC_PCLK_DIV1      ((uint32_t)ADC_CCR_CKMODE_0)  /*!< ADC synchronous clock derived from AHB clock not divided  */
#define ADC_CLOCK_SYNC_PCLK_DIV2      ((uint32_t)ADC_CCR_CKMODE_1)  /*!< ADC synchronous clock derived from AHB clock divided by 2 */
#define ADC_CLOCK_SYNC_PCLK_DIV4      ((uint32_t)ADC_CCR_CKMODE)    /*!< ADC synchronous clock derived from AHB clock divided by 4 */

#define ADC_CLOCKPRESCALER_PCLK_DIV1   ADC_CLOCK_SYNC_PCLK_DIV1     /*!< Obsolete naming, kept for compatibility with some other devices */
#define ADC_CLOCKPRESCALER_PCLK_DIV2   ADC_CLOCK_SYNC_PCLK_DIV2     /*!< Obsolete naming, kept for compatibility with some other devices */
#define ADC_CLOCKPRESCALER_PCLK_DIV4   ADC_CLOCK_SYNC_PCLK_DIV4     /*!< Obsolete naming, kept for compatibility with some other devices */

#define ADC_CLOCK_ASYNC_DIV1       ((uint32_t)0x00000000)                                        /*!< ADC asynchronous clock not divided    */
#define ADC_CLOCK_ASYNC_DIV2       ((uint32_t)ADC_CCR_PRESC_0)                                   /*!< ADC asynchronous clock divided by 2   */
#define ADC_CLOCK_ASYNC_DIV4       ((uint32_t)ADC_CCR_PRESC_1)                                   /*!< ADC asynchronous clock divided by 4   */
#define ADC_CLOCK_ASYNC_DIV6       ((uint32_t)(ADC_CCR_PRESC_1|ADC_CCR_PRESC_0))                 /*!< ADC asynchronous clock divided by 6   */
#define ADC_CLOCK_ASYNC_DIV8       ((uint32_t)(ADC_CCR_PRESC_2))                                 /*!< ADC asynchronous clock divided by 8   */
#define ADC_CLOCK_ASYNC_DIV10      ((uint32_t)(ADC_CCR_PRESC_2|ADC_CCR_PRESC_0))                 /*!< ADC asynchronous clock divided by 10  */
#define ADC_CLOCK_ASYNC_DIV12      ((uint32_t)(ADC_CCR_PRESC_2|ADC_CCR_PRESC_1))                 /*!< ADC asynchronous clock divided by 12  */
#define ADC_CLOCK_ASYNC_DIV16      ((uint32_t)(ADC_CCR_PRESC_2|ADC_CCR_PRESC_1|ADC_CCR_PRESC_0)) /*!< ADC asynchronous clock divided by 16  */
#define ADC_CLOCK_ASYNC_DIV32      ((uint32_t)(ADC_CCR_PRESC_3))                                 /*!< ADC asynchronous clock divided by 32  */
#define ADC_CLOCK_ASYNC_DIV64      ((uint32_t)(ADC_CCR_PRESC_3|ADC_CCR_PRESC_0))                 /*!< ADC asynchronous clock divided by 64  */
#define ADC_CLOCK_ASYNC_DIV128     ((uint32_t)(ADC_CCR_PRESC_3|ADC_CCR_PRESC_1))                 /*!< ADC asynchronous clock divided by 128 */
#define ADC_CLOCK_ASYNC_DIV256     ((uint32_t)(ADC_CCR_PRESC_3|ADC_CCR_PRESC_1|ADC_CCR_PRESC_0)) /*!< ADC asynchronous clock divided by 256 */
/**
  * @}
  */

/** @defgroup ADC_Resolution ADC Resolution
  * @{
  */
#define ADC_RESOLUTION_16B      ((uint32_t)0x00000000)                             /*!<  ADC 16-bit resolution */
#define ADC_RESOLUTION_14B      ((uint32_t)ADC_CFGR_RES_0)                         /*!<  ADC 14-bit resolution */
#define ADC_RESOLUTION_12B      ((uint32_t)ADC_CFGR_RES_1)                         /*!<  ADC 12-bit resolution */
#define ADC_RESOLUTION_10B      ((uint32_t)(ADC_CFGR_RES_1 | ADC_CFGR_RES_0))      /*!<  ADC 10-bit resolution */
#define ADC_RESOLUTION_8B       ((uint32_t)ADC_CFGR_RES_2)                         /*!<  ADC 8-bit resolution */
/**
  * @}
  */

/** @defgroup ADC_Scan_mode ADC sequencer scan mode
  * @{
  */
#define ADC_SCAN_DISABLE         ((uint32_t)0x00000000)        /*!< Scan mode disabled */
#define ADC_SCAN_ENABLE          ((uint32_t)0x00000001)        /*!< Scan mode enabled  */
/**
  * @}
  */

/** @defgroup ADC_regular_external_trigger_source ADC group regular trigger source
  * @{
  */
/* External triggers of regular group for ADC1, ADC2, ADC3 */
#define ADC_EXTERNALTRIG_T1_CC1           ((uint32_t)0x00000000)
#define ADC_EXTERNALTRIG_T1_CC2           ((uint32_t)ADC_CFGR_EXTSEL_0)
#define ADC_EXTERNALTRIG_T1_CC3           ((uint32_t)ADC_CFGR_EXTSEL_1)
#define ADC_EXTERNALTRIG_T2_CC2           ((uint32_t)(ADC_CFGR_EXTSEL_1 | ADC_CFGR_EXTSEL_0))
#define ADC_EXTERNALTRIG_T3_TRGO          ((uint32_t)ADC_CFGR_EXTSEL_2)
#define ADC_EXTERNALTRIG_T4_CC4           ((uint32_t)(ADC_CFGR_EXTSEL_2 | ADC_CFGR_EXTSEL_0))
#define ADC_EXTERNALTRIG_EXT_IT11         ((uint32_t)(ADC_CFGR_EXTSEL_2 | ADC_CFGR_EXTSEL_1))
#define ADC_EXTERNALTRIG_T8_TRGO          ((uint32_t)(ADC_CFGR_EXTSEL_2 | ADC_CFGR_EXTSEL_1 | ADC_CFGR_EXTSEL_0))
#define ADC_EXTERNALTRIG_T8_TRGO2         ((uint32_t) ADC_CFGR_EXTSEL_3)
#define ADC_EXTERNALTRIG_T1_TRGO          ((uint32_t)(ADC_CFGR_EXTSEL_3 | ADC_CFGR_EXTSEL_0))
#define ADC_EXTERNALTRIG_T1_TRGO2         ((uint32_t)(ADC_CFGR_EXTSEL_3 | ADC_CFGR_EXTSEL_1))
#define ADC_EXTERNALTRIG_T2_TRGO          ((uint32_t)(ADC_CFGR_EXTSEL_3 | ADC_CFGR_EXTSEL_1 | ADC_CFGR_EXTSEL_0))
#define ADC_EXTERNALTRIG_T4_TRGO          ((uint32_t)(ADC_CFGR_EXTSEL_3 | ADC_CFGR_EXTSEL_2))
#define ADC_EXTERNALTRIG_T6_TRGO          ((uint32_t)(ADC_CFGR_EXTSEL_3 | ADC_CFGR_EXTSEL_2 | ADC_CFGR_EXTSEL_0))
#define ADC_EXTERNALTRIG_T15_TRGO         ((uint32_t)(ADC_CFGR_EXTSEL_3 | ADC_CFGR_EXTSEL_2 | ADC_CFGR_EXTSEL_1))
#define ADC_EXTERNALTRIG_T3_CC4           ((uint32_t)(ADC_CFGR_EXTSEL_3 | ADC_CFGR_EXTSEL_2 | ADC_CFGR_EXTSEL_1 | ADC_CFGR_EXTSEL_0))
#define ADC_EXTERNALTRIG_HR1_ADCTRG1      ((uint32_t) ADC_CFGR_EXTSEL_4)
#define ADC_EXTERNALTRIG_HR1_ADCTRG3      ((uint32_t) (ADC_CFGR_EXTSEL_4 | ADC_CFGR_EXTSEL_0))
#define ADC_EXTERNALTRIG_LPTIM1_OUT       ((uint32_t) (ADC_CFGR_EXTSEL_4 | ADC_CFGR_EXTSEL_1))
#define ADC_EXTERNALTRIG_LPTIM2_OUT       ((uint32_t) (ADC_CFGR_EXTSEL_4 | ADC_CFGR_EXTSEL_1| ADC_CFGR_EXTSEL_0))
#define ADC_EXTERNALTRIG_LPTIM3_OUT       ((uint32_t) (ADC_CFGR_EXTSEL_4 | ADC_CFGR_EXTSEL_2))

#define ADC_SOFTWARE_START                ((uint32_t)0x00000001)
/**
  * @}
  */

/** @defgroup ADC_regular_external_trigger_edge ADC group regular trigger edge (when external trigger is selected)
  * @{
  */
#define ADC_EXTERNALTRIGCONVEDGE_NONE           ((uint32_t)0x00000000)        /*!< Regular conversions hardware trigger detection disabled */
#define ADC_EXTERNALTRIGCONVEDGE_RISING         ((uint32_t)ADC_CFGR_EXTEN_0)  /*!< Regular conversions hardware trigger detection on the rising edge */
#define ADC_EXTERNALTRIGCONVEDGE_FALLING        ((uint32_t)ADC_CFGR_EXTEN_1)  /*!< Regular conversions hardware trigger detection on the falling edge */
#define ADC_EXTERNALTRIGCONVEDGE_RISINGFALLING  ((uint32_t)ADC_CFGR_EXTEN)    /*!< Regular conversions hardware trigger detection on both the rising and falling edges */
/**
  * @}
  */

/** @defgroup ADC_EOCSelection ADC sequencer end of unitary conversion or sequence conversions
  * @{
  */
#define ADC_EOC_SINGLE_CONV         ((uint32_t) ADC_ISR_EOC)                 /*!< End of unitary conversion flag  */
#define ADC_EOC_SEQ_CONV            ((uint32_t) ADC_ISR_EOS)                 /*!< End of sequence conversions flag    */
/**
  * @}
  */

/** @defgroup ADC_Overrun ADC overrun
  * @{
  */
#define ADC_OVR_DATA_PRESERVED             ((uint32_t)0x00000000)           /*!< Data preserved in case of overrun   */
#define ADC_OVR_DATA_OVERWRITTEN           ((uint32_t)ADC_CFGR_OVRMOD)      /*!< Data overwritten in case of overrun */
/**
  * @}
  */

/** @defgroup ADC_regular_rank ADC group regular sequencer rank
  * @{
  */
#define ADC_REGULAR_RANK_1    ((uint32_t)0x00000001)       /*!< ADC regular conversion rank 1  */
#define ADC_REGULAR_RANK_2    ((uint32_t)0x00000002)       /*!< ADC regular conversion rank 2  */
#define ADC_REGULAR_RANK_3    ((uint32_t)0x00000003)       /*!< ADC regular conversion rank 3  */
#define ADC_REGULAR_RANK_4    ((uint32_t)0x00000004)       /*!< ADC regular conversion rank 4  */
#define ADC_REGULAR_RANK_5    ((uint32_t)0x00000005)       /*!< ADC regular conversion rank 5  */
#define ADC_REGULAR_RANK_6    ((uint32_t)0x00000006)       /*!< ADC regular conversion rank 6  */
#define ADC_REGULAR_RANK_7    ((uint32_t)0x00000007)       /*!< ADC regular conversion rank 7  */
#define ADC_REGULAR_RANK_8    ((uint32_t)0x00000008)       /*!< ADC regular conversion rank 8  */
#define ADC_REGULAR_RANK_9    ((uint32_t)0x00000009)       /*!< ADC regular conversion rank 9  */
#define ADC_REGULAR_RANK_10   ((uint32_t)0x0000000A)       /*!< ADC regular conversion rank 10 */
#define ADC_REGULAR_RANK_11   ((uint32_t)0x0000000B)       /*!< ADC regular conversion rank 11 */
#define ADC_REGULAR_RANK_12   ((uint32_t)0x0000000C)       /*!< ADC regular conversion rank 12 */
#define ADC_REGULAR_RANK_13   ((uint32_t)0x0000000D)       /*!< ADC regular conversion rank 13 */
#define ADC_REGULAR_RANK_14   ((uint32_t)0x0000000E)       /*!< ADC regular conversion rank 14 */
#define ADC_REGULAR_RANK_15   ((uint32_t)0x0000000F)       /*!< ADC regular conversion rank 15 */
#define ADC_REGULAR_RANK_16   ((uint32_t)0x00000010)       /*!< ADC regular conversion rank 16 */
/**
  * @}
  */

/** @defgroup ADC_channels ADC Channels
  * @{
  */
#define ADC_CHANNEL_0           ((uint32_t)(0x00000000))
#define ADC_CHANNEL_1           ((uint32_t)(ADC_SQR3_SQ10_0))
#define ADC_CHANNEL_2           ((uint32_t)(ADC_SQR3_SQ10_1))
#define ADC_CHANNEL_3           ((uint32_t)(ADC_SQR3_SQ10_1 | ADC_SQR3_SQ10_0))
#define ADC_CHANNEL_4           ((uint32_t)(ADC_SQR3_SQ10_2))
#define ADC_CHANNEL_5           ((uint32_t)(ADC_SQR3_SQ10_2 | ADC_SQR3_SQ10_0))
#define ADC_CHANNEL_6           ((uint32_t)(ADC_SQR3_SQ10_2 | ADC_SQR3_SQ10_1))
#define ADC_CHANNEL_7           ((uint32_t)(ADC_SQR3_SQ10_2 | ADC_SQR3_SQ10_1 | ADC_SQR3_SQ10_0))
#define ADC_CHANNEL_8           ((uint32_t)(ADC_SQR3_SQ10_3))
#define ADC_CHANNEL_9           ((uint32_t)(ADC_SQR3_SQ10_3 | ADC_SQR3_SQ10_0))
#define ADC_CHANNEL_10          ((uint32_t)(ADC_SQR3_SQ10_3 | ADC_SQR3_SQ10_1))
#define ADC_CHANNEL_11          ((uint32_t)(ADC_SQR3_SQ10_3 | ADC_SQR3_SQ10_1 | ADC_SQR3_SQ10_0))
#define ADC_CHANNEL_12          ((uint32_t)(ADC_SQR3_SQ10_3 | ADC_SQR3_SQ10_2))
#define ADC_CHANNEL_13          ((uint32_t)(ADC_SQR3_SQ10_3 | ADC_SQR3_SQ10_2 | ADC_SQR3_SQ10_0))
#define ADC_CHANNEL_14          ((uint32_t)(ADC_SQR3_SQ10_3 | ADC_SQR3_SQ10_2 | ADC_SQR3_SQ10_1))
#define ADC_CHANNEL_15          ((uint32_t)(ADC_SQR3_SQ10_3 | ADC_SQR3_SQ10_2 | ADC_SQR3_SQ10_1 | ADC_SQR3_SQ10_0))
#define ADC_CHANNEL_16          ((uint32_t)(ADC_SQR3_SQ10_4))
#define ADC_CHANNEL_17          ((uint32_t)(ADC_SQR3_SQ10_4 | ADC_SQR3_SQ10_0))
#define ADC_CHANNEL_18          ((uint32_t)(ADC_SQR3_SQ10_4 | ADC_SQR3_SQ10_1))
#define ADC_CHANNEL_19          ((uint32_t)(ADC_SQR3_SQ10_4 | ADC_SQR3_SQ10_1| ADC_SQR3_SQ10_0))

/* Note: Vbat/4, TempSensor and VREFINT internal channels are available on ADC3 only */
#define ADC_CHANNEL_VBAT_DIV4    ADC_CHANNEL_17
#define ADC_CHANNEL_TEMPSENSOR   ADC_CHANNEL_18
#define ADC_CHANNEL_VREFINT      ADC_CHANNEL_19

/* Note: DAC1CH1 and DAC1CH2 internal channels is available on ADC2 only  */
#define ADC_CHANNEL_DAC1CH1_ADC2 (ADC_CHANNEL_16) /*!< ADC internal channel connected to DAC1 channel 1, channel specific to ADC2 */
#define ADC_CHANNEL_DAC1CH2_ADC2 (ADC_CHANNEL_17) /*!< ADC internal channel connected to DAC1 channel 2, channel specific to ADC2 */
/**
  * @}
  */


/** @defgroup ADC_ConversionDataManagement ADC Conversion Data Management
  * @{
  */
#define ADC_CONVERSIONDATA_DR                  ((uint32_t)0x00000000)                            /*!< Regular Conversion data stored in DR register only  */
#define ADC_CONVERSIONDATA_DFSDM               ((uint32_t)ADC_CFGR_DMNGT_1)                      /*!< DFSDM mode selected */
#define ADC_CONVERSIONDATA_DMA_ONESHOT         ((uint32_t)ADC_CFGR_DMNGT_0)                      /*!< DMA one shot mode selected */
#define ADC_CONVERSIONDATA_DMA_CIRCULAR        ((uint32_t)(ADC_CFGR_DMNGT_0 | ADC_CFGR_DMNGT_1)) /*!< DMA circular mode selected */
/**
  * @}
  */

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/

/** @defgroup ADC_Private_Macro ADC Private Macros
  * @{
  */

/**
  * @brief Verify the ADC data conversion setting.
  * @param DATA : programmed DATA conversion mode.
  * @retval SET (DATA is a valid value) or RESET (DATA is invalid)
  */
#define IS_ADC_CONVERSIONDATAMGT(DATA)                                         \
   ((((DATA) == ADC_CONVERSIONDATA_DR))          || \
    (((DATA) == ADC_CONVERSIONDATA_DFSDM))       || \
    (((DATA) == ADC_CONVERSIONDATA_DMA_ONESHOT)) || \
    (((DATA) == ADC_CONVERSIONDATA_DMA_CIRCULAR)))

/**
  * @brief Test if conversion trigger of regular group is software start
  *        or external trigger.
  * @param __HANDLE__: ADC handle
  * @retval SET (software start) or RESET (external trigger)
  */
#define ADC_IS_SOFTWARE_START_REGULAR(__HANDLE__)                        \
       (((__HANDLE__)->Instance->CFGR & ADC_CFGR_EXTEN) == RESET)

/**
  * @brief Returns resolution bits in CFGR register: RES[1:0].
  *        Returned value is among parameters in @ref ADC_Resolution.
  * @param __HANDLE__: ADC handle
  * @retval Parameter of @ref ADC_Resolution set.
  */
#define ADC_GET_RESOLUTION(__HANDLE__) (((__HANDLE__)->Instance->CFGR) & ADC_CFGR_RES)

/**
  * @brief Clear ADC error code (set it to error code: "no error")
  * @param __HANDLE__: ADC handle
  * @retval None
  */
#define ADC_CLEAR_ERRORCODE(__HANDLE__) ((__HANDLE__)->ErrorCode = HAL_ADC_ERROR_NONE)

/**
  * @brief Verification of ADC state: enabled or disabled
  * @param __HANDLE__: ADC handle
  * @retval SET (ADC enabled) or RESET (ADC disabled)
  */
#define ADC_IS_ENABLE(__HANDLE__)                                                    \
       (( ((((__HANDLE__)->Instance->CR) & (ADC_CR_ADEN | ADC_CR_ADDIS)) == ADC_CR_ADEN) && \
          ((((__HANDLE__)->Instance->ISR) & ADC_FLAG_RDY) == ADC_FLAG_RDY)                  \
        ) ? SET : RESET)

/**
  * @brief Check if no conversion on going on regular group
  * @param __HANDLE__: ADC handle
  * @retval SET (conversion is on going) or RESET (no conversion is on going)
  */
#define ADC_IS_CONVERSION_ONGOING_REGULAR(__HANDLE__)                    \
       (( (((__HANDLE__)->Instance->CR) & ADC_CR_ADSTART) == RESET             \
        ) ? RESET : SET)

/**
  * @brief Simultaneously clears and sets specific bits of the handle State
  * @note: ADC_STATE_CLR_SET() macro is merely aliased to generic macro MODIFY_REG(),
  *        the first parameter is the ADC handle State, the second parameter is the
  *        bit field to clear, the third and last parameter is the bit field to set
  * @retval None
  */
#define ADC_STATE_CLR_SET MODIFY_REG

/**
  * @brief Verify that a given value is aligned with the ADC resolution range.
  * @param RESOLUTION: ADC resolution (16, 14, 12, 10 or 8 bits).
  * @param ADC_VALUE: value checked against the resolution.     
  * @retval SET (ADC_VALUE in line with RESOLUTION) or RESET (ADC_VALUE not in line with RESOLUTION)
  */
#define IS_ADC_RANGE(RESOLUTION, ADC_VALUE)                                         \
   ((((RESOLUTION) == ADC_RESOLUTION_16B) && ((ADC_VALUE) <= ((uint32_t)0xFFFF))) || \
    (((RESOLUTION) == ADC_RESOLUTION_14B) && ((ADC_VALUE) <= ((uint32_t)0x3FFF))) || \
    (((RESOLUTION) == ADC_RESOLUTION_12B) && ((ADC_VALUE) <= ((uint32_t)0x0FFF))) || \
    (((RESOLUTION) == ADC_RESOLUTION_10B) && ((ADC_VALUE) <= ((uint32_t)0x03FF))) || \
    (((RESOLUTION) == ADC_RESOLUTION_8B)  && ((ADC_VALUE) <= ((uint32_t)0x00FF))))

/**
  * @brief Verify the length of the scheduled regular conversions group.
  * @param LENGTH: number of programmed conversions.   
  * @retval SET (LENGTH is within the maximum number of possible programmable regular conversions) or RESET (LENGTH is null or too large)
  */
#define IS_ADC_REGULAR_NB_CONV(LENGTH) (((LENGTH) >= ((uint32_t)1)) && ((LENGTH) <= ((uint32_t)16)))

/**
  * @brief Verify the number of scheduled regular conversions in discontinuous mode.
  * @param NUMBER: number of scheduled regular conversions in discontinuous mode.  
  * @retval SET (NUMBER is within the maximum number of regular conversions in discontinous mode) or RESET (NUMBER is null or too large)
  */
#define IS_ADC_REGULAR_DISCONT_NUMBER(NUMBER) (((NUMBER) >= ((uint32_t)1)) && ((NUMBER) <= ((uint32_t)8)))

/**
  * @brief Verify the ADC clock setting.
  * @param ADC_CLOCK : programmed ADC clock.
  * @retval SET (ADC_CLOCK is a valid value) or RESET (ADC_CLOCK is invalid)
  */
#define IS_ADC_CLOCKPRESCALER(ADC_CLOCK) (((ADC_CLOCK) == ADC_CLOCK_SYNC_PCLK_DIV1) || \
                                          ((ADC_CLOCK) == ADC_CLOCK_SYNC_PCLK_DIV2) || \
                                          ((ADC_CLOCK) == ADC_CLOCK_SYNC_PCLK_DIV4) || \
                                          ((ADC_CLOCK) == ADC_CLOCK_ASYNC_DIV1)     || \
                                          ((ADC_CLOCK) == ADC_CLOCK_ASYNC_DIV2)     || \
                                          ((ADC_CLOCK) == ADC_CLOCK_ASYNC_DIV4)     || \
                                          ((ADC_CLOCK) == ADC_CLOCK_ASYNC_DIV6)     || \
                                          ((ADC_CLOCK) == ADC_CLOCK_ASYNC_DIV8)     || \
                                          ((ADC_CLOCK) == ADC_CLOCK_ASYNC_DIV10)    || \
                                          ((ADC_CLOCK) == ADC_CLOCK_ASYNC_DIV12)    || \
                                          ((ADC_CLOCK) == ADC_CLOCK_ASYNC_DIV16)    || \
                                          ((ADC_CLOCK) == ADC_CLOCK_ASYNC_DIV32)    || \
                                          ((ADC_CLOCK) == ADC_CLOCK_ASYNC_DIV64)    || \
                                          ((ADC_CLOCK) == ADC_CLOCK_ASYNC_DIV128)   || \
                                          ((ADC_CLOCK) == ADC_CLOCK_ASYNC_DIV256) )

/**
  * @brief Verify the ADC resolution setting.
  * @param RESOLUTION: programmed ADC resolution.
  * @retval SET (RESOLUTION is a valid value) or RESET (RESOLUTION is invalid)
  */
#define IS_ADC_RESOLUTION(RESOLUTION) (((RESOLUTION) == ADC_RESOLUTION_16B) || \
                                       ((RESOLUTION) == ADC_RESOLUTION_14B) || \
                                       ((RESOLUTION) == ADC_RESOLUTION_12B) || \
                                       ((RESOLUTION) == ADC_RESOLUTION_10B) || \
                                       ((RESOLUTION) == ADC_RESOLUTION_8B)    )

/**
  * @brief Verify the ADC resolution setting when limited to 8 bits.
  * @param RESOLUTION: programmed ADC resolution when limited to 8 bits.
  * @retval SET (RESOLUTION is a valid value) or RESET (RESOLUTION is invalid)
  */
#define IS_ADC_RESOLUTION_8_BITS(RESOLUTION) (((RESOLUTION) == ADC_RESOLUTION_8B))

/**
  * @brief Verify the ADC scan mode.
  * @param SCAN_MODE: programmed ADC scan mode.
  * @retval SET (SCAN_MODE is valid) or RESET (SCAN_MODE is invalid)
  */
#define IS_ADC_SCAN_MODE(SCAN_MODE) (((SCAN_MODE) == ADC_SCAN_DISABLE) || \
                                     ((SCAN_MODE) == ADC_SCAN_ENABLE)    )

/**
  * @brief Verify the ADC edge trigger setting for regular group.
  * @param EDGE: programmed ADC edge trigger setting.
  * @retval SET (EDGE is a valid value) or RESET (EDGE is invalid)
  */
#define IS_ADC_EXTTRIG_EDGE(EDGE) (((EDGE) == ADC_EXTERNALTRIGCONVEDGE_NONE)         || \
                                   ((EDGE) == ADC_EXTERNALTRIGCONVEDGE_RISING)       || \
                                   ((EDGE) == ADC_EXTERNALTRIGCONVEDGE_FALLING)      || \
                                   ((EDGE) == ADC_EXTERNALTRIGCONVEDGE_RISINGFALLING)  )

/**
  * @brief Verify the ADC regular conversions external trigger.
  * @param REGTRIG: programmed ADC regular conversions external trigger.
  * @retval SET (REGTRIG is a valid value) or RESET (REGTRIG is invalid)
  */
#define IS_ADC_EXTTRIG(REGTRIG) (((REGTRIG) == ADC_EXTERNALTRIG_T1_CC1)        || \
                                 ((REGTRIG) == ADC_EXTERNALTRIG_T1_CC2)        || \
                                 ((REGTRIG) == ADC_EXTERNALTRIG_T1_CC3)        || \
                                 ((REGTRIG) == ADC_EXTERNALTRIG_T2_CC2)        || \
                                 ((REGTRIG) == ADC_EXTERNALTRIG_T3_TRGO)       || \
                                 ((REGTRIG) == ADC_EXTERNALTRIG_T4_CC4)        || \
                                 ((REGTRIG) == ADC_EXTERNALTRIG_EXT_IT11)      || \
                                 ((REGTRIG) == ADC_EXTERNALTRIG_T8_TRGO)       || \
                                 ((REGTRIG) == ADC_EXTERNALTRIG_T8_TRGO2)      || \
                                 ((REGTRIG) == ADC_EXTERNALTRIG_T1_TRGO)       || \
                                 ((REGTRIG) == ADC_EXTERNALTRIG_T1_TRGO2)      || \
                                 ((REGTRIG) == ADC_EXTERNALTRIG_T2_TRGO)       || \
                                 ((REGTRIG) == ADC_EXTERNALTRIG_T4_TRGO)       || \
                                 ((REGTRIG) == ADC_EXTERNALTRIG_T6_TRGO)       || \
                                 ((REGTRIG) == ADC_EXTERNALTRIG_T15_TRGO)      || \
                                 ((REGTRIG) == ADC_EXTERNALTRIG_T3_CC4)        || \
                                 ((REGTRIG) == ADC_EXTERNALTRIG_HR1_ADCTRG1)   || \
                                 ((REGTRIG) == ADC_EXTERNALTRIG_HR1_ADCTRG3)   || \
                                 ((REGTRIG) == ADC_EXTERNALTRIG_LPTIM1_OUT)    || \
                                 ((REGTRIG) == ADC_EXTERNALTRIG_LPTIM2_OUT)    || \
                                 ((REGTRIG) == ADC_EXTERNALTRIG_LPTIM3_OUT)    || \
                                 ((REGTRIG) == ADC_SOFTWARE_START)           )

/**
  * @brief Verify the ADC regular conversions check for converted data availability.
  * @param EOC_SELECTION: converted data availability check.
  * @retval SET (EOC_SELECTION is a valid value) or RESET (EOC_SELECTION is invalid)
  */
#define IS_ADC_EOC_SELECTION(EOC_SELECTION) (((EOC_SELECTION) == ADC_EOC_SINGLE_CONV)    || \
                                             ((EOC_SELECTION) == ADC_EOC_SEQ_CONV))

/**
  * @brief Verify the ADC regular conversions overrun handling.
  * @param OVR: ADC regular conversions overrun handling.
  * @retval SET (OVR is a valid value) or RESET (OVR is invalid)
  */
#define IS_ADC_OVERRUN(OVR) (((OVR) == ADC_OVR_DATA_PRESERVED)  || \
                             ((OVR) == ADC_OVR_DATA_OVERWRITTEN)  )

/**
  * @brief Verify the ADC conversions sampling time.
  * @param TIME: ADC conversions sampling time.
  * @retval SET (TIME is a valid value) or RESET (TIME is invalid)
  */
#define IS_ADC_SAMPLE_TIME(TIME) (((TIME) == ADC_SAMPLETIME_1CYCLE_5)    || \
                                  ((TIME) == ADC_SAMPLETIME_2CYCLES_5)   || \
                                  ((TIME) == ADC_SAMPLETIME_8CYCLES_5)  || \
                                  ((TIME) == ADC_SAMPLETIME_16CYCLES_5)  || \
                                  ((TIME) == ADC_SAMPLETIME_32CYCLES_5)  || \
                                  ((TIME) == ADC_SAMPLETIME_64CYCLES_5)  || \
                                  ((TIME) == ADC_SAMPLETIME_387CYCLES_5) || \
                                  ((TIME) == ADC_SAMPLETIME_810CYCLES_5)   )

/**
  * @brief Verify the ADC regular channel setting.
  * @param __CHANNEL__: programmed ADC regular channel.
  * @retval SET (__CHANNEL__ is valid) or RESET (__CHANNEL__ is invalid)
  */
#define IS_ADC_REGULAR_RANK(__CHANNEL__) (((__CHANNEL__) == ADC_REGULAR_RANK_1 ) || \
                                          ((__CHANNEL__) == ADC_REGULAR_RANK_2 ) || \
                                          ((__CHANNEL__) == ADC_REGULAR_RANK_3 ) || \
                                          ((__CHANNEL__) == ADC_REGULAR_RANK_4 ) || \
                                          ((__CHANNEL__) == ADC_REGULAR_RANK_5 ) || \
                                          ((__CHANNEL__) == ADC_REGULAR_RANK_6 ) || \
                                          ((__CHANNEL__) == ADC_REGULAR_RANK_7 ) || \
                                          ((__CHANNEL__) == ADC_REGULAR_RANK_8 ) || \
                                          ((__CHANNEL__) == ADC_REGULAR_RANK_9 ) || \
                                          ((__CHANNEL__) == ADC_REGULAR_RANK_10) || \
                                          ((__CHANNEL__) == ADC_REGULAR_RANK_11) || \
                                          ((__CHANNEL__) == ADC_REGULAR_RANK_12) || \
                                          ((__CHANNEL__) == ADC_REGULAR_RANK_13) || \
                                          ((__CHANNEL__) == ADC_REGULAR_RANK_14) || \
                                          ((__CHANNEL__) == ADC_REGULAR_RANK_15) || \
                                          ((__CHANNEL__) == ADC_REGULAR_RANK_16)   )

/**
  * @}
  */


/* Private constants ---------------------------------------------------------*/

/** @defgroup ADC_Private_Constants ADC Private Constants
  * @{
  */

/* Fixed timeout values for ADC conversion (including sampling time)        */
/* Maximum sampling time is 810.5 ADC clock cycle        */
/* Maximum conversion time is 16.5 + Maximum sampling time                  */
/*                       or 16.5  + 810.5 = 827 ADC clock cycles            */
/* Minimum ADC Clock frequency is 0.35 MHz                                  */
/* Maximum conversion time is                                               */
/*              827 / 0.35 MHz = 2.36 ms                                    */
#define ADC_STOP_CONVERSION_TIMEOUT     ((uint32_t) 5)



/* Delay for temperature sensor stabilization time.                         */
/* Maximum delay is 120us (refer device datasheet, parameter tSTART).       */
/* Unit: us                                                                 */
#define ADC_TEMPSENSOR_DELAY_US         ((uint32_t) 120)


/* Delay for ADC voltage regulator startup time                               */
/*  Maximum delay is 10 microseconds                                          */
/* (refer device RM, parameter Tadcvreg_stup).                                */
#define ADC_STAB_DELAY_US               ((uint32_t) 10)     /*!< ADC voltage regulator startup time */

/**
  * @}
  */

/* Exported macros -----------------------------------------------------------*/

/** @defgroup ADC_Exported_Macro ADC Exported Macros
  * @{
  */

/**
  * @brief  Reset ADC handle state
  * @param  __HANDLE__: ADC handle
  * @retval None
  */
#define __HAL_ADC_RESET_HANDLE_STATE(__HANDLE__) ((__HANDLE__)->State = HAL_ADC_STATE_RESET)

/**
  * @brief  Checks if the specified ADC interrupt source is enabled or disabled.
  * @param __HANDLE__: ADC handle
  * @param __INTERRUPT__: ADC interrupt source to check
  *          This parameter can be one of the following values:
  *            @arg ADC_IT_RDY    ADC Ready (ADRDY) interrupt source
  *            @arg ADC_IT_EOSMP  ADC End of Sampling interrupt source
  *            @arg ADC_IT_EOC    ADC End of Regular Conversion interrupt source
  *            @arg ADC_IT_EOS    ADC End of Regular sequence of Conversions interrupt source
  *            @arg ADC_IT_OVR    ADC overrun interrupt source
  *            @arg ADC_IT_JEOC   ADC End of Injected Conversion interrupt source
  *            @arg ADC_IT_JEOS   ADC End of Injected sequence of Conversions interrupt source
  *            @arg ADC_IT_AWD1   ADC Analog watchdog 1 interrupt source (main analog watchdog)
  *            @arg ADC_IT_AWD2   ADC Analog watchdog 2 interrupt source (additional analog watchdog)
  *            @arg ADC_IT_AWD3   ADC Analog watchdog 3 interrupt source (additional analog watchdog)
  *            @arg ADC_IT_JQOVF  ADC Injected Context Queue Overflow interrupt source
  * @retval State of interruption (SET or RESET)
  */
#define __HAL_ADC_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__)                     \
    (( ((__HANDLE__)->Instance->IER & (__INTERRUPT__)) == (__INTERRUPT__)      \
     )? SET : RESET                                                            \
    )

/**
  * @brief Enable an ADC interrupt.
  * @param __HANDLE__: ADC handle
  * @param __INTERRUPT__: ADC Interrupt to enable
   *          This parameter can be one of the following values:
  *            @arg ADC_IT_RDY    ADC Ready (ADRDY) interrupt source
  *            @arg ADC_IT_EOSMP  ADC End of Sampling interrupt source
  *            @arg ADC_IT_EOC    ADC End of Regular Conversion interrupt source
  *            @arg ADC_IT_EOS    ADC End of Regular sequence of Conversions interrupt source
  *            @arg ADC_IT_OVR    ADC overrun interrupt source
  *            @arg ADC_IT_JEOC   ADC End of Injected Conversion interrupt source
  *            @arg ADC_IT_JEOS   ADC End of Injected sequence of Conversions interrupt source
  *            @arg ADC_IT_AWD1   ADC Analog watchdog 1 interrupt source (main analog watchdog)
  *            @arg ADC_IT_AWD2   ADC Analog watchdog 2 interrupt source (additional analog watchdog)
  *            @arg ADC_IT_AWD3   ADC Analog watchdog 3 interrupt source (additional analog watchdog)
  *            @arg ADC_IT_JQOVF  ADC Injected Context Queue Overflow interrupt source
  * @retval None
  */
#define __HAL_ADC_ENABLE_IT(__HANDLE__, __INTERRUPT__) (((__HANDLE__)->Instance->IER) |= (__INTERRUPT__))

/**
  * @brief Disable an ADC interrupt.
  * @param __HANDLE__: ADC handle
  * @param __INTERRUPT__: ADC Interrupt to disable
  *            @arg ADC_IT_RDY    ADC Ready (ADRDY) interrupt source
  *            @arg ADC_IT_EOSMP  ADC End of Sampling interrupt source
  *            @arg ADC_IT_EOC    ADC End of Regular Conversion interrupt source
  *            @arg ADC_IT_EOS    ADC End of Regular sequence of Conversions interrupt source
  *            @arg ADC_IT_OVR    ADC overrun interrupt source
  *            @arg ADC_IT_JEOC   ADC End of Injected Conversion interrupt source
  *            @arg ADC_IT_JEOS   ADC End of Injected sequence of Conversions interrupt source
  *            @arg ADC_IT_AWD1   ADC Analog watchdog 1 interrupt source (main analog watchdog)
  *            @arg ADC_IT_AWD2   ADC Analog watchdog 2 interrupt source (additional analog watchdog)
  *            @arg ADC_IT_AWD3   ADC Analog watchdog 3 interrupt source (additional analog watchdog)
  *            @arg ADC_IT_JQOVF  ADC Injected Context Queue Overflow interrupt source
  * @retval None
  */
#define __HAL_ADC_DISABLE_IT(__HANDLE__, __INTERRUPT__) (((__HANDLE__)->Instance->IER) &= ~(__INTERRUPT__))

/**
  * @brief Checks whether the specified ADC flag is set or not.
  * @param __HANDLE__: ADC handle
  * @param __FLAG__: ADC flag to check
  *        This parameter can be one of the following values:
  *            @arg ADC_FLAG_RDY     ADC Ready (ADRDY) flag
  *            @arg ADC_FLAG_EOSMP   ADC End of Sampling flag
  *            @arg ADC_FLAG_EOC     ADC End of Regular Conversion flag
  *            @arg ADC_FLAG_EOS     ADC End of Regular sequence of Conversions flag
  *            @arg ADC_FLAG_OVR     ADC overrun flag
  *            @arg ADC_FLAG_JEOC    ADC End of Injected Conversion flag
  *            @arg ADC_FLAG_JEOS    ADC End of Injected sequence of Conversions flag
  *            @arg ADC_FLAG_AWD1    ADC Analog watchdog 1 flag (main analog watchdog)
  *            @arg ADC_FLAG_AWD2    ADC Analog watchdog 2 flag (additional analog watchdog)
  *            @arg ADC_FLAG_AWD3    ADC Analog watchdog 3 flag (additional analog watchdog)
  *            @arg ADC_FLAG_JQOVF   ADC Injected Context Queue Overflow flag
  * @retval The new state of __FLAG__ (TRUE or FALSE).
  */
#define __HAL_ADC_GET_FLAG(__HANDLE__, __FLAG__) ((((__HANDLE__)->Instance->ISR) & (__FLAG__)) == (__FLAG__))

/**
  * @brief Clear a specified ADC flag
  * @param __HANDLE__: ADC handle
  * @param __FLAG__: ADC flag to clear
  *        This parameter can be one of the following values:
  *            @arg ADC_FLAG_RDY     ADC Ready (ADRDY) flag
  *            @arg ADC_FLAG_EOSMP   ADC End of Sampling flag
  *            @arg ADC_FLAG_EOC     ADC End of Regular Conversion flag
  *            @arg ADC_FLAG_EOS     ADC End of Regular sequence of Conversions flag
  *            @arg ADC_FLAG_OVR     ADC overrun flag
  *            @arg ADC_FLAG_JEOC    ADC End of Injected Conversion flag
  *            @arg ADC_FLAG_JEOS    ADC End of Injected sequence of Conversions flag
  *            @arg ADC_FLAG_AWD1    ADC Analog watchdog 1 flag (main analog watchdog)
  *            @arg ADC_FLAG_AWD2    ADC Analog watchdog 2 flag (additional analog watchdog)
  *            @arg ADC_FLAG_AWD3    ADC Analog watchdog 3 flag (additional analog watchdog)
  *            @arg ADC_FLAG_JQOVF   ADC Injected Context Queue Overflow flag
  * @note: bit cleared bit by writing 1 (writing 0 has no effect on any bit of register ISR)
  * @retval None
  */
#define __HAL_ADC_CLEAR_FLAG(__HANDLE__, __FLAG__) (((__HANDLE__)->Instance->ISR) = (__FLAG__))

/**
  * @}
  */

/* Include ADC HAL Extended module */
#include "stm32h7xx_hal_adc_ex.h"

/* Exported functions --------------------------------------------------------*/
/** @addtogroup ADC_Exported_Functions ADC Exported Functions
  * @{
  */

/** @addtogroup ADC_Exported_Functions_Group1 Initialization and deinitialization functions
  * @brief      ADC Initialization and Configuration functions
  * @{
  */
/* Initialization and de-initialization functions  **********************************/
HAL_StatusTypeDef       HAL_ADC_Init(ADC_HandleTypeDef* hadc);
HAL_StatusTypeDef       HAL_ADC_DeInit(ADC_HandleTypeDef *hadc);
void                    HAL_ADC_MspInit(ADC_HandleTypeDef* hadc);
void                    HAL_ADC_MspDeInit(ADC_HandleTypeDef* hadc);
/**
  * @}
  */

/** @addtogroup ADC_Exported_Functions_Group2 Input and Output operation functions
  * @brief      ADC IO operation functions
  * @{
  */
/* IO operation functions  *****************************************************/

/* Blocking mode: Polling */
HAL_StatusTypeDef       HAL_ADC_Start(ADC_HandleTypeDef* hadc);
HAL_StatusTypeDef       HAL_ADC_Stop(ADC_HandleTypeDef* hadc);
HAL_StatusTypeDef       HAL_ADC_PollForConversion(ADC_HandleTypeDef* hadc, uint32_t Timeout);
HAL_StatusTypeDef       HAL_ADC_PollForEvent(ADC_HandleTypeDef* hadc, uint32_t EventType, uint32_t Timeout);

/* Non-blocking mode: Interruption */
HAL_StatusTypeDef       HAL_ADC_Start_IT(ADC_HandleTypeDef* hadc);
HAL_StatusTypeDef       HAL_ADC_Stop_IT(ADC_HandleTypeDef* hadc);

/* Non-blocking mode: DMA */
HAL_StatusTypeDef       HAL_ADC_Start_DMA(ADC_HandleTypeDef* hadc, uint32_t* pData, uint32_t Length);
HAL_StatusTypeDef       HAL_ADC_Stop_DMA(ADC_HandleTypeDef* hadc);

/* ADC retrieve conversion value intended to be used with polling or interruption */
uint32_t                HAL_ADC_GetValue(ADC_HandleTypeDef* hadc);

/* ADC IRQHandler and Callbacks used in non-blocking modes (Interruption and DMA) */
void                    HAL_ADC_IRQHandler(ADC_HandleTypeDef* hadc);
void                    HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc);
void                    HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef* hadc);
void                    HAL_ADC_LevelOutOfWindowCallback(ADC_HandleTypeDef* hadc);
void                    HAL_ADC_ErrorCallback(ADC_HandleTypeDef *hadc);
/**
  * @}
  */

/** @addtogroup ADC_Exported_Functions_Group3 Peripheral Control functions
  * @brief      Peripheral Control functions
  * @{
  */
/* Peripheral Control functions ***********************************************/
HAL_StatusTypeDef       HAL_ADC_ConfigChannel(ADC_HandleTypeDef* hadc, ADC_ChannelConfTypeDef* sConfig);
HAL_StatusTypeDef       HAL_ADC_AnalogWDGConfig(ADC_HandleTypeDef* hadc, ADC_AnalogWDGConfTypeDef* AnalogWDGConfig);

/**
  * @}
  */

/* Peripheral State functions *************************************************/
/** @addtogroup ADC_Exported_Functions_Group4
  * @{
  */
uint32_t      HAL_ADC_GetState(ADC_HandleTypeDef* hadc);
uint32_t      HAL_ADC_GetError(ADC_HandleTypeDef *hadc);

/**
  * @}
  */


/* Private functions -----------------------------------------------------------*/
/** @addtogroup ADC_Private_Functions ADC Private Functions
  * @{
  */
HAL_StatusTypeDef ADC_ConversionStop(ADC_HandleTypeDef* hadc, uint32_t ConversionGroup);
HAL_StatusTypeDef ADC_Enable(ADC_HandleTypeDef* hadc);
HAL_StatusTypeDef ADC_Disable(ADC_HandleTypeDef* hadc);
void ADC_DMAConvCplt(DMA_HandleTypeDef *hdma);
void ADC_DMAHalfConvCplt(DMA_HandleTypeDef *hdma);
void ADC_DMAError(DMA_HandleTypeDef *hdma);

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


#endif /*__STM32H7xx_ADC_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
