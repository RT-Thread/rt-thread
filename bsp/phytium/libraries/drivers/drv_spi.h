/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Email: opensource_embedded@phytium.com.cn
 *
 * Change Logs:
 * Date        Author       Notes
 * 2022-11-10  liqiaozhong  first commit
 * 2023-03-08  liqiaozhong  support 4 spis and qspi working together
 */
#ifndef __DRV_SPI_H__
#define __DRV_SPI_H__

#include <rtthread.h>

struct drv_spi
{
    u32 spi_id;
    FSpim spim_instance;
    struct rt_spi_device device;
};


#endif


