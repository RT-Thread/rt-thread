/*
 * arch/arm/include/asm/unwind.h
 *
 * Copyright (C) 2008 ARM Limited
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#ifndef __ASM_UNWIND_H
#define __ASM_UNWIND_H

#ifdef  RT_DEBUG_UNWIND

#ifndef __ASSEMBLY__

/* Unwind reason code according the the ARM EABI documents */
enum unwind_reason_code
{
    URC_OK = 0,			/* operation completed successfully */
    URC_CONTINUE_UNWIND = 8,
    URC_FAILURE = 9			/* unspecified failure of some kind */
};

struct unwind_idx
{
    unsigned long addr_offset;
    unsigned long insn;
};

struct unwind_table
{
    const struct unwind_idx *start;
    const struct unwind_idx *origin;
    const struct unwind_idx *stop;
    unsigned long begin_addr;
    unsigned long end_addr;
};

struct stackframe
{
    /*
     * FP member should hold R7 when CONFIG_THUMB2_KERNEL is enabled
     * and R11 otherwise.
     */
    unsigned long fp;
    unsigned long sp;
    unsigned long lr;
    unsigned long pc;
};

struct pt_regs
{
    unsigned long uregs[18];
};

#define ARM_cpsr    uregs[16]
#define ARM_pc      uregs[15]
#define ARM_lr      uregs[14]
#define ARM_sp      uregs[13]
#define ARM_ip      uregs[12]
#define ARM_fp      uregs[11]
#define ARM_r10     uregs[10]
#define ARM_r9      uregs[9]
#define ARM_r8      uregs[8]
#define ARM_r7      uregs[7]
#define ARM_r6      uregs[6]
#define ARM_r5      uregs[5]
#define ARM_r4      uregs[4]
#define ARM_r3      uregs[3]
#define ARM_r2      uregs[2]
#define ARM_r1      uregs[1]
#define ARM_r0      uregs[0]
#define ARM_ORIG_r0 uregs[17]

#define instruction_pointer(regs)   (regs)->ARM_pc

#ifdef CONFIG_THUMB2_KERNEL
#define frame_pointer(regs) (regs)->ARM_r7
#else
#define frame_pointer(regs) (regs)->ARM_fp
#endif

static inline void arm_get_current_stackframe(struct pt_regs *regs, struct stackframe *frame)
{
    frame->fp = frame_pointer(regs);
    frame->sp = regs->ARM_sp;
    frame->lr = regs->ARM_lr;
    frame->pc = regs->ARM_pc;
}

extern int unwind_frame(struct stackframe *frame);
extern void unwind_backtrace(struct pt_regs *regs);

#endif	/* !__ASSEMBLY__ */

#define pr_debug(...)
//#define pr_debug(...) rt_kprintf(__VA_ARGS__)
#define pr_warn(...) rt_kprintf(__VA_ARGS__)
#define likely(...) __VA_ARGS__
#define unlikely(...) __VA_ARGS__

#endif  /* RT_DEBUG_UNWIND */

#endif	/* __ASM_UNWIND_H */

