/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-08-25     GuEe-GUI     first version
 */

#ifndef __OFW_RAW_H__
#define __OFW_RAW_H__

#include <libfdt/libfdt.h>

#define FDT_SIZE_KB 1024
#define FDT_SIZE_MB (1024 * FDT_SIZE_KB)

#define FDT_SIZE_MAX        (2 * FDT_SIZE_MB)
#define FDT_PADDING_SIZE    (1 * FDT_SIZE_KB)

typedef uint8_t fdt8_t;

static inline uint8_t fdt8_to_cpu(fdt8_t x)
{
    return (uint8_t)x;
}

int fdt_add_subnode_possible(void *fdt, int parentoffset, const char *name);
int fdt_add_mem_rsv_possible(void *fdt, size_t addr, size_t size);

#define fdt_setprop_cstring(fdt, nodeoffset, name, str) \
    fdt_setprop((fdt), (nodeoffset), (name), (str), sizeof(str))

#define fdt_prop_cells_ops(ops, fdt, nodeoffset, prop, ...) \
({                                                          \
    int ret = 0;                                            \
    uint32_t tmp[] = { __VA_ARGS__ };                       \
    for (int i = 0; i < sizeof(tmp) / sizeof(tmp[0]); ++i)  \
    {                                                       \
        tmp[i] = cpu_to_fdt32(tmp[i]);                      \
    }                                                       \
    ret += ops(fdt, nodeoffset, prop, tmp, sizeof(tmp));    \
    ret;                                                    \
})

#define fdt_setprop_cells(fdt, nodeoffset, prop, ...)   \
    fdt_prop_cells_ops(fdt_setprop, fdt, nodeoffset, prop, __VA_ARGS__)

#define fdt_appendprop_cells(fdt, nodeoffset, prop, ...)    \
    fdt_prop_cells_ops(fdt_appendprop, fdt, nodeoffset, prop, __VA_ARGS__)

int fdt_setprop_uxx(void *fdt, int nodeoffset, const char *name, uint64_t val, bool is_u64);
int fdt_getprop_u8(void *fdt, int nodeoffset, const char *name, uint8_t *out_value, int *lenp);
int fdt_getprop_s8(void *fdt, int nodeoffset, const char *name, int8_t *out_value, int *lenp);
int fdt_getprop_u16(void *fdt, int nodeoffset, const char *name, uint16_t *out_value, int *lenp);
int fdt_getprop_s16(void *fdt, int nodeoffset, const char *name, int16_t *out_value, int *lenp);
int fdt_getprop_u32(void *fdt, int nodeoffset, const char *name, uint32_t *out_value, int *lenp);
int fdt_getprop_s32(void *fdt, int nodeoffset, const char *name, int32_t *out_value, int *lenp);

int fdt_io_addr_cells(void *fdt, int nodeoffset);
int fdt_io_size_cells(void *fdt, int nodeoffset);

int fdt_install_initrd(void *fdt, char *os_name, size_t initrd_addr, size_t initrd_size);

#endif /* __OFW_RAW_H__ */
