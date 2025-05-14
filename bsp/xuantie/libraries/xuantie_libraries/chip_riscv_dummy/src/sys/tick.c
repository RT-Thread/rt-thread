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

#include <soc.h>
#include <csi_core.h>
#include <csi_config.h>
#include <sys_clk.h>
#include <drv/common.h>
#include <drv/irq.h>
#include <drv/tick.h>
#include <drv/porting.h>
#include <drv/timer.h>
#include <rtthread.h>

#define __WEAK         __attribute__((weak))

#if defined(CONFIG_SMP) && CONFIG_SMP
static volatile uint32_t csi_tick[CONFIG_NR_CPUS] = {0U};
#else
static volatile uint32_t csi_tick = 0U;
#endif
static volatile uint32_t last_time_ms = 0U;
static volatile uint64_t last_time_us = 0U;
static volatile uint64_t timer_init_value = 0U;

#if CONFIG_CPU_XUANTIE_E9XX || CONFIG_INTC_CLIC_PLIC
static csi_dev_t tick_dev;
#endif

void csi_tick_increase(void)
{
#if defined(CONFIG_SMP) && CONFIG_SMP
    csi_tick[csi_get_cpu_id()]++;
#else
    csi_tick++;
#endif
}

uint32_t csi_tick_get(void)
{
#if defined(CONFIG_SMP) && CONFIG_SMP
    return csi_tick[csi_get_cpu_id()];
#else
    return csi_tick;
#endif
}

void tick_irq_handler(void *arg)
{
    csi_tick_increase();
    csi_coret_config((soc_get_coretim_freq() / RT_TICK_PER_SECOND), CORET_IRQn);
#if CONFIG_AOS_OSAL
    extern void aos_sys_tick_handler(void);
    aos_sys_tick_handler();
#else
#ifdef CONFIG_KERNEL_FREERTOS
    extern void xPortSysTickHandler(void);
    xPortSysTickHandler();
#elif defined(CONFIG_KERNEL_RTTHREAD)
    rt_interrupt_enter();
    extern void rt_tick_increase(void);
    rt_tick_increase();
    rt_interrupt_leave();
#else
#endif
#endif /* end CONFIG_AOS_OSAL */
}

csi_error_t csi_tick_init(void)
{
#if CONFIG_CPU_XUANTIE_E9XX || CONFIG_INTC_CLIC_PLIC
    tick_dev.irq_num = CORET_IRQn;
    csi_vic_set_prio(tick_dev.irq_num, 31U);
    csi_irq_attach(tick_dev.irq_num, &tick_irq_handler, &tick_dev);
#endif

#if defined(CONFIG_SMP) && CONFIG_SMP
    csi_tick[csi_get_cpu_id()] = 0;
#else
    csi_tick = 0U;
#endif
    timer_init_value = csi_coret_get_value2();
    csi_coret_reset_value2();
    csi_coret_config((soc_get_coretim_freq() / RT_TICK_PER_SECOND), CORET_IRQn);
    csi_coret_irq_enable();

    return CSI_OK;
}

void csi_tick_uninit(void)
{
    csi_coret_irq_disable();
#if CONFIG_CPU_XUANTIE_E9XX || CONFIG_INTC_CLIC_PLIC
    csi_irq_detach(tick_dev.irq_num);
#endif
}

uint32_t csi_tick_get_ms(void)
{
    uint32_t time;

    time = (uint32_t)((csi_coret_get_value2() - timer_init_value) * 1000U / (uint64_t)soc_get_coretim_freq());
    last_time_ms = time;
    return time;
}

uint64_t csi_tick_get_us(void)
{
    uint64_t time;

    time = (csi_coret_get_value2() - timer_init_value) * 1000U * 1000U / (uint64_t)soc_get_coretim_freq();
    last_time_us = time;
    return time;
}

static void _mdelay(void)
{
    uint64_t start = csi_coret_get_value2();
    uint64_t cur;
    uint32_t cnt = (soc_get_coretim_freq() / 1000U);

    while (1) {
        cur = csi_coret_get_value2();

        if (start > cur) {
            if ((start - cur) >= cnt) {
                break;
            }
        } else {
            if (cur - start >= cnt) {
                break;
            }
        }
    }
}

static void _10udelay(void)
{
    uint64_t cur;
    uint64_t start = csi_coret_get_value2();
    uint32_t cnt = (soc_get_coretim_freq() / 1000U / 100U);

    while (1) {
        cur = csi_coret_get_value2();

        if (start > cur) {
            if ((start - cur) >= cnt) {
                break;
            }
        } else {
            if (cur - start >= cnt) {
                break;
            }
        }
    }
}

__WEAK void mdelay(uint32_t ms)
{
    while (ms) {
        ms--;
        _mdelay();
    }
}

/**
 * Ps: At least delay over 10us
*/
void udelay(uint32_t us)
{
    us /= 10U;

    while (us) {
        us--;
        _10udelay();
    }
}

