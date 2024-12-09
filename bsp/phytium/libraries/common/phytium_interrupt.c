#include "rtconfig.h"
#if defined(TARGET_ARMV8_AARCH64)
#include <rthw.h>
#include <rtthread.h>
#include "interrupt.h"
#include "gic.h"
#include "gicv3.h"
#include "ioremap.h"
#include "phytium_cpu.h"
#include "ftypes.h"
#include "fparameters.h"

struct arm_gic *phytium_gic_table;

extern struct rt_irq_desc isr_table[MAX_HANDLERS];

int arm_gic_redist_address_set(rt_uint64_t index, rt_uint64_t redist_addr, int cpu_id)
{
    RT_ASSERT(index < ARM_GIC_MAX_NR);

    if (cpu_id == 0)
    {
        rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, &cpu_id, sizeof(cpu_id));
    }

    phytium_gic_table[index].redist_hw_base[cpu_id] = redist_addr;

    return 0;
}

static int arm_gicv3_wait_rwp(rt_uint64_t index, rt_uint64_t irq)
{
    rt_uint64_t rwp_bit;
    rt_uint64_t base;

    RT_ASSERT(index < ARM_GIC_MAX_NR);

    if (irq < 32)
    {
        rt_int32_t cpu_id = rt_hw_cpu_id();

        base = phytium_gic_table[index].redist_hw_base[cpu_id];
        rwp_bit = GICR_CTLR_RWP;
    }
    else
    {
        base = phytium_gic_table[index].dist_hw_base;
        rwp_bit = GICD_CTLR_RWP;
    }

    while (HWREG32(base) & rwp_bit)
    {
    }

    return 0;
}

int phytium_aarch64_arm_gic_redist_init()
{
    rt_uint64_t cpu_id = rt_hw_cpu_id();
    rt_uint64_t redist_base = phytium_gic_table[0].redist_hw_base[cpu_id];

    /* redistributor enable */
    GIC_RDIST_WAKER(redist_base) &= ~(1 << 1);
    while (GIC_RDIST_WAKER(redist_base) & (1 << 2))
    {
    }

    /* Disable all sgi and ppi interrupt */
    GIC_RDISTSGI_ICENABLER0(redist_base) = 0xffffffff;
    arm_gicv3_wait_rwp(0, 0);

    /* Clear all inetrrupt pending */
    GIC_RDISTSGI_ICPENDR0(redist_base) = 0xffffffff;

    /* the corresponding interrupt is Group 1 or Non-secure Group 1. */
    GIC_RDISTSGI_IGROUPR0(redist_base, 0) = 0xffffffff;
    GIC_RDISTSGI_IGRPMODR0(redist_base, 0) = 0xffffffff;

    /* Configure default priorities for SGI 0:15 and PPI 16:31. */
    for (int i = 0; i < 32; i += 4)
    {
        GIC_RDISTSGI_IPRIORITYR(redist_base, i) = 0xa0a0a0a0U;
    }

    /* Trigger level for PPI interrupts*/
    GIC_RDISTSGI_ICFGR1(redist_base) = 0;

    return 0;
}

void phytium_interrupt_init(void)
{
    rt_uint64_t gic_cpu_base;
    rt_uint64_t gic_dist_base;
    rt_uint64_t gic_irq_start;

    phytium_gic_table = (struct arm_gic *)arm_gic_get_gic_table_addr();
    /* initialize vector table */
    rt_hw_vector_init();

    /* initialize exceptions table */
    rt_memset(isr_table, 0x00, sizeof(isr_table));

#if defined(RT_USING_SMART)
    gic_dist_base = (rt_uint64_t)rt_ioremap((void *)platform_get_gic_dist_base(), 0x40000);
    gic_cpu_base = (rt_uint64_t)rt_ioremap((void*)platform_get_gic_cpu_base(), 0x1000);
#else
    gic_dist_base = platform_get_gic_dist_base();
    gic_cpu_base = platform_get_gic_cpu_base();
#endif

    gic_irq_start = 0;
    arm_gic_dist_init(0, gic_dist_base, gic_irq_start);
    arm_gic_cpu_init(0, gic_cpu_base);
    arm_gic_redist_address_set(0, platform_get_gic_redist_base(), 0);

    phytium_aarch64_arm_gic_redist_init();
}
#endif
