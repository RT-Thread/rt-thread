 /*
 * Copyright (C) 2017-2024 Alibaba Group Holding Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdio.h>
#include <csi_config.h>
#include <soc.h>
#include <drv/uart.h>
#include <drv/timer.h>
#include <drv/dma.h>
#include <drv/iic.h>
#include <drv/rtc.h>
#include <drv/spi.h>
#include <drv/adc.h>
#include <drv/gpio.h>
#include <drv/irq.h>
#include <drv/pin.h>

const csi_perip_info_t g_soc_info[] = {
    {DW_UART0_BASE,            DW_UART0_IRQn,            0,    DEV_DW_UART_TAG},
    {DW_TIMER0_BASE,           TIM0_IRQn,                0,    DEV_DW_TIMER_TAG},
    {DW_TIMER1_BASE,           TIM1_IRQn,                1,    DEV_DW_TIMER_TAG},
    {DW_TIMER2_BASE,           TIM2_IRQn,                2,    DEV_DW_TIMER_TAG},
    {DW_TIMER3_BASE,           TIM3_IRQn,                3,    DEV_DW_TIMER_TAG},
#if CONFIG_SUPPORT_NMI_DEMO
    {DW_TIMER4_BASE,           FAKE_IRQ_TIMER4,          4,    DEV_DW_TIMER_TAG},
#endif
    {0, 0, 0, 0}
};

const uint8_t g_dma_chnum[] = {};

const uint16_t uart_tx_hs_num[1] = {};
const uint16_t uart_rx_hs_num[1] = {};

const csi_dma_ch_desc_t uart0_dma_ch_list[] = {
    {0xff, 0xff}
};

const csi_dma_ch_spt_list_t dma_spt_list[] = {
    {0xFFFFU,         0xFFU,         NULL},
};

const csi_pinmap_t gpio_pinmap[] = {
    {0xFFFFFFFFU,   0xFFU, 0xFFU,       0xFFFFFFFFU   },
};

const csi_pinmap_t uart_pinmap[] = {
    {0xFFFFFFFFU, 0xFFU, 0xFFU,      0xFFFFFFFFU  },
};

const csi_clkmap_t clk_map[] = {
    {0xFFFFFFFFU, 0xFFFFU,          0xFFU}
};

