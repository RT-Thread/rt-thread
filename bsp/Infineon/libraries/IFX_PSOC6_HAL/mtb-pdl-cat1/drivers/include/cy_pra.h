/***************************************************************************//**
* \file cy_pra.h
* \version 2.40
*
* \brief The header file of the PRA driver. The API is not intended to
* be used directly by the user application.
*
********************************************************************************
* \copyright
* Copyright (c) (2020-2022), Cypress Semiconductor Corporation
* (an Infineon company) or an affiliate of Cypress Semiconductor Corporation.
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
* \addtogroup group_pra
* \{
* \note The Protection Register Access (PRA) driver is intended for the PSoC 64
* devices only and provides other PDL drivers access to the registers that have
* secure access restrictions. It is not intended to be used directly by user
* application.
*
* The PRA driver is used to protect the system from invalid configurations that
* could potentially cause the system to be unstable or indirectly allow access
* to registers and memory that are protected. This is done using several
* methods:
* * Allow only valid register settings.
* * Force a specified sequence of operations when writing to a register.
* * Totally block access to registers that are deemed critical to security.
* * Allow only known, well defined system configurations.
* * Allow access to non-critical registers that are protected by a fixed PPU.
*
*   On PSoC 64 devices, secure firmware protects entire regions of registers
*   with the fixed PPUs, however there are some registers within that regions
*   that should not be protected but, are protected due to fixed PPU
*   granularity.
*
*   The list of the registers that can be accessed by PRA driver directly is
*   defined in the cy_pra.h file with the CY_PRA_INDX_ prefix.
*
* Most PDL drivers are not affected or use the PRA driver. Only the following
* PDL drivers are affected by this driver:
* * \ref group_lvd
* * \ref group_syslib
* * \ref group_sysclk
* * \ref group_syspm
* * \ref group_arm_system_timer
* * \ref group_wdt
* * \ref group_flash
* * \ref group_sysint (PSoC 64 CYB06xx7 devices only)
* * \ref group_prot (PSoC 64 CYB06xx7 devices only)
* * \ref group_gpio
*
* The execution time of the functions that access the protected registers is
* increased on the PSoC 64 devices because the access is performed on Cortex-M0+
* via the IPC command (both CPU cores run at 8 MHz):
* * The access to the protected register may take about 50 us, while access
*   to the unprotected one may take about 3 us.
* * The initial device configuration may take up to 1.75 ms for PSoC 64 devices,
*   while for the other devices it may take about 0.3 ms.
* * The transition Active to DeepSleep to Active may take about 2 times longer.
*
* \section group_pra_basic_operation Basic Operation
* The PRA driver uses an IPC channel to transfer register data between the user
* application running on the Cortex-CM4 and the secure Cortex-CM0+ CPU. The
* secure processor performs the data validation and correct register write
* sequence to ensure proper stable operation of the system. Function status and
* requested data is also returned via the IPC channel.
*
* The PDL driver that accesses protected registers, generates request to the
* PRA driver and it passes request over the IPC to secure Cortex-M0+, where
* request is validated and executed, and, then, reports result back to the
* driver on Cortex-M4 side.
*
* \image html pra_high_level_diagram.png
*
* \section group_pra_device_config Device Configuration
* For PSoC 64 device, device configuration (like system clock settings and
* power modes) is applied on the secure Cortex-M0+. The device configuration
* can be initiated from either of the core or both the cores. The device
* configuration structure \ref cy_stc_pra_system_config_t is initialized
* with Device Configurator. For Cortext-M4 application, it passed to the
* secure Cortex-M0+ core through IPC for validation and register the update
* in the cybsp_init() function. For Cortext-M0+ application, this device
* configuration structure is directly validated and applied.
*
* \note The external clocks (ECO, WCO, and EXTCLK) require
* additional configuration to be allowed to source CLK_HF0 (clocks both
* Cortex-M0+ and Cortex-M4 CPUs) in order to prevent clock tampering.
* See \ref group_pra_external_clocks for details.
*
* \note The ALTHF (BLE ECO) is not allowed to source CLK_HF0 (clocks both
* Cortex-M0+ and Cortex-M4 CPUs) in order to prevent clock tampering.
*
* \note The internal low-frequency clocks (ILO and PILO) are not allowed to
* source the CLK_HF0 directly and through PLL or FLL.
*
* \note The clock source for Cortex-M4 SysTick cannot be configured with
* the Device Configurator. Enabling CLK_ALT_SYS_TICK will result in a
* compilation error. SysTick still can be configured in run-time with
* some limitations. For more details, refer to \ref Cy_SysTick_SetClockSource()
* in \ref group_arm_system_timer.
*
* \note
* When EXT_CLK is source to HF0 then the drive mode for EXT_CLK pin is hard coded
* to CY_GPIO_DM_HIGHZ. So user has to make sure this pin configuration is not
* overwritten from secure application.
*
*\section group_pra_external_clocks External Clock Sources
* The PSoC 64 devices must be provisioned with the external clocks
* (ECO, WCO, and EXTCLK) configuration before routing these
* clocks to CLK_HF0. To do that, update the JSON
* file (delivered with CySecureTools) with the "extclk" node in the
* custom data section as shown below. The configuration fields in the
* JSON file match the fields in the Device Configurator.
*
* For more details, refer to the PSoC 64 Secure MCU Secure Boot SDK User Guide.
*
*\code{json}
*    For EXTCLK:
*        "custom_data_sections": ["extclk"],
*        "extclk": {
*                "extClkEnable": 1,
*                "extClkFreqHz": 24000000,
*                "extClkPort": 0,
*                "extClkPinNum": 0,
*                "extClkHsiom": 0
*        }
*
*    For ECO:
*        "custom_data_sections": ["extclk"],
*        "extclk": {
*                "ecoEnable": 1,
*                "ecoFreqHz": 24000000,
*                "ecoLoad": 18,
*                "ecoEsr": 50,
*                "ecoDriveLevel": 100,
*                "ecoInPort": 12,
*                "ecoOutPort": 12,
*                "ecoInPinNum": 6,
*                "ecoOutPinNum": 7,
*        }
*
*    For WCO:
*        "custom_data_sections": ["extclk"],
*        "extclk": {
*                "wcoEnable": 1,
*                "bypassEnable": 0
*                "wcoInPort": 0,
*                "wcoOutPort": 0,
*                "wcoInPinNum": 0,
*                "wcoOutPinNum": 1
*        }
*\endcode
*
*\note The same "extclk" section is used for all external clocks. If more than
* one external clock source is required, please append its parameters.
*
*\section group_pra_sram_power_config SRAM Power Mode Configurations
* The PSoC 64 devices must be provisioned with the SRAM power mode configuration
* to protects secure core memory. To do that, update the JSON
* file (delivered with CySecureTools) with the "srampwrmode" node in the
* custom data section as shown below.
*
* For more details, refer to the PSoC 64 Secure MCU Secure Boot SDK User Guide.
*
*\code{json}
*    "custom_data_sections": ["srampwrmode"],
*    "sram0": [
*        {
*            "macroNum": 1,      // bits 0
*            "powerMode": 6,     // bit 2 = ON, bit 1 = RETAIN, bit 0 = OFF
*        },
*        {
*            "macroNum": 2,      // bits 1
*            "powerMode": 1,     // bit 2 = ON, bit 1 = RETAIN, bit 0 = OFF
*        },
*        {
*            "macroNum": 65532,  // bits [15-2] = 0xFFFC
*            "powerMode": 7,     // bit 2 = ON, bit 1 = RETAIN, bit 0 = OFF
*        }
*    ],
*    "sram1": [
*        {
*            "macroNum": 1,      // bit 0
*            "powerMode": 7,     // bit 2 = ON, bit 1 = RETAIN, bit 0 = OFF
*        }
*    ],
*    "sram2": [
*        {
*            "macroNum": 1,      // bit 0
*            "powerMode": 7,     // bit 2 = ON, bit 1 = RETAIN, bit 0 = OFF
*        }
*    ]
*\endcode
*
*\note If a particular configuration(either SRAM or macro section) is
* not present in the policy file but available in the device then SRAM MACRO
* can be allowed to be modified to any of power modes (ON, RETAIN and OFF).
*
* \section group_pra_standalone Using without BSPs
* If PDL is used in Standalone mode without Board Support Package (BSP),
* do the following:
* * 1) Call the \ref Cy_PRA_Init function prior to executing
*   API of any of the drivers listed above. By default, this function is
*   called from \ref SystemInit on both CPU cores.
* * 2) Call the \ref Cy_PRA_SystemConfig function with the initial
*   device configuration passed as a parameter. Refer to Section "Function Usage"
*   of the \ref Cy_PRA_SystemConfig function for more details.
*
* \section group_pra_more_information More Information
* See the device technical reference manual (TRM) reference manual (TRM) for
* the list of the protected registers.
*
* \section group_pra_changelog Changelog
* <table class="doxtable">
*   <tr><th>Version</th><th>Changes</th><th>Reason for Change</th></tr>
*   <tr>
*     <td>2.40</td>
*     <td>Initialize internal data structure to initial values when external
*         clock policy pointer is NULL to avoid null pointer de-referencing.</td>
*     <td>Defect fix.</td>
*   </tr>
*   <tr>
*     <td rowspan="4">2.30</td>
*     <td>System Configuration can be done from CM0+ using PRA API with
*         CY_PRA_MSG_TYPE_SYS_CFG_FUNC and CY_PRA_FUNC_INIT_CYCFG_DEVICE arguments.</td>
*     <td>Enhancement based on customer feedback.</td>
*   </tr>
*   <tr>
*     <td>System configuration structure is updated with appropriate value, when
*         cm0+ application calls any PDL API accessing to FUNCTION_POLICY registers.</td>
*     <td>Enhancement based on customer feedback.</td>
*   </tr>
*   <tr>
*     <td>Fixed MISRA 2012 violations.</td>
*     <td>MISRA 2012 compliance.</td>
*   </tr>
*   <tr>
*     <td>Updated doxygen for External clock source to HF0.</td>
*     <td>Documentation enhancement.</td>
*   </tr>
*   <tr>
*     <td>2.20</td>
*     <td>Allowing external clocks (EXT_CLK, ECO and WCO) can be source to secure core.
*         Provide interface for validating and configuring SRAM power modes.</td>
*     <td>External clock support and
*         SRAM power mode configuration support.</td>
*   </tr>
*   <tr>
*     <td rowspan="3">2.10</td>
*     <td>Removed include of cy_gpio.h from the driver's c source files.
*         Added some source code comments.</td>
*     <td>Source code cleanup.</td>
*   </tr>
*   <tr>
*     <td>Updated attribute usage for the linker section placement.</td>
*     <td>Enhancement based on usability feedback.</td>
*   </tr>
*   <tr>
*     <td>Fixed MISRA 2012 violations.</td>
*     <td>MISRA 2012 compliance.</td>
*   </tr>
*   <tr>
*     <td rowspan="6">2.0</td>
*     <td> Added PSoC 64 CYB06xx7 devices support.</td>
*     <td> New devices support.</td>
*   </tr>
*   <tr>
*     <td>
*          Updated Cy_PRA_Init() to compare the major and minor version of the PRA driver on the
*          Cortex-M0+ and Cortex-M4 sides and halt Cortex-M4 if the versions are different.
*     </td>
*     <td> Ensure that the same PRA driver version is used on the  Cortex-M0+ and Cortex-M4 sides.</td>
*   </tr>
*   <tr>
*     <td> Fixed the location of the \ref cy_stc_pra_system_config_t description in the documentation.
*     </td>
*     <td>Documentation update.</td>
*   </tr>
*   <tr>
*     <td> Corrected the reference to the \ref group_arm_system_timer function with the
*          limitation description - \ref Cy_SysTick_SetClockSource().
*     </td>
*     <td> Documentation update.</td>
*   </tr>
*   <tr>
*     <td> The state of the following clocks changes only when the requested state
*          differs from the actual state in the hardware:
*          HF1-HF5, TIMER, PUMP, BLE_ECO, ILO, PILO, and WCO.
*     </td>
*     <td> Improved the \ref Cy_PRA_SystemConfig() function execution time.</td>
*   </tr>
*   <tr>
*     <td> Renamed altHfFreq to altHFclkFreq in \ref cy_stc_pra_system_config_t.</td>
*     <td> Eliminated the naming conflict with the SysClk driver.</td>
*   </tr>
*   <tr>
*     <td>1.0</td>
*     <td>Initial version</td>
*     <td></td>
*   </tr>
* </table>
*
* \defgroup group_pra_macros        Macros
* \defgroup group_pra_functions     Functions
* \defgroup group_pra_enums         Enumerated Types
* \defgroup group_pra_stc           Data Structures
*/

#if !defined(CY_PRA_H)
#define CY_PRA_H

#include "cy_device.h"

#if defined (CY_IP_MXS40SRSS)

#include <stdint.h>
#include <stdbool.h>
#include "cy_systick.h"
#include "cy_ble_clk.h"
#include "cy_device_headers.h"

#if defined (CY_DEVICE_SECURE) || defined (CY_DOXYGEN)

#ifdef __cplusplus
extern "C" {
#endif

/***************************************
*        Constants
***************************************/

/** \cond INTERNAL */

#if defined(CY_DEVICE_PSOC6ABLE2)
#define CY_PRA_REG_INDEX_COUNT           (157U)
#else
#define CY_PRA_REG_INDEX_COUNT           (147U)
#endif /* defined(CY_DEVICE_PSOC6ABLE2) */
#define CY_PRA_EXTCLK_PIN_NR             (5U) /* Protected pins: EXTCLK, ECO_IN, ECO_OUT, WCO_IN,  WCO_OUT */
#define CY_PRA_SRAM_MAX_NR               CPUSS_SRAM_COUNT
#define CY_PRA_SRAM_MACRO_MAX_NR         (16U)

#define CY_PRA_MSG_TYPE_REG32_GET        (1U)
#define CY_PRA_MSG_TYPE_REG32_CLR_SET    (2U)
#define CY_PRA_MSG_TYPE_REG32_SET        (3U)
#define CY_PRA_MSG_TYPE_CM0_WAKEUP       (4U)
#define CY_PRA_MSG_TYPE_SYS_CFG_FUNC     (5U)
#define CY_PRA_MSG_TYPE_SECURE_ONLY      (6U)
#define CY_PRA_MSG_TYPE_FUNC_POLICY      (7U)
#define CY_PRA_MSG_TYPE_VERSION_CHECK    (8U)
#define CY_PRA_MSG_TYPE_EXTCLK_PIN_LIST  (9U)
#define CY_PRA_MSG_TYPE_EXTCLK_ADJHSIOM_LIST    (10U)

/* IPC */
#define CY_PRA_IPC_NOTIFY_INTR          (0x1UL << CY_IPC_INTR_PRA)
#define CY_PRA_IPC_CHAN_INTR            (0x1UL << CY_IPC_CHAN_PRA)
#define CY_PRA_IPC_NONE_INTR            (0UL)

/* Registers Index */
#define CY_PRA_INDX_SRSS_PWR_LVD_CTL            (0U)
#define CY_PRA_INDX_SRSS_SRSS_INTR              (1U)
#define CY_PRA_INDX_SRSS_SRSS_INTR_SET          (2U)
#define CY_PRA_INDX_SRSS_SRSS_INTR_MASK         (3U)
#define CY_PRA_INDX_SRSS_SRSS_INTR_CFG          (4U)
#define CY_PRA_INDX_SRSS_CLK_ROOT_SELECT_1      (5U)
/* Do not change the index below because it is used in flash loaders */
#define CY_PRA_INDX_SRSS_CLK_ROOT_SELECT_2      (6U)
#define CY_PRA_INDX_SRSS_CLK_ROOT_SELECT_3      (7U)
#define CY_PRA_INDX_SRSS_CLK_ROOT_SELECT_4      (8U)
#define CY_PRA_INDX_SRSS_CLK_ROOT_SELECT_5      (9U)
#define CY_PRA_INDX_SRSS_CLK_ROOT_SELECT_6      (10U)
#define CY_PRA_INDX_FLASHC_FLASH_CMD            (11U)
#define CY_PRA_INDX_SRSS_PWR_HIBERNATE          (12U)
#define CY_PRA_INDX_SRSS_CLK_MFO_CONFIG         (13U)
#define CY_PRA_INDX_SRSS_CLK_MF_SELECT          (14U)
#define CY_PRA_INDX_FLASHC_FM_CTL_BOOKMARK      (15U)
/* There are MS_NR (16) registers. The index 16 to 31 are used. */
#define CY_PRA_INDX_PROT_MPU_MS_CTL             (16u)
/* The next index should be 32. */
/* EXT CLK port has 21 registers. The index 32 to 52 are used. */
#define CY_PRA_INDX_GPIO_EXTCLK_PRT             (32U)
/* ECO in-Port has 21 registers. The index 53 to 73 are used */
#define CY_PRA_INDX_GPIO_ECO_IN_PRT             (53U)
/* ECO out-Port has 21 registers. The index 74 to 94 are used */
#define CY_PRA_INDX_GPIO_ECO_OUT_PRT            (74U)
/* HSIOM PORT has 2 registers. The index 95 to 115 are used */
#define CY_PRA_INDX_GPIO_WCO_IN_PRT             (95U)
/* WCO out-Port has 21 registers. The index 116 to 136 are used */
#define CY_PRA_INDX_GPIO_WCO_OUT_PRT            (116U)
/* HSIOM PORT has 2 registers. The index 137 to 138 are used */
#define CY_PRA_INDEX_HSIOM_EXTCLK_PRT           (137U)
/* HSIOM PORT has 2 registers. The index 139 to 140 are used */
#define CY_PRA_INDEX_HSIOM_ECO_IN_PRT           (139U)
/* HSIOM PORT has 2 registers. The index 141 to 142 are used */
#define CY_PRA_INDEX_HSIOM_ECO_OUT_PRT          (141U)
/* HSIOM PORT has 2 registers. The index 143 to 144 are used */
#define CY_PRA_INDEX_HSIOM_WCO_IN_PRT           (143U)
/* HSIOM PORT has 2 registers. The index 145 to 146 are used */
#define CY_PRA_INDEX_HSIOM_WCO_OUT_PRT          (145U)

#if defined(CY_DEVICE_PSOC6ABLE2)
/* HSIOM PORT has 2 registers. The index 147 to 148 are used */
#define CY_PRA_INDEX_HSIOM_EXTCLK_ADJ_PRT       (147U)
/* HSIOM PORT has 2 registers. The index 149 to 150 are used */
#define CY_PRA_INDEX_HSIOM_ECO_IN_ADJ_PRT       (149U)
/* HSIOM PORT has 2 registers. The index 151 to 152 are used */
#define CY_PRA_INDEX_HSIOM_ECO_OUT_ADJ_PRT      (151U)
/* HSIOM PORT has 2 registers. The index 153 to 154 are used */
#define CY_PRA_INDEX_HSIOM_WCO_IN_ADJ_PRT       (153U)
/* HSIOM PORT has 2 registers. The index 155 to 156 are used */
#define CY_PRA_INDEX_HSIOM_WCO_OUT_ADJ_PRT      (155U)
/* The next index should be 157 */
#else
/* The next index should be 147 */
#endif /* defined(CY_DEVICE_PSOC6ABLE2) */

/* GPIO PORT REG Sub Index */
#define CY_PRA_SUB_INDEX_PORT_OUT                   (0U)
#define CY_PRA_SUB_INDEX_PORT_OUT_CLR               (1U)
#define CY_PRA_SUB_INDEX_PORT_OUT_SET               (2U)
#define CY_PRA_SUB_INDEX_PORT_OUT_INV               (3U)
#define CY_PRA_SUB_INDEX_PORT_IN                    (4U)
#define CY_PRA_SUB_INDEX_PORT_INTR                  (5U)
#define CY_PRA_SUB_INDEX_PORT_INTR_MASK             (6U)
#define CY_PRA_SUB_INDEX_PORT_INTR_MASKED           (7U)
#define CY_PRA_SUB_INDEX_PORT_INTR_SET              (8U)
#define CY_PRA_SUB_INDEX_PORT_INTR_CFG              (9U)
#define CY_PRA_SUB_INDEX_PORT_CFG                   (10U)
#define CY_PRA_SUB_INDEX_PORT_CFG_IN                (11U)
#define CY_PRA_SUB_INDEX_PORT_CFG_OUT               (12U)
#define CY_PRA_SUB_INDEX_PORT_CFG_SIO               (13U)

/* HSIOM PORT REG sub index */
#define CY_PRA_SUB_INDEX_HSIOM_PORT0                (0U)
#define CY_PRA_SUB_INDEX_HSIOM_PORT1                (1U)


/* Functions Index */
#define CY_PRA_FUNC_INIT_CYCFG_DEVICE           (0U)

#define CY_PRA_CLK_FUNC_ECO_DISABLE             (8U)
#define CY_PRA_CLK_FUNC_FLL_DISABLE             (9U)
#define CY_PRA_CLK_FUNC_PLL_DISABLE             (10U)
#define CY_PRA_CLK_FUNC_ILO_ENABLE              (11U)
#define CY_PRA_CLK_FUNC_ILO_DISABLE             (12U)
#define CY_PRA_CLK_FUNC_ILO_HIBERNATE_ON        (13U)
#define CY_PRA_CLK_FUNC_PILO_ENABLE             (14U)
#define CY_PRA_CLK_FUNC_PILO_DISABLE            (15U)
#define CY_PRA_CLK_FUNC_PILO_SET_TRIM           (16U)
#define CY_PRA_CLK_FUNC_WCO_ENABLE              (17U)
#define CY_PRA_CLK_FUNC_WCO_DISABLE             (18U)
#define CY_PRA_CLK_FUNC_WCO_BYPASS              (19U)
#define CY_PRA_CLK_FUNC_HF_ENABLE               (20U)
#define CY_PRA_CLK_FUNC_HF_DISABLE              (21U)
#define CY_PRA_CLK_FUNC_HF_SET_SOURCE           (22U)
#define CY_PRA_CLK_FUNC_HF_SET_DIVIDER          (23U)
#define CY_PRA_CLK_FUNC_FAST_SET_DIVIDER        (24U)
#define CY_PRA_CLK_FUNC_PERI_SET_DIVIDER        (25U)
#define CY_PRA_CLK_FUNC_LF_SET_SOURCE           (26U)
#define CY_PRA_CLK_FUNC_TIMER_SET_SOURCE        (27U)
#define CY_PRA_CLK_FUNC_TIMER_SET_DIVIDER       (28U)
#define CY_PRA_CLK_FUNC_TIMER_ENABLE            (29U)
#define CY_PRA_CLK_FUNC_TIMER_DISABLE           (30U)
#define CY_PRA_CLK_FUNC_PUMP_SET_SOURCE         (31U)
#define CY_PRA_CLK_FUNC_PUMP_SET_DIVIDER        (32U)
#define CY_PRA_CLK_FUNC_PUMP_ENABLE             (33U)
#define CY_PRA_CLK_FUNC_PUMP_DISABLE            (34U)
#define CY_PRA_CLK_FUNC_BAK_SET_SOURCE          (35U)
#define CY_PRA_CLK_FUNC_ECO_CONFIGURE           (36U)
#define CY_PRA_CLK_FUNC_ECO_ENABLE              (37U)
#define CY_PRA_CLK_FUNC_PATH_SET_SOURCE         (38U)
#define CY_PRA_CLK_FUNC_FLL_MANCONFIG           (39U)
#define CY_PRA_CLK_FUNC_FLL_ENABLE              (40U)
#define CY_PRA_CLK_FUNC_PLL_MANCONFIG           (41U)
#define CY_PRA_CLK_FUNC_PLL_ENABLE              (42U)
#define CY_PRA_CLK_FUNC_SLOW_SET_DIVIDER        (43U)
#define CY_PRA_CLK_FUNC_DS_BEFORE_TRANSITION    (44U)
#define CY_PRA_CLK_FUNC_DS_AFTER_TRANSITION     (45U)
#define CY_PRA_CLK_FUNC_EXT_CLK_SET_FREQUENCY   (46U)
#define CY_PRA_CLK_FUNC_ILO_TRIM                (47U)
#define CY_PRA_CLK_FUNC_SET_PILO_TRIM           (48U)
#define CY_PRA_CLK_FUNC_UPDATE_PILO_TRIM_STEP   (49U)
#define CY_PRA_CLK_FUNC_START_MEASUREMENT       (50U)
#define CY_PRA_CLK_FUNC_PILO_INITIAL_TRIM       (51U)

#define CY_PRA_PM_FUNC_HIBERNATE                (102U)
#define CY_PRA_PM_FUNC_CM4_DP_FLAG_SET          (103U)
#define CY_PRA_PM_FUNC_LDO_SET_VOLTAGE          (104U)
#define CY_PRA_PM_FUNC_BUCK_ENABLE              (105U)
#define CY_PRA_PM_FUNC_SET_MIN_CURRENT          (106U)
#define CY_PRA_PM_FUNC_SET_NORMAL_CURRENT       (107U)
#define CY_PRA_PM_FUNC_BUCK_ENABLE_VOLTAGE2     (108U)
#define CY_PRA_PM_FUNC_BUCK_DISABLE_VOLTAGE2    (109U)
#define CY_PRA_PM_FUNC_BUCK_VOLTAGE2_HW_CTRL    (110U)
#define CY_PRA_PM_FUNC_BUCK_SET_VOLTAGE2        (111U)
#define CY_PRA_PM_FUNC_SRAM_MACRO_PWR_MODE      (112U) /* Apply power mode to particular macro */
#define CY_PRA_PM_FUNC_SRAM_PWR_MODE            (113U) /* Apply power mode to entire sram */

#define CY_PRA_BLE_CLK_FUNC_ECO_CONFIGURE       (200U)
#define CY_PRA_BLE_CLK_FUNC_ECO_RESET           (201U)

#define CY_PRA_GPIO_FUNC_SECPIN                 (300U)

#define CY_PRA_PM_SRAM_PWR_MODE_OFF_Pos         (0UL)
#define CY_PRA_PM_SRAM_PWR_MODE_OFF_Msk         (0x1UL)
#define CY_PRA_PM_SRAM_PWR_MODE_RETAIN_Pos      (1UL)
#define CY_PRA_PM_SRAM_PWR_MODE_RETAIN_Msk      (0x2UL)
#define CY_PRA_PM_SRAM_PWR_MODE_ON_Pos          (2UL)
#define CY_PRA_PM_SRAM_PWR_MODE_ON_Msk          (0x4UL)

#define CY_PRA_SRAM0_INDEX                      (0U) /* SRAM0 index */
#define CY_PRA_SRAM1_INDEX                      (1U) /* SRAM1 index */
#define CY_PRA_SRAM2_INDEX                      (2U) /* SRAM2 index */

/** Driver major version */
#define CY_PRA_DRV_VERSION_MAJOR       2

/** Driver minor version */
#define CY_PRA_DRV_VERSION_MINOR       40

/** Protected Register Access driver ID */
#define CY_PRA_ID                       (CY_PDL_DRV_ID(0x46U))

/** \endcond */

/**
* \addtogroup group_pra_enums
* \{
*/
/** Status definitions of the PRA function return values. */
typedef enum
{
    CY_PRA_STATUS_SUCCESS                           = 0x0U,                                         /**< Returns success */
    CY_PRA_STATUS_ACCESS_DENIED                     = CY_PRA_ID | CY_PDL_STATUS_ERROR | 0xFFFU,     /**< Access denied - PRA does not allow a call from Non-Secure */
    CY_PRA_STATUS_INVALID_PARAM                     = CY_PRA_ID | CY_PDL_STATUS_ERROR | 0xFFEU,     /**< Invalid parameter */
    CY_PRA_STATUS_ERROR_PROCESSING                  = CY_PRA_ID | CY_PDL_STATUS_ERROR | 0xFFDU,     /**< An error while applying the device configuration */
    CY_PRA_STATUS_REQUEST_SENT                      = CY_PRA_ID | CY_PDL_STATUS_INFO  | 0xFFCU,     /**< The IPC message status when sent from Non-Secure to Secure */
    CY_PRA_STATUS_ERROR_SYSPM_FAIL                  = CY_PRA_ID | CY_PDL_STATUS_ERROR | 0xFFBU,     /**< SysPM failure */
    CY_PRA_STATUS_ERROR_SYSPM_TIMEOUT               = CY_PRA_ID | CY_PDL_STATUS_ERROR | 0xFFAU,     /**< SysPM operation timeout */
    CY_PRA_STATUS_ERROR_PRA_VERSION                 = CY_PRA_ID | CY_PDL_STATUS_ERROR | 0xFF9U,     /**< The driver version mismatch between Cortex-M0+ and Cortex-M4 */
    /* Reserve 0xFF9 - 0xFF0 */

    CY_PRA_STATUS_INVALID_PARAM_ECO                 = CY_PRA_ID | CY_PDL_STATUS_ERROR | 0xFEFU,     /**< Returns Error while validating the ECO parameters */
    CY_PRA_STATUS_INVALID_PARAM_EXTCLK              = CY_PRA_ID | CY_PDL_STATUS_ERROR | 0xFEEU,     /**< Returns Error while validating the CLK_EXT parameters */
    CY_PRA_STATUS_INVALID_PARAM_ALTHF               = CY_PRA_ID | CY_PDL_STATUS_ERROR | 0xFEDU,     /**< Returns Error while validating the CLK_ALTHF parameters */
    CY_PRA_STATUS_INVALID_PARAM_ILO                 = CY_PRA_ID | CY_PDL_STATUS_ERROR | 0xFECU,     /**< Returns Error while validating the CLK_ILO parameters */
    CY_PRA_STATUS_INVALID_PARAM_PILO                = CY_PRA_ID | CY_PDL_STATUS_ERROR | 0xFEBU,     /**< Returns Error while validating the CLK_PILO parameters */
    CY_PRA_STATUS_INVALID_PARAM_WCO                 = CY_PRA_ID | CY_PDL_STATUS_ERROR | 0xFEAU,     /**< Returns Error while validating the CLK_WCO parameters */
    CY_PRA_STATUS_INVALID_ECO_PROVISION             = CY_PRA_ID | CY_PDL_STATUS_ERROR | 0xFE9U,     /**< Returns Error while validating the provisioned CLK_ECO policy */
    CY_PRA_STATUS_INVALID_EXTCLK_PROVISION          = CY_PRA_ID | CY_PDL_STATUS_ERROR | 0xFE8U,     /**< Returns Error while validating the provisioned CLK_EXT policy */
    CY_PRA_STATUS_INVALID_WCO_PROVISION             = CY_PRA_ID | CY_PDL_STATUS_ERROR | 0xFE7U,     /**< Returns Error while validating the provisioned CLK_WCO policy */
    /* Reserve for other source clocks 0xFE6 - 0xFE0 */

    CY_PRA_STATUS_INVALID_PARAM_PATHMUX0            = CY_PRA_ID | CY_PDL_STATUS_ERROR | 0xFDFU,     /**< Returns Error while validating PATH_MUX0 */
    CY_PRA_STATUS_INVALID_PARAM_PATHMUX1            = CY_PRA_ID | CY_PDL_STATUS_ERROR | 0xFDEU,     /**< Returns Error while validating PATH_MUX1 */
    CY_PRA_STATUS_INVALID_PARAM_PATHMUX2            = CY_PRA_ID | CY_PDL_STATUS_ERROR | 0xFDDU,     /**< Returns Error while validating PATH_MUX2 */
    CY_PRA_STATUS_INVALID_PARAM_PATHMUX3            = CY_PRA_ID | CY_PDL_STATUS_ERROR | 0xFDCU,     /**< Returns Error while validating PATH_MUX3 */
    CY_PRA_STATUS_INVALID_PARAM_PATHMUX4            = CY_PRA_ID | CY_PDL_STATUS_ERROR | 0xFDBU,     /**< Returns Error while validating PATH_MUX4 */
    CY_PRA_STATUS_INVALID_PARAM_PATHMUX5            = CY_PRA_ID | CY_PDL_STATUS_ERROR | 0xFDAU,     /**< Returns Error while validating PATH_MUX5 */
    /* Reserve for other path-mux 0xFD9 - 0xFD0 */

    CY_PRA_STATUS_INVALID_PARAM_FLL0                = CY_PRA_ID | CY_PDL_STATUS_ERROR | 0xFCFU,     /**< Returns Error while validating FLL */
    /* Reserve for other FLLs 0xFCE - 0xFC0 */

    CY_PRA_STATUS_INVALID_PARAM_PLL0                = CY_PRA_ID | CY_PDL_STATUS_ERROR | 0xFBFU,     /**< Returns Error while validating PLL0 */
    CY_PRA_STATUS_INVALID_PARAM_PLL1                = CY_PRA_ID | CY_PDL_STATUS_ERROR | 0xFBEU,     /**< Returns Error while validating PLL1 */
    CY_PRA_STATUS_INVALID_PARAM_PLL_NUM             = CY_PRA_ID | CY_PDL_STATUS_ERROR | 0xFBDU,     /**< Returns Error for the invalid PLL number */
    /* Reserve for other PLLs 0xFBC - 0xFB0 */

    CY_PRA_STATUS_INVALID_PARAM_CLKLF               = CY_PRA_ID | CY_PDL_STATUS_ERROR | 0xFAFU,     /**< Returns Error while validating CLK_LF */
    /* Reserve for other clocks 0xFAE - 0xFA0 */

    CY_PRA_STATUS_INVALID_PARAM_CLKHF0              = CY_PRA_ID | CY_PDL_STATUS_ERROR | 0xF9FU,     /**< Returns Error while validating CLK_HF0 */
    CY_PRA_STATUS_INVALID_PARAM_CLKHF1              = CY_PRA_ID | CY_PDL_STATUS_ERROR | 0xF9EU,     /**< Returns Error while validating CLK_HF1 */
    CY_PRA_STATUS_INVALID_PARAM_CLKHF2              = CY_PRA_ID | CY_PDL_STATUS_ERROR | 0xF9DU,     /**< Returns Error while validating CLK_HF2 */
    CY_PRA_STATUS_INVALID_PARAM_CLKHF3              = CY_PRA_ID | CY_PDL_STATUS_ERROR | 0xF9CU,     /**< Returns Error while validating CLK_HF3 */
    CY_PRA_STATUS_INVALID_PARAM_CLKHF4              = CY_PRA_ID | CY_PDL_STATUS_ERROR | 0xF9BU,     /**< Returns Error while validating CLK_HF4 */
    CY_PRA_STATUS_INVALID_PARAM_CLKHF5              = CY_PRA_ID | CY_PDL_STATUS_ERROR | 0xF9AU,     /**< Returns Error while validating CLK_HF5 */
    /* Reserve for other HF clocks 0xF99 - 0xF90 */

    CY_PRA_STATUS_INVALID_PARAM_CLKPUMP             = CY_PRA_ID | CY_PDL_STATUS_ERROR | 0xF8FU,     /**< Returns Error while validating CLK_PUMP */
    CY_PRA_STATUS_INVALID_PARAM_CLKBAK              = CY_PRA_ID | CY_PDL_STATUS_ERROR | 0xF8EU,     /**< Returns Error while validating CLK_BAK */
    CY_PRA_STATUS_INVALID_PARAM_CLKFAST             = CY_PRA_ID | CY_PDL_STATUS_ERROR | 0xF8DU,     /**< Returns Error while validating CLK_FAST */
    CY_PRA_STATUS_INVALID_PARAM_CLKPERI             = CY_PRA_ID | CY_PDL_STATUS_ERROR | 0xF8CU,     /**< Returns Error while validating CLK_PERI */
    CY_PRA_STATUS_INVALID_PARAM_CLKSLOW             = CY_PRA_ID | CY_PDL_STATUS_ERROR | 0xF8BU,     /**< Returns Error while validating CLK_SLOW */
    CY_PRA_STATUS_INVALID_PARAM_SYSTICK             = CY_PRA_ID | CY_PDL_STATUS_ERROR | 0xF8AU,     /**< Returns Error while validating CLK_ALT_SYS_TICK */
    CY_PRA_STATUS_INVALID_PARAM_CLKTIMER            = CY_PRA_ID | CY_PDL_STATUS_ERROR | 0xF89U,     /**< Returns Error while validating CLK_TIMER */
    /* Reserve for other HF clocks 0xF88 - 0xF70 */

    CY_PRA_STATUS_ERROR_PROCESSING_PWR              = CY_PRA_ID | CY_PDL_STATUS_ERROR | 0xF6FU,     /**< Returns Error while initializing power */
    /* Reserve 0xF6E - 0xF60*/

    CY_PRA_STATUS_ERROR_PROCESSING_ECO              = CY_PRA_ID | CY_PDL_STATUS_ERROR | 0xF5FU,     /**< Returns Error while initializing ECO */
    CY_PRA_STATUS_ERROR_PROCESSING_EXTCLK           = CY_PRA_ID | CY_PDL_STATUS_ERROR | 0xF5EU,     /**< Returns Error while enabling CLK_EXT */
    CY_PRA_STATUS_ERROR_PROCESSING_ALTHF            = CY_PRA_ID | CY_PDL_STATUS_ERROR | 0xF5DU,     /**< Returns Error while enabling CLK_ALTHF */
    CY_PRA_STATUS_ERROR_PROCESSING_ILO              = CY_PRA_ID | CY_PDL_STATUS_ERROR | 0xF5CU,     /**< Returns Error while enabling/disabling CLK_ILO */
    CY_PRA_STATUS_ERROR_PROCESSING_PILO             = CY_PRA_ID | CY_PDL_STATUS_ERROR | 0xF5BU,     /**< Returns Error while enabling/disabling CLK_ALTHF */
    CY_PRA_STATUS_ERROR_PROCESSING_WCO              = CY_PRA_ID | CY_PDL_STATUS_ERROR | 0xF5AU,     /**< Returns Error while enabling/disabling CLK_WCO */
    CY_PRA_STATUS_ERROR_PROCESSING_ECO_ENABLED      = CY_PRA_ID | CY_PDL_STATUS_ERROR | 0xF59U,     /**< Returns Error while enabling CLK_ECO */
    CY_PRA_STATUS_ERROR_PROCESSING_ECO_PROVISION    = CY_PRA_ID | CY_PDL_STATUS_ERROR | 0xF58U,     /**< Returns Error if failed to process the provisioned CLK_ECO policy  */
    CY_PRA_STATUS_ERROR_PROCESSING_EXTCLK_PROVISION = CY_PRA_ID | CY_PDL_STATUS_ERROR | 0xF57U,     /**< Returns Error if failed to process the provisioned CLK_EXT policy  */
    CY_PRA_STATUS_ERROR_PROCESSING_WCO_PROVISION    = CY_PRA_ID | CY_PDL_STATUS_ERROR | 0xF56U,     /**< Returns Error if failed to process the provisioned CLK_WCO policy  */
    /* Reserve for other source clocks 0xF55 - 0xF50 */

    CY_PRA_STATUS_ERROR_PROCESSING_PATHMUX0         = CY_PRA_ID | CY_PDL_STATUS_ERROR | 0xF4FU,     /**< Returns Error while setting PATH_MUX0 */
    CY_PRA_STATUS_ERROR_PROCESSING_PATHMUX1         = CY_PRA_ID | CY_PDL_STATUS_ERROR | 0xF4EU,     /**< Returns Error while setting PATH_MUX1 */
    CY_PRA_STATUS_ERROR_PROCESSING_PATHMUX2         = CY_PRA_ID | CY_PDL_STATUS_ERROR | 0xF4DU,     /**< Returns Error while setting PATH_MUX2 */
    CY_PRA_STATUS_ERROR_PROCESSING_PATHMUX3         = CY_PRA_ID | CY_PDL_STATUS_ERROR | 0xF4CU,     /**< Returns Error while setting PATH_MUX3 */
    CY_PRA_STATUS_ERROR_PROCESSING_PATHMUX4         = CY_PRA_ID | CY_PDL_STATUS_ERROR | 0xF4BU,     /**< Returns Error while setting PATH_MUX4 */
    CY_PRA_STATUS_ERROR_PROCESSING_PATHMUX5         = CY_PRA_ID | CY_PDL_STATUS_ERROR | 0xF4AU,     /**< Returns Error while setting PATH_MUX5 */
    /* Reserve for other path-mux 0xF49 - 0xF40 */

    CY_PRA_STATUS_ERROR_PROCESSING_FLL0             = CY_PRA_ID | CY_PDL_STATUS_ERROR | 0xF3FU,     /**< Returns Error while enabling/disabling FLL */
    CY_PRA_STATUS_ERROR_PROCESSING_FLL0_ENABLED     = CY_PRA_ID | CY_PDL_STATUS_ERROR | 0xF3EU,     /**< Returns Error while trying to enable an already enabled FLL */
    /* Reserve for other FLLs 0xF3D - 0xF30 */

    CY_PRA_STATUS_ERROR_PROCESSING_PLL0             = CY_PRA_ID | CY_PDL_STATUS_ERROR | 0xF2FU,     /**< Returns Error while enabling/disabling PLL0 */
    CY_PRA_STATUS_ERROR_PROCESSING_PLL1             = CY_PRA_ID | CY_PDL_STATUS_ERROR | 0xF2EU,     /**< Returns Error while enabling/disabling PLL1 */
    CY_PRA_STATUS_ERROR_PROCESSING_PLL_ENABLED      = CY_PRA_ID | CY_PDL_STATUS_ERROR | 0xF2DU,     /**< Returns Error while trying to enable an already enabled PLL */
    /* Reserve for other PLLs 0xF2C - 0xF20 */

    CY_PRA_STATUS_ERROR_PROCESSING_CLKLF            = CY_PRA_ID | CY_PDL_STATUS_ERROR | 0xF1FU,     /**< Returns Error while enabling/disabling CLK_LF */
    /* Reserve for other clocks 0xF1E - 0xF10 */

    CY_PRA_STATUS_ERROR_PROCESSING_CLKHF0           = CY_PRA_ID | CY_PDL_STATUS_ERROR | 0xF0FU,     /**< Returns Error while enabling/disabling CLK_HF0 */
    CY_PRA_STATUS_ERROR_PROCESSING_CLKHF1           = CY_PRA_ID | CY_PDL_STATUS_ERROR | 0xF0EU,     /**< Returns Error while enabling/disabling CLK_HF1 */
    CY_PRA_STATUS_ERROR_PROCESSING_CLKHF2           = CY_PRA_ID | CY_PDL_STATUS_ERROR | 0xF0DU,     /**< Returns Error while enabling/disabling CLK_HF2 */
    CY_PRA_STATUS_ERROR_PROCESSING_CLKHF3           = CY_PRA_ID | CY_PDL_STATUS_ERROR | 0xF0CU,     /**< Returns Error while enabling/disabling CLK_HF3 */
    CY_PRA_STATUS_ERROR_PROCESSING_CLKHF4           = CY_PRA_ID | CY_PDL_STATUS_ERROR | 0xF0BU,     /**< Returns Error while enabling/disabling CLK_HF4 */
    CY_PRA_STATUS_ERROR_PROCESSING_CLKHF5           = CY_PRA_ID | CY_PDL_STATUS_ERROR | 0xF0AU,     /**< Returns Error while enabling/disabling CLK_HF5 */

    /* Reserve for other HF clocks 0xF09 - 0xF00 */
    CY_PRA_STATUS_ERROR_PROCESSING_CLKPUMP          = CY_PRA_ID | CY_PDL_STATUS_ERROR | 0xEFFU,     /**< Returns Error while enabling/disabling CLK_PUMP */
    CY_PRA_STATUS_ERROR_PROCESSING_CLKBAK           = CY_PRA_ID | CY_PDL_STATUS_ERROR | 0xEFEU,     /**< Returns Error while enabling/disabling CLK_BAK */
    CY_PRA_STATUS_ERROR_PROCESSING_CLKFAST          = CY_PRA_ID | CY_PDL_STATUS_ERROR | 0xEFDU,     /**< Returns Error while enabling/disabling CLK_FAST */
    CY_PRA_STATUS_ERROR_PROCESSING_CLKPERI          = CY_PRA_ID | CY_PDL_STATUS_ERROR | 0xEFCU,     /**< Returns Error while enabling/disabling CLK_PERI */
    CY_PRA_STATUS_ERROR_PROCESSING_CLKSLOW          = CY_PRA_ID | CY_PDL_STATUS_ERROR | 0xEFBU,     /**< Returns Error while enabling/disabling CLK_SLOW */
    CY_PRA_STATUS_ERROR_PROCESSING_SYSTICK          = CY_PRA_ID | CY_PDL_STATUS_ERROR | 0xEFAU,     /**< Returns Error while enabling/disabling CLK_ALT_SYS_TICK */
    CY_PRA_STATUS_ERROR_PROCESSING_CLKTIMER         = CY_PRA_ID | CY_PDL_STATUS_ERROR | 0xEF9U,     /**< Returns Error while enabling/disabling CLK_TIMER */
} cy_en_pra_status_t;

/** GPIO PIN protection type */
typedef enum
{
    CY_PRA_PIN_SECURE,                      /**< Is a secure PIN. Can't be updated from CM4 application through register level PRA policy. This PIN can only be updated through service-level policy */
    CY_PRA_PIN_SECURE_UNCONSTRAINED,        /**< Is a secure PIN. Can be updated from CM4 application through register level PRA policy */
    CY_PRA_PIN_SECURE_NONE,                 /**< Not a secure PIN */
} cy_en_pra_pin_prot_type_t;
/** \} group_pra_enums */


/*******************************************************************************
 * Data Structures
 ******************************************************************************/

/** \cond INTERNAL */
/** PRA register access */
typedef struct
{
    volatile uint32_t * addr;           /**< A protected register address */
    uint32_t writeMask;                 /**< The write mask. Zero grants access, one - no access. */
} cy_stc_pra_reg_policy_t;

/** Message used for communication */
typedef struct
{
    uint16_t praCommand;            /**< The message type. Refer to \ref group_pra_macros. */
    uint16_t praIndex;              /**< The register or function index. */
    cy_en_pra_status_t praStatus;   /**< The status */
    uint32_t praData1;              /**< The first data word. The usage depends on \ref group_pra_macros. */
    uint32_t praData2;              /**< The second data word. The usage depends on \ref group_pra_macros. */
} cy_stc_pra_msg_t;

/* External clock pin structure */
typedef struct
{
    GPIO_PRT_Type *port;            /**< Port Number */
    uint32_t pinNum;                /**< Bit fields for each secure pin number */
    uint16_t index;                 /**< GPIO Port base address index */
    uint16_t hsiomIndex;            /**< HSIOM Port base address index */
} cy_stc_pra_extclk_pin_t;

#if defined(CY_DEVICE_PSOC6ABLE2)
/* External clock adjacent HSIOM index structure */
typedef struct
{
    GPIO_PRT_Type *port;            /**< Port Number */
    uint16_t hsiomIndex;            /**< HSIOM Port base address index */
} cy_stc_pra_extclk_hsiom_t;

#endif /* defined(CY_DEVICE_PSOC6ABLE2) */

/** \endcond */

#if (CY_CPU_CORTEX_M0P) || defined (CY_DOXYGEN)
/** \cond INTERNAL */
/* contains power mode configuration of a macro */
typedef struct
{
    uint32_t sramMacros;            /**< Bit fields for each SRAM macro number */
    uint32_t sramPwrMode;           /**< Bit fields for SRAM power modes. bit 0->OFF, bit 1->RETAIN bit 2->ON */
} cy_pra_sram_pwr_macro_config_t;

/* contains all macro configurations of a sram */
typedef struct
{
    cy_pra_sram_pwr_macro_config_t macroConfigs[CY_PRA_SRAM_MACRO_MAX_NR];       /**< SRAM macro configurations */
    uint32_t macroConfigCount;                                                   /**< Number of macros present in in policy file */
} cy_pra_sram_pwr_mode_config_t;

/** \endcond */

/** \cond INTERNAL */
extern cy_pra_sram_pwr_mode_config_t sramPwrModeConfig[CY_PRA_SRAM_MAX_NR];
/** \endcond */

#endif /* (CY_CPU_CORTEX_M0P) || defined (CY_DOXYGEN) */

/** \cond INTERNAL */
/* Public for testing purposes */
extern cy_stc_pra_reg_policy_t regIndexToAddr[CY_PRA_REG_INDEX_COUNT];

extern cy_stc_pra_extclk_pin_t secExtclkPinList[CY_PRA_EXTCLK_PIN_NR];
#if defined(CY_DEVICE_PSOC6ABLE2)
extern cy_stc_pra_extclk_hsiom_t secExtClkAdjHsiomList[CY_PRA_EXTCLK_PIN_NR];
#endif /* defined(CY_DEVICE_PSOC6ABLE2) */
/** \endcond */


/*******************************************************************************
*        Function Prototypes
*******************************************************************************/

/**
* \addtogroup group_pra_functions
* \{
*/
void Cy_PRA_Init(void);

/** \cond INTERNAL */
#if (CY_CPU_CORTEX_M0P) || defined (CY_DOXYGEN)
    void Cy_PRA_UpdateExtClockRegIndex(void);
    void Cy_PRA_CloseSrssMain2(void);
    void Cy_PRA_OpenSrssMain2(void);
#endif /* (CY_CPU_CORTEX_M0P) || defined (CY_DOXYGEN) */
/** \endcond */

cy_en_pra_status_t Cy_PRA_SendCmd(uint16_t cmd, uint16_t regIndex, uint32_t clearMask, uint32_t setMask);

#if (CY_CPU_CORTEX_M4) || defined (CY_DOXYGEN)

    cy_en_pra_pin_prot_type_t Cy_PRA_GetPinProtType(GPIO_PRT_Type *base, uint32_t pinNum);

    bool Cy_PRA_IsPortSecure(GPIO_PRT_Type *base);

    uint16_t Cy_PRA_GetPortRegIndex(GPIO_PRT_Type *base, uint16_t subIndex);

    uint16_t Cy_PRA_GetHsiomRegIndex(GPIO_PRT_Type *base, uint16_t subIndex);

#if defined(CY_DEVICE_PSOC6ABLE2)
    bool Cy_PRA_IsHsiomSecure(GPIO_PRT_Type *base);
    uint16_t Cy_PRA_GetAdjHsiomRegIndex(GPIO_PRT_Type *base, uint16_t subIndex);
#endif /* defined(CY_DEVICE_PSOC6ABLE2) */

    /** \} group_pra_functions */

    /**
    * \addtogroup group_pra_macros
    * \{
    */

/*******************************************************************************
* Macro Name: CY_PRA_REG32_CLR_SET(regIndex, field, value)
****************************************************************************//**
*
* Provides get-clear-modify-write operations with a name field and value and
* writes a resulting value to the 32-bit register.
*
* \note An attempt to access not-supported registers (not secure and
* not listed in the TRM) results in an error. The list of the registers that
* can be accessed by the PRA driver directly is defined in the cy_pra.h file
* with the CY_PRA_INDX_ prefix.
*
* \param regIndex The register address index.
*
* \param field The field to be updated.
*
* \param value The value to write.
*
*******************************************************************************/
    #define CY_PRA_REG32_CLR_SET(regIndex, field, value)  \
        (void)Cy_PRA_SendCmd(CY_PRA_MSG_TYPE_REG32_CLR_SET, (regIndex), ((uint32_t)(~(field ## _Msk))), (_VAL2FLD(field, (value))))


/*******************************************************************************
* Macro Name: CY_PRA_REG32_SET(regIndex, value)
****************************************************************************//**
*
* Writes the 32-bit value to the specified register.
*
* \note An attempt to access not-supported registers (not secure and
* not listed in the TRM) results in an error. The list of the registers that
* can be accessed by the PRA driver directly is defined in the cy_pra.h file
* with the CY_PRA_INDX_ prefix.
*
* \param regIndex The register address index.
*
* \param value The value to write.
*
*******************************************************************************/
    #define CY_PRA_REG32_SET(regIndex, value)  \
        (void)Cy_PRA_SendCmd(CY_PRA_MSG_TYPE_REG32_SET, (regIndex), (value), 0UL)


/*******************************************************************************
* Macro Name: CY_PRA_REG32_GET(regIndex)
****************************************************************************//**
*
* Reads the 32-bit value from the specified register.
*
* \note An attempt to access not-supported registers (not secure and
* not listed in the TRM) results in an error. The list of the registers that
* can be accessed by the PRA driver directly is defined in the cy_pra.h file
* with the CY_PRA_INDX_ prefix.
*
* \param regIndex The register address index.
*
* \return The read value.
*
*******************************************************************************/
    #define CY_PRA_REG32_GET(regIndex)  \
        (uint32_t) Cy_PRA_SendCmd(CY_PRA_MSG_TYPE_REG32_GET, (regIndex), 0UL, 0UL)


/*******************************************************************************
* Macro Name: CY_PRA_CM0_WAKEUP()
****************************************************************************//**
*
* The request to wake up the Cortex-M0+ core.
*
*******************************************************************************/
    #define CY_PRA_CM0_WAKEUP()  \
        (void)Cy_PRA_SendCmd(CY_PRA_MSG_TYPE_CM0_WAKEUP, (uint16_t) 0U, 0UL, 0UL)

#endif /* (CY_CPU_CORTEX_M4) */

/*******************************************************************************
* Macro Name: CY_PRA_FUNCTION_CALL_RETURN_PARAM(msgType, funcIndex, param)
****************************************************************************//**
*
* Calls the specified function with the provided parameter and returns the
* execution status.
*
* \param msgType The function type.
*
* \param funcIndex The function reference.
*
* \param param The pointer to the function parameter.
*
* \return The function execution status.
*
*******************************************************************************/
    #define CY_PRA_FUNCTION_CALL_RETURN_PARAM(msgType, funcIndex, param)  \
        Cy_PRA_SendCmd((msgType), (funcIndex), (uint32_t)(param), 0UL)


/*******************************************************************************
* Macro Name: CY_PRA_FUNCTION_CALL_RETURN_VOID(msgType, funcIndex)
****************************************************************************//**
*
* Calls the specified function without a parameter and returns the
* execution status.
*
* \param msgType The function type.
*
* \param funcIndex The function reference.
*
* \return The function execution status.
*
*******************************************************************************/
    #define CY_PRA_FUNCTION_CALL_RETURN_VOID(msgType, funcIndex)  \
        Cy_PRA_SendCmd((msgType), (funcIndex), 0UL, 0UL)


/*******************************************************************************
* Macro Name: CY_PRA_FUNCTION_CALL_VOID_PARAM(msgType, funcIndex, param)
****************************************************************************//**
*
* Calls the specified function with the provided parameter and returns void.
*
* \param msgType The function type.
*
* \param funcIndex The function reference.
*
* \param param The pointer to the function parameter.
*
*******************************************************************************/
    #define CY_PRA_FUNCTION_CALL_VOID_PARAM(msgType, funcIndex, param)  \
        (void)Cy_PRA_SendCmd((msgType), (funcIndex), (uint32_t)(param), 0UL)


/*******************************************************************************
* Macro Name: CY_PRA_FUNCTION_CALL_VOID_VOID(msgType, funcIndex)
****************************************************************************//**
*
* Calls the specified function without a parameter and returns void.
*
* \param msgType The function type.
*
* \param funcIndex The function reference.
*
*******************************************************************************/
    #define CY_PRA_FUNCTION_CALL_VOID_VOID(msgType, funcIndex)  \
        (void)Cy_PRA_SendCmd((msgType), (funcIndex), 0UL, 0UL)


#if (CY_CPU_CORTEX_M4) || defined (CY_DOXYGEN)

/*******************************************************************************
* Macro Name: CY_PRA_GET_PIN_PROT_TYPE(base, pinNum)
****************************************************************************//**
*
* Compares the PORT and PIN number with secure PIN list and returns PIN
* protection type.
*
* \param base GPIO Port address
*
* \param pinNum GPIO PIN number
*
* \return The categories of PIN.
*
*******************************************************************************/
    #define CY_PRA_GET_PIN_PROT_TYPE(base, pinNum)  \
        Cy_PRA_GetPinProtType(base, pinNum)

/*******************************************************************************
* Macro Name: CY_PRA_IS_PORT_SECURE(base)
****************************************************************************//**
*
* Compares the PORT with secure PIN list and returns PORT protection status.
*
* \param base GPIO Port address
*
* \return true if port is secure otherwise false.
*
*******************************************************************************/
    #define CY_PRA_IS_PORT_SECURE(base)  \
        Cy_PRA_IsPortSecure(base)

#if defined(CY_DEVICE_PSOC6ABLE2)
/*******************************************************************************
* Macro Name: CY_PRA_IS_HSIOM_SECURE(base)
****************************************************************************//**
*
* Compares the PORT with secure adjacent HSIOM list and returns protection status.
*
* \param base GPIO Port address
*
* \return true if HSIOM is secure otherwise false.
*
*******************************************************************************/
    #define CY_PRA_IS_HSIOM_SECURE(base)  \
        Cy_PRA_IsHsiomSecure(base)

#endif /* defined(CY_DEVICE_PSOC6ABLE2) */

/*******************************************************************************
* Macro Name: CY_PRA_GET_PORT_INDEX(base, pinNum, subIndex)
****************************************************************************//**
*
* Compares the PORT and PIN number with secure PIN list and returns PORT index
*
* \param base GPIO Port address
*
* \param subIndex register index of GPIO PORT
*
* \return PRA GPIO PORT register index
*
*******************************************************************************/
    #define CY_PRA_GET_PORT_REG_INDEX(base, subIndex)  \
        Cy_PRA_GetPortRegIndex(base, subIndex)

/*******************************************************************************
* Macro Name: CY_PRA_GET_HSIOM_REG_INDEX(base, subIndex)
****************************************************************************//**
*
* Compares the PORT with secure PIN list and returns HSIOM port index
*
* \param base GPIO Port address
*
* \param subIndex register index of HSIOM PORT
*
* \return PRA HSIOM PORT register index
*
*******************************************************************************/
    #define CY_PRA_GET_HSIOM_REG_INDEX(base, subIndex)  \
        Cy_PRA_GetHsiomRegIndex(base, subIndex)

#if defined(CY_DEVICE_PSOC6ABLE2)
/*******************************************************************************
* Macro Name: CY_PRA_GET_ADJHSIOM_REG_INDEX(base, subIndex)
****************************************************************************//**
*
* Compares the PORT with adjacent HSIOM list and returns HSIOM port index
*
* \param base GPIO Port address
*
* \param subIndex register index of HSIOM PORT
*
* \return PRA HSIOM PORT register index
*
*******************************************************************************/
    #define CY_PRA_GET_ADJHSIOM_REG_INDEX(base, subIndex)  \
        Cy_PRA_GetAdjHsiomRegIndex(base, subIndex)
#endif /* defined(CY_DEVICE_PSOC6ABLE2) */

/** \} group_pra_macros */

#endif /* (CY_CPU_CORTEX_M4) */

#ifdef __cplusplus
}
#endif

#endif /* (CY_DEVICE_SECURE) */

#endif /* defined (CY_IP_MXS40SRSS) */

#endif /* #if !defined(CY_PRA_H) */

/** \} group_pra */

/* [] END OF FILE */
