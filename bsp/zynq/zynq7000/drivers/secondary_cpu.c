#include <rthw.h>
#include <rtthread.h>
#include <stdint.h>

#include "board.h"
#include "gic.h"
#include "drv_timer.h"
#include "xil_io.h"

#ifdef RT_USING_SMP
#include <interrupt.h>

#ifdef RT_USING_SMART
#include <mmu.h>
#endif

#define CPU1_COPY_ADDR 0xFFFFFFF0

#define sev() __asm__ __volatile__("sev")

void rt_hw_secondary_cpu_up(void)
{
    volatile void **plat_boot_reg = (volatile void **)CPU1_COPY_ADDR;
    char *entry = (char *)rt_secondary_cpu_entry;

#ifdef RT_USING_SMART
    plat_boot_reg = (volatile void **)rt_ioremap_nocache((void *)plat_boot_reg, 0x1000);
    if (!plat_boot_reg)
    {
        /* failed */
        return;
    }
    entry += PV_OFFSET;
#endif

    *plat_boot_reg = (void *)entry;
    dmb();
    sev();
}

#include "xil_cache.h"

/* Interface */
void rt_hw_secondary_cpu_bsp_start(void)
{
    rt_uint32_t gic_cpu_base;

    rt_hw_vector_init();

    rt_hw_spin_lock(&_cpus_lock);

    gic_cpu_base = platform_get_gic_cpu_base();

    arm_gic_cpu_init(0, gic_cpu_base);
    arm_gic_set_cpu(0, TIMER_IRPT_INTR, 0x3);

    rt_hw_timer_init();

    rt_system_scheduler_start();
}

void rt_hw_secondary_cpu_idle_exec(void)
{
    asm volatile ("wfi");
}

#endif
