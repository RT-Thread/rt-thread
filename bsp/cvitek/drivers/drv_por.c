/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date         Author          Notes
 * 2024-03-21   qiujingbao     the first version
 */

#include <rtthread.h>
#include <rtdevice.h>


#define DBG_TAG "DRV.POR"
#define DBG_LVL DBG_WARNING
#include <rtdbg.h>

#include "mmio.h"
#include "drv_ioremap.h"

static rt_ubase_t _cvi_rtc_ctrl_base = 0x05025000U;
static rt_ubase_t _cvi_rtc_reg_base = 0x05026000U;

#define CVI_RTC_CTRL_BASE       _cvi_rtc_ctrl_base
#define CVI_RTC_REG_BASE        _cvi_rtc_reg_base
#define RTC_CTRL0_UNLOCKKEY     0x4
#define RTC_CTRL0               0x8
#define RTC_APB_BUSY_SEL        0x3C
#define RTC_EN_WARM_RST_REQ     0xCC
#define RSM_STATE               0xD4
#define ST_ON                   0x3

static int cvi_restart(void)
{
    /* Enable power suspend wakeup source mask */
    mmio_write_32(CVI_RTC_REG_BASE + RTC_APB_BUSY_SEL,0x1);

    /* unlock register */
    mmio_write_32(CVI_RTC_CTRL_BASE + RTC_CTRL0_UNLOCKKEY, 0xAB18);

    mmio_write_32(CVI_RTC_REG_BASE + RTC_EN_WARM_RST_REQ, 0x1);

    while (mmio_read_32(CVI_RTC_REG_BASE + RTC_EN_WARM_RST_REQ) != 0x01);

    while (mmio_read_32(CVI_RTC_REG_BASE + RSM_STATE) != ST_ON);

    mmio_write_32( CVI_RTC_CTRL_BASE + RTC_CTRL0,0xFFFF0800 | (0x1 << 4));

    return 0;
}

void rt_hw_cpu_reset(void)
{
    rt_kprintf("Rebooting...\n");

    _cvi_rtc_ctrl_base = (rt_ubase_t)DRV_IOREMAP((void *)_cvi_rtc_ctrl_base, 0x1000);
    _cvi_rtc_reg_base = (rt_ubase_t)DRV_IOREMAP((void *)_cvi_rtc_reg_base, 0x1000);

    cvi_restart();

    rt_kprintf("ERROR: Failed to reboot the system\n");
    while (1);
}

MSH_CMD_EXPORT_ALIAS(rt_hw_cpu_reset, reboot, reset machine);
