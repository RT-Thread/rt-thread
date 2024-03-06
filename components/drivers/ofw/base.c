/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-08-25     GuEe-GUI     first version
 */

#include <rthw.h>
#include <rtthread.h>

#include <drivers/ofw.h>
#include <drivers/ofw_io.h>
#include <drivers/ofw_fdt.h>
#include <drivers/ofw_raw.h>

#define DBG_TAG "rtdm.ofw"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "ofw_internal.h"

struct rt_ofw_node *ofw_node_root = RT_NULL;
struct rt_ofw_node *ofw_node_cpus = RT_NULL;
struct rt_ofw_node *ofw_node_chosen = RT_NULL;
struct rt_ofw_node *ofw_node_aliases = RT_NULL;
struct rt_ofw_node *ofw_node_reserved_memory = RT_NULL;

static rt_phandle _phandle_range[2] = { 1, 1 }, _phandle_next = 1;
static struct rt_ofw_node **_phandle_hash = RT_NULL;

static rt_list_t _aliases_nodes = RT_LIST_OBJECT_INIT(_aliases_nodes);

rt_err_t ofw_phandle_hash_reset(rt_phandle min, rt_phandle max)
{
    rt_err_t err = RT_EOK;
    rt_phandle next = max;
    struct rt_ofw_node **hash_ptr = RT_NULL;

    max = RT_ALIGN(max, OFW_NODE_MIN_HASH);

    if (max > _phandle_range[1])
    {
        rt_size_t size = sizeof(*_phandle_hash) * (max - min);

        if (!_phandle_hash)
        {
            hash_ptr = rt_calloc(1, size);
        }
        else
        {
            hash_ptr = rt_realloc(_phandle_hash, size);

            if (hash_ptr)
            {
                rt_size_t old_max = _phandle_range[1];

                rt_memset(&hash_ptr[old_max], 0, sizeof(_phandle_hash) * (max - old_max));
            }
        }
    }

    if (hash_ptr)
    {
        /* We always reset min value only once */
        if (min)
        {
            _phandle_range[0] = min;
        }
        _phandle_range[1] = max;
        _phandle_next = next + 1;
        _phandle_hash = hash_ptr;
    }
    else
    {
        err = -RT_ENOMEM;
    }

    return err;
}

static rt_phandle ofw_phandle_next(void)
{
    rt_phandle next;
    static struct rt_spinlock op_lock = {};

    rt_hw_spin_lock(&op_lock.lock);

    RT_ASSERT(_phandle_next != OFW_PHANDLE_MAX);

    if (_phandle_next <= _phandle_range[1])
    {
        next = _phandle_next++;
    }
    else
    {
        rt_err_t err = ofw_phandle_hash_reset(_phandle_range[0], _phandle_next);

        if (!err)
        {
            next = _phandle_next++;
        }
        else
        {
            next = 0;
            LOG_E("Expanded phandle hash[%u, %u] fail error = %s",
                    _phandle_range[0], _phandle_next + 1, rt_strerror(err));
        }
    }

    rt_hw_spin_unlock(&op_lock.lock);

    return next;
}
static void ofw_prop_destroy(struct rt_ofw_prop *prop)
{
    struct rt_ofw_prop *next;

    while (prop)
    {
        next = prop->next;

        rt_free(prop);

        prop = next;
    }
}

static struct rt_ofw_node *ofw_get_next_node(struct rt_ofw_node *prev)
{
    struct rt_ofw_node *np;

    /*
     * Walk:
     *
     *    / { ------------------------ [0] (START) has child, goto child.
     *
     *        node0 { ---------------- [1] has child, goto child.
     *
     *            node0_0 { ---------- [2] no child, has sibling, goto sibling.
     *            };
     *
     *            node0_1 { ---------- [3] no sibling now.
     *                                     upward while the parent has sibling.
     *            };
     *        };
     *
     *        node1 { ---------------- [4] come from node0 who find the sibling:
     *                                     node1, node1 has child, goto child.
     *
     *            node1_0 { ---------- [5] has child, goto child.
     *
     *                node1_0_0 { ---- [6] no sibling now.
     *                                     upward while the parent has sibling.
     *                                     (END) in the root.
     *                };
     *            };
     *        };
     *    };
     */

    if (!prev)
    {
        np = ofw_node_root;
    }
    else if (prev->child)
    {
        np = prev->child;
    }
    else
    {
        np = prev;

        while (np->parent && !np->sibling)
        {
            np = np->parent;
        }

        np = np->sibling;
    }

    return np;
}

static void ofw_node_destroy(struct rt_ofw_node *np)
{
    struct rt_ofw_node *prev;

    if (np->parent)
    {
        /* Ask parent and prev sibling we are destroy. */
        prev = np->parent->child;

        if (prev == np)
        {
            np->parent->child = RT_NULL;
        }
        else
        {
            while (prev->sibling != np)
            {
                prev = prev->sibling;
            }

            prev->sibling = np->sibling;
        }
    }

    while (np)
    {
        if (rt_ofw_node_test_flag(np, RT_OFW_F_SYSTEM) == RT_FALSE)
        {
            LOG_E("%s is system node", np->full_name);
            RT_ASSERT(0);
        }

        prev = np;

        np = ofw_get_next_node(np);

        ofw_prop_destroy(prev->props);
        rt_free(prev);
    }
}

rt_err_t rt_ofw_node_destroy(struct rt_ofw_node *np)
{
    rt_err_t err = RT_EOK;

    if (np)
    {
        if (rt_ref_read(&np->ref) <= 1)
        {
            ofw_node_destroy(np);
        }
        else
        {
            err = -RT_EBUSY;
        }
    }
    else
    {
        err = -RT_EINVAL;
    }

    return err;
}

struct rt_ofw_node *rt_ofw_node_get(struct rt_ofw_node *np)
{
    if (np)
    {
        LOG_D("%s get ref = %d", np->full_name, rt_ref_read(&np->ref));
        rt_ref_get(&np->ref);
    }

    return np;
}

static void ofw_node_release(struct rt_ref *r)
{
    struct rt_ofw_node *np = rt_container_of(r, struct rt_ofw_node, ref);

    LOG_E("%s is release", np->full_name);
    (void)np;

    RT_ASSERT(0);
}

void rt_ofw_node_put(struct rt_ofw_node *np)
{
    if (np)
    {
        LOG_D("%s put ref = %d", np->full_name, rt_ref_read(&np->ref));
        rt_ref_put(&np->ref, &ofw_node_release);
    }
}

rt_bool_t rt_ofw_node_tag_equ(const struct rt_ofw_node *np, const char *tag)
{
    rt_bool_t ret = RT_FALSE;

    if (np && tag)
    {
        const char *node_name = rt_fdt_node_name(np->full_name);
        rt_size_t tag_len = strchrnul(node_name, '@') - node_name;

        ret = (rt_strlen(tag) == tag_len && !rt_strncmp(node_name, tag, tag_len));
    }

    return ret;
}

rt_bool_t rt_ofw_node_tag_prefix(const struct rt_ofw_node *np, const char *prefix)
{
    rt_bool_t ret = RT_FALSE;

    if (np && prefix)
    {
        ret = !rt_strncmp(rt_fdt_node_name(np->full_name), prefix, rt_strlen(prefix));
    }

    return ret;
}

static int ofw_prop_index_of_string(struct rt_ofw_prop *prop, const char *string,
        rt_int32_t (*cmp)(const char *cs, const char *ct))
{
    int index = -1;
    rt_size_t len = prop->length, slen = 0;
    const char *value = prop->value;

    for (int idx = 0; len > 0; ++idx)
    {
        /* Add '\0' */
        slen = rt_strlen(value) + 1;

        if (!cmp(value, string))
        {
            index = idx;

            break;
        }

        len -= slen;
        value += slen;
    }

    return index;
}

static rt_int32_t ofw_strcasecmp(const char *cs, const char *ct)
{
    extern rt_int32_t strcasecmp(const char *cs, const char *ct);

    return rt_strcasecmp(cs, ct);
}

static int ofw_prop_index_of_compatible(struct rt_ofw_prop *prop, const char *compatible)
{
    return ofw_prop_index_of_string(prop, compatible, ofw_strcasecmp);
}

static int ofw_node_index_of_compatible(const struct rt_ofw_node *np, const char *compatible)
{
    int idx = -1;
    struct rt_ofw_prop *prop = rt_ofw_get_prop(np, "compatible", RT_NULL);

    if (prop)
    {
        idx = ofw_prop_index_of_compatible(prop, compatible);
    }

    return idx;
}

rt_bool_t rt_ofw_machine_is_compatible(const char *compatible)
{
    return ofw_node_index_of_compatible(ofw_node_root, compatible) >= 0;
}

/*
 * Property status:
 *
 *  "okay" or "ok":
 *      Indicates the device is operational.
 *
 *  "disabled":
 *      Indicates that the device is not presently operational, but it might
 *      become operational in the future (for example, something is not
 *      plugged in, or switched off).
 *      Refer to the device binding for details on what disabled means for a
 *      given device.
 *
 *  "reserved":
 *      Indicates that the device is operational, but should not be used.
 *      Typically this is used for devices that are controlled by another
 *      software component, such as platform firmware.
 *
 *  "fail":
 *      Indicates that the device is not operational. A serious error was
 *      detected in the device, and it is unlikely to become operational
 *      without repair.
 *
 *  "fail-sss":
 *      Indicates that the device is not operational. A serious error was
 *      detected in the device and it is unlikely to become operational
 *      without repair. The sss portion of the value is specific to the
 *      device and indicates the error condition detected.
 */

static rt_bool_t ofw_node_is_fail(const struct rt_ofw_node *np)
{
    rt_bool_t res = RT_FALSE;
    const char *status = rt_ofw_prop_read_raw(np, "status", RT_NULL);

    if (status)
    {
        res = !rt_strcmp(status, "fail") || !rt_strncmp(status, "fail-", 5);
    }

    return res;
}

static rt_bool_t ofw_node_is_available(const struct rt_ofw_node *np)
{
    rt_bool_t res = RT_TRUE;
    const char *status = rt_ofw_prop_read_raw(np, "status", RT_NULL);

    if (status)
    {
        res = !rt_strcmp(status, "okay") || !rt_strcmp(status, "ok");
    }

    return res;
}

rt_bool_t rt_ofw_node_is_available(const struct rt_ofw_node *np)
{
    return np ? ofw_node_is_available(np) : RT_FALSE;
}

rt_bool_t rt_ofw_node_is_compatible(const struct rt_ofw_node *np, const char *compatible)
{
    rt_bool_t res = RT_FALSE;

    if (np)
    {
        res = ofw_node_index_of_compatible(np, compatible) >= 0;
    }

    return res;
}

static struct rt_ofw_node_id *ofw_prop_match(struct rt_ofw_prop *prop, const struct rt_ofw_node_id *ids)
{
    int best_index = RT_UINT32_MAX >> 1, index;
    struct rt_ofw_node_id *found_id = RT_NULL, *id;

    for (id = (struct rt_ofw_node_id *)ids; id->compatible[0]; ++id)
    {
        index = ofw_prop_index_of_compatible(prop, id->compatible);

        if (index >= 0 && index < best_index)
        {
            found_id = id;
            best_index = index;
        }
    }

    return found_id;
}

struct rt_ofw_node_id *rt_ofw_prop_match(struct rt_ofw_prop *prop, const struct rt_ofw_node_id *ids)
{
    struct rt_ofw_node_id *id = RT_NULL;

    if (prop && ids && !rt_strcmp(prop->name, "compatible"))
    {
        id = ofw_prop_match(prop, ids);
    }

    return id;
}

struct rt_ofw_node_id *rt_ofw_node_match(struct rt_ofw_node *np, const struct rt_ofw_node_id *ids)
{
    struct rt_ofw_prop *prop;
    struct rt_ofw_node_id *id = RT_NULL;

    if (np && ids && (prop = rt_ofw_get_prop(np, "compatible", RT_NULL)))
    {
        id = ofw_prop_match(prop, ids);
    }

    return id;
}

struct rt_ofw_node *rt_ofw_find_node_by_tag(struct rt_ofw_node *from, const char *tag)
{
    struct rt_ofw_node *np = RT_NULL;

    if (tag)
    {
        rt_ofw_foreach_nodes(from, np)
        {
            if (rt_ofw_node_tag_equ(np, tag))
            {
                break;
            }
        }
    }

    return np;
}

struct rt_ofw_node *rt_ofw_find_node_by_prop_r(struct rt_ofw_node *from, const char *propname,
        const struct rt_ofw_prop **out_prop)
{
    struct rt_ofw_node *np = RT_NULL;

    if (propname)
    {
        rt_ofw_foreach_nodes(from, np)
        {
            struct rt_ofw_prop *prop = rt_ofw_get_prop(np, propname, RT_NULL);

            if (prop)
            {
                if (out_prop)
                {
                    *out_prop = prop;
                }

                break;
            }
        }
    }

    return np;
}

struct rt_ofw_node *rt_ofw_find_node_by_name(struct rt_ofw_node *from, const char *name)
{
    struct rt_ofw_node *np = RT_NULL;

    if (name)
    {
        rt_ofw_foreach_nodes(from, np)
        {
            if (np->name && !rt_strcmp(np->name, name))
            {
                np = rt_ofw_node_get(np);
                break;
            }
        }
    }

    return np;
}

struct rt_ofw_node *rt_ofw_find_node_by_type(struct rt_ofw_node *from, const char *type)
{
    struct rt_ofw_node *np = RT_NULL;

    if (type)
    {
        rt_ofw_foreach_nodes(from, np)
        {
            if (rt_ofw_node_is_type(np, type))
            {
                break;
            }
        }
    }

    return np;
}

struct rt_ofw_node *rt_ofw_find_node_by_compatible(struct rt_ofw_node *from, const char *compatible)
{
    struct rt_ofw_node *np = RT_NULL;

    if (compatible)
    {
        rt_ofw_foreach_nodes(from, np)
        {
            if (ofw_node_index_of_compatible(np, compatible) >= 0)
            {
                break;
            }
        }
    }

    return np;
}

struct rt_ofw_node *rt_ofw_find_node_by_ids_r(struct rt_ofw_node *from, const struct rt_ofw_node_id *ids,
        const struct rt_ofw_node_id **out_id)
{
    struct rt_ofw_node *np = RT_NULL;

    if (ids)
    {
        rt_ofw_foreach_nodes(from, np)
        {
            struct rt_ofw_node_id *id = rt_ofw_node_match(np, ids);

            if (id)
            {
                if (out_id)
                {
                    *out_id = id;
                }

                break;
            }
        }
    }

    return np;
}

struct rt_ofw_node *rt_ofw_find_node_by_path(const char *path)
{
    struct rt_ofw_node *np = RT_NULL, *parent, *tmp = RT_NULL;

    if (path)
    {
        if (!rt_strcmp(path, "/"))
        {
            np = ofw_node_root;
        }
        else
        {
            ++path;
            parent = rt_ofw_node_get(ofw_node_root);

            while (*path)
            {
                const char *next = strchrnul(path, '/');
                rt_size_t len = next - path;

                tmp = RT_NULL;

                rt_ofw_foreach_child_node(parent, np)
                {
                    if (!rt_strncmp(np->full_name, path, len))
                    {
                        rt_ofw_node_put(parent);

                        parent = np;
                        tmp = np;

                        break;
                    }
                }

                if (!tmp)
                {
                    rt_ofw_node_put(parent);

                    break;
                }

                path += len + !!*next;
            }

            np = tmp;
        }

        rt_ofw_node_get(np);
    }

    return np;
}

struct rt_ofw_node *rt_ofw_find_node_by_phandle(rt_phandle phandle)
{
    struct rt_ofw_node *np = RT_NULL;

    if (phandle >= OFW_PHANDLE_MIN && phandle <= OFW_PHANDLE_MAX)
    {
        /* rebase from zero */
        rt_phandle poff = phandle - _phandle_range[0];

        np = _phandle_hash[poff];

        if (!np)
        {
            rt_ofw_foreach_allnodes(np)
            {
                if (np->phandle == phandle)
                {
                    _phandle_hash[poff] = np;

                    break;
                }
            }
        }
        else
        {
            rt_ofw_node_get(np);
        }
    }

    return np;
}

struct rt_ofw_node *rt_ofw_get_parent(const struct rt_ofw_node *np)
{
    if (np)
    {
        np = rt_ofw_node_get(np->parent);
    }

    return (struct rt_ofw_node *)np;
}

struct rt_ofw_node *rt_ofw_get_child_by_tag(const struct rt_ofw_node *parent, const char *tag)
{
    struct rt_ofw_node *child = RT_NULL;

    if (parent && tag)
    {
        rt_ofw_foreach_child_node(parent, child)
        {
            if (rt_ofw_node_tag_equ(child, tag))
            {
                break;
            }
        }
    }

    return child;
}

struct rt_ofw_node *rt_ofw_get_child_by_compatible(const struct rt_ofw_node *parent, const char *compatible)
{
    struct rt_ofw_node *child = RT_NULL;

    if (parent && compatible)
    {
        rt_ofw_foreach_child_node(parent, child)
        {
            if (ofw_node_index_of_compatible(child, compatible) >= 0)
            {
                break;
            }
        }
    }

    return child;
}

int rt_ofw_get_child_count(const struct rt_ofw_node *np)
{
    int nr;

    if (np)
    {
        struct rt_ofw_node *child;

        nr = 0;

        rt_ofw_foreach_child_node(np, child)
        {
            ++nr;
        }
    }
    else
    {
        nr = -RT_EINVAL;
    }

    return nr;
}

int rt_ofw_get_available_child_count(const struct rt_ofw_node *np)
{
    int nr;

    if (np)
    {
        struct rt_ofw_node *child;

        nr = 0;

        rt_ofw_foreach_available_child_node(np, child)
        {
            ++nr;
        }
    }
    else
    {
        nr = -RT_EINVAL;
    }

    return nr;
}

struct rt_ofw_node *rt_ofw_get_next_node(struct rt_ofw_node *prev)
{
    struct rt_ofw_node *np;

    np = rt_ofw_node_get(ofw_get_next_node(prev));
    rt_ofw_node_put(prev);

    return np;
}

struct rt_ofw_node *rt_ofw_get_next_parent(struct rt_ofw_node *prev)
{
    struct rt_ofw_node *next = RT_NULL;

    if (prev)
    {
        next = rt_ofw_node_get(prev->parent);
        rt_ofw_node_put(prev);
    }

    return next;
}

struct rt_ofw_node *rt_ofw_get_next_child(const struct rt_ofw_node *parent, struct rt_ofw_node *prev)
{
    struct rt_ofw_node *next = RT_NULL;

    if (parent)
    {
        next = prev ? prev->sibling : parent->child;
        rt_ofw_node_put(prev);
        rt_ofw_node_get(next);
    }

    return next;
}

struct rt_ofw_node *rt_ofw_get_next_available_child(const struct rt_ofw_node *parent, struct rt_ofw_node *prev)
{
    struct rt_ofw_node *next = RT_NULL;

    if (parent)
    {
        next = prev;

        do {
            next = rt_ofw_get_next_child(parent, next);

        } while (next && !ofw_node_is_available(next));
    }

    return next;
}

struct rt_ofw_node *rt_ofw_get_cpu_node(int cpu, int *thread, rt_bool_t (*match_cpu_hwid)(int cpu, rt_uint64_t hwid))
{
    const char *propname = "reg";
    struct rt_ofw_node *cpu_np = RT_NULL;

    /*
     * "reg" (some of the obsolete arch may be other names):
     *  The value of reg is a <prop-encoded-array> that defines a unique
     *  CPU/thread id for the CPU/threads represented by the CPU node.
     *
     *  If a CPU supports more than one thread (i.e. multiple streams of
     *  execution) the reg property is an array with 1 element per thread. The
     *  #address-cells on the /cpus node specifies how many cells each element
     *  of the array takes. Software can determine the number of threads by
     *  dividing the size of reg by the parent node’s #address-cells:
     *
     *      thread-number = reg-cells / address-cells
     *
     *  If a CPU/thread can be the target of an external interrupt the reg
     *  property value must be a unique CPU/thread id that is addressable by the
     *  interrupt controller.
     *
     *  If a CPU/thread cannot be the target of an external interrupt, then reg
     *  must be unique and out of bounds of the range addressed by the interrupt
     *  controller
     *
     *  If a CPU/thread’s PIR (pending interrupt register) is modifiable, a
     *  client program should modify PIR to match the reg property value. If PIR
     *  cannot be modified and the PIR value is distinct from the interrupt
     *  controller number space, the CPUs binding may define a binding-specific
     *  representation of PIR values if desired.
     */

    rt_ofw_foreach_cpu_node(cpu_np)
    {
        rt_ssize_t prop_len;
        rt_bool_t is_end = RT_FALSE;
        int tid, addr_cells = rt_ofw_io_addr_cells(cpu_np);
        const fdt32_t *cell = rt_ofw_prop_read_raw(cpu_np, propname, &prop_len);

        if (!cell && !addr_cells)
        {
            if (match_cpu_hwid && match_cpu_hwid(cpu, 0))
            {
                break;
            }

            continue;
        }

        if (!match_cpu_hwid)
        {
            continue;
        }

        prop_len /= sizeof(*cell) * addr_cells;

        for (tid = 0; tid < prop_len; ++tid)
        {
            rt_uint64_t hwid = rt_fdt_read_number(cell, addr_cells);

            if (match_cpu_hwid(cpu, hwid))
            {
                if (thread)
                {
                    *thread = tid;
                }

                is_end = RT_TRUE;

                break;
            }

            cell += addr_cells;
        }

        if (is_end)
        {
            break;
        }
    }

    return cpu_np;
}

struct rt_ofw_node *rt_ofw_get_next_cpu_node(struct rt_ofw_node *prev)
{
    struct rt_ofw_node *cpu_np;

    if (prev)
    {
        cpu_np = prev->sibling;
        rt_ofw_node_put(prev);
    }
    else
    {
        cpu_np = ofw_node_cpus->child;
    }

    for (; cpu_np; cpu_np = cpu_np->sibling)
    {
        if (ofw_node_is_fail(cpu_np))
        {
            continue;
        }

        if (!(rt_ofw_node_tag_equ(cpu_np, "cpu") || rt_ofw_node_is_type(cpu_np, "cpu")))
        {
            continue;
        }

        if (rt_ofw_node_get(cpu_np))
        {
            break;
        }
    }

    return cpu_np;
}

struct rt_ofw_node *rt_ofw_get_cpu_state_node(struct rt_ofw_node *cpu_np, int index)
{
    struct rt_ofw_cell_args args;
    struct rt_ofw_node *np = RT_NULL, *state_np;
    rt_err_t err = rt_ofw_parse_phandle_cells(cpu_np, "power-domains", "#power-domain-cells", 0, &args);

    if (!err)
    {
        state_np = rt_ofw_parse_phandle(args.data, "domain-idle-states", index);

        rt_ofw_node_put(args.data);

        if (state_np)
        {
            np = state_np;
        }
    }

    if (!np)
    {
        int count = 0;
        rt_uint32_t phandle;
        const fdt32_t *cell;
        struct rt_ofw_prop *prop;

        rt_ofw_foreach_prop_u32(cpu_np, "cpu-idle-states", prop, cell, phandle)
        {
            if (count == index)
            {
                np = rt_ofw_find_node_by_phandle((rt_phandle)phandle);

                break;
            }

            ++count;
        }
    }

    return np;
}

rt_uint64_t rt_ofw_get_cpu_id(struct rt_ofw_node *cpu_np)
{
    rt_uint64_t cpuid = ~0ULL;

    if (cpu_np)
    {
        rt_uint64_t idx = 0;
        struct rt_ofw_node *np = ofw_node_cpus->child;

        for (; np; np = np->sibling)
        {
            if (!(rt_ofw_node_tag_equ(cpu_np, "cpu") || rt_ofw_node_is_type(cpu_np, "cpu")))
            {
                continue;
            }

            if (cpu_np == np)
            {
                cpuid = idx;

                break;
            }

            ++idx;
        }

        if ((rt_int64_t)cpuid < 0 && !rt_ofw_prop_read_u64(cpu_np, "rt-thread,cpuid", &idx))
        {
            cpuid = idx;
        }
    }

    return cpuid;
}

rt_uint64_t rt_ofw_get_cpu_hwid(struct rt_ofw_node *cpu_np, unsigned int thread)
{
    rt_uint64_t thread_id, hwid = ~0ULL;

    if (cpu_np && thread >= 0 && !rt_ofw_get_address(cpu_np, thread, &thread_id, RT_NULL))
    {
        hwid = thread_id;
    }

    return hwid;
}

rt_err_t ofw_alias_scan(void)
{
    rt_err_t err = RT_EOK;
    struct rt_ofw_prop *prop;
    struct rt_ofw_node *np = ofw_node_aliases, *tmp;

    rt_ofw_foreach_prop(np, prop)
    {
        int id = 0, rate = 1;
        struct alias_info *info;
        const char *name = prop->name, *end;

        /* Maybe the bootloader will set the name, or other nodes reference the aliases */
        if (!rt_strcmp(name, "name") || !rt_strcmp(name, "phandle"))
        {
            continue;
        }

        if (!(tmp = rt_ofw_find_node_by_path(prop->value)))
        {
            continue;
        }

        end = name + rt_strlen(name) - 1;

        while (*end && !(*end >= '0' && *end <= '9') && end > name)
        {
            --end;
        }

        while (*end && (*end >= '0' && *end <= '9'))
        {
            id += (*end - '0') * rate;
            rate *= 10;

            ++end;
        }

        info = rt_malloc(sizeof(*info));

        if (!info)
        {
            err = -RT_ENOMEM;
            break;
        }

        rt_list_init(&info->list);

        info->id = id;
        info->tag = name;
        info->tag_len = end - name - 1;
        info->np = tmp;

        rt_list_insert_after(&_aliases_nodes, &info->list);
    }

    return err;
}

struct rt_ofw_node *rt_ofw_get_alias_node(const char *tag, int id)
{
    struct alias_info *info;
    struct rt_ofw_node *np = RT_NULL;

    if (tag && id >= 0)
    {
        if (!rt_list_isempty(&_aliases_nodes))
        {
            rt_list_for_each_entry(info, &_aliases_nodes, list)
            {
                if (rt_strncmp(info->tag, tag, info->tag_len))
                {
                    continue;
                }

                if (info->id == id)
                {
                    np = info->np;
                    break;
                }
            }
        }
    }

    return np;
}

int ofw_alias_node_id(struct rt_ofw_node *np)
{
    int id;
    struct alias_info *info = RT_NULL;

    if (np)
    {
        id = -1;
        if (!rt_list_isempty(&_aliases_nodes))
        {
            rt_list_for_each_entry(info, &_aliases_nodes, list)
            {
                if (info->np == np)
                {
                    id = info->id;
                    break;
                }
            }
        }
    }
    else
    {
        id = -RT_EINVAL;
    }

    return id;
}

int rt_ofw_get_alias_id(struct rt_ofw_node *np, const char *tag)
{
    int id;
    struct alias_info *info;

    if (np && tag)
    {
        id = -1;
        if (!rt_list_isempty(&_aliases_nodes))
        {
            rt_list_for_each_entry(info, &_aliases_nodes, list)
            {
                if (rt_strncmp(info->tag, tag, info->tag_len))
                {
                    continue;
                }

                if (info->np == np)
                {
                    id = info->id;
                    break;
                }
            }
        }
    }
    else
    {
        id = -RT_EINVAL;
    }

    return id;
}

int rt_ofw_get_alias_last_id(const char *tag)
{
    int id;
    struct alias_info *info;

    if (tag)
    {
        id = -1;
        if (!rt_list_isempty(&_aliases_nodes))
        {
            rt_list_for_each_entry(info, &_aliases_nodes, list)
            {
                if (rt_strncmp(info->tag, tag, info->tag_len))
                {
                    continue;
                }

                if (info->id > id)
                {
                    id = info->id;
                }
            }
        }
    }
    else
    {
        id = -RT_EINVAL;
    }

    return id;
}

struct rt_ofw_node *rt_ofw_append_child(struct rt_ofw_node *parent, const char *full_name)
{
    rt_phandle phandle;
    rt_err_t err = RT_EOK;
    fdt32_t *phandle_value;
    struct rt_ofw_node *np = RT_NULL, *child;

    if (full_name)
    {
        if ((phandle = ofw_phandle_next()))
        {
            np = rt_calloc(1, sizeof(*np) + sizeof(*phandle_value));
        }
    }

    if (np)
    {
        parent = parent ? : ofw_node_root;

        np->full_name = full_name;
        np->phandle = phandle;
        np->parent = parent;

        rt_ref_init(&np->ref);

        phandle_value = (void *)np + sizeof(*np);
        *phandle_value = cpu_to_fdt32(phandle);

        err = rt_ofw_append_prop(np, "phandle", sizeof(*phandle_value), phandle_value);

        if (!err)
        {
            if (parent->child)
            {
                rt_ofw_foreach_child_node(parent, child)
                {
                    if (!child->sibling)
                    {
                        child->sibling = np;
                        rt_ofw_node_put(child);
                        break;
                    }
                }
            }
            else
            {
                parent->child = np;
            }
        }
        else
        {
            rt_free(np);
            np = RT_NULL;
        }
    }

    return np;
}

rt_err_t rt_ofw_append_prop(struct rt_ofw_node *np, const char *name, int length, void *value)
{
    rt_err_t err = RT_EOK;

    if (np && name && ((length && value) || (!length && !value)))
    {
        struct rt_ofw_prop *prop = rt_malloc(sizeof(*prop)), *last_prop;

        if (prop)
        {
            prop->name = name;
            prop->length = length;
            prop->value = value;
            prop->next = RT_NULL;

            if (np->props)
            {
                rt_ofw_foreach_prop(np, last_prop)
                {
                    if (!last_prop->next)
                    {
                        last_prop->next = prop;
                        break;
                    }
                }
            }
            else
            {
                np->props = prop;
            }
        }
        else
        {
            err = -RT_ENOMEM;
        }
    }
    else
    {
        err = -RT_EINVAL;
    }

    return err;
}

struct rt_ofw_node *rt_ofw_parse_phandle(const struct rt_ofw_node *np, const char *phandle_name, int index)
{
    struct rt_ofw_cell_args args;
    struct rt_ofw_node *ref_np = RT_NULL;

    if (!rt_ofw_parse_phandle_cells(np, phandle_name, RT_NULL, index, &args))
    {
        ref_np = args.data;
    }

    return ref_np;
}

static rt_err_t ofw_parse_phandle_cells(const struct rt_ofw_node *np, const char *list_name, const char *cells_name,
        int index, struct rt_ofw_cell_args *out_args)
{
    rt_err_t err = -RT_EEMPTY;
    rt_uint32_t value;
    rt_size_t count = 0;
    const fdt32_t *cell;
    struct rt_ofw_prop *prop;

    /*
     * List:
     *
     *      phandle1: node1 {
     *          #list-cells = <2>;
     *      };
     *
     *      phandle2: node2 {
     *          #list-cells = <1>;
     *      };
     *
     *      node3 {
     *          list = <&phandle1 0xaa 0xbb>, <&phandle2 0xcc>;
     *      };
     *
     * if call:
     *  rt_ofw_parse_phandle_cells(node3, "list", "#list-cells", 0, &args):
     *
     *      args.data = node1;
     *      args.args_count = 2;
     *      args.args[0] = 0xaa;
     *      args.args[1] = 0xbb;
     *
     *  rt_ofw_parse_phandle_cells(node3, "list", "#list-cells", 1, &args):
     *
     *      args.data = node2;
     *      args.args_count = 1;
     *      args.args[0] = 0xcc;
     */

    rt_ofw_foreach_prop_u32(np, list_name, prop, cell, value)
    {
        rt_uint32_t cells_count = 0;
        struct rt_ofw_node *phandle_np = rt_ofw_find_node_by_phandle((rt_phandle)value);

        /* if phandle node is undefined, we assume that the cels_count is 0 */
        if (cells_name && phandle_np)
        {
            rt_ofw_prop_read_u32(phandle_np, cells_name, &cells_count);
        }

        if (count++ == index)
        {
            for (int idx = 0; idx < cells_count; ++idx)
            {
                cell = rt_ofw_prop_next_u32(prop, cell, &value);

                out_args->args[idx] = value;
            }

            out_args->args_count = cells_count;
            out_args->data = phandle_np;

            if (out_args->data)
            {
                err = RT_EOK;
            }

            break;
        }

        cell += cells_count;
    }

    return err;
}

rt_err_t rt_ofw_parse_phandle_cells(const struct rt_ofw_node *np, const char *list_name, const char *cells_name,
        int index, struct rt_ofw_cell_args *out_args)
{
    rt_err_t err;

    if (np && list_name && index >= 0 && out_args)
    {
        err = ofw_parse_phandle_cells(np, list_name, cells_name, index, out_args);
    }
    else
    {
        err = -RT_EINVAL;
    }

    return err;
}

int rt_ofw_count_phandle_cells(const struct rt_ofw_node *np, const char *list_name, const char *cells_name)
{
    int count;

    if (np && list_name)
    {
        count = -1;

        if (!cells_name)
        {
            rt_ssize_t length;

            if (rt_ofw_get_prop(np, list_name, &length))
            {
                count = length / sizeof(fdt32_t);
            }
        }
        else
        {
            int index = count = 0;
            struct rt_ofw_cell_args args;

            while (!ofw_parse_phandle_cells(np, list_name, cells_name, index, &args))
            {
                ++index;
                ++count;
            }
        }
    }
    else
    {
        count = -RT_EINVAL;
    }

    return count;
}

static const char *ofw_get_prop_fuzzy_name(const struct rt_ofw_node *np, const char *name)
{
    char *sf, split_field[64];
    rt_size_t len = 0, max_ak = 0;
    const char *str, *result = RT_NULL;
    RT_BITMAP_DECLARE(ak, sizeof(split_field));
    struct rt_ofw_prop *prop;

    /*
     * List:
     *
     *      node {
     *          property;
     *          front-prop-rear;
     *          front-prop;
     *          prop-rear;
     *      };
     *
     * if call:
     *  ofw_get_prop_fuzzy_name(node, name):
     *      ["prop"] => property
     *      ["-prop"] => front-prop-rear
     *      ["prop-"] => front-prop-rear
     *      ["-prop$"] => front-prop
     *      ["^prop-"] => prop-rear
     *      ["-prop-"] => front-prop-rear
     *      ["front-*-rear"] => front-prop-rear
     */

    str = name;
    sf = split_field;

    if (str[0] != '^')
    {
        /* As '*' */
        *sf++ = '\0';
        rt_bitmap_set_bit(ak, len++);
    }
    else
    {
        ++str;
    }

    for (; *str && len < sizeof(split_field); ++str, ++sf, ++len)
    {
        if (*str != '*')
        {
            *sf = *str;
            rt_bitmap_clear_bit(ak, len);
        }
        else
        {
            max_ak = len;
            *sf = '\0';
            rt_bitmap_set_bit(ak, len);
        }
    }
    *sf = '\0';

    if (str[-1] != '$')
    {
        /* As '*' */
        max_ak = len;
        rt_bitmap_set_bit(ak, len++);
    }
    else
    {
        sf[-1] = '\0';
        --len;
    }

    sf = split_field;

    if (len >= sizeof(split_field))
    {
        LOG_W("%s fuzzy name = %s len is %d out of %d", np->full_name, name, rt_strlen(name), sizeof(split_field));
    }

    rt_ofw_foreach_prop(np, prop)
    {
        int prep_ak = 0, next_ak, field;
        rt_bool_t match = RT_TRUE;
        const char *propname = prop->name, *fuzzy_name = sf;

        if (!rt_bitmap_test_bit(ak, prep_ak))
        {
            next_ak = rt_bitmap_next_set_bit(ak, prep_ak + 1, max_ak) ? : len;
            field = next_ak - prep_ak;

            if (rt_strncmp(propname, fuzzy_name, field))
            {
                continue;
            }

            propname += field;
            fuzzy_name += field;
            prep_ak = next_ak;
        }

        rt_bitmap_for_each_set_bit_from(ak, prep_ak, next_ak, max_ak)
        {
            /* Skip the '*' */
            if (prep_ak == next_ak)
            {
                ++fuzzy_name;

                next_ak = rt_bitmap_next_set_bit(ak, prep_ak + 1, max_ak);
            }

            if (!(str = rt_strstr(propname, fuzzy_name)))
            {
                match = RT_FALSE;
                break;
            }

            field = next_ak - prep_ak;
            propname = str + field - 1;
            fuzzy_name += field;
            prep_ak = next_ak;
        }

        if (match)
        {
            if ((max_ak || !split_field[0]) && next_ak >= max_ak && len - max_ak > 1)
            {
                if (next_ak == max_ak)
                {
                    /* Skip the last '*' */
                    ++fuzzy_name;
                }

                if (!(propname = rt_strstr(propname, fuzzy_name)))
                {
                    continue;
                }

                /* Check end flag */
                if (propname[len - max_ak - 1] != '\0')
                {
                    continue;
                }
            }

            result = prop->name;
            break;
        }
    }

    return result;
}

const char *rt_ofw_get_prop_fuzzy_name(const struct rt_ofw_node *np, const char *name)
{
    const char *propname = RT_NULL;

    if (np && name)
    {
        propname = ofw_get_prop_fuzzy_name(np, name);
    }

    return propname;
}


struct rt_ofw_prop *rt_ofw_get_prop(const struct rt_ofw_node *np, const char *name, rt_ssize_t *out_length)
{
    struct rt_ofw_prop *prop = RT_NULL;

    if (np && name)
    {
        rt_ofw_foreach_prop(np, prop)
        {
            if (!rt_strcmp(prop->name, name))
            {
                if (out_length)
                {
                    *out_length = prop->length;
                }

                break;
            }
        }
    }

    return prop;
}

#define OFW_PROP_READ_UXX_ARRAY_INDEX(bit)                      \
int rt_ofw_prop_read_u##bit##_array_index(                      \
        const struct rt_ofw_node *np, const char *propname,     \
        int index, int nr, rt_uint##bit##_t *out_values)        \
{                                                               \
    int res, max_nr;                                            \
    if (np && propname && index >= 0 && nr >= 0 && out_values)  \
    {                                                           \
        rt_ssize_t len;                                         \
        const fdt##bit##_t *elm;                                \
        elm = rt_ofw_prop_read_raw(np, propname, &len);         \
        max_nr = len / sizeof(*elm);                            \
        if (elm && index < max_nr)                              \
        {                                                       \
            elm += index;                                       \
            max_nr -= index;                                    \
            res = nr > max_nr ? max_nr : nr;                    \
            for (nr = 0; nr < res; ++nr)                        \
            {                                                   \
                *out_values++ = fdt##bit##_to_cpu(*elm++);      \
            }                                                   \
        }                                                       \
        else                                                    \
        {                                                       \
            res = -RT_EEMPTY;                                   \
        }                                                       \
    }                                                           \
    else                                                        \
    {                                                           \
        res = -RT_EINVAL;                                       \
    }                                                           \
    return res;                                                 \
}

OFW_PROP_READ_UXX_ARRAY_INDEX(8)
OFW_PROP_READ_UXX_ARRAY_INDEX(16)
OFW_PROP_READ_UXX_ARRAY_INDEX(32)
OFW_PROP_READ_UXX_ARRAY_INDEX(64)

#undef OFW_PROP_READ_UXX_ARRAY_INDEX

int rt_ofw_prop_read_string_array_index(const struct rt_ofw_node *np, const char *propname,
        int index, int nr, const char **out_strings)
{
    int res = 0;

    if (np && propname && index >= 0 && nr >= 0 && out_strings)
    {
        rt_ssize_t len, slen = 0;
        const char *value = rt_ofw_prop_read_raw(np, propname, &len);

        if (value)
        {
            nr += index;

            for (int idx = 0; idx < nr && len > 0; ++idx)
            {
                /* Add '\0' */
                slen = rt_strlen(value) + 1;

                if (idx >= index)
                {
                    *out_strings++ = value;

                    ++res;
                }

                len -= slen;
                value += slen;
            }
        }
        else
        {
            res = -RT_EEMPTY;
        }
    }
    else
    {
        res = -RT_EINVAL;
    }

    return res;
}

int rt_ofw_prop_count_of_size(const struct rt_ofw_node *np, const char *propname, int size)
{
    int count;

    if (np && propname && size > 0)
    {
        rt_ssize_t len;

        count = -RT_EEMPTY;

        if (rt_ofw_get_prop(np, propname, &len))
        {
            count = len / size;
        }
    }
    else
    {
        count = -RT_EINVAL;
    }

    return count;
}

static rt_int32_t ofw_strcmp(const char *cs, const char *ct)
{
    return rt_strcmp(cs, ct);
}

int rt_ofw_prop_index_of_string(const struct rt_ofw_node *np, const char *propname, const char *string)
{
    int idx;

    if (np && propname && string)
    {
        struct rt_ofw_prop *prop = rt_ofw_get_prop(np, propname, RT_NULL);

        idx = -1;

        if (prop)
        {
            idx = ofw_prop_index_of_string(prop, string, ofw_strcmp);
        }
    }
    else
    {
        idx = -RT_EINVAL;
    }

    return idx;
}

const fdt32_t *rt_ofw_prop_next_u32(struct rt_ofw_prop *prop, const fdt32_t *cur, rt_uint32_t *out_value)
{
    if (prop && out_value)
    {
        if (cur)
        {
            ++cur;

            if ((void *)cur >= prop->value + prop->length)
            {
                cur = RT_NULL;
            }
        }
        else
        {
            cur = prop->value;
        }

        if (cur)
        {
            *out_value = fdt32_to_cpu(*cur);
        }
    }
    else
    {
        cur = RT_NULL;
    }

    return cur;
}

const char *rt_ofw_prop_next_string(struct rt_ofw_prop *prop, const char *cur)
{
    if (prop)
    {
        if (cur)
        {
            cur += rt_strlen(cur) + 1;

            if ((void *)cur >= prop->value + prop->length)
            {
                cur = RT_NULL;
            }
        }
        else
        {
            cur = prop->value;
        }
    }
    else
    {
        cur = RT_NULL;
    }

    return cur;
}
