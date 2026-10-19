/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-09-27     RT-Thread    ESP32-S3 (Xtensa LX7) port helpers
 * 2026-10-10     RT-Thread    Add eager FPU (CP0) save/restore constants
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
 *   XtExcFrame: the first word of the XtExcFrame itself is still the exit
 *   dispatcher (_rt_user_exit), set by rt_hw_stack_init() and _rt_lowint1.
 *   An FP save block of RT_S3_FP_BLOCK_SIZE bytes sits below the XtExcFrame
 *   on the thread's stack; thread->sp points at the FP block, not the
 *   XtExcFrame. The first word of the FP block (at thread->sp) is
 *   RT_S3_FP_FRAME_MARK, which lets _rt_s3_dispatch distinguish it from a
 *   solicited frame. The FP block carries FCR, FSR, and f0-f15 -- every
 *   level-1 interrupt saves them eagerly, and _rt_s3_dispatch restores them
 *   before calling _xt_context_restore and jumping to _rt_user_exit.
 *
 *   XtSolFrame: first word = RT_S3_SOL_YIELDED. Created by
 *   rt_hw_context_switch() when a thread gives the CPU away. Resumed with
 *   `retw`, whose register refill walks the window chain that that thread
 *   spilled when it yielded. The frame is RT_S3_SOL_FRMSZ (XT_SOL_FRMSZ + 16)
 *   bytes: the standard 32 bytes plus 16 bytes that hold FCR/FSR at
 *   RT_S3_SOL_FCR / RT_S3_SOL_FSR (the window spill's base-save area moves to
 *   sp+0x20..0x2F with the larger frame, leaving sp+0x10..0x1F free).
 *
 * The FPU (CP0) is enabled: CPENABLE has bit 0 set (see cp_enable_fpu in
 * cpuport.c). The AI/SIMD coprocessor (CP3) stays disabled. CP state is
 * saved/restored eagerly on every interrupt and cooperative switch, so there
 * is no per-thread save area and no lazy owner tracking. ESP-IDF's lazy
 * coprocessor machinery (_xt_coproc_savecs() / _xt_coproc_restorecs() /
 * _frxt_task_coproc_state) is never invoked by this port.
 */

#ifndef __ASSEMBLER__
#include <xtensa/xtensa_context.h>
#endif

/* What rt_hw_context_switch() writes into a yielding thread's frame at
 * XT_SOL_EXIT, to mark it as the solicited kind. */
#define RT_S3_SOL_YIELDED 0

/* Solicited frame size: XT_SOL_FRMSZ (32) + 16 bytes for FCR/FSR.
 * With entry sp,RT_S3_SOL_FRMSZ the window spill's base-save area lands at
 * sp+0x20..0x2F, leaving sp+0x10..0x1F free for FCR and FSR. */
#define RT_S3_SOL_FRMSZ (XT_SOL_FRMSZ + 16)
#define RT_S3_SOL_FCR   0x10
#define RT_S3_SOL_FSR   0x14

/* FP save block: sits below every XtExcFrame (interrupt-preempted thread and
 * initial thread frame). thread->sp points at the block. The marker at
 * offset 0 lets _rt_s3_dispatch tell this from a solicited frame (whose
 * first word is 0). Total size is padded to 16-byte alignment so both
 * thread->sp and the XtExcFrame above stay 16-byte aligned. */
#define RT_S3_FP_BLOCK_SIZE 80
#define RT_S3_FP_MARKER_OFS 0
#define RT_S3_FP_FCR        4
#define RT_S3_FP_FSR        8
#define RT_S3_FP_F0         12      /* fN at RT_S3_FP_F0 + 4*N */
#define RT_S3_FP_FRAME_MARK 0x46505530  /* "FPU0" */

#endif /* __CPU_PORT_H__ */
