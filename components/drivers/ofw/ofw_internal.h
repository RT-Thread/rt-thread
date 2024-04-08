/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-08-25     GuEe-GUI     first version
 */

#ifndef __OFW_INTERNAL_H__
#define __OFW_INTERNAL_H__

#include <rtthread.h>
#include <posix/string.h>
#include <drivers/ofw.h>

#define OFW_PHANDLE_MIN     1
#define OFW_PHANDLE_MAX     FDT_MAX_PHANDLE

#define OFW_NODE_MAX_DEPTH  64
#define OFW_NODE_MIN_HASH   128

#define OFW_ROOT_NODE_ADDR_CELLS_DEFAULT    1
#define OFW_ROOT_NODE_SIZE_CELLS_DEFAULT    1
struct fdt_info
{
    /* Always "/", because we save "ofw" information in root node. */
    char name[sizeof("/")];

    /* Information start */
    void *fdt;

    /* Only root can use */
    struct fdt_reserve_entry *rsvmap;
    rt_size_t rsvmap_nr;
};

struct alias_info
{
    rt_list_t list;

    int id;
    const char *tag;
    rt_size_t tag_len;

    struct rt_ofw_node *np;
};

struct bus_ranges
{
    rt_size_t nr;

    rt_uint64_t *child_addr;
    rt_uint64_t *parent_addr;
    rt_uint64_t *child_size;
};

extern struct rt_ofw_node *ofw_node_root;
extern struct rt_ofw_node *ofw_node_cpus;
extern struct rt_ofw_node *ofw_node_chosen;
extern struct rt_ofw_node *ofw_node_aliases;
extern struct rt_ofw_node *ofw_node_reserved_memory;

extern struct rt_fdt_earlycon fdt_earlycon;

#define ofw_static_cast(to_type, value) \
    (to_type)(((value) >> ((sizeof(value) - sizeof(to_type)) * 8)))

rt_err_t ofw_alias_scan(void);
int ofw_alias_node_id(struct rt_ofw_node *np);
rt_err_t ofw_phandle_hash_reset(rt_phandle min, rt_phandle max);

#endif /* __OFW_INTERNAL_H__ */
