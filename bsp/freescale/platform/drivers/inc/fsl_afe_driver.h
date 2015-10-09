/*
 * Copyright (c) 2013 - 2014, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __FSL_AFE_DRIVER_H__
#define __FSL_AFE_DRIVER_H__

#include <stdint.h>
#include <stdbool.h>
#include "fsl_os_abstraction.h"
#include "fsl_afe_hal.h"
#if FSL_FEATURE_SOC_AFE_COUNT

/*!
 * @addtogroup afe_driver
 * @{
 */

/******************************************************************************
 * Definitions
 *****************************************************************************/
/*! @brief Table of base addresses for AFE instances. */
extern AFE_Type * const g_afeBase[];

/*! @brief Table to save AFE IRQ enumeration numbers defined in CMSIS header file. */
extern const IRQn_Type g_afeIrqId[];

/*!
 * @brief Defines the PGA's values.
 */
typedef enum _afe_pga_state
{ 
    kAfePgaDisable  = 0U, /*!< PGA disabled. @internal gui name="Disabled" */
    kAfePgaGain1  = 1U, /*!< Input gained by 1. @internal gui name="1" */
    kAfePgaGain2  = 2U, /*!< Input gained by 2. @internal gui name="2" */
    kAfePgaGain4  = 3U, /*!< Input gained by 4. @internal gui name="4" */
    kAfePgaGain8  = 4U, /*!< Input gained by 8. @internal gui name="8" */
    kAfePgaGain16 = 5U, /*!< Input gained by 16. @internal gui name="16" */
    kAfePgaGain32 = 6U /*!< Input gained by 32. @internal gui name="32" */
} afe_pga_state_t;

/*!
 * @brief Defines the channel's modes.
 */
typedef enum _afe_chn_mode
{
    kAfeNormal = 0, /*!< Normal channel mode. @internal gui name="Normal" */ 
    kAfeBypassExternCltPosEdge = 1,  /*!< Bypassed channel mode - external clock selected,
                                       positive edge for registering data by the decimation filter
                                       @internal gui name="External with positive edge" */ 
    kAfeBypassExternClkNegEdge = 2,  /*!< Bypassed channel mode - external clock selected,
                                       negative edge for registering data by the decimation filter
                                       @internal gui name="External with negative edge" */ 
    kAfeBypassInternClkPosEdge = 3,  /*!< Bypassed channel mode - internal clock selected,
                                       positive edge for registering data by the decimation filter
                                       @internal gui name="Internal with positive edge" */ 
    kAfeBypassInternClkNegEdge = 4   /*!< Bypassed channel mode - external clock selected,
                                       negative edge for registering data by the decimation filter
                                       @internal gui name="Internal with negative edge" */ 
} afe_chn_mode_t;

/*!
 * @brief Defines the channel's event requests.
 */
typedef enum _afe_chn_event
{
    kAfeNoneReq = 0,  /*!< None request is enabled if conversion is completed. @internal gui name="None" */
    kAfeIntReq = 1,  /*!< Interrupt request is enabled if conversion is completed. @internal gui name="Interrupt" */
    kAfeDmaReq = 2  /*!< DMA request is enabled if conversion is completed. @internal gui name="DMA" */
} afe_chn_event_t;

/*!
 * @brief Defines the structure to initialize the AFE channel.
 *
 * This structure keeps the configuration for the AFE channel.
 * @internal gui name="Channel configuration" id="afeChnCfg"
 */
typedef struct AfeChnConfig
{
    bool hwTriggerEnable;  /*!< Enable triggering by hardware. @internal gui name="Hardware trigger" id="HardwareTrigger" */
    bool continuousConvEnable;  /*!< Enable continuous conversion mode. @internal gui name="Continuous conversion" id="ContinousConv" */
    uint32_t delay;  /*!< Set the phase compensation. @internal gui name="Delay" id="ChannelDelay" range="0..2047" */
    afe_chn_mode_t chnMode; /*!< Select if channel is in bypassed mode. @internal gui name="Channel mode" id="ChannelMode" */
    afe_pga_state_t pgaGainSel;  /*!< Select the analog gain applied to the input signal. @internal gui name="PGA gain" id="PGAState" */
    afe_chn_osr_mode_t decimOSR;  /*!< Select the over sampling ration. @internal gui name="Oversampling ratio" id="DecimOSR" */
    afe_chn_event_t chnEvent;  /*!< Select DMA or interrupt function. @internal gui name="Event select" id="ChnEvent" */
} afe_chn_config_t;

/*!
 * @brief Defines the structure to initialize the AFE module.
 * 
 * This structure keeps the configuration for the AFE module.
 * @internal gui name="Common configuration" id="afeCfg"
 */
typedef struct AfeUserConfig
{
    bool lowPowerEnable;  /*!< Enable low power mode. @internal gui name="Low power mode" id="LowpowerEnable" */
    afe_result_format_mode_t resultFormat; /*!< Select the result format. @internal gui name="Result format" id="ResultFormat" */
    afe_clk_divider_mode_t clkDividerMode;  /*!< Select the clock divider ration for the modulator clock. @internal gui name="Clock divider" id="ClockDivider" */
    afe_clk_src_mode_t clkSrcMode;  /*!< Select clock source for modulator clock. @internal gui name="Clock source" id="ClockSource" */
    uint8_t startupCnt;  /*!< Select the start up delay of modulators. @internal gui name="Start up delay" id="StartupCnt" range="0..127" */
} afe_user_config_t;

/*!
 * @brief Defines the structure to configure phase delay of each AFE channel.
 *
 * This structure keeps the phase delay of each AFE channel.
 */
typedef struct AfeDelayConfig
{
    uint32_t delayChn0;  /*!< Phase compensation of channel0. */
    uint32_t delayChn1;  /*!< Phase compensation of channel1. */
    uint32_t delayChn2;  /*!< Phase compensation of channel2. */
#ifdef FSL_FEATURE_AFE_HAS_FOUR_CHANNELS        
    uint32_t delayChn3;  /*!< Phase compensation of channel3. */
#endif //FSL_FEATURE_AFE_HAS_FOUR_CHANNELS      
    
} afe_delay_config_t;


/*!
 * @brief Defines the type of event flags.
 */
typedef enum _afe_flag
{ 
    kAfeOverflowFlag = 0U, /*!< Indicates if a previous conversion result has not been read and new data has already arrived. */
    kAfeReadyFlag = 1U, /*!< Indicates whether a channel is ready to conversion. */
    kAfeConvCompleteFlag = 2U /*!< Indicates whether a conversion is complete. */
} afe_flag_t;
    
#if defined(__cplusplus)
extern "C" {
#endif

 /*******************************************************************************
 * API
 ******************************************************************************/

/*!
 * @brief Fills the user configure structure.
 *
 * This function fills the afe_user_config_t structure with default settings.
 * These setting are:
       @code
       .lowPowerEnable = false
       .resultFormat = kAfeResultFormatLeft
       .clkDividerMode = kAfeClkDividerInputOf2
       .clkSrcMode = kAfeClkSrcClk0
       .startupCnt = 125
       @endcode
 * @param userConfigPtr Pointer to structure of "afe_user_config_t".
 * @return Execution status.
 */
afe_status_t AFE_DRV_StructInitUserConfigDefault(afe_user_config_t * userConfigPtr);

/*!
 * @brief Fills the channel configuration structure.
 *
 * This function fills the afe_chn_config_t structure with default settings.
 * These setting are:
       @code
       .hwTriggerEnable = false
       .continuousConvEnable = false
       .chnMode = kAfeNormal
       .decimOSR = kAfeDecOsrOf64
       .delay = 0
       .pgaGainSel = kAfePgaGain1
       .chnEvent = kAfeNoneReq
       @endcode
 * @param chnConfigPtr Pointer to structure of "afe_chn_config_t".
 * @return Execution status.
 */
afe_status_t AFE_DRV_StructInitChnConfigDefault(afe_chn_config_t *chnConfigPtr);

/*!
 * @brief Initializes the AFE module.
 *
 * This function configures the AFE module for the configuration
 * which are shared by all channels.
 *
 * @param instance The AFE instance number.
 * @param userConfigPtr Pointer to structure of "afe_user_config_t". If startupCnt
 * parameter is less than two, this value is calculated according to equation 
 * Statup_cnt = (clk_freq/clk_div)*20e-6.
 * @return Execution status.
 */
afe_status_t AFE_DRV_Init(uint32_t instance, afe_user_config_t *userConfigPtr);

/*!
 * @brief Initializes the selected AFE channel.
 *
 * This function configures the selected AFE channel.
 *
 * @param instance The AFE instance number.
 * @param chn Channel which will be triggered.
 * @param chnConfigPtr Pointer to structure of "afe_chn_config_t".
 * @return Execution status.
 */
afe_status_t AFE_DRV_ChnInit(uint32_t instance, uint32_t chn, afe_chn_config_t *chnConfigPtr);

/*!
 * @brief Enables/disables all configured AFE channels.
 *
 * This function enables or disables all channels whose SD_MOD_EN and DEC_EN bits are asserted.
 *
 * @param instance The AFE instance number.
 * @param enable Enable (true) or disable (false) all ADCs and filters.
 */
void AFE_DRV_Enable(uint32_t instance, bool enable);

/*!
 * @brief Waits until the last conversion is complete.
 *
 * This function holds the program until the last conversion is complete.
 *
 * @param instance The AFE instance number.
 * @param chn Channel which is triggered.
 */
void AFE_DRV_WaitConvDone(uint32_t instance, uint32_t chn);

/*!
 * @brief Waits until the channel is ready for conversion.
 *
 * This function holds the program until the channel is ready for conversion.
 *
 * @param instance The AFE instance number.
 * @param chn Channel which is triggered.
 */
void AFE_DRV_WaitChnReady(uint32_t instance, uint32_t chn);

/*!
 * @brief Triggers the AFE conversion by software.
 *
 * This function triggers the AFE conversion by executing a software command. It
 * starts the conversion on selected channels if the software trigger option is
 * selected for the channels.
 *
 * @param instance The AFE instance number.
 * @param chnMask Channel(s) mask which is triggered.
 */
void AFE_DRV_SoftTriggerConv(uint32_t instance, uint32_t chnMask);

/*!
 * @brief Gets the flag for channel's events.
 *
 * This function returns the selected flag of the desired channel.
 *
 * @param instance The AFE instance number.
 * @param chn The AFE Channel.
 * @param flag Indicated event, see to "afe_flag_t".
 * @return Assertion of indicated event. 
 */
bool AFE_DRV_GetChnFlag(uint32_t instance, uint32_t chn, afe_flag_t flag);

/*!
 * @brief Reads the conversion value in a raw form.
 *
 * This function returns the conversion value of the selected channel. The returned 
 * value could be left or right adjusted according to the AFE module configuration.
 *
 * @param instance The AFE instance number.
 * @param chn The AFE Channel.
 * @return Conversion value. 
 */
uint32_t AFE_DRV_GetChnConvValRaw(uint32_t instance, uint32_t chn);

/*!
 * @brief Reads the conversion value in 2's complement form.
 *
 * This function returns the conversion value of the selected channel. The returned 
 * value is in the twos complement (right adjusted) format.
 *
 * @param instance The AFE instance number.
 * @param chn The AFE Channel.
 * @return Conversion value in 2's complement format. 
 */
int32_t AFE_DRV_GetChnConvVal(uint32_t instance, uint32_t chn);

/*!
 * @brief De-initializes the AFE module.
 *
 * When the AFE is no longer used, calling this function shuts down
 * the device to reduce power consumption.
 *
 * @param instance The AFE instance number.
 */
void AFE_DRV_Deinit(uint32_t instance);

/*!
 * @brief De-initializes the selected AFE channel.
 *
 * De-initializes the selected AFE channel configuration 
 * and interrupt.
 *
 * @param instance The AFE instance number.
 * @param chn The AFE Channel.
 */
void AFE_DRV_ChnDeinit(uint32_t instance, uint32_t chn);

/*!
 * @brief Asserts the phase delay setting.
 * 
 * This function should be called after all desired channel's 
 * delay registers are loaded. Values in channel's delay registers are active
 * after calling this function and after the conversation starts. 
 *
 * @param instance The AFE instance number.
 */
void AFE_DRV_AssertDelayOk(uint32_t instance);

/*!
 * @brief Sets phase delays.
 * 
 * This function sets the phase delays for channels. This delay is inserted before
 * the trigger response of the decimation filters. The delay is used to provide 
 * a phase compensation between AFE channels in step of prescaled modulator clock
 * periods. The DelayOk bit is asserted in this function and the 'AFE_DRV_AssertDelayOk()'
 * function doesn't have to be called. The delays for each channel are stored in a
 * 'afe_delay_config_t' structure.
 *
 * @param instance The AFE instance number.
 * @param delayConfigPtr Pointer to structure of "afe_delay_config_t".
 */
void AFE_DRV_SetPhaseDelays(uint32_t instance, afe_delay_config_t * delayConfigPtr);

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */

#endif
#endif /* __FSL_AFE_DRIVER_H__ */

/******************************************************************************
 * EOF
 *****************************************************************************/
