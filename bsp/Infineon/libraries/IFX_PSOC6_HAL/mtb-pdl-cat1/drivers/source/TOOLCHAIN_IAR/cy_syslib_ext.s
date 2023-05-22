/***************************************************************************//**
* \file cy_syslib_ext.s
* \version 2.70
*
* \brief Assembly routines for IAR Embedded Workbench IDE.
*
********************************************************************************
* \copyright
* Copyright 2016-2020 Cypress Semiconductor Corporation
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

    SECTION .text:CODE:ROOT(4)
    PUBLIC Cy_SysLib_DelayCycles
    PUBLIC Cy_SysLib_EnterCriticalSection
    PUBLIC Cy_SysLib_ExitCriticalSection
    THUMB


/*******************************************************************************
* Function Name: Cy_SysLib_DelayCycles
****************************************************************************//**
*
* Delays for the specified number of cycles.
*
* \param uint32_t cycles: The number of cycles to delay.
*
*******************************************************************************/
/* void Cy_SysLib_DelayCycles(uint32_t cycles) */

Cy_SysLib_DelayCycles:
    ADDS r0, r0, #2
    LSRS r0, r0, #2
    BEQ Cy_DelayCycles_done
Cy_DelayCycles_loop:
    ADDS r0, r0, #1
    SUBS r0, r0, #2
    BNE Cy_DelayCycles_loop
    NOP
Cy_DelayCycles_done:
    BX lr


/*******************************************************************************
* Function Name: Cy_SysLib_EnterCriticalSection
****************************************************************************//**
*
* Cy_SysLib_EnterCriticalSection disables interrupts and returns a value
* indicating whether interrupts were previously enabled.
*
* Note Implementation of Cy_SysLib_EnterCriticalSection manipulates the IRQ
* enable bit with interrupts still enabled. The test and set of the interrupt
* bits are not atomic. Therefore, to avoid corrupting processor state, it must
* be the policy that all interrupt routines restore the interrupt enable bits
* as they were found on entry.
*
* \return Returns 0 if interrupts were previously enabled or 1 if interrupts
* were previously disabled.
*
*******************************************************************************/
/* uint8_t Cy_SysLib_EnterCriticalSection(void) */

Cy_SysLib_EnterCriticalSection:
    MRS r0, PRIMASK         ; Save and return an interrupt state.
    CPSID I                 ; Disable interrupts.
    BX lr

/*******************************************************************************
* Function Name: Cy_SysLib_ExitCriticalSection
****************************************************************************//**
*
* Cy_SysLib_ExitCriticalSection re-enables the interrupts if they were enabled
* before Cy_SysLib_EnterCriticalSection was called. The argument should be the
* value returned from Cy_SysLib_EnterCriticalSection.
*
*  \param uint8_t savedIntrStatus:
*   The saved interrupt status returned by the
*   \ref Cy_SysLib_EnterCriticalSection().
*
*******************************************************************************/
/* void Cy_SysLib_ExitCriticalSection(uint8_t savedIntrStatus) */

Cy_SysLib_ExitCriticalSection:
    MSR PRIMASK, r0         ; Restore the interrupt state.
    BX lr

    END
