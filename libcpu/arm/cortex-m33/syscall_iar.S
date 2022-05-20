;/*
; * Copyright (c) 2006-2022, RT-Thread Development Team
; *
; * SPDX-License-Identifier: Apache-2.0
; *
; * Change Logs:
; * Date           Author       Notes
; * 2019-10-25     tyx          first version
; * 2021-03-26     lxf          modify bad instruction
; */

;/*
; * @addtogroup cortex-m33
; */


    SECTION    .text:CODE(2)
    THUMB
    REQUIRE8
    PRESERVE8

    IMPORT rt_secure_svc_handle

;/*
; * int tzcall(int id, rt_ubase_t arg0, rt_ubase_t arg1, rt_ubase_t arg2);
; */
    EXPORT tzcall
tzcall:
    SVC     1                       ;/* call SVC 1 */
    BX      LR

tzcall_entry:
    PUSH    {R1, R4, LR}
    MOV     R4, R1                  ;/* copy thread SP to R4 */
    LDMFD   R4!, {r0 - r3}          ;/* pop user stack, get input arg0, arg1, arg2 */
    STMFD   R4!, {r0 - r3}          ;/* push stack, user stack recovery */
    BL      rt_secure_svc_handle    ;/* call fun */
    POP     {R1, R4, LR}
    STR     R0, [R1]                ;/* update return value */
    BX      LR                      ;/* return to thread */

syscall_entry:
    BX      LR                      ;/* return to user app */

    EXPORT SVC_Handler
SVC_Handler:

    ;/* get SP, save to R1 */
    MRS     R1, MSP                 ;/* get fault context from handler. */
    TST     LR, #0x04               ;/* if(!EXC_RETURN[2]) */
    BEQ     get_sp_done
    MRS     R1, PSP                 ;/* get fault context from thread. */
get_sp_done:

    ;/* get svc index */
    LDR     R0, [R1, #24]
    LDRB    R0, [R0, #-2]

    ;/* if svc == 0, do system call */
    CMP     R0, #0x0
    BEQ    syscall_entry

    ;/* if svc == 1, do TrustZone call */
    CMP     R0, #0x1
    BEQ    tzcall_entry

    END
