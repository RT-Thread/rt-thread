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
 * 2019-11-09     wangyq        the first version
 * 2021-04-20     liuhy         the second version
 */

#ifndef DRV_CAN_H__
#define DRV_CAN_H__

#include <board.h>
#include <rtdevice.h>
#include <rtthread.h>
#include "es_conf_info_can.h"

#ifdef RT_USING_CAN
/* es32f0 can device */
struct es32f0_can
{
    can_handle_t CanHandle;
    can_filter_t FilterConfig;
    struct rt_can_device device;     /* inherit from can device */
};

int rt_hw_can_init(void);

#endif
#endif /*DRV_CAN_H__ */
