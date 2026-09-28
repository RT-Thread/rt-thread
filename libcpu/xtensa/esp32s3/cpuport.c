/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-09-27     RT-Thread    ESP32-S3 (Xtensa LX7) C glue for context_gcc.S
 *
 * Coprocessor policy (see also context_gcc.S): v1 of this BSP runs with
 * CPENABLE cleared, i.e. neither the FPU (CP0) nor the AI accelerator (CP3) is
 * enabled for any thread. Nothing in the linked image executes a coprocessor
 * instruction (checked over the disassembly of every component this BSP builds
 * in), and Wi-Fi/BLE/AI code is not part of v1; an accidental FP/AI access
 * therefore surfaces as a CoprocessorDisabled exception reported by
 * rt_xt_exception_handler instead of silently corrupting a save area.
 *
 * Keeping the coprocessors off is also what lets the port stay small: no
 * per-thread XtSysCoProcInfo area has to be reserved at the top of every stack
 * (XT_CP_SIZE is 456 bytes on this part), and ESP-IDF's lazy coprocessor
 * machinery -- _xt_coproc_savecs()/_xt_coproc_restorecs(), which ask the RTOS
 * for the owning thread's save area through XT_RTOS_CP_STATE -- returns at its
 * first "CPENABLE == 0" test and never runs. Those routines are still
 * assembled into xtensa_context.o, so the symbols they reference exist there
 * with the right size, in writable memory, and are unused.
 *
 * Level >= 2 interrupts are not handled (the vectors panic), so ISRs must be
 * allocated with ESP_INTR_FLAG_LEVEL1.
 *
 * Frame types (see context_gcc.S for the assembly): there are two, and the
 * resume path picks one by the word at offset 0 of the frame -- 0 means a
 * solicited frame left by a thread that gave the CPU away, anything else is the
 * exit dispatcher of an exception frame. That is ESP-IDF's own convention
 * (_frxt_dispatch tests XT_STK_EXIT the same way), and it gives each of the two
 * ways a thread stops its own resume instruction:
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

/* ---- coprocessors: off for v1 (see the file header for why) ------------
 *
 * CPENABLE is cleared here rather than left to the reset value because IDF's
 * startup and ROM code are free to enable the FPU for themselves, and this
 * port's resume path must know what state a thread wakes up in. With the
 * register at 0, ESP-IDF's _xt_coproc_savecs/_xt_coproc_restorecs return
 * immediately and no thread stack has to carry a coprocessor save area.
 */
static void cp_disable_all(void)
{
    const rt_uint32_t none = 0;

    __asm__ volatile("wsr %0, cpenable; rsync" ::"r"(none) : "memory");
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
 * A stack has to be comfortably bigger than the frame it starts with: the
 * thread's initial context is an XT_STK_FRMSZ-byte exception frame sitting at
 * the top of the array, the windowed ABI additionally spills to the base-save
 * area below its sp, and the first interrupt it takes pushes a second whole
 * exception frame there. The kernel's own threads default to a few hundred
 * bytes, in which case the initial frame lands below thread->stack_addr and
 * whatever the heap allocator parked there gets overwritten. The checks below
 * make that a build error instead.
 */
#define RT_S3_STACK_MIN (XT_STK_FRMSZ + 16 + 256)

#ifdef RT_USING_IDLE_OBJECT
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
 * The frame a thread starts in, mirroring uxInitialiseStackFrame() in
 * ESP-IDF's Xtensa FreeRTOS port: an *interrupt/exception* frame, resumed
 * through the exit dispatcher (_rt_user_exit in context_gcc.S) exactly like a
 * thread that was preempted by an interrupt.
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
 * PS_CALLINC(1) makes the entry point behave as if it had been reached by
 * `call4`, so the argument registers of that call are the frame's a4..a7: a6
 * becomes the entry's a2, i.e. the thread's parameter. a0 = 0 terminates a
 * backtrace, and texit is not used: the kernel's threads never return
 * (src/thread.c runs _thread_exit and does not come back).
 */
rt_uint8_t *rt_hw_stack_init(void *tentry, void *parameter,
                             rt_uint8_t *stack_addr, void *texit)
{
    static int cp_disabled;
    /* The kernel passes stack_addr + stack_size - sizeof(rt_ubase_t) as the
     * top (src/thread.c); put the 4 back so the frame is placed flush below the
     * end of the array rather than up to 16 bytes lower on some alignments. */
    rt_ubase_t top = (rt_ubase_t)stack_addr + sizeof(rt_ubase_t);
    rt_ubase_t frame = (top - XT_STK_FRMSZ) & ~15U;
    XtExcFrame *f = (XtExcFrame *)frame;

    (void)texit;   /* threads never return; see _thread_exit in src/thread.c */

    if (!cp_disabled)
    {
        cp_disabled = 1;
        cp_disable_all();
    }

    /* Every slot of the frame is read by _xt_context_restore / _rt_user_exit,
     * so nothing here may be left uninitialized. */
    rt_memset((void *)frame, 0, XT_STK_FRMSZ);

    f->pc = (rt_ubase_t)tentry;
    f->a0 = 0;                        /* terminate a backtrace */
    f->a1 = frame + XT_STK_FRMSZ;     /* the thread's own sp, above the frame */
    f->exit = (rt_ubase_t)_rt_user_exit;/* the resume path's tail jumps here */
    f->a6 = (rt_ubase_t)parameter;
    f->ps = PS_UM | PS_EXCM | PS_WOE | PS_CALLINC(1);

    /* First word of the non-coprocessor extra save area (threadptr); this BSP
     * sets up no TLS. */
    *(rt_uint32_t *)(frame + XT_STK_EXTRA) = 0;

    return (rt_uint8_t *)frame;
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
