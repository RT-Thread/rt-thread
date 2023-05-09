/*
 * Copyright (C) 2022 Shanghai Eastsoft Microelectronics Co., Ltd.
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
 * Change Logs:
 * Date           Author        Notes
 * 2022-04-18     liuhy         the first version
 */

/* <<< Use Configuration Wizard in Context Menu >>>*/
#ifndef __BOARD_H__
#define __BOARD_H__

#include "ald_conf.h"

#include "rtconfig.h"
#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#include "es_conf_info_cmu.h"
#include "es_conf_info_dma.h"
#include "es_conf_info_map.h"
#include "es_conf_info_gpio.h"
#include "es_conf_info_adc.h"
#include "es_conf_info_hwtimer.h"
#include "es_conf_info_pwm.h"
#include "es_conf_info_uart.h"
#include "es_conf_info_spi.h"
#include "es_conf_info_i2c.h"
#include "es_conf_info_pm.h"

#define GET_PIN(port,pin)  (ES_PIN_GPIO_##port##_##pin)

extern int __bss_end__;
#define HEAP_BEGIN  ((void *)&__bss_end__)

#define HEAP_END    (0x20008000)

void rt_hw_board_init(void);

#endif
