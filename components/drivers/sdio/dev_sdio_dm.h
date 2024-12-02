/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-12-06     GuEe-GUI     first version
 */

#ifndef __DEV_SDIO_DM_H__
#define __DEV_SDIO_DM_H__

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

int sdio_host_set_name(struct rt_mmcsd_host *host, char *out_devname);

#ifdef RT_USING_REGULATOR
rt_err_t sdio_regulator_set_ocr(struct rt_mmcsd_host *host,
        struct rt_regulator *supply, rt_uint16_t vdd_bit);
rt_err_t sdio_regulator_set_vqmmc(struct rt_mmcsd_host *host,
        struct rt_mmcsd_io_cfg *ios);
rt_err_t sdio_regulator_get_supply(struct rt_device *dev, struct rt_mmcsd_host *host);
rt_err_t sdio_regulator_enable_vqmmc(struct rt_mmcsd_host *host);
void sdio_regulator_disable_vqmmc(struct rt_mmcsd_host *host);
#endif /* RT_USING_REGULATOR */

#ifdef RT_USING_OFW
rt_err_t sdio_ofw_parse(struct rt_ofw_node *dev_np, struct rt_mmcsd_host *host);
#else
rt_inline rt_err_t sdio_ofw_parse(struct rt_ofw_node *dev_np, struct rt_mmcsd_host *host)
{
    return RT_EOK;
}
#endif /* RT_USING_OFW */

#endif /* __DEV_SDIO_DM_H__ */
