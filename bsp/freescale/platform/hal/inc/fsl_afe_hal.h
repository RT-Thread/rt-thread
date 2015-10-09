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

#ifndef __FSL_AFE_HAL_H__
#define __FSL_AFE_HAL_H__

#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include "fsl_device_registers.h"
#if FSL_FEATURE_SOC_AFE_COUNT

/*!
 * @addtogroup afe_hal
 * @{
 */

/******************************************************************************
 * Definitions
 *****************************************************************************/
#define CHN_TRIG_MASK(x)   (uint32_t)(1U<<(FSL_FEATURE_AFE_CHANNEL_NUMBER-1-(x)))
#define CHN(x)             (uint32_t)(x)
/*!
 * @brief AFE status return codes.
 */
typedef enum _afe_status
{
    kStatus_AFE_Success         = 0U, /*!< Success. */
    kStatus_AFE_InvalidArgument = 1U, /*!< Invalid argument existed. */
    kStatus_AFE_Failed          = 2U  /*!< Execution failed. */
} afe_status_t;

/*!
 * @brief AFE OSR modes.
 */
typedef enum _afe_dec_osr_mode
{
    kAfeDecimOsrOf64   = 0U, /*!< Decimator over sampling ratio is 64. @internal gui name="64" */
    kAfeDecimOsrOf128  = 1U, /*!< Decimator over sampling ratio is 128. @internal gui name="128" */
    kAfeDecimOsrOf256  = 2U, /*!< Decimator over sampling ratio is 256. @internal gui name="256" */
    kAfeDecimOsrOf512  = 3U, /*!< Decimator over sampling ratio is 512. @internal gui name="512" */
    kAfeDecimOsrOf1024 = 4U, /*!< Decimator over sampling ratio is 1024. @internal gui name="1024" */
    kAfeDecimOsrOf2048 = 5U, /*!< Decimator over sampling ratio is 2048. @internal gui name="2048" */
} afe_chn_osr_mode_t;

/*!
 * @brief AFE PGA modes.
 */
typedef enum _afe_pga_gain_mode
{
    kAfePgaGainBy1  = 1U, /*!< Input gained by 1. @internal gui name="1" */
    kAfePgaGainBy2  = 2U, /*!< Input gained by 2. @internal gui name="2" */
    kAfePgaGainBy4  = 3U, /*!< Input gained by 4. @internal gui name="4" */
    kAfePgaGainBy8  = 4U, /*!< Input gained by 8. @internal gui name="8" */
    kAfePgaGainBy16 = 5U, /*!< Input gained by 16. @internal gui name="16" */
    kAfePgaGainBy32 = 6U, /*!< Input gained by 32. @internal gui name="32" */
} afe_pga_gain_mode_t;

/*!
 * @brief Defines the AFE result format modes.
 */
typedef enum _afe_result_format_mode
{
    kAfeResultFormatLeft    = 0U, /*!< Left justified result format. @internal gui name="Left justified" */
    kAfeResultFormatRight   = 1U, /*!< Right justified result format. @internal gui name="Right justified" */
} afe_result_format_mode_t;

/*!
 * @brief Defines the AFE clock divider modes.
 */
typedef enum _afe_clk_divider_mode
{
    kAfeClkDividerInputOf1 = 0U,   /*!< Clock divided by 1. @internal gui name="1" */
    kAfeClkDividerInputOf2 = 1U,   /*!< Clock divided by 2. @internal gui name="2" */
    kAfeClkDividerInputOf4 = 2U,   /*!< Clock divided by 4. @internal gui name="4" */
    kAfeClkDividerInputOf8 = 3U,   /*!< Clock divided by 8. @internal gui name="8" */
    kAfeClkDividerInputOf16 = 4U,  /*!< Clock divided by 16. @internal gui name="16" */
    kAfeClkDividerInputOf32 = 5U,  /*!< Clock divided by 32. @internal gui name="32" */
    kAfeClkDividerInputOf64 = 6U,  /*!< Clock divided by 64. @internal gui name="64" */
    kAfeClkDividerInputOf128 = 7U, /*!< Clock divided by 128. @internal gui name="128" */
    kAfeClkDividerInputOf256 = 8U  /*!< Clock divided by 256. @internal gui name="256" */
} afe_clk_divider_mode_t;

/*!
 * @brief Defines the AFE clock source modes.
 */
typedef enum _afe_clk_src_mode
{
    kAfeClkSrcClk0 = 0U, /*!< Modulator clock source 0. @internal gui name="MCGIRCLK" */
    kAfeClkSrcClk1 = 1U, /*!< Modulator clock source 1. @internal gui name="SIMAFECLK" */
    kAfeClkSrcClk2 = 2U, /*!< Modulator clock source 2. @internal gui name="Quad timer channel 0" */
    kAfeClkSrcClk3 = 3U  /*!< Modulator clock source 3. @internal gui name="External clock" */
} afe_clk_src_mode_t;

/*!
 * @brief Defines the structure to configure the AFE Channel.
 */
typedef struct AfeChnSet
{
    bool hwTriggerEnable;  /*!< Enable triggering by hardware. */
    bool continuousConvEnable;  /*!< Enable continuous conversion mode. */
    bool bypassEnable; /*!< Enable bypass mode that modulator and PGA of this channel are disabled. */
    afe_pga_gain_mode_t pgaGainSel;  /*!< Select the analog gain applied to the input signal. */
    bool pgaEnable;  /*!< Enable the analog gain. */
    afe_chn_osr_mode_t decimOSR;  /*!< Select the over sampling ration. */
    bool modulatorEnable;  /*!< Enable sigma delta modulator. */
    bool decimFilterEnable;  /*!< Enable decimation filter*/
    bool decimNegedgeEnable;  /*!< Enable falling edge for decimator input*/
    bool externClockEnable;  /*!< Enable external clock for decimator*/
} afe_chn_set_t;

/*!
 * @brief Defines the structure to configure the AFE converter.
 */
typedef struct AfeConverterConfig
{
    uint8_t startupCnt;  /*!< Set startup delay of modulators. */
    afe_result_format_mode_t resultFormat;  /*!< Select the result format. */
    bool delayOk;  /*!< Confirm delay registers. */
    bool swReset;  /*!< Do a software reset. */
    bool lowPowerEnable;  /*!< Enable low power mode. */
    bool swTriggChn0;  /*!< Trigger conversion on channel 0. */
    bool swTriggChn1;  /*!< Trigger conversion on channel 1. */
    bool swTriggChn2;  /*!< Trigger conversion on channel 2. */
#ifdef FSL_FEATURE_AFE_HAS_FOUR_CHANNELS       
    bool swTriggChn3;  /*!< Trigger conversion on channel 3. */
#endif //FSL_FEATURE_AFE_HAS_FOUR_CHANNELS    
    bool masterEnable;  /*!< Enable all ADCs and filters simultaneously whose modulatorEnable and decimFilterEnable is asserted. */
} afe_converter_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif
  
/*!
 * @name AFE Channel Configurations
 * @{
 */

/*!
 * @brief Resets the channel registers into a reset state.
 *
 * This function resets the channel registers into a reset state. This state
 * is defined in the chip Reference Manual.
 *
 * @param base Register base address for the module.
 * @param chn AFE Channel.
 */  
void AFE_HAL_ChnInit(AFE_Type * base, uint32_t chn);
    
/*!
 * @brief Sets the interrupt request on conversion complete event.
 *
 * This function sets the interrupt request on conversion complete event. Once enabled, the conversion complete 
 * interrupt request is asserted for the desired channel when INTENx and COCx bits are 
 * set.
 * 
 * @param base Register base address for the AFE module.
 * @param chn AFE Channel.
 * @param enable Bool value for enabling or disabling interrupt function.
 */
static inline void AFE_HAL_SetIntEnableCmd(AFE_Type * base, uint32_t chn, bool enable)
{
    assert(chn < FSL_FEATURE_AFE_CHANNEL_NUMBER);
    AFE_BWR_DI_INTEN(base, chn, enable);
}

/*!
 * @brief Sets the DMA request on conversion complete event.
 *
 * This function sets the DMA request on conversion complete event. Once enabled, the DMA request is asserted 
 * when the INTENx and the COCx bits are set.
 * 
 * @param base Register base address for the AFE module.
 * @param chn AFE Channel.
 * @param enable Bool value for enabling or disabling DMA function.
 */
static inline void AFE_HAL_SetDmaEnableCmd(AFE_Type * base, uint32_t chn, bool enable)
{
    assert(chn < FSL_FEATURE_AFE_CHANNEL_NUMBER);
    AFE_BWR_DI_DMAEN(base, chn, enable);
}

/*!
 * @brief Sets the delay value.
 *
 * This function sets the delay value. This delay is inserted into the
 * trigger response of the decimation filters in order to provide phase compensation
 * between AFE channels. 
 * 
 * @param base Register base address for the AFE module.
 * @param chn AFE Channel.
 * @param delay Delay value.
 */
static inline void AFE_HAL_SetDelayVal(AFE_Type * base, uint32_t chn, int32_t delay)
{
    assert(chn < FSL_FEATURE_AFE_CHANNEL_NUMBER);
    AFE_BWR_DR_DLY(base, chn, delay);
}

/*!
 * @brief Gets the delay value.
 *
 * This function gets the delay value.
 * 
 * @param base Register base address for the AFE module.
 * @param chn AFE Channel.
 * @return Delay value.
 */
static inline int32_t AFE_HAL_GetDelayVal(AFE_Type * base, uint32_t chn)
{
    assert(chn < FSL_FEATURE_AFE_CHANNEL_NUMBER);
    return (int32_t)AFE_BRD_DR_DLY(base, chn);
}

/*!
 * @brief Gets the measurement result.
 *
 * This function gets the measurement result. The result can be represented in
 * left justified twos complement 32-bit or right justified twos complement 32-bit 
 * format. See the "AFE_HAL_SetResultFormatMode()" for format setting.
 * 
 * @param base Register base address for the AFE module.
 * @param chn AFE Channel.
 * @return result.
 */
static inline uint32_t AFE_HAL_GetResult(AFE_Type * base, uint32_t chn)
{
    assert(chn < FSL_FEATURE_AFE_CHANNEL_NUMBER);
    return (uint32_t)AFE_BRD_RR(base, chn);
}

/*!
 * @brief Checks whether a conversion is completed.
 *
 * This function checks whether the conversion is completed. When the result is 
 * read (see the "AFE_HAL_GetResult()"), the corresponding bit is cleared.
 * 
 * @param base Register base address for the AFE module.
 * @param chn AFE Channel.
 * @return Conversion is completed (true) or not (false).
 */
static inline bool AFE_HAL_GetConvCompleteFlag(AFE_Type * base, uint32_t chn)
{
    assert(chn < FSL_FEATURE_AFE_CHANNEL_NUMBER);
    return (bool)AFE_BRD_SR_COC(base, chn);
}

/*!
 * @brief Checks whether the selected channel has overflown.
 *
 * This function checks whether the selected channel has overflown. This function
 * returns true when new data has already arrived but previous data has not 
 * been read. The corresponding bit is cleared when the result is read
 * (see the "AFE_HAL_GetResult()").
 * 
 * @param base Register base address for the AFE module.
 * @param chn AFE Channel.
 * @return Channel is overflowed (true) or not (false).
 */
static inline bool AFE_HAL_GetOverflowFlag(AFE_Type * base, uint32_t chn)
{
    assert(chn < FSL_FEATURE_AFE_CHANNEL_NUMBER);
    return (bool)AFE_BRD_SR_OVR(base, chn);
}

/*!
 * @brief Checks whether the selected channel is ready for conversion.
 *
 * This function checks whether the selected channel is ready for conversion.
 * 
 * @param base Register base address for the AFE module.
 * @param chn AFE Channel.
 * @return Channel is ready to initiate conversions (true) or is disabled
 * or has not completed its start up period (false).
 */
static inline bool AFE_HAL_GetReadyFlag(AFE_Type * base, uint32_t chn)
{
    assert(chn < FSL_FEATURE_AFE_CHANNEL_NUMBER);
    return (bool)AFE_BRD_SR_RDY(base, chn);
}

/*@}*/

/*!
 * @name AFE Common Configurations
 * @{
 */

/*!
 * @brief Resets all registers into a reset state for the AFE module.
 *
 * This function resets all registers into a reset state for the AFE
 * module. This state is defined in the chip Reference Manual.
 *
 * @param base Register base address for the module.
 */
void AFE_HAL_Init(AFE_Type * base);

/*!
 * @brief Enables all ADCs and filters.
 *
 * This function enables all ADCs and filters. The only ADCs that have asserted are
 * SD_MOD_EN (only when AFE channel is not bypassed) and DEC_EN () are enabled 
 * by setting this bit.
 * 
 * @param base Register base address for the AFE module.
 * @param enable Bool value for enabling or disabling ADCs and filters simultaneously.
 */
static inline void AFE_HAL_SetMasterEnableCmd(AFE_Type * base, bool enable)
{
    AFE_BWR_CR_MSTR_EN(base, enable);
}

/*!
 * @brief Triggers conversion on the AFE channels.
 *
 * This function sets the software trigger conversion on the desired AFE channels. 
 * To trigger more channels simultaneously, use the red enumeration members.
 * 
 * @param base Register base address for the AFE module.
 * @param chnMask Channels which will be triggered.
 */
static inline void AFE_HAL_ChnSwTriggerCmd(AFE_Type * base, uint32_t chnMask)
{
    AFE_BWR_CR_SOFT_TRG(base, chnMask);
}

/*!
 * @brief Sets a low power mode.
 *
 * This function sets an AFE low power mode. The maximal modulator clock in low power mode
 * is bellow 1 MHz. 
 * 
 * @param base Register base address for the AFE module.
 * @param enable Bool value for enabling or disabling low power mode.
 */
static inline void AFE_HAL_SetLowPowerCmd(AFE_Type * base, bool enable)
{
    AFE_BWR_CR_LPM_EN(base, enable);
}

/*!
 * @brief Sets the software reset.
 *
 * This function sets the software reset which is used to reset all ADCs,
 * decimation filters, and clock configuration bits.
 * 
 * @param base Register base address for the AFE module.
 * @param enable If this value is true, all ADCs, PGAs and decimation filters are enabled. Otherwise, are disabled.
 */
static inline void AFE_HAL_SetSwResetCmd(AFE_Type * base, bool enable)
{
    AFE_BWR_CR_RST_B(base, enable);
}

/*!
 * @brief Asserts the delay OK.
 *
 * This function asserts the delay OK. When all delay registers are loaded, the delay OK bit should be asserted.
 * 
 * @param base Register base address for the AFE module.
 */
static inline void AFE_HAL_SetDelayOkCmd(AFE_Type * base)
{
    AFE_BWR_CR_DLY_OK(base, 1);
}

/*!
 * @brief Selects the result format mode.
 *
 * This function selects the result format mode.
 *
 * @param base Register base address for the AFE module.
 * @param mode Selection of mode enumeration. See to " afe_result_format_mode_t".
 */
static inline void AFE_HAL_SetResultFormatMode(AFE_Type * base, afe_result_format_mode_t mode)
{
    AFE_BWR_CR_RESULT_FORMAT(base, mode);
}

/*!
 * @brief Gets the conversion resolution mode.
 *
 * This function gets the conversion resolution mode.
 *
 * @param base Register base address for the AFE module.
 * @return Current conversion resolution mode.
 */
static inline afe_result_format_mode_t AFE_HAL_GetResultFormatMode(AFE_Type * base)
{
    return (afe_result_format_mode_t)AFE_BRD_CR_RESULT_FORMAT(base);
}

/*!
 * @brief Sets the start up count value.
 *
 * This function sets the start up count value. A minimum value is two. This value
 * should be greater than 20 µs. To compute the 20 µs value use, such as startDelay = (CLOCK_FREQ / DIV_factor)*20E-6
 * 
 * @param base Register base address for the AFE module.
 * @param startDelay Value for start up count.
 */
static inline void AFE_HAL_SetStartUpDelayVal(AFE_Type * base, int32_t startDelay)
{
    AFE_BWR_CR_STRTUP_CNT(base, startDelay); 
}

/*!
 * @brief Selects the clock divider mode.
 *
 * This function selects the clock divider mode.
 *
 * @param base Register base address for the AFE module.
 * @param mode Selection of mode enumeration. See to "afe_clk_divider_mode_t".
 */
static inline void AFE_HAL_SetClkDividerMode(AFE_Type * base, afe_clk_divider_mode_t mode)
{
    AFE_BWR_CKR_DIV(base, mode);
}

/*!
 * @brief Selects the input clock source for the AFE module.
 *
 * This function selects the input clock source for the AFE module.
 *
 * @param base Register base address for the AFE module.
 * @param mode Selection of mode enumeration. See to "afe_clk_src_mode_t".
 */
static inline void AFE_HAL_SetClkSourceMode(AFE_Type * base, afe_clk_src_mode_t mode)
{
    AFE_BWR_CKR_CLS(base, mode);
}

/*!
 * @brief Sets the DMA and interrupt requests for all channels.
 *
 * This function sets a DMA and Interrupt requests for all channels.
 * 
 * @param base Register base address for the AFE module.
 * @param data which will be written to register.
 */
static inline void AFE_HAL_SetDmaIntReq(AFE_Type * base, uint32_t data)
{
    AFE_WR_DI(base, data);
}

/*!
 * @brief Configures the AFE channel.
 *
 * This function configures the AFE channel.
 * 
 * @param base Register base address for the AFE module.
 * @param chn AFE Channel.
 * @param chnStructPtr Channel configuration structure.
 */
void AFE_HAL_ConfigChn(AFE_Type * base, uint32_t chn, afe_chn_set_t * chnStructPtr);

/*!
 * @brief Configures the AFE converter.
 *
 * This function configures an AFE converter.
 * 
 * @param base Register base address for the AFE module.
 * @param converterStructPtr Converter configuration structure.
 */
void AFE_HAL_ConfigConverter(AFE_Type * base, afe_converter_config_t * converterStructPtr);

/*@}*/

#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */

#endif
#endif /* __FSL_AFE_HAL_H__ */
/******************************************************************************
 * EOF
 *****************************************************************************/
