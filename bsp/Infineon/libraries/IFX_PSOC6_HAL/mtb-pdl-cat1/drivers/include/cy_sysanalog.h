/***************************************************************************//**
* \file cy_sysanalog.h
* \version 2.10
*
* Header file for the system level analog reference driver.
*
********************************************************************************
* \copyright
* Copyright 2017-2020 Cypress Semiconductor Corporation
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
* \addtogroup group_sysanalog
* \{
*
* This driver provides an interface for configuring the Analog Reference (AREF),
* Low Power Oscillator (LpOsc), Deep Sleep Clock and Timer blocks
* and querying the INTR_CAUSE register of the Programmable Analog SubSystem (PASS) hardware block.
*
* The functions and other declarations used in this driver are in cy_sysanalog.h.
* You can include cy_pdl.h to get access to all functions
* and declarations in the PDL.
*
* \section group_pass_structure PASS block structure
*
* \image html passv2_diagram.png
* \image latex passv2_diagram.png
*
* The Programmable Analog SubSystem (PASS) hardware block contains a set of analog
* subblocks such as AREF, CTB, SAR, analog routing switches and others.
* In order to provide a firmware interface to PASS, subblocks are united into groups,
* which have their own drivers: SysAnalog, \ref group_ctb "CTB" and
* \ref group_sar "SAR".
*
* \section group_sysanalog_features SysAnalog Features Description
*
* SysAnalog driver includes the following features:
* - \ref group_sysanalog_aref
* - \ref group_sysanalog_lposc (Available only for PASS_ver2.)
* - \ref group_sysanalog_dpslp (Available only for PASS_ver2.)
* - \ref group_sysanalog_timer (Available only for PASS_ver2.)
*
* The following sections describe how to initialize driver features:
* - \ref group_sysanalog_aref_usage_init
* - \ref group_sysanalog_deepsleepinit
*
* \section group_sysanalog_aref AREF
*
* The AREF block has the following features:
*
*   - Generates a voltage reference (VREF) from one of three sources:
*       - Local 1.2 V reference (<b>low noise, optimized for analog performance</b>)
*       - Reference from the SRSS (high noise, not recommended for analog performance)
*       - An external pin
*   - Generates a 1 uA "zero dependency to absolute temperature" (IZTAT) current reference
*     that is independent of temperature variations. It can come from one of two sources:
*       - Local reference (<b>low noise, optimized for analog performance</b>)
*       - Reference from the SRSS (high noise, not recommended for analog performance)
*   - Generates a "proportional to absolute temperature" (IPTAT) current reference
*   - Option to enable local references in Deep Sleep mode
*
* The locally generated references are the recommended sources for blocks in the PASS because
* they have tighter accuracy, temperature stability, and lower noise than the SRSS references.
* The SRSS references can be used to save power if the low accuracy and higher noise can be tolerated.
*
* \image html aref_block_diagram.png
* \image latex aref_block_diagram.png
*
* The outputs of the AREF are consumed by multiple blocks in the PASS and by the CapSense (CSDv2) block.
* In some cases, these blocks have the option of using the references from the AREF. This selection would be
* in the respective drivers for these blocks. In some cases, these blocks require the references from the
* AREF to function.
*
* <table class="doxtable">
*   <tr><th>AREF Output</th><th>\ref group_sar "SAR"</th><th>\ref group_ctdac "CTDAC"</th><th>\ref group_ctb "CTB"</th><th>CSDv2</th></tr>
*   <tr>
*     <td>VREF</td>
*     <td>optional</td>
*     <td>optional</td>
*     <td>--</td>
*     <td>optional</td>
*   </tr>
*   <tr>
*     <td>IZTAT</td>
*     <td><b>required</b></td>
*     <td>--</td>
*     <td>optional</td>
*     <td>optional</td>
*   </tr>
*   <tr>
*     <td>IPTAT</td>
*     <td>--</td>
*     <td>--</td>
*     <td><b>required</b></td>
*     <td>--</td>
*   </tr>
* </table>
*
* This driver provides a function to query the INTR_CAUSE register of the PASS.
* There are two interrupts in the PASS:
*
*   -# one global interrupt for all CTBs (up to 4)
*   -# one global interrupt for all CTDACs (up to 4)
*
* Because the interrupts are global, the INTR_CAUSE register is needed to query which hardware instance
* triggered the interrupt.
*
* \subsection group_sysanalog_aref_usage_init AREF Configuration
*
* To configure the AREF, call \ref Cy_SysAnalog_Init and provide a pointer
* to the configuration structure, \ref cy_stc_sysanalog_config_t. Three predefined structures
* are provided in this driver to cover a majority of use cases:
*
*   - \ref Cy_SysAnalog_Fast_Local <b>(recommended for analog performance)</b>
*   - \ref Cy_SysAnalog_Fast_SRSS
*   - \ref Cy_SysAnalog_Fast_External
*
* After initialization, call \ref Cy_SysAnalog_Enable to enable the hardware.
*
* ### Deep Sleep Operation
*
* The AREF current and voltage references can be enabled to operate in Deep Sleep mode
* with \ref Cy_SysAnalog_SetDeepSleepMode. There are four options for Deep Sleep operation:
*
*   - \ref CY_SYSANALOG_DEEPSLEEP_DISABLE : Disable AREF IP block
*   - \ref CY_SYSANALOG_DEEPSLEEP_IPTAT_1 : Enable IPTAT generator for fast wakeup from Deep Sleep mode. IPTAT outputs for CTBs are disabled.
*   - \ref CY_SYSANALOG_DEEPSLEEP_IPTAT_2 : Enable IPTAT generator and IPTAT outputs for CTB
*   - \ref CY_SYSANALOG_DEEPSLEEP_IPTAT_IZTAT_VREF : Enable all generators and outputs: IPTAT, IZTAT, and VREF
*
* Recall that the CTB requires the IPTAT reference. For the CTB to operate at the 1 uA current mode in Deep Sleep mode,
* the AREF must be enabled for \ref CY_SYSANALOG_DEEPSLEEP_IPTAT_IZTAT_VREF. For the CTB to operate at the 100 nA
* current mode in Deep Sleep mode, the AREF must be enabled for \ref CY_SYSANALOG_DEEPSLEEP_IPTAT_2 minimum. In this
* lower current mode, the AREF IPTAT must be redirected to the CTB IZTAT. See the high level function \ref
* Cy_CTB_SetCurrentMode in the CTB PDL driver.
*
* If the CTDAC is configured to use the VREF in Deep Sleep mode, the AREF must be enabled for \ref CY_SYSANALOG_DEEPSLEEP_IPTAT_IZTAT_VREF.
*
* \note
* The SRSS references are not available to the AREF in Deep Sleep mode. When operating
* in Deep Sleep mode, the local or external references must be selected.
*
* \section group_sysanalog_lposc Low Power Oscillator
* Features:
*   - Internal PASS_ver2 8MHz oscillator which does not require any external components.
*   - Can work in Deep Sleep power mode.
*   - Can be used as a clock source for the Deep Sleep Clock.
*
* Low Power Oscillator clocking mode is configured by
* cy_stc_sysanalog_deep_sleep_config_t::lpOscDsMode configuration structure item, which
* should be passed as a parameter to \ref Cy_SysAnalog_DeepSleepInit function.
* See \ref group_sysanalog_functions_lposc for other Low Power Oscillator control functions.
*
* \section group_sysanalog_dpslp Deep Sleep Clock
* Features:
*   - Internal PASS_ver2 deep sleep capable clock selector/divider
*   - Can be used as clock source for CTB pump, SAR ADC and Timer
*
* Deep Sleep clock is configurable by cy_stc_sysanalog_deep_sleep_config_t::dsClkSource and
* cy_stc_sysanalog_deep_sleep_config_t::dsClkdivider configuration structure items,
* which should be passed as a parameter to \ref Cy_SysAnalog_DeepSleepInit function.
*
* \section group_sysanalog_timer Timer
* Features:
*   - Internal PASS_ver2 16-bit down counting timer
*   - Can be used to trigger one or few SAR ADCs
*   - Can be clocked from
*       - Peripheral Clock (CLK_PERI),
*       - Low Frequency Clock (CLK_LF)
*       - Deep Sleep Clock
*   - If clocked from Deep Sleep Clock, timer can be used to trigger SAR ADC scans
*     in Deep Sleep power mode.
*
* Timer is configurable by cy_stc_sysanalog_deep_sleep_config_t::timerClock
* and cy_stc_sysanalog_deep_sleep_config_t::timerPeriod configuration structure items,
* which should be passed as a parameter to \ref Cy_SysAnalog_DeepSleepInit function.
* Also see \ref group_sysanalog_functions_timer for other Timer configuration and control functions.
*
* \section group_sysanalog_deepsleepinit Low Power Oscillator, Deep Sleep Clock and Timer Configuration
* To configure Low Power Oscillator, Deep Sleep Clock and Timer blocks,
* call \ref Cy_SysAnalog_DeepSleepInit function and provide pointer to PASS block and pointer
* to the \ref cy_stc_sysanalog_deep_sleep_config_t configuration structure. In order to start
* Low Power Oscillator and Timer, call corresponding enable functions:
*
* \snippet sysanalog/snippet/main.c SYSANA_SNIPPET_INIT_DS
*
* \section group_sysanalog_more_information More Information
*
* For more information on the AREF, Deep Sleep Clock and Timer, refer to the technical reference manual (TRM).
*
* \section group_sysanalog_changelog Changelog
* <table class="doxtable">
*   <tr><th>Version</th><th>Changes</th><th>Reason for Change</th></tr>
*   <tr>
*     <td>2.10</td>
*     <td>The CY_SYSANALOG_STARTUP_NORMAL and Cy_SysAnalog_SetArefMode are deprecated.
*         The HW is anyways initialized with the CY_SYSANALOG_STARTUP_FAST.</td>
*     <td>User experience enhancement.</td>
*   </tr>
*   <tr>
*     <td>2.0</td>
*     <td>Added new features: LPOSC, DSCLK, TIMER.</td>
*     <td>New silicon family support.</td>
*   </tr>
*   <tr>
*     <td>1.10.1</td>
*     <td>Minor documentation updates.</td>
*     <td>Documentation enhancement.</td>
*   </tr>
*   <tr>
*     <td rowspan="2">1.10</td>
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
*     <td>1.0</td>
*     <td>Initial version</td>
*     <td></td>
*   </tr>
* </table>
*
* \defgroup group_sysanalog_macros Macros
* \defgroup group_sysanalog_functions Functions
* \{
*   \defgroup group_sysanalog_functions_lposc   Low Power Oscillator Functions
*   \defgroup group_sysanalog_functions_timer   Timer Functions
* \}
* \defgroup group_sysanalog_globals Global Variables
* \defgroup group_sysanalog_data_structures Data Structures
* \defgroup group_sysanalog_enums Enumerated Types
*/

#if !defined(CY_SYSANALOG_H)
#define CY_SYSANALOG_H

#include "cy_device.h"

#ifdef CY_IP_MXS40PASS

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#include "cy_syslib.h"
#include "cy_syspm.h"

#if defined(__cplusplus)
extern "C" {
#endif

CY_MISRA_DEVIATE_BLOCK_START('MISRA C-2012 Rule 11.3', 19, \
'PASS_Type will typecast to either PASS_V1_Type or PASS_V2_Type but not both on PDL initialization based on the target device at compile time.');

/** \addtogroup group_sysanalog_macros
* \{
*/

/** Driver major version */
#define CY_SYSANALOG_DRV_VERSION_MAJOR          2

/** Driver minor version */
#define CY_SYSANALOG_DRV_VERSION_MINOR          10

/** PASS driver identifier */
#define CY_SYSANALOG_ID                         CY_PDL_DRV_ID(0x17u)


/** \cond INTERNAL */
#define CY_SYSANALOG_DEINIT                     (0UL)   /**< De-init value for PASS register */
#define CY_SYSANALOG_DEFAULT_BIAS_SCALE         (1UL << PASS_AREF_AREF_CTRL_AREF_BIAS_SCALE_Pos)    /**< Default AREF bias current scale of 250 nA */

/**< Macros for conditions used in CY_ASSERT calls */
#define CY_SYSANALOG_DEEPSLEEP(deepSleep)       (((deepSleep) == CY_SYSANALOG_DEEPSLEEP_DISABLE) \
                                                || ((deepSleep) == CY_SYSANALOG_DEEPSLEEP_IPTAT_1) \
                                                || ((deepSleep) == CY_SYSANALOG_DEEPSLEEP_IPTAT_2) \
                                                || ((deepSleep) == CY_SYSANALOG_DEEPSLEEP_IPTAT_IZTAT_VREF))
#define CY_SYSANALOG_VREF(vref)                 (((vref) == CY_SYSANALOG_VREF_SOURCE_SRSS) \
                                                || ((vref) == CY_SYSANALOG_VREF_SOURCE_LOCAL_1_2V) \
                                                || ((vref) == CY_SYSANALOG_VREF_SOURCE_EXTERNAL))
#define CY_SYSANALOG_IZTAT(iztat)               (((iztat) == CY_SYSANALOG_IZTAT_SOURCE_SRSS) || ((iztat) == CY_SYSANALOG_IZTAT_SOURCE_LOCAL))

/** \endcond */

/** \} group_sysanalog_macros */

/** \addtogroup group_sysanalog_enums
* \{
*/

/******************************************************************************
 * Enumerations
 *****************************************************************************/

/** The AREF status/error code definitions */
typedef enum
{
    CY_SYSANALOG_SUCCESS     = 0x00UL,                                         /**< Successful */
    CY_SYSANALOG_BAD_PARAM   = CY_SYSANALOG_ID | CY_PDL_STATUS_ERROR | 0x01UL, /**< Invalid input parameters */
    CY_SYSANALOG_UNSUPPORTED = CY_SYSANALOG_ID | CY_PDL_STATUS_ERROR | 0x02UL  /**< Unsupported feature */
}cy_en_sysanalog_status_t;

/** \cond Deprecated, left here for BWC, HW is anyways initialized with CY_SYSANALOG_STARTUP_FAST */
typedef enum
{
    CY_SYSANALOG_STARTUP_NORMAL     = 0UL,
    CY_SYSANALOG_STARTUP_FAST       = 1UL << PASS_AREF_AREF_CTRL_AREF_MODE_Pos
}cy_en_sysanalog_startup_t;
/** \endcond */

/** AREF voltage reference sources
*
* The voltage reference can come from three sources:
*   - the locally generated 1.2 V reference
*   - the SRSS which provides a 0.8 V reference (not available in Deep Sleep mode)
*   - an external device pin
*/
typedef enum
{
    CY_SYSANALOG_VREF_SOURCE_SRSS        = 0UL,                                         /**< Use 0.8 V Vref from SRSS. Low accuracy high noise source that is not intended for analog subsystems. */
    CY_SYSANALOG_VREF_SOURCE_LOCAL_1_2V  = 1UL << PASS_AREF_AREF_CTRL_VREF_SEL_Pos,     /**< Use locally generated 1.2 V Vref */
    CY_SYSANALOG_VREF_SOURCE_EXTERNAL    = 2UL << PASS_AREF_AREF_CTRL_VREF_SEL_Pos      /**< Use externally supplied Vref */
}cy_en_sysanalog_vref_source_t;


/** AREF IZTAT sources
*
* The AREF generates a 1 uA "Zero dependency To Absolute Temperature" (IZTAT) current reference
* that is independent of temperature variations. It can come from one of two sources:
*   - Local reference (1 uA)
*   - Reference from the SRSS (250 nA that is gained by 4. Not available in Deep Sleep mode)
*/
typedef enum
{
    CY_SYSANALOG_IZTAT_SOURCE_SRSS       = 0UL,                                         /**< Use 250 nA IZTAT from SRSS and gain by 4 to output 1 uA*/
    CY_SYSANALOG_IZTAT_SOURCE_LOCAL      = 1UL << PASS_AREF_AREF_CTRL_IZTAT_SEL_Pos     /**< Use locally generated 1 uA IZTAT */
}cy_en_sysanalog_iztat_source_t;

/** AREF Deep Sleep mode
*
* Configure what part of the AREF block is enabled in Deep Sleep mode.
*   - Disable AREF IP block
*   - Enable IPTAT generator for fast wakeup from Deep Sleep mode.
*     IPTAT outputs for CTBs are disabled.
*   - Enable IPTAT generator and IPTAT outputs for CTB
*   - Enable all generators and outputs: IPTAT, IZTAT, and VREF
*/
typedef enum
{
    CY_SYSANALOG_DEEPSLEEP_DISABLE             = 0UL,                                               /**< Disable AREF IP block */
    CY_SYSANALOG_DEEPSLEEP_IPTAT_1             = PASS_AREF_AREF_CTRL_DEEPSLEEP_ON_Msk | \
                                                 (1UL << PASS_AREF_AREF_CTRL_DEEPSLEEP_MODE_Pos),  /**< Enable IPTAT generator for fast wakeup from Deep Sleep mode
                                                                                                        IPTAT outputs for CTBs are disabled. */
    CY_SYSANALOG_DEEPSLEEP_IPTAT_2             = PASS_AREF_AREF_CTRL_DEEPSLEEP_ON_Msk | \
                                                 (2UL << PASS_AREF_AREF_CTRL_DEEPSLEEP_MODE_Pos),  /**< Enable IPTAT generator and IPTAT outputs for CTB */
    CY_SYSANALOG_DEEPSLEEP_IPTAT_IZTAT_VREF    = PASS_AREF_AREF_CTRL_DEEPSLEEP_ON_Msk | \
                                                 (3UL << PASS_AREF_AREF_CTRL_DEEPSLEEP_MODE_Pos)   /**< Enable all generators and outputs: IPTAT, IZTAT, and VREF */
}cy_en_sysanalog_deep_sleep_t;

/** Interrupt cause sources
*
* Depending on the device, there may be interrupts from these PASS blocks:
*   -# CTDAC (up to 4 instances)
*   -# CTB(m) (up to 4 instances)
*   -# SAR (up to 4 instances)
*   -# FIFO (up to 4 instances)
*
* A device could potentially have more than one instance of CTB or CTDAC blocks.
* To find out which instance caused the interrupt, call
* \ref Cy_SysAnalog_GetIntrCauseExtended and compare the returned result with one of
* these enum values.
*/
typedef enum
{
    CY_SYSANALOG_INTR_CAUSE_CTB0         = PASS_INTR_CAUSE_CTB0_INT_Msk,         /**< Interrupt cause mask for CTB0 */
    CY_SYSANALOG_INTR_CAUSE_CTB1         = PASS_INTR_CAUSE_CTB1_INT_Msk,         /**< Interrupt cause mask for CTB1 */
    CY_SYSANALOG_INTR_CAUSE_CTB2         = PASS_INTR_CAUSE_CTB2_INT_Msk,         /**< Interrupt cause mask for CTB2 */
    CY_SYSANALOG_INTR_CAUSE_CTB3         = PASS_INTR_CAUSE_CTB3_INT_Msk,         /**< Interrupt cause mask for CTB3 */
    CY_SYSANALOG_INTR_CAUSE_CTDAC0       = PASS_INTR_CAUSE_CTDAC0_INT_Msk,       /**< Interrupt cause mask for CTDAC0 */
    CY_SYSANALOG_INTR_CAUSE_CTDAC1       = PASS_INTR_CAUSE_CTDAC1_INT_Msk,       /**< Interrupt cause mask for CTDAC1 */
    CY_SYSANALOG_INTR_CAUSE_CTDAC2       = PASS_INTR_CAUSE_CTDAC2_INT_Msk,       /**< Interrupt cause mask for CTDAC2 */
    CY_SYSANALOG_INTR_CAUSE_CTDAC3       = PASS_INTR_CAUSE_CTDAC3_INT_Msk,       /**< Interrupt cause mask for CTDAC3 */
    CY_SYSANALOG_INTR_CAUSE_SAR0         = PASS_V2_INTR_CAUSE_SAR0_INT_Msk,      /**< Interrupt cause mask for SAR0. Available only for PASS_ver2. */
    CY_SYSANALOG_INTR_CAUSE_SAR1         = PASS_V2_INTR_CAUSE_SAR1_INT_Msk,      /**< Interrupt cause mask for SAR1. Available only for PASS_ver2. */
    CY_SYSANALOG_INTR_CAUSE_SAR2         = PASS_V2_INTR_CAUSE_SAR2_INT_Msk,      /**< Interrupt cause mask for SAR2. Available only for PASS_ver2. */
    CY_SYSANALOG_INTR_CAUSE_SAR3         = PASS_V2_INTR_CAUSE_SAR3_INT_Msk,      /**< Interrupt cause mask for SAR3. Available only for PASS_ver2. */
    CY_SYSANALOG_INTR_CAUSE_FIFO0        = PASS_V2_INTR_CAUSE_FIFO0_INT_Msk,     /**< Interrupt cause mask for FIFO0. Available only for PASS_ver2. */
    CY_SYSANALOG_INTR_CAUSE_FIFO1        = PASS_V2_INTR_CAUSE_FIFO1_INT_Msk,     /**< Interrupt cause mask for FIFO1. Available only for PASS_ver2. */
    CY_SYSANALOG_INTR_CAUSE_FIFO2        = PASS_V2_INTR_CAUSE_FIFO2_INT_Msk,     /**< Interrupt cause mask for FIFO2. Available only for PASS_ver2. */
    CY_SYSANALOG_INTR_CAUSE_FIFO3        = PASS_V2_INTR_CAUSE_FIFO3_INT_Msk,     /**< Interrupt cause mask for FIFO3. Available only for PASS_ver2. */
}cy_en_sysanalog_intr_cause_t;

/** Deep Sleep Clock selection
*
*  Specifies Deep Sleep Clock source:
*  - DSCLK is set to LPOSC
*  - DSCLK is set to CLK_MF
*/
typedef enum
{
    CY_SYSANALOG_DEEPSLEEP_SRC_LPOSC  = 0UL,   /**< DSCLK is set to LPOSC */
    CY_SYSANALOG_DEEPSLEEP_SRC_CLK_MF = 1UL    /**< DSCLK is set to CLK_MF */
}cy_en_sysanalog_deep_sleep_clock_sel_t;

/** Deep Sleep clock divider
*
*  Specifies Deep Sleep Clock divider.
*  - Transparent mode, feed through selected clock source w/o dividing
*  - Divide selected clock source by 2
*  - Divide selected clock source by 4
*  - Divide selected clock source by 8
*  - Divide selected clock source by 16
*/
typedef enum
{
    CY_SYSANALOG_DEEPSLEEP_CLK_NO_DIV    = 0UL,    /**< Transparent mode, feed through selected clock source w/o dividing */
    CY_SYSANALOG_DEEPSLEEP_CLK_DIV_BY_2  = 1UL,    /**< Divide selected clock source by 2 */
    CY_SYSANALOG_DEEPSLEEP_CLK_DIV_BY_4  = 2UL,    /**< Divide selected clock source by 4 */
    CY_SYSANALOG_DEEPSLEEP_CLK_DIV_BY_8  = 3UL,    /**< Divide selected clock source by 8 */
    CY_SYSANALOG_DEEPSLEEP_CLK_DIV_BY_16 = 4UL,    /**< Divide selected clock source by 16 */
}cy_en_sysanalog_deep_sleep_clock_div_t;

/** Low Power Oscillator (LPOSC) modes
*
*   Configures Low Power Oscillator mode in Deep Sleep.
*   - LPOSC enabled by TIMER trigger
*   - LPOSC always on in Deep Sleep
*/
typedef enum
{
    CY_SYSANALOG_LPOSC_DUTY_CYCLED = 0UL,         /**< LPOSC enabled by TIMER trigger */
    CY_SYSANALOG_LPOSC_ALWAYS_ON   = 1UL          /**< LPOSC always on in Deep Sleep */
}cy_en_sysanalog_lposc_deep_sleep_mode_t;

/** Timer clock */
typedef enum
{
    CY_SYSANALOG_TIMER_CLK_PERI      = 0UL,       /**< Timer clocked from CLK_PERI */
    CY_SYSANALOG_TIMER_CLK_DEEPSLEEP = 1UL,       /**< Timer clocked from CLK_DPSLP */
    CY_SYSANALOG_TIMER_CLK_LF        = 2UL        /**< Timer clocked from CLK_LF */
}cy_en_sysanalog_timer_clock_t;

/** \} group_sysanalog_enums */

/** \addtogroup group_sysanalog_data_structures
* \{
*/

/***************************************
*       Configuration Structures
***************************************/

/** Structure to configure the entire AREF block */
typedef struct
{
/** \cond Deprecated, left here for BWC, HW is anyways initialized with CY_SYSANALOG_STARTUP_FAST */
    cy_en_sysanalog_startup_t                   startup;   /**< AREF normal or fast start */
/** \endcond */
    cy_en_sysanalog_iztat_source_t              iztat;     /**< AREF 1uA IZTAT source: Local or SRSS */
    cy_en_sysanalog_vref_source_t               vref;      /**< AREF Vref: Local, SRSS, or external pin */
    cy_en_sysanalog_deep_sleep_t                deepSleep; /**< AREF Deep Sleep mode */
}cy_stc_sysanalog_config_t;

/** Structure to configure PASS_ver2 Deep Sleep features such as Low Power Oscillator, Deep Sleep Clock, Timer */
typedef struct
{
    cy_en_sysanalog_lposc_deep_sleep_mode_t     lpOscDsMode;    /**< Low Power Oscillator Deep Sleep mode */
    cy_en_sysanalog_deep_sleep_clock_sel_t      dsClkSource;    /**< Deep Sleep Clock source select */
    cy_en_sysanalog_deep_sleep_clock_div_t      dsClkdivider;   /**< Deep Sleep Clock divider */
    cy_en_sysanalog_timer_clock_t               timerClock;     /**< Timer Clock source select */
    uint32_t                                    timerPeriod;    /**< Timer period. Range 1..65536 */
}cy_stc_sysanalog_deep_sleep_config_t;

/** \} group_sysanalog_data_structures */

/** \addtogroup group_sysanalog_globals
* \{
*/
/***************************************
*        Global Constants
***************************************/

/** Configure the AREF to use the local Vref and local IZTAT. Can be used with \ref Cy_SysAnalog_Init.
* Other configuration options are set to:
*   - .startup          = CY_PASS_AREF_MODE_FAST
*   - .deepSleep        = CY_PASS_AREF_DEEPSLEEP_DISABLE
*/
extern const cy_stc_sysanalog_config_t Cy_SysAnalog_Fast_Local;

/** Configure the AREF to use the SRSS Vref and SRSS IZTAT. Can be used with \ref Cy_SysAnalog_Init.
* Other configuration options are set to:
*   - .startup          = CY_PASS_AREF_MODE_FAST
*   - .deepSleep        = CY_PASS_AREF_DEEPSLEEP_DISABLE
*/
extern const cy_stc_sysanalog_config_t Cy_SysAnalog_Fast_SRSS;

/** Configure the AREF to use the external Vref and local IZTAT. Can be used with \ref Cy_SysAnalog_Init.
* Other configuration options are set to:
*   - .startup          = CY_PASS_AREF_MODE_FAST
*   - .deepSleep        = CY_PASS_AREF_DEEPSLEEP_DISABLE
*/
extern const cy_stc_sysanalog_config_t Cy_SysAnalog_Fast_External;

/** \} group_sysanalog_globals */

/** \addtogroup group_sysanalog_functions
* \{
*/

/***************************************
*        Function Prototypes
***************************************/

cy_en_sysanalog_status_t Cy_SysAnalog_Init(const cy_stc_sysanalog_config_t * config);
__STATIC_INLINE void Cy_SysAnalog_DeInit(void);
__STATIC_INLINE uint32_t Cy_SysAnalog_GetIntrCauseExtended(const PASS_Type * base);
__STATIC_INLINE void Cy_SysAnalog_SetDeepSleepMode(cy_en_sysanalog_deep_sleep_t deepSleep);
__STATIC_INLINE cy_en_sysanalog_deep_sleep_t Cy_SysAnalog_GetDeepSleepMode(void);
__STATIC_INLINE void Cy_SysAnalog_Enable(void);
__STATIC_INLINE void Cy_SysAnalog_Disable(void);
__STATIC_INLINE void Cy_SysAnalog_VrefSelect(cy_en_sysanalog_vref_source_t vref);
__STATIC_INLINE void Cy_SysAnalog_IztatSelect(cy_en_sysanalog_iztat_source_t iztat);
cy_en_sysanalog_status_t Cy_SysAnalog_DeepSleepInit(PASS_Type * base, const cy_stc_sysanalog_deep_sleep_config_t * config);

/**
* \addtogroup group_sysanalog_functions_lposc
* \{
*/
__STATIC_INLINE void Cy_SysAnalog_LpOscEnable(PASS_Type * base);
__STATIC_INLINE void Cy_SysAnalog_LpOscDisable(PASS_Type * base);
/** \} */


/**
* \addtogroup group_sysanalog_functions_timer
* \{
*/
__STATIC_INLINE void Cy_SysAnalog_TimerEnable(PASS_Type * base);
__STATIC_INLINE void Cy_SysAnalog_TimerDisable(PASS_Type * base);
__STATIC_INLINE void Cy_SysAnalog_TimerSetPeriod(PASS_Type * base, uint32_t periodVal);
__STATIC_INLINE uint32_t Cy_SysAnalog_TimerGetPeriod(const PASS_Type * base);
/** \} */


/*******************************************************************************
* Function Name: Cy_SysAnalog_DeInit
****************************************************************************//**
*
* Reset AREF configuration back to power on reset defaults.
*
* \return None
*
* \funcusage
*
* \snippet sysanalog/snippet/main.c SYSANA_SNIPPET_DEINIT
*
*******************************************************************************/
__STATIC_INLINE void Cy_SysAnalog_DeInit(void)
{
    PASS_AREF_AREF_CTRL = CY_SYSANALOG_DEINIT;
}

/*******************************************************************************
* Function Name: Cy_SysAnalog_GetIntrCauseExtended
****************************************************************************//**
*
* Return the PASS interrupt cause register value.
*
* Depending on the device, there may be interrupts from these PASS blocks:
*   -# CTDAC (up to 4 instances)
*   -# CTB(m) (up to 4 instances)
*   -# SAR (up to 4 instances)
*   -# FIFO (up to 4 instances)
*
* Compare this returned value with the enum values in \ref cy_en_sysanalog_intr_cause_t
* to determine which block caused/triggered the interrupt.
*
* \return uint32_t
* Interrupt cause register value.
*
* \funcusage
*
* \snippet sysanalog/snippet/main.c SYSANA_SNIPPET_GET_INTR_CAUSE
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SysAnalog_GetIntrCauseExtended(const PASS_Type * base)
{
    return PASS_INTR_CAUSE(base);
}

/** \cond **********************************************************************
* Deprecated legacy function - do not use for new designs.
* Use Cy_SysAnalog_GetIntrCauseExtended instead.
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SysAnalog_GetIntrCause(void)
{
    uint32_t retVal = 0UL;

    if (CY_PASS_V1)
    {
        retVal = ((uint32_t)CY_SYSANALOG_INTR_CAUSE_CTB0 |
                  (uint32_t)CY_SYSANALOG_INTR_CAUSE_CTB1 |
                  (uint32_t)CY_SYSANALOG_INTR_CAUSE_CTB2 |
                  (uint32_t)CY_SYSANALOG_INTR_CAUSE_CTB3 |
                  (uint32_t)CY_SYSANALOG_INTR_CAUSE_CTDAC0 |
                  (uint32_t)CY_SYSANALOG_INTR_CAUSE_CTDAC1 |
                  (uint32_t)CY_SYSANALOG_INTR_CAUSE_CTDAC2 |
                  (uint32_t)CY_SYSANALOG_INTR_CAUSE_CTDAC3) &
                  Cy_SysAnalog_GetIntrCauseExtended(CY_PASS_ADDR);
    }

    return (retVal);
} /** \endcond */

/*******************************************************************************
* Function Name: Cy_SysAnalog_SetDeepSleepMode
****************************************************************************//**
*
* Set what parts of the AREF are enabled in Deep Sleep mode.
*   - Disable AREF IP block
*   - Enable IPTAT generator for fast wakeup from Deep Sleep mode.
*     IPTAT outputs for CTBs are disabled.
*   - Enable IPTAT generator and IPTAT outputs for CTB
*   - Enable all generators and outputs: IPTAT, IZTAT, and VREF
*
* \note
* The SRSS references are not available to the AREF in Deep Sleep mode. When operating
* in Deep Sleep mode, the local or external references must be selected.
*
* \param deepSleep
* Select a value from \ref cy_en_sysanalog_deep_sleep_t
*
* \return None
*
* \funcusage
*
* \snippet sysanalog/snippet/main.c SYSANA_SNIPPET_SET_DEEPSLEEP_MODE
*
*******************************************************************************/
__STATIC_INLINE void Cy_SysAnalog_SetDeepSleepMode(cy_en_sysanalog_deep_sleep_t deepSleep)
{
    CY_ASSERT_L3(CY_SYSANALOG_DEEPSLEEP(deepSleep));

    PASS_AREF_AREF_CTRL = (PASS_AREF_AREF_CTRL & ~(PASS_AREF_AREF_CTRL_DEEPSLEEP_ON_Msk | PASS_AREF_AREF_CTRL_DEEPSLEEP_MODE_Msk)) | \
                      (uint32_t) deepSleep;
}

/*******************************************************************************
* Function Name: Cy_SysAnalog_GetDeepSleepMode
****************************************************************************//**
*
* Return Deep Sleep mode configuration as set by \ref Cy_SysAnalog_SetDeepSleepMode
*
* \return
* A value from \ref cy_en_sysanalog_deep_sleep_t
*
* \funcusage
*
* \snippet sysanalog/snippet/main.c SYSANA_SNIPPET_GET_DEEPSLEEP_MODE
*
*******************************************************************************/
__STATIC_INLINE cy_en_sysanalog_deep_sleep_t Cy_SysAnalog_GetDeepSleepMode(void)
{
    return (cy_en_sysanalog_deep_sleep_t) (uint32_t) (PASS_AREF_AREF_CTRL & (PASS_AREF_AREF_CTRL_DEEPSLEEP_ON_Msk | PASS_AREF_AREF_CTRL_DEEPSLEEP_MODE_Msk));
}

/*******************************************************************************
* Function Name: Cy_SysAnalog_Enable
****************************************************************************//**
*
* Enable the AREF hardware block.
*
* \return None
*
* \funcusage
*
* \snippet sysanalog/snippet/main.c SYSANA_SNIPPET_ENABLE
*
*******************************************************************************/
__STATIC_INLINE void Cy_SysAnalog_Enable(void)
{
    PASS_AREF_AREF_CTRL |= PASS_AREF_AREF_CTRL_ENABLED_Msk;
}

/*******************************************************************************
* Function Name: Cy_SysAnalog_Disable
****************************************************************************//**
*
* Disable the AREF hardware block.
*
* \return None
*
* \funcusage
*
* \snippet sysanalog/snippet/main.c SYSANA_SNIPPET_DISABLE
*
*******************************************************************************/
__STATIC_INLINE void Cy_SysAnalog_Disable(void)
{
    PASS_AREF_AREF_CTRL &= ~PASS_AREF_AREF_CTRL_ENABLED_Msk;
}


/** \cond Deprecated, left here for BWC, always writes CY_SYSANALOG_STARTUP_FAST into the register */
__STATIC_INLINE void Cy_SysAnalog_SetArefMode(cy_en_sysanalog_startup_t startup)
{
    CY_UNUSED_PARAMETER(startup);
    PASS_AREF_AREF_CTRL |= (uint32_t)CY_SYSANALOG_STARTUP_FAST;
}
/** \endcond */


/*******************************************************************************
* Function Name: Cy_SysAnalog_VrefSelect
****************************************************************************//**
*
* Set the source for the Vref. The Vref can come from:
*   - the locally generated 1.2 V reference
*   - the SRSS, which provides a 0.8 V reference (not available to the AREF in Deep Sleep mode)
*   - an external device pin
*
* The locally generated reference has higher accuracy, more stability over temperature,
* and lower noise than the SRSS reference.
*
* \param vref
* Value from enum \ref cy_en_sysanalog_vref_source_t
*
* \return None
*
* \funcusage
*
* \snippet sysanalog/snippet/main.c SYSANA_SNIPPET_VREF_SELECT
*
*******************************************************************************/
__STATIC_INLINE void Cy_SysAnalog_VrefSelect(cy_en_sysanalog_vref_source_t vref)
{
    CY_ASSERT_L3(CY_SYSANALOG_VREF(vref));

    PASS_AREF_AREF_CTRL = (PASS_AREF_AREF_CTRL & ~PASS_AREF_AREF_CTRL_VREF_SEL_Msk) | (uint32_t) vref;
}

/*******************************************************************************
* Function Name: Cy_SysAnalog_IztatSelect
****************************************************************************//**
*
* Set the source for the 1 uA IZTAT. The IZTAT can come from:
*   - the locally generated IZTAT
*   - the SRSS (not available to the AREF in Deep Sleep mode)
*
* The locally generated reference has higher accuracy, more stability over temperature,
* and lower noise than the SRSS reference.
*
* \param iztat
* Value from enum \ref cy_en_sysanalog_iztat_source_t
*
* \return None
*
* \funcusage
*
* \snippet sysanalog/snippet/main.c SYSANA_SNIPPET_IZTAT_SELECT
*
*******************************************************************************/
__STATIC_INLINE void Cy_SysAnalog_IztatSelect(cy_en_sysanalog_iztat_source_t iztat)
{
    CY_ASSERT_L3(CY_SYSANALOG_IZTAT(iztat));

    PASS_AREF_AREF_CTRL = (PASS_AREF_AREF_CTRL & ~PASS_AREF_AREF_CTRL_IZTAT_SEL_Msk) | (uint32_t) iztat;
}

/**
* \addtogroup group_sysanalog_functions_lposc
* \{
*/

/*******************************************************************************
* Function Name: Cy_SysAnalog_LpOscEnable
****************************************************************************//**
*
* Enables Low Power Oscillator in configured by \ref Cy_SysAnalog_DeepSleepInit
* mode.
*
* \param base Pointer to the PASS register structure.
*
* \return None
*
* \funcusage \snippet sysanalog/snippet/main.c SYSANA_SNIPPET_LPOSC_ENABLE
*
*******************************************************************************/
__STATIC_INLINE void Cy_SysAnalog_LpOscEnable(PASS_Type * base)
{
    if(!CY_PASS_V1)
    {
        PASS_LPOSC_CTRL(base) = PASS_LPOSC_V2_CTRL_ENABLED_Msk;
    }
    else
    {
        /* Low Power Oscillator feature is not supported on PASS_ver1 IP block. */
        CY_ASSERT_L1(false);
    }
}


/*******************************************************************************
* Function Name: Cy_SysAnalog_LpOscDisable
****************************************************************************//**
*
* Disables the Low Power Oscillator.
*
* \param base Pointer to the PASS register structure.
*
* \return None
*
* \funcusage \snippet sysanalog/snippet/main.c SYSANA_SNIPPET_LPOSC_DISABLE
*
*******************************************************************************/
__STATIC_INLINE void Cy_SysAnalog_LpOscDisable(PASS_Type * base)
{
    if(!CY_PASS_V1)
    {
        PASS_LPOSC_CTRL(base) = 0UL;
    }
}

/** \} */

/**
* \addtogroup group_sysanalog_functions_timer
* \{
*/

/*******************************************************************************
* Function Name: Cy_SysAnalog_TimerEnable
****************************************************************************//**
*
* Enable the analog subsystem timer in configured by
* \ref Cy_SysAnalog_DeepSleepInit mode.
*
* \param base Pointer to the PASS register structure.
*
* \return None
*
* \funcusage \snippet sysanalog/snippet/main.c SYSANA_SNIPPET_TIMER
*
*******************************************************************************/
__STATIC_INLINE void Cy_SysAnalog_TimerEnable(PASS_Type * base)
{
    if (!CY_PASS_V1)
    {
        PASS_TIMER_CTRL(base) = PASS_TIMER_V2_CTRL_ENABLED_Msk;
    }
}


/*******************************************************************************
* Function Name: Cy_SysAnalog_TimerDisable
****************************************************************************//**
*
* Disable the analog subsystem timer.
*
* \param base Pointer to the PASS register structure.
*
* \return None
*
* \funcusage \snippet sysanalog/snippet/main.c SYSANA_SNIPPET_TIMER
*
*******************************************************************************/
__STATIC_INLINE void Cy_SysAnalog_TimerDisable(PASS_Type * base)
{
    if (!CY_PASS_V1)
    {
        PASS_TIMER_CTRL(base) = 0UL;
    }
}

/*******************************************************************************
* Function Name: Cy_SysAnalog_TimerSetPeriod
****************************************************************************//**
*
* Sets the analog subsystem timer period.
*
* \param base Pointer to the PASS register structure.
*
* \param periodVal the period value. Actual timer period equals periodVal + 1.
*
* \return None
*
* \funcusage \snippet sysanalog/snippet/main.c SYSANA_SNIPPET_TIMER_PERIOD
*
*******************************************************************************/
__STATIC_INLINE void Cy_SysAnalog_TimerSetPeriod(PASS_Type * base, uint32_t periodVal)
{
    if (!CY_PASS_V1)
    {
        PASS_TIMER_PERIOD(base) = _VAL2FLD(PASS_TIMER_V2_PERIOD_PER_VAL, periodVal);
    }
    else
    {
        /* Timer feature is not supported on PASS_ver1 IP block. */
        CY_ASSERT_L1(false);
    }
}

/*******************************************************************************
* Function Name: Cy_SysAnalog_TimerGetPeriod
****************************************************************************//**
*
* Returns the analog subsystem timer period.
*
* \param base Pointer to the PASS register structure.
*
* \return the Timer period value.
*
* \funcusage \snippet sysanalog/snippet/main.c SYSANA_SNIPPET_TIMER_PERIOD
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_SysAnalog_TimerGetPeriod(const PASS_Type * base)
{
    uint32_t period = 0UL;
    if (!CY_PASS_V1)
    {
        period = _FLD2VAL(PASS_TIMER_V2_PERIOD_PER_VAL, PASS_TIMER_PERIOD(base));
    }

    return period;
}

/** \} */

/** \} group_sysanalog_functions */
CY_MISRA_BLOCK_END('MISRA C-2012 Rule 11.3');

#if defined(__cplusplus)
}
#endif

#endif /* CY_IP_MXS40PASS */

#endif /** !defined(CY_SYSANALOG_H) */

/** \} group_sysanalog */

/* [] END OF FILE */
