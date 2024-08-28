/*
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include "hpm_gt9xx.h"
static uint8_t g_i2c_addr;

hpm_stat_t gt9xx_read_data(gt9xx_context_t *context, uint16_t addr, uint8_t *buf, uint32_t size)
{
    uint8_t r[2];
    r[0] = addr >> 8;
    r[1] = addr & 0xFF;
    return i2c_master_address_read(context->ptr, g_i2c_addr, r, sizeof(r), buf, size);
}

hpm_stat_t gt9xx_write_data(gt9xx_context_t *context, uint16_t addr, uint8_t *buf, uint32_t size)
{
    uint8_t r[2];
    r[0] = addr >> 8;
    r[1] = addr & 0xFF;

    return i2c_master_address_write(context->ptr, g_i2c_addr, r, sizeof(r), buf, size);
}

hpm_stat_t gt9xx_read_register(gt9xx_context_t *context, uint16_t reg, uint8_t *buf)
{
    return gt9xx_read_data(context, reg, buf, 1);
}

hpm_stat_t gt9xx_write_register(gt9xx_context_t *context, uint16_t reg, uint8_t val)
{
    return gt9xx_write_data(context, reg, &val, 1);
}

hpm_stat_t gt9xx_soft_reset(gt9xx_context_t *context)
{
    return gt9xx_write_register(context, GT9XX_CMD, 0);
}

static uint8_t gt9xx_calcualte_config_data_checksum(uint8_t *config)
{
    uint8_t checksum = 0;
    for (uint32_t i = 0; i < GT9XX_CONFIG_DATA_SIZE - 2; i++) {
        checksum += config[i];
    }
    return (~checksum + 1);
}

hpm_stat_t gt9xx_read_config(gt9xx_context_t *context, uint8_t *buf, uint8_t size)
{
    return gt9xx_read_data(context, GT9XX_CONFIG, buf, size);
}

hpm_stat_t gt9xx_init(gt9xx_context_t *context, uint16_t width, uint16_t height)
{
    hpm_stat_t stat = status_success;
    uint8_t config[GT9XX_CONFIG_DATA_SIZE] = {0};

#ifdef GT9XX_I2C_ADDR
    g_i2c_addr = GT9XX_I2C_ADDR;
    stat = gt9xx_read_data(context, GT9XX_CONFIG, config, sizeof(config));
    if (stat != status_success) {
        return stat;
    }
#elif !GT9XX_NO_AUTO_PROBE
    g_i2c_addr = GT9XX_I2C_ADDR0;
    stat = gt9xx_read_data(context, GT9XX_CONFIG, config, sizeof(config));
    if (stat != status_success) {
        printf("0x%x failed to init GT9XX", g_i2c_addr);
        g_i2c_addr = GT9XX_I2C_ADDR1;
        printf(", try 0x%x\n", g_i2c_addr);
        stat = gt9xx_read_data(context, GT9XX_CONFIG, config, sizeof(config));
    }
    if (stat != status_success) {
        return stat;
    }
#else
    g_i2c_addr = GT9XX_I2C_ADDR0;
    stat = gt9xx_read_data(context, GT9XX_CONFIG, config, sizeof(config));
    if (stat != status_success) {
        return stat;
    }
#endif

    if (config[GT9XX_CONFIG_DATA_SIZE - 2] != gt9xx_calcualte_config_data_checksum(config)) {
        return status_fail;
    }

    /* < 90: fixed config; >=90 custom config */
    if (config[GT9XX_CONFIG_DATA_CONFIG_VERSION] < 90) {
        printf("ERR: GTXXX custom config can't be supported\n");
        return status_fail;
    } else {
        context->abs_x_max = config[GT9XX_CONFIG_DATA_RESOLUTION_XH];
        context->abs_x_max <<= 8;
        context->abs_x_max |= config[GT9XX_CONFIG_DATA_RESOLUTION_XL];

        context->abs_y_max = config[GT9XX_CONFIG_DATA_RESOLUTION_YH];
        context->abs_y_max <<= 8;
        context->abs_y_max |= config[GT9XX_CONFIG_DATA_RESOLUTION_YL];
    }
    /* stat = gt9xx_read_data(context, GT9XX_ID_B0, (uint8_t*)&val, sizeof(val)); */
    /* if (stat != status_success) { */
        /* return stat; */
    /* } */

    /* if (val != GT9XX_PRODUCT_ID) { */
        /* return status_fail; */
    /* } */

    config[GT9XX_CONFIG_DATA_RESOLUTION_XL] = width & 0xFF;
    config[GT9XX_CONFIG_DATA_RESOLUTION_XH] = width >> 8;
    config[GT9XX_CONFIG_DATA_RESOLUTION_YL] = height & 0xFF;
    config[GT9XX_CONFIG_DATA_RESOLUTION_YH] = height >> 8;
    config[GT9XX_CONFIG_DATA_TOUCH_NUMBER] = 5;
    config[GT9XX_CONFIG_DATA_MODULE_SWITCH1] = (config[GT9XX_CONFIG_DATA_MODULE_SWITCH1] & ~0x3);

    config[GT9XX_CONFIG_DATA_SIZE - 2] = gt9xx_calcualte_config_data_checksum(config);
    config[GT9XX_CONFIG_DATA_SIZE - 1] = 1;
    /*
     * for (uint8_t i = 0; i < 5; i++) {
     *     gt9xx_write_data(context, GT9XX_CONFIG, config, GT9XX_CONFIG_DATA_SIZE);
     * }
     */
    gt9xx_write_register(context, GT9XX_CMD, GT9XX_CMD_SOFT_RESET);
    return status_success;
}

hpm_stat_t gt9xx_read_touch_data(gt9xx_context_t *context,
                                  gt9xx_touch_data_t *touch_data)
{
    hpm_stat_t stat = status_success;

    stat = gt9xx_read_data(context, GT9XX_STATUS,
            (uint8_t *)touch_data, sizeof(gt9xx_touch_data_t));
    if (stat != status_success) {
        return stat;
    }

    return stat;
}
