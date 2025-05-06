/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2024/03/02     ShichengChu    first version
 */
#include <rtthread.h>
#include <rtdevice.h>
#include "drv_wdt.h"
#include "drv_ioremap.h"

#define DBG_LEVEL   DBG_LOG
#include <rtdbg.h>
#define LOG_TAG "DRV.WDT"

#define WDT_FREQ_DEFAULT 25000000UL
#define CVI_WDT_MAX_TOP     15

rt_inline void cvi_wdt_top_setting()
{
    uint32_t val;
    rt_ubase_t base = (rt_ubase_t)DRV_IOREMAP((void *)(CV_TOP + CV_TOP_WDT_OFFSET), 0x1000);

    mmio_write_32(base, CV_TOP_WDT_VAL);

    base = (rt_ubase_t)DRV_IOREMAP((void *)CV_RST_REG, 0x1000);
    val = mmio_read_32(base);
    mmio_write_32(base, val & ~CV_RST_WDT);
    rt_hw_us_delay(10);
    mmio_write_32(base, val | CV_RST_WDT);
}

rt_inline void cvi_wdt_start_en(unsigned long reg_base)
{
    WDT_CR(reg_base) |= CVI_WDT_CR_WDT_ENABLE_En;
}

rt_inline void cvi_wdt_start_dis(unsigned long reg_base)
{
    WDT_CR(reg_base) &= ~CVI_WDT_CR_WDT_ENABLE_En;
}

rt_inline uint32_t cvi_wdt_get_start(unsigned long reg_base)
{
    return (WDT_CR(reg_base) & CVI_WDT_CR_WDT_ENABLE_Msk);
}

rt_inline void cvi_wdt_set_timeout(unsigned long reg_base, uint32_t value)
{
    WDT_TORR(reg_base) &= ~CVI_WDT_TORR_WDT_TORR_Pos;
    WDT_TORR(reg_base) = ((value << CVI_WDT_TORR_WDT_ITORR_Pos) | (value << CVI_WDT_TORR_WDT_TORR_Pos));
}

rt_inline void cvi_wdt_set_respond_system_reset(unsigned long reg_base)
{
    WDT_CR(reg_base) &= ~CVI_WDT_CR_WDT_RESPOND_IRQ_THEN_RST;
}

rt_inline void cvi_wdt_set_respond_irq_then_reset(unsigned long reg_base)
{
    WDT_CR(reg_base) |= CVI_WDT_CR_WDT_RESPOND_IRQ_THEN_RST;
}

rt_inline void cvi_wdt_set_reset_pulse_width(unsigned long reg_base, uint32_t value)
{
    WDT_CR(reg_base) &= ~CVI_WDT_CR_WDT_RESET_PULSE_WIDTH_Msk;
    WDT_CR(reg_base) |= (value << CVI_WDT_CR_WDT_RESET_PULSE_WIDTH_Pos);
}

rt_inline void cvi_wdt_feed_en(unsigned long reg_base)
{
    WDT_CRR(reg_base) = CVI_WDT_CRR_FEED_En;
}

rt_inline uint32_t cvi_wdt_get_counter_value(unsigned long reg_base)
{
    return (WDT_CCVR(reg_base) & CVI_WDT_CCVR_COUNTER_Msk);
}

rt_inline uint32_t cvi_wdt_get_irq_stat(unsigned long reg_base)
{
    return (WDT_STAT(reg_base) & CVI_WDT_STAT_IRQ_STAT_Msk);
}

rt_inline void cvi_wdt_clr_irq_en(unsigned long reg_base)
{
    WDT_EOI(reg_base);
}

struct _cvi_wdt_dev
{
    struct rt_watchdog_device device;
    const char *name;
    rt_ubase_t base;
    rt_uint32_t timeout;
};

static struct _cvi_wdt_dev _wdt_dev[] =
{
#ifdef BSP_USING_WDT0
    {
        .name = "wdt0",
        .base = CVI_WDT0_BASE
    },
#endif /* BSP_USING_WDT0 */
#ifdef BSP_USING_WDT1
    {
        .name = "wdt1",
        .base = CVI_WDT1_BASE
    },
#endif /* BSP_USING_WDT1 */
#ifdef BSP_USING_WDT2
    {
        .name = "wdt2",
        .base = CVI_WDT2_BASE
    },
#endif /* BSP_USING_WDT2 */
};
struct rt_watchdog_device wdt_device;

static rt_err_t _wdt_init(rt_watchdog_t *wdt_device)
{
    cvi_wdt_top_setting();

    return RT_EOK;
}

rt_inline int wdt_top_in_ms(unsigned int top)
{
    /*
     * There are 16 possible timeout values in 0..15 where the number of
     * cycles is 2 ^ (16 + i) and the watchdog counts down.
     */
    // pr_debug("wdt top in seconds: %d/%d=%d\n", (1U << (16 + top)), chip->clk_hz, (1U << (16 + top)) / chip->clk_hz);
    return (1U << (16 + top)) / (WDT_FREQ_DEFAULT / 1000);
}

/**
 * @brief set timeout period
 *
 * @param reg_base base address of the watchdog controller
 * @param ms       timeout period (in millisecond)
 *
 * @return RT_EOK if successed.
 */
static rt_err_t csi_wdt_set_timeout(unsigned long reg_base, uint32_t ms)
{
    rt_err_t ret = RT_EOK;
    int i, top_val = CVI_WDT_MAX_TOP;

    /*
     * Iterate over the timeout values until we find the closest match. We
     * always look for >=.
     */
    for (i = 0; i <= CVI_WDT_MAX_TOP; ++i)
        if (wdt_top_in_ms(i) >= ms) {
            top_val = i;
            break;
        }

    if (i < CVI_WDT_MAX_TOP)
    {
        /*
        * Set the new value in the watchdog.  Some versions of wdt_chip
        * have TOPINIT in the TIMEOUT_RANGE register (as per
        * CP_WDT_DUAL_TOP in WDT_COMP_PARAMS_1).  On those we
        * effectively get a pat of the watchdog right here.
        */
        cvi_wdt_set_timeout(reg_base, top_val);
        cvi_wdt_start_en(reg_base);
    }
    else
    {
        ret = -RT_ERROR;
    }

    return ret;
}


static rt_err_t _wdt_control(rt_watchdog_t *wdt_device, int cmd, void *arg)
{
    RT_ASSERT(wdt_device != RT_NULL);

    struct _cvi_wdt_dev *wdt = rt_container_of(wdt_device, struct _cvi_wdt_dev, device);
    rt_uint32_t reg_base = wdt->base;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_WDT_KEEPALIVE:
        cvi_wdt_feed_en(reg_base);
        break;
    case RT_DEVICE_CTRL_WDT_SET_TIMEOUT:
        wdt->timeout = *(rt_uint32_t *)arg;
        csi_wdt_set_timeout(reg_base, wdt->timeout * 1000);
        break;
    case RT_DEVICE_CTRL_WDT_GET_TIMEOUT:
        *(rt_uint32_t *)arg = wdt->timeout;
        break;
    case RT_DEVICE_CTRL_WDT_GET_TIMELEFT:
        *(rt_uint32_t *)arg = (cvi_wdt_get_counter_value(reg_base) / WDT_FREQ_DEFAULT);
        break;
    case RT_DEVICE_CTRL_WDT_START:
        cvi_wdt_set_respond_system_reset(reg_base);
        cvi_wdt_start_en(reg_base);
        break;
    case RT_DEVICE_CTRL_WDT_STOP:
        cvi_wdt_start_dis(reg_base);
        break;
    default:
        LOG_W("This command is not supported.");
        return -RT_EINVAL;
    }

    return RT_EOK;
}

static const struct rt_watchdog_ops _wdt_ops =
{
    .init = _wdt_init,
    .control = _wdt_control
};

int rt_hw_wdt_init(void)
{
    rt_uint8_t i;
    for (i = 0; i < sizeof(_wdt_dev) / sizeof(_wdt_dev[0]); i ++)
    {
        _wdt_dev[i].device.ops = &_wdt_ops;
        _wdt_dev[i].base = (rt_ubase_t)DRV_IOREMAP((void *)_wdt_dev[i].base, 0x1000);

        if (rt_hw_watchdog_register(&_wdt_dev[i].device, _wdt_dev[i].name, RT_DEVICE_FLAG_RDWR, RT_NULL) != RT_EOK)
        {
            LOG_E("%s register failed!", _wdt_dev[i].name);
            return -RT_ERROR;
        }
    }

    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_wdt_init);
