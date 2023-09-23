/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "hpm_ft5406.h"

hpm_stat_t ft5406_read_register(ft5406_context_t *context, uint8_t reg, uint8_t *buf)
{
    return i2c_master_address_read(context->ptr, FT5406_I2C_ADDR, &reg, 1, buf, 1);
}

hpm_stat_t ft5406_write_register(ft5406_context_t *context, uint8_t reg, uint8_t val)
{
    return i2c_master_address_write(context->ptr, FT5406_I2C_ADDR, &reg, 1, &val, 1);
}

hpm_stat_t ft5406_set_mode(ft5406_context_t *context, uint8_t mode)
{
    return ft5406_write_register(context, FT5406_DEVICE_MODE, 1);
}

hpm_stat_t ft5406_init(ft5406_context_t *context)
{
    return ft5406_set_mode(context, FT5406_DEVICE_MODE_NORMAL);
}

hpm_stat_t ft5406_get_sys_info(ft5406_context_t *context, ft5406_sys_info_t *info)
{
    hpm_stat_t stat = status_success;
    uint8_t reg_addr = FT5406_DEVICE_MODE;

    stat = ft5406_set_mode(context, FT5406_DEVICE_MODE_SYS_INFO);
    if (stat != status_success) {
        return stat;
    }
    return i2c_master_address_read(context->ptr, FT5406_I2C_ADDR, &reg_addr, 1, (uint8_t *)info, sizeof(ft5406_sys_info_t));
}

hpm_stat_t ft5406_read_data(ft5406_context_t *context, uint8_t addr, uint8_t *buf, uint32_t size)
{
    return i2c_master_address_read(context->ptr, FT5406_I2C_ADDR, &addr, 1, buf, size);
}

hpm_stat_t ft5406_read_touch_data(ft5406_context_t *context, ft5406_touch_data_t *touch_data)
{
    return ft5406_read_data(context, FT5406_GEST_ID, (uint8_t *)touch_data, sizeof(ft5406_touch_data_t));
}
