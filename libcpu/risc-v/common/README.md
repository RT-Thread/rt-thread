# RISC-V common porting guide

The unified common port separates architectural code from platform policy. A
BSP selects the complete common startup, context and trap ABI with
`RT_USING_RISCV_NEW_COMMON`, then configures platform properties and interrupt
ownership independently.

## Configuration model

The following options describe independent properties. Do not infer one from a
CPU name or from another option.

| Option | Responsibility |
| --- | --- |
| `ARCH_RISCV32` / `ARCH_RISCV64` | RISC-V sub-architecture and XLEN |
| `ARCH_RISCV_M_MODE` | M-mode CSR, trap return, timer and interrupt numbers |
| `ARCH_MM_MMU` | Page tables and virtual memory support |
| `RT_USING_CACHE` | Cache maintenance API and Zicbom block operations; optional on cacheless MCUs |
| `RT_USING_DM` | Device model and OFW driver framework |
| `ARCH_RISCV_USING_IRQ_STACK` | Per-CPU interrupt stack |

The architecture generates `libcpu/risc-v/link.lds` only when the BSP root does
not provide `link.lds`. Device-model builds include `setup.c`; non-DM builds do
not. The DM setup supports both MMU and no-MMU systems. In a no-MMU build, the
BSP initializes the heap first and then calls `rt_hw_common_setup()` to
initialize OFW, CPU information, PIC, timer and SMP. The FDT itself is accessed
directly and firmware-provided FDT memory must remain accessible. OFW device
MMIO uses the identity mapping provided by `ioremap-nommu.c`.

## Startup

The generic startup follows the SBI boot ABI in S-mode:

```text
a0 = boot hart ID
a1 = physical address of the FDT
```

In M-mode it reads `mhartid` directly and does not depend on the reset value of
`a0`. By default, selecting the new common makes this architecture code the sole
owner of `_start`; the BSP must stop compiling its previous reset entry. The
common startup clears BSS and enters `rtthread_startup()`, but it does not
relocate MCU data from flash or initialize clocks.

A BSP that needs a platform-specific reset sequence can provide
`startup_gcc.S` in its BSP root. The build uses that file instead of the common
startup while continuing to use the common context, trap, CPU and timer
implementation. The BSP startup must provide `_start`, initialize the C runtime
state required by the platform, call `riscv_boot_hart_init()` for the boot hart,
and enter `rtthread_startup()`. An SMP BSP must also provide
`_secondary_cpu_entry`, use `riscv_hartid_to_cpu_id()` and
`riscv_cpu_id_set()` to establish the logical CPU ID before accessing per-CPU
state, and enter `rt_hw_secondary_cpu_bsp_start()`. An OFW BSP must preserve the
boot FDT and call `rt_hw_fdt_install_early()` before enabling address
translation or overwriting the firmware-provided FDT memory.

`riscv_boot_hart_init()` registers the boot hart as logical CPU0 and initializes
its current CPU ID. The common SMP startup maps each secondary hart to a logical
CPU ID before initializing its per-CPU architecture state.

## Hart IDs and SMP

For a non-DM SMP system, override the weak hart enumeration function when hart
IDs are not `0..RT_CPUS_NR-1`:

```c
#include <cpu.h>

rt_size_t riscv_hartid_list_get(rt_ubase_t *hartids, rt_size_t max_harts)
{
    static const rt_ubase_t platform_hartids[] = { 1, 3, 5, 7 };
    rt_size_t count = RT_ARRAY_SIZE(platform_hartids);

    if (count > max_harts)
    {
        count = max_harts;
    }

    rt_memcpy(hartids, platform_hartids, count * sizeof(*hartids));
    return count;
}
```

CPU boot, IPI and interrupt-controller code must translate IDs through
`riscv_cpu_id_to_hartid()` and `riscv_hartid_to_cpu_id()`.

The `cpu_ops_t` SBI and spin-wait backends belong to the DM CPU-node startup
flow. A non-DM SMP BSP provides its own `rt_hw_secondary_cpu_up()` and
`rt_hw_secondary_cpu_bsp_start()` implementations according to its reset,
power and per-CPU initialization sequence.

## Interrupt stack

`ARCH_RISCV_USING_IRQ_STACK` gives each CPU a dedicated interrupt stack. It is
enabled by default for M-mode and non-DM ports, and disabled for RT-Smart,
where `xscratch` is used to switch between user and kernel stacks. The common
startup initializes it after the current logical CPU ID is available.

The trap entry saves the exception frame on the interrupted thread stack, so
the scheduler and signal code keep the same frame ABI. Only the C interrupt or
exception handler runs on the per-CPU interrupt stack. Nested traps continue
on that interrupt stack.

## Non-DM interrupts

Non-DM builds provide the classic `rt_hw_interrupt_*` interface automatically.
Choose one controller topology:

- `ARCH_RISCV_NON_DM_IRQ_PLIC`: local RISC-V INTC plus SiFive-compatible PLIC.
- `ARCH_RISCV_NON_DM_IRQ_CLIC`: CLIC handles local and external interrupts.

Set `ARCH_RISCV_MAX_IRQS` large enough for local, IPI and external vectors. Set
`ARCH_RISCV_INTC_ANDES` for the Andes/Nuclei local interrupt CSR layout.

The BSP provides MMIO information by overriding only the hooks it uses:

```c
#include <interrupt.h>

rt_ubase_t platform_get_clint_base(void) { return CLINT_BASE; }
rt_size_t platform_get_clint_size(void) { return CLINT_SIZE; }

rt_ubase_t platform_get_plic_base(void) { return PLIC_BASE; }
rt_size_t platform_get_plic_size(void) { return PLIC_SIZE; }
rt_ubase_t platform_get_plic_quirks(void)
{
    return RISCV_PLIC_QUIRK_EDGE_INTERRUPT;
}
```

All MMIO hooks return zero by default. CLINT is optional when a platform
overrides the timer and IPI implementations; PLIC or CLIC MMIO is required when
the corresponding non-DM interrupt backend is selected. In a no-MMU build,
these addresses are used through an explicit identity mapping.

For CLIC, implement `platform_get_clic_base()`,
`platform_get_clic_size()` and optionally `platform_get_clic_quirks()`. The
common driver uses direct mode by default. Return `RISCV_CLIC_QUIRK_SHV` only
when the BSP supplies a valid hardware vector table through `fast_irq_vectors`.

Use the mapping macros instead of assuming local and external vectors share a
number space:

```c
rt_hw_interrupt_install(IRQ_PLIC(device_hwirq), isr, data, "device");
rt_hw_interrupt_umask(IRQ_PLIC(device_hwirq));
```

A platform with a different interrupt controller should add its backend to the
common PIC implementation as part of its migration.

## Timer

The common timer uses `rdtime` with SBI/Sstc in S-mode and CLINT `mtime` and
`mtimecmp` in M-mode. Initialize the frequency before starting the timer:

```c
riscv_timer_set_frequency(TIMER_FREQUENCY);
riscv_timer_init();
```

The frequency must be at least `RT_TICK_PER_SECOND`. On SMP systems the boot CPU
publishes the timer parameters before secondary CPUs initialize their local
timer interrupt.

The common non-DM M-mode interrupt setup calls `riscv_timer_probe()` with the
CLINT registers. Platforms with another timer implementation can override the
weak `riscv_timer_rdtime()`, `riscv_timer_set_compare()` and
`rt_hw_tick_init()` functions.

## ISA and atomics

Non-DM BSPs populate the ISA bitmap during board initialization. For example:

```c
riscv_isa_ext_set(I);
riscv_isa_ext_set(M);
riscv_isa_ext_set(A);
riscv_isa_ext_set(C);
```

`atomic_riscv.c` is compiled only with `RT_USING_HW_ATOMIC`. SMP selects this
option because the common spinlock implementation requires the A extension.
Uniprocessor MCU ports without A use the kernel software atomic path.

## Board initialization

A typical non-DM board performs initialization in this order:

```c
void rt_hw_board_init(void)
{
    riscv_isa_ext_set(I);
    rt_hw_cpu_icache_enable();
    rt_hw_cpu_dcache_enable();
    rt_hw_interrupt_init();
    riscv_timer_set_frequency(TIMER_FREQUENCY);
    riscv_timer_init();

    /* Heap, console, components and device initialization follow. */
}
```

Validate startup, tick, exception handling and thread switching first. SMP
ports must additionally test a non-zero boot hart and every secondary CPU.
