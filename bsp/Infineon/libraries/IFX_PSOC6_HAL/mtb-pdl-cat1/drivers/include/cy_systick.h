/***************************************************************************//**
* \file cy_systick.h
* \version 1.60
*
* Provides the API declarations of the SysTick driver.
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

#ifndef CY_SYSTICK_H
#define CY_SYSTICK_H

/**
* \addtogroup group_arm_system_timer
* \{
* Provides vendor-specific SysTick API.
*
* The functions and other declarations used in this driver are in cy_systick.h.
* You can include cy_pdl.h to get access to all functions and declarations in the PDL.
*
* The SysTick timer is part of the CPU. The timer is a down counter with a 24-bit reload/tick value that is clocked by
* the FastClk/SlowClk. The timer has the capability to generate an interrupt when the set number of ticks expires and
* the counter is reloaded. This interrupt is available as part of the Nested Vectored Interrupt Controller (NVIC) for
* service by the CPU and can be used for general-purpose timing control in user code.
*
* The timer is independent of the CPU (except for the clock), which is useful in applications requiring
* precise timing that do not have a dedicated timer/counter available for the job.
*
* \section group_systick_configuration Configuration Considerations
*
* The \ref Cy_SysTick_Init() performs all required driver's initialization and enables the timer. The function accepts
* two parameters: clock source \ref cy_en_systick_clock_source_t and the timer interval. You must ensure
* the selected clock source for SysTick is enabled.
* The callbacks can be registered/unregistered any time after \ref Cy_SysTick_Init() by calling
* \ref Cy_SysTick_SetCallback().
*
* Changing the SysTick clock source and/or its frequency will change the interrupt interval and therefore
* \ref Cy_SysTick_SetReload() should be called to compensate for this change.
*
* \section group_systick_more_information More Information
*
* Refer to the SysTick section of the ARM reference guide for complete details on the registers and their use.
* See also the "CPU Subsystem (CPUSS)" chapter of the device technical reference manual (TRM).
*
* \section group_systick_changelog Changelog
*
* <table class="doxtable">
* <tr><th>Version</th><th>Changes</th><th>Reason for Change</th></tr>
*   <tr>
*     <td>1.60</td>
*     <td>Bug fix and Enhancements.<br>
*     <td>Bug fix and Enhancements.</td>
*   </tr>
*   <tr>
*     <td>1.50</td>
*     <td>CAT1C, CAT1D devices support.<br>
*         Updated Cy_SysTick_Init() to use Cy_SysInt_SetVector() API to register the callback function and removed invalid define CY_SYSTICK_IRQ_NUM.</td>
*     <td>Support for new devices.</td>
*   </tr>
*   <tr>
*     <td>1.40</td>
*     <td>Support for CM33.</td>
*     <td>New devices support.</td>
*   </tr>
* <tr>
*   <td rowspan="2">1.30</td>
*     <td>Added function parameter checks.</td>
*     <td>Improved the debugging capability.</td>
* </tr>
* <tr>
*     <td>Minor documentation updates.</td>
*     <td>Documentation enhancement.</td>
* </tr>
* <tr>
*   <td rowspan="2">1.20</td>
*     <td>Updated Cy_SysTick_SetClockSource() for the PSoC 64 devices,
*         so that passing any other value than CY_SYSTICK_CLOCK_SOURCE_CLK_CPU
*         will not affect clock source and it will be as
*         \ref Cy_SysTick_GetClockSource() reports.</td>
*     <td>Added PSoC 64 devices support.</td>
* </tr>
* <tr>
*     <td>Minor documentation updates.</td>
*     <td>Documentation enhancement.</td>
* </tr>
* <tr>
*   <td>1.10.1</td>
*     <td>Updated include files.</td>
*     <td>Improve pdl usability.</td>
* </tr>
* <tr>
*   <td rowspan="2">1.10</td>
*     <td>Flattened the organization of the driver source code into the single
*         source directory and the single include directory.
*     </td>
*     <td>Driver library directory-structure simplification.</td>
* </tr>
*   <tr>
*     <td>Added register access layer. Use register access macros instead
*         of direct register access using dereferenced pointers.</td>
*     <td>Makes register access device-independent, so that the PDL does
*         not need to be recompiled for each supported part number.</td>
*   </tr>
* <tr>
* <td>1.0.1</td>
* <td>Fixed a warning issued when the compilation of C++ source code was
*     enabled.</td>
* <td></td>
* </tr>
* <tr>
* <td>1.0</td>
* <td>Initial version</td>
* <td></td>
* </tr>
* </table>
*
* \defgroup group_systick_macros Macros
* \defgroup group_systick_functions Functions
* \defgroup group_systick_data_structures Data Structures
*/

#include "cy_device.h"

#if defined (CY_IP_M33SYSCPUSS) || defined (CY_IP_M4CPUSS) || defined (CY_IP_M7CPUSS) || defined(CY_IP_M55APPCPUSS)

#include <stdint.h>
#include "cy_syslib.h"

#ifdef __cplusplus
extern "C" {
#endif

/** \cond */
typedef void (*Cy_SysTick_Callback)(void);
/** \endcond */

/**
* \addtogroup group_systick_data_structures
* \{
*/
/** SysTick clocks sources */
typedef enum
{
    CY_SYSTICK_CLOCK_SOURCE_CLK_LF    = 0u,     /**< The low frequency clock clk_lf is selected. */
    CY_SYSTICK_CLOCK_SOURCE_CLK_IMO   = 1u,     /**< The internal main oscillator (IMO) clock clk_imo is selected. */
    CY_SYSTICK_CLOCK_SOURCE_CLK_ECO   = 2u,     /**< The external crystal oscillator (ECO) clock clk_eco is selected. */
    CY_SYSTICK_CLOCK_SOURCE_CLK_TIMER = 3u,     /**< The SRSS clk_timer is selected. */
    CY_SYSTICK_CLOCK_SOURCE_CLK_CPU   = 4u,     /**< The CPU clock is selected. */
} cy_en_systick_clock_source_t;

/** \} group_systick_data_structures */


/**
* \addtogroup group_systick_macros
* \{
*/

/** Driver major version */
#define SYSTICK_DRV_VERSION_MAJOR       1

/** Driver minor version */
#define SYSTICK_DRV_VERSION_MINOR       60

/** SysTick driver ID */
#define CY_SYSTICK_ID           CY_PDL_DRV_ID(0x19U)

/** Number of the callbacks assigned to the SysTick interrupt */
#define CY_SYS_SYST_NUM_OF_CALLBACKS         (5u)

/** \} group_systick_macros */

/** \cond */
/** Macros for the conditions used by CY_ASSERT calls */
#define CY_SYSTICK_IS_RELOAD_VALID(load)     ((load) <= 0xFFFFFFUL)
/** \endcond */

/** \cond */
/** Interrupt number in the vector table */
#define CY_SYSTICK_IRQ_NUM                   (SysTick_IRQn)
/** \endcond */


/**
* \addtogroup group_systick_functions
* \{
*/


/*******************************************************************************
* Function Name: Cy_SysTick_Init
****************************************************************************//**
*
* Initializes the SysTick driver:
* - Initializes the callback addresses with pointers to NULL
* - Associates the SysTick system vector with the callback functions
* - Sets the SysTick clock by calling \ref Cy_SysTick_SetClockSource()
* - Sets the SysTick reload interval by calling \ref Cy_SysTick_SetReload()
* - Clears the SysTick counter value by calling \ref Cy_SysTick_Clear()
* - Enables the SysTick by calling \ref Cy_SysTick_Enable(). Note the \ref
*   Cy_SysTick_Enable() function also enables the SysTick interrupt by calling
*   \ref Cy_SysTick_EnableInterrupt().
*
* \param clockSource The SysTick clock source \ref cy_en_systick_clock_source_t
* \param interval The SysTick reload value.
*
* \sideeffect Clears the SysTick count flag if it was set.
*
*******************************************************************************/
void Cy_SysTick_Init(cy_en_systick_clock_source_t clockSource, uint32_t interval);


/*******************************************************************************
* Function Name: Cy_SysTick_Enable
****************************************************************************//**
*
* Enables the SysTick timer and its interrupt.
*
* \sideeffect Clears the SysTick count flag if it was set
*
*******************************************************************************/
void Cy_SysTick_Enable(void);


/*******************************************************************************
* Function Name: Cy_SysTick_Disable
****************************************************************************//**
*
* Disables the SysTick timer and its interrupt.
*
* \sideeffect Clears the SysTick count flag if it was set
*
*******************************************************************************/
void Cy_SysTick_Disable(void);


/*******************************************************************************
* Function Name: Cy_SysTick_SetCallback
****************************************************************************//**
*
* Sets the callback function to the specified callback number.
*
* \param number The number of the callback function addresses to be set.
* The valid range is from 0 to \ref CY_SYS_SYST_NUM_OF_CALLBACKS - 1.
*
* \param function The pointer to the function that will be associated with the
* SysTick ISR for the specified number.
*
* \return Returns the address of the previous callback function.
* The NULL is returned if the specified address in not set or incorrect
* parameter is specified.

* \sideeffect
* The registered callback functions will be executed in the interrupt.
*
*******************************************************************************/
Cy_SysTick_Callback Cy_SysTick_SetCallback(uint32_t number, Cy_SysTick_Callback function);


/*******************************************************************************
* Function Name: Cy_SysTick_GetCallback
****************************************************************************//**
*
* Gets the specified callback function address.
*
* \param number The number of the callback function address to get. The valid
* range is from 0 to \ref CY_SYS_SYST_NUM_OF_CALLBACKS - 1.
*
* \return Returns the address of the specified callback function.
* The NULL is returned if the specified address in not initialized or incorrect
* parameter is specified.
*
*******************************************************************************/
Cy_SysTick_Callback Cy_SysTick_GetCallback(uint32_t number);


/*******************************************************************************
* Function Name: Cy_SysTick_SetClockSource
****************************************************************************//**
*
* Sets the clock source for the SysTick counter.
*
* Clears the SysTick count flag if it was set. If the clock source is not ready
* this function call will have no effect. After changing the clock source to the
* low frequency clock, the counter and reload register values will remain
* unchanged so the time to the interrupt will be significantly longer and vice
* versa.
*
* Changing the SysTick clock source and/or its frequency will change
* the interrupt interval and Cy_SysTick_SetReload() should be
* called to compensate this change.
*
* \param clockSource \ref cy_en_systick_clock_source_t Clock source.
* For the PSoC 64 devices, passing any other value than
* CY_SYSTICK_CLOCK_SOURCE_CLK_CPU will not affect clock source
* and it will be as \ref Cy_SysTick_GetClockSource() reports.
*
*******************************************************************************/
void Cy_SysTick_SetClockSource(cy_en_systick_clock_source_t clockSource);


/*******************************************************************************
* Function Name: Cy_SysTick_GetClockSource
****************************************************************************//**
*
* Gets the clock source for the SysTick counter.
*
* \returns \ref cy_en_systick_clock_source_t Clock source
*
*******************************************************************************/
cy_en_systick_clock_source_t Cy_SysTick_GetClockSource(void);


#if defined (CY_PDL_TZ_ENABLED) || defined (CY_DOXYGEN)
/*******************************************************************************
* Function Name: Cy_NssysTick_Enable
****************************************************************************//**
*
* Enables the Non-Secure SysTick timer and its interrupt.
*
* \sideeffect Clears the SysTick count flag if it was set
*
* \note
* This macro is available for devices having M33SYSCPUSS IP.
*
*******************************************************************************/
void Cy_NsSysTick_Enable(void);


/*******************************************************************************
* Function Name: Cy_NsSysTick_Disable
****************************************************************************//**
*
* Disables the Non-Secure SysTick timer and its interrupt.
*
* \sideeffect Clears the SysTick count flag if it was set
*
* \note
* This macro is available for devices having M33SYSCPUSS IP.
*
*******************************************************************************/
void Cy_NsSysTick_Disable(void);


#endif

/** \} group_systick_functions */


/**
* \addtogroup group_systick_functions
* \{
*/

/*******************************************************************************
* Function Name: Cy_SysTick_EnableInterrupt
****************************************************************************//**
*
* Enables the SysTick interrupt.
*
* \sideeffect Clears the SysTick count flag if it was set
*
*******************************************************************************/
void Cy_SysTick_EnableInterrupt(void);


/*******************************************************************************
* Function Name: Cy_SysTick_DisableInterrupt
****************************************************************************//**
*
* Disables the SysTick interrupt.
*
* \sideeffect Clears the SysTick count flag if it was set
*
*******************************************************************************/
void Cy_SysTick_DisableInterrupt(void);


#ifdef CY_PDL_TZ_ENABLED

/*******************************************************************************
* Function Name: Cy_NsSysTick_EnableInterrupt
****************************************************************************//**
*
* Enables the Non-Secure SysTick interrupt.
*
* \sideeffect Clears the SysTick count flag if it was set
*
* \note
* It is available for CAT1B devices.
*
*******************************************************************************/
void Cy_NsSysTick_EnableInterrupt(void);


/*******************************************************************************
* Function Name: Cy_NsSysTick_DisableInterrupt
****************************************************************************//**
*
* Disables the Non-Secure SysTick interrupt.
*
* \sideeffect Clears the SysTick count flag if it was set
*
* \note
* It is available for CAT1B devices.
*
*******************************************************************************/
void Cy_NsSysTick_DisableInterrupt(void);


#endif


/*******************************************************************************
* Function Name: Cy_SysTick_SetReload
****************************************************************************//**
*
* Sets the value the counter is set to on a startup and after it reaches zero.
* This function does not change or reset the current sysTick counter value, so
* it should be cleared using the Cy_SysTick_Clear() API.
*
* \param value: The valid range is [0x0-0x00FFFFFF]. The counter reset value.
*
*******************************************************************************/
void Cy_SysTick_SetReload(uint32_t value);


/*******************************************************************************
* Function Name: Cy_SysTick_GetReload
****************************************************************************//**
*
* Gets the value the counter is set to on a startup and after it reaches zero.
*
* \return The counter reset value.
*
*******************************************************************************/
uint32_t Cy_SysTick_GetReload(void);


/*******************************************************************************
* Function Name: Cy_SysTick_GetValue
****************************************************************************//**
*
* Gets the current SysTick counter value.
*
* \return The current SysTick counter value.
*
*******************************************************************************/
uint32_t Cy_SysTick_GetValue(void);


/*******************************************************************************
* Function Name: Cy_SysTick_Clear
****************************************************************************//**
*
* Clears the SysTick counter for a well-defined startup.
*
*******************************************************************************/
void Cy_SysTick_Clear(void);


/*******************************************************************************
* Function Name: Cy_SysTick_GetCountFlag
****************************************************************************//**
*
* Gets the values of the count flag. The count flag is set once the SysTick
* counter reaches zero. The flag is cleared on read.
*
* \return Returns a non-zero value if a flag is set; otherwise a zero is
* returned.
*
* \sideeffect Clears the SysTick count flag if it was set.
*
* \note Applicable only in Polling mode. If the SysTick interrupt is enabled,
* the count flag will be cleared automatically on interrupt event.
*
*******************************************************************************/
uint32_t Cy_SysTick_GetCountFlag(void);


/** \} group_systick_functions */

#ifdef __cplusplus
}
#endif

#endif /* CY_IP_M33SYSCPUSS */

#endif /* CY_SYSTICK_H */

/** \} group_systick */


/* [] END OF FILE */
