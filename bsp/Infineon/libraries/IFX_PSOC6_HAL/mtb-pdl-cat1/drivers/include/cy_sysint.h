/***************************************************************************//**
* \file cy_sysint.h
* \version 1.80
*
* \brief
* Provides an API declaration of the SysInt driver
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
* \addtogroup group_sysint
* \{
* The SysInt driver provides an API to configure the device peripheral interrupts.
* It provides a lightweight interface to complement
* the <a href="https://www.keil.com/pack/doc/CMSIS/Core/html/group__NVIC__gr.html">CMSIS core NVIC API</a>.
* The provided functions are applicable for all cores in a device and they can
* be used to configure and connect device peripheral interrupts to one or more
* cores.
*
* The functions and other declarations used in this driver are in cy_sysint.h.
* You can include cy_pdl.h to get access to all functions
* and declarations in the PDL.
*
* \section group_sysint_vector_table Vector Table
* \subsection group_sysint_CM0_CM4 CM0+/CM4
* The vector table defines the entry addresses of the processor exceptions and
* the device specific interrupts. It is located at the start address of the flash
* and is copied by the startup code to RAM. The symbol code __Vectors is the
* address of the vector table in the startup code and the register SCB->VTOR
* holds the start address of the vector table. See \ref group_system_config_device_vector_table
* section for the implementation details.
* The default interrupt handler functions are defined as weak functions to a dummy handler
* in the startup file. The naming convention is \<interrupt_name\>_IRQHandler.
*
* Defining these in the user application allows the linker to place them in
* the vector table in flash/ROM. For example:
* \code
* void ioss_interrupts_gpio_0_IRQHandler(void)
* {
*     ...
* }
* \endcode
* And can be used like this:
* \snippet sysint/snippet/main.c snippet_Cy_SysInt_flashVT
* Using this method avoids the need for a RAM vector table. However in this scenario,
* interrupt handler re-location at run-time is not possible, unless the vector table is
* relocated to RAM.
*
* \subsection group_sysint_CM33 CM33
* CM33 with Security extension supports two vector tables, one for secure world and another
* for non-secure world. Secure interrupt vector table is placed in the secure ROM/FLASH, where as
* non-secure interrupt vector table is placed in the non-secure ROM/FLASH. In both scenarios,
* vector tables are copied by the startup code to secure and non-secure RAM respectively.
* The symbol code __s_vector_table is the address of the secure vector table and
* __ns_vector_table is for the non-secure world in the startup code. The register SCB->VTOR
* holds the start address of the vector table. See \ref group_system_config_device_vector_table
* section for the implementation details.
*
* CM33 without Security extension will support only non-secure interrupts.
*
* The default interrupt handler functions are defined to a dummy handler in the startup file.
* The naming convention is \<interrupt_name\>_IRQHandler.
*
* \subsection group_sysint_CM55 CM55
* CM55 is without Security extension and will support only non-secure interrupts. It is similar to CM33 non-secure part.
* Additionally CM55 core has support to block EWIC (External Wakeup Interrupt Controller). EWIC is a peripheral to the processor
* and it can be a source of wakeup in the system. EWIC block is disabled by default and needs to be enabled in order for the DS
* wakeup source to work.
*
* \subsection group_sysint_CM0_CM7 CAT1C CM0+/CM7
* The vector table defines the entry addresses of the processor exceptions and
* the device specific interrupts. Interrupt vector table is placed in the ROM/FLASH. The
* vector table is copied by the startup code to RAM. The symbol code __ramVectors is the address of the vector table.
* The register SCB->VTOR holds the start address of the vector table. See \ref group_system_config_device_vector_table
* section for the implementation details.
* Each system interrupt has to be mapped onto one out of eight external CPU interrupts. When a system interrupt is triggered, corresponding mapped
* CPU IRQ gets triggered which results in the execution of the default CPU IRQ handler. In this handler the system interrupt mapped to this
* CPU interrupt will be fetched and executed.
*
* The default CPU IRQ handler functions are defined as weak functions in the startup file.
* The naming convention followed is \<core\>_CpuIntr\<interrupt_number\>_Handler.
* Below is the code snippet.
* \code
* void Interrupt_Handler_Port0(void)
* {
*     ... //User interrupt handler
* }
* \endcode

* \snippet sysint/snippet/main.c snippet_Cy_SysInt_Init
*
* \section group_sysint_driver_usage Driver Usage
*
* \subsection group_sysint_initialization Initialization
*
* Interrupt numbers are defined in a device-specific header file, such as
* cy8c68237bz_ble.h, and are consistent with interrupt handlers defined in the
* vector table.
*
* To configure an interrupt, call Cy_SysInt_Init(). Populate
* the configuration structure (cy_stc_sysint_t) and pass it as a parameter
* along with the ISR address. This initializes the interrupt and
* instructs the CPU to jump to the specified ISR vector upon a valid trigger.
* For CM0+ core, the configuration structure (cy_stc_sysint_t)
* must specify the device interrupt source (cm0pSrc) that feeds into the CM0+ NVIC
* mux (intrSrc).
*
* For CM4/CM33/CM55 core, system interrupt source 'n' is connected to the
* corresponding IRQn. Deep-sleep capable interrupts are allocated to Deep Sleep
* capable IRQn channels.
*
* For CAT1C CM7/CM0+ core, the configuration structure (cy_stc_sysint_t) must specify
* system interrupt source, CPU IRQ and the CPU IRQ priority. The system interrupt source is mapped to bit 0-15 of intrSrc parameter
* and CPU IRQ is mapped to bit 16-31 of intrSrc parameter.
*
* For CM0+ core, deep Sleep wakeup-capability is determined by the CPUSS_CM0_DPSLP_IRQ_NR
* parameter, where the first N number of muxes (NvicMux0 ... NvicMuxN-1) have the
* capability to trigger Deep Sleep interrupts. A Deep Sleep capable interrupt source
* must be connected to one of these muxes to be able to trigger in Deep Sleep.
* Refer to the IRQn_Type definition in the device header.
*
* 1. For CPUSS_ver1 the CM0+ core supports up to 32 interrupt channels (IRQn 0-31). To allow all device
* interrupts to be routable to the NVIC of this core, there is a 240:1 multiplexer
* at each of the 32 NVIC channels.
*
* 2. For CPUSS_ver2 the CM0+ core supports up to 8 hardware interrupt channels (IRQn 0-7) and software-only
* interrupt channels (IRQn 8-15). The device has up to 1023 interrupts that can be connected to any of the
* hardware interrupt channels. In this structure, multiple interrupt sources can be connected
* simultaneously to one NVIC channel. The application must then query the interrupt source on the
* channel and service the active interrupt(s). The priority of these interrupts is determined by the
* interrupt number as defined in the cy_en_intr_t enum, where the lower number denotes higher priority
* over the higher number.
*
* \subsection group_sysint_enable Enable
*
* After initializing an interrupt, use the CMSIS Core
* <a href="https://www.keil.com/pack/doc/CMSIS/Core/html/group__NVIC__gr.html#ga530ad9fda2ed1c8b70e439ecfe80591f">NVIC_EnableIRQ()</a> function
* to enable it. Given an initialization structure named config,
* the function should be called as follows:
* \code
* NVIC_EnableIRQ(config.intrSrc)
* \endcode
*
* \subsection group_sysint_service Writing an interrupt service routine
*
* Servicing interrupts in the Peripheral Drivers should follow a prescribed
* recipe to ensure all interrupts are serviced and duplicate interrupts are not
* received. Any peripheral-specific register that must be written to clear the
* source of the interrupt should be written as soon as possible in the interrupt
* service routine. However, note that due to buffering on the output bus to the
* peripherals, the write clearing of the interrupt may be delayed. After performing
* the normal interrupt service that should respond to the interrupting
* condition, the interrupt register that was initially written to clear the
* register should be read before returning from the interrupt service routine.
* This read ensures that the initial write has been flushed out to the hardware.
* Note, no additional processing should be performed based on the result of this
* read, as this read is intended only to ensure the write operation is flushed.
*
* This final read may indicate a pending interrupt. What this means is that in
* the interval between when the write actually happened at the peripheral and
* when the read actually happened at the peripheral, an interrupting condition
* occurred. This is ok and a return from the interrupt is still the correct
* action. As soon as conditions warrant, meaning interrupts are enabled and
* there are no higher priority interrupts pending, the interrupt will be
* triggered again to service the additional condition.
*
* \section group_sysint_section_configuration_considerations Configuration Considerations
*
* Certain CM0+ <a href="https://www.keil.com/pack/doc/CMSIS/Core/html/group__NVIC__gr.html#ga7e1129cd8a196f4284d41db3e82ad5c8">NVIC IRQn</a>
* channels are reserved for system use:
* <table class="doxtable">
*   <tr><th>NVIC channel (\ref IRQn_Type)</th><th>Interrupt source (\ref cy_en_intr_t)</th><th>Purpose</th></tr>
*   <tr><td>#0 (NvicMux0_IRQn)</td><td>IPC Interrupt #0 (cpuss_interrupts_ipc_0_IRQn)</td><td>System Calls to ROM</td></tr>
*   <tr><td>#1 (NvicMux1_IRQn)</td><td>IPC Interrupt #3 (cpuss_interrupts_ipc_3_IRQn)</td><td>System IPC pipe in the default startup</td></tr>
* </table>
*
* \note For CPUSS_ver2, each NVIC channel can be shared between multiple interrupt sources.
* However it is not recommended to share the application NVIC channel with the reserved channels.
*
* \note In CAT1C, NvicMux0_IRQn and NvicMux1_IRQn are used by ROM and not meant for user.
*
* \section group_sysint_more_information More Information
*
* Refer to the technical reference manual (TRM) and the device datasheet.
*
* \section group_sysint_changelog Changelog
* <table class="doxtable">
*   <tr><th>Version</th><th>Changes</th><th>Reason for Change</th></tr>
*   <tr>
*     <td>1.80</td>
*     <td>API's Cy_SysInt_SetInterruptSource(), Cy_SysInt_GetInterruptSource(), Cy_SysInt_DisconnectInterruptSource(),
*         Cy_SysInt_SetNmiSource(), Cy_SysInt_GetNmiSource(), Cy_SysInt_SoftwareTrig(), Cy_SysInt_GetNvicConnection(),
*         Cy_SysInt_GetInterruptActive(), Cy_SysInt_InitExtIRQ(), Cy_SysInt_InitIntIRQ(), Cy_SysInt_Init(),
*         Cy_SysInt_SetVector(), Cy_SysInt_GetVector(), Cy_SysInt_SetSystemIrqVector(), Cy_SysInt_EnableSystemInt(), Cy_SysInt_DisableSystemInt()
*         modified.</td>
*     <td>New device support, Fix Coverity issues, Documentation enhancement.</td>
*   </tr>
*   <tr>
*     <td>1.70</td>
*     <td>Support for CAT1C, CAT1D.<br>Newly added API's Cy_SysInt_SetSystemIrqVector() to set the user ISR vector for the System Interrupt,
*         Cy_SysInt_GetSystemIrqVector() to get the address of the current user ISR vector for the System Interrupt,
*         Cy_SysInt_EnableSystemInt() to enable system interrupt, Cy_SysInt_DisableSystemInt() to disable system interrupt,
*         Cy_SysInt_InitExtIRQ() to initialize the referenced external interrupt by setting the CPU IRQ priority and the interrupt vector,
*         Cy_SysInt_InitIntIRQ() to initialize the referenced internal interrupt by setting the priority and the interrupt vector.</td>
*     <td>New devices support.</td>
*   </tr>

*   <tr>
*     <td>1.60</td>
*     <td>Support for CM33.</td>
*     <td>New devices support.</td>
*   </tr>
*   <tr>
*     <td>1.50</td>
*     <td>Fixed MISRA 2012 violations.</td>
*     <td>MISRA 2012 compliance.</td>
*   </tr>
*   <tr>
*     <td>1.40</td>
*     <td>Updated the CY_SYSINT_IS_PC_0 macro to access the protected register
*         for the secure CYB06xx7 devices via \ref group_pra driver.
*    </td>
*     <td>Added PSoC 64 devices support.</td>
*   </tr>
*   <tr>
*     <td>1.30.1</td>
*     <td>Minor documentation updates.</td>
*     <td>Documentation enhancement.</td>
*   </tr>
*   <tr>
*     <td>1.30</td>
*     <td>The Cy_SysInt_SetNmiSource is updated with Protection Context check for CM0+.</td>
*     <td>User experience enhancement.</td>
*   </tr>
*   <tr>
*     <td>1.20.1</td>
*     <td>The Vector Table section is extended with a code snippet.</td>
*     <td>Documentation enhancement.</td>
*   </tr>
*   <tr>
*     <td rowspan="3">1.20</td>
*     <td>Flattened the organization of the driver source code into the single source directory and the single include directory.</td>
*     <td>Driver library directory-structure simplification.</td>
*   </tr>
*   <tr>
*     <td>Added CPUSS_ver2 support to the following API functions:
*         - \ref Cy_SysInt_SetInterruptSource
*         - \ref Cy_SysInt_SetNmiSource
*         - \ref Cy_SysInt_GetNmiSource
*
*         Added new API functions:
*         - \ref Cy_SysInt_DisconnectInterruptSource
*         - \ref Cy_SysInt_GetNvicConnection
*         - \ref Cy_SysInt_GetInterruptActive
*
*         Deprecated following functions:
*         - Cy_SysInt_SetIntSource
*         - Cy_SysInt_GetIntSource
*         - Cy_SysInt_SetIntSourceNMI
*         - Cy_SysInt_GetIntSourceNMI
*     </td>
*     <td>New devices support.</td>
*   </tr>
*   <tr>
*     <td>Added register access layer. Use register access macros instead
*         of direct register access using dereferenced pointers.</td>
*     <td>Makes register access device-independent, so that the PDL does
*         not need to be recompiled for each supported part number.</td>
*   </tr>
*   <tr>
*     <td>1.10</td>
*     <td>Cy_SysInt_GetState() function is redefined to call NVIC_GetEnableIRQ()</td>
*     <td></td>
*   </tr>
*   <tr>
*     <td>1.0</td>
*     <td>Initial version</td>
*     <td></td>
*   </tr>
* </table>
*
* \defgroup group_sysint_macros Macros
* \defgroup group_sysint_globals Global variables
* \defgroup group_sysint_functions Functions
* \defgroup group_sysint_data_structures Data Structures
* \defgroup group_sysint_enums Enumerated Types
*/


#if !defined (CY_SYSINT_H)
#define CY_SYSINT_H

#include "cy_device.h"

#if defined (CY_IP_M33SYSCPUSS) || defined (CY_IP_M4CPUSS) || defined (CY_IP_M7CPUSS) || defined(CY_IP_M55APPCPUSS)

#include <stddef.h>
#include "cy_syslib.h"
#if defined(CY_DEVICE_SECURE) && defined(CY_DEVICE_PSOC6ABLE2)
    #include "cy_pra.h"
#endif /* defined(CY_DEVICE_SECURE) && defined(CY_DEVICE_PSOC6ABLE2) */
#include "cy_device_headers.h"

#if defined(__cplusplus)
extern "C" {
#endif

/***************************************
*       Global Variable
***************************************/

/**
* \addtogroup group_sysint_globals
* \{
*/

#if defined (CY_IP_M4CPUSS) || defined (CY_IP_M7CPUSS)
CY_MISRA_DEVIATE_BLOCK_START('MISRA C-2012 Rule 8.6', 2, \
'Coverity does not check the .S assembly files, the definition is a part of startup_psoc6_04_cm4.s file.');
extern const cy_israddress __Vectors[]; /**< Vector table in flash */
extern cy_israddress __ramVectors[]; /**< Relocated vector table in SRAM */
CY_MISRA_BLOCK_END('MISRA C-2012 Rule 8.6');
#endif /* CY_IP_M4CPUSS */

/** \} group_sysint_globals */


/***************************************
*       Global Interrupt
***************************************/

/**
* \addtogroup group_sysint_macros
* \{
*/

/** Driver major version */
#define CY_SYSINT_DRV_VERSION_MAJOR    1

/** Driver minor version */
#define CY_SYSINT_DRV_VERSION_MINOR    80

/** SysInt driver ID */
#define CY_SYSINT_ID CY_PDL_DRV_ID     (0x15U)

/** \} group_sysint_macros */


/***************************************
*       Enumeration
***************************************/

/**
* \addtogroup group_sysint_enums
* \{
*/

/**
* SysInt Driver error codes
*/
typedef enum
{
    CY_SYSINT_SUCCESS   = 0x0UL,                                      /**< Returned successful */
    CY_SYSINT_BAD_PARAM = CY_SYSINT_ID | CY_PDL_STATUS_ERROR | 0x1UL, /**< Bad parameter was passed */
} cy_en_sysint_status_t;

/** NMI connection input */
typedef enum
{
    CY_SYSINT_NMI1       = 1UL, /**< NMI source input 1 */
    CY_SYSINT_NMI2       = 2UL, /**< NMI source input 2 */
    CY_SYSINT_NMI3       = 3UL, /**< NMI source input 3 */
    CY_SYSINT_NMI4       = 4UL, /**< NMI source input 4 */
} cy_en_sysint_nmi_t;

/** \} group_sysint_enums */


/***************************************
*       Configuration Structure
***************************************/

/**
* \addtogroup group_sysint_data_structures
* \{
*/

/**
* Initialization configuration structure for a single interrupt channel
*/
typedef struct {
#if defined (CY_IP_M7CPUSS)
    uint32_t        intrSrc;        /**< Bit 0-15 indicate system interrupt and bit 16-31 will indicate the CPU IRQ */
#else /* CY_IP_M7CPUSS */
    IRQn_Type       intrSrc;        /**< Interrupt source */
#endif
#if (CY_CPU_CORTEX_M0P) && defined (CY_IP_M4CPUSS)
    cy_en_intr_t    cm0pSrc;        /**< Maps cm0pSrc device interrupt to intrSrc */
#endif /* CY_CPU_CORTEX_M0P */
    uint32_t        intrPriority;   /**< Interrupt priority number (Refer to __NVIC_PRIO_BITS) */
} cy_stc_sysint_t;

/** \} group_sysint_data_structures */


/***************************************
*              Constants
***************************************/

/** \cond INTERNAL */

    #define CY_INT_IRQ_BASE            (16U)    /**< Start location of interrupts in the vector table */
    #define CY_SYSINT_STATE_MASK       (1UL)    /**< Mask for interrupt state */
    #define CY_SYSINT_STIR_MASK        (0xFFUL) /**< Mask for software trigger interrupt register */
    #define CY_SYSINT_DISABLE          (0UL)    /**< Disable interrupt */
    #define CY_SYSINT_ENABLE           (1UL)    /**< Enable interrupt */
    #define CY_SYSINT_INT_STATUS_MSK   (0x7UL)

#if defined (CY_IP_M4CPUSS)
    /*(CY_IP_M4CPUSS_VERSION == 1u) */
    #define CY_SYSINT_CM0P_MUX_MASK    (0xFFUL) /**< CM0+ NVIC multiplexer mask */
    #define CY_SYSINT_CM0P_MUX_SHIFT   (2U)     /**< CM0+ NVIC multiplexer shift */
    #define CY_SYSINT_CM0P_MUX_SCALE   (3U)     /**< CM0+ NVIC multiplexer scaling value */
    #define CY_SYSINT_CM0P_MUX0        (0U)     /**< CM0+ NVIC multiplexer register 0 */
    #define CY_SYSINT_CM0P_MUX1        (1U)     /**< CM0+ NVIC multiplexer register 1 */
    #define CY_SYSINT_CM0P_MUX2        (2U)     /**< CM0+ NVIC multiplexer register 2 */
    #define CY_SYSINT_CM0P_MUX3        (3U)     /**< CM0+ NVIC multiplexer register 3 */
    #define CY_SYSINT_CM0P_MUX4        (4U)     /**< CM0+ NVIC multiplexer register 4 */
    #define CY_SYSINT_CM0P_MUX5        (5U)     /**< CM0+ NVIC multiplexer register 5 */
    #define CY_SYSINT_CM0P_MUX6        (6U)     /**< CM0+ NVIC multiplexer register 6 */
    #define CY_SYSINT_CM0P_MUX7        (7U)     /**< CM0+ NVIC multiplexer register 7 */
    #define CY_SYSINT_MUX_REG_MSK      (0x7UL)
#endif /* CY_IP_M4CPUSS */

    /* Parameter validation macros */
    #define CY_SYSINT_IS_PRIORITY_VALID(intrPriority)     ((uint32_t)(1UL << __NVIC_PRIO_BITS) > (intrPriority))
    #define CY_SYSINT_IS_VECTOR_VALID(userIsr)            (NULL != (userIsr))
    #define CY_SYSINT_IS_NMI_NUM_VALID(nmiNum)            (((nmiNum) == CY_SYSINT_NMI1) || \
                                                           ((nmiNum) == CY_SYSINT_NMI2) || \
                                                           ((nmiNum) == CY_SYSINT_NMI3) || \
                                                           ((nmiNum) == CY_SYSINT_NMI4))
#if defined (CY_IP_M4CPUSS)
    #if CY_CPU_CORTEX_M4 && defined(CY_DEVICE_SECURE) && defined(CY_DEVICE_PSOC6ABLE2)
        #define CY_SYSINT_IS_PC_0                         (0UL == _FLD2VAL(PROT_MPU_MS_CTL_PC, \
                                                           CY_PRA_REG32_GET(CY_PRA_INDX_PROT_MPU_MS_CTL)))
    #else
        #define CY_SYSINT_IS_PC_0                         (0UL == _FLD2VAL(PROT_MPU_MS_CTL_PC, PROT_MPU_MS_CTL(0U)))
    #endif
#endif /* CY_IP_M4CPUSS */
/** \endcond */


/***************************************
*       Function Prototypes
***************************************/

/**
* \addtogroup group_sysint_functions
* \{
*/


/*******************************************************************************
* Function Name: Cy_SysInt_Init
****************************************************************************//**
*
* \brief Initializes the referenced interrupt by setting the priority and the
* interrupt vector.
* In case of CM33 with Security Extension enabled, if this function is called
* from secure world then, the parameters are used to configure secure interrupt.
* If it is called form non-secure world then the parameters are used to configure
* non-secure interrupt. In case of CM33 without Security Extension, this function
* always configures the non-secure interrupt.
* In case of CM55, this function always configures the non-secure interrupt.
* In case of CM7/CM0+ it initializes the external system interrupt, maps it to CPU interrupt and
* registers the User ISR vector for the System Interrupt.
*
* Use the CMSIS core function NVIC_EnableIRQ(config.intrSrc) to enable the interrupt.
*
* \param config
* Interrupt configuration structure
*
* \param userIsr
* Address of the ISR
*
* \return
* Initialization status
*
* \note CM0+/CM4 <br/>
* The interrupt vector will be relocated only if the vector table was
* moved to __ramVectors in SRAM. Otherwise it is ignored.
*
* \note CM33<br/>
* The interrupt vector will be relocated only if the vector table was
* moved to __s_vector_table_rw and __ns_vector_table_rw for secure and
* non-secure world respectively.
*
* \note CM55<br/>
* The interrupt vector will be relocated only if the vector table was
* moved to __ns_vector_table_rw non-secure world.
*
* \funcusage
* \snippet sysint/snippet/main.c snippet_Cy_SysInt_Init
*
*******************************************************************************/
cy_en_sysint_status_t Cy_SysInt_Init(const cy_stc_sysint_t* config, cy_israddress userIsr);


/*******************************************************************************
* Function Name: Cy_SysInt_SetVector
****************************************************************************//**
*
* \brief Changes the ISR vector for the interrupt.
*
* CM0+/CM4:<br/>
* This function relies on the assumption that the vector table is
* relocated to __ramVectors[RAM_VECTORS_SIZE] in SRAM. Otherwise it will
* return the address of the default ISR location in the flash vector table.
*
* CM0+/CM7:<br/>
* This function relies on the assumption that the vector table is
* relocated to __ramVectors[RAM_VECTORS_SIZE] in SRAM. Otherwise it will
* return the address of the default ISR location in the flash vector table.
* This function is applicable only to User Interrupts (NvicMux0_IRQn - NvicMux7_IRQn)
* and System Interrupts (Internal0_IRQn - Internal0_IRQn).
*
* CM33:<br/>
* When called from secure world. this function relies on the assumption that the
* vector table is relocated to __s_vector_table_rw[] in secure SRAM. Otherwise it will
* return the address of the default ISR location in the secure flash/ROM vector table.
*
* When called from non-secure world. this function relies on the assumption that
* the vector table is relocated to __ns_vector_table_rw[] in non-secure SRAM.
* Otherwise it will return the address of the default ISR location in the non-secure
* flash/ROM vector table.
*
* CM55:<br/>
* This function relies on the assumption that
* the vector table is relocated to __ns_vector_table_rw[] in non-secure SRAM.
* Otherwise it will return the address of the default ISR location in the non-secure
* flash/ROM vector table.
*
* Use the CMSIS core function NVIC_EnableIRQ(config.intrSrc) to enable the interrupt.
* \param IRQn
* Interrupt source
*
* \param userIsr
* Address of the ISR to set in the interrupt vector table
*
* \return
 * Previous address of the ISR in the interrupt vector table
*
* \note For CM0+, this function sets the interrupt vector for the interrupt
* channel on the NVIC.
*
* \note In case of CM33 with Security Extension enabled, if this function is called
* from secure world then, it sets the interrupt vector for the secure world.
* If it is called form non-secure world then it sets the interrupt vector for the
* non-secure world.
*
* \funcusage
* \snippet sysint/snippet/main.c snippet_Cy_SysInt_SetVector
*
*******************************************************************************/
cy_israddress Cy_SysInt_SetVector(IRQn_Type IRQn, cy_israddress userIsr);


/*******************************************************************************
* Function Name: Cy_SysInt_GetVector
****************************************************************************//**
*
* \brief Gets the address of the current ISR vector for the interrupt.
*
* CM0+/CM4:<br/>
* This function relies on the assumption that the vector table is
* relocated to __ramVectors[RAM_VECTORS_SIZE] in SRAM. Otherwise it will
* return the address of the default ISR location in the flash vector table.
*
* CM0+/CM7:<br/>
* This function relies on the assumption that the vector table is
* relocated to __ramVectors[RAM_VECTORS_SIZE] in SRAM. Otherwise it will
* return the address of the default ISR location in the flash vector table.
* This function is applicable only to User Interrupts (NvicMux0_IRQn - NvicMux7_IRQn)
* and System Interrupts (Internal0_IRQn - Internal0_IRQn).
*
* CM33:<br/>
* When called from the secure world, this function relies on the assumption that
* the vector table is relocated to __ns_vector_table_rw[] in non-secure SRAM.
* Otherwise it will return the address of the default ISR location in the
* flash/ROM vector table.
*
* CM55:<br/>
* This function relies on the assumption that
* the vector table is relocated to __ns_vector_table_rw[] in non-secure SRAM.
* Otherwise it will return the address of the default ISR location in the
* flash/ROM vector table.
*
* \param IRQn
* Interrupt source
*
* \return
* Address of the ISR in the interrupt vector table
*
* \note CM0+:<br/> This function returns the interrupt vector for the interrupt
* channel on the NVIC.
*
* \note CM33:<br/>In case of CM33 with Security Extension enabled, if this function is called
* from secure world then, it returns the interrupt vector for the secure world.
* If it is called form non-secure world then it returns the interrupt vector
* for the non-secure world.
*
* \funcusage
* \snippet sysint/snippet/main.c snippet_Cy_SysInt_SetVector
*
*******************************************************************************/
cy_israddress Cy_SysInt_GetVector(IRQn_Type IRQn);


#if (((CY_CPU_CORTEX_M0P) || defined (CY_IP_M7CPUSS) || defined (CY_DOXYGEN)) && !defined(CY_IP_M0SECCPUSS))
/*******************************************************************************
* Function Name: Cy_SysInt_SetInterruptSource
****************************************************************************//**
*
* \brief Configures the interrupt selection for the specified NVIC channel.
*
* To disconnect the interrupt source from the NVIC channel
* use the \ref Cy_SysInt_DisconnectInterruptSource.
*
* \param IRQn
* NVIC channel number connected to the CPU core.
*
* \param devIntrSrc
* Device interrupt to be routed to the NVIC channel.
*
* \note This function is available for CM0+/CM7 core only.
*
* \funcusage
* \snippet sysint/snippet/main.c snippet_Cy_SysInt_SetInterruptSource
*
*******************************************************************************/
void Cy_SysInt_SetInterruptSource(IRQn_Type IRQn, cy_en_intr_t devIntrSrc);

#if defined(CY_IP_M4CPUSS) && (CY_CPU_CORTEX_M0P) || defined (CY_DOXYGEN)
/*******************************************************************************
* Function Name: Cy_SysInt_GetInterruptSource
****************************************************************************//**
*
* \brief Gets the interrupt source of the NVIC channel.
*
* \param IRQn
* NVIC channel number connected to the CPU core
*
* \return
* Device interrupt connected to the NVIC channel. A returned value of
* "disconnected_IRQn" indicates that the interrupt source is disconnected.
*
* \note This function is available for CM0+ core only.
*
* \note This function supports only devices using CPUSS_ver1. For all
* other devices, use the Cy_SysInt_GetNvicConnection() function.
*
* \funcusage
* \snippet sysint/snippet/main.c snippet_Cy_SysInt_SetInterruptSource
*
*******************************************************************************/
cy_en_intr_t Cy_SysInt_GetInterruptSource(IRQn_Type IRQn);
#endif

/*******************************************************************************
* Function Name: Cy_SysInt_GetNvicConnection
****************************************************************************//**
*
* \brief Gets the NVIC channel to which the interrupt source is connected.
*
* \param devIntrSrc
* Device interrupt that is potentially connected to the NVIC channel.
*
* \return
* NVIC channel number connected to the CPU core. A returned value of
* "unconnected_IRQn" indicates that the interrupt source is disabled.
*
* \note This function is available for CM0+/CM7 core only.
*
* \note This function supports only devices using CPUSS_ver2 or higher.
*
* \funcusage
* \snippet sysint/snippet/main.c snippet_Cy_SysInt_SetInterruptSource
*
*******************************************************************************/
IRQn_Type Cy_SysInt_GetNvicConnection(cy_en_intr_t devIntrSrc);


/*******************************************************************************
* Function Name: Cy_SysInt_GetInterruptActive
****************************************************************************//**
*
* \brief Gets the highest priority active interrupt for the selected NVIC channel.
*
* The priority of the interrupt in a given channel is determined by the index
* value of the interrupt in the cy_en_intr_t enum. The lower the index, the
* higher the priority. E.g. Consider a case where an interrupt source with value
* 29 and an interrupt source with value 46 both source the same NVIC channel. If
* both are active (triggered) at the same time, calling Cy_SysInt_GetInterruptActive()
* will return 29 as the active interrupt.
*
* \param IRQn
* NVIC channel number connected to the CPU core
*
* \return
* Device interrupt connected to the NVIC channel. A returned value of
* "disconnected_IRQn" indicates that there are no active (pending) interrupts
* on this NVIC channel.
*
* \note This function is available for CM0+/CM7 core only.
*
* \note This function supports only devices using CPUSS_ver2 or higher.
*
* \funcusage
* \snippet sysint/snippet/main.c snippet_Cy_SysInt_GetInterruptActive
*
*******************************************************************************/
cy_en_intr_t Cy_SysInt_GetInterruptActive(IRQn_Type IRQn);
#endif


#if defined(CY_IP_M4CPUSS) && (CY_CPU_CORTEX_M0P) || defined (CY_DOXYGEN)
/*******************************************************************************
* Function Name: Cy_SysInt_DisconnectInterruptSource
****************************************************************************//**
*
* \brief Disconnect the interrupt source from the specified NVIC channel.
*
* \param IRQn
* NVIC channel number connected to the CPU core.
* This parameter is ignored for devices using CPUSS_ver2.
*
* \param devIntrSrc
* Device interrupt routed to the NVIC channel.
* This parameter is ignored for devices using CPUSS_ver1.
*
* \note This function is available for CM0+ core only.
*
* \funcusage
* \snippet sysint/snippet/main.c snippet_Cy_SysInt_DisconnectInterruptSource
*
*******************************************************************************/
void Cy_SysInt_DisconnectInterruptSource(IRQn_Type IRQn, cy_en_intr_t devIntrSrc);
#endif

#if defined (CY_IP_M7CPUSS) || defined (CY_DOXYGEN)
/*******************************************************************************
* Function Name: Cy_SysInt_InitExtIRQ
****************************************************************************//**
*
* \brief Initializes the referenced external interrupt by setting the CPU IRQ priority and the
* interrupt vector.
*
* Use the CMSIS core function NVIC_EnableIRQ(config.intrSrc) to enable the interrupt.
*
* \param config
* Interrupt configuration structure
*
* \param userIsr
* Address of the ISR
*
* \note This function is available for CAT1C CM0/CM7 core.
*
* \return
* Initialization status
*
* \note CM0+/CM7 <br/>
* The interrupt vector will be relocated only if the vector table was
* moved to __ramVectors in SRAM. Otherwise it is ignored.
*
*******************************************************************************/
cy_en_sysint_status_t Cy_SysInt_InitExtIRQ(const cy_stc_sysint_t* config, cy_israddress userIsr);


/*******************************************************************************
* Function Name: Cy_SysInt_InitIntIRQ
****************************************************************************//**
*
* \brief Initializes the referenced internal interrupt by setting the priority and the
* interrupt vector.
*
* Use the CMSIS core function NVIC_EnableIRQ(config.intrSrc) to enable the interrupt.
*
* \param config
* Interrupt configuration structure
*
* \param userIsr
* Address of the ISR
*
* \note This function is available for CAT1C CM0/CM7 core.
*
* \return
* Initialization status
*
* \note CM0+/CM7 <br/>
* The interrupt vector will be relocated only if the vector table was
* moved to __ramVectors in SRAM. Otherwise it is ignored.
*
*******************************************************************************/
cy_en_sysint_status_t Cy_SysInt_InitIntIRQ(const cy_stc_sysint_t* config, cy_israddress userIsr);


/*******************************************************************************
* Function Name: Cy_SysInt_SetSystemIrqVector
****************************************************************************//**
*
* \brief Sets the User ISR vector for the System Interrupt.
*
* \param sysIntSrc
* Interrupt source
*
* \note This function is available for CAT1C CM0/CM7 core.
*
* \param userIsr
* Address of the ISR to set in the interrupt vector table
*
* \return none
*
*******************************************************************************/
void  Cy_SysInt_SetSystemIrqVector(cy_en_intr_t sysIntSrc, cy_israddress userIsr);


/*******************************************************************************
* Function Name: Cy_SysInt_GetSystemIrqVector
****************************************************************************//**
*
* \brief Gets the address of the current user ISR vector for the System Interrupt.
*
* \param sysIntSrc
* Interrupt source
*
* \note This function is available for CAT1C CM0/CM7 core.
*
* \return
* Address of the ISR in the interrupt vector table
*
*******************************************************************************/
cy_israddress  Cy_SysInt_GetSystemIrqVector(cy_en_intr_t sysIntSrc);


/*******************************************************************************
* Function Name: Cy_SysInt_EnableSystemInt
****************************************************************************//**
*
* \brief Enable system interrupt.
*
* \param sysIntSrc
* System interrupt source to be enabled.
*
* \note This function is available for CAT1C CM0/CM7 core.
*
* \return none
*
*******************************************************************************/
void Cy_SysInt_EnableSystemInt(cy_en_intr_t sysIntSrc);


/*******************************************************************************
* Function Name: Cy_SysInt_DisableSystemInt
****************************************************************************//**
*
* \brief Disable system interrupt.
*
* \param sysIntSrc
* System interrupt source to be disabled.
*
* \note This function is available for CAT1C CM0/CM7 core.
*
* \return none
*
*******************************************************************************/
void Cy_SysInt_DisableSystemInt(cy_en_intr_t sysIntSrc);
#endif

/***************************************
*           Functions
***************************************/

/*******************************************************************************
* Function Name: Cy_SysInt_SetNmiSource
****************************************************************************//**
*
* \brief Sets the interrupt source of the CPU core NMI.
*
* The interrupt source must be a positive number. Setting the value to
* "unconnected_IRQn" or "disconnected_IRQn" disconnects the interrupt source
* from the NMI. Depending on the device, the number of interrupt sources that
* can provide the NMI trigger signal to the core can vary.
*
* \param nmiNum
* NMI source number.
* CPUSS_ver2 allows up to 4 sources to trigger the core NMI.
* CPUSS_ver1 allows only one source to trigger the core NMI and
*  the specified NMI number is ignored.
*
* \param devIntrSrc
* Interrupt source. This parameter can either be of type cy_en_intr_t or IRQn_Type
* for CM0+/CM7 and CM4/CM33/CM55 respectively.
*
* \note CM0+ may call this function only at PC=0, CM4 may set its NMI handler at any PC.
* \note The CM0+ NMI is used for performing system calls that execute out of ROM.
*
* \funcusage
* \snippet sysint/snippet/main.c snippet_Cy_SysInt_SetNmiSource
*
*******************************************************************************/
CY_MISRA_FP_BLOCK_START('MISRA C-2012 Rule 8.6', 2, 'Only one prototype will be picked for compilation');
CY_MISRA_FP_BLOCK_START('MISRA C-2012 Rule 8.5', 2, 'Only one prototype will be picked for compilation');
CY_MISRA_FP_BLOCK_START('MISRA C-2012 Rule 8.3', 2, 'Only one prototype will be picked for compilation');
#if (((CY_CPU_CORTEX_M0P) || defined (CY_IP_M7CPUSS) || defined (CY_DOXYGEN)) && !defined(CY_IP_M0SECCPUSS))
void Cy_SysInt_SetNmiSource(cy_en_sysint_nmi_t nmiNum, cy_en_intr_t devIntrSrc);
#else
void Cy_SysInt_SetNmiSource(cy_en_sysint_nmi_t nmiNum, IRQn_Type intrSrc);
#endif

/*******************************************************************************
* Function Name: Cy_SysInt_GetIntSourceNMI
****************************************************************************//**
*
* \brief Gets the interrupt source of the CPU core NMI for the given NMI source
* number.
*
* \param nmiNum
* NMI source number.
* CPUSS_ver2 allows up to 4 sources to trigger the core NMI (i.e. #1, 2, 3, 4).
* CPUSS_ver1 allows only 1 source to trigger the core NMI (i.e #1).
*
* \return
* Interrupt Source. This parameter can either be of type cy_en_intr_t or IRQn_Type
* for CM0+/CM7 and CM4/CM33/CM55 respectively.
*
* \funcusage
* \snippet sysint/snippet/main.c snippet_Cy_SysInt_SetNmiSource
*
*******************************************************************************/
#if (((CY_CPU_CORTEX_M0P) || defined(CY_IP_M7CPUSS) || defined (CY_DOXYGEN)) && !defined(CY_IP_M0SECCPUSS))
cy_en_intr_t Cy_SysInt_GetNmiSource(cy_en_sysint_nmi_t nmiNum);
#else
IRQn_Type Cy_SysInt_GetNmiSource(cy_en_sysint_nmi_t nmiNum);
#endif
CY_MISRA_BLOCK_END('MISRA C-2012 Rule 8.3');
CY_MISRA_BLOCK_END('MISRA C-2012 Rule 8.5');
CY_MISRA_BLOCK_END('MISRA C-2012 Rule 8.6');


#if !(defined(CY_CPU_CORTEX_M0P) && (CY_CPU_CORTEX_M0P)) && !(defined(CY_IP_M7CPUSS))
/*******************************************************************************
* Function Name: Cy_SysInt_SoftwareTrig
****************************************************************************//**
*
* \brief Triggers an interrupt using software (Not applicable for CM0+).
*
* \param IRQn
* Interrupt source
*
* \funcusage
* \snippet sysint/snippet/main.c snippet_Cy_SysInt_SoftwareTrig
*
* \note Only privileged software can enable unprivileged access to the
* Software Trigger Interrupt Register (STIR). This function is available for CAT1A, CAT1B and CAT1D devices.
*
*
*******************************************************************************/
void Cy_SysInt_SoftwareTrig(IRQn_Type IRQn);
#endif


/** \} group_sysint_functions */

/** \cond INTERNAL */

/***************************************
*       Deprecated functions
***************************************/

/*******************************************************************************
* Function Name: Cy_SysInt_GetState
****************************************************************************//**
*
* This function is deprecated. It invokes the NVIC_GetEnableIRQ() function.
*
*******************************************************************************/
#define Cy_SysInt_GetState NVIC_GetEnableIRQ


/*******************************************************************************
* Function Name: Cy_SysInt_SetIntSource
****************************************************************************//**
*
* This function is deprecated. It invokes the Cy_SysInt_SetInterruptSource() function.
*
*******************************************************************************/
#define Cy_SysInt_SetIntSource(intrSrc, devIntrSrc) Cy_SysInt_SetInterruptSource(intrSrc, devIntrSrc)


/*******************************************************************************
* Function Name: Cy_SysInt_GetIntSource
****************************************************************************//**
*
* This function is deprecated. It invokes the Cy_SysInt_GetInterruptSource() function.
*
*******************************************************************************/
#define Cy_SysInt_GetIntSource(intrSrc) Cy_SysInt_GetInterruptSource(intrSrc)


/*******************************************************************************
* Function Name: Cy_SysInt_SetIntSourceNMI
****************************************************************************//**
*
* This function is deprecated. It invokes the Cy_SysInt_SetNmiSource() function.
*
*******************************************************************************/
#define Cy_SysInt_SetIntSourceNMI(srcParam) Cy_SysInt_SetNmiSource(CY_SYSINT_NMI1, srcParam)


/*******************************************************************************
* Function Name: Cy_SysInt_GetIntSourceNMI
****************************************************************************//**
*
* This function is deprecated. It invokes the Cy_SysInt_GetNmiSource() function.
*
*******************************************************************************/
#define Cy_SysInt_GetIntSourceNMI() Cy_SysInt_GetNmiSource(CY_SYSINT_NMI1)

/** \endcond */

#if defined(__cplusplus)
}
#endif

#endif /* CY_IP_M33SYSCPUSS */

#endif /* CY_SYSINT_H */

/** \} group_sysint */

/* [] END OF FILE */
