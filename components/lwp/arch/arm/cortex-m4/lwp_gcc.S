/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-10-30     heyuanjie    first version
 */

.cpu cortex-m4
.syntax unified
.thumb
.text

/*
 * void* lwp_get_sys_api(rt_uint32_t number);
 */
.global lwp_get_sys_api
.global lwp_get_kernel_sp
.global lwp_set_kernel_sp


/*
 * void lwp_user_entry(args, text, data);
 */
.global lwp_user_entry
.type lwp_user_entry, % function
lwp_user_entry:
    PUSH    {R0-R3}             @; push text&data addr.

    MOV     R0, SP              @; v1 = SP
    BL      lwp_set_kernel_sp   @; lwp_set_kernel_sp(v1)

    @; set CPU to user-thread mode.
    MRS     R2, CONTROL
    ORR     R2, R2, #0x03       @; use PSP, user-thread mode.
    MSR     CONTROL, R2

    POP     {R0-R3}             @; pop app address to R1.
    @; set data address.
    MOV     R9, R2

    @; run app, only Thumb-mode.
    ORR     R1, R1, #0x01
    BX      R1

/*
 * void SVC_Handler(void);
 */
.global SVC_Handler
.type SVC_Handler, % function
SVC_Handler:
    PUSH    {LR}

    @; get user SP.
    TST     LR, #0x4
    ITE     EQ
    MRSEQ   R1, MSP
    MRSNE   R1, PSP
    PUSH    {R1}           @; push app SP.

    @; get SVC number.
    mov     R0, R7

    @; get kernel system API
    BL      lwp_get_sys_api
    
    PUSH    {R0}            @; push api

    @; get kernel SP to R0.
    BL lwp_get_kernel_sp

    POP     {R2}             @; pop api to R2.
    POP     {R1}             @; pop app SP to R1.

    stmfd     r0!, {r1}      @; save app SP to kernel SP

    @;push app parm5~6 to kernel SP
    STMFD   R0!,  {R4 - R5}
    @; copy R1(app SP) to R0(kernel SP).
    push {r8-r11}
    LDMFD   R1,   {R4 - R11}     @; pop exception_stack_frame to r4 - r11 register
    STMFD   R0!,  {R4 - R11}     @; push exception_stack_frame to server SP.
    pop {r8-r11}

    LDR     R3, =svc_exit
    STR     R3, [R0, #20]       @; update LR
    STR     R2, [R0, #24]       @; update api to PC
    MSR     PSP, R0             @; update SP, API is executed with kernel SP

    @; set to thread-privilege mode.
    MRS     R3, CONTROL
    BIC     R3, R3, #0x01
    ORR     R3, R3, #0x02
    MSR     CONTROL, R3

    POP     {LR}                @; 0xFFFFFFED
    ORR     LR, LR, #0x10
    BX      LR
/*
* void svc_exit(void);
*/
.global svc_exit
.type svc_exit, % function
svc_exit:
    @; get user SP.
    PUSH    {R0}                    @; push result to SP.
    BL      lwp_get_kernel_sp
    ldr     r3, [r0, #-4]
    pop {r0}

    ldr     lr, [r3, #20]
    ldr     r1, [r3, #24]           @; load pc
    add     r3, #32                 @; exception_stack_frame size
    MSR     PSP, R3                 @; restore app stack pointer
    @; restore to PSP & thread-unprivilege mode.
    MRS     R2, CONTROL
    ORR     R2, R2, #0x03
    MSR     CONTROL, R2

    @; return to lwp.
    ORR     R1, R1, #0x01           @; only Thumb-mode.
    BX      R1                      @; return to user app.
