/*
 * Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd.
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
 * 2019-01-24     wangyq        the first version
 * 2021-04-20     liuhy         the second version
 */

#ifndef DRV_SPI_H__
#define DRV_SPI_H__

#include <rtthread.h>
#include <rthw.h>
#include <rtdevice.h>

#include "es_conf_info_spi.h"

struct es32f0_hw_spi_cs
{
    rt_uint32_t pin;
};

/* cannot be used before completion init */
rt_err_t es32f0_spi_device_attach(rt_uint32_t pin, const char *bus_name, const char *device_name);
int rt_hw_spi_init(void);

#endif
