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

#ifndef __ES_CONF_INFO_ADC_H__
#define __ES_CONF_INFO_ADC_H__

#include "es_conf_info_map.h"

#include <ald_adc.h>


#define ES_C_ADC_CLK_DIV_1     ADC_CKDIV_1
#define ES_C_ADC_CLK_DIV_2     ADC_CKDIV_2
#define ES_C_ADC_CLK_DIV_4     ADC_CKDIV_4
#define ES_C_ADC_CLK_DIV_8     ADC_CKDIV_8
#define ES_C_ADC_CLK_DIV_16     ADC_CKDIV_16
#define ES_C_ADC_CLK_DIV_32     ADC_CKDIV_32
#define ES_C_ADC_CLK_DIV_64     ADC_CKDIV_64
#define ES_C_ADC_CLK_DIV_128     ADC_CKDIV_128

#define ES_C_ADC_ALIGN_RIGHT        ADC_DATAALIGN_RIGHT
#define ES_C_ADC_ALIGN_LEFT        ADC_DATAALIGN_LEFT

#define ES_C_ADC_CONV_BIT_6        ADC_CONV_BIT_6
#define ES_C_ADC_CONV_BIT_8        ADC_CONV_BIT_8
#define ES_C_ADC_CONV_BIT_10        ADC_CONV_BIT_10
#define ES_C_ADC_CONV_BIT_12        ADC_CONV_BIT_12

#define ES_C_ADC_SAMPLE_TIME_1       ADC_SAMPLETIME_1
#define ES_C_ADC_SAMPLE_TIME_2       ADC_SAMPLETIME_2
#define ES_C_ADC_SAMPLE_TIME_4       ADC_SAMPLETIME_4
#define ES_C_ADC_SAMPLE_TIME_15       ADC_SAMPLETIME_15

/* ADC 配置 */

/* codes_main */


#define ES_ADC0_ALIGN      ES_C_ADC_ALIGN_RIGHT
#define ES_ADC1_ALIGN      ES_C_ADC_ALIGN_RIGHT
#define ES_ADC1_DATA_BIT   ES_C_ADC_CONV_BIT_12
#define ES_ADC0_DATA_BIT   ES_C_ADC_CONV_BIT_12

#ifndef  ES_DEVICE_NAME_ADC0
#define  ES_DEVICE_NAME_ADC0     "adc0"
#endif
#ifndef  ES_DEVICE_NAME_ADC1
#define  ES_DEVICE_NAME_ADC1     "adc1"
#endif

#ifndef  ES_ADC0_CLK_DIV
#define ES_ADC0_CLK_DIV    ES_C_ADC_CLK_DIV_128
#endif
#ifndef  ES_ADC0_ALIGN
#define ES_ADC0_ALIGN      ES_C_ADC_ALIGN_RIGHT
#endif
#ifndef  ES_ADC0_DATA_BIT
#define ES_ADC0_DATA_BIT   ES_C_ADC_CONV_BIT_12
#endif
#ifndef  ES_ADC0_NCH_SAMPLETIME
#define ES_ADC0_NCH_SAMPLETIME    ES_C_ADC_SAMPLE_TIME_4
#endif

#ifndef  ES_ADC1_CLK_DIV
#define ES_ADC1_CLK_DIV    ES_C_ADC_CLK_DIV_128
#endif
#ifndef  ES_ADC1_ALIGN
#define ES_ADC1_ALIGN      ES_C_ADC_ALIGN_RIGHT
#endif
#ifndef  ES_ADC1_DATA_BIT
#define ES_ADC1_DATA_BIT   ES_C_ADC_CONV_BIT_12
#endif
#ifndef  ES_ADC1_NCH_SAMPLETIME
#define ES_ADC1_NCH_SAMPLETIME    ES_C_ADC_SAMPLE_TIME_4
#endif

#endif
