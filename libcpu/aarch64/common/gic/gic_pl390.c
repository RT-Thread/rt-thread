/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-07-31     GuEe-GUI     the first version
 */
#include <rtthread.h>

#include "gic_pl390.h"

#define BIT(n)              (1ul<<(n))
#define MASK(n)             (BIT(n)-1ul)

#define IRQ_REG(IRQ)        ((IRQ) / 32)
#define IRQ_BIT(IRQ)        BIT((IRQ) % 32)
#define IRQ_MASK            MASK(10)
#define IRQ_SET_ALL         0xffffffff
#define IS_IRQ_VALID(X)     (((X)&IRQ_MASK) < GIC390_SPECIAL_IRQ_START)

#define TARGET_CPU_ALLINT(CPU)  \
(                               \
    (((CPU) & 0xff) << 0 ) |    \
    (((CPU) & 0xff) << 8 ) |    \
    (((CPU) & 0xff) << 16) |    \
    (((CPU) & 0xff) << 24)      \
)
#define CPU(X)              (1<<(X))
#define TARGET_CPU0_ALLINT  TARGET_CPU_ALLINT(CPU(0))

/* memory map for GIC distributor */
struct gic_dist_map
{
    rt_uint32_t enable;                 /* 0x000 */
    rt_uint32_t ic_type;                /* 0x004 */
    rt_uint32_t dist_ident;             /* 0x008 */
    rt_uint32_t res1[29];               /* [0x00C, 0x080) */

    rt_uint32_t security[32];           /* [0x080, 0x100) */

    rt_uint32_t enable_set[32];         /* [0x100, 0x180) */
    rt_uint32_t enable_clr[32];         /* [0x180, 0x200) */
    rt_uint32_t pending_set[32];        /* [0x200, 0x280) */
    rt_uint32_t pending_clr[32];        /* [0x280, 0x300) */
    rt_uint32_t active[32];             /* [0x300, 0x380) */
    rt_uint32_t res2[32];               /* [0x380, 0x400) */

    rt_uint32_t priority[255];          /* [0x400, 0x7FC) */
    rt_uint32_t res3;                   /* 0x7FC */

    rt_uint32_t targets[255];           /* [0x800, 0xBFC) */
    rt_uint32_t res4;                   /* 0xBFC */

    rt_uint32_t config[64];             /* [0xC00, 0xD00) */

    rt_uint32_t spi[32];                /* [0xD00, 0xD80) */
    rt_uint32_t res5[20];               /* [0xD80, 0xDD0) */
    rt_uint32_t res6;                   /* 0xDD0 */
    rt_uint32_t legacy_int;             /* 0xDD4 */
    rt_uint32_t res7[2];                /* [0xDD8, 0xDE0) */
    rt_uint32_t match_d;                /* 0xDE0 */
    rt_uint32_t enable_d;               /* 0xDE4 */
    rt_uint32_t res8[70];               /* [0xDE8, 0xF00) */

    rt_uint32_t sgi_control;            /* 0xF00 */
    rt_uint32_t res9[3];                /* [0xF04, 0xF10) */
    rt_uint32_t sgi_pending_clr[4];     /* [0xF10, 0xF20) */
    rt_uint32_t res10[40];              /* [0xF20, 0xFC0) */

    rt_uint32_t periph_id[12];          /* [0xFC0, 0xFF0) */
    rt_uint32_t component_id[4];        /* [0xFF0, 0xFFF] */
};

/* memory map for GIC CPU interface */
struct gic_cpu_iface_map
{
    rt_uint32_t icontrol;               /* 0x000 */
    rt_uint32_t pri_msk_c;              /* 0x004 */
    rt_uint32_t pb_c;                   /* 0x008 */
    rt_uint32_t int_ack;                /* 0x00C */
    rt_uint32_t eoi;                    /* 0x010 */
    rt_uint32_t run_priority;           /* 0x014 */
    rt_uint32_t hi_pend;                /* 0x018 */
    rt_uint32_t ns_alias_bp_c;          /* 0x01C */
    rt_uint32_t ns_alias_ack;           /* 0x020 GIC400 only */
    rt_uint32_t ns_alias_eoi;           /* 0x024 GIC400 only */
    rt_uint32_t ns_alias_hi_pend;       /* 0x028 GIC400 only */

    rt_uint32_t res1[5];                /* [0x02C, 0x040) */

    rt_uint32_t integ_en_c;             /* 0x040 PL390 only */
    rt_uint32_t interrupt_out;          /* 0x044 PL390 only */
    rt_uint32_t res2[2];                /* [0x048, 0x050) */

    rt_uint32_t match_c;                /* 0x050 PL390 only */
    rt_uint32_t enable_c;               /* 0x054 PL390 only */

    rt_uint32_t res3[30];               /* [0x058, 0x0FC) */
    rt_uint32_t active_priority[4];     /* [0x0D0, 0xDC] GIC400 only */
    rt_uint32_t ns_active_priority[4];  /* [0xE0,0xEC] GIC400 only */
    rt_uint32_t res4[3];

    rt_uint32_t cpu_if_ident;           /* 0x0FC */
    rt_uint32_t res5[948];              /* [0x100. 0xFC0) */

    rt_uint32_t periph_id[8];           /* [0xFC0, 9xFF0) PL390 only */
    rt_uint32_t component_id[4];        /* [0xFF0, 0xFFF] PL390 only */
};

volatile struct gic_dist_map *gic_dist =
    (volatile struct gic_dist_map*)(GIC_PL390_DISTRIBUTOR_PPTR);

volatile struct gic_cpu_iface_map *gic_cpuiface =
    (volatile struct gic_cpu_iface_map*)(GIC_PL390_CONTROLLER_PPTR);

/*
 * The only sane way to get an GIC IRQ number that can be properly
 * ACKED later is through the int_ack register. Unfortunately, reading
 * this register changes the interrupt state to pending so future
 * reads will not return the same value For this reason, we have a
 * global variable to store the IRQ number.
 */
static rt_uint32_t active_irq = GIC390_IRQ_NONE;

rt_inline int is_irq_edge_triggered(int irq)
{
    int word = irq / 16;
    int bit = ((irq & 0xf) * 2);

    return !!(gic_dist->config[word] & BIT(bit + 1));
}

rt_inline void dist_pending_clr(int irq)
{
    int word = irq / 32;
    int bit = irq & 0x1f;
    gic_dist->pending_clr[word] = BIT(bit);
}

rt_inline void dist_init(void)
{
    int i;
    int nirqs = 32 * ((gic_dist->ic_type & 0x1f) + 1);
    gic_dist->enable = 0;

    for (i = 0; i < nirqs; i += 32)
    {
        /* disable */
        gic_dist->enable_clr[i / 32] = IRQ_SET_ALL;
        /* clear pending */
        gic_dist->pending_clr[i / 32] = IRQ_SET_ALL;
    }

    /* reset interrupts priority */
    for (i = 32; i < nirqs; i += 4)
    {
        gic_dist->priority[i / 4] = 0x0;
    }

    /*
     * reset int target to cpu 0
     * (Should really query which processor we're running on and use that)
     */
    for (i = 0; i < nirqs; i += 4)
    {
        gic_dist->targets[i / 4] = TARGET_CPU0_ALLINT;
    }

    /* level-triggered, 1-N */
    for (i = 64; i < nirqs; i += 32)
    {
        gic_dist->config[i / 32] = 0;
    }
    /* enable the int controller */
    gic_dist->enable = 1;
}

rt_inline void cpu_iface_init(void)
{
    rt_uint32_t i;

    /* For non-Exynos4, the registers are banked per CPU, need to clear them */
    gic_dist->enable_clr[0] = IRQ_SET_ALL;
    gic_dist->pending_clr[0] = IRQ_SET_ALL;
    gic_dist->priority[0] = 0x00;
    /* put everything in group 0 */

    /* clear any software generated interrupts */
    for (i = 0; i < 16; i += 4)
    {
        gic_dist->sgi_pending_clr[i / 4] = IRQ_SET_ALL;
    }

    gic_cpuiface->icontrol = 0;
    gic_cpuiface->pri_msk_c = 0x000000f0;
    gic_cpuiface->pb_c = 0x00000003;

    while (((i = gic_cpuiface->int_ack) & IRQ_MASK) != GIC390_IRQ_NONE)
    {
        gic_cpuiface->eoi = i;
    }
    gic_cpuiface->icontrol = 0x1;
}


void arm_gic_irq_init(void)
{
    dist_init();
    cpu_iface_init();
}

int arm_gic_get_active_irq(void)
{
    int irq;
    if (!IS_IRQ_VALID(active_irq))
    {
        active_irq = gic_cpuiface->int_ack;
    }

    if (IS_IRQ_VALID(active_irq))
    {
        irq = active_irq & IRQ_MASK;
    }
    else
    {
        irq = GIC390_IRQ_NONE;
    }

    return irq;
}

void arm_gic_mask(int irq)
{
    int word = irq / 32;
    int bit = irq & 0x1f;

    gic_dist->enable_clr[word] = BIT(bit);
}

void arm_gic_umask(int irq)
{
    int word = irq / 32;
    int bit = irq & 0x1f;
    gic_dist->enable_set[word] = BIT(bit);
}

void arm_gic_ack(int irq)
{
    if (!(IS_IRQ_VALID(active_irq) && (active_irq & IRQ_MASK) == irq))
    {
        return;
    }
    if (is_irq_edge_triggered(irq))
    {
        dist_pending_clr(irq);
    }

    gic_cpuiface->eoi = active_irq;
    active_irq = GIC390_IRQ_NONE;
}

int rt_hw_interrupt_get_irq(void)
{
    return arm_gic_get_active_irq();
}

void rt_hw_interrupt_ack(int fiq_irq)
{
    return arm_gic_ack(fiq_irq);
}

