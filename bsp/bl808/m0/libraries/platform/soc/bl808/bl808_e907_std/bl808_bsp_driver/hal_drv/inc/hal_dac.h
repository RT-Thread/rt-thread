/**
 * @file hal_dac.h
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
#ifndef __HAL_DAC__H__
#define __HAL_DAC__H__

#ifdef __cplusplus
extern "C" {
#endif

#include "hal_common.h"
#include "drv_device.h"
#include "bl808_config.h"

enum dac_index_type {
#ifdef BSP_USING_DAC0
    DAC0_INDEX,
#endif
    DAC_MAX_INDEX
};

#define DAC_CHANNEL_0   (1 << 0)
#define DAC_CHANNEL_1   (1 << 1)
#define DAC_CHANNEL_ALL (DAC_CHANNEL_0 | DAC_CHANNEL_1)

/* default a_rng and b_rng is 0x03*/
/*output Voltage = (1.8V-0.2V) * digital_val/1024 + 0.2V */
#define DAC_VREF_INTERNAL 0 /*0.2V~1.8V*/
/*output Voltage = (0.9vref-0.1vref) * digital_val/1024 + 0.1vref */
#define DAC_VREF_EXTERNAL 1 /*0.1vref~0.9vref,using gpio7 for GPIO_FUN_ADC*/

enum dac_sample_frequence {
    DAC_SAMPLE_FREQ_8KHZ,
    DAC_SAMPLE_FREQ_16KHZ,
    DAC_SAMPLE_FREQ_44P1KHZ,
    DAC_SAMPLE_FREQ_500KHZ,
};

typedef struct dac_device {
    struct device parent;
    enum dac_sample_frequence sample_freq;
    uint8_t channels;
    uint8_t vref;
    void *tx_dma;
} dac_device_t;

#define DAC_DEV(dev) ((adc_device_t *)dev)

int dac_register(enum dac_index_type index, const char *name);
#ifdef __cplusplus
}
#endif
#endif
