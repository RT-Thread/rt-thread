/***************************************************************************//**
* \file cy_gpio.h
* \version 1.70
*
* Provides an API declaration of the GPIO driver
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
* \addtogroup group_gpio
* \{
* The GPIO driver provides an API to configure and access device Input/Output pins.
*
* The functions and other declarations used in this driver are in cy_gpio.h.
* You can include cy_pdl.h to get access to all functions
* and declarations in the PDL.
*
* IO pins include all general purpose types such as GPIO, SIO, HSIO, AUXIO, and
* their variants.
*
* Initialization can be performed either at the port level or by configuring the
* individual pins. For efficient use of code space, port
* configuration should be used in the field. Refer to the product device header files
* for the list of supported ports and pins.
*
* A port is represented by GPIO_PRT_Type and a pin is represented by a number
* 0 to 7.
*
* For PSoC 64 devices the the un-intended protected pins (due to constrain on PPU configuration)
* are modified using PRA driver. But the GPIO diver does not modify the intended protected pins .
*
* - Single pin configuration is performed by using \ref Cy_GPIO_Pin_FastInit
*   (provide specific values) or \ref Cy_GPIO_Pin_Init (provide a filled
*   cy_stc_gpio_pin_config_t structure).
* - An entire port can be configured using \ref Cy_GPIO_Port_Init. Provide a filled
*   cy_stc_gpio_prt_config_t structure. The values in the structure are
*   bitfields representing the desired value for each pin in the port.
* - Pin configuration and management is based on the port address and pin number.
*   \ref Cy_GPIO_PortToAddr function can optionally be used to calculate the port
*   address from the port number at run-time.
* - Each I/O is individually configurable to one of eight drive modes represented
*   by drivemode of cy_stc_gpio_pin_config_t structure.
*
* Once the pin/port initialization is complete, each pin can be accessed by
* specifying the port (GPIO_PRT_Type) and the pin (0-7) in the provided API
* functions.
*
* \section group_gpio_configuration Configuration Considerations
*
* 1. Pin multiplexing is controlled through the High-Speed IO Matrix (HSIOM) selection.
*    This allows the pin to connect to signal sources/sinks throughout the device,
*    as defined by the pin HSIOM selection options (en_hsiom_sel_t).
* 2. All pins are initialized to High-Z drive mode with HSIOM connected to CPU (SW
*    control digital pin only) at Power-On-Reset(POR).
* 3. Some API functions perform read-modify-write operations on shared port
*    registers. These functions are not thread safe and care must be taken when
*    called by the application.
* 4. Digital input buffer provides a high-impedance buffer for the external
*    digital input. The input buffer is connected to the HSIOM for routing to
*    the CPU port registers and selected peripheral. Enabling the input
*    buffer provides possibility to read the pin state via the CPU.
*    If pin is connected to an analog signal, the input buffer should be
*    disabled to avoid crowbar currents. For more information refer to device
*    TRM and the device datasheet.
*
* Multiple pins on a port can be updated using direct port register writes with an
* appropriate port mask. An example is shown below, highlighting the different ways of
* configuring Port 1 pins using:
*
* - Initialize a Pin using cy_stc_gpio_pin_config_t structure
* \snippet gpio/snippet/main.c snippet_Cy_GPIO_Pin_Init
*
* - Initialize entire port using cy_stc_gpio_prt_config_t structure
* \snippet gpio/snippet/main.c snippet_Cy_GPIO_Port_Init
*
* - Port output data register
* - Port output data set register
* - Port output data clear register
*
* \snippet gpio/snippet/main.c Cy_GPIO_Snippet
*
* \section group_gpio_more_information More Information
*
* Refer to the technical reference manual (TRM) and the device datasheet.
*
* \section group_gpio_changelog Changelog
* <table class="doxtable">
*   <tr><th>Version</th><th>Changes</th><th>Reason for Change</th></tr>
*   <tr>
*     <td>1.70</td>
*     <td>Updated driver to support the CAT1D family of devices.</td>
*     <td>Added new family of devices.</td>
*   </tr>
*   <tr>
*     <td rowspan="2">1.60</td>
*     <td>Added \ref Cy_GPIO_SetVtripAuto and \ref Cy_GPIO_GetVtripAuto APIs for
*         configuring    GPIO input buffer voltage for automotive compatible or not,
*         for CAT1C devices.</td>
*     <td>New   APIs support for CAT1C devices.</td>
*   </tr>
*   <tr>
*     <td>Fixed unused variables error.</td>
*     <td>Minor error fixes.</td>
*   </tr>
*   <tr>
*     <td>1.50.1</td>
*     <td>Updated doxygen for External clock source to HF0.</td>
*     <td>Documentation enhancement.</td>
*   </tr>
*   <tr>
*     <td>1.50</td>
*     <td>Modified \ref Cy_GPIO_Pin_Init, \ref Cy_GPIO_Pin_FastInit, and
*         \ref Cy_GPIO_SetDrivemode APIs to catch wrong drive modes.</td>
*     <td>Defect fix.</td>
*   </tr>
*   <tr>
*     <td rowspan="2">1.40</td>
*     <td>Changes in Support of the new family of devices</td>
*     <td>Added new family of devices</td>
*   </tr>
*   <tr>
*     <td>Changes in support of Secure pins used for External clocks on Secure devices</td>
*     <td>Added support for accessing External clocks protected pins</td>
*   </tr>
*   <tr>
*     <td>1.30</td>
*     <td>Fixed/documented MISRA 2012 violations.</td>
*     <td>MISRA 2012 compliance.</td>
*   </tr>
*   <tr>
*     <td>1.20.1</td>
*     <td>Minor documentation updates.</td>
*     <td>Documentation enhancement.</td>
*   </tr>
*   <tr>
*     <td rowspan="3">1.20</td>
*     <td>Flattened the organization of the driver source code into the single source directory and the single include directory.</td>
*     <td>Driver library directory-structure simplification.</td>
*   </tr>
*   <tr>
*     <td>Added the functions for configuring the AMux bus splitter switch cells:
*     - \ref Cy_GPIO_SetAmuxSplit
*     - \ref Cy_GPIO_GetAmuxSplit
*     </td>
*     <td>Added a new functionality related to AMux bus.</td>
*   </tr>
*   <tr>
*     <td>Added register access layer. Use register access macros instead
*         of direct register access using dereferenced pointers.</td>
*     <td>Makes register access device-independent, so that the PDL does
*         not need to be recompiled for each supported part number.</td>
*   </tr>
*   <tr>
*     <td>1.10.1</td>
*     <td>Updated description for the functions: \ref Cy_GPIO_GetInterruptStatus,
*         \ref Cy_GPIO_GetInterruptMask, \ref Cy_GPIO_GetInterruptStatusMasked.
*
*         Minor documentation edits.
*     </td>
*     <td>Documentation update and clarification</td>
*   </tr>
*   <tr>
*     <td>1.10</td>
*     <td>Added input parameter validation to the API functions</td>
*     <td></td>
*   </tr>
*   <tr>
*     <td>1.0</td>
*     <td>Initial version</td>
*     <td></td>
*   </tr>
* </table>
*
* \defgroup group_gpio_macros Macros
* \defgroup group_gpio_functions Functions
* \{
*   \defgroup group_gpio_functions_init       Initialization Functions
*   \defgroup group_gpio_functions_gpio       GPIO Functions
*   \defgroup group_gpio_functions_sio        SIO Functions
*   \defgroup group_gpio_functions_interrupt  Port Interrupt Functions
* \}
* \defgroup group_gpio_data_structures Data Structures
* \defgroup group_gpio_enums Enumerated Types
*/

#if !defined(CY_GPIO_H)
#define CY_GPIO_H

#include "cy_device.h"

#if defined (CY_IP_MXS40SIOSS) || defined (CY_IP_MXS40IOSS) || defined (CY_IP_MXS22IOSS)

#include <stddef.h>
#include "cy_syslib.h"

#if defined(__cplusplus)
extern "C" {
#endif

/** \addtogroup group_gpio_macros
* \{
*/

/** Driver major version */
#define CY_GPIO_DRV_VERSION_MAJOR       1

/** Driver minor version */
#define CY_GPIO_DRV_VERSION_MINOR       70

/** GPIO driver ID */
#define CY_GPIO_ID CY_PDL_DRV_ID(0x16U)

/** \} group_gpio_macros */


/***************************************
*       Enumerations
***************************************/
/**
* \addtogroup group_gpio_enums
* \{
*/

/** GPIO Driver error codes */
typedef enum
{
    CY_GPIO_SUCCESS   = 0x00U,                                    /**< Returned successful */
    CY_GPIO_BAD_PARAM = CY_GPIO_ID | CY_PDL_STATUS_ERROR | 0x01U, /**< Bad parameter was passed */
} cy_en_gpio_status_t;

/** AMux switch open/close config */
typedef enum
{
    CY_GPIO_AMUX_OPENALL,   /**< Open ground switch. Open right switch. Open left switch */
    CY_GPIO_AMUX_L,         /**< Open ground switch. Open right switch. Close left switch */
    CY_GPIO_AMUX_R,         /**< Open ground switch. Close right switch. Open left switch */
    CY_GPIO_AMUX_LR,        /**< Open ground switch. Close right switch. Close left switch */
    CY_GPIO_AMUX_G,         /**< Close ground switch. Open right switch. Open left switch */
    CY_GPIO_AMUX_GL,        /**< Close ground switch. Open right switch. Close left switch */
    CY_GPIO_AMUX_GR,        /**< Close ground switch. Close right switch. Open left switch */
    CY_GPIO_AMUX_GLR,       /**< Close ground switch. Close right switch. Close left switch */
}cy_en_gpio_amuxconnect_t;

/**
* AMux Bus selection
*/
typedef enum
{
    CY_GPIO_AMUXBUSA,       /**< AMuxBus A */
    CY_GPIO_AMUXBUSB        /**< AMuxBus B */
}cy_en_gpio_amuxselect_t;

/** \} group_gpio_enums */


/***************************************
*       Configuration Structures
***************************************/

/**
* \addtogroup group_gpio_data_structures
* \{
*/

/** This structure is used to initialize a port of GPIO pins */
typedef struct
{
    uint32_t out;            /**< Initial output data for the IO pins in the port */
    uint32_t intrMask;       /**< Interrupt enable mask for the port interrupt */
    uint32_t intrCfg;        /**< Port pin interrupt edge detection configuration */
    uint32_t cfg;            /**< Port pin drive modes and input buffer enable configuration */
    uint32_t cfgIn;          /**< Port pin input buffer configuration */
    uint32_t cfgOut;         /**< Port pin output buffer configuration */
    uint32_t cfgSIO;         /**< Port SIO pins configuration */
    uint32_t sel0Active;     /**< HSIOM selection for port pins 0,1,2,3 */
    uint32_t sel1Active;     /**< HSIOM selection for port pins 4,5,6,7 */
#if defined (CY_IP_MXS40SIOSS) || defined (CY_IP_MXS22IOSS)
    /**
    * \note
    * This parameter is available for the CAT1B and CAT1D devices.
    **/
    uint32_t cfgSlew;        /**< Port slew rate configuration */
    /**
    * \note
    * This parameter is available for the CAT1B and CAT1D devices.
    **/
    uint32_t cfgDriveSel0;   /**< Drive strength configuration for pins 0,1,2,3 */
    /**
    * \note
    * This parameter is available for the CAT1B and CAT1D devices.
    **/
    uint32_t cfgDriveSel1;   /**< Drive strength configuration for pins 4,5,6,7 */
    /**
    * \note
    * This parameter is available for the CAT1B and CAT1D devices.
    **/
    uint32_t nonSecMask;     /**< HSIOM non secure mask for port pins 0-7 */
#endif /* CY_IP_MXS40SIOSS, CY_IP_MXS22IOSS */
#if defined (CY_IP_MXS22IOSS)
    /**
    * \note
    * This parameter is available for the CAT1D devices.
    **/
    uint32_t cfgRes;         /**< Pull-up resistor configuration for port pins */
    /**
    * \note
    * This parameter is available for the CAT1D devices.
    **/
    uint32_t cfgOut3;        /**< Port pin extra drive mode \ref CY_GPIO_DM_CFGOUT3_STRONG_PULLUP_HIGHZ */
#endif /* CY_IP_MXS22IOSS */
} cy_stc_gpio_prt_config_t;

/** This structure is used to initialize a single GPIO pin */
typedef struct
{
    uint32_t outVal;         /**< Pin output state */
    uint32_t driveMode;      /**< Drive mode */
    en_hsiom_sel_t hsiom;    /**< HSIOM selection */
    uint32_t intEdge;        /**< Interrupt Edge type */
    uint32_t intMask;        /**< Interrupt enable mask */
    uint32_t vtrip;          /**< Input buffer voltage trip type */
    uint32_t slewRate;       /**< Output buffer slew rate */
    uint32_t driveSel;       /**< Drive strength */
    uint32_t vregEn;         /**< SIO pair output buffer mode */
    uint32_t ibufMode;       /**< SIO pair input buffer mode */
    uint32_t vtripSel;       /**< SIO pair input buffer trip point */
    uint32_t vrefSel;        /**< SIO pair reference voltage for input buffer trip point */
    uint32_t vohSel;         /**< SIO pair regulated voltage output level */
#if defined (CY_IP_MXS40SIOSS) || defined (CY_IP_MXS22IOSS)
    /**
    * \note
    * This parameter is available for the CAT1B and CAT1D devices.
    **/
    uint32_t nonSec;         /**< Secure attribute for each Pin of a port */
#endif /* CY_IP_MXS40SIOSS, CY_IP_MXS22IOSS */
#if defined (CY_IP_MXS22IOSS)
    /**
    * \note
    * This parameter is available for the CAT1D devices.
    **/
    uint32_t pullUpRes; /**< Pull-up resistor configuration for each pin of a port */
#endif /* CY_IP_MXS22IOSS */
} cy_stc_gpio_pin_config_t;

/** \} group_gpio_data_structures */

/***************************************
*        Constants
***************************************/

/** \cond INTERNAL */

/* General Constants */
#define CY_GPIO_PRT_HALF                       (4UL)      /**< Half-way point of a GPIO port */
#define CY_GPIO_PRT_DEINIT                     (0UL)      /**< De-init value for port registers */
#if (defined (CY_IP_MXS40SIOSS) && ((IOSS_HSIOM_HSIOM_SEC_PORT_NR != 0) || (CPUSS_CM33_0_SECEXT_PRESENT != 0))) || defined (CY_IP_MXS22IOSS)
#define CY_HSIOM_NONSEC_DEINIT                 (0xFFUL)   /**< De-init value for port non sec register */
#endif /* CY_IP_MXS40SIOSS, CY_IP_MXS22IOSS */

/* GPIO Masks */
#define CY_GPIO_HSIOM_MASK                     (0x1FUL)   /**< HSIOM selection mask */
#define CY_GPIO_OUT_MASK                       (0x01UL)   /**< Single pin mask for OUT register */
#define CY_GPIO_IN_MASK                        (0x01UL)   /**< Single pin mask for IN register */
#define CY_GPIO_CFG_DM_MASK                    (0x0FUL)   /**< Single pin mask for drive mode in CFG register */
#define CY_GPIO_CFG_DM_NO_INBUF_MASK           (0x07UL)   /**< Single pin mask for drive mode ( without input buffer ) in CFG register */
#define CY_GPIO_CFG_IN_VTRIP_SEL_0_MASK        (0x01UL)   /**< Single pin mask for VTRIP selection in CFG IN register */
#if (defined(CY_IP_MXS40IOSS) && (CY_IP_MXS40IOSS_VERSION == 3U))
#define CY_GPIO_CFG_IN_VTRIP_SEL_1_MASK        (0x01UL)   /**< Single pin mask for VTRIP selection in CFG IN AUTOLVL register */
#endif /* CY_IP_MXS40IOSS_VERSION */
#define CY_GPIO_CFG_IN_VTRIP_SEL_MASK          CY_GPIO_CFG_IN_VTRIP_SEL_0_MASK   /**< Single pin mask for VTRIP selection in CFG IN register */
#define CY_GPIO_INTR_STATUS_MASK               (0x01UL)   /**< Single pin mask for interrupt status in INTR register */
#define CY_GPIO_INTR_EN_MASK                   (0x01UL)   /**< Single pin mask for interrupt status in INTR register */
#define CY_GPIO_INTR_MASKED_MASK               (0x01UL)   /**< Single pin mask for masked interrupt status in INTR_MASKED register */
#define CY_GPIO_INTR_SET_MASK                  (0x01UL)   /**< Single pin mask for setting the interrupt in INTR_MASK register */
#define CY_GPIO_INTR_EDGE_MASK                 (0x03UL)   /**< Single pin mask for interrupt edge type in INTR_EDGE register */
#define CY_GPIO_INTR_FLT_EDGE_MASK             (0x07UL)   /**< Single pin mask for setting filtered interrupt */
#if defined (CY_IP_MXS40IOSS)
#define CY_GPIO_CFG_OUT_SLOW_MASK              (0x01UL)   /**< Single pin mask for slew rate in CFG OUT register */
#define CY_GPIO_CFG_OUT_DRIVE_SEL_MASK         (0x03UL)   /**< Single pin mask for drive strength in CFG OUT register */
#else
#define CY_GPIO_HSIOM_SEC_MASK                 (0x01UL)   /**< Single pin mask for NONSECURE_MASK register */
#define CY_GPIO_CFG_SLEW_EXT_MASK              (0x07UL)   /**< Single pin mask for slew rate in CFG SLEW EXT register */
#define CY_GPIO_CFG_DRIVE_SEL_EXT_MASK         (0x1FUL)   /**< Single pin mask for drive strength in CFG DRIVE EXT register */
#endif /* CY_IP_MXS40IOSS */
#if defined (CY_IP_MXS22IOSS)
#define CY_GPIO_CFG_RES_PULLUP_MODE_MASK       (0x0FUL)   /**< Single pin mask for Pull-up mode in CFG_RES register */
#endif /* CY_IP_MXS22IOSS */

/* SIO Masks */
#define CY_GPIO_VREG_EN_MASK                   (0x01UL)   /**< Single SIO pin mask for voltage regulation enable */
#define CY_GPIO_IBUF_MASK                      (0x01UL)   /**< Single SIO pin mask for input buffer */
#define CY_GPIO_IBUF_SHIFT                     (0x01UL)   /**< Single SIO pin shift for input buffer */
#define CY_GPIO_VTRIP_SEL_MASK                 (0x01UL)   /**< Single SIO pin mask for the input buffer trip point */
#define CY_GPIO_VTRIP_SEL_SHIFT                (0x02UL)   /**< Single SIO pin shift for the input buffer trip point */
#define CY_GPIO_VREF_SEL_MASK                  (0x03UL)   /**< Single SIO pin mask for voltage reference */
#define CY_GPIO_VREF_SEL_SHIFT                 (0x03UL)   /**< Single SIO pin shift for voltage reference */
#define CY_GPIO_VOH_SEL_MASK                   (0x07UL)   /**< Single SIO pin mask for VOH */
#define CY_GPIO_VOH_SEL_SHIFT                  (0x05UL)   /**< Single SIO pin shift for VOH */

/* Special mask for SIO pin pair setting */
#define CY_GPIO_SIO_ODD_PIN_MASK               (0x00FEUL) /**< SIO pin pair selection mask */
#define CY_GPIO_SIO_PIN_MASK                   (0x00FFUL) /**< SIO pin pair mask */

/* Offsets */
#define CY_GPIO_HSIOM_OFFSET                   (3UL)      /**< Offset for HSIOM */
#define CY_GPIO_DRIVE_MODE_OFFSET              (2UL)      /**< Offset for Drive mode */
#define CY_GPIO_INBUF_OFFSET                   (3UL)      /**< Offset for input buffer */
#define CY_GPIO_CFG_OUT_DRIVE_OFFSET           (16UL)     /**< Offset for drive strength */
#define CY_GPIO_INTR_CFG_OFFSET                (1UL)      /**< Offset for interrupt config */
#define CY_GPIO_INTR_FILT_OFFSET               (18UL)     /**< Offset for filtered interrupt config */
#define CY_GPIO_CFG_SIO_OFFSET                 (2UL)      /**< Offset for SIO config */
#if defined (CY_IP_MXS40SIOSS) || defined (CY_IP_MXS22IOSS)
#define CY_GPIO_CFG_SLEW_EXT_OFFSET            (2UL)      /**< Offset for CFG SLEW EXT */
#define CY_GPIO_CFG_DRIVE_SEL_EXT_OFFSET       (3UL)      /**< Offset for CFG SLEW EXT */
#endif /* CY_IP_MXS40SIOSS, CY_IP_MXS22IOSS */
#if defined (CY_IP_MXS22IOSS)
#define CY_GPIO_CFG_RES_PULLUP_MODE_OFFSET     (2UL)      /**< Offset for Pull-up mode */
#endif /* CY_IP_MXS22IOSS */

/* Parameter validation constants */
#define CY_GPIO_PINS_MAX                       (8UL)      /**< Number of pins in the port */
#define CY_GPIO_PRT_PINS_MASK                  (0x0000000FFUL)
#define CY_GPIO_PRT_INTR_CFG_EDGE_SEL_MASK     (GPIO_PRT_INTR_CFG_EDGE0_SEL_Msk | \
                                                GPIO_PRT_INTR_CFG_EDGE1_SEL_Msk | \
                                                GPIO_PRT_INTR_CFG_EDGE2_SEL_Msk | \
                                                GPIO_PRT_INTR_CFG_EDGE3_SEL_Msk | \
                                                GPIO_PRT_INTR_CFG_EDGE4_SEL_Msk | \
                                                GPIO_PRT_INTR_CFG_EDGE5_SEL_Msk | \
                                                GPIO_PRT_INTR_CFG_EDGE6_SEL_Msk | \
                                                GPIO_PRT_INTR_CFG_EDGE7_SEL_Msk)
#define CY_GPIO_PRT_INTR_CFG_RANGE_MASK        (CY_GPIO_PRT_INTR_CFG_EDGE_SEL_MASK | \
                                                GPIO_PRT_INTR_CFG_FLT_EDGE_SEL_Msk | \
                                                GPIO_PRT_INTR_CFG_FLT_SEL_Msk)
#define CY_GPIO_PRT_INT_MASK_MASK              (0x0000001FFUL)
#define CY_GPIO_PRT_SEL_ACTIVE_MASK            (0x1FFFFFFFUL)
#if defined (CY_IP_MXS22IOSS)
#define CY_GPIO_PRT_CFG_RES_MASK               (0x77777777UL)
#endif /* CY_IP_MXS22IOSS */

#define GPIO_MAX_SPLIT_CELL_SEGMENTS           (9U)
#if defined (CY_IP_MXS22IOSS)
/* CY_GPIO_DM_CFGOUT3_STRONG_PULLUP_HIGHZ is 0x80UL, but CFG_OUT3 register uses 0x8UL. */
/* To correctly configure drive mode value in CFG_OUT3 register, CY_GPIO_EXT_DM_SHIFT is used to shift CY_GPIO_DM_CFGOUT3_STRONG_PULLUP_HIGHZ. */
#define CY_GPIO_EXT_DM_SHIFT                   (0x4UL)
#endif /* CY_IP_MXS22IOSS */

/* Parameter validation macros */
#define CY_GPIO_IS_PIN_VALID(pinNum)           (CY_GPIO_PINS_MAX > (pinNum))
#define CY_GPIO_IS_FILTER_PIN_VALID(pinNum)    (CY_GPIO_PINS_MAX >= (pinNum))
#define CY_GPIO_IS_VALUE_VALID(outVal)         (1UL >= (outVal))

#if defined(CY_IP_MXS22IOSS)
#define CY_GPIO_IS_DM_VALID(driveMode)         (((0U == ((driveMode) & (uint32_t)~CY_GPIO_CFG_DM_MASK)) ||\
                                               ((driveMode) == CY_GPIO_DM_CFGOUT3_STRONG_PULLUP_HIGHZ)) && \
                                               ((driveMode) != CY_GPIO_DM_INVALID_IN_OFF) && \
                                               ((driveMode) != CY_GPIO_DM_INVALID))
#else
#define CY_GPIO_IS_DM_VALID(driveMode)         ((0U == ((driveMode) & (uint32_t)~CY_GPIO_CFG_DM_MASK)) && \
                                               ((driveMode) != CY_GPIO_DM_INVALID_IN_OFF) && \
                                               ((driveMode) != CY_GPIO_DM_INVALID))
#endif /* CY_IP_MXS22IOSS */

#define CY_GPIO_IS_HSIOM_VALID(hsiom)          (0U == ((hsiom) & (uint32_t)~CY_GPIO_HSIOM_MASK))

#define CY_GPIO_IS_INT_EDGE_VALID(intEdge)     ((CY_GPIO_INTR_DISABLE  == (intEdge)) || \
                                                (CY_GPIO_INTR_RISING   == (intEdge)) || \
                                                (CY_GPIO_INTR_FALLING  == (intEdge)) || \
                                                (CY_GPIO_INTR_BOTH     == (intEdge)))

#define CY_GPIO_IS_VREF_SEL_VALID(vrefSel)     ((CY_SIO_VREF_PINREF    == (vrefSel)) || \
                                                (CY_SIO_VREF_1_2V      == (vrefSel)) || \
                                                (CY_SIO_VREF_AMUX_A    == (vrefSel)) || \
                                                (CY_SIO_VREF_AMUX_B    == (vrefSel)))

#define CY_GPIO_IS_VOH_SEL_VALID(vrefSel)      ((CY_SIO_VOH_1_00       == (vrefSel)) || \
                                                (CY_SIO_VOH_1_25       == (vrefSel)) || \
                                                (CY_SIO_VOH_1_49       == (vrefSel)) || \
                                                (CY_SIO_VOH_1_67       == (vrefSel)) || \
                                                (CY_SIO_VOH_2_08       == (vrefSel)) || \
                                                (CY_SIO_VOH_2_50       == (vrefSel)) || \
                                                (CY_SIO_VOH_2_78       == (vrefSel)) || \
                                                (CY_SIO_VOH_4_16       == (vrefSel)))

#if defined (CY_IP_MXS22IOSS)
#define CY_GPIO_IS_PULLUP_RES_VALID(PullUp)    ((CY_GPIO_PULLUP_RES_DISABLE   == (PullUp)) || \
                                                (CY_GPIO_PULLUP_RES_570       == (PullUp)) || \
                                                (CY_GPIO_PULLUP_RES_720       == (PullUp)) || \
                                                (CY_GPIO_PULLUP_RES_840       == (PullUp)) || \
                                                (CY_GPIO_PULLUP_RES_1100      == (PullUp)) || \
                                                (CY_GPIO_PULLUP_RES_1200      == (PullUp)) || \
                                                (CY_GPIO_PULLUP_RES_1800      == (PullUp)) || \
                                                (CY_GPIO_PULLUP_RES_2800      == (PullUp)))

#define CY_GPIO_PRT_IS_PULLUP_RES_VALID(PullUp)    (0U == ((PullUp) & (uint32_t)~CY_GPIO_PRT_CFG_RES_MASK))
#endif /* CY_IP_MXS22IOSS */

#define CY_GPIO_IS_PIN_BIT_VALID(pinBit)       (0U == ((pinBit) & (uint32_t)~CY_GPIO_PRT_PINS_MASK))
#define CY_GPIO_IS_INTR_CFG_VALID(intrCfg)     (0U == ((intrCfg) & (uint32_t)~CY_GPIO_PRT_INTR_CFG_RANGE_MASK))
#define CY_GPIO_IS_INTR_MASK_VALID(intrMask)   (0U == ((intrMask) & (uint32_t)~CY_GPIO_PRT_INT_MASK_MASK))
#define CY_GPIO_IS_SEL_ACT_VALID(selActive)    (0U == ((selActive) & (uint32_t)~CY_GPIO_PRT_SEL_ACTIVE_MASK))

#define CY_GPIO_IS_AMUX_SPLIT_VALID(switchCtrl)       (((uint32_t) (switchCtrl)) < GPIO_MAX_SPLIT_CELL_SEGMENTS)

#define CY_GPIO_IS_AMUX_CONNECT_VALID(amuxConnect)    ((CY_GPIO_AMUX_OPENALL == (amuxConnect)) || \
                                                       (CY_GPIO_AMUX_L       == (amuxConnect)) || \
                                                       (CY_GPIO_AMUX_R       == (amuxConnect)) || \
                                                       (CY_GPIO_AMUX_LR      == (amuxConnect)) || \
                                                       (CY_GPIO_AMUX_G       == (amuxConnect)) || \
                                                       (CY_GPIO_AMUX_GL      == (amuxConnect)) || \
                                                       (CY_GPIO_AMUX_GR      == (amuxConnect)) || \
                                                       (CY_GPIO_AMUX_GLR     == (amuxConnect)))

#define CY_GPIO_IS_AMUX_SELECT_VALID(amuxBus)       ((CY_GPIO_AMUXBUSA       == (amuxBus)) || \
                                                     (CY_GPIO_AMUXBUSB       == (amuxBus)))

#if defined (CY_IP_MXS40IOSS)
#define CY_GPIO_IS_DRIVE_SEL_VALID(driveSel)   ((CY_GPIO_DRIVE_FULL    == (driveSel)) || \
                                                (CY_GPIO_DRIVE_1_2     == (driveSel)) || \
                                                (CY_GPIO_DRIVE_1_4     == (driveSel)) || \
                                                (CY_GPIO_DRIVE_1_8     == (driveSel)))
#else
#define CY_GPIO_IS_HSIOM_SEC_VALID(secValue)   (0U == ((secValue) & (uint32_t)~CY_GPIO_HSIOM_SEC_MASK))
#define CY_GPIO_IS_SLEW_RATE_VALID(slewRate)   (0U == ((slewRate) & (uint32_t)~CY_GPIO_CFG_SLEW_EXT_MASK))
#define CY_GPIO_IS_DRIVE_SEL_VALID(driveSel)   (0U == ((driveSel) & (uint32_t)~CY_GPIO_CFG_DRIVE_SEL_EXT_MASK))
#endif /* CY_IP_MXS40IOSS */

/** \endcond */


/***************************************
*        Function Constants
***************************************/

/**
* \addtogroup group_gpio_macros
* \{
*/

/**
* \defgroup group_gpio_driveModes Pin drive mode
* \{
* Constants to be used for setting the drive mode of the pin. There are eight
* primary drive modes.
* Below diagrams are simplified output driver diagrams of the pin view for the
* CPU register and UDB/DSI based digital peripherals on each of the eight drive
* modes.
* \image html gpio_cpu_dm_block_diagram.png
*
* Below is a simplified output driver diagram that shows the pin view for
* fixed-function-based peripherals for each of the eight drive modes.
* \image html gpio_periio_dm_block_diagram.png
*
* - High-Impedance:
*   This is the standard high-impedance (HI-Z) state recommended for analog and
*   digital inputs. For digital signals, the input buffer is enabled; for analog
*   signals, the input buffer is typically disabled to reduce crowbar current
*   and leakage in low-power designs. To achieve the lowest device current, unused
*   GPIOs must be configured to the high-impedance drive mode with input buffer
*   disabled. Highimpedance drive mode with input buffer disabled is also the
*   default pin reset state.
*
* - Resistive Pull-Up or Resistive Pull-Down:
*   Resistive modes provide a series resistance in one of the data states and
*   strong drive in the other. Pins can be used for either digital input or
*   digital output in these modes. If resistive pull-up is required, a '1' must be
*   written to that pin's Data Register bit. If resistive pull-down is required,
*   a '0' must be written to that pin's Data Register. Interfacing mechanical
*   switches is a common application of these drive modes. The resistive modes are
*   also used to interface PSoC with open drain drive lines. Resistive pull-up is
*   used when the input is open drain low and resistive pull-down is used when the
*   input is open drain high.
*
* - Open Drain Drives High and Open Drain Drives Low:
*   Open drain modes provide high impedance in one of the data states and strong
*   drive in the other. Pins are useful as digital inputs or outputs in these
*   modes. Therefore, these modes are widely used in bidirectional digital
*   communication. Open drain drive high mode is used when the signal is
*   externally pulled down and open drain drive low is used when the signal is
*   externally pulled high. A common application for the open drain drives low
*   mode is driving I2C bus signal lines.
*
* - Strong Drive:
*   The strong drive mode is the standard digital output mode for pins; it
*   provides a strong CMOS output drive in both high and low states. Strong drive
*   mode pins should not be used as inputs under normal circumstances. This mode
*   is often used for digital output signals or to drive external devices.
*
* - Resistive Pull-Up and Resistive Pull-Down:
*   In the resistive pull-up and pull-down mode, the GPIO will have a series
*   resistance in both logic 1 and logic 0 output states. The high data state is
*   pulled up while the low data state is pulled down. This mode is useful when
*   the pin is driven by other signals that may cause shorts.
*/
#define CY_GPIO_DM_ANALOG                      (0x00UL)    /**< Analog High-Z. Input buffer off */
#define CY_GPIO_DM_INVALID_IN_OFF              (0x01UL)    /**< Invalid mode. It should not be used */
#define CY_GPIO_DM_PULLUP_IN_OFF               (0x02UL)    /**< Resistive Pull-Up. Input buffer off */
#define CY_GPIO_DM_PULLDOWN_IN_OFF             (0x03UL)    /**< Resistive Pull-Down. Input buffer off */
#define CY_GPIO_DM_OD_DRIVESLOW_IN_OFF         (0x04UL)    /**< Open Drain, Drives Low. Input buffer off */
#define CY_GPIO_DM_OD_DRIVESHIGH_IN_OFF        (0x05UL)    /**< Open Drain, Drives High. Input buffer off */
#define CY_GPIO_DM_STRONG_IN_OFF               (0x06UL)    /**< Strong Drive. Input buffer off */
#define CY_GPIO_DM_PULLUP_DOWN_IN_OFF          (0x07UL)    /**< Resistive Pull-Up/Down. Input buffer off */
#define CY_GPIO_DM_HIGHZ                       (0x08UL)    /**< Digital High-Z. Input buffer on */
#define CY_GPIO_DM_INVALID                     (0x09UL)    /**< Invalid mode. It should not be used */
#define CY_GPIO_DM_PULLUP                      (0x0AUL)    /**< Resistive Pull-Up. Input buffer on */
#define CY_GPIO_DM_PULLDOWN                    (0x0BUL)    /**< Resistive Pull-Down. Input buffer on */
#define CY_GPIO_DM_OD_DRIVESLOW                (0x0CUL)    /**< Open Drain, Drives Low. Input buffer on */
#define CY_GPIO_DM_OD_DRIVESHIGH               (0x0DUL)    /**< Open Drain, Drives High. Input buffer on */
#define CY_GPIO_DM_STRONG                      (0x0EUL)    /**< Strong Drive. Input buffer on */
#define CY_GPIO_DM_PULLUP_DOWN                 (0x0FUL)    /**< Resistive Pull-Up/Down. Input buffer on */
#if defined (CY_IP_MXS22IOSS)
    /**
    * \note
    * This drive mode is available for the CAT1D devices.
    **/
#define CY_GPIO_DM_CFGOUT3_STRONG_PULLUP_HIGHZ (0x80UL)    /**< Strong Drive/Resistive Pull-Up/High-Z based on data_out_en and data_out signals. It is applicable for I3C */
#endif /* CY_IP_MXS22IOSS */
/** \} */

/**
* \defgroup group_gpio_vtrip Voltage trip mode
* \{
* Constants to be used for setting the voltage trip type on the pin.
*/
#define CY_GPIO_VTRIP_CMOS                     (0x00UL) /**< Input buffer compatible with CMOS and I2C interfaces */
#define CY_GPIO_VTRIP_TTL                      (0x01UL) /**< Input buffer compatible with TTL and MediaLB interfaces */
/** \} */

#if (defined(CY_IP_MXS40IOSS) && (CY_IP_MXS40IOSS_VERSION == 3U)) || defined (CY_DOXYGEN)
/**
* \defgroup group_gpio_vtrip_auto Voltage trip automotive compatible mode
* \{
* Constants to be used for setting the input buffer automotive compatible mode (trip points and hysteresis) for GPIO upper bit.
*
* \note
* These macros are available for CAT1B devices.
*
*/
#define CY_GPIO_VTRIP_DIS_AUTO                 (0x00UL) /**< Input buffer is not compatible with automotive and it is compatible with CMOS/TTL interfaces */
#define CY_GPIO_VTRIP_SEL_AUTO                 (0x01UL) /**< Input buffer is compatible with automotive */
/** \} */
#endif/* CY_IP_MXS40IOSS_VERSION */

/**
* \defgroup group_gpio_slewRate Slew Rate Mode
* \{
* Constants to be used for setting the slew rate of the pin.
*/
#define CY_GPIO_SLEW_FAST                      (0x00UL) /**< Fast slew rate */
#define CY_GPIO_SLEW_SLOW                      (0x01UL) /**< Slow slew rate */
/** \} */

/**
* \defgroup group_gpio_driveStrength Pin drive strength
* \{
* Constants to be used for setting the drive strength of the pin.
*/
#define CY_GPIO_DRIVE_FULL                     (0x00UL) /**< Full drive strength: Max drive current */
#define CY_GPIO_DRIVE_1_2                      (0x01UL) /**< 1/2 drive strength: 1/2 drive current */
#define CY_GPIO_DRIVE_1_4                      (0x02UL) /**< 1/4 drive strength: 1/4 drive current */
#define CY_GPIO_DRIVE_1_8                      (0x03UL) /**< 1/8 drive strength: 1/8 drive current */
/** \} */

/**
* \defgroup group_gpio_interruptTrigger Interrupt trigger type
* \{
* Constants to be used for setting the interrupt trigger type on the pin.
*/
#define CY_GPIO_INTR_DISABLE                   (0x00UL) /**< Disable the pin interrupt generation */
#define CY_GPIO_INTR_RISING                    (0x01UL) /**< Rising-Edge interrupt */
#define CY_GPIO_INTR_FALLING                   (0x02UL) /**< Falling-Edge interrupt */
#define CY_GPIO_INTR_BOTH                      (0x03UL) /**< Both-Edge interrupt */
/** \} */

/**
* \defgroup group_gpio_sioVreg SIO output buffer mode
* \{
* Constants to be used for setting the SIO output buffer mode on the pin.
*/
#define CY_SIO_VREG_UNREGULATED                (0x00UL) /**< Unregulated output buffer */
#define CY_SIO_VREG_REGULATED                  (0x01UL) /**< Regulated output buffer */
/** \} */

/**
* \defgroup group_gpio_sioIbuf SIO input buffer mode
* \{
* Constants to be used for setting the SIO input buffer mode on the pin.
*/
#define CY_SIO_IBUF_SINGLEENDED                (0x00UL) /**< Single ended input buffer */
#define CY_SIO_IBUF_DIFFERENTIAL               (0x01UL) /**< Differential input buffer */
/** \} */

/**
* \defgroup group_gpio_sioVtrip SIO input buffer trip-point
* \{
* Constants to be used for setting the SIO input buffer trip-point of the pin.
*/
#define CY_SIO_VTRIP_CMOS                      (0x00UL) /**< CMOS input buffer (single-ended) */
#define CY_SIO_VTRIP_TTL                       (0x01UL) /**< TTL input buffer (single-ended) */
#define CY_SIO_VTRIP_0_5VDDIO_0_5VOH           (0x00UL) /**< 0.5xVddio or 0.5xVoh (differential) */
#define CY_SIO_VTRIP_0_4VDDIO_1_0VREF          (0x01UL) /**< 0.4xVddio or 0.4xVoh (differential) */
/** \} */

/**
* \defgroup group_gpio_sioVref SIO reference voltage for input buffer trip-point
* \{
* Constants to be used for setting the reference voltage of SIO input buffer trip-point.
*/
#define CY_SIO_VREF_PINREF                     (0x00UL) /**< Vref from analog pin */
#define CY_SIO_VREF_1_2V                       (0x01UL) /**< Vref from internal 1.2V reference */
#define CY_SIO_VREF_AMUX_A                     (0x02UL) /**< Vref from AMUXBUS_A */
#define CY_SIO_VREF_AMUX_B                     (0x03UL) /**< Vref from AMUXBUS_B */
/** \} */

/**
* \defgroup group_gpio_sioVoh Regulated output voltage level (Voh) and input buffer trip-point of an SIO pair
* \{
* Constants to be used for setting the Voh and input buffer trip-point of an SIO pair
*/
#define CY_SIO_VOH_1_00                        (0x00UL) /**< Voh = 1 x Reference */
#define CY_SIO_VOH_1_25                        (0x01UL) /**< Voh = 1.25 x Reference */
#define CY_SIO_VOH_1_49                        (0x02UL) /**< Voh = 1.49 x Reference */
#define CY_SIO_VOH_1_67                        (0x03UL) /**< Voh = 1.67 x Reference */
#define CY_SIO_VOH_2_08                        (0x04UL) /**< Voh = 2.08 x Reference */
#define CY_SIO_VOH_2_50                        (0x05UL) /**< Voh = 2.50 x Reference */
#define CY_SIO_VOH_2_78                        (0x06UL) /**< Voh = 2.78 x Reference */
#define CY_SIO_VOH_4_16                        (0x07UL) /**< Voh = 4.16 x Reference */
/** \} */

#if defined (CY_IP_MXS22IOSS)
/**
* \defgroup group_gpio_PullUpMode Pull-up mode
* \{
* Constants to be used for setting the Pull-up mode on the pin.
*
* \note
* This parameter is available for the CAT1D devices.
*
*/
#define CY_GPIO_PULLUP_RES_DISABLE             (0x00UL) /**< Disable additional Pull-ups */
#define CY_GPIO_PULLUP_RES_570                 (0x07UL) /**< Pull-up 570 ohms */
#define CY_GPIO_PULLUP_RES_720                 (0x06UL) /**< Pull-up 720 ohms */
#define CY_GPIO_PULLUP_RES_840                 (0x05UL) /**< Pull-up 840 ohms */
#define CY_GPIO_PULLUP_RES_1100                (0x03UL) /**< Pull-up 1100 ohms */
#define CY_GPIO_PULLUP_RES_1200                (0x04UL) /**< Pull-up 1200 ohms */
#define CY_GPIO_PULLUP_RES_1800                (0x02UL) /**< Pull-up 1800 ohms */
#define CY_GPIO_PULLUP_RES_2800                (0x01UL) /**< Pull-up 2800 ohms */
/** \} */
#endif /* CY_IP_MXS22IOSS */
/** \} group_gpio_macros */

/***************************************
*        Function Prototypes
***************************************/

/**
* \addtogroup group_gpio_functions
* \{
*/

/**
* \addtogroup group_gpio_functions_init
* \{
*/

cy_en_gpio_status_t Cy_GPIO_Pin_Init(GPIO_PRT_Type* base, uint32_t pinNum, const cy_stc_gpio_pin_config_t *config);
cy_en_gpio_status_t Cy_GPIO_Port_Init(GPIO_PRT_Type* base, const cy_stc_gpio_prt_config_t *config);
void Cy_GPIO_Pin_FastInit(GPIO_PRT_Type* base, uint32_t pinNum, uint32_t driveMode, uint32_t outVal, en_hsiom_sel_t hsiom);
void Cy_GPIO_Port_Deinit(GPIO_PRT_Type* base);
void Cy_GPIO_SetHSIOM(GPIO_PRT_Type* base, uint32_t pinNum, en_hsiom_sel_t value);
en_hsiom_sel_t Cy_GPIO_GetHSIOM(GPIO_PRT_Type* base, uint32_t pinNum);
__STATIC_INLINE GPIO_PRT_Type* Cy_GPIO_PortToAddr(uint32_t portNum);
#if (defined (CY_IP_MXS40SIOSS) && ((IOSS_HSIOM_HSIOM_SEC_PORT_NR != 0) || (CPUSS_CM33_0_SECEXT_PRESENT != 0))) || defined (CY_IP_MXS22IOSS)
void Cy_GPIO_Pin_SecFastInit(GPIO_PRT_Type* base, uint32_t pinNum, uint32_t driveMode, uint32_t outVal, en_hsiom_sel_t hsiom);
__STATIC_INLINE void Cy_GPIO_SetHSIOM_SecPin(GPIO_PRT_Type* base, uint32_t pinNum, uint32_t value);
__STATIC_INLINE uint32_t Cy_GPIO_GetHSIOM_SecPin(GPIO_PRT_Type* base, uint32_t pinNum);
#endif /* CY_IP_MXS40SIOSS, IOSS_HSIOM_HSIOM_SEC_PORT_NR, CPUSS_CM33_0_SECEXT_PRESENT, CY_IP_MXS22IOSS */

/** \} group_gpio_functions_init */

/**
* \addtogroup group_gpio_functions_gpio
* \{
*/

void Cy_GPIO_SetAmuxSplit(cy_en_amux_split_t switchCtrl, cy_en_gpio_amuxconnect_t amuxConnect, cy_en_gpio_amuxselect_t amuxBus);
cy_en_gpio_amuxconnect_t Cy_GPIO_GetAmuxSplit(cy_en_amux_split_t switchCtrl, cy_en_gpio_amuxselect_t amuxBus);

uint32_t Cy_GPIO_Read(GPIO_PRT_Type* base, uint32_t pinNum);
void Cy_GPIO_Write(GPIO_PRT_Type* base, uint32_t pinNum, uint32_t value);
uint32_t Cy_GPIO_ReadOut(GPIO_PRT_Type* base, uint32_t pinNum);
void Cy_GPIO_Set(GPIO_PRT_Type* base, uint32_t pinNum);
void Cy_GPIO_Clr(GPIO_PRT_Type* base, uint32_t pinNum);
void Cy_GPIO_Inv(GPIO_PRT_Type* base, uint32_t pinNum);
void Cy_GPIO_SetDrivemode(GPIO_PRT_Type* base, uint32_t pinNum, uint32_t value);
uint32_t Cy_GPIO_GetDrivemode(GPIO_PRT_Type* base, uint32_t pinNum);
void Cy_GPIO_SetVtrip(GPIO_PRT_Type* base, uint32_t pinNum, uint32_t value);
uint32_t Cy_GPIO_GetVtrip(GPIO_PRT_Type* base, uint32_t pinNum);
#if (defined(CY_IP_MXS40IOSS) && (CY_IP_MXS40IOSS_VERSION == 3U)) || defined (CY_DOXYGEN)
void Cy_GPIO_SetVtripAuto(GPIO_PRT_Type* base, uint32_t pinNum, uint32_t value);
uint32_t Cy_GPIO_GetVtripAuto(GPIO_PRT_Type* base, uint32_t pinNum);
#endif /* CY_IP_MXS40IOSS_VERSION */
void Cy_GPIO_SetSlewRate(GPIO_PRT_Type* base, uint32_t pinNum, uint32_t value);
uint32_t Cy_GPIO_GetSlewRate(GPIO_PRT_Type* base, uint32_t pinNum);
void Cy_GPIO_SetDriveSel(GPIO_PRT_Type* base, uint32_t pinNum, uint32_t value);
uint32_t Cy_GPIO_GetDriveSel(GPIO_PRT_Type* base, uint32_t pinNum);

#if defined (CY_IP_MXS22IOSS)
void Cy_GPIO_SetPullupResistance(GPIO_PRT_Type* base, uint32_t pinNum, uint32_t value);
uint32_t Cy_GPIO_GetPullupResistance(GPIO_PRT_Type* base, uint32_t pinNum);
#endif /* CY_IP_MXS22IOSS */

/** \} group_gpio_functions_gpio */

/**
* \addtogroup group_gpio_functions_sio
* \{
*/

void Cy_GPIO_SetVregEn(GPIO_PRT_Type* base, uint32_t pinNum, uint32_t value);
uint32_t Cy_GPIO_GetVregEn(GPIO_PRT_Type* base, uint32_t pinNum);
void Cy_GPIO_SetIbufMode(GPIO_PRT_Type* base, uint32_t pinNum, uint32_t value);
uint32_t Cy_GPIO_GetIbufMode(GPIO_PRT_Type* base, uint32_t pinNum);
void Cy_GPIO_SetVtripSel(GPIO_PRT_Type* base, uint32_t pinNum, uint32_t value);
uint32_t Cy_GPIO_GetVtripSel(GPIO_PRT_Type* base, uint32_t pinNum);
void Cy_GPIO_SetVrefSel(GPIO_PRT_Type* base, uint32_t pinNum, uint32_t value);
uint32_t Cy_GPIO_GetVrefSel(GPIO_PRT_Type* base, uint32_t pinNum);
void Cy_GPIO_SetVohSel(GPIO_PRT_Type* base, uint32_t pinNum, uint32_t value);
uint32_t Cy_GPIO_GetVohSel(GPIO_PRT_Type* base, uint32_t pinNum);

/** \} group_gpio_functions_sio */

/**
* \addtogroup group_gpio_functions_interrupt
* \{
*/

uint32_t Cy_GPIO_GetInterruptStatus(GPIO_PRT_Type* base, uint32_t pinNum);
void Cy_GPIO_ClearInterrupt(GPIO_PRT_Type* base, uint32_t pinNum);
void Cy_GPIO_SetInterruptMask(GPIO_PRT_Type* base, uint32_t pinNum, uint32_t value);
uint32_t Cy_GPIO_GetInterruptMask(GPIO_PRT_Type* base, uint32_t pinNum);
uint32_t Cy_GPIO_GetInterruptStatusMasked(GPIO_PRT_Type* base, uint32_t pinNum);
void Cy_GPIO_SetSwInterrupt(GPIO_PRT_Type* base, uint32_t pinNum);
void Cy_GPIO_SetInterruptEdge(GPIO_PRT_Type* base, uint32_t pinNum, uint32_t value);
uint32_t Cy_GPIO_GetInterruptEdge(GPIO_PRT_Type* base, uint32_t pinNum);
void Cy_GPIO_SetFilter(GPIO_PRT_Type* base, uint32_t value);
uint32_t Cy_GPIO_GetFilter(GPIO_PRT_Type* base);

__STATIC_INLINE uint32_t Cy_GPIO_GetInterruptCause0(void);
__STATIC_INLINE uint32_t Cy_GPIO_GetInterruptCause1(void);
__STATIC_INLINE uint32_t Cy_GPIO_GetInterruptCause2(void);
__STATIC_INLINE uint32_t Cy_GPIO_GetInterruptCause3(void);
#if (defined (CY_IP_MXS40SIOSS) && (CPUSS_CM33_0_SECEXT_PRESENT != 0)) || defined (CY_IP_MXS22IOSS)
__STATIC_INLINE uint32_t Cy_GPIO_GetSecureInterruptCause0(void);
__STATIC_INLINE uint32_t Cy_GPIO_GetSecureInterruptCause1(void);
__STATIC_INLINE uint32_t Cy_GPIO_GetSecureInterruptCause2(void);
__STATIC_INLINE uint32_t Cy_GPIO_GetSecureInterruptCause3(void);
#endif /* CY_IP_MXS40SIOSS, CY_IP_MXS22IOSS */

/** \} group_gpio_functions_interrupt */

/** \cond INTERNAL */
#if defined (CY_IP_MXS40SIOSS) || (defined (CY_IP_MXS40IOSS) && (CY_IP_MXS40IOSS_VERSION > 2)) || defined (CY_IP_MXS22IOSS)
#define HSIOM_PRT_V1_Type HSIOM_PRT_Type
#endif /* CY_IP_MXS40SIOSS, CY_IP_MXS22IOSS */
/** \endcond */

/**
* \addtogroup group_gpio_functions_init
* \{
*/

#if (defined (CY_IP_MXS40SIOSS) && ((IOSS_HSIOM_HSIOM_SEC_PORT_NR != 0) || (CPUSS_CM33_0_SECEXT_PRESENT != 0))) || defined (CY_IP_MXS22IOSS)
/*******************************************************************************
* Function Name: Cy_GPIO_SetHSIOM_SecPin
****************************************************************************//**
*
* Configures the pin as secure or non-secure.
*
*
* \param base
* Pointer to the pin's port register base address
*
* \param pinNum
* Position of the pin bit-field within the port register
*
* \param value
* Secure HSIOM non-secure mask
*
* \note
* This function modifies a port register in a read-modify-write operation. It is
* not thread safe as the resource is shared among multiple pins on a port.
* This function should be called from the right protection context to access
* HSIOM secure port (HSIOM_SECURE_PRT_Type).
*
* \note
* This API is available for the CAT1B and CAT1D devices.
*
* \funcusage
*
*******************************************************************************/
__STATIC_INLINE void Cy_GPIO_SetHSIOM_SecPin(GPIO_PRT_Type* base, uint32_t pinNum, uint32_t value)
{
    uint32_t tempReg;
    uint32_t portNum;
    HSIOM_SECURE_PRT_Type* portAddrSecHSIOM;

    CY_ASSERT_L2(CY_GPIO_IS_PIN_VALID(pinNum));
    CY_ASSERT_L2(CY_GPIO_IS_HSIOM_VALID(value));

    portNum = ((uint32_t)(base) - CY_GPIO_BASE) / GPIO_PRT_SECTION_SIZE;
    portAddrSecHSIOM = (HSIOM_SECURE_PRT_Type*)(CY_HSIOM_SECURE_BASE + (HSIOM_SECURE_PRT_SECTION_SIZE * portNum));

    tempReg= HSIOM_SEC_PRT_NONSEC_MASK(portAddrSecHSIOM) & ~(CY_GPIO_HSIOM_SEC_MASK << pinNum);
    HSIOM_SEC_PRT_NONSEC_MASK(portAddrSecHSIOM) = tempReg | ((value & CY_GPIO_HSIOM_SEC_MASK) << pinNum);
}

/*******************************************************************************
* Function Name: Cy_GPIO_GetHSIOM_SecPin
****************************************************************************//**
*
* Returns the current status of secure Pin.
*
* \param base
* Pointer to the pin's port register base address
*
* \param pinNum
* Position of the pin bit-field within the port register
*
* \return
* HSIOM input selection
*
* \note
* This API is available for the CAT1B and CAT1D devices.
*
* \funcusage
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_GPIO_GetHSIOM_SecPin(GPIO_PRT_Type* base, uint32_t pinNum)
{
    uint32_t portNum;
    HSIOM_SECURE_PRT_Type* portAddrSecHSIOM;

    CY_ASSERT_L2(CY_GPIO_IS_PIN_VALID(pinNum));

    portNum = ((uint32_t)(base) - CY_GPIO_BASE) / GPIO_PRT_SECTION_SIZE;
    portAddrSecHSIOM = (HSIOM_SECURE_PRT_Type*)(CY_HSIOM_SECURE_BASE + (HSIOM_SECURE_PRT_SECTION_SIZE * portNum));

    return (uint32_t)((HSIOM_SEC_PRT_NONSEC_MASK(portAddrSecHSIOM) >> pinNum) & CY_GPIO_HSIOM_SEC_MASK);
}
#endif /* CY_IP_MXS40SIOSS, CY_IP_MXS22IOSS */

/*******************************************************************************
* Function Name: Cy_GPIO_PortToAddr
****************************************************************************//**
*
* Retrieves the port address based on the given port number.
*
* This is a helper function to calculate the port base address when given a port
* number. It is to be used when pin access needs to be calculated at runtime.
*
* \param portNum
* Port number
*
* \return
* Base address of the port register structure
*
* \funcusage
* \snippet gpio/snippet/main.c snippet_Cy_GPIO_PortToAddr
*
*******************************************************************************/
__STATIC_INLINE GPIO_PRT_Type* Cy_GPIO_PortToAddr(uint32_t portNum)
{
    GPIO_PRT_Type* portBase;

    if(portNum < (uint32_t)IOSS_GPIO_GPIO_PORT_NR)
    {
        portBase = (GPIO_PRT_Type *)(CY_GPIO_BASE + (GPIO_PRT_SECTION_SIZE * portNum));
    }
    else
    {
        /* Error: Return default base address */
        portBase = (GPIO_PRT_Type *)(CY_GPIO_BASE);
    }

    return (portBase);
}

/** \} group_gpio_functions_init */



/**
* \addtogroup group_gpio_functions_interrupt
* \{
*/

/*******************************************************************************
* Function Name: Cy_GPIO_GetInterruptCause0
****************************************************************************//**
*
* Returns the interrupt status for ports 0 to 31.
*
* \return
* 0 = Interrupt not detected on port
* 1 = Interrupt detected on port
*
* \funcusage
* \snippet gpio/snippet/main.c snippet_Cy_GPIO_GetInterruptCause0
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_GPIO_GetInterruptCause0(void)
{
    return (GPIO_INTR_CAUSE0);
}


/*******************************************************************************
* Function Name: Cy_GPIO_GetInterruptCause1
****************************************************************************//**
*
* Returns the interrupt status for ports 32 to 63.
*
* \return
* 0 = Interrupt not detected on port
* 1 = Interrupt detected on port
*
* \funcusage
* Refer to the Cy_GPIO_GetInterruptCause0() example.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_GPIO_GetInterruptCause1(void)
{
    return (GPIO_INTR_CAUSE1);
}


/*******************************************************************************
* Function Name: Cy_GPIO_GetInterruptCause2
****************************************************************************//**
*
* Returns the interrupt status for ports 64 to 95.
*
* \return
* 0 = Interrupt not detected on port
* 1 = Interrupt detected on port
* \funcusage
* Refer to the Cy_GPIO_GetInterruptCause0() example.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_GPIO_GetInterruptCause2(void)
{
    return (GPIO_INTR_CAUSE2);
}


/*******************************************************************************
* Function Name: Cy_GPIO_GetInterruptCause3
****************************************************************************//**
*
* Returns the interrupt status for ports 96 to 127.
*
* \return
* 0 = Interrupt not detected on port
* 1 = Interrupt detected on port
*
* \funcusage
* Refer to the Cy_GPIO_GetInterruptCause0() example.
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_GPIO_GetInterruptCause3(void)
{
    return (GPIO_INTR_CAUSE3);
}

#if (defined (CY_IP_MXS40SIOSS) && (CPUSS_CM33_0_SECEXT_PRESENT != 0)) || defined (CY_IP_MXS22IOSS)
/*******************************************************************************
* Function Name: Cy_GPIO_GetSecureInterruptCause0
****************************************************************************//**
*
* Returns the interrupt status for ports 0 to 31.
*
* \return
* 0 = Interrupt not detected on port
* 1 = Interrupt detected on port
*
* \note
* This API is available for the CAT1B and CAT1D devices.
*
* \funcusage
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_GPIO_GetSecureInterruptCause0(void)
{
    return (GPIO_SEC_INTR_CAUSE0);
}


/*******************************************************************************
* Function Name: Cy_GPIO_GetSecureInterruptCause1
****************************************************************************//**
*
* Returns the interrupt status for ports 32 to 63.
*
* \return
* 0 = Interrupt not detected on port
* 1 = Interrupt detected on port
*
* \note
* This API is available for the CAT1B and CAT1D devices.
*
* \funcusage
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_GPIO_GetSecureInterruptCause1(void)
{
    return (GPIO_SEC_INTR_CAUSE1);
}


/*******************************************************************************
* Function Name: Cy_GPIO_GetSecureInterruptCause2
****************************************************************************//**
*
* Returns the interrupt status for ports 64 to 95.
*
* \return
* 0 = Interrupt not detected on port
* 1 = Interrupt detected on port
*
* \note
* This API is available for the CAT1B and CAT1D devices.
*
* \funcusage
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_GPIO_GetSecureInterruptCause2(void)
{
    return (GPIO_SEC_INTR_CAUSE2);
}


/*******************************************************************************
* Function Name: Cy_GPIO_GetSecureInterruptCause3
****************************************************************************//**
*
* Returns the interrupt status for ports 96 to 127.
*
* \return
* 0 = Interrupt not detected on port
* 1 = Interrupt detected on port
*
* \note
* This API is available for the CAT1B and CAT1D devices.
*
* \funcusage
*
*******************************************************************************/
__STATIC_INLINE uint32_t Cy_GPIO_GetSecureInterruptCause3(void)
{
    return (GPIO_SEC_INTR_CAUSE3);
}
#endif /* CY_IP_MXS40SIOSS, CPUSS_CM33_0_SECEXT_PRESENT, CY_IP_MXS22IOSS */

/** \} group_gpio_functions_interrupt */

/** \} group_gpio_functions */

#if defined(__cplusplus)
}
#endif

#endif /* CY_IP_MXS40SIOSS, CY_IP_MXS40IOSS, CY_IP_MXS22IOSS */

#endif /* CY_GPIO_H */

/** \} group_gpio */

/* [] END OF FILE */
