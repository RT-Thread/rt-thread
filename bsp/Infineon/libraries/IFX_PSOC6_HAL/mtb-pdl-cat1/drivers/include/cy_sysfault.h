/***************************************************************************//**
* \file cy_sysfault.h
* \version 1.0
*
* \brief
* Provides an API declaration of the SysFault driver.
*
********************************************************************************
* \copyright
* Copyright (c) (2020-2022), Cypress Semiconductor Corporation (an Infineon company) or
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
* \addtogroup group_sysfault
* \{
*
* The SysFault driver provides an API to configure the Fault reporting structure.
* The functions and other declarations used in this driver are in cy_sysfault.h.
* You can include cy_pdl.h to get access to all functions and declarations in the PDL.
* This driver is only available for CAT1C devices.
*
* The Fault subsystem contains information about faults that occur in the system.
* The fault subsystem captures only faults and it does not take any action to correct it.
* The subsystem can cause a reset, give a pulse indication, or trigger another peripheral.
* CAT1C uses a centralized fault report structure. The centralized nature allows for a
* system-wide consistent handling of faults, which simplifies software development as
* follows only a single fault interrupt handler is required. The fault report structure
* provides the fault source and additional fault-specific information from a single set
* of memory mapped input/output (MMIO) registers, no iterative search is required for
* the fault source and fault information.
* All pending faults are available from a single set of MMIO registers. Below is the block
* diagram.
* \image html fault.png
*
* Fault IP provides fault report structure. Fault report structures capture faults.
* The number of fault report structures is specified by a design time configuration
* parameter (FAULT_NR). In CAT1C there are four instances of fault structures, each fault
* report structure has a dedicated set of MMIO control and status registers and captures
* a single fault. A fault report structure provides the fault source and additional fault
* specific information from a single set of MMIO registers. The fault structures capture
* faults like MPU/SMPU/PPI protection violations, peripheral specific errors, memory
* controller specific errors. E.g., SRAM controller ECC errors,
* FLASH controller read while program and ECC errors, Processor tightly coupled
* memory (TCM) ECC errors.
*
* System fault will be captured by fault report structures. A fault report structure
* provides the fault source and additional fault specific information from a single
* set of MMIO registers.
* The captured fault information includes:
* * A validity bit field that indicates a fault is captured.
* * A fault index that identifies the fault source.
* * Additional fault information describing fault specifics.
*
* \section group_sysfault_configuration Configuration Considerations
*
* Fault configuration includes clearing the existing fault status, enabling fault source,
* setting interrupt mask, and fault initialization.
* Below is the code snippet for the fault configuration.
* \snippet sysfault/snippet/main.c snippet_Cy_SysFault_Config
*
* Once the configured fault occurs, the interrupt handler will be triggered where the
* fault information can be captured.
* Below is the code snippet that can be part of a interrupt handler.
* \snippet sysfault/snippet/main.c snippet_Cy_SysFault_Handle_Fault
*
* \section group_sysfault_section_more_information More Information
*
* For more information on the System Fault, refer to the technical reference
* manual (TRM).
*
* \section group_sysfault_changelog Changelog
* <table class="doxtable">
*   <tr><th>Version</th><th>Changes</th><th>Reason for Change</th></tr>
*   <tr>
*     <td>1.0</td>
*     <td>Initial version</td>
*     <td></td>
*   </tr>
* </table>
*
* \defgroup group_sysfault_macros Macros
* \defgroup group_sysfault_enums Enums
* \defgroup group_sysfault_data_structures Data Structures
* \defgroup group_sysfault_functions Functions
*
*/

#if !defined(CY_SYSFAULT_H)
#define CY_SYSFAULT_H

#include "cy_device.h"

#if defined (CY_IP_M7CPUSS)

#include "cy_syslib.h"
#include "cy_device_headers.h"

#if defined(__cplusplus)
extern "C" {
#endif


/*******************************************************************************
*       Function Constants
*******************************************************************************/

/**
* \addtogroup group_sysfault_macros
* \{
*/

/** Driver major version */
#define CY_SYSFAULT_DRV_VERSION_MAJOR    1

/** Driver minor version */
#define CY_SYSFAULT_DRV_VERSION_MINOR    0

/** Driver ID */
#define CY_SYSFAULT_ID CY_PDL_DRV_ID     (0x76U)

/** \cond INTERNAL */

/* Macro to validate parameters in Cy_SysFault_GetFaultData() function */
#define CY_SYSFAULT_IS_DATA_SET_VALID(dataSet)     (((dataSet) == CY_SYSFAULT_DATA0) || \
                                                    ((dataSet) == CY_SYSFAULT_DATA1) || \
                                                    ((dataSet) == CY_SYSFAULT_DATA2) || \
                                                    ((dataSet) == CY_SYSFAULT_DATA3))

/* Macro to validate parameters in Cy_SysFault_GetPendingFault() function */
#define CY_SYSFAULT_IS_FAULT_SET_VALID(pendingFault)  (((pendingFault) == CY_SYSFAULT_SET0) || \
                                                       ((pendingFault) == CY_SYSFAULT_SET1) || \
                                                       ((pendingFault) == CY_SYSFAULT_SET2))
/** \endcond */


/** \} group_sysfault_macros */


/**
* \addtogroup group_sysfault_enums
* \{
*/

/**
* SysFault driver error codes
*/
typedef enum
{
    CY_SYSFAULT_SUCCESS   = 0x0UL, /**< Returned successful */
    CY_SYSFAULT_BAD_PARAM = CY_SYSFAULT_ID | CY_PDL_STATUS_ERROR | 0x1UL, /**< Bad parameter was passed */
} cy_en_SysFault_status_t;

/**
* SysFault pending Fault source set.
*/
typedef enum
{
    CY_SYSFAULT_SET0 = 0UL, /**< Set of Faults in the range of 0-31 Fault ID */
    CY_SYSFAULT_SET1 = 1UL, /**< Set of Faults in the range of 32-63  Fault ID */
    CY_SYSFAULT_SET2 = 2UL, /**< Set of Faults in the range of 64-95 Fault ID */
} cy_en_SysFault_Set_t;

/**
* Instances of Fault data register.
*/
typedef enum
{
    CY_SYSFAULT_DATA0 = 0UL, /**< Used to get the Fault data for DATA0 register */
    CY_SYSFAULT_DATA1=  1UL, /**< Used to get the Fault data for DATA1 register */
    CY_SYSFAULT_DATA2 = 2UL, /**< Used to get the Fault data for DATA2 register */
    CY_SYSFAULT_DATA3=  3UL, /**< Used to get the Fault data for DATA3 register */
} cy_en_SysFault_Data_t;

/** \} group_sysfault_enums */


/***************************************
*       Configuration Structure
***************************************/

/**
* \addtogroup group_sysfault_data_structures
* \{
*/

/**
* Configuration structure for a Fault control register.
*/
typedef struct {
    bool       TriggerEnable;    /**< Enables the trigger output when it is True */
    bool       OutputEnable;    /**< Enables the output signal when it is True */
    bool       ResetEnable;     /**< Enables the Reset request  when it is True */
} cy_stc_SysFault_t;


/** \} group_sysfault_data_structures */


/***************************************
*       Function Prototypes
***************************************/

/**
* \addtogroup group_sysfault_functions
* \{
*/

/*******************************************************************************
* Function Name: Cy_SysFault_Init
****************************************************************************//**
*
* \brief
* Initializes the SysFault for recording faults.
*
* \param base
* The pointer to a Fault structure instance.
*
* \param config
* The pointer to a Configuration structure.
*
* \return
* Fault status. Refer \ref cy_en_SysFault_status_t
*
* \funcusage
* \snippet sysfault/snippet/main.c snippet_Cy_SysFault_Config
*
*******************************************************************************/
cy_en_SysFault_status_t Cy_SysFault_Init(FAULT_STRUCT_Type *base, cy_stc_SysFault_t *config);


/*******************************************************************************
* Function Name: Cy_SysFault_ClearStatus
****************************************************************************//**
*
* \brief
* Clears status register.
*
* \param base
* The pointer to a Fault structure instance.
*
* \funcusage
* \snippet sysfault/snippet/main.c snippet_Cy_SysFault_Config
*
*******************************************************************************/
void Cy_SysFault_ClearStatus(FAULT_STRUCT_Type *base);


/*******************************************************************************
* Function Name: Cy_SysFault_GetErrorSource
****************************************************************************//**
*
* \brief
* Returns the source of error for the Fault.
*
* \param  base
* The pointer to a Fault structure instance.
*
* \return
* Fault source.
*
* \funcusage
* \snippet sysfault/snippet/main.c snippet_Cy_SysFault_Handle_Fault
*
*******************************************************************************/
cy_en_SysFault_source_t Cy_SysFault_GetErrorSource(FAULT_STRUCT_Type *base);


/*******************************************************************************
* Function Name: Cy_SysFault_GetFaultData
****************************************************************************//**
*
* \brief
* Returns the Fault information for the provided dataSet.
*
* \param base
* The pointer to a Fault structure instance.
*
* \param dataSet
* Instance of data register.
*
* \return
* Fault information.
*
* \funcusage
* \snippet sysfault/snippet/main.c snippet_Cy_SysFault_Handle_Fault
*
*******************************************************************************/
uint32_t Cy_SysFault_GetFaultData(FAULT_STRUCT_Type *base, cy_en_SysFault_Data_t dataSet);


/*******************************************************************************
* Function Name: Cy_SysFault_GetPendingFault
****************************************************************************//**
*
* \brief
* Returns the sources of pending fault that are not captured.
*
* \param base
* The pointer to a Fault structure instance.
*
* \param pendingFault
* Instance of PENDING register. PENDING0 returns the occurred pending Faults in the range of 0-31 Fault ID.
*
* \return
* The status of pending Faults.
*
* \funcusage
* \snippet sysfault/snippet/main.c snippet_Cy_SysFault_PendingFault
*
*******************************************************************************/
uint32_t Cy_SysFault_GetPendingFault(FAULT_STRUCT_Type *base, cy_en_SysFault_Set_t pendingFault);


/*******************************************************************************
* Function Name: Cy_SysFault_SetMaskByIdx
****************************************************************************//**
*
* \brief
* Enable the Fault to be captured.
*
* \param base
* The pointer to a Fault structure instance.
*
* \param idx
* The Fault id to be set in the mask register.
*
* \return
* None.
*
* \funcusage
* \snippet sysfault/snippet/main.c snippet_Cy_SysFault_Config
*
*******************************************************************************/
void Cy_SysFault_SetMaskByIdx(FAULT_STRUCT_Type *base, cy_en_SysFault_source_t idx);


/*******************************************************************************
* Function Name: Cy_SysFault_ClearMaskByIdx
****************************************************************************//**
*
* \brief
* Disable the faults to be captured.
*
* \param base
* The pointer to a Fault structure instance.
*
* \param idx
* The fault id to be cleared in the mask register.
*
* \return
* None.
*
* \funcusage
* \snippet sysfault/snippet/main.c snippet_Cy_SysFault_PendingFault
*
*******************************************************************************/
void Cy_SysFault_ClearMaskByIdx(FAULT_STRUCT_Type *base, cy_en_SysFault_source_t idx);


/*******************************************************************************
* Function Name: Cy_SysFault_GetInterruptStatus
****************************************************************************//**
*
* \brief
* Returns the status of the interrupt.
*
* \param base
* The pointer to a Fault structure instance.
*
* \return
* Interrupt status.
*
* \funcusage
* \snippet sysfault/snippet/main.c snippet_Cy_SysFault_Handle_Fault
*
*******************************************************************************/
uint32_t Cy_SysFault_GetInterruptStatus(FAULT_STRUCT_Type *base);


/*******************************************************************************
* Function Name: Cy_SysFault_ClearInterrupt
****************************************************************************//**
*
* \brief
* Clears Active Interrupt Source.
*
* \param base
* The pointer to a Fault structure instance.
*
* \return
* None.
*
* \funcusage
* \snippet sysfault/snippet/main.c snippet_Cy_SysFault_Handle_Fault
*
*******************************************************************************/
void Cy_SysFault_ClearInterrupt(FAULT_STRUCT_Type *base);


/*******************************************************************************
* Function Name: Cy_SysFault_SetInterrupt
****************************************************************************//**
*
* \brief
* Triggers an interrupt via a software write.
*
* \param base
* The pointer to a Fault structure instance.
*
* \return
* None.
*
* \funcusage
* \snippet sysfault/snippet/main.c snippet_Cy_SysFault_Config
*
*******************************************************************************/
void Cy_SysFault_SetInterrupt(FAULT_STRUCT_Type *base);


/*******************************************************************************
* Function Name: Cy_SysFault_SetInterruptMask
****************************************************************************//**
*
* \brief
* Sets an interrupt mask.
*
* \param base
* The pointer to a Fault structure instance.
*
* \return
* None.
*
* \funcusage
* \snippet sysfault/snippet/main.c snippet_Cy_SysFault_Config
*
*******************************************************************************/
void Cy_SysFault_SetInterruptMask(FAULT_STRUCT_Type *base);


/*******************************************************************************
* Function Name: Cy_SysFault_ClearInterruptMask
****************************************************************************//**
*
* \brief
* Clears an interrupt mask.
*
* \param base
* The pointer to a Fault structure instance.
*
* \return
* None.
*
* \funcusage
* \snippet sysfault/snippet/main.c snippet_Cy_SysFault_Handle_Fault
*
*******************************************************************************/
void Cy_SysFault_ClearInterruptMask(FAULT_STRUCT_Type *base);


/*******************************************************************************
* Function Name: Cy_SysFault_GetInterruptMask
****************************************************************************//**
*
* \brief Returns the interrupt mask.
*
* \param  base
* The pointer to a Fault structure instance.
*
* \return
* Interrupt Mask.
*
* \funcusage
* \snippet sysfault/snippet/main.c snippet_Cy_SysFault_Handle_Fault
*
*******************************************************************************/
uint32_t Cy_SysFault_GetInterruptMask(FAULT_STRUCT_Type *base);


/*******************************************************************************
* Function Name: Cy_SysFault_GetInterruptStatusMasked
****************************************************************************//**
*
* \brief
* Returns whether masked interrupt triggered the interrupt.
*
* \param base
* The pointer to a Fault structure instance.
*
* \return
* Interrupt Mask.
*
* \funcusage
* \snippet sysfault/snippet/main.c snippet_Cy_SysFault_Handle_Fault
*
*******************************************************************************/
uint32_t Cy_SysFault_GetInterruptStatusMasked(FAULT_STRUCT_Type *base);

/** \} group_sysfault_functions */


#if defined(__cplusplus)
}
#endif

#endif /* CY_IP_M7CPUSS */

#endif /* CY_SYSFAULT_H */

/** \} group_sysfault */

/* [] END OF FILE */
