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
#ifndef __FSL_COP_HAL_H__
#define __FSL_COP_HAL_H__

#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include "fsl_device_registers.h"

/*! 
 * @addtogroup cop_hal
 * @{
 */

/*******************************************************************************
 * Definitions
 *******************************************************************************/

/*! @brief COP clock source selection.*/
typedef enum _cop_clock_source {
    kCopLpoClock,                            /*!< LPO clock,1K HZ. @internal gui name="LPO" */
#if FSL_FEATURE_COP_HAS_MORE_CLKSRC
    kCopMcgIrClock,                          /*!< MCG IRC Clock. @internal gui name="MCGIRCLK"*/
    kCopOscErClock,                          /*!< OSCER Clock. @internal gui name="OSCERCLK"*/
#endif
    kCopBusClock                             /*!< BUS clock. @internal gui name="Bus clock"*/
}cop_clock_source_t;

/*! @brief Define the value of the COP timeout cycles */
typedef enum _cop_timeout_cycles {
    kCopTimeout_short_2to5_or_long_2to13  = 1U,   /*!< 2 to 5 clock cycles when clock source is LPO or in short timeout mode otherwise 2 to 13 clock cycles @internal gui name="2^5 or 2^13 clock" */
    kCopTimeout_short_2to8_or_long_2to16  = 2U,   /*!< 2 to 8 clock cycles when clock source is LPO or in short timeout mode otherwise 2 to 16 clock cycles @internal gui name="2^8 or 2^16 clock" */
    kCopTimeout_short_2to10_or_long_2to18 = 3U    /*!< 2 to 10 clock cycles when clock source is LPO or in short timeout mode otherwise 2 to 18 clock cycles @internal gui name="2^10 or 2^18 clock" */
}cop_timeout_cycles_t;

#if FSL_FEATURE_COP_HAS_LONGTIME_MODE
/*! @breif Define the COP's timeout mode */
typedef enum _cop_timeout_mode{
    kCopShortTimeoutMode = 0U,      /*!< COP selects long timeout  @internal gui name="Short timeout" */
    kCopLongTimeoutMode  = 1U       /*!< COP selects short timeout @internal gui name="Long timeout" */
}cop_timeout_mode_t;
#endif

/*! 
 * @brief Data structure to initialize the COP.
 *
 * This structure is used to initialize the COP during the cop_init function call.
 * It contains all COP configurations.
 * @internal gui name="COP configuration" id="copCfg"
 */
typedef struct CopConfig{
    bool copWindowModeEnable;                   /*!< Set COP watchdog run mode---Window mode or Normal mode @internal gui name="Windowed mode" id="WindowedMode" */
#if FSL_FEATURE_COP_HAS_LONGTIME_MODE
    cop_timeout_mode_t copTimeoutMode;          /*!< Set COP watchdog timeout mode---Long timeout or Short timeout @internal gui name="Timeout mode" id="TimeoutMode" */
    bool copStopModeEnable;                     /*!< Set COP enable or disable in STOP mode @internal gui name="Stop mode" id="StopMode" */ 
    bool copDebugModeEnable;                    /*!< Set COP enable or disable in DEBUG mode @internal gui name="Debug mode" id="DebugMode" >*/
#endif
    cop_clock_source_t copClockSource;          /*!< Set COP watchdog clock source @internal gui name="Clock source" id="ClockSource" */
    cop_timeout_cycles_t copTimeout;            /*!< Set COP watchdog timeout value @internal gui name="Timeout value" id="TimeoutValue" */
}cop_config_t;

/*! @brief cop status return codes.*/
typedef enum _cop_status {
    kStatus_COP_Success         = 0x0U, /*!< COP operation Succeed      */
    kStatus_COP_Fail            = 0x01, /*!< COP operation Failed       */
    kStatus_COP_NotInitlialized = 0x2U, /*!< COP is not initialized yet */
    kStatus_COP_NullArgument    = 0x3U, /*!< Argument is NULL           */
}cop_status_t;

/*******************************************************************************
 * API
 *******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*! 
 * @name COP HAL.
 * @{
 */
  
  
/*!
 * @brief Configures the COP Watchdog.
 *
 * The COP control register is write once after reset.
 *
 * @param base The COP peripheral base address
 * @param configPtr configure COP control register
 */
void COP_HAL_SetConfig(SIM_Type * base, const cop_config_t *configPtr);

/*!
 * @brief Enables the COP Watchdog.
 *
 * After reset the COP is enabled.
 *
 */
static inline void COP_HAL_Enable(void)
{

}

/*!
 * @brief Disables the COP Watchdog.
 *
 * This function disables the COP Watchdog and 
 * should be called after reset if your application does not need the COP Watchdog.
 *
 * @param base The COP peripheral base address
 */
static inline void COP_HAL_Disable(SIM_Type * base)
{
    SIM_BWR_COPC_COPT(base, 0U);
}

/*!
 * @brief Determines whether the COP is enabled.
 *
 * This function checks whether the COP is running.
 *
 * @param base The COP peripheral base address
 * @return State of the module
 * @retval true COP is enabled
 * @retval false COP is disabled
 */
static inline bool COP_HAL_IsEnable(SIM_Type * base)
{
    return ((bool)SIM_BRD_COPC_COPT(base));
}

/*!
 * @brief Servicing the COP Watchdog.
 *
 * This function resets the COP timeout by writing 0x55 then 0xAA. 
 * Writing any other value generates a system reset.
 * The writing operations should be atomic.
 * @param base The COP peripheral base address
 */
static inline void COP_HAL_Refresh(SIM_Type * base)
{
    SIM_WR_SRVCOP(base, 0x55U);
    SIM_WR_SRVCOP(base, 0xaaU);
}

/*!
 * @brief Resets the system.
 *
 * This function resets the system.
 * @param base The COP peripheral base address
 */
static inline void COP_HAL_ResetSystem(SIM_Type * base)
{
    SIM_WR_SRVCOP(base, 0U);
}

/*!
 * @brief Restores the COP module to the reset value.
 *
 * This function restores the COP module to the reset value.
 *
 * @param base The COP peripheral base address
 */
void COP_HAL_Init(SIM_Type * base);

/*@}*/

#if defined(__cplusplus)
}
#endif

/*! @}*/

#endif /* __FSL_COP_HAL_H__*/
/*******************************************************************************
 * EOF
 *******************************************************************************/
