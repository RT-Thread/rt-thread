/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-01-30     RT-Thread    first version
 */

#ifndef __SDHCI_DWCMSHC_PLATFORM_H__
#define __SDHCI_DWCMSHC_PLATFORM_H__

#include "sdhci-dwcmshc.h"

rt_err_t sdhci_dwcmshc_platform_register(struct rt_platform_device *pdev,
                                         const struct sdhci_dwcmshc_drv_data *drv_data);

#endif /* __SDHCI_DWCMSHC_PLATFORM_H__ */
