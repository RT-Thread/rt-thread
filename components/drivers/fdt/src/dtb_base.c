/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "dtb_node.h"
#include "libfdt.h"
#include "libfdt_env.h"
#include <ctype.h>

static const char *_parse_integer_fixup_radix(const char *s, unsigned int *base)
{
    if (*base == 0)
    {
        if (s[0] == '0')
        {
            if (tolower(s[1]) == 'x' && isxdigit((int)s[2]))
                *base = 16;
            else
                *base = 8;
        }
        else
            *base = 10;
    }
    if (*base == 16 && s[0] == '0' && tolower(s[1]) == 'x')
        s += 2;
    return s;
}

unsigned long simple_strtoul(const char *cp, char **endp,
                unsigned int base)
{
    unsigned long result = 0;
    unsigned long value;

    cp = _parse_integer_fixup_radix(cp, &base);

    while (isxdigit((int)*cp) && (value = isdigit((int)*cp) ? *cp-'0' : (islower((int)*cp)
        ? toupper(*cp) : *cp)-'A'+10) < base)
    {
        result = result*base + value;
        cp++;
    }

    if (endp)
        *endp = (char *)cp;

    return result;
}

int strict_strtoul(const char *cp, unsigned int base, unsigned long *res)
{
    char *tail;
    unsigned long val;
    size_t len;

    *res = 0;
    len = strlen(cp);
    if (len == 0)
        return -EINVAL;

    val = simple_strtoul(cp, &tail, base);
    if (tail == cp)
        return -EINVAL;

    if ((*tail == '\0') ||
        ((len == (size_t)(tail - cp) + 1) && (*tail == '\n')))
    {
        *res = val;
        return 0;
    }

    return -EINVAL;
}

long simple_strtol(const char *cp, char **endp, unsigned int base)
{
    if (*cp == '-')
        return -simple_strtoul(cp + 1, endp, base);

    return simple_strtoul(cp, endp, base);
}

rt_bool_t dtb_node_read_bool(const struct dtb_node *node, const char *propname)
{
    const void *prop;

    RT_ASSERT(dtb_node_valid(node));
    debug("%s: %s: ", __func__, propname);

    prop = dtb_node_get_property(node, propname, NULL);

    debug("%s\n", prop ? "true" : "false");

    return prop ? RT_TRUE : RT_FALSE;
}

const void *dtb_node_read_prop(const struct dtb_node *node, const char *propname, int *sizep)
{
    const char *val = NULL;
    int len;

    RT_ASSERT(dtb_node_valid(node));
    debug("%s: %s: ", __func__, propname);

    struct dtb_property *prop = dtb_node_get_dtb_node_property(node, propname, &len);

    if (prop)
    {
        val = prop->value;
        len = prop->size;
    }

    if (!val)
    {
        debug("<not found>\n");
        if (sizep)
            *sizep = -FDT_ERR_NOTFOUND;
        return NULL;
    }
    if (sizep)
        *sizep = len;

    return val;
}

const char *dtb_node_read_string(const struct dtb_node *node, const char *propname)
{
    const char *str;
    int len;

    str = dtb_node_read_prop(node, propname, &len);
    if (!str)
        return NULL;

    if (strnlen(str, len) >= len)
    {
        debug("<invalid>\n");
        return NULL;
    }
    debug("%s\n", str);

    return str;
}

const struct dtb_node *dtb_node_find_subnode(const struct dtb_node *node, const char *subnode_name)
{
    const struct dtb_node *subnode;

    RT_ASSERT(dtb_node_valid(node));
    debug("%s: %s: ", __func__, subnode_name);

    for (node = node->child; node; node = node->sibling)
    {
        if (!strcmp(subnode_name, node->name))
            break;
    }
    subnode = node;

    debug("%s\n", dtb_node_valid(subnode) ?\
          dtb_node_get_name(subnode) : "<none>");

    return subnode;
}

struct dtb_node *dtb_node_first_subnode(const struct dtb_node *node)
{
    RT_ASSERT(dtb_node_valid(node));

    return node->child;
}

struct dtb_node *dtb_node_next_subnode(const struct dtb_node *node)
{
    RT_ASSERT(dtb_node_valid(node));

    return node->sibling;
}

const char *dtb_node_get_name(const struct dtb_node *node)
{
    if (!dtb_node_valid(node))
    {
        debug("%s node not valid\n", __func__);
        return NULL;
    }

    return strrchr(node->path, '/') + 1;

}

struct dtb_node *dtb_node_get_by_phandle(uint32_t phandle)
{
    if (dtb_node_active())
        return dtb_node_find_node_by_phandle(phandle);
    return NULL;
}

int dtb_node_read_size(const struct dtb_node *node, const char *propname)
{
    struct dtb_property *prop = dtb_node_get_dtb_node_property( node, propname, NULL);

    if (prop)
        return prop->size;

    return -EINVAL;
}

int dtb_node_get_addr_and_size_by_index(const struct dtb_node *node, int index, size_t *addr, size_t *size)
{
    const uint32_t *prop;
    int psize;
    int onesize, na, ns;

    na = dtb_node_n_addr_cells(node);
    ns = dtb_node_n_size_cells(node);

    prop = dtb_node_get_dtb_node_property_value(node, "reg", &psize);
    if (prop == NULL)
    {
        return -1;
    }

    psize /= 4;
    onesize = na + ns;

    if (psize >= (index + 1) * onesize)
    {
        prop += index * onesize;

        if (addr)
        {
            *addr = dtb_node_read_number(prop, na);
        }
        if (size)
        {
            *size = dtb_node_read_number(prop + na, ns);
        }

        return 0;
    }

    return -1;
}

size_t dtb_node_get_addr_index(const struct dtb_node *node, int index)
{
    int na;
    size_t size;

    const uint32_t *prop_val;
    uint flags;

    prop_val = dtb_node_get_address(node, index,
                    (uint64_t *)&size, &flags);
    if (!prop_val)
        return -1;

    na = dtb_node_n_addr_cells(node);

    return dtb_node_read_number(prop_val, na);
}

size_t dtb_node_get_addr(const struct dtb_node *node)
{
    return dtb_node_get_addr_index(node, 0);
}

int dtb_node_stringlist_search(const struct dtb_node *node, const char *property,
                 const char *string)
{
    return dtb_node_property_match_string(node, property, string);
}

int dtb_node_read_string_index(const struct dtb_node *node, const char *property, int index,
                 const char **outp)
{
    return dtb_node_property_read_string_index(node, property, index, outp);
}

int dtb_node_read_string_count(const struct dtb_node *node, const char *property)
{
    return dtb_node_property_count_strings(node, property);
}

struct dtb_node *dtb_node_path(const char *path)
{
    if (dtb_node_active())
        return dtb_node_find_node_by_path(path);
    return NULL;
}

const char *dtb_node_get_chosen_prop(const char *name)
{
    const struct dtb_node *chosen_node;

    chosen_node = (const struct dtb_node *)dtb_node_path("/chosen");

    return dtb_node_read_string(chosen_node, name);
}

struct dtb_node *dtb_node_get_chosen_node(const char *name)
{
    const char *prop;

    prop = dtb_node_get_chosen_prop(name);
    if (!prop)
        return NULL;

    return dtb_node_path(prop);
}

const void *dtb_node_get_property(const struct dtb_node *node, const char *propname, int *lenp)
{
    return dtb_node_get_dtb_node_property_value(node, propname, lenp);
}

rt_bool_t dtb_node_is_available(const struct dtb_node *node)
{
    return dtb_node_device_is_available(node);
}

size_t dtb_node_get_addr_size(const struct dtb_node *node, const char *property,
                size_t *sizep)
{
    int na, ns;
    int psize;
    const uint32_t *prop = dtb_node_get_dtb_node_property_value(node, property, &psize);

    if (!prop)
        return -1;
    na = dtb_node_n_addr_cells(node);
    ns = dtb_node_n_size_cells(node);
    *sizep = dtb_node_read_number(prop + na, ns);

    return dtb_node_read_number(prop, na);
}

const uint8_t *dtb_node_read_u8_array_ptr(const struct dtb_node *node, const char *propname,
                    size_t sz)
{
    int psize;
    const uint32_t *prop = dtb_node_get_dtb_node_property_value(node, propname, &psize);

    if (!prop || sz != psize)
        return NULL;
    return (uint8_t *)prop;
}

int dtb_node_find_all_compatible_node(const struct dtb_node *from, const char *compatible, struct dtb_node **node_table, int max_num, int *node_num)
{
    const struct dtb_node *dn;
    int num = 0;
    for_each_of_allnodes_from(from, dn)
    {
        if (dtb_node_get_dtb_node_compatible_match(dn, compatible) &&
            dtb_node_get(dn))
        {

            num++;
            *node_table = (struct dtb_node *)dn;
            node_table++;
            if (num >= max_num)
            {
                break;
            }
        }
    }
    *node_num = num;
    dtb_node_put(from);

    return 0;
}

int dtb_node_write_prop(const struct dtb_node *node, const char *propname, int len,
              const void *value)
{
    struct dtb_property *pp;
    struct dtb_property *pp_last = NULL;
    struct dtb_property *new;

    if (!dtb_node_active())
        return -ENOSYS;

    if (!node)
        return -EINVAL;

    for (pp = node->properties; pp; pp = pp->next)
    {
        if (strcmp(pp->name, propname) == 0)
        {
            /* Property exists -> change value */
            pp->value = (void *)value;
            pp->size = len;
            return 0;
        }
        pp_last = pp;
    }

    if (!pp_last)
        return -ENOENT;

    /* Property does not exist -> append new property */
    new = malloc(sizeof(struct dtb_property));
    if (!new)
        return -ENOMEM;

    new->name = strdup(propname);
    if (!new->name)
    {
        free(new);
        return -ENOMEM;
    }

    new->value = (void *)value;
    new->size = len;
    new->next = NULL;

    pp_last->next = new;

    return 0;
}

int dtb_node_write_string(const struct dtb_node *node, const char *propname, const char *value)
{
    if (!dtb_node_active())
        return -ENOSYS;

    RT_ASSERT(dtb_node_valid(node));

    debug("%s: %s = %s", __func__, propname, value);

    return dtb_node_write_prop(node, propname, strlen(value) + 1, value);
}

int dtb_node_set_enabled(const struct dtb_node *node, rt_bool_t value)
{
    if (!dtb_node_active())
        return -ENOSYS;

    RT_ASSERT(dtb_node_valid(node));

    if (value)
        return dtb_node_write_string(node, "status", "okay");
    else
        return dtb_node_write_string(node, "status", "disable");
}

/**
 * dtb_node_irq_find_parent - Given a device node, find its interrupt parent node
 * @child: pointer to device node
 *
 * Returns a pointer to the interrupt parent node, or NULL if the interrupt
 * parent could not be determined.
 */
static struct dtb_node *dtb_node_irq_find_parent(struct dtb_node *child)
{
    struct dtb_node *p;
    phandle parent;

    if (!dtb_node_get(child))
        return NULL;
    do
    {
        if (dtb_node_read_u32_array(child, "interrupt-parent", &parent, 1))
        {
            p = dtb_node_get_parent(child);
        }
        else
        {
            p = dtb_node_get_by_phandle(parent);
        }
        dtb_node_put(child);
        child = p;
    } while (p && dtb_node_get_property(p, "#interrupt-cells", NULL) == NULL);

    return p;
}

int dtb_node_irq_get(struct dtb_node *dev, int index)
{
    int rc = 0;
    struct fdt_phandle_args out_irq;
    struct dtb_node *p;
    uint32_t intsize;
    int res, i;

    p = dtb_node_irq_find_parent(dev);
    if (p == NULL)
        return -EINVAL;
    /* Get size of interrupt specifier */
    if (dtb_node_read_u32_array(p, "#interrupt-cells", &intsize, 1))
    {
        res = -EINVAL;
        goto out;
    }

    debug(" path:%s, parent=%pOF, intsize=%d\n", p->path,p, intsize);

    /* Copy intspec into irq structure */
    out_irq.np = p;
    out_irq.args_count = intsize;
    for (i = 0; i < intsize; i++)
    {
        res = dtb_node_read_u32_index(dev, "interrupts",
                         (index * 3 + i),
                         out_irq.args + i);
        if (res)
            goto out;
    }
    rc = out_irq.args[1];
 out:
    dtb_node_put(p);
    return rc;

}

/**
 * dtb_node_irq_get_byname - Decode a node's IRQ and return it as a Linux IRQ number
 * @dev: pointer to device tree node
 * @name: IRQ name
 *
 * Returns Linux IRQ number on success, or 0 on the IRQ mapping failure, or
 * -EPROBE_DEFER if the IRQ domain is not yet created, or error code in case
 * of any other failure.
 */
int dtb_node_irq_get_byname(struct dtb_node *dev, const char *name)
{
    int index;

    if (!name)
        return -EINVAL;

    index = dtb_node_stringlist_search(dev, "interrupt-names", name);
    if (index < 0)
        return index;

    return dtb_node_irq_get(dev, index);
}

/**
 * dtb_node_irq_count - Count the number of IRQs a node uses
 * @dev: pointer to device tree node
 */
int dtb_node_irq_count(struct dtb_node *device)
{
    struct dtb_node *p;
    uint32_t intsize;
    int nr = 0, res = 0;

    p = dtb_node_irq_find_parent(device);
    if (p == NULL)
        return -EINVAL;

    /* Get size of interrupt specifier */
    if (dtb_node_read_u32_array(p, "#interrupt-cells", &intsize, 1))
    {
        res = -EINVAL;
        goto out;
    }

    debug(" path:%s, parent=%pOF, intsize=%d\n", p->path,p, intsize);

    res = dtb_node_read_size(device, "interrupts");
    if (res < 0)
    {
        goto out;
    }
    nr = res / (intsize * 4);
 out:
    dtb_node_put(p);

    return nr;
}
