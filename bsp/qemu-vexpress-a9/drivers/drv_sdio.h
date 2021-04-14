/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020/12/31     Bernard      Add license info
 */
#ifndef __DRV_SDIO_H__
#define __DRV_SDIO_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <rtthread.h>

struct sdhci_cmd_t
{
    rt_uint32_t cmdidx;
    rt_uint32_t cmdarg;
    rt_uint32_t resptype;
    rt_uint32_t response[4];
};

struct sdhci_data_t
{
    rt_uint8_t * buf;
    rt_uint32_t flag;
    rt_uint32_t blksz;
    rt_uint32_t blkcnt;
};

struct sdhci_t
{
    char * name;
    rt_uint32_t voltages;
    rt_uint32_t width;
    rt_uint32_t clock;
    rt_err_t removeable;
    void * sdcard;

    rt_err_t (*detect)(struct sdhci_t * sdhci);
    rt_err_t (*setwidth)(struct sdhci_t * sdhci, rt_uint32_t width);
    rt_err_t (*setclock)(struct sdhci_t * sdhci, rt_uint32_t clock);
    rt_err_t (*transfer)(struct sdhci_t * sdhci, struct sdhci_cmd_t * cmd, struct sdhci_data_t * dat);
    void * priv;
};

#ifdef __cplusplus
}
#endif

#endif
