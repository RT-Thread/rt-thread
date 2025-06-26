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
 * @file     drv/hmac.h
 * @brief    Header File for HMAC
 * @version  V1.0
 * @date     27. Apri 2023
 * @model    hmac
 ******************************************************************************/
#ifndef _DRV_HMAC_H_
#define _DRV_HMAC_H_

#include <drv/common.h>
#include <drv/dma.h>
#include <drv/sha.h>

#ifdef __cplusplus
extern "C" {
#endif

/****** HMAC Event ******/
typedef enum {
    HMAC_EVENT_COMPLETE    = 0U,           /* Calculate completed */
    HMAC_EVENT_ERROR                       /* Calculate error */
} csi_hmac_event_t;

/****** HMAC Context ******/
typedef struct {
    csi_sha_mode_t   mode;                 /* SHA mode */
    uint32_t         total[2];             /* Number of bytes processed */
    uint8_t          buffer[128];          /* Data block being processed */
} csi_hmac_context_t;

/****** HMAC Ctrl ******/
typedef struct csi_hmac {
    csi_dev_t   dev;
    void        *priv;
}csi_hmac_t;

/**
  \brief       Initialize MAC Interface. Initializes the resources needed for the MAC interface
  \param[in]   mac       operate handle.
  \param[in]   idx       index of mac
  \return      error code \ref csi_error_t
*/
csi_error_t csi_hmac_init(csi_hmac_t *mac, uint32_t idx);

/**
  \brief       De-initialize MAC Interface. stops operation and releases the software resources used by the interface
  \param[in]   mac       mac handle to operate.
  \return      none
*/
void csi_hmac_uninit(csi_hmac_t *mac);

/**
  \brief       MAC set key function.
  \param[in]   mac       mac handle to operate.
  \param[in]   key       Pointer to the mac key.
  \param[in]   key_len   Length of key.
  \return      error code \ref csi_error_t
*/
csi_error_t csi_hmac_set_key(csi_hmac_t *mac, uint8_t *key, uint32_t key_len);

/**
  \brief       MAC start operation function.
  \param[in]   mac        mac handle to operate.
  \param[in]   context    mac context pointer.
  \param[in]   mode       sc_sha_mode_t.
  \return      error code \ref csi_error_t
*/
csi_error_t csi_hmac_start(csi_hmac_t *mac, csi_hmac_context_t *context, csi_sha_mode_t mode);

/**
  \brief       MAC start operation function.
  \param[in]   mac        mac handle to operate.
  \param[in]   msg        Pointer to the mac input message.
  \param[in]   msg_len    Length of msg.
  \return      error code \ref csi_error_t
*/
csi_error_t csi_hmac_update(csi_hmac_t *mac, csi_hmac_context_t *context, uint8_t *msg, uint32_t msg_len);

/**
  \brief       MAC start operation function.
  \param[in]   mac        mac handle to operate.
  \param[out]  out        mac buffer, malloc by caller.
  \param[out]  out_len    out mac length,
  \return      error code \ref csi_error_t
*/
csi_error_t csi_hmac_finish(csi_hmac_t *mac, csi_hmac_context_t *context, uint8_t *out, uint32_t *out_len);

/**
  \brief       MAC cacl operation function.
  \param[in]   mac        mac handle to operate.
  \param[in]   mode       sc_sha_mode_t.
  \param[in]   msg        Pointer to the mac input message.
  \param[in]   msg_len    Length of msg.
  \param[out]  out        mac buffer, malloc by caller.
  \param[out]  out_len    out mac length,
  \return      error code \ref csi_error_t
*/
csi_error_t csi_hmac_calc(csi_hmac_t *mac, csi_sha_mode_t mode, uint8_t *msg,
                            uint32_t msg_len, uint8_t *out, uint32_t *out_len);
#ifdef __cplusplus
}
#endif

#endif /* _SC_MAC_H_ */
