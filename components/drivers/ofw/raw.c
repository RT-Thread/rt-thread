/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-10-19     GuEe-GUI     first version
 */

#include <drivers/ofw_raw.h>

int fdt_add_subnode_possible(void *fdt, int parentoffset, const char *name)
{
    int nodeoffset;

    if ((nodeoffset = fdt_add_subnode(fdt, parentoffset, name)) < 0)
    {
        fdt_open_into(fdt, fdt, fdt_totalsize(fdt) + FDT_PADDING_SIZE);
        nodeoffset = fdt_add_subnode(fdt, parentoffset, name);
    }

    return nodeoffset;
}

int fdt_add_mem_rsv_possible(void *fdt, size_t addr, size_t size)
{
    int err = 0;

    if (fdt_add_mem_rsv(fdt, addr, size) < 0)
    {
        fdt_open_into(fdt, fdt, fdt_totalsize(fdt) + FDT_PADDING_SIZE);
        err = fdt_add_mem_rsv(fdt, addr, size);
    }

    return err;
}

int fdt_setprop_uxx(void *fdt, int nodeoffset, const char *name, uint64_t val, bool is_u64)
{
    int err;

    if (is_u64)
    {
        err = fdt_setprop_u64(fdt, nodeoffset, name, val);
    }
    else
    {
        err = fdt_setprop_u32(fdt, nodeoffset, name, (uint32_t)val);
    }

    return err;
}

#define FDT_RAW_GET_VAL_FLAG(std_type, s, sz)                   \
int fdt_getprop_##std_type##sz(void *fdt, int nodeoffset,       \
        const char *name, s##int##sz##_t *out_value, int *lenp) \
{                                                               \
    int err = -FDT_ERR_NOTFOUND;                                \
    if (fdt && nodeoffset >= 0 && name && out_value)            \
    {                                                           \
        const fdt##sz##_t *ptr;                                 \
        if ((ptr = fdt_getprop(fdt, nodeoffset, name, lenp)))   \
        {                                                       \
            *out_value = fdt##sz##_to_cpu(*ptr);                \
            err = 0;                                            \
        }                                                       \
    }                                                           \
    return err;                                                 \
}

#define FDT_RAW_GET_VAL(size) \
    FDT_RAW_GET_VAL_FLAG(u, u, size) \
    FDT_RAW_GET_VAL_FLAG(s,  , size)

FDT_RAW_GET_VAL(64)
FDT_RAW_GET_VAL(32)
FDT_RAW_GET_VAL(16)
FDT_RAW_GET_VAL(8)

#undef FDT_RAW_GET_VAL
#undef FDT_RAW_GET_VAL_FLAG

int fdt_io_addr_cells(void *fdt, int nodeoffset)
{
    int cells = -1;
    int parentoffset = fdt_parent_offset(fdt, nodeoffset);

    for (; parentoffset >= 0 ; parentoffset = fdt_parent_offset(fdt, parentoffset))
    {
        const fdt32_t *cells_tmp = fdt_getprop(fdt, parentoffset, "#address-cells", NULL);

        if (cells_tmp)
        {
            cells = fdt32_to_cpu(*cells_tmp);
        }
    }

    if (cells < 0)
    {
        cells = fdt_address_cells(fdt, nodeoffset);
    }

    return cells;
}

int fdt_io_size_cells(void *fdt, int nodeoffset)
{
    int cells = -1;
    int parentoffset = fdt_parent_offset(fdt, nodeoffset);

    for (; parentoffset >= 0 ; parentoffset = fdt_parent_offset(fdt, parentoffset))
    {
        const fdt32_t *cells_tmp = fdt_getprop(fdt, parentoffset, "#size-cells", NULL);

        if (cells_tmp)
        {
            cells = fdt32_to_cpu(*cells_tmp);
        }
    }

    if (cells < 0)
    {
        cells = fdt_size_cells(fdt, nodeoffset);
    }

    return cells;
}

int fdt_install_initrd(void *fdt, char *os_name, size_t initrd_addr, size_t initrd_size)
{
    int err = -FDT_ERR_NOTFOUND;
    int chosen_offset = -1, root_off = fdt_path_offset(fdt, "/");

    if (root_off >= 0)
    {
        chosen_offset = fdt_subnode_offset(fdt, root_off, "chosen");

        if (chosen_offset == -FDT_ERR_NOTFOUND)
        {
            chosen_offset = fdt_add_subnode_possible(fdt, root_off, "chosen");
        }
    }

    if (chosen_offset >= 0)
    {
        uint64_t addr, size;

        err = 0;

        /* Update the entry */
        for (int i = fdt_num_mem_rsv(fdt) - 1; i >= 0; --i)
        {
            fdt_get_mem_rsv(fdt, i, &addr, &size);

            if (addr == initrd_addr)
            {
                fdt_del_mem_rsv(fdt, i);
                break;
            }
        }

        /* Add the memory */
        if (fdt_add_mem_rsv(fdt, initrd_addr, initrd_size) < 0)
        {
            /* Move the memory */
            fdt_open_into(fdt, fdt, fdt_totalsize(fdt) + FDT_PADDING_SIZE);

            if (fdt_add_mem_rsv(fdt, initrd_addr, initrd_size) < 0)
            {
                err = -FDT_ERR_NOSPACE;
            }
        }

        if (!err)
        {
            size_t name_len;
            char initrd_name[64];
            bool is_u64 = (fdt_io_addr_cells(fdt, root_off) == 2);

            if (!os_name)
            {
                os_name = "rt-thread";
            }

            name_len = strlen(initrd_name);

            strncpy(&initrd_name[name_len], ",initrd-start", sizeof(initrd_name) - name_len);
            fdt_setprop_uxx(fdt, chosen_offset, initrd_name, initrd_addr, is_u64);

            strncpy(&initrd_name[name_len], ",initrd-end", sizeof(initrd_name) - name_len);
            fdt_setprop_uxx(fdt, chosen_offset, initrd_name, initrd_addr + initrd_size, is_u64);
        }
    }

    return err;
}
