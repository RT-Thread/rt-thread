/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-07-16     thread-liu   first version
 */

#ifndef __DRV_EMMC_H__
#define __DRV_EMMC_H__

#include <rtthread.h>
#include "rtdevice.h"
#include <rthw.h>
#include <drv_common.h>
#include <string.h>
#include <drivers/dev_mmcsd_core.h>
#include <drivers/dev_sdio.h>

#define SDIO_BUFF_SIZE       4096

#ifndef EMMC_BASE_ADDRESS
#define EMMC_BASE_ADDRESS    (SDMMC2)
#endif

#ifndef EMMC_CLOCK_FREQ
#define EMMC_CLOCK_FREQ      (99U * 1000 * 1000)
#endif

#ifndef EMMC_MAX_FREQ
#define EMMC_MAX_FREQ        (50 * 1000 * 1000)
#endif

#define DIV_ROUND_UP(n,d) (((n) + (d) - 1) / (d))

#define SDMMC_ERRORS \
    (SDMMC_STA_IDMATE | SDMMC_STA_ACKTIMEOUT | \
     SDMMC_STA_RXOVERR | SDMMC_STA_TXUNDERR | \
     SDMMC_STA_DTIMEOUT | SDMMC_STA_CTIMEOUT | \
     SDMMC_STA_DCRCFAIL | SDMMC_STA_CCRCFAIL)

#define SDIO_MASKR_ALL \
    (SDMMC_MASK_CCRCFAILIE | SDMMC_MASK_DCRCFAILIE | SDMMC_MASK_CTIMEOUTIE | \
     SDMMC_MASK_TXUNDERRIE | SDMMC_MASK_RXOVERRIE | SDMMC_MASK_CMDRENDIE | \
     SDMMC_MASK_CMDSENTIE | SDMMC_MASK_DATAENDIE | SDMMC_MASK_ACKTIMEOUTIE)

#define HW_SDIO_DATATIMEOUT                 (0xFFFFFFFFU)

struct stm32_sdio
{
    volatile rt_uint32_t power;         /* offset 0x00 */
    volatile rt_uint32_t clkcr;         /* offset 0x04 */
    volatile rt_uint32_t arg;           /* offset 0x08 */
    volatile rt_uint32_t cmd;           /* offset 0x0C */
    volatile rt_uint32_t respcmd;       /* offset 0x10 */
    volatile rt_uint32_t resp1;         /* offset 0x14 */
    volatile rt_uint32_t resp2;         /* offset 0x18 */
    volatile rt_uint32_t resp3;         /* offset 0x1C */
    volatile rt_uint32_t resp4;         /* offset 0x20 */
    volatile rt_uint32_t dtimer;        /* offset 0x24 */
    volatile rt_uint32_t dlen;          /* offset 0x28 */
    volatile rt_uint32_t dctrl;         /* offset 0x2C */
    volatile rt_uint32_t dcount;        /* offset 0x30 */
    volatile rt_uint32_t sta;           /* offset 0x34 */
    volatile rt_uint32_t icr;           /* offset 0x38 */
    volatile rt_uint32_t mask;          /* offset 0x3C */
    volatile rt_uint32_t acktimer;      /* offset 0x40 */
    volatile rt_uint32_t reserved0[3];  /* offset 0x44 ~ 0x4C */
    volatile rt_uint32_t idmatrlr;      /* offset 0x50 */
    volatile rt_uint32_t idmabsizer;    /* offset 0x54 */
    volatile rt_uint32_t idmabase0r;    /* offset 0x58 */
    volatile rt_uint32_t idmabase1r;    /* offset 0x5C */
    volatile rt_uint32_t reserved1[1];  /* offset 0x60 */
    volatile rt_uint32_t idmalar;
    volatile rt_uint32_t idmabar;
    volatile rt_uint32_t reserved2[5];
    volatile rt_uint32_t fifo;
    volatile rt_uint32_t reserved3[220];
    volatile rt_uint32_t verr;
    volatile rt_uint32_t ipidr;
    volatile rt_uint32_t sidr;
};

typedef rt_uint32_t (*sdio_clk_get)(struct stm32_sdio *hw_sdio);

struct stm32_sdio_des
{
    struct stm32_sdio *hw_sdio;
    sdio_clk_get clk_get;
};

/* stm32 sdio dirver class */
struct stm32_sdio_class
{
    struct stm32_sdio_des *des;
    const struct stm32_sdio_config *cfg;
    struct rt_mmcsd_host host;
};

extern void stm32_mmcsd_change(void);

#endif /* __DRV_SDIO_H__ */
