/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-09-27     RT-Thread    ESP32-S3 (Xtensa LX7) C glue for context_gcc.S
 *
 * Coprocessor policy (see also context_gcc.S): the FPU (CP0) is enabled
 * (CPENABLE bit 0) so that applications can use single-precision float
 * arithmetic. Every level-1 interrupt saves the full FP state eagerly
 * (FCR/FSR/f0-f15) below the XtExcFrame, and cooperative switches save
 * FCR/FSR into the solicited frame. AI/SIMD (CP3) stays disabled; using
 * CP3 instructions triggers a CoprocessorDisabled exception reported by
 * rt_xt_exception_handler.
 *
 * Because CP state is handled eagerly, there is no per-thread coprocessor
 * save area on the stack (XT_CP_SIZE = 456 bytes is not reserved). ESP-IDF's
 * lazy coprocessor machinery (_xt_coproc_savecs() / _xt_coproc_restorecs() /
 * _frxt_task_coproc_state) is never invoked by this port: _xt_context_save()
 * and _xt_context_restore() do not call them, and no other code path does.
 *
 * Level >= 2 interrupts are not handled (the vectors panic), so ISRs must be
 * allocated with ESP_INTR_FLAG_LEVEL1.
 *
 * Frame types (see context_gcc.S for the assembly): there are two, and the
 * resume path (_rt_s3_dispatch) picks one by the word at offset 0 of the
 * frame -- 0 means a solicited frame left by a thread that gave the CPU away,
 * RT_S3_FP_FRAME_MARK means an FP save block below an exception frame
 * (preempted thread or initial thread). That is a change from the original
 * ESP-IDF convention where the exit dispatcher address sat at offset 0; here
 * the FP block's marker takes that slot and the XtExcFrame sits above it.
 *   - a thread that yields in rt_hw_context_switch() owns a real register-window
 *     chain, so it is resumed with `retw` and its registers refill from that
 *     chain;
 *   - a thread that was interrupted, and a thread that has never run, are both
 *     resumed through the exit dispatcher with `rfe` -- for the second case that
 *     is the only way its UM/OWB/CALLINC can be installed, and it is what
 *     pxPortInitialiseStack()/uxInitialiseStackFrame() do in ESP-IDF.
 */

#include <rtthread.h>
#include <rthw.h>

#include <xtensa/config/core.h>
#include <xtensa/corebits.h>
#include <xtensa/xtensa_context.h>
#include <xtensa/xtensa_api.h>
#include <xtensa/hal.h>

#include "esp_attr.h"

#include "cpuport.h"

/* ---- globals referenced by context_gcc.S (same names/semantics as the
 * ---- RISC-V common port, which this replaces for Xtensa) ---- */
#ifndef RT_USING_SMP
volatile rt_ubase_t rt_interrupt_from_thread = 0;
volatile rt_ubase_t rt_interrupt_to_thread = 0;
volatile rt_uint32_t rt_thread_switch_interrupt_flag = 0;
#endif

/* Handler/arg table maintained by ESP-IDF xtensa_intr.c (xt_set_interrupt_handler,
 * called from intr_alloc.c) and read by the level-1 dispatcher below exactly
 * like dispatch_c_isr in the ESP-IDF vectors. The entry struct is private to
 * xtensa_intr.c; this is its ABI (two words: handler, arg — see
 * xtensa_intr_asm.S table init), single-core so index == interrupt number. */
struct xt_int_entry
{
    void (*handler)(void *);
    void *arg;
};
extern struct xt_int_entry _xt_interrupt_table[];

/* the exit dispatcher in context_gcc.S, referenced by every thread's frame */
extern void _rt_user_exit(void);

/* ---- coprocessors: FPU on, AI off ----------------------------------------
 *
 * CPENABLE is set here (rather than left to the reset value) because IDF's
 * startup and ROM code may have changed it. This port enables CP0 (FPU) so
 * that float arithmetic works, and leaves CP3 (AI/SIMD) off. The eager
 * save/restore in context_gcc.S means every interrupt and cooperative switch
 * moves FP state, so no per-thread save area is needed.
 */
static void cp_enable_fpu(void)
{
    const rt_uint32_t cpenable = (1 << 0);   /* CP0 only, CP3 off */

    __asm__ volatile("wsr %0, cpenable; rsync" ::"r"(cpenable) : "memory");
}

/* ---- interrupt dispatch (called from _rt_lowint1 with a C environment) ---- */
void rt_xt_irq_process(void)
{
    rt_ubase_t enabled, active, pending;

    rt_interrupt_enter();
    do
    {
        __asm__ __volatile__("rsr %0, intenable" : "=r"(enabled));
        __asm__ __volatile__("rsr %0, interrupt" : "=r"(active));
        pending = enabled & active & XCHAL_INTLEVEL1_MASK;
        if (!pending)
        {
            break;
        }

        int n = 31 - __builtin_clz(pending);     /* MSB first, like IDF */
        __asm__ __volatile__("wsr %0, intclear; rsync" ::"r"(1u << n));

        /* Same table ESP-IDF's own dispatcher walks, so every driver that did
         * allocate a level-1 handler here (the tick, gptimer, esp_timer) runs. */
        if (_xt_interrupt_table[n].handler)
        {
            _xt_interrupt_table[n].handler(_xt_interrupt_table[n].arg);
        }
    } while (1);
    rt_interrupt_leave();
}

/* ---- exception report for non-interrupt user exceptions ---- */
void rt_xt_exception_handler(XtExcFrame *frame)
{
    /* esp_rom_printf, not rt_kprintf: this can fire before RT-Thread's
     * console device exists (e.g. from ESP-IDF startup, before the first
     * context switch). */
    extern int esp_rom_printf(const char *fmt, ...);
    esp_rom_printf("\nXtensa exception %u at 0x%08x (EXCVADDR 0x%08x, PS 0x%08x, A1 0x%08x)\n",
                   (unsigned)frame->exccause, (unsigned)frame->pc,
                   (unsigned)frame->excvaddr, (unsigned)frame->ps, (unsigned)frame->a1);
    esp_rom_printf("A0=0x%08x A2=0x%08x A3=0x%08x A4=0x%08x SAR=0x%x\n",
                   (unsigned)frame->a0, (unsigned)frame->a2, (unsigned)frame->a3,
                   (unsigned)frame->a4, (unsigned)frame->sar);
    while (1)
    {
        /* let the reset watchdog/POWERON bring us back */
    }
}

/* ---- thread startup frame ---- */

/*
 * Conservative headroom a thread stack needs beyond the frame it starts with.
 * The initial context is released the moment the thread first runs -- dispatch
 * restores sp above it -- so it does not stack with anything. What must fit:
 * one exception frame + FP block for a preemption that lands on top of the
 * initial frame, the initial frame + FP block itself (the first switch reads
 * them before sp moves), and spill space for the windowed ABI save area below
 * sp. The kernel's own threads default to a few hundred bytes, in which case
 * the initial frame lands below thread->stack_addr and whatever the heap
 * allocator parked there gets overwritten. The checks below make that a build
 * error instead.
 */
#define RT_S3_STACK_MIN (2 * (XT_STK_FRMSZ + RT_S3_FP_BLOCK_SIZE) + 64)

#ifdef IDLE_THREAD_STACK_SIZE
_Static_assert(IDLE_THREAD_STACK_SIZE >= RT_S3_STACK_MIN,
               "IDLE_THREAD_STACK_SIZE below the ESP32-S3 Xtensa minimum");
#endif
#ifdef RT_USING_TIMER_SOFT
_Static_assert(RT_TIMER_THREAD_STACK_SIZE >= RT_S3_STACK_MIN,
               "RT_TIMER_THREAD_STACK_SIZE below the ESP32-S3 Xtensa minimum");
#endif
#ifdef RT_USING_USER_MAIN
_Static_assert(RT_MAIN_THREAD_STACK_SIZE >= RT_S3_STACK_MIN,
               "RT_MAIN_THREAD_STACK_SIZE below the ESP32-S3 Xtensa minimum");
#endif

/*
 * Trampoline that wraps every thread's entry point. The windowed ABI starts
 * the thread in a clean register window (PS.CALLINC=1, as if reached by
 * call4), so a `retw` from the entry function has no caller window to return
 * to -- putting texit in a0 does not work. Instead, the frame's pc points
 * here, with entry/parameter/texit in a6/a7/a8 (the call4 argument slots),
 * and this function calls texit() explicitly when entry() returns.
 */
static void __attribute__((noinline))
rt_xt_thread_start(void (*entry)(void *), void *parameter, void (*texit)(void))
{
    entry(parameter);
    texit();
    while (1)
    {
        /* texit (_thread_exit) never returns; guard loop just in case */
    }
}

/*
 * The frame a thread starts in, mirroring uxInitialiseStackFrame() in
 * ESP-IDF's Xtensa FreeRTOS port: an *interrupt/exception* frame, resumed
 * through the exit dispatcher (_rt_user_exit in context_gcc.S) exactly like a
 * thread that was preempted by an interrupt. Below the XtExcFrame sits an
 * FP save block (RT_S3_FP_BLOCK_SIZE bytes) with the frame marker, FCR/FSR
 * and f0-f15 all zeroed; thread->sp points at the FP block base.
 *
 * It cannot be a solicited frame. A solicited frame is left behind by a thread
 * that has a register-window chain of its own, and resuming one is a `retw`
 * whose register refill walks that chain; a thread that has never run has no
 * chain, so there is nothing correct to refill. The exception return instead
 * hands the window state to the hardware: PS.EXCM in the frame makes `rfe`
 * install PS -- including UM, OWB and CALLINC, which a `wsr` may not write
 * while PS.INTLEVEL is non-zero, i.e. while the switcher has interrupts masked
 * -- and start the thread in a clean window.
 *
 * PS_CALLINC(1) makes the trampoline (rt_xt_thread_start) behave as if it had
 * been reached by `call4`, so the argument registers of that call are the
 * frame's a6..a8: a6 becomes entry, a7 becomes parameter, a8 becomes texit.
 * a0 = 0 terminates a backtrace; the trampoline never returns, so a0 is never
 * used as a return address.
 */
rt_uint8_t *rt_hw_stack_init(void *tentry, void *parameter,
                             rt_uint8_t *stack_addr, void *texit)
{
    static int fpu_enabled;
    /* The kernel passes stack_addr + stack_size - sizeof(rt_ubase_t) as the
     * top (src/thread.c); put the 4 back so the frame is placed flush below the
     * end of the array rather than up to 16 bytes lower on some alignments. */
    rt_ubase_t top = (rt_ubase_t)stack_addr + sizeof(rt_ubase_t);
    rt_ubase_t frame = (top - XT_STK_FRMSZ) & ~15U;
    XtExcFrame *f = (XtExcFrame *)frame;
    rt_ubase_t fp_block = frame - RT_S3_FP_BLOCK_SIZE;

    if (!fpu_enabled)
    {
        fpu_enabled = 1;
        cp_enable_fpu();
    }

    /* Every slot of the frame and FP block is read by _xt_context_restore /
     * _rt_s3_dispatch / _rt_user_exit, so nothing may be left uninitialized. */
    rt_memset((void *)frame, 0, XT_STK_FRMSZ);
    rt_memset((void *)fp_block, 0, RT_S3_FP_BLOCK_SIZE);

    /* Marker at FP block offset 0 so _rt_s3_dispatch recognises this as an
     * exception frame (not a solicited frame whose first word is 0). */
    *(rt_uint32_t *)fp_block = RT_S3_FP_FRAME_MARK;

    f->pc = (rt_ubase_t)rt_xt_thread_start;
    f->a0 = 0;                        /* terminate a backtrace */
    f->a1 = frame + XT_STK_FRMSZ;     /* the thread's own sp, above the frame */
    f->exit = (rt_ubase_t)_rt_user_exit;/* the resume path's tail jumps here */
    f->a6 = (rt_ubase_t)tentry;       /* trampoline arg 0: entry function */
    f->a7 = (rt_ubase_t)parameter;    /* trampoline arg 1: entry parameter */
    f->a8 = (rt_ubase_t)texit;        /* trampoline arg 2: thread exit handler */
    f->ps = PS_UM | PS_EXCM | PS_WOE | PS_CALLINC(1);

    /* First word of the non-coprocessor extra save area (threadptr); this BSP
     * sets up no TLS. */
    *(rt_uint32_t *)(frame + XT_STK_EXTRA) = 0;

    return (rt_uint8_t *)fp_block;    /* thread->sp = FP block base */
}

/* ---- misc port API ---- */
void rt_hw_cpu_reset(void)
{
    extern void esp_restart(void);
    esp_restart();
}

void rt_hw_cpu_shutdown(void)
{
    while (1)
    {
    }
}
