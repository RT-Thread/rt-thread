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

#if !defined(__FSL_SIM_HAL_KL25Z4_H__)
#define __FSL_SIM_HAL_KL25Z4_H__

/*! @addtogroup sim_hal*/
/*! @{*/

/*! @file*/

/*******************************************************************************
 * Definitions
 ******************************************************************************/

 /*! @brief COP clock source select */
typedef enum _clock_cop_src_t
{
    kClockCopSrcLpoClk,       /* LPO                                          */
    kClockCopSrcAltClk,       /* Altnative clock, for KL25Z4 it is Bus clock. */
} clock_cop_src_t;

/*! @brief TPM clock source select */
typedef enum _clock_tpm_src
{
    kClockTpmSrcNone,             /* clock disabled */
    kClockTpmSrcPllFllSel,        /* clock as selected by SOPT2[PLLFLLSEL]. */
    kClockTpmSrcOsc0erClk,        /* OSCERCLK clock */
    kClockTpmSrcMcgIrClk          /* MCGIR clock */
} clock_tpm_src_t;

/*! @brief LPTMR clock source select */
typedef enum _clock_lptmr_src_t
{
    kClockLptmrSrcMcgIrClk,        /* MCG out clock  */
    kClockLptmrSrcLpoClk,             /* LPO clock      */
    kClockLptmrSrcEr32kClk,        /* ERCLK32K clock */
    kClockLptmrSrcOsc0erClk,       /* OSCERCLK clock */
} clock_lptmr_src_t;

/*! @brief UART0 clock source select */
typedef enum _clock_lpsci_src
{
    kClockLpsciSrcNone,             /* clock disabled */
    kClockLpsciSrcPllFllSel,        /* clock as selected by SOPT2[PLLFLLSEL]. */
    kClockLpsciSrcOsc0erClk,        /* OSCERCLK clock */
    kClockLpsciSrcMcgIrClk          /* MCGIR clock */
} clock_lpsci_src_t;

/*! @brief USB clock source select */
#if FSL_FEATURE_SOC_USB_COUNT
typedef enum _clock_usbfs_src
{
    kClockUsbfsSrcExt,       /* USB CLKIN Clock */
    kClockUsbfsSrcPllFllSel    /* clock as selected by SOPT2[PLLFLLSEL] */
} clock_usbfs_src_t;
#endif

/*! @brief SIM PLLFLLSEL clock source select */
typedef enum _clock_pllfll_sel
{
    kClockPllFllSelFll,       /* Fll clock */
    kClockPllFllSelPll        /* Pll0 clock */
} clock_pllfll_sel_t;

/*! @brief SIM external reference clock source select (OSC32KSEL) */
typedef enum _clock_er32k_src
{
    kClockEr32kSrcOsc0     = 0U,     /* OSC 32k clock */
    kClockEr32kSrcReserved = 1U,     /* Reserved */
    kClockEr32kSrcRtc      = 2U,     /* RTC 32k clock */
    kClockEr32kSrcLpo      = 3U      /* LPO clock */
} clock_er32k_src_t;

/*! @brief SIM CLKOUT_SEL clock source select */
typedef enum _clock_clkout_src
{
    kClockClkoutReserved  = 0U,        /* Reserved */
    kClockClkoutReserved1 = 1U,        /* Reserved */
    kClockClkoutBusClk    = 2U,        /* Bus clock */
    kClockClkoutLpoClk    = 3U,        /* LPO clock */
    kClockClkoutMcgIrClk  = 4U,        /* MCG ir clock */
    kClockClkoutReserved2 = 5U,        /* Reserved */
    kClockClkoutOsc0erClk = 6U,        /* OSC0ER clock */
    kClockClkoutReserved3 = 7U         
} clock_clkout_src_t;

/*! @brief SIM RTCCLKOUTSEL clock source select */
typedef enum _clock_rtcout_src
{
    kClockRtcoutSrc1Hz,         /* 1Hz clock */
    kClockRtcoutSrc32kHz        /* 32KHz clock */
} clock_rtcout_src_t;

/*! @brief SIM USB voltage regulator in standby mode setting during stop modes */
#if FSL_FEATURE_SOC_USB_COUNT
typedef enum _sim_usbsstby_mode
{
    kSimUsbsstbyNoRegulator,        /* regulator not in standby during Stop modes */
    kSimUsbsstbyWithRegulator       /* regulator in standby during Stop modes */
} sim_usbsstby_mode_t;

/*! @brief SIM USB voltage regulator in standby mode setting during VLPR and VLPW modes */
typedef enum _sim_usbvstby_mode
{
    kSimUsbvstbyNoRegulator,        /* regulator not in standby during VLPR and VLPW modes */
    kSimUsbvstbyWithRegulator       /* regulator in standby during VLPR and VLPW modes */
} sim_usbvstby_mode_t;
#endif

/*! @brief SIM ADCx pre-trigger select */
typedef enum _sim_adc_pretrg_sel
{
    kSimAdcPretrgselA,              /* Pre-trigger A selected for ADCx */
    kSimAdcPretrgselB               /* Pre-trigger B selected for ADCx */
} sim_adc_pretrg_sel_t;

/*! @brief SIM ADCx trigger select */
typedef enum _sim_adc_trg_sel
{
    kSimAdcTrgselExt       = 0U,         /* External trigger */
    kSimAdcTrgSelComp0     = 1U,         /* CMP0 output */
    kSimAdcTrgSelReserved  = 2U,         /* Reserved */
    kSimAdcTrgSelReserved1 = 3U,         /* Reserved */
    kSimAdcTrgSelPit0      = 4U,         /* PIT trigger 0 */
    kSimAdcTrgSelPit1      = 5U,         /* PIT trigger 1 */
    kSimAdcTrgSelReserved2 = 6U,         /* Reserved */
    kSimAdcTrgSelReserved3 = 7U,         /* Reserved */
    kSimAdcTrgSelTpm0      = 8U,         /* TPM0 overflow */
    kSimAdcTrgSelTpm1      = 9U,         /* TPM1 overflow */
    kSimAdcTrgSelTpm2      = 10U,        /* TPM2 overflow */
    kSimAdcTrgSelReserved4 = 11U,        /* Reserved */
    kSimAdcTrgSelRtcAlarm  = 12U,        /* RTC alarm */
    kSimAdcTrgSelRtcSec    = 13U,        /* RTC seconds */
    kSimAdcTrgSelLptimer   = 14U,        /* Low-power timer trigger */
    kSimAdcTrgSelReserved5 = 15U         /* Reserved */
} sim_adc_trg_sel_t;

/*! @brief SIM UART receive data source select */
typedef enum _sim_uart_rxsrc
{
    kSimUartRxsrcPin,               /* UARTx_RX Pin */
    kSimUartRxsrcCmp0,              /* CMP0 */
} sim_uart_rxsrc_t;

/*! @brief SIM UART transmit data source select */
typedef enum _sim_uart_txsrc
{
    kSimUartTxsrcPin,               /* UARTx_TX Pin */
    kSimUartTxsrcTpm0,              /* UARTx_TX pin modulated with TPM1 channel 0 output */
    kSimUartTxsrcTpm1,              /* UARTx_TX pin modulated with TPM2 channel 0 output */
    kSimUartTxsrcReserved           /* Reserved */
} sim_uart_txsrc_t;

/*! @brief SIM LPSCI receive data source select */
typedef enum _sim_lpsci_rxsrc
{
    kSimLpsciRxsrcPin,               /* LPSCIx_RX Pin */
    kSimLpsciRxsrcCmp0,              /* CMP0 */
} sim_lpsci_rxsrc_t;

/*! @brief SIM LPSCI transmit data source select */
typedef enum _sim_lpsci_txsrc
{
    kSimLpsciTxsrcPin,               /* LPSCIx_TX Pin */
    kSimLpsciTxsrcTpm0,              /* LPSCIx_TX pin modulated with TPM1 channel 0 output */
    kSimLpsciTxsrcTpm1,              /* LPSCIx_TX pin modulated with TPM2 channel 0 output */
    kSimLpsciTxsrcReserved           /* Reserved */
} sim_lpsci_txsrc_t;

/*! @brief SIM Timer/PWM external clock select */
typedef enum _sim_tpm_clk_sel
{
    kSimTpmClkSel0,                 /* Timer/PWM TPM_CLKIN0 pin. */
    kSimTpmClkSel1                  /* Timer/PWM TPM_CLKIN1 pin. */
} sim_tpm_clk_sel_t;

/*! @brief SIM Timer/PWM x channel y input capture source select */
typedef enum _sim_tpm_ch_src
{
    kSimTpmChSrc0,                  /* TPMx_CH0 signal */
    kSimTpmChSrc1,                  /* CMP0 output */
    kSimTpmChSrc2,                  /* Reserved */
    kSimTpmChSrc3                   /* USB start of frame pulse */	
} sim_tpm_ch_src_t;

/* SCGC bit index. */
#define FSL_SIM_SCGC_BIT(SCGCx, n) (((SCGCx-1U)<<5U) + n)

typedef enum _sim_clock_gate_name
{
    kSimClockGateI2c0      = FSL_SIM_SCGC_BIT(4U, 6U),
    kSimClockGateI2c1      = FSL_SIM_SCGC_BIT(4U, 7U),
    kSimClockGateLpsci0    = FSL_SIM_SCGC_BIT(4U, 10U),
    kSimClockGateUart1     = FSL_SIM_SCGC_BIT(4U, 11U),
    kSimClockGateUart2     = FSL_SIM_SCGC_BIT(4U, 12U),
    kSimClockGateUsbfs0    = FSL_SIM_SCGC_BIT(4U, 18U),
    kSimClockGateCmp0      = FSL_SIM_SCGC_BIT(4U, 19U),
    kSimClockGateSpi0      = FSL_SIM_SCGC_BIT(4U, 22U),
    kSimClockGateSpi1      = FSL_SIM_SCGC_BIT(4U, 23U),
    kSimClockGateLptmr0    = FSL_SIM_SCGC_BIT(5U, 0U),
    kSimClockGateTsi0      = FSL_SIM_SCGC_BIT(5U, 5U),
    kSimClockGatePortA     = FSL_SIM_SCGC_BIT(5U, 9U),
    kSimClockGatePortB     = FSL_SIM_SCGC_BIT(5U, 10U),
    kSimClockGatePortC     = FSL_SIM_SCGC_BIT(5U, 11U),
    kSimClockGatePortD     = FSL_SIM_SCGC_BIT(5U, 12U),
    kSimClockGatePortE     = FSL_SIM_SCGC_BIT(5U, 13U),
    kSimClockGateFtf0      = FSL_SIM_SCGC_BIT(6U, 0U),
    kSimClockGateDmamux0   = FSL_SIM_SCGC_BIT(6U, 1U),
    kSimClockGatePit0      = FSL_SIM_SCGC_BIT(6U, 23U),
    kSimClockGateTpm0      = FSL_SIM_SCGC_BIT(6U, 24U),
    kSimClockGateTpm1      = FSL_SIM_SCGC_BIT(6U, 25U),
    kSimClockGateTpm2      = FSL_SIM_SCGC_BIT(6U, 26U),
    kSimClockGateAdc0      = FSL_SIM_SCGC_BIT(6U, 27U),
    kSimClockGateRtc0      = FSL_SIM_SCGC_BIT(6U, 29U),
    kSimClockGateDac0      = FSL_SIM_SCGC_BIT(6U, 31U),
    kSimClockGateDma0      = FSL_SIM_SCGC_BIT(7U, 8U)
} sim_clock_gate_name_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus*/

/*! @name IP related clock feature APIs*/
/*@{*/

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
 * @brief Set the selection of the clock source for the USB FS 48 MHz clock.
 *
 * This function sets the selection of the clock source for the USB FS 48 MHz clock.
 *
 * @param base Base address for current SIM instance.
 * @param instance IP instance.
 * @param setting  The value to set.
 */
 #if FSL_FEATURE_SOC_USB_COUNT
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
#endif

/*!
 * @brief Set the TPM clock source selection.
 *
 * This function sets the TPM clock source selection.
 *
 * @param base Base address for current SIM instance.
 * @param instance IP instance.
 * @param setting  The value to set.
 */
static inline void CLOCK_HAL_SetTpmSrc(SIM_Type * base,
                                       uint32_t  instance,
                                       clock_tpm_src_t setting)
{
    SIM_BWR_SOPT2_TPMSRC(base, setting);
}

/*!
 * @brief Get the TPM clock source selection.
 *
 * This function gets the TPM clock source selection.
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
 * @brief Set the LPSCI clock source selection.
 *
 * This function sets the LPSCI clock source selection.
 *
 * @param base Base address for current SIM instance.
 * @param instance IP instance.
 * @param setting  The value to set.
 */
static inline void CLOCK_HAL_SetLpsciSrc(SIM_Type * base,
                                         uint32_t instance,
                                         clock_lpsci_src_t setting)
{
    SIM_BWR_SOPT2_UART0SRC(base, setting);
}

/*!
 * @brief Get the LPSCI clock source selection.
 *
 * This function gets the LPSCI clock source selection.
 *
 * @param base Base address for current SIM instance.
 * @param instance IP instance.
 * @return Current selection.
 */
static inline clock_lpsci_src_t CLOCK_HAL_GetLpsciSrc(SIM_Type * base,
                                                      uint32_t instance)
{
    return (clock_lpsci_src_t)SIM_BRD_SOPT2_UART0SRC(base);
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
 * @brief Set PLL/FLL clock selection.
 *
 * This function sets the selection of the high frequency clock for
 * various peripheral clocking options
 *
 * @param base Base address for current SIM instance.
 * @param setting  The value to set.
 */
static inline void CLOCK_HAL_SetPllfllSel(SIM_Type * base,
                                          clock_pllfll_sel_t setting)
{
    SIM_BWR_SOPT2_PLLFLLSEL(base, setting);
}

/*!
 * @brief Get PLL/FLL clock selection.
 *
 * This function gets the selection of the high frequency clock for
 * various peripheral clocking options
 *
 * @param base Base address for current SIM instance.
 * @return Current selection.
 */
static inline clock_pllfll_sel_t CLOCK_HAL_GetPllfllSel(SIM_Type * base)
{
    return (clock_pllfll_sel_t)SIM_BRD_SOPT2_PLLFLLSEL(base);
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
 * @brief Sets the USB voltage regulator enabled setting.
 *
 * This function  controls whether the USB voltage regulator is enabled. This bit
 * can only be written when the SOPT1CFG[URWE] bit is set.
 *
 * @param base     Base address for current SIM instance.
 * @param enable   USB voltage regulator enable setting
 *                  - true: USB voltage regulator is enabled.
 *                  - false: USB voltage regulator is disabled.
 */
#if FSL_FEATURE_SOC_USB_COUNT
static inline void SIM_HAL_SetUsbVoltRegulatorCmd(SIM_Type * base, bool enable)
{
    SIM_BWR_SOPT1_USBREGEN(base, enable ? 1 : 0);
}

/*!
 * @brief Gets the USB voltage regulator enabled setting.
 *
 * This function  gets the USB voltage regulator enabled setting.
 *
 * @param base     Base address for current SIM instance.
 * @return enabled True if the USB voltage regulator is enabled.
 */
static inline bool SIM_HAL_GetUsbVoltRegulatorCmd(SIM_Type * base)
{
    return SIM_BRD_SOPT1_USBREGEN(base);
}

/*!
 * @brief Sets the USB voltage regulator in a standby mode setting during Stop, VLPS, LLS, and VLLS.
 *
 * This function  controls whether the USB voltage regulator is placed in a standby
 * mode during Stop, VLPS, LLS, and VLLS modes. This bit can only be written when the
 * SOPT1CFG[USSWE] bit is set.
 *
 * @param base     Base address for current SIM instance.
 * @param setting   USB voltage regulator in standby mode setting
 *                  - 0: USB voltage regulator not in standby during Stop, VLPS, LLS and
 *                       VLLS modes.
 *                  - 1: USB voltage regulator in standby during Stop, VLPS, LLS and VLLS
 *                       modes.
 */
static inline void SIM_HAL_SetUsbVoltRegulatorInStdbyDuringStopMode(SIM_Type * base,
                                                                    sim_usbsstby_mode_t setting)
{
    SIM_BWR_SOPT1_USBSSTBY(base, setting);
}

/*!
 * @brief Gets the USB voltage regulator in a standby mode setting.
 *
 * This function  gets the USB voltage regulator in a standby mode setting.
 *
 * @param base     Base address for current SIM instance.
 * @return setting  USB voltage regulator in a standby mode setting
 */
static inline sim_usbsstby_mode_t SIM_HAL_GetUsbVoltRegulatorInStdbyDuringStopMode(SIM_Type * base)
{
    return (sim_usbsstby_mode_t)SIM_BRD_SOPT1_USBSSTBY(base);
}

/*!
 * @brief Sets the USB voltage regulator in a standby mode during the VLPR or the VLPW.
 *
 * This function  controls whether the USB voltage regulator is placed in a standby
 * mode during the VLPR and the VLPW modes. This bit can only be written when the
 * SOPT1CFG[UVSWE] bit is set.
 *
 * @param base     Base address for current SIM instance.
 * @param setting   USB voltage regulator in standby mode setting
 *                  - 0: USB voltage regulator not in standby during VLPR and VLPW modes.
 *                  - 1: USB voltage regulator in standby during VLPR and VLPW modes.
 */
static inline void SIM_HAL_SetUsbVoltRegulatorInStdbyDuringVlprwMode(SIM_Type * base,
                                                                     sim_usbvstby_mode_t setting)
{
    SIM_BWR_SOPT1_USBVSTBY(base, setting);
}

/*!
 * @brief Gets the USB voltage regulator in a standby mode during the VLPR or the VLPW.
 *
 * This function  gets the USB voltage regulator in a standby mode during the VLPR or the VLPW.
 *
 * @param base     Base address for current SIM instance.
 * @return setting  USB voltage regulator in a standby mode during the VLPR or the VLPW
 */
static inline sim_usbvstby_mode_t SIM_HAL_GetUsbVoltRegulatorInStdbyDuringVlprwMode(SIM_Type * base)
{
    return (sim_usbvstby_mode_t)SIM_BRD_SOPT1_USBVSTBY(base);
}

/*!
 * @brief Sets the USB voltage regulator stop standby write enable setting.
 *
 * This function  controls whether the USB voltage regulator stop  standby write
 * feature is enabled. Writing one to this bit allows the SOPT1[USBSSTBY] bit to be written. This
 * register bit clears after a write to SOPT1[USBSSTBY].
 *
 * @param base     Base address for current SIM instance.
 * @param enable  USB voltage regulator stop standby write enable setting
 *                  - true: SOPT1[USBSSTBY] can be written.
 *                  - false: SOPT1[USBSSTBY] cannot be written.
 */
static inline void SIM_HAL_SetUsbVoltRegulatorInStdbyDuringStopCmd(SIM_Type * base, bool enable)
{
    SIM_BWR_SOPT1CFG_USSWE(base, enable ? 1 : 0);
}

/*!
 * @brief Gets the USB voltage regulator stop standby write enable setting.
 *
 * This function  gets the USB voltage regulator stop standby write enable setting.
 *
 * @param base     Base address for current SIM instance.
 * @return enabled True if the USB voltage regulator stop standby write is enabled.
 */
static inline bool SIM_HAL_GetUsbVoltRegulatorInStdbyDuringStopCmd(SIM_Type * base)
{
    return SIM_BRD_SOPT1CFG_USSWE(base);
}

/*!
 * @brief Sets the USB voltage regulator VLP standby write enable setting.
 *
 * This function  controls whether USB voltage regulator VLP standby write
 * feature is enabled. Writing one to this bit allows the SOPT1[USBVSTBY] bit to be written. This
 * register bit clears after a write to SOPT1[USBVSTBY].
 *
 * @param base     Base address for current SIM instance.
 * @param enable   USB voltage regulator VLP standby write enable setting
 *                  - true: SOPT1[USBSSTBY] can be written.
 *                  - false: SOPT1[USBSSTBY] cannot be written.
 */
static inline void SIM_HAL_SetUsbVoltRegulatorInStdbyDuringVlprwCmd(SIM_Type * base, bool enable)
{
    SIM_BWR_SOPT1CFG_UVSWE(base, enable ? 1 : 0);
}

/*!
 * @brief Gets the USB voltage regulator VLP standby write enable setting.
 *
 * This function  gets the USB voltage regulator VLP standby write enable setting.
 *
 * @param base     Base address for current SIM instance.
 * @return enabled True if the USB voltage regulator VLP standby write is enabled.
 */
static inline bool SIM_HAL_GetUsbVoltRegulatorInStdbyDuringVlprwCmd(SIM_Type * base)
{
    return SIM_BRD_SOPT1CFG_UVSWE(base);
}

/*!
 * @brief Sets the USB voltage regulator enable write enable setting.
 *
 * This function  controls whether the USB voltage regulator write enable
 * feature is enabled. Writing one to this bit allows the SOPT1[USBREGEN] bit to be written.
 * This register bit clears after a write to SOPT1[USBREGEN].
 *
 * @param base     Base address for current SIM instance.
 * @param enable   USB voltage regulator enable write enable setting
 *                  - true: SOPT1[USBSSTBY] can be written.
 *                  - false: SOPT1[USBSSTBY] cannot be written.
 */
static inline void SIM_HAL_SetUsbVoltRegulatorWriteCmd(SIM_Type * base, bool enable)
{
    SIM_BWR_SOPT1CFG_URWE(base, enable ? 1 : 0);
}

/*!
 * @brief Gets the USB voltage regulator enable write enable setting.
 *
 * This function  gets the USB voltage regulator enable write enable setting.
 *
 * @param base     Base address for current SIM instance.
 * @return enabled True if USB voltage regulator enable write is enabled.
 */
static inline bool SIM_HAL_GetUsbVoltRegulatorWriteCmd(SIM_Type * base)
{
    return SIM_BRD_SOPT1CFG_URWE(base);
}
#endif

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
void SIM_HAL_SetAdcAlternativeTriggerCmd(SIM_Type * base,
                                         uint32_t instance,
                                         bool enable);

/*!
 * @brief Gets the ADCx alternate trigger enable setting.
 *
 * This function gets the ADCx alternate trigger enable setting.
 *
 * @param base     Base address for current SIM instance.
 * @param instance     device instance.
 * @return enabled True if  ADCx alternate trigger is enabled
 */
bool SIM_HAL_GetAdcAlternativeTriggerCmd(SIM_Type * base, uint32_t instance);

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
void SIM_HAL_SetAdcPreTriggerMode(SIM_Type * base,
                                  uint32_t instance,
                                  sim_adc_pretrg_sel_t select);

/*!
 * @brief Gets the ADCx pre-trigger select setting.
 *
 * This function  gets the ADCx pre-trigger select setting.
 *
 * @param base     Base address for current SIM instance.
 * @param instance     device instance.
 * @return select ADCx pre-trigger select setting
 */
sim_adc_pretrg_sel_t SIM_HAL_GetAdcPreTriggerMode(SIM_Type * base,
                                                  uint32_t instance);

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
void SIM_HAL_SetAdcTriggerMode(SIM_Type * base,
                               uint32_t instance,
                               sim_adc_trg_sel_t select);

/*!
 * @brief Gets the ADCx trigger select setting.
 *
 * This function  gets the ADCx trigger select setting.
 *
 * @param base     Base address for current SIM instance.
 * @param instance     device instance.
 * @return ADCx trigger select setting
 */
sim_adc_trg_sel_t SIM_HAL_GetAdcTriggerMode(SIM_Type * base,
                                            uint32_t instance);

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
 * @brief Sets the UARTx receive data source select setting.
 *
 * This function  selects the source for the UARTx receive data.
 *
 * @param base     Base address for current SIM instance.
 * @param instance     device instance.
 * @param select the source for the UARTx receive data
 */
static inline void SIM_HAL_SetUartRxSrcMode(SIM_Type * base,
                                            uint32_t instance,
                                            sim_uart_rxsrc_t select)
{
    SIM_BWR_SOPT5_UART1RXSRC(base, select);
}

/*!
 * @brief Gets the UARTx receive data source select setting.
 *
 * This function  gets the UARTx receive data source select setting.
 *
 * @param base     Base address for current SIM instance.
 * @param instance     device instance.
 * @return select UARTx receive data source select setting
 */
static inline sim_uart_rxsrc_t SIM_HAL_GetUartRxSrcMode(SIM_Type * base, uint32_t instance)
{
    return (sim_uart_rxsrc_t)SIM_BRD_SOPT5_UART1RXSRC(base);
}

/*!
 * @brief Sets the UARTx transmit data source select setting.
 *
 * This function  selects the source for the UARTx transmit data.
 *
 * @param base     Base address for current SIM instance.
 * @param instance     device instance.
 * @param select the source for the UARTx transmit data
 */
static inline void SIM_HAL_SetUartTxSrcMode(SIM_Type * base,
                                            uint32_t instance,
                                            sim_uart_txsrc_t select)
{
    SIM_BWR_SOPT5_UART1TXSRC(base, select);
}

/*!
 * @brief Gets the UARTx transmit data source select setting.
 *
 * This function  gets the UARTx transmit data source select setting.
 *
 * @param base     Base address for current SIM instance.
 * @param instance     device instance.
 * @return select UARTx transmit data source select setting
 */
static inline sim_uart_txsrc_t SIM_HAL_GetUartTxSrcMode(SIM_Type * base, uint32_t instance)
{
    return (sim_uart_txsrc_t)SIM_BRD_SOPT5_UART1TXSRC(base);
}

/*!
 * @brief Sets the LPSCIx receive data source select setting.
 *
 * This function  selects the source for the LPSCIx receive data.
 *
 * @param base     Base address for current SIM instance.
 * @param instance     device instance.
 * @param select the source for the LPSCIx receive data
 */
static inline void SIM_HAL_SetLpsciRxSrcMode(SIM_Type * base,
                              uint32_t instance,
                              sim_lpsci_rxsrc_t select)
{
    SIM_BWR_SOPT5_UART0RXSRC(base, select);
}

/*!
 * @brief Gets the LPSCIx receive data source select setting.
 *
 * This function  gets the LPSCIx receive data source select setting.
 *
 * @param base     Base address for current SIM instance.
 * @param instance     device instance.
 * @return select LPSCIx receive data source select setting
 */
static inline sim_lpsci_rxsrc_t SIM_HAL_GetLpsciRxSrcMode(SIM_Type * base, uint32_t instance)
{
    return (sim_lpsci_rxsrc_t)SIM_BRD_SOPT5_UART0RXSRC(base);
}

/*!
 * @brief Sets the LPSCIx transmit data source select setting.
 *
 * This function  selects the source for the LPSCIx transmit data.
 *
 * @param base     Base address for current SIM instance.
 * @param instance     device instance.
 * @param select the source for the LPSCIx transmit data
 */
static inline void SIM_HAL_SetLpsciTxSrcMode(SIM_Type * base,
                              uint32_t instance,
                              sim_lpsci_txsrc_t select)
{
    SIM_BWR_SOPT5_UART0TXSRC(base, select);
}

/*!
 * @brief Gets the LPSCIx transmit data source select setting.
 *
 * This function  gets the LPSCIx transmit data source select setting.
 *
 * @param base     Base address for current SIM instance.
 * @param instance     device instance.
 * @return select LPSCIx transmit data source select setting
 */
static inline sim_lpsci_txsrc_t SIM_HAL_GetLpsciTxSrcMode(SIM_Type * base, uint32_t instance)
{
    return (sim_lpsci_txsrc_t)SIM_BRD_SOPT5_UART0TXSRC(base);
}

#if FSL_FEATURE_SIM_OPT_HAS_ODE

/*!
* @brief Sets the UARTx Open Drain Enable setting.


*
* This function  enables/disables the UARTx Open Drain.
*
* @param base Register base address of SIM.
* @param instance UART instance.
* @param enable Enable/disable UARTx Open Drain


*                - True: Enable UARTx Open Drain
*                - False: Disable UARTx Open Drain
*/
void SIM_HAL_SetUartOpenDrainCmd(SIM_Type * base, uint32_t  instance, bool enable);

/*!
* @brief Gets the UARTx Open Drain Enable setting.
*
* This function  gets the UARTx Open Drain Enable setting.
*
* @param base Register base address of SIM.
* @param instance UART instance.
* @return enabled True if UARTx Open Drain is enabled.
*/
bool SIM_HAL_GetUartOpenDrainCmd(SIM_Type * base, uint32_t  instance);

/*!
* @brief Sets the LPSCIx Open Drain Enable setting.
*
* This function  enables/disables the LPSCIx Open Drain.
*
* @param base Register base address of SIM.
* @param instance LPSCI instance.
* @param enable Enable/disable LPSCIx Open Drain
*				 - True: Enable LPSCIx Open Drain
*				 - False: Disable LPSCIx Open Drain
*/
static inline void SIM_HAL_SetLpsciOpenDrainCmd(SIM_Type * base, uint32_t  instance, bool enable)
{
    SIM_BWR_SOPT5_UART0ODE(base, enable);
}

/*!
* @brief Gets the LPSCIx Open Drain Enable setting.
*
* This function  gets the LPSCIx Open Drain Enable setting.
*
* @param base Register base address of SIM.
* @param instance LPSCI instance.
* @return enabled True if LPSCIx Open Drain is enabled.
*/
static inline bool SIM_HAL_GetLpsciOpenDrainCmd(SIM_Type * base, uint32_t  instance)
{
    return (bool)SIM_BRD_SOPT5_UART0ODE(base);
}
#endif

#if FSL_FEATURE_SIM_OPT_HAS_TPM

/*!
* @brief Sets the Timer/PWM x external clock pin select setting.
*
* This function selects the source of the Timer/PWM x external clock pin select.


*
* @param base     Base address for current SIM instance.
* @param instance     device instance.
* @param select Timer/PWM x external clock pin select
*/

void SIM_HAL_SetTpmExternalClkPinSelMode(SIM_Type * base,
                                         uint32_t instance,
                                         sim_tpm_clk_sel_t select);

/*!
* @brief Gets the Timer/PWM x external clock pin select setting.
*
* This function  gets the Timer/PWM x external clock pin select setting.
*
* @param base     Base address for current SIM instance.
* @param instance     device instance.
* @return Timer/PWM x external clock pin select setting
*/
sim_tpm_clk_sel_t SIM_HAL_GetTpmExternalClkPinSelMode(SIM_Type * base, uint32_t instance);

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
* This function  gets the Timer/PWM x channel y input capture source.
*
* @param base     Base address for current SIM instance.
* @param instance     device instance.
* @param channel      TPM channel y
* @return select Timer/PWM x channel y input capture source
*/

sim_tpm_ch_src_t SIM_HAL_GetTpmChSrcMode(SIM_Type * base,
                                         uint32_t instance,
                                         uint8_t channel); 
#endif

/*!
 * @brief Gets the Kinetis Family ID in the System Device ID register (SIM_SDID).
 *
 * This function  gets the Kinetis Family ID in the System Device ID register.
 *
 * @param base     Base address for current SIM instance.
 * @return id Kinetis Family ID
 */
static inline uint32_t SIM_HAL_GetFamilyId(SIM_Type * base)
{
    return SIM_BRD_SDID_FAMID(base);
}

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
 * @brief Gets the Kinetis SramSize in the System Device ID register (SIM_SDID).
 *
 * This function  gets the Kinetis SramSize in System Device ID register.
 *
 * @param base     Base address for current SIM instance.
 * @return id Kinetis SramSize
 */
static inline uint32_t SIM_HAL_GetSramSize(SIM_Type * base)
{
    return SIM_BRD_SDID_SRAMSIZE(base);
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
 * @brief Gets the Kinetis Die ID in the System Device ID register (SIM_SDID).
 *
 * This function  gets the Kinetis Die ID in System Device ID register.
 *
 * @param base     Base address for current SIM instance.
 * @return id Kinetis Die ID
 */
static inline uint32_t SIM_HAL_GetDieId(SIM_Type * base)
{
    return SIM_BRD_SDID_DIEID(base);
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

#if defined(__cplusplus)
}
#endif /* __cplusplus*/

/*! @}*/

#endif /* __FSL_SIM_HAL_KL25Z4_H__*/
/*******************************************************************************
 * EOF
 ******************************************************************************/

