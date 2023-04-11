/***************************************************************************//**
* \file cy_syslib_ext.S
* \version 2.70
*
* \brief Assembly routines for Apple Clang.
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

.syntax unified
.text
.thumb


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
.align 3                    /* Align to 8 byte boundary (2^n) */
.global _Cy_SysLib_DelayCycles
.thumb_func

_Cy_SysLib_DelayCycles:      /* cycles bytes */
    ADDS r0, r0, #2         /*    1    2    Round to nearest multiple of 4 */
    LSRS r0, r0, #2         /*    1    2    Divide by 4 and set flags */
    BEQ Cy_DelayCycles_done /*    2    2    Skip if 0 */

    .align 2                    /* Align to 8 byte boundary (2^n) */
Cy_DelayCycles_loop:
    ADDS r0, r0, #1         /*    1    2    Increment counter */
    SUBS r0, r0, #2         /*    1    2    Decrement counter by 2 */
    BNE Cy_DelayCycles_loop /*   (1)2  2    2 CPU cycles (if branch is taken) */
    NOP                     /*    1    2    Loop alignment padding */

    .align 2                    /* Align to 8 byte boundary (2^n) */
Cy_DelayCycles_done:
    NOP                     /*    1    2    Loop alignment padding */
    BX lr                   /*    3    2 */


/*******************************************************************************
* Function Name: Cy_SysLib_EnterCriticalSection
****************************************************************************//**
*
* Cy_SysLib_EnterCriticalSection disables interrupts and returns a value
* indicating whether interrupts were previously enabled.
*
* Note Implementation of Cy_SysLib_EnterCriticalSection manipulates the IRQ
* enable bit with interrupts still enabled.
*
* \return Returns 0 if interrupts were previously enabled or 1 if interrupts
* were previously disabled.
*
*******************************************************************************/
/* uint8_t Cy_SysLib_EnterCriticalSection(void) */
.global _Cy_SysLib_EnterCriticalSection
.thumb_func

_Cy_SysLib_EnterCriticalSection:
    MRS r0, PRIMASK         /* Save and return interrupt state */
    cpsid i                 /* Disable interrupts */
    BX lr


/*******************************************************************************
* Function Name: Cy_SysLib_ExitCriticalSection
****************************************************************************//**
*
*  Re-enables interrupts if they were enabled before
*  Cy_SysLib_EnterCriticalSection() was called. The argument should be the value
*  returned from \ref Cy_SysLib_EnterCriticalSection().
*
*  \param uint8_t savedIntrStatus:
*   Saved interrupt status returned by the \ref Cy_SysLib_EnterCriticalSection().
*
*******************************************************************************/
/* void Cy_SysLib_ExitCriticalSection(uint8_t savedIntrStatus) */
.global _Cy_SysLib_ExitCriticalSection
.thumb_func

_Cy_SysLib_ExitCriticalSection:
    MSR PRIMASK, r0         /* Restore interrupt state */
    BX lr

.end

/* [] END OF FILE */
