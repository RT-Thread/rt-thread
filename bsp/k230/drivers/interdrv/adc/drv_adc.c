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
 * Copyright (c) 2006-2025 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <drivers/adc.h>
#include <ioremap.h>
#include <rtthread.h>
#include <rthw.h>
#include <rtdevice.h>
#include <riscv_io.h>
#include <string.h>

#include "board.h"
#include "drv_adc.h"

struct k230_adc adc_dev;

static int k230_adc_hw_init(struct k230_adc_regs *adc_regs)
{
    rt_uint32_t reg;

    reg = readl(&adc_regs->trim_reg);
    reg &= (~(0x1));
    writel(reg, &adc_regs->trim_reg);

    reg = readl(&adc_regs->trim_reg);
    reg |= 0x1;
    writel(reg, &adc_regs->trim_reg);

    reg = readl(&adc_regs->trim_reg);
    reg |= (0x1 << 20);
    writel(reg, &adc_regs->trim_reg);

    /* delay 150us */
    rt_hw_us_delay(150);

    reg &= ~(0x1 << 20);
    writel(reg, &adc_regs->trim_reg);

    writel(0x0, &adc_regs->mode_reg);

    return RT_EOK;
}

static int k230_adc_init()
{
    int i;

    adc_dev.adc_regs = (struct k230_adc_regs*)rt_ioremap((void *)ADC_BASE_ADDR, ADC_IO_SIZE);

    for (i = 0; i < ADC_MAX_DMA_CHN; i++)
    {
        adc_dev.chn[i].chn_num = i;
        adc_dev.chn[i].enabled = 0;
    }

    k230_adc_hw_init(adc_dev.adc_regs);

    return RT_EOK;
}

static int k_adc_drv_enabled(struct k230_adc_regs *adc_regs)
{
    rt_uint32_t reg;

    reg = readl(&adc_regs->trim_reg);
    reg |= 0x1;
    writel(reg, &adc_regs->trim_reg);

    return RT_EOK;
}

static int k_adc_drv_disabled(struct k230_adc_regs *adc_regs)
{
    rt_uint32_t reg;

    reg = readl(&adc_regs->trim_reg);
    reg = reg & (~(0x1));
    writel(reg, &adc_regs->trim_reg);

    return RT_EOK;
}

rt_err_t k230_adc_enabled(struct rt_adc_device *device, rt_int8_t channel, rt_bool_t enabled)
{
    if (channel >= ADC_MAX_CHANNEL)
        return -RT_ERROR;

    struct k230_adc *kd_adc = rt_container_of(device, struct k230_adc, dev);

    kd_adc->chn[channel].enabled = 1;
    if (enabled)
    {
        kd_adc->chn[channel].enabled = 1;
    }
    else
    {
        kd_adc->chn[channel].enabled = 0;
    }

    return RT_EOK;
}

rt_err_t k230_get_adc_value(struct rt_adc_device *device, rt_int8_t channel, rt_uint32_t *value)
{
    if (channel >= ADC_MAX_CHANNEL)
        return -RT_ERROR;

    struct k230_adc *kd_adc = rt_container_of(device, struct k230_adc, dev);

    if (!kd_adc->chn[channel].enabled)
        return -RT_ERROR;

    writel(channel | 0x10, &kd_adc->adc_regs->cfg_reg);
    while ((readl(&kd_adc->adc_regs->cfg_reg) & 0x10000) == 0);
    *value = readl(&kd_adc->adc_regs->data_reg[channel]);

    return RT_EOK;
}

static const struct rt_adc_ops k230_adc_ops =
{
    .enabled = k230_adc_enabled,
    .convert = k230_get_adc_value,
};

int rt_hw_adc_init(void)
{
    k230_adc_init();

    rt_hw_adc_register(&adc_dev.dev, K230_ADC_NAME, &k230_adc_ops, NULL);

    return RT_EOK;
}
INIT_BOARD_EXPORT(rt_hw_adc_init);
