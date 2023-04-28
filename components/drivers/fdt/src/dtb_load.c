/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "libfdt.h"
#include <stdio.h>
#include <unistd.h>
#include "dtb_node.h"

extern int fdt_exec_status;

rt_bool_t dtb_node_check(void *fdt)
{
    return fdt_check_header(fdt) == 0 ? RT_TRUE : RT_FALSE;
}

void *dtb_node_load_from_fs(char *dtb_filename)
{
    void *fdt = NULL;
    size_t dtb_sz;
    int fd = -1;

    if (dtb_filename == NULL)
    {
        fdt_exec_status = FDT_RET_GET_EMPTY;
        goto end;
    }

    fd = open(dtb_filename, O_RDONLY, 0);

    if (fd == -1)
    {
        rt_kprintf("File `%s' not found.\n", dtb_filename);
        fdt_exec_status = FDT_RET_GET_EMPTY;
        goto end;
    }

    dtb_sz = lseek(fd, 0, SEEK_END);

    if (dtb_sz > 0)
    {
        if ((fdt = (struct fdt_header *)malloc(sizeof(uint8_t) * dtb_sz)) == NULL)
        {
            fdt_exec_status = FDT_RET_NO_MEMORY;
            goto end;
        }

        lseek(fd, 0, SEEK_SET);
        read(fd, fdt, sizeof(uint8_t) * dtb_sz);

        if (dtb_node_check(fdt) == RT_FALSE)
        {
            free(fdt);
            fdt=NULL;
        }
    }

end:
    if (fd != -1)
    {
        close(fd);
    }

    return fdt;
}

void *dtb_node_load_from_memory(void *dtb_ptr, rt_bool_t is_clone)
{
    void *fdt = NULL;

    if (dtb_ptr == NULL)
    {
        fdt_exec_status = FDT_RET_GET_EMPTY;
        goto end;
    }

    if (dtb_node_check(dtb_ptr) == RT_FALSE)
    {
        fdt_exec_status = FDT_RET_GET_EMPTY;
        fdt = NULL;
        goto end;
    }

    if (is_clone)
    {
        size_t dtb_sz = fdt_totalsize(dtb_ptr);
        if (dtb_sz > 0)
        {
            if ((fdt = (size_t *)malloc(dtb_sz)) != NULL)
            {
                memcpy(fdt, dtb_ptr, dtb_sz);
            }
            else
            {
                fdt_exec_status = FDT_RET_NO_MEMORY;
            }
        }
    }
    else
    {
        fdt = dtb_ptr;
    }

end:
    return fdt;
}
