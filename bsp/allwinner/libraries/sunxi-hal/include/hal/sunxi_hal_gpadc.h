/*
 * drivers/input/sensor/sunxi_gpadc.h
 *
 * Copyright (C) 2016 Allwinner.
 * fuzhaoke <fuzhaoke@allwinnertech.com>
 *
 * SUNXI GPADC Controller Driver Header
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 */

#ifndef HAL_GPADC_H
#define HAL_GPADC_H

#include "hal_clk.h"
#include "sunxi_hal_common.h"
#include <hal_log.h>
#include <interrupt.h>
#include <gpadc/platform_gpadc.h>
#include <gpadc/common_gpadc.h>

#ifdef __cplusplus
extern "C" {
#endif

#define CONFIG_DRIVERS_GPADC_DEBUG
#ifdef CONFIG_DRIVERS_GPADC_DEBUG
#define GPADC_INFO(fmt, arg...) hal_log_info(fmt, ##arg)
#else
#define GPADC_INFO(fmt, arg...) do {}while(0)
#endif

#define GPADC_ERR(fmt, arg...) hal_log_err(fmt, ##arg)

enum
{
    GPADC_DOWN,
    GPADC_UP
};

typedef enum
{
    GP_CH_0 = 0,
    GP_CH_1,
    GP_CH_2,
    GP_CH_3,
    GP_CH_4,
    GP_CH_5,
    GP_CH_6,
    GP_CH_7,
    GP_CH_MAX
} hal_gpadc_channel_t;

typedef enum
{
    GPADC_IRQ_ERROR = -4,
    GPADC_CHANNEL_ERROR = -3,
    GPADC_CLK_ERROR = -2,
    GPADC_ERROR = -1,
    GPADC_OK = 0,
} hal_gpadc_status_t;

typedef enum gp_select_mode
{
    GP_SINGLE_MODE = 0,
    GP_SINGLE_CYCLE_MODE,
    GP_CONTINUOUS_MODE,
    GP_BURST_MODE,
} hal_gpadc_mode_t;

typedef int (*gpadc_callback_t)(uint32_t data_type, uint32_t data);

typedef struct
{
    uint32_t reg_base;
    uint32_t channel_num;
    uint32_t irq_num;
    uint32_t sample_rate;
#if defined(CONFIG_SOC_SUN20IW1)
    hal_clk_id_t bus_clk;
    hal_clk_id_t rst_clk;
    hal_clk_t mbus_clk;
#else
    hal_clk_id_t mclk;
    hal_clk_id_t pclk;
#endif
    hal_gpadc_mode_t mode;
    gpadc_callback_t callback[CHANNEL_MAX_NUM];
} hal_gpadc_t;

int hal_gpadc_init(void);
hal_gpadc_status_t hal_gpadc_deinit(void);
hal_gpadc_status_t hal_gpadc_channel_init(hal_gpadc_channel_t channal);
hal_gpadc_status_t hal_gpadc_channel_exit(hal_gpadc_channel_t channal);
hal_gpadc_status_t hal_gpadc_register_callback(hal_gpadc_channel_t channal,
        gpadc_callback_t user_callback);

#ifdef __cplusplus
}
#endif

#endif
