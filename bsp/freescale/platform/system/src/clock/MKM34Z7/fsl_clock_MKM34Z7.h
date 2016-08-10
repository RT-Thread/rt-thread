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

#if !defined(__FSL_CLOCK_KM34Z7_H__)
#define __FSL_CLOCK_KM34Z7_H__

#include <fsl_mcg_hal.h>
#include "fsl_mcg_hal_modes.h"
#include "fsl_osc_hal.h"

/*! @addtogroup clock_manager_km34z7 */
/*! @{*/

/*! @file*/

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief AFE external clock source count.  */
#define AFE_EXT_CLK_COUNT  1
/*! @brief RTC OSC Enable bit in the IRTC_GP register */
#define IRTC_OSC_ENABLE_MASK  (1U << 0U)
/*! @brief Bit in the IRTC_GP register to enable RTC OSC 2pF capacitor */
#define IRTC_OSC_SC2P_MASK    (1U << 1U)
/*! @brief Bit in the IRTC_GP register to enable RTC OSC 4pF capacitor */
#define IRTC_OSC_SC4P_MASK    (1U << 2U)
/*! @brief Bit in the IRTC_GP register to enable RTC OSC 8pF capacitor */
#define IRTC_OSC_SC8P_MASK    (1U << 3U)
/*! @brief Bit in the IRTC_GP register to enable RTC OSC 16pF capacitor */
#define IRTC_OSC_SC16P_MASK   (1U << 4U)
#define IRTC_OSC_BOOT_MASK    (1U << 7U)

/*! @brief AFE_CLK          */
extern uint32_t g_afeClkFreq[AFE_EXT_CLK_COUNT];

/*! @brief SIM configuration structure for dynamic clock setting. */
typedef struct SimConfig
{
    clock_pllfll_sel_t pllFllSel;  /*!< PLL/FLL  selection.          */
    clock_er32k_src_t  er32kSrc;   /*!< ERCLK32K source selection.   */
    uint8_t sysdiv, busdiv, flashclkmode;       /*!< CLKDIV setting. */
} sim_config_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus*/

/*!
 * @brief Sets the system clock divider setting(CLKDIVSYS).
 *
 * This function sets divide value CLKDIVSYS.
 *
 * @param sysdiv      system clock divider setting
 */
static inline void CLOCK_SYS_SetSysDiv(uint8_t sysdiv)
{
    CLOCK_HAL_SetSysDiv(SIM, sysdiv);
}

/*!
 * @brief Gets the system clock divider setting(CLKDIVSYS).
 *
 * This function gets divide value CLKDIVSYS.
 *
 * @return clock divider setting
 */
static inline uint8_t CLOCK_SYS_GetSysDiv(void)
{
    return CLOCK_HAL_GetSysDiv(SIM);
}

/*!
 * @brief Sets the bus clock divider setting(CLKDIVBUS).
 *
 * This function sets divide value CLKDIVBUS.
 *
 * @param busdiv      system clock divider setting
 */
static inline void CLOCK_SYS_SetBusDiv(uint8_t busdiv)
{
    CLOCK_HAL_SetBusDiv(SIM, busdiv);
}

/*!
 * @brief Gets the bus clock divider setting(CLKDIVBUS).
 *
 * This function gets divide value CLKDIVBUS.
 *
 * @return clock divider setting
 */
static inline uint8_t CLOCK_SYS_GetBusDiv(void)
{
    return CLOCK_HAL_GetBusDiv(SIM);
}

/*!
 * @brief Sets the flash clock mode setting(FLASHCLKMODE).
 *
 * This function sets clock mode value FLASHCLKMODE.
 *
 * @param flashclkmode      flash clock mode setting
 */
static inline void CLOCK_SYS_SetFlashClockMode(uint8_t flashclkmode)
{
    CLOCK_HAL_SetFlashClkMode(SIM, flashclkmode);
}

/*!
 * @brief Gets the flash clock divider setting(FLASHCLKMODE).
 *
 * This function gets divide value FLASHCLKMODE.
 *
 * @return flashclkmode setting
 */
static inline uint8_t CLOCK_SYS_GetFlashClkMode(void)
{
    return CLOCK_HAL_GetFlashClkMode(SIM);
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
 * @brief Gets RTC_CLK frequency.
 *
 * This function gets the frequency of RTC_CLK.
 *
 * @return Current frequency.
 */
uint32_t CLOCK_SYS_GetRtcOutFreq(void);

/*!
 * @brief Gets RTC_CLK source.
 *
 * This function sets the source of RTC_CLK.
 *
 * @param src RTC_CLK source to set.
 */
static inline void CLOCK_SYS_SetRtcOutSrc(clock_rtcout_src_t src)
{
    CLOCK_HAL_SetRtcClkSel(SIM, src);
}

/*!
 * @brief Gets RTC_CLK source.
 *
 * This function gets the source of RTC_CLK.
 * It is determined by SIM_MISC_CTL[RTCCLKSEL].
 *
 * @return Current source.
 */
static inline clock_rtcout_src_t CLOCK_SYS_GetRtcOutSrc(void)
{
    return CLOCK_HAL_GetRtcClkSel(SIM);
}

/*!
 * @brief Gets the AFE module clock frequency.
 *
 * This function gets the AFE module clock frequency.
 *
 * @param instance module device instance
 * @param afeSrc  AFE module clock source selection.
 *
 * @return Current frequency.
 */
uint32_t CLOCK_SYS_GetAfeFreq(uint32_t instance, clock_afe_src_t afeSrc);

/*!
 * @brief Gets the watch dog clock frequency.
 *
 * This function gets the watch dog clock frequency.
 *
 * @param instance module device instance
 * @param wdogSrc  watch dog clock source selection, WDOG_STCTRLH[CLKSRC].
 *
 * @return Current frequency.
 */
uint32_t CLOCK_SYS_GetWdogFreq(uint32_t instance, clock_wdog_src_t wdogSrc);

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
 * @brief Gets the Segment LCD clock frequency.
 *
 * This function gets the Segment LCD clock frequency.
 *
 * @param instance module device instance
 * @param slcdSrc  segment lcd clock source selection.
 *
 * @return Current frequency.
 */
uint32_t CLOCK_SYS_GetSlcdFreq(uint32_t instance, clock_slcd_src_t slcdSrc);

 /*!
 * @brief Gets the clock frequency for UART module.
 *
 * This function gets the clock frequency for UART module.
 * @param instance module device instance
 * @return freq    clock frequency for this module
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
 * @brief Gets the clock frequency for EWM module
 *
 * This function gets the clock frequency for EWM module.
 * @param instance module device instance
 * @return freq    clock frequency for this module
 */
static inline uint32_t CLOCK_SYS_GetEwmFreq(uint32_t instance)
{
    return CLOCK_SYS_GetBusClockFreq();
}

/*!
 * @brief Gets the clock frequency for PDB module
 *
 * This function gets the clock frequency for PDB module.
 * @param instance module device instance
 * @return freq    clock frequency for this module
 */
static inline uint32_t CLOCK_SYS_GetPdbFreq(uint32_t instance)
{
    return CLOCK_SYS_GetBusClockFreq();
}

/*!
 * @brief Gets the clock frequency for CRC module
 *
 * This function gets the clock frequency for CRC module.
 * @param instance module device instance
 * @return freq    clock frequency for this module
 */
static inline uint32_t CLOCK_SYS_GetCrcFreq(uint32_t instance)
{
    return CLOCK_SYS_GetBusClockFreq();
}

/*!
 * @brief Gets the clock frequency for SPI module
 *
 * This function gets the clock frequency for SPI module.
 * @param instance module device instance
 * @return freq    clock frequency for this module
 */
static inline uint32_t CLOCK_SYS_GetSpiFreq(uint32_t instance)
{
    return CLOCK_SYS_GetSystemClockFreq();
}

/*!
 * @brief Gets the clock frequency for I2C module
 *
 * This function gets the clock frequency for I2C module.
 * @param instance module device instance
 * @return freq    clock frequency for this module
 */
static inline uint32_t CLOCK_SYS_GetI2cFreq(uint32_t instance)
{
    return CLOCK_SYS_GetBusClockFreq();
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
 * This function gets the clock gate state for DMA module.
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
 * This function gets the clock gate state for DMAMUX module.
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
 * This function gets the clock gate state for PORT module.
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
 * This function gets the clock gate state for FTF module.
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
 * This function gets the clock gate state for ADC module.
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
 * This function gets the clock gate state for CMP module.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
static inline bool CLOCK_SYS_GetCmpGateCmd(uint32_t instance)
{
    return SIM_HAL_GetGateCmd(SIM, kSimClockGateCmp0);
}

/*!
 * @brief Enable the clock for PIT module.
 *
 * This function enables the clock for PIT module.
 * @param instance module device instance
 */
void CLOCK_SYS_EnablePitClock(uint32_t instance);

/*!
 * @brief Disable the clock for PIT module.
 *
 * This function disables the clock for PIT module.
 * @param instance module device instance
 */
void CLOCK_SYS_DisablePitClock(uint32_t instance);

/*!
 * @brief Get the the clock gate state for PIT module.
 *
 * This function gets the clock gate state for PIT module.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
bool CLOCK_SYS_GetPitGateCmd(uint32_t instance);

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
 * This function gets the clock gate state for LPTIMER module.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
static inline bool CLOCK_SYS_GetLptmrGateCmd(uint32_t instance)
{
    return SIM_HAL_GetGateCmd(SIM, kSimClockGateLptmr0);
}

/*!
 * @brief Enable the clock for RTC module.
 *
 * This function enables the clock for RTC module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_EnableRtcClock(uint32_t instance)
{
    SIM_HAL_EnableClock(SIM, kSimClockGateIRtc0);
}

/*!
 * @brief Disable the clock for RTC module.
 *
 * This function disables the clock for RTC module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_DisableRtcClock(uint32_t instance)
{
    SIM_HAL_DisableClock(SIM, kSimClockGateIRtc0);
}

/*!
 * @brief Get the the clock gate state for RTC module.
 *
 * This function gets the clock gate state for RTC module.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
static inline bool CLOCK_SYS_GetRtcGateCmd(uint32_t instance)
{
    return SIM_HAL_GetGateCmd(SIM, kSimClockGateIRtc0);
}

/*!
 * @brief Enable the clock for RTC_REG_FILE .
 *
 * This function enables the clock for RTC_REG_FILE .
 * @param instance module device instance
 */
static inline void CLOCK_SYS_EnableRtcRegFileClock(uint32_t instance)
{
    SIM_HAL_EnableClock(SIM, kSimClockGateIRtcRegFile0);
}

/*!
 * @brief Disable the clock for RTC_REG_FILE.
 *
 * This function disables the clock for RTC_REG_FILE.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_DisableRtcRegFileClock(uint32_t instance)
{
    SIM_HAL_DisableClock(SIM, kSimClockGateIRtcRegFile0);
}

/*!
 * @brief Get the the clock gate state for RTC_REG_FILE.
 *
 * This function gets the clock gate state for RTC_REG_FILE.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
static inline bool CLOCK_SYS_GetRtcRegFileGateCmd(uint32_t instance)
{
    return SIM_HAL_GetGateCmd(SIM, kSimClockGateIRtcRegFile0);
}

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
 * This function gets the clock gate state for SPI module.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
bool CLOCK_SYS_GetSpiGateCmd(uint32_t instance);

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
 * This function gets the clock gate state for UART module.
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
 * This function gets the clock gate state for I2C module.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
bool CLOCK_SYS_GetI2cGateCmd(uint32_t instance);

/*!
 * @brief Enable the clock for MMAU module.
 *
 * This function enables the clock for MMAU module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_EnableMmauClock(uint32_t instance)
{
    SIM_HAL_EnableClock(SIM, kSimClockGateMmau0);
}

/*!
 * @brief Disable the clock for MMAU module.
 *
 * This function disables the clock for MMAU module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_DisableMmauClock(uint32_t instance)
{
    SIM_HAL_DisableClock(SIM, kSimClockGateMmau0);
}

/*!
 * @brief Get the the clock gate state for MMAU module.
 *
 * This function gets the clock gate state for MMAU module.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
static inline bool CLOCK_SYS_GetMmauGateCmd(uint32_t instance)
{
    return SIM_HAL_GetGateCmd(SIM, kSimClockGateMmau0);
}

/*!
 * @brief Enable the clock for CAU module.
 *
 * This function enables the clock for CAU module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_EnableCauClock(uint32_t instance)
{
    SIM_HAL_EnableClock(SIM, kSimClockGateCau0);
}

/*!
 * @brief Disable the clock for CAU module.
 *
 * This function disables the clock for CAU module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_DisableCauClock(uint32_t instance)
{
    SIM_HAL_DisableClock(SIM, kSimClockGateCau0);
}

/*!
 * @brief Get the the clock gate state for CAU module.
 *
 * This function gets the clock gate state for CAU module.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
static inline bool CLOCK_SYS_GetCauGateCmd(uint32_t instance)
{
    return SIM_HAL_GetGateCmd(SIM, kSimClockGateCau0);
}

/*!
 * @brief Enable the clock for MPU module.
 *
 * This function enables the clock for MPU module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_EnableMpuClock(uint32_t instance)
{
    SIM_HAL_EnableClock(SIM, kSimClockGateMpu0);
}

/*!
 * @brief Disable the clock for MPU module.
 *
 * This function disables the clock for MPU module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_DisableMpuClock(uint32_t instance)
{
    SIM_HAL_DisableClock(SIM, kSimClockGateMpu0);
}

/*!
 * @brief Get the the clock gate state for MPU module.
 *
 * This function gets the clock gate state for MPU module.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
static inline bool CLOCK_SYS_GetMpuGateCmd(uint32_t instance)
{
    return SIM_HAL_GetGateCmd(SIM, kSimClockGateMpu0);
}

/*!
 * @brief Enable the clock for AFE module.
 *
 * This function enables the clock for AFE module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_EnableAfeClock(uint32_t instance)
{
    SIM_HAL_EnableClock(SIM, kSimClockGateAfe0);
}

/*!
 * @brief Disable the clock for AFE module.
 *
 * This function disables the clock for AFE module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_DisableAfeClock(uint32_t instance)
{
    SIM_HAL_DisableClock(SIM, kSimClockGateAfe0);
}

/*!
 * @brief Get the the clock gate state for AFE module.
 *
 * This function gets the clock gate state for AFE module.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
static inline bool CLOCK_SYS_GetAfeGateCmd(uint32_t instance)
{
    return SIM_HAL_GetGateCmd(SIM, kSimClockGateAfe0);
}

/*!
 * @brief Enable the clock for XBAR module.
 *
 * This function enables the clock for XBAR module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_EnableXbarClock(uint32_t instance)
{
    SIM_HAL_EnableClock(SIM, kSimClockGateXbar0);
}

/*!
 * @brief Disable the clock for XBAR module.
 *
 * This function disables the clock for XBAR module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_DisableXbarClock(uint32_t instance)
{
    SIM_HAL_DisableClock(SIM, kSimClockGateXbar0);
}

/*!
 * @brief Get the the clock gate state for XBAR module.
 *
 * This function gets the clock gate state for XBAR module.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
static inline bool CLOCK_SYS_GetXbarGateCmd(uint32_t instance)
{
    return SIM_HAL_GetGateCmd(SIM, kSimClockGateXbar0);
}

/*!
 * @brief Enable the clock for Quad Timer module.
 *
 * This function enables the clock for Quad Timer module.
 * @param instance module device instance
 */
void CLOCK_SYS_EnableQuadTmrClock(uint32_t instance);

/*!
 * @brief Disable the clock for Quad Timer module.
 *
 * This function disables the clock for Quad Timer module.
 * @param instance module device instance
 */
void CLOCK_SYS_DisableQuadTmrClock(uint32_t instance);

/*!
 * @brief Get the the clock gate state for Quad Timer module.
 *
 * This function gets the clock gate state for Quad Timer module.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
bool CLOCK_SYS_GetQuadTmrGateCmd(uint32_t instance);

/*!
 * @brief Enable the clock for SLCD module.
 *
 * This function enables the clock for SLCD module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_EnableSlcdClock(uint32_t instance)
{
    SIM_HAL_EnableClock(SIM, kSimClockGateSlcd0);
}

/*!
 * @brief Disable the clock for SLCD module.
 *
 * This function disables the clock for SLCD module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_DisableSlcdClock(uint32_t instance)
{
    SIM_HAL_DisableClock(SIM, kSimClockGateSlcd0);
}

/*!
 * @brief Get the the clock gate state for SLCD module.
 *
 * This function gets the clock gate state for SLCD module.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
static inline bool CLOCK_SYS_GetSlcdGateCmd(uint32_t instance)
{
    return SIM_HAL_GetGateCmd(SIM, kSimClockGateSlcd0);
}

/*!
 * @brief Enable the clock for EWM module.
 *
 * This function enables the clock for EWM module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_EnableEwmClock(uint32_t instance)
{
    SIM_HAL_EnableClock(SIM, kSimClockGateEwm0);
}

/*!
 * @brief Disable the clock for EWM module.
 *
 * This function disables the clock for EWM module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_DisableEwmClock(uint32_t instance)
{
    SIM_HAL_DisableClock(SIM, kSimClockGateEwm0);
}

/*!
 * @brief Get the the clock gate state for EWM module.
 *
 * This function gets the clock gate state for EWM module.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
static inline bool CLOCK_SYS_GetEwmGateCmd(uint32_t instance)
{
    return SIM_HAL_GetGateCmd(SIM, kSimClockGateEwm0);
}

/*!
 * @brief Enable the clock for RNGA module.
 *
 * This function enables the clock for RNGA module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_EnableRngaClock(uint32_t instance)
{
    SIM_HAL_EnableClock(SIM, kSimClockGateRnga0);
    SIM_HAL_DisableClock(SIM, kSimClockGateRnga0);
    SIM_HAL_EnableClock(SIM, kSimClockGateRnga0);
}

/*!
 * @brief Disable the clock for RNGA module.
 *
 * This function disables the clock for RNGA module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_DisableRngaClock(uint32_t instance)
{
    SIM_HAL_DisableClock(SIM, kSimClockGateRnga0);
}

/*!
 * @brief Get the the clock gate state for RNGA module.
 *
 * This function gets the clock gate state for RNGA module.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
static inline bool CLOCK_SYS_GetRngaGateCmd(uint32_t instance)
{
    return SIM_HAL_GetGateCmd(SIM, kSimClockGateRnga0);
}

/*!
 * @brief Enable the clock for LPUART module.
 *
 * This function enables the clock for LPUART module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_EnableLpuartClock(uint32_t instance)
{
    SIM_HAL_EnableClock(SIM, kSimClockGateLpuart0);
}

/*!
 * @brief Disable the clock for LPUART module.
 *
 * This function disables the clock for LPUART module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_DisableLpuartClock(uint32_t instance)
{
    SIM_HAL_DisableClock(SIM, kSimClockGateLpuart0);
}

/*!
 * @brief Sets the clock source for LPUART module
 *
 * This function sets the clock source for LPUART module.
 * @param instance module device instance
 * @param lpuartSrc Clock source.
 */
static inline void CLOCK_SYS_SetLpuartSrc(uint32_t instance, clock_lpuart_src_t lpuartSrc)
{
    CLOCK_HAL_SetLpuartClkSel(SIM, lpuartSrc);
}

/*!
 * @brief Gets the clock source for LPUART module
 *
 * This function gets the clock source for LPUART module.
 * @param instance module device instance
 */
static inline clock_lpuart_src_t CLOCK_SYS_GetLpuartSrc(uint32_t instance)
{
    return (clock_lpuart_src_t)CLOCK_HAL_GetLpuartClkSel(SIM);
}

/*!
 * @brief Get the the clock gate state for LPUART module.
 *
 * This function gets the clock gate state for LPUART module.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
static inline bool CLOCK_SYS_GetLpuartGateCmd(uint32_t instance)
{
    return SIM_HAL_GetGateCmd(SIM, kSimClockGateLpuart0);
}

/*!
 * @brief Gets the clock frequency for LPUART module
 *
 * This function gets the clock frequency for LPUART module.
 * @param instance module device instance
 * @return freq    clock frequency for this module
 */
uint32_t CLOCK_SYS_GetLpuartFreq(uint32_t instance);


/*!
 * @brief Get the MCGPLLCLK/MCGFLLCLK/BUS/RTC_OSC clock frequency selected
 * by PLLFLL register bit.
 *
 * This function gets the frequency of the MCGPLLCLK/MCGFLLCLK/BUS/RTC_OSC.
 *
 * @return Current clock frequency.
 */
uint32_t CLOCK_SYS_GetPllFllClockFreq(void);

/*!
 * @brief Enable the clock for CRC module.
 *
 * This function enables the clock for CRC module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_EnableCrcClock(uint32_t instance)
{
    SIM_HAL_EnableClock(SIM, kSimClockGateCrc0);
}

/*!
 * @brief Disable the clock for CRC module.
 *
 * This function disables the clock for CRC module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_DisableCrcClock(uint32_t instance)
{
    SIM_HAL_DisableClock(SIM, kSimClockGateCrc0);
}

/*!
 * @brief Get the the clock gate state for CRC module.
 *
 * This function gets the clock gate state for CRC module.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
static inline bool CLOCK_SYS_GetCrcGateCmd(uint32_t instance)
{
    return SIM_HAL_GetGateCmd(SIM, kSimClockGateCrc0);
}

/*!
 * @brief Enable the clock for PDB module.
 *
 * This function enables the clock for PDB module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_EnablePdbClock(uint32_t instance)
{
    SIM_HAL_EnableClock(SIM, kSimClockGatePdb0);
}

/*!
 * @brief Disable the clock for PDB module.
 *
 * This function disables the clock for PDB module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_DisablePdbClock(uint32_t instance)
{
    SIM_HAL_DisableClock(SIM, kSimClockGatePdb0);
}

/*!
 * @brief Get the the clock gate state for PDB module.
 *
 * This function gets the clock gate state for PDB module.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
static inline bool CLOCK_SYS_GetPdbGateCmd(uint32_t instance)
{
    return SIM_HAL_GetGateCmd(SIM, kSimClockGatePdb0);
}

/*!
 * @brief Enable the clock for VREF module.
 *
 * This function enables the clock for VREF module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_EnableVrefClock(uint32_t instance)
{
    SIM_HAL_EnableClock(SIM, kSimClockGateVref0);
}

/*!
 * @brief Disable the clock for VREF module.
 *
 * This function disables the clock for VREF module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_DisableVrefClock(uint32_t instance)
{
    SIM_HAL_DisableClock(SIM, kSimClockGateVref0);
}

/*!
 * @brief Get the the clock gate state for VREF module.
 *
 * This function gets the clock gate state for VREF module.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
static inline bool CLOCK_SYS_GetVrefGateCmd(uint32_t instance)
{
    return SIM_HAL_GetGateCmd(SIM, kSimClockGateVref0);
}

/*!
 * @brief Set the AFE external clock frequency(AFE_CLKx).
 *
 * This function sets the AFE external clock frequency (AFE_CLKx).
 *
 * @param  srcInstance External source instance.
 * @param  freq        Frequency value.
 */
static inline void CLOCK_SYS_SetAfeExternalFreq(uint32_t srcInstance, uint32_t freq)
{
    assert(srcInstance < AFE_EXT_CLK_COUNT);

    g_afeClkFreq[srcInstance] = freq;
}

#if defined(__cplusplus)
}
#endif /* __cplusplus*/

/*! @}*/

#endif /* __FSL_CLOCK_KM34Z7_H__ */
/*******************************************************************************
 * EOF
 ******************************************************************************/

