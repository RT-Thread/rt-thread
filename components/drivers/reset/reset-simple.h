/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-26     GuEe-GUI     first version
 */

#ifndef __RESET_SIMPLE_H__
#define __RESET_SIMPLE_H__

#include <rtthread.h>
#include <rtdevice.h>

struct reset_simple
{
    struct rt_reset_controller parent;

    void *mmio_base;

    /*
     * If true, bits are cleared to assert the reset.
     * Otherwise, bits are set to assert the reset.
     */
    rt_bool_t active_low;
    /*
     * If true, bits read back as cleared while the reset is asserted.
     * Otherwise, bits read back as set while the reset is asserted.
     */
    rt_bool_t status_active_low;

    /*
     * Minimum delay in microseconds needed that needs to be
     * waited for between an assert and a deassert to reset the device.
     * If multiple consumers with different delay
     * requirements are connected to this controller, it must
     * be the largest minimum delay. 0 means that such a delay is
     * unknown and the reset operation is unsupported.
     */
    rt_uint32_t reset_us;

    /* protect registers during read-modify-write cycles */
    struct rt_spinlock lock;
};

extern const struct rt_reset_control_ops reset_simple_ops;

#endif /* __RESET_SIMPLE_H__ */
