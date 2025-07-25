 /*
 * Copyright (C) 2017-2024 Alibaba Group Holding Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/******************************************************************************
 * @file     sensor.h
 * @brief    Header File for SENSOR Driver
 * @version  V1.0
 * @date     15. June 2020
 * @model    sensor
 ******************************************************************************/

#ifndef _DRV_SENSOR_H_
#define _DRV_SENSOR_H_

#include <drv/common.h>
#include <soc.h>

typedef enum {
    SENSOR_VDS_3V3_3V3 = 1,
    SENSOR_VDS_2V5_3V3,
    SENSOR_VDS_1V8_1V8,
    SENSOR_VDS_1V5_1V8,
    SENSOR_VDS_1V2_1V2,
    SENSOR_VDS_1V1_1V2
}drv_sensor_vds_t;

typedef enum {
    SENSOR_VHS_RANGE_15 = 0,
    SENSOR_VHS_RANGE_12,
    SENSOR_VHS_RANGE_9,
    SENSOR_VHS_RANGE_6,
}drv_sensor_vhs_t;

typedef enum {
    SENSOR_VLS_RANGE_6 = 0,
    SENSOR_VLS_RANGE_9,
    SENSOR_VLS_RANGE_12,
    SENSOR_VLS_RANGE_15,
}drv_sensor_vls_t;

typedef enum {
    SENSOR_TDHS_NEG_55 = 0,     ///< -55
    SENSOR_TDHS_NEG_50,
    SENSOR_TDHS_NEG_45,
    SENSOR_TDHS_NEG_40,
    SENSOR_TDHS_NEG_35,
    SENSOR_TDHS_NEG_30,
    SENSOR_TDHS_NEG_25,
    SENSOR_TDHS_NEG_20,
    SENSOR_TDHS_NEG_15,
    SENSOR_TDHS_NEG_10,
    SENSOR_TDHS_NEG_5,
    SENSOR_TDHS_NEG_0,
    SENSOR_TDHS_POS_5,          ///< +5
    SENSOR_TDHS_POS_10,
    SENSOR_TDHS_POS_15,
    SENSOR_TDHS_POS_20,
    SENSOR_TDHS_POS_25,
    SENSOR_TDHS_POS_30,
    SENSOR_TDHS_POS_35,
    SENSOR_TDHS_POS_40,
    SENSOR_TDHS_POS_45,
    SENSOR_TDHS_POS_50,
    SENSOR_TDHS_POS_55,
    SENSOR_TDHS_POS_60,
    SENSOR_TDHS_POS_65,
    SENSOR_TDHS_POS_70,
    SENSOR_TDHS_POS_75,
    SENSOR_TDHS_POS_80,
    SENSOR_TDHS_POS_85,
    SENSOR_TDHS_POS_90,
    SENSOR_TDHS_POS_95,
    SENSOR_TDHS_POS_100,
    SENSOR_TDHS_POS_105,
    SENSOR_TDHS_POS_110,
    SENSOR_TDHS_POS_115,
    SENSOR_TDHS_POS_120,
    SENSOR_TDHS_POS_125
}drv_sensor_tdhs_t;

typedef enum {
    SENSOR_TDLS_NEG_55 = 0,     ///< -55
    SENSOR_TDLS_NEG_50,
    SENSOR_TDLS_NEG_45,
    SENSOR_TDLS_NEG_40,
    SENSOR_TDLS_NEG_35,
    SENSOR_TDLS_NEG_30,
    SENSOR_TDLS_NEG_25,
    SENSOR_TDLS_NEG_20,
    SENSOR_TDLS_NEG_15,
    SENSOR_TDLS_NEG_10,
    SENSOR_TDLS_NEG_5,
    SENSOR_TDLS_NEG_0,
    SENSOR_TDLS_POS_5,          ///< +5
    SENSOR_TDLS_POS_10,
    SENSOR_TDLS_POS_15,
    SENSOR_TDLS_POS_20,
}drv_sensor_tdls_t;

typedef enum {
    SENSOR_FHS_RANGE_50 = 0,
    SENSOR_FHS_RANGE_30,
    SENSOR_FHS_RANGE_10,
    SENSOR_FHS_RANGE_5,
}drv_sensor_fhs_t;

typedef enum {
    SENSOR_FLS_RANGE_50 = 0,
    SENSOR_FLS_RANGE_30,
    SENSOR_FLS_RANGE_10,
    SENSOR_FLS_RANGE_5,
}drv_sensor_fls_t;

typedef enum {
    SENSOR_FHS_FREQ_33M = 0,
    SENSOR_FHS_FREQ_66M,
    SENSOR_FHS_FREQ_24M,
    SENSOR_FHS_FREQ_12M,
    SENSOR_FHS_FREQ_99M,
    SENSOR_FHS_FREQ_198M,
    SENSOR_FHS_FREQ_72M,
    SENSOR_FHS_FREQ_36M,
}drv_sensor_freq_t;

typedef enum {
    SENSOR_WARN_H = 0,
    SENSOR_WARN_L,
    SENSOR_WARN_RST,
}drv_sensor_warn_t;

/**
  \brief       Initialize Sensor VD
  \param[in]   vds   Voltage range
  \param[in]   vhs   Voltage high threshold
  \param[in]   vls   Voltage low threshold
  \param[in]   vtm   Used to modify the threshold value of the voltage detection point
  \return      Error code
*/
csi_error_t drv_sensor_vd_init(drv_sensor_vds_t vds,drv_sensor_vhs_t vhs,drv_sensor_vls_t vls,uint8_t vtm);

/**
  \brief       Get vd  warn
  \param[in]   warn  Vd warn select
  \return      Vd warn code
*/
uint32_t drv_sensor_vd_get_warn(drv_sensor_warn_t warn);

/**
  \brief       Initialize Sensor td
  \param[in]   hs   Temp high threshold
  \param[in]   ls   Temp low threshold
  \return      Error code
*/
csi_error_t drv_sensor_td_init(drv_sensor_tdhs_t hs,drv_sensor_tdls_t ls);

/**
  \brief       Get td  warn
  \param[in]   warn  Td warn select
  \return      Td warn code
*/
uint32_t drv_sensor_td_get_warn(drv_sensor_warn_t warn);

/**
  \brief       Initialize Sensor FD
  \param[in]   hs   Temp high threshold
  \param[in]   ls   Temp low threshold
  \return      Error code
*/
csi_error_t drv_sensor_fd_init(drv_sensor_freq_t freq,drv_sensor_fhs_t fhs,drv_sensor_fls_t fls);

/**
  \brief       Get fd  warn
  \param[in]   warn  Fd warn select
  \return      FD warn code
*/
uint32_t drv_sensor_fd_get_warn(drv_sensor_warn_t warn);

#endif /* _DRV_SENSOR_H_ */
