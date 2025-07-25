/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Support for RISC-V Platform-Level Interrupt Controller(PLIC)
 * Specification Version 1.0.0, which is currently(3/12/2023) the
 * lastest draft.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-05-20     bigmagic     first version
 * 2022-09-16     WangXiaoyao  Porting to rv64
 * 2025-01-26     ZhangJing    Porting to ultrarisc cp100
 */
#include <rthw.h>
#include <rtthread.h>
#include <stdint.h>
#include "plic.h"
#include <io.h>
#include "encoding.h"
#include <interrupt.h>
#include <riscv_io.h>
#include <riscv.h>
#include <string.h>
#include <stdlib.h>

#ifdef RT_USING_SMART
    #include <ioremap.h>
#else
    #define rt_ioremap(addr, ...) (addr)
#endif

/* plic_base should be initialized in the bsp*/
size_t plic_base = 0 ;

/*
 * Each PLIC interrupt source can be assigned a priority by writing
 * to its 32-bit memory-mapped priority register.
 * Maximum priority is 7.
 * A priority value of 0 is reserved to mean "never interrupt" and
 * effectively disables the interrupt.
 * Ties between global interrupts of the same priority are broken by
 * the Interrupt ID; interrupts with the lowest ID have the highest
 * effective priority.
 */
void plic_set_priority(int irq, int priority)
{
    writel(priority, (void *)PLIC_PRIORITY(irq));
}

/*
 * Each global interrupt can be enabled by setting the corresponding
 * bit in the enables registers.
 */
void plic_irq_enable(int irq)
{
    int hart = __raw_hartid();
    void *enable = (void *)PLIC_ENABLE(hart) + (irq / 32) * sizeof(uint32_t);
    rt_uint32_t val = readl(enable);
    val |= (1 << (irq % 32));
    writel(val, enable);
    return;
}

/*
 * Each global interrupt can be disabled by clearing the corresponding
 * bit in the enables registers.
 */
void plic_irq_disable(int irq)
{
    int hart = __raw_hartid();
    void *enable = (void *)PLIC_ENABLE(hart) + (irq / 32) * sizeof(uint32_t);
    rt_uint32_t val = readl(enable);
    val &= ~(1 << (irq % 32));
    writel(val, enable);

    return;
}

/*
 * PLIC will mask all interrupts of a priority less than or equal to threshold.
 * Maximum threshold is 7.
 * For example, a threshold value of zero permits all interrupts with
 * non-zero priority, whereas a value of 7 masks all interrupts.
 * Notice, the threshold is global for PLIC, not for each interrupt source.
 */
void plic_set_threshold(int threshold)
{
    int hart = __raw_hartid();
    writel(threshold, (void *)PLIC_THRESHOLD(hart));
    return;
}

/*
 * DESCRIPTION:
 *    Query the PLIC what interrupt we should serve.
 *    Perform an interrupt claim by reading the claim register, which
 *    returns the ID of the highest-priority pending interrupt or zero if there
 *    is no pending interrupt.
 *    A successful claim also atomically clears the corresponding pending bit
 *    on the interrupt source.
 * RETURN VALUE:
 *    the ID of the highest-priority pending interrupt or zero if there
 *    is no pending interrupt.
 */
rt_uint32_t plic_claim(void)
{
    int hart = __raw_hartid();
    void *claim = (void *)PLIC_CLAIM(hart);
    return readl(claim);
}

/*
 * DESCRIPTION:
 *    Writing the interrupt ID it received from the claim (irq) to the
 *    complete register would signal the PLIC we've served this IRQ.
 *    The PLIC does not check whether the completion ID is the same as the
 *    last claim ID for that target. If the completion ID does not match an
 *    interrupt source that is currently enabled for the target, the completion
 *    is silently ignored.
 * RETURN VALUE: none
 */
void plic_complete(int irq)
{
    int hart = __raw_hartid();
    void *complete = (void *)PLIC_COMPLETE(hart);
    writel(irq, complete);
    return;
}

void plic_init()
{
    if (!plic_base)
    {
        return;
    }
    /* PLIC takes up 64 MB space */
    plic_base = (size_t)rt_ioremap((void *)plic_base, 64 * 1024 * 1024);

    plic_set_threshold(0);

    /*set the same priority for all the irqs*/
    for (int i = 1; i < CONFIG_IRQ_NR; i++)
    {
        plic_set_priority(i, 1);
    }

    /*disable all interrupts*/
    for (int i = 1; i < CONFIG_IRQ_NR; i++)
    {
        plic_irq_disable(i);
    }

    set_csr(sie, read_csr(sie) | MIP_SEIP);

    return;
}

extern struct rt_irq_desc irq_desc[MAX_HANDLERS];
#ifdef BOARD_UR_DP1000
int find_first_bit(rt_uint32_t *addr, int size)
{
    int i;
    for (i = 0; i < size; i++)
    {
        if (*addr & (1 << i))
            return i;
    }
    return -1;
}

static rt_bool_t is_irqs_pending(rt_uint32_t ie[])
{

    int hartid = __raw_hartid();
    int nr_irqs = CONFIG_IRQ_NR;
    int nr_irq_groups = (nr_irqs + 31) / 32;
    rt_bool_t is_pending = RT_FALSE;
    void *pending_base = (void *)PLIC_PENDING(0);
    void *enable_base = (void *)PLIC_ENABLE(hartid);
    int i, j;

    for (i = 0; i < nr_irq_groups; i++)
        ie[i] =  readl(enable_base + i * sizeof(rt_uint32_t));

    for (i = 0; i < nr_irq_groups; i++)
    {
        rt_uint32_t pending_irqs = readl(pending_base + i * sizeof(rt_uint32_t)) & ie[i];
        if (pending_irqs)
        {
            int nbit = find_first_bit(&pending_irqs, 32);
            for (j = 0; j < nr_irq_groups; j++)
                writel((i == j) ? (1 << nbit) : 0, enable_base + j * sizeof(rt_uint32_t));

            is_pending = RT_TRUE;
            break;
        }
    }

    return is_pending;
}

static void restore_irqs_enable(rt_uint32_t ie[])
{
    int hartid = __raw_hartid();
    int nr_irqs = CONFIG_IRQ_NR;
    int nr_irq_groups = (nr_irqs + 31) / 32;
    void *enable_base = (void *)PLIC_ENABLE(hartid);
    int i;

    for (i = 0; i < nr_irq_groups; i++)
        writel(ie[i], enable_base + i * sizeof(rt_uint32_t));

    return;
}
#endif
/*
 * Handling an interrupt is a two-step process: first you claim the interrupt
 * by reading the claim register, then you complete the interrupt by writing
 * that source ID back to the same claim register.  This automatically enables
 * and disables the interrupt, so there's nothing else to do.
 */
void plic_handle_irq(void)
{
    rt_uint32_t plic_irq;
#ifdef BOARD_UR_DP1000
    /* TODO: if not only one interrupt, we need to continue to check the interrupt source */
    unsigned int ie[32] = {0};
    plic_irq = is_irqs_pending(ie) ? plic_claim() : 0;
    restore_irqs_enable(ie);
    if (plic_irq > CONFIG_IRQ_NR)
    {
        /*spurious interrupt, return directly*/
        rt_kprintf("spurious interrupt, irq = %d\n", plic_irq);
        return;
    }
    plic_complete(plic_irq);

    irq_desc[plic_irq].handler(plic_irq, irq_desc[plic_irq].param);

#else
    plic_irq = plic_claim();
    plic_complete(plic_irq);
    if (plic_irq > CONFIG_IRQ_NR)
    {
        /*spurious interrupt, return directly*/
        rt_kprintf("spurious interrupt, irq = %d\n", plic_irq);
        return;
    }

    irq_desc[plic_irq].handler(plic_irq, irq_desc[plic_irq].param);
#endif
    return;
}