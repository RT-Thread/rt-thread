/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-03-01     Wangyuqiang  first version
 */

.syntax unified
.text

.globl rt_thread_switch_interrupt_flag
.globl rt_interrupt_from_thread
.globl rt_interrupt_to_thread
.globl rt_interrupt_enter
.globl rt_interrupt_leave
.globl rt_hw_trap_irq

/*
 * rt_base_t rt_hw_interrupt_disable();
 */
.globl rt_hw_interrupt_disable
rt_hw_interrupt_disable:
    mrs r0, cpsr
    cpsid i
    bx  lr

/*
 * void rt_hw_interrupt_enable(rt_base_t level);
 */
.globl rt_hw_interrupt_enable
rt_hw_interrupt_enable:
    msr cpsr, r0
    bx  lr

/*
 * void rt_hw_context_switch(rt_uint32 from, rt_uint32 to)
 * r0 --> from
 * r1 --> to
 */
.globl rt_hw_context_switch
rt_hw_context_switch:
    clrex
    stmfd   sp!, {lr}       @ push pc (lr should be pushed in place of PC)
    stmfd   sp!, {r0-r12, lr}   @ push lr & register file

    mrs r4, cpsr
    tst lr, #0x01
    orrne r4, r4, #0x20     @ it's thumb code

    stmfd sp!, {r4}         @ push cpsr

#ifdef RT_USING_FPU
    /* fpu context */
    vmrs r6, fpexc
    tst  r6, #(1<<30)
    beq __no_vfp_frame1
    vstmdb sp!, {d0-d15}
    vstmdb sp!, {d16-d31}
    vmrs r5, fpscr
    stmfd sp!, {r5}
__no_vfp_frame1:
    stmfd sp!, {r6}
#endif
    str sp, [r0]            @ store sp in preempted tasks TCB
    ldr sp, [r1]            @ get new task stack pointer

#ifdef RT_USING_FPU
    /* fpu context */
    ldmfd sp!, {r6}
    vmsr fpexc, r6
    tst  r6, #(1<<30)
    beq __no_vfp_frame2
    ldmfd sp!, {r5}
    vmsr fpscr, r5
    vldmia sp!, {d16-d31}
    vldmia sp!, {d0-d15}
__no_vfp_frame2:
#endif

    ldmfd   sp!, {r1}
    msr     spsr_cxsf, r1        /* original mode */

    ldmfd   sp!, {r0-r12,lr,pc}^ /* irq return */

/*
 * void rt_hw_context_switch_to(rt_uint32 to)
 * r0 --> to
 */
.globl rt_hw_context_switch_to
rt_hw_context_switch_to:
    LDR     sp, [r0]            @ get new task stack pointer

#ifdef RT_USING_FPU
    ldmfd sp!, {r6}
    vmsr fpexc, r6
    tst  r6, #(1<<30)
    beq     __no_vfp_frame_to
    ldmfd sp!, {r5}
    vmsr fpscr, r5
    vldmia sp!, {d0-d15}
__no_vfp_frame_to:
#endif

    LDMIA   sp!, {r4}           @ pop new task cpsr to spsr
    MSR     spsr_cxsf, r4

    ldmfd   sp!, {r0-r12,lr,pc}^ /* irq return */

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

#ifdef RT_USING_FPU
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

#ifdef RT_USING_FPU
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

#ifdef RT_USING_FPU
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

#ifdef RT_USING_FPU
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

#ifdef RT_USING_FPU
    ldmfd sp!, {r6}
    vmsr fpexc, r6
    tst  r6, #(1<<30)
    beq     __no_vfp_frame_do3
    ldmfd sp!, {r5}
    vmsr fpscr, r5
    vldmia sp!, {d0-d15}

__no_vfp_frame_do3:
#endif

    LDMIA   sp!, {r4}         @ pop new task's cpsr to spsr
    MSR     spsr_cxsf, r4

    ldmfd   sp!, {r0-r12,lr,pc}^ /* irq return */

