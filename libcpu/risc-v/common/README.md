# Port to NOT DM

## Cache

Fill the cache CBOM block size in your BSP if supported ISA 'ZICBOM':

```c
#include <cache.h>

void rt_hw_cache_init(void)
{
    riscv_cache_set_cbom_block_size(<...>);
}
```

## CPU

Fill the hartid map in your BSP if the hardid is not equal to the CPU id:

```c
#include <cpu.h>

rt_ubase_t cpu_id_to_hartid_map[RT_CPUS_NR] =
{
    [...]
};
```

## SMP

Select your CPU ops in your BSP:

```c
#include <cpu.h>

extern struct cpu_ops_t cpu_sbi_ops;
extern struct cpu_ops_t cpu_spinwait_ops;
[...]

void rt_hw_secondary_cpu_up(void)
{
    int cpu_id;
    rt_ubase_t entry;
    struct cpu_ops_t *cpu_ops;

    if (!(entry = (rt_ubase_t)rt_kmem_v2p(_secondary_cpu_entry)))
    {
        LOG_E("Failed to translate '_secondary_cpu_entry' to physical address");
        RT_ASSERT(0);
    }

    cpu_ops = <...>;
    cpu_id = rt_hw_cpu_id();

    /* Maybe we are no in the first cpu */
    for (int i = 0; i < RT_CPUS_NR; ++i)
    {
        int err;

        if (i == cpu_id)
        {
            continue;
        }

        if (cpu_ops->cpu_init)
        {
            cpu_ops->cpu_init(i, RT_NULL);
        }

        if ((err = cpu_ops->cpu_boot(i, entry)))
        {
            LOG_W("Call cpu %d on %s", i, "failed");
        }
    }
}
```

## Interrupt

Implement the PLIC information if enable M-mode in your BSP by `board.h`:

```c
rt_inline void rt_ubase_t platform_get_clint_base(void)
{
    return clint_physical_address_base;
}

rt_inline void rt_size_t platform_get_clint_size(void)
{
    return clint_physical_address_size;
}
```

### PLIC + RISC-V INTC

Implement the PLIC information and `MAX_HANDLERS`, INTC type in your BSP by `board.h`:

```c
#define MAX_HANDLERS    <...>

/*
 * Type:
 *  - INTC_TYPE_RISCV (Default, could not define)
 *  - INTC_TYPE_ANDESTECH
 */
#define INTC_TYPE       <...>

/*
 * Bits (Not quicks could not define):
 *  - PLIC_QUIRK_EDGE_INTERRUPT
 */
#define PLIC_QUICKS     <...>

rt_inline void rt_ubase_t platform_get_plic_base(void)
{
    return plic_physical_address_base;
}

rt_inline void rt_size_t platform_get_plic_size(void)
{
    return plic_physical_address_size;
}
```

Use the `IRQ_XYZ(vector)` or `IPI_INTC(vector)` to instread of `vector`:

```c
#include <interrupt.h>

#define DEVICE_HWIRQ    1

static void device_isr(int hwirq, void *param)
{
    RT_ASSERT(DEVICE_HWIRQ == hwirq);
}

void rt_hw_device_init(void)
{
    rt_hw_interrupt_install(IRQ_PLIC(DEVICE_HWIRQ), device_isr, RT_NULL, "device isr");
    rt_hw_interrupt_umask(IRQ_PLIC(DEVICE_HWIRQ));
}

#include <csr.h>

static void pmu_isr(int hwirq, void *param)
{
    RT_ASSERT(IRQ_PMU_OVF == hwirq);
}

void rt_hw_pmu_init(void)
{
    rt_hw_interrupt_install(IRQ_INTC(IRQ_PMU_OVF), pmu_isr, RT_NULL, "pmu isr");
    rt_hw_interrupt_umask(IRQ_INTC(IRQ_PMU_OVF));
}

#ifdef RT_USING_SMP
void rt_hw_ipi_init(void)
{
    rt_hw_ipi_handler_install(IPI_INTC(RT_SCHEDULE_IPI), rt_scheduler_ipi_handler);
    rt_hw_interrupt_umask(IPI_INTC(RT_SCHEDULE_IPI));
}
#endif /* RT_USING_SMP */
```

### CLIC
Implement the CLIC information and `MAX_HANDLERS`, INTC type in your BSP by `board.h`:

```c
#define MAX_HANDLERS    <...>

#define INTC_TYPE       INTC_TYPE_CLIC

/*
 * Bits (Not quicks could not define):
 *  - CLIC_QUIRK_MODE_FIXED
 *  - CLIC_QUIRK_MINTTHRESH
 */
#define CLIC_QUICKS     <...>

rt_inline void rt_ubase_t platform_get_clic_base(void)
{
    return clic_physical_address_base;
}

rt_inline void rt_size_t platform_get_clic_size(void)
{
    return clic_physical_address_size;
}
```

Use the `IRQ_CLIC(vector)` or `IPI_CLIC(vector)` to instread of `vector`:

```c
#include <interrupt.h>

#define DEVICE_HWIRQ    1

static void device_isr(int hwirq, void *param)
{
    RT_ASSERT(DEVICE_HWIRQ == hwirq);
}

void rt_hw_device_init(void)
{
    rt_hw_interrupt_install(IRQ_CLIC(DEVICE_HWIRQ), device_isr, RT_NULL, "device isr");
    rt_hw_interrupt_umask(IRQ_CLIC(DEVICE_HWIRQ));
}

#ifdef RT_USING_SMP
void rt_hw_ipi_init(void)
{
    rt_hw_ipi_handler_install(IPI_CLIC(RT_SCHEDULE_IPI), rt_scheduler_ipi_handler);
    rt_hw_interrupt_umask(IPI_CLIC(RT_SCHEDULE_IPI));
}
#endif /* RT_USING_SMP */
```

## ISA

Select the ISA in your BSP:

```c
#include <isa_ext.h>

void rt_hw_isa_init(void)
{
    riscv_isa_ext_set(I);
    riscv_isa_ext_set(M);
    riscv_isa_ext_set(A);
    riscv_isa_ext_set(F);
    riscv_isa_ext_set(D);
    riscv_isa_ext_set(Q);
    riscv_isa_ext_set(C);
    riscv_isa_ext_set(V);
    riscv_isa_ext_set(ZICBOM);
    [...]
}
```

## Timer

Initialize the RISC-V timer in your BSP:

```c
#include <cpu.h>
#include <csr.h>
#include <riscv_timer.h>

void rt_hw_timer_init(int cpu_id)
{
    if (riscv_cpu_id_to_hartid(cpu_id) == boot_cpu_hartid)
    {
        riscv_timer_set_frequency(<...>);
    }

    riscv_timer_init();
}
```

## MMU

Define the virtual address size in your BSP:

```c
rt_uint8_t rt_hw_arch_vaddr_width = <...>; /* 0/32/39/48/57/64 */
```

if the `rt_hw_arch_vaddr_width` is zero (RTOS only), the MMU will be disabled, we recommended to disable the SoC's Kconfig option `ARCH_MM_MMU` before build.

## Board

There is a recommended initialization:

```c
[...]

void rt_hw_board_init(void)
{
    int cpu_id = rt_hw_cpu_id();

    /* Memory, Pages, MMU... */
    [...]

    rt_hw_isa_init();

    rt_hw_cache_init();

    rt_hw_interrupt_init();

    rt_hw_timer_init(cpu_id);

    /* Components, Console, Idle hook, SMP install... */
    [...]
}

#ifdef RT_USING_SMP
void rt_hw_secondary_cpu_bsp_start(void)
{
    int cpu_id = rt_hw_cpu_id();

    rt_hw_spin_lock(&_cpus_lock);

    /* MMU... */
    [...]

    rt_hw_interrupt_init();

    rt_hw_timer_init(cpu_id);

    /* SMP install, Scheduler... */
    [...]
}
#endif /* RT_USING_SMP */
```
