/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-10-24     GuEe-GUI     first version
 */

#ifndef __PHYE_H__
#define __PHYE_H__

#include <rtthread.h>
#include <drivers/ofw.h>

enum rt_phye_mode
{
    RT_PHYE_MODE_INVALID,
    RT_PHYE_MODE_USB_HOST,
    RT_PHYE_MODE_USB_HOST_LS,
    RT_PHYE_MODE_USB_HOST_FS,
    RT_PHYE_MODE_USB_HOST_HS,
    RT_PHYE_MODE_USB_HOST_SS,
    RT_PHYE_MODE_USB_DEVICE,
    RT_PHYE_MODE_USB_DEVICE_LS,
    RT_PHYE_MODE_USB_DEVICE_FS,
    RT_PHYE_MODE_USB_DEVICE_HS,
    RT_PHYE_MODE_USB_DEVICE_SS,
    RT_PHYE_MODE_USB_OTG,
    RT_PHYE_MODE_UFS_HS_A,
    RT_PHYE_MODE_UFS_HS_B,
    RT_PHYE_MODE_PCIE,
    RT_PHYE_MODE_ETHERNET,
    RT_PHYE_MODE_MIPI_DPHY,
    RT_PHYE_MODE_SATA,
    RT_PHYE_MODE_LVDS,
    RT_PHYE_MODE_DP,

    RT_PHYE_MODE_MAX,

    /* PCIe */
    RT_PHYE_MODE_PCIE_RC = RT_PHYE_MODE_MAX,
    RT_PHYE_MODE_PCIE_EP,
    RT_PHYE_MODE_PCIE_BIFURCATION,
};

struct rt_phye_ops;

struct rt_phye
{
    struct rt_device *dev;

    const struct rt_phye_ops *ops;

    int init_count;
    int power_count;
    struct rt_spinlock lock;
};

struct rt_phye_ops
{
    rt_err_t (*init)(struct rt_phye *phye);
    rt_err_t (*exit)(struct rt_phye *phye);
    rt_err_t (*reset)(struct rt_phye *phye);
    rt_err_t (*power_on)(struct rt_phye *phye);
    rt_err_t (*power_off)(struct rt_phye *phye);
    rt_err_t (*set_mode)(struct rt_phye *phye, enum rt_phye_mode mode, int submode);
    rt_err_t (*ofw_parse)(struct rt_phye *phye, struct rt_ofw_cell_args *phye_args);
};

rt_err_t rt_phye_register(struct rt_phye *phye);
rt_err_t rt_phye_unregister(struct rt_phye *phye);

rt_err_t rt_phye_init(struct rt_phye *phye);
rt_err_t rt_phye_exit(struct rt_phye *phye);
rt_err_t rt_phye_reset(struct rt_phye *phye);
rt_err_t rt_phye_power_on(struct rt_phye *phye);
rt_err_t rt_phye_power_off(struct rt_phye *phye);
rt_err_t rt_phye_set_mode(struct rt_phye *phye, enum rt_phye_mode mode, int submode);

rt_inline rt_err_t rt_phye_set_mode_simple(struct rt_phye *phye, enum rt_phye_mode mode)
{
    return rt_phye_set_mode(phye, mode, RT_PHYE_MODE_INVALID);
}

struct rt_phye *rt_phye_get_by_index(struct rt_device *dev, int index);
struct rt_phye *rt_phye_get_by_name(struct rt_device *dev, const char *id);
void rt_phye_put(struct rt_phye *phye);

#endif /* __PHYE_H__ */
