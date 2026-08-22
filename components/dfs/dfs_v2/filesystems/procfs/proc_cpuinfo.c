/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#include "proc.h"
#include "procfs.h"

#include <rthw.h>
#include <rtdbg.h>

#include <fcntl.h>
#include <errno.h>

#include <dfs_dentry.h>

static rt_uint64_t cpu_midr(void)
{
#if defined(__aarch64__) || defined(__AARCH64EL__)
    rt_uint64_t value;

    __asm__ volatile ("mrs %0, midr_el1" : "=r" (value));
    return value;
#else
    return 0;
#endif
}

static void *seq_start(struct dfs_seq_file *seq, off_t *index)
{
    return (*index < RT_CPUS_NR) ? (void *)1 : RT_NULL;
}

static void seq_stop(struct dfs_seq_file *seq, void *data)
{
}

static void *seq_next(struct dfs_seq_file *seq, void *data, off_t *index)
{
    RT_UNUSED(seq);
    RT_UNUSED(data);
    *index += 1;
    return (*index < RT_CPUS_NR) ? (void *)1 : RT_NULL;
}

static int seq_show(struct dfs_seq_file *seq, void *data)
{
    rt_uint64_t midr;
    rt_uint32_t implementer;
    rt_uint32_t variant;
    rt_uint32_t architecture;
    rt_uint32_t part;
    rt_uint32_t revision;

    RT_UNUSED(data);
    midr = cpu_midr();
    implementer = (rt_uint32_t)((midr >> 24) & 0xffU);
    variant = (rt_uint32_t)((midr >> 20) & 0x0fU);
    architecture = (rt_uint32_t)((midr >> 16) & 0x0fU);
    part = (rt_uint32_t)((midr >> 4) & 0x0fffU);
    revision = (rt_uint32_t)(midr & 0x0fU);

    dfs_seq_printf(seq, "processor\t: %lu\n", (unsigned long)seq->index);
#if defined(__aarch64__) || defined(__AARCH64EL__)
    dfs_seq_puts(seq, "model name\t: ARMv8 Generic\n");
    dfs_seq_printf(seq, "CPU implementer\t: 0x%02lx\n", (unsigned long)implementer);
    dfs_seq_printf(seq, "CPU architecture: %lu\n", (unsigned long)(architecture ? architecture : 8U));
    dfs_seq_printf(seq, "CPU variant\t: 0x%lx\n", (unsigned long)variant);
    dfs_seq_printf(seq, "CPU part\t: 0x%03lx\n", (unsigned long)part);
    dfs_seq_printf(seq, "CPU revision\t: %lu\n", (unsigned long)revision);
#elif defined(__riscv)
    dfs_seq_puts(seq, "model name\t: RISC-V Generic\n");
    dfs_seq_puts(seq, "isa\t\t: rv64\n");
#else
    dfs_seq_puts(seq, "model name\t: RT-Thread Generic CPU\n");
#endif
    dfs_seq_puts(seq, "\n");

    return 0;
}

static const struct dfs_seq_ops seq_ops = {
    .start  = seq_start,
    .stop   = seq_stop,
    .next   = seq_next,
    .show   = seq_show,
};

rt_weak const struct dfs_seq_ops *cpuinfo_get_seq_ops(void)
{
    return &seq_ops;
}

static int proc_open(struct dfs_file *file)
{
    return dfs_seq_open(file, cpuinfo_get_seq_ops());
}

static int proc_close(struct dfs_file *file)
{
    return dfs_seq_release(file);
}

static const struct dfs_file_ops file_ops = {
    .open   = proc_open,
    .read   = dfs_seq_read,
    .lseek  = dfs_seq_lseek,
    .close  = proc_close,
};

int proc_cpuinfo_init(void)
{
    struct proc_dentry *dentry = proc_create_data("cpuinfo", 0, NULL, &file_ops, NULL);
    proc_release(dentry);

    return 0;
}
INIT_ENV_EXPORT(proc_cpuinfo_init);
