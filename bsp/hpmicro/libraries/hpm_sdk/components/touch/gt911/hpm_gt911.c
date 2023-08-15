/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "hpm_gt911.h"
static uint8_t g_i2c_addr;

hpm_stat_t gt911_read_data(gt911_context_t *context, uint16_t addr, uint8_t *buf, uint32_t size)
{
    uint8_t r[2];
    r[0] = addr >> 8;
    r[1] = addr & 0xFF;
    return i2c_master_address_read(context->ptr, g_i2c_addr, r, sizeof(r), buf, size);
}

hpm_stat_t gt911_write_data(gt911_context_t *context, uint16_t addr, uint8_t *buf, uint32_t size)
{
    uint8_t r[2];
    r[0] = addr >> 8;
    r[1] = addr & 0xFF;

    return i2c_master_address_write(context->ptr, g_i2c_addr, r, sizeof(r), buf, size);
}

hpm_stat_t gt911_read_register(gt911_context_t *context, uint16_t reg, uint8_t *buf)
{
    return gt911_read_data(context, reg, buf, 1);
}

hpm_stat_t gt911_write_register(gt911_context_t *context, uint16_t reg, uint8_t val)
{
    return gt911_write_data(context, reg, &val, 1);
}

hpm_stat_t gt911_soft_reset(gt911_context_t *context)
{
    return gt911_write_register(context, GT911_CMD, 0);
}

static uint8_t gt911_calcualte_config_data_checksum(uint8_t *config)
{
    uint8_t checksum = 0;
    for (uint32_t i = 0; i < GT911_CONFIG_DATA_SIZE - 2; i++) {
        checksum += config[i];
    }
    return (~checksum + 1);
}

hpm_stat_t gt911_read_config(gt911_context_t *context, uint8_t *buf, uint8_t size)
{
    return gt911_read_data(context, GT911_CONFIG, buf, size);
}

hpm_stat_t gt911_init(gt911_context_t *context, uint16_t width, uint16_t height)
{
    hpm_stat_t stat = status_success;
    uint8_t config[GT911_CONFIG_DATA_SIZE] = {0};

#ifdef GT911_I2C_ADDR
    g_i2c_addr = GT911_I2C_ADDR;
    stat = gt911_read_data(context, GT911_CONFIG, config, sizeof(config));
    if (stat != status_success) {
        return stat;
    }
#elif !GT911_NO_AUTO_PROBE
    g_i2c_addr = GT911_I2C_ADDR0;
    stat = gt911_read_data(context, GT911_CONFIG, config, sizeof(config));
    if (stat != status_success) {
        printf("0x%x failed to init GT911", g_i2c_addr);
        g_i2c_addr = GT911_I2C_ADDR1;
        printf(", try 0x%x\n", g_i2c_addr);
        stat = gt911_read_data(context, GT911_CONFIG, config, sizeof(config));
    }
    if (stat != status_success) {
        return stat;
    }
#else
    g_i2c_addr = GT911_I2C_ADDR0;
    stat = gt911_read_data(context, GT911_CONFIG, config, sizeof(config));
    if (stat != status_success) {
        return stat;
    }
#endif

    if (config[GT911_CONFIG_DATA_SIZE - 2] != gt911_calcualte_config_data_checksum(config)) {
        return status_fail;
    }

    /* stat = gt911_read_data(context, GT911_ID_B0, (uint8_t*)&val, sizeof(val)); */
    /* if (stat != status_success) { */
        /* return stat; */
    /* } */

    /* if (val != GT911_PRODUCT_ID) { */
        /* return status_fail; */
    /* } */

    config[GT911_CONFIG_DATA_RESOLUTION_XL] = width & 0xFF;
    config[GT911_CONFIG_DATA_RESOLUTION_XH] = width >> 8;
    config[GT911_CONFIG_DATA_RESOLUTION_YL] = height & 0xFF;
    config[GT911_CONFIG_DATA_RESOLUTION_YH] = height >> 8;
    config[GT911_CONFIG_DATA_TOUCH_NUMBER] = 5;
    config[GT911_CONFIG_DATA_MODULE_SWITCH1] = (config[GT911_CONFIG_DATA_MODULE_SWITCH1] & ~0x3);

    config[GT911_CONFIG_DATA_SIZE - 2] = gt911_calcualte_config_data_checksum(config);
    config[GT911_CONFIG_DATA_SIZE - 1] = 1;
    /*
     * for (uint8_t i = 0; i < 5; i++) {
     *     gt911_write_data(context, GT911_CONFIG, config, GT911_CONFIG_DATA_SIZE);
     * }
     */
    gt911_write_register(context, GT911_CMD, GT911_CMD_SOFT_RESET);
    return status_success;
}

hpm_stat_t gt911_read_touch_data(gt911_context_t *context,
                                  gt911_touch_data_t *touch_data)
{
    hpm_stat_t stat = status_success;

    stat = gt911_read_data(context, GT911_STATUS,
            (uint8_t *)touch_data, sizeof(gt911_touch_data_t));
    if (stat != status_success) {
        return stat;
    }

    gt911_write_register(context, GT911_STATUS, 0);

    return stat;
}
