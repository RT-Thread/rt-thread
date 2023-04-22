/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "libfdt.h"
#include "dtb_node.h"

static struct
{
    const char *ptr;
    const char *end;
    char *cur;
} paths_buf = {NULL, NULL};
static void *current_fdt;

int fdt_exec_status = FDT_RET_GET_OK;

int dtb_node_get_exec_status()
{
    return fdt_exec_status;
}

static int _dtb_node_get_dtb_properties_list(struct dtb_property *dtb_property, off_t node_off)
{
    /* caller alrealy checked current_fdt */
    off_t property_off = fdt_first_property_offset(current_fdt, node_off);
    struct fdt_property *fdt_property;

    if (property_off < 0)
    {
        return FDT_RET_GET_EMPTY;
    }

    for (;;)
    {
        fdt_property = (struct fdt_property *)fdt_get_property_by_offset(current_fdt, property_off, &dtb_property->size);
        if (fdt_property != NULL)
        {
            dtb_property->name = fdt_string(current_fdt, fdt32_to_cpu(fdt_property->nameoff));
            dtb_property->value = fdt_property->data;
            dtb_property->size = fdt32_to_cpu(fdt_property->len);
        }

        property_off = fdt_next_property_offset(current_fdt, property_off);
        if (property_off >= 0)
        {
            dtb_property->next = (struct dtb_property *)malloc(sizeof(struct dtb_property));
            if (dtb_property->next == NULL)
            {
                return FDT_RET_NO_MEMORY;
            }
            dtb_property = dtb_property->next;
        }
        else
        {
            dtb_property->next = NULL;
            break;
        }
    }

    return FDT_RET_GET_OK;
}

static int _dtb_node_get_dtb_nodes_list(struct dtb_node *dtb_node_head, struct dtb_node *dtb_node, const char *pathname)
{
    off_t root_off;
    off_t node_off;
    int pathname_sz;
    int node_name_sz;

    /* caller alrealy checked current_fdt */
    if ((root_off = fdt_path_offset(current_fdt, pathname)) >= 0)
    {
        pathname_sz = strlen(pathname);
        node_off = fdt_first_subnode(current_fdt, root_off);

        if (node_off < 0)
        {
            return FDT_RET_GET_EMPTY;
        }

        for (;;)
        {
            dtb_node->parent = dtb_node_head;
            dtb_node->sibling = NULL;
            dtb_node->name = fdt_get_name(current_fdt, node_off, &node_name_sz);

            /* parent_path + name + '/' + '\0' */
            if (paths_buf.cur + pathname_sz + node_name_sz + 2 < paths_buf.end)
            {
                dtb_node->path = (const char *)paths_buf.cur;
                strncpy(paths_buf.cur, pathname, pathname_sz);
                paths_buf.cur += pathname_sz;
                strncpy(paths_buf.cur, (char *)dtb_node->name, node_name_sz);
                paths_buf.cur += node_name_sz;
                *paths_buf.cur++ = '/';
                *paths_buf.cur++ = '\0';
            }
            else
            {
                dtb_node->path = NULL;
                rt_kprintf("\033[31m\rERROR: `FDT_DTB_ALL_NODES_PATH_SIZE' = %d bytes is configured too low.\033[0m\n", FDT_DTB_ALL_NODES_PATH_SIZE);
                return FDT_RET_NO_MEMORY;
            }

            dtb_node->handle = fdt_get_phandle(current_fdt, node_off);
            dtb_node->properties = (struct dtb_property *)malloc(sizeof(struct dtb_property));
            dtb_node->child = (struct dtb_node *)malloc(sizeof(struct dtb_node));

            if (dtb_node->properties == NULL || dtb_node->child == NULL)
            {
                return FDT_RET_NO_MEMORY;
            }

            fdt_exec_status = _dtb_node_get_dtb_properties_list(dtb_node->properties, node_off);
            if (fdt_exec_status == FDT_RET_GET_EMPTY)
            {
                free(dtb_node->properties);
                dtb_node->properties = NULL;
            }
            else if (fdt_exec_status != FDT_RET_GET_OK)
            {
                return fdt_exec_status;
            }

            fdt_exec_status = _dtb_node_get_dtb_nodes_list(dtb_node, dtb_node->child, dtb_node->path);
            if (fdt_exec_status == FDT_RET_GET_EMPTY)
            {
                free(dtb_node->child);
                dtb_node->child = NULL;
            }
            else if (fdt_exec_status != FDT_RET_GET_OK)
            {
                return fdt_exec_status;
            }

            node_off = fdt_next_subnode(current_fdt, node_off);
            if (node_off >= 0)
            {
                dtb_node->sibling = (struct dtb_node *)malloc(sizeof(struct dtb_node));
                if (dtb_node->sibling == NULL)
                {
                    return FDT_RET_NO_MEMORY;
                }
                dtb_node = dtb_node->sibling;
            }
            else
            {
                break;
            }
        }
    }

    return FDT_RET_GET_OK;
}

struct dtb_node *dtb_node_get_dtb_list(void *fdt)
{
    int root_off;
    struct dtb_node *dtb_node_head = NULL;

    if (fdt == NULL)
    {
        fdt_exec_status = FDT_RET_NO_LOADED;
        goto fail;
    }

    current_fdt = fdt;

    if ((dtb_node_head = (struct dtb_node *)malloc(sizeof(struct dtb_node))) == NULL)
    {
        fdt_exec_status = FDT_RET_NO_MEMORY;
        goto fail;
    }

    if (paths_buf.ptr == NULL)
    {
        paths_buf.ptr = malloc(FDT_DTB_ALL_NODES_PATH_SIZE);
        if (paths_buf.ptr == NULL)
        {
            fdt_exec_status = FDT_RET_NO_MEMORY;
            goto fail;
        }
        paths_buf.cur = (char *)paths_buf.ptr;
        paths_buf.end = (char *)(paths_buf.ptr + FDT_DTB_ALL_NODES_PATH_SIZE);
    }

    root_off = fdt_path_offset(fdt, "/");

    if ((dtb_node_head->header = malloc(sizeof(struct dtb_header))) == NULL)
    {
        fdt_exec_status = FDT_RET_NO_MEMORY;
        goto fail;
    }
    else
    {
        ((struct dtb_header *)dtb_node_head->header)->root = '/';
        ((struct dtb_header *)dtb_node_head->header)->zero = '\0';
        ((struct dtb_header *)dtb_node_head->header)->memreserve_sz = fdt_num_mem_rsv(fdt);

        if (dtb_node_head->header->memreserve_sz > 0)
        {
            int i;
            int memreserve_sz = dtb_node_head->header->memreserve_sz;
            uint32_t off_mem_rsvmap = fdt_off_mem_rsvmap(fdt);
            struct fdt_reserve_entry *rsvmap = (struct fdt_reserve_entry *)((char *)fdt + off_mem_rsvmap);

            ((struct dtb_header *)dtb_node_head->header)->memreserve = malloc(sizeof(struct dtb_memreserve) * memreserve_sz);
            if (dtb_node_head->header->memreserve == NULL)
            {
                fdt_exec_status = FDT_RET_NO_MEMORY;
                goto fail;
            }
            for (i = 0; i < memreserve_sz; ++i)
            {
                ((struct dtb_header *)dtb_node_head->header)->memreserve[i].address = fdt64_to_cpu(rsvmap[i].address);
                ((struct dtb_header *)dtb_node_head->header)->memreserve[i].size = fdt64_to_cpu(rsvmap[i].size);
            }
        }
        else
        {
            ((struct dtb_header *)dtb_node_head->header)->memreserve = NULL;
        }
    }

    dtb_node_head->path = paths_buf.ptr;
    *paths_buf.cur++ = '/';
    *paths_buf.cur++ = '\0';
    dtb_node_head->parent = NULL;
    dtb_node_head->sibling = NULL;

    dtb_node_head->handle = fdt_get_phandle(fdt, root_off);
    dtb_node_head->properties = (struct dtb_property *)malloc(sizeof(struct dtb_property));
    dtb_node_head->child = (struct dtb_node *)malloc(sizeof(struct dtb_node));

    if (dtb_node_head->properties == NULL || dtb_node_head->child == NULL)
    {
        fdt_exec_status = FDT_RET_NO_MEMORY;
        goto fail;
    }

    if ((fdt_exec_status = _dtb_node_get_dtb_properties_list(dtb_node_head->properties, root_off)) != FDT_RET_GET_OK)
    {
        goto fail;
    }

    if ((fdt_exec_status = _dtb_node_get_dtb_nodes_list(dtb_node_head, dtb_node_head->child, dtb_node_head->path)) != FDT_RET_GET_OK)
    {
        goto fail;
    }

    /* paths_buf.ptr addr save in the dtb_node_head's path */
    paths_buf.ptr = NULL;
    paths_buf.cur = NULL;

    return dtb_node_head;

fail:
    if (dtb_node_head != NULL)
    {
        dtb_node_free_dtb_list(dtb_node_head);
    }

    return NULL;
}

static void _dtb_node_free_dtb_node(struct dtb_node *dtb_node)
{
    struct dtb_node *dtb_node_last;
    struct dtb_property *dtb_property;
    struct dtb_property *dtb_property_last;

    while (dtb_node != NULL)
    {
        dtb_property = dtb_node->properties;
        while (dtb_property != NULL)
        {
            dtb_property_last = dtb_property;
            dtb_property = dtb_property->next;
            free(dtb_property_last);
        }

        _dtb_node_free_dtb_node(dtb_node->child);

        dtb_node_last = dtb_node;
        dtb_node = dtb_node->sibling;
        free(dtb_node_last);
    }
}

void dtb_node_free_dtb_list(struct dtb_node *dtb_node_head)
{
    if (dtb_node_head == NULL)
    {
        return;
    }

    /* only root node can free all path buffer */
    if (dtb_node_head->parent == NULL || (dtb_node_head->path != NULL && !strcmp(dtb_node_head->path, "/")))
    {
        if (dtb_node_head->path != NULL)
        {
            free((void *)dtb_node_head->path);
        }
        if (dtb_node_head->header != NULL)
        {
            if (dtb_node_head->header->memreserve != NULL)
            {
                free((void *)dtb_node_head->header->memreserve);
            }
            free((void *)dtb_node_head->header);
        }
    }

    _dtb_node_free_dtb_node(dtb_node_head);
}

static void _dtb_node_printf_depth(int depth)
{
    int i = depth;
    while (i --> 0)
    {
        rt_kputs("\t");
    }
}

rt_bool_t _dtb_node_test_string_list(const void *value, int size)
{
    const char *str = value;
    const char *str_start, *str_end;

    if (size == 0)
    {
        return RT_FALSE;
    }

    /* string end with '\0' */
    if (str[size - 1] != '\0')
    {
        return RT_FALSE;
    }

    /* get string list end */
    str_end = str + size;

    while (str < str_end)
    {
        str_start = str;
        /* before string list end, not '\0' and a printable characters */
        while (str < str_end && *str && ((unsigned char)*str >= ' ' && (unsigned char)*str <= '~'))
        {
            ++str;
        }

        /* not zero, or not increased */
        if (*str != '\0' || str == str_start)
        {
            return RT_FALSE;
        }

        /* next string */
        ++str;
    }

    return RT_TRUE;
}

static void _dtb_node_printf_dtb_node_info(struct dtb_node *dtb_node)
{
    static int depth = 0;
    struct dtb_property *dtb_property;

    while (dtb_node != NULL)
    {
        rt_kputs("\n");
        _dtb_node_printf_depth(depth);
        rt_kputs(dtb_node->name);
        rt_kputs(" {\n");
        ++depth;

        dtb_property = dtb_node->properties;
        while (dtb_property != NULL)
        {
            _dtb_node_printf_depth(depth);

            rt_kputs(dtb_property->name);

            if (dtb_property->size > 0)
            {
                int size = dtb_property->size;
                char *value = dtb_property->value;

                rt_kputs(" = ");
                if (_dtb_node_test_string_list(value, size) == RT_TRUE)
                {
                    /* print string list */
                    char *str = value;
                    do
                    {
                        rt_kprintf("\"%s\"", str);
                        str += strlen(str) + 1;
                        rt_kputs(", ");
                    } while (str < value + size);
                    rt_kputs("\b\b");
                }
                else if ((size % 4) == 0)
                {
                    /* print addr and size cell */
                    int i;
                    fdt32_t *cell = (fdt32_t *)value;

                    rt_kputs("<");
                    for (i = 0, size /= 4; i < size; ++i)
                    {
                        rt_kprintf("0x%x ", fdt32_to_cpu(cell[i]));
                    }
                    rt_kputs("\b>");
                }
                else
                {
                    /* print bytes array */
                    int i;
                    uint8_t *byte = (uint8_t *)value;

                    rt_kputs("[");
                    for (i = 0; i < size; ++i)
                    {
                       rt_kprintf("%02x ", *byte++);
                    }
                    rt_kputs("\b]");
                }
            }
            rt_kputs(";\n");
            dtb_property = dtb_property->next;
        }

        _dtb_node_printf_dtb_node_info(dtb_node->child);
        dtb_node = dtb_node->sibling;

        --depth;
        _dtb_node_printf_depth(depth);
        rt_kputs("};\n");
    }
}

void dtb_node_get_dts_dump(struct dtb_node *dtb_node_head)
{
    if (dtb_node_head != NULL)
    {
        int i = dtb_node_head->header->memreserve_sz;

        rt_kputs("/dts-v1/;\n");
        while (i --> 0)
        {
            rt_kprintf("\n/memreserve/\t0x%lx 0x%zx;", dtb_node_head->header->memreserve[i].address, dtb_node_head->header->memreserve[i].size);
        }

        _dtb_node_printf_dtb_node_info(dtb_node_head);
    }
}

static void _dtb_node_get_enum_dtb_node(struct dtb_node *dtb_node, void (callback(struct dtb_node *dtb_node)))
{
    while (dtb_node != NULL)
    {
        callback(dtb_node);
        _dtb_node_get_enum_dtb_node(dtb_node->child, callback);
        dtb_node = dtb_node->sibling;
    }
}

void dtb_node_get_enum_dtb_node(struct dtb_node *dtb_node_head, void (callback(struct dtb_node *dtb_node)))
{
    if (dtb_node_head == NULL || callback == NULL)
    {
        return;
    }

    _dtb_node_get_enum_dtb_node(dtb_node_head, callback);
}

struct dtb_node *dtb_node_get_dtb_node_by_name_DFS(struct dtb_node *dtb_node, const char *nodename)
{
    struct dtb_node *dtb_node_child;

    while (dtb_node != NULL)
    {
        if (!strcmp(nodename, dtb_node->name))
        {
            return dtb_node;
        }

        dtb_node_child = dtb_node_get_dtb_node_by_name_DFS(dtb_node->child, nodename);

        if (dtb_node_child != NULL)
        {
            return dtb_node_child;
        }
        dtb_node = dtb_node->sibling;
    }

    return NULL;
}

struct dtb_node *dtb_node_get_dtb_node_by_name_BFS(struct dtb_node *dtb_node, const char *nodename)
{
    if (dtb_node != NULL)
    {
        struct dtb_node *dtb_node_child, *dtb_node_head = dtb_node;

        while (dtb_node != NULL)
        {
            if (!strcmp(nodename, dtb_node->name))
            {
                return dtb_node;
            }
            dtb_node = dtb_node->sibling;
        }

        dtb_node = dtb_node_head;

        while (dtb_node != NULL)
        {
            dtb_node_child = dtb_node_get_dtb_node_by_name_BFS(dtb_node->child, nodename);

            if (dtb_node_child != NULL)
            {
                return dtb_node_child;
            }
            dtb_node = dtb_node->sibling;
        }
    }

    return NULL;
}

struct dtb_node *dtb_node_get_dtb_node_by_path(struct dtb_node *dtb_node, const char *pathname)
{
    int i = 0;
    char *node_name;
    char *pathname_clone;
    int pathname_sz;

    if (pathname == NULL || dtb_node == NULL)
    {
        return NULL;
    }

    /* skip '/' */
    if (*pathname == '/')
    {
        ++pathname;
    }

    /* root not have sibling, so skip */
    if (dtb_node->parent == NULL || !strcmp(dtb_node->path, "/"))
    {
        dtb_node = dtb_node->child;
    }

    pathname_sz = strlen(pathname) + 1;
    pathname_clone = malloc(pathname_sz);
    if (pathname_clone == NULL)
    {
        return NULL;
    }
    strncpy(pathname_clone, pathname, pathname_sz);
    node_name = pathname_clone;

    while (pathname_clone[i])
    {
        if (pathname_clone[i] == '/')
        {
            /* set an end of name that can used to strcmp */
            pathname_clone[i] = '\0';

            while (dtb_node != NULL)
            {
                if (!strcmp(dtb_node->name, node_name))
                {
                    break;
                }
                dtb_node = dtb_node->sibling;
            }
            if (dtb_node == NULL)
            {
                free(pathname_clone);
                return NULL;
            }
            dtb_node = dtb_node->child;
            node_name = &pathname_clone[i + 1];
        }
        ++i;
    }

    /*
     *  found the end node and it's name:
     *      (pathname[pathname_sz - 1]) is '\0'
     *      (&pathname_clone[i] - node_name) is the node_name's length
     */
    node_name = &((char *)pathname)[(pathname_sz - 1) - (&pathname_clone[i] - node_name)];
    free(pathname_clone);

    while (dtb_node != NULL)
    {
        if (!strcmp(dtb_node->name, node_name))
        {
            return dtb_node;
        }
        dtb_node = dtb_node->sibling;
    }

    return NULL;
}

struct dtb_node *dtb_node_get_dtb_node_by_phandle_DFS(struct dtb_node *dtb_node, phandle handle)
{
    struct dtb_node *dtb_node_child;

    while (dtb_node != NULL)
    {
        if (dtb_node->handle == handle)
        {
            return dtb_node;
        }

        dtb_node_child = dtb_node_get_dtb_node_by_phandle_DFS(dtb_node->child, handle);

        if (dtb_node_child != NULL)
        {
            return dtb_node_child;
        }
        dtb_node = dtb_node->sibling;
    }

    return NULL;
}

struct dtb_node *dtb_node_get_dtb_node_by_phandle_BFS(struct dtb_node *dtb_node, phandle handle)
{
    if (dtb_node != NULL)
    {
        struct dtb_node *dtb_node_child, *dtb_node_head = dtb_node;

        while (dtb_node != NULL)
        {
            if (dtb_node->handle == handle)
            {
                return dtb_node;
            }
            dtb_node = dtb_node->sibling;
        }

        dtb_node = dtb_node_head;

        while (dtb_node != NULL)
        {
            dtb_node_child = dtb_node_get_dtb_node_by_phandle_BFS(dtb_node->child, handle);

            if (dtb_node_child != NULL)
            {
                return dtb_node_child;
            }
            dtb_node = dtb_node->sibling;
        }
    }

    return NULL;
}

void dtb_node_get_dtb_node_cells(struct dtb_node *dtb_node, int *addr_cells, int *size_cells)
{
    if (dtb_node != NULL && addr_cells != NULL && size_cells != NULL)
    {
        struct dtb_property *dtb_property;
        *addr_cells = -1;
        *size_cells = -1;

        /* if couldn't found, check parent */
        while ((dtb_node = dtb_node->parent) != NULL)
        {
            dtb_property = dtb_node->properties;
            while (dtb_property != NULL)
            {
                if (!strcmp(dtb_property->name, "#address-cells"))
                {
                    *addr_cells = fdt32_to_cpu(*(int *)dtb_property->value);
                }
                else if (!strcmp(dtb_property->name, "#size-cells"))
                {
                    *size_cells = fdt32_to_cpu(*(int *)dtb_property->value);
                }
                if (*addr_cells != -1 && *size_cells != -1)
                {
                    return;
                }
                dtb_property = dtb_property->next;
            }
        }

        if (*addr_cells == -1)
        {
            *addr_cells = FDT_ROOT_ADDR_CELLS_DEFAULT;
        }
        if (*size_cells == -1)
        {
            *size_cells = FDT_ROOT_SIZE_CELLS_DEFAULT;
        }
    }
}

struct dtb_memreserve *dtb_node_get_dtb_memreserve(struct dtb_node *dtb_node, int *memreserve_size)
{
    if (dtb_node != NULL && memreserve_size != NULL)
    {
        struct dtb_node *dtb_node_root = dtb_node;

        while (dtb_node_root != NULL)
        {
            if (!strcmp(dtb_node_root->path, "/"))
            {
                break;
            }
            dtb_node_root = dtb_node_root->parent;
        }
        if(dtb_node_root == NULL) return NULL;

        *memreserve_size = dtb_node_root->header->memreserve_sz;

        return dtb_node_root->header->memreserve;
    }
    return NULL;
}

rt_bool_t dtb_node_get_dtb_node_status(const struct dtb_node *dtb_node)
{
    if (dtb_node != NULL)
    {
        char *status = dtb_node_get_dtb_node_property_value(dtb_node, "status", NULL);
        if (status != NULL)
        {
            return (!strcmp(status, "okay") || !strcmp(status, "ok")) ? RT_TRUE : RT_FALSE;
        }

        return RT_TRUE;
    }

    return RT_FALSE;
}

rt_bool_t dtb_node_get_dtb_node_compatible_match(const struct dtb_node *dtb_node, const char *compatibles)
{
    if (dtb_node != NULL)
    {
        if (compatibles != NULL)
        {
            char *str_ptr;
            int prop_sz;

            for_each_property_string(dtb_node, "compatible", str_ptr, prop_sz)
            {
                if (!strcmp(compatibles, str_ptr))
                {
                    return RT_TRUE;
                }
            }
        }
    }

    return RT_FALSE;
}

char *dtb_node_get_dtb_string_list_value(void *value, int size, int index)
{
    int i = 0;
    char *str = value;

    if (str != NULL)
    {
        do
        {
            if (i++ == index)
            {
                return str;
            }
            str += strlen(str) + 1;
        } while (str < (char *)value + size);
    }

    return NULL;
}

char *dtb_node_get_dtb_string_list_value_next(void *value, void *end)
{
    char *str = value;

    if (str != NULL)
    {
        str += strlen(str) + 1;
        if (str < (char *)end)
        {
            return str;
        }
    }

    return NULL;
}

uint32_t dtb_node_get_dtb_cell_value(void *value)
{
    return fdt32_to_cpu(*(fdt32_t *)value);
}

uint8_t dtb_node_get_dtb_byte_value(void *value)
{
    return *(uint8_t *)value;
}
