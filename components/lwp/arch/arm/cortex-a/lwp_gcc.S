/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-12-10     Jesven       first version
 */

#define  Mode_USR       0x10
#define  Mode_FIQ       0x11
#define  Mode_IRQ       0x12
#define  Mode_SVC       0x13
#define  Mode_MON       0x16
#define  Mode_ABT       0x17
#define  Mode_UDF       0x1B
#define  Mode_SYS       0x1F

#define A_Bit        0x100 
#define I_Bit        0x80 @; when I bit is set, IRQ is disabled
#define F_Bit        0x40 @; when F bit is set, FIQ is disabled
#define T_Bit        0x20

.cpu cortex-a9
.syntax unified
.text

/*
 * void lwp_user_entry(args, text, data);
 */
.global lwp_user_entry
.type lwp_user_entry, % function
lwp_user_entry:
    mrs     r9, cpsr
    bic     r9, #0x1f
    orr     r9, #Mode_USR
    cpsid i
    msr     spsr, r9

    /* set data address. */
    mov     r9, r2
    movs    pc, r1

/*
 * void SVC_Handler(void);
 */
.global SVC_Handler
.type SVC_Handler, % function
SVC_Handler:
    push {lr}
    mrs lr, spsr
    push {r4, r5, lr}
    cpsie i

    push {r0 - r3, r12}
    and r0, r7, #0xff
    bl lwp_get_sys_api
    cmp r0, #0           /* r0 = api */
    mov lr, r0
    pop {r0 - r3, r12}
    beq svc_exit
    blx lr

svc_exit:
    cpsid i
    pop {r4, r5, lr}
    msr spsr_cxsf, lr
    pop {lr}
    movs pc, lr
