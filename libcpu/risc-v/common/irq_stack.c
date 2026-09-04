/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rthw.h>
#include <rtthread.h>

#include <cpu.h>
#include <csr.h>
#include <stack.h>

#define RISCV_IRQ_STACK_ALIGN  16
#define RISCV_IRQ_STACK_STRIDE RT_ALIGN(ARCH_RISCV_IRQ_STACK_SIZE, RISCV_IRQ_STACK_ALIGN)

static rt_uint8_t irq_stacks[RT_CPUS_NR][RISCV_IRQ_STACK_STRIDE]
        rt_align(RISCV_IRQ_STACK_ALIGN);

void riscv_irq_stack_init(void)
{
    csr_write(CSR_SCRATCH, riscv_irq_stack_top());
}

void *riscv_irq_stack_top(void)
{
    int cpu_id = rt_hw_cpu_id();

    RT_ASSERT(cpu_id >= 0 && cpu_id < RT_CPUS_NR);
    if (cpu_id < 0 || cpu_id >= RT_CPUS_NR)
    {
        cpu_id = 0;
    }

    return &irq_stacks[cpu_id][RISCV_IRQ_STACK_STRIDE];
}
