/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018/10/28     Bernard      The unify RISC-V porting code.
 * 2021-02-11     lizhirui     add gp support
 * 2021-11-19     JasonHu      add fpu support
 */

#include <csi_core.h>
#include <rthw.h>
#include <rtthread.h>
#include <stddef.h>
#include <asm/riscv_csr.h>
#include "cpuport.h"
#include "stack.h"

/**
 * @brief from thread used interrupt context switch
 *
 */
volatile rt_ubase_t  rt_interrupt_from_thread = 0;
/**
 * @brief to thread used interrupt context switch
 *
 */
volatile rt_ubase_t  rt_interrupt_to_thread   = 0;
/**
 * @brief flag to indicate context switch in interrupt or not
 *
 */
volatile rt_ubase_t rt_thread_switch_interrupt_flag = 0;


/**
 * This function will initialize thread stack
 *
 * @param tentry the entry of thread
 * @param parameter the parameter of entry
 * @param stack_addr the beginning stack address
 * @param texit the function will be called when thread exit
 *
 * @return stack address
 */
rt_uint8_t *rt_hw_stack_init(void       *tentry,
                             void       *parameter,
                             rt_uint8_t *stack_addr,
                             void       *texit)
{
    struct rt_hw_stack_frame *frame;
    rt_uint8_t         *stk;
    int                i;
    extern int __global_pointer$;

    stk  = stack_addr + sizeof(rt_ubase_t);
    stk  = (rt_uint8_t *)RT_ALIGN_DOWN((rt_ubase_t)stk, REGBYTES);
    stk -= sizeof(struct rt_hw_stack_frame);

    frame = (struct rt_hw_stack_frame *)stk;

    for (i = 0; i < sizeof(struct rt_hw_stack_frame) / sizeof(rt_ubase_t); i++) {
        ((rt_ubase_t *)frame)[i] = i;
    }

    frame->ra      = (rt_ubase_t)texit;
    frame->gp      = (rt_ubase_t)&__global_pointer$;
    frame->a0      = (rt_ubase_t)parameter;
    frame->epc     = (rt_ubase_t)tentry;

#if defined(CONFIG_RISCV_SMODE) && CONFIG_RISCV_SMODE
    /* SPP=0b01 SPIE=0b10 */
    frame->mstatus = SR_SPP_S | SR_SPIE;    /* sstatus */
#else
    /* MPP=0b11 MPIE=0b1 */
    frame->mstatus = SR_MPP_M | SR_MPIE;    /* mstatus */
#endif
    frame->mstatus |= SR_SUM;

#if defined(__riscv_dsp) && defined(ARCH_RISCV_DSP)
    /* init vxsat */
    stk -= sizeof(rt_ubase_t);
    *(rt_ubase_t *)stk = 0;
#endif

#if defined(__riscv_flen) && defined(ARCH_RISCV_FPU)
    int f_rgs_len;
    f_rgs_len = sizeof(rt_hw_stack_f_frame_t);
    stk -= f_rgs_len;
    rt_hw_stack_f_frame_t *fframe = (rt_hw_stack_f_frame_t *)stk;
    for (i = 0; i < f_rgs_len / sizeof(rt_ubase_t); i++) {
        ((rt_ubase_t *)fframe)[i] = i;
    }

    frame->mstatus |= SR_FS_INITIAL;    /* enable FPU */
#endif

#if defined(__riscv_vector) && defined(ARCH_RISCV_VECTOR)
    int vlenb = csi_vlenb_get_value();

    stk -= sizeof(rt_hw_stack_v_frame_t);
    rt_hw_stack_v_frame_t *vframe = (rt_hw_stack_v_frame_t *)stk;
    vframe->vl      = (rt_ubase_t)0;
    vframe->vstart  = (rt_ubase_t)0;
    vframe->vtype   = (rt_ubase_t)0;
    vframe->vxsat   = (rt_ubase_t)0;
    vframe->vxrm    = (rt_ubase_t)0;

    stk -= CTX_VECTOR_REG_NR * vlenb;
    vframe = (rt_hw_stack_v_frame_t *)stk;
    for (i = 0; i < CTX_VECTOR_REG_NR * vlenb / sizeof(rt_ubase_t); i++) {
        ((rt_ubase_t *)vframe)[i] = i;
    }

    frame->mstatus |= SR_VS_INITIAL;
#endif

#if (defined(__riscv_matrix) || defined(__riscv_xtheadmatrix)) && defined(ARCH_RISCV_MATRIX)
    int xmlenb = csi_xmlenb_get_value();

    stk -= sizeof(rt_hw_stack_x_frame_t);
    rt_hw_stack_x_frame_t *xframe = (rt_hw_stack_x_frame_t *)stk;
    xframe->xmrstart = (rt_ubase_t)0;
    xframe->xmcsr    = (rt_ubase_t)0;
    xframe->xmsize   = (rt_ubase_t)0;

    stk -= xmlenb * 8;
    xframe = (rt_hw_stack_x_frame_t *)stk;
    for (i = 0; i < xmlenb * 8 / sizeof(rt_ubase_t); i++) {
        ((rt_ubase_t *)xframe)[i] = i;
    }

    frame->mstatus  |= SR_MS_INITIAL;
#endif

    frame->x2      = (rt_ubase_t)stk;
    return stk;
}
/*
 * #ifdef RT_USING_SMP
 * void rt_hw_context_switch_interrupt(void *context, rt_ubase_t from, rt_ubase_t to, struct rt_thread *to_thread);
 * #else
 * void rt_hw_context_switch_interrupt(rt_ubase_t from, rt_ubase_t to);
 * #endif
 */
// #ifndef RT_USING_SMP
// void rt_hw_context_switch_interrupt(rt_ubase_t from, rt_ubase_t to, rt_thread_t from_thread, rt_thread_t to_thread)
// {
//     if (rt_thread_switch_interrupt_flag == 0)
//         rt_interrupt_from_thread = from;

//     rt_interrupt_to_thread = to;
//     rt_thread_switch_interrupt_flag = 1;

//     // rt_trigger_software_interrupt();
//     return ;
// }

// #endif /* end of RT_USING_SMP */

int rt_hw_cpu_id(void)
{
    unsigned long long temp;
    asm volatile("csrr %0, mhartid" : "=r" (temp) );
    return temp;
}

void rt_hw_set_process_id(int pid)
{
    //TODO
}

rt_bool_t rt_hw_interrupt_is_disabled(void)
{
    extern unsigned long cpu_is_irq_enable();
    return !cpu_is_irq_enable();
}
