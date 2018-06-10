;/*
; * File      : lwp_rvds.S
; * This file is part of RT-Thread RTOS
; * COPYRIGHT (C) 2006 - 2018, RT-Thread Development Team
; *
; *  This program is free software; you can redistribute it and/or modify
; *  it under the terms of the GNU General Public License as published by
; *  the Free Software Foundation; either version 2 of the License, or
; *  (at your option) any later version.
; *
; *  This program is distributed in the hope that it will be useful,
; *  but WITHOUT ANY WARRANTY; without even the implied warranty of
; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
; *  GNU General Public License for more details.
; *
; *  You should have received a copy of the GNU General Public License along
; *  with this program; if not, write to the Free Software Foundation, Inc.,
; *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
; *
; * Change Logs:
; * Date           Author       Notes
; */

    AREA |.text|, CODE, READONLY, ALIGN=2
    THUMB
    REQUIRE8
    PRESERVE8

;/*
; * void* lwp_get_sys_api(rt_uint32_t number);
; */
    IMPORT lwp_get_sys_api
    IMPORT lwp_get_kernel_sp
    IMPORT lwp_set_kernel_sp

;/*
; * void lwp_user_entry(u32 R0_text_addr, u32 R1_data_addr);
; */
lwp_user_entry    PROC
    EXPORT  lwp_user_entry

    PUSH    {R0-R1}             ; push text&data addr.

    MOV     R0, SP              ; v1 = SP
    BL      lwp_set_kernel_sp   ; lwp_set_kernel_sp(v1)

    POP     {R0-R1}             ; pop app address to R1.

    ; set CPU to user-thread mode.
    MRS     R2, CONTROL
    ORR     R2, R2, #0x03       ; use PSP, user-thread mode.
    MSR     CONTROL, R2

    ; set data address.
    MOV     R9, R1

    ; run app, only Thumb-mode.
    ORR     R0, R0, #0x01
    BX      R0

    ; never reach here!
    ENDP

;/*
; * void SVC_Handler(void);
; */
SVC_Handler    PROC
    EXPORT SVC_Handler

    PUSH    {LR}

    ; get user SP.
    TST     LR, #0x4
    ITE     EQ
    MRSEQ   R1, MSP
    MRSNE   R1, PSP

    PUSH    {R1}                        ; push app SP.
    MOV     R2, R1

    IF      {FPU} != "SoftVFP"
    TST       LR, #0x10
    VSTMFDEQ  R2!, {D8 - D15}
    ENDIF

    STMFD   R2!, {R4 - R11}              ; push app R4-R11 to app stack , and R1 not change.

    IF      {FPU} != "SoftVFP"
    MOV     R4, #0x00               ; flag = 0
    TST     LR, #0x10               ; if(!EXC_RETURN[4])
    MOVEQ   R4, #0x01               ; flag = 1
    STMFD   R2!, {R4}               ; push flag
    ENDIF

    ; get SVC number.
    LDR     R0, [R1, #24]               ; get the app LR.
    LDRB    R0, [R0, #-2]               ; get the SVC No. from instruction.

    ; get kernel system API
    BL      lwp_get_sys_api

    ; if(api == NULL) return;
    CMP     R0, #0
    POPEQ   {R1}
    POPEQ   {LR}
    BXEQ    LR

    ; push api
    PUSH    {R0}

    ; get kernel SP to R0.
    BL lwp_get_kernel_sp

    POP     {R2}                        ; pop api to R2.
    POP     {R1}                        ; pop app SP to R1.

    ; copy R1(app SP) to R0(server SP).
    LDMFD   R1,   {R4 - R11}     ; pop exception_stack_frame to r4 - r11 register
    STMFD   R0!,  {R4 - R11}     ; push exception_stack_frame to server SP.

    POP     {LR}
    PUSH    {LR}

    ; save app SP.
    PUSH    {R0 - R3}
    IF      {FPU} != "SoftVFP"
    TST     LR, #0x10
    SUBEQ   R0, R1, #0x64               ; keep {R4 - R11}, {D8-D15}, FLAG
    SUBNE   R0, R1, #0x24               ; keep {R4 - R11}, FLAG
    ELSE
    SUB     R0, R1, #0x20               ; keep {R4 - R11}
    ENDIF
    BL      lwp_set_kernel_sp
    POP     {R0 - R3}

    ; set to thread-privilege mode.
    MRS     R3, CONTROL
    BIC     R3, R3, #0x01
    ORR     R3, R3, #0x02
    MSR     CONTROL, R3

    ; call api.
    LDR     R3, =svc_exit
    STR     R3, [R0, #20]       ; update LR
    STR     R2, [R0, #24]       ; update api to PC
    MSR     PSP, R0             ; update stack pointer
    POP     {LR}                ; 0xFFFFFFED

    ORR     LR, LR, #0x10

    BX      LR

    ENDP

;/*
; * void svc_exit(void);
; */
svc_exit     PROC
    EXPORT svc_exit

    ; get user SP.
    PUSH    {R0}                    ; push result to SP.
    BL      lwp_get_kernel_sp

    IF      {FPU} != "SoftVFP"
    LDMFD   R0!, {R3}               ; pop flag
    ENDIF

    LDMFD   R0!, {R4 - R11}         ; pop app {R4 - R11}

    IF      {FPU} != "SoftVFP"
    CMP     R3,  #0                 ; if(flag_r3 != 0)
    VLDMFDNE  R0!, {D8 - D15}       ; pop FPU register s16~s31
    ENDIF

    ADD     R0, R0, #16             ; skip R0-R3
    LDMFD   R0!, {R12, LR}          ;
    LDMFD   R0!, {R1}               ; pop PC to R1
    LDMFD   R0!, {R2}               ; pop PSR to R2

    IF      {FPU} != "SoftVFP"
    CMP     R3,  #0                 ; if(flag_r3 != 0)
    VLDMFDNE  R0!, {D0 - D7}       ; pop FPU register s16~s31
    LDMFDNE   R0!, {R3}
    VMSRNE    FPSCR,  R3

    ENDIF

    ; align to 2 words
    ADD     R0, R0, #0x07
    BIC     R0, R0, #0x07
    PUSH    {R0}                    ; push user-SP to SP

    ; save server SP.
    ADD     R0, SP, #0x08           ; [user-SP, result]
    PUSH    {R1 - R2, LR}
    BL      lwp_set_kernel_sp
    POP     {R1 - R2, LR}

    POP     {R3}                    ; pop user-SP to R3
    POP     {R0}                    ; restore API result.

    MSR     APSR, R2                ; restore PSR
    MSR     PSP, R3                 ; restore app stack pointer

    ; restore to PSP & thread-unprivilege mode.
    MRS     R2, CONTROL
    ORR     R2, R2, #0x03
    MSR     CONTROL, R2

    ; return to lwp.
    ORR     R1, R1, #0x01           ; only Thumb-mode.
    BX      R1                      ; return to user app.

    ENDP

    ALIGN

    END
