/**
 * @file hal_mtimer.c
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
#include "hal_mtimer.h"
#include "bl808_glb.h"

static void (*systick_callback)(void);
static uint64_t current_set_ticks = 0;

static void Systick_Handler(void)
{
    csi_coret_config(current_set_ticks, MTIME_IRQn);
    systick_callback();
}

/**
 * @brief
 *
 */
void mtimer_init(void)
{
    uint32_t clkSrc = CPU_Get_MTimer_Source_Clock();

    CPU_Interrupt_Disable(MTIME_IRQn);

    if (clkSrc > 1 * 1000 * 1000) {
        /* Set MTimer clock source 1M */
        CPU_Set_MTimer_CLK(1, clkSrc / 1000 / 1000 - 1);
    } else {
        /* Set MTimer clock source 1k */
        CPU_Set_MTimer_CLK(1, clkSrc / 1000 - 1);
    }

    /* never reset mtimer */
    //CPU_Reset_MTimer();
}

/**
 * @brief
 *
 */
void mtimer_deinit()
{
    CPU_Interrupt_Disable(MTIME_IRQn);
}
/**
 * @brief
 *
 * @param time
 * @param interruptFun
 */
void mtimer_set_alarm_time(uint64_t ticks, void (*interruptfun)(void))
{
    current_set_ticks = ticks;
    systick_callback = interruptfun;

    csi_coret_config_use(ticks, MTIME_IRQn);
    CPU_Interrupt_Disable(MTIME_IRQn);
    Interrupt_Handler_Register(MTIME_IRQn, Systick_Handler);
    CPU_Interrupt_Enable(MTIME_IRQn);
}
/**
 * @brief
 *
 */
void mtimer_start()
{
}
/**
 * @brief
 *
 */
void mtimer_stop()
{
}
/**
 * @brief
 *
 */
void mtimer_clear_time()
{
    CPU_Reset_MTimer();
}

/**
 * @brief
 *
 * @return uint64_t
 */
uint64_t mtimer_get_time_ms()
{
    return CPU_Get_MTimer_MS();
}
/**
 * @brief
 *
 * @return uint64_t
 */
uint64_t mtimer_get_time_us()
{
    return CPU_Get_MTimer_US();
}
/**
 * @brief
 *
 * @param time
 */
void mtimer_delay_ms(uint32_t time)
{
    CPU_MTimer_Delay_MS(time);
}
/**
 * @brief
 *
 * @param time
 */
void mtimer_delay_us(uint32_t time)
{
    CPU_MTimer_Delay_US(time);
}
