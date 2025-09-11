/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date             Author              Notes
 * 2025-08-21       kurisaw             first version
 */

#include <drv_gpio.h>
#include <rtthread.h>

void rt_pin_mode(rt_uint64_t pin, rt_uint8_t mode)
{
    fsp_err_t err;

    switch (mode)
    {
    case PIN_MODE_OUTPUT:
        err = R_IOPORT_PinCfg(&g_ioport_ctrl, (bsp_io_port_pin_t)pin, BSP_IO_DIRECTION_OUTPUT);
        if (err != FSP_SUCCESS)
        {
            return;
        }
        break;

    case PIN_MODE_INPUT:
        err = R_IOPORT_PinCfg(&g_ioport_ctrl, (bsp_io_port_pin_t)pin, BSP_IO_DIRECTION_INPUT);
        if (err != FSP_SUCCESS)
        {
            return;
        }
        break;

    case PIN_MODE_OUTPUT_OD:
        err = R_IOPORT_PinCfg(&g_ioport_ctrl, (bsp_io_port_pin_t)pin, IOPORT_CFG_NMOS_ENABLE);
        if (err != FSP_SUCCESS)
        {
            return;
        }
        break;
    }
}

void rt_pin_write(rt_uint64_t pin, rt_uint8_t value)
{
    bsp_io_level_t level = BSP_IO_LEVEL_HIGH;

    if (value != level)
    {
        level = BSP_IO_LEVEL_LOW;
    }

    R_BSP_PinAccessEnable();
#ifdef SOC_SERIES_R9A07G0
    R_IOPORT_PinWrite(&g_ioport_ctrl, (bsp_io_port_pin_t)pin, (bsp_io_level_t)level);
#else
    R_BSP_PinWrite(pin, level);
#endif
    R_BSP_PinAccessDisable();
}

rt_int8_t rt_pin_read(rt_uint64_t pin)
{
    if ((pin > RA_MAX_PIN_VALUE) || (pin < RA_MIN_PIN_VALUE))
    {
        return -RT_EINVAL;
    }
#ifdef SOC_SERIES_R9A07G0
    bsp_io_level_t io_level;
    R_IOPORT_PinRead(&g_ioport_ctrl, (bsp_io_port_pin_t)pin, &io_level);
    return io_level;
#else
    return R_BSP_PinRead(pin);
#endif
}
