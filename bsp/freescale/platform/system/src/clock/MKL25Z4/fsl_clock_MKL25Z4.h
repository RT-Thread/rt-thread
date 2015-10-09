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

#if !defined(__FSL_CLOCK_KL25Z4_H__)
#define __FSL_CLOCK_KL25Z4_H__

#include "fsl_mcg_hal.h"
#include "fsl_mcg_hal_modes.h"
#include "fsl_osc_hal.h"

/*! @addtogroup clock_manager_kl25z4 */
/*! @{*/

/*! @file*/

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief TPM external clock source count.  */
#define TPM_EXT_CLK_COUNT  2
/*! @brief USB external clock source count.  */
#define USB_EXT_CLK_COUNT  1

/*! @brief TPM external clock frequency(TPM_CLK). */
extern uint32_t g_tpmClkFreq[TPM_EXT_CLK_COUNT];
/*! @brief USB external clock frequency(USB_CLKIN). */
extern uint32_t g_usbClkInFreq[USB_EXT_CLK_COUNT];

/*!@brief SIM configuration structure for dynamic clock setting. */
typedef struct SimConfig
{
    clock_pllfll_sel_t pllFllSel;  /*!< PLL/FLL/IRC48M selection.    */
    clock_er32k_src_t  er32kSrc;   /*!< ERCLK32K source selection.   */
    uint8_t outdiv1, outdiv4; /*!< OUTDIV setting. */
#if (defined(DOXYGEN_OUTPUT) && (DOXYGEN_OUTPUT))
} sim_config_kl25z4_t;
#else
} sim_config_t;
#endif

/*! @}*/

/*! @addtogroup clock_manager*/
/*! @{*/

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus*/

/*!
 * @brief Sets the clock out divider1 setting(OUTDIV1).
 *
 * This function sets divide value OUTDIV1.
 *
 * @param outdiv1      Outdivider1 setting
 */
static inline void CLOCK_SYS_SetOutDiv1(uint8_t outdiv1)
{
    CLOCK_HAL_SetOutDiv1(SIM, outdiv1);
}

/*!
 * @brief Gets the clock out divider1 setting(OUTDIV1).
 *
 * This function gets divide value OUTDIV1.
 *
 * @return Outdivider1 setting
 */
static inline uint8_t CLOCK_SYS_GetOutDiv1(void)
{
    return CLOCK_HAL_GetOutDiv1(SIM);
}

/*!
 * @brief Sets the clock out divider4 setting(OUTDIV4).
 *
 * This function sets divide value OUTDIV4.
 *
 * @param outdiv4      Outdivider4 setting
 */
static inline void CLOCK_SYS_SetOutDiv4(uint8_t outdiv4)
{
    CLOCK_HAL_SetOutDiv4(SIM, outdiv4);
}

/*!
 * @brief Gets the clock out divider4 setting(OUTDIV4).
 *
 * This function gets divide value OUTDIV4.
 *
 * @return Outdivider4 setting
 */
static inline uint8_t CLOCK_SYS_GetOutDiv4(void)
{
    return CLOCK_HAL_GetOutDiv4(SIM);
}

/*!
 * @brief Sets the clock out dividers setting.
 *
 * This function sets the setting for all clock out dividers at the same time.
 *
 * @param outdiv1      Outdivider1 setting
 * @param outdiv2      Outdivider2 setting
 * @param outdiv3      Outdivider3 setting
 * @param outdiv4      Outdivider4 setting
 */
static inline void CLOCK_SYS_SetOutDiv(uint8_t outdiv1, uint8_t outdiv2,
                                       uint8_t outdiv3, uint8_t outdiv4)
{
    CLOCK_HAL_SetOutDiv(SIM, outdiv1, outdiv2, outdiv3, outdiv4);
}

/*!
 * @brief Gets the clock out dividers setting.
 *
 * This function gets the setting for all clock out dividers at the same time.
 *
 * @param outdiv1      Outdivider1 setting
 * @param outdiv2      Outdivider2 setting
 * @param outdiv3      Outdivider3 setting
 * @param outdiv4      Outdivider4 setting
 */
static inline void CLOCK_SYS_GetOutDiv(uint8_t *outdiv1, uint8_t *outdiv2,
                                       uint8_t *outdiv3, uint8_t *outdiv4)
{
    CLOCK_HAL_GetOutDiv(SIM, outdiv1, outdiv2, outdiv3, outdiv4);
}

/*!
 * @brief Get the MCGPLLCLK/MCGFLLCLK/IRC48MCLK clock frequency.
 *
 * This function gets the frequency of the MCGPLLCLK/MCGFLLCLK/IRC48MCLK.
 *
 * @return Current clock frequency.
 */
uint32_t CLOCK_SYS_GetPllFllClockFreq(void);

/*!
 * @brief Set PLL/FLL clock selection.
 *
 * This function sets the selection of the high frequency clock for
 * various peripheral clocking options
 *
 * @param setting  The value to set.
 */
static inline void CLOCK_SYS_SetPllfllSel(clock_pllfll_sel_t setting)
{
    CLOCK_HAL_SetPllfllSel(SIM, setting);
}

/*!
 * @brief Get PLL/FLL clock selection.
 *
 * This function gets the selection of the high frequency clock for
 * various peripheral clocking options
 *
 * @return Current selection.
 */
static inline clock_pllfll_sel_t CLOCK_SYS_GetPllfllSel(void)
{
    return CLOCK_HAL_GetPllfllSel(SIM);
}

/*!
 * @brief Gets the MCGFFCLK clock frequency.
 *
 * This function gets the MCG fixed frequency clock (MCGFFCLK) frequency.
 *
 * @return Current clock frequency.
 */
static inline uint32_t CLOCK_SYS_GetFixedFreqClockFreq(void)
{
    return CLOCK_HAL_GetFixedFreqClk(MCG);
}

/*!
 * @brief Get internal reference clock frequency.
 *
 * This function gets the internal reference clock frequency.
 *
 * @return Current clock frequency.
 */
static inline uint32_t CLOCK_SYS_GetInternalRefClockFreq(void)
{
    return CLOCK_HAL_GetInternalRefClk(MCG);
}

/*!
 * @brief Gets the external reference 32k clock frequency.
 *
 * This function gets the external reference (ERCLK32K) clock frequency.
 *
 * @return Current frequency.
 */
uint32_t CLOCK_SYS_GetExternalRefClock32kFreq(void);

/*!
 * @brief Set the clock selection of ERCLK32K.
 *
 * This function sets the clock selection of ERCLK32K.
 *
 * @param src clock source.
 */
static inline void CLOCK_SYS_SetExternalRefClock32kSrc(clock_er32k_src_t src)
{
    CLOCK_HAL_SetExternalRefClock32kSrc(SIM, src);
}

/*!
 * @brief Get the clock selection of ERCLK32K.
 *
 * This function gets the clock selection of ERCLK32K.
 *
 * @return Current selection.
 */
static inline clock_er32k_src_t CLOCK_SYS_GetExternalRefClock32kSrc(void)
{
    return CLOCK_HAL_GetExternalRefClock32kSrc(SIM);
}

/*!
 * @brief Gets the OSC0ERCLK frequency.
 *
 * This function gets the OSC0 external reference frequency.
 *
 * @return Current frequency.
 */
uint32_t CLOCK_SYS_GetOsc0ExternalRefClockFreq(void);

 /*!
 * @brief Gets RTC input clock frequency.
 *
 * This function gets the RTC input clock frequency.
 *
 * @param instance module device instance
 *
 * @return Current frequency.
 */
uint32_t CLOCK_SYS_GetRtcFreq(uint32_t instance);

/*!
 * @brief Gets RTC_CLKOUT frequency.
 *
 * This function gets the frequency of RTC_CLKOUT.
 *
 * @return Current frequency.
 */
uint32_t CLOCK_SYS_GetRtcOutFreq(void);

/*!
 * @brief Gets RTC_CLKOUT source.
 *
 * This function gets the source of RTC_CLKOUT. It is determined by RTCCLKOUTSEL.
 *
 * @return Current source.
 */
static inline clock_rtcout_src_t CLOCK_SYS_GetRtcOutSrc(void)
{
    return CLOCK_HAL_GetRtcClkOutSel(SIM);
}

/*!
 * @brief Gets RTC_CLKOUT source.
 *
 * This function sets the source of RTC_CLKOUT.
 *
 * @param src RTC_CLKOUT source to set.
 */
static inline void CLOCK_SYS_SetRtcOutSrc(clock_rtcout_src_t src)
{
    CLOCK_HAL_SetRtcClkOutSel(SIM, src);
}

/*!
 * @brief Gets the COP clock frequency.
 *
 * This function gets the COP clock frequency.
 *
 * @param instance module device instance
 * @param copSrc  COP clock source selection.
 *
 * @return Current frequency.
 */
uint32_t CLOCK_SYS_GetCopFreq(uint32_t instance, clock_cop_src_t copSrc);
/*!
 * @brief Gets LPTMRx pre-scaler/glitch filter clock frequency.
 *
 * This function gets the LPTMRx pre-scaler/glitch filter clock frequency.
 *
 * @param instance module device instance
 * @param lptmrSrc LPTMRx clock source selection.
 *
 * @return Current frequency.
 */
uint32_t CLOCK_SYS_GetLptmrFreq(uint32_t instance, clock_lptmr_src_t lptmrSrc);

/*!
 * @brief Gets TPM clock frequency.
 *
 * This function gets the TPM clock frequency.
 *
 * @param instance module device instance
 *
 * @return Current frequency.
 */
uint32_t CLOCK_SYS_GetTpmFreq(uint32_t instance);

/*!
 * @brief Set the TPM clock source selection.
 *
 * This function sets the TPM clock source selection.
 *
 * @param instance IP instance.
 * @param tpmSrc  The value to set.
 */
static inline void CLOCK_SYS_SetTpmSrc(uint32_t instance, clock_tpm_src_t tpmSrc)
{
    CLOCK_HAL_SetTpmSrc(SIM, instance, tpmSrc);
}

/*!
 * @brief Get the TPM clock source selection.
 *
 * This function gets the TPM clock source selection.
 *
 * @param instance IP instance.
 * @return Current selection.
 */
static inline clock_tpm_src_t CLOCK_SYS_GetTpmSrc(uint32_t instance)
{
    return CLOCK_HAL_GetTpmSrc(SIM, instance);
}

/*!
 * @brief Get the TPM external clock source frequency.
 *
 * This function gets the TPM external clock source frequency.
 *
 * @param instance IP instance.
 * @return TPM external clock frequency.
 */
uint32_t CLOCK_SYS_GetTpmExternalFreq(uint32_t instance);

/*!
 * @brief Set the TPM external clock source selection.
 *
 * This function sets the TPM external clock source selection.
 *
 * @param instance IP instance.
 * @param src TPM external clock source.
 */
static inline void CLOCK_SYS_SetTpmExternalSrc(uint32_t instance, sim_tpm_clk_sel_t src)
{
    SIM_HAL_SetTpmExternalClkPinSelMode(SIM, instance, src);
}

/*!
 * @brief Set the TPM external clock source selection.
 *
 * This function sets the TPM external clock source selection.
 *
 * @param instance IP instance.
 * @return setting Current TPM external clock source.
 */
static inline sim_tpm_clk_sel_t CLOCK_SYS_GetTpmExternalSrc(uint32_t instance)
{
    return SIM_HAL_GetTpmExternalClkPinSelMode(SIM, instance);
}

/*!
 * @brief Gets the clock frequency for USB FS OTG module
 *
 * This function gets the clock frequency for USB FS OTG module.
 * @param instance module device instance
 * @return freq    clock frequency for this module
 */
 #if FSL_FEATURE_SOC_USB_COUNT
uint32_t CLOCK_SYS_GetUsbfsFreq(uint32_t instance);

/*!
 * @brief Set the selection of the clock source for the USB FS 48 MHz clock.
 *
 * This function sets the selection of the clock source for the USB FS 48 MHz clock.
 *
 * @param instance IP instance.
 * @param usbfsSrc  The value to set.
 */
static inline void CLOCK_SYS_SetUsbfsSrc(uint32_t instance, clock_usbfs_src_t usbfsSrc)
{
    CLOCK_HAL_SetUsbfsSrc(SIM, instance, usbfsSrc);
}

/*!
 * @brief Get the selection of the clock source for the USB FS 48 MHz clock.
 *
 * This function gets the selection of the clock source for the USB FS 48 MHz clock.
 *
 * @param instance IP instance.
 * @return Current selection.
 */
static inline clock_usbfs_src_t CLOCK_SYS_GetUsbfsSrc(uint32_t instance)
{
    return CLOCK_HAL_GetUsbfsSrc(SIM, instance);
}
#endif

/*!
 * @brief Gets the clock frequency for SPI module
 *
 * This function gets the clock frequency for SPI module.
 * @param instance module device instance
 * @return freq    clock frequency for this module
 */
uint32_t CLOCK_SYS_GetSpiFreq(uint32_t instance);

/*!
 * @brief Gets the clock frequency for I2C module
 *
 * This function gets the clock frequency for I2C module.
 * @param instance module device instance
 * @return freq    clock frequency for this module
 */
uint32_t CLOCK_SYS_GetI2cFreq(uint32_t instance);

 /*!
 * @brief Gets the clock frequency for LPSCI module.
 *
 * This function gets the clock frequency for LPSCI module.
 * @param instance module device instance
 * @return freq    clock frequency for this module
 */
uint32_t CLOCK_SYS_GetLpsciFreq(uint32_t instance);

/*!
 * @brief Set the LPSCI clock source selection.
 *
 * This function sets the LPSCI clock source selection.
 *
 * @param instance IP instance.
 * @param lpsciSrc  The value to set.
 */
static inline void CLOCK_SYS_SetLpsciSrc(uint32_t instance, clock_lpsci_src_t lpsciSrc)
{
    CLOCK_HAL_SetLpsciSrc(SIM, instance, lpsciSrc);
}

/*!
 * @brief Get the LPSCI clock source selection.
 *
 * This function gets the LPSCI clock source selection.
 *
 * @param instance IP instance.
 * @return Current selection.
 */
static inline clock_lpsci_src_t CLOCK_SYS_GetLpsciSrc(uint32_t  instance)
{
    return CLOCK_HAL_GetLpsciSrc(SIM, instance);
}

/*!
 * @brief Get the UART clock frequency.
 *
 * This function gets the UART clock frequency.
 *
 * @param instance IP instance.
 * @return Current frequency.
 */
uint32_t CLOCK_SYS_GetUartFreq(uint32_t instance);

/*!
 * @brief Gets ADC alternate clock frequency.
 *
 * This function gets the ADC alternate clock frequency.
 *
 * @param instance module device instance
 * @return freq    Current frequency.
 */
static inline uint32_t CLOCK_SYS_GetAdcAltFreq(uint32_t instance)
{
    return CLOCK_SYS_GetOsc0ExternalRefClockFreq();
}

/*!
 * @brief Gets the clock frequency for GPIO module
 *
 * This function gets the clock frequency for GPIO module.
 * @param instance module device instance
 * @return freq    clock frequency for this module
 */
static inline uint32_t CLOCK_SYS_GetGpioFreq(uint32_t instance)
{
    return CLOCK_SYS_GetSystemClockFreq();
}

/*!
 * @brief Gets the clock frequency for CMP module.
 *
 * This function gets the clock frequency for CMP module.
 * @param instance module device instance
 * @return freq    clock frequency for this module
 */
static inline uint32_t CLOCK_SYS_GetCmpFreq(uint32_t instance)
{
    return CLOCK_SYS_GetBusClockFreq();
}

/*!
 * @brief Gets the clock frequency for PIT module.
 *
 * This function gets the clock frequency for PIT module.
 * @param instance module device instance
 * @return freq    clock frequency for this module
 */
static inline uint32_t CLOCK_SYS_GetPitFreq(uint32_t instance)
{
    return CLOCK_SYS_GetBusClockFreq();
}

/*!
 * @brief Gets the clock frequency for FTF module. (Flash Memory)
 *
 * This function gets the clock frequency for FTF module. (Flash Memory)
 * @param instance module device instance
 * @return freq    clock frequency for this module
 */
static inline uint32_t CLOCK_SYS_GetFtfFreq(uint32_t instance)
{
    return CLOCK_SYS_GetFlashClockFreq();
}

/*!
 * @brief Enable the clock for DMA module.
 *
 * This function enables the clock for DMA module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_EnableDmaClock(uint32_t instance)
{
    SIM_HAL_EnableClock(SIM, kSimClockGateDma0);
}

/*!
 * @brief Disable the clock for DMA module.
 *
 * This function disables the clock for DMA module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_DisableDmaClock(uint32_t instance)
{
    SIM_HAL_DisableClock(SIM, kSimClockGateDma0);
}

/*!
 * @brief Get the the clock gate state for DMA module.
 *
 * This function will get the clock gate state for DMA module.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
static inline bool CLOCK_SYS_GetDmaGateCmd(uint32_t instance)
{
    return SIM_HAL_GetGateCmd(SIM, kSimClockGateDma0);
}

/*!
 * @brief Enable the clock for DMAMUX module.
 *
 * This function enables the clock for DMAMUX module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_EnableDmamuxClock(uint32_t instance)
{
    SIM_HAL_EnableClock(SIM, kSimClockGateDmamux0);
}

/*!
 * @brief Disable the clock for DMAMUX module.
 *
 * This function disables the clock for DMAMUX module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_DisableDmamuxClock(uint32_t instance)
{
    SIM_HAL_DisableClock(SIM, kSimClockGateDmamux0);
}

/*!
 * @brief Get the the clock gate state for DMAMUX module.
 *
 * This function will get the clock gate state for DMAMUX module.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
static inline bool CLOCK_SYS_GetDmamuxGateCmd(uint32_t instance)
{
    return SIM_HAL_GetGateCmd(SIM, kSimClockGateDmamux0);
}

/*!
 * @brief Enable the clock for PORT module.
 *
 * This function enables the clock for PORT module.
 * @param instance module device instance
 */
void CLOCK_SYS_EnablePortClock(uint32_t instance);

/*!
 * @brief Disable the clock for PORT module.
 *
 * This function disables the clock for PORT module.
 * @param instance module device instance
 */
void CLOCK_SYS_DisablePortClock(uint32_t instance);

/*!
 * @brief Get the the clock gate state for PORT module.
 *
 * This function will get the clock gate state for PORT module.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
bool CLOCK_SYS_GetPortGateCmd(uint32_t instance);

/*!
 * @brief Enable the clock for FTF module.
 *
 * This function enables the clock for FTF module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_EnableFtfClock(uint32_t instance)
{
    SIM_HAL_EnableClock(SIM, kSimClockGateFtf0);
}

/*!
 * @brief Disable the clock for FTF module.
 *
 * This function disables the clock for FTF module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_DisableFtfClock(uint32_t instance)
{
    SIM_HAL_DisableClock(SIM, kSimClockGateFtf0);
}

/*!
 * @brief Get the the clock gate state for FTF module.
 *
 * This function will get the clock gate state for FTF module.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
static inline bool CLOCK_SYS_GetFtfGateCmd(uint32_t instance)
{
    return SIM_HAL_GetGateCmd(SIM, kSimClockGateFtf0);
}

/*!
 * @brief Enable the clock for ADC module.
 *
 * This function enables the clock for ADC module.
 * @param instance module device instance
 */
void CLOCK_SYS_EnableAdcClock(uint32_t instance);

/*!
 * @brief Disable the clock for ADC module.
 *
 * This function disables the clock for ADC module.
 * @param instance module device instance
 */
void CLOCK_SYS_DisableAdcClock(uint32_t instance);

/*!
 * @brief Get the the clock gate state for ADC module.
 *
 * This function will get the clock gate state for ADC module.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
bool CLOCK_SYS_GetAdcGateCmd(uint32_t instance);

/*!
 * @brief Enable the clock for CMP module.
 *
 * This function enables the clock for CMP module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_EnableCmpClock(uint32_t instance)
{
    SIM_HAL_EnableClock(SIM, kSimClockGateCmp0);
}

/*!
 * @brief Disable the clock for CMP module.
 *
 * This function disables the clock for CMP module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_DisableCmpClock(uint32_t instance)
{
    SIM_HAL_DisableClock(SIM, kSimClockGateCmp0);
}

/*!
 * @brief Get the the clock gate state for CMP module.
 *
 * This function will get the clock gate state for CMP module.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
static inline bool CLOCK_SYS_GetCmpGateCmd(uint32_t instance)
{
    return SIM_HAL_GetGateCmd(SIM, kSimClockGateCmp0);
}

/*!
 * @brief Enable the clock for DAC module.
 *
 * This function enables the clock for DAC module.
 * @param instance module device instance
 */
#if FSL_FEATURE_SOC_DAC_COUNT
void CLOCK_SYS_EnableDacClock(uint32_t instance);

/*!
 * @brief Disable the clock for DAC module.
 *
 * This function disables the clock for DAC module.
 * @param instance module device instance
 */
void CLOCK_SYS_DisableDacClock(uint32_t instance);

/*!
 * @brief Get the the clock gate state for DAC module.
 *
 * This function will get the clock gate state for DAC module.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
bool CLOCK_SYS_GetDacGateCmd(uint32_t instance);
#endif

/*!
 * @brief Enable the clock for TPM module.
 *
 * This function enables the clock for TPM module.
 * @param instance module device instance
 */
void CLOCK_SYS_EnableTpmClock(uint32_t instance);

/*!
 * @brief Disable the clock for TPM module.
 *
 * This function disables the clock for TPM module.
 * @param instance module device instance
 */
void CLOCK_SYS_DisableTpmClock(uint32_t instance);

/*!
 * @brief Get the the clock gate state for TPM module.
 *
 * This function will get the clock gate state for TPM module.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
bool CLOCK_SYS_GetTpmGateCmd(uint32_t instance);

/*!
 * @brief Enable the clock for PIT module.
 *
 * This function enables the clock for PIT module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_EnablePitClock(uint32_t instance)
{
    SIM_HAL_EnableClock(SIM, kSimClockGatePit0);
}

/*!
 * @brief Disable the clock for PIT module.
 *
 * This function disables the clock for PIT module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_DisablePitClock(uint32_t instance)
{
    SIM_HAL_DisableClock(SIM, kSimClockGatePit0);
}

/*!
 * @brief Get the the clock gate state for PIT module.
 *
 * This function will get the clock gate state for PIT module.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
static inline bool CLOCK_SYS_GetPitGateCmd(uint32_t instance)
{
    return SIM_HAL_GetGateCmd(SIM, kSimClockGatePit0);
}

/*!
 * @brief Enable the clock for LPTIMER module.
 *
 * This function enables the clock for LPTIMER module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_EnableLptmrClock(uint32_t instance)
{
    SIM_HAL_EnableClock(SIM, kSimClockGateLptmr0);
}

/*!
 * @brief Disable the clock for LPTIMER module.
 *
 * This function disables the clock for LPTIMER module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_DisableLptmrClock(uint32_t instance)
{
    SIM_HAL_DisableClock(SIM, kSimClockGateLptmr0);
}

/*!
 * @brief Get the the clock gate state for LPTIMER module.
 *
 * This function will get the clock gate state for LPTIMER module.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
static inline bool CLOCK_SYS_GetLptmrGateCmd(uint32_t instance)
{
    return SIM_HAL_GetGateCmd(SIM, kSimClockGateLptmr0);
}

/*!
 * @brief Enable the clock for TSI module.
 *
 * This function enables the clock for TSI module.
 * @param instance module device instance
 */
#if FSL_FEATURE_SOC_TSI_COUNT
static inline void CLOCK_SYS_EnableTsiClock(uint32_t instance)
{
    SIM_HAL_EnableClock(SIM, kSimClockGateTsi0);
}

/*!
 * @brief Disable the clock for TSI module.
 *
 * This function disables the clock for TSI module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_DisableTsiClock(uint32_t instance)
{
    SIM_HAL_DisableClock(SIM, kSimClockGateTsi0);
}

/*!
 * @brief Get the the clock gate state for TSI module.
 *
 * This function will get the clock gate state for TSI module.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
static inline bool CLOCK_SYS_GetTsiGateCmd(uint32_t instance)
{
    return SIM_HAL_GetGateCmd(SIM, kSimClockGateTsi0);
}
#endif

/*!
 * @brief Enable the clock for RTC module.
 *
 * This function enables the clock for RTC module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_EnableRtcClock(uint32_t instance)
{
    SIM_HAL_EnableClock(SIM, kSimClockGateRtc0);
}

/*!
 * @brief Disable the clock for RTC module.
 *
 * This function disables the clock for RTC module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_DisableRtcClock(uint32_t instance)
{
    SIM_HAL_DisableClock(SIM, kSimClockGateRtc0);
}

/*!
 * @brief Get the the clock gate state for RTC module.
 *
 * This function will get the clock gate state for RTC module.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
static inline bool CLOCK_SYS_GetRtcGateCmd(uint32_t instance)
{
    return SIM_HAL_GetGateCmd(SIM, kSimClockGateRtc0);
}

/*!
 * @brief Enable the clock for USBFS module.
 *
 * This function enables the clock for USBFS module.
 * @param instance module device instance
 */
 #if FSL_FEATURE_SOC_USB_COUNT
static inline void CLOCK_SYS_EnableUsbfsClock(uint32_t instance)
{
    SIM_HAL_EnableClock(SIM, kSimClockGateUsbfs0);
}

/*!
 * @brief Disable the clock for USBFS module.
 *
 * This function disables the clock for USBFS module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_DisableUsbfsClock(uint32_t instance)
{
    SIM_HAL_DisableClock(SIM, kSimClockGateUsbfs0);
}

/*!
 * @brief Get the the clock gate state for USB module.
 *
 * This function will get the clock gate state for USB module.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
static inline bool CLOCK_SYS_GetUsbfsGateCmd(uint32_t instance)
{
    return SIM_HAL_GetGateCmd(SIM, kSimClockGateUsbfs0);
}
#endif

/*!
 * @brief Enable the clock for SPI module.
 *
 * This function enables the clock for SPI module.
 * @param instance module device instance
 */
void CLOCK_SYS_EnableSpiClock(uint32_t instance);

/*!
 * @brief Disable the clock for SPI module.
 *
 * This function disables the clock for SPI module.
 * @param instance module device instance
 */
void CLOCK_SYS_DisableSpiClock(uint32_t instance);

/*!
 * @brief Get the the clock gate state for SPI module.
 *
 * This function will get the clock gate state for SPI module.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
bool CLOCK_SYS_GetSpiGateCmd(uint32_t instance);

/*!
 * @brief Enable the clock for LPSCI module.
 *
 * This function enables the clock for LPSCI module.
 * @param instance module device instance
 */
void CLOCK_SYS_EnableLpsciClock(uint32_t instance);

/*!
 * @brief Disable the clock for LPSCI module.
 *
 * This function disables the clock for LPSCI module.
 * @param instance module device instance
 */
void CLOCK_SYS_DisableLpsciClock(uint32_t instance);

/*!
 * @brief Get the the clock gate state for LPSCI module.
 *
 * This function will get the clock gate state for LPSCI module.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
bool CLOCK_SYS_GetLpsciGateCmd(uint32_t instance);

/*!
 * @brief Enable the clock for UART module.
 *
 * This function enables the clock for UART module.
 * @param instance module device instance
 */
void CLOCK_SYS_EnableUartClock(uint32_t instance);

/*!
 * @brief Disable the clock for UART module.
 *
 * This function disables the clock for UART module.
 * @param instance module device instance
 */
void CLOCK_SYS_DisableUartClock(uint32_t instance);

/*!
 * @brief Get the the clock gate state for UART module.
 *
 * This function will get the clock gate state for UART module.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
bool CLOCK_SYS_GetUartGateCmd(uint32_t instance);

/*!
 * @brief Enable the clock for I2C module.
 *
 * This function enables the clock for I2C module.
 * @param instance module device instance
 */
void CLOCK_SYS_EnableI2cClock(uint32_t instance);

/*!
 * @brief Disable the clock for I2C module.
 *
 * This function disables the clock for I2C module.
 * @param instance module device instance
 */
void CLOCK_SYS_DisableI2cClock(uint32_t instance);

/*!
 * @brief Get the the clock gate state for I2C module.
 *
 * This function will get the clock gate state for I2C module.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
bool CLOCK_SYS_GetI2cGateCmd(uint32_t instance);

/*!
 * @brief Set the USB external clock frequency(USB_CLKIN).
 *
 * This function sets the USB external clock frequency (USB_CLKIN).
 *
 * @param  srcInstance External source instance.
 * @param  freq        Frequcney value.
 */
static inline void CLOCK_SYS_SetUsbExternalFreq(uint32_t srcInstance, uint32_t freq)
{
    assert(srcInstance < USB_EXT_CLK_COUNT);

    g_usbClkInFreq[srcInstance] = freq;
}

/*!
 * @brief Set the TPM external clock frequency(TPM_CLKx).
 *
 * This function sets the TPM external clock frequency (TPM_CLKx).
 *
 * @param  srcInstance External source instance.
 * @param  freq        Frequcney value.
 */
static inline void CLOCK_SYS_SetTpmExternalFreq(uint32_t srcInstance, uint32_t freq)
{
    assert(srcInstance < TPM_EXT_CLK_COUNT);

    g_tpmClkFreq[srcInstance] = freq;
}

#if defined(__cplusplus)
}
#endif /* __cplusplus*/

/*! @}*/

#endif /* __FSL_CLOCK_KL25Z4_H__ */
/*******************************************************************************
 * EOF
 ******************************************************************************/

