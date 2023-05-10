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

#ifndef __ES_CONF_INFO_I2C_H__
#define __ES_CONF_INFO_I2C_H__

#include "es_conf_info_map.h"
#include <ald_i2c.h>
#include <ald_gpio.h>
#include <rtdbg.h>

#define ES_C_I2C_STRETCH                 ALD_I2C_NOSTRETCH_DISABLE
#define ES_C_I2C_NO_STRETCH              ALD_I2C_NOSTRETCH_ENABLE

#define ES_C_I2C_GENERALCALL             ALD_I2C_GENERALCALL_ENABLE
#define ES_C_I2C_NO_GENERALCALL          ALD_I2C_GENERALCALL_DISABLE


#define ES_C_I2C_ADDR_7_MODE                ALD_I2C_ADDR_7BIT
#define ES_C_I2C_ADDR_10_MODE                ALD_I2C_ADDR_10BIT


/* I2C 配置 */



/* codes_main */





#ifndef  ES_DEVICE_NAME_I2C0
#define  ES_DEVICE_NAME_I2C0     "i2c0"
#endif

#ifndef  ES_DEVICE_NAME_I2C1
#define  ES_DEVICE_NAME_I2C1     "i2c1"
#endif

#ifndef  ES_I2C0_CLK_SPEED
#define ES_I2C0_CLK_SPEED                100000
#endif
#ifndef  ES_I2C0_OWN_ADDR1
#define ES_I2C0_OWN_ADDR1                0x20
#endif
#ifndef  ES_I2C0_GENERAL_CALL
#define ES_I2C0_GENERAL_CALL             ES_C_I2C_NO_GENERALCALL
#endif
#ifndef  ES_I2C0_STRETCH
#define ES_I2C0_STRETCH               ES_C_I2C_STRETCH
#endif
#ifndef ES_I2C0_ADDR_MODE
#define ES_I2C0_ADDR_MODE                ES_C_I2C_ADDR_7_MODE
#endif

#ifndef  ES_I2C1_CLK_SPEED
#define ES_I2C1_CLK_SPEED                100000
#endif
#ifndef  ES_I2C1_OWN_ADDR1
#define ES_I2C1_OWN_ADDR1                0x20
#endif
#ifndef  ES_I2C1_GENERAL_CALL
#define ES_I2C1_GENERAL_CALL             ES_C_I2C_NO_GENERALCALL
#endif
#ifndef  ES_I2C1_STRETCH
#define ES_I2C1_STRETCH               ES_C_I2C_STRETCH
#endif
#ifndef ES_I2C1_ADDR_MODE
#define ES_I2C1_ADDR_MODE                ES_C_I2C_ADDR_7_MODE
#endif



#endif
