/* Copyright (c) 2023, Canaan Bright Sight Co., Ltd
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/*
 * K230 Hardware Timer Driver
 *
 * K230 provides 9 timers, 6 general-purpose timers (TIMER0-TIMER5) and
 * 3 STC timers.
 * This driver only implements the general-purpose timers (TIMER0-TIMER5).
 * This driver only supports the ONESHOT mode.
 * Support frequency options: 12.5M(min), 25M, 50M, 100M(max)
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "riscv_io.h"
#include "board.h"
#include "ioremap.h"
#include <rtdbg.h>
#include <stdbool.h>
#include <stdio.h>
#include <rthw.h>
#include "sysctl_rst.h"
#include "drv_timer.h"
#include <dfs_posix.h>

static void k230_timer_stop(rt_hwtimer_t *timer);
static void k230_timer_init(rt_hwtimer_t *timer, rt_uint32_t state)
{
    struct k230_timer *kd_timer = rt_container_of(timer, struct k230_timer, device);

    uint8_t id = kd_timer->id;
    if (state == 0)
    {
        k230_timer_stop(timer);
    }
    else
    {
        sysctl_clk_set_leaf_parent(kd_timer->clk, kd_timer->clk_src);
        if (timer->freq == timer->info->minfreq)
            sysctl_clk_set_leaf_div(kd_timer->clk_src, 1, 8);
        if (timer->freq == timer->info->maxfreq)
            sysctl_clk_set_leaf_div(kd_timer->clk_src, 1, 1);
        if (timer->freq == 50*MHz)
            sysctl_clk_set_leaf_div(kd_timer->clk_src, 1, 2);
        if (timer->freq == 25*MHz)
            sysctl_clk_set_leaf_div(kd_timer->clk_src, 1, 4);
    }
}

static rt_err_t k230_timer_start(rt_hwtimer_t *timer, rt_uint32_t cnt, rt_hwtimer_mode_t mode)
{
    struct k230_timer *kd_timer = rt_container_of(timer, struct k230_timer, device);
    uint8_t id = kd_timer->id;
    k230_timer_regs_t* reg = (k230_timer_regs_t *)kd_timer->base;
    reg->channel[id].load_count = cnt;
    reg->channel[id].control &= ~(TIMER_CR_INTERRUPT_MASK);
    reg->channel[id].control |= (TIMER_CR_USER_MODE | TIMER_CR_ENABLE);
    return RT_EOK;
}

static void k230_timer_stop(rt_hwtimer_t *timer)
{
    struct k230_timer *kd_timer = rt_container_of(timer, struct k230_timer, device);
    uint8_t id = kd_timer->id;
    k230_timer_regs_t* reg = (k230_timer_regs_t *)kd_timer->base;
    reg->channel[id].control &= ~TIMER_CR_ENABLE;
    reg->channel[id].control |= TIMER_CR_INTERRUPT_MASK;
}

static rt_uint32_t k230_timer_get(rt_hwtimer_t *timer)
{
    struct k230_timer *kd_timer = rt_container_of(timer, struct k230_timer, device);
    uint8_t id = kd_timer->id;
    k230_timer_regs_t* reg = (k230_timer_regs_t *)kd_timer->base;
    return reg->channel[id].current_value;
}

static rt_err_t k230_timer_ctrl(rt_hwtimer_t *timer, rt_uint32_t cmd, void *arg)
{
    struct k230_timer *kd_timer = rt_container_of(timer, struct k230_timer, device);

    switch (cmd)
    {
    case HWTIMER_CTRL_FREQ_SET:
        timer->freq = *((rt_uint32_t*)arg);
        sysctl_clk_set_leaf_parent(kd_timer->clk, kd_timer->clk_src);
        if (timer->freq == timer->info->minfreq)
            sysctl_clk_set_leaf_div(kd_timer->clk_src, 1, 8);
        if (timer->freq == timer->info->maxfreq)
            sysctl_clk_set_leaf_div(kd_timer->clk_src, 1, 1);
        if (timer->freq == 50*MHz)
            sysctl_clk_set_leaf_div(kd_timer->clk_src, 1, 2);
        if (timer->freq == 25*MHz)
            sysctl_clk_set_leaf_div(kd_timer->clk_src, 1, 4);
        break;
    case HWTIMER_CTRL_STOP:
        k230_timer_stop(timer);
        break;
    case HWTIMER_CTRL_INFO_GET:
        if (arg == RT_NULL)
        {
            LOG_E("HWTIMER_CTRL_INFO_GET arg is NULL");
            return -RT_ERROR;
        }
        *(struct rt_hwtimer_info *)arg = *(kd_timer->device.info);
        break;
    case HWTIMER_CTRL_MODE_SET:
        if (arg == RT_NULL)
        {
            LOG_E("HWTIMER_CTRL_MODE_SET arg is NULL");
            return -RT_ERROR;
        }
        timer->mode = *(rt_hwtimer_mode_t *)arg;
        if (timer->mode != HWTIMER_MODE_ONESHOT)
        {
            LOG_E("mode is invalid/unsupported, only ONESHOT is supported");
            return -RT_ERROR;
        }
        break;
    default:
        LOG_E("HWTIMER_CTRL cmd is invalid");
        return -RT_ERROR;
    }
    return RT_EOK;
}

static int k230_timer_fops_open(struct dfs_file* fd)
{
    rt_device_t device = (rt_device_t)fd->vnode->data;
    return rt_device_open(device, RT_DEVICE_OFLAG_RDWR);
}

static int k230_timer_fops_close(struct dfs_file* fd)
{
    rt_device_t device = (rt_device_t)fd->vnode->data;
    return rt_device_close(device);
}

static const struct rt_hwtimer_info k230_timer_info =
{
    100000000,          /* the maximum count frequency can be set */
    12500000,           /* the minimum count frequency can be set */
    0xFFFFFFFF,         /* the maximum counter value */
    HWTIMER_CNTMODE_DW, /* Increment or Decreasing count mode */
};

static const struct rt_hwtimer_ops k230_timer_ops =
{
    .init = k230_timer_init,
    .start = k230_timer_start,
    .stop = k230_timer_stop,
    .count_get = k230_timer_get,
    .control = k230_timer_ctrl,
};

static const struct dfs_file_ops k230_timer_fops = {
    k230_timer_fops_open,
    k230_timer_fops_close,
};

void k230_hwtimer_isr(int vector, void *param)
{
    uint32_t ret;
    struct k230_timer *kd_timer = (struct k230_timer *)param;
    rt_hwtimer_t *hwtimer = (rt_hwtimer_t *)&(kd_timer->device);

    RT_ASSERT(kd_timer != RT_NULL && hwtimer != RT_NULL);

    int id = kd_timer->id;
    k230_timer_regs_t* reg = (k230_timer_regs_t *)kd_timer->base;

    ret = (reg->channel[id].eoi);

    rt_device_hwtimer_isr(hwtimer);
}

static struct k230_timer timer_devices[] =
{
#ifdef BSP_USING_TIMER0
    {
        .device.info = &k230_timer_info,
        .device.ops = &k230_timer_ops,
        .device.parent.fops = &k230_timer_fops,

        .name = "hwtimer0",
        .id = 0,
        .clk = SYSCTL_CLK_TIMER0,
        .clk_src = SYSCTL_CLK_TIMER0_SRC,
        .irq_num = IRQN_TIMER_0_INTERRUPT
    },
#endif /* BSP_USING_TIMER0 */

#ifdef BSP_USING_TIMER1
    {
        .device.info = &k230_timer_info,
        .device.ops = &k230_timer_ops,
        .device.parent.fops = &k230_timer_fops,

        .name = "hwtimer1",
        .id = 1,
        .clk = SYSCTL_CLK_TIMER1,
        .clk_src = SYSCTL_CLK_TIMER1_SRC,
        .irq_num = IRQN_TIMER_1_INTERRUPT
    },
#endif /* BSP_USING_TIMER1 */

#ifdef BSP_USING_TIMER2
    {
        .device.info = &k230_timer_info,
        .device.ops = &k230_timer_ops,
        .device.parent.fops = &k230_timer_fops,

        .name = "hwtimer2",
        .id = 2,
        .clk = SYSCTL_CLK_TIMER2,
        .clk_src = SYSCTL_CLK_TIMER2_SRC,
        .irq_num = IRQN_TIMER_2_INTERRUPT
    },
#endif /* BSP_USING_TIMER0 */

#ifdef BSP_USING_TIMER3
    {
        .device.info = &k230_timer_info,
        .device.ops = &k230_timer_ops,
        .device.parent.fops = &k230_timer_fops,

        .name = "hwtimer3",
        .id = 3,
        .clk = SYSCTL_CLK_TIMER3,
        .clk_src = SYSCTL_CLK_TIMER3_SRC,
        .irq_num = IRQN_TIMER_3_INTERRUPT
    },
#endif /* BSP_USING_TIMER3 */

#ifdef BSP_USING_TIMER4
    {
        .device.info = &k230_timer_info,
        .device.ops = &k230_timer_ops,
        .device.parent.fops = &k230_timer_fops,

        .name = "hwtimer4",
        .id = 4,
        .clk = SYSCTL_CLK_TIMER4,
        .clk_src = SYSCTL_CLK_TIMER4_SRC,
        .irq_num = IRQN_TIMER_4_INTERRUPT
    },
#endif /* BSP_USING_TIMER4 */

#ifdef BSP_USING_TIMER5
    {
        .device.info = &k230_timer_info,
        .device.ops = &k230_timer_ops,
        .device.parent.fops = &k230_timer_fops,

        .name = "hwtimer5",
        .id = 5,
        .clk = SYSCTL_CLK_TIMER5,
        .clk_src = SYSCTL_CLK_TIMER5_SRC,
        .irq_num = IRQN_TIMER_5_INTERRUPT
    },
#endif /* BSP_USING_TIMER5 */

#if !defined(BSP_USING_TIMER0) && \
    !defined(BSP_USING_TIMER1) && \
    !defined(BSP_USING_TIMER2) && \
    !defined(BSP_USING_TIMER3) && \
    !defined(BSP_USING_TIMER4) && \
    !defined(BSP_USING_TIMER5)
#error "No hardware timer device enabled!"
#endif
};

int rt_hw_timer_init(void)
{
    rt_uint8_t i, array_size;

    array_size = sizeof(timer_devices) / sizeof(struct k230_timer);
    if (array_size == 0)
    {
        LOG_E("No timer device defined!");
        return -RT_ERROR;
    }

    volatile void* base = (void *)rt_ioremap((void *)HW_TIMER_BASE_ADDR, HW_TIMER_IO_SIZE);
    for (i = 0; i < array_size; i++)
    {
        timer_devices[i].base = (rt_ubase_t)base;

        if (rt_device_hwtimer_register(&timer_devices[i].device, timer_devices[i].name, RT_NULL) != RT_EOK)
        {
            LOG_E("%s register failed!", timer_devices[i].name);
            return -RT_ERROR;
        }
        LOG_D("%s register OK!", timer_devices[i].name);

        rt_hw_interrupt_install(timer_devices[i].irq_num,
                                k230_hwtimer_isr,
                                &timer_devices[i],
                                timer_devices[i].name);
        rt_hw_interrupt_umask(timer_devices[i].irq_num);
    }
    return RT_EOK;
}
INIT_BOARD_EXPORT(rt_hw_timer_init);