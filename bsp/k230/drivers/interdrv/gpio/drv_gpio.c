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

#include <rtthread.h>
#include <rthw.h>
#include <rtdevice.h>
#include <riscv_io.h>
#include <rtdef.h>
#include "ioremap.h"
#include "drv_gpio.h"
#include "drv_hardlock.h"
#include "board.h"
#include <dfs_posix.h>
#include <lwp_user_mm.h>
#include <sys/ioctl.h>
#include <rtdbg.h>

#define DBG_TAG "GPIO"
#ifdef RT_DEBUG
#define DBG_LVL DBG_LOG
#else
#define DBG_LVL DBG_WARNING
#endif
#define DBG_COLOR

struct kd_gpio_device {
    struct rt_device dev;
    void* base[2];
    int hardlock;
};

static struct kd_gpio_device gpio_dev;

static struct
{
    void (*hdr)(void* args);
    void* args;
    gpio_pin_edge_t edge;
    int debounce;
    struct rt_work debounce_work;
    struct rt_work send_sig_work;
    struct rt_lwp* lwp;
    int lwp_ref_cnt;
    int signo;
    void* sigval;
} irq_table[GPIO_MAX_NUM];

static void kd_gpio_reg_writel(void* reg, rt_size_t offset, rt_uint32_t value)
{
    while (0 != kd_hardlock_lock(gpio_dev.hardlock))
        ;
    rt_uint32_t val = readl(reg);
    val &= ~(1 << offset);
    val |= (value << offset);
    writel(val, reg);
    kd_hardlock_unlock(gpio_dev.hardlock);
}

static rt_uint32_t kd_gpio_reg_readl(void* reg, rt_size_t offset)
{
    rt_uint32_t val = readl(reg);
    return (val & (1 << offset)) >> offset;
}

static int check_pin_valid(rt_base_t pin)
{
    if ((rt_uint16_t)pin < 0 || (rt_uint16_t)pin > GPIO_MAX_NUM)
    {
        LOG_E("pin %d is not valid\n", pin);
        return -RT_EINVAL;
    }
    return pin;
}

rt_err_t kd_pin_mode(rt_base_t pin, rt_base_t mode)
{
    void* reg;
    uint32_t dir;

    if (check_pin_valid(pin) < 0)
        return -RT_EINVAL;

    switch (mode)
    {
    case GPIO_DM_INPUT:
        dir = 0;
        break;
    case GPIO_DM_OUTPUT:
        dir = 1;
        break;
    default:
        LOG_E("GPIO drive mode is not supported.");
        return -RT_EINVAL;
    }

    if (pin < 32)
    {
        reg = gpio_dev.base[0] + DIRECTION;
    } else {
        pin -= 32;
        if (pin < 32)
        {
            reg = gpio_dev.base[1] + DIRECTION;
        } else {
            reg = gpio_dev.base[1] + DIRECTION + DIRECTION_STRIDE;
            pin -= 32;
        }
    }

    kd_gpio_reg_writel(reg, pin, dir);

    return RT_EOK;
}

int kd_pin_mode_get(rt_base_t pin)
{
    void* reg;

    if (check_pin_valid(pin) < 0)
        return -RT_EINVAL;

    if (pin < 32)
    {
        reg = gpio_dev.base[0] + DIRECTION;
    } else {
        pin -= 32;
        if (pin < 32)
        {
            reg = gpio_dev.base[1] + DIRECTION;
        } else {
            reg = gpio_dev.base[1] + DIRECTION + DIRECTION_STRIDE;
            pin -= 32;
        }
    }

    return kd_gpio_reg_readl(reg, pin) ? GPIO_DM_OUTPUT : GPIO_DM_INPUT;
}

rt_err_t kd_pin_write(rt_base_t pin, rt_base_t value)
{
    void* reg;

    if (check_pin_valid(pin) < 0)
        return -RT_EINVAL;

    if (pin < 32)
    {
        reg = gpio_dev.base[0] + DATA_OUTPUT;
    } else {
        pin -= 32;
        if (pin < 32)
        {
            reg = gpio_dev.base[1] + DATA_OUTPUT;
        } else {
            reg = gpio_dev.base[1] + DATA_OUTPUT + DATA_INPUT_STRIDE;
            pin -= 32;
        }
    }

    kd_gpio_reg_writel(reg, pin, value ? GPIO_PV_HIGH : GPIO_PV_LOW);

    return RT_EOK;
}

int kd_pin_read(rt_base_t pin)
{
    void* reg;

    if (check_pin_valid(pin) < 0)
        return -RT_EINVAL;

    if (pin < 32)
    {
        reg = gpio_dev.base[0] + DATA_INPUT;
    } else {
        pin -= 32;
        if (pin < 32)
        {
            reg = gpio_dev.base[1] + DATA_INPUT;
        } else {
            reg = gpio_dev.base[1] + DATA_INPUT + DATA_INPUT_STRIDE;
            pin -= 32;
        }
    }

    return kd_gpio_reg_readl(reg, pin) ? GPIO_PV_HIGH : GPIO_PV_LOW;
}

static int kd_set_pin_edge(rt_int32_t pin, gpio_pin_edge_t edge)
{
    void* reg;

    reg = gpio_dev.base[pin >> 5];
    pin = pin & 0x1f;

    switch (edge)
    {
    case GPIO_PE_RISING:
        kd_gpio_reg_writel(reg + INT_TYPE_LEVEL, pin, 0x1);
        kd_gpio_reg_writel(reg + INT_POLARITY, pin, 0x1);
        kd_gpio_reg_writel(reg + INT_BOTHEDGE, pin, 0x0);
        break;
    case GPIO_PE_FALLING:
        kd_gpio_reg_writel(reg + INT_TYPE_LEVEL, pin, 0x1);
        kd_gpio_reg_writel(reg + INT_POLARITY, pin, 0x0);
        kd_gpio_reg_writel(reg + INT_BOTHEDGE, pin, 0x0);
        break;
    case GPIO_PE_BOTH:
        kd_gpio_reg_writel(reg + INT_BOTHEDGE, pin, 0x1);
        break;
    case GPIO_PE_LOW:
        kd_gpio_reg_writel(reg + INT_TYPE_LEVEL, pin, 0x0);
        kd_gpio_reg_writel(reg + INT_POLARITY, pin, 0x0);
        kd_gpio_reg_writel(reg + INT_BOTHEDGE, pin, 0x0);
        break;
    case GPIO_PE_HIGH:
        kd_gpio_reg_writel(reg + INT_TYPE_LEVEL, pin, 0x0);
        kd_gpio_reg_writel(reg + INT_POLARITY, pin, 0x1);
        kd_gpio_reg_writel(reg + INT_BOTHEDGE, pin, 0x0);
        break;
    default:
        break;
    }

    kd_gpio_reg_writel(reg + INT_ENABLE, pin, 0x1);

    return RT_EOK;
}

static void debounce_work(struct rt_work* work, void* param)
{
    void* reg;
    rt_size_t pin = (rt_size_t)param;

    reg = gpio_dev.base[pin >> 5];
    pin = pin & 0x1f;

    rt_base_t level = rt_hw_interrupt_disable();
    kd_gpio_reg_writel(reg + INT_MASK, pin, 0x0);
    rt_hw_interrupt_enable(level);
}

static void pin_irq(int vector, void* param)
{
    void* reg;
    long pin = vector - IRQN_GPIO0_INTERRUPT;
    gpio_pin_edge_t edge = irq_table[pin].edge;
    long pin_offset;

    reg = gpio_dev.base[pin >> 5];
    pin_offset = pin & 0x1f;

    switch (edge)
    {
    case GPIO_PE_RISING:
    case GPIO_PE_FALLING:
    case GPIO_PE_BOTH:
        kd_gpio_reg_writel(reg + INT_CLEAR, pin_offset, 0x1);
        break;
    case GPIO_PE_LOW:
    case GPIO_PE_HIGH:
        kd_gpio_reg_writel(reg + INT_MASK, pin_offset, 0x1);
        rt_work_init(&irq_table[pin].debounce_work, debounce_work, (void *)pin);
        rt_work_submit(&irq_table[pin].debounce_work, irq_table[pin].debounce);
        break;
    default:
        break;
    }

    if (irq_table[pin].hdr)
        irq_table[pin].hdr(irq_table[pin].args);
}

static void gpio_irq_to_user(void* args)
{
}

rt_err_t kd_pin_attach_irq(rt_int32_t pin, rt_uint32_t mode, void (*hdr)(void* args), void* args)
{
    char irq_name[10];

    if (check_pin_valid(pin) < 0)
        return -RT_EINVAL;
    if (pin >= GPIO_IRQ_MAX_NUM)
    {
        LOG_E("pin %d not support interrupt", pin);
        return -RT_EINVAL;
    }

    irq_table[pin].hdr = hdr;
    irq_table[pin].args = args;
    if (hdr != gpio_irq_to_user)
    {
        irq_table[pin].lwp = NULL;
        irq_table[pin].lwp_ref_cnt = 0;
    }

    if (mode < 0 || mode > 4)
        return -RT_EINVAL;
    irq_table[pin].edge = mode;
    irq_table[pin].debounce = rt_tick_from_millisecond(10);

    kd_set_pin_edge(pin, irq_table[pin].edge);
    rt_snprintf(irq_name, sizeof irq_name, "pin%d", pin);
    rt_hw_interrupt_install(IRQN_GPIO0_INTERRUPT + pin, pin_irq, RT_NULL, irq_name);

    return RT_EOK;
}

rt_err_t kd_pin_detach_irq(rt_int32_t pin)
{
    void* reg;

    if (check_pin_valid(pin) < 0)
        return -RT_EINVAL;
    if (pin >= GPIO_IRQ_MAX_NUM)
    {
        LOG_E("pin %d not support interrupt", pin);
        return -RT_EINVAL;
    }

    irq_table[pin].hdr = RT_NULL;
    irq_table[pin].args = RT_NULL;
    irq_table[pin].lwp = NULL;
    irq_table[pin].lwp_ref_cnt = 0;
    irq_table[pin].signo = 0;
    irq_table[pin].sigval = 0;

    reg = gpio_dev.base[pin >> 5];
    pin = pin & 0x1f;
    kd_gpio_reg_writel(reg + INT_ENABLE, pin, 0x0);

    return RT_EOK;
}

rt_err_t kd_pin_irq_enable(rt_base_t pin, rt_uint32_t enabled)
{
    if (check_pin_valid(pin) < 0)
        return -RT_EINVAL;
    if (pin >= GPIO_IRQ_MAX_NUM)
    {
        LOG_E("pin %d not support interrupt", pin);
        return -RT_EINVAL;
    }

    if (enabled)
        rt_hw_interrupt_umask(IRQN_GPIO0_INTERRUPT + pin);
    else
        rt_hw_interrupt_mask(IRQN_GPIO0_INTERRUPT + pin);

    return RT_EOK;
}

int rt_hw_gpio_init(void)
{
    rt_err_t ret;

    gpio_dev.base[0] = rt_ioremap((void*)GPIO0_BASE_ADDR, GPIO0_IO_SIZE);
    gpio_dev.base[1] = rt_ioremap((void*)GPIO1_BASE_ADDR, GPIO1_IO_SIZE);

    if (kd_request_lock(HARDLOCK_GPIO))
    {
        rt_kprintf("fail to request hardlock-%d\n", HARDLOCK_GPIO);
        return -RT_ERROR;
    }
    gpio_dev.hardlock = HARDLOCK_GPIO;

    ret = rt_device_register(&gpio_dev.dev, "gpio", RT_DEVICE_FLAG_RDWR);

    return ret;
}
INIT_BOARD_EXPORT(rt_hw_gpio_init);