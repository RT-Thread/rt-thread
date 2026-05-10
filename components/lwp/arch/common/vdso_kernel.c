/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2024-07-04     rcitach        init ver.
 * 2025-04-22     ScuDays        Add VDSO functionality under the riscv64 architecture.
 * 2026-04-21     rcitach        Refactor vDSO runtime around the clock data page.
 */

#include <rtthread.h>
#include <mmu.h>
#include <elf.h>
#include <time.h>
#include <lwp_user_mm.h>
#include <drivers/clock_time.h>
#ifdef RT_USING_RTC
#include <rtdevice.h>
#endif

#include <vdso_kernel.h>
#include <vdso_kernel_internal.h>
#define DBG_TAG "vdso"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

enum rt_vdso_binary_id
{
    RT_VDSO_BINARY_COMMON,
};

struct rt_vdso_binary_info
{
    const char *name;
    const char *image_start;
    const char *image_end;
    unsigned long page_count;
};

static struct rt_vdso_binary_info rt_vdso_binaries[] = {
    [RT_VDSO_BINARY_COMMON] = {
        .name = "rt_vdso_common",
        .image_start = __rt_vdso_image_start,
        .image_end = __rt_vdso_image_end,
    },
};

static union
{
    struct rt_vdso_data_page data_page;
    uint8_t raw[RT_VDSO_DATA_PAGE_COUNT * ARCH_PAGE_SIZE];
} rt_vdso_data_page_store RT_VDSO_DATA_PAGE_ALIGNED;
struct rt_vdso_data_page *rt_vdso_kernel_data_page = &rt_vdso_data_page_store.data_page;
static struct rt_spinlock rt_vdso_data_page_lock;
static int rt_vdso_runtime_status = RT_EOK;

static struct timespec rt_vdso_realtime_offset;
static rt_bool_t rt_vdso_realtime_offset_ready;

#ifdef MMU_MAP_U_ROCB_XN
#define RT_VDSO_DATA_PAGE_ATTR MMU_MAP_U_ROCB_XN

#elif defined(MMU_MAP_U_ROCB)
#define RT_VDSO_DATA_PAGE_ATTR MMU_MAP_U_ROCB

#else
#error "No user-read-only mapping available for vDSO data page!"
#endif

#define RT_VDSO_IMAGE_PAGE_ATTR MMU_MAP_U_ROCB

static void rt_vdso_normalize_timespec(struct timespec *ts)
{
    while (ts->tv_nsec >= RT_VDSO_NSEC_PER_SEC)
    {
        ts->tv_sec += 1;
        ts->tv_nsec -= RT_VDSO_NSEC_PER_SEC;
    }

    while (ts->tv_nsec < 0)
    {
        ts->tv_sec -= 1;
        ts->tv_nsec += RT_VDSO_NSEC_PER_SEC;
    }
}

static void rt_vdso_counter_to_timespec(rt_uint64_t counter_value,
                                        struct timespec *ts)
{
    rt_uint64_t monotonic_ns;

    monotonic_ns = rt_clock_time_counter_to_ns(counter_value);
    ts->tv_sec = monotonic_ns / RT_VDSO_NSEC_PER_SEC;
    ts->tv_nsec = monotonic_ns % RT_VDSO_NSEC_PER_SEC;
}

static rt_uint64_t rt_vdso_read_arch_counter(void)
{
    rt_uint64_t counter;

#if defined(__aarch64__)
    __asm__ volatile("mrs %0, CNTVCT_EL0" : "=r"(counter));
#elif defined(__arm__)
    rt_uint32_t lo;
    rt_uint32_t hi;

    __asm__ volatile("mrrc p15, 1, %0, %1, c14" : "=r"(lo), "=r"(hi));
    counter = ((rt_uint64_t)hi << 32) | lo;
#elif defined(__riscv)
    __asm__ volatile("rdtime %0" : "=r"(counter));
#else
    counter = rt_clock_time_get_counter();
#endif

    return counter;
}

static struct timespec rt_vdso_timespec_subtract(const struct timespec *lhs,
                                                 const struct timespec *rhs)
{
    struct timespec ret;

    ret.tv_sec = lhs->tv_sec - rhs->tv_sec;
    ret.tv_nsec = lhs->tv_nsec - rhs->tv_nsec;
    rt_vdso_normalize_timespec(&ret);

    return ret;
}

static struct timespec rt_vdso_add_timespec(const struct timespec *lhs,
                                            const struct timespec *rhs)
{
    struct timespec ret;

    ret.tv_sec = lhs->tv_sec + rhs->tv_sec;
    ret.tv_nsec = lhs->tv_nsec + rhs->tv_nsec;
    rt_vdso_normalize_timespec(&ret);

    return ret;
}

static int rt_vdso_read_monotonic_snapshot(struct timespec *monotonic_time,
                                           rt_uint64_t *counter_value,
                                           rt_uint64_t *counter_freq)
{
    rt_uint64_t monotonic_counter;

    monotonic_counter = rt_clock_time_get_counter();
    *counter_freq = rt_clock_time_get_freq();
    if (*counter_freq == 0)
    {
        return -RT_ERROR;
    }

    /* User vDSO computes deltas from the raw architecture counter. */
    *counter_value = rt_vdso_read_arch_counter();
    rt_vdso_counter_to_timespec(monotonic_counter, monotonic_time);

    return RT_EOK;
}

static void rt_vdso_update_data_page_flags(void)
{
    rt_uint64_t flags = 0;

    if (rt_vdso_realtime_offset_ready)
    {
        flags |= RT_VDSO_FLAG_REALTIME_VALID;
    }

    rt_vdso_kernel_data_page->flags = flags;
}

static void rt_vdso_store_clock_snapshot(const struct timespec *monotonic_time,
                                         rt_uint64_t counter_value,
                                         rt_uint64_t counter_freq)
{
    rt_vdso_kernel_data_page->counter_last = counter_value;
    rt_vdso_kernel_data_page->counter_freq = counter_freq;
    rt_vdso_update_data_page_flags();
    rt_vdso_kernel_data_page->base_time[RT_VDSO_CLOCK_MONOTONIC_INDEX] = *monotonic_time;
    if (rt_vdso_realtime_offset_ready)
    {
        rt_vdso_kernel_data_page->base_time[RT_VDSO_CLOCK_REALTIME_INDEX] =
            rt_vdso_add_timespec(monotonic_time, &rt_vdso_realtime_offset);
    }
    else
    {
        rt_vdso_kernel_data_page->base_time[RT_VDSO_CLOCK_REALTIME_INDEX] = *monotonic_time;
    }
}

void rt_vdso_set_realtime(const struct timespec *realtime)
{
    struct timespec monotonic;
    rt_uint64_t counter;
    rt_uint64_t freq;
    rt_base_t level;
    if (rt_vdso_runtime_status != RT_EOK || realtime == RT_NULL)
    {
        return;
    }

    if (rt_vdso_read_monotonic_snapshot(&monotonic, &counter, &freq) != RT_EOK)
    {
        return;
    }

    level = rt_spin_lock_irqsave(&rt_vdso_data_page_lock);
    rt_vdso_data_page_write_begin(rt_vdso_kernel_data_page);
    rt_vdso_realtime_offset = rt_vdso_timespec_subtract(realtime, &monotonic);
    rt_vdso_realtime_offset_ready = RT_TRUE;
    rt_vdso_store_clock_snapshot(&monotonic, counter, freq);
    rt_vdso_data_page_write_end(rt_vdso_kernel_data_page);
    rt_spin_unlock_irqrestore(&rt_vdso_data_page_lock, level);
}

static void *rt_vdso_map_physical_pages(struct rt_lwp *lwp, void *user_va,
                                        void *kernel_pa, size_t map_size,
                                        rt_size_t attr)
{
    int err;
    char *va;
    size_t offset = 0;

    if (!map_size)
    {
        return RT_NULL;
    }

    if (user_va)
    {
        if (((size_t)user_va & ARCH_PAGE_MASK) !=
            ((size_t)kernel_pa & ARCH_PAGE_MASK))
        {
            return RT_NULL;
        }
    }

    offset = (size_t)kernel_pa & ARCH_PAGE_MASK;
    map_size += offset + ARCH_PAGE_SIZE - 1;
    map_size &= ~ARCH_PAGE_MASK;
    kernel_pa = (void *)((size_t)kernel_pa & ~ARCH_PAGE_MASK);
    struct rt_mm_va_hint hint = {
        .flags = 0,
        .limit_range_size = lwp->aspace->size,
        .limit_start = lwp->aspace->start,
        .prefer = user_va,
        .map_size = map_size,
    };

    if (user_va != RT_NULL)
    {
        hint.flags |= MMF_MAP_FIXED;
    }

    err = rt_aspace_map_phy(lwp->aspace, &hint, attr, MM_PA_TO_OFF(kernel_pa),
                            (void **)&va);
    if (err != RT_EOK)
    {
        return RT_NULL;
    }

    return va + offset;
}


static int rt_vdso_map_binary_pages(enum rt_vdso_binary_id binary_id,
                                    struct rt_lwp *lwp)
{
    void *data_page_base = RT_NULL;
    void *image_base = RT_NULL;
    unsigned long data_page_len;
    unsigned long image_len;

    RT_ASSERT(lwp != RT_NULL);

    data_page_len = RT_VDSO_DATA_PAGE_COUNT * ARCH_PAGE_SIZE;
    image_len = rt_vdso_binaries[binary_id].page_count << ARCH_PAGE_SHIFT;

    data_page_base = rt_vdso_map_physical_pages(
        lwp, RT_NULL, rt_kmem_v2p((void *)rt_vdso_get_kernel_data_page()),
        data_page_len, RT_VDSO_DATA_PAGE_ATTR);
    if (data_page_base == RT_NULL)
    {
        lwp->vdso_vbase = RT_NULL;
        return -RT_ERROR;
    }

    image_base = (uint8_t *)data_page_base + data_page_len;
    image_base = rt_vdso_map_physical_pages(
        lwp, image_base,
        rt_kmem_v2p((void *)rt_vdso_binaries[binary_id].image_start),
        image_len, RT_VDSO_IMAGE_PAGE_ATTR);
    if (image_base == RT_NULL)
    {
        lwp_unmap_user_phy(lwp, data_page_base);
        lwp->vdso_vbase = RT_NULL;
        return -RT_ERROR;
    }

    lwp->vdso_vbase = image_base;
    return RT_EOK;
}

int rt_vdso_map_process_image(struct rt_lwp *lwp)
{
    if (rt_vdso_runtime_status != RT_EOK)
    {
        return -RT_ERROR;
    }

    return rt_vdso_map_binary_pages(RT_VDSO_BINARY_COMMON, lwp);
}

void rt_vdso_sync_clock_data(void)
{
    struct timespec monotonic;
    rt_uint64_t counter;
    rt_uint64_t freq;

    if (rt_vdso_runtime_status != RT_EOK)
    {
        return;
    }

    if (rt_vdso_read_monotonic_snapshot(&monotonic, &counter, &freq) != RT_EOK)
    {
        return;
    }

    rt_spin_lock(&rt_vdso_data_page_lock);
    rt_vdso_data_page_write_begin(rt_vdso_kernel_data_page);
    rt_vdso_store_clock_snapshot(&monotonic, counter, freq);
    rt_vdso_data_page_write_end(rt_vdso_kernel_data_page);
    rt_spin_unlock(&rt_vdso_data_page_lock);
}

static int rt_vdso_validate_elf_header(const void *image)
{
    const unsigned char *ident = (const unsigned char *)image;

#if defined(__aarch64__)
    const Elf64_Ehdr *ehdr = (const Elf64_Ehdr *)image;

    if (ident[EI_CLASS] != ELFCLASS64)
    {
        LOG_E("vDSO ELF class mismatch: expect ELF64");
        return -RT_ERROR;
    }

    if (ehdr->e_type != ET_DYN)
    {
        LOG_E("vDSO ELF type mismatch!");
        return -RT_ERROR;
    }

    if (ehdr->e_machine != EM_AARCH64)
    {
        LOG_E("vDSO machine mismatch: expect AArch64");
        return -RT_ERROR;
    }
#elif defined(__arm__)
    const Elf32_Ehdr *ehdr = (const Elf32_Ehdr *)image;

    if (ident[EI_CLASS] != ELFCLASS32)
    {
        LOG_E("vDSO ELF class mismatch: expect ELF32");
        return -RT_ERROR;
    }

    if (ehdr->e_type != ET_DYN)
    {
        LOG_E("vDSO ELF type mismatch!");
        return -RT_ERROR;
    }

    if (ehdr->e_machine != EM_ARM)
    {
        LOG_E("vDSO machine mismatch: expect ARM");
        return -RT_ERROR;
    }
#elif defined(__riscv)
    const Elf64_Ehdr *ehdr = (const Elf64_Ehdr *)image;

    if (ident[EI_CLASS] != ELFCLASS64)
    {
        LOG_E("vDSO ELF class mismatch: expect ELF64");
        return -RT_ERROR;
    }

    if (ehdr->e_type != ET_DYN)
    {
        LOG_E("vDSO ELF type mismatch!");
        return -RT_ERROR;
    }

    if (ehdr->e_machine != EM_RISCV)
    {
        LOG_E("vDSO machine mismatch: expect RISC-V");
        return -RT_ERROR;
    }
#else
    LOG_E("vDSO unsupported architecture!");
    return -RT_ERROR;
#endif

    return RT_EOK;
}

static int rt_vdso_validate_image(void)
{
    const void *image = rt_vdso_binaries[RT_VDSO_BINARY_COMMON].image_start;

    rt_memset(rt_vdso_data_page_store.raw, 0, sizeof(rt_vdso_data_page_store.raw));
    rt_vdso_realtime_offset_ready = RT_FALSE;
    rt_memset(&rt_vdso_realtime_offset, 0, sizeof(rt_vdso_realtime_offset));

    if (rt_memcmp(image, RT_VDSO_IMAGE_ELF_MAGIC, RT_VDSO_IMAGE_ELF_MAGIC_LEN))
    {
        LOG_E("vDSO is not a valid ELF object!");
        rt_vdso_runtime_status = -RT_ERROR;
        return -RT_ERROR;
    }

    if (rt_vdso_validate_elf_header(image) != RT_EOK)
    {
        rt_vdso_runtime_status = -RT_ERROR;
        return -RT_ERROR;
    }

    rt_vdso_binaries[RT_VDSO_BINARY_COMMON].page_count =
        (rt_vdso_binaries[RT_VDSO_BINARY_COMMON].image_end -
         rt_vdso_binaries[RT_VDSO_BINARY_COMMON].image_start) >>
        ARCH_PAGE_SHIFT;
    if (rt_vdso_binaries[RT_VDSO_BINARY_COMMON].page_count == 0)
    {
        LOG_E("vDSO image is empty!");
        rt_vdso_runtime_status = -RT_ERROR;
        return -RT_ERROR;
    }

    return RT_EOK;
}
INIT_COMPONENT_EXPORT(rt_vdso_validate_image);
