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

#include <stdint.h>
#include <soc.h>
#include <sys_clk.h>
#include <drv/io.h>

uint32_t g_system_clock = IHS_VALUE;

#if CONFIG_BOARD_XIAOHUI_EVB
uint32_t soc_get_cpu_freq(uint32_t idx)
{
    return 50*1000000;
}

uint32_t soc_get_coretim_freq(void)
{
    return 25*1000000;
}

uint32_t soc_get_uart_freq(uint32_t idx)
{
    return 36*1000000;
}

uint32_t soc_get_timer_freq(uint32_t idx)
{
    return 25*1000000;
}

#else
uint32_t soc_get_cpu_freq(uint32_t idx)
{
    return g_system_clock;
}

uint32_t soc_get_cur_cpu_freq(void)
{
    return g_system_clock;
}

uint32_t soc_get_coretim_freq(void)
{
    return g_system_clock;
}

uint32_t soc_get_uart_freq(uint32_t idx)
{
    return g_system_clock;
}

csi_error_t soc_sysclk_config(system_clk_config_t *config)
{
    return CSI_OK;
}

void soc_reset_uart(uint32_t idx)
{
}

uint32_t soc_get_timer_freq(uint32_t idx)
{
    return g_system_clock;
}
#endif

void soc_clk_enable(int32_t module)
{
}

void soc_clk_disable(int32_t module)
{
}

void soc_set_sys_freq(uint32_t val)
{
    g_system_clock = val;
}


