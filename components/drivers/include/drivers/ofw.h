/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-08-25     GuEe-GUI     first version
 */

#ifndef __OFW_H__
#define __OFW_H__

#include <rtthread.h>

#include <ref.h>
#include <bitmap.h>

#include <libfdt/libfdt.h>

typedef rt_uint32_t rt_phandle;

struct rt_ofw_prop
{
    const char *name;
    int length;
    void *value;

    struct rt_ofw_prop *next;
};

struct rt_ofw_node
{
    const char *name;
    /* full_name is 'path/tag' or 'path/tag@reg' */
    const char *full_name;
    /* phandles range from 1 to 2^32-2 (0xfffffffe) */
    rt_phandle phandle;

    struct rt_ofw_prop *props;
    struct rt_ofw_node *parent;
    struct rt_ofw_node *child;
    struct rt_ofw_node *sibling;

    struct rt_ref ref;

#define RT_OFW_F_SYSTEM         0   /* node is system node */
#define RT_OFW_F_READLY         1   /* node has driver */
#define RT_OFW_F_PLATFORM       2   /* node is platform device */
#define RT_OFW_F_OVERLAY        3   /* node is from overlay */
    rt_bitmap_t flags;

    /* RT-Thread object prototype */
    void *rt_data;
};

#define RT_OFW_MAX_CELL_ARGS    16

struct rt_ofw_cell_args
{
    void *data;

    int args_count;
    rt_uint32_t args[RT_OFW_MAX_CELL_ARGS];
};

struct rt_ofw_node_id
{
    /* The name string should consist name property (deprecated) */
    char name[32];

    /*
     * The type string should consist device_type property, such as pci, memory
     * serial. Because it's deprecated in <devicetree-basics>, we can use other
     * name (like "ttyS" or "ttyAMA" ...) to config with /chosen.
     */
    char type[32];

    /*
     * The compatible string should consist only of lowercase letters, digits
     * and dashes, and should start with a letter. A single comma is typically
     * only used following a vendor prefix. Underscores should not be used.
     */
    char compatible[128];

    const void *data;
};

struct rt_ofw_stub
{
    const struct rt_ofw_node_id *ids;
    rt_err_t (*handler)(struct rt_ofw_node *np, const struct rt_ofw_node_id *id);
};

#define RT_OFW_SYMBOL(_class, _level) \
    rt_section(".rt_ofw_data." #_class "." #_level)

#define RT_OFW_SYMBOL_TYPE_RANGE(_class, _type, _start, _end) \
static const rt_used RT_OFW_SYMBOL(_class, 0) _type _start; \
static const rt_used RT_OFW_SYMBOL(_class, end) _type _end; \

#define RT_OFW_STUB_EXPORT(_name, _ids, _class, _handler, ...) \
static const struct rt_ofw_stub __rt_ofw_##_name    \
rt_used RT_OFW_SYMBOL(_class, __VA_ARGS__ _) =      \
{                                                   \
    .ids = _ids,                                    \
    .handler = _handler,                            \
}

#define RT_OFW_STUB_RANGE_EXPORT(_class, _start, _end) \
    RT_OFW_SYMBOL_TYPE_RANGE(_class, struct rt_ofw_stub, _start = {}, _end = {})

#define rt_ofw_data(np)  ((struct rt_ofw_node *)np)->rt_data

rt_inline rt_bool_t rt_ofw_node_test_flag(const struct rt_ofw_node *np, int flag)
{
    return rt_bitmap_test_bit((rt_bitmap_t *)&np->flags, flag);
}

rt_inline void rt_ofw_node_set_flag(struct rt_ofw_node *np, int flag)
{
    rt_bitmap_set_bit(&np->flags, flag);
}

rt_inline rt_bool_t rt_ofw_node_test_and_set_flag(struct rt_ofw_node *np, int flag)
{
    rt_bool_t res = rt_ofw_node_test_flag(np, flag);

    rt_ofw_node_set_flag(np, flag);

    return res;
}

rt_inline void rt_ofw_node_clear_flag(struct rt_ofw_node *np, int flag)
{
    rt_bitmap_clear_bit(&np->flags, flag);
}

rt_err_t rt_ofw_node_destroy(struct rt_ofw_node *np);

struct rt_ofw_node *rt_ofw_node_get(struct rt_ofw_node *np);
void rt_ofw_node_put(struct rt_ofw_node *np);

rt_bool_t rt_ofw_node_tag_equ(const struct rt_ofw_node *np, const char *tag);
rt_bool_t rt_ofw_node_tag_prefix(const struct rt_ofw_node *np, const char *prefix);

rt_inline const char *rt_ofw_node_name(const struct rt_ofw_node *np)
{
    return np ? np->name : "<no-node>";
}

rt_inline const char *rt_ofw_node_full_name(const struct rt_ofw_node *np)
{
    return np ? np->full_name : "<no-node>";
}

rt_bool_t rt_ofw_machine_is_compatible(const char *compatible);
rt_bool_t rt_ofw_node_is_available(const struct rt_ofw_node *np);
rt_bool_t rt_ofw_node_is_compatible(const struct rt_ofw_node *np, const char *compatible);

struct rt_ofw_node_id *rt_ofw_prop_match(struct rt_ofw_prop *prop, const struct rt_ofw_node_id *ids);
struct rt_ofw_node_id *rt_ofw_node_match(struct rt_ofw_node *np, const struct rt_ofw_node_id *ids);

struct rt_ofw_node *rt_ofw_find_node_by_tag(struct rt_ofw_node *from, const char *tag);
struct rt_ofw_node *rt_ofw_find_node_by_prop_r(struct rt_ofw_node *from, const char *propname,
        const struct rt_ofw_prop **out_prop);

rt_inline struct rt_ofw_node *rt_ofw_find_node_by_prop(struct rt_ofw_node *from, const char *propname)
{
    return rt_ofw_find_node_by_prop_r(from, propname, RT_NULL);
}

struct rt_ofw_node *rt_ofw_find_node_by_name(struct rt_ofw_node *from, const char *name);
struct rt_ofw_node *rt_ofw_find_node_by_type(struct rt_ofw_node *from, const char *type);
struct rt_ofw_node *rt_ofw_find_node_by_compatible(struct rt_ofw_node *from, const char *compatible);
struct rt_ofw_node *rt_ofw_find_node_by_ids_r(struct rt_ofw_node *from, const struct rt_ofw_node_id *ids,
        const struct rt_ofw_node_id **out_id);
struct rt_ofw_node *rt_ofw_find_node_by_path(const char *path);
struct rt_ofw_node *rt_ofw_find_node_by_phandle(rt_phandle phandle);

rt_inline struct rt_ofw_node *rt_ofw_find_node_by_ids(struct rt_ofw_node *from, const struct rt_ofw_node_id *ids)
{
    return rt_ofw_find_node_by_ids_r(from, ids, RT_NULL);
}

struct rt_ofw_node *rt_ofw_get_parent(const struct rt_ofw_node *np);
struct rt_ofw_node *rt_ofw_get_child_by_tag(const struct rt_ofw_node *parent, const char *tag);
struct rt_ofw_node *rt_ofw_get_child_by_compatible(const struct rt_ofw_node *parent, const char *compatible);

int rt_ofw_get_child_count(const struct rt_ofw_node *np);
int rt_ofw_get_available_child_count(const struct rt_ofw_node *np);

struct rt_ofw_node *rt_ofw_get_next_node(struct rt_ofw_node *prev);
struct rt_ofw_node *rt_ofw_get_next_parent(struct rt_ofw_node *prev);
struct rt_ofw_node *rt_ofw_get_next_child(const struct rt_ofw_node *parent, struct rt_ofw_node *prev);
struct rt_ofw_node *rt_ofw_get_next_available_child(const struct rt_ofw_node *parent, struct rt_ofw_node *prev);

struct rt_ofw_node *rt_ofw_get_cpu_node(int cpu, int *thread, rt_bool_t (*match_cpu_hwid)(int cpu, rt_uint64_t hwid));
struct rt_ofw_node *rt_ofw_get_next_cpu_node(struct rt_ofw_node *prev);
struct rt_ofw_node *rt_ofw_get_cpu_state_node(struct rt_ofw_node *cpu_np, int index);
rt_uint64_t rt_ofw_get_cpu_id(struct rt_ofw_node *cpu_np);
rt_uint64_t rt_ofw_get_cpu_hwid(struct rt_ofw_node *cpu_np, unsigned int thread);

struct rt_ofw_node *rt_ofw_get_alias_node(const char *tag, int id);
int rt_ofw_get_alias_id(struct rt_ofw_node *np, const char *tag);
int rt_ofw_get_alias_last_id(const char *tag);

struct rt_ofw_node *rt_ofw_append_child(struct rt_ofw_node *parent, const char *full_name);
rt_err_t rt_ofw_append_prop(struct rt_ofw_node *np, const char *name, int length, void *value);

struct rt_ofw_node *rt_ofw_parse_phandle(const struct rt_ofw_node *np, const char *phandle_name, int index);
rt_err_t rt_ofw_parse_phandle_cells(const struct rt_ofw_node *np, const char *list_name, const char *cells_name,
        int index, struct rt_ofw_cell_args *out_args);
int rt_ofw_count_phandle_cells(const struct rt_ofw_node *np, const char *list_name, const char *cells_name);

const char *rt_ofw_get_prop_fuzzy_name(const struct rt_ofw_node *np, const char *name);
struct rt_ofw_prop *rt_ofw_get_prop(const struct rt_ofw_node *np, const char *name, rt_ssize_t *out_length);

rt_inline const void *rt_ofw_prop_read_raw(const struct rt_ofw_node *np, const char *name, rt_ssize_t *out_length)
{
    struct rt_ofw_prop *prop = rt_ofw_get_prop(np, name, out_length);

    return prop ? prop->value : RT_NULL;
}

int rt_ofw_prop_read_u8_array_index(const struct rt_ofw_node *np, const char *propname,
        int index, int nr, rt_uint8_t *out_values);
int rt_ofw_prop_read_u16_array_index(const struct rt_ofw_node *np, const char *propname,
        int index, int nr, rt_uint16_t *out_values);
int rt_ofw_prop_read_u32_array_index(const struct rt_ofw_node *np, const char *propname,
        int index, int nr, rt_uint32_t *out_values);
int rt_ofw_prop_read_u64_array_index(const struct rt_ofw_node *np, const char *propname,
        int index, int nr, rt_uint64_t *out_values);
int rt_ofw_prop_read_string_array_index(const struct rt_ofw_node *np, const char *propname,
        int index, int nr, const char **out_strings);

int rt_ofw_prop_count_of_size(const struct rt_ofw_node *np, const char *propname, int size);
int rt_ofw_prop_index_of_string(const struct rt_ofw_node *np, const char *propname, const char *string);

const fdt32_t *rt_ofw_prop_next_u32(struct rt_ofw_prop *prop, const fdt32_t *cur, rt_uint32_t *out_value);
const char *rt_ofw_prop_next_string(struct rt_ofw_prop *prop, const char *cur);

rt_inline rt_err_t rt_ofw_prop_read_u8_index(const struct rt_ofw_node *np, const char *propname,
        int index, rt_uint8_t *out_value)
{
    int nr = rt_ofw_prop_read_u8_array_index(np, propname, index, 1, out_value);

    return nr > 0 ? RT_EOK : (rt_err_t)nr;
}

rt_inline rt_err_t rt_ofw_prop_read_u16_index(const struct rt_ofw_node *np, const char *propname,
        int index, rt_uint16_t *out_value)
{
    int nr = rt_ofw_prop_read_u16_array_index(np, propname, index, 1, out_value);

    return nr > 0 ? RT_EOK : (rt_err_t)nr;
}

rt_inline rt_err_t rt_ofw_prop_read_u32_index(const struct rt_ofw_node *np, const char *propname,
        int index, rt_uint32_t *out_value)
{
    int nr = rt_ofw_prop_read_u32_array_index(np, propname, index, 1, out_value);

    return nr > 0 ? RT_EOK : (rt_err_t)nr;
}

rt_inline rt_err_t rt_ofw_prop_read_u64_index(const struct rt_ofw_node *np, const char *propname,
        int index, rt_uint64_t *out_value)
{
    int nr = rt_ofw_prop_read_u64_array_index(np, propname, index, 1, out_value);

    return nr > 0 ? RT_EOK : (rt_err_t)nr;
}

rt_inline rt_err_t rt_ofw_prop_read_string_index(const struct rt_ofw_node *np, const char *propname,
        int index, const char **out_string)
{
    int nr = rt_ofw_prop_read_string_array_index(np, propname, index, 1, out_string);

    return nr > 0 ? RT_EOK : (rt_err_t)nr;
}

rt_inline rt_err_t rt_ofw_prop_read_u8(const struct rt_ofw_node *np, const char *propname,
        rt_uint8_t *out_value)
{
    return rt_ofw_prop_read_u8_index(np, propname, 0, out_value);
}

rt_inline rt_err_t rt_ofw_prop_read_u16(const struct rt_ofw_node *np, const char *propname,
        rt_uint16_t *out_value)
{
    return rt_ofw_prop_read_u16_index(np, propname, 0, out_value);
}

rt_inline rt_err_t rt_ofw_prop_read_u32(const struct rt_ofw_node *np, const char *propname,
        rt_uint32_t *out_value)
{
    return rt_ofw_prop_read_u32_index(np, propname, 0, out_value);
}

rt_inline rt_err_t rt_ofw_prop_read_s32(const struct rt_ofw_node *np, const char *propname,
        rt_int32_t *out_value)
{
    return rt_ofw_prop_read_u32_index(np, propname, 0, (rt_uint32_t *)out_value);
}

rt_inline rt_err_t rt_ofw_prop_read_u64(const struct rt_ofw_node *np, const char *propname,
        rt_uint64_t *out_value)
{
    return rt_ofw_prop_read_u64_index(np, propname, 0, out_value);
}

rt_inline rt_err_t rt_ofw_prop_read_string(const struct rt_ofw_node *np, const char *propname,
        const char **out_string)
{
    return rt_ofw_prop_read_string_index(np, propname, 0, out_string);
}

rt_inline rt_bool_t rt_ofw_prop_read_bool(const struct rt_ofw_node *np, const char *propname)
{
    return rt_ofw_get_prop(np, propname, RT_NULL) ? RT_TRUE : RT_FALSE;
}

rt_inline int rt_ofw_prop_count_of_u8(const struct rt_ofw_node *np, const char *propname)
{
    return rt_ofw_prop_count_of_size(np, propname, sizeof(rt_uint8_t));
}

rt_inline int rt_ofw_prop_count_of_u16(const struct rt_ofw_node *np, const char *propname)
{
    return rt_ofw_prop_count_of_size(np, propname, sizeof(rt_uint16_t));
}

rt_inline int rt_ofw_prop_count_of_u32(const struct rt_ofw_node *np, const char *propname)
{
    return rt_ofw_prop_count_of_size(np, propname, sizeof(rt_uint32_t));
}

rt_inline int rt_ofw_prop_count_of_u64(const struct rt_ofw_node *np, const char *propname)
{
    return rt_ofw_prop_count_of_size(np, propname, sizeof(rt_uint64_t));
}

rt_inline const char *rt_ofw_node_type(const struct rt_ofw_node *np)
{
    return rt_ofw_prop_read_raw(np, "device_type", RT_NULL);
}

rt_inline rt_bool_t rt_ofw_node_is_type(const struct rt_ofw_node *np, const char *type)
{
    const char *get_type = rt_ofw_node_type(np);

    return np && get_type && type && !rt_strcmp(get_type, type);
}

#define rt_ofw_foreach_node_by_tag(np, name)                \
    for (np = rt_ofw_find_node_by_tag(RT_NULL, name); np;   \
         np = rt_ofw_find_node_by_tag(np, name))

#define rt_ofw_foreach_node_by_prop(np, prop_name)          \
    for (np = rt_ofw_find_node_by_prop(RT_NULL, prop_name); \
        np; np = rt_ofw_find_node_by_prop(np, prop_name))

#define rt_ofw_foreach_node_by_prop_r(np, prop_name, prop)          \
    for (np = rt_ofw_find_node_by_prop_r(RT_NULL, prop_name, prop); \
        np; np = rt_ofw_find_node_by_prop_r(np, prop_name, prop))

#define rt_ofw_foreach_node_by_name(np, name)               \
    for (np = rt_ofw_find_node_by_name(RT_NULL, name); np;  \
         np = rt_ofw_find_node_by_name(np, name))

#define rt_ofw_foreach_node_by_type(np, type)               \
    for (np = rt_ofw_find_node_by_type(RT_NULL, type); np;  \
         np = rt_ofw_find_node_by_type(np, type))

#define rt_ofw_foreach_node_by_compatible(np, type, compatible)                 \
    for (np = rt_ofw_find_node_by_compatible(RT_NULL, type, compatible); np;    \
         np = rt_ofw_find_node_by_compatible(np, type, compatible))

#define rt_ofw_foreach_node_by_ids_r(np, id, ids)           \
    for (np = rt_ofw_find_node_by_ids_r(RT_NULL, ids, id);  \
        np; np = rt_ofw_find_node_by_ids_r(np, ids, id))

#define rt_ofw_foreach_node_by_ids(np, ids)                 \
    for (np = rt_ofw_find_node_by_ids(RT_NULL, ids); np;    \
         np = rt_ofw_find_node_by_ids(np, ids))

#define rt_ofw_foreach_nodes(from, np)      \
    for (np = rt_ofw_get_next_node(from);   \
        np; np = rt_ofw_get_next_node(np))

#define rt_ofw_foreach_allnodes(np) \
    rt_ofw_foreach_nodes(RT_NULL, np)

#define rt_ofw_foreach_parent_node(np)                      \
    for (np = rt_ofw_get_next_parent(rt_ofw_node_get(np));  \
        np; np = rt_ofw_get_next_parent(np))

#define rt_ofw_foreach_child_node(parent, child)            \
    for (child = rt_ofw_get_next_child(parent, RT_NULL);    \
        child; child = rt_ofw_get_next_child(parent, child))

#define rt_ofw_foreach_available_child_node(parent, child)                  \
    for (child = rt_ofw_get_next_available_child(parent, RT_NULL); child;   \
         child = rt_ofw_get_next_available_child(parent, child))

#define rt_ofw_foreach_cpu_node(cpu_np)                     \
    for (cpu_np = rt_ofw_get_next_cpu_node(RT_NULL);        \
        cpu_np; cpu_np = rt_ofw_get_next_cpu_node(cpu_np))

#define rt_ofw_foreach_prop(np, prop)   \
    for (prop = np->props; prop; prop = prop->next)

#define rt_ofw_foreach_prop_u32(np, propname, prop, p, u)   \
    for (prop = rt_ofw_get_prop(np, propname, RT_NULL),     \
        p = rt_ofw_prop_next_u32(prop, RT_NULL, &u); p;     \
        p = rt_ofw_prop_next_u32(prop, p, &u))

#define rt_ofw_foreach_prop_string(np, propname, prop, s)   \
    for (prop = rt_ofw_get_prop(np, propname, RT_NULL),     \
        s = rt_ofw_prop_next_string(prop, RT_NULL); s;      \
        s = rt_ofw_prop_next_string(prop, s))

#define rt_ofw_foreach_stub(stub, stub_start, stub_end) \
    for (stub = stub_start; stub <= stub_end; ++stub)

struct rt_ofw_stub *rt_ofw_stub_probe_range(struct rt_ofw_node *np,
        const struct rt_ofw_stub *stub_start, const struct rt_ofw_stub *stub_end);

rt_err_t rt_ofw_console_setup(void);
const char *rt_ofw_bootargs_select(const char *key, int index);

#ifdef RT_USING_CONSOLE
void rt_ofw_node_dump_dts(struct rt_ofw_node *np, rt_bool_t sibling_too);
#endif

#endif /* __OFW_H__ */
