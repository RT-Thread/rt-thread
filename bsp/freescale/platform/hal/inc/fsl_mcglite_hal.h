/*
* Copyright (c) 2014-2015, Freescale Semiconductor, Inc.
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

#if !defined(__FSL_MCGLITE_HAL_H__)
#define __FSL_MCGLITE_HAL_H__

#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include "fsl_device_registers.h"
#if FSL_FEATURE_SOC_MCGLITE_COUNT

/*! @addtogroup mcglite_hal*/
/*! @{*/

/*! @file fsl_mcglite_hal.h */

/*******************************************************************************
* Definitions
******************************************************************************/
extern uint32_t g_xtalRtcClkFreq;         /* EXTAL RTC clock */
extern uint32_t g_xtal0ClkFreq;           /* EXTAL0 clock */

/*! @brief MCG_Lite constant definitions. */
enum _mcglite_constant
{
    kMcgliteConst0   =          0U,
    kMcgliteConst2M  =    2000000U,
    kMcgliteConst8M  =    8000000U,
    kMcgliteConst48M =   48000000U,
};

/*! @brief MCG_Lite clock source selection. */
typedef enum _mcglite_mcgoutclk_source
{
    kMcgliteClkSrcHirc,      /*!< MCGOUTCLK source is HIRC */
    kMcgliteClkSrcLirc,      /*!< MCGOUTCLK source is LIRC */
    kMcgliteClkSrcExt,       /*!< MCGOUTCLK source is external clock source */
    kMcgliteClkSrcReserved
} mcglite_mcgoutclk_source_t;

/*! @brief MCG_Lite LIRC select. */
typedef enum _mcglite_lirc_select
{
    kMcgliteLircSel2M,          /*!< slow internal reference(LIRC) 2 MHz clock selected */
    kMcgliteLircSel8M,          /*!< slow internal reference(LIRC) 8 MHz clock selected */
} mcglite_lirc_select_t;

/*! @brief MCG_Lite divider factor selection for clock source*/
typedef enum _mcglite_lirc_div
{
    kMcgliteLircDivBy1 = 0U,          /*!< divider is 1 */
    kMcgliteLircDivBy2 ,              /*!< divider is 2 */
    kMcgliteLircDivBy4 ,              /*!< divider is 4 */
    kMcgliteLircDivBy8 ,              /*!< divider is 8 */
    kMcgliteLircDivBy16,              /*!< divider is 16 */
    kMcgliteLircDivBy32,              /*!< divider is 32 */
    kMcgliteLircDivBy64,              /*!< divider is 64 */
    kMcgliteLircDivBy128              /*!< divider is 128 */
} mcglite_lirc_div_t;

/*! @brief MCG_Lite external clock Select */
typedef enum _osc_src
{
    kOscSrcExt,                /*!< Selects external input clock */
    kOscSrcOsc                 /*!< Selects Oscillator  */
} osc_src_t;

/*! @brief MCG frequency range select */
typedef enum _osc_range
{
    kOscRangeLow,         /*!< Low frequency range selected for the crystal OSC */
    kOscRangeHigh,        /*!< High frequency range selected for the crystal OSC */
    kOscRangeVeryHigh,    /*!< Very High frequency range selected for the crystal OSC */
    kOscRangeVeryHigh1    /*!< Very High frequency range selected for the crystal OSC */
} osc_range_t;

/*! @brief MCG high gain oscillator select */
typedef enum _osc_gain
{
    kOscGainLow,               /*!< Configure crystal oscillator for low-power operation */
    kOscGainHigh               /*!< Configure crystal oscillator for high-gain operation */
} osc_gain_t;

/*******************************************************************************
* API
******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus*/

/*! @name MCG_Lite output clock access API*/
/*@{*/

/*!
* @brief Gets the current MCGPCLK frequency.
*
* This function returns the MCGPCLK frequency (Hertz) based on
* the current MCG_Lite configurations and settings. The configuration should be
* properly done in order to get the valid value.
*
* @param base MCG_Lite register base address.
*
* @return Frequency value in Hertz of MCGPCLK.
*/
uint32_t CLOCK_HAL_GetPeripheralClk(MCG_Type * base);

/*!
* @brief Gets the current MCG_Lite low internal reference clock(2 MHz or 8 MHz)
*
* This function returns the MCG_Lite LIRC frequency (Hertz) based
* on the current MCG_Lite configurations and settings. Ensure that the LIRC
* has been properly configured to get the valid value.
*
* @param base MCG_Lite register base address.
*
* @return Frequency value in Hertz of the MCG_Lite LIRC.
*/
uint32_t CLOCK_HAL_GetLircClk(MCG_Type * base);

/*!
* @brief Gets the current MCG_Lite LIRC_DIV1_CLK frequency.
*
* This function returns the MCG_Lite LIRC_DIV1_CLK frequency (Hertz) based
* on the current MCG_Lite configurations and settings. Ensure that the LIRC
* has been properly configured to get the valid value.
*
* @param base MCG_Lite register base address.
*
* @return Frequency value in Hertz of the MCG_Lite LIRC_DIV1_CLK.
*/
uint32_t CLOCK_HAL_GetLircDiv1Clk(MCG_Type * base);

/*!
* @brief Gets the current MCGIRCLK frequency.
*
* This function returns the MCGIRCLK frequency (Hertz) based
* on the current MCG_Lite configurations and settings. Ensure that the LIRC
* has been properly configured to get the valid value.
*
* @param base MCG_Lite register base address.
*
* @return Frequency value in Hertz of MCGIRCLK.
*/
uint32_t CLOCK_HAL_GetInternalRefClk(MCG_Type * base);

/*!
* @brief Gets the current MCGOUTCLK frequency.
*
* This function returns the MCGOUTCLK frequency (Hertz) based on
* the current MCG_Lite configurations and settings. The configuration should be
* properly done to get the valid value.
*
* @param base MCG_Lite register base address.
*
* @return Frequency value in Hertz of MCGOUTCLK.
*/
uint32_t CLOCK_HAL_GetOutClk(MCG_Type * base);

/*@}*/

/*! @name MCG_Lite control register access API*/
/*@{*/

/*!
* @brief Sets the Low Internal Reference Select.
*
* This function sets the LIRC to work at 2 MHz or 8 MHz.
*
* @param base MCG_Lite register base address.
*
* @param select 2MHz or 8MHz.
*/
static inline void CLOCK_HAL_SetLircSelMode(MCG_Type * base, mcglite_lirc_select_t select)
{
    MCG_BWR_C2_IRCS(base, select);
}

/*!
* @brief Sets the low internal reference divider 1.
*
* This function sets the low internal reference divider 1, the register FCRDIV.
*
* @param base MCG_Lite register base address.
*
* @param setting LIRC divider 1 setting value.
*/
static inline void CLOCK_HAL_SetLircRefDiv(MCG_Type * base, mcglite_lirc_div_t setting)
{
    MCG_BWR_SC_FCRDIV(base, setting);
}

/*!
* @brief Sets the low internal reference divider 2.
*
* This function sets the low internal reference divider 2.
*
* @param base MCG_Lite register base address.
*
* @param setting LIRC divider 2 setting value.
*/
static inline void CLOCK_HAL_SetLircDiv2(MCG_Type * base, mcglite_lirc_div_t setting)
{
    MCG_BWR_MC_LIRC_DIV2(base, setting);
}

/*!
* @brief Enables the Low Internal Reference Clock setting
*
* This function enables/disables the low internal reference clock.
*
* @param base MCG_Lite register base address.
*
* @param enable Enable or disable internal reference clock.
*                 - true: MCG_Lite Low IRCLK active
*                 - false: MCG_Lite Low IRCLK inactive
*/
static inline void CLOCK_HAL_SetLircCmd(MCG_Type * base, bool enable)
{
    MCG_BWR_C1_IRCLKEN(base, enable);
}

/*!
* @brief Sets the Low Internal Reference Clock disabled or not in STOP mode.
*
* This function controls whether or not the low internal reference clock remains
* enabled when the MCG_Lite enters STOP mode.
*
* @param base MCG_Lite register base address.
*
* @param enable Enable or disable low internal reference clock stop setting.
*                 - true: Internal reference clock is enabled in stop mode if IRCLKEN is set
before entering STOP mode.
*                 - false: Low internal reference clock is disabled in STOP mode
*/
static inline void CLOCK_HAL_SetLircStopCmd(MCG_Type * base, bool enable)
{
    MCG_BWR_C1_IREFSTEN(base, enable);
}

/*!
* @brief Enable or disable the High Internal Reference Clock setting.
*
* This function enables/disables the internal reference clock for use as MCGPCLK.
*
* @param base MCG_Lite register base address.
*
* @param enable Enable or disable HIRC.
*                 - true: MCG_Lite HIRC active
*                 - false: MCG_Lite HIRC inactive
*/
static inline void CLOCK_HAL_SetHircCmd(MCG_Type * base, bool enable)
{
    MCG_BWR_MC_HIRCEN(base, enable);
}

/*!
* @brief Sets the External Reference Select.
*
* This function selects the source for the external reference clock.
* Refer to the Oscillator (OSC) for more details.
*
* @param base MCG_Lite register base address.
*
* @param select  External Reference Select.
*                 - 0: External input clock requested
*                 - 1: Crystal requested
*/
static inline void CLOCK_HAL_SetExtRefSelMode0(MCG_Type * base, osc_src_t select)
{
    MCG_BWR_C2_EREFS0(base, select);
}

/*!
* @brief Gets the Clock Mode Status.
*
* This function gets the Clock Mode Status. These bits indicate the current clock mode.
* The CLKST bits do not update immediately after a write to the CLKS bits because of the
* internal synchronization between clock domains.
*
* @param base MCG_Lite register base address.
*
* @return status  Clock Mode Status
*                  - 00: HIRC clock is select.
*                  - 01: LIRC(low Internal reference clock) is selected.
*                  - 10: External reference clock is selected.
*                  - 11: Reserved.
*/
static inline mcglite_mcgoutclk_source_t CLOCK_HAL_GetClkSrcStat(MCG_Type * base)
{
    return (mcglite_mcgoutclk_source_t)MCG_BRD_S_CLKST(base);
}

/*!
* @brief Gets the OSC Initialization Status.
*
* This function gets the OSC Initialization Status OSCINIT0. This bit,
* which resets to 0, is set to 1 after the initialization cycles of
* the crystal oscillator clock have completed. After being set, the bit
* is cleared to 0 if the OSC is subsequently disabled. See
* the OSC module's detailed description for more information.
*
* @param base MCG_Lite register base address.
*
* @return OSC initialization status
*/
static inline bool CLOCK_HAL_IsOscStable(MCG_Type * base)
{
    return (bool)MCG_BRD_S_OSCINIT0(base);
}

#if FSL_FEATURE_MCGLITE_HAS_RANGE0
/*!
 * @brief Sets the Frequency Range0 Select Setting.
 *
 * This function  selects the frequency range for the OSC crystal oscillator
 * or an external clock source. See the Oscillator chapter for more details and
 * the device data sheet for the frequency ranges used.
 *
 * @param base MCG_Lite register base address.
 * @param setting  Frequency Range0 Select Setting
 *                  - 00: Low frequency range selected for the crystal oscillator.
 *                  - 01: High frequency range selected for the crystal oscillator.
 *                  - 1X: Very high frequency range selected for the crystal oscillator.
 */
static inline void CLOCK_HAL_SetRange0Mode(MCG_Type * base, osc_range_t setting)
{
    MCG_BWR_C2_RANGE0(base, setting);
}
#endif

#if FSL_FEATURE_MCGLITE_HAS_HGO0
/*!
 * @brief Sets the High Gain Oscillator0 Select Setting.
 *
 * This function controls the OSC0 crystal oscillator mode of operation.
 * See the Oscillator chapter for more details.
 *
 * @param base MCG_Lite register base address.
 * @param setting  High Gain Oscillator0 Select Setting
 *                  - 0: Configure crystal oscillator for low-power operation.
 *                  - 1: Configure crystal oscillator for high-gain operation.
 */
static inline void CLOCK_HAL_SetHighGainOsc0Mode(MCG_Type * base,
                                                 osc_gain_t setting)
{
    MCG_BWR_C2_HGO0(base, setting);
}
#endif

#if FSL_FEATURE_MCGLITE_HAS_HCTRIM
/*!
 * @brief Gets the High-frequency IRC coarse trim value.
 *
 * This function gets the High-frequency IRC coarse trim value.
 *
 * @param base MCG_Lite register base address.
 * @return The coarse trim value.
 */
static inline uint8_t CLOCK_HAL_GetHircCoarseTrim(MCG_Type * base)
{
    return MCG_BRD_HCTRIM_COARSE_TRIM(base);
}
#endif

#if FSL_FEATURE_MCGLITE_HAS_HTTRIM
/*!
 * @brief Gets the High-frequency IRC tempco trim value.
 *
 * This function gets the High-frequency IRC tempco trim value.
 *
 * @param base MCG_Lite register base address.
 * @return The tempco trim value.
 */
static inline uint8_t CLOCK_HAL_GetHircTempcoTrim(MCG_Type * base)
{
    return MCG_BRD_HTTRIM_TEMPCO_TRIM(base);
}
#endif

#if FSL_FEATURE_MCGLITE_HAS_HFTRIM
/*!
 * @brief Gets the High-frequency IRC fine trim value.
 *
 * This function gets the High-frequency IRC fine trim value.
 *
 * @param base MCG_Lite register base address.
 * @return The fine trim value.
 */
static inline uint8_t CLOCK_HAL_GetHircFineTrim(MCG_Type * base)
{
    return MCG_BRD_HFTRIM_FINE_TRIM(base);
}
#endif

#if FSL_FEATURE_MCGLITE_HAS_LTRIMRNG
/*!
 * @brief Gets the LIRC 8M TRIM RANGE value.
 *
 * This function gets the LIRC 8M RANGE value.
 *
 * @param base MCG_Lite register base address.
 * @return The trim range value.
 */
static inline uint8_t CLOCK_HAL_GetLirc8MTrimRange(MCG_Type * base)
{
    return MCG_BRD_LTRIMRNG_FTRIMRNG(base);
}

/*!
 * @brief Gets the LIRC 2M TRIM RANGE value.
 *
 * This function gets the LIRC 2M RANGE value.
 *
 * @param base MCG_Lite register base address.
 * @return The trim range value.
 */
static inline uint8_t CLOCK_HAL_GetLirc2MTrimRange(MCG_Type * base)
{
    return MCG_BRD_LTRIMRNG_STRIMRNG(base);
}
#endif

#if FSL_FEATURE_MCGLITE_HAS_LFTRIM
/*!
 * @brief Gets the LIRC 8M trim value.
 *
 * This function gets the LIRC 8M trim value.
 *
 * @param base MCG_Lite register base address.
 * @return The trim value.
 */
static inline uint8_t CLOCK_HAL_GetLirc8MTrim(MCG_Type * base)
{
    return MCG_BRD_LFTRIM_LIRC_FTRIM(base);
}
#endif

#if FSL_FEATURE_MCGLITE_HAS_LSTRIM
/*!
 * @brief Gets the LIRC 2M trim value.
 *
 * This function gets the LIRC 2M trim value.
 *
 * @param base MCG_Lite register base address.
 * @return The trim value.
 */
static inline uint8_t CLOCK_HAL_GetLirc2MTrim(MCG_Type * base)
{
    return MCG_BRD_LSTRIM_LIRC_STRIM(base);
}
#endif


/*@}*/

#if defined(__cplusplus)
}
#endif /* __cplusplus*/

/*! @}*/

#endif
#endif /* __FSL_MCGLITE_HAL_H__*/
/*******************************************************************************
* EOF
******************************************************************************/

