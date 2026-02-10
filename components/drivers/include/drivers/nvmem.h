/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-25     GuEe-GUI     the first version
 */

#ifndef __NVMEM_H__
#define __NVMEM_H__

#include <ref.h>

#include <drivers/ofw.h>
#include <drivers/core/dm.h>
#include <drivers/core/driver.h>

struct rt_nvmem_device
{
    struct rt_device parent;

    int cells_nr;
    rt_list_t cell_nodes;

    rt_ssize_t (*reg_read)(struct rt_nvmem_device *, int offset, void *val, rt_size_t bytes);
    rt_ssize_t (*reg_write)(struct rt_nvmem_device *, int offset, void *val, rt_size_t bytes);

    rt_ssize_t size;
    int word_size;
    int stride;

    rt_bool_t read_only;
    rt_bool_t ignore_wp;
    rt_base_t wp_pin;
    rt_uint8_t wp_pin_active;

    struct rt_ref ref;
    struct rt_spinlock spinlock;

    void *priv;
};

struct rt_nvmem_cell
{
    rt_list_t list;

    int index;
    const char *id;
    const rt_bool_t free_able;

    rt_uint32_t offset;
    rt_uint32_t bytes;
    rt_uint32_t bit_offset;
    rt_uint32_t nbits;

    struct rt_ref ref;

    struct rt_ofw_node *np;
    struct rt_nvmem_device *nvmem;
};

rt_err_t rt_nvmem_device_register(struct rt_nvmem_device *ndev);
rt_err_t rt_nvmem_device_unregister(struct rt_nvmem_device *ndev);

rt_err_t rt_nvmem_device_append_cell(struct rt_nvmem_device *ndev, struct rt_nvmem_cell *cell);

rt_ssize_t rt_nvmem_cell_read(struct rt_nvmem_cell *cell, void *buffer, rt_size_t len);
rt_ssize_t rt_nvmem_cell_write(struct rt_nvmem_cell *cell, void *buffer, rt_size_t len);

rt_ssize_t rt_nvmem_cell_read_u8(struct rt_nvmem_cell *cell, rt_uint8_t *out_val);
rt_ssize_t rt_nvmem_cell_read_u16(struct rt_nvmem_cell *cell, rt_uint16_t *out_val);
rt_ssize_t rt_nvmem_cell_read_u32(struct rt_nvmem_cell *cell, rt_uint32_t *out_val);
rt_ssize_t rt_nvmem_cell_read_u64(struct rt_nvmem_cell *cell, rt_uint64_t *out_val);

struct rt_nvmem_cell *rt_nvmem_get_cell_by_index(struct rt_device *dev, int index);
struct rt_nvmem_cell *rt_nvmem_get_cell_by_name(struct rt_device *dev, const char *id);
void rt_nvmem_put_cell(struct rt_nvmem_cell *cell);

#endif /* __NVMEM_H__ */
