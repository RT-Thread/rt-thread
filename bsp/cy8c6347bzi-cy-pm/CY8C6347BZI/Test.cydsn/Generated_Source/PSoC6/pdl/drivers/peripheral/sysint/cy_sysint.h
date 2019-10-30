/***************************************************************************//**
* \file cy_sysint.h
* \version 1.20
*
* \brief
* Provides an API declaration of the SysInt driver
*
********************************************************************************
* \copyright
* Copyright 2016-2018, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
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
* You can include cy_pdl.h (ModusToolbox only) to get access to all functions 
* and declarations in the PDL. 
*
* \section group_sysint_vector_table Vector Table
* The vector table defines the entry addresses of the processor exceptions and
* the device specific interrupts. It is located at the start address of the flash
* and is copied by the startup code to RAM. The symbol code __Vectors is the
* address of the vector table in the startup code and the register SCB->VTOR
* holds the start address of the vector table. See \ref group_system_config_device_vector_table
* section for the implementation details.
*
* The default interrupt handler functions are defined as weak functions to a dummy handler
* in the startup file. The naming convention for the interrupt handler names are
* <interrupt_name>_IRQHandler. Defining these in the user application will allow
* the linker to place them in the vector table in flash. For example:
* \code
* void scb_0_interrupt_IRQHandler(void)
* {
*     ...
* }
\endcode
* Using this method avoids the need for a RAM vector table. However in this scenario, 
* interrupt handler re-location at run-time is not possible, unless the vector table is
* relocated to RAM.

* \section group_sysint_driver_usage Driver Usage
*
* \subsection group_sysint_initialization Initialization
*
* Interrupt numbers are defined in a device-specific header file, such as 
* cy8c68237bz_ble.h, and is consistent with interrupt handlers defined in the 
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
* For CM4 core, system interrupt source 'n' is connected to the 
* corresponding IRQn. Deep-sleep capable interrupts are allocated to Deep Sleep
* capable IRQn channels. 
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
* \section group_sysint_more_information More Information
*
* Refer to the technical reference manual (TRM) and the device datasheet.
*
* \section group_sysint_MISRA MISRA-C Compliance
* <table class="doxtable">
*   <tr>
*     <th>MISRA Rule</th>
*     <th>Rule Class (Required/Advisory)</th>
*     <th>Rule Description</th>
*     <th>Description of Deviation(s)</th>
*   </tr>
*   <tr>
*     <td>8.12</td>
*     <td>R</td>
*     <td>Array declared with unknown size.</td>
*     <td>
*         __Vectors and __ramVectors arrays can have the different size depend on the selected device.</td>
*   </tr>
* </table>
*
* \section group_sysint_changelog Changelog
* <table class="doxtable">
*   <tr><th>Version</th><th>Changes</th><th>Reason for Change</th></tr>
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


#if !defined(CY_SYSINT_H)
#define CY_SYSINT_H

#include <stddef.h>
#include "cy_device.h"
#include "cy_syslib.h"
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

extern const cy_israddress __Vectors[]; /**< Vector table in flash */
extern cy_israddress __ramVectors[]; /**< Relocated vector table in SRAM */

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
#define CY_SYSINT_DRV_VERSION_MINOR    20

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
    IRQn_Type       intrSrc;        /**< Interrupt source */
#if (CY_CPU_CORTEX_M0P)
    cy_en_intr_t    cm0pSrc;        /**< Maps cm0pSrc device interrupt to intrSrc */
#endif
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

    /* Parameter validation macros */
    #define CY_SYSINT_IS_PRIORITY_VALID(intrPriority)     ((uint32_t)(1UL << __NVIC_PRIO_BITS) > (intrPriority))
    #define CY_SYSINT_IS_VECTOR_VALID(userIsr)            (NULL != (userIsr))
    #define CY_SYSINT_IS_NMI_NUM_VALID(nmiNum)            (((nmiNum) == CY_SYSINT_NMI1) || \
                                                           ((nmiNum) == CY_SYSINT_NMI2) || \
                                                           ((nmiNum) == CY_SYSINT_NMI3) || \
                                                           ((nmiNum) == CY_SYSINT_NMI4))
/** \endcond */


/***************************************
*       Function Prototypes
***************************************/

/**
* \addtogroup group_sysint_functions
* \{
*/

cy_en_sysint_status_t Cy_SysInt_Init(const cy_stc_sysint_t* config, cy_israddress userIsr);
cy_israddress Cy_SysInt_SetVector(IRQn_Type IRQn, cy_israddress userIsr);
cy_israddress Cy_SysInt_GetVector(IRQn_Type IRQn);

#if (CY_CPU_CORTEX_M0P) || defined (CY_DOXYGEN)
    void Cy_SysInt_SetInterruptSource(IRQn_Type IRQn, cy_en_intr_t devIntrSrc);
    cy_en_intr_t Cy_SysInt_GetInterruptSource(IRQn_Type IRQn);
    IRQn_Type Cy_SysInt_GetNvicConnection(cy_en_intr_t devIntrSrc);
    cy_en_intr_t Cy_SysInt_GetInterruptActive(IRQn_Type IRQn);
    void Cy_SysInt_DisconnectInterruptSource(IRQn_Type IRQn, cy_en_intr_t devIntrSrc);
#endif
#if (!CY_CPU_CORTEX_M0P) || defined (CY_DOXYGEN)
    __STATIC_INLINE void Cy_SysInt_SetNmiSource(cy_en_sysint_nmi_t nmiNum, IRQn_Type intrSrc);
    __STATIC_INLINE IRQn_Type Cy_SysInt_GetNmiSource(cy_en_sysint_nmi_t nmiNum);
#else
    __STATIC_INLINE void Cy_SysInt_SetNmiSource(cy_en_sysint_nmi_t nmiNum, cy_en_intr_t devIntrSrc);
    __STATIC_INLINE cy_en_intr_t Cy_SysInt_GetNmiSource(cy_en_sysint_nmi_t nmiNum);
#endif
#if (!CY_CPU_CORTEX_M0P) || defined (CY_DOXYGEN)
    __STATIC_INLINE void Cy_SysInt_SoftwareTrig(IRQn_Type IRQn);
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
* \param intrSrc
* Interrupt source. This parameter can either be of type cy_en_intr_t or IRQn_Type
* based on the selected core.
*
* \note The CM0+ NMI is used for performing system calls that execute out of ROM.
* Hence modification of the NMI source is strongly discouraged for this core.
*
* \funcusage
* \snippet sysint\1.20\snippet\main.c snippet_Cy_SysInt_SetNmiSource
*
*******************************************************************************/
#if (!CY_CPU_CORTEX_M0P) || defined (CY_DOXYGEN)
__STATIC_INLINE void Cy_SysInt_SetNmiSource(cy_en_sysint_nmi_t nmiNum, IRQn_Type intrSrc)
#else
__STATIC_INLINE void Cy_SysInt_SetNmiSource(cy_en_sysint_nmi_t nmiNum, cy_en_intr_t devIntrSrc)
#endif
{
    CY_ASSERT_L3(CY_SYSINT_IS_NMI_NUM_VALID(nmiNum));
    
    if (CY_CPUSS_V1)
    {
        nmiNum = CY_SYSINT_NMI1; /* For CPUSS_ver1 the NMI number is 1 */
    }
    
    #if (CY_CPU_CORTEX_M0P)
        CPUSS_CM0_NMI_CTL((uint32_t)nmiNum - 1UL) = (uint32_t)devIntrSrc;
    #else
        CPUSS_CM4_NMI_CTL((uint32_t)nmiNum - 1UL) = (uint32_t)intrSrc;
    #endif
}


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
* based on the selected core.
*
* \funcusage
* \snippet sysint\1.20\snippet\main.c snippet_Cy_SysInt_SetNmiSource
*
*******************************************************************************/
#if (!CY_CPU_CORTEX_M0P) || defined (CY_DOXYGEN)
__STATIC_INLINE IRQn_Type Cy_SysInt_GetNmiSource(cy_en_sysint_nmi_t nmiNum)
#else
__STATIC_INLINE cy_en_intr_t Cy_SysInt_GetNmiSource(cy_en_sysint_nmi_t nmiNum)
#endif
{
    CY_ASSERT_L3(CY_SYSINT_IS_NMI_NUM_VALID(nmiNum));
    
    if (CY_CPUSS_V1)
    {
        nmiNum = CY_SYSINT_NMI1; /* For CPUSS_ver1 the NMI number is 1 */
    }

    #if (CY_CPU_CORTEX_M0P)
        return ((cy_en_intr_t)(CPUSS_CM0_NMI_CTL((uint32_t)nmiNum - 1UL)));
    #else
        return ((IRQn_Type)(CPUSS_CM4_NMI_CTL((uint32_t)nmiNum - 1UL)));
    #endif
}


#if (!CY_CPU_CORTEX_M0P) || defined (CY_DOXYGEN)

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
* \snippet sysint\1.20\snippet\main.c snippet_Cy_SysInt_SoftwareTrig
*
* \note Only privileged software can enable unprivileged access to the
* Software Trigger Interrupt Register (STIR).
*
*******************************************************************************/
__STATIC_INLINE void Cy_SysInt_SoftwareTrig(IRQn_Type IRQn)
{
    NVIC->STIR = (uint32_t)IRQn & CY_SYSINT_STIR_MASK;
}

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

#endif /* CY_SYSINT_H */

/** \} group_sysint */

/* [] END OF FILE */
