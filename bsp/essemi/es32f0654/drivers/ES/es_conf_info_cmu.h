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

#ifndef __ES_CONF_INFO_CMU_H__
#define __ES_CONF_INFO_CMU_H__


#include <ald_cmu.h>


/* 时钟树 配置 */

#define   ES_C_MUL_9          CMU_PLL1_OUTPUT_36M
#define   ES_C_MUL_12         CMU_PLL1_OUTPUT_48M

#define  ES_C_DIV_1          CMU_DIV_1
#define  ES_C_DIV_2          CMU_DIV_2
#define  ES_C_DIV_4          CMU_DIV_4
#define  ES_C_DIV_8          CMU_DIV_8
#define  ES_C_DIV_16          CMU_DIV_16
#define  ES_C_DIV_32          CMU_DIV_32
#define  ES_C_DIV_64          CMU_DIV_64
#define  ES_C_DIV_128          CMU_DIV_128
#define  ES_C_DIV_256          CMU_DIV_256
#define  ES_C_DIV_512          CMU_DIV_512
#define  ES_C_DIV_1024          CMU_DIV_1024
#define  ES_C_DIV_2048          CMU_DIV_2048
#define  ES_C_DIV_4096          CMU_DIV_4096

#define  ES_C_HOSC_DIV_1        CMU_PLL1_INPUT_HOSC
#define  ES_C_HOSC_DIV_2        CMU_PLL1_INPUT_HOSC_2
#define  ES_C_HOSC_DIV_3        CMU_PLL1_INPUT_HOSC_3
#define  ES_C_HOSC_DIV_4        CMU_PLL1_INPUT_HOSC_4
#define  ES_C_HOSC_DIV_5        CMU_PLL1_INPUT_HOSC_5
#define  ES_C_HOSC_DIV_6        CMU_PLL1_INPUT_HOSC_6
#define  ES_C_HRC_DIV_6         CMU_PLL1_INPUT_HRC_6





#define   ES_PLL1_REFER_CLK           ES_C_HOSC_DIV_3
#define   ES_PLL1_OUT_CLK             ES_C_MUL_12
#define   ES_CMU_PLL1_EN              ES_C_ENABLE
#define   ES_CMU_PLL1_SAFE_EN         ES_C_DISABLE
#define   ES_CMU_LOSC_EN              ES_C_ENABLE
#define   ES_CMU_LRC_EN               ES_C_ENABLE
#define   ES_CMU_HOSC_EN              ES_C_ENABLE
#define   ES_CMU_HRC_EN               ES_C_ENABLE
#define   ES_CMU_SYS_DIV              ES_C_DIV_1
#define   ES_CMU_HCLK_1_DIV           ES_C_DIV_1
#define   ES_CMU_PCLK_1_DIV           ES_C_DIV_1
#define   ES_CMU_PCLK_2_DIV           ES_C_DIV_1
#define   ES_SYS_CLK_SOURSE           CMU_CLOCK_PLL1
#define   ES_PLL_CLK                  48000000
#define   ES_SYS_SOURCE_CLK           48000000
#define   ES_SYS_CLK                  48000000
#define   ES_PCLK1_CLK                48000000
#define   ES_PCLK2_CLK                48000000
#define   ES_HCLK1_CLK                48000000
#define   ES_CMU_EXTERN_CLK_LOSC      32768
#define   ES_CMU_EXTERN_CLK_HOSC      12000000




#endif
