/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
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
#ifndef __FSL_CMT_HAL_H__
#define __FSL_CMT_HAL_H__
 
#include <assert.h>
#include <stdint.h>
#include <stdbool.h>
#include "fsl_device_registers.h"

/*!
 * @addtogroup cmt_hal
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*!
* @brief Error codes for the CMT driver.
*/
typedef enum _cmt_status
{
    kStatus_CMT_Success    = 0x00U,
    kStatus_CMT_Fail       = 0x01U,
    kStatus_CMT_Process    = 0x02U,
    kStatus_CMT_Done       = 0x03U
} cmt_status_t;

/*!
 * @brief The modes of CMT.
 */
typedef enum _cmt_mode 
{
    kCMTDirectIROCtl  =  0x00U, /*!< Carrier modulator is disabled and the IRO signal is directly in software control */
    kCMTTimeMode      =  0x01U, /*!< Carrier modulator is enabled in time mode. */
    kCMTFSKMode       =  0x05U, /*!< Carrier modulator is enabled in FSK mode. */
    kCMTBasebandMode  =  0x09U /*!< Carrier modulator is enabled in baseband mode. */      
} cmt_mode_t;

/*!
 * @brief The CMT macro definition for a specific value.
 */
typedef enum _cmt_int
{
    kCMTModeBitMask    =  0x0DU, /*!< CMT mode bit mask*/
    kCMTModulCountMask =  0xFFFF /*!< CMT modulator count mask. */
} cmt_int_t;


/*!
 * @brief The CMT clock divide primary prescaler.
 */
 typedef enum _cmt_primary_clkdiv
{
    kCMTPriClkDiv1  = 0U, /*!< The intermediate frequency is the bus clock divided by 1. */
    kCMTPriClkDiv2  = 1U, /*!< The intermediate frequency is the bus clock divided by 2. */
    kCMTPriClkDiv3  = 2U, /*!< The intermediate frequency is the bus clock divided by 3. */
    kCMTPriClkDiv4  = 3U, /*!< The intermediate frequency is the bus clock divided by 4. */
    kCMTPriClkDiv5  = 4U, /*!< The intermediate frequency is the bus clock divided by 5. */
    kCMTPriClkDiv6  = 5U, /*!< The intermediate frequency is the bus clock divided by 6. */
    kCMTPriClkDiv7  = 6U, /*!< The intermediate frequency is the bus clock divided by 7. */
    kCMTPriClkDiv8  = 7U, /*!< The intermediate frequency is the bus clock divided by 8. */
    kCMTPriClkDiv9  = 8U, /*!< The intermediate frequency is the bus clock divided by 9. */
    kCMTPriClkDiv10 = 9U, /*!< The intermediate frequency is the bus clock divided by 10. */
    kCMTPriClkDiv11 = 10U, /*!< The intermediate frequency is the bus clock divided by 11. */
    kCMTPriClkDiv12 = 11U, /*!< The intermediate frequency is the bus clock divided by 12. */
    kCMTPriClkDiv13 = 12U, /*!< The intermediate frequency is the bus clock divided by 13. */
    kCMTPriClkDiv14 = 13U, /*!< The intermediate frequency is the bus clock divided by 14. */
    kCMTPriClkDiv15 = 14U, /*!< The intermediate frequency is the bus clock divided by 15. */
    kCMTPriClkDiv16 = 15U /*!< The intermediate frequency is the bus clock divided by 16. */
} cmt_primary_clkdiv_t;

/*!
 * @brief The CMT clock divide secondary prescaler.
 */
 typedef enum _cmt_second_clkdiv
{
    kCMTSecClkDiv1 = 0U, /*!< The CMT clock is the intermediate frequency frequency divided by 1. */
    kCMTSecClkDiv2 = 1U, /*!< The CMT clock is the intermediate frequency frequency divided by 2. */
    kCMTSecClkDiv4 = 2U, /*!< The CMT clock is the intermediate frequency frequency divided by 4. */
    kCMTSecClkDiv8 = 3U /*!< The CMT clock is the intermediate frequency frequency divided by 8. */
} cmt_second_clkdiv_t;

/*!
 * @brief The CMT output polarity.
 */
 typedef enum _cmt_iro_polarity
{
    kCMTIROActiveLow   = 0U, /*!< The CMT IRO signal is active-low. */
    kCMTIROActiveHigh  = 1U /*!< The CMT IRO signal is active-high. */
} cmt_iro_polarity_t;

/*!
 * @brief The CMT IRO latch control.
 */
 typedef enum _cmt_iro_ctl
{
    kCMTIROCtlLow   = 0U, /*!< The CMT IRO signal is controlled to low. */
    kCMTIROCtlHigh  = 1U /*!< The CMT IRO signal is controlled to high. */
} cmt_iro_ctl_t;

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @name Initialization
 * @{
 */

/*!
 * @brief Initializes the CMT module.
 *
 * This function initializes the CMT module. All control and data settings
 * are cleared after initialization.
 *
 * @param base Base address for current CMT instance.
 */
void CMT_HAL_Init(CMT_Type * base);

/*!
 * @brief Selects the mode for CMT.
 *
 * This function selects the mode for CMT. The function is called
 * during CMT initialization. 
 *
 * @param base Base address for current CMT instance.
 * @param mode Selection of CMT feature mode enumeration. See to "cmt_mode_t".
 */
static inline void CMT_HAL_SetMode(CMT_Type * base, cmt_mode_t mode)
{ 
    uint8_t mscDate;
    mscDate = CMT_RD_MSC(base) & (uint8_t)(~ (uint8_t) kCMTModeBitMask); 
    CMT_WR_MSC(base, (mscDate | mode));   
}

/*!
 * @brief Gets the mode of the CMT module.
 *
 * This function gets the mode of the CMT module  .
 *
 * @param base Base address for current CMT instance.
 * @return The mode of CMT module, See to "cmt_mode_t".
 */
cmt_mode_t CMT_HAL_GetMode(CMT_Type * base);

/*!
 * @brief Enables the extended space operation for the CMT modulator.
 *
 * This function enables the extended space operation for the CMT modulator. It enlarges the space   
 * period for CMT and causes subsequent modulator cycles to be spaces for
 * the duration of the modulator. It should be used in the CMT time, baseband, or FSK mode.
 * This means it's valid when the CMT carrier generator and modulator is enabled.
 *
 * @param base Base address for current CMT instance.
 */
static inline void CMT_HAL_EnableExtendSpace(CMT_Type * base)
{ 
    CMT_BWR_MSC_EXSPC(base, 1);   
}

/*!
 * @brief Disables the extended space operation for the CMT modulator.
 *
 * This function disables the extended space operation for the CMT modulator. It can be used to
 * return the modulator to a standard operation when the extended space operation has been enabled.
 *
 * @param base Base address for current CMT instance.
 */
static inline void CMT_HAL_DisableExtendSpace(CMT_Type * base)
{ 
    CMT_BWR_MSC_EXSPC(base, 0);   
}

/*!
 * @brief Finds out whether the extended space feature is enabled.
 *
 * This function finds out whether the extended space is enabled for the CMT modulator. When the carrier generator and 
 * modulator is enabled, this function can be used to check whether the extended space feature is opened or not. 
 *
 * @param base Base address for the current CMT instance.
 * @return Current status of the extended space feature.
 *         - true:  the extended space feature is enabled. 
 *         - false: the extended space feature is disabled.
 */
static inline bool CMT_HAL_IsExtendSpace(CMT_Type * base)
{
    return CMT_BRD_MSC_EXSPC(base);
}


/* @} */

/*! 
 * @name Counters
 * @{
 */

/*!
 * @brief Sets the primary data set for the CMT carrier generator counter.
 *
 * This function sets the high time and low time of the primary data set for the CMT carrier generator counter
 * to control the period and the duty cycle of the output carrier signal. 
 * If the CMT clock period is Tcmt, The period of the carrier generator signal equals  
 * (highCount + lowCount) * Tcmt. The duty cycle equals  highCount / (highCount + lowCount).  
 *
 * @param base Base address for current CMT instance.
 * @param highCount The number of CMT clocks for carrier generator signal high time, integer in the range of 0 ~ 0xFF. 
 * @param lowCount The number of CMT clocks for carrier generator signal low time, integer in the range of 0 ~ 0xFF.
 */
static inline void CMT_HAL_SetCGCountOne(CMT_Type * base, uint32_t highCount, uint32_t lowCount)
{
    assert(highCount <= CMT_CGH1_PH_MASK);
    assert(highCount > 0);
    assert(lowCount <= CMT_CGL1_PL_MASK);
    assert(lowCount > 0);

    CMT_WR_CGH1(base, highCount);  
    CMT_WR_CGL1(base, lowCount);
}

/*!
 * @brief Sets the secondary data set for the CMT carrier generator counter.
 *
 * This function sets the high time and low time of the secondary data set CMT carrier generator counter
 * to control the period and the duty cycle of the output carrier signal. 
 * If the CMT clock period is Tcmt, The period of the carrier generator signal equals  
 * (highCount + lowCount) * Tcmt. The duty cycle equals  highCount / (highCount + lowCount). 
 * This data set is mainly used for FSK mode.
 *
 * @param base Base address for current CMT instance.
 * @param highCount The number of CMT clocks for carrier generator signal high time, integer in the range of 0 ~ 0xFF. 
 * @param lowCount The number of CMT clocks for carrier generator signal low time, integer in the range of 0 ~ 0xFF.
 */
static inline void CMT_HAL_SetCGCountTwo(CMT_Type * base, uint32_t highCount, uint32_t lowCount)
{
    assert(highCount <= CMT_CGH2_SH_MASK);
    assert(highCount > 0);
    assert(lowCount <= CMT_CGL2_SL_MASK);
    assert(lowCount > 0);

    CMT_WR_CGH2(base, highCount);  
    CMT_WR_CGL2(base, lowCount);
}


/*!
 * @brief Sets the modulation mark time period for the CMT modulator counter.
 *
 * This function sets the mark time period of the CMT modulator counter
 * to control the mark time of the output modulated signal from the carrier generator output signal. 
 * If the CMT clock frequency is Fcmt and the carrier out signal frequency is fcg: 
 *        - In Time and Baseband mode: The mark period of the generated signal equals (markCount + 1) / (Fcmt/8).
 *        - In FSK mode:The mark period of the generated signal equals (markCount + 1)/fcg.
 *
 * @param base Base address for current CMT instance.
 * @param markCount The number of clock period for CMT modulator signal mark period,
 *                   in the range of 0 ~ 0xFFFF. 
 */
static inline void CMT_HAL_SetModulateMarkCount(CMT_Type * base, uint32_t markCount)
{
    assert(markCount <= kCMTModulCountMask);

    CMT_WR_CMD1(base, markCount >> CMT_CMD1_MB_WIDTH);  
    CMT_WR_CMD2(base, markCount & CMT_CMD2_MB_MASK);
}



/*!
 * @brief Sets the modulation space time period for the CMT modulator counter.
 *
 * This function sets the mark time period of the CMT modulator counter
 * to control the space time of the output modulated signal from the carrier generator output signal. 
 * If the CMT clock frequency is Fcmt and the carrier out signal frequency is fcg: 
 *      - In Time and Baseband mode: The space period of the generated signal equals spaceCount / (Fcmt/8).  
 *      - In FSK mode:The space period of the generated signal equals spaceCount/fcg.
 *
 * @param base Base address for current CMT instance.
 * @param spaceCount The number of clock period for CMT modulator signal space period,
 *                   in the range of 0 ~ 0xFFFF. 
 */
static inline void CMT_HAL_SetModulateSpaceCount(CMT_Type * base, uint32_t spaceCount)
{
    assert(spaceCount <= kCMTModulCountMask);

    CMT_WR_CMD3(base, spaceCount >> CMT_CMD3_SB_WIDTH);  
    CMT_WR_CMD4(base, spaceCount & CMT_CMD4_SB_MASK);
}


/* @} */

/*!
 * @name Clock divider
 * @{
 */

/*!
 * @brief Configures the CMT clock by setting the clock divider.
 *
 * There are two prescalers with 8 MHz or higher frequency 
 * in the clock divider block for the CMT flexible clock frequency generation from the bus clock. 
 *
 * @param base Base address for current CMT instance.
 * @param ppsDiv The primary prescaler divider. ppsDiv should be a integer 
 *        range between 0 ~ 15 representing the divisor 1 ~ 16 (See "cmt_primary_clkdiv_t"). 
 *        It divides the bus clock to generate the Intermediate Frequency clock.
 *        The Intermediate frequency (IF) clock should be approximately
 *        8 MHz.
 *        For example, if the bus clock is 50 MHz, ppsDiv should be set to kCMTPriClkDivSix, 
 *        then IF = 50 MHz/6 = 8.333.333... .
 *        if the bus clock is 8 MHz, ppsDiv should be set to kCMTPriClkDivOne.
 * @param spsDiv The secondary prescaler divider. The CMT carrier generator resolution is 
 *        8Mhz/(2 ^ spsDiv) . spsDiv should be a integer range between
 *        0 ~ 3 representing the divisor 1,2,4 and 8 (See "cmt_second_clkdiv_t").
 */
static inline void CMT_HAL_SetClkByDiv(CMT_Type * base, cmt_primary_clkdiv_t ppsDiv, cmt_second_clkdiv_t spsDiv)
{
    CMT_BWR_PPS_PPSDIV(base, ppsDiv);
    CMT_BWR_MSC_CMTDIV(base, spsDiv);
}

/*!
 * @brief Gets the CMT primary clock divider.
 *
 * @param base Base address for current CMT instance.
 * @return The CMT primary clock divider.
 */
static inline cmt_primary_clkdiv_t CMT_HAL_GetPriClkDiv(CMT_Type * base)
{
    return (cmt_primary_clkdiv_t)CMT_BRD_PPS_PPSDIV(base);
}

/*!
 * @brief Gets the CMT secondary clock divider.
 *
 * @param base Base address for current CMT instance.
 * @return The CMT secondary clock divider.
 */
static inline cmt_second_clkdiv_t CMT_HAL_GetSecClkDiv(CMT_Type * base)
{
    return (cmt_second_clkdiv_t)CMT_BRD_MSC_CMTDIV(base);
}

/* @} */

/*!
 * @name Interrupt and DMA
 * @{
 */

/*!
 * @brief Enables or disables the CMT end of cycle interrupt.
 * 
 * If enabled, an interrupt occurs at the end of the modulator cycle or
 * when the CMT_HAL_IsEndofCycle returns true.
 * (Note: NVIC should be called to enable the CMT interrupt on the system level).
 *
 * @param base Base address for current CMT instance.
 * @param enable Enable or disable interrupt.
 *        - true:  CPU interrupt is enabled.
 *        - false: CPU interrupt is disabled.
 */
static inline void CMT_HAL_SetIntCmd(CMT_Type * base, bool enable)
{
    CMT_BWR_MSC_EOCIE(base, enable);
}

/*!
 * @brief Gets whether the CMT end of cycle interrupt is enabled or not.
 *
 * @param base Base address for current CMT instance.
 * @return Status of enabled or disabled interrupt
 *        - true: Interrupt is enabled.
 *        - false: Interrupt is disabled.
 */
static inline bool CMT_HAL_GetIntCmd(CMT_Type * base)
{
    return CMT_BRD_MSC_EOCIE(base);
}

/*!
 * @brief Reads the end of cycle status flag.
 * 
 * The flag is set: 
 *           - When the modulator is not currently active and carrier and modulator 
 *             is set to start the initial CMT transmission.  
 *           - At the end of each modulation cycle when the counter is reloaded and 
 *             the carrier and modulator are enabled.
 * @param base Base address for current CMT instance.
 * @return Current status of the end of cycle status flag
 *         - true:  End-of-cycle has occurred. 
 *         - false: End-of-cycle has not yet occurred since the flag last cleared. 
 */
static inline bool CMT_HAL_IsEndofCycle(CMT_Type * base)
{
    return CMT_BRD_MSC_EOCF(base);
}

/*!
 * @brief Enables or disables the DMA.
 * 
 * If enabled, a DMA transfer request occurs at the end of the modulator cycle
 * when the end-of-cycle interrupt is enabled.
 *
 * @param base Base address for current CMT instance.
 * @param enable Enable or disable DMA.
 *        - true:  DMA transfer request and done are enabled.
 *        - false: DMA transfer request and done are disabled.
 */
static inline void CMT_HAL_SetDMACmd(CMT_Type * base, bool enable)
{
    CMT_BWR_DMA_DMA(base, enable);
}

/*!
 * @brief Gets whether the DMA is enabled or not.
 * 
 * @param base Base address for current CMT instance.
 * @return Status of enabled or disabled DMA
 *        - true: DMA is enabled.
 *        - false: DMA is disabled.
 */
static inline bool CMT_HAL_GetDMACmd(CMT_Type * base)
{
    return CMT_BRD_DMA_DMA(base);
}


/* @} */

/*!
 * @name Output signal Control
 * @{
 */

/*!
 * @brief Controls the CMT output signal polarity.
 * 
 *
 * @param base Base address for current CMT instance.
 * @param polarVal The polarity of the IRO signal. See "cmt_iro_polarity_t"
 */
static inline void CMT_HAL_SetIroPol(CMT_Type * base, cmt_iro_polarity_t polarVal)
{
    CMT_BWR_OC_CMTPOL(base, polarVal);
}

/*!
 * @brief Enables or disables the IRO signal.
 * 
 * This function enables and disables the IRO signal. When the IRO signal is enabled, it is an output
 * that drives out either the CMT transmitter output or the state of IRO latch control
 * depending on whether the carrier modulator is enabled.
 *
 * @param base Base address for current CMT instance.
 * @param enable Enable or disable IRO signal.
 *        - true:  The IRO signal is enabled.
 *        - false: The IRO signal is disabled.
 */
static inline void CMT_HAL_SetIroCmd(CMT_Type * base, bool enable)
{
    CMT_BWR_OC_IROPEN(base, enable);
}


/*!
 * @brief Controls the IRO latch.
 * 
 * This function changes the states of the IRO signal when the kCMTDirectIROMode mode is set
 * and the IRO signal is enabled.
 *
 * @param base Base address for current CMT instance.
 * @param ctlVal The control of the IRO signal. See "cmt_iro_ctl_t"
 */
static inline void CMT_HAL_SetIroCtl(CMT_Type * base, cmt_iro_ctl_t ctlVal)
{
    CMT_BWR_OC_IROL(base, ctlVal);
}

/*!
 * @brief Reads the states of the IRO latch.
 * 
 *
 * @param base Base address for current CMT instance.
 * @return The states of the IRO latch
 */
static inline bool CMT_HAL_GetIrolatchState(CMT_Type * base)
{
    return CMT_BRD_OC_IROL(base);
}

/* @} */


#if defined(__cplusplus)
}
#endif
 
/*! @}*/
 
#endif /* __FSL_CMT_HAL_H__*/
/*******************************************************************************
* EOF
*******************************************************************************/

