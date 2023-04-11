/***************************************************************************//**
* \file cy_wdt.h
* \version 1.50
*
*  This file provides constants and parameter values for the WDT driver.
*
********************************************************************************
* \copyright
* Copyright (c) (2016-2022), Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation.
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
*******************************************************************************/

/**
* \addtogroup group_wdt
* \{
*
* The Watchdog timer (WDT) has a 16-bit free-running up-counter.
*
* The functions and other declarations used in this driver are in cy_wdt.h.
* You can include cy_pdl.h to get access to all functions
* and declarations in the PDL.
*
* The WDT can issue counter match interrupts, and a device reset if its interrupts are not
* handled. Use the Watchdog timer for two main purposes:
*
* The <b> First use case </b> is recovering from a CPU or firmware failure.
* A timeout period is set up in the Watchdog timer, and if a timeout occurs, the
* device is reset (WRES). <br>
* The <b>Second use case</b> is to generate periodic interrupts.
* It is strongly recommended not to use the WDT for periodic interrupt
* generation. However, if absolutely required, see information below.
*
* A "reset cause" register(RES_CAUSE, Part of SRSS IP) exists, and the firmware should
* check this register at a start-up. An appropriate action can be taken if a WRES
* reset is detected.
*
* The user's firmware periodically resets the timeout period (clears or "feeds"
* the watchdog) before a timeout occurs. If the firmware fails to do so, that is
* considered to be a CPU crash or a firmware failure, and the reason for a
* device reset.
* The WDT can generate an interrupt instead of a device reset. The Interrupt
* Service Routine (ISR) can handle the interrupt either as a periodic interrupt,
* or as an early indication of a firmware failure and respond accordingly.
* However, it is not recommended to use the WDT for periodic interrupt
* generation. The Multi-counter Watchdog Timers (MCWDT) can be used to generate
* periodic interrupts if such are presented in the device.
*
* <b> Functional Description </b>
*
* The WDT generates an interrupt when the count value in the counter equals the
* configured match value.
*
* Note that the counter is not reset on a match. In such case the WDT
* reset period is:
* WDT_Reset_Period = ILO_Period * (2*2^(16-IgnoreBits) + MatchValue);
* When the counter reaches a match value, it generates an interrupt and then
* keeps counting up until it overflows and rolls back to zero and reaches the
* match value again, at which point another interrupt is generated.
*
* To use a WDT to generate a periodic interrupt, the match value should be
* incremented in the ISR. As a result, the next WDT interrupt is generated when
* the counter reaches a new match value.
*
* You can also reduce the entire WDT counter period by
* specifying the number of most significant bits that are ignored in the WDT
* counter. For example, if the Cy_WDT_SetIgnoreBits() function is called with
* parameter 3, the WDT counter becomes a 13-bit free-running up-counter.
*
* <b> Power Modes </b>
*
* WDT can operate in all possible low power modes.
* Operation during Hibernate mode is possible because the logic and
* high-voltage internal low oscillator (ILO) are supplied by the external
* high-voltage supply (Vddd). The WDT can be configured to wake the device from
* Hibernate mode.
*
* In CPU Active mode, an interrupt request from the WDT is sent to the
* CPU. In CPU Sleep, CPU Deep Sleep mode, the CPU subsystem
* is powered down, so the interrupt request from the WDT is sent directly to the
* WakeUp Interrupt Controller (WIC) which will then wake up the CPU. The
* CPU then acknowledges the interrupt request and executes the ISR.
*
* <b> Clock Source </b>
*
* The WDT is clocked by the ILO. The WDT must be disabled before disabling
* the ILO. According to the device datasheet, the ILO accuracy is +/-30% over
* voltage and temperature. This means that the timeout period may vary by 30%
* from the configured value. Appropriate margins should be added while
* configuring WDT intervals to make sure that unwanted device resets do not
* occur on some devices.
*
* Refer to the device datasheet for more information on the oscillator accuracy.
*
* <b> Register Locking </b>
*
* You can prevent accidental corruption of the WDT configuration by calling
* the Cy_WDT_Lock() function. When the WDT is locked, any writing to the WDT_*,
* CLK_ILO_CONFIG, CLK_SELECT.LFCLK_SEL, and CLK_TRIM_ILO_CTL registers is
* ignored.
* Call the Cy_WDT_Unlock() function to allow registers modification, mentioned
* above.
*
* Note that the WDT lock state is not retained during system Deep Sleep. After
* the wakeup from system Deep Sleep the WDT is locked.
*
* <b> Clearing WDT </b>
*
* The ILO clock is asynchronous to the SysClk. Therefore it generally
* takes three ILO cycles for WDT register changes to come into effect. It is
* important to remember that a WDT should be cleared at least four cycles
* (3 + 1 for sure) before a timeout occurs, especially when small
* match values / low-toggle bit numbers are used.
*
* \warning It may happen that a WDT reset can be generated
* faster than a device start-up. To prevent this, calculate the
* start-up time and WDT reset time. The WDT reset time should be always greater
* than device start-up time.
*
* <b> Reset Detection </b>
*
* Use the Cy_SysLib_GetResetReason() function to detect whether the WDT has
* triggered a device reset.
*
* <b> Interrupt Configuration </b>
*
* If the WDT is configured to generate an interrupt, pending
* interrupts must be cleared within the ISR (otherwise, the interrupt will be
* generated continuously).
* A pending interrupt to the WDT block must be cleared by calling the
* Cy_WDT_ClearInterrupt() function. The call to the function will clear the
* unhandled WDT interrupt counter.
*
* Use the WDT ISR as a timer to trigger certain actions
* and to change a next WDT match value.
*
* Ensure that the interrupts from the WDT are passed to the CPU to avoid
* unregistered interrupts. Unregistered WDT interrupts result in a continuous
* device reset. To avoid this, call Cy_WDT_UnmaskInterrupt().
* After that, call the WDT API functions for interrupt
* handling/clearing.
*
* \section group_wdt_configuration Configuration Considerations
*
* To start the WDT, make sure that ILO is enabled.
* After the ILO is enabled, ensure that the WDT is unlocked and disabled by
* calling the Cy_WDT_Unlock() and Cy_WDT_Disable() functions. Set the WDT match
* value by calling Cy_WDT_SetMatch() with the required match value. If needed,
* set the ignore bits for reducing the WDT counter period by calling
* Cy_WDT_SetIgnoreBits() function. After the WDT configuration is set,
* call Cy_WDT_Enable().
*
* \note Enable a WDT if the power supply can produce
* sudden brownout events that may compromise the CPU functionality. This
* ensures that the system can recover after a brownout.
*
* When the WDT is used to protect against system crashes, the
* WDT interrupt should be cleared by a portion of the code that is not directly
* associated with the WDT interrupt.
* Otherwise, it is possible that the main firmware loop has crashed or is in an
* endless loop, but the WDT interrupt vector continues to operate and service
* the WDT. The user should:
* * Feed the watchdog by clearing the interrupt bit regularly in the main body
* of the firmware code.
*
* * Guarantee that the interrupt is cleared at least once every WDT period.
*
* * Use the WDT ISR only as a timer to trigger certain actions and to change the
* next match value.
*
* \section group_wdt_section_more_information More Information
*
* For more information on the WDT peripheral, refer to the technical reference
* manual (TRM).
*
* \section group_wdt_changelog Changelog
* <table class="doxtable">
*   <tr><th>Version</th><th>Changes</th><th>Reason for Change</th></tr>
*   <tr>
*     <td>1.50</td>
*     <td>Added WDT_B type support required for CAT1C devices.<br>Newly added APIs:
*         \n Cy_WDT_SetLowerLimit(),
*         \n Cy_WDT_SetUpperLimit(),
*         \n Cy_WDT_SetWarnLimit(),
*         \n Cy_WDT_SetLowerAction(),
*         \n Cy_WDT_SetUpperAction(),
*         \n Cy_WDT_SetWarnAction(),
*         \n Cy_WDT_SetAutoService(),
*         \n Cy_WDT_SetDeepSleepPause(),
*         \n Cy_WDT_SetHibernatePause(),
*         \n Cy_WDT_SetDebugRun(),
*         \n Cy_WDT_SetService(),
*     <td>Support for new devices.</td>
*   </tr>
*   <tr>
*     <td>1.40</td>
*     <td>CAT1B, CAT1C devices support.<br>
*         Newly added API's Cy_WDT_SetClkSource() to configure the WDT clock source, Cy_WDT_GetClkSource() to get the WDT clock source configured,
*         Cy_WDT_SetMatchBits() to configure the bit position above which the bits will be ignored for match, Cy_WDT_GetMatchBits() to get the bit position above which the bits will be ignored for match.</td>
*     <td>Support for new devices.</td>
*   </tr>
*   <tr>
*     <td>1.30.1</td>
*     <td>Minor documentation updates.</td>
*     <td>Removed MISRA 2004 compliance details and verified MISRA 2012 compliance.</td>
*   </tr>
*   <tr>
*     <td rowspan="2">1.30</td>
*     <td>Updated the following functions for the PSoC 64 devices: \ref Cy_WDT_ClearInterrupt(),
*         \ref Cy_WDT_MaskInterrupt(), and \ref Cy_WDT_UnmaskInterrupt().</td>
*     <td>Added PSoC 64 device support.</td>
*   </tr>
*   <tr>
*     <td>Minor documentation updates.</td>
*     <td>Documentation enhancement.</td>
*   </tr>
*   <tr>
*     <td>1.20</td>
*     <td>Added a new API function \ref Cy_WDT_IsEnabled() </td>
*     <td>Enhancement based on usability feedback.</td>
*   </tr>
*   <tr>
*     <td>1.10.1</td>
*     <td>Added info that the WDT lock state is not retained during
*        system Deep Sleep power mode.
*     </td>
*     <td>Documentation updates.</td>
*   </tr>
*   <tr>
*     <td rowspan="4">1.10</td>
*     <td>Flattened the organization of the driver source code into the single
*         source directory and the single include directory.
*     </td>
*     <td>Driver library directory-structure simplification.</td>
*   </tr>
*   <tr>
*     <td> Removed critical section usage in the following functions:
*           - \ref Cy_WDT_Init()
*           - \ref Cy_WDT_Lock()
*           - \ref Cy_WDT_Unlock()
*     </td>
*   <td>Driver functions simplification</td>
*   </tr>
*   <tr>
*     <td>Updated the \ref Cy_WDT_Init(), \ref Cy_WDT_Enable() to clear WDT interrupt.</td>
*     <td>Corner case reliability improvements</td>
*   </tr>
*   <tr>
*     <td>Added register access layer. Use register access macros instead
*         of direct register access using dereferenced pointers.</td>
*     <td>Makes register access device-independent, so that the PDL does
*         not need to be recompiled for each supported part number.</td>
*   </tr>
*   <tr>
*     <td>1.0.2</td>
*     <td>Minor documentation updates</td>
*     <td>Corrected info about a reset generation</td>
*   </tr>
*   <tr>
*     <td>1.0.1</td>
*     <td>General documentation updates</td>
*     <td>Added info about periodic interrupt generation use case</td>
*   </tr>
*   <tr>
*     <td>1.0</td>
*     <td>Initial version</td>
*     <td></td>
*   </tr>
* </table>
*
* \defgroup group_wdt_macros Macros
* \defgroup group_wdt_clk_src_enums Enums
* \defgroup group_wdt_functions Functions
*
*/

#if !defined(CY_WDT_H)
#define CY_WDT_H

#include "cy_device.h"

#if defined (CY_IP_MXS28SRSS)|| defined (CY_IP_MXS40SSRSS ) || defined (CY_IP_MXS40SRSS) || defined (CY_IP_MXS22SRSS)

#include <stdint.h>
#include <stdbool.h>
#include "cy_syslib.h"
#if defined(CY_DEVICE_SECURE)
    #include "cy_pra.h"
#endif /* defined(CY_DEVICE_SECURE) */


#if defined(__cplusplus)
extern "C" {
#endif


/*******************************************************************************
*       Function Constants
*******************************************************************************/

/**
* \addtogroup group_wdt_macros
* \{
*/

/** The driver major version */
#define CY_WDT_DRV_VERSION_MAJOR                       1

/** The driver minor version */
#define CY_WDT_DRV_VERSION_MINOR                       50

#if (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3))
/** The internal define for the first iteration of WDT unlocking */
#define CY_SRSS_WDT_LOCK_BIT0                           ((uint32_t)0x01U)

/** The internal define for the second iteration of WDT unlocking */
#define CY_SRSS_WDT_LOCK_BIT1                           ((uint32_t)0x02U)
#else
/** The internal define for the first iteration of WDT unlocking */
#define CY_SRSS_WDT_LOCK_BIT0                           ((uint32_t)0x01U << 30U)

/** The internal define for the second iteration of WDT unlocking */
#define CY_SRSS_WDT_LOCK_BIT1                           ((uint32_t)0x01U << 31U)
#endif

/** The WDT default match value */
#define CY_SRSS_WDT_DEFAULT_MATCH_VALUE                 ((uint32_t) 4096U)

/** The default match value of the WDT ignore bits */
#define CY_SRSS_WDT_DEFAULT_IGNORE_BITS                 (0U)

/** The default match value of the WDT ignore bits */
#define CY_SRSS_WDT_LOCK_BITS                           (3U)

/** The WDT driver identifier */
#define CY_WDT_ID                                       CY_PDL_DRV_ID(0x34U)

/** \cond Internal */

#if defined (CY_IP_MXS40SSRSS) || defined (CY_IP_MXS22SRSS)
/** The WDT maximum match value */
#define WDT_MAX_MATCH_VALUE                      ((0xFFFFFFFFuL) >> (32 - SRSS_NUM_WDT_A_BITS))
/* Internal macro to validate match value */
#define CY_WDT_IS_IGNORE_BITS_ABOVE_VALID(bitPos)     ((bitPos) < SRSS_NUM_WDT_A_BITS)

#else
/** The WDT maximum match value */
#define WDT_MAX_MATCH_VALUE                      (0xFFFFuL)
#endif

/** The WDT maximum Ignore Bits */
#define WDT_MAX_IGNORE_BITS                      (0xFuL)

 /* Internal macro to validate match value */
 #define CY_WDT_IS_MATCH_VAL_VALID(match)        ((match) <= WDT_MAX_MATCH_VALUE)

/* Internal macro to validate match value */
#define CY_WDT_IS_IGNORE_BITS_VALID(bitsNum)     ((bitsNum) <= WDT_MAX_IGNORE_BITS)

#if (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3))
/** The WDT default match value */
/**
* \note
* This Macro is available for CAT1C devices.
**/
#define CY_WDT_DEFAULT_MATCH_VALUE                     (32000UL) // 1 sec when clk_lf = 32KHz

/** The WDT default LOWER_LIMIT value */
/**
* \note
* This Macro is available for CAT1C devices.
**/
#define CY_WDT_DEFAULT_LOWER_LIMIT                     (0U)

/** The WDT default UPPER_LIMIT value */
/**
* \note
* This Macro is available for CAT1C devices.
**/
#define CY_WDT_DEFAULT_UPPER_LIMIT                     CY_WDT_DEFAULT_MATCH_VALUE

/** The WDT default WARN_LIMIT value */
/**
* \note
* This Macro is available for CAT1C devices.
**/
#define CY_WDT_DEFAULT_WARN_LIMIT                     (0U)
#endif

#if defined (CY_IP_MXS40SSRSS) || defined (CY_IP_MXS22SRSS)
/**
* \note
* This Macro is available for CAT1B devices.
**/
/* Internal macro to validate match value */
#define CY_WDT_IS_CLK_SRC_VALID(src)         (((src) == CY_WDT_CLK_SOURCE_ILO)  || \
                                              ((src) == CY_WDT_CLK_SOURCE_PILO) || \
                                              ((src) == CY_WDT_CLK_SOURCE_BAK))
#endif

/** \endcond */
/** \} group_wdt_macros */
/**
* \addtogroup group_wdt_clk_src_enums
* \{
*/

#if defined (CY_IP_MXS40SSRSS) || defined (CY_IP_MXS22SRSS) ||defined (CY_DOXYGEN)
/**
* \note
* This enum is available for CAT1B devices.
**/

typedef enum
{
    CY_WDT_CLK_SOURCE_ILO       =     0U, /**< Select the ILO as clock source to WDT */
    CY_WDT_CLK_SOURCE_PILO      =     1U, /**< Select the PILO as clock source to WDT */
    CY_WDT_CLK_SOURCE_BAK       =     2U, /**< Select the clk_bak as clock source to WDT */
} cy_en_wdt_clk_sources_t;
#endif

#if (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3))
/** The wdt lower/upper limit actions. */
/**
* \note
* This Enum is available for CAT1C devices.
**/
typedef enum
{
    CY_WDT_LOW_UPPER_LIMIT_ACTION_NONE,
    CY_WDT_LOW_UPPER_LIMIT_ACTION_RESET
} cy_en_wdt_lower_upper_action_t;

/** The wdt lower/upper limit actions. */
/**
* \note
* This Enum is available for CAT1C devices.
**/
typedef enum
{
    CY_WDT_WARN_ACTION_NONE,
    CY_WDT_WARN_ACTION_INT
} cy_en_wdt_warn_action_t;

/** The wdt Disable/Enable Macros. */
/**
* \note
* This Enum is available for CAT1C devices.
**/
typedef enum
{
    CY_WDT_DISABLE,
    CY_WDT_ENABLE
} cy_en_wdt_enable_t;
#endif

/** \} group_wdt_clk_src_enums */


/*******************************************************************************
*        Function Prototypes
*******************************************************************************/
/**
* \addtogroup group_wdt_functions
* @{
*/
/* WDT API */
void Cy_WDT_Init(void);
void Cy_WDT_Lock(void);
void Cy_WDT_Unlock(void);
bool Cy_WDT_Locked(void);
void Cy_WDT_ClearInterrupt(void);
void Cy_WDT_ClearWatchdog(void);

__STATIC_INLINE void Cy_WDT_Enable(void);
__STATIC_INLINE void Cy_WDT_Disable(void);
__STATIC_INLINE bool Cy_WDT_IsEnabled(void);
__STATIC_INLINE uint32_t Cy_WDT_GetCount(void);
__STATIC_INLINE void Cy_WDT_MaskInterrupt(void);
__STATIC_INLINE void Cy_WDT_UnmaskInterrupt(void);

#if defined (CY_IP_MXS28SRSS) || defined (CY_IP_MXS40SSRSS) || defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION < 3) || defined (CY_IP_MXS22SRSS)
void Cy_WDT_SetMatch(uint32_t match);
void Cy_WDT_SetIgnoreBits(uint32_t bitsNum);
__STATIC_INLINE uint32_t Cy_WDT_GetMatch(void);
__STATIC_INLINE uint32_t Cy_WDT_GetIgnoreBits(void);

#if defined (CY_IP_MXS40SSRSS) || defined (CY_IP_MXS22SRSS) ||defined (CY_DOXYGEN)
void Cy_WDT_SetMatchBits(uint32_t bitPos);
__STATIC_INLINE void Cy_WDT_SetClkSource(cy_en_wdt_clk_sources_t src);
__STATIC_INLINE cy_en_wdt_clk_sources_t Cy_WDT_GetClkSource(void);
__STATIC_INLINE uint32_t Cy_WDT_GetMatchBits(void);
#endif

#endif

#if (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3))
void Cy_WDT_SetLowerLimit(uint32_t match);
void Cy_WDT_SetUpperLimit(uint32_t match);
void Cy_WDT_SetWarnLimit(uint32_t match);
void Cy_WDT_SetLowerAction(cy_en_wdt_lower_upper_action_t action);
void Cy_WDT_SetUpperAction(cy_en_wdt_lower_upper_action_t action);
void Cy_WDT_SetWarnAction(cy_en_wdt_warn_action_t action);
void Cy_WDT_SetAutoService(cy_en_wdt_enable_t enable);
void Cy_WDT_SetDeepSleepPause(cy_en_wdt_enable_t enable);
void Cy_WDT_SetHibernatePause(cy_en_wdt_enable_t enable);
void Cy_WDT_SetDebugRun(cy_en_wdt_enable_t enable);
void Cy_WDT_SetService(void);
#endif


/*******************************************************************************
* Function Name: Cy_WDT_Enable
****************************************************************************//**
*
* Enables the Watchdog timer.
*
* \sideeffect
* This function clears the WDT interrupt.
*
*******************************************************************************/
__STATIC_INLINE void Cy_WDT_Enable(void)
{
#if (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3))
    SRSS_WDT_CTL |= WDT_CTL_ENABLE_Msk;
#else
    SRSS_WDT_CTL |= _VAL2FLD(SRSS_WDT_CTL_WDT_EN, 1U);
#endif

    Cy_WDT_ClearInterrupt();
}


/*******************************************************************************
* Function Name: Cy_WDT_Disable
****************************************************************************//**
*
* Disables the Watchdog timer. The Watchdog timer should be unlocked before being
* disabled. Call the Cy_WDT_Unlock() API to unlock the WDT.
*
*******************************************************************************/
__STATIC_INLINE void Cy_WDT_Disable(void)
{
#if (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3))
    SRSS_WDT_CTL &= ((uint32_t) ~(_VAL2FLD(WDT_CTL_ENABLE, 1U)));
#else
    SRSS_WDT_CTL &= ((uint32_t) ~(_VAL2FLD(SRSS_WDT_CTL_WDT_EN, 1U)));
#endif
}


/*******************************************************************************
* Function Name: Cy_WDT_IsEnabled
****************************************************************************//**
*
* Reports an enable/disable state of the Watchdog timer.
*
* \return
* - true - if the timer is enabled
* - false - if the timer is disabled
*
*******************************************************************************/
__STATIC_INLINE bool Cy_WDT_IsEnabled(void)
{
#if (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3))
    return _FLD2BOOL(WDT_CTL_ENABLE, SRSS_WDT_CTL);
#else
    return _FLD2BOOL(SRSS_WDT_CTL_WDT_EN, SRSS_WDT_CTL);
#endif
}

#if defined (CY_IP_MXS28SRSS) || defined (CY_IP_MXS40SSRSS) || defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION < 3) || defined (CY_IP_MXS22SRSS)

/*******************************************************************************
* Function Name: Cy_WDT_GetMatch
****************************************************************************//**
*
* Reads the WDT counter match comparison value.
*
* \return The counter match value.
*
* \note
* This API is available for CAT1A, CAT1B and CAT1D devices.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_WDT_GetMatch(void)
{
    return ((uint32_t) _FLD2VAL(SRSS_WDT_MATCH_MATCH, SRSS_WDT_MATCH));
}

/*******************************************************************************
* Function Name: Cy_WDT_GetIgnoreBits
****************************************************************************//**
*
* Reads the number of the most significant bits of the Watchdog timer that are
* not checked against the match.
*
* \return The number of the most significant bits.
*
* \note
* This API is available for CAT1A, CAT1B and CAT1D devices.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_WDT_GetIgnoreBits(void)
{
#if defined (CY_IP_MXS40SSRSS) || defined (CY_IP_MXS22SRSS)
    return((uint32_t) (WDT_MAX_IGNORE_BITS - _FLD2VAL(SRSS_WDT_MATCH2_IGNORE_BITS_ABOVE, SRSS_WDT_MATCH2)));
#else
    return((uint32_t) _FLD2VAL(SRSS_WDT_MATCH_IGNORE_BITS, SRSS_WDT_MATCH));
#endif
}

#if defined (CY_IP_MXS40SSRSS) || defined (CY_IP_MXS22SRSS) || defined (CY_DOXYGEN)
/*******************************************************************************
* Function Name: Cy_WDT_SetClkSource
****************************************************************************//**
*
* Configures the WDT clock source
*
* \param src
* \ref cy_en_wdt_clk_sources_t
*
* \note
* This API is available for CAT1B and CAT1D devices.
*
* \note  It takes four cycles of the originally selected clock to switch away
* from it.  Do not disable the original clock during this time.
*
*******************************************************************************/
__STATIC_INLINE void Cy_WDT_SetClkSource(cy_en_wdt_clk_sources_t src)
{
    CY_ASSERT_L2(CY_WDT_IS_CLK_SRC_VALID(src));

    if (false == Cy_WDT_Locked())
    {
        SRSS_WDT_CTL = _CLR_SET_FLD32U((SRSS_WDT_CTL), SRSS_WDT_CTL_WDT_CLK_SEL, src);
    }
}

/*******************************************************************************
* Function Name: Cy_WDT_GetClkSource
****************************************************************************//**
*
* Gets the WDT clock source configured.
*
* \return The Clock source enum \ref cy_en_wdt_clk_sources_t
*
* \note
* This API is available for CAT1B and CAT1D devices.
*
*******************************************************************************/
__STATIC_INLINE cy_en_wdt_clk_sources_t Cy_WDT_GetClkSource(void)
{
    CY_MISRA_DEVIATE_LINE('MISRA C-2012 Rule 10.8','Intentional typecast to cy_en_wdt_clk_sources_t enum.');
    return ((cy_en_wdt_clk_sources_t) _FLD2VAL(SRSS_WDT_CTL_WDT_CLK_SEL, SRSS_WDT_CTL));
}

/*******************************************************************************
* Function Name: Cy_WDT_GetMatchBits
****************************************************************************//**
*
* Gets the bit position above which the bits will be ignored for match.
*
* \return The bit position above which the bits will be ignored for match.
*
* \note
* This API is available for CAT1B and CAT1D devices.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_WDT_GetMatchBits(void)
{
    return((uint32_t) (_FLD2VAL(SRSS_WDT_MATCH2_IGNORE_BITS_ABOVE, SRSS_WDT_MATCH2)));
}
#endif

#endif /*defined (CY_IP_MXS28SRSS) || defined (CY_IP_MXS40SSRSS) || defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION < 3) */


/*******************************************************************************
* Function Name: Cy_WDT_GetCount
****************************************************************************//**
*
* Reads the current WDT counter value.
*
* \return A live counter value.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_WDT_GetCount(void)
{
#if (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3))
    return ((uint32_t) _FLD2VAL(WDT_CNT_CNT, SRSS_WDT_CNT));
#else
    return ((uint32_t) _FLD2VAL(SRSS_WDT_CNT_COUNTER, SRSS_WDT_CNT));
#endif
}


/*******************************************************************************
* Function Name: Cy_WDT_MaskInterrupt
****************************************************************************//**
*
* After masking interrupts from the WDT, they are not passed to the CPU.
* This function does not disable the WDT-reset generation.
*
*******************************************************************************/
__STATIC_INLINE void Cy_WDT_MaskInterrupt(void)
{
#if (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3))
    SRSS_WDT_INTR_MASK &= ~WDT_INTR_MASK_WDT_Msk;
#else
    #if CY_CPU_CORTEX_M4 && defined(CY_DEVICE_SECURE)
        CY_PRA_REG32_CLR_SET(CY_PRA_INDX_SRSS_SRSS_INTR_MASK, SRSS_SRSS_INTR_MASK_WDT_MATCH, 0U);
    #else
        SRSS_SRSS_INTR_MASK &= (uint32_t)(~ _VAL2FLD(SRSS_SRSS_INTR_MASK_WDT_MATCH, 1U));
    #endif /* CY_CPU_CORTEX_M4 && defined(CY_DEVICE_SECURE) */
#endif
}


/*******************************************************************************
* Function Name: Cy_WDT_UnmaskInterrupt
****************************************************************************//**
*
* After unmasking interrupts from the WDT, they are passed to CPU.
* This function does not impact the reset generation.
*
*******************************************************************************/
__STATIC_INLINE void Cy_WDT_UnmaskInterrupt(void)
{
#if (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3))
    SRSS_WDT_INTR_MASK |= WDT_INTR_MASK_WDT_Msk;
#else
    #if CY_CPU_CORTEX_M4 && defined(CY_DEVICE_SECURE)
        CY_PRA_REG32_CLR_SET(CY_PRA_INDX_SRSS_SRSS_INTR_MASK, SRSS_SRSS_INTR_MASK_WDT_MATCH, 1U);
    #else
        SRSS_SRSS_INTR_MASK |= _VAL2FLD(SRSS_SRSS_INTR_MASK_WDT_MATCH, 1U);
    #endif /* CY_CPU_CORTEX_M4 && defined(CY_DEVICE_SECURE) */
#endif
}
/** \} group_wdt_functions */

#if defined(__cplusplus)
}
#endif

#endif /* CY_IP_MXS28SRSS, CY_IP_MXS40SRSS */

#endif /* CY_WDT_H */

/** \} group_wdt */


/* [] END OF FILE */
