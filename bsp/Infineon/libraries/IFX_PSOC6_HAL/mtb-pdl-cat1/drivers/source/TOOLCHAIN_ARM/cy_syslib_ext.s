;-------------------------------------------------------------------------------
; \file cy_syslib_ext.s
; \version 2.70
;
;  \brief Assembly routines for ARMCC.
;
;-------------------------------------------------------------------------------
; Copyright 2016-2020 Cypress Semiconductor Corporation
; SPDX-License-Identifier: Apache-2.0
;
; Licensed under the Apache License, Version 2.0 (the "License");
; you may not use this file except in compliance with the License.
; You may obtain a copy of the License at
;
;     http://www.apache.org/licenses/LICENSE-2.0
;
; Unless required by applicable law or agreed to in writing, software
; distributed under the License is distributed on an "AS IS" BASIS,
; WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
; See the License for the specific language governing permissions and
; limitations under the License.
;-------------------------------------------------------------------------------

    AREA |.text|,CODE,ALIGN=3
    THUMB
    EXTERN Reset

;-------------------------------------------------------------------------------
; Function Name: Cy_SysLib_DelayCycles
;-------------------------------------------------------------------------------
;
; Summary:
;  Delays for the specified number of cycles.
;
; Parameters:
;  uint32_t cycles: The number of cycles to delay.
;
;-------------------------------------------------------------------------------
; void Cy_SysLib_DelayCycles(uint32_t cycles)
    ALIGN 8
Cy_SysLib_DelayCycles FUNCTION
    EXPORT Cy_SysLib_DelayCycles
                            ; cycles bytes
    ADDS r0, r0, #2         ;    1    2    Round to the nearest multiple of 4.
    LSRS r0, r0, #2         ;    1    2    Divide by 4 and set flags.
    BEQ Cy_DelayCycles_done ;    2    2    Skip if 0.
Cy_DelayCycles_loop
    ADDS r0, r0, #1         ;    1    2    Increment the counter.
    SUBS r0, r0, #2         ;    1    2    Decrement the counter by 2.
    BNE Cy_DelayCycles_loop ;   (1)2  2    2 CPU cycles (if branch is taken).
    NOP                     ;    1    2    Loop alignment padding.
Cy_DelayCycles_done
    BX lr                   ;    3    2
    ENDFUNC


;-------------------------------------------------------------------------------
; Function Name: Cy_SysLib_EnterCriticalSection
;-------------------------------------------------------------------------------
;
; Summary:
;  Cy_SysLib_EnterCriticalSection disables interrupts and returns a value
;  indicating whether interrupts were previously enabled.
;
;  Note Implementation of Cy_SysLib_EnterCriticalSection manipulates the IRQ
;  enable bit with interrupts still enabled. The test and set of the interrupt
;  bits are not atomic. Therefore, to avoid a corrupting processor state, it must
;  be the policy that all interrupt routines restore the interrupt enable bits as
;  they were found on entry.
;
; Return:
;  uint8_t
;   Returns 0 if interrupts were previously enabled or 1 if interrupts
;   were previously disabled.
;
;-------------------------------------------------------------------------------
; uint8_t Cy_SysLib_EnterCriticalSection(void)
Cy_SysLib_EnterCriticalSection FUNCTION
    EXPORT Cy_SysLib_EnterCriticalSection
    MRS r0, PRIMASK         ; Save and return an interrupt state.
    CPSID I                 ; Disable the interrupts.
    BX lr
    ENDFUNC


;-------------------------------------------------------------------------------
; Function Name: Cy_SysLib_ExitCriticalSection
;-------------------------------------------------------------------------------
;
; Summary:
;  Cy_SysLib_ExitCriticalSection re-enables interrupts if they were enabled
;  before Cy_SysLib_EnterCriticalSection was called. The argument should be the
;  value returned from Cy_SysLib_EnterCriticalSection.
;
; Parameters:
;  uint8_t savedIntrStatus:
;   The saved interrupt status returned by the Cy_SysLib_EnterCriticalSection
;   function.
;
;-------------------------------------------------------------------------------
; void Cy_SysLib_ExitCriticalSection(uint8_t savedIntrStatus)
Cy_SysLib_ExitCriticalSection FUNCTION
    EXPORT Cy_SysLib_ExitCriticalSection
    MSR PRIMASK, r0         ; Restore the interrupt state.
    BX lr
    ENDFUNC

    END

; [] END OF FILE
