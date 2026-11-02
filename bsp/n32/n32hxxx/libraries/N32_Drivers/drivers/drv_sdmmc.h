/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-07-10     Claude       N32 SDMMC driver with rt_mmcsd_host_ops
 */

#ifndef __DRV_SDMMC_H__
#define __DRV_SDMMC_H__

#include <rtthread.h>
#include "n32h7xx_sdmmc.h"         /* BEFORE mmcsd_cmd.h — avoids SWITCH macro clash */
#include <drivers/mmcsd_host.h>
#include <drivers/mmcsd_cmd.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ── SDMMC clock frequencies ─────────────────────────────────────────── */
#define SD_XIN_CLK           100000000U   /* SDMMC module base clock (Hz) */
#define SD_INIT_FREQ         400000U      /* Identification mode: 400 kHz */
#define SD_NORMAL_SPEED_FREQ 25000000U    /* Default speed: 25 MHz       */
#define SD_HIGH_SPEED_FREQ   50000000U    /* High speed: 50 MHz          */

#ifndef SDIO_MAX_FREQ
#define SDIO_MAX_FREQ SD_HIGH_SPEED_FREQ
#endif

/* ── Data buffer ─────────────────────────────────────────────────────── */
#ifndef SDIO_BUFF_SIZE
#define SDIO_BUFF_SIZE 4096
#endif

#ifndef SDIO_ALIGN_LEN
#define SDIO_ALIGN_LEN 32
#endif

/* ── N32 per-instance descriptor ─────────────────────────────────────── */
struct n32_sdio_config
{
    SDHOST_Module *sdhost;        /* SDHOST register base        */
    SDMMC_Module *sdmmc;         /* SDMMC wrapper register base */
    IRQn_Type irqn;          /* IRQ number                  */
    uint32_t clkfb_val;     /* AFIO clock feedback select  */
    uint32_t pwrctrl_val;   /* PWR power control bit       */
    uint32_t lpclk_en;      /* RCC LP clock enable bit     */
    uint32_t periphrst_val; /* RCC peripheral reset mask   */
    const char *name;          /* device name ("sd0")         */
};

struct n32_sdio
{
    struct n32_sdio_config cfg;
    struct rt_mmcsd_host *host;
};

/* ── Public API ──────────────────────────────────────────────────────── */
int n32_hw_sdio_init(void);

#ifdef __cplusplus
}
#endif

#endif /* __DRV_SDMMC_H__ */
