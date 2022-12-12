/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date       Author       Notes
 * 2009-01-20     Bernard      first version
 * 2011-07-22     Bernard      added thumb mode porting
 * 2013-05-24     Grissiom     port to CCS
 * 2013-05-26     Grissiom     optimize for ARMv7
 * 2013-10-20     Grissiom     port to GCC
 */

#include <rtconfig.h>

   .text
   .arm
   .globl rt_thread_switch_interrupt_flag
   .globl rt_interrupt_from_thread
   .globl rt_interrupt_to_thread
   .globl rt_interrupt_enter
   .globl rt_interrupt_leave
   .globl rt_hw_trap_irq

/*
 * rt_base_t rt_hw_interrupt_disable()
 */
    .globl rt_hw_interrupt_disable
rt_hw_interrupt_disable:
    MRS r0, cpsr
    CPSID IF
    BX  lr

/*
 * void rt_hw_interrupt_enable(rt_base_t level)
 */
    .globl rt_hw_interrupt_enable
rt_hw_interrupt_enable:
    MSR cpsr_c, r0
    BX  lr

/*
 * void rt_hw_context_switch(rt_uint32 from, rt_uint32 to)
 * r0 --> from
 * r1 --> to
 */
    .globl rt_hw_context_switch
rt_hw_context_switch:
    STMDB   sp!, {lr}           @ push pc (lr should be pushed in place of PC)
    STMDB   sp!, {r0-r12, lr}   @ push lr & register file

    MRS     r4, cpsr
    TST     lr, #0x01
    ORRNE   r4, r4, #0x20       @ it's thumb code

    STMDB   sp!, {r4}           @ push cpsr

#if defined (__VFP_FP__) && !defined(__SOFTFP__) && defined(RT_VFP_LAZY_STACKING)
        VMRS    r4,  fpexc
        TST     r4,  #0x40000000
        BEQ     __no_vfp_frame1
        VSTMDB  sp!, {d0-d15}
        VMRS    r5, fpscr
        @ TODO: add support for Common VFPv3.
        @       Save registers like FPINST, FPINST2
        STMDB   sp!, {r5}
__no_vfp_frame1:
        STMDB   sp!, {r4}
#endif

    STR     sp, [r0]            @ store sp in preempted tasks TCB
    LDR     sp, [r1]            @ get new task stack pointer

#if defined (__VFP_FP__) && !defined(__SOFTFP__) && defined(RT_VFP_LAZY_STACKING)
        LDMIA   sp!, {r0}       @ get fpexc
        VMSR    fpexc,  r0      @ restore fpexc
        TST     r0,  #0x40000000
        BEQ     __no_vfp_frame2
        LDMIA   sp!, {r1}       @ get fpscr
        VMSR    fpscr, r1
        VLDMIA  sp!, {d0-d15}
__no_vfp_frame2:
    #endif

    LDMIA   sp!, {r4}           @ pop new task cpsr to spsr
    MSR     spsr_cxsf, r4

    LDMIA   sp!, {r0-r12, lr, pc}^ @ pop new task r0-r12, lr & pc, copy spsr to cpsr

/*
 * void rt_hw_context_switch_to(rt_uint32 to)
 * r0 --> to
 */
    .globl rt_hw_context_switch_to
rt_hw_context_switch_to:
    LDR     sp, [r0]            @ get new task stack pointer

#if defined (__VFP_FP__) && !defined(__SOFTFP__) && defined(RT_VFP_LAZY_STACKING)
        LDMIA   sp!, {r0}       @ get fpexc
        VMSR    fpexc, r0
        TST     r0,  #0x40000000
        BEQ     __no_vfp_frame_to
        LDMIA   sp!, {r1}       @ get fpscr
        VMSR    fpscr, r1
        VLDMIA  sp!, {d0-d15}
__no_vfp_frame_to:
#endif

    LDMIA   sp!, {r4}           @ pop new task cpsr to spsr
    MSR     spsr_cxsf, r4

    LDMIA   sp!, {r0-r12, lr, pc}^ @ pop new task r0-r12, lr & pc, copy spsr to cpsr

/*
 * void rt_hw_context_switch_interrupt(rt_uint32 from, rt_uint32 to)@
 */

    .globl rt_hw_context_switch_interrupt
rt_hw_context_switch_interrupt:
    LDR r2, =rt_thread_switch_interrupt_flag
    LDR r3, [r2]
    CMP r3, #1
    BEQ _reswitch
    MOV r3, #1              @ set rt_thread_switch_interrupt_flag to 1
    STR r3, [r2]
    LDR r2, =rt_interrupt_from_thread  @ set rt_interrupt_from_thread

    STR r0, [r2]
_reswitch:
    LDR r2, =rt_interrupt_to_thread       @ set rt_interrupt_to_thread
    STR r1, [r2]
    BX  lr

    .globl IRQ_Handler
IRQ_Handler:
    STMDB   sp!, {r0-r12,lr}

#if defined (__VFP_FP__) && !defined(__SOFTFP__) && defined(RT_VFP_LAZY_STACKING)
        VMRS    r0,  fpexc
        TST     r0,  #0x40000000
        BEQ     __no_vfp_frame_str_irq
        VSTMDB  sp!, {d0-d15}
        VMRS    r1, fpscr
        @ TODO: add support for Common VFPv3.
        @       Save registers like FPINST, FPINST2
        STMDB   sp!, {r1}
__no_vfp_frame_str_irq:
        STMDB   sp!, {r0}
#endif

    BL  rt_interrupt_enter
    BL  rt_hw_trap_irq
    BL  rt_interrupt_leave

    @ if rt_thread_switch_interrupt_flag set, jump to
    @ rt_hw_context_switch_interrupt_do and don't return
    LDR r0, =rt_thread_switch_interrupt_flag
    LDR r1, [r0]
    CMP r1, #1
    BEQ rt_hw_context_switch_interrupt_do

#if defined (__VFP_FP__) && !defined(__SOFTFP__) && defined(RT_VFP_LAZY_STACKING)
        LDMIA   sp!, {r0}       @ get fpexc
        VMSR    fpexc, r0
        TST     r0,  #0x40000000
        BEQ     __no_vfp_frame_ldr_irq
        LDMIA   sp!, {r1}       @ get fpscr
        VMSR    fpscr, r1
        VLDMIA  sp!, {d0-d15}
__no_vfp_frame_ldr_irq:
#endif

    LDMIA   sp!, {r0-r12,lr}
    SUBS    pc, lr, #4

/*
 * void rt_hw_context_switch_interrupt_do(rt_base_t flag)
 */
    .globl rt_hw_context_switch_interrupt_do
rt_hw_context_switch_interrupt_do:
    MOV     r1,  #0           @ clear flag
    STR     r1,  [r0]

#if defined (__VFP_FP__) && !defined(__SOFTFP__) && defined(RT_VFP_LAZY_STACKING)
        LDMIA   sp!, {r0}       @ get fpexc
        VMSR    fpexc, r0
        TST     r0,  #0x40000000
        BEQ     __no_vfp_frame_do1
        LDMIA   sp!, {r1}       @ get fpscr
        VMSR    fpscr, r1
        VLDMIA  sp!, {d0-d15}
__no_vfp_frame_do1:
#endif

    LDMIA   sp!, {r0-r12,lr}  @ reload saved registers
    STMDB   sp, {r0-r3}       @ save r0-r3. We will restore r0-r3 in the SVC
                              @ mode so there is no need to update SP.
    SUB     r1,  sp, #16      @ save the right SP value in r1, so we could restore r0-r3.
    SUB     r2,  lr, #4       @ save old task's pc to r2

    MRS     r3,  spsr         @ get cpsr of interrupt thread

    @ switch to SVC mode and no interrupt
    CPSID   IF, #0x13

    STMDB   sp!, {r2}         @ push old task's pc
    STMDB   sp!, {r4-r12,lr}  @ push old task's lr,r12-r4
    LDMIA   r1!, {r4-r7}      @ restore r0-r3 of the interrupted thread
    STMDB   sp!, {r4-r7}      @ push old task's r3-r0. We don't need to push/pop them to
                              @ r0-r3 because we just want to transfer the data and don't
                              @ use them here.
    STMDB   sp!, {r3}         @ push old task's cpsr

#if defined (__VFP_FP__) && !defined(__SOFTFP__) && defined(RT_VFP_LAZY_STACKING)
        VMRS    r0,  fpexc
        TST     r0,  #0x40000000
        BEQ     __no_vfp_frame_do2
        VSTMDB  sp!, {d0-d15}
        VMRS    r1, fpscr
        @ TODO: add support for Common VFPv3.
        @       Save registers like FPINST, FPINST2
        STMDB   sp!, {r1}
__no_vfp_frame_do2:
        STMDB   sp!, {r0}
#endif

    LDR     r4,  =rt_interrupt_from_thread
    LDR     r5,  [r4]
    STR     sp,  [r5]         @ store sp in preempted tasks's TCB

    LDR     r6,  =rt_interrupt_to_thread
    LDR     r6,  [r6]
    LDR     sp,  [r6]         @ get new task's stack pointer

#if defined (__VFP_FP__) && !defined(__SOFTFP__) && defined(RT_VFP_LAZY_STACKING)
        LDMIA   sp!, {r0}       @ get fpexc
        VMSR    fpexc, r0
        TST     r0,  #0x40000000
        BEQ     __no_vfp_frame_do3
        LDMIA   sp!, {r1}       @ get fpscr
        VMSR    fpscr, r1
        VLDMIA  sp!, {d0-d15}
__no_vfp_frame_do3:
#endif

    LDMIA   sp!, {r4}         @ pop new task's cpsr to spsr
    MSR     spsr_cxsf, r4

    LDMIA   sp!, {r0-r12,lr,pc}^ @ pop new task's r0-r12,lr & pc, copy spsr to cpsr

