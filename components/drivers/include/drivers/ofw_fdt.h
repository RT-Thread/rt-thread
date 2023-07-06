/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-08-25     GuEe-GUI     first version
 */

#ifndef __OFW_FDT_H__
#define __OFW_FDT_H__

#include <mm_page.h>
#include <drivers/ofw.h>

struct rt_fdt_earlycon
{
    union { rt_ubase_t mmio, port; };
    union { rt_ubase_t size, width; };

    void *fdt;
    long nodeoffset;

    void *data;
    void (*console_putc)(void *data, char c);

#define FDT_EARLYCON_KICK_UPDATE    0
#define FDT_EARLYCON_KICK_COMPLETED 1
    void (*console_kick)(struct rt_fdt_earlycon *earlycon, int why);

    long msg_idx;
    char msg[RT_FDT_EARLYCON_MSG_SIZE * 1024];
};

struct rt_fdt_earlycon_id
{
    char *name;
    char *type;
    char *compatible;
    rt_err_t (*setup)(struct rt_fdt_earlycon *earlycon, const char *options);
};

#define RT_FDT_EARLYCON_OPTION_SIGNATURE    '\n'

#define RT_FDT_EARLYCON_EXPORT(_name, _type, _compatible, _setup)   \
static const struct rt_fdt_earlycon_id __rt_fdt_##_name##_earlycon  \
rt_used RT_OFW_SYMBOL(earlycon, _) =                                \
{                                                                   \
    .name = #_name,                                                 \
    .type = _type,                                                  \
    .compatible = _compatible,                                      \
    .setup = _setup,                                                \
}

const char *rt_fdt_node_name(const char *full_name);
rt_uint64_t rt_fdt_read_number(const fdt32_t *cell, int size);
rt_uint64_t rt_fdt_next_cell(const fdt32_t **cellptr, int size);
rt_uint64_t rt_fdt_translate_address(void *fdt, int nodeoffset, rt_uint64_t address);
rt_bool_t rt_fdt_device_is_available(void *fdt, int nodeoffset);

rt_err_t rt_fdt_commit_memregion_early(rt_region_t *region, rt_bool_t is_reserved);
rt_err_t rt_fdt_commit_memregion_request(rt_region_t **out_region, rt_size_t *out_nr, rt_bool_t is_reserved);

rt_err_t rt_fdt_prefetch(void *fdt);
rt_err_t rt_fdt_scan_root(void);
rt_err_t rt_fdt_scan_memory(void);
rt_err_t rt_fdt_scan_initrd(rt_uint64_t *ranges);
rt_err_t rt_fdt_model_dump(void);
rt_err_t rt_fdt_boot_dump(void);
void rt_fdt_earlycon_output(const char *str);
void rt_fdt_earlycon_kick(int why);
rt_err_t rt_fdt_scan_chosen_stdout(void);
rt_err_t rt_fdt_unflatten(void);

struct rt_ofw_node *rt_fdt_unflatten_single(void *fdt);

#endif /* __OFW_FDT_H__ */
