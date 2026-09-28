/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-09-27     RT-Thread    ESP32-S3 (Xtensa LX7) vectors + context switch
 *
 * Xtensa windowed-ABI vector table and RT-Thread context switch for ESP32-S3.
 *
 * The window overflow/underflow vectors, the interrupt frame layout
 * (XtExcFrame/XtSolFrame from Espressif's <xtensa/xtensa_context.h>) and the
 * entry/exit sequences follow the canonical ESP-IDF Xtensa port
 * (components/freertos/.../portable/xtensa, Apache-2.0), pared down to what
 * this single-core BSP needs and re-targeted at RT-Thread:
 *   - the interrupt frame is on the interrupted thread's stack, but the C
 *     dispatcher runs on rt_xt_isr_stack, because a windowed spill needs 64
 *     bytes below sp and the frame cannot hold both its saved registers and
 *     those spills (ESP-IDF: _frxt_int_enter / port_IntStack);
 *   - no FreeRTOS hooks: instead of XT_RTOS_INT_ENTER/EXIT bookkeeping, the
 *     vector calls the C dispatcher rt_xt_irq_process() (cpuport.c), which
 *     wraps the ESP-IDF _xt_interrupt_table dispatch in
 *     rt_interrupt_enter()/rt_interrupt_leave();
 *   - coprocessors stay disabled (CPENABLE = 0, see cp_disable_all() in
 *     cpuport.c), so no thread has coprocessor state to move and IDF's lazy
 *     _xt_coproc_exc path is not implemented;
 *   - fatal vectors end in ESP-IDF's _xt_panic (register dump + backtrace).
 */

#include <xtensa/config/core.h>
#include <xtensa/config/system.h>
#include <xtensa/coreasm.h>
#include <xtensa/corebits.h>
#include <xtensa/specreg.h>
#include <xtensa/xtensa_context.h>
#include <esp_private/panic_reason.h>
#include "cpuport.h"

/*
 * External symbols (see the .S notes at the top of cpuport.c):
 *   _xt_context_save/_xt_context_restore: ESP-IDF xtensa_context.S, spills
 *     register windows and saves the rest of the interrupt context; the
 *     caller must pre-store XT_STK_A12/A13 (windowed) and PS/PC/A0/A1.
 *   xthal_window_spill_nw: libxt_hal, non-windowed-clobber window spill.
 *   rt_xt_*: C glue in cpuport.c.
 */
    .extern _xt_context_save
    .extern _xt_context_restore
    .extern rt_xt_irq_process
    .extern rt_xt_exception_handler
    .extern _xt_panic

    .extern rt_thread_switch_interrupt_flag
    .extern rt_interrupt_from_thread
    .extern rt_interrupt_to_thread

/*
 * rt_hw_context_switch() has to carry the `to` argument across its window
 * spill, and no register survives that (xthal_window_spill_nw opens with
 * `rsr a2, WINDOWBASE` and rotates windows as it walks). One .bss word is
 * enough because the switch raises PS.INTLEVEL to XCHAL_EXCM_LEVEL before the
 * spill, and every interrupt this BSP services is below that.
 */
    .section .bss.rt_sol_to, "aw", @nobits
    .align  4
rt_xt_s3_sol_to:
    .space  4

#if !XCHAL_HAVE_WINDOWED
#error this port requires the Xtensa windowed register ABI (ESP32-S3 LX7)
#endif
#if !XCHAL_HAVE_XEA2
#error this port requires XEA2 vector layout (ESP32-S3 LX7)
#endif

    .text

/*
-------------------------------------------------------------------------------
  WINDOW VECTORS. Fixed .org offsets mirror XCHAL_WINDOW_OF*_VADDR; they are
  the unmodified canonical Tensilica sequences (identical in every Xtensa RTOS
  port): on overflow the victim window's a0-a3 are stored into the top of the
  next-lower frame and rfwo rotates back; underflow reloads them.
-------------------------------------------------------------------------------
*/

    .begin      literal_prefix .WindowVectors
    .section    .WindowVectors.text, "ax"
    .align      4

    .org    0x0
    .global _WindowOverflow4
_WindowOverflow4:
    s32e    a0, a5, -16
    s32e    a1, a5, -12
    s32e    a2, a5, -8
    s32e    a3, a5, -4
    rfwo

    .org    0x40
    .global _WindowUnderflow4
_WindowUnderflow4:
    l32e    a0, a5, -16
    l32e    a1, a5, -12
    l32e    a2, a5, -8
    l32e    a3, a5, -4
    rfwu

/* MOVSP-induced alloca: handled in the gap between call4 slots. */
    .align  4
    .global _rt_alloca_exc
_rt_alloca_exc:
    rsr     a0, WINDOWBASE
    rotw    -1
    rsr     a2, PS
    extui   a3, a2, XCHAL_PS_OWB_SHIFT, XCHAL_PS_OWB_BITS
    xor     a3, a3, a4
    rsr     a4, EXCSAVE_1
    slli    a3, a3, XCHAL_PS_OWB_SHIFT
    xor     a2, a2, a3
    wsr     a2, PS
    rsync
    _bbci.l a4, 31, _WindowUnderflow4
    rotw    -1
    _bbci.l a8, 30, _WindowUnderflow8
    rotw    -1
    j       _WindowUnderflow12

    .org    0x80
    .global _WindowOverflow8
_WindowOverflow8:
    s32e    a0, a9, -16
    l32e    a0, a1, -12
    s32e    a1, a9, -12
    s32e    a2, a9, -8
    s32e    a3, a9, -4
    s32e    a4, a0, -32
    s32e    a5, a0, -28
    s32e    a6, a0, -24
    s32e    a7, a0, -20
    rfwo

    .org    0xC0
    .global _WindowUnderflow8
_WindowUnderflow8:
    l32e    a0, a9, -16
    l32e    a1, a9, -12
    l32e    a2, a9, -8
    l32e    a7, a1, -12
    l32e    a3, a9, -4
    l32e    a4, a7, -32
    l32e    a5, a7, -28
    l32e    a6, a7, -24
    l32e    a7, a7, -20
    rfwu

    .org    0x100
    .global _WindowOverflow12
_WindowOverflow12:
    s32e    a0,  a13, -16
    l32e    a0,  a1,  -12
    s32e    a1,  a13, -12
    s32e    a2,  a13, -8
    s32e    a3,  a13, -4
    s32e    a4,  a0,  -48
    s32e    a5,  a0,  -44
    s32e    a6,  a0,  -40
    s32e    a7,  a0,  -36
    s32e    a8,  a0,  -32
    s32e    a9,  a0,  -28
    s32e    a10, a0,  -24
    s32e    a11, a0,  -20
    rfwo

    .org    0x140
    .global _WindowUnderflow12
_WindowUnderflow12:
    l32e    a0,  a13, -16
    l32e    a1,  a13, -12
    l32e    a2,  a13, -8
    l32e    a11, a1,  -12
    l32e    a3,  a13, -4
    l32e    a4,  a11, -48
    l32e    a5,  a11, -44
    l32e    a6,  a11, -40
    l32e    a7,  a11, -36
    l32e    a8,  a11, -32
    l32e    a9,  a11, -28
    l32e    a10, a11, -24
    l32e    a11, a11, -20
    rfwu

    .end        literal_prefix

/*
-------------------------------------------------------------------------------
  UNUSED VECTORS. v1 runs every interrupt at level 1; debug/NMI/kernel/double
  and levels 2-5 are fatal firmware errors: stage the vector's own EPC into
  EPC_1, publish the ESP-IDF panic reason in EXCCAUSE and fall into IDF's
  _xt_panic, which builds the frame, saves the context and runs panicHandler
  (register dump + backtrace over the ROM printf). Those vectors already
  compile into this image, and their output is what an ESP32 developer reads.
-------------------------------------------------------------------------------
*/

/* _xt_panic allocates an XtExcFrame plus a C environment on whatever sp it is
 * given, and the fatal vectors are exactly the case where that sp is no longer
 * trustworthy -- hence a stack of our own, sized for the frame plus the
 * window spills of the walk it does. */
#define RT_S3_PANIC_STACK_SIZE 1024

    .section .bss.rt_panic_stack, "aw", @nobits
    .align  16
rt_xt_panic_stack:
    .space  RT_S3_PANIC_STACK_SIZE
rt_xt_panic_stack_end:

/* _rt_panic_halt: a2 = PANIC_RSN_*; does not return. */
    .section .iram1, "ax"
    .align  4
    .type   _rt_panic_halt, @function
_rt_panic_halt:
    rsil    a3, XCHAL_DEBUGLEVEL            /* mask everything maskable */
    wsr     a2, EXCCAUSE                    /* reason, as panicHandler expects */
    movi    sp, rt_xt_panic_stack_end
    call0   _xt_panic
.Lrt_halt_loop:
    nop
    nop
    j       .Lrt_halt_loop

/*
-------------------------------------------------------------------------------
  void rt_xt_panic_report(code, cause, epc, excvaddr, ra, sp) -- called from
  _rt_panic_halt with a C environment set up. Lives in cpuport.c.
-------------------------------------------------------------------------------
*/

    .begin      literal_prefix .Level2InterruptVector
    .section    .Level2InterruptVector.text, "ax"
    .global     _Level2Vector
    .align      4
_Level2Vector:
    wsr     a0, EXCSAVE_2
    rsr     a2, EPC_2
    wsr     a2, EPC_1
    movi    a2, 20  /* vector id, see _rt_panic_halt */
    j       _rt_panic_halt
    .end        literal_prefix

    .begin      literal_prefix .Level3InterruptVector
    .section    .Level3InterruptVector.text, "ax"
    .global     _Level3Vector
    .align      4
_Level3Vector:
    wsr     a0, EXCSAVE_3
    rsr     a2, EPC_3
    wsr     a2, EPC_1
    movi    a2, 30  /* vector id, see _rt_panic_halt */
    j       _rt_panic_halt
    .end        literal_prefix

    .begin      literal_prefix .Level4InterruptVector
    .section    .Level4InterruptVector.text, "ax"
    .global     _Level4Vector
    .align      4
_Level4Vector:
    wsr     a0, EXCSAVE_4
    rsr     a2, EPC_4
    wsr     a2, EPC_1
    movi    a2, 40  /* vector id, see _rt_panic_halt */
    j       _rt_panic_halt
    .end        literal_prefix

    .begin      literal_prefix .Level5InterruptVector
    .section    .Level5InterruptVector.text, "ax"
    .global     _Level5Vector
    .align      4
_Level5Vector:
    wsr     a0, EXCSAVE_5
    rsr     a2, EPC_5
    wsr     a2, EPC_1
    movi    a2, 50  /* vector id, see _rt_panic_halt */
    j       _rt_panic_halt
    .end        literal_prefix

    .begin      literal_prefix .DebugExceptionVector
    .section    .DebugExceptionVector.text, "ax"
    .global     _DebugExceptionVector
    .align      4
_DebugExceptionVector:
    wsr     a0, EXCSAVE + XCHAL_DEBUGLEVEL
    rsr     a2, EPC + XCHAL_DEBUGLEVEL
    wsr     a2, EPC_1
    movi    a2, PANIC_RSN_DEBUGEXCEPTION
    j       _rt_panic_halt
    .end        literal_prefix

    .begin      literal_prefix .NMIExceptionVector
    .section    .NMIExceptionVector.text, "ax"
    .global     _NMIExceptionVector
    .align      4
_NMIExceptionVector:
    wsr     a0, EXCSAVE + XCHAL_NMILEVEL
    movi    a2, 60  /* vector id, see _rt_panic_halt */
    j       _rt_panic_halt
    .end        literal_prefix

    .begin      literal_prefix .KernelExceptionVector
    .section    .KernelExceptionVector.text, "ax"
    .global     _KernelExceptionVector
    .align      4
_KernelExceptionVector:
    wsr     a0, EXCSAVE_1
    movi    a2, PANIC_RSN_KERNELEXCEPTION
    j       _rt_panic_halt
    .end        literal_prefix

    .begin      literal_prefix .DoubleExceptionVector
    .section    .DoubleExceptionVector.text, "ax"
    .global     _DoubleExceptionVector
    .align      4
_DoubleExceptionVector:
    /* No "break 1,4" here (IDF uses it to hand control to a debug agent): a
     * debug exception would overwrite EPC_1 with the double vector's own PC
     * and throw away the original cause we are trying to read. On a double
     * exception EPC_1/EPS_1/EXCCAUSE still describe the first exception, and
     * the double vector's own PC is in DEPC -- so just report.
     * IDF also does `wsr a0, EXCSAVE_1` first (to clear a debugger single
     * step); we skip that because EXCSAVE_1 holds the first fault's a0, i.e.
     * the return address of the frame that faulted, which is the one piece of
     * the picture EPC_1 cannot give. */
    movi    a2, PANIC_RSN_DOUBLEEXCEPTION
    j       _rt_panic_halt
    .end        literal_prefix

/*
-------------------------------------------------------------------------------
  USER EXCEPTION VECTOR (VECBASE+0x340): level-1 interrupts AND exceptions
  taken while PS.EXCM=0. Mirrors _xt_user_exc. Coprocessor-disabled causes
  (>= EXCCAUSE_CP0_DISABLED) cannot happen: this port never clears CPENABLE.
-------------------------------------------------------------------------------
*/

    .begin      literal_prefix .UserExceptionVector
    .section    .UserExceptionVector.text, "ax"
    .global     _UserExceptionVector
    .type       _UserExceptionVector, @function
    .align      4
_UserExceptionVector:
    wsr     a0, EXCSAVE_1
    call0   _rt_user_exc
    /* never returns here - call0 is used as a jump */
    .end        literal_prefix

    .section .iram1, "ax"
    .literal_position
    .align  4
    .type   _rt_user_exc, @function
_rt_user_exc:
    rsr     a0, EXCCAUSE
    beqi    a0, EXCCAUSE_LEVEL1INTERRUPT, _rt_lowint1
    bnei    a0, EXCCAUSE_ALLOCA, .Lrt_not_alloca
    J       _rt_alloca_exc                /* long branch into window vectors */
.Lrt_not_alloca:

    /* Any other exception: full frame so the C handler can print state. */
    mov     a0, sp
    addi    sp, sp, -XT_STK_FRMSZ
    s32i    a0, sp, XT_STK_A1
    s32e    a0, sp, -12                   /* debug backtrace base-save slot */
    rsr     a0, PS                          /* interruptee's PS, as IDF stores it */
    s32i    a0, sp, XT_STK_PS
    rsr     a0, EPC_1
    s32i    a0, sp, XT_STK_PC
    rsr     a0, EXCSAVE_1
    s32i    a0, sp, XT_STK_A0
    s32e    a0, sp, -16
    s32i    a12, sp, XT_STK_A12
    s32i    a13, sp, XT_STK_A13
    call0   _xt_context_save
    rsr     a0, EXCCAUSE
    s32i    a0, sp, XT_STK_EXCCAUSE
    rsr     a0, EXCVADDR
    s32i    a0, sp, XT_STK_EXCVADDR

    mov     a10, sp                       /* the frame is the handler's argument */
    movi    a0, rt_xt_isr_frame
    s32i    a10, a0, 0                    /* same ISR-stack move as _rt_lowint1 */
    movi    sp, rt_xt_isr_stack_end

    movi    a0, PS_INTLEVEL(1) | PS_UM | PS_WOE
    wsr     a0, PS                        /* C environment */
    rsync

    call8   rt_xt_exception_handler       /* prints, never returns */

/*
-------------------------------------------------------------------------------
  LEVEL 1 INTERRUPT. Frame on the interrupted thread's stack (exactly
  _xt_lowint1's prologue), then the C dispatch on rt_xt_isr_stack, then the
  RT-Thread switch-in via the globals that
  rt_hw_context_switch_interrupt() filled in.
-------------------------------------------------------------------------------
*/

/*
 * Interrupt stack for C-level ISR code, and the word that remembers the
 * exception frame while C runs elsewhere.
 *
 * A windowed-ABI function spill needs 64 bytes below its own sp, and an
 * exception frame is only XT_STK_FRMSZ (192) bytes with most of that holding
 * saved registers. Running the ISR C code directly on the frame therefore
 * turns frame slots into spill links: a window overflow inside a handler would
 * take its link out of a register slot and store through it. ESP-IDF makes the
 * same move in _frxt_int_enter (pxCurrentTCB->pxTopOfStack, then port_IntStack).
 *
 * v1 is single-core and runs the C dispatch at PS.INTLEVEL = 1, which masks
 * every level-1 source, so one stack and one frame slot are enough.
 */
#define RT_S3_ISR_STACK_SIZE 2048

    .section .bss.rt_isr_stack, "aw", @nobits
    .align  16
rt_xt_isr_stack:
    .space  RT_S3_ISR_STACK_SIZE
rt_xt_isr_stack_end:

    .section .bss.rt_isr_frame, "aw", @nobits
    .align  4
rt_xt_isr_frame:
    .space  4

    .section .iram1, "ax"
    .align  4
    .type   _rt_lowint1, @function
    .global _rt_lowint1
_rt_lowint1:
    mov     a0, sp
    addi    sp, sp, -XT_STK_FRMSZ
    s32i    a0, sp, XT_STK_A1
    rsr     a0, PS
    s32i    a0, sp, XT_STK_PS
    rsr     a0, EPC_1
    s32i    a0, sp, XT_STK_PC
    rsr     a0, EXCSAVE_1
    s32i    a0, sp, XT_STK_A0
    movi    a0, _rt_user_exit
    s32i    a0, sp, XT_STK_EXIT

    s32i    a12, sp, XT_STK_A12           /* _xt_context_save expects these */
    s32i    a13, sp, XT_STK_A13           /* already written into the frame */
    call0   _xt_context_save              /* windows + a2-a15 + extra state */

    movi    a0, rt_xt_isr_frame
    s32i    sp, a0, 0                     /* publish the frame ... */
    movi    sp, rt_xt_isr_stack_end       /* ... and leave it for the C code */
    l32i    a0, a0, 0

    /* Copy the pre-exception base save area below the new sp. This is not
       only for the debugger: a windowed spill handler fetches the previous
       frame's sp from [sp-12], and on a stack this fresh ([sp-12] is zeroed
       .bss) that read would become a store through a null link. Same block in
       IDF's xtensa_vectors.S, whose a0 synthesis is left out here because
       nothing unwinds this stack. */
    l32i    a3, a0, XT_STK_A0
    s32e    a3, sp, -16
    l32i    a3, a0, XT_STK_A1
    s32e    a3, sp, -12

    movi    a0, PS_INTLEVEL(1) | PS_UM | PS_WOE
    wsr     a0, PS                        /* C environment (EPS_1 write, like IDF) */
    rsync

    call8   rt_xt_irq_process             /* dispatch */

    movi    a0, rt_thread_switch_interrupt_flag
    l32i    a1, a0, 0
    beqz    a1, .Lrt_irq_noswitch
    movi    a1, 0
    s32i    a1, a0, 0                     /* consume the request */
    movi    a2, rt_xt_isr_frame
    l32i    a2, a2, 0                     /* the frame C was away from */
    movi    a0, rt_interrupt_from_thread
    l32i    a0, a0, 0
    s32i    a2, a0, 0                     /* from_thread->sp = frame base */
    movi    a0, rt_interrupt_to_thread
    l32i    a0, a0, 0                     /* a0 = &to_thread->sp */
    l32i    sp, a0, 0                     /* sp = to_thread->sp */
    j       _rt_s3_dispatch
.Lrt_irq_noswitch:
    movi    sp, rt_xt_isr_frame
    l32i    sp, sp, 0                     /* resume the interrupted frame */
    j       _rt_s3_dispatch               /* not fall through: the .align below
                                             is filled with non-instructions */

/*
-------------------------------------------------------------------------------
  _rt_s3_dispatch -- resume the thread whose frame base is in sp.
  Same shape and same frame test as ESP-IDF's _frxt_dispatch: the word at
  offset 0 is 0 for a thread that yielded the CPU in rt_hw_context_switch(),
  and otherwise the address of the exit dispatcher of an XtExcFrame (built by
  _rt_lowint1 for a preempted thread, or by rt_hw_stack_init() for one that has
  never run).
  Reached by `j`, with interrupts masked, from the level-1 vector's tail and
  from both context switch functions below.
-------------------------------------------------------------------------------
*/

    .align  4
    .type   _rt_s3_dispatch, @function
_rt_s3_dispatch:
    l32i    a2, sp, XT_STK_EXIT
    beqz    a2, _rt_s3_sol_return
    /* _xt_context_restore returns to the word after this call, so reaching the
     * exit dispatcher needs an explicit jump: the next label is .align 4 and
     * the assembler fills the gap with bytes that are not a valid instruction,
     * so falling through would execute that fill. */
    call0   _xt_context_restore
    j       _rt_user_exit

/*
-------------------------------------------------------------------------------
  Exit dispatcher (== IDF _xt_user_exit): restore PS/PC/a0, pop the frame,
  rfe. Referenced from every interrupt/initial XtExcFrame at XT_STK_EXIT.
-------------------------------------------------------------------------------
*/

    .global  _rt_user_exit
    .type    _rt_user_exit, @function
    .align   4
_rt_user_exit:
    l32i    a0, sp, XT_STK_PS
    wsr     a0, PS
    l32i    a0, sp, XT_STK_PC
    wsr     a0, EPC_1
    l32i    a0, sp, XT_STK_A0
    l32i    sp, sp, XT_STK_A1
    rsync
    rfe

/*
-------------------------------------------------------------------------------
  _rt_s3_sol_return -- resume the thread whose solicited frame sp points at,
  the way ESP-IDF's _frxt_dispatch_sol does: restore what such a frame carries
  (threadptr, PS, return address) and `retw` into it. Only _rt_s3_dispatch
  reaches it, and only for a frame marked RT_S3_SOL_YIELDED -- the thread that
  left it owns a window chain, spilled by rt_hw_context_switch() below, and the
  refill that `retw` triggers reads that chain. It must be a jump, not a call:
  `call0` would overwrite the a0 just loaded from the frame.
-------------------------------------------------------------------------------
*/

    .align  4
    .type   _rt_s3_sol_return, @function
_rt_s3_sol_return:
    l32i    a2, sp, XT_SOL_THREADPTR
    wur.threadptr a2
    l32i    a0, sp, XT_SOL_PC
    /* Solicited frames always hold a C-context PS (EXCM=0), so WSR.PS can
     * install it even though that lowers INTLEVEL back to what the incoming
     * thread ran with. PS.OWB/CALLINC are write-masked: the window rotation
     * therefore stays the switcher's own, which is precisely what makes this
     * return land inside another thread's call chain. */
    l32i    a3, sp, XT_SOL_PS
    wsr     a3, PS
    retw

/*
-------------------------------------------------------------------------------
  void rt_hw_context_switch(rt_ubase_t from, rt_ubase_t to)
  Cooperative switch, mirroring vPortYield + _frxt_dispatch: save the solicited
  frame (pc/ps/threadptr, plus RT_S3_SOL_YIELDED in the exit slot that marks the
  frame type), let xthal_window_spill_nw put the caller's a0-a3 in the frame's
  base-save area, *from = frame base, then hand over through _rt_s3_dispatch.
  No coprocessor handling: CPENABLE is 0 in this BSP, so neither thread has any
  coprocessor state to move.
-------------------------------------------------------------------------------
*/

    .align  4
    .global rt_hw_context_switch
    .type   rt_hw_context_switch, @function
rt_hw_context_switch:
    entry   sp, XT_SOL_FRMSZ

    rsr     a4, PS
    s32i    a0, sp, XT_SOL_PC
    s32i    a4, sp, XT_SOL_PS
    rur.threadptr a5
    s32i    a5, sp, XT_SOL_THREADPTR
    movi    a5, RT_S3_SOL_YIELDED
    s32i    a5, sp, XT_SOL_EXIT           /* marks it solicited for the resume */

    /* Both argument registers are scratch for xthal_window_spill_nw, which
       opens with `rsr a2, WINDOWBASE` and rotates windows to walk them, so
       publish *from while a2 still holds it, and park `to` in memory. */
    s32i    sp, a2, 0                     /* *from = solicited frame base */
    movi    a2, rt_xt_s3_sol_to
    s32i    a3, a2, 0

    /* Window spill: EXCM already clear (C code); disable WOE and raise
       INTLEVEL to EXCM_LEVEL so no interrupt preempts the spill. */
    movi    a6, ~(PS_WOE_MASK | PS_INTLEVEL_MASK)
    and     a4, a4, a6
    addi    a4, a4, XCHAL_EXCM_LEVEL
    wsr     a4, PS
    rsync
    call0   xthal_window_spill_nw
    l32i    a4, sp, XT_SOL_PS
    wsr     a4, PS

    rsil    a4, XCHAL_EXCM_LEVEL          /* keep interrupts off for the swap */

    movi    a3, rt_xt_s3_sol_to
    l32i    a3, a3, 0                     /* a3 = &to_thread->sp */
    l32i    sp, a3, 0                     /* sp     = to_thread->sp */
    j       _rt_s3_dispatch

/*
-------------------------------------------------------------------------------
  void rt_hw_context_switch_to(rt_ubase_t to)
  First switch out of rt_system_scheduler_start(). to_thread->sp is the
  exception frame rt_hw_stack_init() built, so this is the same resume the
  vector's tail performs: restore it and leave through the exit dispatcher,
  whose `rfe` is what installs the thread's UM/OWB/CALLINC -- a `wsr` may not
  write those while the switcher still has PS.INTLEVEL raised.
-------------------------------------------------------------------------------
*/

    .align  4
    .global rt_hw_context_switch_to
    .type   rt_hw_context_switch_to, @function
rt_hw_context_switch_to:
    entry   sp, 32                        /* the ABI's minimum windowed frame */
    rsil    a3, XCHAL_EXCM_LEVEL          /* no interrupt may see the half-swap */
    l32i    sp, a2, 0                     /* sp = to_thread->sp */
    j       _rt_s3_dispatch

/*
-------------------------------------------------------------------------------
  void rt_hw_context_switch_interrupt(rt_ubase_t from, rt_ubase_t to, ...)
  Records the pending pair for _rt_lowint1's exit path. Same semantics as the
  RISC-V weak implementation (first caller wins; nested rt_schedule() inside
  one interrupt must not overwrite the interrupted thread).
-------------------------------------------------------------------------------
*/

    .align  4
    .global rt_hw_context_switch_interrupt
    .type   rt_hw_context_switch_interrupt, @function
rt_hw_context_switch_interrupt:
    entry   sp, 32
    movi    a4, rt_thread_switch_interrupt_flag
    l32i    a5, a4, 0
    bnez    a5, .Lrt_swirec_to
    movi    a5, rt_interrupt_from_thread
    s32i    a2, a5, 0
.Lrt_swirec_to:
    movi    a5, rt_interrupt_to_thread
    s32i    a3, a5, 0
    movi    a5, 1
    s32i    a5, a4, 0
    retw

/*
-------------------------------------------------------------------------------
  rt_base_t rt_hw_interrupt_disable(void);  void rt_hw_interrupt_enable(level)

  RT-Thread passes an opaque token from disable to enable, and this port's
  token is the *full* PS: rt_hw_interrupt_enable writes it back with WSR.PS.
  RSIL returns the old INTLEVEL only, so it cannot be the token -- handing a
  bare level to WSR.PS would install PS = 0..6, clearing UM/OWB/WOE; with WOE
  off, the next window overflow/underflow is reported as IllegalInstruction
  and the kernel dies in the first call/ret after re-enabling interrupts.
  So: snapshot PS first, then RSIL to XCHAL_EXCM_LEVEL (3 here, which masks
  every interrupt level v1 uses) and return the snapshot.
-------------------------------------------------------------------------------
*/

    .align  4
    .global rt_hw_interrupt_disable
    .type   rt_hw_interrupt_disable, @function
rt_hw_interrupt_disable:
    /* 32, not 16: the windowed ABI's minimum frame, because these are call8
       targets from C and the caller's 16-byte incoming area must not overlap
       this frame's own spill save area. */
    entry   sp, 32
    rsr     a3, PS                      /* full PS before masking */
    rsil    a2, XCHAL_EXCM_LEVEL        /* a2 = old INTLEVEL only, discarded */
    mov     a2, a3
    retw

    .align  4
    .global rt_hw_interrupt_enable
    .type   rt_hw_interrupt_enable, @function
rt_hw_interrupt_enable:
    entry   sp, 32
    wsr     a2, PS                      /* full PS from rt_hw_interrupt_disable */
    rsync
    retw

/*
-------------------------------------------------------------------------------
  Coprocessor bookkeeping used by ESP-IDF's xtensa_context.S: when an
  interrupt or a context switch has to move coprocessor state, _xt_context_save
  / _xt_context_restore ask the RTOS, through XT_RTOS_CP_STATE
  (_frxt_task_coproc_state below), for the save area of the thread that owns it
  and record that owner in _xt_coproc_owner_sa[]. Both are therefore WRITABLE
  data -- putting the owner array in a read-only section makes IDF's save store
  fault with EXCCAUSE 29 (StoreProhibited). Sizes and layouts follow the
  ESP-IDF definitions; the owner array is sized for this single-core part.
-------------------------------------------------------------------------------
*/
#if XCHAL_CP_NUM > 0
    .section .rodata, "a"
    .global  _xt_coproc_sa_offset
    .type    _xt_coproc_sa_offset, @object
    .align   16
_xt_coproc_sa_offset:
    .word   XT_CP0_SA, XT_CP1_SA, XT_CP2_SA, XT_CP3_SA
    .word   XT_CP4_SA, XT_CP5_SA, XT_CP6_SA, XT_CP7_SA

    .section .bss.rt_coproc, "aw", @nobits
    .global  _xt_coproc_owner_sa
    .type    _xt_coproc_owner_sa, @object
    .align   16,,XCHAL_CP_MAX<<2
_xt_coproc_owner_sa:
    .space  (XCHAL_CP_MAX) << 2

    .section .iram1, "ax"
    .global  _frxt_task_coproc_state
    .type    _frxt_task_coproc_state, @function
    .align   4
_frxt_task_coproc_state:
    /* XT_RTOS_CP_STATE hook: ESP-IDF's lazy coprocessor code asks the RTOS for
     * the save area of the thread that owns the coprocessors. This BSP leaves
     * CPENABLE at 0 (see cp_disable_all() in cpuport.c), so
     * _xt_coproc_savecs()/_xt_coproc_restorecs() return at their first test and
     * never get here; answering "no owner" is also the only correct answer
     * because no thread has a coprocessor save area. Entered with call0, so
     * only a15 (the result) may be written. */
    movi    a15, 0
    ret
#endif /* XCHAL_CP_NUM > 0 */
