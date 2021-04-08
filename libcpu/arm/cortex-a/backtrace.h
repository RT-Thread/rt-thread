#ifndef __BACKTRACE_H
#define __BACKTRACE_H

#ifndef __ASSEMBLY__
#include <cpuport.h>

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

int unwind_frame(struct stackframe *frame, const struct unwind_idx **origin_idx, const struct unwind_idx exidx_start[], const struct unwind_idx exidx_end[]);
void unwind_backtrace(struct pt_regs *regs, const struct unwind_idx exidx_start[], const struct unwind_idx exidx_end[]);

void rt_unwind(struct rt_hw_exp_stack *regs, unsigned int pc_adj);
void rt_backtrace(void);

#endif	/* !__ASSEMBLY__ */

#endif	/* __BACKTRACE_H */

