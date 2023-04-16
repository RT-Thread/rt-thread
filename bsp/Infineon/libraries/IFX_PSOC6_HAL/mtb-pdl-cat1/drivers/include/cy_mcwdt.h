/***************************************************************************//**
* \file cy_mcwdt.h
* \version 1.70
*
* Provides an API declaration of the Cypress PDL 3.0 MCWDT driver
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
*******************************************************************************/

/**
* \addtogroup group_mcwdt
* \{
* A MCWDT has two 16-bit counters and one 32-bit counter.
*
* The functions and other declarations used in this driver are in cy_mcwdt.h.
* You can include cy_pdl.h to get access to all functions
* and declarations in the PDL.
*
* You can use this driver to create a free-running
* timer or generate periodic interrupts. The driver also
* includes support for the watchdog function to recover from CPU or
* firmware failures.
*
* There are two primary use cases for MCWDT: generating periodic CPU interrupts;
* and implementing a free-running timer. Both have many applications in
* embedded systems:
* * Measuring time between events
* * Generating periodic events
* * Synchronizing actions
* * Real-time clocking
* * Polling
*
* An additional use case is to implement a watchdog used for recovering from a CPU or
* firmware failure.
*
* \section group_mcwdt_configuration Configuration Considerations
*
* Each MCWDT may be configured for a particular product.
* One MCWDT block can be associated with only one CPU during runtime.
* A single MCWDT is not intended to be used by multiple CPUs simultaneously.
* Each block contains three sub-counters, each of which can be configured for
* various system utility functions - free running counter, periodic interrupts,
* watchdog reset, or three interrupts followed by a watchdog reset.
* All counters are clocked by either LFCLK (nominal 32 kHz) or by a cascaded
* counter.
* A simplified diagram of the MCWDT hardware is shown below:
* \image html mcwdt.png
* The frequency of the periodic interrupts can be configured using the Match
* value with combining Clear on match option, which can be set individually
* for each counter using Cy_MCWDT_SetClearOnMatch(). When the Clear on match option
* is not set, the periodic interrupts of the C0 and C1 16-bit sub-counters occur
* after 65535 counts and the match value defines the shift between interrupts
* (see the figure below). The enabled Clear on match option
* resets the counter when the interrupt occurs.
* \image html mcwdt_counters.png
* 32-bit sub-counter C2 does not have Clear on match option.
* The interrupt of counter C2 occurs when the counts equal
* 2<sup>Toggle bit</sup> value.
* \image html mcwdt_subcounters.png
* To set up an MCWDT, provide the configuration parameters in the
* cy_stc_mcwdt_config_t structure. Then call
* Cy_MCWDT_Init() to initialize the driver.
* Call Cy_MCWDT_Enable() to enable all specified counters.
*
* You can also set the mode of operation for any counter. If you choose
* interrupt mode, use Cy_MCWDT_SetInterruptMask() with the
* parameter for the masks described in Macro Section. All counter interrupts
* are OR'd together to from a single combined MCWDT interrupt.
* Additionally, enable the Global interrupts and initialize the referenced
* interrupt by setting the priority and the interrupt vector using
* \ref Cy_SysInt_Init() of the sysint driver.
*
* The values of the MCWDT counters can be monitored using
* Cy_MCWDT_GetCount().
*
* CAT1C devices supports MCWDT_B type of counters, which are slightly different
* from MCWDT, which is explained above
*
* A simplified diagram of the MCWDT_B hardware is shown below:
* \image html mcwdt_b.png
*
* \note Please refer to TRM for more information on CAT1C supported MCWDT_B counters.
*
* \note In addition to the MCWDTs, each device has a separate watchdog timer
* (WDT) that can also be used to generate a watchdog reset or periodic
* interrupts. For more information on the WDT, see the appropriate section
* of the PDL.
*
* \section group_mcwdt_more_information More Information
*
* For more information on the MCWDT peripheral, refer to
* the technical reference manual (TRM).
*
* \section group_mcwdt_changelog Changelog
* <table class="doxtable">
*   <tr><th>Version</th><th>Changes</th><th>Reason for Change</th></tr>
*   <tr>
*     <td>1.70</td>
*     <td>Added MCWDT_B type support required for CAT1C devices.<br>Newly added APIs:
*         \n Cy_MCWDT_SetLowerAction(),
*         \n Cy_MCWDT_SetUpperAction(),
*         \n Cy_MCWDT_SetWarnAction(),
*         \n Cy_MCWDT_SetSubCounter2Action(),
*         \n Cy_MCWDT_GetLowerAction(),
*         \n Cy_MCWDT_GetUpperAction(),
*         \n Cy_MCWDT_GetWarnAction(),
*         \n Cy_MCWDT_GetSubCounter2Action(),
*         \n Cy_MCWDT_SetAutoService(),
*         \n Cy_MCWDT_GetAutoService(),
*         \n Cy_MCWDT_SetSleepDeepPause(),
*         \n Cy_MCWDT_GetSleepDeepPause(),
*         \n Cy_MCWDT_SetDebugRun(),
*         \n Cy_MCWDT_GetDebugRun(),
*         \n Cy_MCWDT_SetLowerLimit(),
*         \n Cy_MCWDT_SetUpperLimit(),
*         \n Cy_MCWDT_SetWarnLimit(),
*         \n Cy_MCWDT_GetLowerLimit(),
*         \n Cy_MCWDT_GetUpperLimit(),
*         \n Cy_MCWDT_GetWarnLimit(),
*         \n Cy_MCWDT_WaitForCounterReset(),
*         \n Cy_MCWDT_CpuSelectForDpSlpPauseAction(),
*         \n Cy_MCWDT_GetCascadeMatchCombined().</td>
*     <td>Support for new devices.</td>
*   </tr>
*   <tr>
*     <td>1.60</td>
*     <td>CAT1B, CAT1C devices support.<br>Newly added APIs:
*         \n Cy_MCWDT_GetLowerLimit() to get the lower limit value of the specified counter,
*         \n Cy_MCWDT_SetLowerLimit() to set the the lower limit value of the specified counter,
*         \n Cy_MCWDT_GetLowerLimitMode() to get the lower limit mode of the specified counter,
*         \n Cy_MCWDT_SetLowerLimitMode() to set the lower limit mode of the specified counter,
*         \n Cy_MCWDT_GetLowerLimitCascaded() to get the lower limit registers cascaded value,
*         \n Cy_MCWDT_SetCascadeCarryOutRollOver() to enable the Rollover mode for carryout,
*         \n Cy_MCWDT_GetCascadeCarryOutRollOver() to check if Rollover mode enabled for carryout or not,
*         \n Cy_MCWDT_SetCascadeMatchCombined() to set the match to combined cascade counters,
*         \n Cy_MCWDT_GetCascadeMatchCombined() to report if match is enabled with combined cascade counters or not.</td>
*     <td>Support for new devices.</td>
*   </tr>
*   <tr>
*     <td>1.50.1</td>
*     <td>Minor documentation updates.</td>
*     <td>Documentation enhancement.</td>
*   </tr>
*   <tr>
*     <td>1.50</td>
*     <td>Added support for new family of devices.</td>
*     <td>New device support.</td>
*   </tr>
*   <tr>
*     <td>1.40</td>
*     <td>Fixed/documented MISRA 2012 violations.</td>
*     <td>MISRA 2012 compliance.</td>
*   </tr>
*   <tr>
*     <td>1.30.1</td>
*     <td>Minor documentation updates.</td>
*     <td>Documentation enhancement.</td>
*   </tr>
*   <tr>
*     <td>1.30</td>
*     <td>In version 1.20 the Cy_MCWDT_GetCountCascaded() function
*         returned the wrong value when counter#1 overflowed.
*         This bug is corrected in version 1.30.
*     </td>
*     <td>Defect fixes.
*     </td>
*   </tr>
*   <tr>
*     <td rowspan="2">1.20</td>
*     <td>Flattened the organization of the driver source code into the single
*         source directory and the single include directory.
*     </td>
*     <td>Driver library directory-structure simplification.</td>
*   </tr>
*   <tr>
*     <td>Added register access layer. Use register access macros instead
*         of direct register access using dereferenced pointers.</td>
*     <td>Makes register access device-independent, so that the PDL does
*         not need to be recompiled for each supported part number.</td>
*   </tr>
*   <tr>
*     <td>1.10.1</td>
*     <td>Updated description of the \ref cy_stc_mcwdt_config_t structure type</td>
*     <td>Documentation update and clarification</td>
*   </tr>
*   <tr>
*     <td>1.10</td>
*     <td>Added input parameter validation to the API functions.<br>
*     Added API function GetCountCascaded()</td>
*     <td></td>
*   </tr>
*   <tr>
*     <td>1.0</td>
*     <td>Initial version</td>
*     <td></td>
*   </tr>
* </table>
*
* \defgroup group_mcwdt_macros Macros
* \defgroup group_mcwdt_functions Functions
* \defgroup group_mcwdt_data_structures Data Structures
* \defgroup group_mcwdt_enums Enumerated Types
*/

#ifndef CY_MCWDT_H
#define CY_MCWDT_H

#if defined(__cplusplus)
extern "C" {
#endif

#include "cy_device.h"

#if defined (CY_IP_MXS28SRSS) || defined (CY_IP_MXS40SSRSS) || defined (CY_IP_MXS40SRSS) || defined (CY_IP_MXS22SRSS)

#include <stdbool.h>
#include <stddef.h>
#include "cy_syslib.h"


/**
* \addtogroup group_mcwdt_macros
* \{
*/

/** Driver major version */
#define CY_MCWDT_DRV_VERSION_MAJOR       1

/** Driver minor version */
#define CY_MCWDT_DRV_VERSION_MINOR       70

/** \cond INTERNAL_MACROS */

/***************************************
*        Registers Constants
***************************************/

#define CY_MCWDT_LOCK_CLR0      (1u)
#define CY_MCWDT_LOCK_CLR1      (2u)
#define CY_MCWDT_LOCK_SET01     (3u)

#define CY_MCWDT_BYTE_SHIFT     (8u)
#define CY_MCWDT_C0C1_MODE_MASK (3u)
#define CY_MCWDT_C2_MODE_MASK   (1u)


/***************************************
*            API Constants
***************************************/

#define CY_MCWDT_ALL_WDT_ENABLE_Msk (MCWDT_STRUCT_MCWDT_CTL_WDT_ENABLE0_Msk | MCWDT_STRUCT_MCWDT_CTL_WDT_ENABLE1_Msk | \
                                  MCWDT_STRUCT_MCWDT_CTL_WDT_ENABLE2_Msk)

#define CY_MCWDT_CTR0_Pos (0u)
#define CY_MCWDT_CTR1_Pos (1u)
#define CY_MCWDT_CTR2_Pos (2u)
#define CY_MCWDT_CTR_Pos  (0UL)

/** \endcond */

#define CY_MCWDT_ID       CY_PDL_DRV_ID(0x35u)                      /**< MCWDT PDL ID */

#define CY_MCWDT_CTR0     (1UL << CY_MCWDT_CTR0_Pos)                /**< The sub-counter#0 mask. This macro is used with functions
                                                                   that handle multiple counters, including Cy_MCWDT_Enable(),
                                                                   Cy_MCWDT_Disable(), Cy_MCWDT_ClearInterrupt() and Cy_MCWDT_ResetCounters(). */
#define CY_MCWDT_CTR1     (1UL << CY_MCWDT_CTR1_Pos)                /**< The sub-counter#1 mask. This macro is used with functions
                                                                   that handle multiple counters, including Cy_MCWDT_Enable(),
                                                                   Cy_MCWDT_Disable(), Cy_MCWDT_ClearInterrupt() and Cy_MCWDT_ResetCounters(). */
#define CY_MCWDT_CTR2     (1UL << CY_MCWDT_CTR2_Pos)                /**< The sub-counter#2 mask. This macro is used with functions
                                                                   that handle multiple counters, including Cy_MCWDT_Enable(),
                                                                   Cy_MCWDT_Disable(), Cy_MCWDT_ClearInterrupt() and Cy_MCWDT_ResetCounters(). */
#define CY_MCWDT_CTR_Msk  (CY_MCWDT_CTR0 | CY_MCWDT_CTR1 | CY_MCWDT_CTR2) /**< The mask for all sub-counters. This macro is used with functions
                                                                   that handle multiple counters, including Cy_MCWDT_Enable(),
                                                                   Cy_MCWDT_Disable(), Cy_MCWDT_ClearInterrupt() and Cy_MCWDT_ResetCounters(). */

#if (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3))
/** For compatibility with CAT1C MCWDT driver */
#define MCWDT_STRUCT_Type MCWDT_Type
#endif

/** \} group_mcwdt_macros */


/**
* \addtogroup group_mcwdt_enums
* \{
*/

/** The mcwdt sub-counter identifiers. */
typedef enum
{
    CY_MCWDT_COUNTER0,  /**< Sub-counter#0 identifier. */
    CY_MCWDT_COUNTER1,  /**< Sub-counter#1 identifier. */
    CY_MCWDT_COUNTER2   /**< Sub-counter#2 identifier. */
} cy_en_mcwdtctr_t;

/** The mcwdt modes. */
typedef enum
{
    CY_MCWDT_MODE_NONE,      /**< The No action mode. It is used for Set/GetMode functions. */
    CY_MCWDT_MODE_INT,       /**< The Interrupt mode. It is used for Set/GetMode functions. */
    CY_MCWDT_MODE_RESET,     /**< The Reset mode. It is used for Set/GetMode functions. */
    CY_MCWDT_MODE_INT_RESET  /**< The Three interrupts then watchdog reset mode. It is used for
                               Set/GetMode functions. */
} cy_en_mcwdtmode_t;

/** The mcwdt cascading. */
typedef enum
{
    CY_MCWDT_CASCADE_NONE,  /**< The cascading is disabled. It is used for Set/GetCascade functions. */
    CY_MCWDT_CASCADE_C0C1,  /**< The sub-counter#1 is clocked by LFCLK or from sub-counter#0 cascade.
                              It is used for Set/GetCascade functions. */
    CY_MCWDT_CASCADE_C1C2,  /**< The sub-counter#2 is clocked by LFCLK or from sub-counter#1 cascade.
                              It is used for Set/GetCascade functions. */
    CY_MCWDT_CASCADE_BOTH   /**< The sub-counter#1 is clocked by LFCLK or from sub-counter#0 cascade
                              and the sub-counter#2 is clocked by LFCLK or from sub-counter#1 cascade.
                              It is used for Set/GetCascade functions. */
} cy_en_mcwdtcascade_t;

#if defined (CY_IP_MXS28SRSS) || defined (CY_IP_MXS40SSRSS) || defined (CY_IP_MXS22SRSS)
/** The mcwdt lower limit identifiers. */
/**
* \note
* This enum is available for CAT1B devices.
**/
typedef enum
{
    CY_MCWDT_LOWER_LIMIT0,  /**< Lower limit for Sub-counter#0 identifier. */
    CY_MCWDT_LOWER_LIMIT1,  /**< Lower limit for Sub-counter#1 identifier. */
} cy_en_mcwdtlowerlimit_t;

/** The mcwdt lower limit mode identifiers. */
/**
* \note
* This enum is available for CAT1B devices.
**/
typedef enum
{
    CY_MCWDT_LOWER_LIMIT_MODE_NOTHING,  /**< Do nothing. */
    CY_MCWDT_LOWER_LIMIT_MODE_INT,      /**< Assert WDT_INTx. */
    CY_MCWDT_LOWER_LIMIT_MODE_RESET,         /**< Assert WDT Reset. */
} cy_en_mcwdtlowerlimitmode_t;
#endif /* CY_IP_MXS28SRSS, CY_IP_MXS40SSRSS, CY_IP_MXS22SRSS*/

/** The MCWDT error codes. */
typedef enum
{
    CY_MCWDT_SUCCESS = 0x00u,                                            /**< Successful */
    CY_MCWDT_BAD_PARAM = CY_MCWDT_ID | CY_PDL_STATUS_ERROR | 0x01u,     /**< One or more invalid parameters */
} cy_en_mcwdt_status_t;

#if (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3))
/** The MCWDT Enable/Disable identifiers. */
/**
* \note
* Below enum is available for CAT1C devices only.
**/
typedef enum
{
    CY_MCWDT_DISABLE = 0u,
    CY_MCWDT_ENABLE,
} cy_en_mcwdt_enable_t;

/** The MCWDT Deep Sleep Cores identifiers. */
/**
* \note
* Below enum is available for CAT1C devices only.
**/
typedef enum
{
    CY_MCWDT_PAUSED_BY_DPSLP_CM0       = 0u,
    CY_MCWDT_PAUSED_BY_DPSLP_CM7_0     = 1u,
    CY_MCWDT_PAUSED_BY_DPSLP_CM7_1     = 2u,
    CY_MCWDT_PAUSED_BY_NO_CORE         = 3u,
} cy_en_mcwdt_select_core_t;

/** The MCWDT subcounter 2 actions. */
/**
* \note
* Below enum is available for CAT1C devices only.
**/
typedef enum
{
    CY_MCWDT_CNT2_ACTION_NONE,
    CY_MCWDT_CNT2_ACTION_INT,
} cy_en_mcwdt_cnt2_action_t;

/** The MCWDT lower and upper actions. */
/**
* \note
* Below enum is available for CAT1C devices only.
**/
typedef enum
{
    CY_MCWDT_ACTION_NONE,                 /**< The No action mode. It is used for Set/GetMode functions. */
    CY_MCWDT_ACTION_FAULT,                /**< The Fault mode. It is used for Set/GetMode functions. */
    CY_MCWDT_ACTION_FAULT_THEN_RESET,     /**< The Reset mode. It is used for Set/GetMode functions. */
} cy_en_mcwdt_lower_upper_action_t;

/** The MCWDT warn actions. */
typedef enum
{
    CY_MCWDT_WARN_ACTION_NONE,
    CY_MCWDT_WARN_ACTION_INT,
} cy_en_mcwdt_warn_action_t;

#endif /* (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3)) */

/** \} group_mcwdt_enums */

/**
* \addtogroup group_mcwdt_data_structures
* \{
*/

/** The MCWDT component configuration structure. */
#if (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3))
typedef struct
{
    uint16_t c0LowerLimit;                              /**< The sub-counter#0 lower limit value, for reset or fault.
                                                        Range: 0 - 65535 for c0AutoService = 0 and 1 - 65535 for c0AutoService = 1.
                                                        Only for CAT1C devices*/
    uint16_t c0UpperLimit;                              /**< The sub-counter#0 upper limit value, for reset or fault.
                                                        Range: 0 - 65535 for c0AutoService = 0 and 1 - 65535 for c0AutoService = 1.
                                                        Only for CAT1C devices*/
    uint16_t c0WarnLimit;                               /**< The sub-counter#0 warn limit value, for interrupt.
                                                        Range: 0 - 65535 for c0AutoService = 0 and 1 - 65535 for c0AutoService = 1.
                                                        Only for CAT1C devices*/
    cy_en_mcwdt_lower_upper_action_t  c0LowerAction;    /**< The sub-counter#0 action. It can have the following values:
                                                        \ref cy_en_mcwdt_lower_upper_action_t. Only for CAT1C devices*/
    cy_en_mcwdt_lower_upper_action_t  c0UpperAction;    /**< The sub-counter#0 action. It can have the following values:
                                                        \ref cy_en_mcwdt_lower_upper_action_t. Only for CAT1C devices*/
    cy_en_mcwdt_warn_action_t  c0WarnAction;            /**< The sub-counter#0 warn action. It can have the following values:
                                                        \ref cy_en_mcwdt_warn_action_t. Only for CAT1C devices*/
    cy_en_mcwdt_enable_t     c0AutoService;             /**< The sub-counter#0 Auto Service parameter enabled/disabled.
                                                        Range: FALSE - TRUE. Only for CAT1C devices*/
    cy_en_mcwdt_enable_t     c0SleepDeepPause;          /**< The sub-counter#0 Auto Service parameter enabled/disabled.
                                                        Range: FALSE - TRUE. Only for CAT1C devices*/
    cy_en_mcwdt_enable_t     c0DebugRun;                /**< The sub-counter#0 Auto Service parameter enabled/disabled.
                                                        Range: FALSE - TRUE. Only for CAT1C devices*/
    uint16_t c1LowerLimit;                              /**< The sub-counter#0 lower limit value, for reset or fault.
                                                        Range: 0 - 65535 for c1AutoService = 0 and 1 - 65535 for c1AutoService = 1.
                                                        Only for CAT1C devices*/
    uint16_t c1UpperLimit;                              /**< The sub-counter#0 upper limit value, for reset or fault.
                                                        Range: 0 - 65535 for c1AutoService = 0 and 1 - 65535 for c1AutoService = 1.
                                                        Only for CAT1C devices*/
    uint16_t c1WarnLimit;                               /**< The sub-counter#0 warn limit value, for interrupt.
                                                        Range: 0 - 65535 for c1AutoService = 0 and 1 - 65535 for c1AutoService = 1.
                                                        Only for CAT1C devices*/
    cy_en_mcwdt_lower_upper_action_t  c1LowerAction;    /**< The sub-counter#1 action. It can have the following values:
                                                        \ref cy_en_mcwdt_lower_upper_action_t. Only for CAT1C devices*/
    cy_en_mcwdt_lower_upper_action_t  c1UpperAction;    /**< The sub-counter#1 action. It can have the following values:
                                                        \ref cy_en_mcwdt_lower_upper_action_t. Only for CAT1C devices*/
    cy_en_mcwdt_warn_action_t  c1WarnAction;            /**< The sub-counter#1 warn action. It can have the following values:
                                                        \ref cy_en_mcwdt_warn_action_t. Only for CAT1C devices*/
    cy_en_mcwdt_enable_t     c1AutoService;             /**< The sub-counter#1 Auto Service parameter enabled/disabled.
                                                        Range: FALSE - TRUE. Only for CAT1C devices*/
    cy_en_mcwdt_enable_t     c1SleepDeepPause;          /**< The sub-counter#1 Auto Service parameter enabled/disabled.
                                                        Range: FALSE - TRUE. Only for CAT1C devices*/
    cy_en_mcwdt_enable_t     c1DebugRun;                /**< The sub-counter#1 Auto Service parameter enabled/disabled.
                                                        Range: FALSE - TRUE. Only for CAT1C devices*/
    uint32_t  c2ToggleBit;                              /**< The sub-counter#2 Period / Toggle Bit value. Only for CAT1C devices*/
    cy_en_mcwdt_cnt2_action_t  c2Action;                /**< The sub-counter#2 mode. It can have the following values:
                                                        \ref cy_en_mcwdt_cnt2_action_t. Only for CAT1C devices*/
    cy_en_mcwdt_enable_t     c2SleepDeepPause;          /**< The sub-counter#2 Auto Service parameter enabled/disabled.
                                                        Range: FALSE - TRUE. Only for CAT1C devices*/
    cy_en_mcwdt_enable_t     c2DebugRun;                /**< The sub-counter#2 Auto Service parameter enabled/disabled. Only for CAT1C devices **/

    cy_en_mcwdt_select_core_t coreSelect;               /**< Selecting the the core. The DeepSleep of the core pauses this MCWDT counter Only for CAT1C devices **/
} cy_stc_mcwdt_config_t;
#endif


#if defined (CY_IP_MXS28SRSS) || defined (CY_IP_MXS40SSRSS) || (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION < 3)) || defined (CY_IP_MXS22SRSS)
/**
* \note
* Below structure variables are available for CAT1A, CAT1B and CAT1D devices.
**/
typedef struct
{
    uint16_t c0Match;        /**< The sub-counter#0 match comparison value, for interrupt or watchdog timeout.
                                  Range: 0 - 65535 for c0ClearOnMatch = 0 and 1 - 65535 for
                                  c0ClearOnMatch = 1. For CAT1A, CAT1B and CAT1D devices */
    uint16_t c1Match;        /**< The sub-counter#1 match comparison value, for interrupt or watchdog timeout.
                                  Range: 0 - 65535 for c1ClearOnMatch = 0 and 1 - 65535 for
                                  c1ClearOnMatch = 1. For CAT1A, CAT1B and CAT1D devices */
    uint8_t  c0Mode;         /**< The sub-counter#0 mode. It can have the following values: \ref CY_MCWDT_MODE_NONE,
                                  \ref CY_MCWDT_MODE_INT, \ref CY_MCWDT_MODE_RESET and \ref CY_MCWDT_MODE_INT_RESET.
                                  For CAT1A, CAT1B and CAT1D devices */
    uint8_t  c1Mode;         /**< The sub-counter#1 mode.  It can have the following values: \ref CY_MCWDT_MODE_NONE,
                                  \ref CY_MCWDT_MODE_INT, \ref CY_MCWDT_MODE_RESET and \ref CY_MCWDT_MODE_INT_RESET.
                                  For CAT1A, CAT1B and CAT1D devices */
    uint8_t  c2ToggleBit;    /**< The sub-counter#2 Period / Toggle Bit value.
                                  Range: 0 - 31. For CAT1A, CAT1B and CAT1D devices */
    uint8_t  c2Mode;         /**< The sub-counter#2 mode. It can have the following values: \ref CY_MCWDT_MODE_NONE
                                  and \ref CY_MCWDT_MODE_INT. For CAT1A, CAT1B and CAT1D devices */
#if defined (CY_IP_MXS28SRSS) || defined (CY_IP_MXS40SSRSS) || defined (CY_IP_MXS22SRSS)
    uint16_t c0LowerLimit;        /**< Lower limit for sub-counter 0 of this MCWDT.
                                  Range: 0 - 65535. Only for CAT1B devices */
    uint16_t c1LowerLimit;        /**< Lower limit for sub-counter 0 of this MCWDT.
                                  Range: 0 - 65535. Only for CAT1B devices */
    uint16_t c0LowerLimitMode;        /**< Watchdog Counter Action on service before lower limit.
                                  Range: 0 - 2., 0 - Do nothing, 1 - Assert WDT_INTx, 2 - Assert WDT Reset.
                                  Only for CAT1B devices */
    uint16_t c1LowerLimitMode;        /**< Watchdog Counter Action on service before lower limit.
                                  Range: 0 - 2., 0 - Do nothing, 1 - Assert WDT_INTx, 2 - Assert WDT Reset.
                                  Only for CAT1B devices */
#endif /* CY_IP_MXS28SRSS, CY_IP_MXS40SSRSS, CY_IP_MXS22SRSS */

/**
* \note
* This parameter is available for devices having MXS40SSRSS IP.
**/

#if defined (CY_IP_MXS40SSRSS) || defined (CY_IP_MXS22SRSS) || defined (CY_DOXYGEN)
    bool  c0c1carryoutconfig;      /**< Carryout behaviour that applies when counter 0 and 1 are cascaded
                                      false: carry out on counter 0 match, true: carry out on counter 0 roll-over.
                                      Only for CAT1B devices */
    bool  c0c1matchconfig;         /**< Matching behaviour that applies when counter 0 and 1 are cascaded
                                      false: Match based on counter 1 alone, true: Match based on counter 1 and 0 simultaneously.
                                      Only for CAT1B devices */
    bool  c1c2carryoutconfig;      /**< Carryout behaviour that applies when counter 1 and 2 are cascaded
                                      false: carry out on counter 1 match, true: carry out on counter 1 roll-over.
                                      Only for CAT1B devices */
    bool  c1c2matchconfig;         /**< Matching behaviour that applies when counter 1 and 2 are cascaded
                                      false: Match based on counter 1 alone, true: Match based on counter 2 and 1 simultaneously.
                                      Only for CAT1B devices */
#endif /* CY_IP_MXS40SSRSS, CY_IP_MXS22SRSS */

    bool     c0ClearOnMatch; /**< The sub-counter#0 Clear On Match parameter enabled/disabled. For CAT1A, CAT1B and CAT1D devices */
    bool     c1ClearOnMatch; /**< The sub-counter#1 Clear On Match parameter enabled/disabled. For CAT1A, CAT1B and CAT1D devices */
    bool     c0c1Cascade;    /**< The sub-counter#1 is clocked by LFCLK or from sub-counter#0 cascade. For CAT1A, CAT1B and CAT1D devices */
    bool     c1c2Cascade;    /**< The sub-counter#2 is clocked by LFCLK or from sub-counter#1 cascade. For CAT1A, CAT1B and CAT1D devices */
} cy_stc_mcwdt_config_t;
#endif
/** \} group_mcwdt_data_structures */


/** \cond PARAM_CHECK_MACROS */

/** Parameter check macros */
#define CY_MCWDT_IS_CNTS_MASK_VALID(counters)  (0U == ((counters) & (uint32_t)~CY_MCWDT_CTR_Msk))

#if defined (CY_IP_MXS28SRSS) || defined (CY_IP_MXS40SSRSS) || defined (CY_IP_MXS22SRSS)
#define CY_MCWDT_IS_LOWER_LIMIT_VALID(counter)             ((CY_MCWDT_LOWER_LIMIT0 == (counter)) || \
                                                           (CY_MCWDT_LOWER_LIMIT1 == (counter)))

#define CY_MCWDT_IS_LOWER_LIMIT_MODE_VALID(mode)           ((CY_MCWDT_LOWER_LIMIT_MODE_NOTHING == (mode)) || \
                                                           (CY_MCWDT_LOWER_LIMIT_MODE_INT == (mode))       || \
                                                           (CY_MCWDT_LOWER_LIMIT_MODE_RESET == (mode)))
#endif /* CY_IP_MXS28SRSS, CY_IP_MXS40SSRSS, CY_IP_MXS22SRSS */

#define CY_MCWDT_IS_CNT_NUM_VALID(counter)    ((CY_MCWDT_COUNTER0 == (counter)) || \
                                               (CY_MCWDT_COUNTER1 == (counter)) || \
                                               (CY_MCWDT_COUNTER2 == (counter)))

#define CY_MCWDT_IS_MODE_VALID(mode)          ((CY_MCWDT_MODE_NONE == (mode)) || \
                                               (CY_MCWDT_MODE_INT == (mode)) || \
                                               (CY_MCWDT_MODE_RESET == (mode)) || \
                                               (CY_MCWDT_MODE_INT_RESET == (mode)))

#define CY_MCWDT_IS_ENABLE_VALID(enable)      (1UL >= (enable))


#define CY_MCWDT_IS_CASCADE_VALID(cascade)    ((CY_MCWDT_CASCADE_NONE == (cascade)) || \
                                               (CY_MCWDT_CASCADE_C0C1 == (cascade)) || \
                                               (CY_MCWDT_CASCADE_C1C2 == (cascade)) || \
                                               (CY_MCWDT_CASCADE_BOTH == (cascade)))

#define CY_MCWDT_IS_MATCH_VALID(clearOnMatch, match)  ((clearOnMatch) ? (1UL <= (match)) : true)

#define CY_MCWDT_IS_BIT_VALID(bit)            (31UL >= (bit))

#if defined (CY_IP_MXS40SSRSS) || defined (CY_IP_MXS22SRSS)
#define CY_MCWDT_IS_CARRYMODE_CASCADE_VALID(cascade)    ((CY_MCWDT_CASCADE_C0C1 == (cascade)) || \
                                                        (CY_MCWDT_CASCADE_C1C2 == (cascade)))
#endif

/** \endcond */


/*******************************************************************************
*        Function Prototypes
*******************************************************************************/

/**
* \addtogroup group_mcwdt_functions
* \{
*/
cy_en_mcwdt_status_t     Cy_MCWDT_Init(MCWDT_STRUCT_Type *base, cy_stc_mcwdt_config_t const *config);
                void     Cy_MCWDT_DeInit(MCWDT_STRUCT_Type *base);
__STATIC_INLINE void     Cy_MCWDT_Enable(MCWDT_STRUCT_Type *base, uint32_t counters, uint16_t waitUs);
__STATIC_INLINE void     Cy_MCWDT_Disable(MCWDT_STRUCT_Type *base, uint32_t counters, uint16_t waitUs);
__STATIC_INLINE uint32_t Cy_MCWDT_GetEnabledStatus(MCWDT_STRUCT_Type const *base, cy_en_mcwdtctr_t counter);
__STATIC_INLINE void     Cy_MCWDT_Lock(MCWDT_STRUCT_Type *base);
__STATIC_INLINE void     Cy_MCWDT_Unlock(MCWDT_STRUCT_Type *base);
__STATIC_INLINE uint32_t Cy_MCWDT_GetLockedStatus(MCWDT_STRUCT_Type const *base);
#if defined (CY_IP_MXS28SRSS) || defined (CY_IP_MXS40SSRSS) || defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION < 3) || defined (CY_IP_MXS22SRSS)
__STATIC_INLINE void     Cy_MCWDT_SetMode(MCWDT_STRUCT_Type *base, cy_en_mcwdtctr_t counter, cy_en_mcwdtmode_t mode);
__STATIC_INLINE cy_en_mcwdtmode_t Cy_MCWDT_GetMode(MCWDT_STRUCT_Type const *base, cy_en_mcwdtctr_t counter);
__STATIC_INLINE void     Cy_MCWDT_SetClearOnMatch(MCWDT_STRUCT_Type *base, cy_en_mcwdtctr_t counter, uint32_t enable);
__STATIC_INLINE uint32_t Cy_MCWDT_GetClearOnMatch(MCWDT_STRUCT_Type const *base, cy_en_mcwdtctr_t counter);
__STATIC_INLINE void     Cy_MCWDT_SetCascade(MCWDT_STRUCT_Type *base, cy_en_mcwdtcascade_t cascade);
__STATIC_INLINE cy_en_mcwdtcascade_t Cy_MCWDT_GetCascade(MCWDT_STRUCT_Type const *base);
__STATIC_INLINE void     Cy_MCWDT_SetMatch(MCWDT_STRUCT_Type *base, cy_en_mcwdtctr_t counter, uint32_t match, uint16_t waitUs);
__STATIC_INLINE uint32_t Cy_MCWDT_GetMatch(MCWDT_STRUCT_Type const *base, cy_en_mcwdtctr_t counter);
uint32_t Cy_MCWDT_GetCountCascaded(MCWDT_STRUCT_Type const *base);
#endif
__STATIC_INLINE void     Cy_MCWDT_SetToggleBit(MCWDT_STRUCT_Type *base, uint32_t bit);
__STATIC_INLINE uint32_t Cy_MCWDT_GetToggleBit(MCWDT_STRUCT_Type const *base);
__STATIC_INLINE uint32_t Cy_MCWDT_GetCount(MCWDT_STRUCT_Type const *base, cy_en_mcwdtctr_t counter);
__STATIC_INLINE void     Cy_MCWDT_ResetCounters(MCWDT_STRUCT_Type *base, uint32_t counters, uint16_t waitUs);
__STATIC_INLINE uint32_t Cy_MCWDT_GetInterruptStatus(MCWDT_STRUCT_Type const *base);
__STATIC_INLINE void     Cy_MCWDT_ClearInterrupt(MCWDT_STRUCT_Type *base, uint32_t counters);
__STATIC_INLINE void     Cy_MCWDT_SetInterrupt(MCWDT_STRUCT_Type *base, uint32_t counters);
__STATIC_INLINE uint32_t Cy_MCWDT_GetInterruptMask(MCWDT_STRUCT_Type const *base);
__STATIC_INLINE void     Cy_MCWDT_SetInterruptMask(MCWDT_STRUCT_Type *base, uint32_t counters);
__STATIC_INLINE uint32_t Cy_MCWDT_GetInterruptStatusMasked(MCWDT_STRUCT_Type const *base);
#if defined (CY_IP_MXS28SRSS) || defined (CY_IP_MXS40SSRSS) || defined (CY_IP_MXS22SRSS)
__STATIC_INLINE uint32_t Cy_MCWDT_GetLowerLimit(MCWDT_STRUCT_Type const *base, cy_en_mcwdtlowerlimit_t counter);
__STATIC_INLINE void Cy_MCWDT_SetLowerLimit(MCWDT_STRUCT_Type *base, cy_en_mcwdtlowerlimit_t counter, uint32_t lowerLimit, uint16_t waitUs);
__STATIC_INLINE cy_en_mcwdtlowerlimitmode_t Cy_MCWDT_GetLowerLimitMode(MCWDT_STRUCT_Type const *base, cy_en_mcwdtlowerlimit_t counter);
__STATIC_INLINE void Cy_MCWDT_SetLowerLimitMode(MCWDT_STRUCT_Type *base, cy_en_mcwdtlowerlimit_t counter, cy_en_mcwdtlowerlimitmode_t mode);
__STATIC_INLINE uint32_t Cy_MCWDT_GetLowerLimitCascaded(MCWDT_STRUCT_Type const *base);
#endif /* CY_IP_MXS28SRSS, CY_IP_MXS40SSRSS, CY_IP_MXS22SRSS */

#if defined (CY_IP_MXS40SSRSS) || defined (CY_IP_MXS22SRSS)
__STATIC_INLINE void Cy_MCWDT_SetCascadeCarryOutRollOver(MCWDT_STRUCT_Type *base, cy_en_mcwdtcascade_t counter, bool carryoutconfig);
__STATIC_INLINE bool Cy_MCWDT_GetCascadeCarryOutRollOver(MCWDT_STRUCT_Type const *base, cy_en_mcwdtcascade_t counter);

__STATIC_INLINE void Cy_MCWDT_SetCascadeMatchCombined(MCWDT_STRUCT_Type *base, cy_en_mcwdtcascade_t counter, bool matchconfig);
__STATIC_INLINE bool Cy_MCWDT_GetCascadeMatchCombined(MCWDT_STRUCT_Type const *base, cy_en_mcwdtcascade_t counter);
#endif /* CY_IP_MXS40SSRSS,CY_IP_MXS22SRSS */

#if (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3))
void Cy_MCWDT_CpuSelectForDpSlpPauseAction(MCWDT_Type *base, cy_en_mcwdt_select_core_t core);
void Cy_MCWDT_SetLowerAction(MCWDT_Type *base, cy_en_mcwdtctr_t counter, cy_en_mcwdt_lower_upper_action_t action);
void Cy_MCWDT_SetUpperAction(MCWDT_Type *base, cy_en_mcwdtctr_t counter, cy_en_mcwdt_lower_upper_action_t action);
void Cy_MCWDT_SetWarnAction(MCWDT_Type *base, cy_en_mcwdtctr_t counter, cy_en_mcwdt_warn_action_t action);
void Cy_MCWDT_SetSubCounter2Action(MCWDT_Type *base, cy_en_mcwdt_cnt2_action_t action);
cy_en_mcwdt_lower_upper_action_t Cy_MCWDT_GetLowerAction(MCWDT_Type *base, cy_en_mcwdtctr_t counter);
cy_en_mcwdt_lower_upper_action_t  Cy_MCWDT_GetUpperAction(MCWDT_Type *base, cy_en_mcwdtctr_t counter);
cy_en_mcwdt_warn_action_t Cy_MCWDT_GetWarnAction(MCWDT_Type *base, cy_en_mcwdtctr_t counter);
cy_en_mcwdt_cnt2_action_t Cy_MCWDT_GetSubCounter2Action(MCWDT_Type *base);
void Cy_MCWDT_SetAutoService(MCWDT_Type *base, cy_en_mcwdtctr_t counter, uint32_t enable);
uint32_t Cy_MCWDT_GetAutoService(MCWDT_Type const *base, cy_en_mcwdtctr_t counter);
uint32_t Cy_MCWDT_GetSleepDeepPause(MCWDT_Type const *base, cy_en_mcwdtctr_t counter);
void Cy_MCWDT_SetSleepDeepPause(MCWDT_Type *base, cy_en_mcwdtctr_t counter, uint32_t enable);
void Cy_MCWDT_SetDebugRun(MCWDT_Type *base, cy_en_mcwdtctr_t counter, uint32_t enable);
uint32_t Cy_MCWDT_GetDebugRun(MCWDT_Type const *base, cy_en_mcwdtctr_t counter);
void Cy_MCWDT_SetLowerLimit(MCWDT_Type *base, cy_en_mcwdtctr_t counter, uint16_t limit, uint16_t waitUs);
void Cy_MCWDT_SetUpperLimit(MCWDT_Type *base, cy_en_mcwdtctr_t counter, uint16_t limit, uint16_t waitUs);
void Cy_MCWDT_SetWarnLimit(MCWDT_Type *base, cy_en_mcwdtctr_t counter, uint16_t limit, uint16_t waitUs);
uint16_t Cy_MCWDT_GetUpperLimit(MCWDT_Type *base, cy_en_mcwdtctr_t counter);
uint16_t Cy_MCWDT_GetWarnLimit(MCWDT_Type *base, cy_en_mcwdtctr_t counter);
void Cy_MCWDT_WaitForCounterReset(MCWDT_Type *base, cy_en_mcwdtctr_t counter);
void Cy_MCWDT_ClearWatchdog(MCWDT_Type *base, uint32_t counters);
uint16_t Cy_MCWDT_GetLowerLimit(MCWDT_Type *base, cy_en_mcwdtctr_t counter);

#endif


/*******************************************************************************
* Function Name: Cy_MCWDT_Enable
****************************************************************************//**
*
*  Enables all specified counters.
*
*  \param base
*  The base pointer to a structure that describes registers.
*
*  \param counters
*  OR of all counters to enable. See the \ref CY_MCWDT_CTR0, CY_MCWDT_CTR1, and
*  CY_MCWDT_CTR2  macros.
*
*  \param waitUs
*  The function waits for some delay in microseconds before returning,
*  because the counter begins counting after two lf_clk cycles pass.
*  The recommended value is 93 us.
*  \note
*  Setting this parameter to a zero means No wait. In this case, it is
*  the user's responsibility to check whether the selected counters were enabled
*  immediately after the function call. This can be done by the
*  Cy_MCWDT_GetEnabledStatus() API.
*
*******************************************************************************/
__STATIC_INLINE void Cy_MCWDT_Enable(MCWDT_STRUCT_Type *base, uint32_t counters, uint16_t waitUs)
{
#if (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3))

    if (0UL != (counters & CY_MCWDT_CTR0))
    {
        MCWDT_CTR_CTL(base, CY_MCWDT_COUNTER0) |= MCWDT_CTR_CTL_ENABLE_Msk;
    }
    if (0UL != (counters & CY_MCWDT_CTR1))
    {
        MCWDT_CTR_CTL(base, CY_MCWDT_COUNTER1) |= MCWDT_CTR_CTL_ENABLE_Msk;
    }
    if (0UL != (counters & CY_MCWDT_CTR2))
    {
        MCWDT_CTR2_CTL(base) |= MCWDT_CTR2_CTL_ENABLE_Msk;
    }

#else
    uint32_t enableCounters;

    CY_ASSERT_L2(CY_MCWDT_IS_CNTS_MASK_VALID(counters));

    /* Extract particular counters for enable */
    enableCounters = ((0UL != (counters & CY_MCWDT_CTR0)) ? MCWDT_STRUCT_MCWDT_CTL_WDT_ENABLE0_Msk : 0UL) |
                     ((0UL != (counters & CY_MCWDT_CTR1)) ? MCWDT_STRUCT_MCWDT_CTL_WDT_ENABLE1_Msk : 0UL) |
                     ((0UL != (counters & CY_MCWDT_CTR2)) ? MCWDT_STRUCT_MCWDT_CTL_WDT_ENABLE2_Msk : 0UL);

    MCWDT_CTL(base) |= enableCounters;
#endif

    Cy_SysLib_DelayUs(waitUs);
}


/*******************************************************************************
* Function Name: Cy_MCWDT_Disable
****************************************************************************//**
*
*  Disables all specified counters.
*
*  \param base
*  The base pointer to a structure describing registers.
*
*  \param counters
*  OR of all counters to disable. See the \ref CY_MCWDT_CTR0, CY_MCWDT_CTR1, and
*  CY_MCWDT_CTR2 macros.
*
*  \param waitUs
*  The function waits for some delay in microseconds before returning,
*  because the counter stops counting after two lf_clk cycles pass.
*  The recommended value is 93 us.
*  \note
*  Setting this parameter to a zero means No wait. In this case, it is
*  the user's responsibility to check whether the selected counters were disabled
*  immediately after the function call. This can be done by the
*  Cy_MCWDT_GetEnabledStatus() API.
*
*******************************************************************************/
__STATIC_INLINE void Cy_MCWDT_Disable(MCWDT_STRUCT_Type *base, uint32_t counters, uint16_t waitUs)
{
#if (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3))

    if (0UL != (counters & CY_MCWDT_CTR0))
    {
        MCWDT_CTR_CTL(base, CY_MCWDT_COUNTER0) &= (uint32_t) ~MCWDT_CTR_CTL_ENABLE_Msk;
    }
    if (0UL != (counters & CY_MCWDT_CTR1))
    {
        MCWDT_CTR_CTL(base, CY_MCWDT_COUNTER1) &= (uint32_t) ~MCWDT_CTR_CTL_ENABLE_Msk;
    }
    if (0UL != (counters & CY_MCWDT_CTR2))
    {
        MCWDT_CTR2_CTL(base) &= (uint32_t) ~MCWDT_CTR2_CTL_ENABLE_Msk;
    }
#else
    uint32_t disableCounters;

    CY_ASSERT_L2(CY_MCWDT_IS_CNTS_MASK_VALID(counters));

    /* Extract particular counters for disable */
    disableCounters = ((0UL != (counters & CY_MCWDT_CTR0)) ? MCWDT_STRUCT_MCWDT_CTL_WDT_ENABLE0_Msk : 0UL) |
                      ((0UL != (counters & CY_MCWDT_CTR1)) ? MCWDT_STRUCT_MCWDT_CTL_WDT_ENABLE1_Msk : 0UL) |
                      ((0UL != (counters & CY_MCWDT_CTR2)) ? MCWDT_STRUCT_MCWDT_CTL_WDT_ENABLE2_Msk : 0UL);

    MCWDT_CTL(base) &= ~disableCounters;
#endif

    Cy_SysLib_DelayUs(waitUs);
}


/*******************************************************************************
* Function Name: Cy_MCWDT_GetEnabledStatus
****************************************************************************//**
*
*  Reports the enabled status of the specified counter.
*
*  \param base
*  The base pointer to a structure that describes registers.
*
*  \param counter
*  The number of the MCWDT counter. The valid range is [0-2].
*
*  \return
*  The status of the MCWDT counter: 0 = disabled, 1 = enabled.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_MCWDT_GetEnabledStatus(MCWDT_STRUCT_Type const *base, cy_en_mcwdtctr_t counter)
{
    uint32_t status = 0u;

    CY_ASSERT_L3(CY_MCWDT_IS_CNT_NUM_VALID(counter));

#if (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3))
    switch (counter)
    {
    case CY_MCWDT_COUNTER0:
        status = _FLD2VAL(MCWDT_CTR_CTL_ENABLE, MCWDT_CTR_CTL(base, CY_MCWDT_COUNTER0));
        break;
    case CY_MCWDT_COUNTER1:
         status = _FLD2VAL(MCWDT_CTR_CTL_ENABLE, MCWDT_CTR_CTL(base, CY_MCWDT_COUNTER1));
        break;
    case CY_MCWDT_COUNTER2:
        status = _FLD2VAL(MCWDT_CTR2_CTL_ENABLE, MCWDT_CTR2_CTL(base));
        break;
    default:
        CY_ASSERT(0u != 0u);
    break;
    }
#else
    switch (counter)
    {
        case CY_MCWDT_COUNTER0:
            status = _FLD2VAL(MCWDT_STRUCT_MCWDT_CTL_WDT_ENABLED0, MCWDT_CTL(base));
            break;
        case CY_MCWDT_COUNTER1:
            status = _FLD2VAL(MCWDT_STRUCT_MCWDT_CTL_WDT_ENABLED1, MCWDT_CTL(base));
            break;
        case CY_MCWDT_COUNTER2:
            status = _FLD2VAL(MCWDT_STRUCT_MCWDT_CTL_WDT_ENABLED2, MCWDT_CTL(base));
            break;

        default:
            CY_ASSERT(0u != 0u);
        break;
    }
#endif

    return (status);
}


/*******************************************************************************
* Function Name: Cy_MCWDT_Lock
****************************************************************************//**
*
*  Locks out configuration changes to all MCWDT registers.
*
*  \param base
*  The base pointer to a structure that describes registers.
*
*******************************************************************************/
__STATIC_INLINE void Cy_MCWDT_Lock(MCWDT_STRUCT_Type *base)
{
    uint32_t interruptState;

    interruptState = Cy_SysLib_EnterCriticalSection();
#if (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3))
    MCWDT_LOCK(base) = _CLR_SET_FLD32U(MCWDT_LOCK(base), MCWDT_LOCK_MCWDT_LOCK, CY_MCWDT_LOCK_SET01);
#else
    MCWDT_LOCK(base) = _CLR_SET_FLD32U(MCWDT_LOCK(base), MCWDT_STRUCT_MCWDT_LOCK_MCWDT_LOCK, (uint32_t)CY_MCWDT_LOCK_SET01);
#endif

    Cy_SysLib_ExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: Cy_MCWDT_Unlock
****************************************************************************//**
*
*  Unlocks the MCWDT configuration registers.
*
*  \param base
*  The base pointer to a structure that describes registers.
*
*******************************************************************************/
__STATIC_INLINE void Cy_MCWDT_Unlock(MCWDT_STRUCT_Type *base)
{
    uint32_t interruptState;

    interruptState = Cy_SysLib_EnterCriticalSection();
#if (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3))
    MCWDT_LOCK(base) = _CLR_SET_FLD32U(MCWDT_LOCK(base), MCWDT_LOCK_MCWDT_LOCK, (uint32_t)CY_MCWDT_LOCK_CLR0);
    MCWDT_LOCK(base) = _CLR_SET_FLD32U(MCWDT_LOCK(base), MCWDT_LOCK_MCWDT_LOCK, (uint32_t)CY_MCWDT_LOCK_CLR1);
#else
    MCWDT_LOCK(base) = _CLR_SET_FLD32U(MCWDT_LOCK(base), MCWDT_STRUCT_MCWDT_LOCK_MCWDT_LOCK, (uint32_t)CY_MCWDT_LOCK_CLR0);
    MCWDT_LOCK(base) = _CLR_SET_FLD32U(MCWDT_LOCK(base), MCWDT_STRUCT_MCWDT_LOCK_MCWDT_LOCK, (uint32_t)CY_MCWDT_LOCK_CLR1);
#endif
    Cy_SysLib_ExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: Cy_MCWDT_GetLockStatus
****************************************************************************//**
*
*  Reports the locked/unlocked state of the MCWDT.
*
*  \param base
*  The base pointer to a structure that describes registers.
*
*  \return
*  The state of the MCWDT counter: 0 = unlocked, 1 = locked.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_MCWDT_GetLockedStatus(MCWDT_STRUCT_Type const *base)
{
#if (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3))
    return ((0UL !=_FLD2VAL(MCWDT_LOCK_MCWDT_LOCK, MCWDT_LOCK(base))) ? 1UL : 0UL);
#else
    return ((0UL != (MCWDT_LOCK(base) & MCWDT_STRUCT_MCWDT_LOCK_MCWDT_LOCK_Msk)) ? 1UL : 0UL);
#endif
}


#if defined (CY_IP_MXS28SRSS) || defined (CY_IP_MXS40SSRSS) || defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION < 3) || defined (CY_IP_MXS22SRSS)

/*******************************************************************************
* Function Name: Cy_MCWDT_SetMode
****************************************************************************//**
*
*  Sets the mode of the specified counter.
*
*  \param base
*  The base pointer to a structure that describes registers.
*
*  \param counter
*  The number of the WDT counter. The valid range is [0-2].
*
*  \param mode
*  The mode of operation for the counter. See enum typedef cy_en_mcwdtmode_t.
*
*  \note
*  The mode for Counter 2 can be set only to CY_MCWDT_MODE_NONE or CY_MCWDT_MODE_INT.
*
*  \note
*  This API must not be called while the counters are running.
*  Prior to calling this API, the counter must be disabled.
*
* \note
* This API is available for CAT1A, CAT1B and CAT1D devices.
*
*******************************************************************************/
__STATIC_INLINE void Cy_MCWDT_SetMode(MCWDT_STRUCT_Type *base, cy_en_mcwdtctr_t counter, cy_en_mcwdtmode_t mode)
{
    uint32_t mask, shift;

    CY_ASSERT_L3(CY_MCWDT_IS_CNT_NUM_VALID(counter));
    CY_ASSERT_L3(CY_MCWDT_IS_MODE_VALID(mode));

    shift = CY_MCWDT_BYTE_SHIFT * ((uint32_t)counter);
    mask = (counter == CY_MCWDT_COUNTER2) ? CY_MCWDT_C2_MODE_MASK : CY_MCWDT_C0C1_MODE_MASK;
    mask = mask << shift;

    MCWDT_CONFIG(base) = (MCWDT_CONFIG(base) & ~mask) | ((uint32_t) mode << shift);
}


/*******************************************************************************
* Function Name: Cy_MCWDT_GetMode
****************************************************************************//**
*
*  Reports the mode of the  specified counter.
*
*  \param base
*  The base pointer to a structure that describes registers.
*
*  \param counter
*  The number of the WDT counter. The valid range is [0-2].
*
*  \return
*  The current mode of the counter. See enum typedef cy_en_mcwdtmode_t.
*
* \note
* This API is available for CAT1A, CAT1B and CAT1D devices.
*
*******************************************************************************/
__STATIC_INLINE cy_en_mcwdtmode_t Cy_MCWDT_GetMode(MCWDT_STRUCT_Type const *base, cy_en_mcwdtctr_t counter)
{
    uint32_t mode, mask;

    CY_ASSERT_L3(CY_MCWDT_IS_CNT_NUM_VALID(counter));

    mask = (counter == CY_MCWDT_COUNTER2) ? CY_MCWDT_C2_MODE_MASK : CY_MCWDT_C0C1_MODE_MASK;
    mode = (MCWDT_CONFIG(base) >> (CY_MCWDT_BYTE_SHIFT * ((uint32_t)counter))) & mask;

    return ((cy_en_mcwdtmode_t) mode);
}


/*******************************************************************************
* Function Name: Cy_MCWDT_SetClearOnMatch
****************************************************************************//**
*
*  Sets the Clear on match option for the specified counter.
*
*  \param base
*  The base pointer to a structure that describes registers.
*
*  \param counter
*   The number of the WDT counter. The valid range is [0-1].
*
*  \note
*  The match values are not supported by Counter 2.
*
*  \param enable
*  Set 0 to disable; 1 to enable.
*
*  \note
*  This API must not be called while the counters are running.
*  Prior to calling this API, the counter must be disabled.
*
* \note
* This API is available for CAT1A, CAT1B and CAT1D devices.
*
*******************************************************************************/
__STATIC_INLINE void Cy_MCWDT_SetClearOnMatch(MCWDT_STRUCT_Type *base, cy_en_mcwdtctr_t counter, uint32_t enable)
{
    CY_ASSERT_L3(CY_MCWDT_IS_CNT_NUM_VALID(counter));
    CY_ASSERT_L2(CY_MCWDT_IS_ENABLE_VALID(enable));

    if (CY_MCWDT_COUNTER0 == counter)
    {
        MCWDT_CONFIG(base) = _CLR_SET_FLD32U(MCWDT_CONFIG(base), MCWDT_STRUCT_MCWDT_CONFIG_WDT_CLEAR0, enable);
    }
    else
    {
        MCWDT_CONFIG(base) = _CLR_SET_FLD32U(MCWDT_CONFIG(base), MCWDT_STRUCT_MCWDT_CONFIG_WDT_CLEAR1, enable);
    }
}


/*******************************************************************************
* Function Name: Cy_MCWDT_GetClearOnMatch
****************************************************************************//**
*
*  Reports the Clear on match setting for the specified counter.
*
*  \param base
*  The base pointer to a structure that describes registers.
*
*  \param counter
*  The number of the WDT counter. The valid range is [0-1].
*
*  \return
*  The Clear on match status: 1 = enabled, 0 = disabled.
*
*  \note
*  The match value is not supported by Counter 2.
*
* \note
* This API is available for CAT1A, CAT1B and CAT1D devices.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_MCWDT_GetClearOnMatch(MCWDT_STRUCT_Type const *base, cy_en_mcwdtctr_t counter)
{
    uint32_t getClear;

    CY_ASSERT_L3(CY_MCWDT_IS_CNT_NUM_VALID(counter));

    if (CY_MCWDT_COUNTER0 == counter)
    {
        getClear = _FLD2VAL(MCWDT_STRUCT_MCWDT_CONFIG_WDT_CLEAR0, MCWDT_CONFIG(base));
    }
    else
    {
        getClear = _FLD2VAL(MCWDT_STRUCT_MCWDT_CONFIG_WDT_CLEAR1, MCWDT_CONFIG(base));
    }

    return (getClear);
}


/*******************************************************************************
* Function Name: Cy_MCWDT_SetCascade
****************************************************************************//**
*
*  Sets all the counter cascade options.
*
*  \param base
*  The base pointer to a structure that describes registers.
*
*  \param cascade
*  Sets or clears each of the cascade options.
*
*  \note
*  This API must not be called when the counters are running.
*  Prior to calling this API, the counter must be disabled.
*
* \note
* This API is available for CAT1A, CAT1B and CAT1D devices.
*
*******************************************************************************/
__STATIC_INLINE void Cy_MCWDT_SetCascade(MCWDT_STRUCT_Type *base, cy_en_mcwdtcascade_t cascade)
{
    CY_ASSERT_L3(CY_MCWDT_IS_CASCADE_VALID(cascade));

    MCWDT_CONFIG(base) = _CLR_SET_FLD32U(MCWDT_CONFIG(base), MCWDT_STRUCT_MCWDT_CONFIG_WDT_CASCADE0_1,
                                             (uint32_t) cascade);
    MCWDT_CONFIG(base) = _CLR_SET_FLD32U(MCWDT_CONFIG(base), MCWDT_STRUCT_MCWDT_CONFIG_WDT_CASCADE1_2,
                                             ((uint32_t) cascade >> 1u));
}

/*******************************************************************************
* Function Name: Cy_MCWDT_GetCascade
****************************************************************************//**
*
*  Reports all the counter cascade option settings.
*
*  \param base
*  The base pointer to a structure that describes registers.
*
*  \return
*  The current cascade option values.
*
* \note
* This API is available for CAT1A, CAT1B and CAT1D devices.
*
*******************************************************************************/
__STATIC_INLINE cy_en_mcwdtcascade_t Cy_MCWDT_GetCascade(MCWDT_STRUCT_Type const *base)
{
    uint32_t cascade;

    cascade = (_FLD2VAL(MCWDT_STRUCT_MCWDT_CONFIG_WDT_CASCADE1_2, MCWDT_CONFIG(base)) << 1u) |
               _FLD2VAL(MCWDT_STRUCT_MCWDT_CONFIG_WDT_CASCADE0_1, MCWDT_CONFIG(base));

    return ((cy_en_mcwdtcascade_t) cascade);
}

/*******************************************************************************
* Function Name: Cy_MCWDT_SetMatch
****************************************************************************//**
*
*  Sets the match comparison value for the specified counter (0 or 1).
*
*  \param base
*  The base pointer to a structure that describes registers.
*
*  \param counter
*   The number of the WDT counter. The valid range is [0-1].
*
*  \param match
*  The value to match against the counter.
*  The valid range is [0-65535] for c0ClearOnMatch (or c1ClearOnMatch) = 0
*  and [1-65535] for c0ClearOnMatch (or c1ClearOnMatch) = 1.
*
*  \note
*  The match value is not supported by Counter 2.
*
*  \note
*  Action on match is taken on the next increment after the counter value
*  equal to match value.
*
*  \param waitUs
*  The function waits for some delay in microseconds before returning,
*  because the match affects after two lf_clk cycles pass. The recommended
*  value is 93 us.
*  \note
*  Setting this parameter to a zero means No wait. This must be taken
*  into account when changing the match values on the running counters.
*
* \note
* This API is available for CAT1A, CAT1B and CAT1D devices.
*
*******************************************************************************/
__STATIC_INLINE void Cy_MCWDT_SetMatch(MCWDT_STRUCT_Type *base, cy_en_mcwdtctr_t counter, uint32_t match, uint16_t waitUs)
{
    CY_ASSERT_L3(CY_MCWDT_IS_CNT_NUM_VALID(counter));
    CY_ASSERT_L2(CY_MCWDT_IS_MATCH_VALID((CY_MCWDT_COUNTER0 == counter) ?                                                       \
                                         ((MCWDT_CONFIG(base) & MCWDT_STRUCT_MCWDT_CONFIG_WDT_CLEAR0_Msk) > 0U) :  \
                                         ((MCWDT_CONFIG(base) & MCWDT_STRUCT_MCWDT_CONFIG_WDT_CLEAR1_Msk) > 0U),   \
                                          match));

    MCWDT_MATCH(base) = (counter == CY_MCWDT_COUNTER0) ?
        _CLR_SET_FLD32U(MCWDT_MATCH(base), MCWDT_STRUCT_MCWDT_MATCH_WDT_MATCH0,
                        (match & MCWDT_STRUCT_MCWDT_MATCH_WDT_MATCH0_Msk)) :
        _CLR_SET_FLD32U(MCWDT_MATCH(base), MCWDT_STRUCT_MCWDT_MATCH_WDT_MATCH1,
                        (match & MCWDT_STRUCT_MCWDT_MATCH_WDT_MATCH0_Msk));

    Cy_SysLib_DelayUs(waitUs);
}


/*******************************************************************************
* Function Name: Cy_MCWDT_GetMatch
****************************************************************************//**
*
*  Reports the match comparison value for the specified counter (0 or 1).
*
*  \param base
*  The base pointer to a structure that describes registers.
*
*  \param counter
*  The number of the WDT counter. The valid range is [0-1].
*
*  \note
*  The match values are not supported by Counter 2.
*
*  \return
*  A 16-bit match value.
*
* \note
* This API is available for CAT1A, CAT1B and CAT1D devices.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_MCWDT_GetMatch(MCWDT_STRUCT_Type const *base, cy_en_mcwdtctr_t counter)
{
    uint32_t match;

    CY_ASSERT_L3(CY_MCWDT_IS_CNT_NUM_VALID(counter));

    match = (counter == CY_MCWDT_COUNTER0) ? _FLD2VAL(MCWDT_STRUCT_MCWDT_MATCH_WDT_MATCH0, MCWDT_MATCH(base)) :
                                          _FLD2VAL(MCWDT_STRUCT_MCWDT_MATCH_WDT_MATCH1, MCWDT_MATCH(base));

    return (match);
}
#endif /* (CY_IP_MXS28SRSS) || defined (CY_IP_MXS40SSRSS) || defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION < 3) || defined (CY_IP_MXS22SRSS) */

/*******************************************************************************
* Function Name: Cy_MCWDT_SetToggleBit
****************************************************************************//**
*
*  Sets a bit in Counter 2 to monitor for a toggle.
*
*  \param base
*  The base pointer to a structure that describes registers.
*
*  \param bit
*  The Counter 2 bit is set to monitor for a toggle. The valid range [0-31].
*
*  \note
*  This API must not be called when counters are running.
*  Prior to calling this API, the counter must be disabled.
*
*******************************************************************************/
__STATIC_INLINE void Cy_MCWDT_SetToggleBit(MCWDT_STRUCT_Type *base, uint32_t bit)
{
    CY_ASSERT_L2(CY_MCWDT_IS_BIT_VALID(bit));
#if (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3))
    MCWDT_CTR2_CONFIG(base) = _CLR_SET_FLD32U(MCWDT_CTR2_CONFIG(base), MCWDT_CTR2_CONFIG_BITS, bit);
#else
    MCWDT_CONFIG(base) = _CLR_SET_FLD32U(MCWDT_CONFIG(base), MCWDT_STRUCT_MCWDT_CONFIG_WDT_BITS2, bit);
#endif
}


/*******************************************************************************
* Function Name: Cy_MCWDT_GetToggleBit
****************************************************************************//**
*
*  Reports which bit in Counter 2 is monitored for a toggle.
*
*  \param base
*  The base pointer to a structure that describes registers.
*
*  \return
*  The bit that is monitored (range 0 to 31).
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_MCWDT_GetToggleBit(MCWDT_STRUCT_Type const *base)
{
#if (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3))
    return (uint32_t)(_FLD2VAL(MCWDT_CTR2_CONFIG_BITS, MCWDT_CTR2_CONFIG(base)));
#else
    return (_FLD2VAL(MCWDT_STRUCT_MCWDT_CONFIG_WDT_BITS2, MCWDT_CONFIG(base)));
#endif
}


/*******************************************************************************
* Function Name: Cy_MCWDT_GetCount
****************************************************************************//**
*
*  Reports the current counter value of the specified counter.
*
*  \param base
*  The base pointer to a structure that describes registers.
*
*  \param counter
*  The number of the WDT counter. The valid range is [0-2].
*
*  \return
*  A live counter value. Counters 0 and 1 are 16-bit counters and Counter 2 is
*  a 32-bit counter.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_MCWDT_GetCount(MCWDT_STRUCT_Type const *base, cy_en_mcwdtctr_t counter)
{
    uint32_t countVal = 0u;

    CY_ASSERT_L3(CY_MCWDT_IS_CNT_NUM_VALID(counter));

#if (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3))
    switch (counter)
    {
    case CY_MCWDT_COUNTER0:
        countVal = (uint16_t)(_FLD2VAL(MCWDT_CTR_CNT_CNT, MCWDT_CTR_CNT(base, CY_MCWDT_COUNTER0)));
        break;
    case CY_MCWDT_COUNTER1:
        countVal = (uint16_t)(_FLD2VAL(MCWDT_CTR_CNT_CNT, MCWDT_CTR_CNT(base, CY_MCWDT_COUNTER1)));
        break;
    case CY_MCWDT_COUNTER2:
        countVal = (_FLD2VAL(MCWDT_CTR2_CNT_CNT2, MCWDT_CTR2_CNT(base)));
        break;
    default:
        CY_ASSERT(0u != 0u);
        break;
    }

#else

    switch (counter)
    {
        case CY_MCWDT_COUNTER0:
            countVal = _FLD2VAL(MCWDT_STRUCT_MCWDT_CNTLOW_WDT_CTR0, MCWDT_CNTLOW(base));
            break;
        case CY_MCWDT_COUNTER1:
            countVal = _FLD2VAL(MCWDT_STRUCT_MCWDT_CNTLOW_WDT_CTR1, MCWDT_CNTLOW(base));
            break;
        case CY_MCWDT_COUNTER2:
            countVal = _FLD2VAL(MCWDT_STRUCT_MCWDT_CNTHIGH_WDT_CTR2, MCWDT_CNTHIGH(base));
            break;
        default:
            CY_ASSERT(0u != 0u);
            break;
    }
#endif

    return (countVal);
}


/*******************************************************************************
* Function Name: Cy_MCWDT_ResetCounters
****************************************************************************//**
*
*  Resets all specified counters.
*
*  \param base
*  The base pointer to a structure that describes registers.
*
*  \param counters
*  OR of all counters to reset. See the \ref CY_MCWDT_CTR0, CY_MCWDT_CTR1, and
*  CY_MCWDT_CTR2 macros.
*
*  \param waitUs
*  The function waits for some delay in microseconds before returning, because
*  a reset occurs after one lf_clk cycle passes. The recommended value is 62 us.
*  \note This function resets the counters two times to prevent the case when
*  the Counter 1 is not reset when the counters are cascaded. The delay waitUs
*  must be greater than 100 us when the counters are cascaded.
*  The total delay is greater than 2*waitUs because the function has
*  the delay after the first reset.
*  \note
*  Setting this parameter to a zero means No wait. In this case, it is the
*  user's responsibility to check whether the selected counters were reset
*  immediately after the function call. This can be done by the
*  Cy_MCWDT_GetCount() API.
*
*  \note
*  For CAT1C devices, only CY_MCWDT_CTR0 and CY_MCWDT_CTR1 can be Reset.
*
*******************************************************************************/
__STATIC_INLINE void Cy_MCWDT_ResetCounters(MCWDT_STRUCT_Type *base, uint32_t counters, uint16_t waitUs)
{
#if (defined (CY_IP_MXS40SRSS) && (CY_IP_MXS40SRSS_VERSION >= 3))
    if (0UL != (counters & CY_MCWDT_CTR0))
    {
        MCWDT_SERVICE(base) |= MCWDT_SERVICE_CTR0_SERVICE_Msk;
    }
    if (0UL != (counters & CY_MCWDT_CTR1))
    {
        MCWDT_SERVICE(base) |= MCWDT_SERVICE_CTR1_SERVICE_Msk;
    }

#else

    uint32_t resetCounters;

    CY_ASSERT_L2(CY_MCWDT_IS_CNTS_MASK_VALID(counters));

    /* Extract particular counters for reset */
    resetCounters = ((0UL != (counters & CY_MCWDT_CTR0)) ? MCWDT_STRUCT_MCWDT_CTL_WDT_RESET0_Msk : 0UL) |
                    ((0UL != (counters & CY_MCWDT_CTR1)) ? MCWDT_STRUCT_MCWDT_CTL_WDT_RESET1_Msk : 0UL) |
                    ((0UL != (counters & CY_MCWDT_CTR2)) ? MCWDT_STRUCT_MCWDT_CTL_WDT_RESET2_Msk : 0UL);

    MCWDT_CTL(base) |= resetCounters;

    Cy_SysLib_DelayUs(waitUs);

    MCWDT_CTL(base) |= resetCounters;
#endif

    Cy_SysLib_DelayUs(waitUs);
}


/*******************************************************************************
* Function Name: Cy_MCWDT_GetInterruptStatus
****************************************************************************//**
*
*  Reports the state of all MCWDT interrupts.
*
*  \param base
*  The base pointer to a structure that describes registers.
*
*  \return
*  The OR'd state of the interrupts. See the \ref CY_MCWDT_CTR0, CY_MCWDT_CTR1, and
*  CY_MCWDT_CTR2 macros.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_MCWDT_GetInterruptStatus(MCWDT_STRUCT_Type const *base)
{
    return (MCWDT_INTR(base));
}


/*******************************************************************************
* Function Name: Cy_MCWDT_ClearInterrupt
****************************************************************************//**
*
*  Clears all specified MCWDT interrupts.
*
*  All the WDT interrupts must be cleared by the firmware; otherwise
*  interrupts are generated continuously.
*
*  \param base
*  The base pointer to a structure describes registers.
*
*  \param counters
*  OR of all interrupt sources to clear. See the \ref CY_MCWDT_CTR0, CY_MCWDT_CTR1, and
*  CY_MCWDT_CTR2  macros.
*
*******************************************************************************/
__STATIC_INLINE void Cy_MCWDT_ClearInterrupt(MCWDT_STRUCT_Type *base, uint32_t counters)
{
    CY_ASSERT_L2(CY_MCWDT_IS_CNTS_MASK_VALID(counters));

    MCWDT_INTR(base) = counters;
    (void) MCWDT_INTR(base);
}


/*******************************************************************************
* Function Name: Cy_MCWDT_SetInterrupt
****************************************************************************//**
*
*  Sets MCWDT interrupt sources in the interrupt request register.
*
*  \param base
*  The base pointer to a structure that describes registers.
*
*  \param counters
*  OR of all interrupt sources to set. See the \ref CY_MCWDT_CTR0, CY_MCWDT_CTR1, and
*  CY_MCWDT_CTR2  macros.
*
*******************************************************************************/
__STATIC_INLINE void Cy_MCWDT_SetInterrupt(MCWDT_STRUCT_Type *base, uint32_t counters)
{
    CY_ASSERT_L2(CY_MCWDT_IS_CNTS_MASK_VALID(counters));

    MCWDT_INTR_SET(base) = counters;
}


/*******************************************************************************
* Function Name: Cy_MCWDT_GetInterruptMask
****************************************************************************//**
*
* Returns the CWDT interrupt mask register. This register specifies which bits
* from the MCWDT interrupt request register will trigger an interrupt event.
*
*  \param base
*  The base pointer to a structure that describes registers.
*
*  \return
*  The OR'd state of the interrupt masks. See the \ref CY_MCWDT_CTR0, CY_MCWDT_CTR1, and
*  CY_MCWDT_CTR2  macros.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_MCWDT_GetInterruptMask(MCWDT_STRUCT_Type const *base)
{
    return (MCWDT_INTR_MASK(base));
}


/*******************************************************************************
* Function Name: Cy_MCWDT_SetInterruptMask
****************************************************************************//**
*
* Writes MCWDT interrupt mask register. This register configures which bits
* from MCWDT interrupt request register will trigger an interrupt event.
*
*  \param base
*  The base pointer to a structure that describes registers.
*
*  \param counters
*  OR of all interrupt masks to set. See \ref CY_MCWDT_CTR0, CY_MCWDT_CTR1, and
*  CY_MCWDT_CTR2  macros.
*
*******************************************************************************/
__STATIC_INLINE void Cy_MCWDT_SetInterruptMask(MCWDT_STRUCT_Type *base, uint32_t counters)
{
    CY_ASSERT_L2(CY_MCWDT_IS_CNTS_MASK_VALID(counters));

    MCWDT_INTR_MASK(base) = counters;
}


/*******************************************************************************
* Function Name: Cy_MCWDT_GetInterruptStatusMasked
****************************************************************************//**
*
* Returns the MCWDT interrupt masked request register. This register contains
* the logical AND of corresponding bits from the MCWDT interrupt request and
* mask registers.
* In the interrupt service routine, this function identifies which of the
* enabled MCWDT interrupt sources caused an interrupt event.
*
*  \param base
*  The base pointer to a structure that describes registers.
*
*  \return
*  The current status of enabled MCWDT interrupt sources. See
*  the \ref CY_MCWDT_CTR0, CY_MCWDT_CTR1, and CY_MCWDT_CTR2 macros.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_MCWDT_GetInterruptStatusMasked(MCWDT_STRUCT_Type const *base)
{
    return (MCWDT_INTR_MASKED(base));
}

#if defined (CY_IP_MXS28SRSS) || defined (CY_IP_MXS40SSRSS) || defined (CY_IP_MXS22SRSS)
/*******************************************************************************
* Function Name: Cy_MCWDT_SetLowerLimit
****************************************************************************//**
*
*  Sets the lower limit value for the specified counter (0 or 1).
*
*  \param base
*  The base pointer to a structure that describes registers.
*
*  \param counter
*   The number of the WDT counter. The valid range is [0-1].
*
*  \param lowerLimit
*  The value to be written in the lower limit register
*  The valid range is [0-65535] for c0
*  and [1-65535] for c1.
*
*  \note
*  The lower limit mode is not supported by Counter 2.
*
*  \param waitUs
*  The function waits for some delay in microseconds before returning,
*  because the lower limit register write affects after two lf_clk cycles pass.
* The recommended value is 93 us.
*  \note
*  Setting this parameter to a zero means No wait. This must be taken
*  into account when changing the lower limit register values.
*
* \note
* This API is available for CAT1B devices.
*
*******************************************************************************/
__STATIC_INLINE void Cy_MCWDT_SetLowerLimit(MCWDT_STRUCT_Type *base, cy_en_mcwdtlowerlimit_t counter, uint32_t lowerLimit, uint16_t waitUs)
{
    CY_ASSERT_L3(CY_MCWDT_IS_LOWER_LIMIT_VALID(counter));

    MCWDT_LOWER_LIMIT(base) = (counter == CY_MCWDT_LOWER_LIMIT0) ?
        _CLR_SET_FLD32U(MCWDT_LOWER_LIMIT(base), MCWDT_STRUCT_MCWDT_LOWER_LIMIT_WDT_LOWER_LIMIT0,
                        (lowerLimit & MCWDT_STRUCT_MCWDT_LOWER_LIMIT_WDT_LOWER_LIMIT0_Msk)) :
        _CLR_SET_FLD32U(MCWDT_LOWER_LIMIT(base), MCWDT_STRUCT_MCWDT_LOWER_LIMIT_WDT_LOWER_LIMIT1,
                        (lowerLimit & MCWDT_STRUCT_MCWDT_LOWER_LIMIT_WDT_LOWER_LIMIT0_Msk));

    Cy_SysLib_DelayUs(waitUs);
}

/*******************************************************************************
* Function Name: Cy_MCWDT_GetLowerLimit
****************************************************************************//**
*
*  Reports the Lower Limit value of the specified counter.
*
*  \param base
*  The base pointer to a structure that describes registers.
*
*  \param counter
*  The number of the WDT counter. The valid range is [0-1].
*
*  \return
*  A Lower Limit value. Counters 0 and 1 are 16-bit counters.
*
* \note
* This API is available for CAT1B devices.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_MCWDT_GetLowerLimit(MCWDT_STRUCT_Type const *base, cy_en_mcwdtlowerlimit_t counter)
{
    uint32_t countVal = 0u;

    CY_ASSERT_L3(CY_MCWDT_IS_LOWER_LIMIT_VALID(counter));

    switch (counter)
    {
        case CY_MCWDT_LOWER_LIMIT0:
            countVal = _FLD2VAL(MCWDT_STRUCT_MCWDT_LOWER_LIMIT_WDT_LOWER_LIMIT0, MCWDT_LOWER_LIMIT(base));
            break;
        case CY_MCWDT_LOWER_LIMIT1:
            countVal = _FLD2VAL(MCWDT_STRUCT_MCWDT_LOWER_LIMIT_WDT_LOWER_LIMIT1, MCWDT_LOWER_LIMIT(base));
            break;
        default:
            CY_ASSERT(0u != 0u);
        break;
    }

    return (countVal);
}

/*******************************************************************************
* Function Name: Cy_MCWDT_SetLowerLimitMode
****************************************************************************//**
*
*  Sets the lower limit mode option for the specified counter.
*
*  \param base
*  The base pointer to a structure that describes registers.
*
*  \param counter
*   The number of the WDT counter. The valid range is [0-1].
*
*  \note
*  The lower limit mode is not supported by Counter 2.
*
*  \param mode
*  Set 0 - Do nothing, 1 - Assert WDT_INTx, 2 - Assert WDT Reset
*
*  \note
*  This API must not be called while the counters are running.
*  Prior to calling this API, the counter must be disabled.
*  This API is available for CAT1B devices.
*
*******************************************************************************/
__STATIC_INLINE void Cy_MCWDT_SetLowerLimitMode(MCWDT_STRUCT_Type *base, cy_en_mcwdtlowerlimit_t counter, cy_en_mcwdtlowerlimitmode_t mode)
{
    CY_ASSERT_L3(CY_MCWDT_IS_LOWER_LIMIT_VALID(counter));
    CY_ASSERT_L2(CY_MCWDT_IS_LOWER_LIMIT_MODE_VALID(mode));

    if (CY_MCWDT_LOWER_LIMIT0 == counter)
    {
        MCWDT_CONFIG(base) = _CLR_SET_FLD32U(MCWDT_CONFIG(base), MCWDT_STRUCT_MCWDT_CONFIG_WDT_LOWER_MODE0, mode);
    }
    else
    {
        MCWDT_CONFIG(base) = _CLR_SET_FLD32U(MCWDT_CONFIG(base), MCWDT_STRUCT_MCWDT_CONFIG_WDT_LOWER_MODE1, mode);
    }
}

/*******************************************************************************
* Function Name: Cy_MCWDT_GetLowerLimitMode
****************************************************************************//**
*
*  Reports the lower limit mode of the  specified counter.
*
*  \param base
*  The base pointer to a structure that describes registers.
*
*  \param counter
*  The number of the WDT counter. The valid range is [0-1].
*
*  \return
*  The current lower limit mode of the counter. See enum typedef cy_en_mcwdtlowerlimitmode_t.
*
* \note
* This API is available for CAT1B devices.
*
*******************************************************************************/
__STATIC_INLINE cy_en_mcwdtlowerlimitmode_t Cy_MCWDT_GetLowerLimitMode(MCWDT_STRUCT_Type const *base, cy_en_mcwdtlowerlimit_t counter)
{
    uint32_t getLowerLimitMode;

    CY_ASSERT_L3(CY_MCWDT_IS_LOWER_LIMIT_VALID(counter));

    if (CY_MCWDT_LOWER_LIMIT0 == counter)
    {
        getLowerLimitMode = _FLD2VAL(MCWDT_STRUCT_MCWDT_CONFIG_WDT_LOWER_MODE0, MCWDT_CONFIG(base));
    }
    else
    {
        getLowerLimitMode = _FLD2VAL(MCWDT_STRUCT_MCWDT_CONFIG_WDT_LOWER_MODE1, MCWDT_CONFIG(base));
    }

    return (cy_en_mcwdtlowerlimitmode_t)getLowerLimitMode;

}

/*******************************************************************************
* Function Name: Cy_MCWDT_GetLowerLimitCascaded
****************************************************************************//**
*
*  Gets lower limit registers cascaded value.
*
*  \param base
*  The base pointer to a structure that describes registers.
*
*  \note
*  The lower limit mode is not supported by Counter 2.
*
*  \return
*  A 32-bit lower limit register value.
*
* \note
* This API is available for CAT1B devices.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_MCWDT_GetLowerLimitCascaded(MCWDT_STRUCT_Type const *base)
{
    return (uint32_t)(MCWDT_LOWER_LIMIT(base));
}
#endif /* CY_IP_MXS28SRSS, CY_IP_MXS40SSRSS ,CY_IP_MXS22SRSS*/

#if defined (CY_IP_MXS40SSRSS) || defined (CY_IP_MXS22SRSS) || defined (CY_DOXYGEN)

/*******************************************************************************
* Function Name: Cy_MCWDT_SetCascadeCarryOutRollOver
****************************************************************************//**
*
*  Enables the Rollover mode for carryout.
*
*  \param base
*  The base pointer to a structure that describes registers.
*
*  \param counter
*   The cascaded counter type. The valid cascaded type is either C0C1 or C1C2.
*
*  \param carryoutconfig
*   For CY_MCWDT_CASCADE_C0C1:
*   FALSE: carry out on counter 0 match
*   TRUE:  carry out on counter 0 rollover.
*   For CY_MCWDT_CASCADE_C1C2:
*   FALSE: carry out on counter 1 match
*   TRUE:  carry out on counter 1 rollover.
*
*  \note
*  This API is available for CAT1B devices.
*
*******************************************************************************/
__STATIC_INLINE void Cy_MCWDT_SetCascadeCarryOutRollOver(MCWDT_STRUCT_Type *base, cy_en_mcwdtcascade_t counter, bool carryoutconfig)
{
    CY_ASSERT_L3(CY_MCWDT_IS_CARRYMODE_CASCADE_VALID(counter));

    if (CY_MCWDT_CASCADE_C0C1 == counter)
    {
        MCWDT_CONFIG(base) = _CLR_SET_FLD32U(MCWDT_CONFIG(base), MCWDT_STRUCT_MCWDT_CONFIG_WDT_CARRY0_1, carryoutconfig);
    }
    else
    {
        MCWDT_CONFIG(base) = _CLR_SET_FLD32U(MCWDT_CONFIG(base), MCWDT_STRUCT_MCWDT_CONFIG_WDT_CARRY1_2, carryoutconfig);
    }
}

/*******************************************************************************
* Function Name: Cy_MCWDT_GetCascadeCarryOutModeRollOver
****************************************************************************//**
*
*  Checks if Rollover mode enabled for carryout or not.
*
*  \param base
*  The base pointer to a structure that describes registers.
*
*  \param counter
*  The cascaded counter type. The valid cascaded type is either C0C1 or C1C2.
*
*  \return
*  True : Rollover Enabled
*  False : Rollover Disabled
*
* \note
* This API is available for CAT1B devices.
*
*******************************************************************************/
__STATIC_INLINE bool Cy_MCWDT_GetCascadeCarryOutRollOver(MCWDT_STRUCT_Type const *base, cy_en_mcwdtcascade_t counter)
{
    bool countVal = false;

    CY_ASSERT_L3(CY_MCWDT_IS_CARRYMODE_CASCADE_VALID(counter));

    switch (counter)
    {
        case CY_MCWDT_CASCADE_C0C1:
            countVal = _FLD2BOOL(MCWDT_STRUCT_MCWDT_CONFIG_WDT_CARRY0_1, MCWDT_CONFIG(base));
            break;
        case CY_MCWDT_CASCADE_C1C2:
            countVal = _FLD2BOOL(MCWDT_STRUCT_MCWDT_CONFIG_WDT_CARRY1_2, MCWDT_CONFIG(base));
            break;
        default:
            CY_ASSERT(0u != 0u);
        break;
    }

    return (countVal);
}

/*******************************************************************************
* Function Name: Cy_MCWDT_SetCascadeMatchCombined
****************************************************************************//**
*
*  Sets the match to combined cascade counters.
*
*  \param base
*  The base pointer to a structure that describes registers.
*
*  \param counter
*   The cascaded counter type. The valid cascaded type is either C0C1 or C1C2.
*
*  \param matchconfig
*   For CY_MCWDT_CASCADE_C0C1:
*   FALSE: Match based on counter 1 alone
*   TRUE:  Match based on counter 1 and counter 0 matching simultaneously
*   For CY_MCWDT_CASCADE_C1C2:
*   FALSE: Match based on counter 2 alone
*   TRUE:  Match based on counter 2 and counter 1 matching simultaneously
*
*  \note
*  This API is available for CAT1B devices.
*
*******************************************************************************/
__STATIC_INLINE void Cy_MCWDT_SetCascadeMatchCombined(MCWDT_STRUCT_Type *base, cy_en_mcwdtcascade_t counter, bool matchconfig)
{
    if (CY_MCWDT_CASCADE_C0C1 == counter)
    {
        MCWDT_CONFIG(base) = _CLR_SET_FLD32U(MCWDT_CONFIG(base), MCWDT_STRUCT_MCWDT_CONFIG_WDT_MATCH0_1, matchconfig);
    }
    else
    {
        MCWDT_CONFIG(base) = _CLR_SET_FLD32U(MCWDT_CONFIG(base), MCWDT_STRUCT_MCWDT_CONFIG_WDT_MATCH1_2, matchconfig);
    }
}

/*******************************************************************************
* Function Name: Cy_MCWDT_GetCascadeMatchModeCombined
****************************************************************************//**
*
*  Reports if match is enabled with combined cascade counters or not.
*
*  \param base
*  The base pointer to a structure that describes registers.
*
*  \param counter
*  The cascaded counter type. The valid cascaded type is either C0C1 or C1C2.
*
*  \return
*  True : Combined match is enabled
*  False : Combined match is disabled.
*
* \note
* This API is available for CAT1B devices.
*
*******************************************************************************/
__STATIC_INLINE bool Cy_MCWDT_GetCascadeMatchCombined(MCWDT_STRUCT_Type const *base, cy_en_mcwdtcascade_t counter)
{
    bool countVal = false;

    switch (counter)
    {
        case CY_MCWDT_CASCADE_C0C1:
            countVal = _FLD2BOOL(MCWDT_STRUCT_MCWDT_CONFIG_WDT_MATCH0_1, MCWDT_CONFIG(base));
            break;
        case CY_MCWDT_CASCADE_C1C2:
            countVal = _FLD2BOOL(MCWDT_STRUCT_MCWDT_CONFIG_WDT_MATCH1_2, MCWDT_CONFIG(base));
            break;
        default:
            CY_ASSERT(0u != 0u);
        break;
    }

    return (countVal);
}

#endif /*  CY_IP_MXS40SSRSS,CY_IP_MXS22SRSS */


/** \} group_mcwdt_functions */

#endif /* CY_IP_MXS40SRSS_MCWDT, CY_IP_MXS28SRSS, CY_IP_MXS40SSRSS, CY_IP_MXS22SRSS */

#if defined(__cplusplus)
}
#endif

#endif /* CY_MCWDT_H */

/** \} group_mcwdt */

/* [] END OF FILE */
