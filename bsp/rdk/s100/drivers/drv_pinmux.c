/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-04-20     rcitach      first version
 */

#include "drv_pinmux.h"

#define S100_PIN_MUX_REG_BASE            0x234C0060U
#define S100_PIN_CONFIG_REG_BASE         0x234D0010U

#define S100_PORT_IP_NUM                         2
#define S100_PORT_LLD_IP_NUM                     6
#define S100_PORT_PIN_NUM                        (uint8_t)124U
#define S100_PORT_MCU_PIN_NUM                    (uint8_t)88U
#define S100_PORT_AON_PIN_NUM                    (uint8_t)18U

#define AON_PIN_NUM(aon_gpio_idx) ((aon_gpio_idx) + (S100_PORT_MCU_PIN_NUM))
/*
 * Keep the same MCU GPIO blacklist as the SDK Port subsystem.
 * These pins are reserved for power/debug or other board-critical uses
 * and must not be reconfigured as generic GPIO from RT-Thread.
 *
 * Note:
 * The SDK also blacklists a few AON pins. The current cpu1_rtthread BSP
 * driver only manages MCU GPIO pins, so only the MCU-side blacklist is
 * enforced here.
 */
static const s100_pin_t s100_gpio_blacklist[] =
{
    0,  /* S100 Power related pins */
    5,  /* S100 debug uart tx */
    38, /* S100 Power related pins */
    15, /* S100 Power related pins */
    68, /* S100 Power related pins */
    69, /* S100 Power related pins */
    71, /* S100 Power related pins */
    80, /* S100 Power related pins */
    81, /* S100 Power related pins */
    82, /* S100 Power related pins */
    83, /* S100 Power related pins */
    AON_PIN_NUM(0),  /* S100 debug uart rx */
    AON_PIN_NUM(12), /* S100 Power related pins */
};

typedef struct
{
    volatile rt_uint32_t reg_pin_mux_func;
} s100_pin_mux_reg_t;

typedef union
{
    struct
    {
        volatile rt_uint32_t ds  : 4;
        volatile rt_uint32_t ie  : 1;
        volatile rt_uint32_t pd  : 1;
        volatile rt_uint32_t pu  : 1;
        volatile rt_uint32_t st  : 1;
        volatile rt_uint32_t rsvd: 24;
    } type0;
    volatile rt_uint32_t value;
} s100_pin_cfg_reg_t;

static s100_pin_mux_reg_t *const s100_pin_mux_regs =
    (s100_pin_mux_reg_t *)S100_PIN_MUX_REG_BASE;
static s100_pin_cfg_reg_t *const s100_pin_cfg_regs =
    (s100_pin_cfg_reg_t *)S100_PIN_CONFIG_REG_BASE;

static rt_bool_t s100_pin_is_blacklisted(s100_pin_t pin)
{
    rt_size_t i;

    for (i = 0; i < sizeof(s100_gpio_blacklist) / sizeof(s100_gpio_blacklist[0]); i++)
    {
        if (pin == s100_gpio_blacklist[i])
        {
            return RT_TRUE;
        }
    }

    return RT_FALSE;
}

rt_bool_t s100_pin_is_valid(s100_pin_t pin)
{
    if (pin >= S100_GPIO_PIN_COUNT)
    {
        return RT_FALSE;
    }

    /* Pin 79 is a hole in the MCU GPIO numbering and must be skipped. */
    if (pin == 79U)
    {
        return RT_FALSE;
    }

    if (s100_pin_is_blacklisted(pin) == RT_TRUE)
    {
        return RT_FALSE;
    }

    return RT_TRUE;
}

rt_err_t s100_pin_set_function(s100_pin_t pin, s100_pin_function_t function)
{
    if (!s100_pin_is_valid(pin))
    {
        return -RT_EINVAL;
    }

    s100_pin_mux_regs[pin].reg_pin_mux_func = (rt_uint32_t)function & 0x3U;
    return RT_EOK;
}

rt_err_t s100_pin_set_pull(s100_pin_t pin, s100_pin_pull_t pull)
{
    s100_pin_cfg_reg_t cfg;

    if (!s100_pin_is_valid(pin))
    {
        return -RT_EINVAL;
    }

    cfg = s100_pin_cfg_regs[pin];
    cfg.type0.ie = 1U;
    cfg.type0.st = 1U;
    cfg.type0.pu = 0U;
    cfg.type0.pd = 0U;

    if (pull == S100_PIN_PULL_UP)
    {
        cfg.type0.pu = 1U;
    }
    else if (pull == S100_PIN_PULL_DOWN)
    {
        cfg.type0.pd = 1U;
    }

    s100_pin_cfg_regs[pin].value = cfg.value;
    return RT_EOK;
}

