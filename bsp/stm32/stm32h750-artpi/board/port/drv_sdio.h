/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-05-23     liuduanfei   first version
 * 2020-08-25     wanghaijing  add sdmmmc2
 */

#ifndef __DRV_SDIO_H__
#define __DRV_SDIO_H__

#include <rtthread.h>
#include "rtdevice.h"
#include <rthw.h>
#include <drv_common.h>
#include <string.h>
#include <drivers/mmcsd_core.h>
#include <drivers/sdio.h>

#define SDIO_BUFF_SIZE       4096
#define SDIO_ALIGN_LEN       32

#ifndef SDIO1_BASE_ADDRESS
#define SDIO1_BASE_ADDRESS    (0x52007000)
#endif

#ifndef SDIO2_BASE_ADDRESS
#define SDIO2_BASE_ADDRESS    (0x48022400)
#endif

#ifndef SDIO_CLOCK_FREQ
#define SDIO_CLOCK_FREQ      (200U * 1000 * 1000)
#endif

#ifndef SDIO_BUFF_SIZE
#define SDIO_BUFF_SIZE       (4096)
#endif

#ifndef SDIO_ALIGN_LEN
#define SDIO_ALIGN_LEN       (32)
#endif

#ifndef SDIO_MAX_FREQ
#define SDIO_MAX_FREQ        (25 * 1000 * 1000)
#endif

#define DIV_ROUND_UP(n,d) (((n) + (d) - 1) / (d))

#define SDIO_ERRORS \
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
    volatile rt_uint32_t reserved1[8];  /* offset 0x60 ~ 7C */
    volatile rt_uint32_t fifo;          /* offset 0x80 */
};

typedef rt_uint32_t (*sdio_clk_get)(struct stm32_sdio *hw_sdio);

struct stm32_sdio_des
{
    struct stm32_sdio *hw_sdio;
    sdio_clk_get clk_get;
    SD_HandleTypeDef hsd;
};

/* stm32 sdio dirver class */
struct stm32_sdio_class
{
    struct stm32_sdio_des *des;
    const struct stm32_sdio_config *cfg;
    struct rt_mmcsd_host host;
};

extern void sdcard_change(void);

#endif /* __DRV_SDIO_H__ */
