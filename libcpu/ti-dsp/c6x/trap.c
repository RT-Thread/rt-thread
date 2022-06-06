/*
 * Copyright (c) 2021, Shenzhen Academy of Aerospace Technology
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-11-16     Dystopia     the first version
 */

#include "trap.h"
#include "c66xx.h"

#include <rthw.h>
#include <rtdef.h>
#include <rtthread.h>

#define RT_SYS_STACK_SIZE    4096

rt_uint8_t rt_system_stack[RT_SYS_STACK_SIZE];
rt_uint8_t *rt_system_stack_top;

void rt_trap_init(void)
{
    rt_system_stack_top = &rt_system_stack[RT_SYS_STACK_SIZE-1];
    rt_system_stack_top  = (rt_uint8_t *)RT_ALIGN_DOWN((rt_uint32_t)rt_system_stack_top, 8);

    ack_exception(EXCEPT_TYPE_NXF);
    ack_exception(EXCEPT_TYPE_EXC);
    ack_exception(EXCEPT_TYPE_IXF);
    ack_exception(EXCEPT_TYPE_SXF);
    rt_hw_enable_exception();
}

void show_regs(struct rt_hw_exp_stack_register *regs)
{
    rt_kprintf("\n");
    rt_kprintf("PC: %08lx SP: %08lx\n",
           regs->pc, regs->hw_register.sp);
    rt_kprintf("Status: %08lx ORIG_A4: %08lx\n",
           regs->csr, regs->orig_a4);
    rt_kprintf("A0: %08lx  B0: %08lx\n",
           regs->hw_register.a0, regs->hw_register.b0);
    rt_kprintf("A1: %08lx  B1: %08lx\n",
           regs->hw_register.a1, regs->hw_register.b1);
    rt_kprintf("A2: %08lx  B2: %08lx\n",
           regs->hw_register.a2, regs->hw_register.b2);
    rt_kprintf("A3: %08lx  B3: %08lx\n",
           regs->hw_register.a3, regs->hw_register.b3);
    rt_kprintf("A4: %08lx  B4: %08lx\n",
           regs->hw_register.a4, regs->hw_register.b4);
    rt_kprintf("A5: %08lx  B5: %08lx\n",
           regs->hw_register.a5, regs->hw_register.b5);
    rt_kprintf("A6: %08lx  B6: %08lx\n",
           regs->hw_register.a6, regs->hw_register.b6);
    rt_kprintf("A7: %08lx  B7: %08lx\n",
           regs->hw_register.a7, regs->hw_register.b7);
    rt_kprintf("A8: %08lx  B8: %08lx\n",
           regs->hw_register.a8, regs->hw_register.b8);
    rt_kprintf("A9: %08lx  B9: %08lx\n",
           regs->hw_register.a9, regs->hw_register.b9);
    rt_kprintf("A10: %08lx  B10: %08lx\n",
           regs->hw_register.a10, regs->hw_register.b10);
    rt_kprintf("A11: %08lx  B11: %08lx\n",
           regs->hw_register.a11, regs->hw_register.b11);
    rt_kprintf("A12: %08lx  B12: %08lx\n",
           regs->hw_register.a12, regs->hw_register.b12);
    rt_kprintf("A13: %08lx  B13: %08lx\n",
           regs->hw_register.a13, regs->hw_register.b13);
    rt_kprintf("A14: %08lx  B14: %08lx\n",
           regs->hw_register.a14, regs->hw_register.dp);
    rt_kprintf("A15: %08lx  B15: %08lx\n",
           regs->hw_register.a15, regs->hw_register.sp);
    rt_kprintf("A16: %08lx  B16: %08lx\n",
           regs->hw_register.a16, regs->hw_register.b16);
    rt_kprintf("A17: %08lx  B17: %08lx\n",
           regs->hw_register.a17, regs->hw_register.b17);
    rt_kprintf("A18: %08lx  B18: %08lx\n",
           regs->hw_register.a18, regs->hw_register.b18);
    rt_kprintf("A19: %08lx  B19: %08lx\n",
           regs->hw_register.a19, regs->hw_register.b19);
    rt_kprintf("A20: %08lx  B20: %08lx\n",
           regs->hw_register.a20, regs->hw_register.b20);
    rt_kprintf("A21: %08lx  B21: %08lx\n",
           regs->hw_register.a21, regs->hw_register.b21);
    rt_kprintf("A22: %08lx  B22: %08lx\n",
           regs->hw_register.a22, regs->hw_register.b22);
    rt_kprintf("A23: %08lx  B23: %08lx\n",
           regs->hw_register.a23, regs->hw_register.b23);
    rt_kprintf("A24: %08lx  B24: %08lx\n",
           regs->hw_register.a24, regs->hw_register.b24);
    rt_kprintf("A25: %08lx  B25: %08lx\n",
           regs->hw_register.a25, regs->hw_register.b25);
    rt_kprintf("A26: %08lx  B26: %08lx\n",
           regs->hw_register.a26, regs->hw_register.b26);
    rt_kprintf("A27: %08lx  B27: %08lx\n",
           regs->hw_register.a27, regs->hw_register.b27);
    rt_kprintf("A28: %08lx  B28: %08lx\n",
           regs->hw_register.a28, regs->hw_register.b28);
    rt_kprintf("A29: %08lx  B29: %08lx\n",
           regs->hw_register.a29, regs->hw_register.b29);
    rt_kprintf("A30: %08lx  B30: %08lx\n",
           regs->hw_register.a30, regs->hw_register.b30);
    rt_kprintf("A31: %08lx  B31: %08lx\n",
           regs->hw_register.a31, regs->hw_register.b31);
}

void do_trap(struct rt_exception_info *except_info, struct rt_hw_exp_stack_register *regs)
{
    rt_kprintf("Enter exception: %s\n", except_info->kernel_str);

    show_regs(regs);

    for(;;){}
}

static struct rt_exception_info iexcept_table[10] = {
    { " - instruction fetch",         ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - fetch packet",              ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - execute packet",            ABORT_TYPE_UNDDEF, ABORT_OPCODE_ILL },
    { " - undefined instruction",     ABORT_TYPE_UNDDEF, ABORT_OPCODE_ILL },
    { " - resource conflict",         ABORT_TYPE_UNDDEF, ABORT_OPCODE_ILL },
    { " - resource access",           ABORT_TYPE_UNDDEF, ABORT_PRVREG_ILL },
    { " - privilege",                 ABORT_TYPE_UNDDEF, ABORT_PRVOPC_ILL },
    { " - loops buffer",              ABORT_TYPE_UNDDEF, ABORT_PRVOPC_ILL },
    { " - software exception",        ABORT_TYPE_UNDDEF, ABORT_ILLTRP_ILL },
    { " - unknown exception",         ABORT_TYPE_UNDDEF, ABORT_PRVOPC_ILL }
};

/*
 * Process an internal exception (non maskable)
 */
static int process_iexcept(struct rt_hw_exp_stack_register *regs)
{
    unsigned int iexcept_report = get_iexcept();
    unsigned int iexcept_num = 0;

    ack_exception(EXCEPT_TYPE_IXF);

    while(iexcept_report)
    {
        iexcept_num = ffs(iexcept_report);
        iexcept_report &= ~(1 << iexcept_num);
        set_iexcept(iexcept_report);

        if (*(unsigned int *)regs->pc == BKPT_OPCODE)
        {
            /* This is a breakpoint */
            struct rt_exception_info bkpt_exception = \
                                     { " - undefined instruction",\
                                     ABORT_TYPE_UNDDEF, ABORT_BRKPT_ILL };
            do_trap(&bkpt_exception, regs);
            iexcept_report &= ~(0xFF);
            set_iexcept(iexcept_report);
            continue;
        }
        do_trap(&iexcept_table[iexcept_num], regs);
    }
    return 0;
}

static struct rt_exception_info eexcept_table[128] = {
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },

    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },

    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },

    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },
    { " - external exception", ABORT_TYPE_BUS, ABORT_BUS_ADDRERR },

    { " - CPU memory protection fault",        ABORT_TYPE_MAP, ABORT_BUS_ACCERR },
    { " - CPU memory protection fault in L1P", ABORT_TYPE_MAP, ABORT_BUS_ACCERR },
    { " - DMA memory protection fault in L1P", ABORT_TYPE_MAP, ABORT_BUS_ACCERR },
    { " - CPU memory protection fault in L1D", ABORT_TYPE_MAP, ABORT_BUS_ACCERR },
    { " - DMA memory protection fault in L1D", ABORT_TYPE_MAP, ABORT_BUS_ACCERR },
    { " - CPU memory protection fault in L2",  ABORT_TYPE_MAP, ABORT_BUS_ACCERR },
    { " - DMA memory protection fault in L2",  ABORT_TYPE_MAP, ABORT_BUS_ACCERR },
    { " - EMC CPU memory protection fault",    ABORT_TYPE_MAP, ABORT_BUS_ACCERR },
    { " - EMC bus error",                      ABORT_TYPE_MAP, ABORT_BUS_ADDRERR }
};

/*
 * Process an external exception (maskable)
 */
static void process_eexcept(struct rt_hw_exp_stack_register *regs)
{
    int except_num = 0;
    int bank = 0;
    int i = 0;

    for (i = 0; i <= 3; i++)
    {
        while (INTC_MEXPMASK[i])
       {
            __dint();
            except_num = ffs(INTC_MEXPMASK[i]);
            INTC_MEXPMASK[i] &= ~(1 << except_num); /* ack the external exception */
            __rint();
            do_trap(&eexcept_table[except_num + (bank << 5)], regs);
        }
        bank++;
    }

    ack_exception(EXCEPT_TYPE_EXC);
}

extern void hw_nmi_handler(struct rt_hw_exp_stack_register *regs);
/*
 * Main exception processing
 */
int rt_hw_process_exception(struct rt_hw_exp_stack_register *regs)
{
    int type = 0;
    int type_num = 0;
    int ie_num = 9; /* default is unknown exception */

    while ((type = get_except_type()) != 0) {
        type_num = fls(type) - 1;

        switch(type_num) {
        case EXCEPT_TYPE_NXF:                   /* NMI exception   */
            ack_exception(EXCEPT_TYPE_NXF);     /* clear exception */
            if (hw_nmi_handler != RT_NULL)
            {
                hw_nmi_handler(regs);
            }
            break;

        case EXCEPT_TYPE_IXF:                   /* internal exception */
            if (process_iexcept(regs))
            {
                return 1;
            }
            break;

        case EXCEPT_TYPE_EXC:                   /* external exception  */
            process_eexcept(regs);
            break;

        case EXCEPT_TYPE_SXF:                   /* software exception */
            ie_num = 8;
            ack_exception(type_num);
            break;
        default:                                /* clear exception */
            ack_exception(type_num);
            do_trap(&iexcept_table[ie_num], regs);
            break;
        }
    }
    return 0;
}

