/**
 * @file hal_clock.h
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
#ifndef __HAL_CLOCK__H__
#define __HAL_CLOCK__H__

#include "hal_common.h"

/*XTAL_TYPE*/
#define XTAL_NONE           0
#define EXTERNAL_XTAL_24M   1
#define EXTERNAL_XTAL_32M   2
#define EXTERNAL_XTAL_38P4M 3
#define EXTERNAL_XTAL_40M   4
#define EXTERNAL_XTAL_26M   5
#define INTERNAL_RC_32M     6

/*CLOCK_32K_XTAL*/
#define EXTERNAL_XTAL_32K 0
#define INTERNAL_RC_32K   1

#define ROOT_CLOCK_SOURCE_32K_CLK      0
#define ROOT_CLOCK_SOURCE_XCLK         1
#define ROOT_CLOCK_SOURCE_WIFIPLL_32M  2
#define ROOT_CLOCK_SOURCE_WIFIPLL_48M  3
#define ROOT_CLOCK_SOURCE_WIFIPLL_80M  4
#define ROOT_CLOCK_SOURCE_WIFIPLL_96M  5
#define ROOT_CLOCK_SOURCE_WIFIPLL_160M 6
#define ROOT_CLOCK_SOURCE_WIFIPLL_240M 7
#define ROOT_CLOCK_SOURCE_WIFIPLL_320M 8
#define ROOT_CLOCK_SOURCE_CPUPLL_80M   9
#define ROOT_CLOCK_SOURCE_CPUPLL_100M  10
#define ROOT_CLOCK_SOURCE_CPUPLL_160M  11
#define ROOT_CLOCK_SOURCE_CPUPLL_200M  12
#define ROOT_CLOCK_SOURCE_CPUPLL_400M  13
#define ROOT_CLOCK_SOURCE_AUPLL_DIV1   14
#define ROOT_CLOCK_SOURCE_AUPLL_DIV2   15
#define ROOT_CLOCK_SOURCE_AUPLL_DIV2P5 16
#define ROOT_CLOCK_SOURCE_AUPLL_DIV5   17
#define ROOT_CLOCK_SOURCE_AUPLL_DIV6   18
#define ROOT_CLOCK_SOURCE_AUPLL_CLK    19

#define BSP_CLOCK_SOURCE_FCLK 20
#define BSP_CLOCK_SOURCE_BCLK 21

#define BSP_CLOCK_SOURCE_MUXPLL_80M  ROOT_CLOCK_SOURCE_WIFIPLL_80M
#define BSP_CLOCK_SOURCE_MUXPLL_160M ROOT_CLOCK_SOURCE_WIFIPLL_160M

void system_clock_init(void);
void peripheral_clock_init(void);
void system_mtimer_clock_init(void);
void system_mtimer_clock_reinit(void);
#endif