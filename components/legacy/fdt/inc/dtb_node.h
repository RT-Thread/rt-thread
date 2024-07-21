/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef _DTB_NODE_H__
#define _DTB_NODE_H__

#include "libfdt_env.h"
#include <rtthread.h>
#include <stdint.h>

#ifdef RT_USING_FDT_FWNODE
#include "dtb_fwnode.h"
#endif

//#define RT_DTB_DEBUG
#ifdef RT_DTB_DEBUG
#define debug(fmt, args...) rt_kprintf(fmt, ##args)
#else
#define debug(fmt, args...)
#endif

#define DTB_ERR_PTR(err)    ((void *)((long)(err)))
#define DTB_PTR_ERR(ptr)    ((long)(ptr))
#define DTB_IS_ERR(ptr)     ((unsigned long)(ptr) > (unsigned long)(-1000))

#define DEV_ROOT_NODE_ADDR_CELLS_DEFAULT 2
#define DEV_ROOT_NODE_SIZE_CELLS_DEFAULT 1
/* will be optimized to only u64 or u32 by gcc */
#define IN_64BITS_MODE (sizeof(void *) == 8)

#define FDT_ROOT_ADDR_CELLS_DEFAULT 1
#define FDT_ROOT_SIZE_CELLS_DEFAULT 1

#define FDT_DTB_ALL_NODES_PATH_SIZE (32 * 1024)
#define FDT_DTB_PAD_SIZE 1024

#define FDT_RET_NO_MEMORY 2
#define FDT_RET_NO_LOADED 1
#define FDT_RET_GET_OK 0
#define FDT_RET_GET_EMPTY (-1)

typedef uint32_t phandle;

struct dtb_memreserve
{
    uintptr_t address;
    size_t size;
};

struct dtb_header
{
    char root, zero; /* "/" */
    struct dtb_memreserve *memreserve;
    size_t memreserve_sz;
};

struct dtb_property
{
    const char *name;
    int size;
    void *value;

    struct dtb_property *next;
};

struct dtb_node
{
    union
    {
        const char *name;
        const struct dtb_header *header;
    };
    const char *path;
    phandle handle;
    int level;
#ifdef RT_USING_FDT_FWNODE
    struct fwnode_handle fwnode;
    unsigned long _flags;
#endif
    struct dtb_property *properties;
    struct dtb_node *parent;
    struct dtb_node *child;
    struct dtb_node *sibling;
};

#define FDT_MAX_PHANDLE_ARGS 16

/**
 * struct dtb_node_phandle_args - structure to hold phandle and arguments
 *
 * This is used when decoding a phandle in a device tree property. Typically
 * these look like this:
 *
 * wibble {
 *    phandle = <5>;
 * };
 *
 * ...
 * some-prop = <&wibble 1 2 3>
 *
 * Here &node is the phandle of the node 'wibble', i.e. 5. There are three
 * arguments: 1, 2, 3.
 *
 * So when decoding the phandle in some-prop, np will point to wibble,
 * args_count will be 3 and the three arguments will be in args.
 *
 * @np: Node that the phandle refers to
 * @args_count: Number of arguments
 * @args: Argument values
 */
struct fdt_phandle_args
{
    struct dtb_node *np;
    int args_count;
    uint32_t args[FDT_MAX_PHANDLE_ARGS];
};

/*
 * A single signal can be specified via a range of minimal and maximal values
 * with a typical value, that lies somewhere inbetween.
 */
struct timing_entry
{
    uint32_t min;
    uint32_t typ;
    uint32_t max;
};

void *get_fdt_blob(void);
struct dtb_node *get_dtb_node_head(void);
rt_bool_t dtb_node_active(void);
int device_tree_setup(void *mem_addr);

void *dtb_node_load_from_fs(char *dtb_filename);
void *dtb_node_load_from_memory(void *dtb_ptr, rt_bool_t is_clone);

size_t dtb_node_set_linux_cmdline(void *fdt, char *cmdline);
size_t dtb_node_set_linux_initrd(void *fdt, uint64_t initrd_addr, size_t initrd_size);

size_t dtb_node_set_dtb_property(void *fdt, char *pathname, char *property_name, uint32_t *cells, size_t cells_size);
size_t dtb_node_add_dtb_memreserve(void *fdt, uint64_t address, uint64_t size);
size_t dtb_node_del_dtb_memreserve(void *fdt, uint64_t address);

int dtb_node_get_exec_status();
struct dtb_node *dtb_node_get_dtb_list(void *fdt);
void dtb_node_free_dtb_list(struct dtb_node *dtb_node_head);
void dtb_node_get_dts_dump(struct dtb_node *dtb_node_head);
void dtb_node_get_enum_dtb_node(struct dtb_node *dtb_node_head, void(callback(struct dtb_node *dtb_node)));

struct dtb_node *dtb_node_get_dtb_node_by_name_DFS(struct dtb_node *dtb_node, const char *nodename);
struct dtb_node *dtb_node_get_dtb_node_by_name_BFS(struct dtb_node *dtb_node, const char *nodename);
struct dtb_node *dtb_node_get_dtb_node_by_path(struct dtb_node *dtb_node, const char *pathname);
struct dtb_node *dtb_node_get_dtb_node_by_phandle_DFS(struct dtb_node *dtb_node, phandle handle);
struct dtb_node *dtb_node_get_dtb_node_by_phandle_BFS(struct dtb_node *dtb_node, phandle handle);
void dtb_node_get_dtb_node_cells(struct dtb_node *dtb_node, int *addr_cells, int *size_cells);
struct dtb_memreserve *dtb_node_get_dtb_memreserve(struct dtb_node *dtb_node, int *memreserve_size);
uint8_t dtb_node_get_dtb_byte_value(void *value);

char *dtb_node_get_dtb_string_list_value(void *value, int size, int index);
char *dtb_node_get_dtb_string_list_value_next(void *value, void *end);
uint32_t dtb_node_get_dtb_cell_value(void *value);

rt_bool_t dtb_node_get_dtb_node_status(const struct dtb_node *dtb_node);
rt_bool_t dtb_node_get_dtb_node_compatible_match(const struct dtb_node *dtb_node, const char *compatibles);

/*dtb_node_access.c */
int dtb_node_read_u32(const struct dtb_node *dn, const char *propname, uint32_t *outp);
uint32_t dtb_node_read_u32_default(const struct dtb_node *node, const char *propname, uint32_t def);
int dtb_node_read_u32_index(const struct dtb_node *node, const char *propname, int index,
                           uint32_t *outp);
uint32_t dtb_node_read_u32_index_default(const struct dtb_node *node, const char *propname, int index,
                                        uint32_t def);
int dtb_node_read_u32_array(const struct dtb_node *dn, const char *propname,
                       uint32_t *out_values, size_t sz);
int dtb_node_read_u32_index(const struct dtb_node *dn, const char *propname,
                       int index, uint32_t *outp);
int dtb_node_read_s32_default(const struct dtb_node *node, const char *propname, int32_t def);
int dtb_node_read_u64(const struct dtb_node *dn, const char *propname, uint64_t *outp);
uint64_t dtb_node_read_u64_default(const struct dtb_node *node, const char *propname, uint64_t def);

int dtb_node_n_addr_cells(const struct dtb_node *dn);
int dtb_node_n_size_cells(const struct dtb_node *dn);
int dtb_node_simple_addr_cells(const struct dtb_node *np);
int dtb_node_simple_size_cells(const struct dtb_node *np);

struct dtb_node *dtb_node_find_all_nodes(const struct dtb_node *prev);
struct dtb_node *dtb_node_find_node_by_phandle(phandle handle);
struct dtb_node *dtb_node_find_compatible_node(struct dtb_node *from, const char *compatible);
void *dtb_node_get_dtb_node_property_value(const struct dtb_node *dtb_node, const char *property_name, int *property_size);
struct dtb_property *dtb_node_get_dtb_node_property(const struct dtb_node *dtb_node, const char *property_name, int *property_size);
const struct dtb_node *dtb_node_find_node_by_prop_value(struct dtb_node *from, const char *propname, const void *propval, int proplen);
struct dtb_node *dtb_node_find_node_opts_by_path(const char *path,
                                            const char **opts);

static inline struct dtb_node *dtb_node_find_node_by_path(const char *path)
{
    return dtb_node_find_node_opts_by_path(path, NULL);
}

rt_bool_t dtb_node_device_is_available(const struct dtb_node *device);
struct dtb_node *dtb_node_get_parent(const struct dtb_node *node);
int dtb_node_property_match_string(const struct dtb_node *dn, const char *propname,
                              const char *string);
int dtb_node_property_read_string_helper(const struct dtb_node *dn,
                                    const char *propname, const char **out_strs,
                                    size_t sz, int skip);
/**
 * of_property_read_string_index() - Find and read a string from a multiple
 * strings property.
 * @np:     device node from which the property value is to be read.
 * @propname:   name of the property to be searched.
 * @index:  index of the string in the list of strings
 * @out_string: pointer to null terminated return string, modified only if
 *      return value is 0.
 *
 * Search for a property in a device tree node and retrieve a null
 * terminated string value (pointer to data, not a copy) in the list of strings
 * contained in that property.
 * Returns 0 on success, -EINVAL if the property does not exist, -ENODATA if
 * property does not have a value, and -EILSEQ if the string is not
 * null-terminated within the length of the property data.
 *
 * The out_string pointer is modified only if a valid string can be decoded.
 */
static inline int dtb_node_property_read_string_index(const struct dtb_node *dn,
                                                 const char *propname,
                                                 int index, const char **output)
{
    int rc = dtb_node_property_read_string_helper(dn, propname, output, 1, index);
    return rc < 0 ? rc : 0;
}

/**
 * of_property_count_strings() - Find and return the number of strings from a
 * multiple strings property.
 * @np:     device node from which the property value is to be read.
 * @propname:   name of the property to be searched.
 *
 * Search for a property in a device tree node and retrieve the number of null
 * terminated string contain in it. Returns the number of strings on
 * success, -EINVAL if the property does not exist, -ENODATA if property
 * does not have a value, and -EILSEQ if the string is not null-terminated
 * within the length of the property data.
 */
static inline int dtb_node_property_count_strings(const struct dtb_node *dn,
                                             const char *propname)
{
    return dtb_node_property_read_string_helper(dn, propname, NULL, 0, 0);
}

struct dtb_node *dtb_node_parse_phandle(const struct dtb_node *dn,
                                   const char *phandle_name, int index);
int dtb_node_parse_phandle_with_args(const struct dtb_node *dn,
                                const char *list_name, const char *cells_name,
                                int index, struct fdt_phandle_args *out_args);
int dtb_node_count_phandle_with_args(const struct dtb_node *dn,
                                const char *list_name, const char *cells_name);

/* dtb_node_addr.c */
const uint32_t *dtb_node_get_address(const struct dtb_node *dev, int index,
                                uint64_t *size, unsigned int *flags);

#define dtb_node_string_list(string, ...) ((char *[]){string, ##__VA_ARGS__, NULL})

#define for_each_property_string(node_ptr, property_name, str, size)            \
    for (str = dtb_node_get_dtb_node_property_value(node_ptr, property_name, &size), \
        size += (typeof(size))(size_t)str;                                      \
         str && *str;                                                           \
         str = dtb_node_get_dtb_string_list_value_next((void *)str, (void *)(size_t)size))

#define for_each_property_cell(node_ptr, property_name, value, list, size)       \
    for (list = dtb_node_get_dtb_node_property_value(node_ptr, property_name, &size), \
        value = dtb_node_get_dtb_cell_value(list),                                    \
        size /= sizeof(uint32_t);                                                \
         size > 0;                                                               \
         value = dtb_node_get_dtb_cell_value(++list), --size)

#define for_each_property_byte(node_ptr, property_name, value, list, size)       \
    for (list = dtb_node_get_dtb_node_property_value(node_ptr, property_name, &size), \
        value = dtb_node_get_dtb_byte_value(list);                                    \
         size > 0;                                                               \
         value = dtb_node_get_dtb_byte_value(++list), --size)

#define for_each_node_child(node_ptr)                    \
    for (node_ptr = (node_ptr ? node_ptr->child : NULL); \
         node_ptr != NULL;                               \
         node_ptr = node_ptr->sibling)

#define for_each_node_sibling(node_ptr)                    \
    for (node_ptr = (node_ptr ? node_ptr->sibling : NULL); \
         node_ptr != NULL;                                 \
         node_ptr = node_ptr->sibling)

#define for_each_of_allnodes_from(from, dn) \
    for (dn = dtb_node_find_all_nodes(from); dn; dn = dtb_node_find_all_nodes(dn))

#define for_each_of_all_child_nodes_from(from, dn) \
    for (dn = dtb_node_find_all_nodes(from); dn && (dn->level > from->level); dn = dtb_node_find_all_nodes(dn))

#define for_each_of_allnodes(dn) for_each_of_allnodes_from(NULL, dn)

#define dtb_node_get(x) (x)
static inline void dtb_node_put(const struct dtb_node *np)
{
}

/* Helper to read a big number; size is in cells (not bytes) */
static inline uint64_t dtb_node_read_number(const uint32_t *cell, int size)
{
    uint64_t r = 0;
    while (size--)
        r = (r << 32) | fdt32_to_cpu(*(cell++));
    return r;
}

/**
 * ofnode_valid() - check if an ofnode is valid
 *
 * @return true if the reference contains a valid ofnode, RT_FALSE if it is NULL
 */
static inline rt_bool_t dtb_node_valid(const struct dtb_node *node)
{
    if (dtb_node_active())
        return node != NULL;
    return RT_FALSE;
}

/*dtb_base.c */
rt_bool_t dtb_node_read_bool(const struct dtb_node *node, const char *propname);
const void *dtb_node_read_prop(const struct dtb_node *node, const char *propname, int *sizep);
const char *dtb_node_read_string(const struct dtb_node *node, const char *propname);
const struct dtb_node *dtb_node_find_subnode(const struct dtb_node *node, const char *subnode_name);
int dtb_node_read_u32_array(const struct dtb_node *node, const char *propname,
                           uint32_t *out_values, size_t sz);
struct dtb_node *dtb_node_first_subnode(const struct dtb_node *node);
struct dtb_node *dtb_node_next_subnode(const struct dtb_node *node);
struct dtb_node *dtb_node_get_parent(const struct dtb_node *node);
const char *dtb_node_get_name(const struct dtb_node *node);
struct dtb_node *dtb_node_get_by_phandle(uint32_t phandle);
int dtb_node_read_size(const struct dtb_node *node, const char *propname);
int dtb_node_get_addr_and_size_by_index(const struct dtb_node *node, int index, size_t *addr, size_t *size);
size_t dtb_node_get_addr_index(const struct dtb_node *node, int index);
size_t dtb_node_get_addr(const struct dtb_node *node);
int dtb_node_stringlist_search(const struct dtb_node *node, const char *property,
                              const char *string);
int dtb_node_read_string_index(const struct dtb_node *node, const char *property, int index,
                              const char **outp);
int dtb_node_read_string_count(const struct dtb_node *node, const char *property);
struct dtb_node *dtb_node_path(const char *path);
const char *dtb_node_get_chosen_prop(const char *name);
struct dtb_node *dtb_node_get_chosen_node(const char *name);
const void *dtb_node_get_property(const struct dtb_node *node, const char *propname, int *lenp);
rt_bool_t dtb_node_is_available(const struct dtb_node *node);
size_t dtb_node_get_addr_size(const struct dtb_node *node, const char *property,
                             size_t *sizep);
const uint8_t *dtb_node_read_u8_array_ptr(const struct dtb_node *node, const char *propname, size_t sz);
int dtb_node_find_all_compatible_node(const struct dtb_node *from, const char *compatible, struct dtb_node **node_table, int max_num, int *node_num);
int dtb_node_write_prop(const struct dtb_node *node, const char *propname, int len,
                       const void *value);
int dtb_node_write_string(const struct dtb_node *node, const char *propname, const char *value);
int dtb_node_set_enabled(const struct dtb_node *node, rt_bool_t value);
int dtb_node_irq_get(struct dtb_node *dev, int index);
int dtb_node_irq_get_byname(struct dtb_node *dev, const char *name);
int dtb_node_irq_count(struct dtb_node *dev);

/**
 * dtb_node_for_each_subnode() - iterate over all subnodes of a parent
 *
 * @node:       child node (ofnode, lvalue)
 * @parent:     parent node (ofnode)
 *
 * This is a wrapper around a for loop and is used like so:
 *
 * ofnode node;
 *
 * dtb_node_for_each_subnode(node, parent) {
 *      Use node
 *       ...
 * }
 *
 * Note that this is implemented as a macro and @node is used as
 * iterator in the loop. The parent variable can be a constant or even a
 * literal.
 */
#define dtb_node_for_each_subnode(node, parent) \
    for (node = dtb_node_first_subnode(parent); \
         dtb_node_valid(node);                  \
         node = dtb_node_next_subnode(node))

#ifdef RT_USING_FDT_FWNODE
extern const struct fwnode_operations of_fwnode_ops;
static inline void dtb_fwnode_init(struct dtb_node *node)
{
    fwnode_init(&node->fwnode, &of_fwnode_ops);
}
#endif

#endif /* RT_FDT_H__ */
