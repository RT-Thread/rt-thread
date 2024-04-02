#include <rthw.h>
#include <rtthread.h>
#include "interrupt.h"
#include "gic.h"
#include "gicv3.h"
#include "ioremap.h"
#include "phytium_cpu.h"
#include "ftypes.h"
#include "fparameters.h"

#define GIC_RSGI_OFFSET 0x10000
#define GIC_RDIST_WAKER(hw_base)            HWREG32((hw_base) + 0x014U)
#define GIC_RDISTSGI_ICENABLER0(hw_base)    HWREG32((hw_base) + GIC_RSGI_OFFSET + 0x180U)
#define GIC_RDISTSGI_ICPENDR0(hw_base)      HWREG32((hw_base) + GIC_RSGI_OFFSET + 0x280U)
#define GIC_RDISTSGI_IGROUPR0(hw_base, n)   HWREG32((hw_base) + GIC_RSGI_OFFSET + 0x080U + (n) * 4U)
#define GIC_RDISTSGI_IGRPMODR0(hw_base, n)  HWREG32((hw_base) + GIC_RSGI_OFFSET + 0xD00U + (n) * 4)
#define GIC_RDISTSGI_IPRIORITYR(hw_base, n) HWREG32((hw_base) + GIC_RSGI_OFFSET + 0x400U + ((n) / 4U) * 4U)
#define GIC_RDISTSGI_ICFGR1(hw_base)        HWREG32((hw_base) + GIC_RSGI_OFFSET + 0xC04U)

struct arm_gic
{
    rt_uint64_t offset;                     /* the first interrupt index in the vector table */
    rt_uint64_t redist_hw_base[ARM_GIC_CPU_NUM]; /* the pointer of the gic redistributor */
    rt_uint64_t dist_hw_base;               /* the base address of the gic distributor */
    rt_uint64_t cpu_hw_base[ARM_GIC_CPU_NUM];    /* the base address of the gic cpu interface */
};

extern struct arm_gic _gic_table[ARM_GIC_MAX_NR];

extern struct rt_irq_desc isr_table[MAX_HANDLERS];

int arm_gic_redist_address_set(rt_uint64_t index, rt_uint64_t redist_addr, int cpu_id)
{
    RT_ASSERT(index < ARM_GIC_MAX_NR);

    if (cpu_id == 0)
    {
        rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, &cpu_id, sizeof(cpu_id));
    }

    _gic_table[index].redist_hw_base[cpu_id] = redist_addr;

    return 0;
}

int phytium_aarch64_arm_gic_redist_init()
{
    rt_uint64_t cpu_id = rt_hw_cpu_id();

    rt_uint64_t redist_addr = _gic_table[0].redist_hw_base[cpu_id];

    /* redistributor enable */
    GIC_RDIST_WAKER(redist_addr) &= ~(1 << 1);
    while (GIC_RDIST_WAKER(redist_addr) & (1 << 2))
    {
    }

    /* Disable all sgi and ppi interrupt */
    GIC_RDISTSGI_ICENABLER0(redist_addr) = 0xffffffff;
    arm_gicv3_wait_rwp(0, 0);

    /* Clear all inetrrupt pending */
    GIC_RDISTSGI_ICPENDR0(redist_addr) = 0xffffffff;

    /* the corresponding interrupt is Group 1 or Non-secure Group 1. */
    GIC_RDISTSGI_IGROUPR0(redist_addr, 0) = 0xffffffff;
    GIC_RDISTSGI_IGRPMODR0(redist_addr, 0) = 0xffffffff;

    /* Configure default priorities for SGI 0:15 and PPI 16:31. */
    for (int i = 0; i < 32; i += 4)
    {
        GIC_RDISTSGI_IPRIORITYR(redist_addr, i) = 0xa0a0a0a0U;
    }

    /* Trigger level for PPI interrupts*/
    GIC_RDISTSGI_ICFGR1(redist_addr) = 0;

    return 0;
}

void phytium_interrupt_init(void)
{
    rt_uint64_t gic_dist_base;
    rt_uint64_t gic_irq_start;
    rt_uint32_t redist_addr;

    // rt_uint32_t cpu_id, cpu_offset = 0;
    // _gic_table = arm_gic_get_gic_table_addr();
    // GetCpuId(&cpu_id);

// #if defined(RT_USING_SMART)
//     redist_addr = (uint32_t)rt_ioremap(GICV3_RD_BASE_ADDR, 4 * 128 * 1024);
// #else
    redist_addr = GICV3_RD_BASE_ADDR;
// #endif

    arm_gic_redist_address_set(0, redist_addr + 2 * GICV3_RD_OFFSET, 0);

// #if defined(TARGET_E2000Q) || defined(TARGET_PHYTIUMPI)

// #if RT_CPUS_NR == 2
//     arm_gic_redist_address_set(0, redist_addr + 3 * GICV3_RD_OFFSET, 1);
// #elif RT_CPUS_NR == 3
//     arm_gic_redist_address_set(0, redist_addr + 3 * GICV3_RD_OFFSET, 1);
//     arm_gic_redist_address_set(0, redist_addr, 2);
// #elif RT_CPUS_NR == 4
    arm_gic_redist_address_set(0, redist_addr + 3 * GICV3_RD_OFFSET, 1);
    arm_gic_redist_address_set(0, redist_addr, 2);
    arm_gic_redist_address_set(0, redist_addr + GICV3_RD_OFFSET, 3);
// #endif

// #else

// #if RT_CPUS_NR == 2
//     arm_gic_redist_address_set(0, redist_addr + (1 + cpu_offset) * GICV3_RD_OFFSET, 1);
// #elif RT_CPUS_NR == 3
//     arm_gic_redist_address_set(0, redist_addr + (1 + cpu_offset) * GICV3_RD_OFFSET, 1);
//     arm_gic_redist_address_set(0, redist_addr + (2 + cpu_offset) * GICV3_RD_OFFSET, 2);
// #elif RT_CPUS_NR == 4
//     arm_gic_redist_address_set(0, redist_addr + (1 + cpu_offset) * GICV3_RD_OFFSET, 1);
//     arm_gic_redist_address_set(0, redist_addr + (2 + cpu_offset) * GICV3_RD_OFFSET, 2);
//     arm_gic_redist_address_set(0, redist_addr + (3 + cpu_offset) * GICV3_RD_OFFSET, 3);
// #endif

// #endif

    /* initialize vector table */
    rt_hw_vector_init();

    /* initialize exceptions table */
    rt_memset(isr_table, 0x00, sizeof(isr_table));

    /* initialize ARM GIC */
// #if defined(RT_USING_SMART) || defined(RT_USING_OFW)
//     gic_dist_base = (rt_uint64_t)rt_ioremap((void *)platform_get_gic_dist_base(), 0x40000);
// #else
    gic_dist_base = platform_get_gic_dist_base();
// #endif
    gic_irq_start = GIC_IRQ_START;

    arm_gic_dist_init(0, gic_dist_base, gic_irq_start);
    arm_gic_cpu_init(0, 0);
    phytium_aarch64_arm_gic_redist_init();
}
