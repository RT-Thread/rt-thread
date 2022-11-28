/*
 * Copyright 2018 Rockchip Electronics Co., Ltd
 *
 */
#include <stdio.h>
#include <hal_osal.h>
#include <barrier.h>
#include "sunxi_hal_common.h"
#include "platform_watchdog.h"

#define writel_wdt  hal_writel
#define readl_wdt   hal_readl

static unsigned long running;
static unsigned long running_saved;

static const int wdt_timeout_map[] =
{
    [1]  = 0x1,  /* 1s  32000cycles*/
    [2]  = 0x2,  /* 2s  64000*/
    [3]  = 0x3,  /* 3s  96000*/
    [4]  = 0x4,  /* 4s  128000*/
    [5]  = 0x5,  /* 5s  160000*/
    [6]  = 0x6,  /* 6s  192000*/
    [8]  = 0x7,  /* 8s  256000*/
    [10] = 0x8,  /* 10s 320000*/
    [12] = 0x9,  /* 12s 384000*/
    [14] = 0xA,  /* 14s 448000*/
    [16] = 0xB,  /* 16s 512000*/
};

int hal_watchdog_is_running(void)
{

    return running_saved;
}

int hal_watchdog_suspend(int timeout)
{

    running_saved = running;

    pr_debug("%s()\n", __func__);
    if (hal_watchdog_is_running()) {
        pr_debug("%s()\n", __func__);
        hal_watchdog_stop(timeout);
    }

    return 0;
}

int hal_watchdog_resume(int timeout)
{

    pr_debug("%s()\n", __func__);
    if (hal_watchdog_is_running()) {
        pr_debug("%s()\n", __func__);
        hal_watchdog_start(timeout);
    }

    return 0;
}
void hal_watchdog_info(void)
{
    struct hal_sunxi_wdt *wdt = (struct hal_sunxi_wdt *)WDT_BASE;
    printf("mode: 0x%x, cfg=0x%x, ctl=0x%x\n",
    (unsigned int)(wdt->mode), (unsigned int)(wdt->cfg), (unsigned int)(wdt->ctl));
}

void hal_watchdog_disable(void)
{
    struct hal_sunxi_wdt *wdt = (struct hal_sunxi_wdt *)WDT_BASE;
    unsigned int wtmode;

    pr_debug("%s()\n", __func__);
    wtmode = readl_wdt(&wdt->mode);
    wtmode &= ~WDT_MODE_EN;
    wtmode |= KEY_FIELD_MAGIC;

    writel_wdt(wtmode, &wdt->mode);
    isb();
    running = 0;
}

void hal_watchdog_reset(int timeout)
{
    int timeout_set = timeout;
    struct hal_sunxi_wdt *wdt = (struct hal_sunxi_wdt *)WDT_BASE;
    unsigned int wtmode;

    pr_debug("%s()\n", __func__);
    hal_watchdog_disable();

    if (timeout > 16)
    {
        timeout_set = 16;
    }

    if (wdt_timeout_map[timeout_set] == 0)
    {
        timeout_set++;
    }

    wtmode = KEY_FIELD_MAGIC | (wdt_timeout_map[timeout_set] << 4) | WDT_MODE_EN;

    writel_wdt(KEY_FIELD_MAGIC | WDT_CFG_RESET, &wdt->cfg);
    writel_wdt(wtmode, &wdt->mode);

    isb();
    writel_wdt(WDT_CTRL_KEY | WDT_CTRL_RESTART, &wdt->ctl);
    running = 1;
}

void hal_watchdog_restart(void)
{
    struct hal_sunxi_wdt *wdt = (struct hal_sunxi_wdt *)WDT_BASE;

    pr_debug("%s()\n", __func__);
    hal_watchdog_disable();

    /* add delay for watchdog disable */
    udelay(50);
    /* Set the watchdog for its shortest interval (.5s) and wait */
    writel_wdt(KEY_FIELD_MAGIC | WDT_CFG_RESET, &wdt->cfg);
    isb();
    writel_wdt(KEY_FIELD_MAGIC | WDT_MODE_EN, &wdt->mode);

    while (1) {};
}

void hal_watchdog_init(void)
{
    pr_debug("%s()\n", __func__);
    running = 0;
    running_saved = 0;
}

void hal_watchdog_stop(int timeout)
{
    pr_debug("%s()\n", __func__);
    hal_watchdog_disable();
}

void hal_watchdog_start(int timeout)
{
    pr_debug("%s()\n", __func__);
    hal_watchdog_reset(timeout);
}

void hal_watchdog_feed(void)
{
    struct hal_sunxi_wdt *wdt = (struct hal_sunxi_wdt *)WDT_BASE;
    pr_debug("%s()\n", __func__);
    writel_wdt(WDT_CTRL_KEY | WDT_CTRL_RESTART, &wdt->ctl);
}
