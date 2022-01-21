/*
 *  Change Logs:
 *  Date            Author          Notes
 *  2021-04-20      liuhy          the first version
 *
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

#ifndef __ES_CONF_INFO_PWM_H__
#define __ES_CONF_INFO_PWM_H__

#include "es_conf_info_map.h"
#include <ald_cmu.h>
#include <ald_timer.h>
#include <ald_gpio.h>


#define ES_C_PWM_OC_POL_HIGH   TIMER_OC_POLARITY_HIGH
#define ES_C_PWM_OC_POL_LOW    TIMER_OC_POLARITY_LOW

#define  ES_C_PWM_OC_MODE_PWM1     TIMER_OC_MODE_PWM1
#define  ES_C_PWM_OC_MODE_PWM2     TIMER_OC_MODE_PWM2



/* PWM 配置 */


/* codes_main */



#define ES_PWM_OC_POLARITY   ES_C_PWM_OC_POL_HIGH
#define ES_PWM_OC_MODE       ES_C_PWM_OC_MODE_PWM1

#ifndef ES_PWM_OC_POLARITY
#define ES_PWM_OC_POLARITY   ES_C_PWM_OC_POL_HIGH
#endif
#ifndef ES_PWM_OC_MODE
#define ES_PWM_OC_MODE       ES_C_PWM_OC_MODE_PWM2
#endif

#ifndef  ES_DEVICE_NAME_AD16C4T0_PWM
#define  ES_DEVICE_NAME_AD16C4T0_PWM     "pwm0"
#endif
#ifndef  ES_DEVICE_NAME_GP16C4T0_PWM
#define  ES_DEVICE_NAME_GP16C4T0_PWM     "pwm1"
#endif
#ifndef  ES_DEVICE_NAME_GP16C2T0_PWM
#define  ES_DEVICE_NAME_GP16C2T0_PWM     "pwm2"
#endif
#ifndef  ES_DEVICE_NAME_GP16C2T1_PWM
#define  ES_DEVICE_NAME_GP16C2T1_PWM     "pwm3"
#endif


#endif
