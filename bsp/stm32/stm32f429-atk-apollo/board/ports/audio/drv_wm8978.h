/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-14     ZeroFree     first implementation
 * 2019-07-28     Ernest       perfect player, add record and other APIs
 */

#ifndef __DRV_WM8978_H__
#define __DRV_WM8978_H__

#include <rtthread.h>
#include <rtdevice.h>

enum data_fomat_select
{
    RIGHT_FOMAT_SELECT,
    LEFT_FOMAT_SELECT,
    I2S_FOMAT_SELECT,
    PCM_FOMAT_SELECT,
};

rt_err_t wm8978_init(struct rt_i2c_bus_device *dev);
void wm8978_player_start(struct rt_i2c_bus_device *dev);
void wm8978_record_start(struct rt_i2c_bus_device *dev);

int wm8978_set_volume(struct rt_i2c_bus_device *dev, int vol);

void wm8978_reset(struct rt_i2c_bus_device *dev);
/* enable ADC/DAC */
void wm8978_ADC_enabled(struct rt_i2c_bus_device *dev, rt_bool_t bool);
void wm8978_DAC_enabled(struct rt_i2c_bus_device *dev, rt_bool_t bool);

void wm8978_mic_enabled(struct rt_i2c_bus_device *dev, rt_bool_t bool);
void wm8978_linein_enabled(struct rt_i2c_bus_device *dev, rt_bool_t bool);
void wm8978_aux_enabled(struct rt_i2c_bus_device *dev, rt_bool_t bool);
void wm8978_linein_gain(struct rt_i2c_bus_device *dev, rt_uint8_t value);
void wm8978_aux_gain(struct rt_i2c_bus_device *dev, rt_uint8_t value);
void wm8978_mic_gain(struct rt_i2c_bus_device *dev, rt_uint8_t gain);
void wm8978_output_set(struct rt_i2c_bus_device *dev, rt_bool_t dac, rt_bool_t bypass);
void wm8978_hpvol_set(struct rt_i2c_bus_device *dev, rt_uint8_t volume);
void wm8978_spkvol_set(struct rt_i2c_bus_device *dev, rt_uint8_t volume);

/* set interface mode */
void wm8978_interface_cfg(struct rt_i2c_bus_device *dev, enum data_fomat_select fmt, rt_uint32_t bitBand);

void wm8978_mute_enabled(struct rt_i2c_bus_device *dev, rt_bool_t enable);
rt_err_t wm8978_set_EQ1(struct rt_i2c_bus_device *dev, rt_uint8_t freq, rt_uint8_t gain);
rt_err_t wm8978_set_EQ2(struct rt_i2c_bus_device *dev, rt_uint8_t freq, rt_uint8_t gain);
rt_err_t wm8978_set_EQ3(struct rt_i2c_bus_device *dev, rt_uint8_t freq, rt_uint8_t gain);
rt_err_t wm8978_set_EQ4(struct rt_i2c_bus_device *dev, rt_uint8_t freq, rt_uint8_t gain);
rt_err_t wm8978_set_EQ5(struct rt_i2c_bus_device *dev, rt_uint8_t freq, rt_uint8_t gain);
void wm8978_3D_Set(struct rt_i2c_bus_device *dev, rt_uint8_t depth);

#endif
