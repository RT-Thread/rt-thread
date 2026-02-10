/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-25     GuEe-GUI     the first version
 */

#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "rtdm.nvmem"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

rt_err_t rt_nvmem_device_register(struct rt_nvmem_device *ndev)
{
    struct rt_ofw_node *np;

    if (!ndev)
    {
        return -RT_EINVAL;
    }

    np = ndev->parent.ofw_node;

    if (!ndev->ignore_wp)
    {
        rt_uint8_t mode;

        ndev->wp_pin = rt_pin_get_named_pin(&ndev->parent, "wp", 0,
                &mode, &ndev->wp_pin_active);

        if (ndev->wp_pin < 0 && ndev->wp_pin != PIN_NONE)
        {
            return -RT_EINVAL;
        }
        else if (ndev->wp_pin >= 0)
        {
            rt_pin_mode(ndev->wp_pin, mode);
        }
    }

    if (!ndev->cells_nr)
    {
        rt_list_init(&ndev->cell_nodes);
    }

    rt_ref_init(&ndev->ref);

    ndev->read_only = rt_dm_dev_prop_read_bool(&ndev->parent, "read-only") ||
            ndev->read_only || !ndev->reg_write;

    if (np)
    {
        rt_ofw_data(np) = ndev;
    }

    return RT_EOK;
}

rt_err_t rt_nvmem_device_unregister(struct rt_nvmem_device *ndev)
{
    if (!ndev)
    {
        return -RT_EINVAL;
    }

    if (rt_ref_read(&ndev->ref) != 1)
    {
        return -RT_EBUSY;
    }

    return RT_EOK;
}

rt_err_t rt_nvmem_device_append_cell(struct rt_nvmem_device *ndev,
        struct rt_nvmem_cell *cell)
{
    rt_ubase_t level;

    if (!ndev)
    {
        return -RT_EINVAL;
    }

    if (!ndev->cells_nr)
    {
        rt_list_init(&ndev->cell_nodes);
    }

    rt_list_init(&cell->list);

    level = rt_spin_lock_irqsave(&ndev->spinlock);
    rt_list_insert_before(&ndev->cell_nodes, &cell->list);
    ++ndev->cells_nr;
    rt_spin_unlock_irqrestore(&ndev->spinlock, level);

    rt_ref_get(&ndev->ref);

    return RT_EOK;
}

rt_ssize_t rt_nvmem_cell_read(struct rt_nvmem_cell *cell, void *buffer,
        rt_size_t len)
{
    rt_ssize_t res;
    struct rt_nvmem_device *nvmem;

    if (!cell || !buffer || !len)
    {
        return -RT_EINVAL;
    }

    nvmem = cell->nvmem;

    if (len > nvmem->size || len > cell->bytes)
    {
        return -RT_EINVAL;
    }

    if (!nvmem->reg_read)
    {
        return -RT_ENOSYS;
    }

    if ((res = nvmem->reg_read(nvmem, cell->offset, buffer, len)) < 0)
    {
        return res;
    }

    if (cell->bit_offset || cell->nbits)
    {
        /* Shift buffer */
        rt_uint8_t *p, *b;
        int extra, bit_offset = cell->bit_offset;

        p = b = buffer;

        if (bit_offset)
        {
            /* First shift */
            *b++ >>= bit_offset;

            /* Setup rest of the bytes if any */
            for (int i = 1; i < cell->bytes; ++i)
            {
                /* Get bits from next byte and shift them towards msb */
                *p |= *b << (RT_BITS_PER_BYTE - bit_offset);

                p = b;
                *b++ >>= bit_offset;
            }
        }
        else
        {
            /* Point to the msb */
            p += cell->bytes - 1;
        }

        /* Result fits in less bytes */
        extra = cell->bytes - RT_DIV_ROUND_UP(cell->nbits, RT_BITS_PER_BYTE);
        while (--extra >= 0)
        {
            *p-- = 0;
        }

        /* Clear msb bits if any leftover in the last byte */
        if (cell->nbits % RT_BITS_PER_BYTE)
        {
            *p &= RT_GENMASK((cell->nbits % RT_BITS_PER_BYTE) - 1, 0);
        }
    }

    return res;
}

rt_ssize_t rt_nvmem_cell_write(struct rt_nvmem_cell *cell, void *buffer,
        rt_size_t len)
{
    rt_ssize_t res = 0;
    struct rt_nvmem_device *nvmem;

    if (!cell || !buffer || !len)
    {
        return -RT_EINVAL;
    }

    nvmem = cell->nvmem;

    if (len > nvmem->size || len > cell->bytes)
    {
        return -RT_EINVAL;
    }

    if (!nvmem->reg_write)
    {
        return -RT_ENOSYS;
    }

    if (cell->bit_offset || cell->nbits)
    {
        /* Shift buffer */
        int nbits, bit_offset = cell->bit_offset;
        rt_uint8_t v, *p, *buf, *b, pbyte, pbits;

        nbits = cell->nbits;
        buf = rt_calloc(1, cell->bytes);

        if (!buf)
        {
            return -RT_ENOMEM;
        }

        rt_memcpy(buf, buffer, len);
        p = b = buf;

        if (bit_offset)
        {
            pbyte = *b;
            *b <<= bit_offset;

            /* Setup the first byte with lsb bits from nvmem */
            if ((res = nvmem->reg_read(nvmem, cell->offset, &v, 1)) < 0)
            {
                goto _end;
            }
            *b++ |= RT_GENMASK(bit_offset - 1, 0) & v;

            /* Setup rest of the byte if any */
            for (int i = 1; i < cell->bytes; ++i)
            {
                /* Get last byte bits and shift them towards lsb */
                pbits = pbyte >> (RT_BITS_PER_BYTE - 1 - bit_offset);
                pbyte = *b;
                p = b;
                *b <<= bit_offset;
                *b++ |= pbits;
            }
        }

        /* If it's not end on byte boundary */
        if ((nbits + bit_offset) % RT_BITS_PER_BYTE)
        {
            /* Setup the last byte with msb bits from nvmem */
            if ((res = nvmem->reg_read(nvmem, cell->offset + cell->bytes - 1, &v, 1)) < 0)
            {
                goto _end;
            }

            *p |= RT_GENMASK(7, (nbits + bit_offset) % RT_BITS_PER_BYTE) & v;
        }

        buffer = buf;

    _end:
        if (res < 0)
        {
            rt_free(buf);
            return res;
        }
    }

    if (nvmem->wp_pin >= 0)
    {
        rt_pin_write(nvmem->wp_pin, !nvmem->wp_pin_active);
    }

    res = nvmem->reg_write(nvmem, cell->offset, buffer, len);

    if (nvmem->wp_pin >= 0)
    {
        rt_pin_write(nvmem->wp_pin, nvmem->wp_pin_active);
    }

    if (cell->bit_offset || cell->nbits)
    {
        rt_free(buffer);
    }

    return res;
}

rt_ssize_t rt_nvmem_cell_read_u8(struct rt_nvmem_cell *cell, rt_uint8_t *out_val)
{
    return rt_nvmem_cell_read(cell, out_val, sizeof(*out_val));
}

rt_ssize_t rt_nvmem_cell_read_u16(struct rt_nvmem_cell *cell, rt_uint16_t *out_val)
{
    return rt_nvmem_cell_read(cell, out_val, sizeof(*out_val));
}

rt_ssize_t rt_nvmem_cell_read_u32(struct rt_nvmem_cell *cell, rt_uint32_t *out_val)
{
    return rt_nvmem_cell_read(cell, out_val, sizeof(*out_val));
}

rt_ssize_t rt_nvmem_cell_read_u64(struct rt_nvmem_cell *cell, rt_uint64_t *out_val)
{
    return rt_nvmem_cell_read(cell, out_val, sizeof(*out_val));
}

static struct rt_nvmem_cell *ofw_nvmem_get_cell(struct rt_ofw_node *np,
        int index, const char *const_id)
{
    rt_ubase_t level;
    rt_ssize_t length;
    const fdt32_t *addr;
    struct rt_nvmem_device *nvmem;
    struct rt_nvmem_cell *cell, *cell_tmp;
    struct rt_ofw_cell_args cell_args;
    struct rt_ofw_node *cell_np = RT_NULL, *nvmem_np = RT_NULL;

    if (rt_ofw_parse_phandle_cells(np,
            "nvmem-cells", "#nvmem-cell-cells", index, &cell_args))
    {
        return RT_NULL;
    }

    cell_np = cell_args.data;
    index = cell_args.args_count ? cell_args.args[0] : 0;

    if (!cell_np)
    {
        cell = rt_err_ptr(-RT_ERROR);
        goto _put_node;
    }

    /* 1.find in ofw node */
    if (!rt_ofw_data(cell_np))
    {
        rt_platform_ofw_request(cell_np);
    }

    cell = rt_ofw_data(cell_np);

    if (cell && rt_ref_read(&cell->ref) > 0)
    {
        rt_ref_get(&cell->ref);
        goto _put_node;
    }

    cell = rt_err_ptr(-RT_ERROR);
    nvmem_np = rt_ofw_get_parent(cell_np);

    if (!nvmem_np)
    {
        goto _put_node;
    }

    nvmem = rt_ofw_data(nvmem_np);

    if (!nvmem)
    {
        goto _put_node;
    }

    level = rt_spin_lock_irqsave(&nvmem->spinlock);

    /* 2.find in const node */
    rt_list_for_each_entry(cell_tmp, &nvmem->cell_nodes, list)
    {
        if (cell_tmp->index == index)
        {
            if (const_id && cell_tmp->id && rt_strcmp(const_id, cell_tmp->id))
            {
                continue;
            }

            cell = cell_tmp;

            if (rt_ref_read(&cell->ref))
            {
                rt_ref_get(&cell->ref);
            }
            else
            {
                cell = RT_NULL;
            }

            break;
        }
    }

    rt_spin_unlock_irqrestore(&nvmem->spinlock, level);

    if (!rt_is_err_or_null(cell))
    {
        goto _put_node;
    }

    /* 3.create a new one */
    cell = rt_calloc(1, sizeof(*cell));

    if (!cell)
    {
        cell = rt_err_ptr(-RT_ENOMEM);
        LOG_E("No memory to create cell: %s (%d)", const_id, index);
        goto _put_node;
    }

    cell->index = index;
    cell->id = const_id;

    *(rt_bool_t *)&cell->free_able = RT_TRUE;

    addr = rt_ofw_prop_read_raw(cell_np, "reg", &length);
    if (!addr || length < 2 * sizeof(rt_uint32_t))
    {
        LOG_E("%s Invalid reg", rt_ofw_node_full_name(cell_np));
        goto _fail;
    }

    cell->offset = fdt32_to_cpu(*addr++);
    cell->bytes = fdt32_to_cpu(*addr);

    addr = rt_ofw_prop_read_raw(cell_np, "reg", &length);
    if (addr && length == 2 * sizeof(rt_uint32_t))
    {
        cell->bit_offset = fdt32_to_cpu(*addr++);
        cell->nbits = fdt32_to_cpu(*addr);
    }

    /* user ref is '1' */
    rt_ref_init(&cell->ref);

    cell->np = cell_np;
    cell->nvmem = nvmem;

    rt_nvmem_device_append_cell(nvmem, cell);

    rt_ofw_node_get(cell_np);
    rt_ofw_data(cell_np) = cell;

    goto _put_node;

_fail:
    rt_free(cell);
    cell = rt_err_ptr(-RT_EINVAL);

_put_node:
    rt_ofw_node_put(cell_np);
    rt_ofw_node_put(nvmem_np);

    return cell;
}

struct rt_nvmem_cell *rt_nvmem_get_cell_by_index(struct rt_device *dev,
        int index)
{
    if (!dev || index < 0)
    {
        return RT_NULL;
    }

    if (dev->ofw_node)
    {
        return ofw_nvmem_get_cell(dev->ofw_node, index, RT_NULL);
    }

    return rt_err_ptr(-RT_ENOSYS);
}

struct rt_nvmem_cell *rt_nvmem_get_cell_by_name(struct rt_device *dev,
        const char *id)
{
    struct rt_ofw_node *np;

    if (!dev || !id)
    {
        return RT_NULL;
    }

    np = dev->ofw_node;

    if (np)
    {
        int index = 0;
        const char *const_id;
        struct rt_ofw_prop *prop;

        rt_ofw_foreach_prop_string(np, "nvmem-cell-names", prop, const_id)
        {
            if (!rt_strcmp(id, const_id))
            {
                return ofw_nvmem_get_cell(np, index, const_id);
            }

            ++index;
        }
    }

    return rt_err_ptr(-RT_ENOSYS);
}

static void nvmem_release(struct rt_ref *r)
{
    struct rt_nvmem_device *ndev = rt_container_of(r, struct rt_nvmem_device, ref);

    if (ndev->parent.ofw_node)
    {
        LOG_E("%s device is release", rt_ofw_node_full_name(ndev->parent.ofw_node));
    }

    RT_ASSERT(0);
}

static void cell_release(struct rt_ref *r)
{
    rt_ubase_t level;
    struct rt_nvmem_cell *cell = rt_container_of(r, struct rt_nvmem_cell, ref);
    struct rt_nvmem_device *nvmem = cell->nvmem;

    if (!cell->free_able)
    {
        /* only freeable cells can enter */
        LOG_E("%s cell is release", cell->id);
        RT_ASSERT(0);
    }

    if (cell->np)
    {
        rt_ofw_data(cell->np) = RT_NULL;
        rt_ofw_node_put(cell->np);
    }

    level = rt_spin_lock_irqsave(&nvmem->spinlock);
    rt_list_remove(&cell->list);
    --nvmem->cells_nr;
    rt_spin_unlock_irqrestore(&nvmem->spinlock, level);

    rt_ref_put(&nvmem->ref, &nvmem_release);

    rt_free(cell);
}

void rt_nvmem_put_cell(struct rt_nvmem_cell *cell)
{
    if (!cell)
    {
        return;
    }

    rt_ref_put(&cell->ref, &cell_release);
}
