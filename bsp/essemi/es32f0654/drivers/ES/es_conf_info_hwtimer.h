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

#ifndef __ES_CONF_INFO_HWTIMER_H__
#define __ES_CONF_INFO_HWTIMER_H__

#include <ald_cmu.h>
#include <ald_timer.h>

#define ES_C_HWTIMER_MODE_UP         HWTIMER_CNTMODE_UP
#define ES_C_HWTIMER_MODE_DOWN         HWTIMER_CNTMODE_DW

/* HWTIMER 配置 */

/* codes_main */



#ifndef  ES_AD16C4T0_HWTIMER_MODE
#define ES_AD16C4T0_HWTIMER_MODE          ES_C_HWTIMER_MODE_UP
#endif

#ifndef  ES_GP16C4T0_HWTIMER_MODE
#define ES_GP16C4T0_HWTIMER_MODE          ES_C_HWTIMER_MODE_UP
#endif
#ifndef  ES_GP16C2T0_HWTIMER_MODE
#define ES_GP16C2T0_HWTIMER_MODE          ES_C_HWTIMER_MODE_UP
#endif
#ifndef  ES_GP1624T1_HWTIMER_MODE
#define ES_GP16C2T1_HWTIMER_MODE          ES_C_HWTIMER_MODE_UP
#endif
#ifndef  ES_BS16T0_HWTIMER_MODE
#define ES_BS16T0_HWTIMER_MODE          ES_C_HWTIMER_MODE_UP
#endif
#ifndef  ES_BS16T1_HWTIMER_MODE
#define ES_BS16T1_HWTIMER_MODE          ES_C_HWTIMER_MODE_UP
#endif
#ifndef  ES_BS16T2_HWTIMER_MODE
#define ES_BS16T2_HWTIMER_MODE          ES_C_HWTIMER_MODE_UP
#endif
#ifndef  ES_BS16T3_HWTIMER_MODE
#define ES_BS16T3_HWTIMER_MODE          ES_C_HWTIMER_MODE_UP
#endif




#define ES_AD16C4T0_HWTIMER_PRES          1
#define ES_GP16C4T0_HWTIMER_PRES          1
#define ES_GP16C2T0_HWTIMER_PRES          1
#define ES_GP16C2T1_HWTIMER_PRES          1
#define ES_BS16T0_HWTIMER_PRES          1
#define ES_BS16T1_HWTIMER_PRES          1
#define ES_BS16T2_HWTIMER_PRES          1
#define ES_BS16T3_HWTIMER_PRES          1

#ifndef  ES_DEVICE_NAME_AD16C4T0_HWTIMER
#define  ES_DEVICE_NAME_AD16C4T0_HWTIMER     "timer0"
#endif
#ifndef  ES_DEVICE_NAME_GP16C4T0_HWTIMER
#define  ES_DEVICE_NAME_GP16C4T0_HWTIMER     "timer1"
#endif
#ifndef  ES_DEVICE_NAME_GP16C2T0_HWTIMER
#define  ES_DEVICE_NAME_GP16C2T0_HWTIMER     "timer2"
#endif
#ifndef  ES_DEVICE_NAME_GP16C2T1_HWTIMER
#define  ES_DEVICE_NAME_GP16C2T1_HWTIMER     "timer3"
#endif
#ifndef  ES_DEVICE_NAME_BS16T0_HWTIMER
#define  ES_DEVICE_NAME_BS16T0_HWTIMER     "timer4"
#endif
#ifndef  ES_DEVICE_NAME_BS16T1_HWTIMER
#define  ES_DEVICE_NAME_BS16T1_HWTIMER     "timer5"
#endif
#ifndef  ES_DEVICE_NAME_BS16T2_HWTIMER
#define  ES_DEVICE_NAME_BS16T2_HWTIMER     "timer6"
#endif
#ifndef  ES_DEVICE_NAME_BS16T3_HWTIMER
#define  ES_DEVICE_NAME_BS16T3_HWTIMER     "timer7"
#endif


#endif
