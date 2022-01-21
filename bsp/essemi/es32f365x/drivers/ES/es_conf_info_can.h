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

#ifndef __ES_CONF_INFO_CAN_H__
#define __ES_CONF_INFO_CAN_H__

#include "es_conf_info_map.h"
#include <ald_can.h>
#include <ald_gpio.h>


/*默认的CAN硬件过滤器的编号   0 */
#define ES_C_CAN_DEFAULT_FILTER_NUMBER   0

/*硬件过滤器，过滤帧类型*/
#define ES_C_CAN_FILTER_FRAME_TYPE       0


#define ES_C_CAN_SJW_NUM_1   CAN_SJW_1
#define ES_C_CAN_SJW_NUM_2   CAN_SJW_2
#define ES_C_CAN_SJW_NUM_3   CAN_SJW_3
#define ES_C_CAN_SJW_NUM_4   CAN_SJW_4



/* CAN 配置 */

/* codes_main */



#ifndef  ES_DEVICE_NAME_CAN0
#define  ES_DEVICE_NAME_CAN0     "can0"
#endif

#ifndef  ES_CAN0_AUTO_BAN_RE_T
#define ES_CAN0_AUTO_BAN_RE_T    ES_C_DISABLE
#endif
#ifndef  ES_CAN0_SPEED
#define ES_CAN0_SPEED           1000000
#endif
#ifndef  ES_CAN0_SJW
#define ES_CAN0_SJW             ES_C_CAN_SJW_NUM_4
#endif

#define ES_CAN0_CONFIG        \
{                               \
        ES_CAN0_SPEED,              \
        RT_CANMSG_BOX_SZ,       \
        RT_CANSND_BOX_NUM,      \
        RT_CAN_MODE_NORMAL,     \
};
#endif
