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

#if !defined(__FSL_CLOCK_KV30F12810_H__)
#define __FSL_CLOCK_KV30F12810_H__

#include "fsl_mcg_hal.h"
#include "fsl_mcg_hal_modes.h"
#include "fsl_osc_hal.h"

/*! @addtogroup clock_manager_kv30f12810 */
/*! @{*/

/*! @file*/

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief FTM external clock source count.  */
#define FTM_EXT_CLK_COUNT  2

/*! @brief FTM external clock frequency(FTM_CLK).  */
extern uint32_t g_ftmClkFreq[FTM_EXT_CLK_COUNT];

/*!@brief SIM configuration structure for dynamic clock setting. */
typedef struct SimConfig
{
    clock_pllfll_sel_t pllFllSel;  /*!< PLL/FLL/IRC48M selection.    */
    clock_er32k_src_t  er32kSrc;   /*!< ERCLK32K source selection.   */
    uint8_t outdiv1, outdiv2, outdiv3, outdiv4; /*!< OUTDIV setting. */
#if (defined(DOXYGEN_OUTPUT) && (DOXYGEN_OUTPUT))
} sim_config_kv30f12810_t;
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
 * @brief Sets the clock out divider2 setting(OUTDIV2).
 *
 * This function sets divide value OUTDIV2.
 *
 * @param outdiv2      Outdivider2 setting
 */
static inline void CLOCK_SYS_SetOutDiv2(uint8_t outdiv2)
{
    CLOCK_HAL_SetOutDiv2(SIM, outdiv2);
}

/*!
 * @brief Gets the clock out divider2 setting(OUTDIV2).
 *
 * This function gets divide value OUTDIV2.
 *
 * @return Outdivider2 setting
 */
static inline uint8_t CLOCK_SYS_GetOutDiv2(void)
{
    return CLOCK_HAL_GetOutDiv2(SIM);
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
 * @brief Gets the OSC0ERCLK_UNDIV frequency.
 *
 * This function gets the undivided OSC0 external reference frequency.
 *
 * @return Current frequency.
 */
uint32_t CLOCK_SYS_GetOsc0ExternalRefClockUndivFreq(void);

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
 * @brief Gets the debug trace clock source.
 *
 * This function gets the debug trace clock source.
 * @param instance module device instance
 *
 * @return Current source.
 */
static inline clock_trace_src_t CLOCK_SYS_GetTraceSrc(uint32_t instance)
{
    return CLOCK_HAL_GetTraceClkSrc(SIM);
}

/*!
 * @brief Sets the debug trace clock source.
 *
 * This function sets the debug trace clock source.
 * @param instance module device instance.
 * @param src   debug trace clock source.
 */
static inline void CLOCK_SYS_SetTraceSrc(uint32_t instance, clock_trace_src_t src)
{
    CLOCK_HAL_SetTraceClkSrc(SIM, src);
}

/*!
 * @brief Gets the debug trace clock frequency.
 *
 * This function gets the debug trace clock frequency.
 * @param instance module device instance
 *
 * @return Current frequency.
 */
uint32_t CLOCK_SYS_GetTraceFreq(uint32_t instance);

/*!
 * @brief Gets PORTx digital input filter clock frequency.
 *
 * This function gets the PORTx digital input filter clock frequency.
 * @param instance module device instance.
 * @param src      PORTx source selection.
 *
 * @return Current frequency.
 */
uint32_t CLOCK_SYS_GetPortFilterFreq(uint32_t instance, clock_port_filter_src_t src);

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
 * @brief Gets the clock frequency for EWM module.
 *
 * This function gets the clock frequency for EWM module.
 * @param instance module device instance
 * @return freq    clock frequency for this module
 */
static inline uint32_t CLOCK_SYS_GetEwmFreq(uint32_t instance)
{
    return CLOCK_SYS_GetLpoClockFreq();
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
 * @brief Gets the clock frequency for CRC module.
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
 * @brief Gets the clock frequency for VREF module.
 *
 * This function gets the clock frequency for VREF module.
 * @param instance module device instance
 * @return freq    clock frequency for this module
 */
static inline uint32_t CLOCK_SYS_GetVrefFreq(uint32_t instance)
{
    return CLOCK_SYS_GetBusClockFreq();
}

/*!
 * @brief Gets the clock frequency for PDB module.
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
 * @brief Gets the clock frequency for SPI module
 *
 * This function gets the clock frequency for SPI module.
 * @param instance module device instance
 * @return freq    clock frequency for this module
 */
static inline uint32_t CLOCK_SYS_GetSpiFreq(uint32_t instance)
{
    return CLOCK_SYS_GetBusClockFreq();
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
 * @brief Gets ADC alternate 2 clock frequency.
 *
 * This function gets the ADC alternate 2 clock frequency (ALTCLK2).
 *
 * @param instance module device instance
 * @return freq    Current frequency.
 */
static inline uint32_t CLOCK_SYS_GetAdcAlt2Freq(uint32_t instance)
{
    return CPU_INTERNAL_IRC_48M;
}

/*!
 * @brief Gets FTM fixed frequency clock frequency.
 *
 * This function gets the FTM fixed frequency clock frequency.
 *
 * @param instance module device instance
 * @return freq    Current frequency.
 */
static inline uint32_t CLOCK_SYS_GetFtmFixedFreq(uint32_t instance)
{
    return CLOCK_SYS_GetFixedFreqClockFreq();
}

/*!
 * @brief Gets FTM's system clock frequency.
 *
 * This function gets the FTM's system clock frequency.
 *
 * @param instance module device instance
 * @return Current frequency.
 */
static inline uint32_t CLOCK_SYS_GetFtmSystemClockFreq(uint32_t instance)
{
    return CLOCK_SYS_GetBusClockFreq();
}

/*!
 * @brief Gets FTM external clock frequency.
 *
 * This function gets the FTM external clock frequency.
 *
 * @param instance module device instance
 * @return freq    Current frequency.
 */
uint32_t CLOCK_SYS_GetFtmExternalFreq(uint32_t instance);

/*!
 * @brief Gets FTM external clock source.
 *
 * This function gets the FTM external clock source.
 *
 * @param instance module device instance.
 * @return Ftm external clock source.
 */
static inline sim_ftm_clk_sel_t CLOCK_SYS_GetFtmExternalSrc(uint32_t instance)
{
    return SIM_HAL_GetFtmExternalClkPinMode(SIM, instance);
}

/*!
 * @brief Sets FTM external clock source.
 *
 * This function sets the FTM external clock source.
 *
 * @param instance module device instance.
 * @param ftmSrc FTM clock source setting.
 */
static inline void CLOCK_SYS_SetFtmExternalSrc(uint32_t instance,
                                               sim_ftm_clk_sel_t ftmSrc)
{
    SIM_HAL_SetFtmExternalClkPinMode(SIM, instance, ftmSrc);
}

/*!
 * @brief Gets the clock frequency for UART module
 *
 * This function gets the clock frequency for UART module.
 * @param instance module device instance
 * @return freq    clock frequency for this module
 */
uint32_t CLOCK_SYS_GetUartFreq(uint32_t instance);

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
 * This function will get the clock gate state for EWM module.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
static inline bool CLOCK_SYS_GetEwmGateCmd(uint32_t instance)
{
    return SIM_HAL_GetGateCmd(SIM, kSimClockGateEwm0);
}

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
 * This function will get the clock gate state for CRC module.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
static inline bool CLOCK_SYS_GetCrcGateCmd(uint32_t instance)
{
    return SIM_HAL_GetGateCmd(SIM, kSimClockGateCrc0);
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
    SIM_HAL_EnableClock(SIM, kSimClockGateCmp);
}

/*!
 * @brief Disable the clock for CMP module.
 *
 * This function disables the clock for CMP module.
 * @param instance module device instance
 */
static inline void CLOCK_SYS_DisableCmpClock(uint32_t instance)
{
    SIM_HAL_DisableClock(SIM, kSimClockGateCmp);
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
    return SIM_HAL_GetGateCmd(SIM, kSimClockGateCmp);
}

/*!
 * @brief Enable the clock for DAC module.
 *
 * This function enables the clock for DAC module.
 * @param instance module device instance
 */
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
 * This function will get the clock gate state for VREF module.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
static inline bool CLOCK_SYS_GetVrefGateCmd(uint32_t instance)
{
    return SIM_HAL_GetGateCmd(SIM, kSimClockGateVref0);
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
 * This function will get the clock gate state for PDB module.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
static inline bool CLOCK_SYS_GetPdbGateCmd(uint32_t instance)
{
    return SIM_HAL_GetGateCmd(SIM, kSimClockGatePdb0);
}

/*!
 * @brief Enable the clock for FTM module.
 *
 * This function enables the clock for FTM module.
 * @param instance module device instance
 */
void CLOCK_SYS_EnableFtmClock(uint32_t instance);

/*!
 * @brief Disable the clock for FTM module.
 *
 * This function disables the clock for FTM module.
 * @param instance module device instance
 */
void CLOCK_SYS_DisableFtmClock(uint32_t instance);

/*!
 * @brief Get the the clock gate state for FTM module.
 *
 * This function will get the clock gate state for FTM module.
 * @param instance module device instance
 * @return state true - ungated(Enabled), false - gated (Disabled)
 */
bool CLOCK_SYS_GetFtmGateCmd(uint32_t instance);

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
 * @brief Set the FTM external clock frequency(FTM_CLKx).
 *
 * This function sets the FTM external clock frequency (FTM_CLKx).
 *
 * @param  srcInstance External source instance.
 * @param  freq        Frequcney value.
 */
static inline void CLOCK_SYS_SetFtmExternalFreq(uint32_t srcInstance, uint32_t freq)
{
    assert(srcInstance < FTM_EXT_CLK_COUNT);

    g_ftmClkFreq[srcInstance] = freq;
}

#if defined(__cplusplus)
}
#endif /* __cplusplus*/

/*! @}*/

#endif /* __FSL_CLOCK_KV30F12810_H__ */
/*******************************************************************************
 * EOF
 ******************************************************************************/

