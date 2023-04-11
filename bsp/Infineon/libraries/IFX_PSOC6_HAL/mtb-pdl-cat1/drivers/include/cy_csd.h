/***************************************************************************//**
* \file cy_csd.h
* \version 1.20.1
*
* The header file of the CSD driver.
*
********************************************************************************
* \copyright
* Copyright 2018-2022 Cypress Semiconductor Corporation
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
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either expressed or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

/**
* \addtogroup group_csd
*/

/**
********************************************************************************
* \addtogroup group_csd
********************************************************************************
* \{
*
* The CSD HW block enables multiple sensing capabilities on PSoC&trade; devices,
* including self-cap and mutual-cap capacitive touch sensing solutions,
* a 10-bit ADC, IDAC, and Comparator.
*
* The CAPSENSE&trade; solution includes:
* * The CAPSENSE&trade; Configurator tool, which is a configuration wizard to create
*   and configure CAPSENSE&trade; widgets. It can be launched in ModusToolbox&trade;
*   from the CSD personality as well as in standalone mode.
*   It contains separate documentation on how to create and
*   configure widgets, parameters, and algorithm descriptions.
* * An API to control the design from the application program. This documentation
*   describes the API with code snippets about how to use them.
* * The CAPSENSE&trade; Tuner tool for real-time tuning, testing, and debugging,
*   for easy and smooth design of human interfaces on customer products.
*   The Tuner tool communicates with a device through a HW bridge and
*   communication drivers (EzI2C, UART, etc.) and allows monitoring of
*   widget statuses, sensor signals, detected touch positions, gestures, etc.
* The application program does not need to interact with the CSD driver
* and/or other drivers such as GPIO or SysClk directly. All of that is
* configured and managed by middleware.
*
* \image html capsense_solution.png "CAPSENSE&trade; Solution" width=800px
* \image latex capsense_solution.png
*
* This section describes only the CSD driver. Refer to the corresponding sections
* for documentation of middleware supported by the CSD HW block.
*
* The CSD driver is a low-level peripheral driver that provides an interface to
* a complex mixed signal of the CSD HW block.
*
* The CSD driver alone does not provide system-level functions. Instead, it is
* used by upper-level middleware to configure the CSD HW block required by
* an application.
*
* The CSD HW block can support only one function at a time. To allow seamless
* time-multiplex implementation of functionality and to avoid conflicting access
* to hardware from the upper level, the CSD driver also implements a lock
* semaphore mechanism.
*
* The CSD driver supports re-entrance. If a device contains several
* CSD HW blocks, the same CSD driver is used to configure any HW block. For
* that, each function of the CSD driver contains a base address to define
* the CSD HW block to which the CSD driver communicates.
*
* For dual-core devices, the CSD driver functions can be called either by the
* CM0+ or CM4 cores. In case both cores need access to the CSD Driver, you
* should properly manage the memory access.
*
* There is no restriction on the CSD Driver usage in RTOS.
*
********************************************************************************
* \section group_csd_config_usage Usage
********************************************************************************
*
* The CSD driver is simple wrapper driver specifically designed to be used by higher
* level middleware. Hence, is highly not recommended to use CSD driver
* directly in the application program. To incorporate CSD HW block
* functionality in the application program, an associated middleware
* should be used.
*
* The CSD Driver can be used to implement a custom sensing solution. In such a case,
* the application program must acquire and lock the CSD HW block prior to
* accessing it.
*
* Setting up and using the CSD driver can be summed up in these four stages:
* * Define configuration in the config structure.
* * Allocate context structure variable for the driver.
* * Capture the CSD HW block.
* * Execute the action required to perform any kind of conversion.
*
* The following code snippet demonstrates how to capture the CSD HW block for
* custom implementation:
*
* \snippet csd/snippet/main.c snippet_Cy_CSD_Conversion
*
* The entire solution, either CAPSENSE&trade; or CSDADC, in addition to
* the CSD HW block, incorporates the following instances:
*
* * \ref group_csd_config_clocks
* * \ref group_csd_config_refgen
* * \ref group_csd_config_interrupts
* * \ref group_csd_config_pin
*
* The CSD driver does not configure those blocks and they should be managed by
* an upper level. When using CAPSENSE&trade; or CSDADC, those blocks are managed by
* middleware.
*
********************************************************************************
* \subsection group_csd_config_clocks Clocks
********************************************************************************
*
* The CSD HW block requires a peripheral clock (clk_peri) input. It can be
* assigned using two methods:
* * Using the Device Configurator (Peripheral-Clocks tab ).
* * Using the SysClk (System Clock) driver. Refer to \ref group_sysclk driver
*   section for more details.
* If middleware is used, the clock is managed by middleware.
*
********************************************************************************
* \subsection group_csd_config_pin GPIO Pins
********************************************************************************
*
* Any analog-capable GPIO pin that can be connected to an analog multiplexed bus
* (AMUXBUS) can be connected to the CSD HW block as an input.
*
* GPIO input can be assigned to the CSD HW block using the following methods:
* * Using the Device Configurator (Pins tab).
* * Using the GPIO (General Purpose Input Output) driver. Refer to \ref group_gpio
*   driver section.
*
* If middleware is used, pin configuration is managed by middleware. When
* using the CSD driver for custom implementation, the application program must
* manage pin connections.
*
* Each AMUXBUS can be split into multiple segments. Ensure the CSD HW block
* and a GPIO belong to the same bus segment or join the segments to establish
* connection of the GPIO to the CSD HW block.
*
* For more information about pin configuration, refer to the \ref group_gpio
* driver.
*
********************************************************************************
* \subsection group_csd_config_refgen Reference Voltage Input
********************************************************************************
*
* The CSD HW block requires a reference voltage input to generate programmable
* reference voltage within the CSD HW block. There are two on-chip reference
* sources:
* * VREF
* * AREF
*
* For more information about specification and startup of reference voltage
* sources, refer to the \ref group_sysanalog driver prior to making the
* selection.
*
********************************************************************************
* \subsection group_csd_config_interrupts Interrupts
********************************************************************************
*
* The CSD HW block has one interrupt that can be assigned to either the
* Cortex M4 or Cortex M0+ core. The CSD HW block can generate interrupts
* on the following events:
*
* * End of sample: when scanning of a single sensor is complete.
* * End of initialization: when initialization of an analog circuit is complete.
* * End of measurement: when conversion of an CSDADC channel is complete.
*
* Additionally, the CSD interrupt can wake the device from the Sleep power mode.
* The CSD HW block is powered down in the Deep Sleep or Hibernate power modes.
* So, it cannot be used as a wake-up source in these power modes.
*
* If a CAPSENSE&trade; or CSDADC middleware is used, the interrupt service routine is managed
* by middleware. When using the CSD driver for custom implementation or other
* middleware, the application program must manage the interrupt service routine.
*
* Implement an interrupt routine and assign it to the CSD interrupt. Use the
* pre-defined enumeration as the interrupt source of the CSD HW block.
* The CSD interrupt to the NVIC is raised any time the intersection
* (logic AND) of the interrupt flags and the corresponding interrupt
* masks are non-zero. The peripheral interrupt status register should be
* read in the ISR to detect which condition generated the interrupt.
* The appropriate interrupt registers should be cleared so that
* subsequent interrupts can be handled.
*
* The following code snippet demonstrates how to implement a routine to handle
* the interrupt. The routine is called when a CSD interrupt is triggered.
*
* \snippet csd/snippet/main.c snippet_Cy_CSD_IntHandler
*
* The following code snippet demonstrates how to configure and enable
* the CSD interrupt:
*
* \snippet csd/snippet/main.c snippet_Cy_CSD_IntEnabling
*
* For more information, refer to the \ref group_sysint driver.
*
* Alternatively, instead of handling the interrupts, the
* \ref Cy_CSD_GetConversionStatus() function allows for firmware
* polling of the CSD block status.
*
********************************************************************************
* \section group_csd_config_power_modes Power Modes
********************************************************************************
*
* The CSD HW block can operate in Active and Sleep CPU power modes. It is also
* possible to switch between Low power and Ultra Low power system modes.
* In Deep Sleep and in Hibernate power modes, the CSD HW block is powered off.
* When the device wakes up from Deep Sleep, the CSD HW block resumes operation
* without the need for re-initialization. In the case of wake up from Hibernate power
* mode, the CSD HW block does not retain configuration and it requires
* re-initialization.
*
* \note
* 1. The CSD driver does not provide a callback function to facilitate the
*    low-power mode transitions. The responsibility belongs to an upper
*    level that uses the CSD HW block to ensure the CSD HW block is not
*    busy prior to a power mode transition.
* 2. A power mode transition is not recommended while the CSD HW block is busy.
*    The CSD HW block status must be checked using the Cy_CSD_GetStatus()
*    function prior to a power mode transition. Instead, use the same power mode
*    for active operation of the CSD HW block. This restriction is not
*    applicable to Sleep mode and the device can seamlessly enter and exit
*    Sleep mode while the CSD HW block is busy.
*
* \warning
* 1. Do not enter Deep Sleep power mode if the CSD HW block conversion is in
*    progress. Unexpected behavior may occur.
* 2. Analog start up time for the CSD HW block is 25 us. Initiate
*    any kind of conversion only after 25 us from Deep Sleep / Hibernate exit.
*
* Refer to the \ref group_syspm driver for more information about
* low-power mode transitions.
*
********************************************************************************
* \section group_csd_more_information More Information
********************************************************************************
*
* Important information about the CAPSENSE&trade; technology overview, appropriate
* Infineon device for the design, CAPSENSE&trade; system and sensor design guidelines,
* different interfaces and tuning guidelines necessary for a successful design
* of a CAPSENSE&trade; system is available in the Getting Started with CAPSENSE&trade;
* document and the product-specific CAPSENSE&trade; design guide. Infineon highly
* recommends starting with these documents. They can be found on the
* Infineon web site at www.infineon.com
*
* For more information, refer to the following documents:
*
* * CAPSENSE&trade; Overview:
*
*   * <a href="https://github.com/Infineon/capsense">
*     <b>CAPSENSE&trade; Middleware Library</b></a>
*
*   * <a href="https://infineon.github.io/capsense/capsense_api_reference_manual/html/index.html">
*     <b>CAPSENSE&trade; Middleware API Reference Guide</b></a>
*
*   * <a href="https://github.com/Infineon/csdadc">
*     <b>CSDADC Middleware Library</b></a>
*
*   * <a href="https://infineon.github.io/csdadc/csdadc_api_reference_manual/html/index.html">
*     <b>CSDADC Middleware API Reference Guide</b></a>
*
*   * <a href="https://github.com/Infineon/csdidac">
*     <b>CSDIDAC Middleware Library</b></a>
*
*   * <a href="https://infineon.github.io/csdidac/csdidac_api_reference_manual/html/index.html">
*     <b>CSDIDAC Middleware API Reference Guide</b></a>
*
*   * <a href="https://www.infineon.com/dgdl/Infineon-ModusToolbox_CAPSENSE_Configurator_5.0_User_Guide-UserManual-v01_00-EN.pdf?fileId=8ac78c8c8386267f0183a960b36a598c&utm_source=cypress&utm_medium=referral&utm_campaign=202110_globe_en_all_integration-files&redirId=180685">
*     <b>ModusToolbox&trade; CAPSENSE&trade; Configurator Tool Guide</b></a>
*
*   * <a href="https://www.infineon.com/dgdl/Infineon-ModusToolbox_CAPSENSE_Configurator_5.0_User_Guide-UserManual-v01_00-EN.pdf?fileId=8ac78c8c8386267f0183a960b36a598c&utm_source=cypress&utm_medium=referral&utm_campaign=202110_globe_en_all_integration-files&redirId=180685">
*     <b>ModusToolbox&trade; CAPSENSE&trade; Tuner Tool Guide</b></a>
*
*   * <a href="https://www.infineon.com/dgdl/Infineon-AN85951_PSoC_4_and_PSoC_6_MCU_CapSense_Design_Guide-ApplicationNotes-v27_00-EN.pdf?fileId=8ac78c8c7cdc391c017d0723535d4661">
*     <b>CAPSENSE&trade; Design Guide</b></a>
*
* * ModusToolbox&trade; Overview:
*
*   * <a href="https://www.infineon.com/cms/en/design-support/tools/sdk/modustoolbox-software">
*     <b>ModusToolbox&trade; Software Environment, Quick Start Guide, Documentation, and Videos</b></a>
*
*   * <a href="https://www.infineon.com/dgdl/Infineon-ModusToolbox_CAPSENSE_Configurator_5.0_User_Guide-UserManual-v01_00-EN.pdf?fileId=8ac78c8c8386267f0183a960b36a598c&utm_source=cypress&utm_medium=referral&utm_campaign=202110_globe_en_all_integration-files&redirId=180685">
*     <b>ModusToolbox&trade; Device Configurator Tool Guide</b></a>
*
* * General Information:
*
*   * \ref page_getting_started "Getting Started with the PDL"
*
*   * <a href="https://www.infineon.com/dgdl/Infineon-PSoC_6_MCU_PSoC_63_with_BLE_Datasheet_Programmable_System-on-Chip_(PSoC)-DataSheet-v16_00-EN.pdf?fileId=8ac78c8c7d0d8da4017d0ee4efe46c37">
*     <b>PSoC&trade; 63 with BLE Datasheet Programmable System-on-Chip</b></a>
*
*   * <a href="https://www.infineon.com/dgdl/Infineon-AN85951_PSoC_4_and_PSoC_6_MCU_CapSense_Design_Guide-ApplicationNotes-v28_00-EN.pdf?fileId=8ac78c8c7cdc391c017d0723535d4661">
*     <b>AN85951 PSoC&trade; 4 and PSoC&trade; 6 MCU CAPSENSE&trade; Design Guide</b></a>
*
*   * <a href="https://www.infineon.com/dgdl/Infineon-AN210781_Getting_Started_with_PSoC_6_MCU_with_Bluetooth_Low_Energy_(BLE)_Connectivity_on_PSoC_Creator-ApplicationNotes-v05_00-EN.pdf?fileId=8ac78c8c7cdc391c017d0d311f536528">
*     <b>AN210781 Getting Started with PSoC&trade; 6 MCU with Bluetooth Low Energy (BLE) Connectivity</b></a>
*
*   * <a href="https://www.infineon.com/cms/en/design-support/software/code-examples/psoc-6-code-examples-for-modustoolbox">
*     <b>PSoC&trade; 6 MCU Code Examples for ModusToolbox&trade; Software</b></a>
*
*   * <a href="https://github.com/Infineon"><b>Infineon Technologies GitHub</b></a>
*
*   * <a href="http://www.infineon.com"><b>Infineon Technologies</b></a>
*
********************************************************************************
* \section group_csd_changelog Changelog
********************************************************************************
* <table class="doxtable">
*   <tr><th>Version</th><th>Changes</th><th>Reason for Change</th></tr>
*   <tr>
*     <td>1.20.1</td>
*     <td>Documentation updates</td>
*     <td>Add trademark symbol</td>
*   </tr>
*   <tr>
*     <td>1.20</td>
*     <td>Added Cy_CSD_Capture() function</td>
*     <td>CAPSENSE&trade; memory consumption optimization</td>
*   </tr>
*   <tr>
*     <td>1.10.2</td>
*     <td>Documentation updates</td>
*     <td>Documented MISRA 2012 violations</td>
*   </tr>
*   <tr>
*     <td>1.10.1</td>
*     <td>Documentation updates</td>
*     <td>Update middleware references</td>
*   </tr>
*   <tr>
*     <td rowspan="2">1.10</td>
*     <td>The CSD driver sources are enclosed with the conditional compilation
*         to ensure successful compilation for incompatible devices
*     </td>
*     <td>Compilation for incompatible devices</td>
*   <tr>
*     <td>Changed the Cy_CSD_GetConversionStatus() function implementation</td>
*     <td>Fixed defect</td>
*   </tr>
*   </tr>
*   <tr>
*     <td>1.0.1</td>
*     <td>Documentation updates</td>
*     <td>Improve user's experience</td>
*   </tr>
*   <tr>
*     <td>1.0</td>
*     <td>The initial version</td>
*     <td></td>
*   </tr>
* </table>
*/

/** \} group_csd */

/**
********************************************************************************
* \addtogroup group_csd
********************************************************************************
* \{
* \defgroup group_csd_macros                Macros
* \defgroup group_csd_functions             Functions
* \defgroup group_csd_data_structures       Data Structures
* \defgroup group_csd_enums                 Enumerated Types
*/


#if !defined(CY_CSD_H)
#define CY_CSD_H

#include "cy_device.h"

#if defined (CY_IP_MXCSDV2)

#include <stdint.h>
#include <stddef.h>
#include "cy_syslib.h"

#if defined(__cplusplus)
extern "C" {
#endif

/**
* \addtogroup group_csd_macros
* \{
*/

/** Driver major version */
#define CY_CSD_DRV_VERSION_MAJOR            (1)

/** Driver minor version */
#define CY_CSD_DRV_VERSION_MINOR            (20)

/** Driver version */
#define CY_CSD_DRV2_VERSION                 (120)


/******************************************************************************
* API Constants
******************************************************************************/

/** CSD driver identifier */
#define CY_CSD_ID                           (CY_PDL_DRV_ID(0x41U))

/** Initialization macro for the driver context variable */
#define CY_CSD_CONTEXT_INIT_VALUE           {.lockKey = CY_CSD_NONE_KEY}

/** Nominal Vref stored in SFLASH register */
#define CY_CSD_ADC_VREF_0P8                 (800U)
/** Nominal Vref stored in SFLASH register */
#define CY_CSD_ADC_VREF_1P2                 (1164U)
/** Nominal Vref stored in SFLASH register */
#define CY_CSD_ADC_VREF_1P6                 (1600U)
/** Nominal Vref stored in SFLASH register */
#define CY_CSD_ADC_VREF_2P1                 (2133U)
/** Nominal Vref stored in SFLASH register */
#define CY_CSD_ADC_VREF_2P6                 (2560U)
/** One hundred percent */
#define CY_CSDADC_PERCENTAGE_100            (100u)
/** Max deviation for trim */
#define CY_CSDADC_VREF_TRIM_MAX_DEVIATION   (20u)
/** Vref max gain */
#define CY_CSDADC_VREF_GAIN_MAX             (32u)

/*******************************************************************************
* The CSD HW Block Registers Constants
*******************************************************************************/

/**
* \defgroup group_csd_reg_const Registers Constants
* \{
*/

/** \} group_csd_reg_const */

/** \} group_csd_macros */


/*******************************************************************************
 * Enumerations
 ******************************************************************************/

/**
* \addtogroup group_csd_enums
* \{
*/

/** CSD status definitions */
typedef enum
{
    /** Successful */
    CY_CSD_SUCCESS = 0x00U,

    /** One or more invalid parameters */
    CY_CSD_BAD_PARAM = CY_CSD_ID | CY_PDL_STATUS_ERROR | 0x01U,

    /** The CSD HW block performs conversion */
    CY_CSD_BUSY =  CY_CSD_ID | CY_PDL_STATUS_ERROR | 0x02U,

    /** The CSD HW block is captured by another middleware */
    CY_CSD_LOCKED =  CY_CSD_ID | CY_PDL_STATUS_ERROR | 0x03U

} cy_en_csd_status_t;


/**
* Definitions of upper level keys that use the driver.
*
* Each middleware has a unique key assigned. When middleware successfully
* captures the CSD HW block, this key is placed into the CSD driver context
* structure. All attempts to capture the CSD HW block by other middleware
* are rejected. When the first middleware releases the CSD HW block,
* CY_CSD_NONE_KEY is written to the lockKey variable of the CSD driver context
* structure and any other middleware can capture the CSD HW block.
*/
typedef enum
{
    /** The CSD HW block is unused and not captured by any middleware */
    CY_CSD_NONE_KEY = 0U,

    /**
    * The CSD HW block is captured by the application program
    * directly to implement a customer's specific case
    */
    CY_CSD_USER_DEFINED_KEY = 1U,

    /** The CSD HW block is captured by a CAPSENSE middleware */
    CY_CSD_CAPSENSE_KEY = 2U,

    /** The CSD HW block is captured by a CSDADC middleware */
    CY_CSD_ADC_KEY = 3U,

    /** The CSD HW block is captured by a CSDIDAC middleware */
    CY_CSD_IDAC_KEY = 4U,

    /** The CSD HW block is captured by a CMP middleware */
    CY_CSD_CMP_KEY = 5U

}cy_en_csd_key_t;

/** \} group_csd_enums */


/*******************************************************************************
*       Type Definitions
*******************************************************************************/

/**
* \addtogroup group_csd_data_structures
* \{
*/

/**
* CSD configuration structure.
*
* This structure contains all register values of the CSD HW block. This
* structure is provided by middleware through the Cy_CSD_Init() and
* Cy_CSD_Configure() functions to implement the CSD HW block supported
* sensing modes like self-cap / mutual-cap scanning, ADC measurement, etc.
*/
typedef struct
{
    uint32_t config;       /**< Stores the CSD.CONFIG register value */
    uint32_t spare;        /**< Stores the CSD.SPARE register value */
    uint32_t status;       /**< Stores the CSD.STATUS register value */
    uint32_t statSeq;      /**< Stores the CSD.STAT_SEQ register value */
    uint32_t statCnts;     /**< Stores the CSD.STAT_CNTS register value */
    uint32_t statHcnt;     /**< Stores the CSD.STAT_HCNT register value */
    uint32_t resultVal1;   /**< Stores the CSD.RESULT_VAL1 register value */
    uint32_t resultVal2;   /**< Stores the CSD.RESULT_VAL2 register value */
    uint32_t adcRes;       /**< Stores the CSD.ADC_RES register value */
    uint32_t intr;         /**< Stores the CSD.INTR register value */
    uint32_t intrSet;      /**< Stores the CSD.INTR_SET register value */
    uint32_t intrMask;     /**< Stores the CSD.INTR_MASK register value */
    uint32_t intrMasked;   /**< Stores the CSD.INTR_MASKED register value */
    uint32_t hscmp;        /**< Stores the CSD.HSCMP register value */
    uint32_t ambuf;        /**< Stores the CSD.AMBUF register value */
    uint32_t refgen;       /**< Stores the CSD.REFGEN register value */
    uint32_t csdCmp;       /**< Stores the CSD.CSDCMP register value */
    uint32_t swRes;        /**< Stores the CSD.SW_RES register value */
    uint32_t sensePeriod;  /**< Stores the CSD.SENSE_PERIOD register value */
    uint32_t senseDuty;    /**< Stores the CSD.SENSE_DUTY register value */
    uint32_t swHsPosSel;   /**< Stores the CSD.SW_HS_P_SEL register value */
    uint32_t swHsNegSel;   /**< Stores the CSD.SW_HS_N_SEL register value */
    uint32_t swShieldSel;  /**< Stores the CSD.SW_SHIELD_SEL register value */
    uint32_t swAmuxbufSel; /**< Stores the CSD.SW_AMUXBUF_SEL register value */
    uint32_t swBypSel;     /**< Stores the CSD.SW_BYP_SEL register value */
    uint32_t swCmpPosSel;  /**< Stores the CSD.SW_CMP_P_SEL register value */
    uint32_t swCmpNegSel;  /**< Stores the CSD.SW_CMP_N_SEL register value */
    uint32_t swRefgenSel;  /**< Stores the CSD.SW_REFGEN_SEL register value */
    uint32_t swFwModSel;   /**< Stores the CSD.SW_FW_MOD_SEL register value */
    uint32_t swFwTankSel;  /**< Stores the CSD.SW_FW_TANK_SEL register value */
    uint32_t swDsiSel;     /**< Stores the CSD.SW_DSI_SEL register value */
    uint32_t ioSel;        /**< Stores the CSD.IO_SEL register value */
    uint32_t seqTime;      /**< Stores the CSD.SEQ_TIME register value */
    uint32_t seqInitCnt;   /**< Stores the CSD.SEQ_INIT_CNT register value */
    uint32_t seqNormCnt;   /**< Stores the CSD.SEQ_NORM_CNT register value */
    uint32_t adcCtl;       /**< Stores the CSD.ADC_CTL register value */
    uint32_t seqStart;     /**< Stores the CSD.SEQ_START register value */
    uint32_t idacA;        /**< Stores the CSD.IDACA register value */
    uint32_t idacB;        /**< Stores the CSD.IDACB register value */
} cy_stc_csd_config_t;


/**
* CSD driver context structure.
* This structure is an internal structure of the CSD driver and should not be
* accessed directly by the application program.
*/
typedef struct
{
    /** Middleware ID that currently captured CSD */
    cy_en_csd_key_t lockKey;
} cy_stc_csd_context_t;

/** \} group_csd_data_structures */

/**
* \addtogroup group_csd_reg_const
* \{
*/


/** The register offset */
#define CY_CSD_REG_OFFSET_CONFIG            (offsetof(CSD_Type, CONFIG))
/** The register offset */
#define CY_CSD_REG_OFFSET_SPARE             (offsetof(CSD_Type, SPARE))
/** The register offset */
#define CY_CSD_REG_OFFSET_STATUS            (offsetof(CSD_Type, STATUS))
/** The register offset */
#define CY_CSD_REG_OFFSET_STAT_SEQ          (offsetof(CSD_Type, STAT_SEQ))
/** The register offset */
#define CY_CSD_REG_OFFSET_STAT_CNTS         (offsetof(CSD_Type, STAT_CNTS))
/** The register offset */
#define CY_CSD_REG_OFFSET_STAT_HCNT         (offsetof(CSD_Type, STAT_HCNT))
/** The register offset */
#define CY_CSD_REG_OFFSET_RESULT_VAL1       (offsetof(CSD_Type, RESULT_VAL1))
/** The register offset */
#define CY_CSD_REG_OFFSET_RESULT_VAL2       (offsetof(CSD_Type, RESULT_VAL2))
/** The register offset */
#define CY_CSD_REG_OFFSET_ADC_RES           (offsetof(CSD_Type, ADC_RES))
/** The register offset */
#define CY_CSD_REG_OFFSET_INTR              (offsetof(CSD_Type, INTR))
/** The register offset */
#define CY_CSD_REG_OFFSET_INTR_SET          (offsetof(CSD_Type, INTR_SET))
/** The register offset */
#define CY_CSD_REG_OFFSET_INTR_MASK         (offsetof(CSD_Type, INTR_MASK))
/** The register offset */
#define CY_CSD_REG_OFFSET_INTR_MASKED       (offsetof(CSD_Type, INTR_MASKED))
/** The register offset */
#define CY_CSD_REG_OFFSET_HSCMP             (offsetof(CSD_Type, HSCMP))
/** The register offset */
#define CY_CSD_REG_OFFSET_AMBUF             (offsetof(CSD_Type, AMBUF))
/** The register offset */
#define CY_CSD_REG_OFFSET_REFGEN            (offsetof(CSD_Type, REFGEN))
/** The register offset */
#define CY_CSD_REG_OFFSET_CSDCMP            (offsetof(CSD_Type, CSDCMP))
/** The register offset */
#define CY_CSD_REG_OFFSET_SW_RES            (offsetof(CSD_Type, SW_RES))
/** The register offset */
#define CY_CSD_REG_OFFSET_SENSE_PERIOD      (offsetof(CSD_Type, SENSE_PERIOD))
/** The register offset */
#define CY_CSD_REG_OFFSET_SENSE_DUTY        (offsetof(CSD_Type, SENSE_DUTY))
/** The register offset */
#define CY_CSD_REG_OFFSET_SW_HS_P_SEL       (offsetof(CSD_Type, SW_HS_P_SEL))
/** The register offset */
#define CY_CSD_REG_OFFSET_SW_HS_N_SEL       (offsetof(CSD_Type, SW_HS_N_SEL))
/** The register offset */
#define CY_CSD_REG_OFFSET_SW_SHIELD_SEL     (offsetof(CSD_Type, SW_SHIELD_SEL))
/** The register offset */
#define CY_CSD_REG_OFFSET_SW_AMUXBUF_SEL    (offsetof(CSD_Type, SW_AMUXBUF_SEL))
/** The register offset */
#define CY_CSD_REG_OFFSET_SW_BYP_SEL        (offsetof(CSD_Type, SW_BYP_SEL))
/** The register offset */
#define CY_CSD_REG_OFFSET_SW_CMP_P_SEL      (offsetof(CSD_Type, SW_CMP_P_SEL))
/** The register offset */
#define CY_CSD_REG_OFFSET_SW_CMP_N_SEL      (offsetof(CSD_Type, SW_CMP_N_SEL))
/** The register offset */
#define CY_CSD_REG_OFFSET_SW_REFGEN_SEL     (offsetof(CSD_Type, SW_REFGEN_SEL))
/** The register offset */
#define CY_CSD_REG_OFFSET_SW_FW_MOD_SEL     (offsetof(CSD_Type, SW_FW_MOD_SEL))
/** The register offset */
#define CY_CSD_REG_OFFSET_SW_FW_TANK_SEL    (offsetof(CSD_Type, SW_FW_TANK_SEL))
/** The register offset */
#define CY_CSD_REG_OFFSET_SW_DSI_SEL        (offsetof(CSD_Type, SW_DSI_SEL))
/** The register offset */
#define CY_CSD_REG_OFFSET_IO_SEL            (offsetof(CSD_Type, IO_SEL))
/** The register offset */
#define CY_CSD_REG_OFFSET_SEQ_TIME          (offsetof(CSD_Type, SEQ_TIME))
/** The register offset */
#define CY_CSD_REG_OFFSET_SEQ_INIT_CNT      (offsetof(CSD_Type, SEQ_INIT_CNT))
/** The register offset */
#define CY_CSD_REG_OFFSET_SEQ_NORM_CNT      (offsetof(CSD_Type, SEQ_NORM_CNT))
/** The register offset */
#define CY_CSD_REG_OFFSET_ADC_CTL           (offsetof(CSD_Type, ADC_CTL))
/** The register offset */
#define CY_CSD_REG_OFFSET_SEQ_START         (offsetof(CSD_Type, SEQ_START))
/** The register offset */
#define CY_CSD_REG_OFFSET_IDACA             (offsetof(CSD_Type, IDACA))
/** The register offset */
#define CY_CSD_REG_OFFSET_IDACB             (offsetof(CSD_Type, IDACB))
/** \} group_csd_reg_const */

/*******************************************************************************
*        Function Prototypes
*******************************************************************************/

/**
* \addtogroup group_csd_functions
* \{
*/

cy_en_csd_status_t Cy_CSD_Init(CSD_Type * base, cy_stc_csd_config_t const * config, cy_en_csd_key_t key, cy_stc_csd_context_t * context);
cy_en_csd_status_t Cy_CSD_DeInit(const CSD_Type * base, cy_en_csd_key_t key, cy_stc_csd_context_t * context);
cy_en_csd_status_t Cy_CSD_Capture(CSD_Type * base, cy_en_csd_key_t key, cy_stc_csd_context_t * context);
cy_en_csd_status_t Cy_CSD_Configure(CSD_Type * base, const cy_stc_csd_config_t * config, cy_en_csd_key_t key, const cy_stc_csd_context_t * context);

__STATIC_INLINE cy_en_csd_key_t Cy_CSD_GetLockStatus(const CSD_Type * base, const cy_stc_csd_context_t * context);
__STATIC_INLINE cy_en_csd_status_t Cy_CSD_GetConversionStatus(const CSD_Type * base, const cy_stc_csd_context_t * context);

uint32_t Cy_CSD_GetVrefTrim(uint32_t referenceVoltage);

__STATIC_INLINE uint32_t Cy_CSD_ReadReg(const CSD_Type * base, uint32_t offset);
__STATIC_INLINE void Cy_CSD_WriteReg(CSD_Type * base, uint32_t offset, uint32_t value);
__STATIC_INLINE void Cy_CSD_SetBits(CSD_Type * base, uint32_t offset, uint32_t mask);
__STATIC_INLINE void Cy_CSD_ClrBits(CSD_Type * base, uint32_t offset, uint32_t mask);
__STATIC_INLINE void Cy_CSD_WriteBits(CSD_Type* base, uint32_t offset, uint32_t mask, uint32_t value);

/*******************************************************************************
* Function Name: Cy_CSD_ReadReg
****************************************************************************//**
*
* Reads value from the specified the CSD HW block register.
*
* \param base
* Pointer to a CSD HW block base address.
*
* \param offset
* Register offset relative to base address.
*
* \return
* Returns a value of the CSD HW block register, specified by the offset
* parameter.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_CSD_ReadReg(const CSD_Type * base, uint32_t offset)
{
    return(* (volatile uint32_t *)((uint32_t)base + offset));
}


/*******************************************************************************
* Function Name: Cy_CSD_WriteReg
****************************************************************************//**
*
* Writes a value to the specified CSD HW block register.
*
* \param base
* Pointer to a CSD HW block base address.
*
* \param offset
* Register offset relative to base address.
*
* \param value
* Value to be written to the register.
*
*******************************************************************************/
__STATIC_INLINE void Cy_CSD_WriteReg(CSD_Type * base, uint32_t offset, uint32_t value)
{
    (* (volatile uint32_t *)((uint32_t)base + offset)) = value;
}


/*******************************************************************************
* Function Name: Cy_CSD_SetBits
****************************************************************************//**
*
* Sets bits, specified by the Mask parameter in the CSD HW block register,
* specified by the Offset parameter.
*
* \param base
* Pointer to a CSD HW block base address.
*
* \param offset
* Register offset relative to base address.
*
* \param mask
* Mask value for register bits to be set.
*
*******************************************************************************/
__STATIC_INLINE void Cy_CSD_SetBits(CSD_Type * base, uint32_t offset, uint32_t mask)
{
    volatile uint32_t * regPtr = (volatile uint32_t *)((uint32_t)base + offset);
    (* regPtr) |= mask;
}


/*******************************************************************************
* Function Name: Cy_CSD_ClrBits
****************************************************************************//**
*
* Clears bits, specified by the Mask parameter in the CSD HW block register,
* specified by the Offset parameter.
*
* \param base
* Pointer to a CSD HW block base address.
*
* \param offset
* Register offset relative to base address.
*
* \param mask
* Mask value for register bits to be cleared.
*
*******************************************************************************/
__STATIC_INLINE void Cy_CSD_ClrBits(CSD_Type * base, uint32_t offset, uint32_t mask)
{
    volatile uint32_t * regPtr = (volatile uint32_t *)((uint32_t)base + offset);
    (* regPtr) &= ~mask;
}


/*******************************************************************************
* Function Name: Cy_CSD_WriteBits
****************************************************************************//**
*
* Writes field, specified by the Mask parameter with the value, specified by
* the Value parameter.
*
* \param base
* Pointer to a CSD HW block base address.
*
* \param offset
* Register offset relative to base address.
*
* \param mask
* Specifies bits to be modified.
*
* \param value
* Specifies a value to be written to the register.
*
*******************************************************************************/
__STATIC_INLINE void Cy_CSD_WriteBits(CSD_Type * base, uint32_t offset, uint32_t mask, uint32_t value)
{
    volatile uint32_t * regPtr = (volatile uint32_t *)((uint32_t)base + offset);
    (* regPtr) = ((* regPtr) & ~mask) | (value & mask);
}


/*******************************************************************************
* Function Name: Cy_CSD_GetLockStatus
****************************************************************************//**
*
* Verifies whether the specified CSD HW block is acquired and locked by a
* higher-level firmware.
*
* \param base
* Pointer to a CSD HW block base address.
*
* \param context
* The pointer to the context structure allocated by a user or middleware.
*
* \return
* Returns a key code. See \ref cy_en_csd_key_t.
*
* \funcusage
*
* \snippet csd/snippet/main.c snippet_Cy_CSD_CheckKey
*
*******************************************************************************/
__STATIC_INLINE cy_en_csd_key_t Cy_CSD_GetLockStatus(const CSD_Type * base, const cy_stc_csd_context_t * context)
{
    (void)base;
    return(context->lockKey);
}


/*******************************************************************************
* Function Name: Cy_CSD_GetConversionStatus
****************************************************************************//**
*
* Verifies whether the specified CSD HW block is busy
* (performing scan or conversion).
*
* \param base
* Pointer to a CSD HW block base address.
*
* \param context
* The pointer to the context structure allocated by a user or middleware.
*
* \return
* Returns status code. See \ref cy_en_csd_status_t.
*
* \funcusage
*
* \snippet csd/snippet/main.c snippet_Cy_CSD_CheckStatus
*
*******************************************************************************/
__STATIC_INLINE cy_en_csd_status_t Cy_CSD_GetConversionStatus(const CSD_Type * base, const cy_stc_csd_context_t * context)
{
    cy_en_csd_status_t csdStatus = CY_CSD_BUSY;

    (void)context;
    if (((base->SEQ_START & CSD_SEQ_START_START_Msk) == 0u) &&
        ((base->STAT_SEQ & (CSD_STAT_SEQ_SEQ_STATE_Msk | CSD_STAT_SEQ_ADC_STATE_Msk)) == 0u))
    {
        csdStatus = CY_CSD_SUCCESS;
    }

    return(csdStatus);
}
/** \} group_csd_functions */

/** \} group_csd */

#if defined(__cplusplus)
}
#endif

#endif /* CY_IP_MXCSDV2 */

#endif /* CY_CSD_H */


/* [] END OF FILE */
