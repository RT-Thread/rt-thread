/*
 * Copyright (C) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-08     CDT          first version
 * 2023-12-01     CDT          added swdt support
 */

#include "board.h"

#ifdef BSP_USING_WDT_TMR
#include <math.h>
#include <string.h>

// #define DRV_DEBUG
#define LOG_TAG             "drv_wdt"
#include <drv_log.h>

enum
{
    WDT_INIT_ING,
    WDT_INIT_OVER,
    WDT_IS_ENABLE
};
static struct rt_watchdog_ops _ops;

#ifdef BSP_USING_WDT
struct hc32_wdt_obj
{
    rt_watchdog_t watchdog;
    stc_wdt_init_t stcwdg;
    rt_uint32_t pclk3;
    rt_uint8_t sta;
    rt_uint8_t index;
};
static struct hc32_wdt_obj hc32_wdt;

struct time_match
{
    uint32_t u32ClockDiv;
    uint32_t u32CountPeriod;
    float timeout_s;
};

static uint32_t const Div[] = {4U, 64U, 128U, 256U, 512U, 1024U, 2048U, 8192U};
static uint32_t const Peri[] = {256U, 4096U, 16384U, 65536U};
static struct time_match wdt_match[(sizeof(Div) / sizeof(Div[0])) * (sizeof(Peri) / sizeof(Peri[0]))];

static void wdt_match_init(uint32_t clock)
{
    int i, j;
    for (i = 0; i < (sizeof(Div) / sizeof(Div[0])); i++)
    {
        for (j = 0; j < (sizeof(Peri) / sizeof(Peri[0])); j++)
        {
            wdt_match[j + i * (sizeof(Peri) / sizeof(Peri[0]))].u32ClockDiv = Div[i];
            wdt_match[j + i * (sizeof(Peri) / sizeof(Peri[0]))].u32CountPeriod = Peri[j];
            wdt_match[j + i * (sizeof(Peri) / sizeof(Peri[0]))].timeout_s = (Div[i] * Peri[j]) / (float)clock;
        }
    }
}
static void wdt_match_sort(void)
{
    int i, j;
    struct time_match Temp;
    /* bubble sort */
    for (i = 0; i < ((sizeof(Div) / sizeof(Div[0])) * (sizeof(Peri) / sizeof(Peri[0])) - 1); i++)
    {
        for (j = 0; j < ((sizeof(Div) / sizeof(Div[0])) * (sizeof(Peri) / sizeof(Peri[0])) - i - 1); j++)
        {
            if (wdt_match[j].timeout_s > wdt_match[j + 1].timeout_s)
            {
                memcpy(&Temp, &wdt_match[j], sizeof(struct time_match));
                memcpy(&wdt_match[j], &wdt_match[j + 1], sizeof(struct time_match));
                memcpy(&wdt_match[j + 1], &Temp, sizeof(struct time_match));
            }
        }
    }
}
static int wdt_match_find_index(uint32_t time_out)
{
    int i;
    /* Min and Max case */
    if (time_out <= wdt_match[0].timeout_s)
    {
        return 0;
    }
    else if (time_out >= wdt_match[((sizeof(Div) / sizeof(Div[0])) * (sizeof(Peri) / sizeof(Peri[0]))) - 1].timeout_s)
    {
        return (((sizeof(Div) / sizeof(Div[0])) * (sizeof(Peri) / sizeof(Peri[0]))) - 1);
    }
    /* Other case */
    for (i = 1; i < (((sizeof(Div) / sizeof(Div[0])) * (sizeof(Peri) / sizeof(Peri[0]))) - 1); i++)
    {
        if (time_out >= wdt_match[i].timeout_s && time_out < wdt_match[i + 1].timeout_s)
        {
            /* Min difference */
            if (time_out - wdt_match[i].timeout_s < wdt_match[i + 1].timeout_s - time_out)
            {
                return i;
            }
            else
            {
                return (i + 1);
            }
        }
    }
    /* Not match case */
    return (((sizeof(Div) / sizeof(Div[0])) * (sizeof(Peri) / sizeof(Peri[0]))) - 1);
}

static rt_uint32_t wdt_match_find_period(rt_uint32_t Period)
{
    rt_uint32_t CountPeriod = 0U;
    switch (Period)
    {
    case 256U:
        CountPeriod = WDT_CNT_PERIOD256;
        break;
    case 4096U:
        CountPeriod = WDT_CNT_PERIOD4096;
        break;
    case 16384U:
        CountPeriod = WDT_CNT_PERIOD16384;
        break;
    case 65536U:
        CountPeriod = WDT_CNT_PERIOD65536;
        break;
    default:
        break;
    }
    return CountPeriod;
}

static rt_uint32_t wdt_get_timeout_s(void)
{
    /* timeout(s) = PERI * DIV / PCLK3 */
    return ((rt_uint32_t)(wdt_match[hc32_wdt.index].u32CountPeriod * wdt_match[hc32_wdt.index].u32ClockDiv / (float)hc32_wdt.pclk3));
}

static rt_uint32_t wdt_get_timeleft_s(void)
{
    /* wdt is down counter */
    return ((rt_uint32_t)(WDT_GetCountValue() * wdt_match[hc32_wdt.index].u32ClockDiv / (float)hc32_wdt.pclk3));
}

static rt_err_t _wdt_init(rt_watchdog_t *wdt)
{
    hc32_wdt.pclk3 = CLK_GetBusClockFreq(CLK_BUS_PCLK3);
    if (!hc32_wdt.pclk3)
    {
        LOG_E("pclk3 getbusclockfreq failed.");
        return -RT_ERROR;
    }
    wdt_match_init(hc32_wdt.pclk3);
    wdt_match_sort();
    hc32_wdt.stcwdg.u32RefreshRange  = WDT_RANGE_0TO100PCT;
#ifdef BSP_WDT_CONTINUE_COUNT
    hc32_wdt.stcwdg.u32LPMCount      = WDT_LPM_CNT_CONTINUE;
#else
    hc32_wdt.stcwdg.u32LPMCount      = WDT_LPM_CNT_STOP;
#endif
    hc32_wdt.stcwdg.u32ExceptionType = WDT_EXP_TYPE_RST;
    hc32_wdt.sta = WDT_INIT_ING;
    /* WDT_CR register only support write once,so can't call WDT_Init of ther */

    return RT_EOK;
}

static rt_err_t _wdt_control(rt_watchdog_t *wdt, int cmd, void *arg)
{
    switch (cmd)
    {
    /* feed the watchdog */
    case RT_DEVICE_CTRL_WDT_KEEPALIVE:
        /* Prevention of unexpected start-up when feed dog */
        if (hc32_wdt.sta == WDT_IS_ENABLE)
        {
            WDT_FeedDog();
        }
        break;
    /* set watchdog timeout */
    case RT_DEVICE_CTRL_WDT_SET_TIMEOUT:
        hc32_wdt.index = wdt_match_find_index((*((rt_uint32_t *)arg)));
        hc32_wdt.stcwdg.u32CountPeriod   = wdt_match_find_period(wdt_match[hc32_wdt.index].u32CountPeriod);
        hc32_wdt.stcwdg.u32ClockDiv      = ((uint32_t)log2(wdt_match[hc32_wdt.index].u32ClockDiv) << WDT_CR_CKS_POS);
        if (WDT_Init(&hc32_wdt.stcwdg) != LL_OK)
        {
            LOG_E("wdg set timeout failed.");
            return -RT_ERROR;
        }
        hc32_wdt.sta = WDT_INIT_OVER;
        LOG_D("wdg set timeout successful. timeout = %d s", wdt_get_timeout_s());
        break;
    case RT_DEVICE_CTRL_WDT_GET_TIMEOUT:
        (*((rt_uint32_t *)arg)) = wdt_get_timeout_s();
        break;
    case RT_DEVICE_CTRL_WDT_START:
        if (hc32_wdt.sta == WDT_INIT_ING)
        {
            LOG_E("please set the timeout values.");
            return -RT_ERROR;
        }
        /* First reload counter to start WDT */
        WDT_FeedDog();
        hc32_wdt.sta = WDT_IS_ENABLE;
        break;
    case RT_DEVICE_CTRL_WDT_GET_TIMELEFT:
        (*((rt_uint32_t *)arg)) = wdt_get_timeleft_s();
        break;
    default:
        LOG_W("This command is not supported.");
        return -RT_ERROR;
    }
    return RT_EOK;
}

int rt_wdt_init(void)
{
    _ops.init = &_wdt_init;
    _ops.control = &_wdt_control;
    hc32_wdt.watchdog.ops = &_ops;

    /* register watchdog device */
    if (rt_hw_watchdog_register(&hc32_wdt.watchdog, "wdt", RT_DEVICE_FLAG_DEACTIVATE, RT_NULL) != RT_EOK)
    {
        LOG_E("wdt device register failed.");
        return -RT_ERROR;
    }
    LOG_D("wdt device register success.");
    return RT_EOK;
}
INIT_BOARD_EXPORT(rt_wdt_init);

#else   /* BSP_USING_WDT */

struct hc32_swdt_obj
{
    rt_watchdog_t watchdog;
    stc_swdt_init_t stcwdg;
    rt_uint32_t swdtclk;
    rt_uint8_t sta;
    rt_uint8_t index;
};
static struct hc32_swdt_obj hc32_swdt;

struct time_match
{
    uint32_t u32ClockDiv;
    uint32_t u32CountPeriod;
    float timeout_s;
};

static uint32_t const Div[] = {1U, 16U, 32U, 64U, 128U, 256U, 2048U};
static uint32_t const Peri[] = {256U, 4096U, 16384U, 65536U};
static struct time_match swdt_match[(sizeof(Div) / sizeof(Div[0])) * (sizeof(Peri) / sizeof(Peri[0]))];

static void swdt_match_init(uint32_t clock)
{
    int i, j;
    for (i = 0; i < (sizeof(Div) / sizeof(Div[0])); i++)
    {
        for (j = 0; j < (sizeof(Peri) / sizeof(Peri[0])); j++)
        {
            swdt_match[j + i * (sizeof(Peri) / sizeof(Peri[0]))].u32ClockDiv = Div[i];
            swdt_match[j + i * (sizeof(Peri) / sizeof(Peri[0]))].u32CountPeriod = Peri[j];
            swdt_match[j + i * (sizeof(Peri) / sizeof(Peri[0]))].timeout_s = (Div[i] * Peri[j]) / (float)clock;
        }
    }
}
static void swdt_match_sort(void)
{
    int i, j;
    struct time_match Temp;
    /* bubble sort */
    for (i = 0; i < ((sizeof(Div) / sizeof(Div[0])) * (sizeof(Peri) / sizeof(Peri[0])) - 1); i++)
    {
        for (j = 0; j < ((sizeof(Div) / sizeof(Div[0])) * (sizeof(Peri) / sizeof(Peri[0])) - i - 1); j++)
        {
            if (swdt_match[j].timeout_s > swdt_match[j + 1].timeout_s)
            {
                memcpy(&Temp, &swdt_match[j], sizeof(struct time_match));
                memcpy(&swdt_match[j], &swdt_match[j + 1], sizeof(struct time_match));
                memcpy(&swdt_match[j + 1], &Temp, sizeof(struct time_match));
            }
        }
    }
}
static int swdt_match_find_index(uint32_t time_out)
{
    int i;
    /* Min and Max case */
    if (time_out <= swdt_match[0].timeout_s)
    {
        return 0;
    }
    else if (time_out >= swdt_match[((sizeof(Div) / sizeof(Div[0])) * (sizeof(Peri) / sizeof(Peri[0]))) - 1].timeout_s)
    {
        return (((sizeof(Div) / sizeof(Div[0])) * (sizeof(Peri) / sizeof(Peri[0]))) - 1);
    }
    /* Other case */
    for (i = 1; i < (((sizeof(Div) / sizeof(Div[0])) * (sizeof(Peri) / sizeof(Peri[0]))) - 1); i++)
    {
        if (time_out >= swdt_match[i].timeout_s && time_out < swdt_match[i + 1].timeout_s)
        {
            /* Min difference */
            if (time_out - swdt_match[i].timeout_s < swdt_match[i + 1].timeout_s - time_out)
            {
                return i;
            }
            else
            {
                return (i + 1);
            }
        }
    }
    /* Not match case */
    return (((sizeof(Div) / sizeof(Div[0])) * (sizeof(Peri) / sizeof(Peri[0]))) - 1);
}

static rt_uint32_t swdt_match_find_period(rt_uint32_t Period)
{
    rt_uint32_t CountPeriod = 0U;
    switch (Period)
    {
    case 256U:
        CountPeriod = SWDT_CNT_PERIOD256;
        break;
    case 4096U:
        CountPeriod = SWDT_CNT_PERIOD4096;
        break;
    case 16384U:
        CountPeriod = SWDT_CNT_PERIOD16384;
        break;
    case 65536U:
        CountPeriod = SWDT_CNT_PERIOD65536;
        break;
    default:
        break;
    }
    return CountPeriod;
}

static rt_uint32_t swdt_get_timeout_s(void)
{
    /* timeout(s) = PERI * DIV / SWDTCLK */
    return ((rt_uint32_t)(swdt_match[hc32_swdt.index].u32CountPeriod * swdt_match[hc32_swdt.index].u32ClockDiv / (float)hc32_swdt.swdtclk));
}

static rt_uint32_t swdt_get_timeleft_s(void)
{
    /* swdt is down counter */
    return ((rt_uint32_t)(SWDT_GetCountValue() * swdt_match[hc32_swdt.index].u32ClockDiv / (float)hc32_swdt.swdtclk));
}

static rt_err_t swdt_init(rt_watchdog_t *swdt)
{
    hc32_swdt.swdtclk = 10000U;
    swdt_match_init(hc32_swdt.swdtclk);
    swdt_match_sort();
    hc32_swdt.stcwdg.u32RefreshRange  = SWDT_RANGE_0TO100PCT;
#ifdef BSP_WDT_CONTINUE_COUNT
    hc32_swdt.stcwdg.u32LPMCount      = SWDT_LPM_CNT_CONTINUE;
#else
    hc32_swdt.stcwdg.u32LPMCount      = SWDT_LPM_CNT_STOP;
#endif
    hc32_swdt.stcwdg.u32ExceptionType = SWDT_EXP_TYPE_RST;
    hc32_swdt.sta = WDT_INIT_ING;
    /* SWDT_CR register only support write once,so can't call swdt_Init of ther */

    return RT_EOK;
}

static rt_err_t swdt_control(rt_watchdog_t *swdt, int cmd, void *arg)
{
    switch (cmd)
    {
    /* feed the watchdog */
    case RT_DEVICE_CTRL_WDT_KEEPALIVE:
        /* Prevention of unexpected start-up when feed dog */
        if (hc32_swdt.sta == WDT_IS_ENABLE)
        {
            SWDT_FeedDog();
        }
        break;
    /* set watchdog timeout */
    case RT_DEVICE_CTRL_WDT_SET_TIMEOUT:
        hc32_swdt.index = swdt_match_find_index((*((rt_uint32_t *)arg)));
        hc32_swdt.stcwdg.u32CountPeriod   = swdt_match_find_period(swdt_match[hc32_swdt.index].u32CountPeriod);
        hc32_swdt.stcwdg.u32ClockDiv      = ((uint32_t)log2(swdt_match[hc32_swdt.index].u32ClockDiv) << SWDT_CR_CKS_POS);
        if (SWDT_Init(&hc32_swdt.stcwdg) != LL_OK)
        {
            LOG_E("swdg set timeout failed.");
            return -RT_ERROR;
        }
        hc32_swdt.sta = WDT_INIT_OVER;
        LOG_D("swdg set timeout successful. timeout = %d s", swdt_get_timeout_s());
        break;
    case RT_DEVICE_CTRL_WDT_GET_TIMEOUT:
        (*((rt_uint32_t *)arg)) = swdt_get_timeout_s();
        break;
    case RT_DEVICE_CTRL_WDT_START:
        if (hc32_swdt.sta == WDT_INIT_ING)
        {
            LOG_E("please set the timeout values.");
            return -RT_ERROR;
        }
        /* First reload counter to start swdt */
        SWDT_FeedDog();
        hc32_swdt.sta = WDT_IS_ENABLE;
        break;
    case RT_DEVICE_CTRL_WDT_GET_TIMELEFT:
        (*((rt_uint32_t *)arg)) = swdt_get_timeleft_s();
        break;
    default:
        LOG_W("This command is not supported.");
        return -RT_ERROR;
    }
    return RT_EOK;
}

static int rt_hw_swdt_init(void)
{
    _ops.init = &swdt_init;
    _ops.control = &swdt_control;
    hc32_swdt.watchdog.ops = &_ops;

    /* register watchdog device */
    if (rt_hw_watchdog_register(&hc32_swdt.watchdog, "swdt", RT_DEVICE_FLAG_DEACTIVATE, RT_NULL) != RT_EOK)
    {
        LOG_E("swdt device register failed.");
        return -RT_ERROR;
    }
    LOG_D("swdt device register success.");
    return RT_EOK;
}
INIT_BOARD_EXPORT(rt_hw_swdt_init);

#endif  /* BSP_USING_SWDT */

#endif
