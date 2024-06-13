/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "libfdt.h"
#include "dtb_node.h"

/* "/aliaes" node */
static struct dtb_node *fdt_aliases;

/**
 * of_find_property_value_of_size() - find property of given size
 *
 * Search for a property in a device node and validate the requested size.
 *
 * @np:     device node from which the property value is to be read.
 * @propname:   name of the property to be searched.
 * @len:    requested length of property value
 *
 * @return the property value on success, -EINVAL if the property does not
 * exist, -ENODATA if property does not have a value, and -EOVERFLOW if the
 * property data isn't large enough.
 */
static void *dtb_node_find_property_value_of_size(const struct dtb_node *dn,
                                             const char *propname, uint32_t len)
{
    struct dtb_property *prop = dtb_node_get_dtb_node_property(dn, propname, NULL);

    if (!prop)
        return ERR_PTR(-EINVAL);
    if (!prop->value)
        return ERR_PTR(-ENODATA);
    if (len > prop->size)
        return ERR_PTR(-EOVERFLOW);
    return prop->value;
}

int dtb_node_read_u32(const struct dtb_node *dn, const char *propname, uint32_t *outp)
{
    const uint32_t *val;

    debug("%s: %s: \n", __func__, propname);
    if (!dn)
        return -EINVAL;
    val = dtb_node_find_property_value_of_size(dn, propname, sizeof(*outp));
    if (IS_ERR(val))
    {
        debug("(not found)\n");
        return PTR_ERR(val);
    }

    *outp = fdt32_to_cpu(*val);
    debug("%#x (%d)\n", *outp, *outp);

    return 0;
}

uint32_t dtb_node_read_u32_default(const struct dtb_node *node, const char *propname, uint32_t def)
{
    dtb_node_read_u32(node, propname, &def);

    return def;
}

int dtb_node_read_u32_array(const struct dtb_node *dn, const char *propname,
                       uint32_t *out_values, size_t sz)
{
    const uint32_t *val;

    debug("%s: %s: ", __func__, propname);
    val = dtb_node_find_property_value_of_size(dn, propname,
                                          sz * sizeof(*out_values));

    if (IS_ERR(val))
        return PTR_ERR(val);

    debug("size %zd, val:%d\n", sz, *val);
    while (sz--)
        *out_values++ = fdt32_to_cpu(*val++);

    return 0;
}

uint32_t dtb_node_read_u32_index_default(const struct dtb_node *node, const char *propname, int index,
                  uint32_t def)
{
    RT_ASSERT(dtb_node_valid(node));
    dtb_node_read_u32_index(node, propname, index, &def);

    return def;
}

int dtb_node_read_s32_default(const struct dtb_node *node, const char *propname, int32_t def)
{
    RT_ASSERT(dtb_node_valid(node));
    dtb_node_read_u32(node, propname, (uint32_t *)&def);

    return def;
}

int dtb_node_read_u32_index(const struct dtb_node *dn, const char *propname,
                       int index, uint32_t *outp)
{
    const uint32_t *val;

    debug("%s: %s: ", __func__, propname);
    if (!dn)
        return -EINVAL;

    val = dtb_node_find_property_value_of_size(dn, propname,
                                          sizeof(*outp) * (index + 1));
    if (IS_ERR(val))
    {
        debug("(not found)\n");
        return PTR_ERR(val);
    }

    *outp = fdt32_to_cpu(val[index]);
    debug("%#x (%d)\n", *outp, *outp);

    return 0;
}

int dtb_node_read_u64(const struct dtb_node *dn, const char *propname, uint64_t *outp)
{
    const uint64_t *val;

    debug("%s: %s: ", __func__, propname);
    if (!dn)
        return -EINVAL;
    val = dtb_node_find_property_value_of_size(dn, propname, sizeof(*outp));
    if (IS_ERR(val))
    {
        debug("(not found)\n");
        return PTR_ERR(val);
    }

    *outp = fdt64_to_cpu(*val);
    debug("%#llx (%lld)\n", (unsigned long long)*outp,
          (unsigned long long)*outp);

    return 0;
}

uint64_t dtb_node_read_u64_default(const struct dtb_node *node, const char *propname, uint64_t def)
{
    RT_ASSERT(dtb_node_valid(node));
    dtb_node_read_u64(node, propname, &def);

    return def;
}

int dtb_node_n_addr_cells(const struct dtb_node *dn)
{
    const uint32_t *ip;

    do
    {
        if (dn->parent)
            dn = dn->parent;
        ip = dtb_node_get_dtb_node_property_value(dn, "#address-cells", NULL);
        if (ip)
            return fdt32_to_cpu(*ip);
    } while (dn->parent);

    /* No #address-cells property for the root node */
    return DEV_ROOT_NODE_ADDR_CELLS_DEFAULT;
}

int dtb_node_n_size_cells(const struct dtb_node *dn)
{
    const uint32_t *ip;

    do
    {
        if (dn->parent)
            dn = dn->parent;
        ip = dtb_node_get_dtb_node_property_value(dn, "#size-cells", NULL);
        if (ip)
            return fdt32_to_cpu(*ip);
    } while (dn->parent);

    /* No #size-cells property for the root node */
    return DEV_ROOT_NODE_SIZE_CELLS_DEFAULT;
}

int dtb_node_simple_addr_cells(const struct dtb_node *dn)
{
    const uint32_t *ip;

    ip = dtb_node_get_dtb_node_property_value(dn, "#address-cells", NULL);
    if (ip)
        return fdt32_to_cpu(*ip);

    /* Return a default of 2 to match fdt_address_cells()*/
    return 2;
}

int dtb_node_simple_size_cells(const struct dtb_node *dn)
{
    const uint32_t *ip;

    ip = dtb_node_get_dtb_node_property_value(dn, "#size-cells", NULL);
    if (ip)
        return fdt32_to_cpu(*ip);

    /* Return a default of 2 to match fdt_size_cells()*/
    return 2;
}

struct dtb_property *dtb_node_get_dtb_node_property(const struct dtb_node *dtb_node, const char *property_name, int *property_size)
{
    struct dtb_property *dtb_property = NULL;

    if (dtb_node != NULL && property_name != NULL)
    {
        dtb_property = dtb_node->properties;

        while (dtb_property != NULL)
        {
            if (!strcmp(dtb_property->name, property_name))
            {
                if (property_size != NULL)
                {
                    *property_size = dtb_property->size;
                }
                return dtb_property;
            }
            dtb_property = dtb_property->next;
        }
    }

    return dtb_property;
}

#define for_each_property_of_node(dn, pp) \
    for (pp = dn->properties; pp != NULL; pp = pp->next)

struct dtb_node *dtb_node_find_node_opts_by_path(const char *path,
                                            const char **opts)
{
    struct dtb_node *np = NULL;
    struct dtb_property *pp;
    const char *separator = strchr(path, ':');

    if (opts)
        *opts = separator ? separator + 1 : NULL;

    if (strcmp(path, "/") == 0)
        return dtb_node_get(get_dtb_node_head());

    /* The path could begin with an alias */
    if (*path != '/')
    {
        int len;
        const char *p = separator;

        if (!p)
            p = strchrnul(path, '/');
        len = p - path;

        /* of_aliases must not be NULL */
        if (!fdt_aliases)
            return NULL;

        for_each_property_of_node(fdt_aliases, pp)
        {
            if (strlen(pp->name) == len && !strncmp(pp->name, path,
                                                    len))
            {
                np = dtb_node_find_node_by_path(pp->value);
                break;
            }
        }
        if (!np)
            return NULL;
        path = p;
    }

    /* Step down the tree matching path components */
    if (!np)
        np = dtb_node_get(get_dtb_node_head());
    while (np && *path == '/')
    {
        struct dtb_node *tmp = np;

        path++; /* Increment past '/' delimiter */
        np = dtb_node_get_dtb_node_by_path(np, path);
        dtb_node_put(tmp);
        path = strchrnul(path, '/');
        if (separator && separator < path)
            break;
    }

    return np;
}

struct dtb_node *dtb_node_find_compatible_node(struct dtb_node *from, const char *compatible)
{
    struct dtb_node *dn;

    for_each_of_allnodes_from(from, dn)
    {
        if (dtb_node_get_dtb_node_compatible_match(dn, compatible) &&
            dtb_node_get(dn))
            break;
    }
    dtb_node_put(from);

    return dn;
}

void *dtb_node_get_dtb_node_property_value(const struct dtb_node *dtb_node, const char *property_name, int *property_size)
{
    struct dtb_property *dtb_property = dtb_node_get_dtb_node_property(dtb_node, property_name, NULL);

    if (!dtb_property || !dtb_property->value || !dtb_property->size)
    {
        return NULL;
    }

    if (property_size != NULL)
    {
        *property_size = dtb_property->size;
    }

    return dtb_property->value;
}

const struct dtb_node *dtb_node_find_node_by_prop_value(struct dtb_node *from,
                                                   const char *propname,
                                                   const void *propval, int proplen)
{
    struct dtb_node *np;
    void *value;
    for_each_of_allnodes_from(from, np)
    {
        value = dtb_node_get_dtb_node_property_value(np, propname, &proplen);
        if (!memcmp(value, propval, proplen) && dtb_node_get(np))
            break;
    }
    dtb_node_put(from);

    return np;
}

struct dtb_node *dtb_node_find_all_nodes(const struct dtb_node *prev)
{
    const struct dtb_node *dn;

    if (!prev)
    {
        dn = get_dtb_node_head();
    }
    else if (prev->child)
    {
        dn = prev->child;
    }
    else
    {
        /*
         * Walk back up looking for a sibling, or the end of the
         * structure
         */
        dn = prev;
        while (dn->parent && !dn->sibling)
            dn = dn->parent;
        dn = dn->sibling; /* Might be null at the end of the tree */
    }

    return (struct dtb_node *)dn;
}

rt_bool_t dtb_node_device_is_available(const struct dtb_node *device)
{
    const char *status;
    int statlen;

    if (!device)
        return RT_FALSE;

    status = dtb_node_get_dtb_node_property_value(device, "status", &statlen);
    if (status == NULL)
        return RT_TRUE;

    if (statlen > 0)
    {
        if (!strcmp(status, "okay"))
            return RT_TRUE;
    }

    return RT_FALSE;
}

struct dtb_node *dtb_node_get_parent(const struct dtb_node *node)
{
    const struct dtb_node *dn;

    if (!node)
        return NULL;

    dn = dtb_node_get(node->parent);

    return (struct dtb_node *)dn;
}

struct dtb_node *dtb_node_find_node_by_phandle(phandle handle)
{
    struct dtb_node *dn;

    if (!handle)
        return NULL;

    for_each_of_allnodes(dn) if (dn->handle == handle) break;
    (void)dtb_node_get(dn);

    return dn;
}

int dtb_node_property_match_string(const struct dtb_node *dn, const char *propname,
                              const char *string)
{
    const struct dtb_property *prop = dtb_node_get_dtb_node_property(dn, propname, NULL);
    size_t l;
    int i;
    const char *p, *end;

    if (!prop)
        return -EINVAL;
    if (!prop->value)
        return -ENODATA;

    p = prop->value;
    end = p + prop->size;

    for (i = 0; p < end; i++, p += l)
    {
        l = strnlen(p, end - p) + 1;
        if (p + l > end)
            return -EILSEQ;
        debug("comparing %s with %s\n", string, p);
        if (strcmp(string, p) == 0)
            return i; /* Found it; return index */
    }
    return -ENODATA;
}

/**
 * of_property_read_string_helper() - Utility helper for parsing string properties
 * @np:     device node from which the property value is to be read.
 * @propname:   name of the property to be searched.
 * @out_strs:   output array of string pointers.
 * @sz:     number of array elements to read.
 * @skip:   Number of strings to skip over at beginning of list.
 *
 * Don't call this function directly. It is a utility helper for the
 * of_property_read_string*() family of functions.
 */
int dtb_node_property_read_string_helper(const struct dtb_node *dn,
                                    const char *propname, const char **out_strs,
                                    size_t sz, int skip)
{
    const struct dtb_property *prop = dtb_node_get_dtb_node_property(dn, propname, NULL);
    int l = 0, i = 0;
    const char *p, *end;

    if (!prop)
        return -EINVAL;
    if (!prop->value)
        return -ENODATA;
    p = prop->value;
    end = p + prop->size;

    for (i = 0; p < end && (!out_strs || i < skip + sz); i++, p += l)
    {
        l = strnlen(p, end - p) + 1;
        if (p + l > end)
            return -EILSEQ;
        if (out_strs && i >= skip)
            *out_strs++ = p;
    }
    i -= skip;
    return i <= 0 ? -ENODATA : i;
}

static int __dtb_node_parse_phandle_with_args(const struct dtb_node *dn,
                                         const char *list_name,
                                         const char *cells_name,
                                         int cell_count, int index,
                                         struct fdt_phandle_args *out_args)
{
    const uint32_t *list, *list_end;
    int rc = 0, cur_index = 0;
    uint32_t count = 0;
    struct dtb_node *node = NULL;
    phandle phandle;
    int size;

    /* Retrieve the phandle list property */
    list = dtb_node_get_dtb_node_property_value(dn, list_name, &size);
    if (!list)
        return -ENOENT;
    list_end = list + size / sizeof(*list);

    /* Loop over the phandles until all the requested entry is found */
    while (list < list_end)
    {
        rc = -EINVAL;
        count = 0;

        /*
         * If phandle is 0, then it is an empty entry with no
         * arguments.  Skip forward to the next entry.
         */
        phandle = fdt32_to_cpu(*(list++));
        if (phandle)
        {
            /*
             * Find the provider node and parse the #*-cells
             * property to determine the argument length.
             *
             * This is not needed if the cell count is hard-coded
             * (i.e. cells_name not set, but cell_count is set),
             * except when we're going to return the found node
             * below.
             */
            if (cells_name || cur_index == index)
            {
                node = dtb_node_find_node_by_phandle(phandle);
                if (!node)
                {
                    debug("%s: could not find phandle\n",
                          dn->path);
                    goto err;
                }
            }

            if (cells_name)
            {
                if (dtb_node_read_u32(node, cells_name, &count))
                {
                    debug("%s: could not get %s for %s\n",
                          dn->path, cells_name,
                          node->path);
                    goto err;
                }
            }
            else
            {
                count = cell_count;
            }

            /*
             * Make sure that the arguments actually fit in the
             * remaining property data length
             */
            if (list + count > list_end)
            {
                debug("%s: arguments longer than property\n",
                      dn->path);
                goto err;
            }
        }

        /*
         * All of the error cases above bail out of the loop, so at
         * this point, the parsing is successful. If the requested
         * index matches, then fill the out_args structure and return,
         * or return -ENOENT for an empty entry.
         */
        rc = -ENOENT;
        if (cur_index == index)
        {
            if (!phandle)
                goto err;

            if (out_args)
            {
                int i;
                if (count > FDT_MAX_PHANDLE_ARGS)
                    count = FDT_MAX_PHANDLE_ARGS;
                out_args->np = node;
                out_args->args_count = count;
                for (i = 0; i < count; i++)
                    out_args->args[i] =
                        fdt32_to_cpu(*(list++));
            }
            else
            {
                dtb_node_put(node);
            }

            /* Found it! return success */
            return 0;
        }

        dtb_node_put(node);
        node = NULL;
        list += count;
        cur_index++;
    }

    /*
     * Unlock node before returning result; will be one of:
     * -ENOENT : index is for empty phandle
     * -EINVAL : parsing error on data
     * [1..n]  : Number of phandle (count mode; when index = -1)
     */
    rc = index < 0 ? cur_index : -ENOENT;
err:
    if (node)
        dtb_node_put(node);
    return rc;
}

struct dtb_node *dtb_node_parse_phandle(const struct dtb_node *dn,
                                   const char *phandle_name, int index)
{
    struct fdt_phandle_args args;

    if (index < 0)
        return NULL;

    if (__dtb_node_parse_phandle_with_args(dn, phandle_name, NULL, 0, index,
                                      &args))
        return NULL;

    return args.np;
}

int dtb_node_parse_phandle_with_args(const struct dtb_node *dn,
                                const char *list_name, const char *cells_name,
                                int index, struct fdt_phandle_args *out_args)
{
    if (index < 0)
        return -EINVAL;

    return __dtb_node_parse_phandle_with_args(dn, list_name, cells_name, 0,
                                         index, out_args);
}

int dtb_node_count_phandle_with_args(const struct dtb_node *dn,
                                const char *list_name, const char *cells_name)
{
    return __dtb_node_parse_phandle_with_args(dn, list_name, cells_name, 0,
                                         -1, NULL);
}
