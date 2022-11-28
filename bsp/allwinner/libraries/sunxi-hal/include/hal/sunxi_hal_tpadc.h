/*
 * drivers/input/sensor/sunxi_gpadc.h
 *
 * Copyright (C) 2016 Allwinner.
 * fuzhaoke <fuzhaoke@allwinnertech.com>
 *
 * SUNXI TPADC Controller Driver Header
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 */

#ifndef HAL_TPADC_H
#define HAL_TPADC_H

#include "hal_clk.h"
#include "hal_reset.h"
#include "sunxi_hal_common.h"
#include <hal_log.h>
#include <interrupt.h>
#include <tpadc/platform_tpadc.h>
#include <tpadc/common_tpadc.h>

#ifdef __cplusplus
extern "C" {
#endif

#define TPADC_DEBUG
#ifdef TPADC_DEBUG
#define TPADC_INFO(fmt, arg...) hal_log_info(fmt, ##arg)
#else
#define TPADC_INFO(fmt, arg...) do {}while(0)
#endif

#define TPADC_ERR(fmt, arg...) hal_log_err(fmt, ##arg)

typedef enum
{
    TPADC_IRQ_ERROR = -4,
    TPADC_CHANNEL_ERROR = -3,
    TPADC_CLK_ERROR = -2,
    TPADC_ERROR = -1,
    TPADC_OK = 0,
} hal_tpadc_status_t;

typedef enum
{
    DATA_X = 0,
    DATA_Y,
    DATA_UP,
} data_flag_t;

typedef enum
{
    TP_CH_0 = 0,
    TP_CH_1,
    TP_CH_2,
    TP_CH_3,
    TP_CH_MAX,
} tp_channel_id;

typedef int (*tpadc_usercallback_t)(uint32_t data, data_flag_t flag);
typedef int (*tpadc_adc_usercallback_t)(uint32_t data, tp_channel_id channel);

typedef struct hal_tpadc
{
    unsigned long reg_base;
    uint32_t channel_num;
    uint32_t irq_num;
    uint32_t rate;
    hal_clk_id_t bus_clk_id;
    hal_clk_id_t mod_clk_id;
    hal_reset_id_t rst_clk_id;
    hal_clk_t   bus_clk;
    hal_clk_t   mod_clk;
    struct reset_control    *rst_clk;
    tpadc_usercallback_t callback;
    tpadc_adc_usercallback_t adc_callback[TP_CH_MAX];
} hal_tpadc_t;

hal_tpadc_status_t hal_tpadc_init(void);
hal_tpadc_status_t hal_tpadc_exit(void);
hal_tpadc_status_t hal_tpadc_register_callback(tpadc_usercallback_t user_callback);

hal_tpadc_status_t hal_tpadc_adc_init(void);
hal_tpadc_status_t hal_tpadc_adc_channel_init(tp_channel_id channel);
hal_tpadc_status_t hal_tpadc_adc_channel_exit(tp_channel_id channel);
hal_tpadc_status_t hal_tpadc_adc_exit(void);
hal_tpadc_status_t hal_tpadc_adc_register_callback(tp_channel_id channel , tpadc_adc_usercallback_t user_callback);

hal_tpadc_status_t hal_tpadc_resume(void);
hal_tpadc_status_t hal_tpadc_suspend(void);

#ifdef __cplusplus
}
#endif

#endif
