/**
 * @file hal_adc.h
 * @brief
 *
 * Copyright (c) 2021 Bouffalolab team
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 */
#ifndef __HAL_ADC__H__
#define __HAL_ADC__H__

#ifdef __cplusplus
extern "C" {
#endif

#include "hal_common.h"
#include "drv_device.h"
#include "bl808_config.h"

#define DEVICE_CTRL_ADC_CHANNEL_START  0x10
#define DEVICE_CTRL_ADC_CHANNEL_STOP   0x11
#define DEVICE_CTRL_ADC_CHANNEL_CONFIG 0x12
#define DEVICE_CTRL_ADC_VBAT_ON        0x13
#define DEVICE_CTRL_ADC_VBAT_OFF       0x14
#define DEVICE_CTRL_ADC_TSEN_ON        0x15
#define DEVICE_CTRL_ADC_TSEN_OFF       0x16

enum adc_index_type {
#ifdef BSP_USING_ADC0
    ADC0_INDEX,
#endif
    ADC_MAX_INDEX
};

#define adc_channel_start(dev)        device_control(dev, DEVICE_CTRL_ADC_CHANNEL_START, NULL)
#define adc_channel_stop(dev)         device_control(dev, DEVICE_CTRL_ADC_CHANNEL_STOP, NULL)
#define adc_channel_config(dev, list) device_control(dev, DEVICE_CTRL_ADC_CHANNEL_CONFIG, list)

typedef enum {
    ADC_CHANNEL0,          /* ADC channel 0 */
    ADC_CHANNEL1,          /* ADC channel 1 */
    ADC_CHANNEL2,          /* ADC channel 2 */
    ADC_CHANNEL3,          /* ADC channel 3 */
    ADC_CHANNEL4,          /* ADC channel 4 */
    ADC_CHANNEL5,          /* ADC channel 5 */
    ADC_CHANNEL6,          /* ADC channel 6 */
    ADC_CHANNEL7,          /* ADC channel 7 */
    ADC_CHANNEL8,          /* ADC channel 8 */
    ADC_CHANNEL9,          /* ADC channel 9 */
    ADC_CHANNEL10,         /* ADC channel 10 */
    ADC_CHANNEL11,         /* ADC channel 11 */
    ADC_CHANNEL_DAC_OUTA,  /* DACA, ADC channel 12 */
    ADC_CHANNEL_DAC_OUTB,  /* DACB, ADC channel 13 */
    ADC_CHANNEL_TSEN_P,    /* TSenp, ADC channel 14 */
    ADC_CHANNEL_TSEN_N,    /* TSenn, ADC channel 15 */
    ADC_CHANNEL_VREF,      /* Vref, ADC channel 16 */
    ADC_CHANNEL_DCTEST,    /* DCTest, ADC channel 17 */
    ADC_CHANNEL_VABT_HALF, /* VBAT/2, ADC channel 18 */
    ADC_CHANNEL_SENP3,     /* SenVP3, ADC channel 19 */
    ADC_CHANNEL_SENP2,     /* SenVP2, ADC channel 20 */
    ADC_CHANNEL_SENP1,     /* SenVP1, ADC channel 21 */
    ADC_CHANNEL_SENP0,     /* SenVP0, ADC channel 22 */
    ADC_CHANNEL_GND,       /* GND, ADC channel 23 */
} adc_channel_t;

typedef enum {
    ADC_CLOCK_DIV_1,  /*!< ADC clock:on 32M clock is 32M */
    ADC_CLOCK_DIV_4,  /*!< ADC clock:on 32M clock is 8M */
    ADC_CLOCK_DIV_8,  /*!< ADC clock:on 32M clock is 4M */
    ADC_CLOCK_DIV_12, /*!< ADC clock:on 32M clock is 2.666M */
    ADC_CLOCK_DIV_16, /*!< ADC clock:on 32M clock is 2M */
    ADC_CLOCK_DIV_20, /*!< ADC clock:on 32M clock is 1.6M */
    ADC_CLOCK_DIV_24, /*!< ADC clock:on 32M clock is 1.333M */
    ADC_CLOCK_DIV_32, /*!< ADC clock:on 32M clock is 1M */
} adc_clk_div_t;

typedef enum {
    ADC_VREF_3V2 = 0, /* ADC select 3.2V as reference voltage */
    ADC_VREF_2V = 1,  /* ADC select 2V as reference voltage */
} adc_vref_t;

/**
 *  @brief ADC data width type definition
 */
typedef enum {
    ADC_DATA_WIDTH_12B,                  /*!< ADC 12 bits */
    ADC_DATA_WIDTH_14B_WITH_16_AVERAGE,  /*!< ADC 14 bits,and the value is average of 16 converts */
    ADC_DATA_WIDTH_14B_WITH_64_AVERAGE,  /*!< ADC 14 bits,and the value is average of 64 converts */
    ADC_DATA_WIDTH_16B_WITH_128_AVERAGE, /*!< ADC 16 bits,and the value is average of 128 converts */
    ADC_DATA_WIDTH_16B_WITH_256_AVERAGE, /*!< ADC 16 bits,and the value is average of 256 converts */
} adc_data_width_t;

/**
 *  @brief ADC FIFO threshold type definition
 */
typedef enum {
    ADC_FIFO_THRESHOLD_1BYTE,  /*!< ADC FIFO threshold is 1 */
    ADC_FIFO_THRESHOLD_4BYTE,  /*!< ADC FIFO threshold is 4 */
    ADC_FIFO_THRESHOLD_8BYTE,  /*!< ADC FIFO threshold is 8 */
    ADC_FIFO_THRESHOLD_16BYTE, /*!< ADC FIFO threshold is 16 */
} adc_fifo_threshold_t;

/**
 *  @brief ADC PGA gain type definition
 */
typedef enum {
    ADC_GAIN_NONE, /*!< No PGA gain */
    ADC_GAIN_1,    /*!< PGA gain 1 */
    ADC_GAIN_2,    /*!< PGA gain 2 */
    ADC_GAIN_4,    /*!< PGA gain 4 */
    ADC_GAIN_8,    /*!< PGA gain 8 */
    ADC_GAIN_16,   /*!< PGA gain 16 */
    ADC_GAIN_32,   /*!< PGA gain 32 */
} adc_pga_gain_t;

enum adc_event_type {
    ADC_EVENT_UNDERRUN,
    ADC_EVENT_OVERRUN,
    ADC_EVENT_FIFO,
    ADC_EVENT_UNKNOWN
};

enum adc_it_type {
    ADC_UNDERRUN_IT = 1 << 2,
    ADC_OVERRUN_IT = 1 << 3,
    ADC_FIFO_IT = 1 << 5,
};

typedef struct {
    uint8_t *pos_channel;
    uint8_t *neg_channel;
    uint8_t num;
} adc_channel_cfg_t;

typedef struct {
    int8_t posChan; /*!< Positive channel */
    int8_t negChan; /*!< Negative channel */
    uint16_t value; /*!< ADC value */
    float volt;     /*!< ADC voltage result */
} adc_channel_val_t;

typedef struct adc_device {
    struct device parent;
    adc_clk_div_t clk_div;     /* CLK is not more than 2Mhz */
    adc_vref_t vref;           /* ADC voltage reference*/
    bool continuous_conv_mode; /** conversion mode: shot conversion mode or continuous conversion mode. */
    bool differential_mode;    /** Channel type: single-ended or differential. */
    adc_data_width_t data_width;
    adc_fifo_threshold_t fifo_threshold;
    adc_pga_gain_t gain;
} adc_device_t;

#define ADC_DEV(dev) ((adc_device_t *)dev)

int adc_register(enum adc_index_type index, const char *name);
int adc_trim_tsen(uint16_t *tsen_offset);
float adc_get_tsen(uint16_t tsen_offset);

#ifdef __cplusplus
}
#endif
#endif