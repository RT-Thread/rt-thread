/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-05-23     liuduanfei   first version
 * 2020-08-25     wanghaijing  add sdmmmc2
 * 2023-03-26     wdfk-prog    Distinguish between SDMMC and SDIO drivers
 */

#ifndef __DRV_SDMMC_H__
#define __DRV_SDMMC_H__

#include <rtthread.h>
#include "rtdevice.h"
#include <rthw.h>
#include <drv_common.h>
#include <string.h>
#include <drivers/dev_mmcsd_core.h>
#include <drivers/dev_sdio.h>

#define SDIO_BUFF_SIZE       4096
#define SDIO_ALIGN_LEN       32

#define SDIO1_BASE_ADDRESS  (SDMMC1_BASE)
#define SDIO2_BASE_ADDRESS  (SDMMC2_BASE)

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

/* Frequencies used in the driver for clock divider calculation */
#define SD_INIT_FREQ                   400000U   /* Initalization phase : 400 kHz max */
#define SD_NORMAL_SPEED_FREQ           25000000U /* Normal speed phase : 25 MHz max */
#define SD_HIGH_SPEED_FREQ             50000000U /* High speed phase : 50 MHz max */

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

typedef rt_uint32_t (*sdio_clk_get)(void);

struct stm32_sdio_des
{
    SD_HandleTypeDef hw_sdio;
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

#endif /* __DRV_SDMMC_H__ */
