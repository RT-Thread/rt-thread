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

#if !defined(__FSL_SIM_HAL_KV11Z7_H__)
#define __FSL_SIM_HAL_KV11Z7_H__

#include <assert.h>
/*!
 * @addtogroup sim_hal_kv11z7
 * @{
 */
/*! @file*/

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*! @brief WDOG clock source select */
typedef enum _clock_wdog_src_t
{
    kClockWdogSrcLpoClk,       /*!< LPO             */
    kClockWdogSrcAltClk,       /*!< Alternative clock */
#if (defined(DOXYGEN_OUTPUT) && (DOXYGEN_OUTPUT))
} clock_wdog_src_kv11z7_t;
#else
} clock_wdog_src_t;
#endif

/*! @brief LPTMR clock source select */
typedef enum _clock_lptmr_src_t
{
    kClockLptmrSrcMcgIrClk,        /*!< MCG IRC clock  */
    kClockLptmrSrcLpoClk,          /*!< LPO clock      */
    kClockLptmrSrcEr32kClk,        /*!< ERCLK32K clock */
    kClockLptmrSrcOsc0erClk,       /*!< OSCERCLK clock */
#if (defined(DOXYGEN_OUTPUT) && (DOXYGEN_OUTPUT))
} clock_lptmr_src_kv11z7_t;
#else
} clock_lptmr_src_t;
#endif

/*! @brief SIM external reference clock source select (OSC32KSEL). */
typedef enum _clock_er32k_src
{
    kClockEr32kSrcOsc0 = 0U, /*!< OSC0 clock (OSC032KCLK).  */
    kClockEr32kSrcLpo  = 3U, /*!< LPO clock.                */
#if (defined(DOXYGEN_OUTPUT) && (DOXYGEN_OUTPUT))
} clock_er32k_src_kv11z7_t;
#else
} clock_er32k_src_t;
#endif

/*! @brief SIM CLKOUT_SEL clock source select */
typedef enum _clock_clkout_src
{
    kClockClkoutSelBusClk      = 2U,  /*!< Bus clock    */
    kClockClkoutSelLpoClk      = 3U,  /*!< LPO clock      */
    kClockClkoutSelMcgIrClk    = 4U,  /*!< MCG IRC clock  */
    kClockClkoutSelOsc0erClk   = 6U,  /*!< OSCERCLK0 clock*/
#if (defined(DOXYGEN_OUTPUT) && (DOXYGEN_OUTPUT))
} clock_clkout_src_kv11z7_t;
#else
} clock_clkout_src_t;
#endif

/*! @brief SIM SIM ADCx alternative conversion trigger select */
typedef enum _sim_adc_alttrg_sel
{
    kSimAdcAltTrgselPDB0       = 0U,  /*!< PDB0 channel 0         */
    kSimAdcAltTrgselPDB1       = 1U,  /*!< PDB1 channel 0         */
    kSimAdcAltTrgselALT        = 2U,  /*!< Alternative trigger    */
    kSimAdcAltTrgselPDB0orPDB1 = 3U,  /*!< PDB0 or PDB1 channel 0 */
#if (defined(DOXYGEN_OUTPUT) && (DOXYGEN_OUTPUT))
} sim_adc_alttrg_sel_kv11z7_t;
#else
} sim_adc_alttrg_sel_t;
#endif

/*! @brief SIM ADCx pre-trigger select */
typedef enum _sim_adc_pretrg_sel
{
    kSimAdcPretrgselA,              /*!< Pre-trigger A selected for ADCx */
    kSimAdcPretrgselB               /*!< Pre-trigger B selected for ADCx */
#if (defined(DOXYGEN_OUTPUT) && (DOXYGEN_OUTPUT))
} sim_adc_pretrg_sel_kv11z7_t;
#else
} sim_adc_pretrg_sel_t;
#endif

/*! @brief SIM ADCx trigger select */
typedef enum _sim_adc_trg_sel
{
    kSimAdcTrgselExt              = 0U,    /*!< External trigger                */
    kSimAdcTrgselExt0             = 0U,    /*!< External trigger 0              */
    kSimAdcTrgSelHighSpeedComp0   = 1U,    /*!< High speed comparator 0 output  */
    kSimAdcTrgSelHighSpeedComp1   = 2U,    /*!< High speed comparator 1 output  */
    kSimAdcTrgselExt1             = 3U,    /*!< External trigger 1              */
    kSimAdcTrgSelDma0             = 4U,    /*!< DMA channel 0                   */
    kSimAdcTrgSelDma1             = 5U,    /*!< DMA channel 1                   */
    kSimAdcTrgSelDma2             = 6U,    /*!< DMA channel 2                   */
    kSimAdcTrgSelDma3             = 7U,    /*!< DMA channel 3                   */
    kSimAdcTrgSelFtm0             = 8U,    /*!< FTM0 trigger                    */
    kSimAdcTrgSelFtm1             = 9U,    /*!< FTM1 trigger                    */
    kSimAdcTrgSelFtm2             = 10U,   /*!< FTM2 trigger                    */
    kSimAdcTrgSelFtm3             = 11U,   /*!< FTM3 trigger                    */
    kSimAdcTrgSelFtm4             = 12U,   /*!< FTM4 trigger                    */
    kSimAdcTrgSelFtm5             = 13U,   /*!< FTM5 trigger                    */
    kSimAdcTrgSelLptimer          = 14U    /*!< Low-power timer trigger         */
#if (defined(DOXYGEN_OUTPUT) && (DOXYGEN_OUTPUT))
} sim_adc_trg_sel_kv11z7_t;
#else
} sim_adc_trg_sel_t;
#endif

/*! @brief SIM receive data source select */
typedef enum _sim_uart_rxsrc
{
    kSimUartRxsrcPin,               /*!< UARTx_RX Pin  */
    kSimUartRxsrcCmp0,              /*!< CMP0          */
    kSimUartRxsrcCmp1,              /*!< CMP1          */
#if (defined(DOXYGEN_OUTPUT) && (DOXYGEN_OUTPUT))
} sim_uart_rxsrc_kv11z7_t;
#else
} sim_uart_rxsrc_t;
#endif

/*! @brief SIM transmit data source select */
typedef enum _sim_uart_txsrc
{
    kSimUartTxsrcPin,    /*!< UARTx_TX Pin */
    kSimUartTxsrcFtm1,   /*!< UARTx_TX pin modulated with FTM1 channel 0 output */
    kSimUartTxsrcFtm2,   /*!< UARTx_TX pin modulated with FTM2 channel 0 output */
#if (defined(DOXYGEN_OUTPUT) && (DOXYGEN_OUTPUT))
} sim_uart_txsrc_kv11z7_t;
#else
} sim_uart_txsrc_t;
#endif

/*! @brief SIM FlexTimer x trigger y select */
typedef enum _sim_ftm_trg_src
{
    kSimFtmTrgSrc0,                 /*!< FlexTimer x trigger y select 0 */
    kSimFtmTrgSrc1                  /*!< FlexTimer x trigger y select 1 */
#if (defined(DOXYGEN_OUTPUT) && (DOXYGEN_OUTPUT))
} sim_ftm_trg_src_kv11z7_t;
#else
} sim_ftm_trg_src_t;
#endif

/*! @brief SIM FlexTimer external clock select */
typedef enum _sim_ftm_clk_sel
{
    kSimFtmClkSel0,                 /*!< FTM CLKIN0 pin. */
    kSimFtmClkSel1,                 /*!< FTM CLKIN1 pin. */
    kSimFtmClkSel2                  /*!< FTM CLKIN2 pin. */
#if (defined(DOXYGEN_OUTPUT) && (DOXYGEN_OUTPUT))
} sim_ftm_clk_sel_kv11z7_t;
#else
} sim_ftm_clk_sel_t;
#endif

/*! @brief SIM FlexTimer Fixed Frequency clock source */
typedef enum _clock_ftm_fixedfreq_src
{
    kClockFtmClkMcgFfClk   = 0U,          /*!< MCGFFCLK. */
    kClockFtmClkMcgIrClk   = 1U,          /*!< MCGIRCLK. */
    kClockFtmClkOsc0erClk  = 2U,          /*!< OSCERCLK. */
#if (defined(DOXYGEN_OUTPUT) && (DOXYGEN_OUTPUT))
} clock_ftm_fixedfreq_src_kv11z7_t;
#else
} clock_ftm_fixedfreq_src_t;
#endif

/*! @brief SIM ADC alt clock source */
typedef enum _clock_adc_alt_src
{
    kClockAdcAltClkSrcOutdiv5    = 0U,          /*!< OUTDIV5 output clock. */
    kClockAdcAltClkSrcMcgIrClk   = 1U,          /*!< MCGIRCLK. */
    kClockAdcAltClkSrcOsc0erClk  = 2U,          /*!< OSCERCLK. */
#if (defined(DOXYGEN_OUTPUT) && (DOXYGEN_OUTPUT))
} clock_adc_alt_src_kv11z7_t;
#else
} clock_adc_alt_src_t;
#endif


/*! @brief SIM FlexTimer x channel y input capture source select */
typedef enum _sim_ftm_ch_src
{
    kSimFtmChSrc0, /*!< FlexTimer x channel y uses input capture source 0. */
    kSimFtmChSrc1, /*!< FlexTimer x channel y uses input capture source 1. */
    kSimFtmChSrc2, /*!< FlexTimer x channel y uses input capture source 2. */
    kSimFtmChSrc3, /*!< FlexTimer x channel y uses input capture source 3. */
#if (defined(DOXYGEN_OUTPUT) && (DOXYGEN_OUTPUT))
} sim_ftm_ch_src_kv11z7_t;
#else
} sim_ftm_ch_src_t;
#endif

/*! @brief SIM FlexTimer x channel y output source select */
typedef enum _sim_ftm_ch_out_src
{
    kSimFtmChOutSrc0, /*!< FlexTimer x channel y output source 0. */
    kSimFtmChOutSrc1, /*!< FlexTimer x channel y output source 1. */
#if (defined(DOXYGEN_OUTPUT) && (DOXYGEN_OUTPUT))
} sim_ftm_ch_out_src_kv11z7_t;
#else
} sim_ftm_ch_out_src_t;
#endif

/*! @brief SIM FlexTimer x Fault y select */
typedef enum _sim_ftm_flt_sel
{
    kSimFtmFltSel0,                 /*!< FlexTimer x fault y select 0 */
    kSimFtmFltSel1                  /*!< FlexTimer x fault y select 1 */
#if (defined(DOXYGEN_OUTPUT) && (DOXYGEN_OUTPUT))
} sim_ftm_flt_sel_kv11z7_t;
#else
} sim_ftm_flt_sel_t;
#endif

/*! @brief SIM FlexTimer0/2 output channel Carrier frequency selection */
typedef enum _sim_ftm_carrier_sel
{
    kSimFtmCarrierSel0,             /*!< Carrier frequency selection 0 */
    kSimFtmCarrierSel1,             /*!< Carrier frequency selection 1 */
    kSimFtmCarrierSel2              /*!< Carrier frequency selection 2 */
#if (defined(DOXYGEN_OUTPUT) && (DOXYGEN_OUTPUT))
} sim_ftm_flt_carrier_sel_kv11z7_t;
#else
} sim_ftm_flt_carrier_sel_t;
#endif

/*! @brief FLEXCAN clock source select */
typedef enum _clock_flexcan_src_t
{
    kClockFlexcanSrcOsc0erClk,    /*!< OSCERCLK  */
    kClockFlexcanSrcBusClk        /*!< Bus clock */
#if (defined(DOXYGEN_OUTPUT) && (DOXYGEN_OUTPUT))
} clock_flexcan_src_kv11z7_t;
#else
} clock_flexcan_src_t;
#endif

/*! @brief SIM SCGC bit index. */
#define FSL_SIM_SCGC_BIT(SCGCx, n) (((SCGCx-1U)<<5U) + n)

/*! @brief Clock gate name used for SIM_HAL_EnableClock/SIM_HAL_DisableClock. */
typedef enum _sim_clock_gate_name
{
    kSimClockGateEwm0      = FSL_SIM_SCGC_BIT(4U, 1U),
    kSimClockGateI2c0      = FSL_SIM_SCGC_BIT(4U, 6U),
    kSimClockGateUart0     = FSL_SIM_SCGC_BIT(4U, 10U),
    kSimClockGateUart1     = FSL_SIM_SCGC_BIT(4U, 11U),
    kSimClockGateCmp       = FSL_SIM_SCGC_BIT(4U, 19U),

    kSimClockGateLptmr0    = FSL_SIM_SCGC_BIT(5U, 0U),
    kSimClockGatePortA     = FSL_SIM_SCGC_BIT(5U, 9U),
    kSimClockGatePortB     = FSL_SIM_SCGC_BIT(5U, 10U),
    kSimClockGatePortC     = FSL_SIM_SCGC_BIT(5U, 11U),
    kSimClockGatePortD     = FSL_SIM_SCGC_BIT(5U, 12U),
    kSimClockGatePortE     = FSL_SIM_SCGC_BIT(5U, 13U),
    
    kSimClockGateFtf0      = FSL_SIM_SCGC_BIT(6U, 0U),
    kSimClockGateDmamux0   = FSL_SIM_SCGC_BIT(6U, 1U),
    kSimClockGateFlexcan0  = FSL_SIM_SCGC_BIT(6U, 4U),
    kSimClockGateFtm3      = FSL_SIM_SCGC_BIT(6U, 6U),
    kSimClockGateFtm4      = FSL_SIM_SCGC_BIT(6U, 7U),
    kSimClockGateFtm5      = FSL_SIM_SCGC_BIT(6U, 8U),
    kSimClockGateSpi0      = FSL_SIM_SCGC_BIT(6U, 12U),
    kSimClockGatePdb1      = FSL_SIM_SCGC_BIT(6U, 17U),
    kSimClockGateCrc0      = FSL_SIM_SCGC_BIT(6U, 18U),
    kSimClockGatePdb0      = FSL_SIM_SCGC_BIT(6U, 22U),
    kSimClockGateFtm0      = FSL_SIM_SCGC_BIT(6U, 24U),
    kSimClockGateFtm1      = FSL_SIM_SCGC_BIT(6U, 25U),
    kSimClockGateFtm2      = FSL_SIM_SCGC_BIT(6U, 26U),
    kSimClockGateAdc0      = FSL_SIM_SCGC_BIT(6U, 27U),
    kSimClockGateAdc1      = FSL_SIM_SCGC_BIT(6U, 28U),
    kSimClockGateDac0      = FSL_SIM_SCGC_BIT(6U, 31U),
    
    kSimClockGateDma0      = FSL_SIM_SCGC_BIT(7U, 8U),
#if (defined(DOXYGEN_OUTPUT) && (DOXYGEN_OUTPUT))
} sim_clock_gate_name_kv11z7_t;
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
 * @brief Set OUTDIV5EN.
 *
 * This function sets divide value OUTDIV5EN.
 *
 * @param base Base address for current SIM instance.
 * @param setting  The value to set.
 */
static inline void CLOCK_HAL_SetOutDiv5ENCmd(SIM_Type * base, bool setting)
{
    SIM_BWR_CLKDIV1_OUTDIV5EN(base, setting);
}

/*!
 * @brief Get OUTDIV5EN.
 *
 * This function gets divide value OUTDIV5EN.
 *
 * @param base Base address for current SIM instance.
 * @return Current divide value.
 */
static inline bool CLOCK_HAL_GetOutDiv5ENCmd(SIM_Type * base)
{
    return SIM_BRD_CLKDIV1_OUTDIV5EN(base);
}

/*!
 * @brief Set OUTDIV5.
 *
 * This function sets divide value OUTDIV5.
 *
 * @param base Base address for current SIM instance.
 * @param setting  The value to set.
 */
static inline void CLOCK_HAL_SetOutDiv5(SIM_Type * base, uint8_t setting)
{
    SIM_BWR_CLKDIV1_OUTDIV5(base, setting);
}

/*!
 * @brief Get OUTDIV5.
 *
 * This function gets divide value OUTDIV5.
 *
 * @param base Base address for current SIM instance.
 * @return Current divide value.
 */
static inline uint8_t CLOCK_HAL_GetOutDiv5(SIM_Type * base)
{
    return SIM_BRD_CLKDIV1_OUTDIV5(base);
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
 * @brief Sets the ADC ALT clock source selection setting.
 *
 * This function sets the ADC ALT clock source selection setting.
 *
 * @param base     Base address for current SIM instance.
 * @param instance     ADC module instance.
 * @param adcAltSrcSel     ADC ALT clock source.
 */
void CLOCK_HAL_SetAdcAltClkSrc(SIM_Type * base, uint32_t instance, clock_adc_alt_src_t adcAltSrcSel);

/*!
 * @brief Gets the ADC ALT clock source selection setting.
 *
 * This function gets the ADC ALT clock source selection setting.
 *
 * @param base     Base address for current SIM instance.
 * @param instance     ADC module instance.
 * @return             the ADC ALT clock source selection.
 */
clock_adc_alt_src_t CLOCK_HAL_GetAdcAltClkSrc(SIM_Type * base, uint32_t instance);

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
 * @brief Sets the ADCx alternate trigger select setting.
 *
 * This function selects the alternative conversion triggers for ADCx.
 *
 * @param base     Base address for current SIM instance.
 * @param instance     device instance.
 * @param select alternative conversion triggers for ADCx
 */
void SIM_HAL_SetAdcAlternativeTriggerMode(SIM_Type * base,
                                         uint32_t instance,
                                         sim_adc_alttrg_sel_t select);

/*!
 * @brief Gets the ADCx alternate trigger select setting.
 *
 * This function gets the ADCx alternate trigger select setting.
 *
 * @param base     Base address for current SIM instance.
 * @param instance     device instance.
 * @return selected ADCx alternate trigger select setting
 */
sim_adc_alttrg_sel_t SIM_HAL_GetAdcAlternativeTriggerMode(SIM_Type * base, uint32_t instance);

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
 * This function sets ADC alternate trigger mode, pre-trigger mode and trigger mode.
 *
 * @param base     Base address for current SIM instance.
 * @param instance     device instance.
 * @param altTrigSel   Alternative trigger mode.
 * @param preTrigSel   Pre-trigger mode.
 * @param trigSel      Trigger mode.
*/
void SIM_HAL_SetAdcTriggerModeOneStep(SIM_Type * base,
                                      uint32_t instance,
                                      sim_adc_alttrg_sel_t altTrigSel,
                                      sim_adc_pretrg_sel_t preTrigSel,
                                      sim_adc_trg_sel_t trigSel);

/*!
 *
 * @brief WDOG Clock Select
 *
 * This function selects the clock source of the WDOG2008 watchdog.
 * 
 * @param base Base address for current SIM instance.
 * @param select:
 * 0 Internal 1 kHz clock is source to WDOG2008
 * 1 MCGIRCLK is source to WDOG2008
 *
 *END**************************************************************************/
void SIM_HAL_SetWdogClkSrc(SIM_Type* base, bool select);

/*!
 *
 * @brief Get WDOG Clock Src
 *
 * This function gets the clock source of the WDOG2008 watchdog.
 * 
 * @param base Base address for current SIM instance.
 * @return select:
 * 0 Internal 1 kHz clock is source to WDOG2008
 * 1 MCGIRCLK is source to WDOG2008
 *
 *END**************************************************************************/
bool SIM_HAL_GetWdogClkSrc(SIM_Type* base);

/*!
 * @brief Sets the UARTx open drain enable setting.
 *
 * This function enables/disables open drain for UARTx.
 *
 * @param base     Base address for current SIM instance.
 * @param instance     device instance.
 * @param enable Enable open drain for UARTx
 *               - true:  Open drain is enabled.
 *               - false: Open drain is disabled.
 */
void SIM_HAL_SetUartOpenDrainMode(SIM_Type * base,
                                  uint32_t instance,
                                  bool enable);

/*!
 * @brief Gets the UARTx open drain enable setting.
 *
 * This function Gets the UARTx open drain enable setting for UARTx.
 *
 * @param base     Base address for current SIM instance.
 * @param instance     device instance.
 * @return UARTx open drain setting
 */
bool SIM_HAL_GetUartOpenDrainMode(SIM_Type * base, uint32_t instance);

/*!
 * @brief Sets the UARTx receive data source select setting.
 *
 * This function  selects the source for the UARTx receive data.
 *
 * @param base     Base address for current SIM instance.
 * @param instance     device instance.
 * @param select the source for the UARTx receive data
 */
void SIM_HAL_SetUartRxSrcMode(SIM_Type * base,
                              uint32_t instance,
                              sim_uart_rxsrc_t select);

/*!
 * @brief Gets the UARTx receive data source select setting.
 *
 * This function  gets the UARTx receive data source select setting.
 *
 * @param base     Base address for current SIM instance.
 * @param instance     device instance.
 * @return select UARTx receive data source select setting
 */
sim_uart_rxsrc_t SIM_HAL_GetUartRxSrcMode(SIM_Type * base, uint32_t instance);

/*!
 * @brief Sets the UARTx transmit data source select setting.
 *
 * This function  selects the source for the UARTx transmit data.
 *
 * @param base     Base address for current SIM instance.
 * @param instance     device instance.
 * @param select the source for the UARTx transmit data
 */
void SIM_HAL_SetUartTxSrcMode(SIM_Type * base,
                              uint32_t instance,
                              sim_uart_txsrc_t select);

/*!
 * @brief Gets the UARTx transmit data source select setting.
 *
 * This function  gets the UARTx transmit data source select setting.
 *
 * @param base     Base address for current SIM instance.
 * @param instance     device instance.
 * @return select UARTx transmit data source select setting
 */
sim_uart_txsrc_t SIM_HAL_GetUartTxSrcMode(SIM_Type * base, uint32_t instance);

/*!
 * @brief Sets the FTM Fixed clock source selection setting.
 *
 * This function sets the FTM Fixed clock source selection setting.
 *
 * @param base     Base address for current SIM instance.
 * @param ftmFixedFreqSel     FTM Fixed clock source.
 */
static inline void CLOCK_HAL_SetFtmFixFreqClkSrc(SIM_Type * base, clock_ftm_fixedfreq_src_t ftmFixedFreqSel)
{
    assert(ftmFixedFreqSel < 3);
    SIM_BWR_SOPT2_FTMFFCLKSEL(base, ftmFixedFreqSel);
}

/*!
 * @brief Gets the FTM Fixed clock source selection setting.
 *
 * This function gets the FTM Fixed clock source selection setting.
 *
 * @param base     Base address for current SIM instance.
 * @return             the FTM Fixed clock source selection.
 */
static inline clock_ftm_fixedfreq_src_t CLOCK_HAL_GetFtmFixFreqClkSrc(SIM_Type * base)
{
    return (clock_ftm_fixedfreq_src_t)SIM_BRD_SOPT2_FTMFFCLKSEL(base);
}

/*!
 * @brief Sets the FlexTimer x hardware trigger y source select setting.
 *
 * This function  selects  the source of FTMx hardware trigger y.
 *
 * @param base     Base address for current SIM instance.
 * @param instance     device instance.
 * @param trigger      hardware trigger y
 * @param select FlexTimer x hardware trigger y
 *               - 0: Pre-trigger A selected for ADCx.
 *               - 1: Pre-trigger B selected for ADCx.
 */
void SIM_HAL_SetFtmTriggerSrcMode(SIM_Type * base,
                                  uint32_t instance,
                                  uint8_t trigger,
                                  sim_ftm_trg_src_t select);

/*!
 * @brief Gets the FlexTimer x hardware trigger y source select setting.
 *
 * This function  gets the FlexTimer x hardware trigger y source select setting.
 *
 * @param base     Base address for current SIM instance.
 * @param instance     device instance.
 * @param trigger      hardware trigger y
 * @return select FlexTimer x hardware trigger y source select setting
 */
sim_ftm_trg_src_t SIM_HAL_GetFtmTriggerSrcMode(SIM_Type * base,
                                               uint32_t instance,
                                               uint8_t trigger);

/*!
 * @brief Sets the FlexTimer x external clock pin select setting.
 *
 * This function  selects the source of FTMx external clock pin select.
 *
 * @param base     Base address for current SIM instance.
 * @param instance     device instance.
 * @param select FTMx external clock pin select
 *               - 0: FTMx external clock driven by FTM CLKIN0 pin.
 *               - 1: FTMx external clock driven by FTM CLKIN1 pin.
 */
void SIM_HAL_SetFtmExternalClkPinMode(SIM_Type * base,
                                      uint32_t instance,
                                      sim_ftm_clk_sel_t select);

/*!
 * @brief Gets the FlexTimer x external clock pin select setting.
 *
 * This function gets the FlexTimer x external clock pin select setting.
 *
 * @param base     Base address for current SIM instance.
 * @param instance     device instance.
 * @return select FlexTimer x external clock pin select setting
 */
sim_ftm_clk_sel_t SIM_HAL_GetFtmExternalClkPinMode(SIM_Type * base,
                                                   uint32_t instance);

/*!
 * @brief Sets the FlexTimer x channel y input capture source select setting.
 *
 * This function  selects the FlexTimer x channel y input capture source.
 *
 * @param base     Base address for current SIM instance.
 * @param instance     device instance.
 * @param channel      FlexTimer channel y
 * @param select FlexTimer x channel y input capture source
 */
void SIM_HAL_SetFtmChSrcMode(SIM_Type * base,
                             uint32_t instance,
                             uint8_t channel,
                             sim_ftm_ch_src_t select);

/*!
 * @brief Gets the FlexTimer x channel y input capture source select setting.
 *
 * This function gets the FlexTimer x channel y input capture
 * source select setting.
 *
 * @param base     Base address for current SIM instance.
 * @param instance     device instance.
 * @param channel      FlexTimer channel y
 * @return select FlexTimer x channel y input capture source select setting
 */
sim_ftm_ch_src_t SIM_HAL_GetFtmChSrcMode(SIM_Type * base,
                                         uint32_t instance,
                                         uint8_t channel);
   
/*!
 * @brief Sets the Carrier frequency selection for FTM0/2/3/4 output channel.
 *
 * This function  Sets the Carrier frequency selection for FTM0/2/3/4 output channel.
 *
 * @param base     Base address for current SIM instance.
 * @param instance     device instance.
 * @param select       Carrier frequency source select.
 *          - 0 :      FTM1_CH1 output provides the carrier signal.
 *          - 1 :      LPTMR0 pre-scaler output provides the carrier signal.
 *          - 2 :      FTM5_CH1 pre-scaler output provides the carrier signal.
 */
static inline void SIM_HAL_SetFtmCarrierFreqMode(SIM_Type * base,
                                                 uint32_t instance,
                                                 sim_ftm_flt_carrier_sel_t select)
{
    assert ((0U==instance) || (2U==instance) || (3U==instance) || (4U==instance));
    
    if(instance < 3) {
      SIM_BWR_SOPT8_CARRIER_SELECT0(base, select);
    }
    else {
      SIM_BWR_SOPT9_CARRIER_SELECT1(base, select);
    }
}

/*!
 * @brief Gets the Carrier frequency selection for FTM0/2 output channel.
 *
 * This function gets Carrier frequency selection setting for FTM0/2 output channel.
 *
 * @param base     Base address for current SIM instance.
 * @param instance     device instance.
 * @return             Carrier frequency selection.
 */
static inline sim_ftm_flt_carrier_sel_t SIM_HAL_GetFtmCarrierFreqMode(SIM_Type * base,
                                                                      uint32_t instance)
{
    assert ((0U==instance) || (2U==instance) || (3U==instance) || (4U==instance));
    
    if(instance < 3) {
      return (sim_ftm_flt_carrier_sel_t)SIM_BRD_SOPT8_CARRIER_SELECT0(base);
    }
    else {
      return (sim_ftm_flt_carrier_sel_t)SIM_BRD_SOPT9_CARRIER_SELECT1(base);
    }
} 
  
/*!
 * @brief Sets the FlexTimer x channel y output source select setting.
 *
 * This function  selects the FlexTimer x channel y output source.
 *
 * @param base     Base address for current SIM instance.
 * @param instance     device instance.
 * @param channel      FlexTimer channel y
 * @param select FlexTimer x channel y output source
 */
void SIM_HAL_SetFtmChOutSrcMode(SIM_Type * base,
                                uint32_t instance,
                                uint8_t channel,
                                sim_ftm_ch_out_src_t select);

/*!
 * @brief Gets the FlexTimer x channel y output source select setting.
 *
 * This function gets the FlexTimer x channel y output
 * source select setting.
 *
 * @param base     Base address for current SIM instance.
 * @param instance     device instance.
 * @param channel      FlexTimer channel y
 * @return select FlexTimer x channel y output source select setting
 */
sim_ftm_ch_out_src_t SIM_HAL_GetFtmChOutSrcMode(SIM_Type * base,
                                                uint32_t instance,
                                                uint8_t channel);

/*!
 * @brief Set FlexTimer x hardware trigger 0 software synchronization.
 *
 * This function sets FlexTimer x hardware trigger 0 software synchronization.
 * FTMxSYNCBIT.
 *
 * @param base     Base address for current SIM instance.
 * @param instance     device instance.
 * @param sync         Synchronize or not.
 */
void SIM_HAL_SetFtmSyncCmd(SIM_Type * base, uint32_t instance, bool sync);

/*!
 * @brief Get FlexTimer x hardware trigger 0 software synchronization setting.
 *
 * This function gets FlexTimer x hardware trigger 0 software synchronization.
 * FTMxSYNCBIT.
 *
 * @param base     Base address for current SIM instance.
 * @param instance     device instance.
 * @return synchronization setting
 */
static inline bool SIM_HAL_GetFtmSyncCmd(SIM_Type * base, uint32_t instance)
{
    assert (instance < FTM_INSTANCE_COUNT);
    return (bool)(SIM_RD_SOPT8(base) & (1U<<instance));
}                                         
                                         
  
/*!
 * @brief Sets the FlexTimer x fault y select setting.
 *
 * This function  sets the FlexTimer x fault y select setting.
 *
 * @param base     Base address for current SIM instance.
 * @param instance     device instance.
 * @param fault        fault y
 * @param select FlexTimer x fault y select setting
 *               - 0: FlexTimer x fault y select 0.
 *               - 1: FlexTimer x fault y select 1.
 */
void SIM_HAL_SetFtmFaultSelMode(SIM_Type * base,
                                uint32_t instance,
                                uint8_t fault,
                                sim_ftm_flt_sel_t select);

/*!
 * @brief Gets the FlexTimer x fault y select setting.
 *
 * This function  gets the FlexTimer x fault y select setting.
 *
 * @param base     Base address for current SIM instance.
 * @param instance     device instance.
 * @param fault        fault y
 * @return select FlexTimer x fault y select setting
 */
sim_ftm_flt_sel_t SIM_HAL_GetFtmFaultSelMode(SIM_Type * base,
                                             uint32_t instance,
                                             uint8_t fault);

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
    return SIM_BRD_SDID_SERIERID(base);
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
 * @brief Gets the Kinetis SbuFam ID in System Device ID register (SIM_SDID).
 *
 * This function  gets the Kinetis SubFam ID in System Device ID register.
 *
 * @param base     Base address for current SIM instance.
 * @return id Kinetis SubFam ID
 */
static inline uint32_t SIM_HAL_GetSubFamId(SIM_Type * base)
{
    return SIM_BRD_SDID_SUBFAMID(base);
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
 * @brief Gets the Kinetis SRAMSIZE ID in the System Device ID register (SIM_SDID).
 *
 * This function  gets the Kinetis SRAMSIZE ID in System Device ID register.
 *
 * @param base     Base address for current SIM instance.
 * @return id Kinetis SRAMSIZE ID
 */
static inline uint32_t SIM_HAL_GetSramSizeId(SIM_Type * base)
{
    return SIM_BRD_SDID_SRAMSIZE(base);
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
 * @brief Gets the Flash maximum address block in the Flash Configuration Register 1  (SIM_FCFG).
 *
 * This function gets the Flash maximum block in Flash Configuration Register 2.
 *
 * @param base     Base address for current SIM instance.
 * @return address Flash maximum block address
 */
static inline uint32_t SIM_HAL_GetFlashMaxAddrBlock(SIM_Type * base)
{
    return SIM_BRD_FCFG2_MAXADDR(base);
}


#if defined(__cplusplus)
}
#endif /* __cplusplus*/

/*! @}*/

#endif /* __FSL_SIM_HAL_KV11Z7_H__ */
/*******************************************************************************
 * EOF
 ******************************************************************************/

