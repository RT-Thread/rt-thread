/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "libfdt.h"
#include "dtb_node.h"

/* Max address size we deal with */
#define FDT_MAX_ADDR_CELLS  4
#define FDT_CHECK_ADDR_COUNT(na)    ((na) > 0 && (na) <= FDT_MAX_ADDR_CELLS)
#define FDT_CHECK_COUNTS(na, ns)    (FDT_CHECK_ADDR_COUNT(na) && (ns) > 0)

static void dtb_node_default_count_cells(const struct dtb_node *dn,
                       int *addrc, int *sizec)
{
    if (addrc)
        *addrc = dtb_node_n_addr_cells(dn);
    if (sizec)
        *sizec = dtb_node_n_size_cells(dn);
}

const uint32_t *dtb_node_get_address(const struct dtb_node *dev, int index,
                 uint64_t *size, unsigned int *flags)
{
    const uint32_t *prop;
    int psize;
    struct dtb_node *parent;
    int onesize, i, na, ns;

    /* Get parent */
    parent = dtb_node_get_parent(dev);
    if (parent == NULL)
        return NULL;

    dtb_node_default_count_cells(dev, &na, &ns);
    if (!FDT_CHECK_ADDR_COUNT(na))
        return NULL;

    /* Get "reg" or "assigned-addresses" property */
    prop = dtb_node_get_dtb_node_property_value(dev, "reg", &psize);
    if (prop == NULL)
        return NULL;
    psize /= 4;

    onesize = na + ns;
    for (i = 0; psize >= onesize; psize -= onesize, prop += onesize, i++)
        if (i == index)
        {
            if (size)
                *size = dtb_node_read_number(prop + na, ns);
            if (flags)
                *flags = 0x200;
            return prop;
        }
    return NULL;
}
