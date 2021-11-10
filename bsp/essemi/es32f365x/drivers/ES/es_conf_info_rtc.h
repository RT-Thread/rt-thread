/*
 * Copyright (C) 2021 Shanghai Eastsoft Microelectronics Co., Ltd. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#ifndef __ES_CONF_INFO_RTC_H__
#define __ES_CONF_INFO_RTC_H__

#include <ald_cmu.h>
#include <ald_rtc.h>

/* RTC 配置 */

#define ES_C_RTC_SOURCE_LRC      RTC_SOURCE_LRC
#define ES_C_RTC_SOURCE_LOSC      RTC_SOURCE_LOSC

#define ES_RTC_CLK_SOURCE        ES_C_RTC_SOURCE_LOSC




/* codes_main */


#ifndef  ES_DEVICE_NAME_RTC
#define  ES_DEVICE_NAME_RTC     "rtc"
#endif

#endif
