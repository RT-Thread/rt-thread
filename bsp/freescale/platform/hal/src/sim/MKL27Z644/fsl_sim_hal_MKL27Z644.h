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

#if !defined(__FSL_SIM_HAL_MKL27Z644_H__)
#define __FSL_SIM_HAL_MKL27Z644_H__

/*!
 * @addtogroup sim_hal_kl27z644
 * @{
 */
/*! @file*/

/*******************************************************************************
* Definitions
******************************************************************************/
/*! @brief COP clock source selection.*/
typedef enum _clock_cop_src {
    kClockCopSrcLpoClk,							 /*!< LPO clock 1K HZ.*/
    kClockCopSrcMcgIrClk, 						 /*!< MCG IRC Clock   */
    kClockCopSrcOsc0erClk, 						 /*!< OSCER Clock	  */
    kClockCopSrcBusClk							 /*!< BUS clock 	  */
#if (defined(DOXYGEN_OUTPUT) && (DOXYGEN_OUTPUT))
}clock_cop_src_kl27z644_t;
#else
}clock_cop_src_t;
#endif

/*! @brief SIM external reference clock source select (OSC32KSEL). */
typedef enum _clock_er32k_src
{
    kClockEr32kSrcOsc0 = 0U, /*!< OSC0 clock (OSC032KCLK).  */
    kClockEr32kSrcRtc  = 2U, /*!< RTC 32k clock .           */
    kClockEr32kSrcLpo  = 3U, /*!< LPO clock.                */
#if (defined(DOXYGEN_OUTPUT) && (DOXYGEN_OUTPUT))
} clock_er32k_src_kl27z644_t;
#else
} clock_er32k_src_t;
#endif

/*! @brief SIM external reference clock output pin select (OSC32KOUT). */
typedef enum _clock_osc32kout_sel
{
    kClockOsc32koutNone,   /*!< ERCLK32K is not output. */
    kClockOsc32koutPte0,   /*!< ERCLK32K output on PTE0 */
#if (defined(DOXYGEN_OUTPUT) && (DOXYGEN_OUTPUT))
} clock_osc32kout_sel_kl27z644_t;
#else
} clock_osc32kout_sel_t;
#endif

/*! @brief SIM LPUART clock source */
typedef enum _clock_lpuart_src
{
    kClockLpuartSrcNone,          /*!< disabled */
    kClockLpuartSrcIrc48M,	      /*!< IRC48M */
    kClockLpuartSrcOsc0erClk,	  /*!< OSCER clock */
    kClockLpuartSrcMcgIrClk 	  /*!< MCGIR clock */
#if (defined(DOXYGEN_OUTPUT) && (DOXYGEN_OUTPUT))
} clock_lpuart_src_kl27z644_t;
#else
} clock_lpuart_src_t;
#endif

/*! @brief SIM TPM clock source */
typedef enum _clock_tpm_src
{
    kClockTpmSrcNone,         /*!< disabled */
    kClockTpmSrcIrc48M,	      /*!< IRC48M/MCGPCLK */
    kClockTpmSrcOsc0erClk,	  /*!< OSCER clock */
    kClockTpmSrcMcgIrClk 	  /*!< MCGIR clock */
#if (defined(DOXYGEN_OUTPUT) && (DOXYGEN_OUTPUT))
} clock_tpm_src_kl27z644_t;
#else
} clock_tpm_src_t;
#endif

/*! @brief SIM USB FS clock source */
typedef enum _clock_usbfs_src
{
    kClockUsbfsSrcExt,       /*!< External bypass clock (USB_CLKIN)  */
    kClockUsbfsSrcIrc48M,    /*!< IRC48/MCGPCLK                      */
#if (defined(DOXYGEN_OUTPUT) && (DOXYGEN_OUTPUT))
} clock_usbfs_src_kl27z644_t;
#else
} clock_usbfs_src_t;
#endif

/*! @brief FLEXIO clock source. */
typedef enum _clock_flexio_src
{
    kClockFlexioSrcNone,      /*!< Clock disabled. */
    kClockFlexioSrcIrc48M,    /*!< MCGPCLK/IRC48M. */
    kClockFlexioSrcOsc0erClk, /*!< OSCERCLK.       */
    kClockFlexioSrcMcgIrClk,  /*!< MCGIRCLK.       */
#if (defined(DOXYGEN_OUTPUT) && (DOXYGEN_OUTPUT))
} clock_flexio_src_kl27z644_t;
#else
} clock_flexio_src_t;
#endif

/*! @brief LPTMR clock source select */
typedef enum _clock_lptmr_src_t
{
    kClockLptmrSrcMcgIrClk,        /*!< MCG out clock  */
    kClockLptmrSrcLpoClk,          /*!< LPO clock      */
    kClockLptmrSrcEr32kClk,        /*!< ERCLK32K clock */
    kClockLptmrSrcOsc0erClk,       /*!< OSCERCLK clock */
#if (defined(DOXYGEN_OUTPUT) && (DOXYGEN_OUTPUT))
} clock_lptmr_src_kl27z644_t;
#else
} clock_lptmr_src_t;
#endif

/*! @brief SIM CLKOUT_SEL clock source select */
typedef enum _clock_clkout_src
{
    kClockClkoutSelFlashClk  = 2U,  /*!< Flash clock    */
    kClockClkoutSelLpoClk    = 3U,  /*!< LPO clock      */
    kClockClkoutSelMcgIrClk  = 4U,  /*!< MCG out clock  */
    kClockClkoutSelOsc0erClk = 6U,  /*!< OSCER clock */
    kClockClkoutSelIrc48M    = 7U   /*!< IRC48M clock */
#if (defined(DOXYGEN_OUTPUT) && (DOXYGEN_OUTPUT))
} clock_clkout_src_kl27z644_t;
#else
} clock_clkout_src_t;
#endif

/*! @brief SIM RTCCLKOUTSEL clock source select */
typedef enum _clock_rtcout_src
{
    kClockRtcoutSrc1Hz,        /*!< 1Hz clock      */
    kClockRtcoutSrcOsc0erClk,  /*!< OSCER clock */
#if (defined(DOXYGEN_OUTPUT) && (DOXYGEN_OUTPUT))
} clock_rtcout_src_kl27z644_t;
#else
} clock_rtcout_src_t;
#endif

/*! @brief SIM ADCx pre-trigger select */
typedef enum _sim_adc_pretrg_sel
{
    kSimAdcPretrgselA,              /*!< Pre-trigger A selected for ADCx */
    kSimAdcPretrgselB               /*!< Pre-trigger B selected for ADCx */
#if (defined(DOXYGEN_OUTPUT) && (DOXYGEN_OUTPUT))
} sim_adc_pretrg_sel_kl27z644_t;
#else
} sim_adc_pretrg_sel_t;
#endif

/*! @brief SIM ADCx trigger select */
typedef enum _sim_adc_trg_sel
{
    kSimAdcTrgselExt        = 0U,         /*!< External trigger         */
    kSimAdcTrgSelComp0      = 1U,         /*!< CMP0 output              */
	kSimAdcTrgSelPit0       = 4U,         /*!< PIT trigger 0            */
    kSimAdcTrgSelPit1       = 5U,         /*!< PIT trigger 1            */
    kSimAdcTrgSelTpm0       = 8U,         /*!< TPM0 overflow            */
    kSimAdcTrgSelTpm1       = 9U,         /*!< TPM1 overflow            */
    kSimAdcTrgSelTpm2       = 10U,        /*!< TPM2 overflow            */
    kSimAdcTrgSelRtcAlarm	= 12U,        /*!< RTC alarm                */
    kSimAdcTrgSelRtcSec		= 13U,        /*!< RTC seconds              */
    kSimAdcTrgSelLptimer	= 14U,        /*!< Low-power timer trigger  */
#if (defined(DOXYGEN_OUTPUT) && (DOXYGEN_OUTPUT))
} sim_adc_trg_sel_kl27z644_t;
#else
} sim_adc_trg_sel_t;
#endif

/*! @brief LPUART receive data source. */
typedef enum _sim_lpuart_rxsrc
{
    kSimLpuartRxsrcPin,               /*!< LPUARTx_RX Pin */
    kSimLpuartRxsrcCmp0,              /*!< CMP0           */
#if (defined(DOXYGEN_OUTPUT) && (DOXYGEN_OUTPUT))
} sim_lpuart_rxsrc_kl27z644_t;
#else
} sim_lpuart_rxsrc_t;
#endif

/*! @brief LPUART transmit data source. */
typedef enum _sim_lpuart_txsrc
{
    kSimLpuartTxsrcPin,    /*!< UARTx_TX Pin */
    kSimLpuartTxsrcTpm1,   /*!< UARTx_TX pin modulated with TPM1 channel 0 output */
    kSimLpuartTxsrcTpm2,   /*!< UARTx_TX pin modulated with TPM2 channel 0 output */
#if (defined(DOXYGEN_OUTPUT) && (DOXYGEN_OUTPUT))
} sim_lpuart_txsrc_kl27z644_t;
#else
} sim_lpuart_txsrc_t;
#endif

/*! @brief SIM Timer/PWM external clock select */
typedef enum _sim_tpm_clk_sel
{
    kSimTpmClkSel0,                 /*!< Timer/PWM TPM_CLKIN0 pin. */
    kSimTpmClkSel1                  /*!< Timer/PWM TPM_CLKIN1 pin. */
#if (defined(DOXYGEN_OUTPUT) && (DOXYGEN_OUTPUT))
} sim_tpm_clk_sel_kl27z644_t;
#else
} sim_tpm_clk_sel_t;
#endif

/*! @brief SIM Timer/PWM x channel y input capture source select */
typedef enum _sim_tpm_ch_src
{
    kSimTpmChSrc0,   /*!< Channel y input capture source uses 0. */
    kSimTpmChSrc1,   /*!< Channel y input capture source uses 1. */
    kSimTpmChSrc2,   /*!< Channel y input capture source uses 2. */
    kSimTpmChSrc3,   /*!< Channel y input capture source uses 3. */
#if (defined(DOXYGEN_OUTPUT) && (DOXYGEN_OUTPUT))
} sim_tpm_ch_src_kl27z644_t;
#else
} sim_tpm_ch_src_t;
#endif

/*! @brief SIM SCGC bit index. */
#define FSL_SIM_SCGC_BIT(SCGCx, n) (((SCGCx-1U)<<5U) + n)

/*! @brief Clock gate name used for SIM_HAL_EnableClock/SIM_HAL_DisableClock. */
typedef enum _sim_clock_gate_name
{
    kSimClockGateI2c0      = FSL_SIM_SCGC_BIT(4U, 6U),
    kSimClockGateI2c1      = FSL_SIM_SCGC_BIT(4U, 7U),
    kSimClockGateUart2     = FSL_SIM_SCGC_BIT(4U, 12U),
    kSimClockGateUsbfs0    = FSL_SIM_SCGC_BIT(4U, 18U),
    kSimClockGateCmp0      = FSL_SIM_SCGC_BIT(4U, 19U),
    kSimClockGateVref0     = FSL_SIM_SCGC_BIT(4U, 20U),
    kSimClockGateSpi0      = FSL_SIM_SCGC_BIT(4U, 22U),
    kSimClockGateSpi1      = FSL_SIM_SCGC_BIT(4U, 23U),
    kSimClockGateLptmr0    = FSL_SIM_SCGC_BIT(5U, 0U),
    kSimClockGatePortA     = FSL_SIM_SCGC_BIT(5U, 9U),
    kSimClockGatePortB     = FSL_SIM_SCGC_BIT(5U, 10U),
    kSimClockGatePortC     = FSL_SIM_SCGC_BIT(5U, 11U),
    kSimClockGatePortD     = FSL_SIM_SCGC_BIT(5U, 12U),
    kSimClockGatePortE     = FSL_SIM_SCGC_BIT(5U, 13U),
    kSimClockGateLpuart0   = FSL_SIM_SCGC_BIT(5U, 20U),
    kSimClockGateLpuart1   = FSL_SIM_SCGC_BIT(5U, 21U),
    kSimClockGateFlexio0   = FSL_SIM_SCGC_BIT(5U, 31U),
    kSimClockGateFtf0      = FSL_SIM_SCGC_BIT(6U, 0U),
    kSimClockGateDmamux0   = FSL_SIM_SCGC_BIT(6U, 1U),
    kSimClockGateCrc0      = FSL_SIM_SCGC_BIT(6U, 18U),
    kSimClockGatePit0      = FSL_SIM_SCGC_BIT(6U, 23U),
    kSimClockGateTpm0      = FSL_SIM_SCGC_BIT(6U, 24U),
    kSimClockGateTpm1      = FSL_SIM_SCGC_BIT(6U, 25U),
    kSimClockGateTpm2      = FSL_SIM_SCGC_BIT(6U, 26U),
    kSimClockGateAdc0      = FSL_SIM_SCGC_BIT(6U, 27U),
    kSimClockGateRtc0      = FSL_SIM_SCGC_BIT(6U, 29U),
    kSimClockGateDma0      = FSL_SIM_SCGC_BIT(7U, 8U),
#if (defined(DOXYGEN_OUTPUT) && (DOXYGEN_OUTPUT))
} sim_clock_gate_name_kl27z644_t;
#else
} sim_clock_gate_name_t;
#endif

/*@}*/

/*******************************************************************************
* API
******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus*/

/*!
 * @addtogroup sim_hal
 * @{
 */

/*!
 * @brief Enable the clock for specific module.
 *
 * This function enables the clock for specific module.
 *
 * @param base Base address for current SIM instance.
 * @param name Name of the module to enable.
 */
static inline void SIM_HAL_EnableClock(SIM_Type * base, sim_clock_gate_name_t name)
{
    SIM_BWR_SCGC_BIT(base, name, 1U);
}

/*!
* @brief Disable the clock for specific module.
*
* This function disables the clock for specific module.
*
* @param base Base address for current SIM instance.
* @param name Name of the module to disable.
*/
static inline void SIM_HAL_DisableClock(SIM_Type * base, sim_clock_gate_name_t name)
{
    SIM_BWR_SCGC_BIT(base, name, 0U);
}

/*!
* @brief Get the the clock gate state for specific module.
*
* This function will get the clock gate state for specific module.
*
* @param base Base address for current SIM instance.
* @param name Name of the module to get.
* @return state true - ungated(Enabled), false - gated (Disabled)
*/
static inline bool SIM_HAL_GetGateCmd(SIM_Type * base, sim_clock_gate_name_t name)
{
    return (bool)SIM_BRD_SCGC_BIT(base, name);
}

/*!
* @brief Set the clock selection of LPUART.
*
* This function sets the clock selection of LPUART.
*
* @param base Base address for current SIM instance.
* @param instance LPUART instance.
* @param setting  The value to set.
*/
void CLOCK_HAL_SetLpuartSrc(SIM_Type * base,
                            uint32_t instance,
                            clock_lpuart_src_t setting);

/*!
* @brief Get the clock selection of LPUART.
*
* This function gets the clock selection of LPUART.
*
* @param base Base address for current SIM instance.
* @param instance LPUART instance.
* @return Current selection.
*/
clock_lpuart_src_t CLOCK_HAL_GetLpuartSrc(SIM_Type * base,
                                          uint32_t instance);

/*!
* @brief Set the clock selection of TPM.
*
* This function sets the clock selection of TPM.
*
* @param base Base address for current SIM instance.
* @param instance IP instance.
* @param setting  The value to set.
*/
static inline void CLOCK_HAL_SetTpmSrc(SIM_Type * base,
                                       uint32_t instance,
                                       clock_tpm_src_t setting)
{
    SIM_BWR_SOPT2_TPMSRC(base, setting);
}

/*!
* @brief Get the clock selection of TPM.
*
* This function gets the clock selection of TPM.
*
* @param base Base address for current SIM instance.
* @param instance IP instance.
* @return Current selection.
*/
static inline clock_tpm_src_t CLOCK_HAL_GetTpmSrc(SIM_Type * base,
                                                  uint32_t instance)
{
    return (clock_tpm_src_t)SIM_BRD_SOPT2_TPMSRC(base);
}

/*!
 * @brief Set the selection of the clock source for the USB FS 48 MHz clock.
 *
 * This function sets the selection of the clock source for the USB FS 48 MHz clock.
 *
 * @param base Base address for current SIM instance.
 * @param instance IP instance.
 * @param setting  The value to set.
 */
static inline void CLOCK_HAL_SetUsbfsSrc(SIM_Type * base,
                                         uint32_t instance,
                                         clock_usbfs_src_t setting)
{
    SIM_BWR_SOPT2_USBSRC(base, setting);
}

/*!
 * @brief Get the selection of the clock source for the USB FS 48 MHz clock.
 *
 * This function gets the selection of the clock source for the USB FS 48 MHz clock.
 *
 * @param base Base address for current SIM instance.
 * @param instance IP instance.
 * @return Current selection.
 */
static inline clock_usbfs_src_t CLOCK_HAL_GetUsbfsSrc(SIM_Type * base,
                                                      uint32_t instance)
{
    return (clock_usbfs_src_t)SIM_BRD_SOPT2_USBSRC(base);
}

/*!
 * @brief Select the clock source for FLEXIO.
 *
 * This function selects the clock source for FLEXIO.
 *
 * @param base Base address for current SIM instance.
 * @param instance IP instance.
 * @param setting  The value to set.
 */
static inline void CLOCK_HAL_SetFlexioSrc(SIM_Type * base,
                                          uint32_t instance,
                                          clock_flexio_src_t setting)
{
    SIM_BWR_SOPT2_FLEXIOSRC(base, setting);
}

/*!
 * @brief Get the clock source of FLEXIO.
 *
 * This function gets the clock source of FLEXIO.
 *
 * @param base Base address for current SIM instance.
 * @param instance IP instance.
 * @return Current selection.
 */
static inline clock_flexio_src_t CLOCK_HAL_GetFlexioSrc(SIM_Type * base,
                                                        uint32_t instance)
{
    return (clock_flexio_src_t)SIM_BRD_SOPT2_FLEXIOSRC(base);
}

/*!
* @brief Set the clock ERCLK32K output on selected pin.
*
* This function sets ERCLK32K output on selected pin.
*
* @param base Base address for current SIM instance.
* @param setting  The value to set.
*/
static inline void CLOCK_HAL_SetOsc32kOutSel(SIM_Type * base,
                                             clock_osc32kout_sel_t setting)
{
    SIM_BWR_SOPT1_OSC32KOUT(base, setting);
}

/*!
* @brief Get output status of ERCLK32K.
*
* This function gets the output status of ERCLK32K.
*
* @param base Base address for current SIM instance.
* @return Current selection.
*/
static inline clock_osc32kout_sel_t CLOCK_HAL_GetOsc32kOutSel(SIM_Type * base)
{
    return (clock_osc32kout_sel_t)SIM_BRD_SOPT1_OSC32KOUT(base);
}


/*!
* @brief Set the clock selection of ERCLK32K.
*
* This function sets the clock selection of ERCLK32K.
*
* @param base Base address for current SIM instance.
* @param setting  The value to set.
*/
static inline void CLOCK_HAL_SetExternalRefClock32kSrc(SIM_Type * base,
                                                       clock_er32k_src_t setting)
{
    SIM_BWR_SOPT1_OSC32KSEL(base, setting);
}

/*!
* @brief Get the clock selection of ERCLK32K.
*
* This function gets the clock selection of ERCLK32K.
*
* @param base Base address for current SIM instance.
* @return Current selection.
*/
static inline clock_er32k_src_t CLOCK_HAL_GetExternalRefClock32kSrc(SIM_Type * base)
{
    return (clock_er32k_src_t)SIM_BRD_SOPT1_OSC32KSEL(base);
}

/*!
* @brief Set CLKOUTSEL selection.
*
* This function sets the selection of the clock to output on the CLKOUT pin.
*
* @param base Base address for current SIM instance.
* @param setting  The value to set.
*/
static inline void CLOCK_HAL_SetClkOutSel(SIM_Type * base, clock_clkout_src_t setting)
{
    SIM_BWR_SOPT2_CLKOUTSEL(base, setting);
}

/*!
* @brief Get CLKOUTSEL selection.
*
* This function gets the selection of the clock to output on the CLKOUT pin.
*
* @param base Base address for current SIM instance.
* @return Current selection.
*/
static inline clock_clkout_src_t CLOCK_HAL_GetClkOutSel(SIM_Type * base)
{
    return (clock_clkout_src_t)SIM_BRD_SOPT2_CLKOUTSEL(base);
}

/*!
* @brief Set RTCCLKOUTSEL selection.
*
* This function sets the selection of the clock to output on the RTC_CLKOUT pin.
*
* @param base Base address for current SIM instance.
* @param setting  The value to set.
*/
static inline void CLOCK_HAL_SetRtcClkOutSel(SIM_Type * base,
                                             clock_rtcout_src_t setting)
{
    SIM_BWR_SOPT2_RTCCLKOUTSEL(base, setting);
}

/*!
* @brief Get RTCCLKOUTSEL selection.
*
* This function gets the selection of the clock to output on the RTC_CLKOUT pin.
*
* @param base Base address for current SIM instance.
* @return Current selection.
*/
static inline clock_rtcout_src_t CLOCK_HAL_GetRtcClkOutSel(SIM_Type * base)
{
    return (clock_rtcout_src_t)SIM_BRD_SOPT2_RTCCLKOUTSEL(base);
}


/*!
* @brief Set the clock selection of COP.
*
* This function sets the clock selection of COP.
*
* @param base Base address for current SIM instance.
* @param setting  The value to set.
*/
static inline void CLOCK_HAL_SetCopSrc(SIM_Type * base,
                                       clock_cop_src_t setting)
{
    SIM_BWR_COPC_COPCLKSEL(base, setting);
}

/*!
* @brief Get the clock selection of COP.
*
* This function gets the clock selection of COP.
*
* @param base Base address for current SIM instance.
* @return Current selection.
*/
static inline clock_cop_src_t CLOCK_HAL_GetCopSrc(SIM_Type * base)
{
    return (clock_cop_src_t)SIM_BRD_COPC_COPCLKSEL(base);
}


/*!
* @brief Set OUTDIV1.
*
* This function sets divide value OUTDIV1.
*
* @param base Base address for current SIM instance.
* @param setting  The value to set.
*/
static inline void CLOCK_HAL_SetOutDiv1(SIM_Type * base, uint8_t setting)
{
    SIM_BWR_CLKDIV1_OUTDIV1(base, setting);
}

/*!
* @brief Get OUTDIV1.
*
* This function gets divide value OUTDIV1.
*
* @param base Base address for current SIM instance.
* @return Current divide value.
*/
static inline uint8_t CLOCK_HAL_GetOutDiv1(SIM_Type * base)
{
    return SIM_BRD_CLKDIV1_OUTDIV1(base);
}

/*!
* @brief Set OUTDIV4.
*
* This function sets divide value OUTDIV4.
*
* @param base Base address for current SIM instance.
* @param setting  The value to set.
*/
static inline void CLOCK_HAL_SetOutDiv4(SIM_Type * base, uint8_t setting)
{
    SIM_BWR_CLKDIV1_OUTDIV4(base, setting);
}

/*!
* @brief Get OUTDIV4.
*
* This function gets divide value OUTDIV4.
*
* @param base Base address for current SIM instance.
* @return Current divide value.
*/
static inline uint8_t CLOCK_HAL_GetOutDiv4(SIM_Type * base)
{
    return SIM_BRD_CLKDIV1_OUTDIV4(base);
}

/*!
 * @brief Sets the clock out dividers setting.
 *
 * This function sets the setting for all clock out dividers at the same time.
 *
 * @param base     Base address for current SIM instance.
 * @param outdiv1      Outdivider1 setting
 * @param outdiv2      Outdivider2 setting
 * @param outdiv3      Outdivider3 setting
 * @param outdiv4      Outdivider4 setting
 */
void CLOCK_HAL_SetOutDiv(SIM_Type * base,
                         uint8_t outdiv1,
                         uint8_t outdiv2,
                         uint8_t outdiv3,
                         uint8_t outdiv4);

/*!
 * @brief Gets the clock out dividers setting.
 *
 * This function gets the setting for all clock out dividers at the same time.
 *
 * @param base     Base address for current SIM instance.
 * @param outdiv1      Outdivider1 setting
 * @param outdiv2      Outdivider2 setting
 * @param outdiv3      Outdivider3 setting
 * @param outdiv4      Outdivider4 setting
 */
void CLOCK_HAL_GetOutDiv(SIM_Type * base,
                         uint8_t *outdiv1,
                         uint8_t *outdiv2,
                         uint8_t *outdiv3,
                         uint8_t *outdiv4);

/*!
* @brief Sets the ADCx alternate trigger enable setting.
*
* This function enables/disables the alternative conversion triggers for ADCx.
*
* @param base     Base address for current SIM instance.
* @param instance     device instance.
* @param enable Enable alternative conversion triggers for ADCx
*               - true:  Select alternative conversion trigger.
*               - false: Select PDB trigger.
*/
static inline void SIM_HAL_SetAdcAlternativeTriggerCmd(SIM_Type * base,
                                                       uint32_t instance,
                                                       bool enable)
{
    SIM_BWR_SOPT7_ADC0ALTTRGEN(base, enable ? 1 : 0);
    
}    
/*!
* @brief Gets the ADCx alternate trigger enable setting.
*
* This function gets the ADCx alternate trigger enable setting.
*
* @param base     Base address for current SIM instance.
* @param instance     device instance.
* @return enabled True if  ADCx alternate trigger is enabled
*/

static inline bool SIM_HAL_GetAdcAlternativeTriggerCmd(SIM_Type * base, uint32_t instance)
{
    bool retValue = false;
    
    retValue = SIM_BRD_SOPT7_ADC0ALTTRGEN(base);
    
    return retValue;
}


/*!
* @brief Sets the ADCx pre-trigger select setting.
*
* This function selects the ADCx pre-trigger source when the alternative
* triggers are enabled through ADCxALTTRGEN.
*
* @param base     Base address for current SIM instance.
* @param instance     device instance.
* @param select pre-trigger select setting for ADCx
*/
static inline void SIM_HAL_SetAdcPreTriggerMode(SIM_Type * base,
                                                uint32_t instance,
                                                sim_adc_pretrg_sel_t select)
{
    SIM_BWR_SOPT7_ADC0PRETRGSEL(base, select);
    
}
/*!
* @brief Gets the ADCx pre-trigger select setting.
*
* This function  gets the ADCx pre-trigger select setting.
*
* @param base     Base address for current SIM instance.
* @param instance     device instance.
* @return select ADCx pre-trigger select setting
*/
static inline sim_adc_pretrg_sel_t SIM_HAL_GetAdcPreTriggerMode(SIM_Type * base,
                                                                uint32_t instance)
{
    sim_adc_pretrg_sel_t retValue = (sim_adc_pretrg_sel_t)0;
    
    retValue = (sim_adc_pretrg_sel_t)SIM_BRD_SOPT7_ADC0PRETRGSEL(base);
    
    return retValue;
}

/*!
* @brief Sets the ADCx trigger select setting.
*
* This function  selects the ADCx trigger source when alternative triggers
* are enabled through ADCxALTTRGEN.
*
* @param base     Base address for current SIM instance.
* @param instance     device instance.
* @param select       trigger select setting for ADCx
*/
static inline void SIM_HAL_SetAdcTriggerMode(SIM_Type * base,
                                             uint32_t instance,
                                             sim_adc_trg_sel_t select)
{
    SIM_BWR_SOPT7_ADC0TRGSEL(base, select);
    
}

/*!
* @brief Gets the ADCx trigger select setting.
*
* This function  gets the ADCx trigger select setting.
*
* @param base     Base address for current SIM instance.
* @param instance     device instance.
* @return ADCx trigger select setting
*/
static inline sim_adc_trg_sel_t SIM_HAL_GetAdcTriggerMode(SIM_Type * base, uint32_t instance)
{
    sim_adc_trg_sel_t retValue = (sim_adc_trg_sel_t)0;
    
    retValue = (sim_adc_trg_sel_t)SIM_BRD_SOPT7_ADC0TRGSEL(base);
    
    return retValue;
}

/*!
* @brief Sets the ADCx trigger select setting in one function.
*
* This function sets ADC alternate trigger, pre-trigger mode and trigger mode.
*
* @param base     Base address for current SIM instance.
* @param instance     device instance.
* @param altTrigEn    Alternative trigger enable or not.
* @param preTrigSel   Pre-trigger mode.
* @param trigSel      Trigger mode.
*/
void SIM_HAL_SetAdcTriggerModeOneStep(SIM_Type * base,
                                      uint32_t instance,
                                      bool    altTrigEn,
                                      sim_adc_pretrg_sel_t preTrigSel,
                                      sim_adc_trg_sel_t trigSel);

/*!
* @brief Sets the LPUARTx receive data source select setting.
*
* This function  selects the source for the LPUARTx receive data.
*
* @param base Register base address of SIM.
* @param instance LPUART instance.
* @param select the source for the LPUARTx receive data
*/
void SIM_HAL_SetLpuartRxSrcMode(SIM_Type * base,
                                uint32_t instance,
                                sim_lpuart_rxsrc_t select);

/*!
* @brief Gets the LPUARTx receive data source select setting.
*
* This function  gets the LPUARTx receive data source select setting.
*
* @param base Register base address of SIM.
* @param instance LPUART instance.
*
* @return select UARTx receive data source select setting
*/
sim_lpuart_rxsrc_t SIM_HAL_GetLpuartRxSrcMode(SIM_Type * base, uint32_t instance);

/*!
* @brief Sets the LPUARTx transmit data source select setting.
*
* This function  selects the source for the LPUARTx transmit data.
*
* @param base Register base address of SIM.
* @param instance LPUART instance.
* @param select the source for the UARTx transmit data.
*/
void SIM_HAL_SetLpuartTxSrcMode(SIM_Type * base,
                                uint32_t instance,
                                sim_lpuart_txsrc_t select);

/*!
* @brief Gets the LPUARTx transmit data source select setting.
*
* This function  gets the LPUARTx transmit data source select setting.
*
* @param base Register base address of SIM.
* @param instance LPUART instance.
* @return select UARTx transmit data source select setting.
*/
sim_lpuart_txsrc_t SIM_HAL_GetLpuartTxSrcMode(SIM_Type * base, uint32_t instance);

/*!
* @brief Sets the LPUARTx Open Drain Enable setting.
*
* This function  enables/disables the LPUARTx Open Drain.
*
* @param base Register base address of SIM.
* @param instance LPUART instance.
* @param enable Enable/disable LPUARTx Open Drain
*				 - True: Enable LPUARTx Open Drain
*				 - False: Disable LPUARTx Open Drain
*/
void SIM_HAL_SetLpuartOpenDrainCmd(SIM_Type * base, uint32_t instance, bool enable);

/*!
* @brief Gets the LPUARTx Open Drain Enable setting.
*
* This function  gets the LPUARTx Open Drain Enable setting.
*
* @param base Register base address of SIM.
* @param instance LPUART instance.
* @return enabled True if LPUARTx Open Drain is enabled.
*/
bool SIM_HAL_GetLpuartOpenDrainCmd(SIM_Type * base, uint32_t instance);

/*!
* @brief Sets the UARTx Open Drain Enable setting.
*
* This function  enables/disables the UARTx Open Drain.
*
* @param base Register base address of SIM.
* @param instance UART instance.
* @param enable Enable/disable UARTx Open Drain
*				 - True: Enable UARTx Open Drain
*				 - False: Disable UARTx Open Drain
*/
static inline void SIM_HAL_SetUartOpenDrainCmd(SIM_Type * base,
                                               uint32_t instance,
                                               bool enable)
{
    // Only support UART2
    assert (2 == instance);
    SIM_BWR_SOPT5_UART2ODE(base, enable ? 1 : 0);
}

/*!
* @brief Gets the UARTx Open Drain Enable setting.
*
* This function  gets the UARTx Open Drain Enable setting.
*
* @param base Register base address of SIM.
* @param instance UART instance.
* @return enabled True if UARTx Open Drain is enabled.
*/
static inline bool SIM_HAL_GetUartOpenDrainCmd(SIM_Type * base,
                                               uint32_t instance)
{
    // Only support UART2
    assert (2 == instance);
    return (bool)SIM_BRD_SOPT5_UART2ODE(base);
}

/*!
* @brief Sets the Timer/PWM x channel y input capture source select setting.
*
* This function  selects the Timer/PWM x channel y input capture source.
*
* @param base     Base address for current SIM instance.
* @param instance     device instance.
* @param channel      TPM channel y
* @param select Timer/PWM x channel y input capture source
*/
void SIM_HAL_SetTpmChSrcMode(SIM_Type * base,
                             uint32_t instance,
                             uint8_t channel,
                             sim_tpm_ch_src_t select);

/*!
* @brief Gets the Timer/PWM x channel y input capture source select setting.
*
* This function  gets the Timer/PWM x channel y input capture source select setting.
*
* @param base     Base address for current SIM instance.
* @param instance     device instance.
* @param channel      Tpm channel y
* @return select Timer/PWM x channel y input capture source select setting
*/
sim_tpm_ch_src_t SIM_HAL_GetTpmChSrcMode(SIM_Type * base,
                                         uint32_t instance,
                                         uint8_t channel);

/*!
* @brief Gets the Kinetis Sub-Family ID in the System Device ID register (SIM_SDID).
*
* This function  gets the Kinetis Sub-Family ID in System Device ID register.
*
* @param base     Base address for current SIM instance.
* @return id Kinetis Sub-Family ID
*/
static inline uint32_t SIM_HAL_GetSubFamilyId(SIM_Type * base)
{
    return SIM_BRD_SDID_SUBFAMID(base);
}

/*!
* @brief Gets the Kinetis SeriesID in the System Device ID register (SIM_SDID).
*
* This function  gets the Kinetis Series ID in System Device ID register.
*
* @param base     Base address for current SIM instance.
* @return id Kinetis Series ID
*/
static inline uint32_t SIM_HAL_GetSeriesId(SIM_Type * base)
{
    return SIM_BRD_SDID_SERIESID(base);
}

/*!
* @brief Gets the Kinetis Fam ID in System Device ID register (SIM_SDID).
*
* This function  gets the Kinetis Fam ID in System Device ID register.
*
* @param base     Base address for current SIM instance.
* @return id Kinetis Fam ID
*/
static inline uint32_t SIM_HAL_GetFamId(SIM_Type * base)
{
    return SIM_BRD_SDID_FAMID(base);
}

/*!
* @brief Gets the Kinetis Pincount ID in System Device ID register (SIM_SDID).
*
* This function  gets the Kinetis Pincount ID in System Device ID register.
*
* @param base     Base address for current SIM instance.
* @return id Kinetis Pincount ID
*/
static inline uint32_t SIM_HAL_GetPinCntId(SIM_Type * base)
{
    return SIM_BRD_SDID_PINID(base);
}

/*!
* @brief Gets the Kinetis Revision ID in the System Device ID register (SIM_SDID).
*
* This function  gets the Kinetis Revision ID in System Device ID register.
*
* @param base     Base address for current SIM instance.
* @return id Kinetis Revision ID
*/
static inline uint32_t SIM_HAL_GetRevId(SIM_Type * base)
{
    return SIM_BRD_SDID_REVID(base);
}

/*!
* @brief Gets the program flash size in the Flash Configuration Register 1 (SIM_FCFG).
*
* This function  gets the program flash size in the Flash Configuration Register 1.
*
* @param base     Base address for current SIM instance.
* @return size Program flash Size
*/
static inline uint32_t SIM_HAL_GetProgramFlashSize(SIM_Type * base)
{
    return SIM_BRD_FCFG1_PFSIZE(base);
}

/*!
* @brief Sets the Flash Doze in the Flash Configuration Register 1  (SIM_FCFG).
*
* This function  sets the Flash Doze in the Flash Configuration Register 1.
*
* @param base     Base address for current SIM instance.
* @param setting Flash Doze setting
*/
static inline void SIM_HAL_SetFlashDoze(SIM_Type * base, uint32_t setting)
{
    SIM_BWR_FCFG1_FLASHDOZE(base, setting);
}

/*!
* @brief Gets the Flash Doze in the Flash Configuration Register 1  (SIM_FCFG).
*
* This function  gets the Flash Doze in the Flash Configuration Register 1.
*
* @param base     Base address for current SIM instance.
* @return setting Flash Doze setting
*/
static inline uint32_t SIM_HAL_GetFlashDoze(SIM_Type * base)
{
    return SIM_BRD_FCFG1_FLASHDOZE(base);
}

/*!
* @brief Sets the Flash disable setting.
*
* This function  sets the Flash disable setting in the
* Flash Configuration Register 1.
*
* @param base     Base address for current SIM instance.
* @param disable      Flash disable setting
*/
static inline void SIM_HAL_SetFlashDisableCmd(SIM_Type * base, bool disable)
{
    SIM_BWR_FCFG1_FLASHDIS(base, disable);
}

/*!
* @brief Gets the Flash disable setting.
*
* This function  gets the Flash disable setting in the
* Flash Configuration Register 1.
*
* @param base     Base address for current SIM instance.
* @return setting Flash disable setting
*/
static inline bool SIM_HAL_GetFlashDisableCmd(SIM_Type * base)
{
    return (bool)SIM_BRD_FCFG1_FLASHDIS(base);
}

/*!
* @brief Gets the Flash maximum address block 0 in the Flash Configuration Register 1  (SIM_FCFG).
*
* This function gets the Flash maximum block 0 in Flash Configuration Register 2.
*
* @param base     Base address for current SIM instance.
* @return address Flash maximum block 0 address
*/
static inline uint32_t SIM_HAL_GetFlashMaxAddrBlock0(SIM_Type * base)
{
    return SIM_BRD_FCFG2_MAXADDR0(base);
}

/*!
* @brief Sets the Timer/PWM x external clock pin select setting.
*
* This function  selects the source of the Timer/PWM x external clock pin select.
*
* @param base	   Base address for current SIM instance.
* @param instance	   device instance.
* @param select Timer/PWM x external clock pin select
*				 - 0: Timer/PWM x external clock driven by the TPM_CLKIN0 pin.
*				 - 1: Timer/PWM x external clock driven by the TPM_CLKIN1 pin.
*/
void SIM_HAL_SetTpmExternalClkPinSelMode(SIM_Type * base,
                                         uint32_t instance,
                                         sim_tpm_clk_sel_t select);

/*!
* @brief Gets the Timer/PWM x external clock pin select setting.
*
* This function  gets the Timer/PWM x external clock pin select setting.
*
* @param base	   Base address for current SIM instance.
* @param instance	   device instance.
* @return select Timer/PWM x external clock pin select setting
*/
sim_tpm_clk_sel_t SIM_HAL_GetTpmExternalClkPinSelMode(SIM_Type * base, uint32_t instance);


#if defined(__cplusplus)
}
#endif /* __cplusplus*/

/*! @}*/

#endif /* __FSL_SIM_HAL_MKL27Z644_H__*/
/*******************************************************************************
* EOF
******************************************************************************/
