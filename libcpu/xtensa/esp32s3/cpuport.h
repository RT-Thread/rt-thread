/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-09-27     RT-Thread    ESP32-S3 (Xtensa LX7) port helpers
 */

#ifndef __CPU_PORT_H__
#define __CPU_PORT_H__

/*
 * Frame layouts come straight from Espressif's Xtensa port:
 * <xtensa/xtensa_context.h> defines XtExcFrame (XT_STK_*) and XtSolFrame
 * (XT_SOL_*) with offsets that are visible to C and to the assembler alike.
 *
 * This port uses both, and which one a thread is sitting in is recorded in the
 * frame's first word -- the slot ESP-IDF's _frxt_dispatch tests the same way:
 *
 *   XtExcFrame, first word = the exit dispatcher (_rt_user_exit). Created by
 *   the level-1 vector on the stack of a running thread, and by
 *   rt_hw_stack_init() as a thread's initial context (mirroring
 *   pxPortInitialiseStack()/uxInitialiseStackFrame() in ESP-IDF). Resumed with
 *   `rfe`, which is the only instruction that can install a thread's UM, OWB
 *   and CALLINC: a `wsr` may not write those while PS.INTLEVEL is non-zero, and
 *   every switcher has interrupts masked.
 *
 *   XtSolFrame, first word = RT_S3_SOL_YIELDED. Created by
 *   rt_hw_context_switch() when a thread gives the CPU away. Resumed with
 *   `retw`, whose register refill walks the window chain that that thread
 *   spilled when it yielded; a thread that has never run has no such chain, so
 *   a `retw` into its frame would refill a1 from whatever the *switching*
 *   thread had left there and the new thread would run on the wrong stack.
 *
 * The top 16 bytes of an XtSolFrame are the base-save area the window spill
 * writes and the window-underflow vector reads, so a solicited frame is never
 * smaller than the 32 bytes XT_SOL_FRMSZ says and this port does not touch
 * those slots.
 *
 * Coprocessors (FPU = CP0, AI = CP3) are left disabled: CPENABLE stays 0 (see
 * cp_disable_all in cpuport.c), so no thread carries a coprocessor save area,
 * XT_RTOS_CP_STATE is never asked, and IDF's _xt_coproc_savecs/_restorecs
 * return at their first test.
 */

#ifndef __ASSEMBLER__
#include <xtensa/xtensa_context.h>
#endif

/* What rt_hw_context_switch() writes into a yielding thread's frame at
 * XT_SOL_EXIT, to mark it as the solicited kind. */
#define RT_S3_SOL_YIELDED         0

#endif /* __CPU_PORT_H__ */
