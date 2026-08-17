/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-26     GuEe-GUI     first version
 */

#ifndef __DWMAC_PLATFORM_H__
#define __DWMAC_PLATFORM_H__

#include "dwmac.h"

rt_err_t dwmac_platform_register(struct rt_platform_device *pdev,
        const struct dwmac_config *config);
rt_err_t dwmac_platform_remove(struct rt_platform_device *pdev);

#endif /* __DWMAC_PLATFORM_H__ */
