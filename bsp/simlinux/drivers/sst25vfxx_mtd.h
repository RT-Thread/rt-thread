/*
 * File      : sst25vfxx_mtd.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2011, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-12-16     aozima       the first version
 * 2012-02-01     mbbill       MTD driver version
 */

#ifndef SST25VFXX_MTD_H
#define SST25VFXX_MTD_H

#include <rtthread.h>
#include <drivers/spi.h>

rt_err_t sst25vfxx_mtd_init(const char *spi_device_name, rt_uint32_t block_start, rt_uint32_t block_end);

#endif
