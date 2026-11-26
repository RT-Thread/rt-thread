/*
 * This file is part of the OpenMV project.
 *
 * Copyright (c) 2013-2023 Ibrahim Abdelkader <iabdalkader@openmv.io>
 * Copyright (c) 2013-2023 Kwabena W. Agyeman <kwagyeman@openmv.io>
 *
 * This work is licensed under the MIT license, see the file LICENSE for details.
 *
 * GD32 SCCB adapter. The low-level transfer is shared with drv_ov7670.c so
 * that its timeout and bus-recovery behavior remains in one place.
 */
#include <rtdevice.h>

#include "cam_boardconfig.h"
#include "omv_i2c.h"

int omv_i2c_init(omv_i2c_t *bus, rt_uint32_t bus_id, rt_uint32_t speed)
{
    if (bus == RT_NULL)
    {
        return -1;
    }

    bus->id = bus_id;
    bus->speed = speed;
    bus->inst = rt_i2c_bus_device_find(OMV_CAM_BUS_NAME);
    bus->initialized = (bus->inst != RT_NULL);

    return bus->initialized ? 0 : -1;
}

int omv_i2c_deinit(omv_i2c_t *bus)
{
    if (bus == RT_NULL)
    {
        return -1;
    }

    bus->inst = RT_NULL;
    bus->initialized = 0U;
    return 0;
}

int omv_i2c_scan(omv_i2c_t *bus, rt_uint8_t *list, rt_uint8_t size)
{
    RT_UNUSED(bus);
    RT_UNUSED(list);
    RT_UNUSED(size);
    return 0;
}

int omv_i2c_enable(omv_i2c_t *bus, bool enable)
{
    RT_UNUSED(bus);
    RT_UNUSED(enable);
    return 0;
}

int omv_i2c_readb(omv_i2c_t *bus, rt_uint8_t slv_addr,
                  rt_uint8_t reg_addr, rt_uint8_t *reg_data)
{
    if ((bus == RT_NULL) || !bus->initialized || (reg_data == RT_NULL))
    {
        return -1;
    }

    return gd32_camera_sccb_read(slv_addr, reg_addr, reg_data);
}

int omv_i2c_writeb(omv_i2c_t *bus, rt_uint8_t slv_addr,
                   rt_uint8_t reg_addr, rt_uint8_t reg_data)
{
    if ((bus == RT_NULL) || !bus->initialized)
    {
        return -1;
    }

    return gd32_camera_sccb_write(slv_addr, reg_addr, reg_data);
}
