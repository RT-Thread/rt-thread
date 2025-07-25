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
 * @file     drv_etb.h
 * @brief    header file for event trigger driver
 * @version  V1.0
 * @date     27. octorber 2017
 * @model    etb
 ******************************************************************************/

#ifndef _DRV_ETB_H_
#define _DRV_ETB_H_

#include <drv/common.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    ETB_HARDWARE_TRIG  = 0,           ///< etb channel inout is hardware trigger.
    ETB_SOFTWARE_TRIG                 ///< etb channel inout is software trigger.
} csi_etb_trig_mode_t;

typedef enum {
    ETB_CH_ONE_TRIGGER_ONE  = 0,      ///< one device trig one deivce
    ETB_CH_ONE_TRIGGER_MORE,          ///< one device trig two for more device
    ETB_CH_MORE_TRIGGER_ONE           ///< two or more device trig one deivce
} csi_etb_ch_type_t;

typedef struct {
    uint8_t               src_ip;     ///< a specific number represent a location in an source trigger location map to trigger other ip(s).
    uint8_t               dst_ip;     ///< a specific number represent an location in an dest trigger map to wait signal(s) from source ip(s) or location(s).
    csi_etb_trig_mode_t   trig_mode;  ///< the input source is hardware trigger or software trigger.
    csi_etb_ch_type_t     ch_type;    ///< channel type
} csi_etb_config_t;

/**
  \brief       Init the etb device
  \return      error code
*/
csi_error_t csi_etb_init(void);

/**
  \brief       Uninit the etb device
  \return      none
*/
void csi_etb_uninit(void);

/**
  \brief       alloc an etb channel
  \param[in]   ch_mode    etb channel work mode
  \return      channel id or CSI_ERROR
*/
int32_t csi_etb_ch_alloc(csi_etb_ch_type_t ch_type);

/**
  \brief       free an etb channel
  \param[in]   ch_id      etb channel work mode
  \return      none
*/
void csi_etb_ch_free(int32_t ch_id);

/**
  \brief       config etb channel
  \param[in]   ch_id      etb channel id
  \param[in]   config     the config structure for etb channel
  \return      csi error code
*/
csi_error_t csi_etb_ch_config(int32_t ch_id, csi_etb_config_t *config);

/**
  \brief       start an etb channel
  \param[in]   ch_id      etb channel id
  \return      none
*/
void csi_etb_ch_start(int32_t ch_id);

/**
  \brief       stop an etb channel
  \param[in]   etb        etb channel id
  \return      none
*/
void csi_etb_ch_stop(int32_t ch_id);

#endif /* _CSI_ETB_H_ */
