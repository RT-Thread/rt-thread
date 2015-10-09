/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
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
#ifndef __FSL_WDOG_HAL_H__
#define __FSL_WDOG_HAL_H__

#include <assert.h>
#include <stdint.h>
#include <stdbool.h>
#include "fsl_device_registers.h"
#if FSL_FEATURE_SOC_WDOG_COUNT

/*! 
 * @addtogroup wdog_hal
 * @{
 */

/*******************************************************************************
 * Definitions
 *******************************************************************************/

/*! @brief Describes WDOG clock source structure */
typedef enum _wdog_clk_src
{
    kWdogLpoClkSrc       = 0U,  /*!< WDOG clock sourced from the LPO @internal gui name="LPO clock" */
    kWdogAlternateClkSrc = 1U   /*!< WDOG clock sourced from the alternate clock source @internal gui name="Bus clock" */
}wdog_clk_src_t;

/*! @brief Describes WDOG work mode structure */
typedef struct _wdog_work_mode
{
#if FSL_FEATURE_WDOG_HAS_WAITEN
    bool kWdogEnableInWaitMode;   /*!< Enables or disables WDOG in wait mode  */
#endif
    bool kWdogEnableInStopMode;   /*!< Enables or disables WDOG in stop mode  */
    bool kWdogEnableInDebugMode;  /*!< Enables or disables WDOG in debug mode */
}wdog_work_mode_t;

/*! @brief Describes the selection of the clock prescaler */
typedef enum _wdog_clk_prescaler {
    kWdogClkPrescalerDivide1 = 0x0U, /*!< Divided by 1 @internal gui name="1" */
    kWdogClkPrescalerDivide2 = 0x1U, /*!< Divided by 2 @internal gui name="2" */
    kWdogClkPrescalerDivide3 = 0x2U, /*!< Divided by 3 @internal gui name="3" */
    kWdogClkPrescalerDivide4 = 0x3U, /*!< Divided by 4 @internal gui name="4" */
    kWdogClkPrescalerDivide5 = 0x4U, /*!< Divided by 5 @internal gui name="5" */
    kWdogClkPrescalerDivide6 = 0x5U, /*!< Divided by 6 @internal gui name="6" */
    kWdogClkPrescalerDivide7 = 0x6U, /*!< Divided by 7 @internal gui name="7" */
    kWdogClkPrescalerDivide8 = 0x7U  /*!< Divided by 8 @internal gui name="8" */
} wdog_clk_prescaler_t;

/*! @brief Describes WDOG configuration structure 
    @internal gui name="Basic configuration" id="wdogCfg"
 */
typedef struct _wdog_config
{
    bool                 wdogEnable;   /*!< Enables or disables WDOG @internal gui name="Watchdog" id="Watchdog" */
    wdog_clk_src_t       clkSrc;       /*!< Clock source select @internal gui name="Clock source" id="ClockSource" */
    wdog_clk_prescaler_t prescaler;    /*!< Clock prescaler value @internal gui name="Clock prescaler" id="ClockPrescaler" */
    wdog_work_mode_t     workMode;     /*!< Configures WDOG work mode in debug stop and wait mode @internal gui name="Work mode" id="WorkMode" */
    bool                 updateEnable; /*!< Update write-once register enable @internal gui name="Update write-once register" id="UpdateReg" */
    bool                 intEnable;    /*!< Enables or disables WDOG interrupt @internal gui name="Interrupt" id="Interrupt" */
    bool                 winEnable;    /*!< Enables or disables WDOG window mode @internal gui name="Window mode" id="WindowMode" */
    uint32_t             windowValue;  /*!< Window value @internal gui name="Window value" id="WindowValue" default="1" */
    uint32_t             timeoutValue; /*!< Timeout value @internal gui name="Timeout value" id="TimeoutValue" default="1000" */
}wdog_config_t;

/*! @brief WDOG status return codes.*/
typedef enum _wdog_status {
    kStatus_WDOG_Success         = 0x0U, /*!< WDOG operation Succeed      */
    kStatus_WDOG_Fail            = 0x1U, /*!< WDOG operation Failed       */
    kStatus_WDOG_NotInitlialized = 0x2U, /*!< WDOG is not initialized yet */
    kStatus_WDOG_NullArgument    = 0x3U, /*!< Argument is NULL            */
}wdog_status_t;

/*******************************************************************************
 * API
 *******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*! 
 * @name Watchdog HAL.
 * @{
 */

/*!
 * @brief Enables the Watchdog module.
 *
 * This function enables the WDOG.
 * Ensure that the WDOG registers are unlocked by the WDOG_HAL_Unlock, that the WCT window is still open, and that
 * the WDOG_STCTRLH register is not written in this WCT while this function is called.
 *
 * @param base The WDOG peripheral base address
 */
static inline void WDOG_HAL_Enable(WDOG_Type * base)
{
    WDOG_BWR_STCTRLH_WDOGEN(base, 1U);
}

/*!
 * @brief Disables the Watchdog module.
 * 
 * This function disables the WDOG.
 * Ensure that the WDOG registers are unlocked by the WDOG_HAL_Unlock, that the WCT window is still open, and that
 * the WDOG_STCTRLH register is not written in this WCT while this function is called.
 *
 * @param base The WDOG peripheral base address
 */
static inline void WDOG_HAL_Disable(WDOG_Type * base)
{
    WDOG_BWR_STCTRLH_WDOGEN(base, 0U);
}

/*!
 * @brief Checks whether the WDOG is enabled.
 * 
 * This function checks whether the WDOG is enabled.
 *
 * @param base The WDOG peripheral base address
 * @return false means WDOG is disabled, true means WODG is enabled.
 *
 */
static inline bool WDOG_HAL_IsEnable(WDOG_Type * base)
{
    return (bool)WDOG_BRD_STCTRLH_WDOGEN(base);
}

/*!
 * @brief Sets the WDOG common configuration.
 *
 * This function is used to set the WDOG common configuration.
 * Ensure WDOG registers are unlocked by the WDOG_HAL_Unlock, that the WCT window is still open, and
 * that the WDOG_STCTRLH register is not written in this WCT while this function is called.
 * Additionally, ensure that the WDOG_STCTRLH.ALLOWUPDATE is 1, which means that the register update is enabled.
 * The common configuration is controlled by the WDOG_STCTRLH. This is a write-once register and this interface 
 * is used to set all field of the WDOG_STCTRLH registers at the same time. 
 * If only one field needs to be set, the API can be used. These API write to the WDOG_STCTRLH register:
 * #WDOG_HAL_Enable,#WDOG_HAL_Disable,#WDOG_HAL_SetIntCmd,#WDOG_HAL_SetClockSourceMode,#WDOG_HAL_SetWindowModeCmd,
 * #WDOG_HAL_SetRegisterUpdateCmd,#WDOG_HAL_SetWorkInDebugModeCmd,#WDOG_HAL_SetWorkInStopModeCmd,
 * #WDOG_HAL_SetWorkInWaitModeCmd
 *
 * @param base The WDOG peripheral base address
 * @param configPtr The common configure of the WDOG
 */
void WDOG_HAL_SetConfig(WDOG_Type * base, const wdog_config_t *configPtr);

/*!
 * @brief Enables and disables the Watchdog interrupt.
 *
 * This function enables or disables the WDOG interrupt.
 * Ensure that the WDOG registers are unlocked by the WDOG_HAL_Unlock, that the WCT window is still open, and that
 * the WDOG_STCTRLH register is not written in this WCT while this function is called.
 * Additionally, ensure that the WDOG_STCTRLH.ALLOWUPDATE is 1, which means that the register update is enabled.
 *
 * @param base The WDOG peripheral base address
 * @param enable false means disable watchdog interrupt and true means enable watchdog interrupt.
 */
static inline void WDOG_HAL_SetIntCmd(WDOG_Type * base,  bool enable)
{
    WDOG_BWR_STCTRLH_IRQRSTEN(base, enable);
}

/*!
 * @brief Gets the Watchdog interrupt status.
 *
 * This function gets the WDOG interrupt flag.
 *
 * @param base The WDOG peripheral base address
 * @return Watchdog interrupt status, false means interrupt not asserted, true means interrupt asserted.
 */
static inline bool WDOG_HAL_GetIntFlag(WDOG_Type * base)
{
    return (bool)WDOG_BRD_STCTRLL_INTFLG(base);
}

/*!
 * @brief Clears the  Watchdog interrupt flag.
 *
 * This function  clears the WDOG interrupt flag.
 *
 * @param base The WDOG peripheral base address
 */
static inline void WDOG_HAL_ClearIntStatusFlag(WDOG_Type * base)
{
    WDOG_BWR_STCTRLL_INTFLG(base, 1U);
}

/*!
 * @brief Sets the Watchdog timeout value.
 *
 * This function sets the WDOG_TOVAL value.
 * Ensure that the timeout value for the Watchdog is always greater than
 * 2xWCT time + 20 bus clock cycles.
 * Additionally, ensure that the WDOG registers are unlocked by the WDOG_HAL_Unlock, that the WCT window is still open, and that
 * the WDOG_STCTRLH register is not written in this WCT while this function is called.
 * Make sure that the WDOG_STCTRLH.ALLOWUPDATE is 1, which means that the register update is enabled.
 *
 * @param base The WDOG peripheral base address
 * @param timeoutCount watchdog timeout value, count of watchdog clock tick.
 */
static inline void WDOG_HAL_SetTimeoutValue(WDOG_Type * base,  uint32_t timeoutCount)
{
    WDOG_WR_TOVALH(base, (uint16_t)((timeoutCount >> 16U) & 0xFFFFU));
    WDOG_WR_TOVALL(base, (uint16_t)((timeoutCount) & 0xFFFFU));
}

/*!
 * @brief Gets the Watchdog timer output.
 *
 * This function gets the WDOG_TMROUT value.
 *
 * @param base The WDOG peripheral base address
 * @return Current value of watchdog timer counter.
 */
static inline uint32_t WDOG_HAL_GetTimerOutputValue(WDOG_Type * base)
{
    return (uint32_t)((((uint32_t)(WDOG_RD_TMROUTH(base))) << 16U) | (WDOG_RD_TMROUTL(base)));
}

/*!
 * @brief Sets the Watchdog window value.
 *
 * This function sets the WDOG_WIN value.
 * Ensure that the WDOG registers are unlocked by the WDOG_HAL_Unlock, that the WCT window is still open, and that
 * the WDOG_STCTRLH register is not written in this WCT while this function is called.
 * Additionally, ensure that the WDOG_STCTRLH.ALLOWUPDATE is 1, which means that the register update is enabled.
 *
 * @param base The WDOG peripheral base address
 * @param windowValue watchdog window value.
 */
static inline void WDOG_HAL_SetWindowValue(WDOG_Type * base,  uint32_t windowValue)
{
    WDOG_WR_WINH(base, (uint16_t)((windowValue>>16U) & 0xFFFFU));
    WDOG_WR_WINL(base, (uint16_t)((windowValue) & 0xFFFFU));
}

/*!
 * @brief Unlocks the Watchdog register written.
 * 
 * This function unlocks the WDOG register written.
 * This function must be called before any configuration is set because watchdog register
 * is locked automatically after a WCT(256 bus cycles).
 *
 * @param base The WDOG peripheral base address
 */
static inline void WDOG_HAL_Unlock(WDOG_Type * base)
{
    WDOG_WR_UNLOCK(base, 0xC520U);
    WDOG_WR_UNLOCK(base, 0xD928U);
}

/*!
 * @brief Refreshes the Watchdog timer.
 *
 * This function feeds the WDOG.
 * This function should be called before watchdog timer is in timeout. Otherwise, a reset is asserted.
 *
 * @param base The WDOG peripheral base address
 */
static inline void WDOG_HAL_Refresh(WDOG_Type * base)
{
    WDOG_WR_REFRESH(base, 0xA602U);
    WDOG_WR_REFRESH(base, 0xB480U);
}

/*!
 * @brief Resets the chip using the Watchdog.
 *
 * This function resets the chip using WDOG.
 *
 * @param base The WDOG peripheral base address
 */
static inline void WDOG_HAL_ResetSystem(WDOG_Type * base)
{
    WDOG_WR_REFRESH(base, 0xA602U);
    WDOG_WR_REFRESH(base, 0);
    while(1)
    {
    }
}

/*!
 * @brief Restores the WDOG module to reset value.
 *
 * This function restores the WDOG module to reset value.
 *
 * @param base The WDOG peripheral base address
 */
void WDOG_HAL_Init(WDOG_Type * base);

/*@}*/

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif
#endif /* __FSL_WDOG_HAL_H__*/
/*******************************************************************************
 * EOF
 *******************************************************************************/

