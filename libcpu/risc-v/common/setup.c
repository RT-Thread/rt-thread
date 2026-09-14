/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-04-20     GuEe-GUI     the first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#if __riscv_xlen == 128
#define DBG_TAG "cpu.rv128"
#elif __riscv_xlen == 64
#define DBG_TAG "cpu.setup"
#elif __riscv_xlen == 32
#define DBG_TAG "cpu.rv32"
#else
#error "Unexpected __riscv_xlen"
#endif
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <cpu.h>
#include <sbi.h>
#include <board.h>
#ifdef RT_USING_CACHE
#include <cache.h>
#endif
#include <setup.h>
#include <isa_ext.h>
#include <cpuport.h>
#ifdef RT_USING_SMP
#include <smp_call.h>
#endif
#include <interrupt.h>
#include <riscv_timer.h>
#ifdef ARCH_MM_MMU
#include <mmu.h>
#include <stdlib.h>
#include <ioremap.h>
#include <mm_memblock.h>
#include <dt-bindings/size.h>
#endif
#ifdef RT_USING_LWP
#include <lwp.h>
#include <lwp_arch.h>
#endif

#ifdef ARCH_MM_MMU
#ifndef IOREMAP_SIZE
#define IOREMAP_SIZE 0x20000000
#endif
#endif

#ifdef RT_USING_BUILTIN_FDT
extern const rt_uint8_t rt_hw_builtin_fdt[];
#endif
#ifdef ARCH_MM_MMU
extern rt_ubase_t _start, _end;
extern rt_ubase_t MMUTable[];
#if __riscv_xlen == 32 && !defined(RT_USING_SMART)
extern char __text_start;
#endif
#endif

static void *fdt_ptr = RT_NULL;
static rt_size_t fdt_size = 0;

#ifdef RT_USING_SMP
static rt_uint32_t cpu_boot_delay_us = 0;

#ifndef ARCH_RISCV_M_MODE
extern struct cpu_ops_t cpu_sbi_ops;
#endif
extern struct cpu_ops_t cpu_spinwait_ops;

static struct cpu_ops_t *cpu_ops = &cpu_spinwait_ops;
static struct rt_ofw_node *cpu_np[RT_CPUS_NR] = { };
#endif /* RT_USING_SMP */

#ifdef ARCH_MM_MMU
static const struct { rt_uint8_t size; const char name[11]; } mmu_type[] =
{
    {  0, "riscv,none" },
#if __riscv_xlen == 32
    { 32, "riscv,sv32" },
#else
    { 39, "riscv,sv39" },
    { 48, "riscv,sv48" },
    { 57, "riscv,sv57" },
    { 64, "riscv,sv64" },
#endif
};
#endif /* ARCH_MM_MMU */

rt_weak void rt_hw_fdt_vendor_install_early(void *fdt)
{
    RT_UNUSED(fdt);
}

void rt_hw_fdt_install_early(void *fdt)
{
    int registered_cpus = 1, cpus, cpu;

#ifdef RT_USING_BUILTIN_FDT
    fdt = (void *)rt_hw_builtin_fdt;
#endif

    if (!fdt || fdt_check_header(fdt))
    {
        fdt_ptr = RT_NULL;
        fdt_size = 0;
        return;
    }

    fdt_ptr = fdt;
    fdt_size = fdt_totalsize(fdt);

    rt_hw_fdt_vendor_install_early(fdt);

#ifdef ARCH_MM_MMU
    rt_hw_arch_vaddr_width = ARCH_ADDRESS_WIDTH_BITS;
#endif

    cpus = fdt_path_offset(fdt, "/cpus");
    if (cpus < 0)
    {
        return;
    }

    fdt_for_each_subnode(cpu, fdt, cpus)
    {
        uint32_t hartid;
#ifdef ARCH_MM_MMU
        int size;
        const char *name = fdt_getprop(fdt, cpu, "mmu-type", RT_NULL);
#endif

        if (fdt_getprop_u32(fdt, cpu, "reg", &hartid, RT_NULL))
        {
            continue;
        }

        if (hartid != boot_cpu_hartid && riscv_hartid_to_cpu_id(hartid) < 0)
        {
            if (registered_cpus >= RT_CPUS_NR)
            {
                continue;
            }
            ++registered_cpus;
        }

        riscv_hartid_register(hartid);

        if (hartid == boot_cpu_hartid)
        {
            uint32_t cbom_size;

            if (!fdt_getprop_u32(fdt, cpu, "riscv,cbom-block-size", &cbom_size, RT_NULL) &&
                cbom_size > 0)
            {
                riscv_isa_ext_set(ZICBOM);
#ifdef RT_USING_CACHE
                riscv_cache_set_cbom_block_size(cbom_size);
#endif
            }
        }

#ifdef ARCH_MM_MMU
        size = name ? rt_hw_arch_vaddr_width : 0;

        for (int i = 0; name && i < RT_ARRAY_SIZE(mmu_type); ++i)
        {
            rt_typeof(mmu_type[0]) *type = &mmu_type[i];

            if (!rt_strcmp(name, type->name))
            {
                size = type->size;
                break;
            }
        }

        if (size < rt_hw_arch_vaddr_width)
        {
            rt_hw_arch_vaddr_width = size;
        }
#endif /* ARCH_MM_MMU */
    }
}

rt_weak void rt_hw_idle_wfi(void)
{
    rt_hw_wfi();
}

static struct { const char *name; rt_uint8_t size; } isa_ext[] =
{
#define DECLARE_ISA(isa, name)  [RISCV_ISA_EXT_##isa] = { name, sizeof(name) - 1 },
    DECLARE_ISA(I, "i")
    DECLARE_ISA(M, "m")
    DECLARE_ISA(A, "a")
    DECLARE_ISA(F, "f")
    DECLARE_ISA(D, "d")
    DECLARE_ISA(Q, "q")
    DECLARE_ISA(C, "c")
    DECLARE_ISA(V, "v")
    DECLARE_ISA(H, "h")
    DECLARE_ISA(SSCOFPMF, "sscofpmf")
    DECLARE_ISA(SSTC, "sstc")
    DECLARE_ISA(SVINVAL, "svinval")
    DECLARE_ISA(SVPBMT, "svpbmt")
    DECLARE_ISA(ZBB, "zbb")
    DECLARE_ISA(ZICBOM, "zicbom")
    DECLARE_ISA(ZIHINTPAUSE, "zihintpause")
    DECLARE_ISA(SVNAPOT, "svnapot")
    DECLARE_ISA(ZICBOZ, "zicboz")
    DECLARE_ISA(SMAIA, "smaia")
    DECLARE_ISA(SSAIA, "ssaia")
    DECLARE_ISA(ZBA, "zba")
    DECLARE_ISA(ZBS, "zbs")
    DECLARE_ISA(ZICNTR, "zicntr")
    DECLARE_ISA(ZICSR, "zicsr")
    DECLARE_ISA(ZIFENCEI, "zifencei")
    DECLARE_ISA(ZIHPM, "zihpm")
    DECLARE_ISA(SMSTATEEN, "smstateen")
    DECLARE_ISA(ZICOND, "zicond")
    DECLARE_ISA(ZBC, "zbc")
    DECLARE_ISA(ZBKB, "zbkb")
    DECLARE_ISA(ZBKC, "zbkc")
    DECLARE_ISA(ZBKX, "zbkx")
    DECLARE_ISA(ZKND, "zknd")
    DECLARE_ISA(ZKNE, "zkne")
    DECLARE_ISA(ZKNH, "zknh")
    DECLARE_ISA(ZKR, "zkr")
    DECLARE_ISA(ZKSED, "zksed")
    DECLARE_ISA(ZKSH, "zksh")
    DECLARE_ISA(ZKT, "zkt")
    DECLARE_ISA(ZVBB, "zvbb")
    DECLARE_ISA(ZVBC, "zvbc")
    DECLARE_ISA(ZVKB, "zvkb")
    DECLARE_ISA(ZVKG, "zvkg")
    DECLARE_ISA(ZVKNED, "zvkned")
    DECLARE_ISA(ZVKNHA, "zvknha")
    DECLARE_ISA(ZVKNHB, "zvknhb")
    DECLARE_ISA(ZVKSED, "zvksed")
    DECLARE_ISA(ZVKSH, "zvksh")
    DECLARE_ISA(ZVKT, "zvkt")
    DECLARE_ISA(ZFH, "zfh")
    DECLARE_ISA(ZFHMIN, "zfhmin")
    DECLARE_ISA(ZIHINTNTL, "zihintntl")
    DECLARE_ISA(ZVFH, "zvfh")
    DECLARE_ISA(ZVFHMIN, "zvfhmin")
    DECLARE_ISA(ZFA, "zfa")
    DECLARE_ISA(ZTSO, "ztso")
    DECLARE_ISA(ZACAS, "zacas")
    DECLARE_ISA(XANDESPMU, "xandespmu")
#undef DECLARE_ISA
};

rt_inline void cpu_info_init(void)
{
    int i = 0;
    rt_uint32_t value;
    const char *string;
    struct rt_ofw_prop *prop;
    struct rt_ofw_node *np, *boot_cpu_np = RT_NULL;

    if ((np = rt_ofw_find_node_by_path("/cpus")) &&
        !rt_ofw_prop_read_u32(np, "timebase-frequency", &value))
    {
        riscv_timer_set_frequency(value);

    #ifdef RT_USING_HWTIMER
        if (!rt_device_hwtimer_us_delay)
        {
            rt_device_hwtimer_us_delay = &riscv_timer_us_delay;
        }
    #endif /* RT_USING_HWTIMER */
    }
    else
    {
        LOG_E("No '%s' in DTS", "timebase-frequency");
    }

#ifdef RT_USING_SMP
    rt_ofw_prop_read_u32(np, "cpu-boot-delay-us", &cpu_boot_delay_us);
#endif

    rt_ofw_node_put(np);

#if defined(RT_USING_SMP) && !defined(ARCH_RISCV_M_MODE)
    if (sbi_probe_extension(SBI_EXT_ID_HSM))
    {
        rt_bool_t use_hsm = RT_TRUE;

        for (int cpu_id = 0; cpu_id < RT_CPUS_NR; ++cpu_id)
        {
            rt_ubase_t hartid;
            int status;

            if (!riscv_cpu_id_available(cpu_id))
            {
                continue;
            }

            hartid = riscv_cpu_id_to_hartid(cpu_id);
            if (hartid == boot_cpu_hartid)
            {
                continue;
            }

            status = sbi_hsm_hart_status(hartid);
            if (status == SBI_HSM_STATUS_STARTED)
            {
                use_hsm = RT_FALSE;
                break;
            }
        }

        if (use_hsm)
        {
            LOG_I("SBI HSM extension detected");
            cpu_ops = &cpu_sbi_ops;
        }
        else
        {
            LOG_I("SBI HSM extension detected, use spinwait for started harts");
        }
    }
#endif /* RT_USING_SMP && !ARCH_RISCV_M_MODE */

    rt_ofw_foreach_cpu_node(np)
    {
        rt_ubase_t hartid = (rt_ubase_t)rt_ofw_get_cpu_hwid(np, 0);

        if (hartid == boot_cpu_hartid)
        {
            boot_cpu_np = np;
            rt_ofw_node_get(boot_cpu_np);
        }

    #ifdef RT_USING_SMP
        int cpu_id = riscv_hartid_to_cpu_id(hartid);

        if (cpu_id >= 0 && cpu_id < RT_CPUS_NR)
        {
            cpu_np[cpu_id] = np;

            if (cpu_ops->cpu_init)
            {
                cpu_ops->cpu_init(cpu_id, np);
            }
        }
    #endif /* RT_USING_SMP */
    }

    if (!(np = boot_cpu_np))
    {
        LOG_E("No '%s' in DTS", "Boot CPU");
        return;
    }

    rt_ofw_foreach_prop_string(np, "riscv,isa-extensions", prop, string)
    {
        for (i = 0; i < RT_ARRAY_SIZE(isa_ext); ++i)
        {
            rt_typeof(isa_ext[0]) *ext = &isa_ext[i];

            if (ext->name && !rt_strcmp(ext->name, string))
            {
                riscv_isa_ext_set_raw(i);
                break;
            }
        }
    }

    if (!rt_ofw_prop_read_bool(np, "riscv,isa-base"))
    {
        if (rt_ofw_prop_read_string(np, "riscv,isa", &string))
        {
            LOG_E("%s ISA no found", rt_ofw_node_full_name(np));
            goto _exit;
        }

        if ((!rt_strncmp(string, "rv32", 4) && __riscv_xlen != 32) ||
            (!rt_strncmp(string, "rv64", 4) && __riscv_xlen != 64))
        {
            LOG_E("%s ISA %.4s is not supported", rt_ofw_node_full_name(np), string);
            goto _exit;
        }

        string += 4;

        /* ISA: 'i', 'm', 'a', 'f', 'd', 'q', 'c', 'v', 'h'... */
        while (*string && *string != '_')
        {
            for (i = 0; i < RISCV_ISA_EXT_BASE; ++i)
            {
                rt_typeof(isa_ext[0]) *ext = &isa_ext[i];

                if (ext->name && ext->name[0] == *string)
                {
                    riscv_isa_ext_set_raw(i);
                    break;
                }
            }

            ++string;
        }

        /* Skip '_' */
        while (*string && *(++string))
        {
            int size = 0;

            for (i = RISCV_ISA_EXT_BASE; i < RT_ARRAY_SIZE(isa_ext); ++i)
            {
                rt_typeof(isa_ext[0]) *ext = &isa_ext[i];

                if (ext->name && !rt_strncmp(ext->name, string, ext->size))
                {
                    size = ext->size;
                    riscv_isa_ext_set_raw(i);
                    break;
                }
            }

            if (!size)
            {
                const char *skip = rt_strstr(string, "_");

                size = skip ? skip - string : rt_strlen(string);

                LOG_E("Unknow ISA %.*s", size, string);
            }

            string += size;
        }
    }

_exit:
    rt_ofw_node_put(np);
}

#if defined(ARCH_MM_MMU) && defined(RT_USING_DMA)
static rt_size_t string_to_size(const char *string, const char *who)
{
    char unit;
    rt_size_t size;
    const char *cp = string;

    size = atoi(cp);

    while (*cp >= '0' && *cp <= '9')
    {
        ++cp;
    }

    unit = *cp;
    if (unit >= 'a' && unit <= 'z')
    {
        unit -= 'a' - 'A';
    }

    if (unit == 'M')
    {
        size *= SIZE_MB;
    }
    else if (unit == 'K')
    {
        size *= SIZE_KB;
    }
    else if (unit == 'G')
    {
        size *= SIZE_GB;
    }
    else
    {
        LOG_W("Unknown unit of '%c' in `%s`", unit, who);
    }

    return size;
}
#endif /* ARCH_MM_MMU && RT_USING_DMA */

void rt_hw_common_setup(void)
{
#ifdef RT_USING_BUILTIN_FDT
    fdt_ptr = (void *)rt_hw_builtin_fdt;
    fdt_size = fdt_totalsize(fdt_ptr);
#endif

    if (!fdt_ptr)
    {
        LOG_E("No valid FDT installed");
        RT_ASSERT(0);
        return;
    }

#ifdef ARCH_MM_MMU
    rt_uint64_t initrd_ranges[3];
    rt_size_t kernel_start, kernel_end;
    rt_size_t heap_start, heap_end;
    rt_size_t init_page_start, init_page_end;
    rt_size_t fdt_start, fdt_end;
    rt_region_t init_page_region = { 0 };
    rt_region_t platform_mem_region = { 0 };
    static struct mem_desc platform_mem_desc;
    const rt_ubase_t pv_off = PV_OFFSET;

#ifdef RT_USING_SMART
#if KERNEL_VADDR_START > USER_VADDR_START
    rt_hw_mmu_map_init(&rt_kernel_space, (void *)(0UL - IOREMAP_SIZE), IOREMAP_SIZE, MMUTable, pv_off);
#else
    rt_hw_mmu_map_init(&rt_kernel_space, (void *)(USER_VADDR_START - IOREMAP_SIZE), IOREMAP_SIZE, MMUTable, pv_off);
#endif
#else
#if __riscv_xlen == 32
    rt_hw_mmu_map_init(&rt_kernel_space, (void *)((rt_ubase_t)&__text_start - IOREMAP_SIZE), IOREMAP_SIZE, MMUTable, 0);
#else
    /* Keep dynamic mappings within the lower canonical address range. */
    rt_hw_mmu_map_init(&rt_kernel_space, (void *)((1UL << (rt_hw_arch_vaddr_width - 1)) - IOREMAP_SIZE), IOREMAP_SIZE, MMUTable, 0);
#endif
#endif /* RT_USING_SMART */

    kernel_start    = RT_ALIGN_DOWN((rt_size_t)&_start + pv_off - 64, ARCH_PAGE_SIZE);
    kernel_end      = RT_ALIGN((rt_size_t)&_end + pv_off, ARCH_PAGE_SIZE);
    heap_start      = kernel_end;
    heap_end        = RT_ALIGN(heap_start + ARCH_HEAP_SIZE, ARCH_PAGE_SIZE);
    init_page_start = heap_end;
    init_page_end   = RT_ALIGN(init_page_start + ARCH_INIT_PAGE_SIZE, ARCH_PAGE_SIZE);
    fdt_start       = init_page_end;
    fdt_end         = RT_ALIGN(fdt_start + fdt_size, ARCH_PAGE_SIZE);

    platform_mem_region.start = kernel_start;
#ifndef RT_USING_BUILTIN_FDT
    platform_mem_region.end   = fdt_end;
#else
    platform_mem_region.end   = init_page_end;
    (void)fdt_start;
    (void)fdt_end;
#endif

    rt_memblock_reserve_memory("kernel", kernel_start, kernel_end, MEMBLOCK_NONE);
    rt_memblock_reserve_memory("memheap", heap_start, heap_end, MEMBLOCK_NONE);
    rt_memblock_reserve_memory("init-page", init_page_start, init_page_end, MEMBLOCK_NONE);
#ifndef RT_USING_BUILTIN_FDT
    rt_memblock_reserve_memory("fdt", fdt_start, fdt_end, MEMBLOCK_NONE);

    /* To virtual address */
    fdt_ptr = (void *)(fdt_ptr - pv_off);
#ifdef KERNEL_VADDR_START
    if ((rt_ubase_t)fdt_ptr + fdt_size - KERNEL_VADDR_START > ARCH_EARLY_MAP_SIZE)
    {
        fdt_ptr = rt_ioremap_early(fdt_ptr + pv_off, fdt_size);

        RT_ASSERT(fdt_ptr != RT_NULL);
    }
#endif /* KERNEL_VADDR_START */
    rt_memmove((void *)(fdt_start - pv_off), fdt_ptr, fdt_size);
    fdt_ptr = (void *)fdt_start - pv_off;
#endif /* RT_USING_BUILTIN_FDT */

    rt_system_heap_init((void *)(heap_start - pv_off), (void *)(heap_end - pv_off));

    init_page_region.start = init_page_start - pv_off;
    init_page_region.end = init_page_end - pv_off;
    rt_page_init(init_page_region);

    /* Create MMU mapping of kernel memory */
    platform_mem_region.start = RT_ALIGN_DOWN(platform_mem_region.start, ARCH_PAGE_SIZE);
    platform_mem_region.end   = RT_ALIGN(platform_mem_region.end, ARCH_PAGE_SIZE);

    platform_mem_desc.paddr_start = platform_mem_region.start;
    platform_mem_desc.vaddr_start = platform_mem_region.start - pv_off;
    platform_mem_desc.vaddr_end = platform_mem_region.end - pv_off - 1;
    platform_mem_desc.attr = NORMAL_MEM;

    rt_hw_mmu_setup(&rt_kernel_space, &platform_mem_desc, 1);
#endif /* ARCH_MM_MMU */

    if (rt_fdt_prefetch(fdt_ptr))
    {
        LOG_E("Failed to prefetch FDT");
        RT_ASSERT(0);
        return;
    }

#ifdef RT_USING_HWCACHE
    rt_hwcache_init();

    rt_hwcache_icache_enable();
    rt_hwcache_dcache_enable();
#endif /* RT_USING_HWCACHE */

    rt_fdt_scan_chosen_stdout();

#if defined(ARCH_MM_MMU) && defined(RT_USING_MEMBLOCK)
    rt_fdt_scan_initrd(initrd_ranges);

    rt_fdt_scan_memory();

#ifdef RT_USING_DMA
    do {
        const char *bootargs;
        rt_ubase_t dma_pool_base;
        rt_size_t cma_size = 0, coherent_pool_size = 0;

        if (!rt_fdt_bootargs_select("cma=", 0, &bootargs))
        {
            cma_size = string_to_size(bootargs, "cma");
        }

        if (!rt_fdt_bootargs_select("coherent_pool=", 0, &bootargs))
        {
            coherent_pool_size = string_to_size(bootargs, "coherent-pool");
        }

        if (cma_size <= coherent_pool_size)
        {
            if (cma_size || coherent_pool_size)
            {
                LOG_W("DMA pool %s=%u > %s=%u",
                    "CMA", cma_size, "coherent-pool", coherent_pool_size);
            }

            cma_size = 8 * SIZE_MB;
            coherent_pool_size = 2 * SIZE_MB;
        }

        dma_pool_base = platform_mem_region.end;
        rt_memblock_reserve_memory("dma-pool",
                dma_pool_base, dma_pool_base + cma_size + coherent_pool_size, MEMBLOCK_NONE);

        if (rt_dma_pool_extract(cma_size, coherent_pool_size))
        {
            LOG_E("Alloc DMA pool %s=%u, %s=%u fail",
                    "CMA", cma_size, "coherent-pool", coherent_pool_size);
        }
    } while (0);
#endif /* RT_USING_DMA */

    rt_memblock_setup_memory_environment();
#endif /* ARCH_MM_MMU && RT_USING_MEMBLOCK */

    rt_fdt_earlycon_kick(FDT_EARLYCON_KICK_UPDATE);

    if (rt_fdt_unflatten())
    {
        LOG_E("Failed to unflatten FDT");
        RT_ASSERT(0);
        return;
    }

    cpu_info_init();

#ifdef RT_USING_PIC
    rt_pic_init();
    rt_pic_irq_init();
#endif

    riscv_timer_init();

#ifdef RT_USING_COMPONENTS_INIT
    rt_components_board_init();
#endif

#if defined(RT_USING_CONSOLE) && defined(RT_USING_DEVICE)
    rt_ofw_console_setup();
#endif

#if defined(RT_USING_HOOK) || defined(RT_USING_IDLE_HOOK)
    rt_thread_idle_sethook(rt_hw_idle_wfi);
#endif

#ifdef RT_USING_SMP
    rt_smp_call_init();
#ifdef RT_USING_PIC
    /* Install the IPI handle */
    rt_hw_ipi_handler_install(RT_SCHEDULE_IPI, rt_scheduler_ipi_handler);
    rt_hw_ipi_handler_install(RT_STOP_IPI, rt_scheduler_ipi_handler);
    rt_hw_ipi_handler_install(RT_SMP_CALL_IPI, rt_smp_call_ipi_handler);
    rt_hw_interrupt_umask(RT_SCHEDULE_IPI);
    rt_hw_interrupt_umask(RT_STOP_IPI);
    rt_hw_interrupt_umask(RT_SMP_CALL_IPI);
#endif /* RT_USING_PIC */
#endif /* RT_USING_SMP */
}

#ifndef ARCH_RISCV_M_MODE
static rt_err_t sbi_srst_reboot_mode(struct rt_device *dev, char *cmd)
{
    if (!rt_strcmp(cmd, "software") || !rt_strcmp(cmd, "warm"))
    {
        sbi_srst_reboot(SBI_SRST_RESET_TYPE_WARM_REBOOT);
    }
    else
    {
        sbi_srst_reboot(SBI_SRST_RESET_TYPE_COLD_REBOOT);
    }

    return RT_EOK;
}

static int system_power_init(void)
{
    rt_dm_machine_shutdown = rt_dm_machine_shutdown ? : sbi_shutdown;

    if (has_srst_extension)
    {
        static struct rt_device pm;

        rt_dm_machine_shutdown = sbi_srst_power_off;

        rt_dm_dev_set_name(&pm, "SBI-SRST");
        rt_dm_reboot_mode_register(&pm, sbi_srst_reboot_mode);
    }

    return 0;
}
INIT_PREV_EXPORT(system_power_init);
#endif /* ARCH_RISCV_M_MODE */

#ifdef RT_USING_SMP
rt_weak void rt_hw_secondary_cpu_up(void)
{
    int cpu_id = rt_hw_cpu_id();
#ifdef ARCH_MM_MMU
    rt_ubase_t entry = (rt_ubase_t)rt_kmem_v2p(_secondary_cpu_entry);
#else
    rt_ubase_t entry = (rt_ubase_t)_secondary_cpu_entry;
#endif

    if (!entry)
    {
        LOG_E("Failed to translate '_secondary_cpu_entry' to physical address");
        RT_ASSERT(0);
    }

    /* Maybe we are no in the first cpu */
    for (int i = 0; i < RT_ARRAY_SIZE(cpu_np); ++i)
    {
        int err;

        if (!cpu_np[i] || i == cpu_id)
        {
            continue;
        }

        if (cpu_boot_delay_us)
        {
            rt_hw_us_delay(cpu_boot_delay_us);
        }

        if ((err = cpu_ops->cpu_boot(i, entry)))
        {
            LOG_W("Call cpu %d on %s", i, "failed");
        }
    }
}

rt_weak void rt_hw_secondary_cpu_bsp_start(void)
{
    int cpu_id;

    cpu_id = rt_hw_cpu_id();
    rt_hw_spin_lock(&_cpus_lock);

#ifdef ARCH_MM_MMU
    rt_hw_mmu_tbl_set((unsigned long)rt_kernel_space.page_table);
#endif

#ifdef RT_USING_PIC
    rt_pic_irq_init();
#endif

    riscv_timer_init();

    rt_dm_secondary_cpu_init();

#ifdef RT_USING_PIC
    rt_hw_interrupt_umask(RT_SCHEDULE_IPI);
    rt_hw_interrupt_umask(RT_STOP_IPI);
    rt_hw_interrupt_umask(RT_SMP_CALL_IPI);
#endif

    LOG_I("Call cpu %d on %s", cpu_id, "success");

    rt_system_scheduler_start();
}

rt_weak void rt_hw_secondary_cpu_idle_exec(void)
{
    rt_hw_idle_wfi();
}
#endif /* RT_USING_SMP */

void rt_hw_console_output(const char *str)
{
    rt_fdt_earlycon_output(str);
}
