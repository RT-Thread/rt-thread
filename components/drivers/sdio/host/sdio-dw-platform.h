/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-12-06     GuEe-GUI     first version
 */

#ifndef __SDIO_DW_PLATFORM_H__
#define __SDIO_DW_PLATFORM_H__

#include "sdio-dw.h"

rt_err_t sdio_dw_platform_register(struct rt_platform_device *pdev,
        const struct sdio_dw_drv_data *drv_data);

#endif /* __SDIO_DW_PLATFORM_H__ */
