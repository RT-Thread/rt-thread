/**
 * @file hal_timer.h
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
#ifndef __HAL_TIMER__H__
#define __HAL_TIMER__H__

#include "hal_common.h"
#include "drv_device.h"
#include "bl808_config.h"

#define DEVICE_CTRL_TIMER_CH_START 0x80
#define DEVICE_CTRL_TIMER_CH_STOP  0x81

enum timer_index_type {
#ifdef BSP_USING_TIMER_CH0
    TIMER_CH0_INDEX,
#endif
#ifdef BSP_USING_TIMER_CH1
    TIMER_CH1_INDEX,
#endif
    TIMER_MAX_INDEX
};

enum timer_event_type {
    TIMER_EVENT_COMP0,
    TIMER_EVENT_COMP1,
    TIMER_EVENT_COMP2,
    TIMER_EVENT_UNKNOWN
};

enum timer_it_type {
    TIMER_COMP0_IT = 1 << 0,
    TIMER_COMP1_IT = 1 << 1,
    TIMER_COMP2_IT = 1 << 2,
    TIMER_ALL_IT = 1 << 3
};
typedef enum {
    TIMER_CLK_FCLK,
    TIMER_CLK_32K,
    TIMER_CLK_1K,
    TIMER_CLK_XTAL,
} timer_clk_src_t;

typedef enum {
    TIMER_PL_TRIG_NONE,
    TIMER_PL_TRIG_COMP0,
    TIMER_PL_TRIG_COMP1,
    TIMER_PL_TRIG_COMP2,
} timer_pl_trig_t;

typedef enum {
    TIMER_CNT_PRELOAD,
    TIMER_CNT_FREERUN,
} timer_cnt_mode;

typedef struct
{
    uint32_t timeout_val;
    uint32_t comp_it;
} timer_user_cfg_t;

typedef struct timer_device {
    struct device parent;
    uint8_t id;
    uint8_t ch;
    uint8_t clk_div;
    timer_cnt_mode cnt_mode;
    timer_pl_trig_t pl_trig_src;
} timer_device_t;

#define TIMER_DEV(dev) ((timer_device_t *)dev)

int timer_register(enum timer_index_type index, const char *name);

#endif