/**
 * @file hal_rtc.h
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
#ifndef __HAL_RTC__H__
#define __HAL_RTC__H__

#ifdef __cplusplus
extern "C" {
#endif

#include "hal_common.h"

void rtc_init(uint64_t sleep_time);
void rtc_set_timestamp(uint64_t time_stamp);
uint64_t rtc_get_timestamp(void);
#ifdef __cplusplus
}
#endif
#endif
