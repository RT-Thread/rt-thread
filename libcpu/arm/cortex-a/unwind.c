/*
 * arch/arm/kernel/unwind.c
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
 *
 *
 * Stack unwinding support for ARM
 *
 * An ARM EABI version of gcc is required to generate the unwind
 * tables. For information about the structure of the unwind tables,
 * see "Exception Handling ABI for the ARM Architecture" at:
 *
 * http://infocenter.arm.com/help/topic/com.arm.doc.subset.swdev.abi/index.html
 */

#ifndef __CHECKER__
#if !defined (__ARM_EABI__)
#warning Your compiler does not have EABI support.
#warning    ARM unwind is known to compile only with EABI compilers.
#warning    Change compiler or disable ARM_UNWIND option.
#elif (__GNUC__ == 4 && __GNUC_MINOR__ <= 2) && !defined(__clang__)
#warning Your compiler is too buggy; it is known to not compile ARM unwind support.
#warning    Change compiler or disable ARM_UNWIND option.
#endif
#endif /* __CHECKER__ */

#include <rtthread.h>
#include <rthw.h>

#ifdef RT_DEBUG_UNWIND
#include <unwind.h>
#define EXPORT_SYMBOL(n)

/* Dummy functions to avoid linker complaints */
void __aeabi_unwind_cpp_pr0(void)
{
};
EXPORT_SYMBOL(__aeabi_unwind_cpp_pr0);

void __aeabi_unwind_cpp_pr1(void)
{
};
EXPORT_SYMBOL(__aeabi_unwind_cpp_pr1);

void __aeabi_unwind_cpp_pr2(void)
{
};
EXPORT_SYMBOL(__aeabi_unwind_cpp_pr2);

struct unwind_ctrl_block {
    unsigned long vrs[16];		/* virtual register set */
    const unsigned long *insn;	/* pointer to the current instructions word */
    unsigned long sp_high;		/* highest value of sp allowed */
    /*
     * 1 : check for stack overflow for each register pop.
     * 0 : save overhead if there is plenty of stack remaining.
     */
    int check_each_pop;
    int entries;			/* number of entries left to interpret */
    int byte;			/* current byte number in the instructions word */
};

enum regs
{
#ifdef CONFIG_THUMB2_KERNEL
    FP = 7,
#else
    FP = 11,
#endif
    SP = 13,
    LR = 14,
    PC = 15
};

extern const struct unwind_idx __exidx_start[];
static const struct unwind_idx *__origin_idx;
extern const struct unwind_idx __exidx_end[];

static int core_kernel_text(unsigned long addr)
{
    return 1;
}

/* Convert a prel31 symbol to an absolute address */
#define prel31_to_addr(ptr)				\
    ({							\
     /* sign-extend to 32 bits */			\
     long offset = (((long)*(ptr)) << 1) >> 1;	\
     (unsigned long)(ptr) + offset;			\
     })

/*
 * Binary search in the unwind index. The entries are
 * guaranteed to be sorted in ascending order by the linker.
 *
 * start = first entry
 * origin = first entry with positive offset (or stop if there is no such entry)
 * stop - 1 = last entry
 */
static const struct unwind_idx *search_index(unsigned long addr,
        const struct unwind_idx *start,
        const struct unwind_idx *origin,
        const struct unwind_idx *stop)
{
    unsigned long addr_prel31;

    pr_debug("%s(%08lx, %x, %x, %x)\n",
            __func__, addr, start, origin, stop);

    /*
     * only search in the section with the matching sign. This way the
     * prel31 numbers can be compared as unsigned longs.
     */
    if (addr < (unsigned long)start)
        /* negative offsets: [start; origin) */
        stop = origin;
    else
        /* positive offsets: [origin; stop) */
        start = origin;

    /* prel31 for address relavive to start */
    addr_prel31 = (addr - (unsigned long)start) & 0x7fffffff;

    while (start < stop - 1)
    {
        const struct unwind_idx *mid = start + ((stop - start) >> 1);

        /*
         * As addr_prel31 is relative to start an offset is needed to
         * make it relative to mid.
         */
        if (addr_prel31 - ((unsigned long)mid - (unsigned long)start) <
                mid->addr_offset)
            stop = mid;
        else
        {
            /* keep addr_prel31 relative to start */
            addr_prel31 -= ((unsigned long)mid -
                    (unsigned long)start);
            start = mid;
        }
    }

    if (likely(start->addr_offset <= addr_prel31))
        return start;
    else
    {
        pr_warn("unwind: Unknown symbol address %08lx\n", addr);
        return NULL;
    }
}

static const struct unwind_idx *unwind_find_origin(
        const struct unwind_idx *start, const struct unwind_idx *stop)
{
    pr_debug("%s(%x, %x)\n", __func__, start, stop);
    while (start < stop)
    {
        const struct unwind_idx *mid = start + ((stop - start) >> 1);

        if (mid->addr_offset >= 0x40000000)
            /* negative offset */
            start = mid + 1;
        else
            /* positive offset */
            stop = mid;
    }
    pr_debug("%s -> %x\n", __func__, stop);
    return stop;
}

static const struct unwind_idx *unwind_find_idx(unsigned long addr)
{
    const struct unwind_idx *idx = NULL;

    pr_debug("%s(%08lx)\n", __func__, addr);

    if (core_kernel_text(addr))
    {
        if (unlikely(!__origin_idx))
            __origin_idx =
                unwind_find_origin(__exidx_start,
                        __exidx_end);

        /* main unwind table */
        idx = search_index(addr, __exidx_start,
                __origin_idx,
                __exidx_end);
    }

    pr_debug("%s: idx = %x\n", __func__, idx);
    return idx;
}

static unsigned long unwind_get_byte(struct unwind_ctrl_block *ctrl)
{
    unsigned long ret;

    if (ctrl->entries <= 0)
    {
        pr_warn("unwind: Corrupt unwind table\n");
        return 0;
    }

    ret = (*ctrl->insn >> (ctrl->byte * 8)) & 0xff;

    if (ctrl->byte == 0)
    {
        ctrl->insn++;
        ctrl->entries--;
        ctrl->byte = 3;
    }
    else
        ctrl->byte--;

    return ret;
}

/* Before poping a register check whether it is feasible or not */
static int unwind_pop_register(struct unwind_ctrl_block *ctrl,
        unsigned long **vsp, unsigned int reg)
{
    if (unlikely(ctrl->check_each_pop))
        if (*vsp >= (unsigned long *)ctrl->sp_high)
            return -URC_FAILURE;

    ctrl->vrs[reg] = *(*vsp)++;
    return URC_OK;
}

/* Helper functions to execute the instructions */
static int unwind_exec_pop_subset_r4_to_r13(struct unwind_ctrl_block *ctrl,
        unsigned long mask)
{
    unsigned long *vsp = (unsigned long *)ctrl->vrs[SP];
    int load_sp, reg = 4;

    load_sp = mask & (1 << (13 - 4));
    while (mask)
    {
        if (mask & 1)
            if (unwind_pop_register(ctrl, &vsp, reg))
                return -URC_FAILURE;
        mask >>= 1;
        reg++;
    }
    if (!load_sp)
        ctrl->vrs[SP] = (unsigned long)vsp;

    return URC_OK;
}

static int unwind_exec_pop_r4_to_rN(struct unwind_ctrl_block *ctrl,
        unsigned long insn)
{
    unsigned long *vsp = (unsigned long *)ctrl->vrs[SP];
    int reg;

    /* pop R4-R[4+bbb] */
    for (reg = 4; reg <= 4 + (insn & 7); reg++)
        if (unwind_pop_register(ctrl, &vsp, reg))
            return -URC_FAILURE;

    if (insn & 0x8)
        if (unwind_pop_register(ctrl, &vsp, 14))
            return -URC_FAILURE;

    ctrl->vrs[SP] = (unsigned long)vsp;

    return URC_OK;
}

static int unwind_exec_pop_subset_r0_to_r3(struct unwind_ctrl_block *ctrl,
        unsigned long mask)
{
    unsigned long *vsp = (unsigned long *)ctrl->vrs[SP];
    int reg = 0;

    /* pop R0-R3 according to mask */
    while (mask)
    {
        if (mask & 1)
            if (unwind_pop_register(ctrl, &vsp, reg))
                return -URC_FAILURE;
        mask >>= 1;
        reg++;
    }
    ctrl->vrs[SP] = (unsigned long)vsp;

    return URC_OK;
}

/*
 * Execute the current unwind instruction.
 */
static int unwind_exec_insn(struct unwind_ctrl_block *ctrl)
{
    unsigned long insn = unwind_get_byte(ctrl);
    int ret = URC_OK;

    pr_debug("%s: insn = %08lx\n", __func__, insn);

    if ((insn & 0xc0) == 0x00)
        ctrl->vrs[SP] += ((insn & 0x3f) << 2) + 4;
    else if ((insn & 0xc0) == 0x40)
        ctrl->vrs[SP] -= ((insn & 0x3f) << 2) + 4;
    else if ((insn & 0xf0) == 0x80)
    {
        unsigned long mask;

        insn = (insn << 8) | unwind_get_byte(ctrl);
        mask = insn & 0x0fff;
        if (mask == 0)
        {
            pr_warn("unwind: 'Refuse to unwind' instruction %04lx\n",
                    insn);
            return -URC_FAILURE;
        }

        ret = unwind_exec_pop_subset_r4_to_r13(ctrl, mask);
        if (ret)
            goto error;
    }
    else if ((insn & 0xf0) == 0x90 &&
            (insn & 0x0d) != 0x0d)
        ctrl->vrs[SP] = ctrl->vrs[insn & 0x0f];
    else if ((insn & 0xf0) == 0xa0)
    {
        ret = unwind_exec_pop_r4_to_rN(ctrl, insn);
        if (ret)
            goto error;
    }
    else if (insn == 0xb0)
    {
        if (ctrl->vrs[PC] == 0)
            ctrl->vrs[PC] = ctrl->vrs[LR];
        /* no further processing */
        ctrl->entries = 0;
    }
    else if (insn == 0xb1)
    {
        unsigned long mask = unwind_get_byte(ctrl);

        if (mask == 0 || mask & 0xf0)
        {
            pr_warn("unwind: Spare encoding %04lx\n",
                    (insn << 8) | mask);
            return -URC_FAILURE;
        }

        ret = unwind_exec_pop_subset_r0_to_r3(ctrl, mask);
        if (ret)
            goto error;
    }
    else if (insn == 0xb2)
    {
        unsigned long uleb128 = unwind_get_byte(ctrl);

        ctrl->vrs[SP] += 0x204 + (uleb128 << 2);
    }
    else
    {
        pr_warn("unwind: Unhandled instruction %02lx\n", insn);
        return -URC_FAILURE;
    }

    pr_debug("%s: fp = %08lx sp = %08lx lr = %08lx pc = %08lx\n", __func__,
            ctrl->vrs[FP], ctrl->vrs[SP], ctrl->vrs[LR], ctrl->vrs[PC]);

error:
    return ret;
}

/*
 * Unwind a single frame starting with *sp for the symbol at *pc. It
 * updates the *pc and *sp with the new values.
 */
int unwind_frame(struct stackframe *frame)
{
    unsigned long low;
    const struct unwind_idx *idx;
    struct unwind_ctrl_block ctrl;
    struct rt_thread *rt_c_thread = rt_thread_self();

    /* store the highest address on the stack to avoid crossing it*/
    low = frame->sp;
    ctrl.sp_high = (unsigned long)(rt_c_thread->stack_addr + rt_c_thread->stack_size);

    pr_debug("%s(pc = %08lx lr = %08lx sp = %08lx)\n", __func__,
            frame->pc, frame->lr, frame->sp);

    idx = unwind_find_idx(frame->pc);
    if (!idx)
    {
        pr_warn("unwind: Index not found %08lx\n", frame->pc);
        return -URC_FAILURE;
    }

    ctrl.vrs[FP] = frame->fp;
    ctrl.vrs[SP] = frame->sp;
    ctrl.vrs[LR] = frame->lr;
    ctrl.vrs[PC] = 0;

    if (idx->insn == 1)
        /* can't unwind */
        return -URC_FAILURE;
    else if ((idx->insn & 0x80000000) == 0)
        /* prel31 to the unwind table */
        ctrl.insn = (unsigned long *)prel31_to_addr(&idx->insn);
    else if ((idx->insn & 0xff000000) == 0x80000000)
        /* only personality routine 0 supported in the index */
        ctrl.insn = &idx->insn;
    else
    {
        pr_warn("unwind: Unsupported personality routine %08lx in the index at %x\n",
                idx->insn, idx);
        return -URC_FAILURE;
    }

    /* check the personality routine */
    if ((*ctrl.insn & 0xff000000) == 0x80000000)
    {
        ctrl.byte = 2;
        ctrl.entries = 1;
    }
    else if ((*ctrl.insn & 0xff000000) == 0x81000000)
    {
        ctrl.byte = 1;
        ctrl.entries = 1 + ((*ctrl.insn & 0x00ff0000) >> 16);
    }
    else
    {
        pr_warn("unwind: Unsupported personality routine %08lx at %x\n",
                *ctrl.insn, ctrl.insn);
        return -URC_FAILURE;
    }

    ctrl.check_each_pop = 0;

    while (ctrl.entries > 0)
    {
        int urc;
        if ((ctrl.sp_high - ctrl.vrs[SP]) < sizeof(ctrl.vrs))
            ctrl.check_each_pop = 1;
        urc = unwind_exec_insn(&ctrl);
        if (urc < 0)
            return urc;
        if (ctrl.vrs[SP] < low || ctrl.vrs[SP] >= ctrl.sp_high)
            return -URC_FAILURE;
    }

    if (ctrl.vrs[PC] == 0)
        ctrl.vrs[PC] = ctrl.vrs[LR];

    /* check for infinite loop */
    if (frame->pc == ctrl.vrs[PC])
        return -URC_FAILURE;

    frame->fp = ctrl.vrs[FP];
    frame->sp = ctrl.vrs[SP];
    frame->lr = ctrl.vrs[LR];
    frame->pc = ctrl.vrs[PC];

    return URC_OK;
}

void unwind_backtrace(struct pt_regs *regs)
{
    struct stackframe frame;

    pr_debug("%s(regs = %x)\n", __func__, regs);

    arm_get_current_stackframe(regs, &frame);

    rt_kprintf("please use: addr2line -e rtthread.elf -a -f %08x", frame.pc);
    pr_debug("pc = %08x, sp = %08x\n", frame.pc, frame.sp);

    while (1)
    {
        int urc;

        urc = unwind_frame(&frame);
        if (urc < 0)
            break;
        //dump_backtrace_entry(where, frame.pc, frame.sp - 4);
        rt_kprintf(" %08x", frame.pc);
        pr_debug("from: pc = %08x, frame = %08x\n", frame.pc, frame.sp - 4);
    }
    rt_kprintf("\n");
}
#endif /* RT_DEBUG_UNWIND */
