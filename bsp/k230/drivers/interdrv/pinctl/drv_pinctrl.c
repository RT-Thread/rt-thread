/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include <rtthread.h>
#include <ioremap.h>
#include "board.h"
#include "drv_pinctrl.h"
#include <rtdbg.h>

#define DBG_TAG "PINCTRL"
#ifdef RT_DEBUG
#define DBG_LVL DBG_LOG
#else
#define DBG_LVL DBG_WARNING
#endif
#define DBG_COLOR

#define MAX_NUM_PIN 64

#define IO_CFG_SEL_MASK 0x7
#define IO_CFG_SEL_OFFSET 11
#define IO_CFG_IE_MASK 0x1
#define IO_CFG_IE_OFFSET 8
#define IO_CFG_OE_MASK 0x1
#define IO_CFG_OE_OFFSET 7
#define IO_CFG_PU_MASK 0x1
#define IO_CFG_PU_OFFSET 6
#define IO_CFG_PD_MASK 0x1
#define IO_CFG_PD_OFFSET 5
#define IO_CFG_DRV_MASK 0xF
#define IO_CFG_DRV_OFFSET 1
#define IO_CFG_ST_MASK 0x1
#define IO_CFG_ST_OFFSET 0

volatile static rt_ubase_t pinctrl_base;

static int check_pin(rt_uint32_t pin)
{
    if (pin < 0 || pin > MAX_NUM_PIN)
    {
        LOG_E("pin %d is not valid\n", pin);
        return -RT_EINVAL;
    }
    return 0;
}

rt_inline rt_uint32_t _read32(rt_uint32_t pin)
{
    return HWREG32(pinctrl_base + (pin * 4));
}

rt_inline void _write32(rt_uint32_t pin, rt_uint32_t value)
{
    HWREG32(pinctrl_base + (pin * 4)) = value;
}

void k230_pinctrl_set_function(rt_uint32_t pin, rt_uint32_t func)
{
    if (check_pin(pin) != 0)
        return;
    if (func > IOMUX_FUNC5)
        return;

    rt_uint32_t val = _read32(pin);
    val &= ~(IO_CFG_SEL_MASK << IO_CFG_SEL_OFFSET); /* Clear bits 11-13 */
    /* Set bits 11-13 to the function value */
    val |= (func << IO_CFG_SEL_OFFSET);
    _write32(pin, val);
}

void k230_pinctrl_set_ie(rt_uint32_t pin, rt_uint32_t ie)
{
    if (check_pin(pin) != 0)
        return;

    rt_uint32_t val = _read32(pin);
    if (ie)
        val |= IO_CFG_IE_MASK << IO_CFG_IE_OFFSET;
    else
        val &= ~(IO_CFG_IE_MASK << IO_CFG_IE_OFFSET);
    _write32(pin, val);
}

void k230_pinctrl_set_oe(rt_uint32_t pin, rt_uint32_t oe)
{
    if (check_pin(pin) != 0)
        return;

    rt_uint32_t val = _read32(pin);
    if (oe)
        val |= IO_CFG_OE_MASK << IO_CFG_OE_OFFSET;
    else
        val &= ~(IO_CFG_OE_MASK << IO_CFG_OE_OFFSET);
    _write32(pin, val);
}

void k230_pinctrl_set_pu(rt_uint32_t pin, rt_uint32_t pu)
{
    if (check_pin(pin) != 0)
        return;

    rt_uint32_t val = _read32(pin);
    if (pu)
        val |= IO_CFG_PU_MASK << IO_CFG_PU_OFFSET;
    else
        val &= ~(IO_CFG_PU_MASK << IO_CFG_PU_OFFSET);
    _write32(pin, val);
}

void k230_pinctrl_set_pd(rt_uint32_t pin, rt_uint32_t pd)
{
    if (check_pin(pin) != 0)
        return;

    rt_uint32_t val = _read32(pin);
    if (pd)
        val |= IO_CFG_PD_MASK << IO_CFG_PD_OFFSET;
    else
        val &= ~(IO_CFG_PD_MASK << IO_CFG_PD_OFFSET);
    _write32(pin, val);
}

void k230_pinctrl_set_drv(rt_uint32_t pin, rt_uint32_t drv)
{
    if (check_pin(pin) != 0)
        return;
    /* FIXME: Unsupported yet */
}

void k230_pinctrl_set_st(rt_uint32_t pin, rt_uint32_t st)
{
    if (check_pin(pin) != 0)
        return;

    rt_uint32_t val = _read32(pin);
    if (st)
        val |= IO_CFG_ST_MASK << IO_CFG_ST_OFFSET;
    else
        val &= ~(IO_CFG_ST_MASK << IO_CFG_ST_OFFSET);
    _write32(pin, val);
}

rt_uint32_t k230_pinctrl_get_regval(rt_uint32_t pin)
{
    if (check_pin(pin) != 0)
        return 0;

    return _read32(pin);
}

int k230_pinctrl_init(void)
{
    rt_err_t ret;

    pinctrl_base = (rt_ubase_t)rt_ioremap((void *)IOMUX_BASE_ADDR, IOMUX_IO_SIZE);

    return RT_EOK;
}
INIT_BOARD_EXPORT(k230_pinctrl_init);