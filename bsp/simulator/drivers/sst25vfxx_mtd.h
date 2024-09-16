/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-12-16     aozima       the first version
 * 2012-02-01     mbbill       MTD driver version
 */

#ifndef SST25VFXX_MTD_H
#define SST25VFXX_MTD_H

#include <rtthread.h>
#include "drivers/dev_spi.h"

rt_err_t sst25vfxx_mtd_init(const char *spi_device_name, rt_uint32_t block_start, rt_uint32_t block_end);

#endif
