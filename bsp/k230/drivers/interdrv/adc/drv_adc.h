/* Copyright (c) 2023, Canaan Bright Sight Co., Ltd
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __DRV_ADC__
#define __DRV_ADC__
#include "board.h"

#define K230_ADC_NAME       "adc"

#define ADC_MAX_CHANNEL     6
#define ADC_MAX_DMA_CHN     3

struct k230_adc_regs
{
    rt_uint32_t trim_reg;                       /**< 0x00 */
    rt_uint32_t cfg_reg;                        /**< 0x04 */
    rt_uint32_t mode_reg;                       /**< 0x08 */
    rt_uint32_t thsd_reg;                       /**< 0x0c */
    rt_uint32_t dma_intr_reg;                   /**< 0x10 */
    rt_uint32_t data_reg[ADC_MAX_CHANNEL];      /**< 0x14~0x28 */
    rt_uint32_t data_dma[ADC_MAX_DMA_CHN];      /**< 0x2c~0x34 */
};

struct k230_adc_chan
{
    rt_uint32_t chn_num;
    rt_int8_t enabled;
};

struct k230_adc
{
    struct rt_adc_device dev;
    struct k230_adc_regs *adc_regs;
    struct k230_adc_chan chn[ADC_MAX_CHANNEL];
};

#endif /*__DRV_ADC__*/