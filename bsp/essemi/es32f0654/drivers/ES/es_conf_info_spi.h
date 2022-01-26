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

#ifndef __ES_CONF_INFO_SPI_H__
#define __ES_CONF_INFO_SPI_H__

#include "es_conf_info_map.h"
#include <ald_spi.h>
#include <ald_gpio.h>
#include <ald_cmu.h>

/* SPI 配置 */

#define SPI_BUS_CONFIG(_CONF_,_I_)       do{_CONF_.mode = 0U;                                         \
                                            _CONF_.mode |= ( ES_SPI##_I_##_MASTER_SLAVE |             \
                                                             ES_SPI##_I_##_WIRE_3_4     |             \
                                                             ES_SPI##_I_##_CPHA_1_2     |             \
                                                             ES_SPI##_I_##_CPOL_H_L     |             \
                                                             ES_SPI##_I_##_CS           |             \
                                                             ES_SPI##_I_##_M_L_SB          );         \
                                            _CONF_.data_width = ES_SPI##_I_##_DATA_W;                 \
                                            _CONF_.max_hz = ES_SPI##_I_##_MAX_HZ;                     \
                                            }while(0)


//    spi_config.mode &= ~RT_SPI_SLAVE; /* 主机模式 */
//    spi_config.mode &= ~RT_SPI_3WIRE; /* 4线，双向传输 */
//    spi_config.mode |= RT_SPI_CPHA;   /* 第二边沿采样 */
//    spi_config.mode |= RT_SPI_CPOL;   /* 空闲高电平 */
//    spi_config.mode |= RT_SPI_NO_CS;  /* 禁用软件从机选择管理 */
//    spi_config.mode |= RT_SPI_MSB;    /* 高位在前 */
//    spi_config.data_width = 8;        /* 数据长度：8 */
//    spi_config.max_hz = 2000000;      /* 最快时钟频率 */

#define ES_C_SPI_CLK_POL_HIGH            RT_SPI_CPOL
#define ES_C_SPI_CLK_POL_LOW             !RT_SPI_CPOL

#define ES_C_SPI_CLK_PHA_FIRST            !RT_SPI_CPHA
#define ES_C_SPI_CLK_PHA_SECOND           RT_SPI_CPHA

#define ES_C_SPI_MSB                      RT_SPI_MSB
#define ES_C_SPI_LSB                      RT_SPI_LSB

#define ES_C_SPI_CS_LOW_LEVEL             0
#define ES_C_SPI_CS_HIGH_LEVEL            1

/* codes_main */


#ifndef  ES_DEVICE_NAME_SPI0_BUS
#define  ES_DEVICE_NAME_SPI0_BUS     "spi0"
#endif
#ifndef  ES_DEVICE_NAME_SPI0_DEV0
#define  ES_DEVICE_NAME_SPI0_DEV0     "spi00"
#endif

#ifndef  ES_DEVICE_NAME_SPI1_BUS
#define  ES_DEVICE_NAME_SPI1_BUS     "spi1"
#endif
#ifndef  ES_DEVICE_NAME_SPI1_DEV0
#define  ES_DEVICE_NAME_SPI1_DEV0     "spi10"
#endif


#define ES_SPI_CS_LEVEL               ES_C_SPI_CS_LOW_LEVEL

#ifndef   ES_SPI0_CPHA_1_2
#define   ES_SPI0_CPHA_1_2               ES_C_SPI_CLK_PHA_SECOND
#endif
#ifndef   ES_SPI0_CPOL_H_L
#define   ES_SPI0_CPOL_H_L               ES_C_SPI_CLK_POL_HIGH
#endif
#ifndef   ES_SPI0_M_L_SB
#define   ES_SPI0_M_L_SB                 RT_SPI_MSB
#endif
#ifndef   ES_SPI0_MAX_HZ
#define   ES_SPI0_MAX_HZ                 2000000
#endif
#ifndef   ES_SPI0_NSS_PIN
#define ES_SPI0_NSS_PIN 0xFFFFFFFF
#endif

#ifndef   ES_SPI1_CPHA_1_2
#define   ES_SPI1_CPHA_1_2               ES_C_SPI_CLK_PHA_SECOND
#endif
#ifndef   ES_SPI1_CPOL_H_L
#define   ES_SPI1_CPOL_H_L               ES_C_SPI_CLK_POL_HIGH
#endif
#ifndef   ES_SPI1_M_L_SB
#define   ES_SPI1_M_L_SB                 RT_SPI_MSB
#endif
#ifndef   ES_SPI1_MAX_HZ
#define   ES_SPI1_MAX_HZ                 2000000
#endif
#ifndef   ES_SPI1_NSS_PIN
#define ES_SPI1_NSS_PIN 0xFFFFFFFF
#endif



#define   ES_SPI0_MASTER_SLAVE           !RT_SPI_SLAVE
#define   ES_SPI0_WIRE_3_4               !RT_SPI_3WIRE
#define   ES_SPI0_CS                     RT_SPI_NO_CS
#define   ES_SPI0_DATA_W                 8

#define   ES_SPI1_MASTER_SLAVE           !RT_SPI_SLAVE
#define   ES_SPI1_WIRE_3_4               !RT_SPI_3WIRE
#define   ES_SPI1_CS                     RT_SPI_NO_CS
#define   ES_SPI1_DATA_W                 8


#endif
