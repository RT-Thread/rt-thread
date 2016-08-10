/*
 * Copyright (c) 2013, Freescale Semiconductor, Inc.
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
#if !defined(__FSL_MCG_HAL_MODES_H__)
#define __FSL_MCG_HAL_MODES_H__

#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include "fsl_mcg_hal.h"
#if FSL_FEATURE_SOC_MCG_COUNT

//! @addtogroup mcg_hal
//! @{

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

/*! @brief
 * Check parameter or not during MCG mode switching. It is recommend to enable
 * this macro when debug. After debug, disable this macro for code size
 * optimization.
 */
#define MCG_MODE_CHECK_PARAM 0

/*! @brief MCG mode definitions */
typedef enum _mcg_modes {
    kMcgModeFEI    = 0x01 << 0U,   /*!< FEI   - FLL Engaged Internal         */
    kMcgModeFBI    = 0x01 << 1U,   /*!< FBI   - FLL Bypassed Internal        */
    kMcgModeBLPI   = 0x01 << 2U,   /*!< BLPI  - Bypassed Low Power Internal  */
    kMcgModeFEE    = 0x01 << 3U,   /*!< FEE   - FLL Engaged External         */
    kMcgModeFBE    = 0x01 << 4U,   /*!< FBE   - FLL Bypassed External        */
    kMcgModeBLPE   = 0x01 << 5U,   /*!< BLPE  - Bypassed Low Power External  */
    kMcgModePBE    = 0x01 << 6U,   /*!< PBE   - PLL Bypassed External        */
    kMcgModePEE    = 0x01 << 7U,   /*!< PEE   - PLL Engaged External         */
#if (defined(FSL_FEATURE_MCG_HAS_PLL_INTERNAL_MODE) && FSL_FEATURE_MCG_HAS_PLL_INTERNAL_MODE)
    kMcgModePEI    = 0x01 << 8U,   /*!< PEI   - PLL Engaged Internal         */
    kMcgModePBI    = 0x01 << 9U,   /*!< PBI   - PLL Bypassed Internal        */
    kMcgModeSTOP   = 0x01 << 10U,  /*!< STOP  - Stop                         */
    kMcgModeError  = 0x01 << 11U   /*!< Unknown mode                         */
#else
    kMcgModeSTOP   = 0x01 << 8U,   /*!< STOP  - Stop                         */
    kMcgModeError  = 0x01 << 9U    /*!< Unknown mode                         */
#endif
} mcg_modes_t;

/*! @brief MCG mode transition API error code definitions */
typedef enum McgModeError {

    kMcgModeErrNone            = 0x00U,    /*!< No error. */
    kMcgModeErrModeUnreachable = 0x01U,    /*!< Target mode is unreachable. */

    /* Oscillator error codes */
    kMcgModeErrOscFreqRange    = 0x21U,    /*!< OSC frequency is invalid. */

    /* IRC and FLL error codes */
    kMcgModeErrIrcSlowRange    = 0x31U,    /*!< Slow IRC is outside the allowed range */
    kMcgModeErrIrcFastRange    = 0x32U,    /*!< Fast IRC is outside the allowed range */
    kMcgModeErrFllRefRange     = 0x33U,    /*!< FLL reference frequency is outside the allowed range */
    kMcgModeErrFllFrdivRange   = 0x34U,    /*!< FRDIV outside allowed range */
    kMcgModeErrFllDrsRange     = 0x35U,    /*!< DRS is out of range */
    kMcgModeErrFllDmx32Range   = 0x36U,    /*!< DMX32 setting not allowed. */

    /* PLL error codes */
    kMcgModeErrPllPrdivRange   = 0x41U,    /*!< PRDIV outside allowed range */
    kMcgModeErrPllVdivRange    = 0x42U,    /*!< VDIV outside allowed range */
    kMcgModeErrPllRefClkRange  = 0x43U,    /*!< PLL reference clock frequency, out of range */
    kMcgModeErrPllLockBit      = 0x44U,    /*!< LOCK or LOCK2 bit did not set */
    kMcgModeErrPllOutClkRange  = 0x45U,    /*!< PLL output frequency is outside allowed range.  */
    kMcgModeErrMax = 0x1000U
} mcg_mode_error_t;

////////////////////////////////////////////////////////////////////////////////
// API
////////////////////////////////////////////////////////////////////////////////

#if defined(__cplusplus)
extern "C" {
#endif // __cplusplus

/*!
 * @brief Gets the current MCG mode.
 *
 * This function checks the MCG registers and determine current MCG mode.
 *
 * @param       base  Base address for current MCG instance.
 * @return      Current MCG mode or error code mcg_modes_t
 */
mcg_modes_t CLOCK_HAL_GetMcgMode(MCG_Type * base);

/*!
 * @brief Sets the MCG to FEI mode.
 *
 * This function sets the MCG to FEI mode.
 *
 * @param       base  Base address for current MCG instance.
 * @param       drs       The DCO range selection.
 * @param       fllStableDelay Delay function to make sure FLL is stable.
 * @return      Error code
 */
mcg_mode_error_t CLOCK_HAL_SetFeiMode(MCG_Type * base,
                              mcg_dco_range_select_t drs,
                              void (* fllStableDelay)(void));

/*!
 * @brief Sets the MCG to FEE mode.
 *
 * This function sets the MCG to FEE mode.
 *
 * @param       base  Base address for current MCG instance.
 * @param       oscselval OSCSEL in FEE mode.
 * @param       frdivVal  FRDIV in FEE mode.
 * @param       dmx32     DMX32 in FEE mode.
 * @param       drs       The DCO range selection.
 * @param       fllStableDelay Delay function to make sure FLL is stable.
 * @return      Error code
 */
mcg_mode_error_t CLOCK_HAL_SetFeeMode(MCG_Type * base,
                              mcg_oscsel_select_t oscselVal,
                              uint8_t frdivVal,
                              mcg_dmx32_select_t dmx32,
                              mcg_dco_range_select_t drs,
                              void (* fllStableDelay)(void));

/*!
 * @brief Sets the MCG to FBI mode.
 *
 * This function sets the MCG to FBI mode.
 *
 * @param       base  Base address for current MCG instance.
 * @param       drs       The DCO range selection.
 * @param       ircselect The internal reference clock to select.
 * @param       fllStableDelay Delay function to make sure FLL is stable.
 * @return      Error code
 */
mcg_mode_error_t CLOCK_HAL_SetFbiMode(MCG_Type * base,
                              mcg_dco_range_select_t drs,
                              mcg_irc_mode_t ircSelect,
                              uint8_t fcrdivVal,
                              void (* fllStableDelay)(void));

/*!
 * @brief Sets the MCG to FBE mode.
 *
 * This function sets the MCG to FBE mode.
 *
 * @param       base  Base address for current MCG instance.
 * @param       oscselval OSCSEL in FEE mode.
 * @param       frdivVal  FRDIV in FEE mode.
 * @param       dmx32     DMX32 in FEE mode.
 * @param       drs       The DCO range selection.
 * @param       fllStableDelay Delay function to make sure FLL is stable.
 * @return      Error code
 */
mcg_mode_error_t CLOCK_HAL_SetFbeMode(MCG_Type * base,
                             mcg_oscsel_select_t oscselVal,
                             uint8_t frdivVal,
                             mcg_dmx32_select_t dmx32,
                             mcg_dco_range_select_t drs,
                             void (* fllStableDelay)(void));

/*!
 * @brief Sets the MCG to BLPI mode.
 *
 * This function sets the MCG to BLPI mode.
 *
 * @param       base  Base address for current MCG instance.
 * @param       ircselect The internal reference clock to select.
 * @return      Error code
 */
mcg_mode_error_t CLOCK_HAL_SetBlpiMode(MCG_Type * base,
                               uint8_t fcrdivVal,
                               mcg_irc_mode_t ircSelect);

/*!
 * @brief Sets the MCG to BLPE mode.
 *
 * This function sets the MCG to BLPE mode.
 *
 * @param       base  Base address for current MCG instance.
 * @param       oscselval OSCSEL in FEE mode.
 * @return      Error code
 */
mcg_mode_error_t CLOCK_HAL_SetBlpeMode(MCG_Type * base,
                               mcg_oscsel_select_t oscselVal);


#if (defined(FSL_FEATURE_MCG_HAS_PLL_INTERNAL_MODE) && FSL_FEATURE_MCG_HAS_PLL_INTERNAL_MODE)
/*!
 * @brief Sets the MCG to PBE mode.
 *
 * This function sets the MCG to PBE mode.
 *
 * @param       base  Base address for current MCG instance.
 * @param       oscselVal OSCSEL in PBE mode.
 * @param       pll32kRef PLL 32K reference source selection MCG_C7[PLL32KREFSEL].
 * @param       frdivVal  FRDIV in PBE mode.
 * @return      Error code
 */
mcg_mode_error_t CLOCK_HAL_SetPbeMode(MCG_Type * base,
                              mcg_oscsel_select_t oscselVal,
                              mcg_pll_ref_clock_source_t pll32kRef,
                              uint8_t frdivVal);
#else
/*!
 * @brief Sets the MCG to PBE mode.
 *
 * This function sets the MCG to PBE mode.
 *
 * @param       base  Base address for current MCG instance.
 * @param       oscselVal OSCSEL in PBE mode.
 * @param       pllcsSelect  PLLCS in PBE mode.
 * @param       prdivVal  PRDIV in PBE mode.
 * @param       vdivVal   VDIV in PBE mode.
 * @return      Error code
 */
mcg_mode_error_t CLOCK_HAL_SetPbeMode(MCG_Type * base,
                              mcg_oscsel_select_t oscselVal,
                              mcg_pll_clk_select_t pllcsSelect,
                              uint8_t prdivVal,
                              uint8_t vdivVal);
#endif

/*!
 * @brief Sets the MCG to PBE mode.
 *
 * This function sets the MCG to PBE mode.
 *
 * @param       base  Base address for current MCG instance.
 * @return      Error code
 * @note        This function only change CLKS to use PLL/FLL output. If the
 *              PRDIV/VDIV are different from PBE mode, please setup these
 *              settings in PBE mode and wait for stable then switch to PEE mode.
 */
mcg_mode_error_t CLOCK_HAL_SetPeeMode(MCG_Type * base);

#if (defined(FSL_FEATURE_MCG_HAS_PLL_INTERNAL_MODE) && FSL_FEATURE_MCG_HAS_PLL_INTERNAL_MODE)
/*!
 * @brief Sets the MCG to PEI mode.
 *
 * This function sets the MCG to PEI mode.
 *
 * @param       base  Base address for current MCG instance.
 * @param       ircSelect The internal reference clock to select.
 * @param       fcrdivVal The external reference clock divider MCG_C1[FRDIV].
 * @return      Error code
 */
mcg_mode_error_t CLOCK_HAL_SetPbiMode(MCG_Type * base,
                                      mcg_irc_mode_t ircSelect,
                                      uint8_t fcrdivVal);

/*!
 * @brief Sets the MCG to PEI mode.
 *
 * This function sets the MCG to PEI mode.
 *
 * @param       base  Base address for current MCG instance.
 * @return      Error code
 */
mcg_mode_error_t CLOCK_HAL_SetPeiMode(MCG_Type * base);
#endif

#if defined(__cplusplus)
}
#endif // __cplusplus

//! @}

#endif
#endif // __FSL_MCG_HAL_MODES_H__
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
