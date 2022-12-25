/**
 * @file hal_mtimer.h
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
#ifndef __HAL_MTIMER__H__
#define __HAL_MTIMER__H__

#include "stdint.h"

#ifdef __cplusplus
extern "C" {
#endif

void mtimer_init(void);
void mtimer_set_alarm_time(uint64_t ticks, void (*interruptfun)(void));
uint64_t mtimer_get_time_ms();
uint64_t mtimer_get_time_us();
void mtimer_delay_ms(uint32_t time);
void mtimer_delay_us(uint32_t time);

#ifdef __cplusplus
}
#endif

#endif